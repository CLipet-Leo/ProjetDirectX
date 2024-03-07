#pragma once

#ifndef GAMETIMER_H
#define GAMETIMER_H

class Timer
{
public:
	Timer();

	float getDeltaTime()const;
	float getTotalTime()const;

	void Pause();
	void Unpause();
	void Reset();
	void Update();

private:
	double iDeltaTime;
	float fTotalTime;
	double mSecondsPerCount;

	__int64 iCurTime;
	__int64 iPrevTime;

	bool bStopped;
};

#endif GAMETIMER_H