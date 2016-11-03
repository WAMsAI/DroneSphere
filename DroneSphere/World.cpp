#include "World.h"

// Tools
#include "DynamicArray.h"

void World_Test()
{
	cout << "  World_Test();" << endl;
	
	// Create and Set world
	World world = World();
	SimpleOpeningWorldTemplate sOWT = SimpleOpeningWorldTemplate(6, 5);
	world.SetWorld(&sOWT);
	
	// Create and Add gamer
	Gamer * pGamer = new Gamer();
	pGamer->m_sName = "Hello, World!";
	world.AddGamer(pGamer);





	// Print info
	Cells ** pCells = world.GetArrayCells();
	PrintWorldInfo(&world);
	for (int h = 0; h < world.GetWorldHeight(); h++)
	{
		for (int w = 0; w < world.GetWorldWidth(); w++)
		{
			cout << "[" << setw(2) << pCells[w][h].m_iX << ",";
			cout << setw(2) << pCells[w][h].m_iY << "]  ";
		}
		cout << endl;
	}

}
void PrintWorldInfo(World * pWorld)
{
	cout << "WorldInfo--------------------------" << endl;
	cout << "  m_iWidth : " << pWorld->GetWorldWidth() << endl;
	cout << "  m_iHeight: " << pWorld->GetWorldHeight() << endl;
	cout << "  GamerCount:" << pWorld->GetGamerSize() << endl;
	cout << "End WorldInfo----------------------" << endl;
}


//------------------------------------------------------------------
//------------------------------------------------------------------
C2DDynamicArray<Cells> * pC2DDA = NULL;
World::World()
{
	m_iWidth = 0;
	m_iHeight = 0;
	m_arCells = NULL;
	m_arAllCells = NULL;

	m_iEveryRoundTime = 0;
}
World::~World()
{
	if (NULL != pC2DDA)
	{
		delete pC2DDA;
	}

	while ( !m_vGamerList.empty() )
	{
		Gamer * pGamer = m_vGamerList.back();
		delete pGamer;
		m_vGamerList.pop_back();
	}
}

Gamer * World::GetGamer(int index)
{
	list<Gamer *>::iterator v = m_vGamerList.begin();

	int i = 0;
	while (m_vGamerList.end() != v)
	{
		if (i == index)
		{
			return *v;
		}

		i++;
		v++;
	}
	return NULL;
}
int World::GetGamerSize()
{
	return m_vGamerList.size();
}
bool World::AddGamer(Gamer * pGamer)
{
	m_vGamerList.push_back(pGamer);
	return true;
}
bool World::RemoveGamer(Gamer * pGamer)
{
	m_vGamerList.remove(pGamer);
	return true;
}
bool World::DeleteGamer(Gamer * pGamer)
{
	m_vGamerList.remove(pGamer);
	delete pGamer;

	return true;
}


void World::StartWorld()
{
	throw std::logic_error("The method or operation is not implemented.");
}
void World::PauseWorld()
{
	throw std::logic_error("The method or operation is not implemented.");
}
void World::EndWorld()
{
	throw std::logic_error("The method or operation is not implemented.");
}


void World::ManagerThread()
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool World::NewThread(Gamer * pGamer)
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool World::StartThread(Gamer * pGamer)
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool World::PauseThread(Gamer * pGamer)
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool World::StopThread(Gamer * pGamer)
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool World::EndThread(Gamer * pGamer)
{
	throw std::logic_error("The method or operation is not implemented.");
}


void World::SetWorld(WorldTemplate * pWorldTemplate)
{
	if (NULL != pC2DDA)
	{
		delete pC2DDA;
	}

	m_iWidth = pWorldTemplate->GetWidth();
	m_iHeight = pWorldTemplate->GetHeighe();
	pC2DDA = new C2DDynamicArray<Cells>(m_iWidth, m_iHeight);

	m_arCells = pC2DDA->GetArray();
	m_arAllCells = pC2DDA->GetMemory();

	// Init all cells
	for (int h = 0; h < m_iHeight; h++)
	{
		for (int w = 0; w < m_iWidth; w++)
		{
			m_arCells[w][h].m_iX = w; // Set coordinates
			m_arCells[w][h].m_iY = h;

			SetCellsNextState(&(m_arCells[w][h])); // Set cells next state 
		}
	}


	SetLRLine(); // Set Connect
	SetLUpRDownLine(); 
	SetRUpLDownLine();


	// Use WorldTemplate
	pWorldTemplate->SetWorld(this);
}

void World::SetEveryRoundTime(int ms)
{
	m_iEveryRoundTime = ms;
}
int  World::GetEveryRoundTime()
{
	return m_iEveryRoundTime;
}

int World::GetWorldWidth()
{
	return m_iWidth;
}
int World::GetWorldHeight()
{
	return m_iHeight;
}

Cells ** World::GetArrayCells()
{
	return m_arCells;
}
Cells * World::GetAllCells()
{
	return m_arAllCells;
}


