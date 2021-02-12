#ifndef NUMBERPRINTER
#define NUMBERPRINTER

#include <iostream>
#include "PageGroupItem.h"

using namespace std;

#define TYPE_INT 0
#define TYPE_FLOAT 1
#define TYPE_DOUBLE 2
#define TYPE_VEC2 3
#define TYPE_VEC3 4 
#define TYPE_VEC4 5

struct NumberPrinterData
{
	string Description;
	int Type;
	int* Integer = nullptr;
	float* Float = nullptr;
	glm::vec2* VEC2 = nullptr;
	glm::vec3* VEC3 = nullptr;
	glm::vec4* VEC4 = nullptr;
};

class NumberPrinter : public PageGroupItem
{
public: 

	NumberPrinterData CurrentNumberPrinter;

	NumberPrinter() {};
	NumberPrinter(llBookData* llBook);
	NumberPrinter(llBookData* llBook, llPageItemData* llPageItem, NumberPrinterData NumberPrinter);
	NumberPrinter(llPageItemData* llPageItem);

	void llUpdate();
	void CreateNumber();
	void CreateInt();
	void CreateFloat();
	void CreateDouble();
	void CreateVec2();
	void CreateVec3();
	void CreateVec4();
	void ReplaceNumber();

	void Add_Default() override {};
	void Add_Duplicate() override {};
	void Add_Insert() override {};
};

#endif
