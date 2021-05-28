#include "PageGroup.h"

void PageGroup::llInit(llBookData* llBook)
{
	LoadedBook = llBook;
}

PageGroup::PageGroup()
{
	LoadedBook = nullptr;
	CurrentllPageGroup = nullptr;
}

PageGroup::PageGroup(llBookData* llBook)
{
	if (llBook != nullptr)
	{

		if (llBook->Page == nullptr)
		{
			Log::LogString("Book Is Brand New");
			llPageData* CreatedPage = new llPageData;
			llPageGroupData* CreatedPageGroup = new llPageGroupData;

			llBook->Page = CreatedPage;
			llBook->PageHead = CreatedPage;

			llBook->Page->PageGroup = CreatedPageGroup;
			llBook->Page->PageGroupHead = CreatedPageGroup;
		}

		CurrentllPageGroup = new llPageGroupData;
		//Log::LogString("PageItem Created and Shape Group?");

		llPageGroupData* TestingPageGroup = llBook->Page->PageGroup;

		//Completely new object
		if (TestingPageGroup == nullptr)
		{
			//Log::LogString("New PageGroup Linked");
			llBook->Page->PageGroup = CurrentllPageGroup;
			llBook->Page->PageGroupHead = CurrentllPageGroup;
			llBook->Page->PageGroupCount++;
		}
		else //Shapes already created
		{
			llPageGroupData* FoundTail = TestingPageGroup;
			int LinkCount = 0;

			//Find tail then add
			//Log::LogString("Finding Tail..");
			while (FoundTail->Next != nullptr)
			{
				FoundTail = FoundTail->Next;
				LinkCount++;
			}
			//Log::LogString("New PageGroup Linked");
			FoundTail->Next = CurrentllPageGroup;
			CurrentllPageGroup->Previous = FoundTail;
			llBook->Page->PageGroup = CurrentllPageGroup;
			llBook->Page->PageGroupCount++;
		}

		CurrentllPageGroup->Type = TYPE_PAGEGROUP;
		LoadedBook = llBook;
	}
	else
	{
		Log::LogString("ERROR:: PageGroup Constructor FAILED:: No Book Provided");
	}
}

PageGroup::PageGroup(llBookData* llBookData, llPageGroupData* llPageGroup)
{
	//Make sure we are provided with data
	if (llPageGroup != nullptr && llBookData != nullptr)
	{
		//Look at the book, is there a Page in the book? no?
		if (llBookData->Page == nullptr)
		{
			//Create a new Page & PageGroup for the PageItem we are about to create
			//Log::LogString("Book Is Brand New");
			llPageData* CreatedPage = new llPageData;
			llPageGroupData* CreatedPageGroup = new llPageGroupData;

			//Link the Created groups to the book we are looking at
			llBookData->Page = CreatedPage;
			llBookData->PageHead = CreatedPage;

			llBookData->Page->PageGroup = CreatedPageGroup;
			llBookData->Page->PageGroupHead = CreatedPageGroup;
		}

		//Create a new PageItem & Copy the provided data
		CurrentllPageGroup = new llPageGroupData;
		*CurrentllPageGroup = *llPageGroup;
		//Log::LogString("PageItem Created and ShapeGroup Created?");

		//Take a look at the current PageItem in the current PageGroup
		llPageGroupData* TestingPageGroup = llBookData->Page->PageGroup;

		//The book doesn't have a PageItem in the current PageGroup
		if (TestingPageGroup == nullptr)
		{
			//Set the book to include and point to the newly created PageItem
			//Log::LogString("New PageGroup Linked");
			llBookData->Page->PageGroup = CurrentllPageGroup;
			llBookData->Page->PageGroupHead = CurrentllPageGroup;
		}
		else //A Page Item already exists in the current Page Group
		{
			llPageGroupData* FoundTail = TestingPageGroup;
			int LinkCount = 0;

			//Find the last PageItem in the current PageGroup
			//Log::LogString("Finding Tail..");
			while (FoundTail->Next != nullptr)
			{
				FoundTail = FoundTail->Next;
				LinkCount++;
			}

			//When we find the last PageItem in the PageGroup, attach the newly created PageItem next to it and
			//Log::LogString("New PageGroup Linked");
			FoundTail->Next = CurrentllPageGroup;
			CurrentllPageGroup->Previous = FoundTail;

			//Then set the book to point to the new PageItem we created
			llBookData->Page->PageGroup = CurrentllPageGroup;
		}

		CurrentllPageGroup->Type = TYPE_PAGEGROUP;
		LoadedBook = llBookData;
	}
	else
	{
		Log::LogString("ERROR:: PageGroup Constructor FAILED:: No Book or Page Group Provided");
	}
}

void PageGroup::llInit(llBookData* llBookData, llPageGroupData* llPageGroup)
{
	//Make sure we are provided with data
	if (llPageGroup == nullptr) { Log::LogString("ERROR:: PageGroup Init FAILED:: No PageItem Provided ");  return; }
	if (llBookData == nullptr) { Log::LogString("ERROR:: PageGroup Init FAILED:: No Book Provided ");  return; }

	//Look at the book, is there a Page in the book? no?
	if (llBookData->Page == nullptr)
	{
		//Create a new Page & PageGroup for the PageItem we are about to create
		Log::LogString("Book Is Brand New");
		llPageData* CreatedPage = new llPageData;
		llPageGroupData* CreatedPageGroup = new llPageGroupData;

		//Link the Created groups to the book we are looking at
		llBookData->Page = CreatedPage;
		llBookData->PageHead = CreatedPage;

	}

	//Create a new PageItem & Copy the provided data
	CurrentllPageGroup = new llPageGroupData;
	*CurrentllPageGroup = *llPageGroup;
	//Log::LogString("PageItem Created and ShapeGroup Created?");

	//Take a look at the current PageItem in the current PageGroup
	llPageGroupData* TestingPageGroup = llBookData->Page->PageGroup;

	//The book doesn't have a PageItem in the current PageGroup
	if (TestingPageGroup == nullptr)
	{
		//Set the book to include and point to the newly created PageItem
		Log::LogString("Page Empty. First PageGroup!");
		llBookData->Page->PageGroup = CurrentllPageGroup;
		llBookData->Page->PageGroupHead = CurrentllPageGroup;
	}
	else //A Page Item already exists in the current Page Group
	{
		while (TestingPageGroup->Next != nullptr)
		{
			TestingPageGroup = TestingPageGroup->Next;
		}

		//When we find the last PageItem in the PageGroup, attach the newly created PageItem next to it and
		Log::LogString("PageGroup Linked");
		TestingPageGroup->Next = CurrentllPageGroup;
		CurrentllPageGroup->Previous = TestingPageGroup;

		//Then set the book to point to the new PageItem we created
		llBookData->Page->PageGroup = CurrentllPageGroup;
	}

	CurrentllPageGroup->Type = TYPE_PAGEGROUP;
	LoadedBook = llBookData;
	ProcessBackGround();
}

