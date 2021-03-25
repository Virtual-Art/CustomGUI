#ifndef NUMBERPRINTER
#define NUMBERPRINTER

#include <iostream>
#include "PageGroupItem.h"

#define GROUP_DESCRIPTION 0
#define GROUP_PRINT 1

using namespace std;

class NumberPrinter : public PageGroupItem
{
public: 

	NumberPrinterData CurrentNumberPrinter;
	string Empty = "";

	NumberPrinter() {};
	NumberPrinter(llBookData* llBook);
	NumberPrinter(llBookData* llBook, llPageItemData* llPageItem, NumberPrinterData NumberPrinter);
	NumberPrinter(llPageItemData* llPageItem);

	void llInit(llBookData* llBook, llPageItemData* llPageItem, NumberPrinterData NumberPrinter);

	//Creation Functions
	void CreateNumber();
	void CreateString();
	void CreateInt();
	void CreateFloat();
	void CreateDouble();
	void CreateVec2();
	void CreateVec3();
	void CreateVec4();

	//Update Functions
	void llUpdate();
	void ReplaceVec2();
	void ReplaceString();

	void HighlightDescription(glm::vec4 Color);
	void HighlightDescriptionOff();

	//Set NumberPrinter Pointers
	void SetVec2(const glm::vec2& vec2);
	void SetString(const string& NewString);
	void SetInt(const int& Int);

	//Change NumberPrinterPointers
	void ChangeVec2(glm::vec2* NewVec2);
	void ChangeString(string* NewString);

	string& GetCurrentString();


	//void ReplaceString() {};           //INCOMPLETE
	void SetString(string* String) {}; //INCOMPLETE

	void Add_Default() override {};
	void Add_Insert() override {};


private:

	void ProcessDescriptionHighlight(llShapeGroupData* DescriptionGroup);

};

#endif
