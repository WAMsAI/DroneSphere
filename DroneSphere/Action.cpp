#include "Action.h"




void Action_Test()
{
	cout << "  Action_Test();" << endl;
	Action * pAction = new Action();
	ActionList pAList = ActionList();

	pAList.AddAction(pAction);

	Action * temp;
	temp = pAList.GetFirstAction();
	if (temp == pAction)
	{
		cout << "yes" << endl;
	}

	temp->TakeAction();

	
	delete pAction;
}

//------------------------------------------------------------------
Action::Action()
{

}
Action::~Action()
{
}


string Action::GetName()
{
	return m_stName;
}
void Action::SetAlias(string alias)
{
	m_stAlias = alias;
}
string Action::GetAlias()
{
	return m_stAlias;
}

void Action::TakeAction()
{

}



//------------------------------------------------------------------
ActionList::ActionList()
{

}
ActionList::~ActionList()
{
}

void ActionList::TakeAction(Action * pAction)
{
	pAction->TakeAction();
}

Action * ActionList::GetFirstAction()
{
	return m_liActionList.front();
}
void ActionList::RemoveFirstAction()
{
	m_liActionList.pop_front();
}
Action * ActionList::GetFirstAutoAction()
{
	return m_liAutoActionList.front();
}
void ActionList::RemoveFirstAutoAction()
{
	m_liAutoActionList.pop_front();
}

void ActionList::AddAction(Action * pAction)
{
	m_liActionList.push_back(pAction);
}
void ActionList::AddAutoAction(Action * pAction)
{
	m_liAutoActionList.push_back(pAction);
}

int ActionList::GetSize_ActionList()
{
	return m_liActionList.size();
}
int ActionList::GetSize_AutoActionList()
{
	return m_liAutoActionList.size();
}