void PageGroup::llPageGroupInit(llBookData* llBookData, llPageGroupData* llPageGroup)
{

//Make sure we are provided with data
if (llPageGroup != nullptr && llBookData != nullptr)
{
	//Look at the book, is there a Page in the book? no?
	if (llBookData->Page == nullptr)
	{
		//Create a new Page & PageGroup for the PageItem we are about to create
		//Log::LogString("Book Is Brand New");
		llPageData* CreatedPage = new llPageData;
		llPageGroupData* CreatedPageGroup = new llPageGroupData;

		//Link the Created groups to the book we are looking at
		llBookData->Page = CreatedPage;
		llBookData->PageHead = CreatedPage;

		llBookData->Page->PageGroup = CreatedPageGroup;
		llBookData->Page->PageGroupHead = CreatedPageGroup;
	}

	//Create a new PageItem & Copy the provided data
	CurrentllPageGroup = new llPageGroupData;
	*CurrentllPageGroup = *llPageGroup;
	//Log::LogString("PageItem Created and ShapeGroup Created?");

	//Take a look at the current PageItem in the current PageGroup
	llPageGroupData* TestingPageGroup = llBookData->Page->PageGroup;

	//The book doesn't have a PageItem in the current PageGroup
	if (TestingPageGroup == nullptr)
	{
		//Set the book to include and point to the newly created PageItem
		//Log::LogString("New PageGroup Linked");
		llBookData->Page->PageGroup = CurrentllPageGroup;
		llBookData->Page->PageGroupHead = CurrentllPageGroup;
	}
	else //A Page Item already exists in the current Page Group
	{
		llPageGroupData* FoundTail = TestingPageGroup;
		int LinkCount = 0;

		//Find the last PageItem in the current PageGroup
		//Log::LogString("Finding Tail..");
		while (FoundTail->Next != nullptr)
		{
			FoundTail = FoundTail->Next;
			LinkCount++;
		}

		//When we find the last PageItem in the PageGroup, attach the newly created PageItem next to it and
		//Log::LogString("New PageGroup Linked");
		FoundTail->Next = CurrentllPageGroup;
		CurrentllPageGroup->Previous = FoundTail;

		//Then set the book to point to the new PageItem we created
		llBookData->Page->PageGroup = CurrentllPageGroup;
	}

	CurrentllPageGroup->Type = TYPE_PAGEGROUP;
	LoadedBook = llBookData;
}
else
{
	Log::LogString("ERROR:: PageGroup Constructor FAILED:: No Book or Page Group Provided");
}
}
//PageItem Provided Ready Pre-Made 
void PageGroup::CreateGrid(llPageItemData* PageItem_Reference, glm::vec2 Colomns_Rows, llBookData* llBookData, int RowSpacing)
{
	//Keep Track of lastest column Page Item
	bool FirstTime = true;
	PageGroupItem PageItem_Copy(PageItem_Reference);
	PageItem_Copy.llSwitch(PageItem_Reference);
	PageItem_Copy.LoadedBook = llBookData;

	glm::vec4 LastRowEdges = PageItem_Copy.GetEdges();
	glm::vec4 LastColumnEdges = PageItem_Copy.GetEdges();

	//Coloums
	for (int i = 0; i < Colomns_Rows[0]; i++)
	{
		if (FirstTime != true)
		{
			//Place in New Column
			PageItem_Copy.Second_Add_Duplicate(llBookData);
			PageItem_Copy.PlaceRight(LastColumnEdges, MATCH_CENTERS, RowSpacing);
			LastColumnEdges = PageItem_Copy.GetEdges();
			LastRowEdges = PageItem_Copy.GetEdges();

		}FirstTime = false;

		//Rows
		for (int i = 0; i < Colomns_Rows[1]; i++)
		{
		//Place in New Row
		PageItem_Copy.Second_Add_Duplicate(llBookData);
		PageItem_Copy.PlaceBelow(LastRowEdges, MATCH_CENTERS, RowSpacing);
		LastRowEdges = PageItem_Copy.GetEdges();
		}

	}

	//SetllMouseAccess();
}

PageGroup::PageGroup(llPageGroupData* llPageGroup)
{
	//If it exists
	if (llPageGroup != nullptr && llPageGroup->PageItem != nullptr)
	{

		CurrentllPageGroup = llPageGroup;
	}
	else
	{
		Log::LogString("ERROR:: PageGroup Constructor FAILED:: No PageGroup Provided");
	}
}

void PageGroup::llSwitch(llPageGroupData* llPageGroup)
{
	//Validate
	if (llPageGroup == nullptr) { Log::LogString("ERROR:: PageGroup Switch FAILED:: No PageGroup Provided ");  return; }

	//Switch
	CurrentllPageGroup = llPageGroup;

}

void PageGroup::Delete()
{
	DeletePageGroup(LoadedBook, CurrentllPageGroup);
}

