
#define NOMINMAX
#include <Windows.h>
class Timer
{
	LARGE_INTEGER tt;
	__int64 counterFrequency = 0;	//frequency of the system timer
	__int64 counterStart = 0;		//counter value at the start of this counter
	__int64 counterEnd = 0;			//counter value at the end of this counter
	__int64 counterLast = 0;		//counter value on the last pause
	__int64 counterTotalTicks = 0;	//sum of all ticks between all: start-pause, resume-pause, start-end and resume-end

public:
	Timer();
	void start();
	void stop();
	void pause();
	void resume();
	__int64 getCounterTotalTicks() { return counterTotalTicks; };
	__int64 getCounterFrequency() { return counterFrequency; };
};