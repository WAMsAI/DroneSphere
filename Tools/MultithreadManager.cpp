#include "MultithreadManager.h"



// ---------------------------------------------------------
const int END_PRODUCE_NUMBER = 10;   // 生产产品个数  
int g_Buffer;                        // 缓冲区  

// 事件与关键段  
CRITICAL_SECTION g_cs;
HANDLE g_hEventBufferEmpty, g_hEventBufferFull;

// 生产者线程函数  
unsigned int __stdcall ProducerThreadFun(PVOID pM)
{
	for (int i = 1; i <= END_PRODUCE_NUMBER; i++)
	{
		//等待缓冲区为空  
		WaitForSingleObject(g_hEventBufferEmpty, INFINITE);

		//互斥的访问缓冲区  
		EnterCriticalSection(&g_cs);
		g_Buffer = i;
		cout << redcolor << "  生产者将数据 [" << i << "] 放入缓冲区"  << defcolor << endl;
		LeaveCriticalSection(&g_cs);

		//通知缓冲区有新数据了  
		SetEvent(g_hEventBufferFull);
	}
	return 0;
}

// 消费者线程函数  
unsigned int __stdcall ConsumerThreadFun(PVOID pM)
{
	volatile bool flag = true;
	while (flag)
	{
		// 等待缓冲区中有数据  
		WaitForSingleObject(g_hEventBufferFull, INFINITE);

		// 互斥的访问缓冲区  
		EnterCriticalSection(&g_cs);
		
		cout << greencolor << "    消费者从缓冲区中取数据：" << g_Buffer << defcolor << endl;
		
		if (g_Buffer == END_PRODUCE_NUMBER)
		{
			flag = false;
		}

		LeaveCriticalSection(&g_cs);

		// 通知缓冲区已为空  
		SetEvent(g_hEventBufferEmpty);

		Sleep(10); // some other work should to do  
	}
	return 0;
}

void MultithreadManager_Learn_0_Test()
{
	cout << "  MultithreadManager_Learn_0_Test();" << endl << endl;

	// 1生产者 1消费者 1缓冲区  
	// 使用二个事件，一个表示缓冲区空，一个表示缓冲区满。  
	// 再使用一个关键段来控制缓冲区的访问  
	cout << "  生产者消费者问题   1生产者 1消费者 1缓冲区" << endl << endl;

	InitializeCriticalSection(&g_cs);
	
	// 创建二个自动复位事件，一个表示缓冲区是否为空，另一个表示缓冲区是否已经处理  
	g_hEventBufferEmpty = CreateEvent(NULL, FALSE, TRUE, NULL);
	g_hEventBufferFull = CreateEvent(NULL, FALSE, FALSE, NULL);


	const int THREADNUM = 2;
	HANDLE hThread[THREADNUM];

	hThread[0] = (HANDLE)_beginthreadex(NULL, 0, ProducerThreadFun, NULL, 0, NULL);
	hThread[1] = (HANDLE)_beginthreadex(NULL, 0, ConsumerThreadFun, NULL, 0, NULL);
	WaitForMultipleObjects(THREADNUM, hThread, TRUE, INFINITE);
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);

	// 销毁事件和关键段  
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
	MultithreadManager * pMTM = new MultithreadManager(12);

	pMTM->AddThread(new ThreadMTM(false));
	pMTM->AddThread(new ThreadMTM(false));


	cout << pMTM->WaitForAllThread() << endl;

	//delete pMTM;
}

MultithreadManager::MultithreadManager(int SharedResSize)
{
	m_iThreadSize = 0;
	m_iSharedResourceSize = SharedResSize;

	m_arResourceLock = new ResourceLock[SharedResSize];
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
}



int MultithreadManager::GetThreadSize()
{
	return m_iThreadSize;
}
int MultithreadManager::GetSharedResSize()
{
	return m_iSharedResourceSize;
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
