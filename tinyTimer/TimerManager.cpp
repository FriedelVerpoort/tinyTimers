#include "stdafx.h"
#include "TimerManager.h"
#include <algorithm>
using namespace tinyTimer;
ITimer* TimerManager::CreateTimer(std::chrono::milliseconds interval, uint32_t reps, TimerFunctionBasePtr delegate)
{
	ITimer* ptr = new SimpleTimer(interval, reps, delegate);
	m_SimpleTimers.push_back(static_cast<SimpleTimer* >(ptr));
	return ptr;
}

ITimer* TimerManager::CreateTimer(const std::string& identifier, std::chrono::milliseconds interval, uint32_t reps, TimerFunctionBasePtr delegate)
{
	ITimer * ptr = new ExtendedTimer(identifier, interval, reps, delegate);
	if(m_Timers.insert(std::make_pair(identifier, static_cast<ExtendedTimer*>(ptr))).second)
		return ptr;
	return nullptr;
}

bool TimerManager::RemoveTimer(const std::string& identifier)
{
	auto it = m_Timers.find(identifier);
	if(it != m_Timers.end())
	{
		m_Timers.erase(it);
		return true;
	}
	return false;
}

bool TimerManager::RemoveTimer(ITimer* id)
{
	SimpleTimer * sTimer = dynamic_cast<SimpleTimer*>(id);
	ExtendedTimer* eTimer = dynamic_cast<ExtendedTimer*>(id);
	if (sTimer || eTimer)
	{
		if(sTimer)
		{
			auto it = std::remove(m_SimpleTimers.begin(), m_SimpleTimers.end(), id);
			m_SimpleTimers.erase(it, m_SimpleTimers.end());
			return true;
		}
		else
		{
			std::string i{};
			eTimer->GetIdentifier(i);
			return RemoveTimer(i);
		}
	}
	return false;
}

bool TimerManager::ExistsTimer(const std::string& identifier)
{
	auto it = m_Timers.find(identifier);
	if (it != m_Timers.end())
		return true;
	return false;
}

ITimer* TimerManager::GetTimer(const std::string& identifier)
{
	auto it = m_Timers.find(identifier);
	if (it != m_Timers.end())
		return it->second;
	return nullptr;
}

void TimerManager::PreUpdate()
{
	for(auto it = m_Timers.begin(); it != m_Timers.end(); it++)
	{
		if(it->second->ShouldBeDestroyed())
		{
			m_Timers.erase(it);
		}
	}

	auto simpleIt = std::remove_if(m_SimpleTimers.begin(), m_SimpleTimers.end(), [](SimpleTimer* p) {return p->ShouldBeDestroyed(); });
	m_SimpleTimers.erase(simpleIt, m_SimpleTimers.end());
}

void TimerManager::Update(std::chrono::milliseconds dt)
{
	for(auto timer : m_Timers)
	{
		timer.second->Update(dt);
	}
	for(auto timer : m_SimpleTimers)
	{
		timer->Update(dt);
	}
}
