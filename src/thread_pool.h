
#ifndef ZZIDUO_THREADPOOL_H
#define ZZIDUO_THREADPOOL_H 1

#include <mutex>
#include <condition_variable>
#include <thread>

#include <functional>

#include <deque>
#include <vector>

namespace zziduo
{

class thread_pool
{
public:
  typedef std::function<void ()>  callable_type; // todo
  typedef std::mutex              mutex_type;
  typedef std::condition_variable condition_type;

  typedef std::unique_ptr<std::thread>    unique_thread_type;
  typedef std::vector<unique_thread_type> vector_thread_type;
  typedef std::deque<callable_type>       deque_callable_type;

  typedef std::size_t size_type;
  typedef std::string name_type;

private:
  mutable mutex_type  _M_mutex;
  condition_type      _M_not_empty;
  condition_type      _M_not_full;

  callable_type       _M_init;
  vector_thread_type  _M_threads;
  deque_callable_type _M_queue;

  name_type _M_name;
  size_type _M_capacity;

  bool _M_running;

public:
  explicit thread_pool(const std::string &__name);
  ~thread_pool();

  thread_pool(const thread_pool&) = delete;
  thread_pool& operator=(const thread_pool&&) = delete;

	void set_init(const callable_type& __init) { _M_init = __init; }


	const name_type& name() const { return _M_name; }

  void reserve(size_type __capacity) { _M_capacity =  __capacity; }
	size_type size() const;

	void start(size_type __thread_num);
	void stop();

private:
	void run();
	callable_type take();
}; // class thread_pool


} // namespace zziduo

#endif // ZZIDUO_THREADPOOL_H