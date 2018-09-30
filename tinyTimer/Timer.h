#pragma once
#include <string>
#include <functional>
#include <chrono>
/*Idea's: 
 destroyable timers
*
1.templated ITimer for precision
2.Updates with different inputs
*
*/
namespace tinyTimer
{

	template<typename ...args>
	struct TimerFunctionContainer
	{
		std::function<void(args...)> func;
		std::tuple<args...> arg;

		explicit TimerFunctionContainer(std::function<void(args...)> f, args... argList) :
			func{ f },
			arg{ std::tuple<args...>(std::forward<args>(argList)...) }
		{
		}
	};

	class ITimerFunction
	{
	public:
		ITimerFunction() = default;
		virtual ~ITimerFunction() = default;

		virtual void operator()() = 0;
	};

	template<typename ...args>
	class TimerFunction : public ITimerFunction
	{
	public:
		TimerFunction(std::function<void(args...)> f, args ... argList)
			:m_Container(f, std::forward<args>(argList)...)
		{
		}
		virtual ~TimerFunction() = default;

		template<std::size_t... Is>
		void CallFunction(std::function<void(args...)>& func, const std::tuple<args...>& tuple, std::index_sequence<Is...>)
		{
			func(std::get<Is>(tuple)...);
		}

		virtual void operator()() override
		{
			CallFunction(m_Container.func, m_Container.arg, std::index_sequence_for<args...>());
		}
	private:
		TimerFunctionContainer<args...> m_Container;
	};


	using TimerFunctionBasePtr = ITimerFunction * ;

	class ITimer
	{
	public:
		explicit ITimer(std::chrono::milliseconds interval, uint32_t reps, TimerFunctionBasePtr delegate);
		virtual ~ITimer() = default;

		void Adjust(std::chrono::milliseconds delay);
		void Adjust(std::chrono::milliseconds delay, uint32_t repititions);
		void Adjust(std::chrono::milliseconds delay, TimerFunctionBasePtr delegate);

		void Adjust(uint32_t repititions);
		void Adjust(uint32_t repititions, TimerFunctionBasePtr delegate);

		void Adjust(TimerFunctionBasePtr timeDelegate);
		void Adjust(std::chrono::milliseconds delay, uint32_t repititions, TimerFunctionBasePtr delegate);

		void Pause();
		void Unpause();
		void Toggle();

		std::chrono::milliseconds TimeLeft() const;
		uint32_t RepititionsLeft() const;

		std::chrono::milliseconds IntervalTime() const;
		uint32_t TotalReptitions() const;
		bool ShouldBeDestroyed() const;
		void SetDestroyed(bool destroy);

		void Update(std::chrono::milliseconds dt);

	protected:
		std::chrono::milliseconds m_Interval;
		uint32_t m_TotalRepititions;
		TimerFunctionBasePtr m_TimeDelegate;
	private:
		std::chrono::milliseconds m_Delta;
		uint32_t m_Repititions;
		bool m_Paused;
		bool m_Destroy;
	};

	class SimpleTimer : public ITimer
	{
	public:
		explicit SimpleTimer(std::chrono::milliseconds interval, uint32_t reps, TimerFunctionBasePtr timeDelegate);
		virtual ~SimpleTimer() = default;
	};

	class ExtendedTimer : public ITimer
	{
	public:
		explicit ExtendedTimer(const std::string& identifier, std::chrono::milliseconds interval, uint32_t reps, TimerFunctionBasePtr timeDelegate);
		virtual ~ExtendedTimer() = default;

		void GetIdentifier(std::string& str);
		std::string GetIdentifier() const;
	private:
		std::string m_Identifier;
	};
}