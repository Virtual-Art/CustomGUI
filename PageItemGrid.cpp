#include "PageItemGrid.h"


PageItemGrid::PageItemGrid(llBookData* llBookData, llPageGroupData* PageGroupData, llPageItemData* PageItem_Template, PageItemGridData& PageItemGrid)
	:PageGroup(llBookData, PageGroupData)
{
	CurrentllPageGroup->Type = TYPE_PAGEGROUP_PAGEITEMGRID;
	CurrentGrid = PageItemGrid;
	Grid_Template = PageItem_Template;
	CurrentPlacement = &PageGroupItem::PlaceRight;
	AddPageItemGrid();
}

void PageItemGrid::llInit(llBookData* llBook, llPageGroupData* llPageGroup, llPageItemData* llPageItem, PageItemGridData& GridData)
{
	llPageGroupInit(llBook, llPageGroup);
	CurrentllPageGroup->Type = TYPE_PAGEGROUP_PAGEITEMGRID;
	CurrentGrid = GridData;
	Grid_Template = llPageItem;
	CurrentPlacement = &PageGroupItem::PlaceRight;
	AddPageItemGrid();
}


//Working in terms of the book and data
void PageItemGrid::AddPageItemGrid()
{
	if (CurrentllPageGroup == nullptr) { Log::LogString("ERROR::AddPageItemGrid FAILED:: Invalid PageGroup State"); return; }
	if (CurrentGrid.RowCount < 0) { CurrentGrid.RowCount = 0; }
	if (CurrentGrid.ColumnCount < 0) { CurrentGrid.ColumnCount = 0; }

	//Place out of view
	PageGroupItem PageItem_First(Grid_Template);
	PageItem_First.LoadedBook = LoadedBook;
	PageItem_First.llSwitch(Grid_Template);
	PageItem_First.UnHide();
	PageItem_First.SetllPosition({ -3.0, 0.0 });

	//First One
	llPageItemData* CurrentPageItem = PageItemIntoPageGroup(CurrentllPageGroup, Grid_Template);
	PageItem_First.llSwitch(CurrentPageItem);
	PageItem_First.SetllPosition(CurrentllPageGroup->Position, CurrentllPageGroup->InputType); //Doubling ......?
	CurrentGrid.first_edges = PageItem_First.GetEdges();
	CurrentGrid.last_edges = CurrentGrid.first_edges;
	PageGroupItem PageItem_Current(CurrentPageItem);
	PageItem_Current.LoadedBook = LoadedBook;

	//Provide at least one page item hide if none required
	if (CurrentGrid.ResultCount == 0) {PageItem_First.Hide();}

	/////////////////////
	glm::vec4 LastColumnOrRowEdges = CurrentGrid.last_edges;
	glm::vec4 EdgeToUse = CurrentGrid.last_edges;
	int SwapCount;
	int CurrentCount = 1;

	SwapCount = SetPlacementDirection();

	//Loop through Result Count and add a PageItem to the grid
	for (int i = 0; i < (CurrentGrid.ResultCount - 1); i++)
	{
		// Stop Typing, it's time for a new line
		if (CurrentCount == SwapCount)
		{
			SwapPlacementDirection(); // Iteration j
			CurrentCount = -1;
			EdgeToUse = LastColumnOrRowEdges; //First Column
		}

		//We are on a new line, it's time to go back to typing
		if (CurrentCount == 0) // 0
		{
			SwapPlacementDirection(); // Iteration  after j
			CurrentCount = 1;
		}
		///////////////////////////
		//Add a PageItem
		//CurrentPageItem = PageItemIntoPageGroup(CurrentllPageGroup, Grid_Template);
		//PageGroupItem PageItem_Current(CurrentPageItem);
		//PageItem_Current.LoadedBook = LoadedBook;
		//PageItem_Current.llSwitch(CurrentPageItem);
		//PageItem_Current.PlaceBelow(CurrentGrid.last_edges, MATCH_CENTERS, CurrentGrid.yPadding);
		//CurrentGrid.last_edges = PageItem_Current.GetEdges();
		////////////////////////////////////////////////
		//Add if Neccessary
		CurrentPageItem = PageItemIntoPageGroup(CurrentllPageGroup, Grid_Template);
		PageItem_Current.llSwitch(CurrentPageItem);
		(PageItem_Current.*CurrentPlacement)(EdgeToUse, MATCH_CENTERS, CurrentGrid.yPadding);
		EdgeToUse = PageItem_Current.GetEdgesWithBackGround();

		//New Column
		if (CurrentCount == -1)
		{
			LastColumnOrRowEdges = EdgeToUse;
		}

		CurrentCount++;
	}
}

