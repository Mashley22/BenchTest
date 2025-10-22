#include <assert.h>


#include "Test_priv.hpp"

namespace benchtest {

namespace test {

namespace priv {

std::size_t Registry::counter(void) noexcept {
  ASSERT_SYNC;
  return m_stats.counter++;
}

std::mutex& Registry::syncLock(void) noexcept {
  return m_syncLock;
}

void Registry::updStats_(void) noexcept {

}

}

}

}
