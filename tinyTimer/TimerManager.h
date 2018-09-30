#pragma once
#include <unordered_map>
#include "Timer.h"
namespace tinyTimer
{
	class TimerManager
	{
	public:
		TimerManager() = default;
		~TimerManager() = default;
		ITimer* CreateTimer(std::chrono::milliseconds interval, uint32_t reps, TimerFunctionBasePtr delegate);
		ITimer* CreateTimer(const std::string& identifier, std::chrono::milliseconds interval, uint32_t reps, TimerFunctionBasePtr delegate);

		bool RemoveTimer(const std::string& identifier);
		bool RemoveTimer(ITimer* id);

		bool ExistsTimer(const std::string& identifier);
		ITimer* GetTimer(const std::string& identifier);
		void Update(std::chrono::milliseconds dt);

	private:
		std::unordered_map<std::string, ExtendedTimer*> m_Timers{};
		std::vector<SimpleTimer*> m_SimpleTimers{};
	};
}