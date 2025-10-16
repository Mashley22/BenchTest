#ifndef BENCHTEST_COMMON_CASE_IMPL_HPP
#define BENCHTEST_COMMON_CASE_IMPL_HPP

#include <chrono>

namespace benchtest {

/**@brief basic timekeeping type */
using mSeconds = std::chrono::milliseconds;

namespace utils {

/**@brief  Basic stopwatch functionality,
 *         Everything is in milliseconds (std::chrono::duration<double, std::chrono::milliseconds>)
 */
class Stopwatch {
public:

  /**@brief The timer keeps ticking, it carries on from the same time from when it was last stopped */
  void start(void) noexcept;

  /**@brief Returns the time delta from the current time to the internal clock */
  mSeconds time(void) const noexcept;
  
  /**@brief Resets the internal timer to the default
   * @note call @ref start() before using the timer again */
  void reset(void) noexcept;
    
  /**@brief Resets and then starts the timer, returns the time duration before resetting */
  mSeconds restart(void) noexcept;

private:
  std::chrono::time_point<std::chrono::steady_clock> m_timer = {};
};

}

}

#endif /* BENCHTEST_COMMON_CASE_IMPL_HPP */
