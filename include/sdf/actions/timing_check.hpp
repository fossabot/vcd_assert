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

#ifndef LIBSDF_ACTIONS_TIMINGCHECK_HPP
#define LIBSDF_ACTIONS_TIMINGCHECK_HPP

#include <sdf/actions/base.hpp>
#include <sdf/actions/constants.hpp>
#include <sdf/actions/values.hpp>
#include <sdf/actions/timing.hpp>

#include <sdf/grammar/timing.hpp>

#include <sdf/types/timing_check.hpp>
#include <sdf/types/timing.hpp>

#include <fmt/format.h>

using namespace fmt::literals;

namespace SDF{
namespace Actions{

using namespace Parse;  

struct EqualityOperatorAction : all_dispatch<apply0<Apply::rule_value>> {
  using state = EqualityOperator;
};

struct NodeConstantEqualityAction : multi_dispatch<
  Grammar::scalar_node, inner_action<
    ScalarNodeAction, Storage::member<&NodeConstantEquality::left>
  >,
  Grammar::equality_operator, inner_action<
    EqualityOperatorAction, Storage::member<&NodeConstantEquality::op>
  >,
  Grammar::scalar_constant, inner_action<
    BinaryAction, Storage::member<&NodeConstantEquality::right>
  >
>{
  using state = NodeConstantEquality;
};

struct InvertedNodeStorage{
  static bool store(InvertedNode &in, Node n) {
    in.type = std::move(n.type);
    in.basename_identifier = std::move(n.basename_identifier);
    
    if(n.edge.has_value()){
      in.edge = std::move(n.edge);
    }
    if(n.hierarchical_identifier.has_value()){
      in.hierarchical_identifier = std::move(n.hierarchical_identifier);
    }
    if(n.start.has_value()){
      in.start = std::move(n.start);
    }
    if(n.end.has_value()){
      in.end = std::move(n.end);
    }
    return true;
  }
};

struct InvertedNodeAction : single_dispatch<
  Grammar::scalar_node, inner_action<
    ScalarNodeAction, InvertedNodeStorage
  >
>{
  using state = InvertedNode;
};

struct TimingCheckConditionAction : multi_dispatch<
  Grammar::inversion_condition, inner_action<
    InvertedNodeAction, Storage::member<&TimingCheckCondition::value>
  >,
  Grammar::node_constant_equality_condition, inner_action<
    NodeConstantEqualityAction, Storage::member<&TimingCheckCondition::value>
  >,
  Grammar::scalar_node, inner_action<
    ScalarNodeAction, Storage::member<&TimingCheckCondition::value>
  >
>{
  using state = TimingCheckCondition;
};


// struct PortCheckPortStorage {
//   // static bool store(PortTimingCheck &ptc, EdgeType edge, Node port) {
//   static bool store(PortTimingCheck &ptc, Node inner) {
//     // ptc.edge = std::move(inner.edge);
//     ptc.port = std::move(inner);
//     return true;
//   }
// };

struct PortCheckAction : multi_dispatch<
  Grammar::qstring, inner_action<
    QStringAction, Storage::member<&PortTimingCheck::symbolic_name>
  >,
  Grammar::timing_check_condition, inner_action<
   TimingCheckConditionAction, 
   Storage::member<&PortTimingCheck::timing_check_condition>
  >,
  Grammar::port_spec, inner_action<
    PortSpecAction, Storage::member<&PortTimingCheck::port>
  >
>{
  using state = PortTimingCheck;
};

struct HoldTimingCheckAction : multi_dispatch<
  Grammar::port_tchk_1, inner_action<
    PortCheckAction, Storage::member<&Hold::trig>>,
  Grammar::port_tchk_2, inner_action<
    PortCheckAction, Storage::member<&Hold::reg>>,
  Grammar::value, inner_action<
    ValueAction, Storage::member<&Hold::value>>
>{
  using state = Hold;
};

struct TimingCheckAction : single_dispatch<
  // Grammar::setup_timing_check, inner_action<
  //   SetupTimingCheckAction, SetupTimingCheckStorage >,
  Grammar::hold_timing_check, inner_action<
    HoldTimingCheckAction, Storage::member<&TimingCheck::value> > 
> {
  using state = TimingCheck;
};

struct TimingCheckArrayAction : single_dispatch<
  Grammar::tchk_def, inner_action<
    TimingCheckAction,
    Storage::push_back
  >
> {
  using state = TimingCheckSpec;
};

}

}

#endif // LIBSDF_ACTIONS_TIMINGSPEC_HPP
