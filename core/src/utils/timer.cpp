#include <BenchTest/utils/timer.hpp>

#include <assert.h>

namespace benchtest {

namespace utils {

void Stopwatch::start(void) noexcept {
  m_start = std::chrono::steady_clock::now();
}

void Stopwatch::stop(void) noexcept {
  m_end = std::chrono::steady_clock::now();
}

void Stopwatch::reset(void) noexcept {
  m_start = {};
  m_end = {};
}

mSeconds Stopwatch::time(void) const noexcept {
  std::chrono::time_point<std::chrono::steady_clock> check_time = {};
  assert(m_start != check_time && m_end != check_time && "Please start the stopwatch before trying to get the time");
  return std::chrono::duration_cast<mSeconds>(m_end - m_start);
}

mSeconds Stopwatch::restart(void) noexcept {
  m_end = {};
  auto current_time = std::chrono::steady_clock::now();
  auto retVal = std::chrono::duration_cast<mSeconds>(current_time - m_start);
  m_start = current_time;
  return retVal;
}


}

}
