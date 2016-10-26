#pragma once

#include <iostream>
#include <string>

#include "thing.h"

using namespace std;


void Resource_Test();



class ResourceOperation
{
public:
	virtual string GetName() = 0;
	virtual void SetAlias(string alias) = 0;
	virtual string GetAlias() = 0;

	virtual int GetCount() = 0;
	virtual int GetCountMax() = 0;
	virtual int GetRecoveryRate() = 0;

};

class Resource : public Thing, public ResourceOperation
{
public:
	Resource();
	virtual ~Resource();

	virtual string GetName() override;
	virtual void   SetAlias(string alias) override;
	virtual string GetAlias() override;


	virtual int GetCount() override;
	virtual int GetCountMax() override;
	virtual int GetRecoveryRate() override;

public:
	int m_iCount;
	int m_iCountMax;
	int m_iRecoveryRate;
};

