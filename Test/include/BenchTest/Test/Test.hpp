#ifndef BENCHTEST_TEST_TEST_HPP
#define BENCHTEST_TEST_TEST_HPP

#include <string_view>

#include <BenchTest/utils/timer.hpp>

/**@brief the assert to use when testing
 */
#define BENCHTEST_ASSERT(expr)                                          \
    do {                                                                \
        if (!(expr)) {                                                  \
            std::cerr << "Assertion failed: " #expr                     \
                      << " at " << __FILE__ << ":" << __LINE__ << "\n"; \
            assertFail(#expr, __LINE__);                                \
        }                                                               \
    } while (0)


namespace benchtest {

namespace test {

namespace priv {

class Suite;

}

namespace detail {

/**@brief thows an expcetion that is only internally available
 */
void assertFail(std::string_view, std::size_t lineNum);

}

/**@brief struct for creation of testcases
 */
struct Case {
/**@brief the name of the test::Case
 */
  std::string_view name;

/**@brief the actual function to run see @ref func_t
 */
  func_t func;
};


/**@brief struct for creation of test::Suite 
 *        Groups all common tests, namely they should have a shared setup, reset and recover functions 
 *        Create suites only via the registry function
 * @note  if any of the functions fail for any reason the suite will be skipped
 */
struct SuiteCreate_t {
/**@brief ...
 */
  std::string_view name;

/**@brief a list of cases belonging to this suite
 */
  std::initializer_list<Case> cases;

/**@brief a function to run before each test case
 */
  func_t setupFunc;

/**@brief a function to run after a successful test
 */
  func_t resetFunc;

/**@brief a function to run after a failed test
 */
  func_t recoverFunc;
};

void runAll(void);

}

}

#endif /* BENCHTEST_TEST_TEST_HPP */
