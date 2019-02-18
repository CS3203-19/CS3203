/*!
 * \file   interface.h
 * \brief  Interface for the SIMPLE language.
 *
 * The bridging interface for SIMPLE subcomponents with the SPA manager.
 *
 * \date   2019-02-15
 */

#include <memory>

#include "simple_parser/lexer.h"
#include "simple_parser/parser.h"
#include "simple_parser/token.h"

namespace Simple {
class SimpleInterface {
 public:
  static std::shared_ptr<ProcedureNode> getAstFromFile(std::string filename);
};
}  // namespace Simple
