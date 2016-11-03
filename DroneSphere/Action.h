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
};


class ActionListOperation
{
	virtual void     TakeAction(Action * pAction) = 0;
	virtual Action * GetFirstAction() = 0;
	virtual void     RemoveFirstAction() = 0;
	virtual Action * GetFirstAutoAction() = 0;
	virtual void     RemoveFirstAutoAction() = 0;


	virtual void AddAction(Action * pAction) = 0;     // add to list back
	virtual void AddAutoAction(Action * pAction) = 0; // add to list back
	
	virtual int GetSize_ActionList() = 0;
	virtual int GetSize_AutoActionList() = 0;
};
class ActionList : public ActionListOperation
{
public:
	ActionList();
	~ActionList();

	virtual void TakeAction(Action * pAction) override;

	virtual Action * GetFirstAction() override;
	virtual void RemoveFirstAction() override;
	virtual Action * GetFirstAutoAction() override;
	virtual void RemoveFirstAutoAction() override;

	virtual void AddAction(Action * pAction) override;
	virtual void AddAutoAction(Action * pAction) override;

	virtual int GetSize_ActionList() override;
	virtual int GetSize_AutoActionList() override;


private:
	list<Action *> m_liActionList;
	list<Action *> m_liAutoActionList;
};


