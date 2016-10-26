#pragma once

#include <iostream>
#include <string>

#include "thing.h"

using namespace std;

void Weather_Test();

class WeatherOperation
{
public:
	virtual string GetName() = 0;
	virtual void SetAlias(string alias) = 0;
	virtual string GetAlias() = 0;

};

class Weather : public Thing, public WeatherOperation
{
public:
	Weather();
	virtual ~Weather();

	virtual string GetName() override;
	virtual void SetAlias(string alias) override;
	virtual string GetAlias() override;

};

