/*
 * =====================================================================================
 *
 *       Filename:  sp_sort_subrange.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  04/07/24 09:04:54
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  rgc (),
 *   Organization:
 *
 * =====================================================================================
 */

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

template <typename I>
void
sort_subrange1 (I f, I l, I sf, I sl)
{
  std::nth_element (f, sf, l);
}

template <typename I>
void
sort_subrange (I f, I l, I sf, I sl)
{
  if (sf == sl)
    return;
  if (sf != f)
    {
      std::nth_element (f, sf, l);
      ++sf;
    }
  std::partial_sort (sf, sl, l);
}

int
main ()
{
  {
    int a[] = { 4, 13, 12, 7, 9, 5, 15, 14, 2, 11, 6, 16, 10, 1, 8, 3 };
    std::for_each (std::begin (a), std::end (a),
                   [] (auto i) { std::cout << i << " "; });
    std::cout << "\n";
    sort_subrange1 (std::begin (a), std::end (a), std::begin (a) + 5,
                    std::begin (a) + 8);
    std::for_each (std::begin (a), std::end (a),
                   [] (auto i) { std::cout << i << " "; });
    std::cout << "\n";
  }

  {
    int a[] = { 4, 13, 12, 7, 9, 5, 15, 14, 2, 11, 6, 16, 10, 1, 8, 3 };
    std::for_each (std::begin (a), std::end (a),
                   [] (auto i) { std::cout << i << " "; });
    std::cout << "\n";
    sort_subrange (std::begin (a), std::end (a), std::begin (a) + 5,
                   std::begin (a) + 8);
    std::for_each (std::begin (a), std::end (a),
                   [] (auto i) { std::cout << i << " "; });
    std::cout << "\n";
  }

  {
    int a[] = { 4, 13, 12, 7, 9, 5, 15, 14, 2, 11, 6, 16, 10, 1, 8, 3 };
    std::for_each (std::begin (a), std::end (a),
                   [] (auto i) { std::cout << i << " "; });
    std::cout << "\n";
    sort_subrange (std::begin (a), std::end (a), std::begin (a) + 5,
                   std::begin (a) + 8);
    std::partial_sort (std::begin (a) + 8, std::begin (a) + 12, std::end (a));
    std::for_each (std::begin (a), std::end (a),
                   [] (auto i) { std::cout << i << " "; });
    std::cout << "\n";
  }

  return 0;
}
