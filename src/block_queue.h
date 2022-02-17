
#ifndef ZZIDUO_BLOCKQUEUE_H
#define ZZIDUO_BLOCKQUEUE_H 1


#include <deque>
#include <mutex>
#include <condition_variable>
#include <memory>

namespace zziduo
{

template<typename _Tp>
class block_queue
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
	queue_type			_M_queue;

public:
	block_queue()
	:	_M_mutex(),
		_M_not_empty(),
		_M_queue()
	{
	}

	block_queue(const block_queue&) = delete;
  void operator=(const block_queue&) = delete;

	void append(const type& __x)
	{
		std::unique_lock<mutex_type> lk(_M_mutex);

		_M_queue.push_back(__x);
		_M_not_empty.notify_one();
	}

	void append(type&& __x)
	{
		std::unique_lock<mutex_type> lk(_M_mutex);

		_M_queue.push_back(std::move(__x));
		_M_not_empty.notify_one();
	}

	type take()
	{
		std::unique_lock<mutex_type> lk(_M_mutex);

		while (_M_queue.empty())
		{
			_M_not_empty.wait(lk);
		}

		type ret(std::move(_M_queue.front()));
		_M_queue.pop_front();
		return ret;
	}

	queue_type drain()
	{
		queue_type queue;
		{
			std::unique_lock lk(_M_mutex);
			queue = std::move(_M_queue);
		}
		return queue;
	}

	size_type size() const
	{
		std::unique_lock lk(_M_mutex);
		return _M_queue.size();
	}
private:

}; // class block_queue

} // namespace zziduo

#endif // ZZIDUO_BLOCKQUEUE_H