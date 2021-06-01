#include "PageItemGrid.h"


PageItemGrid::PageItemGrid(llBookData* llBookData, llPageGroupData* PageGroupData, llPageItemData* PageItem_Template, PageItemGridData& PageItemGrid)
	:PageGroup(llBookData, PageGroupData)
{
	CurrentllPageGroup->Type = TYPE_PAGEGROUP_PAGEITEMGRID;
	CurrentllPageGroup->PageItemGridData = PageItemGrid;
	CurrentGrid = &CurrentllPageGroup->PageItemGridData;
	Grid_Template = PageItem_Template;
	CurrentllPageGroup->PageItem_Template = PageItem_Template;
	CurrentPlacement = &PageGroupItem::PlaceRight;
	AddPageItemGrid();
}

PageItemGrid::PageItemGrid(llPageGroupData* PageGroupData)
	:PageGroup(PageGroupData)
{
	CurrentGrid = &PageGroupData->PageItemGridData;
	Grid_Template = PageGroupData->PageItem_Template;
	CurrentPlacement = &PageGroupItem::PlaceRight;
}

void PageItemGrid::llInit(llBookData* llBook, llPageGroupData* llPageGroup, llPageItemData* llPageItem, PageItemGridData& GridData)
{
	llPageGroupInit(llBook, llPageGroup);
	CurrentllPageGroup->PageItemGridData = GridData;
	CurrentGrid = &CurrentllPageGroup->PageItemGridData;
	CurrentllPageGroup->PageItem_Template = llPageItem;
	Grid_Template = llPageItem;
	CurrentllPageGroup->Type = TYPE_PAGEGROUP_PAGEITEMGRID;
	CurrentPlacement = &PageGroupItem::PlaceRight;
	AddPageItemGrid();
}

void PageItemGrid::llSwitch(llPageGroupData* PageGroup)
{
	//If it exists
	if (PageGroup != nullptr && PageGroup->PageItem != nullptr)
	{
		CurrentllPageGroup = PageGroup;
		CurrentGrid = &PageGroup->PageItemGridData;
		Grid_Template = PageGroup->PageItem_Template;
		CurrentPlacement = &PageGroupItem::PlaceRight;
	}
	else
	{
		Log::LogString("ERROR:: PageItemGrid Switch FAILED:: No PageGroup Provided");
	}
}


//Working in terms of the book and data
void PageItemGrid::AddPageItemGrid()
{
	//Validate
	if (CurrentllPageGroup == nullptr) { Log::LogString("ERROR::AddPageItemGrid FAILED:: Invalid PageGroup State"); return; }
	if (CurrentGrid->RowCount < 0) { CurrentGrid->RowCount = 0; }
	if (CurrentGrid->ColumnCount < 0) { CurrentGrid->ColumnCount = 0; }

	//Place Copy Out Of View
	PageGroupItem PageItem_First(Grid_Template);
	PageItem_First.LoadedBook = LoadedBook;
	PageItem_First.llSwitch(Grid_Template);
	PageItem_First.UnHide();
	PageItem_First.SetllPosition({ -30.0, 0.0 });

	//Title Group
	PageGroupItem Description(LoadedBook);
	TextData TextData_Template;
	TextData_Template.Phrase = CurrentGrid->Description;
	llShapeGroupData ShapeGroup_Template;
	ShapeGroup_Template.Color = CurrentGrid->DescriptionColor;
	Text Text_Description(LoadedBook, &ShapeGroup_Template, TextData_Template);

	//First Grid PageItem
	llPageItemData* CurrentPageItem = PageItemIntoPageGroup(CurrentllPageGroup, Grid_Template);
	PageItem_First.llSwitch(CurrentPageItem);
	PageItem_First.SetllPosition(CurrentllPageGroup->Position, CurrentllPageGroup->InputType); //Doubling ......?
	CurrentGrid->first_edges = PageItem_First.GetEdges();
	CurrentGrid->last_edges = CurrentGrid->first_edges;
	PageGroupItem PageItem_Current(CurrentPageItem);
	PageItem_Current.LoadedBook = LoadedBook;

	Text_Description.PlaceAbove(PageItem_First.GetEdgesWithBackGround(), CurrentGrid->DescriptionMatchType, CurrentGrid->DescriptionyPadding);

	/////////////////////
	glm::vec4 LastColumnOrRowEdges = CurrentGrid->last_edges;
	glm::vec4 EdgeToUse = CurrentGrid->last_edges;
	int SwapCount;
	int CurrentCount = 1;

	SwapCount = SetPlacementDirection();

	//Loop through Result Count and add a PageItem to the grid
	for (int i = 0; i < (CurrentGrid->ResultCount - 1); i++)
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

		//Add if Neccessary
		CurrentPageItem = PageItemIntoPageGroup(CurrentllPageGroup, Grid_Template);
		PageItem_Current.llSwitch(CurrentPageItem);
		(PageItem_Current.*CurrentPlacement)(EdgeToUse, MATCH_CENTERS, CurrentPadding);
		EdgeToUse = PageItem_Current.GetEdgesWithBackGround();

		//New Column
		if (CurrentCount == -1)
		{
			LastColumnOrRowEdges = EdgeToUse;
		}

		CurrentCount++;
	}

	//Provide at least one page item hide if none required
	if (CurrentGrid->ResultCount == 0) { PageItem_First.Hide(); }
}

