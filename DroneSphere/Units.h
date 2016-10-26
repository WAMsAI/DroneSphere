#pragma once

#include <iostream>
#include <string>

#include "thing.h"

using namespace std;

void Units_Test();

class UnitsOperation
{
public:
	virtual string GetName() = 0;
	virtual void SetAlias(string alias) = 0;
	virtual string GetAlias() = 0;

	virtual int GetWork() = 0;
	virtual int GetCarry() = 0;
	virtual int GetMove() = 0;

	virtual int GetCloseATK() = 0;
	virtual int GetRangedATK() = 0;
	virtual int GetCloseATKCD() = 0;
	virtual int GetRangedATKCD() = 0;
	virtual int GetRangedATKSpeed() = 0;

	virtual int GetHP() = 0;
	virtual int GetHPMax() = 0;
	virtual int GetHPRe() = 0;
	virtual int GetSP() = 0;
	virtual int GetSPMax() = 0;
	virtual int GetSPRe() = 0;
	virtual int GetArmor() = 0;
};


class Units : public Thing, public UnitsOperation
{
public:
	Units();
	virtual ~Units();

	virtual string GetName() override;
	virtual void SetAlias(string alias) override;
	virtual string GetAlias() override;

	virtual int GetWork() override;
	virtual int GetCarry() override;
	virtual int GetMove() override;
	virtual int GetCloseATK() override;
	virtual int GetRangedATK() override;
	virtual int GetCloseATKCD() override;
	virtual int GetRangedATKCD() override;
	virtual int GetRangedATKSpeed() override;

	virtual int GetHP() override;
	virtual int GetHPMax() override;
	virtual int GetHPRe() override;
	virtual int GetSP() override;
	virtual int GetSPMax() override;
	virtual int GetSPRe() override;
	virtual int GetArmor() override;

public:
	int m_iWork;
	int m_iCarry;
	int m_iMove;

	int m_iCloseATK;
	int m_iRangedATK;
	int m_iCloseATKCD;
	int m_iRangedATKCD;
	int m_iRangedATKSpeed;

	int m_iHP;
	int m_iHPMax;
	int m_iHPRe;   // HP Recovery Rate 
	int m_iSP;
	int m_iSPMax;
	int m_iSPRe;   // Shield Point Recovery Rate
	int m_iArmor;
};

