#include "PageGroupGrid.h"

PageGroupGrid::PageGroupGrid(llBookData* llBook, llPageData* Page, llPageGroupData* PageGroup_Template, PageGroupGridData PageGroupGrid, ShaderProgram* ShaderProgram, RawTexture* Texture0, RawTexture* Texture1, RawTexture* Texture2)
  : NewPage(llBook, Page, ShaderProgram, Texture0, Texture1, Texture2)
{
	CurrentGrid = PageGroupGrid;
	Grid_Template = PageGroup_Template;
	CurrentPlacement = &PageGroup::PlaceRight;
	AddPageGroupGrid();
}

void PageGroupGrid::llInit(llBookData* llBook, llPageData* Page, llPageGroupData* PageGroup_Template, PageGroupGridData PageGroupGrid, ShaderProgram* ShaderProgram, RawTexture* Texture0, RawTexture* Texture1, RawTexture* Texture2)
{
	llPageInit(llBook, Page, ShaderProgram, Texture0, Texture1, Texture2);
	
	CurrentGrid = PageGroupGrid;
	Grid_Template = PageGroup_Template;
	CurrentPlacement = &PageGroup::PlaceRight;
	AddPageGroupGrid();
}


void PageGroupGrid::AddPageGroupGrid()
{
	if (CurrentllPage == nullptr) { Log::LogString("ERROR::AddPageItemGrid FAILED:: Invalid PageGroup State"); return; }
	if (CurrentGrid.RowCount < 0) { CurrentGrid.RowCount = 0; }
	if (CurrentGrid.ColumnCount < 0) { CurrentGrid.ColumnCount = 0; }

	Log::LogString("---------Adding PageGroup Grid---------");

	//Place out of view
	PageGroup PageGroup_First(Grid_Template);
	PageGroup_First.LoadedBook = LoadedBook;

	PageGroup_First.llSwitch(Grid_Template);
	PageGroup_First.UnHide();
	PageGroup_First.SetllPosition({-30.0, 0.0}, INPUT_LEFT);

	//First One
	llPageGroupData* CurrentPageGroup = PageGroupIntoPage(CurrentllPage, Grid_Template);
	PageGroup_First.llSwitch(CurrentPageGroup);
	PageGroup_First.SetllPosition(CurrentGrid.Position, CurrentGrid.InputType); //Doubling ......?
	CurrentGrid.first_edges = PageGroup_First.GetEdges();
	CurrentGrid.last_edges = CurrentGrid.first_edges;
	PageGroup PageGroup_Current(CurrentPageGroup);
	PageGroup_Current.LoadedBook = LoadedBook;
	First_PageGroup = PageGroup_First.GetData();

	Log::LogString("---------Adding PageGroup Grid FINISHED ---------");

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
	
		//Add if Neccessary
		CurrentPageGroup = PageGroupIntoPage(CurrentllPage, Grid_Template);
		PageGroup_Current.llSwitch(CurrentPageGroup);
		(PageGroup_Current.*CurrentPlacement)(EdgeToUse, MATCH_CENTERS, CurrentGrid.yPadding);
		EdgeToUse = PageGroup_Current.GetEdges();
	
		//New Column
		if (CurrentCount == -1)
		{
			LastColumnOrRowEdges = EdgeToUse;
		}
	
		CurrentCount++;
	}
	
	//Provide at least one page item hide if none required
	if (CurrentGrid.ResultCount == 0) { PageGroup_First.Hide(); }
}
void PageGroupGrid::ReplacePageGroupGrid()
{
	if (CurrentllPage == nullptr) { Log::LogString("ERROR::ReplacePageItemGrid FAILED:: Invalid PageGroup State"); return; }
	if (CurrentGrid.RowCount < 0) { CurrentGrid.RowCount = 0; }
	if (CurrentGrid.ColumnCount < 0) { CurrentGrid.ColumnCount = 0; }

	//Make Sure Reference is Visible or it can ruin things
	PageGroup PageGroup_First(Grid_Template);
	PageGroup_First.LoadedBook = LoadedBook;
	PageGroup_First.llSwitch(Grid_Template);
	PageGroup_First.UnHide();

	//First One
	llPageGroupData* Current_PageGroup = CurrentllPage->PageGroup;
	PageGroup_First.llSwitch(Current_PageGroup);
	PageGroup_First.SetllPosition({0.0, 0.0}, INPUT_CENTER); //Doubling ......?
	PageGroup_First.UnHide();
	CurrentGrid.first_edges = PageGroup_First.GetEdges();
	CurrentGrid.last_edges = CurrentGrid.first_edges;
	PageGroup PageItem_Current(Current_PageGroup);
	PageItem_Current.LoadedBook = LoadedBook;

	Current_PageGroup = Current_PageGroup->Next;

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
		if (Current_PageGroup != nullptr)
		{
			PageItem_Current.llSwitch(Current_PageGroup);
			(PageItem_Current.*CurrentPlacement)(EdgeToUse, MATCH_CENTERS, CurrentGrid.yPadding);
			PageItem_Current.UnHide();
			EdgeToUse = PageItem_Current.GetEdges();

			//New Row
			if (CurrentCount == -1)
			{
				LastColumnOrRowEdges = EdgeToUse;
			}
		}

		//Add if Neccessary
		if (Current_PageGroup == nullptr)
		{
			Current_PageGroup = PageGroupIntoPage(CurrentllPage, Grid_Template);
			PageItem_Current.llSwitch(Current_PageGroup);
			(PageItem_Current.*CurrentPlacement)(EdgeToUse, MATCH_CENTERS, CurrentGrid.yPadding);
			EdgeToUse = PageItem_Current.GetEdges();

			//New Column
			if (CurrentCount == -1)
			{
				LastColumnOrRowEdges = EdgeToUse;
			}
		}

		//Next PageItem
		if (Current_PageGroup != nullptr) { Current_PageGroup = Current_PageGroup->Next; }
		CurrentCount++;
	}

	//Hide if Neccessary
	while (Current_PageGroup != nullptr)
	{
		PageItem_Current.llSwitch(Current_PageGroup);
		PageItem_Current.Hide();
		Current_PageGroup = Current_PageGroup->Next;
	}

	//Provide at least one page item hide if none required
	if (CurrentGrid.ResultCount == 0) { PageGroup_First.Hide(); }
}

