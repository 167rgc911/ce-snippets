/*
 * =====================================================================================
 *
 *       Filename:  da_value_semantics.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  04/09/24 10:20:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  rgc (),
 *   Organization:
 *
 * =====================================================================================
 */

#include <iostream>

template <typename T>
void
offset (T &x, T const &delta)
{
  x += delta;
}

template <typename T>
void
offset2 (T &x, T const &delta)
{
  offset (x, delta);
  offset (x, delta);
}

int
main (void)
{
  auto x = 3;
  offset2 (x, x);
  std::cout << x << std::endl;
  return 0;
}
