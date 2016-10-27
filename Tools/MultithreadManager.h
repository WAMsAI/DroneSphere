#pragma once
/*
Creation Time: 2016-10-26 19:43:05
Creator:       WAMsAI
Email:         377253608@qq.com

Describe:
*/
#include <iostream>
#include <string>
#include <iomanip>
#include <list>
#include <strstream>

#include <windows.h>
#include <process.h>

#include "ColorCout.h"

using namespace std;

class ThreadMTM;
class ResourceLock;
class MultithreadManager;


void MultithreadManager_Learn_0_Test();
void MultithreadManager_Learn_1_Test();

void MultithreadManager_Test();
class MultithreadManager
{
public:
	MultithreadManager(int SharedResSize);
	~MultithreadManager();

	int GetThreadSize();
	int GetSharedResSize();
	
	void AddThread(ThreadMTM * pThreadMTM);
	void RemoveThread(ThreadMTM * pThreadMTM);
	void DeleteThread(ThreadMTM * pThreadMTM);

	
	bool WaitForAllThread();
	bool WaitForAllThread(long ms);

private:
	int m_iSharedResourceSize;
	ResourceLock * m_arResourceLock;

	int m_iThreadSize;
	list<ThreadMTM *> m_liThreadMTM;
};


void ThreadMTM_Test();
class ThreadMTM
{
public:
	ThreadMTM(bool bIsSuspend);
	~ThreadMTM();

	bool StartThread();
	bool PauseThread();
	bool EndThread();

	bool IsStopped();

	bool WaitForThread();
	bool WaitForThread(long ms);

	HANDLE GetHandle();

protected:
	virtual void Run();
	

private:
	static unsigned int WINAPI StartRoutine(void * parm)
	{
		ThreadMTM * pThreadMTM = (ThreadMTM *)parm;
		pThreadMTM->Run();
		pThreadMTM->m_bIsStopped = true;
		return 0;
	}

	void EndThreadInRunFunc();


private:
	HANDLE m_hThread;
	bool   m_bIsStopped;
	unsigned int m_uiId;
};


void ResourceLock_Test();
class ResourceLock
{
public:
	ResourceLock();
	ResourceLock(bool isInit);
	ResourceLock(bool isOwner, LPCWSTR name);
	ResourceLock(LPCWSTR openName, bool * pIsOk);
	~ResourceLock();

	LPCWSTR GetLockName();
	
	bool Lock();
	bool TryLock();
	bool Unlock();

private:
	HANDLE m_hMutex;
	LPCWSTR m_lpName;
};

void ActionSignal_Test();
class ActionSignal
{
public:
	ActionSignal(long lInitCount, long lMaxCount, LPCWSTR name);
	ActionSignal(LPCWSTR openName, bool * pIsOk);
	~ActionSignal();

	LPCWSTR GetName();
	long GetInitCount();
	long GetMaxCount();
	
	bool WaitActionSignal();
	bool WaitZeroActionSignal();
	bool ReleaseActionSignal(ActionSignal * pActionSignal, long i);

private:
	HANDLE GetSemaphore();

private:
	HANDLE m_hSemaphore;
	LPCWSTR m_lpName;
	long m_lInitCount;
	long m_lMaxCount;
};


