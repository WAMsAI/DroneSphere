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
};

class Resource : public Thing, public ResourceOperation
{
public:
	Resource();
	virtual ~Resource();

	virtual string GetName() override;

public:

};

