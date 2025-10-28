#include <BenchTest/Test/Test.hpp>

int emptyFunc(void) { return 0;}

#define EMPTY benchtest::test::SuiteCreate_t({emptyFunc, emptyFunc, emptyFunc})

BENCHTEST_TESTSUITE(basic, EMPTY);



BENCHTEST_TESTCASE(basic, ah) {
  BENCHTEST_ASSERT(0==0, "a");
  return 0;
}

