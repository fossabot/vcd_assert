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

#ifndef LIBSDF_TYPES_TIMINGCHECK_HPP
#define LIBSDF_TYPES_TIMINGCHECK_HPP

#include "./enums.hpp"
#include "./timing.hpp"
#include "./values.hpp"

#include <parse/util/dependent_value.hpp>

#include <tuple>
#include <variant>

namespace SDF {
 
namespace Unsupported {
  struct Setup{};
  struct Setuphold{};
  struct Recovery{};
  struct Removal{};
  struct Recrem{};
  struct Skew{};
  struct Bidirectskew{};
  struct Width{};
  struct Period{};
  struct Nochange{};
}


struct InvertedNode : public Node {};

using NodeEqualityTuple = std::tuple<Node,Node>;

struct NodeConstantEquality {
  Node left = {};
  EqualityOperator op = {};
  bool right = {};

  bool operator==(const NodeConstantEquality& other) const noexcept{
    if((left == other.left)
        && (op == other.op) 
        && (right == other.right)){
            return true;
    }else{
        return false;
    }
  }
};

using TimingCheckConditionVariant = std::variant<
  Node,
  InvertedNode,
  NodeConstantEquality
>;

//   using TimingCheckConditionVariant::TimingCheckConditionVariant;
struct TimingCheckCondition  {
  TimingCheckConditionVariant value;

  ConditionalType get_enum_type() const {

    return std::visit([](auto&& param) 
                        -> ConditionalType {
      using T = typename std::decay<decltype(param)>::type;
      if constexpr (std::is_same_v<T,Node>) {
          return ConditionalType::simple;
      } else if constexpr (std::is_same_v<T,InvertedNode>) {
          return ConditionalType::inverted;
      } else if constexpr (std::is_same_v<T,NodeConstantEquality>) {
          return ConditionalType::equality;
      } else {
          static_assert(Parse::Util::dependent_value<false, T>);
      }
    }, value);
  }

  bool operator==(const TimingCheckCondition& other) const {
    if (get_enum_type() == other.get_enum_type()) {
      return (value==other.value);
    }else{
      return false;
    }
  }
    // return std::visit([][](auto&& t, auto&&  o) -> bool {
    //   using This = typename std::decay<decltype(t)>::type;
    //   using Other = typename std::decay<decltype(o)>::type;
    //   if constexpr (std::is_same_v<This,Other>) {
    //       return t==o;
    //   } else {
    //       return false;
    //   }
    // }, value, other);
};


struct PortTimingCheck{
  Node port; //Todo make Port and remove edge
  std::optional<TimingCheckCondition> timing_check_condition {};
  std::optional<std::string> symbolic_name {};
};

//note input == port_tchk 2 ! 
//note : order is important.
struct Hold {
  PortTimingCheck trig;  //triggers HOLD violation (data)
  PortTimingCheck reg;   //triggers HOLD check     (clk)
  Value value;           //time period from check start that wil cause violation.
};

// clang-format off
using TimingCheckVariant = std::variant<
  Hold,
  Unsupported::Setup, // TODO
  Unsupported::Setuphold,
  Unsupported::Recovery,
  Unsupported::Removal,
  Unsupported::Recrem,
  Unsupported::Skew,
  Unsupported::Bidirectskew,
  Unsupported::Width,
  Unsupported::Period,
  Unsupported::Nochange 
>;
// clang-format on

struct TimingCheck {
  TimingCheckVariant value;

  TimingCheckType get_enum_type() const {

    return std::visit([](auto&& param) -> TimingCheckType {

      using T = typename std::decay<decltype(param)>::type;

      if constexpr (std::is_same_v<T, Unsupported::Setup>) {
          return TimingCheckType::setup;
      } else if constexpr (std::is_same_v<T, Hold>) {
          return TimingCheckType::hold;
      } else if constexpr (std::is_same_v<T, Unsupported::Setuphold>) {
          return TimingCheckType::setuphold;
      } else if constexpr (std::is_same_v<T, Unsupported::Recovery>) {
          return TimingCheckType::recovery;
      } else if constexpr (std::is_same_v<T, Unsupported::Removal>) {
          return TimingCheckType::removal;
      } else if constexpr (std::is_same_v<T, Unsupported::Recrem>) {
          return TimingCheckType::recrem;
      } else if constexpr (std::is_same_v<T, Unsupported::Skew>) {
          return TimingCheckType::skew;
      } else if constexpr (std::is_same_v<T, Unsupported::Bidirectskew>) {
          return TimingCheckType::bidirectskew;
      } else if constexpr (std::is_same_v<T, Unsupported::Width>) {
          return TimingCheckType::width;
      } else if constexpr (std::is_same_v<T, Unsupported::Period>) {
          return TimingCheckType::period;
      } else if constexpr (std::is_same_v<T, Unsupported::Nochange>) {
          return TimingCheckType::nochange;
      } else {
          static_assert(Parse::Util::dependent_value<false, T>);
      }
    }, value);
  }
};

using TimingCheckVector = std::vector<TimingCheck>;

struct TimingCheckSpec : public TimingCheckVector {
  using TimingCheckVector::TimingCheckVector;

  std::vector<std::size_t> get_timing_check_indices_by_type(TimingCheckType &type) const;
};

// get_timing_check_indices_by_type<TimingCheckVariant::Hold>()
 
} // namespace SDF

#endif // LIBSDF_TYPES_TIMINGCHECK_HPP
