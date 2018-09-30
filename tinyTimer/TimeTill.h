#pragma once
#include <chrono>
namespace tinyTimer
{
	class TimeTill
	{
	public:
		TimeTill();
		TimeTill(std::chrono::time_point<std::chrono::steady_clock> time);
		TimeTill(std::chrono::nanoseconds _ns);
		TimeTill(std::chrono::microseconds _us);
		TimeTill(std::chrono::milliseconds _ms);
		TimeTill(std::chrono::seconds _sec);
		TimeTill(std::chrono::minutes _min);
		TimeTill(std::chrono::hours _hour);
		~TimeTill() = default;

		operator float() const;
	private:
		std::chrono::time_point<std::chrono::steady_clock> m_Time;
	};
}