void PageItemGrid::ReplacePageItemGrid()
{
	if (CurrentllPageGroup == nullptr) { Log::LogString("ERROR::ReplacePageItemGrid FAILED:: Invalid PageGroup State"); return; }
	if (CurrentGrid.RowCount < 0) { CurrentGrid.RowCount = 0; }
	if (CurrentGrid.ColumnCount < 0) { CurrentGrid.ColumnCount = 0; }

	//Make Sure Reference is Visible or it can ruin things
	PageGroupItem PageItem_First(Grid_Template);
	PageItem_First.LoadedBook = LoadedBook;
	PageItem_First.llSwitch(Grid_Template);
	PageItem_First.UnHide();

	//First One
	llPageItemData* Current_PageItem = HeadPageItem(CurrentllPageGroup->PageItem);
	PageItem_First.llSwitch(Current_PageItem);
	PageItem_First.SetllPosition(CurrentllPageGroup->Position, CurrentllPageGroup->InputType); //Doubling ......?
	PageItem_First.UnHide();
	CurrentGrid.first_edges = PageItem_First.GetEdgesWithBackGround();
	CurrentGrid.last_edges = CurrentGrid.first_edges;
	PageGroupItem PageItem_Current(Current_PageItem);
	PageItem_Current.LoadedBook = LoadedBook;

	Current_PageItem = Current_PageItem->Next;

	glm::vec4 LastColumnOrRowEdges = CurrentGrid.last_edges;
	glm::vec4 EdgeToUse = CurrentGrid.last_edges;
	int SwapCount;
	int CurrentCount = 1;

	SwapCount = SetPlacementDirection();

	//Display Grid
	for (int i = 0; i < (CurrentGrid.ResultCount - 1); i++)
	{
		// Stop Typing, it's time for a new line
		if (CurrentCount == SwapCount) 
		{
			SwapPlacementDirection(); // Iteration j
			CurrentCount = -1;
			EdgeToUse = LastColumnOrRowEdges; //First Column
		}

		//We are on a new line, it's time to go back to typing
		if (CurrentCount == 0) // 0
		{
			SwapPlacementDirection(); // Iteration  after j
			CurrentCount = 1;
		}

		//Update
		if (Current_PageItem != nullptr)
		{
			PageItem_Current.llSwitch(Current_PageItem);
			(PageItem_Current.*CurrentPlacement)(EdgeToUse, MATCH_CENTERS, CurrentGrid.yPadding);
			PageItem_Current.UnHide();
			EdgeToUse = PageItem_Current.GetEdgesWithBackGround();

			//New Row
			if (CurrentCount == -1)
			{
				LastColumnOrRowEdges = EdgeToUse;
			}
		}

		//Add if Neccessary
		if (Current_PageItem == nullptr)
		{
			Current_PageItem = PageItemIntoPageGroup(CurrentllPageGroup, Grid_Template);
			PageItem_Current.llSwitch(Current_PageItem);
			(PageItem_Current.*CurrentPlacement)(EdgeToUse, MATCH_CENTERS, CurrentGrid.yPadding);
			EdgeToUse = PageItem_Current.GetEdgesWithBackGround();

			//New Column
			if (CurrentCount == -1)
			{
				LastColumnOrRowEdges = EdgeToUse;
			}
		}

		//Next PageItem
		if (Current_PageItem != nullptr) { Current_PageItem = Current_PageItem->Next; }
		CurrentCount++;
	}

	//Hide if Neccessary
	while (Current_PageItem != nullptr)
	{
		PageItem_Current.llSwitch(Current_PageItem);
		PageItem_Current.Hide();
		Current_PageItem = Current_PageItem->Next;
	}
}

