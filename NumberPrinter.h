#ifndef NUMBERPRINTER
#define NUMBERPRINTER

#include <iostream>
#include "PageGroupItem.h"

using namespace std;


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
	void CreateString() {};
	void CreateNumber();
	void CreateInt();
	void CreateFloat();
	void CreateDouble();
	void CreateVec2();
	void CreateVec3();
	void CreateVec4();
	void ReplaceNumber();

	void SetDescriptionColor(glm::vec4 Color);

	void ReplaceVec2();
	void SetVec2(glm::vec2* NewVec2);

	void ReplaceString() {};           //INCOMPLETE
	void SetString(string* String) {}; //INCOMPLETE

	void Add_Default() override {};
	void Add_Insert() override {};
};

#endif
