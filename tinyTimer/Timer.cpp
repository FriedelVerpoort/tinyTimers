#include "stdafx.h"
#include "Timer.h"
using namespace tinyTimer;

ITimer::ITimer(std::chrono::milliseconds interval, uint32_t reps, TimerFunctionBasePtr delegate)
	:m_Interval(interval), m_Delta(0), m_Repititions(reps), m_TotalRepititions(reps), m_TimeDelegate(delegate), m_Paused(false)
{
}

void ITimer::Adjust(std::chrono::milliseconds delay)
{
	m_Interval = delay;
	m_Delta = delay;
}

void ITimer::Adjust(std::chrono::milliseconds delay, uint32_t repititions)
{
	m_Interval = delay;
	m_Delta = delay;
	m_Repititions = repititions;
	m_TotalRepititions = repititions;
}

void ITimer::Adjust(std::chrono::milliseconds delay, TimerFunctionBasePtr delegate)
{
	m_Interval = delay;
	m_Delta = delay;
	m_TimeDelegate = delegate;
}

void ITimer::Adjust(uint32_t repititions)
{
	m_Repititions = repititions;
	m_TotalRepititions = repititions;
}

void ITimer::Adjust(uint32_t repititions, TimerFunctionBasePtr delegate)
{
	m_Repititions = repititions;
	m_TotalRepititions = repititions;
	m_TimeDelegate = delegate;
}

void ITimer::Adjust(TimerFunctionBasePtr timeDelegate)
{
	m_TimeDelegate = timeDelegate;
}

void ITimer::Adjust(std::chrono::milliseconds delay, uint32_t repititions, TimerFunctionBasePtr delegate)
{
	m_Interval = delay;
	m_Delta = delay;
	m_Repititions = repititions;
	m_TotalRepititions = repititions;
	m_TimeDelegate = delegate;
}

void ITimer::Pause()
{
	m_Paused = true;
}

void ITimer::Unpause()
{
	m_Paused = false;
}

void ITimer::Toggle()
{
	m_Paused = !m_Paused;
}

std::chrono::milliseconds ITimer::TimeLeft() const
{
	return m_Delta;
}

uint32_t ITimer::RepititionsLeft() const
{
	return m_Repititions;
}

std::chrono::milliseconds ITimer::IntervalTime() const
{
	return  m_Interval;
}

uint32_t ITimer::TotalReptitions() const
{
	return m_TotalRepititions;
}

void ITimer::Update(std::chrono::milliseconds dt)
{
	if (m_Repititions == 0) return;
	m_Delta += dt;
	if (m_Delta >= m_Interval)
	{
		if (m_TotalRepititions != (std::numeric_limits<uint32_t>::max)())
			m_Repititions--;
		m_Delta -= m_Interval;
		(*m_TimeDelegate)();
	}
}

SimpleTimer::SimpleTimer(std::chrono::milliseconds interval, uint32_t reps, TimerFunctionBasePtr timeDelegate)
	:ITimer(interval, reps, timeDelegate)
{
}

ExtendedTimer::ExtendedTimer(const std::string& identifier, std::chrono::milliseconds interval, uint32_t reps, TimerFunctionBasePtr timeDelegate)
	:ITimer(interval, reps, timeDelegate), m_Identifier(identifier)
{
}

void ExtendedTimer::GetIdentifier(std::string& str)
{
	str = m_Identifier;
}

std::string ExtendedTimer::GetIdentifier() const
{
	return m_Identifier;
}