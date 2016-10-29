#include "MultithreadManager.h"



// ---------------------------------------------------------
const int END_PRODUCE_NUMBER = 10;   
int g_Buffer;                       

// CriticalSection and Event
CRITICAL_SECTION g_cs;
HANDLE g_hEventBufferEmpty, g_hEventBufferFull;

// Producer Thread Fun 
unsigned int __stdcall ProducerThreadFun(PVOID pM)
{
	for (int i = 1; i <= END_PRODUCE_NUMBER; i++)
	{
		WaitForSingleObject(g_hEventBufferEmpty, INFINITE);

		EnterCriticalSection(&g_cs);
		g_Buffer = i;
		cout << redcolor << "  Producer put [" << i << "] in buffer"  << defcolor << endl;
		LeaveCriticalSection(&g_cs);

		
		SetEvent(g_hEventBufferFull);
	}
	return 0;
}

// Consumer Thread Fun
unsigned int __stdcall ConsumerThreadFun(PVOID pM)
{
	volatile bool flag = true;
	while (flag)
	{
		WaitForSingleObject(g_hEventBufferFull, INFINITE);

		EnterCriticalSection(&g_cs);
		
		cout << greencolor << "    Consumer get data from " << g_Buffer << defcolor << endl;
		
		if (g_Buffer == END_PRODUCE_NUMBER)
		{
			flag = false;
		}

		LeaveCriticalSection(&g_cs);

		SetEvent(g_hEventBufferEmpty);

		Sleep(10); // some other work should to do  
	}
	return 0;
}

void MultithreadManager_Learn_0_Test()
{
	cout << "  MultithreadManager_Learn_0_Test();" << endl << endl;

	// 1 Producer, 1 Consumer, 1 Buffer.  
	// Use two Event, one represented  Buffer is empty,  one represented Buffer is full. 
	// Then use CriticalSection to control Buffer visit.
	cout << "  Producer and Consumer problem:   1 Producer, 1 Consumer, 1 Buffer." << endl << endl;

	InitializeCriticalSection(&g_cs);
	
	// Create two auto-reset events.
	g_hEventBufferEmpty = CreateEvent(NULL, FALSE, TRUE, NULL);
	g_hEventBufferFull = CreateEvent(NULL, FALSE, FALSE, NULL);


	const int THREADNUM = 2;
	HANDLE hThread[THREADNUM];

	hThread[0] = (HANDLE)_beginthreadex(NULL, 0, ProducerThreadFun, NULL, 0, NULL);
	hThread[1] = (HANDLE)_beginthreadex(NULL, 0, ConsumerThreadFun, NULL, 0, NULL);
	WaitForMultipleObjects(THREADNUM, hThread, TRUE, INFINITE);
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);

	// delete 
	CloseHandle(g_hEventBufferEmpty);
	CloseHandle(g_hEventBufferFull);
	DeleteCriticalSection(&g_cs);

}
void MultithreadManager_Learn_1_Test()
{
	cout << "  MultithreadManager_Learn_1_Test();" << endl << endl;


}




// ---------------------------------------------------------


void MultithreadManager_Test()
{
	cout << "  MultithreadManager_Test();" << endl << endl;
	MultithreadManager * pMTM = new MultithreadManager(12, 3);

	//pMTM->AddThread(new ThreadMTM(false));
	//pMTM->AddThread(new ThreadMTM(false));


	cout << pMTM->WaitForAllThread() << endl;

	delete pMTM;
}

MultithreadManager::MultithreadManager(int SharedResSize, int SyncSignalSize)
{
	m_iThreadSize = 0;
	m_iSharedResourceSize = SharedResSize;
	m_iSynchronousSignalSize = SyncSignalSize;

	m_arResourceLock = new ResourceLock[SharedResSize];
	m_arSyncSignal = new ActionSignal[SyncSignalSize];

}
MultithreadManager::~MultithreadManager()
{
	while (!m_liThreadMTM.empty())
	{
		ThreadMTM * tMTM = m_liThreadMTM.back();
		if (tMTM == NULL)
		{
			break;
		}

		delete tMTM;
		m_liThreadMTM.pop_back();
	}

	delete[] m_arResourceLock;
	delete[] m_arSyncSignal;
}



