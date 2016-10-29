/* Randomizer.h -- */
#ifndef _RANDOMIZER_H
#define _RANDOMIZER_H


//* Interface */

// Operation: Reset random seed, at the current time as a random seed.
void ResetRandomize();

// Operation: Reset random seed, iSeed as a random seed.
void ResetRandomize(unsigned int iSeed);

// Operation: Reset random seed, at the current precision time as a random seed,
// Return:    false, Does not support.
// Attention: Be careful use this function, in the loop.
bool ResetRandomize_Frequency();

// Operation: Generate random boolean value.
bool GetRandomBool();

// Operation: Generate a random natural number [0, N].
unsigned int GetRandom0ToN_unGenerateInt(unsigned int iN);

// Operation: Generate a random positive integer number [1, N].
unsigned int GetRandom1ToN_unInt(unsigned int iN);

// Operation: Generate a random double [0, 1].
double GetRandom0To1_double();

// Operation: Generate a random double [-1, 1].
double GetRandomM1ToI1_double();

#endif