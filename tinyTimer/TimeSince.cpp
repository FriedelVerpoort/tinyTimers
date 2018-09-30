#include "stdafx.h"
#include "TimeSince.h"
using namespace tinyTimer;
TimeSince::TimeSince()
	:m_Time(std::chrono::steady_clock::now())
{
}

TimeSince::TimeSince(std::chrono::time_point<std::chrono::steady_clock> time)
	: m_Time(time)
{
}

TimeSince::TimeSince(std::chrono::nanoseconds _ns)
	: m_Time{ std::chrono::steady_clock::now() - _ns }
{
}

TimeSince::TimeSince(std::chrono::microseconds _us)
	: m_Time{ std::chrono::steady_clock::now() - _us }
{
}

TimeSince::TimeSince(std::chrono::milliseconds _ms)
	: m_Time{ std::chrono::steady_clock::now() - _ms }
{
}

TimeSince::TimeSince(std::chrono::seconds _sec)
	: m_Time{ std::chrono::steady_clock::now() - _sec }
{
}

TimeSince::TimeSince(std::chrono::minutes _min)
	: m_Time{ std::chrono::steady_clock::now() - _min }
{
}

TimeSince::TimeSince(std::chrono::hours _hour)
	: m_Time{ std::chrono::steady_clock::now() - _hour }
{
}

TimeSince::operator float() const
{
	return std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::steady_clock::now() - m_Time).count();
}