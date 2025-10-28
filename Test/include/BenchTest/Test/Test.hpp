#ifndef BENCHTEST_TEST_TEST_HPP
#define BENCHTEST_TEST_TEST_HPP

#include <string_view>

#include <BenchTest/types.hpp>
#include <BenchTest/utils/timer.hpp>

/**@brief the assert to use when testing
 */
#define BENCHTEST_ASSERT(expr, msg)                                     \
    do {                                                                \
        if (!(expr)) {                                                  \
            std::cerr << "Assertion failed: " #expr << msg              \
                      << " at " << __FILE__ << ":" << __LINE__ << "\n"; \
            assertFail(#expr, __LINE__);                                \
        }                                                               \
    } while (0)


#define BENCHTEST_TESTCASE(suite, case) \
  static func_t test_##suite##_##case(void); \
  static benchtest::test::detail::CaseAutoRegister testCase_##suite##_##case##(suite, #case, case); \
  static func_t test_##suite##_##case(void)

#define BENCHTEST_SUITE(name, suiteInfo) \
  static benchtest::test::detail::SuiteAutoRegister suite_##name(#name, suiteInfo)

namespace benchtest {

namespace test {

/**@brief struct for creation of test::Suite 
 *        Groups all common tests, namely they should have a shared setup, reset and recover functions 
 *        Create suites only via the registry function
 * @note  if any of the functions fail for any reason the suite will be skipped
 */
struct SuiteCreate_t {

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

namespace priv {
  class Suite;
  class Case;
}

namespace detail {

/**@brief thows an expcetion that is only internally available
 */
void assertFail(std::string_view, std::size_t lineNum);

struct SuiteAutoRegister {
  SuiteAutoRegister() = delete;
  SuiteAutoRegister(std::string_view name, const SuiteCreate_t& suiteInfo);
  benchtest::test::priv::Suite& suite;
};

struct CaseAutoRegister {
  CaseAutoRegister() = delete;
  CaseAutoRegister(benchtest::test::priv::Suite& suite, const func_t func, std::string_view name);
};

}

}

}

#endif /* BENCHTEST_TEST_TEST_HPP */
