#include "program_knowledge_base/pkb_manager.h"
#include "simple_parser/interface.h"

#include "catch.hpp"

#include <fstream>

using Simple::SimpleInterface;

TEST_CASE ("Test PKB for assign.txt") {
  auto ast = SimpleInterface::getAstFromFile("tests/simple_source/assign.txt");

  PKB::PKBManager pkb = PKB::PKBManager(ast);

  // variable
  auto var_exist_test_1 = pkb.isVariableExists("i");
  REQUIRE(var_exist_test_1 == true);
  auto var_exist_test_2 = pkb.isVariableExists("j");
  REQUIRE(var_exist_test_2 == false);

  std::unordered_set<std::string> var_get_test_1_check;
  var_get_test_1_check.insert("i");
  auto var_get_test_1_vector = pkb.getVariableList();
  std::unordered_set<Variable> var_get_test_1_set(var_get_test_1_vector.begin(),
                                                  var_get_test_1_vector.end());
  REQUIRE(var_get_test_1_set == var_get_test_1_check);

  // assign
  auto assign_exist_test_1 = pkb.isAssignExists("1");
  REQUIRE(assign_exist_test_1 == true);
  auto assign_exist_test_2 = pkb.isAssignExists("2");
  REQUIRE(assign_exist_test_2 == false);

  // statement
  auto statement_exist_test_1 = pkb.isStatementExists("1");
  REQUIRE(statement_exist_test_1 == true);
  auto statement_exist_test_2 = pkb.isStatementExists("2");
  REQUIRE(statement_exist_test_2 == false);

  // test modifies
  auto modifies_test_1 = pkb.isLineModifiesVar("1", "i");
  REQUIRE(modifies_test_1 == true);

  // test pattern
  std::unordered_set<std::string> pattern_test_1_check;
  pattern_test_1_check.insert("1");
  auto pattern_test_1 = pkb.getCompleteMatchLinesWithVar("i", "2+5");
  std::unordered_set<Variable> pattern_test_1_set(pattern_test_1->begin(),
                                                  pattern_test_1->end());
  REQUIRE(pattern_test_1_set == pattern_test_1_check);

  std::unordered_set<std::string> pattern_test_2_check;
  pattern_test_2_check.insert("1");
  auto pattern_test_2 = pkb.getPartialMatchLinesWithVar("i", "2");
  std::unordered_set<Variable> pattern_test_2_set;
  if (pattern_test_2) {
    for (const auto &elem : (*pattern_test_2)) {
      pattern_test_2_set.insert(elem);
    }
  }
  REQUIRE(pattern_test_2_set == pattern_test_2_check);

  std::unordered_set<std::string> pattern_test_3_check;
  pattern_test_3_check.insert("1");
  auto pattern_test_3 = pkb.getPartialMatchLinesWithVar("i", "5");
  std::unordered_set<Variable> pattern_test_3_set;
  if (pattern_test_3) {
    for (const auto &elem : (*pattern_test_3)) {
      pattern_test_3_set.insert(elem);
    }
  }
  REQUIRE(pattern_test_3_set == pattern_test_3_check);

  std::unordered_set<std::string> pattern_test_4_check;
  auto pattern_test_4 = pkb.getPartialMatchLinesWithVar("x", "x");
  std::unordered_set<Variable> pattern_test_4_set;
  if (pattern_test_4) {
    for (const auto &elem : (*pattern_test_4)) {
      pattern_test_4_set.insert(elem);
    }
  }
  REQUIRE(pattern_test_4_set == pattern_test_4_check);

  std::unordered_set<std::string> pattern_test_5_check;
  auto pattern_test_5 = pkb.getPartialMatchLines("x");
  std::unordered_set<Variable> pattern_test_5_set;
  if (pattern_test_5) {
    for (const auto &elem : (*pattern_test_5)) {
      pattern_test_5_set.insert(elem);
    }
  }
  REQUIRE(pattern_test_5_set == pattern_test_5_check);

  std::unordered_set<std::string> pattern_test_6_check;
  auto pattern_test_6 = pkb.getCompleteMatchLines("x");
  std::unordered_set<Variable> pattern_test_6_set;
  if (pattern_test_6) {
    for (const auto &elem : (*pattern_test_6)) {
      pattern_test_6_set.insert(elem);
    }
  }
  REQUIRE(pattern_test_6_set == pattern_test_6_check);

  std::unordered_set<std::string> pattern_test_7_check;
  pattern_test_7_check.insert("1");
  auto pattern_test_7 = pkb.getCompleteMatchLines("2+5");
  std::unordered_set<Variable> pattern_test_7_set;
  if (pattern_test_7) {
    for (const auto &elem : (*pattern_test_7)) {
      pattern_test_7_set.insert(elem);
    }
  }
  REQUIRE(pattern_test_7_set == pattern_test_7_check);
}