void PageItemGrid::ReplacePageItemGrid()
{
	if (CurrentllPageGroup == nullptr) { Log::LogString("ERROR::ReplacePageItemGrid FAILED:: Invalid PageGroup State"); return; }
	if (CurrentGrid->RowCount < 0) { CurrentGrid->RowCount = 0; }
	if (CurrentGrid->ColumnCount < 0) { CurrentGrid->ColumnCount = 0; }

	//Make Sure Reference is Visible or it can ruin things
	PageGroupItem PageItem_First(Grid_Template);
	PageItem_First.LoadedBook = LoadedBook;
	PageItem_First.llSwitch(Grid_Template);
	PageItem_First.UnHide();

	llPageItemData* Current_PageItem = HeadPageItem(CurrentllPageGroup->PageItem);
	llShapeGroupData* Current_ShapeGroup = HeadShapeGroup(Current_PageItem->ShapeGroup);
	Text Text_Description(Current_ShapeGroup);
	Text_Description.LoadedBook = LoadedBook;
	Text_Description.llSwitch(Current_ShapeGroup);
	Current_ShapeGroup->Color = CurrentGrid->DescriptionColor;
	Text_Description.SetllText(CurrentGrid->Description);

	//First One
	Current_PageItem = Current_PageItem->Next;
	PageItem_First.llSwitch(Current_PageItem);
	PageItem_First.SetllPosition(CurrentllPageGroup->Position, CurrentllPageGroup->InputType); //Doubling ......?
	PageItem_First.UnHide();
	CurrentGrid->first_edges = PageItem_First.GetEdgesWithBackGround();
	CurrentGrid->last_edges = CurrentGrid->first_edges;
	PageGroupItem PageItem_Current(Current_PageItem);
	PageItem_Current.LoadedBook = LoadedBook;

	Current_PageItem = Current_PageItem->Next;

	glm::vec4 LastColumnOrRowEdges = CurrentGrid->last_edges;
	glm::vec4 EdgeToUse = CurrentGrid->last_edges;
	int SwapCount;
	int CurrentCount = 1;

	SwapCount = SetPlacementDirection();

	//Display Grid
	for (int i = 0; i < (CurrentGrid->ResultCount - 1); i++)
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
			(PageItem_Current.*CurrentPlacement)(EdgeToUse, MATCH_CENTERS, CurrentPadding);
			PageItem_Current.UnHide();
			EdgeToUse = PageItem_Current.GetEdgesWithBackGround();

			//New Row
			if (CurrentCount == -1)
			{
				LastColumnOrRowEdges = EdgeToUse;
			}
		}

		Log::LogString("Looping");

		//Add if Neccessary
		if (Current_PageItem == nullptr)
		{
			Current_PageItem = PageItemIntoPageGroup(CurrentllPageGroup, Grid_Template);
			PageItem_Current.llSwitch(Current_PageItem);
			(PageItem_Current.*CurrentPlacement)(EdgeToUse, MATCH_CENTERS, CurrentPadding);
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

	//Provide at least one page item hide if none required
	if (CurrentGrid->ResultCount == 0) { PageItem_First.Hide(); }
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
		CurrentMatchType = CurrentGrid->yMatchType;
		CurrentPadding = CurrentGrid->yPadding;
		Log::LogString("Swapped to Right");
	}
	else
	{
		CurrentPlacement = &PageGroupItem::PlaceBelow;
		CurrentMatchType = CurrentGrid->xMatchType;
		CurrentPadding = CurrentGrid->xPadding;
		Log::LogString("Swapped to Below");
	}
}

