#ifndef DROPDOWNLIST
#define DROPDOWNLIST

#include <iostream>
#include "PageGroupItem.h"

#define GROUP_BACKGROUND 0


using namespace std;

struct DropDownListData
{
	string Description = "Drop Down";
	string* StringList;
	int MaxListCount;
	int CurrentListCount = MaxListCount;
	bool Hidden = true;
};

class DropDownList : public PageGroupItem
{
public:
	DropDownListData CurrentDropDownListData;

	DropDownList() {};
	DropDownList(llBookData* llBook);
	DropDownList(llBookData* llBook, llPageItemData* llPageItem, DropDownListData& DropDownListData);
	DropDownList(llPageItemData* llPageItem);

	void llDropDownListInit(llBookData* llBook, llPageItemData* llPageItem, DropDownListData& DropDownListData);

	void CreateDropDownList();
	void llUpdate();
	void llReplaceDropDownList();
	void ToggleShow()
	{
		ToggleToggle(CurrentDropDownListData.Hidden);
		llUpdate();
	}

	void HoverDriver();

	void UpdateDropDownMouseAccess();

	//void ClickToggle();


	//Reference Functions
	//void Add_Default() override;
	//void Add_Duplicate() override;
	//void Add_Insert() override;

private:

	bool HighlightDriver = false;

};

#endif

