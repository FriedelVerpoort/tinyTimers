// tinyTimer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <thread>
#include "TimerManager.h"
#include <iostream>
#include "TimeSince.h"
#include "TimeTill.h"
using namespace tinyTimer;
int main()
{
	TimerManager timeManager{};
	auto lamda = [](int a, int b)
	{std::cout << a << ", " << b << '\n'; };

	timeManager.CreateTimer(std::chrono::milliseconds(1000), 5,
		new TimerFunction<int, int>{ lamda, 1, 2 });
	TimeSince t{};
	TimeTill till{ std::chrono::seconds{3} };

	while(true)
	{
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

