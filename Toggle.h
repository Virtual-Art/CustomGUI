#ifndef TOGGLE
#define TOGGLE

#include <iostream>
#include "PageGroupItem.h"

#define GROUP_DESCRIPTION 0
#define GROUP_TOGGLE 1

#define TOGGLE 0
#define TOGGLE_BACKGROUND 1

using namespace std;

struct ToggleData
{
	string Description = "Description";
	bool* OnOff;
};

class Toggle : public PageGroupItem
{
public:
	ToggleData CurrentToggleData;

	Toggle() {};
	Toggle(llBookData* llBook);
	Toggle(llBookData* llBook, llPageItemData* llPageItem, ToggleData& ToggleData);
	Toggle(llPageItemData* llPageItem);

	void llToggleInit(llBookData* llBook, llPageItemData* llPageItem, ToggleData NumberPrinter);

	void CreateToggle();
	void llUpdate();
	void llReplaceToggle();

	void ClickToggle();
	

	//Reference Functions
	void Add_Default() override;
	void Add_Duplicate() override;
	void Add_Insert() override;

};

#endif

