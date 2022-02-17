
#ifndef ZZIDUO_BOUNDQUEUE_H
#define ZZIDUO_BOUNDQUEUE_H 1


#include <deque>
#include <mutex>
#include <condition_variable>
#include <memory>

namespace zziduo
{

template<typename _Tp>
class bound_queue
{
public:
	using type = _Tp;
	using size_type	=	std::size_t;

	using queue_type			= std::deque<type>;
	using mutex_type 			= std::mutex;
	using condition_type	= std::condition_variable;

private:
	mutex_type 			_M_mutex;
	condition_type	_M_not_empty;
	condition_type	_M_not_full;
	queue_type			_M_queue;
	size_type				_M_size;
	size_type				_M_capacity;

public:
	bound_queue(size_type __cap)
	:	_M_mutex(),
		_M_not_empty(),
		_M_queue(),
		_M_capacity(__cap)
	{
	}

	bound_queue(const bound_queue&) = delete;
  void operator=(const bound_queue&) = delete;

	void append(const type& __x)
	{
		std::unique_lock<mutex_type> lk(_M_mutex);

		while (_M_size >= _M_capacity)
		{
			_M_not_full.wait(lk);
		}

		_M_queue.push_back(__x);
		_M_size++;
		_M_not_empty.notify_one();
	}

	void append(type&& __x)
	{
		std::unique_lock<mutex_type> lk(_M_mutex);


		while (_M_size >= _M_capacity)
		{
			_M_not_full.wait(lk);
		}

		_M_queue.push_back(std::move(__x));
		_M_size++;
		_M_not_empty.notify_one();
	}

	type take()
	{
		std::unique_lock<mutex_type> lk(_M_mutex);

		while (_M_size == 0)
		{
			_M_not_empty.wait(lk);
		}

		type ret(std::move(_M_queue.front()));
		_M_queue.pop_front();
		_M_size--;
		_M_not_full.notify_one();
		return ret;
	}

	bool empty() const
	{
		std::unique_lock<mutex_type> lk(_M_mutex);
		return _M_size == 0;
	}

	bool full() const
	{
		std::unique_lock<mutex_type> lk(_M_mutex);
		return _M_size == _M_capacity;
	}

	size_type size() const
	{
		std::unique_lock<mutex_type> lk(_M_mutex);
		return _M_size;
	}

	size_type capacity() const
	{
		std::unique_lock<mutex_type> lk(_M_mutex);
		return _M_capacity;
	}

private:

}; // class bound_queue

} // namespace zziduo

#endif // ZZIDUO_BOUNDQUEUE_H