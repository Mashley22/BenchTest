#ifndef BENCHTEST_DETAIL_CASE_IMPL_HPP
#define BENCHTEST_DETAIL_CASE_IMPL_HPP

#include <string_view>

#include <BenchTest/types.hpp>

namespace benchtest {

namespace detail {

/**@brief The Case encapsulates the core of the methadology
 *        This contains just some of the components of the thing that are present in all cases
 */
class Case_impl {
public:

/**@brief Constructor for the guy 
 * @param func the actual function to run
 * @param name the name of this case
 */
  Case_impl(func_t func, std::string_view name);

/**@brief Don't need this, it should all be compile time anyways
 */
  Case_impl() = delete;

/**@note for some of the bench marking runs with a bit more stuff */
protected:
  func_t m_func;
  std::string_view m_name;
  std::size_t m_num;
};

}

}

#endif /* BENCHTEST_DETAIL_CASE_IMPL_HPP */
