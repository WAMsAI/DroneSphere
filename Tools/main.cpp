/*
Creation Time: 2016-10-23 11:17:11
Creator:       WAMsAI
Email:         377253608@qq.com

Describe:
*/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

#include "DynamicArray.h"


using namespace std;
int main()
{
	cout << "----- START -----------------------------------------------------" << endl;

	// TODO:
	C2DDynamicArray_Test();

	C2DDynamicArray<int> * twoDA = new C2DDynamicArray<int>(2, 3);


	delete twoDA;

	cout << "-----  END  -----------------------------------------------------" << endl;
	return 0;
}

