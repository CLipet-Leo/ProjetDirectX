#pragma once
#include "Pch.h"

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
	__int64 iDeltaTime;
	float fTotalTime;

	__int64 iCurTime;
	__int64 iPrevTime;

	bool bStopped;
};

#endif // GAMETIMER_H