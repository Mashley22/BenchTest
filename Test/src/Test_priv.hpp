#include <mutex>
#include <string>

#include <BenchTest/Test/Test.hpp>

namespace benchtest {

namespace test {

namespace priv {

class CaseEnv : private Case {
public:

  CaseEnv() = delete;
  CaseEnv(const Case& caseInfo, std::size_t suiteNum) noexcept;

  [[nodiscard]]int run(void);
  
  [[nodiscard]] std::string_view name(void) const noexcept;

  [[nodiscard]] std::size_t globalCaseNum(void) const noexcept;

  [[nodiscard]] std::size_t suiteCaseNum(void) const noexcept;

  [[nodiscard]] mSeconds time(void) const noexcept;  

private:
  using m_case = Case;
  std::size_t m_globalCaseNum;
  std::size_t m_suiteCaseNum;
  utils::Stopwatch m_timer;

};

namespace fail {

enum class Type {
  ASSERT,
  RETURN,
};


struct Info {
  struct Return {
    std::size_t retVal;
    std::size_t testNum;
  };

  struct Assert {
  std::string_view cond;
  std::size_t lineNum;
  };

  Info() = delete;
  
  // Dont need the suite since these infos are store per suite
  Info(const Assert&, const CaseEnv&);
  Info(const Return&, const CaseEnv&);

  Type type;
  std::string_view testName;

  union {
    Assert assert;
    Return ret;
  } info;


};

struct AssertErr {
  Info::Assert info;
};

}

class Suite {
public:
  Suite() = delete;
  Suite(const SuiteCreate_t& suiteInfo);

  bool empty(void) const noexcept;

  std::size_t numFailed(void) const noexcept;

  std::size_t numSuccess(void) const noexcept;

  std::size_t numSkipped(void) const noexcept;

  void runCase(void);

  const std::span<const fail::Info> failInfos(void) const noexcept;

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

  void fail_(const fail::Info::Assert info, const CaseEnv& env);
  void fail_(const fail::Info::Return info, const CaseEnv& env);

///// PRIV VAR START /////
  std::string_view m_name;
  std::vector<Case> m_cases;

  func_t m_setupFunc;
  func_t m_resetFunc;
  func_t m_recoverFunc;

  std::vector<benchtest::test::priv::fail::Info> m_failInfos;

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
  
private:
///// PRIVATE VAR START /////
  static std::size_t m_currentSuiteNum;

  static std::vector<benchtest::test::priv::Suite> m_suites;

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
