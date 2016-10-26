#pragma once

#include <iostream>
#include <list>

#include "Building.h"
#include "Terrain.h"
#include "Units.h"
#include "Resource.h"
#include "Weather.h"

using namespace std;

void Cells_Test();

class Cells
{
public:
	Cells();
	~Cells();

	void CopyCellsTo(Cells * pCellsDest);

public:
	int m_iX;
	int m_iY;

	Cells * m_pLeft;
	Cells * m_pRight;
	Cells * m_pLeftUp;
	Cells * m_pRightUp;
	Cells * m_pLeftDown;
	Cells * m_pRightDown;

	Building * m_pBuilding;
	Terrain * m_pTerrain;
	list<Units> m_lUnitsList;
	Resource * m_pResource;
	Weather * m_pWeather;

	Cells * m_pNextState;
};

