#include "thread_pool.h"
#include <assert.h>

using namespace std;
using namespace zziduo;

thread_pool::thread_pool(const std::string &__name)
  : _M_init(),
    _M_mutex(),
    _M_not_empty(),
    _M_not_full(),
    _M_name(__name),
    _M_capacity(0),
    _M_running(false)
{
}

thread_pool::~thread_pool()
{
  if (_M_running)
  {
    stop();
  }
}

void thread_pool::start(size_type __thread_num)
{
  _M_running = true;
  _M_threads.reserve(__thread_num);
  for (size_type i = 0; i < __thread_num; ++i)
  {
    _M_threads.emplace_back(new thread(&thread_pool::run, this));
  }
  if (__thread_num == 0 && _M_init)
  {
    _M_init();
  }
}

void thread_pool::stop()
{
  unique_lock<mutex_type> lk(_M_mutex);
  _M_running = false;
  _M_not_empty.notify_all();
  _M_not_full.notify_all();
}

thread_pool::size_type thread_pool::size() const
{
  unique_lock<mutex_type> lock(_M_mutex);
  return _M_queue.size();
}

thread_pool::callable_type thread_pool::take()
{
  unique_lock<mutex_type> lock(_M_mutex);

  while (_M_queue.empty() && _M_running)
  {
    _M_not_empty.wait(lock);
  }
  callable_type task;
  if (!_M_queue.empty())
  {
    task = _M_queue.front();
    _M_queue.pop_front();
    if (_M_capacity > 0)
    {
      _M_not_full.notify_one();
    }
  }

  return task;
}

void thread_pool::run()
{
  try
  {
    if (_M_init)
    {
      _M_init();
    }

    while (_M_running)
    {
      callable_type callback(take());
      if (callback) {
        callback();
      }
    }
  }
  catch(const exception &ex)
  {
    fprintf(stderr,
          "expcetion caught in thread_pool %s, at%s:%d\n",
          _M_name.c_str(), __FILE__, __LINE__);
    fprintf(stderr, "reason: %s\n", ex.what());
    abort();
  }
  catch(...)
  {
    fprintf(stderr,
          "unknown exception caught in thread_pool %s, at %s:%d\n",
          _M_name.c_str(), __FILE__, __LINE__);
    throw;
  }

}