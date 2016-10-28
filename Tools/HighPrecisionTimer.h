#pragma once
/*
Creation Time: 2016-10-26 19:45:56
Creator:       WAMsAI
Email:         377253608@qq.com

Describe:
*/
#include <iostream>
#include <string>
#include <iomanip>

#include <windows.h>


using namespace std;

void HighPrecisionTimer_Test();

class HighPrecisionTimer
{
public:
	HighPrecisionTimer();
	~HighPrecisionTimer();

public:
	void Init();
	void Clock_Start();
	void Clock_End();
	double Clock_Endex();

	double GetTimeLag(); // Return : Millisecond

	bool IsAvailable();
private:
	LARGE_INTEGER m_llFreque;

	double m_dFF;
	double m_dFM;
	double m_dFT;

	long long m_llQT1;
	long long m_llQT2;
};

