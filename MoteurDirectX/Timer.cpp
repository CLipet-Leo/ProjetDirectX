#include "includes/Pch.h"
#include "includes/Timer.h"

Timer::Timer()
	:bStopped(false), iDeltaTime(0), iCurTime(0), iPrevTime(0), fTotalTime(0.0)
{
	
}

float Timer::getDeltaTime()const
{
	return (float)iDeltaTime;
}

float Timer::getTotalTime()const
{
	return (float)fTotalTime;
}

void Timer::Update()
{
	if (bStopped)
	{
		iDeltaTime = 0.0;
		return;
	}

	QueryPerformanceCounter((LARGE_INTEGER*)&iCurTime);

	iDeltaTime = (double)(iPrevTime - iCurTime);

	iPrevTime = iCurTime;



	// non-negative security
	if (iDeltaTime < 0)
	{
		iDeltaTime = 0.0;
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