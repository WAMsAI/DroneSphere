#include "Weather.h"

void Weather_Test()
{
	cout << "  Weather_Test();" << endl;

}

Weather::Weather()
{
}
Weather::~Weather()
{
}

string Weather::GetName()
{
	return m_stName;
}
void Weather::SetAlias(string alias)
{
	m_stAlias = alias;
}
string Weather::GetAlias()
{
	return m_stAlias;
}
