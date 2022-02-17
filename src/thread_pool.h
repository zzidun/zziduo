
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
  using callable_type = std::function<void ()>; // todo

  using mutex_type      = std::mutex;
  using condition_type  = std::condition_variable;

  using unique_thread_type  = std::unique_ptr<std::thread>;
  using vector_thread_type  = std::vector<unique_thread_type>;
  using deque_callable_type = std::deque<callable_type>;

  using size_type = std::size_t;
  using name_type = std::string;

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
  void operator=(const thread_pool&) = delete;

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