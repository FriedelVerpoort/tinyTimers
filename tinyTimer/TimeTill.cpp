#include "stdafx.h"
#include "TimeTill.h"
using namespace tinyTimer;
TimeTill::TimeTill()
	:m_Time(std::chrono::steady_clock::now())
{
}

TimeTill::TimeTill(std::chrono::time_point<std::chrono::steady_clock> time)
	:m_Time(time)
{
}

TimeTill::TimeTill(std::chrono::nanoseconds _ns)
	:m_Time(std::chrono::steady_clock::now() + _ns)
{
}

TimeTill::TimeTill(std::chrono::microseconds _us)
	:m_Time(std::chrono::steady_clock::now() + _us)
{
}

TimeTill::TimeTill(std::chrono::milliseconds _ms)
	:m_Time(std::chrono::steady_clock::now() + _ms)
{
}

TimeTill::TimeTill(std::chrono::seconds _sec)
	:m_Time(std::chrono::steady_clock::now() + _sec)
{
}

TimeTill::TimeTill(std::chrono::minutes _min)
	:m_Time(std::chrono::steady_clock::now() + _min)
{
}

TimeTill::TimeTill(std::chrono::hours _hour)
	:m_Time(std::chrono::steady_clock::now() + _hour)
{
}

TimeTill::operator float() const
{
	return std::chrono::duration_cast<std::chrono::duration<float>>(m_Time - std::chrono::steady_clock::now()).count();
}
