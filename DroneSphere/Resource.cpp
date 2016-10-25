#include "Resource.h"

void Resource_Test()
{
	cout << "  Resource_Test();" << endl;

}

Resource::Resource()
{
}
Resource::~Resource()
{
}

string Resource::GetName()
{
	return m_stName;
}