void PageGroup::Add_Default()
{
	//Validate
    if (LoadedBook == nullptr) { Log::LogString("ERROR:: PageGroup Add_Default Failed:: Invalid Book State"); }

	if (LoadedBook->Page == nullptr)
	{
		Log::LogString("Book Is Brand New");
		llPageData* CreatedPage = new llPageData;
		llPageGroupData* CreatedPageGroup = new llPageGroupData;

		LoadedBook->Page = CreatedPage;
		LoadedBook->PageHead = CreatedPage;

		LoadedBook->Page->PageGroup = CreatedPageGroup;
		LoadedBook->Page->PageGroupHead = CreatedPageGroup;
	}

	CurrentllPageGroup = new llPageGroupData;
	//Log::LogString("PageItem Created and Shape Group?");

	llPageGroupData* TestingPageItem = LoadedBook->Page->PageGroup;

	//Completely new object
	if (TestingPageItem == nullptr)
	{
		Log::LogString("PageGroup Empty. First PageItem!");
		LoadedBook->Page->PageGroup = CurrentllPageGroup;
		LoadedBook->Page->PageGroupHead = CurrentllPageGroup;
	}
	else //Shapes already created
	{
		llPageGroupData* FoundTail = TestingPageItem;
		int LinkCount = 0;

		//Find tail then add
		//Log::LogString("Finding Tail..");
		while (FoundTail->Next != nullptr)
		{
			FoundTail = FoundTail->Next;
			LinkCount++;
		}
		Log::LogString("PageItem Linked");
		FoundTail->Next = CurrentllPageGroup;
		CurrentllPageGroup->Previous = FoundTail;
		LoadedBook->Page->PageGroup = CurrentllPageGroup;
	}

	CurrentllPageGroup->Type = TYPE_PAGEGROUP;
}

void PageGroup::HighlightPageGroup(glm::vec4 HighlightColor)
{
	//Validate
	if (CurrentllPageGroup == nullptr) { Log::LogString("ERROR:: PageGroup Highlight FAILED:: Invalid PageGroup State ");  return; }

	CurrentllPageGroup->HighlightColor = HighlightColor;
	CurrentllPageGroup->Highlighted = true;
	llUpdate();
}

void PageGroup::HighlightOff()
{
	//Validate
	if (CurrentllPageGroup == nullptr) { Log::LogString("ERROR:: PageGroup Highlight Off FAILED:: Invalid PageGroup State ");  return; }

	CurrentllPageGroup->Highlighted = false;
	llUpdate();
}


void PageGroup::ProcessBackGround()
{
	if (CurrentllPageGroup == nullptr) { return; }
	
	if (CurrentllPageGroup->BackGround == true)
	{
		//Quad Quad_Reference(LoadedBook);
		//Quad_Reference.SetColor(CurrentllPageGroup->BackGroundColor);
	}
}

void PageGroup::SetBackGround()
{
	if (CurrentllPageGroup == nullptr) { return; }

	if (CurrentllPageGroup->BackGround == true)
	{
		//Go to PageGroup BackGround Address
		llPageItemData* BackGround_PageItem = CurrentllPageGroup->PageItem;
		BackGround_PageItem = HeadPageItem(BackGround_PageItem);
		if (BackGround_PageItem->ShapeGroup == nullptr) { return; }
		llShapeGroupData* ShapeGroup_BackGround = HeadShapeGroup(BackGround_PageItem->ShapeGroup);
		if (BackGround_PageItem->ShapeGroup->Shape == nullptr) { return; }
		llShapeData* BackGround = HeadShape(ShapeGroup_BackGround->Shape);
		/////////////////////////////////////////////////////////////

		Quad Quad_Reference(BackGround);
		Quad_Reference.llSwitch(BackGround);
		Quad_Reference.LoadedBook = LoadedBook;
		BackGround->Size[X_AXIS] = CurrentllPageGroup->Size[X_AXIS] + ((CurrentllPageGroup->BackGroundPadding[PADDING_LEFT] + CurrentllPageGroup->BackGroundPadding[PADDING_RIGHT]) * PIXEL);
		BackGround->Size[Y_AXIS] = CurrentllPageGroup->Size[Y_AXIS] + ((CurrentllPageGroup->BackGroundPadding[PADDING_TOP] + CurrentllPageGroup->BackGroundPadding[PADDING_BOTTOM]) * PIXEL);
		//BackGround->Position = { (CurrentllShapeGroup->Left + CurrentllShapeGroup->Right) / 2, (CurrentllShapeGroup->Top + CurrentllShapeGroup->Bottom) / 2 };

		BackGround->InputType = INPUT_TOPLEFT;
		BackGround->Position = { CurrentllPageGroup->Left - (CurrentllPageGroup->BackGroundPadding[PADDING_LEFT] * PIXEL), CurrentllPageGroup->Top + (CurrentllPageGroup->BackGroundPadding[PADDING_TOP] * PIXEL) };
		Quad_Reference.SetllShape(BackGround);

		//Above, Below, Leftof, Rightof
		switch (CurrentllPageGroup->BackGroundPlacementType)
		{
		case PLACEMENT_ABOVE:
		{
			Quad_Reference.PlaceAbove(GetEdges(), CurrentllPageGroup->BackGroundMatchType, CurrentllPageGroup->BackGroundPadding[PADDING_BOTTOM]);
			break;
		}
		case PLACEMENT_BELOW:

			Quad_Reference.PlaceBelow(GetEdges(), CurrentllPageGroup->BackGroundMatchType, CurrentllPageGroup->BackGroundPadding[PADDING_TOP]);
			break;

		case PLACEMENT_LEFTOF:

			Quad_Reference.PlaceLeft(GetEdges(), CurrentllPageGroup->BackGroundMatchType, CurrentllPageGroup->BackGroundPadding[PADDING_RIGHT]);
			break;

		case PLACEMENT_RIGHTOF:

			Quad_Reference.PlaceRight(GetEdges(), CurrentllPageGroup->BackGroundMatchType, CurrentllPageGroup->BackGroundPadding[PADDING_LEFT]);
			break;
		}

		//Set EdgesWithBackGround
		CurrentllPageGroup->EdgesWithBackGround = UpdateEdges(Quad_Reference.GetEdges(), CurrentllPageGroup->EdgesWithBackGround);
	}
}

glm::vec4 PageGroup::GetEdges()
{
	if (CurrentllPageGroup == nullptr) { return { 0.0, 0.0, 0.0, 0.0 }; }

	return { CurrentllPageGroup->Left, CurrentllPageGroup->Right, CurrentllPageGroup->Top, CurrentllPageGroup->Bottom };
}


