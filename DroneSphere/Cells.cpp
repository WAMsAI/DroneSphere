#include "Cells.h"

void Cells_Test()
{
	cout << "  Cells_Test();" << endl;
	Cells cells = Cells();

}

Cells::Cells()
{
	m_iX = 0;
	m_iY = 0;

	m_pLeft = NULL;
	m_pRight = NULL;
	m_pLeftUp = NULL;
	m_pRightUp = NULL;
	m_pLeftDown = NULL;
	m_pRightDown = NULL;

	m_pBuilding = NULL;
	m_pTerrain = NULL;
	//m_lUnitsList;
	m_pResource = NULL;
	m_pWeather = NULL;


	m_pNextState = NULL; 
}
Cells::~Cells()
{

}

void Cells::CopyCellsTo(Cells * pCellsDest)
{

}

