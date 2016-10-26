#pragma once

#include <iostream>
#include <string>
#include <list>
#include <iomanip>
using namespace std;

#include "Gamer.h"
#include "Cells.h"

class World;
class WorldOperation;
class WorldTemplate;
class SimpleOpeningWorldTemplate;

void World_Test();
void PrintWorldInfo(World *pWorld);

class WorldOperation
{
public:
	virtual bool AddGamer(Gamer * pGamer) = 0;
	virtual bool RemoveGamer(Gamer * pGamer) = 0;
	virtual bool DeleteGamer(Gamer * pGamer) = 0;

	virtual void ManagerThread() = 0;
	virtual bool NewThread(Gamer * pGamer) = 0;
	virtual bool StartThread(Gamer * pGamer) = 0;
	virtual bool PauseThread(Gamer * pGamer) = 0;
	virtual bool StopThread(Gamer * pGamer) = 0;
	virtual bool EndThread(Gamer * pGamer) = 0;

	virtual void SetWorld(WorldTemplate * pWorldTemplate) = 0;
	virtual int  GetWorldWidth() = 0;
	virtual int  GetWorldHeight() = 0;


	virtual bool IsEdge(Cells * pCells) = 0;
};


class World : public WorldOperation
{
public:
	World();
	~World();

	virtual bool AddGamer(Gamer * pGamer) override;

	virtual bool RemoveGamer(Gamer * pGamer) override;

	virtual bool DeleteGamer(Gamer * pGamer) override;

	virtual void ManagerThread() override;

	virtual bool NewThread(Gamer * pGamer) override;

	virtual bool StartThread(Gamer * pGamer) override;

	virtual bool PauseThread(Gamer * pGamer) override;

	virtual bool StopThread(Gamer * pGamer) override;

	virtual bool EndThread(Gamer * pGamer) override;

	virtual void SetWorld(WorldTemplate * pWorldTemplate) override;

	virtual int GetWorldWidth() override;

	virtual int GetWorldHeight() override;


	virtual bool IsEdge(Cells * pCells) override;

private:
	void SetCellsNextState(Cells * pCells);
	void SetLUpRDownLine();
	void SetRUpLDownLine();
	void SetLRLine();

public:
	int m_iWidth;
	int m_iHeight;
	Cells ** m_arCells;
	Cells *  m_arAllCells;
	list<Gamer*> m_vGamerList;
};

class WorldTemplate
{
public:
	WorldTemplate(int width, int height);
	virtual ~WorldTemplate();

	virtual void SetWorld(World * pWorld);

	int GetWidth();
	int GetHeighe();

private:
	int m_iWidth;
	int m_iHeight;
};

class SimpleOpeningWorldTemplate: public WorldTemplate
{
public:
	SimpleOpeningWorldTemplate(int width, int height);
	~SimpleOpeningWorldTemplate();

	virtual void SetWorld(World * pWorld) override;

};

