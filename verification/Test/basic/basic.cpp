#include <BenchTest/Test/Test.hpp>

int emptyFunc(void) { return 0;}

#define EMPTY benchtest::test::SuiteCreate_t({emptyFunc, emptyFunc, emptyFunc})

BENCHTEST_TESTSUITE(basic, EMPTY);

BENCHTEST_TESTCASE(basic, success) {
  BENCHTEST_ASSERT(0==0 && "If this fails its broken");
  return 0;
}

BENCHTEST_TESTCASE(basic, assertFail) {
  BENCHTEST_ASSERT(0==1 && "This is expected to fail");
  return 0;
}

BENCHTEST_TESTCASE(basic, returnFail) {
  return 1;
}
