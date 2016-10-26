#include "Resource.h"

void Resource_Test()
{
	cout << "  Resource_Test();" << endl;

}

Resource::Resource()
{
	m_iCount = 0;
	m_iCountMax = 0;
	m_iRecoveryRate = 0;
}
Resource::~Resource()
{
}

string Resource::GetName()
{
	return m_stName;
}
void Resource::SetAlias(string alias)
{
	m_stAlias = alias;
}
string Resource::GetAlias()
{
	return m_stAlias;
}


int Resource::GetCount()
{
	return m_iCount;
}
int Resource::GetCountMax()
{
	return m_iCountMax;
}
int Resource::GetRecoveryRate()
{
	return m_iRecoveryRate;
}

