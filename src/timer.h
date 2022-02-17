
#ifndef ZZIDUO_TIMER_H
#define ZZIDUO_TIMER_H 1

#include <functional>
#include <chrono>

namespace zziduo
{

template<typename _Tp>
class timer
{
public:
	using callback_type = std::function<void()>;
	using precision_type	= _Tp;
	using timepoint_type	= std::chrono::time_point<std:: chrono::system_clock>;
private:
	callback_type		_M_callback;
	timepoint_type	_M_now;
	const precision_type	_M_wait;
	const bool _M_running;

public:
	timer(timer_callback __cb, timepoint_type __time, precision_type __wait)
	: _M_callback(__cb),
		_M_now(__time),
		_M_wait(__wait),
		_M_running(__wait.count() > 0)
	{
	}
  ~timer();

	timer(const timer&) = delete;
  void operator=(const timer&) = delete;

	void run() const
	{
		_M_callback();
	}

	timepoint_type inited_time() const { return _M_now; }
	void restart(timepoint_type __time)
	{
		if (_M_running)
		{
			_M_now += _M_wait;
		}
		else
		{
			
		}
	}



private:

}; // class timer


} // namespace zziduo

#endif // ZZIDUO_TIMER_H