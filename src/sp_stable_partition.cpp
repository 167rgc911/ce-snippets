/*
 * =====================================================================================
 *
 *       Filename:  sp_stable_partition.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  04/07/24 07:28:15
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

template <typename I, typename P>
auto
sp_stable_partition_position (I f, I l, P p) -> I
{
  auto n = l - f;
  if (n == 0)
    return f;
  if (n == 1)
    return f + p (f);

  auto m = f + (n / 2);

  return std::rotate (sp_stable_partition_position (f, m, p), m,
                      sp_stable_partition_position (m, l, p));
}

template <typename I, typename P>
auto
sp_stable_partition (I f, I l, P p) -> I
{
  auto n = l - f;
  if (n == 0)
    return f;
  if (n == 1)
    return f + p (*f);

  auto m = f + (n / 2);

  return std::rotate (sp_stable_partition (f, m, p), m,
                      sp_stable_partition (m, l, p));
}

int
main ()
{
  {
    int a[] = { 1, 2, 3, 4, 5, 5, 4, 3, 2, 1 };
    int b[] = { 0, 1, 0, 1, 0, 0, 1, 0, 1, 0 };

    const auto p = sp_stable_partition_position (
        std::begin (a), std::end (a),
        [&] (auto i) { return *(std::begin (b) + (i - std::begin (a))); });

    std::cout << "\n";
    const auto sz = sizeof (a) / sizeof (*a);
    for (auto pp = 0; pp < sz; ++pp)
      {
        std::cout << p[pp] << " ";
      };
    std::cout << "\n";

    for (auto f = std::begin (a), l = p; f != l; ++f)
      {
        std::cout << *f << " ";
      };
    std::cout << "^ ";
    for (auto f = p, l = std::end (a); f != l; ++f)
      {
        std::cout << *f << " ";
      };

    std::cout << "\n";

    for (auto pp = 0; pp < sz; ++pp)
        {std::cout << p[pp] << " "; };
    std::cout << "\n";
  }

  {
    std::vector<int> A = { 1, 2, 3, 4, 5, 5, 4, 3, 2, 1 };
    std::vector<int> B = { 0, 1, 0, 1, 0, 0, 1, 0, 1, 0 };

    const auto P = sp_stable_partition_position (
        std::begin (A), std::end (A),
        [&] (auto i) { return *(std::begin (B) + (i - std::begin (A))); });

    for (auto f = std::begin (A), l = P; f != l; ++f)
      {
        std::cout << *f << " ";
      };
    std::cout << "^ ";
    for (auto f = P, l = std::end (A); f != l; ++f)
      {
        std::cout << *f << " ";
      };
    std::cout << "\n";
  }

  return 0;
}
