#include <assert.h>


#include "Test_priv.hpp"

namespace benchtest {

namespace test {

namespace priv {

std::size_t Registry::globalSuiteCounter(void) noexcept {
  return m_globalSuiteCounter;
}

std::mutex& Registry::syncLock(void) noexcept {
  return m_syncLock;
}

void Registry::updStats_(void) noexcept {

}

}

}

}
