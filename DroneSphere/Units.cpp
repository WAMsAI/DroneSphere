#include "Units.h"

void Units_Test()
{
	cout << "  Units_Test();" << endl;
	Units uints = Units();
	cout << "    Work:" << uints.GetWork() << endl;
}

Units::Units()
{
	m_iWork = 0;
	m_iCarry = 0;
	m_iMove = 0;

	m_iCloseATK = 0;
	m_iRangedATK = 0;
	m_iCloseATKCD = 0;
	m_iRangedATKCD = 0;
	m_iRangedATKSpeed = 0;

	m_iHP = 0;
	m_iHPMax = 0;
	m_iHPRe = 0;   // HP Recovery Rate 
	m_iSP = 0;
	m_iSPMax = 0;
	m_iSPRe = 0;   // Shield Point Recovery Rate
	m_iArmor = 0;
}
Units::~Units()
{

}

string Units::GetName()
{
	return m_stName;
}
void Units::SetAlias(string alias)
{
	m_stAlias = alias;
}
string Units::GetAlias()
{
	return m_stAlias;
}

int Units::GetWork()
{
	return m_iWork;
}
int Units::GetCarry()
{
	return m_iCarry;
}
int Units::GetMove()
{
	return m_iMove;
}

int Units::GetCloseATK()
{
	return m_iCloseATK;
}
int Units::GetRangedATK()
{
	return m_iRangedATK;
}
int Units::GetCloseATKCD()
{
	return m_iCloseATKCD;
}
int Units::GetRangedATKCD()
{
	return m_iRangedATKCD;
}
int Units::GetRangedATKSpeed()
{
	return m_iRangedATKSpeed;
}

int Units::GetHP()
{
	return m_iHP;
}
int Units::GetHPMax()
{
	return m_iHPMax;
}
int Units::GetHPRe()
{
	return m_iHPRe;
}
int Units::GetSP()
{
	return m_iSP;
}
int Units::GetSPMax()
{
	return m_iSPMax;
}
int Units::GetSPRe()
{
	return m_iSPRe;
}
int Units::GetArmor()
{
	return m_iArmor;
}
