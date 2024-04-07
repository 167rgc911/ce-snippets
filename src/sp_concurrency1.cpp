/*
 * =====================================================================================
 *
 *       Filename:  sp_concurrency1.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  04/07/24 11:11:13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  rgc (),
 *   Organization:
 *
 * =====================================================================================
 */

/* :REMARK:04/07/24 06:54:39::
 *
 * copying from the presentation slides 2017-01-18-concurrency.pdf
 *  - fix the slideware (thus std:: was added)
 *  -
 * */

#include <algorithm>
#include <condition_variable>
#include <deque>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using lock_t = std::unique_lock<std::mutex>;
class notification_queue
{
  std::deque<std::function<void ()> > _q;
  bool _done{ false };
  std::mutex _mutex;
  std::condition_variable _ready;

public:
  void
  done ()
  {
    {
      std::unique_lock<std::mutex> lock{ _mutex };
      _done = true;
    }
    _ready.notify_all ();
  }

  // void pop(std::function<void()>& x) {
  //     lock_t lock{_mutex};
  //     while (_q.empty()) _ready.wait(lock);
  //     x = std::move(_q.front());
  //     _q.pop_front();
  // }

  bool
  pop (std::function<void ()> &x)
  {
    lock_t lock{ _mutex };
    while (_q.empty () && !_done)
      _ready.wait (lock);
    if (_q.empty ())
      return false;
    x = std::move (_q.front ());
    _q.pop_front ();
    return true;
  }

  template <typename F>
  void
  push (F &&f)
  {
    {
      lock_t lock{ _mutex };
      _q.emplace_back (std::forward<F> (f));
    }
    _ready.notify_one ();
  }
};

class task_system
{
  /* const unsigned _count{ std::thread::hardware_concurrency () }; */
  const unsigned _count{ 2 };
  std::vector<std::thread> _threads;
  notification_queue _q;

  void
  run (unsigned i)
  {
    while (true)
      {
        std::function<void ()> f;
        /* _q.pop (f); */
        /* :REMARK:04/07/24 08:19:26::
         * when _q.done == true; f is garbage!
         * check return value
         * */
        if (!_q.pop (f))
          break;
        f ();
      }
  }

public:
  task_system ()
  {
    for (unsigned n = 0; n != _count; ++n)
      {
        _threads.emplace_back ([&, n] { run (n); });
      }
  }

  ~task_system ()
  {
    /* :REMARK:04/07/24 08:15:59::
     * without this call join() below does an inf-loop */
    _q.done ();

    for (auto &e : _threads)
      e.join ();
  }

  template <typename F>
  void
  async_ (F &&f)
  {
    _q.push (std::forward<F> (f));
  }
};

void
f1 ()
{
  std::cout << "f1()" << std::endl;
  return;
}

void
f4 ()
{
  std::cout << "f4()" << std::endl;
  return;
}

int
main ()
{
  task_system t;

  t.async_ (f1);
  t.async_ (f1);
  t.async_ (f4);
  t.async_ (f1);

  return 0;
}
