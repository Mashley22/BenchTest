
#include <BenchTest/Test/Test.hpp>

#include "Test_priv.hpp"

namespace benchtest {

namespace test {

namespace detail {

void assertFail(std::string_view cond, std::size_t lineNum) {
  throw priv::fail::AssertErr({cond, lineNum});
}

SuiteAutoRegister::SuiteAutoRegister(std::string_view name, const SuiteCreate_t& suiteInfo) : suite(priv::Registry::addSuite(name, suiteInfo)) {}

CaseAutoRegister::CaseAutoRegister(benchtest::test::priv::Suite& suite, const func_t func, std::string_view name) {
  suite.addCase({name, func});
}

}

}

}