void PageGroup::SetPosition(glm::vec2 Position)
{
	if (CurrentllPageGroup == nullptr) { Log::LogString("ERROR:: OffsetPosition FAILED:: PageGroup nullptr"); return; };

	CurrentllPageGroup->Position = Position;
	llUpdate();
	Log::LogString("Position offseted");
}

void PageGroup::SetllPosition(glm::vec2 Position, int InputType)
{
	if (CurrentllPageGroup == nullptr) { Log::LogString("ERROR:: OffsetPosition FAILED:: PageGroup nullptr"); return; };

	CurrentllPageGroup->Position = Position;
	CurrentllPageGroup->InputType = InputType;

	if (InputType == INPUT_CENTER)
	{
		Input_Left_Once = true;
	}

	llUpdate();
}

void PageGroup::OffsetPosition(glm::vec2 Position, glm::vec2 bools)
{
	if (CurrentllPageGroup == nullptr) { Log::LogString("ERROR:: OffsetPosition FAILED:: PageGroup nullptr"); return; };
	if (bools[0] == true)
	{
		CurrentllPageGroup->Position[0] += Position[0];
	}
	if (bools[1] == true)
	{
		CurrentllPageGroup->Position[1] += Position[1];
	}
	llUpdate();
	Log::LogString("Position offseted");
}

void PageGroup::OffsetSize(glm::vec2 Size, glm::vec2 bools)
{
	if (CurrentllPageGroup == nullptr) { Log::LogString("ERROR:: OffsetSize FAILED:: PageGroup nullptr"); return; };
	if (bools[0] == true)
	{
		CurrentllPageGroup->Size[0] += Size[0];
	}
	if (bools[1] == true)
	{
		CurrentllPageGroup->Size[1] += Size[1];
	}
	llUpdate();
}

void PageGroup::OffsetColor(glm::vec4 Color, glm::vec4 bools)
{
	if (CurrentllPageGroup == nullptr) { Log::LogString("ERROR:: OffsetColor FAILED:: PageGroup nullptr"); return; };
	if (bools[0] == true)
	{
		CurrentllPageGroup->Color[0] += Color[0];
	}
	if (bools[1] == true)
	{
		CurrentllPageGroup->Color[1] += Color[1];
	}
	if (bools[2] == true)
	{
		CurrentllPageGroup->Color[2] += Color[2];
	}
	if (bools[3] == true)
	{
		CurrentllPageGroup->Color[3] += Color[3];
	}
	llUpdate();
}





void PageGroup::PlaceBelow(const glm::vec4& ElementEdges, int PlacementType, int PixelPadding)
{
	ManualPlaceBelow(PlacementType, ElementEdges, CurrentllPageGroup->InputType, CurrentllPageGroup->Position, PixelPadding);
	llUpdate();
}

void PageGroup::PlaceAbove(const glm::vec4& ElementEdges, int PlacementType, int PixelPadding)
{
	ManualPlaceAbove(PlacementType, ElementEdges, CurrentllPageGroup->InputType, CurrentllPageGroup->Position, PixelPadding);
	llUpdate();
}

void PageGroup::PlaceRight(const glm::vec4& ElementEdges, int PlacementType, int PixelPadding)
{
	ManualPlaceRight(PlacementType, ElementEdges, CurrentllPageGroup->InputType, CurrentllPageGroup->Position, PixelPadding);
	llUpdate();
}

void PageGroup::PlaceLeft(const glm::vec4& ElementEdges, int PlacementType, int PixelPadding)
{
	ManualPlaceLeft(PlacementType, ElementEdges, CurrentllPageGroup->InputType, CurrentllPageGroup->Position, PixelPadding);
	llUpdate();
}


PageGroup::PageGroup(Page& Page)
{
	if (&Page != nullptr)
	{
		Initialized = true;
		CurrentPage = &Page;
		//if (Page.CurrentShape > 0)
		//{
		//	cout << "Page group not added because there was nothing in the previous one" << endl;
			CurrentPage->TotalPageGroupCount++;
			CurrentPage->CurrentShapeGroupShapeCount = 0;
		//}
		Page.CurrentPageGroup = Page.TotalPageGroupCount;
		Page.CurrentPageItem = -1;
		Page.CurrentShapeGroup = -1;
		Page.CurrentShape = -1;
		Page.CurrentPageGroupShapeCount = -1;
		//CurrentPageGroup.ID = Page.TotalPageGroupCount;
		CurrentPageGroup.ShapeStart = Page.ShapeAmount();
		//CurrentPageGroup.ShapeOffset = Page.TotalPageGroupCount;
		CurrentPageGroup.ID = CurrentPage->CurrentPageGroup;
		//Log::LogString("-------Shape Added--------");
		//Log::LogInt("CurrentShape     ", Page.CurrentShape);
		//Log::LogInt("CurrentShapeGroup", Page.CurrentShapeGroup);
		//Log::LogInt("CurrentPageItem  ", Page.CurrentPageItem);
		//Log::LogInt("CurrentPageGroup ", Page.CurrentPageGroup);
		//Log::LogString(" ");
	}
}

PageGroup::PageGroup(Page& Page, PageGroupData& PageGroup)
{
	if (&Page != nullptr)
	{
		Initialized = true;
		CurrentPage = &Page;
		if (Page.CurrentShape > 0)
		{
			cout << "Page group not added because there was nothing in the previous one" << endl;
			CurrentPage->TotalPageGroupCount++;
		}
		Page.CurrentPageGroup = Page.TotalPageGroupCount;
		Page.CurrentPageItem = 0;
		Page.CurrentShapeGroup = 0;
		Page.CurrentShape = 0;
		CurrentPageGroup = PageGroup;
		//CurrentPageGroup.ID = Page.TotalPageGroupCount;
		CurrentPageGroup.ShapeStart = Page.ShapeAmount();
		CurrentPageGroup.ShapeOffset = Page.TotalPageGroupCount;
		CurrentPageGroup.ID = CurrentPage->CurrentPageGroup;
	}
	//;
}

