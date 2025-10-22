
#include "Test_priv.hpp"

namespace benchtest {

namespace test {

namespace priv {

CaseEnv::CaseEnv(const Case& caseInfo, std::size_t localCaseNum) noexcept 
  : m_case(caseInfo), m_globalSuiteNum(Registry::globalSuiteCounter()), m_localCaseNum(localCaseNum) {}

int CaseEnv::run(void) {
  m_timer.start();
  int retVal = m_case::func();
  m_timer.stop();
  return retVal;
}

std::string_view CaseEnv::name(void) const noexcept {
  return m_case::name;
}

std::size_t CaseEnv::globalSuiteNum(void) const noexcept {
  return m_globalSuiteNum;
}

std::size_t CaseEnv::localCaseNum(void) const noexcept {
  return m_localCaseNum;
}

mSeconds CaseEnv::time(void) const noexcept {
  return m_timer.time();
}

}

}

}
