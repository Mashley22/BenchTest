#include <mutex>
#include <string>
#include <thread>

#include <BenchTest/Test/Test.hpp>

// tests whether the synclock was locked when expected
#define ASSERT_SYNC { std::unique_lock<std::mutex> lock{Registry::syncLock(), std::try_to_lock}; \
                  assert(!lock.owns_lock() && "BenchTest internal sync error"); } while(0)

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


class Info {
public:
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

  [[nodiscard]] Type type(void) const noexcept;

  [[nodiscard]] std::string_view testName(void) const noexcept;

  [[nodiscard]] std::size_t globalCaseNum(void) const noexcept;

  [[nodiscard]] std::size_t suiteCaseNum(void) const noexcept;

  [[nodiscard]] const Assert& assertInfo(void) const noexcept;

  [[nodiscard]] const Return& returnInfo(void) const noexcept;

private:
  Type m_type;
  std::string_view m_testName;

  std::size_t m_globalTestNum;
  std::size_t m_suiteTestNum;

  union {
    Assert assert;
    Return ret;
  } m_info;


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

  void printReset_(const CaseEnv& env) const;

  void printResetFail_(const CaseEnv& env) const;

  void printRecover_(const CaseEnv& env) const;

  void printRecoverFail_(const CaseEnv& env) const;

  void printStart_(const CaseEnv& env) const;

  void printSuccess_(const CaseEnv& env) const;

  void printFail_(const CaseEnv& env) const;

  void failedSuite_(void);

  CaseEnv createEnv_(void);

  Case& nextCase_(void) noexcept;

  CaseEnv setup_(void);

  void reset_(const CaseEnv& env);

  void recover_(const CaseEnv& env);

  void fail_(const fail::Info::Assert info, const CaseEnv& env);
  void fail_(const fail::Info::Return info, const CaseEnv& env);

  std::size_t casesLeft_(void) const noexcept;

///// PRIV VAR START /////
  std::string_view m_name;
  std::vector<Case> m_cases;

  func_t m_resetFunc;
  func_t m_recoverFunc;

  std::vector<benchtest::test::priv::fail::Info> m_failInfos;

  struct {
    std::size_t success{0};
    std::size_t failed{0};
    std::size_t skipped{0};
    std::size_t currentCaseNum{0};
  } m_stats;
};

class Worker {
public:

  Worker() = default;

  Worker(const Worker& other) noexcept;

  [[nodiscard]] bool active(void) const noexcept;

  void start(void);

protected:
  void workLoop_(void);

private:
  std::jthread m_thread;
  std::atomic_bool m_active{false};
};

class MainWorker : private Worker {
public:
  [[nodiscard]] bool active(void) const noexcept;
    
  void start(void);
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
  [[nodiscard]] static std::size_t counter(void) noexcept;

  [[nodiscard]] static std::mutex& syncLock(void) noexcept;

  [[nodiscard]] static Suite& currentSuite(void) noexcept;
  
private:
///// PRIVATE VAR START /////
  static std::size_t m_currentSuiteNum;

  static std::vector<benchtest::test::priv::Suite> m_suites;

  static std::vector<Worker> m_workers;
  
  static MainWorker m_mainWorker;

  static struct {
    std::size_t success;
    std::size_t failed;
    std::size_t skipped;
    std::size_t counter;
  } m_stats;

  static std::mutex m_syncLock;
///// PRIVATE VAR END /////

  static void updStats_(void) noexcept;

  static bool allWorkersDone_(void) noexcept;

};

}

}

}
