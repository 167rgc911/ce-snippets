/*
 * =====================================================================================
 *
 *       Filename:  bm_valarrays.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  04/04/24 16:58:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  rgc (rgc), sessyargc.jp@gmail.com
 *   Organization:
 *
 * =====================================================================================
 */

#include <algorithm>
#include <iostream>
#include <valarray>
#include <vector>

#include <random>

std::vector<double>
random_v (int sz)
{
  std::random_device rd;
  std::mt19937 gen (rd ());
  std::uniform_real_distribution<> dis (1.0, 99.0);

  std::vector<double> sv{};

  for (auto i = 0; i < sz; ++i)
    {
      sv.push_back (dis (gen));
    }

  return sv;
}

#include <benchmark/benchmark.h>

void
t1 (const std::valarray<double> &vad)
{
  auto mean = vad.sum () / vad.size ();
  return;
}

void
t1_1 (const std::vector<double> &vad_)
{
  const auto vad = std::valarray<double> (vad_.data (), vad_.size ());
  auto mean = vad.sum () / vad.size ();

  return;
}

void
t2 (const std::vector<double> &vad)
{
  // [&vad]() {
  //     std::for_each(std::begin(vad), std::end(vad),
  //         [](const double v) {
  //             std::cout << v << ", ";
  //         });
  // }();

  auto mean = std::accumulate (vad.begin (), vad.end (), 0.0) / vad.size ();

  return;
}

static void
BM_valarray (benchmark::State &state)
{
  // Perform setup here
  const auto vad_ = random_v (256);
  const auto vad = std::valarray<double> (vad_.data (), vad_.size ());
  for (auto _ : state)
    {
      // This code gets timed
      t1 (vad);
    }
}

static void
BM_valarray1 (benchmark::State &state)
{
  // Perform setup here
  const auto vad = random_v (256);
  for (auto _ : state)
    {
      // This code gets timed
      t1_1 (vad);
    }
}

static void
BM_stdvector (benchmark::State &state)
{
  // Perform setup here
  const auto vad = random_v (256);
  for (auto _ : state)
    {
      // This code gets timed
      t2 (vad);
    }
}

// Register the function as a benchmark
BENCHMARK (BM_valarray);
BENCHMARK (BM_valarray1);
BENCHMARK (BM_stdvector);

// Run the benchmark
BENCHMARK_MAIN ();