TEST_CASE ("Test PKB for simple_1.txt") {
  auto ast = Simple::SimpleInterface::getAstFromFile(
      "tests/simple_source/simple_1.txt");

  PKB::PKBManager pkb = PKB::PKBManager(ast);

  // variable
  auto var_exist_test_1 = pkb.isVariableExists("i");
  REQUIRE(var_exist_test_1 == true);
  auto var_exist_test_2 = pkb.isVariableExists("j");
  REQUIRE(var_exist_test_2 == true);
  auto var_exist_test_3 = pkb.isVariableExists("k");
  REQUIRE(var_exist_test_3 == false);
  auto var_exist_test_4 = pkb.isVariableExists("l");
  REQUIRE(var_exist_test_4 == false);

  std::unordered_set<std::string> var_get_test_1_check;
  var_get_test_1_check.insert("i");
  var_get_test_1_check.insert("j");
  auto var_get_test_1_vector = pkb.getVariableList();
  std::unordered_set<Variable> var_get_test_1_set(var_get_test_1_vector.begin(),
                                                  var_get_test_1_vector.end());
  REQUIRE(var_get_test_1_set == var_get_test_1_check);

  // assign
  auto assign_exist_test_1 = pkb.isAssignExists("1");
  REQUIRE(assign_exist_test_1 == true);
  auto assign_exist_test_2 = pkb.isAssignExists("2");
  REQUIRE(assign_exist_test_2 == false);

  // assign
  auto statement_exist_test_1 = pkb.isStatementExists("1");
  REQUIRE(statement_exist_test_1 == true);
  auto statement_exist_test_2 = pkb.isStatementExists("2");
  REQUIRE(statement_exist_test_2 == true);
  auto statement_exist_test_3 = pkb.isStatementExists("3");
  REQUIRE(statement_exist_test_3 == true);
  auto statement_exist_test_4 = pkb.isStatementExists("4");
  REQUIRE(statement_exist_test_4 == true);
  auto statement_exist_test_5 = pkb.isStatementExists("5");
  REQUIRE(statement_exist_test_5 == true);
  auto statement_exist_test_6 = pkb.isStatementExists("6");
  REQUIRE(statement_exist_test_6 == false);
  auto statement_exist_test_7 = pkb.isStatementExists("0");
  REQUIRE(statement_exist_test_7 == false);
  auto statement_exist_test_8 = pkb.isStatementExists("-12");
  REQUIRE(statement_exist_test_8 == false);

  // print
  auto print_exist_test_1 = pkb.isPrintExists("3");
  REQUIRE(print_exist_test_1 == true);
  auto print_exist_test_2 = pkb.isPrintExists("4");
  REQUIRE(print_exist_test_2 == true);
  auto print_exist_test_3 = pkb.isPrintExists("5");
  REQUIRE(print_exist_test_3 == false);

  // read
  auto read_exist_test_1 = pkb.isReadExists("5");
  REQUIRE(read_exist_test_1 == true);
  auto read_exist_test_2 = pkb.isReadExists("2");
  REQUIRE(read_exist_test_2 == false);

  // while
  auto while_exist_test_1 = pkb.isWhileExists("2");
  REQUIRE(while_exist_test_1 == true);
  auto while_exist_test_2 = pkb.isWhileExists("3");
  REQUIRE(while_exist_test_2 == false);

  // if
  auto if_exist_test_1 = pkb.isIfExists("1");
  REQUIRE(if_exist_test_1 == false);
  auto if_exist_test_2 = pkb.isIfExists("2");
  REQUIRE(if_exist_test_2 == false);

  // constant
  auto constant_exist_test_1 = pkb.isConstantExists("5");
  REQUIRE(constant_exist_test_1 == true);
  auto constant_exist_test_2 = pkb.isConstantExists("222");
  REQUIRE(constant_exist_test_2 == false);

  // procedure
  auto proc_exist_test_1 = pkb.isProcedureExists("main");
  REQUIRE(proc_exist_test_1 == true);
  auto proc_exist_test_2 = pkb.isProcedureExists("blah");
  REQUIRE(proc_exist_test_2 == false);

  // test follows
  auto follows_test_1 = pkb.isLineFollowLine("1", "2");
  REQUIRE(follows_test_1 == true);
  auto follows_test_2 = pkb.isLineFollowLine("1", "4");
  REQUIRE(follows_test_2 == false);
  auto follows_test_3 = pkb.isLineFollowLine("1", "5");
  REQUIRE(follows_test_3 == false);
  auto follows_test_4 = pkb.isLineFollowLine("2", "4");
  REQUIRE(follows_test_4 == true);
  auto follows_test_5 = pkb.isLineFollowLine("2", "5");
  REQUIRE(follows_test_5 == false);
  auto follows_test_6 = pkb.isLineFollowLine("4", "5");
  REQUIRE(follows_test_6 == true);
  auto follows_test_7 = pkb.isLineFollowLine("1", "9");
  REQUIRE(follows_test_7 == false);
  auto follows_test_8 = pkb.isLineFollowLine("2", "3");
  REQUIRE(follows_test_8 == false);
  auto follows_test_9 = pkb.isLineFollowLine("4", "2");
  REQUIRE(follows_test_9 == false);
  auto follows_test_10 = pkb.isLineFollowLine("8", "0");
  REQUIRE(follows_test_10 == false);
  auto follows_test_11 = pkb.isLineFollowLineS("1", "2");
  REQUIRE(follows_test_11 == true);
  auto follows_test_12 = pkb.isLineFollowLineS("1", "3");
  REQUIRE(follows_test_12 == false);
  auto follows_test_13 = pkb.isLineFollowLineS("1", "4");
  REQUIRE(follows_test_13 == true);
  auto follows_test_14 = pkb.isLineFollowLineS("1", "5");
  REQUIRE(follows_test_14 == true);
  auto follows_test_15 = pkb.isLineFollowLineS("2", "3");
  REQUIRE(follows_test_15 == false);
  auto follows_test_16 = pkb.isLineFollowLineS("2", "4");
  REQUIRE(follows_test_16 == true);
  auto follows_test_17 = pkb.isLineFollowLineS("2", "5");
  REQUIRE(follows_test_17 == true);
  auto follows_test_18 = pkb.isLineFollowLineS("3", "4");
  REQUIRE(follows_test_18 == false);

  // test parent
  auto parent_test_1 = pkb.isLineParentLine("2", "3");
  REQUIRE(parent_test_1 == true);
  auto parent_test_2 = pkb.isLineParentLine("1", "2");
  REQUIRE(parent_test_2 == false);
  auto parent_test_3 = pkb.isLineParentLine("3", "3");
  REQUIRE(parent_test_3 == false);
  auto parent_test_4 = pkb.isLineParentLine("4", "3");
  REQUIRE(parent_test_4 == false);

  std::unordered_set<std::string> parent_test_5_check;
  parent_test_5_check.insert("2");
  std::unordered_set<Variable> parent_test_5_set;
  auto parent_test_5 = pkb.getParentLineS("3");
  if (parent_test_5) {
    for (const auto &elem : (*parent_test_5)) {
      parent_test_5_set.insert(elem);
    }
  }
  REQUIRE(parent_test_5_set == parent_test_5_check);

  // test uses
  auto uses_test_1 = pkb.isLineUsesVar("2", "i");
  REQUIRE(uses_test_1 == true);
  auto uses_test_2 = pkb.isLineUsesVar("1", "i");
  REQUIRE(uses_test_2 == false);
  auto uses_test_3 = pkb.isLineUsesVar("5", "i");
  REQUIRE(uses_test_3 == false);
  auto uses_test_4 = pkb.isLineUsesVar("2", "alpha");
  REQUIRE(uses_test_4 == false);

  auto uses_test_5 = pkb.isProcedureUsesVar("main", "i");
  REQUIRE(uses_test_5 == true);
  auto uses_test_6 = pkb.isProcedureUsesVar("main", "j");
  REQUIRE(uses_test_6 == true);
  auto uses_test_7 = pkb.isProcedureUsesVar("main", "k");
  REQUIRE(uses_test_7 == false);
  auto uses_test_8 = pkb.isProcedureUsesVar("test", "alpha");
  REQUIRE(uses_test_8 == false);

  std::unordered_set<std::string> uses_test_9_check;
  uses_test_9_check.insert("i");
  uses_test_9_check.insert("j");
  std::unordered_set<Variable> uses_test_9_set;
  auto uses_test_9 = pkb.getVarUsedByProcedure("main");
  if (uses_test_9) {
    for (const auto &elem : (*uses_test_9)) {
      uses_test_9_set.insert(elem);
    }
  }
  REQUIRE(uses_test_9_set == uses_test_9_check);

  // test modifies
  auto modifies_test_1 = pkb.isLineModifiesVar("5", "i");
  REQUIRE(modifies_test_1 == true);
  auto modifies_test_2 = pkb.isLineModifiesVar("1", "i");
  REQUIRE(modifies_test_2 == true);
  auto modifies_test_3 = pkb.isLineModifiesVar("1", "beta");
  REQUIRE(modifies_test_3 == false);
  auto modifies_test_4 = pkb.isLineModifiesVar("2", "alpha");
  REQUIRE(modifies_test_4 == false);
  auto modifies_test_5 = pkb.isLineModifiesVar("22", "alpha");
  REQUIRE(modifies_test_5 == false);
  auto modifies_test_6 = pkb.isLineModifiesVar("10", "i");
  REQUIRE(modifies_test_6 == false);

  auto modifies_test_7 = pkb.isProcedureModifiesVar("main", "i");
  REQUIRE(modifies_test_7 == true);
  auto modifies_test_8 = pkb.isProcedureModifiesVar("main", "j");
  REQUIRE(modifies_test_8 == false);
  auto modifies_test_9 = pkb.isProcedureModifiesVar("test", "i");
  REQUIRE(modifies_test_9 == false);
  auto modifies_test_10 = pkb.isProcedureModifiesVar("test", "asd");
  REQUIRE(modifies_test_10 == false);

  std::unordered_set<std::string> modifies_test_11_check;
  modifies_test_11_check.insert("i");
  std::unordered_set<Variable> modifies_test_11_set;
  auto modifies_test_11 = pkb.getVarModifiedByProcedure("main");
  if (modifies_test_11) {
    for (const auto &elem : (*modifies_test_11)) {
      modifies_test_11_set.insert(elem);
    }
  }
  REQUIRE(modifies_test_11_set == modifies_test_11_check);

  // test pattern
  std::unordered_set<std::string> pattern_test_1_check;
  pattern_test_1_check.insert("1");
  auto pattern_test_1 = pkb.getCompleteMatchLinesWithVar("i", "5");
  std::unordered_set<Variable> pattern_test_1_set;
  if (pattern_test_1) {
    for (const auto &elem : (*pattern_test_1)) {
      pattern_test_1_set.insert(elem);
    }
  }
  REQUIRE(pattern_test_1_set == pattern_test_1_check);
}

