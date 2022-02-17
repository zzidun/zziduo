
#ifndef ZZIDUO_EVENTLOOP_H
#define ZZIDUO_EVENTLOOP_H 1

#include <functional>

namespace zziduo
{

class event_loop
{
public:
	using callback_type = std::function<void()>;
private:

public:
	event_loop();
  ~event_loop();

	event_loop(const event_loop&) = delete;
  void operator=(const event_loop&) = delete;

	void loop();
	void quit();
	
private:

}; // class event_loop


} // namespace zziduo

#endif // ZZIDUO_EVENTLOOP_H