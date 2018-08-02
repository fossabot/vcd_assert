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

#ifndef LIBVCD_SERIALIZE_ENUM_HPP
#define LIBVCD_SERIALIZE_ENUM_HPP

#include "../types/enums.hpp"

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <string_view>

namespace VCD {

/// Convert ScopeType enum to string representation
/// \param st The ScopeType to convert.
///           Must be in valid enum state undefined behaviour otherwise
/// \returns static view of ScopeType string
constexpr std::string_view scope_type_to_string(ScopeType st) noexcept
{
  switch (st) {
  case ScopeType::begin:
    return "begin";
  case ScopeType::fork:
    return "fork";
  case ScopeType::function:
    return "function";
  case ScopeType::module:
    return "module";
  case ScopeType::task:
    return "task";
  default:                                           // LCOV_EXCL_LINE
    std::puts("INTERNAL ERROR: Invalid enum state"); // LCOV_EXCL_LINE
    std::abort();                                    // LCOV_EXCL_LINE
  }
}

/// Convert TimeUnit enum to string representation
/// \param tu The TimeUnit to convert.
///           Must be in valid enum state undefined behaviour otherwise
/// \returns static view of TimeUnit string
constexpr std::string_view time_unit_to_string(TimeUnit tu) noexcept
{
  switch (tu) {
  case TimeUnit::s:
    return "s";
  case TimeUnit::ms:
    return "ms";
  case TimeUnit::us:
    return "us";
  case TimeUnit::ns:
    return "ns";
  case TimeUnit::ps:
    return "ps";
  case TimeUnit::fs:
    return "fs";
  default:                                           // LCOV_EXCL_LINE
    std::puts("INTERNAL ERROR: Invalid enum state"); // LCOV_EXCL_LINE
    std::abort();                                    // LCOV_EXCL_LINE
  }
}

/// Convert TimeNumber enum to string representation
/// \param tn The TimeNumber to convert.
///           Must be in valid enum state undefined behaviour otherwise
/// \returns static view of TimeNumber string
constexpr std::string_view time_number_to_string(TimeNumber tn) noexcept
{
  switch (tn) {
  case TimeNumber::_1:
    return "1";
  case TimeNumber::_10:
    return "10";
  case TimeNumber::_100:
    return "100";
  default:                                           // LCOV_EXCL_LINE
    std::puts("INTERNAL ERROR: Invalid enum state"); // LCOV_EXCL_LINE
    std::abort();                                    // LCOV_EXCL_LINE
  }
}

/// Convert VarNumber enum to string representation
/// \param vr The VarNumber to convert.
///           Must be in valid enum state undefined behaviour otherwise
/// \returns static view of VarType string
constexpr std::string_view var_type_to_string(VarType vr) noexcept
{
  switch (vr) {
  case VarType::event:
    return "event";
  case VarType::integer:
    return "integer";
  case VarType::parameter:
    return "parameter";
  case VarType::real:
    return "real";
  case VarType::realtime:
    return "realtime";
  case VarType::reg:
    return "reg";
  case VarType::supply0:
    return "supply0";
  case VarType::supply1:
    return "supply1";
  case VarType::time:
    return "time";
  case VarType::tri:
    return "tri";
  case VarType::triand:
    return "triand";
  case VarType::trior:
    return "trior";
  case VarType::trireg:
    return "trireg";
  case VarType::tri0:
    return "tri0";
  case VarType::tri1:
    return "tri1";
  case VarType::wand:
    return "wand";
  case VarType::wire:
    return "wire";
  case VarType::wor:
    return "wor";
  default:                                           // LCOV_EXCL_LINE
    std::puts("INTERNAL ERROR: Invalid enum state"); // LCOV_EXCL_LINE
    std::abort();                                    // LCOV_EXCL_LINE
  }
}

/// Convert Value enum to char representation
/// \param v The Value to convert.
///          Must be in valid enum state undefined behaviour otherwise
/// \returns char representing the Value
constexpr char value_to_char(Value v) noexcept
{
  switch (v) {
  case Value::zero:
    return '0';
  case Value::one:
    return '1';
  case Value::z:
    return 'Z';
  case Value::x:
    return 'X';
  default:                                           // LCOV_EXCL_LINE
    std::puts("INTERNAL ERROR: Invalid enum state"); // LCOV_EXCL_LINE
    std::abort();                                    // LCOV_EXCL_LINE
  }
}

/// Convert Value enum to string representation
/// \param v The Value to convert.
///          Must be in valid enum state undefined behaviour otherwise
/// \returns static view of Value string
constexpr std::string_view value_to_string(Value v)
{
  switch (v) {
  case Value::zero:
    return "0";
  case Value::one:
    return "1";
  case Value::z:
    return "Z";
  case Value::x:
    return "X";
  default:                                           // LCOV_EXCL_LINE
    std::puts("INTERNAL ERROR: Invalid enum state"); // LCOV_EXCL_LINE
    std::abort();                                    // LCOV_EXCL_LINE
  }
}

} // namespace VCD

#endif // LIBVCD_SERIALIZE_ENUM_HPP
