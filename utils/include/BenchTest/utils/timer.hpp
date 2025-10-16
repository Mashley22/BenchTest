#ifndef BENCHTEST_COMMON_CASE_IMPL_HPP
#define BENCHTEST_COMMON_CASE_IMPL_HPP

#include <chrono>

namespace benchtest {

/**@brief The underlying function type for benchmarks and test cases
 *        For tests, 0 indicates success, anything is fail
 */
using func_t = int(*)();

namespace common {

class Timer {
 
private:
  std::chrono::time_point<std::chrono::steady_clock> m_start;
};

}

}

#endif /* BENCHTEST_COMMON_CASE_IMPL_HPP */
