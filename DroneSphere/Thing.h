#pragma once

#include <iostream>

using namespace std;

void Thing_Test();

class Thing
{
public:
	Thing();
	virtual ~Thing();

public:
	string m_stName;
	string m_stAlias;
};

