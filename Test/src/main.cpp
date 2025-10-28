#include "Test_priv.hpp"

namespace priv = benchtest::test::priv;

int main(int argc, char ** argv) {
  priv::Registry::init(4, 0);
  priv::Registry::runAll();
}
