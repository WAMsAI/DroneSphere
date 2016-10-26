#include "Building.h"

void Building_Test()
{
	cout << "  Building_Test();" << endl;

}

Building::Building()
{
	m_iHP = 0;
	m_iHPMax = 0;
	m_iHPRe = 0;   // HP Recovery Rate 
	m_iSP = 0;
	m_iSPMax = 0;
	m_iSPRe = 0;   // Shield Point Recovery Rate
	m_iArmor = 0;
}
Building::~Building()
{

}

string Building::GetName()
{
	return m_stName;
}
void Building::SetAlias(string alias)
{
	m_stAlias = alias;
}
string Building::GetAlias()
{
	return m_stAlias;
}

int Building::GetHP()
{
	return m_iHP;
}
int Building::GetHPMax()
{
	return m_iHPMax;
}
int Building::GetHPRe()
{
	return m_iHPRe;
}
int Building::GetSP()
{
	return m_iSP;
}
int Building::GetSPMax()
{
	return m_iSPMax;
}
int Building::GetSPRe()
{
	return m_iSPRe;
}
int Building::GetArmor()
{
	return m_iArmor;
}