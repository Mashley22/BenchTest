#include <assert.h>
#include <iostream>
#include <vector>

#include "Test_priv.hpp"

namespace benchtest {

namespace test {

namespace priv {

std::size_t Registry::m_currentSuiteNum = 0;

std::size_t Registry::m_globalSuiteCounter = 0;

std::vector<Suite> Registry::m_suites;

std::vector<Worker> Registry::m_workers;

MainWorker Registry::m_mainWorker;

std::mutex Registry::m_syncLock;

decltype(Registry::m_stats) Registry::m_stats = {0, 0, 0};

std::size_t Registry::globalSuiteCounter(void) noexcept {
  return m_globalSuiteCounter;
}

std::mutex& Registry::syncLock(void) noexcept {
  return m_syncLock;
}

Suite& Registry::currentSuite(void) noexcept {
  return m_suites[m_currentSuiteNum];
}

Suite& Registry::addSuite(std::sttring_view name, const SuiteCreate_t &suiteInfo) {
  return m_suites.emplace_back(name, suiteInfo);
}

void Registry::init(const std::size_t threadNum, const std::size_t globalSuiteCounter, std::string_view name) {
  assert(m_workers.size() == 0);
  m_workers.resize(threadNum - 1);
  m_globalSuiteCounter = globalSuiteCounter;
}

std::vector<std::string_view> Registry::suiteNames(void) {
  std::vector<std::string_view> retVal;

  for (const auto& suite : m_suites) {
    retVal.push_back(suite.name());
  }

  return retVal;
}

std::size_t Registry::suiteNum(void) noexcept {
  return m_suites.size();
}

void Registry::runAll(void) {
  while(numSuitesLeft_() != 0) {
    runSuite_();
  }
}

void Registry::updStats_(void) noexcept {
  assert(currentSuite().empty());
  m_stats.failed += currentSuite().numFailed();
  m_stats.skipped += currentSuite().numSkipped();
  m_stats.success += currentSuite().numSuccess();
}

bool Registry::allWorkersDone_(void) noexcept {
  if (m_mainWorker.active()) {
    return false;
  }
  for (const auto& worker : m_workers) {
    if (worker.active()) {
      return false;
    }
  }

  return true;
}

void Registry::nextSuite_(void) noexcept {
  m_currentSuiteNum++;
  m_globalSuiteCounter++;
}

void Registry::runSuite_(void) {
  for (auto& worker : m_workers) {
    worker.start();
  }
  m_mainWorker.start();

  while (!allWorkersDone_()) {

  }

  updStats_();
  nextSuite_();
}

std::size_t Registry::numSuitesLeft_(void) noexcept {
  return m_suites.size() - m_currentSuiteNum;
}

void Registry::printSuiteEnd_(void) {
  std::lock_guard<std::mutex> lock(m_syncLock);

  std::cout << "[ SUITE END ] " << currentSuite().name() << '\n';

}

}

}

}