void PageGroupGrid::llUpdate()
{
	ReplacePageGroupGrid();
	//SetllMouseAccess();
}

void PageGroupGrid::SetResultCount(int NewResultCount)
{
	if (CurrentllPage == nullptr) { Log::LogString("ERROR::SetResultCount FAILED:: Invalid Page State"); return; }
	if (CurrentGrid.ColumnCount > 0 && CurrentGrid.RowCount > 0) { Log::LogString("WARNING:: Grid SetResultCount BYPASSED:: Column and Row has a restricted count"); return; }

	CurrentGrid.ResultCount = NewResultCount;

	llUpdate();
}
void PageGroupGrid::SetColumnRow(int ColumnCount, int RowCount)
{
	if (CurrentllPage == nullptr) { Log::LogString("ERROR::SetColumnRow FAILED:: Invalid PageGroup State"); return; }
	if (CurrentGrid.ColumnCount > 0 && CurrentGrid.RowCount > 0) { CurrentGrid.ResultCount = CurrentGrid.ColumnCount * CurrentGrid.RowCount; }

	CurrentGrid.ColumnCount = ColumnCount;
	CurrentGrid.RowCount = RowCount;

	llUpdate();
}

llPageGroupData* PageGroupGrid::GetFirst()
{
	return First_PageGroup;
}

int PageGroupGrid::SetPlacementDirection()
{
	Log::LogString("Setting Placement Direction");

	//auto generated lines going towards right
	if (CurrentGrid.RowCount > 0 && CurrentGrid.ColumnCount == 0) //if Rows is > 0
	{
		CurrentPlacement = &PageGroup::PlaceBelow;
		CurrentMatchType = CurrentGrid.xMatchType;
		CurrentPadding = CurrentGrid.xPadding;
		if (CurrentGrid.RowCount == 1)
		{
			CurrentPlacement = &PageGroup::PlaceRight; return NEVER_SWITCH;
			CurrentMatchType = CurrentGrid.yMatchType;
			CurrentPadding = CurrentGrid.yPadding;
		}
		return CurrentGrid.RowCount;
	}

	//auto generated lines going towards bottom
	if (CurrentGrid.ColumnCount > 0 && CurrentGrid.RowCount == 0) // if Columns is greater than 0
	{
		CurrentPlacement = &PageGroup::PlaceRight;
		CurrentMatchType = CurrentGrid.yMatchType;
		CurrentPadding = CurrentGrid.yPadding;
		if (CurrentGrid.ColumnCount == 1)
		{
			CurrentPlacement = &PageGroup::PlaceBelow;  return NEVER_SWITCH;
			CurrentMatchType = CurrentGrid.xMatchType;
			CurrentPadding = CurrentGrid.xPadding;

		}
		return CurrentGrid.ColumnCount;
	}

	//Direct Grid
	if (CurrentGrid.RowCount > 0 && CurrentGrid.ColumnCount > 0) //if row and column > 0
	{
		Log::LogString("Setting Result Count");
		CurrentPlacement = &PageGroup::PlaceBelow;
		CurrentMatchType = CurrentGrid.xMatchType;
		CurrentPadding = CurrentGrid.xPadding;
		CurrentGrid.ResultCount = CurrentGrid.ColumnCount * CurrentGrid.RowCount;
		return CurrentGrid.ColumnCount;
	}
}
void PageGroupGrid::SwapPlacementDirection()
{
	//float F = 1.0;
	//EX: static_cast<int> (F)
	if (CurrentPlacement == static_cast<void(PageGroup::*)(const glm::vec4&, int, int)> (&PageGroup::PlaceBelow))
	{
		CurrentPlacement = &PageGroup::PlaceRight;
		CurrentMatchType = CurrentGrid.yMatchType;
		CurrentPadding = CurrentGrid.yPadding;
	}
	else
	{
		CurrentPlacement = &PageGroup::PlaceBelow;
		CurrentMatchType = CurrentGrid.xMatchType;
		CurrentPadding = CurrentGrid.xPadding;
	}
}