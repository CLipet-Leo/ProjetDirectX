#pragma once
class Timer
{
public:

	Timer();

	float getDeltaTime();
	float getTotalTime();

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