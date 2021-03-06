#include "catch.hpp"

#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>
#include "program_knowledge_base/pkb_manager.h"
#include "query_builder/core/exceptions.h"
#include "query_builder/pql/pql.h"
#include "query_builder/query_builder.h"
#include "query_executor/query_executor.h"
#include "simple_parser/interface.h"

using namespace QE;

TEST_CASE ("Test Query Executor With functionality - system_tests/src/1.txt") {
  auto ast =
      Simple::SimpleInterface::getAstFromFile("tests/system_tests/src/1.txt");

  // Store PKB variable in class for querying later
  auto pkb = new PKBManager(ast);
  auto qm = new QueryExecutor(pkb);
  auto qe = QueryBuilder();

  SECTION ("Test basic with: 2 = 2") {
    auto querystr = std::string("assign a; Select a with 2 = 2");
    auto query = qe.makePqlQuery(querystr);
    REQUIRE(qm->makeQuery(&query) ==
            std::vector<std::string>{"10", "11", "12", "13", "14", "15", "16",
                                     "21", "22"});
  }

  SECTION ("Test basic with: 2 = 3") {
    auto querystr = std::string("assign a; Select a with 2 = 3");
    auto query = qe.makePqlQuery(querystr);
    REQUIRE(qm->makeQuery(&query) == std::vector<std::string>{});
  }

  SECTION ("Test basic with: \"asdf\" = \"asdf\"") {
    auto querystr = std::string("assign a; Select a with \"asdf\" = \"asdf\"");
    auto query = qe.makePqlQuery(querystr);
    REQUIRE(qm->makeQuery(&query) ==
            std::vector<std::string>{"10", "11", "12", "13", "14", "15", "16",
                                     "21", "22"});
  }

  SECTION ("Test basic with:\"asdf\" = \"asdggg\"") {
    auto querystr =
        std::string("assign a; Select a with \"asdf\" = \"asdggg\"");
    auto query = qe.makePqlQuery(querystr);
    REQUIRE(qm->makeQuery(&query) == std::vector<std::string>{});
  }

  SECTION ("Test basic with: n1 = n2") {
    auto querystr = std::string("prog_line n1, n2; Select n1 with n1 = n2");
    std::vector<std::string> proglines = {
        "1", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19",
        "2", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29",
        "3", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39",
        "4", "40", "41", "42", "43", "5",  "6",  "7",  "8",  "9"};
    auto query = qe.makePqlQuery(querystr);
    REQUIRE(qm->makeQuery(&query) == proglines);
  }

  SECTION (
      "Test with that has n2 constrained to 1 value: n1 = n2, Next(1, n2)") {
    auto querystr = std::string(
        "prog_line n1, n2; Select n1 such that Next(1, n2) with n1 = n2");
    std::vector<std::string> proglines = {"2"};
    auto query = qe.makePqlQuery(querystr);
    REQUIRE(qm->makeQuery(&query) == proglines);
  }

  SECTION ("Test impossible with: n1 = n2, Next(n1, n2)") {
    auto querystr = std::string(
        "prog_line n1, n2; Select n1 such that Next(n1, n2) with n1 = n2");
    std::vector<std::string> proglines = {};
    auto query = qe.makePqlQuery(querystr);
    REQUIRE(qm->makeQuery(&query) == proglines);
  }

  SECTION (
      "Test lines that have control flow to themselves with: n1 = n2, "
      "Next*(n1, n2)") {
    auto querystr = std::string(
        "prog_line n1, n2; Select n1 such that Next*(n1, n2) with n1 = n2");
    std::vector<std::string> proglines = {"10", "11", "12", "13",
                                          "14", "15", "16", "9"};
    auto query = qe.makePqlQuery(querystr);
    REQUIRE(qm->makeQuery(&query) == proglines);
  }

  SECTION ("Test basic with: n1 = n1") {
    auto querystr = std::string("prog_line n1, n2; Select n1 with n1 = n1");
    std::vector<std::string> proglines = {
        "1", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19",
        "2", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29",
        "3", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39",
        "4", "40", "41", "42", "43", "5",  "6",  "7",  "8",  "9"};
    auto query = qe.makePqlQuery(querystr);
    REQUIRE(qm->makeQuery(&query) == proglines);
  }

  SECTION ("Test basic with: n1 = 1") {
    auto querystr = std::string("prog_line n1, n2; Select n1 with n1 = 1");
    std::vector<std::string> proglines = {"1"};
    auto query = qe.makePqlQuery(querystr);
    REQUIRE(qm->makeQuery(&query) == proglines);
  }

  SECTION ("Test basic with: 1 = n1") {
    auto querystr = std::string("prog_line n1, n2; Select n1 with 1 = n1");
    std::vector<std::string> proglines = {"1"};
    auto query = qe.makePqlQuery(querystr);
    REQUIRE(qm->makeQuery(&query) == proglines);
  }

  SECTION ("Test no-result basic with: n1 = 50") {
    auto querystr = std::string("prog_line n1, n2; Select n1 with n1 = 50");
    std::vector<std::string> proglines = {};
    auto query = qe.makePqlQuery(querystr);
    REQUIRE(qm->makeQuery(&query) == proglines);
  }

  SECTION ("Test no-result basic with: 50 = n1") {
    auto querystr = std::string("prog_line n1, n2; Select n1 with 50 = n1");
    std::vector<std::string> proglines = {};
    auto query = qe.makePqlQuery(querystr);
    REQUIRE(qm->makeQuery(&query) == proglines);
  }

  SECTION ("Test with: s.stmt# = 1") {
    auto querystr = std::string("stmt s; Select s with s.stmt# = 1");
    std::vector<std::string> proglines = {"1"};
    auto query = qe.makePqlQuery(querystr);
    REQUIRE(qm->makeQuery(&query) == proglines);
  }

  SECTION ("Test with: 1 = s.stmt#") {
    auto querystr = std::string("stmt s; Select s with 1 = s.stmt#");
    std::vector<std::string> proglines = {"1"};
    auto query = qe.makePqlQuery(querystr);
    REQUIRE(qm->makeQuery(&query) == proglines);
  }

  SECTION ("Test with: r.stmt# = 6") {
    auto querystr = std::string("read r; Select r with r.stmt# = 6");
    std::vector<std::string> proglines = {"6"};
    auto query = qe.makePqlQuery(querystr);
    REQUIRE(qm->makeQuery(&query) == proglines);
  }

  SECTION ("Test with: pn.stmt# = 18") {
    auto querystr = std::string("print pn; Select pn with pn.stmt# = 18");
    std::vector<std::string> proglines = {"18"};
    auto query = qe.makePqlQuery(querystr);
    REQUIRE(qm->makeQuery(&query) == proglines);
  }

  SECTION ("Test with: w.stmt# = 9") {
    auto querystr = std::string("while w; Select w with w.stmt# = 9");
    std::vector<std::string> proglines = {"9"};
    auto query = qe.makePqlQuery(querystr);
    REQUIRE(qm->makeQuery(&query) == proglines);
  }

  SECTION ("Test with: ifs.stmt# = 17") {
    auto querystr = std::string("if ifs; Select ifs with ifs.stmt# = 17");
    std::vector<std::string> proglines = {"17"};
    auto query = qe.makePqlQuery(querystr);
    REQUIRE(qm->makeQuery(&query) == proglines);
  }

  SECTION ("Test with: a.stmt# = 10") {
    auto querystr = std::string("assign a; Select a with a.stmt# = 10");
    std::vector<std::string> proglines = {"10"};
    auto query = qe.makePqlQuery(querystr);
    REQUIRE(qm->makeQuery(&query) == proglines);
  }

  SECTION ("Test with: c.value = 100") {
    auto querystr = std::string("constant c; Select c with c.value = 100");
    std::vector<std::string> proglines = {"100"};
    auto query = qe.makePqlQuery(querystr);
    REQUIRE(qm->makeQuery(&query) == proglines);
  }

  SECTION ("Test with: p.procName = \"main\"") {
    auto querystr =
        std::string("procedure p; Select p with p.procName = \"main\"");
    std::vector<std::string> proglines = {"main"};
    auto query = qe.makePqlQuery(querystr);
    REQUIRE(qm->makeQuery(&query) == proglines);
  }

  SECTION ("Test with: \"main\" = p.procName") {
    auto querystr =
        std::string("procedure p; Select p with \"main\" = p.procName");
    std::vector<std::string> proglines = {"main"};
    auto query = qe.makePqlQuery(querystr);
    REQUIRE(qm->makeQuery(&query) == proglines);
  }

  SECTION ("Test with: v.varName = \"v1\"") {
    auto querystr = std::string("variable v; Select v with v.varName = \"v1\"");
    std::vector<std::string> proglines = {"v1"};
    auto query = qe.makePqlQuery(querystr);
    REQUIRE(qm->makeQuery(&query) == proglines);
  }

  SECTION (
      "Test complex with (all statements where 'v' is used): Select s such "
      "that Uses(s, v) with v.varName = \"v\"") {
    auto querystr = std::string(
        "stmt s; variable v; Select s such that Uses(s, v) with v.varName = "
        "\"v\"");
    std::vector<std::string> proglines = {"10", "26", "27", "38", "9"};
    auto query = qe.makePqlQuery(querystr);
    REQUIRE(qm->makeQuery(&query) == proglines);
  }

  SECTION ("Test with: read.varName = \"v1\"") {
    auto querystr = std::string("read r; Select r with r.varName = \"v1\"");
    std::vector<std::string> proglines = {"2"};
    auto query = qe.makePqlQuery(querystr);
    REQUIRE(qm->makeQuery(&query) == proglines);
  }

  SECTION ("Test with: pn.varName = \"v1\"") {
    auto querystr = std::string("print pn; Select pn with pn.varName = \"v1\"");
    std::vector<std::string> proglines = {"18", "24", "30", "33",
                                          "36", "39", "7"};
    auto query = qe.makePqlQuery(querystr);
    REQUIRE(qm->makeQuery(&query) == proglines);
  }

  SECTION ("Test with: s.stmt# = n (all statements)") {
    auto querystr =
        std::string("stmt s; prog_line n; Select s with s.stmt# = n");
    std::vector<std::string> proglines = {
        "1", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19",
        "2", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29",
        "3", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39",
        "4", "40", "41", "42", "43", "5",  "6",  "7",  "8",  "9"};
    auto query = qe.makePqlQuery(querystr);
    REQUIRE(qm->makeQuery(&query) == proglines);
  }

  SECTION ("Test with: n = s.stmt# (all statements)") {
    auto querystr =
        std::string("stmt s; prog_line n; Select s with n = s.stmt#");
    std::vector<std::string> proglines = {
        "1", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19",
        "2", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29",
        "3", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39",
        "4", "40", "41", "42", "43", "5",  "6",  "7",  "8",  "9"};
    auto query = qe.makePqlQuery(querystr);
    REQUIRE(qm->makeQuery(&query) == proglines);
  }

  SECTION ("Test complex with: n = s.stmt#, Next(1, n) - return 2") {
    auto querystr = std::string(
        "stmt s; prog_line n; Select s with n = s.stmt# such that Next(1, n)");
    std::vector<std::string> proglines = {"2"};
    auto query = qe.makePqlQuery(querystr);
    REQUIRE(qm->makeQuery(&query) == proglines);
  }

  SECTION (
      "Test complex with: n = c.value - all constants that have same val as a "
      "line no.") {
    auto querystr =
        std::string("constant c; prog_line n; Select c with c.value = n");
    std::vector<std::string> proglines = {"1"};
    auto query = qe.makePqlQuery(querystr);
    REQUIRE(qm->makeQuery(&query) == proglines);
  }

  SECTION (
      "Test complex with: variable.varName = read.varName, Next*(r, w) - only "
      "variables that are read before a while loop") {
    auto querystr = std::string(
        "variable v; print pn; while w; Select pn such that Next*(pn, w) with "
        "v.varName = pn.varName");
    std::vector<std::string> proglines = {"7", "8"};
    auto query = qe.makePqlQuery(querystr);
    REQUIRE(qm->makeQuery(&query) == proglines);
  }

  delete pkb;
  delete qm;
}
