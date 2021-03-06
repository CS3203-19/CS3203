#pragma once
#include <cassert>
#include <optional>
#include <string>
#include <vector>
#include "program_knowledge_base/pkb_manager.h"
#include "query_builder/pql/pql.h"
#include "query_executor/query_executor.h"
#include "query_executor/suchthat/SuchThatEvaluator.h"

using namespace PKB;
using namespace QE;

class ParentEvaluator : public SuchThatEvaluator {
 public:
  ParentEvaluator(std::vector<QE::Declaration>* decls, QE::RelCond* relCond,
                  PKBManager* pkb, ConstraintDatabase& db)
      : SuchThatEvaluator(decls, relCond, pkb, db){};

  std::unordered_set<std::string> handleLeftSynonymRightBasic(
      std::string& basic_value) override {
    // Parent(s, 3)
    if (auto beforeLine = pkb->getParentLine(basic_value)) {
      return {*beforeLine};
    } else {
      return {};
    }
  }
  std::unordered_set<std::string> handleRightSynonymLeftBasic(
      std::string& basic_value) override {
    // Parent(3, s)
    if (auto afterLine = pkb->getChildLine(basic_value)) {
      return {*afterLine};
    } else {
      return {};
    }
  }
  bool handleLeftSynonymRightUnderscore(std::string& arg_value) override {
    // Parent(s, _) (for each s)
    return pkb->getChildLine(arg_value).has_value();
  }
  bool handleRightSynonymLeftUnderscore(std::string& arg_value) override {
    // Parent(_, s) (for each s)
    return pkb->getParentLine(arg_value).has_value();
  }
  bool handleBothArgsSynonyms(std::string& arg_left,
                              std::string& arg_right) override {
    // Parent(s, s1)
    return pkb->isLineParentLine(arg_left, arg_right);
  }
  bool handleDoubleUnderscore() override {
    return !pkb->isLineFollowLineTSetEmpty();
  }
  bool handleLeftBasicRightUnderscore(std::string& arg) override {
    // Parent(3, _)
    return pkb->getChildLine(arg).has_value();
  }
  bool handleRightBasicLeftUnderscore(std::string& arg) override {
    // Parent(_, 3)
    return pkb->getParentLine(arg).has_value();
  }
  bool handleBothArgsBasic(std::string& arg_left,
                           std::string& arg_right) override {
    // Parent(2, 3)?
    return pkb->isLineParentLine(arg_left, arg_right);
  }
};