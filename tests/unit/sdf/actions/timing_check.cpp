#include "../types/timing_check.hpp"

#include <parse/test/parse.hpp>

#include <sdf/actions/timing_check.hpp>
#include <sdf/actions/timing_spec.hpp>
#include <sdf/actions/timing.hpp>
#include <sdf/grammar/timing.hpp>

#include <variant>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace SDF;
using namespace SDF::Test;
using Parse::Test::require_parse;


// TEST_CASE("SDF.Actions.EqualityOperatorAction", "[SDF][Actions][EqualityOperatorAction]") {

//   EqualityOperator test{};
//   EqualityOperator wanted = EqualityOperator::logic_equal;
//   INFO("logic_equal : \"==1\"");  
//   require_parse<Grammar::equality_operator, 
//                 Actions::EqualityOperatorAction>("==1", test);
//   CAPTURE(test);                
//   REQUIRE(wanted == test);
// } 

TEST_CASE("SDF.Actions.InvertedNodeAction", "[SDF][Actions][InvertedNodeAction]") {
  InvertedNode test{};
  CAPTURE(test_invertednode_1_str.to_cstr());  
  InvertedNode wanted{test_invertednode_1};
  require_parse<Grammar::inversion_condition, 
                Actions::InvertedNodeAction>(test_invertednode_1_str.to_string_view(), test);
  catch_test_node(static_cast<Node>(wanted),static_cast<Node>(test));     
}

TEST_CASE("SDF.Actions.NodeConstantEqualityAction", "[SDF][Actions][NodeConstantEqualityAction]") {
  NodeConstantEquality test{};
  NodeConstantEquality wanted{test_nodeconstantequality_1};
  CAPTURE(test_nodeconstantequality_1_str);
  require_parse<Grammar::node_constant_equality_condition, 
                Actions::NodeConstantEqualityAction>(test_nodeconstantequality_1_str.to_string_view(), test);
  CAPTURE(test);
  REQUIRE(wanted.op == test.op);
  REQUIRE(wanted.right == test.right);
  catch_test_node(static_cast<Node>(wanted.left),static_cast<Node>(test.left));     

}

TEST_CASE("SDF.Actions.TimingCheckCondAction", "[SDF][Actions][TimingCheckCondAction]") {

  TimingCheckCondition test{};
  TimingCheckCondition wanted {};
  
    SECTION("TimingCheckCondAction with condition"){
      wanted = {Node{node_1}};
      CAPTURE(wanted);
      require_parse<Grammar::timing_check_condition, 
                    Actions::TimingCheckConditionAction>(port_1_str.to_string_view(), test);
      catch_test_timingcheckcondition(wanted,test);

    SECTION("InvertedNode"){
      // INFO("test_timingcheckcondition_1_str : " << test_timingcheckcondition_1_str.to_string());
      wanted = test_timingcheckcondition_1;
      CAPTURE(wanted);
      require_parse<Grammar::timing_check_condition, 
                    Actions::TimingCheckConditionAction>(test_timingcheckcondition_1_str.to_string(), test);
      catch_test_timingcheckcondition(wanted,test);
    }
    SECTION("NodeConstantEquality"){
      // INFO("test_timingcheckcondition_2_str : " << test_timingcheckcondition_2_str.to_string());
      wanted = test_timingcheckcondition_2;
      CAPTURE(wanted);
      require_parse<Grammar::timing_check_condition, 
                    Actions::TimingCheckConditionAction>(test_timingcheckcondition_2_str.to_string(), test);
      catch_test_timingcheckcondition(wanted,test);
    }
    SECTION("InvertedNode"){
      // INFO("test_timingcheckcondition_3_str : " << test_timingcheckcondition_3_str.to_string());
      wanted = test_timingcheckcondition_3;
      CAPTURE(wanted);
      require_parse<Grammar::timing_check_condition, 
                    Actions::TimingCheckConditionAction>(test_timingcheckcondition_3_str.to_string(), test);
      catch_test_timingcheckcondition(wanted,test);
    }
    SECTION("NodeConstantEquality"){
      // INFO("test_timingcheckcondition_4_str : " << test_timingcheckcondition_4_str.to_string());
      wanted = test_timingcheckcondition_4;
      CAPTURE(wanted);
      require_parse<Grammar::timing_check_condition, 
                    Actions::TimingCheckConditionAction>(test_timingcheckcondition_4_str.to_string(), test);
      catch_test_timingcheckcondition(wanted,test);
    }
  }
}