PageGroup::PageGroup(Page& Page, ShapeData& ShapeData)
{
	if (&Page != nullptr)
	{
		Initialized = true;
		CurrentPage = &Page;
		if (Page.CurrentShape > 0)
		{
			cout << "Page group not added because there was nothing in the previous one" << endl;
			CurrentPage->TotalPageGroupCount++;
		}
		Page.CurrentPageGroup = Page.TotalPageGroupCount;
		Page.CurrentPageItem = 0;
		Page.CurrentShapeGroup = 0;
		Page.CurrentShape = 0;
		LoadedShape = ShapeData;
		//CurrentPageGroup.ID = Page.TotalPageGroupCount;
		CurrentPageGroup.ShapeStart = Page.ShapeAmount();
		CurrentPageGroup.ShapeOffset = Page.TotalPageGroupCount;
	}
	//CurrentPageItem.GroupID = CurrentPageItem.Page->PageItemCount;
}

void PageGroup::SetllPageGroup(llPageGroupData* PageGroup)
{
	*CurrentllPageGroup = *PageGroup;
	llUpdate();
}

void PageGroup::ShapeToGroup(ShapeData& ShapeData)
{
	//Loading our Item data from first shape
	//CurrentPageGroup.ShapeStartID = ShapeData.PageGroupID;
	//CurrentPageGroup.XYShapesPerRow = ShapeData.PageGroupXYShapePerRow;
	//CurrentPageGroup.ShapeDataSize = ShapeData.PageGroupShapeSize;
	//CurrentPageGroup.Position = ShapeData.PageGroupPosition;
	//CurrentPageGroup.Size = ShapeData.PageGroupSize;
	//CurrentPageGroup.Color = ShapeData.PageGroupColor;
	//CurrentPageGroup.MouseAccess = ShapeData.PageGroupMouseAccess;
	//CurrentPageGroup.Centered = ShapeData.PageGroupCentered;
	//CurrentPageGroup.Highlighted = ShapeData.PageGroupHighlighted;
	//CurrentPageGroup.ShapeType = ShapeData.ShapeDataType;
	//CurrentPageItem.ShapeCount     = ShapeData.PageGroupItemCount;
}

PageGroup::PageGroup(Page& Page, int ID)
{
	if (&Page != nullptr)
	{
		Initialized = true;
		CurrentPage = &Page;
		if (IsInBounds(ID) == false) Log::LogString("Shape Group Initialization failed:: ID out of bounds"); return;
		LoadedShape = Page.GetShapeDataR(ID);
		Page.CurrentPageGroup = CurrentPageGroup.ID;
		Page.CurrentPageItem = 0;
		Page.CurrentShapeGroup = 0;
		Page.CurrentShape = 0;
		Page.CurrentPageGroupShapeCount = 0;
	}
	Log::LogString("Page Item Not Initialized");
}


void PageGroup::ReCalibrateID()
{
	cout << "Recalibrating Group (" << CurrentPageGroup.ID << ") " << endl;

	int CurrentID = 0;
	int GroupStart = 0;

	//Maintenance
	//BoundsChecks()
	if (CurrentPageGroup.ShapeStart < CurrentPage->ShapeAmount())
	{
		//in range
		CurrentID = CurrentPageGroup.ShapeStart;
		GroupStart = CurrentPageGroup.ShapeStart;
	}
	if (CurrentPageGroup.ShapeStart> CurrentPage->ShapeAmount())
	{
		//out of range
		CurrentID  = CurrentPage->ShapeAmount();
		GroupStart = CurrentPage->ShapeAmount();
	}

	///Check if ID is valid
	if (CurrentID > -1)
	{
		cout << "Checking ID: " << CurrentID << "... " << endl;
		ShapeData* RetreivedShape = CurrentPage->GetShapeDataP(CurrentID);


		//Group Calibrated
		if (RetreivedShape->ShapeGroup.ID == CurrentPageGroup.ID)
		{
			//Set the ID
			CurrentPageGroup.ShapeStart = CurrentID - RetreivedShape->ShapeGroup.PageItem.PageGroup.ShapeOffset;
			cout << " Group: " << RetreivedShape->ShapeGroup.PageItem.PageGroup.ID << " Match Found!" << endl;
			cout << "Group Start : " << CurrentID - RetreivedShape->ShapeGroup.PageItem.PageGroup.ShapeOffset << endl;
			cout << "--------" << endl;
			return;
		}

		//Group UnCalibrated
		//if (RetreivedShape->PageGroupID != CurrentGroupData.GroupID)
		if (RetreivedShape->ShapeGroup.PageItem.PageGroup.ID != CurrentPageGroup.ID)
		{
			//Go up
			//if(RetreivedShape->PageGroupID <CurrentGroupData.GroupID)
			if (RetreivedShape->ShapeGroup.PageItem.PageGroup.ID < CurrentPageGroup.ID)
			{
				CurrentPageGroup.ShapeStart = FindNextGroup(CurrentID, RetreivedShape);
				RetreivedShape->ShapeGroup.PageItem.PageGroup.ShapeStart = CurrentPageGroup.ShapeStart;
				return;
			}

			//GO down
			if (RetreivedShape->ShapeGroup.PageItem.PageGroup.ID > CurrentPageGroup.ID)
			{
				CurrentPageGroup.ShapeStart = FindPreviousGroup(CurrentID, RetreivedShape);
				RetreivedShape->ShapeGroup.PageItem.PageGroup.ShapeStart = CurrentPageGroup.ShapeStart;
				return;
			}
		}
	}
}

//Returns the ID of the first shape in the group
int PageGroup::FindNextGroup(int CurrentID, ShapeData* RetreivedShape)
{
	//Found
	if (RetreivedShape->ShapeGroup.PageItem.PageGroup.ID == CurrentPageGroup.ID)
	{
		cout << " Group: " << RetreivedShape->ShapeGroup.PageItem.PageGroup.ID << " Match Found!" << endl;
		cout << " Group Start : " << CurrentID - RetreivedShape->ShapeGroup.ShapeOffset << endl;
		cout << "--------" << endl;
		return CurrentID - RetreivedShape->ShapeGroup.ShapeOffset;
	};

	//Set up next group 
	cout << " Group: " << RetreivedShape->ShapeGroup.PageItem.ID << " No Match" << endl;
	cout << "Trying Shape ID: " << RetreivedShape->ID << endl;
	int NextGroupID = RetreivedShape->ShapeGroup.PageItem.ShapeCount - RetreivedShape->ShapeGroup.PageItem.ShapeOffset + 1;
	Log::LogInt("Shape Count", RetreivedShape->ShapeGroup.PageItem.ShapeCount);
	Log::LogInt("Page Group Item Offset", RetreivedShape->ShapeGroup.PageItem.ShapeOffset);
	cout << "Shapes to hop: " << NextGroupID << endl;
	RetreivedShape += NextGroupID;
	CurrentID += NextGroupID;

	//Check Next Group
	int FoundID = FindNextGroup(CurrentID, RetreivedShape);
	return FoundID;
}


