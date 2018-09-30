#pragma once
#include <chrono>

//idea from https://garry.tv/2018/01/16/timesince/
namespace tinyTimer
{
	class TimeSince
	{
	public:
		TimeSince();
		TimeSince(std::chrono::time_point<std::chrono::steady_clock> time);
		TimeSince(std::chrono::nanoseconds _ns);
		TimeSince(std::chrono::microseconds _us);
		TimeSince(std::chrono::milliseconds _ms);
		TimeSince(std::chrono::seconds _sec);
		TimeSince(std::chrono::minutes _min);
		TimeSince(std::chrono::hours _hour);
		~TimeSince() = default;

		operator float() const;
	private:
		std::chrono::time_point<std::chrono::steady_clock> m_Time;
	};
}