TEST_CASE("SDF.Actions.PortCheckAction", "[SDF][Actions][PortCheckAction]") {
  PortTimingCheck test{};
  SECTION("PortCheckAction"){
    SECTION("test_porttimingcheck_1_str :"){
      CAPTURE(test_porttimingcheck_1_str.to_string());
      PortTimingCheck wanted = test_porttimingcheck_1;
      require_parse<Grammar::port_tchk,
                    Actions::PortCheckAction>(test_porttimingcheck_1_str.to_string(), test);
      catch_test_porttimingcheck(wanted,test);
    }
    SECTION("test_porttimingcheck_2_str :"){
      CAPTURE(test_porttimingcheck_2_str.to_string());
      PortTimingCheck wanted = test_porttimingcheck_2;
      require_parse<Grammar::port_tchk,
                    Actions::PortCheckAction>(test_porttimingcheck_2_str.to_string(), test);
      catch_test_porttimingcheck(wanted,test);
    }
    SECTION("test_porttimingcheck_3_str :"){
      CAPTURE(test_porttimingcheck_3_str.to_string());
      PortTimingCheck wanted = test_porttimingcheck_3;
      require_parse<Grammar::port_tchk,
                    Actions::PortCheckAction>(test_porttimingcheck_3_str.to_string(), test);
      catch_test_porttimingcheck(wanted,test);
    }
    SECTION("test_porttimingcheck_4_str :"){
      CAPTURE(test_porttimingcheck_4_str.to_string());
      PortTimingCheck wanted = test_porttimingcheck_4;
      require_parse<Grammar::port_tchk,
                    Actions::PortCheckAction>(test_porttimingcheck_4_str.to_string(), test);
      catch_test_porttimingcheck(wanted,test);
    }

  }  
}

TEST_CASE("SDF.Actions.HoldTimingCheckAction", "[SDF][Actions][HoldTimingCheckAction]") {
  Hold test{};
  SECTION("HoldTimingCheckAction"){
    SECTION("test_hold_1_str :"){
      CAPTURE(test_hold_1_str.to_string());
      Hold wanted = test_hold_1;
      require_parse<Grammar::hold_timing_check,
                    Actions::HoldTimingCheckAction>(test_hold_1_str.to_string(), test);
      catch_test_hold(wanted,test);
    }
    SECTION("test_hold_2_str :"){
      CAPTURE(test_hold_2_str.to_string());
      Hold wanted = test_hold_2;
      require_parse<Grammar::hold_timing_check,
                    Actions::HoldTimingCheckAction>(test_hold_2_str.to_string(), test);
      catch_test_hold(wanted,test);
    }
    SECTION("test_hold_3_str :"){
      CAPTURE(test_hold_3_str.to_string());
      Hold wanted = test_hold_3;
      require_parse<Grammar::hold_timing_check,
                    Actions::HoldTimingCheckAction>(test_hold_3_str.to_string(), test);
      catch_test_hold(wanted,test);
    }

  }  
}

TEST_CASE("SDF.Actions.TimingCheckAction", "[SDF][Actions][TimingCheckAction]") {
  TimingCheck test{}; 
  SECTION("TimingCheckAction"){
    SECTION("test_timingcheck_1_str :"){
      CAPTURE(test_timingcheck_1_str.to_string());
      TimingCheck wanted = test_timingcheck_1;
      require_parse<Grammar::tchk_def,
                    Actions::TimingCheckAction>(test_timingcheck_1_str.to_string(), test);
      catch_test_timingcheck(wanted,test);
    }
    SECTION("test_timingcheck_2_str :"){
      CAPTURE(test_timingcheck_2_str.to_string());
      TimingCheck wanted = test_timingcheck_2;
      require_parse<Grammar::tchk_def,
                    Actions::TimingCheckAction>(test_timingcheck_2_str.to_string(), test);
      catch_test_timingcheck(wanted,test);
    }
    SECTION("test_timingcheck_3_str :"){
      CAPTURE(test_timingcheck_3_str.to_string());
      TimingCheck wanted = test_timingcheck_3;
      require_parse<Grammar::tchk_def,
                    Actions::TimingCheckAction>(test_timingcheck_3_str.to_string(), test);
      catch_test_timingcheck(wanted,test);
    }
  }  
}

TEST_CASE("SDF.Actions.TimingCheckArrayAction", "[SDF][Actions][TimingCheckArrayAction]") {
  TimingCheckSpec test{};
  SECTION("TimingCheckArrayAction"){
    INFO("test_timingcheckspec_1_str : " << test_timingcheckspec_1_str.to_string());
      TimingCheckSpec wanted = test_timingcheckspec_1;
      require_parse<Grammar::tc_spec,
                    Actions::TimingCheckArrayAction>(test_timingcheckspec_1_str.to_string(), test);
      catch_test_timingcheckspec(wanted,test);
  }  
}

