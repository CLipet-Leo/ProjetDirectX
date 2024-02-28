#include <windows.h>
#include "Timer.h"

Timer::Timer()
	:bStopped(false), iDeltaTime(0), iCurTime(0), iPrevTime(0), fTotalTime(0.0)
{

}

float Timer::getDeltaTime()
{
	return (float)iDeltaTime;
}

float Timer::getTotalTime()
{
	return fTotalTime;
}

void Timer::Update()
{
	if (bStopped)
	{
		iDeltaTime = 0;
		return;
	}

	QueryPerformanceCounter((LARGE_INTEGER*)&iCurTime);

	iDeltaTime = iPrevTime - iCurTime;

	iPrevTime = iCurTime;



	// non-negative security
	if (iDeltaTime < 0)
	{
		iDeltaTime = 0;
	}
}

void Timer::Pause()
{
	bStopped = true;
}

void Timer::Unpause()
{
	bStopped = false;
}

void Timer::Reset()
{
	fTotalTime = 0;
}