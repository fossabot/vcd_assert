// ============================================================================
// Copyright 2018 Paul le Roux and Calvin Maree
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
// ============================================================================

#include "vcd/types/header_reader.hpp"

#include <cassert>

using namespace VCD;

HeaderReader::HeaderReader() { header_ = std::make_unique<Header>(); }

void HeaderReader::scope(ScopeType type, std::string name)
{
  auto &scopes_ref = header_->scopes_;

  if (scope_stack_.empty()) {
    if (header_->num_scopes() > 0)
      throw std::runtime_error("Cannot have more than one base scope");

    // Create root scope
    scopes_ref.emplace_back(type, std::move(name));
    scope_stack_.push_back(0);
  } else {

    auto &current_scope_ref = header_->scopes_.at(scope_stack_.back());

    if (current_scope_ref.contains_scope(name))
      throw std::runtime_error("Duplicate scope name");

    // Create scope within a scope
    auto index = scopes_ref.size();
    current_scope_ref.child_scopes_[name] = index;
    scopes_ref.emplace_back(type, std::move(name));

    // Make new scope active
    scope_stack_.push_back(index);
  }
}

void HeaderReader::scope(VCD::ScopeDataView scope)
{
  this->scope(scope.type, std::string(scope.identifier));
}

void HeaderReader::upscope()
{
  if (scope_stack_.empty())
    throw std::runtime_error("Cannot upscope if there is no scope!");

  scope_stack_.pop_back();
}

void HeaderReader::var(VarType type, std::size_t size,
                       std::string identifier_code, std::string reference)
{
  if (scope_stack_.empty())
    throw std::runtime_error("Variable must have scope");

  // Grab references for convenience
  auto &variables_ref = header_->variables_;
  auto &current_scope_ref = header_->scopes_.at(scope_stack_.back());
  auto &id_codes_ref = header_->id_codes_;

  auto &id_code_map_ref = header_->var_id_code_map_;

  if (current_scope_ref.contains_variable(reference))
    throw std::runtime_error("Duplicate variable reference");

  std::size_t id_code_index;

  if (id_code_map_ref.has_name(identifier_code)) {
    // Check that existing identifier_code has the same type
    id_code_index = id_code_map_ref.get_index(identifier_code);

    auto &id_code_ref = id_codes_ref.at(id_code_index);
    assert(id_code_ref.get_id_code() == identifier_code);

    // Size must always match
    bool same = id_code_ref.get_size() == size;

    // Don't allow real's to alias types that aren't real's
    if(id_code_ref.get_type() == VCD::VarType::real)
      same &= type == VCD::VarType::real;

    if (!same)
      throw std::runtime_error("Same identifier code with different types");
  } else {
    // Add new identifier_code
    id_code_index = id_code_map_ref.add_new_name(identifier_code);
    assert(id_code_index == id_codes_ref.size());

    id_codes_ref.emplace_back(type, size, identifier_code);
  }

  auto var_index = variables_ref.size();
  variables_ref.emplace_back(id_code_index, reference);
  current_scope_ref.child_variables_[reference] = var_index;
}

void HeaderReader::var(VCD::VariableView variable)
{
  this->var(variable.type, variable.size, std::string(variable.identifier_code),
            std::string(variable.reference));
}

void HeaderReader::version(std::string version_string)
{
  if (has_version())
    throw std::runtime_error("Header already has version property");

  header_->version_ = std::move(version_string);
}

void HeaderReader::overwrite_version(std::string version_string) noexcept
{
  header_->version_ = std::move(version_string);
}

bool HeaderReader::has_version() const noexcept
{
  return header_->has_version();
}

void HeaderReader::date(std::string date_string)
{
  if (has_date())
    throw std::runtime_error("Header already has date property");

  header_->date_ = std::move(date_string);
}

void HeaderReader::overwrite_date(std::string date_string) noexcept
{
  header_->date_ = std::move(date_string);
}

bool HeaderReader::has_date() const noexcept { return header_->has_date(); }

void HeaderReader::timescale(TimeNumber number, TimeUnit unit)
{
  if (has_timescale())
    throw std::runtime_error("Header already has version property");

  header_->time_scale_ = TimeScale{number, unit};
}

void HeaderReader::timescale(TimeScaleView time_scale)
{
  timescale(time_scale.number, time_scale.unit);
}

void HeaderReader::overwrite_timescale(TimeNumber number,
                                       TimeUnit unit) noexcept
{
  header_->time_scale_ = TimeScale{number, unit};
}

bool HeaderReader::has_timescale() const noexcept
{
  return header_->has_time_scale();
}

Header HeaderReader::release()
{
  if (!scope_stack_.empty())
    throw std::runtime_error(
        "Cannot release Header while there is still scope");

  auto tmp = std::make_unique<Header>();
  std::swap(tmp, header_);

  return std::move(*tmp);
}