TEST_CASE ("Test PKB for 10_simple_source_deep_nesting.txt") {
  auto proc = SimpleInterface::getAstFromFile(
      "tests/10_simple_source_deep_nesting.txt");

  PKB::PKBManager pkb = PKB::PKBManager(proc);

  // variable
  auto var_exist_test_1 = pkb.isVariableExists("x");
  REQUIRE(var_exist_test_1 == true);
  auto var_exist_test_2 = pkb.isVariableExists("y");
  REQUIRE(var_exist_test_2 == true);
  auto var_exist_test_3 = pkb.isVariableExists("z");
  REQUIRE(var_exist_test_3 == true);
  auto var_exist_test_4 = pkb.isVariableExists("a");
  REQUIRE(var_exist_test_4 == false);

  // assign
  auto assign_exist_test_1 = pkb.isAssignExists("1");
  REQUIRE(assign_exist_test_1 == true);
  auto assign_exist_test_2 = pkb.isAssignExists("2");
  REQUIRE(assign_exist_test_2 == true);
  auto assign_exist_test_3 = pkb.isAssignExists("3");
  REQUIRE(assign_exist_test_3 == true);
  auto assign_exist_test_4 = pkb.isAssignExists("4");
  REQUIRE(assign_exist_test_4 == false);
  auto assign_exist_test_5 = pkb.isAssignExists("5");
  REQUIRE(assign_exist_test_5 == true);
  auto assign_exist_test_6 = pkb.isAssignExists("6");
  REQUIRE(assign_exist_test_6 == true);
  auto assign_exist_test_7 = pkb.isAssignExists("7");
  REQUIRE(assign_exist_test_7 == false);
  auto assign_exist_test_8 = pkb.isAssignExists("8");
  REQUIRE(assign_exist_test_8 == true);
  auto assign_exist_test_9 = pkb.isAssignExists("9");
  REQUIRE(assign_exist_test_9 == true);
  auto assign_exist_test_10 = pkb.isAssignExists("10");
  REQUIRE(assign_exist_test_10 == true);
  auto assign_exist_test_11 = pkb.isAssignExists("11");
  REQUIRE(assign_exist_test_11 == false);
  auto assign_exist_test_12 = pkb.isAssignExists("12");
  REQUIRE(assign_exist_test_12 == true);
  auto assign_exist_test_13 = pkb.isAssignExists("13");
  REQUIRE(assign_exist_test_13 == true);
  auto assign_exist_test_14 = pkb.isAssignExists("14");
  REQUIRE(assign_exist_test_14 == true);
  auto assign_exist_test_15 = pkb.isAssignExists("15");
  REQUIRE(assign_exist_test_15 == true);
  auto assign_exist_test_16 = pkb.isAssignExists("16");
  REQUIRE(assign_exist_test_16 == false);
  auto assign_exist_test_17 = pkb.isAssignExists("17");
  REQUIRE(assign_exist_test_17 == true);
  auto assign_exist_test_18 = pkb.isAssignExists("18");
  REQUIRE(assign_exist_test_18 == true);
  auto assign_exist_test_19 = pkb.isAssignExists("19");
  REQUIRE(assign_exist_test_19 == true);
  auto assign_exist_test_20 = pkb.isAssignExists("20");
  REQUIRE(assign_exist_test_20 == true);
  auto assign_exist_test_21 = pkb.isAssignExists("21");
  REQUIRE(assign_exist_test_21 == true);
  auto assign_exist_test_22 = pkb.isAssignExists("22");
  REQUIRE(assign_exist_test_22 == true);
  auto assign_exist_test_23 = pkb.isAssignExists("23");
  REQUIRE(assign_exist_test_23 == false);
  auto assign_exist_test_24 = pkb.isAssignExists("24");
  REQUIRE(assign_exist_test_24 == false);
  auto assign_exist_test_25 = pkb.isAssignExists("25");
  REQUIRE(assign_exist_test_25 == false);

  // statement
  auto statement_exist_test_1 = pkb.isStatementExists("1");
  REQUIRE(statement_exist_test_1 == true);
  auto statement_exist_test_2 = pkb.isStatementExists("2");
  REQUIRE(statement_exist_test_2 == true);
  auto statement_exist_test_3 = pkb.isStatementExists("3");
  REQUIRE(statement_exist_test_3 == true);
  auto statement_exist_test_4 = pkb.isStatementExists("4");
  REQUIRE(statement_exist_test_4 == true);
  auto statement_exist_test_5 = pkb.isStatementExists("5");
  REQUIRE(statement_exist_test_5 == true);
  auto statement_exist_test_6 = pkb.isStatementExists("6");
  REQUIRE(statement_exist_test_6 == true);
  auto statement_exist_test_7 = pkb.isStatementExists("7");
  REQUIRE(statement_exist_test_7 == true);
  auto statement_exist_test_8 = pkb.isStatementExists("8");
  REQUIRE(statement_exist_test_8 == true);
  auto statement_exist_test_9 = pkb.isStatementExists("9");
  REQUIRE(statement_exist_test_9 == true);
  auto statement_exist_test_10 = pkb.isStatementExists("10");
  REQUIRE(statement_exist_test_10 == true);
  auto statement_exist_test_11 = pkb.isStatementExists("11");
  REQUIRE(statement_exist_test_11 == true);
  auto statement_exist_test_12 = pkb.isStatementExists("12");
  REQUIRE(statement_exist_test_12 == true);
  auto statement_exist_test_13 = pkb.isStatementExists("13");
  REQUIRE(statement_exist_test_13 == true);
  auto statement_exist_test_14 = pkb.isStatementExists("14");
  REQUIRE(statement_exist_test_14 == true);
  auto statement_exist_test_15 = pkb.isStatementExists("15");
  REQUIRE(statement_exist_test_15 == true);
  auto statement_exist_test_16 = pkb.isStatementExists("16");
  REQUIRE(statement_exist_test_16 == true);
  auto statement_exist_test_17 = pkb.isStatementExists("17");
  REQUIRE(statement_exist_test_17 == true);
  auto statement_exist_test_18 = pkb.isStatementExists("18");
  REQUIRE(statement_exist_test_18 == true);
  auto statement_exist_test_19 = pkb.isStatementExists("19");
  REQUIRE(statement_exist_test_19 == true);
  auto statement_exist_test_20 = pkb.isStatementExists("20");
  REQUIRE(statement_exist_test_20 == true);
  auto statement_exist_test_21 = pkb.isStatementExists("21");
  REQUIRE(statement_exist_test_21 == true);
  auto statement_exist_test_22 = pkb.isStatementExists("22");
  REQUIRE(statement_exist_test_22 == true);
  auto statement_exist_test_23 = pkb.isStatementExists("23");
  REQUIRE(statement_exist_test_23 == true);
  auto statement_exist_test_24 = pkb.isStatementExists("24");
  REQUIRE(statement_exist_test_24 == true);
  auto statement_exist_test_25 = pkb.isStatementExists("0");
  REQUIRE(statement_exist_test_25 == false);
  auto statement_exist_test_26 = pkb.isStatementExists("-12");
  REQUIRE(statement_exist_test_26 == false);

  // print
  auto print_exist_test_1 = pkb.isPrintExists("23");
  REQUIRE(print_exist_test_1 == true);
  auto print_exist_test_2 = pkb.isPrintExists("24");
  REQUIRE(print_exist_test_2 == true);
  auto print_exist_test_3 = pkb.isPrintExists("5");
  REQUIRE(print_exist_test_3 == false);
  auto print_exist_test_4 = pkb.isPrintExists("1");
  REQUIRE(print_exist_test_4 == false);
  auto print_exist_test_5 = pkb.isPrintExists("4");
  REQUIRE(print_exist_test_5 == false);
  auto print_exist_test_6 = pkb.isPrintExists("12");
  REQUIRE(print_exist_test_6 == false);

  // read
  auto read_exist_test_1 = pkb.isReadExists("1");
  REQUIRE(read_exist_test_1 == false);
  auto read_exist_test_2 = pkb.isReadExists("2");
  REQUIRE(read_exist_test_2 == false);
  auto read_exist_test_3 = pkb.isReadExists("7");
  REQUIRE(read_exist_test_3 == false);
  auto read_exist_test_4 = pkb.isReadExists("23");
  REQUIRE(read_exist_test_4 == false);
  auto read_exist_test_5 = pkb.isReadExists("24");
  REQUIRE(read_exist_test_5 == false);

  // while
  auto while_exist_test_1 = pkb.isWhileExists("2");
  REQUIRE(while_exist_test_1 == false);
  auto while_exist_test_2 = pkb.isWhileExists("3");
  REQUIRE(while_exist_test_2 == false);
  auto while_exist_test_3 = pkb.isWhileExists("4");
  REQUIRE(while_exist_test_3 == true);
  auto while_exist_test_4 = pkb.isWhileExists("7");
  REQUIRE(while_exist_test_4 == true);
  auto while_exist_test_5 = pkb.isWhileExists("11");
  REQUIRE(while_exist_test_5 == true);
  auto while_exist_test_6 = pkb.isWhileExists("16");
  REQUIRE(while_exist_test_6 == true);
  auto while_exist_test_7 = pkb.isWhileExists("18");
  REQUIRE(while_exist_test_7 == false);

  // if
  auto if_exist_test_1 = pkb.isIfExists("1");
  REQUIRE(if_exist_test_1 == false);
  auto if_exist_test_2 = pkb.isIfExists("2");
  REQUIRE(if_exist_test_2 == false);
  auto if_exist_test_3 = pkb.isIfExists("4");
  REQUIRE(if_exist_test_3 == false);
  auto if_exist_test_4 = pkb.isIfExists("22");
  REQUIRE(if_exist_test_4 == false);

  // constant
  auto constant_exist_test_1 = pkb.isConstantExists("0");
  REQUIRE(constant_exist_test_1 == true);
  auto constant_exist_test_2 = pkb.isConstantExists("1");
  REQUIRE(constant_exist_test_2 == true);
  auto constant_exist_test_3 = pkb.isConstantExists("2");
  REQUIRE(constant_exist_test_3 == true);
  auto constant_exist_test_4 = pkb.isConstantExists("3");
  REQUIRE(constant_exist_test_4 == true);
  auto constant_exist_test_5 = pkb.isConstantExists("4");
  REQUIRE(constant_exist_test_5 == true);
  auto constant_exist_test_6 = pkb.isConstantExists("100");
  REQUIRE(constant_exist_test_6 == true);
  auto constant_exist_test_7 = pkb.isConstantExists("222");
  REQUIRE(constant_exist_test_7 == false);
  auto constant_exist_test_8 = pkb.isConstantExists("-28");
  REQUIRE(constant_exist_test_8 == false);

  // procedure
  auto proc_exist_test_1 = pkb.isProcedureExists("main");
  REQUIRE(proc_exist_test_1 == true);
  auto proc_exist_test_2 = pkb.isProcedureExists("blah");
  REQUIRE(proc_exist_test_2 == false);

  // test follows
  auto follows_test_1 = pkb.isLineFollowLine("1", "2");
  REQUIRE(follows_test_1 == true);
  auto follows_test_2 = pkb.isLineFollowLine("2", "3");
  REQUIRE(follows_test_2 == true);
  auto follows_test_3 = pkb.isLineFollowLine("3", "4");
  REQUIRE(follows_test_3 == true);
  auto follows_test_4 = pkb.isLineFollowLine("5", "6");
  REQUIRE(follows_test_4 == true);
  auto follows_test_5 = pkb.isLineFollowLine("6", "7");
  REQUIRE(follows_test_5 == true);
  auto follows_test_6 = pkb.isLineFollowLine("8", "9");
  REQUIRE(follows_test_6 == true);
  auto follows_test_7 = pkb.isLineFollowLine("9", "10");
  REQUIRE(follows_test_7 == true);
  auto follows_test_8 = pkb.isLineFollowLine("10", "11");
  REQUIRE(follows_test_8 == true);
  auto follows_test_9 = pkb.isLineFollowLine("15", "16");
  REQUIRE(follows_test_9 == true);
  auto follows_test_10 = pkb.isLineFollowLine("7", "22");
  REQUIRE(follows_test_10 == true);
  auto follows_test_11 = pkb.isLineFollowLine("4", "23");
  REQUIRE(follows_test_11 == true);
  auto follows_test_12 = pkb.isLineFollowLine("23", "24");
  REQUIRE(follows_test_12 == true);

  auto follows_test_13 = pkb.isLineFollowLine("1", "4");
  REQUIRE(follows_test_13 == false);
  auto follows_test_14 = pkb.isLineFollowLine("1", "5");
  REQUIRE(follows_test_14 == false);
  auto follows_test_15 = pkb.isLineFollowLine("1", "9");
  REQUIRE(follows_test_15 == false);
  auto follows_test_16 = pkb.isLineFollowLine("2", "4");
  REQUIRE(follows_test_16 == false);
  auto follows_test_17 = pkb.isLineFollowLine("2", "5");
  REQUIRE(follows_test_17 == false);
  auto follows_test_18 = pkb.isLineFollowLine("4", "5");
  REQUIRE(follows_test_18 == false);
  auto follows_test_19 = pkb.isLineFollowLine("4", "7");
  REQUIRE(follows_test_19 == false);
  auto follows_test_20 = pkb.isLineFollowLine("7", "8");
  REQUIRE(follows_test_20 == false);
  auto follows_test_21 = pkb.isLineFollowLine("7", "10");
  REQUIRE(follows_test_21 == false);
  auto follows_test_22 = pkb.isLineFollowLine("8", "10");
  REQUIRE(follows_test_22 == false);
  auto follows_test_23 = pkb.isLineFollowLine("11", "12");
  REQUIRE(follows_test_23 == false);
  auto follows_test_24 = pkb.isLineFollowLine("16", "17");
  REQUIRE(follows_test_24 == false);
  auto follows_test_25 = pkb.isLineFollowLine("21", "22");
  REQUIRE(follows_test_25 == false);
  auto follows_test_26 = pkb.isLineFollowLine("22", "23");
  REQUIRE(follows_test_26 == false);

  auto follows_test_27 = pkb.isLineFollowLineS("1", "2");
  REQUIRE(follows_test_27 == true);
  auto follows_test_28 = pkb.isLineFollowLineS("1", "3");
  REQUIRE(follows_test_28 == true);
  auto follows_test_29 = pkb.isLineFollowLineS("1", "4");
  REQUIRE(follows_test_29 == true);
  auto follows_test_30 = pkb.isLineFollowLineS("1", "5");
  REQUIRE(follows_test_30 == false);
  auto follows_test_31 = pkb.isLineFollowLineS("2", "3");
  REQUIRE(follows_test_31 == true);
  auto follows_test_32 = pkb.isLineFollowLineS("2", "4");
  REQUIRE(follows_test_32 == true);
  auto follows_test_33 = pkb.isLineFollowLineS("2", "5");
  REQUIRE(follows_test_33 == false);
  auto follows_test_34 = pkb.isLineFollowLineS("3", "4");
  REQUIRE(follows_test_34 == true);
  auto follows_test_35 = pkb.isLineFollowLineS("5", "6");
  REQUIRE(follows_test_35 == true);
  auto follows_test_36 = pkb.isLineFollowLineS("5", "7");
  REQUIRE(follows_test_36 == true);
  auto follows_test_37 = pkb.isLineFollowLineS("8", "9");
  REQUIRE(follows_test_37 == true);
  auto follows_test_38 = pkb.isLineFollowLineS("8", "10");
  REQUIRE(follows_test_38 == true);
  auto follows_test_39 = pkb.isLineFollowLineS("8", "12");
  REQUIRE(follows_test_39 == false);
  auto follows_test_40 = pkb.isLineFollowLineS("9", "11");
  REQUIRE(follows_test_40 == true);
  auto follows_test_41 = pkb.isLineFollowLineS("9", "12");
  REQUIRE(follows_test_41 == false);
  auto follows_test_42 = pkb.isLineFollowLineS("12", "13");
  REQUIRE(follows_test_42 == true);
  auto follows_test_43 = pkb.isLineFollowLineS("12", "16");
  REQUIRE(follows_test_43 == true);
  auto follows_test_44 = pkb.isLineFollowLineS("5", "22");
  REQUIRE(follows_test_44 == true);
  auto follows_test_45 = pkb.isLineFollowLineS("1", "23");
  REQUIRE(follows_test_45 == true);
  auto follows_test_46 = pkb.isLineFollowLineS("2", "24");
  REQUIRE(follows_test_46 == true);
  auto follows_test_47 = pkb.isLineFollowLineS("3", "23");
  REQUIRE(follows_test_47 == true);
  auto follows_test_48 = pkb.isLineFollowLineS("3", "24");
  REQUIRE(follows_test_48 == true);
  auto follows_test_49 = pkb.isLineFollowLineS("4", "24");
  REQUIRE(follows_test_49 == true);
  auto follows_test_50 = pkb.isLineFollowLineS("22", "24");
  REQUIRE(follows_test_50 == false);

  // test parent
  auto parent_test_1 = pkb.isLineParentLine("4", "5");
  REQUIRE(parent_test_1 == true);
  auto parent_test_2 = pkb.isLineParentLine("4", "6");
  REQUIRE(parent_test_2 == true);
  auto parent_test_3 = pkb.isLineParentLine("4", "7");
  REQUIRE(parent_test_3 == true);
  auto parent_test_4 = pkb.isLineParentLine("7", "8");
  REQUIRE(parent_test_4 == true);
  auto parent_test_5 = pkb.isLineParentLine("7", "10");
  REQUIRE(parent_test_5 == true);
  auto parent_test_6 = pkb.isLineParentLine("7", "11");
  REQUIRE(parent_test_6 == true);
  auto parent_test_7 = pkb.isLineParentLine("7", "12");
  REQUIRE(parent_test_7 == false);
  auto parent_test_8 = pkb.isLineParentLine("11", "12");
  REQUIRE(parent_test_8 == true);
  auto parent_test_9 = pkb.isLineParentLine("11", "14");
  REQUIRE(parent_test_9 == true);
  auto parent_test_10 = pkb.isLineParentLine("11", "16");
  REQUIRE(parent_test_10 == true);
  auto parent_test_11 = pkb.isLineParentLine("11", "17");
  REQUIRE(parent_test_11 == false);
  auto parent_test_12 = pkb.isLineParentLine("16", "18");
  REQUIRE(parent_test_12 == true);
  auto parent_test_13 = pkb.isLineParentLine("16", "20");
  REQUIRE(parent_test_13 == true);
  auto parent_test_14 = pkb.isLineParentLine("4", "22");
  REQUIRE(parent_test_14 == true);
  auto parent_test_15 = pkb.isLineParentLine("4", "23");
  REQUIRE(parent_test_15 == false);

  auto parent_test_16 = pkb.isLineParentLineS("4", "8");
  REQUIRE(parent_test_16 == true);
  auto parent_test_17 = pkb.isLineParentLineS("4", "9");
  REQUIRE(parent_test_17 == true);
  auto parent_test_18 = pkb.isLineParentLineS("4", "12");
  REQUIRE(parent_test_18 == true);
  auto parent_test_19 = pkb.isLineParentLineS("7", "15");
  REQUIRE(parent_test_19 == true);
  auto parent_test_20 = pkb.isLineParentLineS("7", "18");
  REQUIRE(parent_test_20 == true);
  auto parent_test_21 = pkb.isLineParentLineS("11", "21");
  REQUIRE(parent_test_21 == true);
  auto parent_test_22 = pkb.isLineParentLineS("4", "22");
  REQUIRE(parent_test_22 == true);
  auto parent_test_23 = pkb.isLineParentLineS("4", "19");
  REQUIRE(parent_test_23 == true);
  auto parent_test_24 = pkb.isLineParentLineS("23", "24");
  REQUIRE(parent_test_24 == false);
  auto parent_test_25 = pkb.isLineParentLineS("1", "5");
  REQUIRE(parent_test_25 == false);

  // test uses
  auto uses_test_1 = pkb.isLineUsesVar("4", "x");
  REQUIRE(uses_test_1 == true);
  auto uses_test_2 = pkb.isLineUsesVar("5", "y");
  REQUIRE(uses_test_2 == true);
  auto uses_test_3 = pkb.isLineUsesVar("6", "z");
  REQUIRE(uses_test_3 == true);
  auto uses_test_4 = pkb.isLineUsesVar("7", "x");
  REQUIRE(uses_test_4 == true);
  auto uses_test_5 = pkb.isLineUsesVar("8", "y");
  REQUIRE(uses_test_5 == true);
  auto uses_test_6 = pkb.isLineUsesVar("9", "z");
  REQUIRE(uses_test_6 == true);
  auto uses_test_7 = pkb.isLineUsesVar("11", "x");
  REQUIRE(uses_test_7 == true);
  auto uses_test_8 = pkb.isLineUsesVar("12", "y");
  REQUIRE(uses_test_8 == true);
  auto uses_test_9 = pkb.isLineUsesVar("14", "z");
  REQUIRE(uses_test_9 == true);
  auto uses_test_10 = pkb.isLineUsesVar("16", "x");
  REQUIRE(uses_test_10 == true);
  auto uses_test_11 = pkb.isLineUsesVar("22", "x");
  REQUIRE(uses_test_11 == true);
  auto uses_test_12 = pkb.isLineUsesVar("23", "y");
  REQUIRE(uses_test_12 == true);
  auto uses_test_13 = pkb.isLineUsesVar("24", "z");
  REQUIRE(uses_test_13 == true);
  auto uses_test_14 = pkb.isLineUsesVar("1", "x");
  REQUIRE(uses_test_14 == false);
  auto uses_test_15 = pkb.isLineUsesVar("2", "y");
  REQUIRE(uses_test_15 == false);
  auto uses_test_16 = pkb.isLineUsesVar("4", "x");
  REQUIRE(uses_test_16 == true);
  auto uses_test_17 = pkb.isLineUsesVar("4", "y");
  REQUIRE(uses_test_17 == true);
  auto uses_test_18 = pkb.isLineUsesVar("4", "z");
  REQUIRE(uses_test_18 == true);
  auto uses_test_19 = pkb.isLineUsesVar("16", "y");
  REQUIRE(uses_test_19 == true);
  auto uses_test_20 = pkb.isLineUsesVar("16", "z");
  REQUIRE(uses_test_20 == true);

  auto uses_test_21 = pkb.isProcedureUsesVar("main", "x");
  REQUIRE(uses_test_21 == true);
  auto uses_test_22 = pkb.isProcedureUsesVar("main", "y");
  REQUIRE(uses_test_22 == true);
  auto uses_test_23 = pkb.isProcedureUsesVar("main", "z");
  REQUIRE(uses_test_23 == true);
  auto uses_test_24 = pkb.isProcedureUsesVar("main", "alpha");
  REQUIRE(uses_test_24 == false);
  auto uses_test_25 = pkb.isProcedureUsesVar("test", "beta");
  REQUIRE(uses_test_25 == false);

  std::unordered_set<std::string> uses_test_26_check;
  uses_test_26_check.insert("x");
  uses_test_26_check.insert("y");
  uses_test_26_check.insert("z");
  auto uses_test_26 = pkb.getVarUsedByProcedure("main");
  std::unordered_set<Variable> uses_test_26_set;
  if (uses_test_26) {
    for (const auto &elem : (*uses_test_26)) {
      uses_test_26_set.insert(elem);
    }
  }
  REQUIRE(uses_test_26_set == uses_test_26_check);

  // test modifies
  auto modifies_test_1 = pkb.isLineModifiesVar("1", "x");
  REQUIRE(modifies_test_1 == true);
  auto modifies_test_2 = pkb.isLineModifiesVar("2", "y");
  REQUIRE(modifies_test_2 == true);
  auto modifies_test_3 = pkb.isLineModifiesVar("3", "z");
  REQUIRE(modifies_test_3 == true);
  auto modifies_test_4 = pkb.isLineModifiesVar("5", "y");
  REQUIRE(modifies_test_4 == true);
  auto modifies_test_5 = pkb.isLineModifiesVar("10", "z");
  REQUIRE(modifies_test_5 == true);
  auto modifies_test_6 = pkb.isLineModifiesVar("17", "y");
  REQUIRE(modifies_test_6 == true);
  auto modifies_test_7 = pkb.isLineModifiesVar("1", "alpha");
  REQUIRE(modifies_test_7 == false);
  auto modifies_test_8 = pkb.isLineModifiesVar("2", "beta");
  REQUIRE(modifies_test_8 == false);
  auto modifies_test_9 = pkb.isLineModifiesVar("5", "z");
  REQUIRE(modifies_test_9 == false);
  auto modifies_test_10 = pkb.isLineModifiesVar("6", "alpha");
  REQUIRE(modifies_test_10 == false);
  auto modifies_test_11 = pkb.isLineModifiesVar("22", "y");
  REQUIRE(modifies_test_11 == false);
  auto modifies_test_12 = pkb.isLineModifiesVar("23", "y");
  REQUIRE(modifies_test_12 == false);

  auto modifies_test_13 = pkb.isProcedureModifiesVar("main", "x");
  REQUIRE(modifies_test_13 == true);
  auto modifies_test_14 = pkb.isProcedureModifiesVar("main", "y");
  REQUIRE(modifies_test_14 == true);
  auto modifies_test_15 = pkb.isProcedureModifiesVar("main", "z");
  REQUIRE(modifies_test_15 == true);
  auto modifies_test_16 = pkb.isProcedureModifiesVar("main", "alpha");
  REQUIRE(modifies_test_16 == false);
  auto modifies_test_17 = pkb.isProcedureModifiesVar("main", "beta");
  REQUIRE(modifies_test_17 == false);
  auto modifies_test_18 = pkb.isProcedureModifiesVar("main", "g");
  REQUIRE(modifies_test_18 == false);
  auto modifies_test_19 = pkb.isProcedureModifiesVar("test", "asd");
  REQUIRE(modifies_test_19 == false);
  auto modifies_test_20 = pkb.isProcedureModifiesVar("test", "zxc");
  REQUIRE(modifies_test_20 == false);

  std::unordered_set<std::string> modifies_test_21_check;
  modifies_test_21_check.insert("x");
  modifies_test_21_check.insert("y");
  modifies_test_21_check.insert("z");
  auto modifies_test_21 = pkb.getVarModifiedByProcedure("main");
  std::unordered_set<Variable> modifies_test_21_set;
  if (modifies_test_21) {
    for (const auto &elem : (*modifies_test_21)) {
      modifies_test_21_set.insert(elem);
    }
  }
  REQUIRE(modifies_test_21_set == modifies_test_21_check);

  // test pattern
  std::unordered_set<std::string> pattern_test_1_check;
  pattern_test_1_check.insert("5");
  pattern_test_1_check.insert("8");
  pattern_test_1_check.insert("12");
  pattern_test_1_check.insert("17");
  auto pattern_test_1 = pkb.getCompleteMatchLinesWithVar("y", "y+1");
  std::unordered_set<Variable> pattern_test_1_set;
  if (pattern_test_1) {
    for (const auto &elem : (*pattern_test_1)) {
      pattern_test_1_set.insert(elem);
    }
  }
  REQUIRE(pattern_test_1_set == pattern_test_1_check);

  std::unordered_set<std::string> pattern_test_2_check;
  pattern_test_2_check.insert("10");
  pattern_test_2_check.insert("14");
  pattern_test_2_check.insert("19");
  auto pattern_test_2 = pkb.getCompleteMatchLinesWithVar("z", "z+2");
  std::unordered_set<Variable> pattern_test_2_set;
  if (pattern_test_2) {
    for (const auto &elem : (*pattern_test_2)) {
      pattern_test_2_set.insert(elem);
    }
  }
  REQUIRE(pattern_test_2_set == pattern_test_2_check);

  std::unordered_set<std::string> pattern_test_3_check;
  pattern_test_3_check.insert("21");
  auto pattern_test_3 = pkb.getCompleteMatchLinesWithVar("z", "z+4");
  std::unordered_set<Variable> pattern_test_3_set;
  if (pattern_test_3) {
    for (const auto &elem : (*pattern_test_3)) {
      pattern_test_3_set.insert(elem);
    }
  }
  REQUIRE(pattern_test_3_set == pattern_test_3_check);

  std::unordered_set<std::string> pattern_test_4_check;
  pattern_test_4_check.insert("6");
  pattern_test_4_check.insert("9");
  pattern_test_4_check.insert("10");
  pattern_test_4_check.insert("13");
  pattern_test_4_check.insert("14");
  pattern_test_4_check.insert("15");
  pattern_test_4_check.insert("18");
  pattern_test_4_check.insert("19");
  pattern_test_4_check.insert("20");
  pattern_test_4_check.insert("21");
  auto pattern_test_4 = pkb.getPartialMatchLinesWithVar("z", "z");
  std::unordered_set<Variable> pattern_test_4_set;
  if (pattern_test_4) {
    for (const auto &elem : (*pattern_test_4)) {
      pattern_test_4_set.insert(elem);
    }
  }
  REQUIRE(pattern_test_4_set == pattern_test_4_check);

  std::unordered_set<std::string> pattern_test_5_check;
  pattern_test_5_check.insert("21");
  auto pattern_test_5 = pkb.getCompleteMatchLines("z+4");
  std::unordered_set<Variable> pattern_test_5_set;
  if (pattern_test_5) {
    for (const auto &elem : (*pattern_test_5)) {
      pattern_test_5_set.insert(elem);
    }
  }
  REQUIRE(pattern_test_5_set == pattern_test_5_check);

  std::unordered_set<std::string> pattern_test_6_check;
  pattern_test_6_check.insert("6");
  pattern_test_6_check.insert("9");
  pattern_test_6_check.insert("10");
  pattern_test_6_check.insert("13");
  pattern_test_6_check.insert("14");
  pattern_test_6_check.insert("15");
  pattern_test_6_check.insert("18");
  pattern_test_6_check.insert("19");
  pattern_test_6_check.insert("20");
  pattern_test_6_check.insert("21");
  auto pattern_test_6 = pkb.getPartialMatchLines("z");
  std::unordered_set<Line> pattern_test_6_set;
  if (pattern_test_6) {
    for (const auto &elem : (*pattern_test_6)) {
      pattern_test_6_set.insert(elem);
    }
  }
  REQUIRE(pattern_test_6_set == pattern_test_6_check);

  std::unordered_set<std::pair<std::string, std::string>, pair_hash>
      pattern_test_7_check;
  pattern_test_7_check.insert(std::pair<Line, Variable>("6", "z"));
  pattern_test_7_check.insert(std::pair<Line, Variable>("9", "z"));
  pattern_test_7_check.insert(std::pair<Line, Variable>("13", "z"));
  pattern_test_7_check.insert(std::pair<Line, Variable>("18", "z"));
  auto pattern_test_7 = pkb.getCompleteMatchLinesAndVars("z + 1");
  std::unordered_set<std::pair<Line, Variable>, pair_hash> pattern_test_7_set;
  if (pattern_test_7) {
    for (const auto &elem : (*pattern_test_7)) {
      pattern_test_7_set.insert(elem);
    }
  }
  REQUIRE(pattern_test_7_set == pattern_test_7_check);

  std::unordered_set<std::pair<std::string, std::string>, pair_hash>
      pattern_test_8_check;
  pattern_test_8_check.insert(std::pair<Line, Variable>("6", "z"));
  pattern_test_8_check.insert(std::pair<Line, Variable>("9", "z"));
  pattern_test_8_check.insert(std::pair<Line, Variable>("10", "z"));
  pattern_test_8_check.insert(std::pair<Line, Variable>("13", "z"));
  pattern_test_8_check.insert(std::pair<Line, Variable>("14", "z"));
  pattern_test_8_check.insert(std::pair<Line, Variable>("15", "z"));
  pattern_test_8_check.insert(std::pair<Line, Variable>("18", "z"));
  pattern_test_8_check.insert(std::pair<Line, Variable>("19", "z"));
  pattern_test_8_check.insert(std::pair<Line, Variable>("20", "z"));
  pattern_test_8_check.insert(std::pair<Line, Variable>("21", "z"));
  auto pattern_test_8 = pkb.getPartialMatchLinesAndVars("z");
  // std::cout << "test" << std::endl;
  std::unordered_set<std::pair<Line, Variable>, pair_hash> pattern_test_8_set;
  if (pattern_test_8) {
    for (const auto &elem : (*pattern_test_8)) {
      pattern_test_8_set.insert(elem);
    }
  }
  REQUIRE(pattern_test_8_set == pattern_test_8_check);

  std::unordered_set<std::pair<std::string, std::string>, pair_hash>
      pattern_test_9_check;
  pattern_test_9_check.insert(std::pair<Line, Variable>("1", "x"));
  pattern_test_9_check.insert(std::pair<Line, Variable>("2", "y"));
  pattern_test_9_check.insert(std::pair<Line, Variable>("3", "z"));
  pattern_test_9_check.insert(std::pair<Line, Variable>("5", "y"));
  pattern_test_9_check.insert(std::pair<Line, Variable>("6", "z"));
  pattern_test_9_check.insert(std::pair<Line, Variable>("8", "y"));
  pattern_test_9_check.insert(std::pair<Line, Variable>("9", "z"));
  pattern_test_9_check.insert(std::pair<Line, Variable>("10", "z"));
  pattern_test_9_check.insert(std::pair<Line, Variable>("12", "y"));
  pattern_test_9_check.insert(std::pair<Line, Variable>("13", "z"));
  pattern_test_9_check.insert(std::pair<Line, Variable>("14", "z"));
  pattern_test_9_check.insert(std::pair<Line, Variable>("15", "z"));
  pattern_test_9_check.insert(std::pair<Line, Variable>("17", "y"));
  pattern_test_9_check.insert(std::pair<Line, Variable>("18", "z"));
  pattern_test_9_check.insert(std::pair<Line, Variable>("19", "z"));
  pattern_test_9_check.insert(std::pair<Line, Variable>("20", "z"));
  pattern_test_9_check.insert(std::pair<Line, Variable>("21", "z"));
  pattern_test_9_check.insert(std::pair<Line, Variable>("22", "x"));
  auto pattern_test_9 = pkb.getAllPatternLinesAndVars();
  // std::cout << "test" << std::endl;
  std::unordered_set<std::pair<Line, Variable>, pair_hash> pattern_test_9_set(
      pattern_test_9.begin(), pattern_test_9.end());
  REQUIRE(pattern_test_9_set == pattern_test_9_check);

  std::unordered_set<std::string> pattern_test_10_check;
  pattern_test_10_check.insert("3");
  pattern_test_10_check.insert("6");
  pattern_test_10_check.insert("9");
  pattern_test_10_check.insert("10");
  pattern_test_10_check.insert("13");
  pattern_test_10_check.insert("14");
  pattern_test_10_check.insert("15");
  pattern_test_10_check.insert("18");
  pattern_test_10_check.insert("19");
  pattern_test_10_check.insert("20");
  pattern_test_10_check.insert("21");
  auto pattern_test_10 = pkb.getLineForAssignVar("z");
  std::unordered_set<Line> pattern_test_10_set;
  if (pattern_test_10) {
    for (const auto &elem : (*pattern_test_10)) {
      pattern_test_10_set.insert(elem);
    }
  }
  REQUIRE(pattern_test_10_set == pattern_test_10_check);

  auto pattern_test_11 = pkb.isPatternExists("z+1");
  REQUIRE(pattern_test_11 == true);
  auto pattern_test_12 = pkb.isPatternExists("z + 2");
  REQUIRE(pattern_test_12 == true);
  auto pattern_test_13 = pkb.isPatternExists("x-1");
  REQUIRE(pattern_test_13 == true);
  auto pattern_test_14 = pkb.isPatternExists("x+1");
  REQUIRE(pattern_test_14 == false);
  auto pattern_test_15 = pkb.isPatternExists("z + 20 * 3");
  REQUIRE(pattern_test_15 == false);
}

