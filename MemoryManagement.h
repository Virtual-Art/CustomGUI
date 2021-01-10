#ifndef MEMORY
#define MEMORY

#include <iostream>
#include <memory>
#include <string>
//#include "UIElement.h"

using namespace std;

template <typename _Type>
class MemoryManagment 
{
public:
	//We can create any function even with unkown types, and return unkown times or allocate unkown types
	//MemoryManagment(_Type Object)
	//{
	//}

	string Megabytes(int Bytes);
	string Kilobytes(int Bytes);

	_Type* MakeContainer(int Amount);
	//cout << Something<int>(6, 7) << endl;

};

#endif

