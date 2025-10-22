#include <assert.h>


#include "Test_priv.hpp"

namespace benchtest {

namespace test {

namespace priv {

std::size_t Registry::m_currentSuiteNum = 0;

std::vector<Suite> Registry::m_suites;

std::vector<Worker> Registry::m_workers;

MainWorker Registry::m_mainWorker;

std::mutex Registry::m_syncLock;

decltype(Registry::m_stats) Registry::m_stats = {0, 0, 0, 0};

std::size_t Registry::counter(void) noexcept {
  ASSERT_SYNC;
  return m_stats.counter++;
}

std::mutex& Registry::syncLock(void) noexcept {
  return m_syncLock;
}

Suite& Registry::currentSuite(void) noexcept {
  return m_suites[m_currentSuiteNum];
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

}

}

}
