#pragma once
#include <iostream>
#include <string>
using namespace std;

// ---------------------------------------------------------------------------
void DynamicArray_Test();

// 该类未实现
template <class ELEMENT, class ARRAY>
class DynamicArray
{
public:
	DynamicArray(int N, int[]);
	~DynamicArray();
	
	ARRAY NewArray(int N, int[]);

	ARRAY GetArray();
	int   GetDimension();
	int * GetParmList();

private:
	void FreeArray();

private:
	ARRAY m_arNArray;
	int   m_iN;
	int * m_liParmList;
};


template <class ELEMENT, class ARRAY>
DynamicArray<ELEMENT, ARRAY>::DynamicArray(int N, int[])
{

}

template <class ELEMENT, class ARRAY>
DynamicArray<ELEMENT, ARRAY>::~DynamicArray()
{

}

template <class ELEMENT, class ARRAY>
ARRAY DynamicArray<ELEMENT, ARRAY>::NewArray(int N, int[])
{

}

template <class ELEMENT, class ARRAY>
ARRAY DynamicArray<ELEMENT, ARRAY>::GetArray()
{

}

template <class ELEMENT, class ARRAY>
int DynamicArray<ELEMENT, ARRAY>::GetDimension()
{

}

template <class ELEMENT, class ARRAY>
int * DynamicArray<ELEMENT, ARRAY>::GetParmList()
{

}

template <class ELEMENT, class ARRAY>
void DynamicArray<ELEMENT, ARRAY>::FreeArray()
{

}


// ---------------------------------------------------------------------------
void C2DDynamicArray_Test();

// array[X][Y]->xxxx
// x0y0 x1y0 x2y0 x3y0 ; x0y1 x1y1 x2y2.... ; ...;...;
template <class ELEMENT>
class C2DDynamicArray
{
public:
	C2DDynamicArray(int X, int Y);
	~C2DDynamicArray();
	
	ELEMENT** NewArray(int X, int Y);

	ELEMENT** GetArray();
	ELEMENT * GetMemory();
	int GetX();
	int GetY();



private:
	void FreeArray();


private:
	ELEMENT ** m_ar2DArray;
	ELEMENT * m_pMemory;
	int m_iX;
	int m_iY;
};




template <class ELEMENT>
C2DDynamicArray<ELEMENT>::C2DDynamicArray(int X, int Y)
{
	m_pMemory = NULL;
	m_ar2DArray = NULL;
	NewArray(X, Y);
}

template <class ELEMENT>
C2DDynamicArray<ELEMENT>::~C2DDynamicArray()
{
	FreeArray();
}


template <class ELEMENT>
ELEMENT** C2DDynamicArray<ELEMENT>::NewArray(int X, int Y)
{
	m_iX = X;
	m_iY = Y;
	if (NULL != m_ar2DArray)
	{
		FreeArray();
		m_ar2DArray = NULL;
		m_pMemory = NULL;
	}


	// 申请所需空间
	ELEMENT * memory = new ELEMENT[X * Y];


	// 为空间分配指针
	ELEMENT ** twoDArray = new ELEMENT *[X];
	for (int i = 0; i < X; ++i)
	{
		twoDArray[i] = memory + (i * Y);
	}


	m_ar2DArray = twoDArray;
	m_pMemory = memory;
	return m_ar2DArray;
}

template <class ELEMENT>
ELEMENT** C2DDynamicArray<ELEMENT>::GetArray()
{
	return m_ar2DArray;
}

template <class ELEMENT>
ELEMENT* C2DDynamicArray<ELEMENT>::GetMemory()
{
	return m_pMemory;
}

template <class ELEMENT>
int C2DDynamicArray<ELEMENT>::GetX()
{
	return m_iX;
}

template <class ELEMENT>
int C2DDynamicArray<ELEMENT>::GetY()
{
	return m_iY;
}

template <class ELEMENT>
void C2DDynamicArray<ELEMENT>::FreeArray()
{
	if (NULL != m_ar2DArray)
	{
		// 释放申请的空间
		delete[] m_pMemory;

		// 释放申请的指针
		delete[] m_ar2DArray;
	}
}









