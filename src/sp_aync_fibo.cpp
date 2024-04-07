/*
 * =====================================================================================
 *
 *       Filename:  sp_aync_fibo.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  04/07/24 09:33:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  rgc (),
 *   Organization:
 *
 * =====================================================================================
 */

#include <boost/multiprecision/cpp_int.hpp>

#include <array>
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <thread>

#include "sp_concurrency_async.cpp"

namespace mpre = boost::multiprecision;

void
rest ()
{
  std::this_thread::sleep_for (std::chrono::milliseconds (1));
}

template <typename T, typename N, typename O>
T
power (T x, N n, O op)
{
  if (n == 0)
    return identity_element (op);
  while ((n & 1) == 0)
    {
      n >>= 1;
      x = op (x, x);
    }
  T result = x;
  n >>= 1;
  while (n != 0)
    {
      x = op (x, x);
      if ((n & 1) != 0)
        result = op (result, x);
      n >>= 1;
    }
  return result;
}

template <typename N> struct multiply_2x2
{
  std::array<N, 4>
  operator() (const std::array<N, 4> &x, const std::array<N, 4> &y)
  {
    return { x[0] * y[0] + x[1] * y[2], x[0] * y[1] + x[1] * y[3],
             x[2] * y[0] + x[3] * y[2], x[2] * y[1] + x[3] * y[3] };
  }
};

template <typename N>
std::array<N, 4>
identity_element (const multiply_2x2<N> &)
{
  return { N (1), N (0), N (0), N (1) };
}

template <typename R, typename N>
R
fibonacci (N n)
{
  if (n == 0)
    return R (0);
  return power (std::array<R, 4>{ 1, 1, 1, 0 }, N (n - 1),
                multiply_2x2<R> ())[0];
}

int
main (void)
{
  /* { */
  /*   mpre::cpp_int x = fibonacci<mpre::cpp_int> (1000000); */
  /*   std::cout << "so what should i be doing here?" << std::endl; */
  /*   std::cout << x << std::endl; */
  /* } */

  {
    std::future<mpre::cpp_int> x
        = async ([] { return fibonacci<mpre::cpp_int> (1000000); });
    std::cout << "so what should i be doing here?" << std::endl;
    std::cout << x.get () << std::endl;
  }

  /* { */
  /*   std::future<mpre::cpp_int> x = async ([] { */
  /*     throw std::runtime_error ("failure"); */
  /*     return fibonacci<mpre::cpp_int> (1000000); */
  /*   }); */
  /*   // Do Something */
  /*   try */
  /*     { */
  /*       std::cout << x.get () << std::endl; */
  /*     } */
  /*   catch (const std::runtime_error &error) */
  /*     { */
  /*       std::cout << error.what () << std::endl; */
  /*     } */
  /* } */
  return 0;
}
