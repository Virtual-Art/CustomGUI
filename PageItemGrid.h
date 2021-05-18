#ifndef PAGEITEMGRID
#define PAGEITEMGRID

#include <iostream>
#include "PageGroup.h"

namespace PageItemGridActions
{
	static llBookData* CurrentBook;

	//void Prepare(llBookData* Current_Book); //Sets Pointers to Master Element So that it can use Master Element's Objects
	//void HighlightSelectee(); //Selector has Selectees, Highlight Selectee Selected
}

struct PageItemGridData
{
	int ResultCount = 1;
	glm::vec2 ColumnsRows;
	bool AutoRows = true;
	bool AutoColumns = false;
	int xPadding = 10;
	int yPadding = 10;
	glm::vec4 last_edges;        //(Object) Graphic Reference for the form filler to position with
	glm::vec4 first_edges;        //(Object) Graphic Reference for the form filler to position with
	bool first;
};


typedef void(PageGroupItem::*PlacementFunction)(const glm::vec4&, int , int );

//NOTES: SetPosition Works but only as Input Top
//Work Around: You can use the base class "PageGroup" and input the grid data and it will work that way
class PageItemGrid : public PageGroup
{

public:

	PageItemGridData CurrentGrid;
	llPageItemData* Grid_Template;
	Button Button_Selector;

	PlacementFunction CurrentPlacement;

	//+-----------------------+//
	//PageItemGrid() {};
	//PageItemGrid(llBookData* llBookData);
	PageItemGrid(llBookData* llBookData,llPageGroupData* PageGroupData, llPageItemData* PageItem_Template, PageItemGridData& SelectorData);
	//PageItemGrid(llPageItemData* PageItemData);
	//
	//void llInit(llBookData* llBook, llPageGroupData* llPageGroup, llPageItemData* llPageItem, PageItemGrid& SearchBarData);
	//void llSwitch(llPageGroupData* PageGroup) override;
	//
	void AddPageItemGrid();
	void ReplacePageItemGrid();

	void SetResultCount(int NewResultCount);
	void llUpdate() override;
	//+-----------------------+//

private:

	void SwapPlacementDirection();

};

#endif