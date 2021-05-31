#ifndef PAGEITEMGRID
#define PAGEITEMGRID

#include <iostream>
#include "PageGroup.h"


#define MIN_COLUMN 0 
#define MIN_ROW 0 
#define NEVER_SWITCH -2


namespace PageItemGridActions
{
	static llBookData* CurrentBook;

	//void Prepare(llBookData* Current_Book); //Sets Pointers to Master Element So that it can use Master Element's Objects
	//void HighlightSelectee(); //Selector has Selectees, Highlight Selectee Selected
}


typedef void(PageGroupItem::*PlacementFunction)(const glm::vec4&, int , int );

//NOTES: SetPosition Works but only as Input Top
//Work Around: You can use the base class "PageGroup" and input the grid data and it will work that way
class PageItemGrid : public PageGroup
{

public:

	PageItemGridData* CurrentGrid;
	llPageItemData* Grid_Template;
	Button Button_Selector;

	PlacementFunction CurrentPlacement;

	//+-----------------------+//
	PageItemGrid() {};
	//PageItemGrid(llBookData* llBookData);
	PageItemGrid(llBookData* llBookData,llPageGroupData* PageGroupData, llPageItemData* PageItem_Template, PageItemGridData& SelectorData);
	PageItemGrid(llPageGroupData* PageGroupData);
	//
	void llInit(llBookData* llBook, llPageGroupData* llPageGroup, llPageItemData* llPageItem, PageItemGridData& GridData);
	//void llSwitch(llPageGroupData* PageGroup) override;
	//
	void AddPageItemGrid();
	void ReplacePageItemGrid();

	void SetResultCount(int NewResultCount);
	void SetColumnRow(int Column, int Row);
	void SetDescription(const string& Description);
	llPageItemData* GetFirst();
	void llUpdate() override;
	//+-----------------------+//

private:

	int CurrentMatchType;
	int CurrentPadding;
	int SetPlacementDirection();
	void SwapPlacementDirection();

};

#endif