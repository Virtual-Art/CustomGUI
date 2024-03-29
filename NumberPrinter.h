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
	Button Button_NumberPrinter;

	NumberPrinter() {};
	NumberPrinter(llBookData* llBook);
	NumberPrinter(llBookData* llBook, llPageItemData* llPageItem, NumberPrinterData NumberPrinter);
	NumberPrinter(llPageItemData* llPageItem);

	void llInit(llBookData* llBook, llPageItemData* llPageItem, NumberPrinterData NumberPrinter);
	void llSwitch(llPageItemData* PageItem) override;

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
	void ReplaceFloat();
	void ReplaceInteger();
	void ReplaceString();

	void HighlightDescription(glm::vec4 Color);
	void HighlightDescriptionOff();

	//Set NumberPrinter Pointers
	void SetVec2(const glm::vec2& vec2);
	void SetString(const string& NewString);
	void SetInt(const int& Integer);
	void SetFloat(const float& Float);

	//Change NumberPrinterPointers
	void ChangeVec2(glm::vec2* NewVec2);
	void ChangeString(string NewString);
	void ChangeFloat(string NewFloat);
	string Get_Float_As_String();

	//KeyBoard Input Functions
	void Set_With_Keyboard(string CurrentText);
	string Get_For_Keyboard();


	string& GetCurrentString();


	//void ReplaceString() {};           //INCOMPLETE
	void SetString(string* String) {}; //INCOMPLETE

	void Add_Default() override {};
	void Add_Insert() override {};
		
	//Set to ShapeGroup
	void SetKeyBoardInputFunction(Button* Button, ButtonFunction SetFunction);

private:

	string ProcessDecimalPlace(string& Reference_String, bool DollarSign);
	void ProcessDescriptionHighlight(llShapeGroupData* DescriptionGroup);
	glm::vec2 ProcessAnswerPlacement(Text* Text_Reference);

};

namespace NumberPrinterActions
{
	static llBookData* CurrentBook;
	static NumberPrinter CurrentPrinter;
	static ButtonFunction RunningFunction;
	static KeyResult& Keyboard_State = Keyboard::GetState();

	void Prepare(llBookData* Book);
	void SetKeyboardInput();
	void Update(); //Updates the NumberPrinter for input
	void Stop();
	void Run();
	void Empty();

}

#endif
