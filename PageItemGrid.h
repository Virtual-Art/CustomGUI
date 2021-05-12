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
	glm::vec2 ColumnsRows;
	bool AutoRows = false;
	bool AutoColumns = false;
	glm::vec4 last_ordered_dish_edges;        //(Object) Graphic Reference for the form filler to position with
	glm::vec4 first_ordered_dish_edges;        //(Object) Graphic Reference for the form filler to position with
	bool first_ordered_dish;
	void* First_Ordered_Dish_Graphic;	  //llPageItemData
	void* Ordered_Dish_Selected;          //llPageItemData
};

class PageItemGrid : public PageGroup
{

public:

	PageItemGridData CurrentPageItemGrid;
	Button Button_Selector;

	//+-----------------------+//
	//PageItemGrid() {};
	//PageItemGrid(llBookData* llBookData);
	//PageItemGrid(llBookData* llBookData, llPageItemData* PageItemData, SelectorData& SelectorData);
	//PageItemGrid(llPageItemData* PageItemData);
	//
	//void llInit(llBookData* llBook, llPageGroupData* llPageGroup, llPageItemData* llPageItem, PageItemGrid& SearchBarData);
	//void llSwitch(llPageGroupData* PageGroup) override;
	//
	//void AddPageItemGrid();
	//void ReplacePageItemGrid();
	//void llUpdate() override;
	//+-----------------------+//


};

#endif