int MultithreadManager::GetThreadSize()
{
	return m_iThreadSize;
}
int MultithreadManager::GetSharedResSize()
{
	return m_iSharedResourceSize;
}


ResourceLock * MultithreadManager::GetResourceLockArray()
{
	return m_arResourceLock;
}
ActionSignal * MultithreadManager::GetSyncSignal()
{
	return m_arSyncSignal;
}

ThreadMTM * MultithreadManager::GetThreadMTM(int index)
{
	list<ThreadMTM *>::iterator v = m_liThreadMTM.begin();
	
	int i = 0;
	while (m_liThreadMTM.end() != v)
	{
		if (i == index)
		{
			return *v;
		}

		i++;
		v++;
	}
	return NULL;
}

void MultithreadManager::AddThread(ThreadMTM * pThreadMTM)
{
	m_liThreadMTM.push_back(pThreadMTM);
	m_iThreadSize = m_liThreadMTM.size();
}
void MultithreadManager::RemoveThread(ThreadMTM * pThreadMTM)
{
	m_liThreadMTM.remove(pThreadMTM);
	m_iThreadSize = m_liThreadMTM.size();
}
void MultithreadManager::DeleteThread(ThreadMTM * pThreadMTM)
{
	m_liThreadMTM.remove(pThreadMTM);
	m_iThreadSize = m_liThreadMTM.size();

	delete pThreadMTM;
}

bool MultithreadManager::WaitForAllThread()
{
	// this function, maybe error!
	HANDLE * handle = (HANDLE *)malloc(sizeof(HANDLE) * m_iThreadSize);
	
	list<ThreadMTM *>::iterator v = m_liThreadMTM.begin();
	for (int i = 0; i < m_iThreadSize; i++, v++)
	{
		handle[i] = (*v)->GetHandle();
	}

	//for (v = m_liThreadMTM.begin(); v != m_liThreadMTM.end(); ++v)
	//{
	//	
	//}

	if (WAIT_OBJECT_0 == WaitForMultipleObjects(m_iThreadSize, handle, TRUE, INFINITE))
	{
		free(handle);
		return true;
	}
	free(handle);
	return false;
}
bool MultithreadManager::WaitForAllThread(long ms)
{
	// this function, maybe error!
	HANDLE * handle = new HANDLE[m_iThreadSize];

	DWORD dw = WaitForMultipleObjects(m_iThreadSize, handle, TRUE, INFINITE);
	if (WAIT_OBJECT_0 == dw)
	{
		delete handle;
		return true;
	}
	else if (WAIT_TIMEOUT == dw)
	{
		delete handle;
		return false;
	}
	delete handle;
	return false;
}

// ---------------------------------------------------------
void ThreadMTM_Test()
{
	cout << "  ThreadMTM_Test();" << endl << endl;

	ThreadMTM * pThreadMTM_0 = new ThreadMTM(true);
	ThreadMTM * pThreadMTM_1 = new ThreadMTM(true);
	pThreadMTM_0->StartThread();
	pThreadMTM_1->StartThread();

	pThreadMTM_0->WaitForThread();
	pThreadMTM_1->WaitForThread();

	delete pThreadMTM_0;
	delete pThreadMTM_1;
}

ThreadMTM::ThreadMTM(bool bIsSuspend)
{
	m_bIsStopped = false;
	if (true == bIsSuspend)
	{
		m_hThread = (HANDLE)_beginthreadex(NULL, 0, StartRoutine, this, CREATE_SUSPENDED, &m_uiId);
	}
	else
	{
		m_hThread = (HANDLE)_beginthreadex(NULL, 0, StartRoutine, this, 0, &m_uiId);
	}
	
}
ThreadMTM::~ThreadMTM()
{
	if (NULL != m_hThread)
	{
		EndThread();
		CloseHandle(m_hThread);
	}
	//cout << "~ThreadMTM()" << endl;
}


