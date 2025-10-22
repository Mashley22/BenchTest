#include "Test_priv.hpp"

#include <functional>

namespace benchtest {

namespace test {

namespace priv {

bool Worker::active(void) const noexcept {
  return m_active.load(std::memory_order_seq_cst);
}

void Worker::start(void) {
  m_thread = std::jthread(std::bind(&Worker::workLoop_, this));
}

void Worker::workLoop_(void) {
  m_active.store(true, std::memory_order_seq_cst);
  while (!Registry::currentSuite().empty()) {
    Registry::currentSuite().runCase();
  }
  m_active.store(false, std::memory_order_seq_cst);
}

bool MainWorker::active(void) const noexcept {
  return Worker::active();
}

void MainWorker::start(void) {
  Worker::workLoop_();
}

}

}

}
