/* Randomizer.cpp -- */
#include <time.h>
#include <windows.h>
#include "Randomizer.h"
#include <iostream>

using namespace std;



static bool RandomBool_bool();
static unsigned int Random0ToN_unInt(unsigned int iN);
static unsigned int Random1ToN_unInt(unsigned int iN);
static double Random0To1_double();
static double RandomM1ToI1_double();


void ResetRandomize()
{
	// Randomize seed 
	time_t staTime = (unsigned)time(NULL);
	srand((unsigned)staTime);
}
void ResetRandomize(unsigned int iSeed)
{
	srand(iSeed);
}
bool ResetRandomize_Frequency()
{
	LARGE_INTEGER litmp;
	LONGLONG qt1;


	if (false == QueryPerformanceFrequency(&litmp)) 
	{
		return false; 
	}

	QueryPerformanceCounter(&litmp);  
	qt1 = litmp.QuadPart;

	srand((unsigned)qt1);

	return true;
}

bool GetRandomBool()
{
	return RandomBool_bool();
}
unsigned int GetRandom0ToN_unInt(unsigned int iN)
{
	return Random0ToN_unInt(iN);
}
unsigned int GetRandom1ToN_unInt(unsigned int iN)
{
	return Random1ToN_unInt(iN);
}
double GetRandom0To1_double()
{
	return Random0To1_double();
}
double GetRandomM1ToI1_double()
{
	return RandomM1ToI1_double();
}




static bool RandomBool_bool()
{
	if (0 == (int)(2 * rand() / (RAND_MAX + 1.0)))
	{
		return false;
	} 
	
	return true;
}
static unsigned int Random0ToN_unInt(unsigned int iN)
{
	// Generate a random number [0, N].
	iN += 1;

	int x = (int)(iN * rand() / (RAND_MAX + 1.0));

	return x;
}
static unsigned int Random1ToN_unInt(unsigned int iN)
{
	// Generate a random number [1, N].
	int x = (int)(1 + iN * rand() / (RAND_MAX + 1.0));
	return x;
}
static double Random0To1_double()
{
	double a, b; // Generate a random number [a, b].
	double x;
	a = 0;
	b = 1;

	x = (a + (b - a) * rand() / (RAND_MAX));

	return x;
}
static double RandomM1ToI1_double()
{
	double a, b; // Generate a random number [a, b].
	double x;
	a = -1;
	b = 1;

	x = (a + (b - a) * rand() / (RAND_MAX - 1));

	return x;
}


