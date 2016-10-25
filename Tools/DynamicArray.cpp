#include "DynamicArray.h"


// ---------------------------------------------------------------------------
void DynamicArray_Test()
{

}


// ---------------------------------------------------------------------------
class MyClass
{
public:
	MyClass();
	~MyClass();
	string m_stName;
private:

};
MyClass::MyClass()
{
	m_stName = "Win";
}
MyClass::~MyClass()
{
}
void C2DDynamicArray_Test()
{
	//C2DDynamicArray<int> * twoDA = new C2DDynamicArray<int>(2, 3);
	//int ** p = twoDA->GetArray();
	//if (p !=  NULL)
	//{
	//	cout << "!= NULL" << endl;
	//}
	//
	//cout << "Array Test" << endl;
	//for (int i = 0; i < 2; ++i)
	//{
	//	for (int j = 0; j < 3; j++)
	//	{
	//		p[i][j] = i * 3 + j;
	//		cout << "[" <<p[i][j] << "] ,";
	//	}
	//	cout << endl;
	//}
	//cout << endl;
	//
	//int * p2 = twoDA->GetMemory();
	//for (int i = 0; i < 2 * 3; i++)
	//{
	//	cout << "[" << p2[i] << "] " << endl;
	//}
	//
	//delete twoDA;

	// --------------------------------------
	C2DDynamicArray<MyClass> * twoDA = new C2DDynamicArray<MyClass>(2, 3);

	MyClass * p = twoDA->GetMemory();
	p[0].m_stName += "233";

	delete twoDA;
}



