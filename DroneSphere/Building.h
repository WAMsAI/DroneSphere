#pragma once

#include <iostream>
#include <string>

#include "thing.h"

using namespace std;

void Building_Test();

class BuildingOperation
{
public:
	virtual string GetName() = 0;
	virtual void SetAlias(string alias) = 0;
	virtual string GetAlias() = 0;

	virtual int GetHP() = 0;
	virtual int GetHPMax() = 0;
	virtual int GetHPRe() = 0;
	virtual int GetSP() = 0;
	virtual int GetSPMax() = 0;
	virtual int GetSPRe() = 0;
	virtual int GetArmor() = 0;
};


class Building : public Thing, public BuildingOperation
{
public:
	Building();
	virtual ~Building();

	virtual string GetName() override;
	virtual void SetAlias(string alias) override;
	virtual string GetAlias() override;

	virtual int GetHP() override;
	virtual int GetHPMax() override;
	virtual int GetHPRe() override;
	virtual int GetSP() override;
	virtual int GetSPMax() override;
	virtual int GetSPRe() override;
	virtual int GetArmor() override;

public:
	int m_iHP;
	int m_iHPMax;
	int m_iHPRe;   // HP Recovery Rate 
	int m_iSP;
	int m_iSPMax;
	int m_iSPRe;   // Shield Point Recovery Rate
	int m_iArmor;
};

