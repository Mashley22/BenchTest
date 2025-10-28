/// This file handles all the exceptions type classes and the fail stuff related to them

#include <assert.h>

#include <BenchTest/Test/Test.hpp>
#include "Test_priv.hpp"

namespace benchtest {

namespace test {

namespace priv {

namespace fail {

Info::Info(const Assert& failInfo, const CaseEnv& env) 
 :  m_type(Type::ASSERT), 
    m_info{ .assert = failInfo },
    m_testName(env.name()),
    m_globalTestNum(env.globalCaseNum()),
    m_suiteTestNum(env.suiteCaseNum()) {}

Info::Info(const Return& failInfo, const CaseEnv& env) 
 :  m_type(Type::RETURN), 
    m_info{ .ret = failInfo },
    m_testName(env.name()),
    m_globalTestNum(env.globalCaseNum()),
    m_suiteTestNum(env.suiteCaseNum()) {}

Type Info::type(void) const noexcept {
  return m_type;
}

std::string_view Info::testName(void) const noexcept {
  return m_testName;
}

std::size_t Info::suiteCaseNum(void) const noexcept {
  return m_suiteTestNum;
}

std::size_t Info::globalCaseNum(void) const noexcept {
  return m_globalTestNum;
}

const Info::Assert& Info::assertInfo(void) const noexcept {
  assert(m_type == Type::ASSERT);
  return m_info.assert;
}

const Info::Return& Info::returnInfo(void) const noexcept {
  assert(m_type == Type::RETURN);
  return m_info.ret;
}

}

}

}

}