bool ThreadMTM::StartThread()
{
	if (-1 == ResumeThread(m_hThread))
	{
		return false;
	}
	return true;
}

bool ThreadMTM::PauseThread()
{
	if (-1 == SuspendThread(m_hThread))
	{
		return false;
	}
	return true;
}

bool ThreadMTM::EndThread()
{
	// TerminateThread() is dangerous.
	// If the target thread owns a critical section, 
	// the critical section will not be released.
	// ...
	if (0 == TerminateThread(m_hThread, 2048))
	{
		return false;
	}
	return true;
}


bool ThreadMTM::IsStopped()
{
	return m_bIsStopped;
}


bool ThreadMTM::WaitForThread()
{
	if (WAIT_OBJECT_0 == WaitForSingleObject(m_hThread, INFINITE))
	{
		return true;
	}
	return false;
}
bool ThreadMTM::WaitForThread(long ms)
{
	DWORD dw = WaitForSingleObject(m_hThread, INFINITE);
	if (WAIT_OBJECT_0 == dw)
	{
		return true;
	}
	else if (WAIT_TIMEOUT == dw)
	{
		return false;
	}
	return false;
}


HANDLE ThreadMTM::GetHandle()
{
	return m_hThread;
}


void ThreadMTM::Run()
{
	for (int i = 0; i < 10; ++i)
	{
		Sleep(500);

		strstream ss;
		string st;
		ss << "ThreadID:<" << m_uiId;
		ss << ">____";
		ss << "Times:" << i; 
		ss >> st;
		st += "\n";
		cout << st;
		//cout << "ThreadID:<" << m_uiId << "> Times:" << i << endl;
	}
}


void ThreadMTM::EndThreadInRunFunc()
{
	// _endthreadex()
	_endthreadex(1096);
}

// ---------------------------------------------------------
void ResourceLock_Test()
{
	cout << "  ResourceLock_Test();" << endl << endl;

	ResourceLock * rl0 = new ResourceLock(false, TEXT("HUDDDDDDDDDD"));
	ResourceLock * rl1 = new ResourceLock();
	
	cout << "LockName:<"; 
	if (NULL != rl1->GetLockName())
	{
		wprintf_s(rl1->GetLockName());
	}
	cout << ">"<< endl;
	
	cout << rl1->Lock() << endl;
	rl1->Unlock();

	cout << rl1->TryLock() << endl;
	rl1->Unlock();


	cout << "LockName:<";
	wprintf(rl1->GetLockName());
	cout << ">" << endl;

	delete rl0;
	delete rl1;
}

ResourceLock::ResourceLock()
{
	//cout << redcolor << "FFFFFFFFFFFFF" << defcolor << endl;
	m_lpName = NULL;
	m_hMutex = CreateMutex(NULL, FALSE, NULL);
}
ResourceLock::ResourceLock(bool isInit)
{
	if (true == isInit)
	{
		m_hMutex = CreateMutex(NULL, FALSE, NULL);
	}
	m_lpName = NULL;
}
ResourceLock::ResourceLock(bool isOwner, LPCWSTR name)
{
	m_hMutex = CreateMutex(NULL, isOwner, name);
	m_lpName = name;
}
ResourceLock::ResourceLock(LPCWSTR openName, bool * pIsOk)
{
	m_lpName = openName;
	m_hMutex = OpenMutex(MUTEX_ALL_ACCESS, TRUE, openName);
	

	if (NULL != pIsOk)
	{
		if (NULL == m_hMutex)
		{
			*pIsOk = false;
		}
		else
		{
			*pIsOk = true;
		}
	}
}

