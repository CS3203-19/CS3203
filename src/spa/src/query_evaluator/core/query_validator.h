#pragma once
#include <memory>  // future use of smart pointers
#include <string>
#include <vector>

#include "query_evaluator/pql/query.h"

namespace QE {

//! Utility class for validating the semantics of Query objects after parsing
class QueryValidator {
 private:
  //! Checks that the synonym in a pattern clause is declarated as assign
  void validatePatternVariableAsAssign(const Query&);
  //! Checks neither Modify nor Uses has _ as the first argument (ambiguous)
  void validateModifyUsesNoFirstArgUnderscore(const Query&);

 public:
  //! \brief Checks the semantics in the Query, throws PQLValidationException if
  //! an error is detected
  void validateQuery(const Query&);
};

}  // namespace QE