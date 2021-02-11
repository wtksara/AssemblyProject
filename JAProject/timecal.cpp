#include "timecal.h"

Timer::Timer()
{
	QueryPerformanceFrequency(&tt);
	counterFrequency = tt.QuadPart;
}

void Timer::start()
{
	QueryPerformanceCounter(&tt); // Init start, last and total ticks
	counterStart = tt.QuadPart;
	counterLast = tt.QuadPart;
	counterTotalTicks = 0;
}

void Timer::stop()
{
	QueryPerformanceCounter(&tt); // Increase total ticks and set end
	counterTotalTicks += tt.QuadPart - counterLast;
	counterEnd = tt.QuadPart;
	counterLast = tt.QuadPart;
}

void Timer::pause()
{
	QueryPerformanceCounter(&tt); // Increase total ticks and set counter last
	counterTotalTicks += tt.QuadPart - counterLast;
	counterLast = tt.QuadPart;
}

void Timer::resume()
{
	QueryPerformanceCounter(&tt);// Set counterLast
	counterLast = tt.QuadPart;
}