#ifndef DROPDOWNLIST
#define DROPDOWNLIST

#include <iostream>
#include "PageGroupItem.h"


using namespace std;

struct DropDownListData
{
	string Description = "Drop Down";
	string* StringList;
	int ListCount;
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

	//void ClickToggle();


	//Reference Functions
	//void Add_Default() override;
	//void Add_Duplicate() override;
	//void Add_Insert() override;

};

#endif

