#include <iostream>
#include <assert.h>

#include "Test_priv.hpp"

// tests whether the synclock was locked when expected
#define ASSERT_SYNC { std::unique_lock<std::mutex> lock{Registry::syncLock(), std::try_to_lock}; \
                  assert(!lock.owns_lock() && "BenchTest internal sync error"); } while(0)

namespace benchtest {

namespace test {

namespace priv {

namespace {

static void m_printTime(mSeconds time) {
  std::cout << " ... " << std::chrono::duration_cast<std::chrono::seconds>(time);
}

}

Suite::Suite(std::string_view name, const SuiteCreate_t& suiteInfo)
  : m_name(name), 
    m_resetFunc(suiteInfo.resetFunc),
    m_recoverFunc(suiteInfo.recoverFunc) {}

void Suite::printTestCaseInfos_(const CaseEnv& env) const {
  ASSERT_SYNC;
  std::cout << '#' << env.globalSuiteNum() << ". " << env.localCaseNum() << "  " << m_name << " | " << env.name();
}

void Suite::printReset_(const CaseEnv& env) const {
  ASSERT_SYNC;
  std::cout << "[ RESET ]";
  printTestCaseInfos_(env);
  std::cout << '\n';
}

void Suite::printResetFail_(const CaseEnv& env) const {
  ASSERT_SYNC;
  std::cout << "[ RESET FAIL ]";
  printTestCaseInfos_(env);
  std::cout << '\n';
}

void Suite::printRecover_(const CaseEnv& env) const {
  ASSERT_SYNC;
  std::cout << "[ RECOVER ]";
  printTestCaseInfos_(env);
  std::cout << '\n';
}

void Suite::printRecoverFail_(const CaseEnv& env) const {
  ASSERT_SYNC;
  std::cout << "[ RECOVER FAIL ]";
  printTestCaseInfos_(env);
  std::cout << '\n';
}

void Suite::printStart_(const CaseEnv& env) const {
  ASSERT_SYNC;
  std::cout << "[ START ]";
  printTestCaseInfos_(env);
  std::cout << '\n';
}

void Suite::printSuccess_(const CaseEnv& env) const {
  ASSERT_SYNC;
  std::cout << "[ SUCCESS ]";
  printTestCaseInfos_(env);
  m_printTime(env.time());
  std::cout << '\n';
}

void Suite::printFail_(const CaseEnv& env) const {
  ASSERT_SYNC;
  std::cout << "[ FAIL ]";
  printTestCaseInfos_(env);
  m_printTime(env.time());
  std::cout << '\n';
}

Case& Suite::nextCase_(void) noexcept {
  ASSERT_SYNC;
  return m_cases[m_stats.currentCaseNum];
}

CaseEnv Suite::createEnv_(void) {
  ASSERT_SYNC;
  return CaseEnv(nextCase_(), m_stats.currentCaseNum++);
}

std::size_t Suite::casesLeft_(void) const noexcept {
  ASSERT_SYNC;
  return m_cases.size() - m_stats.currentCaseNum;
}

void Suite::failedSuite_(void) {
  ASSERT_SYNC;
  m_stats.skipped++;
  m_stats.skipped += casesLeft_();
  m_stats.currentCaseNum = m_cases.size();
}

CaseEnv Suite::setup_(void) {
  std::unique_lock<std::mutex> lock(Registry::syncLock());
  CaseEnv env = createEnv_();
  return env;
}

void Suite::reset_(const CaseEnv& env) {
  {
  std::lock_guard<std::mutex> lock(Registry::syncLock());
  printReset_(env);
  }
  try {
    int res = m_resetFunc();
    if (res != 0) {
      throw;
    }
  }
  catch(...) {
    std::lock_guard<std::mutex> lock(Registry::syncLock());
    printResetFail_(env);
    failedSuite_();
  }
}

void Suite::recover_(const CaseEnv& env) {
  // The lock guard here prevents any other test threads from doing too much
  std::lock_guard<std::mutex> lock(Registry::syncLock());
  printRecover_(env);
  try {
    int res = m_recoverFunc();
    if (res != 0) {
      throw;
    }
  }
  catch(...) {
    printRecoverFail_(env);
    failedSuite_();
  }
}

std::size_t Suite::numFailed(void) const noexcept {
  return m_stats.failed;
}

std::size_t Suite::numSuccess(void) const noexcept {
  return m_stats.success;
}

std::size_t Suite::numSkipped(void) const noexcept {
  return m_stats.skipped;
}

bool Suite::empty(void) const noexcept {
  std::lock_guard<std::mutex> lock(Registry::syncLock());
  return casesLeft_();
}

const std::span<const fail::Info> Suite::failInfos(void) const noexcept {
  return m_failInfos;
}

void Suite::runCase(void) {
  CaseEnv curCase = setup_(); 
  try {
    int res = curCase.run();
  }
  catch (fail::AssertErr err) {
    m_stats.failed++;
    recover_(curCase);
    return;
  }

  {
  std::lock_guard<std::mutex> lock(Registry::syncLock());
  m_stats.success++;
  printSuccess_(curCase);
  }

  reset_(curCase);
}

std::string_view Suite::name(void) const noexcept {
  return m_name;
}

void Suite::addCase(const Case& caseInfo) {
  m_cases.push_back(caseInfo);
}

}

}

}
