#ifndef BOOK
#define BOOK

#include <iostream>
#include <string>
#include "Page.h"

//CreateGrid_Act[SIZE][1] = &MyAction;
using namespace std;

class Book : Page
{
public:

	Book(string FilePath);
	string FilePath;
	int CurrentCount;
	Page Page[5];

	void AddPage(string Name, ShaderProgram ShapeShader);

	void Erase();
	void Update();

};

#endif 