ResourceLock::~ResourceLock()
{
	//cout << "~ResourceLock();" << endl;
	if (NULL != m_hMutex)
	{
		CloseHandle(m_hMutex);
	}
}


LPCWSTR ResourceLock::GetLockName()
{
	return m_lpName;
}
bool ResourceLock::Lock()
{
	if (m_hMutex)
	{
		return WaitForSingleObject(m_hMutex, INFINITE) == WAIT_OBJECT_0;
	}
	return false;
}
bool ResourceLock::TryLock()
{
	if (m_hMutex)
	{
		return WaitForSingleObject(m_hMutex, 0) == WAIT_OBJECT_0;
	}
	return false;
}
bool ResourceLock::Unlock()
{
	if (m_hMutex)
	{
		BOOL bhere = ReleaseMutex(m_hMutex);
		if (0 == bhere)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	return false;
}


// ---------------------------------------------------------
void ActionSignal_Test()
{
	cout << "  ActionSignal_Test();" << endl << endl;
	ActionSignal * pAS = new ActionSignal(2, 5, NULL);
	
	if (pAS->GetName())
	{
		wprintf_s(pAS->GetName());
	}
	cout << endl;

	cout << "InitCount:" << pAS->GetInitCount() << endl;
	cout << "MaxCount:" << pAS->GetMaxCount() << endl;
	cout << "Wait:" << pAS->WaitActionSignal() << endl;
	cout << "WaitZero:" << pAS->WaitZeroActionSignal() << endl;
	cout << "WaitZero:" << pAS->WaitZeroActionSignal() << endl;
	cout << endl;
	cout << "Release:" << pAS->ReleaseActionSignal(pAS, 1) << endl;
	cout << "WaitZero:" << pAS->WaitZeroActionSignal() << endl;
	cout << "WaitZero:" << pAS->WaitZeroActionSignal() << endl;


	delete pAS;
}

ActionSignal::ActionSignal()
{
	m_lInitCount = 0;
	m_lMaxCount = 0;
	m_lpName = NULL;
	m_hSemaphore = NULL;
}
ActionSignal::ActionSignal(long lInitCount, long lMaxCount, LPCWSTR name)
{
	m_lInitCount = lInitCount;
	m_lMaxCount = lMaxCount;
	m_lpName = name;
	m_hSemaphore = CreateSemaphore(NULL, lInitCount, lMaxCount, name);
}
ActionSignal::ActionSignal(LPCWSTR openName, bool * pIsOk)
{
	m_lpName = openName;
	m_hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, openName);
	m_lInitCount = -1;
	m_lMaxCount = -1;

	if (NULL != pIsOk)
	{
		if (NULL == m_hSemaphore)
		{
			*pIsOk = false;
		}
		else
		{
			*pIsOk = true;
		}
	}
}

ActionSignal::~ActionSignal()
{
	if (NULL != m_hSemaphore)
	{
		CloseHandle(m_hSemaphore);
	}
}


void ActionSignal::Init(long lInitCount, long lMaxCount, LPCWSTR name)
{
	m_hSemaphore = CreateSemaphore(NULL, lInitCount, lMaxCount, name);
}
bool ActionSignal::Init(LPCWSTR openName)
{
	m_lpName = openName;
	m_hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, openName);
	m_lInitCount = -1;
	m_lMaxCount = -1;

	if (NULL == m_hSemaphore)
	{
		return false;
	}
	else
	{
		return true;
	}
}

LPCWSTR ActionSignal::GetName()
{
	return m_lpName;
}
long ActionSignal::GetInitCount()
{
	return m_lInitCount;
}
long ActionSignal::GetMaxCount()
{
	return m_lMaxCount;
}


bool ActionSignal::WaitActionSignal()
{
	if (m_hSemaphore)
	{
		return WaitForSingleObject(m_hSemaphore, INFINITE) == WAIT_OBJECT_0;
	}
	return false;
}
bool ActionSignal::WaitZeroActionSignal()
{
	if (m_hSemaphore)
	{
		return WaitForSingleObject(m_hSemaphore, 0) == WAIT_OBJECT_0;
	}
	return false;
}

