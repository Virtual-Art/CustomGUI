#ifndef NUMBERPRINTER
#define NUMBERPRINTER

#include <iostream>
#include "PageGroupItem.h"

using namespace std;



struct NumberPrinterData
{
	string Description;
	int FontSize = 16;
	int Type = -1;
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

	void llInit(llBookData* llBook, llPageItemData* llPageItem, NumberPrinterData NumberPrinter);

	void llUpdate();
	void CreateNumber();
	void CreateInt();
	void CreateFloat();
	void CreateDouble();
	void CreateVec2();
	void CreateVec3();
	void CreateVec4();
	void ReplaceNumber();


	void ReplaceVec2();
	void SetVec2(glm::vec2* NewVec2);

	void Add_Default() override {};
	void Add_Duplicate() override {};
	void Add_Insert() override {};
};

#endif
