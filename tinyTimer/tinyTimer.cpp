// tinyTimer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <thread>
#include "TimerManager.h"
#include <iostream>
#include "TimeSince.h"
#include "TimeTill.h"
#include <chrono>
using namespace tinyTimer;

void test(int a)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	//int a{};
	for(int i{}; i < 100; i++)
	{
		a = i * rand() % 500;
	}
}

int lol(int i)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(430));
	return i + 2;
}

int main()
{
	TimerManager timeManager{};
	auto lamda = []()
	{std::cout << 1 << ", " << 2 << '\n'; };

	timeManager.CreateTimer(std::chrono::milliseconds(1000), 5,
		new TimerFunction<>{ lamda });
	TimeSince t{};
	TimeTill till{ std::chrono::seconds{3} };
	//std::chrono::milliseconds ms = TimeFunction<std::chrono::milliseconds, void ,int>(test, 1);
	//auto test = TimeFunction<std::chrono::milliseconds, int, int>(lol, 1);
	auto test2 = TimeFunction<std::chrono::milliseconds, void, int>(test, 1);
	std::cout << test2.count() << '\n';
	//std::cout << "return value: " << test.first << ", time taken: " << test.second.count() << '\n';
	while(true)
	{
		timeManager.PreUpdate();
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		timeManager.Update(std::chrono::milliseconds(50));
		if (t > 7.0f)
		{
			std::cout << "Time Since == 7\n";
			t = TimeSince{};
		}
		if (till < 0)
		{
			std::cout << "Time till < 0\n";
			till =  std::chrono::seconds{ 3 };
		}
	}
    return 0;
}