TEST_CASE ("Test deep nesting for parent*, uses, modifies") {
  auto ast =
      SimpleInterface::getAstFromFile("tests/simple_source/simple_2.txt");
  PKB::PKBManager pkb = PKB::PKBManager(ast);

  SECTION ("design entity variable") {
    // variable
    auto var_exist_test_1 = pkb.isVariableExists("i");
    REQUIRE(var_exist_test_1 == true);
    auto var_exist_test_2 = pkb.isVariableExists("x");
    REQUIRE(var_exist_test_2 == true);
    auto var_exist_test_3 = pkb.isVariableExists("y");
    REQUIRE(var_exist_test_3 == true);
    auto var_exist_test_4 = pkb.isVariableExists("a");
    REQUIRE(var_exist_test_4 == true);
    auto var_exist_test_5 = pkb.isVariableExists("b");
    REQUIRE(var_exist_test_5 == true);

    std::unordered_set<std::string> var_get_test_1_check;
    var_get_test_1_check.insert("i");
    var_get_test_1_check.insert("x");
    var_get_test_1_check.insert("y");
    var_get_test_1_check.insert("a");
    var_get_test_1_check.insert("b");
    auto var_get_test_1_vector = pkb.getVariableList();
    std::unordered_set<Variable> var_get_test_1_set(
        var_get_test_1_vector.begin(), var_get_test_1_vector.end());
    REQUIRE(var_get_test_1_set == var_get_test_1_check);
  }

  SECTION ("design entity assign") {
    // assign
    auto assign_exist_test_1 = pkb.isAssignExists("1");
    REQUIRE(assign_exist_test_1 == true);
    auto assign_exist_test_2 = pkb.isAssignExists("9");
    REQUIRE(assign_exist_test_2 == true);

    std::unordered_set<std::string> assign_get_test_1_check;
    assign_get_test_1_check.insert("1");
    assign_get_test_1_check.insert("9");
    auto assign_get_test_1 = pkb.getAssignList();
    std::unordered_set<Line> assign_get_test_1_set(assign_get_test_1.begin(),
                                                   assign_get_test_1.end());
    REQUIRE(assign_get_test_1_set == assign_get_test_1_check);
  }

  SECTION ("design entity statement") {
    // statement
    auto statement_exist_test_1 = pkb.isStatementExists("1");
    REQUIRE(statement_exist_test_1 == true);
    auto statement_exist_test_2 = pkb.isStatementExists("2");
    REQUIRE(statement_exist_test_2 == true);
    auto statement_exist_test_3 = pkb.isStatementExists("3");
    REQUIRE(statement_exist_test_3 == true);
    auto statement_exist_test_4 = pkb.isStatementExists("4");
    REQUIRE(statement_exist_test_4 == true);
    auto statement_exist_test_5 = pkb.isStatementExists("5");
    REQUIRE(statement_exist_test_5 == true);
    auto statement_exist_test_6 = pkb.isStatementExists("6");
    REQUIRE(statement_exist_test_6 == true);
    auto statement_exist_test_7 = pkb.isStatementExists("7");
    REQUIRE(statement_exist_test_7 == true);
    auto statement_exist_test_8 = pkb.isStatementExists("8");
    REQUIRE(statement_exist_test_8 == true);
    auto statement_exist_test_9 = pkb.isStatementExists("9");
    REQUIRE(statement_exist_test_9 == true);
    auto statement_exist_test_10 = pkb.isStatementExists("10");
    REQUIRE(statement_exist_test_10 == false);
    auto statement_exist_test_11 = pkb.isStatementExists("0");
    REQUIRE(statement_exist_test_11 == false);
    auto statement_exist_test_12 = pkb.isStatementExists("-2");
    REQUIRE(statement_exist_test_12 == false);

    std::unordered_set<std::string> statement_get_test_1_check;
    statement_get_test_1_check.insert("1");
    statement_get_test_1_check.insert("2");
    statement_get_test_1_check.insert("3");
    statement_get_test_1_check.insert("4");
    statement_get_test_1_check.insert("5");
    statement_get_test_1_check.insert("6");
    statement_get_test_1_check.insert("7");
    statement_get_test_1_check.insert("8");
    statement_get_test_1_check.insert("9");
    auto statement_get_test_1 = pkb.getStatementList();
    std::unordered_set<Line> statement_get_test_1_set(
        statement_get_test_1.begin(), statement_get_test_1.end());
    REQUIRE(statement_get_test_1_set == statement_get_test_1_check);
  }

  SECTION ("design entity print") {
    // print
    auto print_exist_test_1 = pkb.isPrintExists("6");
    REQUIRE(print_exist_test_1 == true);
    auto print_exist_test_2 = pkb.isPrintExists("8");
    REQUIRE(print_exist_test_2 == true);
    auto print_exist_test_3 = pkb.isPrintExists("5");
    REQUIRE(print_exist_test_3 == false);

    std::unordered_set<std::string> print_get_test_1_check;
    print_get_test_1_check.insert("6");
    print_get_test_1_check.insert("8");
    auto print_get_test_1 = pkb.getPrintList();
    std::unordered_set<Line> print_get_test_1_set(print_get_test_1.begin(),
                                                  print_get_test_1.end());
    REQUIRE(print_get_test_1_set == print_get_test_1_check);
  }

  SECTION ("design entity read") {
    auto read_exist_test_1 = pkb.isReadExists("5");
    REQUIRE(read_exist_test_1 == true);
    auto read_exist_test_2 = pkb.isReadExists("7");
    REQUIRE(read_exist_test_2 == true);
    auto read_exist_test_3 = pkb.isReadExists("2000");
    REQUIRE(read_exist_test_3 == false);

    std::unordered_set<std::string> read_get_test_1_check;
    read_get_test_1_check.insert("5");
    read_get_test_1_check.insert("7");
    auto read_get_test_1 = pkb.getReadList();
    std::unordered_set<Line> read_get_test_1_set(read_get_test_1.begin(),
                                                 read_get_test_1.end());
    REQUIRE(read_get_test_1_set == read_get_test_1_check);
  }

  SECTION ("design entity while") {
    auto while_exist_test_1 = pkb.isWhileExists("3");
    REQUIRE(while_exist_test_1 == true);
    auto while_exist_test_2 = pkb.isWhileExists("4");
    REQUIRE(while_exist_test_2 == false);

    std::unordered_set<std::string> while_get_test_1_check;
    while_get_test_1_check.insert("3");
    auto while_get_test_1 = pkb.getWhileList();
    std::unordered_set<Line> while_get_test_1_set(while_get_test_1.begin(),
                                                  while_get_test_1.end());
    REQUIRE(while_get_test_1_set == while_get_test_1_check);
  }

  SECTION ("design entity if") {
    auto if_exist_test_1 = pkb.isIfExists("2");
    REQUIRE(if_exist_test_1 == true);
    auto if_exist_test_2 = pkb.isIfExists("4");
    REQUIRE(if_exist_test_2 == true);

    std::unordered_set<std::string> if_get_test_1_check;
    if_get_test_1_check.insert("2");
    if_get_test_1_check.insert("4");
    auto if_get_test_1 = pkb.getIfList();
    std::unordered_set<Line> if_get_test_1_set(if_get_test_1.begin(),
                                               if_get_test_1.end());
    REQUIRE(if_get_test_1_set == if_get_test_1_check);
  }

  SECTION ("design entity constant") {
    auto constant_exist_test_1 = pkb.isConstantExists("5");
    REQUIRE(constant_exist_test_1 == true);
    auto constant_exist_test_2 = pkb.isConstantExists("222");
    REQUIRE(constant_exist_test_2 == false);

    std::unordered_set<std::string> constant_get_test_1_check;
    constant_get_test_1_check.insert("5");
    auto constant_get_test_1 = pkb.getConstantList();
    std::unordered_set<Constant> constant_get_test_1_set(
        constant_get_test_1.begin(), constant_get_test_1.end());
    REQUIRE(constant_get_test_1_set == constant_get_test_1_check);
  }

  SECTION ("design entity procedure") {
    auto proc_exist_test_1 = pkb.isProcedureExists("main");
    REQUIRE(proc_exist_test_1 == true);
    auto proc_exist_test_2 = pkb.isProcedureExists("blah");
    REQUIRE(proc_exist_test_2 == false);

    std::unordered_set<std::string> procedure_get_test_1_check;
    procedure_get_test_1_check.insert("main");
    auto procedure_get_test_1 = pkb.getProcedureList();
    std::unordered_set<Procedure> procedure_get_test_1_set(
        procedure_get_test_1.begin(), procedure_get_test_1.end());
    REQUIRE(procedure_get_test_1_set == procedure_get_test_1_check);
  }

  SECTION ("follows relations") {
    auto follows_test_1 = pkb.isLineFollowLine("1", "2");
    REQUIRE(follows_test_1 == true);
    auto follows_test_2 = pkb.isLineFollowLine("5", "6");
    REQUIRE(follows_test_2 == true);
    auto follows_test_3 = pkb.isLineFollowLine("7", "8");
    REQUIRE(follows_test_3 == true);
    auto follows_test_4 = pkb.isLineFollowLine("1", "2");
    REQUIRE(follows_test_4 == true);
    auto follows_test_5 = pkb.isLineFollowLine("5", "6");
    REQUIRE(follows_test_5 == true);
    auto follows_test_6 = pkb.isLineFollowLine("7", "8");
    REQUIRE(follows_test_6 == true);

    std::string follows_test_7_check = "2";
    auto follows_test_7 = pkb.getFollowingLine("1");
    LineAfter follows_test_7_line = "";
    if (follows_test_7) {
      follows_test_7_line = (*follows_test_7);
    }
    REQUIRE(follows_test_7_line == follows_test_7_check);

    std::unordered_set<std::string> follows_test_8_check;
    follows_test_8_check.insert("2");
    auto follows_test_8 = pkb.getFollowingLineS("1");
    std::unordered_set<LineAfter> follows_test_8_set;
    if (follows_test_8) {
      for (const auto &elem : (*follows_test_8)) {
        follows_test_8_set.insert(elem);
      }
    }
    REQUIRE(follows_test_8_set == follows_test_8_check);

    std::unordered_set<std::string> follows_test_9_check;
    auto follows_test_9 = pkb.getFollowingLine("2");
    std::unordered_set<LineAfter> follows_test_9_set;
    LineAfter follows_test_9_line = "";
    if (follows_test_9) {
      follows_test_9_line = (*follows_test_9);
    }
    REQUIRE(follows_test_9_set == follows_test_9_check);

    std::unordered_set<std::string> follows_test_10_check;
    auto follows_test_10 = pkb.getFollowingLineS("2");
    std::unordered_set<LineAfter> follows_test_10_set;
    if (follows_test_10) {
      for (const auto &elem : (*follows_test_10)) {
        follows_test_10_set.insert(elem);
      }
    }
    REQUIRE(follows_test_10_set == follows_test_10_check);

    std::unordered_set<std::string> follows_test_11_check;
    auto follows_test_11 = pkb.getFollowingLineS("9");
    std::unordered_set<LineAfter> follows_test_11_set;
    if (follows_test_11) {
      for (const auto &elem : (*follows_test_11)) {
        follows_test_11_set.insert(elem);
      }
    }
    REQUIRE(follows_test_11_set == follows_test_11_check);
  }

  SECTION ("parent relations") {
    auto parent_test_1 = pkb.isLineParentLine("2", "3");
    REQUIRE(parent_test_1 == true);
    auto parent_test_2 = pkb.isLineParentLine("3", "4");
    REQUIRE(parent_test_2 == true);
    auto parent_test_3 = pkb.isLineParentLine("4", "5");
    REQUIRE(parent_test_3 == true);
    auto parent_test_4 = pkb.isLineParentLine("4", "6");
    REQUIRE(parent_test_4 == true);
    auto parent_test_5 = pkb.isLineParentLine("4", "7");
    REQUIRE(parent_test_5 == true);
    auto parent_test_6 = pkb.isLineParentLine("4", "8");
    REQUIRE(parent_test_6 == true);
    auto parent_test_7 = pkb.isLineParentLine("2", "9");
    REQUIRE(parent_test_7 == true);
    auto parent_test_8 = pkb.isLineParentLineS("2", "3");
    REQUIRE(parent_test_8 == true);
    auto parent_test_9 = pkb.isLineParentLineS("2", "4");
    REQUIRE(parent_test_9 == true);
    auto parent_test_10 = pkb.isLineParentLineS("2", "5");
    REQUIRE(parent_test_10 == true);
    auto parent_test_11 = pkb.isLineParentLineS("2", "6");
    REQUIRE(parent_test_11 == true);
    auto parent_test_12 = pkb.isLineParentLineS("2", "7");
    REQUIRE(parent_test_12 == true);
    auto parent_test_13 = pkb.isLineParentLineS("2", "8");
    REQUIRE(parent_test_13 == true);
    auto parent_test_14 = pkb.isLineParentLineS("2", "9");
    REQUIRE(parent_test_14 == true);
    auto parent_test_15 = pkb.isLineParentLineS("3", "5");
    REQUIRE(parent_test_15 == true);
    auto parent_test_16 = pkb.isLineParentLineS("3", "6");
    REQUIRE(parent_test_16 == true);
    auto parent_test_17 = pkb.isLineParentLineS("3", "7");
    REQUIRE(parent_test_17 == true);
    auto parent_test_18 = pkb.isLineParentLineS("3", "8");
    REQUIRE(parent_test_18 == true);
    auto parent_test_19 = pkb.isLineParentLineS("4", "5");
    REQUIRE(parent_test_19 == true);
    auto parent_test_20 = pkb.isLineParentLineS("4", "6");
    REQUIRE(parent_test_20 == true);
    auto parent_test_21 = pkb.isLineParentLineS("4", "7");
    REQUIRE(parent_test_21 == true);
    auto parent_test_22 = pkb.isLineParentLineS("4", "8");
    REQUIRE(parent_test_22 == true);

    std::unordered_set<std::string> parent_test_23_check;
    std::unordered_set<Variable> parent_test_23_set;
    auto parent_test_23 = pkb.getParentLineS("1");
    if (parent_test_23) {
      for (const auto &elem : (*parent_test_23)) {
        parent_test_23_set.insert(elem);
      }
    }
    REQUIRE(parent_test_23_set == parent_test_23_check);

    std::unordered_set<std::string> parent_test_24_check;
    parent_test_24_check.insert("2");
    std::unordered_set<Variable> parent_test_24_set;
    auto parent_test_24 = pkb.getParentLineS("3");
    if (parent_test_24) {
      for (const auto &elem : (*parent_test_24)) {
        parent_test_24_set.insert(elem);
      }
    }
    REQUIRE(parent_test_24_set == parent_test_24_check);

    std::unordered_set<std::string> parent_test_25_check;
    parent_test_25_check.insert("2");
    parent_test_25_check.insert("3");
    parent_test_25_check.insert("4");
    std::unordered_set<Variable> parent_test_25_set;
    auto parent_test_25 = pkb.getParentLineS("6");
    if (parent_test_25) {
      for (const auto &elem : (*parent_test_25)) {
        parent_test_25_set.insert(elem);
      }
    }
    REQUIRE(parent_test_25_set == parent_test_25_check);
  }

  SECTION ("uses relations") {
    auto uses_test_1 = pkb.isLineUsesVar("2", "i");
    REQUIRE(uses_test_1 == true);
    auto uses_test_2 = pkb.isLineUsesVar("3", "i");
    REQUIRE(uses_test_2 == true);
    auto uses_test_3 = pkb.isLineUsesVar("4", "i");
    REQUIRE(uses_test_3 == true);
    auto uses_test_4 = pkb.isLineUsesVar("2", "y");
    REQUIRE(uses_test_4 == true);
    auto uses_test_5 = pkb.isLineUsesVar("3", "y");
    REQUIRE(uses_test_5 == true);
    auto uses_test_6 = pkb.isLineUsesVar("4", "y");
    REQUIRE(uses_test_6 == true);
    auto uses_test_7 = pkb.isLineUsesVar("2", "b");
    REQUIRE(uses_test_7 == true);
    auto uses_test_8 = pkb.isLineUsesVar("3", "b");
    REQUIRE(uses_test_8 == true);
    auto uses_test_9 = pkb.isLineUsesVar("4", "b");
    REQUIRE(uses_test_9 == true);
    auto uses_test_10 = pkb.isProcedureUsesVar("main", "i");
    REQUIRE(uses_test_10 == true);
    auto uses_test_11 = pkb.isProcedureUsesVar("main", "y");
    REQUIRE(uses_test_11 == true);
    auto uses_test_12 = pkb.isProcedureUsesVar("main", "b");
    REQUIRE(uses_test_12 == true);

    std::unordered_set<std::string> uses_test_13_check;
    uses_test_13_check.insert("i");
    uses_test_13_check.insert("y");
    uses_test_13_check.insert("b");
    auto uses_test_13 = pkb.getVarUsedByLine("2");
    std::unordered_set<Variable> uses_test_13_set;
    if (uses_test_13) {
      for (const auto &elem : (*uses_test_13)) {
        uses_test_13_set.insert(elem);
      }
    }
    REQUIRE(uses_test_13_set == uses_test_13_check);

    std::unordered_set<std::string> uses_test_14_check;
    uses_test_14_check.insert("i");
    uses_test_14_check.insert("y");
    uses_test_14_check.insert("b");
    auto uses_test_14 = pkb.getVarUsedByLine("3");
    std::unordered_set<Variable> uses_test_14_set;
    if (uses_test_14) {
      for (const auto &elem : (*uses_test_14)) {
        uses_test_14_set.insert(elem);
      }
    }
    REQUIRE(uses_test_14_set == uses_test_14_check);

    std::unordered_set<std::string> uses_test_15_check;
    uses_test_15_check.insert("i");
    uses_test_15_check.insert("y");
    uses_test_15_check.insert("b");
    auto uses_test_15 = pkb.getVarUsedByLine("4");
    std::unordered_set<Variable> uses_test_15_set;
    if (uses_test_15) {
      for (const auto &elem : (*uses_test_15)) {
        uses_test_15_set.insert(elem);
      }
    }
    REQUIRE(uses_test_15_set == uses_test_15_check);

    std::unordered_set<std::string> uses_test_16_check;
    uses_test_16_check.insert("i");
    uses_test_16_check.insert("y");
    uses_test_16_check.insert("b");
    auto uses_test_16 = pkb.getVarUsedByProcedure("main");
    std::unordered_set<Variable> uses_test_16_set;
    if (uses_test_16) {
      for (const auto &elem : (*uses_test_16)) {
        uses_test_16_set.insert(elem);
      }
    }
    REQUIRE(uses_test_16_set == uses_test_16_check);
  }

  SECTION ("modifies relations") {
    auto modifies_test_1 = pkb.isLineModifiesVar("1", "i");
    REQUIRE(modifies_test_1 == true);
    auto modifies_test_2 = pkb.isLineModifiesVar("4", "x");
    REQUIRE(modifies_test_2 == true);
    auto modifies_test_3 = pkb.isLineModifiesVar("4", "a");
    REQUIRE(modifies_test_3 == true);
    auto modifies_test_4 = pkb.isLineModifiesVar("9", "i");
    REQUIRE(modifies_test_4 == true);
    auto modifies_test_5 = pkb.isLineModifiesVar("2", "x");
    REQUIRE(modifies_test_5 == true);
    auto modifies_test_6 = pkb.isLineModifiesVar("2", "a");
    REQUIRE(modifies_test_6 == true);
    auto modifies_test_7 = pkb.isLineModifiesVar("3", "x");
    REQUIRE(modifies_test_7 == true);
    auto modifies_test_8 = pkb.isLineModifiesVar("3", "a");
    REQUIRE(modifies_test_8 == true);
    auto modifies_test_9 = pkb.isProcedureModifiesVar("main", "i");
    REQUIRE(modifies_test_9 == true);
    auto modifies_test_10 = pkb.isProcedureModifiesVar("main", "x");
    REQUIRE(modifies_test_10 == true);
    auto modifies_test_11 = pkb.isProcedureModifiesVar("main", "a");
    REQUIRE(modifies_test_11 == true);

    std::unordered_set<std::string> modifies_test_12_check;
    modifies_test_12_check.insert("i");
    auto modifies_test_12 = pkb.getVarModifiedByLine("1");
    std::unordered_set<Variable> modifies_test_12_set;
    if (modifies_test_12) {
      for (const auto &elem : (*modifies_test_12)) {
        modifies_test_12_set.insert(elem);
      }
    }
    REQUIRE(modifies_test_12_set == modifies_test_12_check);

    std::unordered_set<std::string> modifies_test_13_check;
    modifies_test_13_check.insert("i");
    modifies_test_13_check.insert("x");
    modifies_test_13_check.insert("a");
    auto modifies_test_13 = pkb.getVarModifiedByLine("2");
    std::unordered_set<Variable> modifies_test_13_set;
    if (modifies_test_13) {
      for (const auto &elem : (*modifies_test_13)) {
        modifies_test_13_set.insert(elem);
      }
    }
    REQUIRE(modifies_test_13_set == modifies_test_13_check);

    std::unordered_set<std::string> modifies_test_14_check;
    modifies_test_14_check.insert("x");
    modifies_test_14_check.insert("a");
    auto modifies_test_14 = pkb.getVarModifiedByLine("3");
    std::unordered_set<Variable> modifies_test_14_set;
    if (modifies_test_14) {
      for (const auto &elem : (*modifies_test_14)) {
        modifies_test_14_set.insert(elem);
      }
    }
    REQUIRE(modifies_test_14_set == modifies_test_14_check);

    std::unordered_set<std::string> modifies_test_15_check;
    modifies_test_15_check.insert("i");
    modifies_test_15_check.insert("x");
    modifies_test_15_check.insert("a");
    auto modifies_test_15 = pkb.getVarModifiedByProcedure("main");
    std::unordered_set<Variable> modifies_test_15_set;
    if (modifies_test_15) {
      for (const auto &elem : (*modifies_test_15)) {
        modifies_test_15_set.insert(elem);
      }
    }
    REQUIRE(modifies_test_15_set == modifies_test_15_check);
  }
}

TEST_CASE ("Test detection of semantic errors in AST") {
  SECTION ("procedure and variable with the same name") {
    auto ast = SimpleInterface::getAstFromFile(
        "tests/semantic_errors/proc_variable_same_name.txt");

    REQUIRE_THROWS_WITH(
        PKB::PKBManager(ast),
        "Found procedure and variable with the same name: 'main'.");
  }
}