int PageGroup::FindPreviousGroup(int CurrentID, ShapeData* RetreivedShape)
{
	//Found
	if (RetreivedShape->ShapeGroup.PageItem.PageGroup.ID = CurrentPageGroup.ID)
	{
		cout << " Group: " << RetreivedShape->ShapeGroup.PageItem.PageGroup.ID << " Match Found!" << endl;
		cout << " Group Start : " << CurrentID - RetreivedShape->ShapeGroup.PageItem.PageGroup.ShapeOffset << endl;
		cout << "--------" << endl;
		return CurrentID - RetreivedShape->ShapeGroup.PageItem.PageGroup.ShapeOffset;
	};

	cout << " Group: " << RetreivedShape->ShapeGroup.PageItem.PageGroup.ID << " No Match" << endl;
	//Set up next group / Not found
	int NextGroupTranslation = RetreivedShape->ShapeGroup.PageItem.PageGroup.ShapeOffset - 1;
	RetreivedShape += NextGroupTranslation;
	CurrentID += NextGroupTranslation;

	//Check Next Group
	int FoundID = FindPreviousGroup(CurrentID, RetreivedShape);
	return FoundID;
}


//goal is to get page item StartID
int PageGroup::FindChildGroup(int ChildGroupID)
{
	ReCalibrateID();
	int CurrentID = CurrentPageGroup.ShapeStart;
	bool Found = false;
	ShapeData* RetreivedShape = CurrentPage->GetShapeDataP(CurrentID);

	//Found
	while (RetreivedShape->ShapeGroup.PageItem.PageGroup.ID == CurrentPageGroup.ID)
	{
		if (RetreivedShape->ShapeGroup.PageItem.ID == ChildGroupID)
		{
			cout << " PageItem: " << RetreivedShape->ShapeGroup.ID << " Match Found!" << endl;
			cout << " PageItem Start : " << CurrentID - RetreivedShape->ShapeGroup.PageItem.ShapeOffset << endl;
			cout << "--------" << endl;
			return CurrentID - RetreivedShape->ShapeGroup.PageItem.ShapeOffset;
		}

		//Not Found, Next group
		cout << " No Match " << endl;
		int NextGroupID = RetreivedShape->ShapeGroup.PageItem.ShapeCount - RetreivedShape->ShapeGroup.PageItem.ShapeOffset + 1;
		CurrentID += NextGroupID;
		RetreivedShape += NextGroupID;
	}

	cout << "Group Not Found" << endl;
	return -1;
}

//Working
int PageGroup::FindPageItem(bool FromBottom, double xMouse, double yMouse)
{
   // ReCalibrateID();
    int CurrentID = 22;
    bool Found = false;
    ShapeData* RetreivedShape = CurrentPage->GetShapeDataP(CurrentID);

	//Iterate through all  
	//or start from zero, and go up till you find it...
	//or start from top and go down till you find it...
	for (int i = 0; i < CurrentPage->ShapeAmount(); i++)
	{
		//Log::LogInt("Checking ID", RetreivedShape->ID);
		//Log::LogInt("PageGroup:", RetreivedShape->PageGroupItemID);
		if (xMouse < RetreivedShape->ShapeGroup.PageItem.Right && xMouse >  RetreivedShape->ShapeGroup.PageItem.Left && yMouse < RetreivedShape->ShapeGroup.PageItem.Top && yMouse >  RetreivedShape->ShapeGroup.PageItem.Bottom)
		{
			//Found
			//cout << " Mouse Inside Region" << endl;
			//cout << " PageItem Start : " << CurrentID - RetreivedShape->PageGroupItemShapeOffset << endl;
			return CurrentID - RetreivedShape->ShapeGroup.PageItem.ShapeOffset;
		}

		//Not Found Set up NextGroup
		//cout << " Out Of Mouse Region " << endl;
		int NextGroupID = RetreivedShape->ShapeGroup.PageItem.ShapeCount - RetreivedShape->ShapeGroup.PageItem.ShapeOffset + 1;
		CurrentID += NextGroupID;
		RetreivedShape += NextGroupID;
	}

  //  //Found
  //  while (Found == false)
  //  {
	//	
  //  	if (RetreivedShape->PageGroupItemID == ID)
  //  	{
  //  		cout << " Match Found" << endl;
  //  		cout << " PageItem Start : " << CurrentID - RetreivedShape->PageGroupItemShapeOffset << endl;
  //  		cout << "--------" << endl;
	//		Found = true;
  //  		return CurrentID - RetreivedShape->PageGroupItemShapeOffset;
  //  	}
  //  
  //  	//Not Found, Next group
  //  	cout << " No Match " << endl;
  //  	int NextGroupID = RetreivedShape->PageGroupItemShapeCount - RetreivedShape->PageGroupItemShapeOffset + 1;
  //  	CurrentID += NextGroupID;
  //  	RetreivedShape += NextGroupID;
  //  }
  //  
  //  cout << "Group Not Found" << endl;
    return -1;
}

float PageGroup::SetMouseAccess(glm::vec2 Position, glm::vec2 Size)
{
	float GroupLeft = Position[0] - Size[0] / 2;
	float GroupRight = Position[0] + Size[0] / 2;
	float GroupTop = Position[1] + Size[1] / 2;
	float GroupBottom = Position[1] - Size[1] / 2;

	if (GroupLeft > CurrentPageGroup.Left)
	{
		CurrentPageGroup.Left = GroupLeft;
	}

	if (GroupRight > CurrentPageGroup.Right)
	{
		CurrentPageGroup.Right = GroupRight;
	}

	if (GroupTop > CurrentPageGroup.Top)
	{
		CurrentPageGroup.Top = GroupTop;
	}

	if (GroupBottom > CurrentPageGroup.Bottom)
	{
		CurrentPageGroup.Bottom = GroupBottom;
	}
}

