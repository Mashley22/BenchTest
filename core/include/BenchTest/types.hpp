#ifndef BENCHTEST_TYPES_HPP
#define BENCHTEST_TYPES_HPP

namespace benchtest {

/**@brief The main function type that underlies the whole library
 * @note  For testing 0 is success, 1 is not
 */
using func_t = int(*)();

}

#endif /* BENCHTEST_TYPES_HPP */
