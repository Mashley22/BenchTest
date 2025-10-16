#include <BenchTest/detail/case_impl.hpp>

namespace benchtest {

namespace detail {

Case_impl::Case_impl(func_t func, std::string_view name)
  : m_func(func), m_name(name) {}

}

}
