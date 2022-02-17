
#ifndef ZZIDUO_SINGLETON_H
#define ZZIDUO_SINGLETON_H 1

namespace zziduo
{


template<typename _Tp>
class singleton
{
public:
	using type = _Tp;
private:

public:
	singleton() = delete;
  ~singleton() = delete;

	singleton(const singleton&) = delete;
  void operator=(const singleton&) = delete;

	static type& instance()
	{
		static type __value;
		return __value;
	}

private:

}; // class singleton


} // namespace zziduo

#endif // ZZIDUO_SINGLETON_H