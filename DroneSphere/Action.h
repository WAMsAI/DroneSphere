#pragma once

#include <iostream>
#include <string>
#include <list>

#include "thing.h"

using namespace std;

void Action_Test();

class Action : public Thing
{
public:
	Action();
	virtual ~Action();

	string GetName();
	void SetAlias(string alias);
	string GetAlias();


	virtual void TakeAction();
	

// In order to multi-thread.
public:
	static int GetSize_ActionList();
	static int GetSize_AutoActionList();

	static void AddAction(Action action);
	static void AddAutoAction(Action action);

// In order to multi-thread.
private:
	static list<Action> m_liActionList;
	static list<Action> m_liAutoActionList;
};