void PageItemGrid::llUpdate()
{
	ReplacePageItemGrid();
	SetllMouseAccess();
}

void PageItemGrid::SwapPlacementDirection()
{
	//float F = 1.0;
	//EX: static_cast<int> (F)
	if (CurrentPlacement == static_cast<void(PageGroupItem::*)(const glm::vec4&, int, int)> (&PageGroupItem::PlaceBelow))
	{
		CurrentPlacement = &PageGroupItem::PlaceRight;
		Log::LogString("Swapped to Right");
	}
	else
	{
		CurrentPlacement = &PageGroupItem::PlaceBelow;
		Log::LogString("Swapped to Below");
	}
}

void PageItemGrid::SetResultCount(int NewResultCount)
{
	if (CurrentllPageGroup == nullptr) { Log::LogString("ERROR::SetResultCount FAILED:: Invalid PageGroup State"); return; }
	if (CurrentGrid.ColumnCount > 0 && CurrentGrid.RowCount > 0) { Log::LogString("WARNING:: Grid SetResultCount BYPASSED:: Column and Row has a restricted count"); return; }

	CurrentGrid.ResultCount = NewResultCount;

	llUpdate();
}

void PageItemGrid::SetColumnRow(int ColumnCount, int RowCount)
{
	if (CurrentllPageGroup == nullptr) { Log::LogString("ERROR::SetColumnRow FAILED:: Invalid PageGroup State"); return; }
	if (CurrentGrid.ColumnCount > 0 && CurrentGrid.RowCount > 0) { CurrentGrid.ResultCount = CurrentGrid.ColumnCount * CurrentGrid.RowCount; }

	CurrentGrid.ColumnCount = ColumnCount;
	CurrentGrid.RowCount = RowCount;

	llUpdate();
}

llPageItemData* PageItemGrid::GetFirst()
{
	return HeadPageItem(CurrentllPageGroup->PageItem);
}

int PageItemGrid::SetPlacementDirection()
{
	Log::LogString("Setting Placement Direction");

	//auto generated lines going towards right
	if (CurrentGrid.RowCount > 0 && CurrentGrid.ColumnCount == 0) //if Rows is > 0
	{
		CurrentPlacement = &PageGroupItem::PlaceBelow;
		if (CurrentGrid.RowCount == 1) { CurrentPlacement = &PageGroupItem::PlaceRight; return NEVER_SWITCH; }
		return CurrentGrid.RowCount;
	}

	//auto generated lines going towards bottom
	if (CurrentGrid.ColumnCount > 0 && CurrentGrid.RowCount == 0) // if Columns is greater than 0
	{
		CurrentPlacement = &PageGroupItem::PlaceRight;
		if (CurrentGrid.ColumnCount == 1) { CurrentPlacement = &PageGroupItem::PlaceBelow;  return NEVER_SWITCH; }
		return CurrentGrid.ColumnCount;
	}

	//Direct Grid
	if (CurrentGrid.RowCount > 0  && CurrentGrid.ColumnCount > 0) //if row and column > 0
	{
		Log::LogString("Setting Result Count");
		CurrentPlacement = &PageGroupItem::PlaceBelow;
		CurrentGrid.ResultCount = CurrentGrid.ColumnCount * CurrentGrid.RowCount;
		return CurrentGrid.ColumnCount;
	}
}