//void PageGroup::llSwitch(int Offset)
//{
//	for (int i = 0; i < Offset; i++)
//	{
//		if (Offset > 0)
//		{
//			CurrentllPageGroup = CurrentllPageGroup->Next;
//		}
//		else if (Offset < 0)
//		{
//			CurrentllPageGroup = CurrentllPageGroup->Previous;
//		}
//	}
//}
//

void PageGroup::SetllMouseAccess()
{
	//Checks
	if (CurrentllPageGroup == nullptr) { Log::LogString("ERROR::SetllMouseAccess FAILED::ShapeGroup is null "); return; };
	if (CurrentllPageGroup->PageItem == nullptr) { Log::LogString("ERROR::SetllMouseAccess FAILED::No ShapeGroups in Pageitem"); return; };

	//Setup
	llPageItemData* CurrentPageItem = CurrentllPageGroup->PageItem;


	//Go to Head Shape
	while (CurrentPageItem->Previous != nullptr)
	{
		CurrentPageItem = CurrentPageItem->Previous;
	}

	if (CurrentllPageGroup->BackGround == true)
	{
		CurrentPageItem = CurrentPageItem->Next;
	}

	float FurthestRight = CurrentPageItem->EdgesWithBackGround[EDGE_RIGHT];  //CurrentllPageGroup->EdgesWithBackGround[EDGE_RIGHT];  //
	float FurthestLeft = CurrentPageItem->EdgesWithBackGround[EDGE_LEFT];	  //CurrentllPageGroup->EdgesWithBackGround[EDGE_LEFT];   //
	float FurthestTop = CurrentPageItem->EdgesWithBackGround[EDGE_TOP];	      //CurrentllPageGroup->EdgesWithBackGround[EDGE_TOP];    //
	float FurthestBottom = CurrentPageItem->EdgesWithBackGround[EDGE_BOTTOM]; //CurrentllPageGroup->EdgesWithBackGround[EDGE_BOTTOM]; //

	//if (CurrentPageItem->Next != nullptr)
	//{
	//	CurrentPageItem = CurrentPageItem->Next;
	//}
	//Compare CurrentShape's Access variables with all other shapes
	while (CurrentPageItem != nullptr)
	{
		//Furthest Right is the most positive number
		if (FurthestRight < CurrentPageItem->EdgesWithBackGround[EDGE_RIGHT]) //
		{
			FurthestRight = CurrentPageItem->EdgesWithBackGround[EDGE_RIGHT];
		}

		//Furthest Left is the most negative number
		if (FurthestLeft > CurrentPageItem->EdgesWithBackGround[EDGE_LEFT]) //
		{
			FurthestLeft = CurrentPageItem->EdgesWithBackGround[EDGE_LEFT];
		}

		//Furthest Top is the most positive number
		if (FurthestTop < CurrentPageItem->EdgesWithBackGround[EDGE_TOP]) //
		{
			FurthestTop = CurrentPageItem->EdgesWithBackGround[EDGE_TOP];
		}

		//Furthest Bottom is the most negative number
		if (FurthestBottom > CurrentPageItem->EdgesWithBackGround[EDGE_BOTTOM]) //
		{
			FurthestBottom = CurrentPageItem->EdgesWithBackGround[EDGE_BOTTOM];
		}

		CurrentPageItem = CurrentPageItem->Next;
	}

	//Set ShapeGroup
	CurrentllPageGroup->Right = FurthestRight;
	CurrentllPageGroup->Left = FurthestLeft;
	CurrentllPageGroup->Top = FurthestTop;
	CurrentllPageGroup->Bottom = FurthestBottom;

	CurrentllPageGroup->Size[X_AXIS] = FurthestRight - FurthestLeft; //Correct
	CurrentllPageGroup->Size[Y_AXIS] = FurthestTop - FurthestBottom; //Correct

		//Set Input if not already set
	if (CurrentllPageGroup->InputType != INPUT_CENTER || Input_Left_Once == true)
	{
		TranslateInput();
		//WithNewInput = true;
		llUpdate();
	}

	SetBackGround();
}