void PageItemGrid::SetResultCount(int NewResultCount)
{
	if (CurrentllPageGroup == nullptr) { Log::LogString("ERROR::SetResultCount FAILED:: Invalid PageGroup State"); return; }
	if (CurrentGrid->ColumnCount > 0 && CurrentGrid->RowCount > 0) { Log::LogString("WARNING:: Grid SetResultCount BYPASSED:: Column and Row has a restricted count"); return; }

	CurrentGrid->ResultCount = NewResultCount;

	llUpdate();
}

void PageItemGrid::SetColumnRow(int ColumnCount, int RowCount)
{
	if (CurrentllPageGroup == nullptr) { Log::LogString("ERROR::SetColumnRow FAILED:: Invalid PageGroup State"); return; }
	if (CurrentGrid->ColumnCount > 0 && CurrentGrid->RowCount > 0) { CurrentGrid->ResultCount = CurrentGrid->ColumnCount * CurrentGrid->RowCount; }

	CurrentGrid->ColumnCount = ColumnCount;
	CurrentGrid->RowCount = RowCount;

	llUpdate();
}

void PageItemGrid::SetDescription(const string& Description)
{
	if (CurrentllPageGroup == nullptr) { Log::LogString("ERROR::SetDescription FAILED:: Invalid PageGroup State"); return; }

	CurrentGrid->Description = Description;
	llUpdate();
}

llPageItemData* PageItemGrid::GetFirst()
{
	return HeadPageItem(CurrentllPageGroup->PageItem)->Next;
}

int PageItemGrid::SetPlacementDirection()
{
	Log::LogString("Setting Placement Direction");

	//auto generated lines going towards right
	if (CurrentGrid->RowCount > 0 && CurrentGrid->ColumnCount == 0) //if Rows is > 0
	{
		CurrentPlacement = &PageGroupItem::PlaceBelow;
		CurrentMatchType = CurrentGrid->xMatchType;
		CurrentPadding = CurrentGrid->xPadding;
		if (CurrentGrid->RowCount == 1) 
		{ 
			CurrentPlacement = &PageGroupItem::PlaceRight; return NEVER_SWITCH; 
			CurrentMatchType = CurrentGrid->yMatchType;
			CurrentPadding = CurrentGrid->yPadding;
		}
		return CurrentGrid->RowCount;
	}

	//auto generated lines going towards bottom
	if (CurrentGrid->ColumnCount > 0 && CurrentGrid->RowCount == 0) // if Columns is greater than 0
	{
		CurrentPlacement = &PageGroupItem::PlaceRight;
		CurrentMatchType = CurrentGrid->yMatchType;
		CurrentPadding = CurrentGrid->yPadding;
		if (CurrentGrid->ColumnCount == 1) 
		{
			CurrentPlacement = &PageGroupItem::PlaceBelow;  return NEVER_SWITCH; 
			CurrentMatchType = CurrentGrid->xMatchType;
			CurrentPadding = CurrentGrid->xPadding;
		}
		return CurrentGrid->ColumnCount;
	}

	//Direct Grid
	if (CurrentGrid->RowCount > 0  && CurrentGrid->ColumnCount > 0) //if row and column > 0
	{
		Log::LogString("Setting Result Count");
		CurrentPlacement = &PageGroupItem::PlaceBelow;
		CurrentMatchType = CurrentGrid->xMatchType;
		CurrentPadding = CurrentGrid->xPadding;
		CurrentGrid->ResultCount = CurrentGrid->ColumnCount * CurrentGrid->RowCount;
		return CurrentGrid->ColumnCount;
	}
}