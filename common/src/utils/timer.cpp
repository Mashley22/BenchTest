#include <BenchTest/utils/timer.hpp>

#include <assert.h>

namespace benchtest {

namespace utils {

void Stopwatch::start(void) noexcept {
  m_timer = std::chrono::steady_clock::now();
}

void Stopwatch::reset(void) noexcept {
  m_timer = {};
}

mSeconds Stopwatch::time(void) const noexcept {
  std::chrono::time_point<std::chrono::steady_clock> check_time = {};
  assert(m_timer != check_time && "Please start the stopwatch before trying to get the time");
  return std::chrono::duration_cast<mSeconds>(std::chrono::steady_clock::now() - m_timer);
}

mSeconds Stopwatch::restart(void) noexcept {
  auto current_time = std::chrono::steady_clock::now();
  auto retVal = std::chrono::duration_cast<mSeconds>(current_time - m_timer);
  m_timer = current_time;
  return retVal;
}


}

}