void PageGroup::TranslateInput()
{
	float LeftEdgeOffset = CurrentllPageGroup->Position[X_AXIS] - CurrentllPageGroup->Left;
	float RightEdgeOffset = CurrentllPageGroup->Position[X_AXIS] - CurrentllPageGroup->Right;
	float TopEdgeOffset = CurrentllPageGroup->Position[Y_AXIS] - CurrentllPageGroup->Top;
	float BottomEdgeOffset = CurrentllPageGroup->Position[Y_AXIS] - CurrentllPageGroup->Bottom;

	switch (CurrentllPageGroup->InputType)
	{
	case INPUT_LEFT: //Center
		CurrentllPageGroup->Position[Y_AXIS] += TopEdgeOffset;
		CurrentllPageGroup->Position[Y_AXIS] += (CurrentllPageGroup->Size[Y_AXIS] / 2);
		CurrentllPageGroup->Position[X_AXIS] += LeftEdgeOffset;
		CurrentllPageGroup->InputType = INPUT_CENTER;
		break;
	case INPUT_RIGHT: //Center
		CurrentllPageGroup->Position[Y_AXIS] += TopEdgeOffset;
		CurrentllPageGroup->Position[Y_AXIS] += (CurrentllPageGroup->Size[Y_AXIS] / 2);
		CurrentllPageGroup->Position[X_AXIS] += RightEdgeOffset;
		CurrentllPageGroup->InputType = INPUT_CENTER;
		break;
	case INPUT_TOP: //Center
		CurrentllPageGroup->Position[Y_AXIS] += TopEdgeOffset;
		CurrentllPageGroup->Position[X_AXIS] += RightEdgeOffset;
		CurrentllPageGroup->Position[X_AXIS] += (CurrentllPageGroup->Size[X_AXIS] / 2);
		CurrentllPageGroup->InputType = INPUT_CENTER;
		break;
	case INPUT_BOTTOM: //Center
		CurrentllPageGroup->Position[Y_AXIS] += BottomEdgeOffset;
		CurrentllPageGroup->Position[X_AXIS] += RightEdgeOffset;
		CurrentllPageGroup->Position[X_AXIS] += (CurrentllPageGroup->Size[X_AXIS] / 2);
		CurrentllPageGroup->InputType = INPUT_CENTER;
		break;
	case INPUT_TOPLEFT: //Corner
		CurrentllPageGroup->Position[X_AXIS] += LeftEdgeOffset;
		CurrentllPageGroup->Position[Y_AXIS] += TopEdgeOffset;
		CurrentllPageGroup->InputType = INPUT_CENTER;
		Log::LogString("went in!!!!!!!!!!!!!!!!!!!!!!");
		break;
	case INPUT_TOPRIGHT: //Corner
		CurrentllPageGroup->Position[X_AXIS] += RightEdgeOffset;
		CurrentllPageGroup->Position[Y_AXIS] += TopEdgeOffset;
		CurrentllPageGroup->InputType = INPUT_CENTER;
		break;
	case INPUT_BOTTOMLEFT: //Corner
		CurrentllPageGroup->Position[X_AXIS] += LeftEdgeOffset;
		CurrentllPageGroup->Position[Y_AXIS] += BottomEdgeOffset;
		CurrentllPageGroup->InputType = INPUT_CENTER;
		break;
	case INPUT_BOTTOMRIGHT: //Corner
		CurrentllPageGroup->Position[X_AXIS] += RightEdgeOffset;
		CurrentllPageGroup->Position[Y_AXIS] += BottomEdgeOffset;
		CurrentllPageGroup->InputType = INPUT_CENTER;
		break;
	case INPUT_CENTER:
		CurrentllPageGroup->Position[Y_AXIS] += TopEdgeOffset;
		CurrentllPageGroup->Position[Y_AXIS] += (CurrentllPageGroup->Size[Y_AXIS] / 2);
		CurrentllPageGroup->Position[X_AXIS] += RightEdgeOffset;
		CurrentllPageGroup->Position[X_AXIS] += (CurrentllPageGroup->Size[X_AXIS] / 2);
		Input_Left_Once = false;
		CurrentllPageGroup->InputType = INPUT_CENTER;
		break;
	}

	CurrentllPageGroup->InputType = INPUT_CENTER;
}


void PageGroup::Hide()
{
	if (CurrentllPageGroup == nullptr) { Log::LogString("ERROR:: ShapeGrou Hide FAILED:: Invalid ShapeGroup State"); return; }
	if (CurrentllPageGroup->Hide == true) { return; }

	CurrentllPageGroup->Hide = true;
	CurrentllPageGroup->MouseAccess = false;
	llUpdate();
}

void PageGroup::UnHide()
{
	if (CurrentllPageGroup== nullptr) { Log::LogString("ERROR:: ShapeGroup Hide FAILED:: Invalid ShapeGroup State"); return; }
	if (CurrentllPageGroup->Hide == false) { return; }

	CurrentllPageGroup->Hide = false;
	CurrentllPageGroup->MouseAccess = true;
	llUpdate();
}


void PageGroup::llUpdate()
{
	//Validate
	if (LoadedBook == nullptr) { Log::LogString("ERROR:: PageGroup Update FAILED:: Invalid Book State");  return; }
	if (CurrentllPageGroup == nullptr) { Log::LogString("ERROR:: PageGroup Update FAILED:: Invalid PageGroup State"); return; }
	if (CurrentllPageGroup->PageItem == nullptr) { Log::LogString("WARNING:: PageGroup Update FAILED:: No Contents to Update"); return; }

	llPageItemData* CurrentPageItem = CurrentllPageGroup->PageItem;

	while (CurrentPageItem->Previous != nullptr)
	{
		CurrentPageItem = CurrentPageItem->Previous;
	}

	//if (CurrentllPageGroup->BackGround == true)
	//{
	//	CurrentPageItem = CurrentPageItem->Next;
	//}

	//Main Loop
	while (CurrentPageItem != nullptr)
	{
		//switch (CurrentPageItem->Type)
		//{
		//case TYPE_PAGEITEM: 
		//{
		PageGroupItem PageItemSelected(CurrentPageItem);
		PageItemSelected.llSwitch(CurrentPageItem);
		PageItemSelected.LoadedBook = LoadedBook;
		CurrentPageItem->Position = CurrentllPageGroup->Position + CurrentPageItem->PositionOffset;
		//Log::LogString(" ");
		//Log::LogVec2("New PageItem Position", CurrentPageItem->Position);
		//Log::LogVec2("Based on this offset: ", CurrentPageItem->PositionOffset);
		//Log::LogVec2("from this PageGroup position: ", CurrentllPageGroup->Position);
		//Log::LogString(" ");
		CurrentPageItem->Hide = CurrentllPageGroup->Hide;
		CurrentPageItem->MouseAccess = CurrentllPageGroup->MouseAccess;
		CurrentPageItem->Highlighted = CurrentllPageGroup->Highlighted;
		CurrentPageItem->HighlightColor = CurrentllPageGroup->HighlightColor;
		//CurrentPageItem->Size = CurrentllPageGroup->Size - CurrentPageItem->SizeOffset;
		//CurrentPageItem->Color = CurrentllPageGroup->Color - CurrentPageItem->ColorOffset;
		CurrentPageItem->ChangeAsGroup = true;
		PageItemSelected.SetllPageItem(CurrentPageItem);
		//break;
	//}
	//case TYPE_PAGEITEM_SLIDER:
	//{
	//	Slider SliderSelected(CurrentPageItem);
	//	SliderSelected.llSwitch(CurrentPageItem);
	//	SliderSelected.LoadedBook = LoadedBook;
	//	CurrentPageItem->Position = CurrentllPageGroup->Position - CurrentPageItem->PositionOffset;
	//	CurrentPageItem->Highlighted = CurrentllPageGroup->Highlighted;
	//	CurrentPageItem->HighlightColor = CurrentllPageGroup->HighlightColor;
	//	CurrentPageItem->ChangeAsGroup = true;
	//	SliderSelected.SetllPageItem(CurrentPageItem);
	//	break;
	//}
	//}
		CurrentPageItem = CurrentPageItem->Next;
		//CurrentPageItem = nullptr;
	}
	SetllMouseAccess();
}