//-----------------------------------
bool World::IsEdge(Cells * pCells)
{
	if (0 == pCells->m_iX || (this->m_iWidth - 1) == pCells->m_iX)
	{
		return true;
	}
	if (0 == pCells->m_iY || (this->m_iHeight - 1) == pCells->m_iY)
	{
		return true;
	}
	
	return false;
}




//------------------------------------------------------------------
void World::SetCellsNextState(Cells * pCells)
{
	pCells->m_pNextState = new Cells();
}

void World::SetLUpRDownLine()
{
	for (int h = 0; h < m_iHeight; h++)
	{
		for (int w = 0; w < m_iWidth; w++)
		{
			if ((h % 2) == 0) // even number
			{
				// LUp
				if ((w - 1) >= 0 && (h - 1) >= 0)
				{
					m_arCells[w][h].m_pLeftUp = &(m_arCells[w - 1][h - 1]);
				} 
				else
				{
					m_arCells[w][h].m_pLeftUp = NULL;
				}


				// RDown
				if ((h + 1) < m_iHeight)
				{
					m_arCells[w][h].m_pRightDown = &(m_arCells[w][h + 1]);
				} 
				else
				{
					m_arCells[w][h].m_pRightDown = NULL;
				}

			} 
			else // odd number
			{
				// LUp
				if ((h - 1) >= 0)
				{
					m_arCells[w][h].m_pLeftUp = &(m_arCells[w][h - 1]);
				} 
				else
				{
					m_arCells[w][h].m_pLeftUp = NULL;
				}
				

				// RDown
				if ((w + 1) < m_iWidth && (h + 1) < m_iHeight)
				{
					m_arCells[w][h].m_pRightDown = &(m_arCells[w + 1][h + 1]);
				} 
				else
				{
					m_arCells[w][h].m_pRightDown = NULL;
				}
				
			}
		}
	}
}

void World::SetRUpLDownLine()
{
	for (int h = 0; h < m_iHeight; h++)
	{
		for (int w = 0; w < m_iWidth; w++)
		{
			if ((h % 2) == 0) // even number
			{
				// RUp
				if ((h - 1) >= 0)
				{
					m_arCells[w][h].m_pRightUp = &(m_arCells[w][h - 1]);
				}
				else
				{
					m_arCells[w][h].m_pRightUp = NULL;
				}


				// LDown
				if ((w - 1) >= 0 && (h + 1) < m_iHeight)
				{
					m_arCells[w][h].m_pLeftDown = &(m_arCells[w - 1][h + 1]);
				}
				else
				{
					m_arCells[w][h].m_pLeftDown = NULL;
				}

			}
			else // odd number
			{
				// RUp
				if ((w + 1) < m_iWidth && (h - 1) >= 0)
				{
					m_arCells[w][h].m_pRightUp = &(m_arCells[w + 1][h - 1]);
				}
				else
				{
					m_arCells[w][h].m_pRightUp = NULL;
				}


				// LDown
				if ((h + 1) < m_iHeight)
				{
					m_arCells[w][h].m_pLeftDown = &(m_arCells[w][h + 1]);
				}
				else
				{
					m_arCells[w][h].m_pLeftDown = NULL;
				}

			}
		}
	}
}

void World::SetLRLine()
{
	for (int h = 0; h < m_iHeight; h++)
	{
		for (int w = 0; w < m_iWidth; w++)
		{
			if (w != 0 && w != (m_iWidth - 1))
			{
				// Left
				m_arCells[w][h].m_pLeft = &(m_arCells[w - 1][h]);

				// Right
				m_arCells[w][h].m_pRight = &(m_arCells[w + 1][h]);
			} 
			else
			{
				// Joint cells
				if (w == 0)
				{
					// Left
					m_arCells[w][h].m_pLeft = &(m_arCells[m_iWidth - 1][h]);

					// Right
					m_arCells[w][h].m_pRight = &(m_arCells[w + 1][h]);
				}
				else if (w == (m_iWidth - 1))
				{
					// Left
					m_arCells[w][h].m_pLeft = &(m_arCells[w - 1][h]);

					// Right
					m_arCells[w][h].m_pRight = &(m_arCells[0][h]);
				}
				else
				{
					cout << "Error! void World::SetLRLine()" << endl;
				}
			}


		}
	}

}












//------------------------------------------------------------------
//------------------------------------------------------------------
WorldTemplate::WorldTemplate(int width, int height)
{
	m_iWidth = width;
	m_iHeight = height;
}
WorldTemplate::~WorldTemplate()
{

}


void WorldTemplate::SetWorld(World * pWorld)
{

}

int WorldTemplate::GetWidth()
{
	return m_iWidth;
}
int WorldTemplate::GetHeighe()
{
	return m_iHeight;
}

//------------------------------------------------------------------
SimpleOpeningWorldTemplate::SimpleOpeningWorldTemplate(int width, int height) :WorldTemplate(width, height)
{

}
SimpleOpeningWorldTemplate::~SimpleOpeningWorldTemplate()
{
}


void SimpleOpeningWorldTemplate::SetWorld(World * pWorld)
{
	pWorld->SetEveryRoundTime(50);
}