bool ActionSignal::ReleaseThisActionSignal(long i)
{
	BOOL bhere = ReleaseSemaphore(this->GetSemaphore(), i, NULL);
	if (FALSE == bhere)
	{
		return false;
	}
	else
	{
		return true;
	}

	return false;
}
bool ActionSignal::ReleaseActionSignal(ActionSignal * pActionSignal, long i)
{
	if (NULL != pActionSignal)
	{
		BOOL bhere = ReleaseSemaphore(pActionSignal->GetSemaphore(), i, NULL);
		if (FALSE == bhere)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	return false;
}

HANDLE ActionSignal::GetSemaphore()
{
	return m_hSemaphore;
}


// ---------------------------------------------------------
void WorkerThreadMTM_Test()
{
	cout << "  WorkerThreadMTM_Test();" << endl << endl;
	MultithreadManager * pMTM = new MultithreadManager(12, 3);
	ResourceLock * arRL = pMTM->GetResourceLockArray();
	ActionSignal * arAS = pMTM->GetSyncSignal();



	cout << greencolor;

	pMTM->AddThread(new WorkerThreadMTM(arRL, arAS, true));
	pMTM->AddThread(new WorkerThreadMTM(arRL, arAS, true));

	arAS[1].Init(0, 1, NULL);
	arAS[2].Init(0, 1, NULL);


	WorkerThreadMTM * pWT0 = (WorkerThreadMTM *)pMTM->GetThreadMTM(0);
	WorkerThreadMTM * pWT1 = (WorkerThreadMTM *)pMTM->GetThreadMTM(1);

	bool t1 = false;
	bool t2 = false;

	//bool t1 = arRL[1].TryLock();
	//bool t2 = arRL[2].TryLock();

	pWT0->StartThread();
	pWT1->StartThread();

	t1 = arAS[1].WaitActionSignal();
	t2 = arAS[2].WaitActionSignal();

	printf_s("AS:%d GET:%d\n", 1, t1);
	printf_s("AS:%d GET:%d\n", 2, t2);

	cout << "N1 Time:" << pWT0->m_pHPT->GetTimeLag() << endl;
	cout << "N2 Time:" << pWT1->m_pHPT->GetTimeLag() << endl;


	//printf_s("RL:%d Lock:%d\n", 1, t1);
	//printf_s("RL:%d Lock:%d\n", 2, t2);

	cout << endl << "ThreadIsEnd:" << pMTM->WaitForAllThread() << endl;
	
	cout << defcolor;

	delete pMTM;
}

WorkerThreadMTM::WorkerThreadMTM(ResourceLock * arRL, ActionSignal * arAS, bool bIsSuspend) :ThreadMTM(bIsSuspend)
{
	m_arRL = arRL;
	m_arAS = arAS;
	sm_iThreadCount++;
	m_iNumber = sm_iThreadCount;

	m_pHPT = new HighPrecisionTimer();
}
WorkerThreadMTM::~WorkerThreadMTM()
{
	delete m_pHPT;
	//cout << "~WorkerThreadMTM()" << endl;
}
void WorkerThreadMTM::Run()
{
	m_arRL[m_iNumber].Lock();
	
	srand((unsigned)time(NULL));
	int x = rand() * m_iNumber;
	printf_s("ThreadID:%d Number:%d Rand:%d\n", m_uiId, m_iNumber, x);

	m_pHPT->Clock_Start();
	
	// Todo:
	Sleep(500 * (x % 10)); // Run time

	m_pHPT->Clock_End();

	m_arRL[m_iNumber].Unlock();


	m_arAS[m_iNumber].ReleaseThisActionSignal(1);
}

int WorkerThreadMTM::sm_iThreadCount = 0;
