#ifndef BENCHTEST_CORE_HPP
#define BENCHTEST_CORE_HPP

#include <cassert>
#include <iostream>

namespace benchtest {

namespace utils {

// contentsSize as template param just to be able to check that it works
/**@brief console output of the form [ contents ] 
 * @tparam tagWidth width of the whole tag, excludes the ]
 * @tparam contentSize len of the contents array
 * @param contents to be actually put in the tag
 * */
template<int tagWidth, int contentsSize>
void printTag(std::string_view contents) {
  static_assert(contentsSize < tagWidth - 1);
  int leftPadding = (tagWidth - contentsSize)/2;
  int rightPadding = (tagWidth - contentsSize + 1)/2; // in the case of of tagWidth - tag.size()
  std::cout << "[" << std::string(leftPadding, ' ') << contents << std::string(rightPadding, ' ' ) << "] ";
}

}

}

#endif /* BENCHTEST_CORE_HPP */
