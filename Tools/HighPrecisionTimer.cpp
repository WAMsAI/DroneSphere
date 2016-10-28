#include "HighPrecisionTimer.h"


// ---------------------------------------------------------
void HighPrecisionTimer_Test()
{
	cout << "  HighPrecisionTimer_Test();" << endl << endl;

	HighPrecisionTimer * pHPT = new HighPrecisionTimer();

	cout << "HighPrecisionTimer Is Available:" << pHPT->IsAvailable() << endl;
	cout << "Start" << endl;
	pHPT->Clock_Start();

	Sleep(12);

	pHPT->Clock_End();
	cout << "End(ms):" << pHPT->GetTimeLag() << endl;



	delete pHPT;
}


HighPrecisionTimer::HighPrecisionTimer()
{
	memset(&m_llFreque, 0, sizeof(LARGE_INTEGER));
	m_dFF = 0;
	m_dFM = 0;
	m_dFT = 0;
	m_llQT1 = 0;
	m_llQT2 = 0;
	Init();
}
HighPrecisionTimer::~HighPrecisionTimer()
{

}


void HighPrecisionTimer::Init()
{
	QueryPerformanceFrequency(&m_llFreque);  
	m_dFF = (double)m_llFreque.QuadPart;
}
void HighPrecisionTimer::Clock_Start()
{
	QueryPerformanceCounter(&m_llFreque);
	m_llQT1 = m_llFreque.QuadPart;
}
void HighPrecisionTimer::Clock_End()
{
	QueryPerformanceCounter(&m_llFreque);
	m_llQT2 = m_llFreque.QuadPart;
}
double HighPrecisionTimer::Clock_Endex()
{
	QueryPerformanceCounter(&m_llFreque);
	m_llQT2 = m_llFreque.QuadPart;
	
	return ((((double)(m_llQT2 - m_llQT1)) / m_dFF) * 1000);
}

double HighPrecisionTimer::GetTimeLag()
{
	m_dFM = (double)(m_llQT2 - m_llQT1);
	m_dFT = m_dFM / m_dFF; // Second
	
	return (m_dFT * 1000.0); 
}

bool HighPrecisionTimer::IsAvailable()
{
	LARGE_INTEGER litmp;
	if (0 == QueryPerformanceFrequency(&litmp))
	{
		return false;
	}
	return true;
}
