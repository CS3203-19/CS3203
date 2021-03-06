#include "spa_manager/spa_manager.h"
#include <sstream>
#include <string>
#include <vector>
#include "program_knowledge_base/pkb_manager.h"
#include "query_builder/core/exceptions.h"
#include "query_builder/pql/pql.h"
#include "query_builder/query_builder.h"
#include "query_executor/query_executor.h"
#include "simple_parser/interface.h"

using namespace PKB;
using namespace Simple;
using namespace QE;

void SPAManager::loadSimpleSource(std::string filename) {
  // Complete parse of code to AST
  AST ast = Simple::SimpleInterface::getAstFromFile(filename);

  // Store PKB variable in class for querying laster
  pkb = new PKBManager(ast);
  qm = new QueryExecutor(pkb);
}

std::vector<std::string> SPAManager::query(std::string& pql_query) {
  auto qe = QueryBuilder();
  auto query = qe.makePqlQuery(pql_query);
  auto query_results = qm->makeQuery(&query);
  // Can't reuse cache across queries
  pkb->clearCache();
  pkb->clearBipCache();
  return query_results;
}

SPAManager::~SPAManager() {
  delete pkb;
  delete qm;
}
