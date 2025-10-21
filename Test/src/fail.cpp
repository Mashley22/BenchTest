/// This file handles all the exceptions type classes and the fail stuff related to them

#include <BenchTest/Test/Test.hpp>
#include "Test_priv.hpp"

namespace benchtest {

namespace test {

void detail::assertFail(void) {
  throw priv::fail::AssertErr();
}

namespace priv {

namespace fail {

Info::Info(const Assert& failInfo, const CaseEnv& env) 
 :  type(Type::ASSERT), 
    info{ .assert = failInfo },
    testName(env.name) {}

Info::Info(const Return& failInfo, const CaseEnv& env) 
 :  type(Type::ASSERT), 
    info{ .ret = failInfo },
    testName(env.name) {}

}

}

}

}
