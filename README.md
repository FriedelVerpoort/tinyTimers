# tinyTimers !
NOTE: this was a one day project for now. I might put some more time in this, but this was just to for fun!

tinyTimers is a little C++ project that helps with timers and at this point in time very limited in functionallity, but maybe someone can get some insiration out of this. This is not a one-file include library, just 9 simple classes that I find very usefull.

## Usage

```cpp
TimerManager timeManager{};
/*CreateTimer(interval, repititions, TimerFunction(func, args...))*/
timeManager.CreateTimer(std::chrono::milliseconds(1000), 5,
		new TimerFunction<int, int>{ 
            [](int a, int b){std::cout << a << ", " << b << '\n'; }
        , 1, 2 });
/*CreateTimer(identifier, interval, repititions, TimerFunction(func, args...))*/
timeManager.CreateTimer("example", std::chrono::miliseconds(1500), 5,
       new TimerFunction<int>{
           [](int c){std::cout << c <<'\n';}
       , 3});
/*TimeSince*/
TimeSince timeSince{};
if(timeSince >= 10.0f)
{
    /*is true when longer then 10 seconds ago the timeSince variable was created*/
}
/*TimeTill*/
TimeTill timeTill{std::chrono::seconds(5)};
if(timeTill <= 0.0f)
{
    /*is true when longer then 5 second ago since timeTill*/
}
```

## Contributing
I don't think this library is at a point for contributions, but if you have any suggestions or any ideas feel free to open an issue, fork this or add a pull request.

## License
Not sure a license is needed, but someone said to me that it doesn't hurt and he's right so here you go.

[MIT](https://choosealicense.com/licenses/mit/)