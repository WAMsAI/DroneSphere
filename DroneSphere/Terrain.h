#pragma once

#include <iostream>
#include <string>

#include "thing.h"


using namespace std;

void Terrain_Test();

class TerrainOperation
{
public:
	virtual string GetName() = 0;
	virtual void SetAlias(string alias) = 0;
	virtual string GetAlias() = 0;

};

class Terrain : public Thing, public TerrainOperation
{
public:
	Terrain();
	virtual ~Terrain();

	virtual string GetName() override;
	virtual void SetAlias(string alias) override;
	virtual string GetAlias() override;

};

