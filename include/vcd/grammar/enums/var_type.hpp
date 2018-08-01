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

#ifndef LIBVCD_GRAMMAR_ENUMS_VAR_TYPE_HPP
#define LIBVCD_GRAMMAR_ENUMS_VAR_TYPE_HPP

#include "../../types/enums.hpp"

#include <parse/grammar/base.h>

namespace VCD::Grammar {

using namespace Parse::Grammar::Base;

// clang-format off

/// Variable types
struct var_event : string<'e','v','e','n','t'> {
  static constexpr auto value = VarType::event;
};

struct var_integer : string<'i','n','t','e','g','e','r'> {
  static constexpr auto value = VarType::integer;
};

struct var_parameter : string<'p','a','r','a','m','e','t','e','r'> {
  static constexpr auto value = VarType::parameter;
};

struct var_real : string<'r','e','a','l'> {
  static constexpr auto value = VarType::real;
};

struct var_realtime : string<'r','e','a','l','t','i','m','e'> {
  static constexpr auto value = VarType::realtime;
};

struct var_reg : string<'r','e','g'> {
  static constexpr auto value = VarType::reg;
};

struct var_supply0 : string<'s','u','p','p','l','y','0'> {
  static constexpr auto value = VarType::supply0;
};

struct var_supply1 : string<'s','u','p','p','l','y','1'> {
  static constexpr auto value = VarType::supply1;
};

struct var_time : string<'t','i','m','e'> {
  static constexpr auto value = VarType::time;
};

struct var_tri : string<'t','r','i'> {
  static constexpr auto value = VarType::tri;
};

struct var_triand : string<'t','r','i','a','n','d'> {
  static constexpr auto value = VarType::triand;
};

struct var_trior : string<'t','r','i','o','r'> {
  static constexpr auto value = VarType::trior;
};

struct var_trireg : string<'t','r','i','r','e','g'> {
  static constexpr auto value = VarType::trireg;
};

struct var_tri0 : string<'t','r','i','0'> {
  static constexpr auto value = VarType::tri0;
};

struct var_tri1 : string<'t','r','i','1'> {
  static constexpr auto value = VarType::tri1;
};

struct var_wand : string<'w','a','n','d'> {
  static constexpr auto value = VarType::wand;
};

struct var_wire : string<'w','i','r','e'> {
  static constexpr auto value = VarType::wire;
};

struct var_wor : string<'w','o','r'> {
  static constexpr auto value = VarType::wor;
};

struct var_type : sor<
  var_event, var_integer, var_parameter, var_realtime, var_real, var_reg,
  var_supply0, var_supply1, var_time, var_triand, var_trior,
  var_trireg, var_tri0, var_tri1, var_tri, var_wand, var_wire, var_wor
> {
  static constexpr auto error() { return "Expected variable type"; }
};

// clang-format on

} // namespace VCD::Grammar

#endif // LIBVCD_GRAMMAR_ENUMS_VAR_TYPE_HPP
