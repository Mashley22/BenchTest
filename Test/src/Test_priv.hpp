#include <mutex>
#include <string>

#include <BenchTest/Test/Test.hpp>

namespace benchtest {

namespace test {

namespace priv {

enum class FailType {
  ASSERT,
  RETURN,
};

struct AssertFailInfo {
  std::string_view cond;
  std::size_t lineNum;
};

struct ReturnFailInfo {
  std::string testName;
  std::string_view suiteName;
  std::size_t retVal;
  std::size_t testNum;
};

struct FailInfo {
  FailInfo(const AssertFailInfo&);
  FailInfo(const ReturnFailInfo&);

  FailType type;
  union {
    AssertFailInfo assertInfo;
    ReturnFailInfo returnInfo;
  };
};

struct FailErr {};

class AssertFailErr : FailErr {
public:
  AssertFailErr(const AssertFailInfo& info);
};

class ReturnFailErr : FailErr {
public:
  ReturnFailErr(const ReturnFailInfo& info);
};

class CaseEnv : public Case {
public:
  std::size_t caseNum;
  utils::Stopwatch timer;

  CaseEnv() = delete;
  CaseEnv(const Case& caseInfo, std::size_t testNum) noexcept;
};

class Suite {
public:
  Suite() = delete;
  Suite(const SuiteCreate_t& suiteInfo);

  bool empty(void) const noexcept;

  std::size_t numFailed(void) const noexcept;

  std::size_t numSuccess(void) const noexcept;

  std::size_t numSkipped(void) const noexcept;

  void runCase(void);

private:
  void printTestCaseInfos_(const CaseEnv& env) const;

  void printSetup_(const CaseEnv& env) const;

  void printSetupFail_(const CaseEnv& env) const;

  void printReset_(const CaseEnv& env) const;

  void printResetFail_(const CaseEnv& env) const;

  void printRecover_(const CaseEnv& env) const;

  void printRecoverFail_(const CaseEnv& env) const;

  void printStart_(const CaseEnv& env) const;

  void printSuccess_(const CaseEnv& env) const;

  void printFail_(const CaseEnv& env) const;

  void failedSuite_(void);

  CaseEnv createEnv_(void);

  Case nextCase_(void);

  CaseEnv setup_(void);

  void reset_(const CaseEnv& env);

  void recover_(const CaseEnv& env);

///// PRIV VAR START /////
  std::string_view m_name;
  std::vector<Case> m_cases;

  func_t m_setupFunc;
  func_t m_resetFunc;
  func_t m_recoverFunc;

  struct {
    std::size_t success{0};
    std::size_t failed{0};
    std::size_t skipped{0};
  } m_stats;
};

class Registry {
public:
  /**@brief static... */
  Registry(const Registry&) = delete;
  /**@brief static... */
  Registry operator=(const Registry&) = delete;
  /**@brief static... */
  Registry(Registry&&) = delete;
  /**@brief static... */
  Registry operator=(Registry&&) = delete;
  /**@brief static... */
  Registry() = delete;

/**@brief everytime this is retrieved, it will also increment
  */
  static std::size_t counter(void) noexcept;

  static std::mutex& syncLock(void) noexcept;

  static void runCase(void) noexcept;
  
  static void newFail(const ReturnFailInfo& info);
  static void newFail(const AssertFailInfo& info);

private:
///// PRIVATE VAR START /////
  static std::size_t m_currentSuiteNum;

  static std::vector<benchtest::test::priv::Suite> m_suites;

  static std::vector<benchtest::test::priv::FailInfo> m_failInfos;

  static struct {
    std::size_t success{0};
    std::size_t failed{0};
    std::size_t skipped{0};
    std::size_t counter{0};
  } m_stats;

  static std::mutex m_syncLock;
///// PRIVATE VAR END /////

  static void updStats_(void) noexcept;

};

}

}

}
