#include "Action.h"

list<Action> Action::m_liActionList;
list<Action> Action::m_liAutoActionList;


void Action_Test()
{
	cout << "  Action_Test();" << endl;
	Action action = Action();
	cout << "    ActionListSize:" << Action::GetSize_ActionList() << endl;
	cout << "    AutoActionListSize:" << Action::GetSize_ActionList() << endl;

	Action::AddAction(action);
	Action::AddAutoAction(action);

}

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

int Action::GetSize_ActionList()
{
	return m_liActionList.size();
}
int Action::GetSize_AutoActionList()
{
	return m_liAutoActionList.size();
}

void Action::AddAction(Action action)
{
	m_liActionList.push_back(action);
}
void Action::AddAutoAction(Action action)
{
	m_liAutoActionList.push_back(action);
}
