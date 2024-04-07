/*
 * =====================================================================================
 *
 *       Filename:  sp_concurrency_async.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  04/07/24 09:26:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  rgc (),
 *   Organization:
 *
 * =====================================================================================
 */

#include <dispatch/dispatch.h>

#include <functional>
#include <future>
#include <type_traits>

template <class Function, class... Args>
auto
async (Function &&f, Args &&...args)
{
  using result_type
      = std::result_of_t<std::decay_t<Function> (std::decay_t<Args>...)>;
  using packaged_type = std::packaged_task<result_type ()>;
  auto _p = new packaged_type (
      std::bind ([_f = std::forward<Function> (f)] (
                     Args &...args) { return _f (std::move (args)...); },
                 std::forward<Args> (args)...));
  auto result = _p->get_future ();
  dispatch_async_f (
      dispatch_get_global_queue (DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), _p,
      [] (void *p) {
        auto _p = static_cast<packaged_type *> (p);
        (*_p) ();
        delete _p;
      });
  return result;
}
