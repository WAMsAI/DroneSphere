#include "Terrain.h"

void Terrain_Test()
{
	cout << "  Terrain_Test();" << endl;

}

Terrain::Terrain()
{
}
Terrain::~Terrain()
{
}

string Terrain::GetName()
{
	return m_stName;
}
void Terrain::SetAlias(string alias)
{
	m_stAlias = alias;
}
string Terrain::GetAlias()
{
	return m_stAlias;
}
