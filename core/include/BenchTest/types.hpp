#ifndef BENCHTEST_TYPES_HPP
#define BENCHTEST_TYPES_HPP

namespace benchtest {

/**@brief The main function type that underlies the whole library
 * @note  For testing 0 is success, 1 is not
 */
using func_t = int(*)();

/**@brief Empty @ref func_t that just returns successfully
 * @retval 0 for success
 */
int emptyFunc_t(void) noexcept;

}

#endif /* BENCHTEST_TYPES_HPP */
