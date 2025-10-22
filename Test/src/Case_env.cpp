
#include "Test_priv.hpp"

namespace benchtest {

namespace test {

namespace priv {

CaseEnv::CaseEnv(const Case& caseInfo, std::size_t suiteNum) noexcept 
  : m_case(caseInfo), m_globalCaseNum(Registry::counter()), m_suiteCaseNum(suiteNum) {}

int CaseEnv::run(void) {
  m_timer.start();
  int retVal = m_case::func();
  m_timer.stop();
  return retVal;
}

std::string_view CaseEnv::name(void) const noexcept {
  return m_case::name;
}

std::size_t CaseEnv::globalCaseNum(void) const noexcept {
  return m_globalCaseNum;
}

std::size_t CaseEnv::suiteCaseNum(void) const noexcept {
  return m_suiteCaseNum;
}

mSeconds CaseEnv::time(void) const noexcept {
  return m_timer.time();
}

}

}

}
