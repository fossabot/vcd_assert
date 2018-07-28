#ifndef VCD_ASSERT_SDF_MATCHING_HPP
#define VCD_ASSERT_SDF_MATCHING_HPP

#include "./conditional.hpp"
#include "./state.hpp"

#include "sdf/types/enums.hpp"
#include "sdf/types/timing.hpp"
#include "sdf/types/timing_check.hpp"

namespace VCDAssert {

ConditionalValuePointer
get_sdf_conditional_ptr_helper(SDF::EqualityOperator op,
                               ConditionalValuePointer left,
                               ConditionalValuePointer right);

ConditionalValuePointer get_sdf_node_ptr(State &state, std::size_t var_index);

std::optional<std::size_t> match_scope(const VCD::Header &header,
                                       std::vector<std::string> path,
                                       std::size_t scope_index);

std::optional<std::size_t> match_scope_helper(const VCD::Header &header,
                                              std::vector<std::string> path,
                                              std::size_t path_index,
                                              std::size_t scope_index);

std::optional<std::size_t> get_sdf_node_index(const VCD::Header &header,
                                              SDF::Node node,
                                              std::size_t scope_index,
                                              const VCD::Scope &scope);

std::optional<ConditionalValuePointer>
get_sdf_conditional_ptr(const VCD::Header &header, State &state,
                        SDF::TimingCheckCondition cond, std::size_t scope_index,
                        VCD::Scope &scope);

} // namespace VCDAssert

#endif // VCD_ASSERT_SDF_MATCHING_HPP