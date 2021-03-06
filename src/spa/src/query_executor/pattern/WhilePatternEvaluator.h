#include <cassert>
#include <sstream>
#include <string>
#include <vector>
#include "query_executor/pattern/PatternEvaluator.h"

class WhilePatternEvaluator : public PatternEvaluator {
 private:
  std::optional<SingleConstraintSet> handlePatternLHSUnderscoreRHSUnderscore()
      override {
    std::cout << "LHS Pattern RHS underscore not valid for assign-while\n";
    assert(false);
  }
  std::optional<SingleConstraintSet> handlePatternLHSQuoteIdentRHSUnderscore()
      override {
    std::cout << "LHS QuoteIdent RHS underscore not valid for assign-while\n";
    assert(false);
  }
  PairedConstraintSet handlePatternLHSSynonymRHSUnderscore() override {
    std::cout << "LHS Underscore RHS underscore not valid for assign-while\n";
    assert(false);
  }

  std::optional<SingleConstraintSet> handlePatternLHSUnderscoreRHSPartialMatch()
      override {
    std::cout << "LHS Underscore RHS partial not valid for assign-while\n";
    assert(false);
  }
  std::optional<SingleConstraintSet> handlePatternLHSQuoteIdentRHSPartialMatch()
      override {
    std::cout << "LHS QuoteIdent RHS partial not valid for assign-while\n";
    assert(false);
  }
  std::optional<PairedConstraintSet> handlePatternLHSSynonymRHSPartialMatch()
      override {
    std::cout << "LHS Synonym RHS partial not valid for assign-while\n";
    assert(false);
  }
  std::optional<SingleConstraintSet>
  handlePatternLHSUnderscoreRHSCompleteMatch() override {
    std::cout << "LHS Underscore RHS complete not valid for assign-while\n";
    assert(false);
  }
  std::optional<SingleConstraintSet>
  handlePatternLHSQuoteIdentRHSCompleteMatch() override {
    std::cout << "LHS QuoteIdent RHS complete not valid for assign-while\n";
    assert(false);
  }
  std::optional<PairedConstraintSet> handlePatternLHSSynonymRHSCompleteMatch()
      override {
    std::cout << "LHS Synonym RHS complete not valid for assign-while\n";
    assert(false);
  }
  std::optional<SingleConstraintSet> handlePatternLHSUnderscoreRHSNull()
      override {
    // pattern w (_, _)
    // Get only the lines from the lines & vars
    // There can be while statements without a control variable
    PairedConstraintSet allLinesVars = pkb->getAllWhilePatternLinesAndVars();
    SingleConstraintSet lines;
    for (const auto& [line, var] : allLinesVars) {
      lines.insert(line);
    }
    return lines;
  }
  std::optional<SingleConstraintSet> handlePatternLHSQuoteIdentRHSNull()
      override {
    // pattern w ("x", _)
    return pkb->getWhilePatternLine(*argLeftAsBasic);
  }
  std::optional<PairedConstraintSet> handlePatternLHSSynonymRHSNull() override {
    // pattern w (v, _)
    return pkb->getAllWhilePatternLinesAndVars();
  }

 public:
  WhilePatternEvaluator(std::vector<QE::Declaration>* decls,
                        QE::PatternCond* pattern, PKBManager* pkb,
                        ConstraintDatabase& db)
      : PatternEvaluator(decls, pattern, pkb, db) {}
};