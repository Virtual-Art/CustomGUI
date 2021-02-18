#include "PageGroupItem.h"

void PageGroupItem::llInit(llBookData* llBook)
{
	LoadedBook = llBook;
}

PageGroupItem::PageGroupItem()
{
	LoadedBook = nullptr;
	CurrentllPageItem = nullptr;
}

PageGroupItem::PageGroupItem(llBookData* llBook)
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

	if (llBook->Page->PageGroup == nullptr)
	{
		Log::LogString("Book Is Brand New");
		llPageGroupData* CreatedPageGroup = new llPageGroupData;

		llBook->Page->PageGroup = CreatedPageGroup;
		llBook->Page->PageGroupHead = CreatedPageGroup;
	}

	CurrentllPageItem = new llPageItemData;
	//Log::LogString("PageItem Created and Shape Group?");

	llPageItemData* TestingPageItem = llBook->Page->PageGroup->PageItem;

	//Completely new object
	if (TestingPageItem == nullptr)
	{
		Log::LogString("PageGroup Empty. First PageItem!");
		llBook->Page->PageGroup->PageItem = CurrentllPageItem;
		llBook->Page->PageGroup->PageItemHead = CurrentllPageItem;
	}
	else //Shapes already created
	{
		llPageItemData* FoundTail = TestingPageItem;
		int LinkCount = 0;

		//Find tail then add
		//Log::LogString("Finding Tail..");
		while (FoundTail->Next != nullptr)
		{
			FoundTail = FoundTail->Next;
			LinkCount++;
		}
		Log::LogString("PageItem Linked");
		FoundTail->Next = CurrentllPageItem;
		CurrentllPageItem->Previous = FoundTail;
		llBook->Page->PageGroup->PageItem = CurrentllPageItem;
	}

	CurrentllPageItem->Type = TYPE_CUSTOM;
	LoadedBook = llBook;
}

PageGroupItem::PageGroupItem(llBookData* llBookData, llPageItemData* llPageItem)
{

	//Make sure we are provided with data
	if (llPageItem != nullptr && llBookData != nullptr)
	{
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

			llBookData->Page->PageGroup = CreatedPageGroup;
			llBookData->Page->PageGroupHead = CreatedPageGroup;
		}

		//Create a new PageItem & Copy the provided data
		CurrentllPageItem = new llPageItemData;
		*CurrentllPageItem = *llPageItem;
		//Log::LogString("PageItem Created and ShapeGroup Created?");

		//Take a look at the current PageItem in the current PageGroup
		llPageItemData* TestingPageItem = llBookData->Page->PageGroup->PageItem;

		//The book doesn't have a PageItem in the current PageGroup
		if (TestingPageItem == nullptr)
		{
			//Set the book to include and point to the newly created PageItem
			Log::LogString("PageGroup Empty. First PageItem!");
			llBookData->Page->PageGroup->PageItem = CurrentllPageItem;
			llBookData->Page->PageGroup->PageItemHead = CurrentllPageItem;
		}
		else //A Page Item already exists in the current Page Group
		{
			llPageItemData* FoundTail = TestingPageItem;
			int LinkCount = 0;

			//Find the last PageItem in the current PageGroup
			//Log::LogString("Finding Tail..");
			while (FoundTail->Next != nullptr)
			{
				FoundTail = FoundTail->Next;
				LinkCount++;
			}

			//When we find the last PageItem in the PageGroup, attach the newly created PageItem next to it and
			Log::LogString("PageItem Linked");
			FoundTail->Next = CurrentllPageItem;
			CurrentllPageItem->Previous = FoundTail;


			
			//Then set the book to point to the new PageItem we created
			llBookData->Page->PageGroup->PageItem = CurrentllPageItem;
		}

		CurrentllPageItem->Type = TYPE_CUSTOM;
		LoadedBook = llBookData;
	}
	else
	{
		Log::LogString("Sorry llShape was nullptr");
	}
}

PageGroupItem::PageGroupItem(llPageItemData* llPageItem)
{

}

//New Page Item with data provided by derived class
PageGroupItem::PageGroupItem(Page& Page)
{
	if (&Page != nullptr)
	{
		//Setup
		Initialized = true;
		CurrentPage = &Page;
		CurrentPageItem.ShapeStart = Page.ShapeAmount();

		//Track Counts
		CurrentPage->CurrentPageItem++;
		CurrentPage->TotalPageItemCount++;

		//Reset Child Group Counts / Shape Counts
		CurrentPage->CurrentShapeGroup = 0;
		CurrentPage->CurrentShape = -1;
		CurrentPage->CurrentPageItemShapeCount = -1;
		CurrentPage->CurrentShapeGroupShapeCount = -1;
	}
}

//New PageItem initialized by group data
PageGroupItem::PageGroupItem(Page& Page, PageItemData& PageItemData)
{
	if (&Page != nullptr)
	{
		//Setup
		Initialized = true;
		CurrentPage = &Page;
		CurrentPageItem = PageItemData;
		CurrentPageItem.ShapeStart = Page.ShapeAmount();

		//Track Counts
        CurrentPage->CurrentPageItem++;
		CurrentPage->TotalPageItemCount++;

		CurrentPageItem.ID = CurrentPage->CurrentPageItem;

		//Reset Child Group Counts / Shape Counts
		CurrentPage->CurrentShapeGroup = 0;
		CurrentPage->CurrentShape = -1;
		CurrentPage->CurrentPageItemShapeCount = -1;
		CurrentPage->CurrentShapeGroupShapeCount = -1;
	}
}

//New Page Item initialized by FullShape Data
PageGroupItem::PageGroupItem(Page& Page, ShapeData& FullShape)
{
	if (&Page != nullptr)
	{
		//Setup
		Initialized = true;
		CurrentPage = &Page;
		LoadedShape = FullShape;
		CurrentPageItem.ShapeStart = Page.ShapeAmount();
		
		//Track Counts
		CurrentPage->TotalPageItemCount++;
		CurrentPage->CurrentPageItem++;

		//Reset Child Group Counts
		CurrentPage->CurrentShapeGroup = 0;
		CurrentPage->CurrentShape = -1;
		CurrentPage->CurrentPageItemShapeCount = -1;
		CurrentPage->CurrentShapeGroupShapeCount = -1;

	}
}

//Group can be changed for another
PageGroupItem::PageGroupItem(Page& Page, int ID)
{
	if (&Page != nullptr)
	{
		Initialized = true;
		CurrentPage = &Page;
		if (ID != -1)
		{
			LoadedShape = Page.GetShapeDataR(ID);
			CurrentPageItem = LoadedShape.ShapeGroup.PageItem;
			CurrentPage->CurrentPageItem = CurrentPageItem.ID;
			CurrentPage->CurrentShapeGroup = 0;
			CurrentPage->CurrentShape = 0;
			CurrentPage->CurrentPageItemShapeCount = -1;
		}
		else
		{
			cout << "Page Item Not Initialized " << endl;
		}
	}
	else
	{
		cout << "PageGroup Not Ready:: error page is nullptr" << endl;
	}

}

void PageGroupItem::llPageItemInit(llBookData* llBookData, llPageItemData* llPageItem)
{
	//Make sure we are provided with data
	if (llPageItem != nullptr && llBookData != nullptr)
	{
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

			llBookData->Page->PageGroup = CreatedPageGroup;
			llBookData->Page->PageGroupHead = CreatedPageGroup;
		}

		//Create a new PageItem & Copy the provided data
		CurrentllPageItem = new llPageItemData;
		*CurrentllPageItem = *llPageItem;
		//Log::LogString("PageItem Created and ShapeGroup Created?");

		//Take a look at the current PageItem in the current PageGroup
		llPageItemData* TestingPageItem = llBookData->Page->PageGroup->PageItem;

		//The book doesn't have a PageItem in the current PageGroup
		if (TestingPageItem == nullptr)
		{
			//Set the book to include and point to the newly created PageItem
			Log::LogString("PageGroup Empty. First PageItem!");
			llBookData->Page->PageGroup->PageItem = CurrentllPageItem;
			llBookData->Page->PageGroup->PageItemHead = CurrentllPageItem;
		}
		else //A Page Item already exists in the current Page Group
		{
			llPageItemData* FoundTail = TestingPageItem;
			int LinkCount = 0;

			//Find the last PageItem in the current PageGroup
			//Log::LogString("Finding Tail..");
			while (FoundTail->Next != nullptr)
			{
				FoundTail = FoundTail->Next;
				LinkCount++;
			}

			//When we find the last PageItem in the PageGroup, attach the newly created PageItem next to it and
			Log::LogString("PageItem Linked");
			FoundTail->Next = CurrentllPageItem;
			CurrentllPageItem->Previous = FoundTail;



			//Then set the book to point to the new PageItem we created
			llBookData->Page->PageGroup->PageItem = CurrentllPageItem;
		}

		CurrentllPageItem->Type = TYPE_CUSTOM;
		LoadedBook = llBookData;
	}
	else
	{
		Log::LogString("Sorry llShape was nullptr");
	}
}

void PageGroupItem::llSwitch(llPageItemData* llPageItem)
{
	if (llPageItem != nullptr)
	{
		CurrentllPageItem = llPageItem;
	}
	else
	{
		Log::LogString("ERROR:: llSwitch FAILED:: PageItem was nullptr");
	}
}

void PageGroupItem::OffsetPosition(glm::vec2 Position, glm::vec2 bools)
{
	if (CurrentllPageItem == nullptr) { Log::LogString("ERROR:: OffsetPosition FAILED:: PageItem nullptr"); return; };
	if (bools[0] == true)
	{
		CurrentllPageItem->Position[0] += Position[0];
	}
	if (bools[1] == true)
	{
		CurrentllPageItem->Position[1] += Position[1];
	}
	llUpdate();
}

void PageGroupItem::OffsetSize(glm::vec2 Size, glm::vec2 bools)
{
	if (CurrentllPageItem == nullptr) { Log::LogString("ERROR:: OffsetSize FAILED:: PageItem nullptr"); return; };
	if (bools[0] == true)
	{
		CurrentllPageItem->Size[0] += Size[0];
	}
	if (bools[1] == true)
	{
		CurrentllPageItem->Size[1] += Size[1];
	}
	llUpdate();
}

void PageGroupItem::OffsetColor(glm::vec4 Color, glm::vec4 bools)
{
	if (CurrentllPageItem == nullptr) { Log::LogString("ERROR:: OffsetColor FAILED:: PageItem nullptr"); return; };
	if (bools[0] == true)
	{
		CurrentllPageItem->Color[0] += Color[0];
	}
	if (bools[1] == true)
	{
		CurrentllPageItem->Color[1] += Color[1];
	}
	if (bools[2] == true)
	{
		CurrentllPageItem->Color[2] += Color[2];
	}
	if (bools[3] == true)
	{
		CurrentllPageItem->Color[3] += Color[3];
	}
	llUpdate();
}


void PageGroupItem::SetllPageItem(llPageItemData* llPageItem)
{
	if (llPageItem != nullptr)
	{
		*CurrentllPageItem = *llPageItem;
		llUpdate();
	}
}



void PageGroupItem::llUpdate()
{
	if (CurrentllPageItem != nullptr && LoadedBook != nullptr)
	{
		llShapeGroupData* CurrentShapeGroup = CurrentllPageItem->ShapeGroup;

		while (CurrentShapeGroup->Previous != nullptr)
		{
			CurrentShapeGroup = CurrentShapeGroup->Previous;
		}

		//Main Loop
		while (CurrentShapeGroup != nullptr)
		{
			CurrentShapeGroup->Position = CurrentllPageItem->Position - CurrentShapeGroup->PositionOffset;
			CurrentShapeGroup->Size = CurrentllPageItem->Size - CurrentShapeGroup->SizeOffset;
			CurrentShapeGroup->Color = CurrentllPageItem->Color - CurrentShapeGroup->ColorOffset;

			switch (CurrentShapeGroup->Type)
			{
			case TYPE_SHAPEGROUP:
			{
				ShapeGroup ShapeGroupSelected(CurrentShapeGroup);
				ShapeGroupSelected.SetllShapeGroup(CurrentShapeGroup);
				break;
			}
			case TYPE_SHAPEGROUP_TEXT:
			{
				TextData INCOMPLETE;
				Text QuadSelected(CurrentShapeGroup);
				QuadSelected.SetllTextGroup(CurrentShapeGroup, INCOMPLETE);
				break;
			}
			CurrentShapeGroup = CurrentShapeGroup->Next;
			}

		}
	}
}

void PageGroupItem::SetPosition(glm::vec2 Position)
{
	this->CurrentPageItem.Position = Position;
	//ReCalibrateID();
	Update();
}

void PageGroupItem::OffsetPosition(glm::vec2 Position)
{
	this->CurrentPageItem.Position += Position;
	//ReCalibrateID();
	Update();
}


void PageGroupItem::ShapeToGroup(ShapeData& ShapeData)
{
	////PageItem
	//CurrentPageItem.GroupID        = ShapeData.PageItem.ID;
	//CurrentPageItem.ShapeStartID   = ShapeData.PageItem.ShapeStartID;
	//CurrentPageItem.ShapeCount     = ShapeData.PageGroupShapeCount;
	//CurrentPageItem.Position       = ShapeData.PageItem.Position;
	//cout << "POSITON GOT BACK = " << CurrentPageItem.Position[0] << " , " << CurrentPageItem.Position[1] << endl;
	//CurrentPageItem.Size           = ShapeData.PageItem.Size;
	//CurrentPageItem.Color          = ShapeData.PageItem.Color;
	//CurrentPageItem.MouseAccess    = ShapeData.PageItem.MouseAccess;
	//CurrentPageItem.Centered       = ShapeData.PageItem.Centered;
	//CurrentPageItem.Highlighted    = ShapeData.PageItem.Highlighted;
	//CurrentPageItem.ShapeType      = ShapeData.ShapeDataType;
	//CurrentPageItem.XYShapesPerRow = ShapeData.PageItem.XYShapePerRow;
	//CurrentPageItem.ShapeDataSize  = ShapeData.PageItem.ShapeSize;
	//CurrentPageItem.Left           = ShapeData.PageItem.Left;
	//CurrentPageItem.Right          = ShapeData.PageItem.Right;
	//CurrentPageItem.Top            = ShapeData.PageItem.Top;
	//CurrentPageItem.Bottom         = ShapeData.PageItem.Bottom;
	//
	////ShapeGroup
	//LoadedShapeGroup.PageItemID           = ShapeData.PageItem.ID;
	//LoadedShapeGroup.PageItemShapeStartID = ShapeData.PageItem.ShapeStartID;
	//LoadedShapeGroup.PageItemShapeCount   = ShapeData.PageItem.ShapeCount;

}

//ShapeData Editing
void PageGroupItem::Add_Default()
{
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

	if (LoadedBook->Page->PageGroup == nullptr)
	{
		Log::LogString("Book Is Brand New");
		llPageGroupData* CreatedPageGroup = new llPageGroupData;

		LoadedBook->Page->PageGroup = CreatedPageGroup;
		LoadedBook->Page->PageGroupHead = CreatedPageGroup;
	}

	CurrentllPageItem = new llPageItemData;
	//Log::LogString("PageItem Created and Shape Group?");

	llPageItemData* TestingPageItem = LoadedBook->Page->PageGroup->PageItem;

	//Completely new object
	if (TestingPageItem == nullptr)
	{
		Log::LogString("PageGroup Empty. First PageItem!");
		LoadedBook->Page->PageGroup->PageItem = CurrentllPageItem;
		LoadedBook->Page->PageGroup->PageItemHead = CurrentllPageItem;
	}
	else //Shapes already created
	{
		llPageItemData* FoundTail = TestingPageItem;
		int LinkCount = 0;

		//Find tail then add
		//Log::LogString("Finding Tail..");
		while (FoundTail->Next != nullptr)
		{
			FoundTail = FoundTail->Next;
			LinkCount++;
		}
		Log::LogString("PageItem Linked");
		FoundTail->Next = CurrentllPageItem;
		CurrentllPageItem->Previous = FoundTail;
		LoadedBook->Page->PageGroup->PageItem = CurrentllPageItem;
	}

	CurrentllPageItem->Type = TYPE_CUSTOM;
}

void PageGroupItem::Add_Duplicate()
{

}

void PageGroupItem::Add_Insert()
{

}

void PageGroupItem::Delete()
{

}

ShapeData& PageGroupItem::Switch(int RequstedShapeID)
{
	if (Initialized == true)
	{
		if (IsInBounds(RequstedShapeID) == true)
		{
			 //CurrentPage->CurrentPageGroupShapeCount = -1;
		     LoadedShape = CurrentPage->GetShapeDataR(RequstedShapeID);
			 CurrentPageItem = LoadedShape.ShapeGroup.PageItem;
		     return LoadedShape;
		}
		else
		{
			Log::LogString("Switch Error:: ID out of bounds");
		}
	}
	else
	{
		Log::LogString("Switch Error:: Page Item Not Initialized");
	}
	return LoadedShape;
}

ShapeData& PageGroupItem::Switch(Page& Page, int RequstedShapeID)
{
	return LoadedShape;
}

void PageGroupItem::SetPageItem(ShapeData& ShapeData)
{

}

void PageGroupItem::SetPageItem(ShapeData& ShapeData, glm::vec2 PSConversions)
{

}

void PageGroupItem::UpdateMouseAccess(glm::vec2 Position, glm::vec2 Size, int PositionConversion)
{
	switch(PositionConversion)
	{
	case 1:
		Position = ConvertEndToMiddle(Position, Size);
		break;
	case 2:
		Position = ConvertBeginningToMiddle(Position, Size);
		break;
	}

	float Left = Position[0] - (Size[0] / 2);
	float Right = Position[0] + (Size[0] / 2);
	float Top = Position[1] + (Size[1] / 2);
	float Bottom = Position[1] - (Size[1] / 2);

	if (Left < CurrentPageItem.Left || CurrentPageItem.Left == -3.0)
	{
		CurrentPageItem.Left = Left;
	}

	if (Right > CurrentPageItem.Right || CurrentPageItem.Right == -3.0)
	{
		CurrentPageItem.Right = Right;
	}

	if (Top > CurrentPageItem.Top || CurrentPageItem.Top == -3.0)
	{
		CurrentPageItem.Top = Top;
	}

	if (Bottom < CurrentPageItem.Bottom || CurrentPageItem.Bottom == -3.0)
	{
		CurrentPageItem.Bottom = Bottom;
	}

}

void PageGroupItem::UpdatellMouseAccess()
{
	//Checks
	if (CurrentllPageItem == nullptr) { Log::LogString("ERROR::SetllMouseAccess FAILED::ShapeGroup is null "); return; };
	if (CurrentllPageItem->ShapeGroup == nullptr) { Log::LogString("ERROR::SetllMouseAccess FAILED::No ShapeGroups in Pageitem"); return; };

	//Setup
	llShapeGroupData* CurrentShapeGroup = CurrentllPageItem->ShapeGroup;


	//Go to Head Shape
	while (CurrentShapeGroup->Previous != nullptr)
	{
		CurrentShapeGroup = CurrentShapeGroup->Previous;
	}

	float FurthestRight = CurrentShapeGroup->Right;
	float FurthestLeft = CurrentShapeGroup->Left;
	float FurthestTop = CurrentShapeGroup->Top;
	float FurthestBottom = CurrentShapeGroup->Bottom;

	if (CurrentShapeGroup->Next != nullptr)
	{
		CurrentShapeGroup = CurrentShapeGroup->Next;
	}
	//Compare CurrentShape's Access variables with all other shapes
	while (CurrentShapeGroup != nullptr)
	{
		//Furthest Right is the most positive number
		if (FurthestRight < CurrentShapeGroup->Right) //
		{
			FurthestRight = CurrentShapeGroup->Right;
		}

		//Furthest Left is the most negative number
		if (FurthestLeft > CurrentShapeGroup->Left) //
		{
			FurthestLeft = CurrentShapeGroup->Left;
		}

		//Furthest Top is the most positive number
		if (FurthestTop < CurrentShapeGroup->Top) //
		{
			FurthestTop = CurrentShapeGroup->Top;
		}

		//Furthest Bottom is the most negative number
		if (FurthestBottom > CurrentShapeGroup->Bottom) //
		{
			FurthestBottom = CurrentShapeGroup->Bottom;
		}

		CurrentShapeGroup = CurrentShapeGroup->Next;
	}

	//Set ShapeGroup
	CurrentllPageItem->Right = FurthestRight;
	CurrentllPageItem->Left = FurthestLeft;
	CurrentllPageItem->Top = FurthestTop;
	CurrentllPageItem->Bottom = FurthestBottom;

}

void PageGroupItem::ReCalibrateID()
{
	if (Initialized == false) { Log::LogString("ReCalibrateID Failed:: ShapeGroup Not Initialized"); return; };
	cout << "Recalibrating Group (" << CurrentPageItem.ID << ") " << endl;

	int CurrentID = 0;
	int GroupStart = 0;

	//Maintenance
	//BoundsChecks()
	if (IsInBounds(CurrentPageItem.ShapeStart) == true)
	{
		//in range
		CurrentID = CurrentPageItem.ShapeStart;
		GroupStart = CurrentPageItem.ShapeStart;
	}
	if (IsInBounds(CurrentPageItem.ShapeStart) == false)
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
		if (RetreivedShape->ShapeGroup.PageItem.ID == CurrentPageItem.ID)
		{
			//Set the ID
			CurrentPageItem.ShapeStart = CurrentID - RetreivedShape->ShapeGroup.PageItem.ShapeOffset;
			cout << " Group: " << RetreivedShape->ShapeGroup.PageItem.ID << " Match Successfully Found!" << endl;
			cout << "Group Start : " << CurrentID - RetreivedShape->ShapeGroup.PageItem.ShapeOffset << endl;
			cout << "--------" << endl;
			return;
		}

		//Group UnCalibrated
		//if (RetreivedShape->PageGroupID != CurrentGroupData.GroupID)
		if (RetreivedShape->ShapeGroup.PageItem.ID != CurrentPageItem.ID)
		{
			//Go up
			//if(RetreivedShape->PageGroupID <CurrentGroupData.GroupID)
			if (RetreivedShape->ShapeGroup.PageItem.ID < CurrentPageItem.ID)
			{
				int Result = FindNextGroup(CurrentID, RetreivedShape);
				if (Result != -1)
				{
					RetreivedShape->ShapeGroup.PageItem.ShapeStart = CurrentPageItem.ShapeStart;
					return;
				}
				Log::LogString("FindNextGroupError:: Returned -1"); return;
			}

			//GO down
			if (RetreivedShape->ShapeGroup.PageItem.ID > CurrentPageItem.ID)
			{
				int Result = FindPreviousGroup(CurrentID, RetreivedShape);
				if (Result != -1)
				{
					RetreivedShape->ShapeGroup.PageItem.ShapeStart = CurrentPageItem.ShapeStart;
					return;
				}
				Log::LogString("FindPreviousGroupError:: Returned -1"); return;
			}
		}
	}
}

//Returns the ID of the first shape in the group
int PageGroupItem::FindNextGroup(int CurrentID, ShapeData* RetreivedShape)
{
	if (RetreivedShape == nullptr) return -1;
	//Found
	if (RetreivedShape->ShapeGroup.PageItem.ID == CurrentPageItem.ID)
	{
		cout << " Group: " << RetreivedShape->ShapeGroup.PageItem.ID << " Match Found!" << endl;
		cout << " Group Start : " << CurrentID - RetreivedShape->ShapeGroup.ShapeOffset << endl;
		cout << "--------" << endl;
		return CurrentID - RetreivedShape->ShapeGroup.ShapeOffset;
	};

	//Set up next group 
	cout << " Group: " << RetreivedShape->ShapeGroup.PageItem.ID << " No Match" << endl;
	int NextGroupID = RetreivedShape->ShapeGroup.PageItem.ShapeCount - RetreivedShape->ShapeGroup.PageItem.ShapeOffset + 1;
	RetreivedShape += NextGroupID;
	CurrentID += NextGroupID;
	if (NextGroupID == 0) Log::LogString("FindNextGroup Error:: Cancelled Bootloop"); return -1;

	//Check Next Group
	int FoundID = FindNextGroup(CurrentID, RetreivedShape);
	return FoundID;
}


int PageGroupItem::FindPreviousGroup(int CurrentID, ShapeData* RetreivedShape)
{
	//Found
	if (RetreivedShape->ShapeGroup.PageItem.ID = CurrentPageItem.ID)
	{
		cout << " Group: " << RetreivedShape->ShapeGroup.PageItem.ID << " Match Found!" << endl;
		cout << " Group Start : " << CurrentID - RetreivedShape->ShapeGroup.PageItem.ShapeOffset << endl;
		cout << "--------" << endl;
		return CurrentID - RetreivedShape->ShapeGroup.PageItem.ShapeOffset;
	};

	cout << " Group: " << RetreivedShape->ShapeGroup.PageItem.ID << " No Match" << endl;
	//Set up next group / Not found
	int NextGroupTranslation = RetreivedShape->ShapeGroup.PageItem.ShapeOffset - 1;
	RetreivedShape += NextGroupTranslation;
	CurrentID += NextGroupTranslation;

	//Check Next Group
	int FoundID = FindPreviousGroup(CurrentID, RetreivedShape);
	return FoundID;
}


void PageGroupItem::SetMouseAccess()
{
	if (CurrentPageItem.MouseAccess == true)
	{
		//cout << "PageItem Mouse access!" << endl;
		//Log::LogVec2("PageItem Position", CurrentShapeGroupPosition);
		//Log::LogVec2("PageItem Size", CurrentShapeGroupSize);

		//this->CurrentPageItem.Top = (CurrentPageItem.Position[1] + (CurrentPageItem.Size[1] / 2));
		//this->CurrentPageItem.Bottom = (CurrentPageItem.Position[1] - (CurrentPageItem.Size[1] / 2));
		//this->CurrentPageItem.Left = (CurrentPageItem.Position[0] - (CurrentPageItem.Size[0] / 2));
		//this->CurrentPageItem.Right = (CurrentPageItem.Position[0] + (CurrentPageItem.Size[0] / 2));

		for (int i = CurrentPageItem.ShapeStart; i < CurrentPageItem.ShapeStart + CurrentPageItem.ShapeCount + 1; i++)
		{
			//Log::LogString("yes mouse access");
			ShapeData* RetreivedShape = CurrentPage->GetShapeDataP(i);
			//RetreivedShape->ShapeGroup.PageItem.Top = CurrentShapeGroupTop;
			//RetreivedShape->ShapeGroup.PageItem.Bottom = CurrentShapeGroupBottom;
			//RetreivedShape->ShapeGroup.PageItem.Left = CurrentShapeGroupLeft;
			//RetreivedShape->ShapeGroup.PageItem.Right = CurrentShapeGroupRight;

			RetreivedShape->ShapeGroup.PageItem.Top = CurrentPageItem.Top;
			RetreivedShape->ShapeGroup.PageItem.Bottom = CurrentPageItem.Bottom;
			RetreivedShape->ShapeGroup.PageItem.Left = CurrentPageItem.Left;
			RetreivedShape->ShapeGroup.PageItem.Right = CurrentPageItem.Right;

			//cout << "GroupItem: " << RetreivedShape->GroupID << endl;
			//cout << "GroupItemTop " << RetreivedShape->ShapeGroup.PageItem.Top << endl;
			//cout << "GroupItemBottom " << RetreivedShape->ShapeGroup.PageItem.Bottom << endl;
			//cout << "GroupItemLeft " << RetreivedShape->ShapeGroup.PageItem.Left << endl;
			//cout << "GroupItemRight " << RetreivedShape->ShapeGroup.PageItem.Right << endl;
			//cout << "---- " << endl;
		}
	}
	else
	{
		for (int i = CurrentPageItem.ShapeStart; i < CurrentPageItem.ShapeStart + CurrentPageItem.ShapeCount; i++)
		{
			Log::LogString("no mouse access");
			ShapeData* RetreivedShape = CurrentPage->GetShapeDataP(i);
			RetreivedShape->ShapeGroup.PageItem.Top = -3;
			RetreivedShape->ShapeGroup.PageItem.Bottom = -3;
			RetreivedShape->ShapeGroup.PageItem.Left = 3;
			RetreivedShape->ShapeGroup.PageItem.Right = 3;
		}
	}


}

glm::vec2 PageGroupItem::GetBiggestMouseAccess(glm::vec2 Position, glm::vec2 Size)
{


}


//Working
int PageGroupItem::FindShapeGroup(bool FromBottom, double xMouse, double yMouse)
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
		//Log::LogInt("PageGroup:", RetreivedShape->ShapeGroup.PageItem.ID);
		if (xMouse < RetreivedShape->ShapeGroup.Right && xMouse >  RetreivedShape->ShapeGroup.Left&& yMouse < RetreivedShape->ShapeGroup.Top && yMouse >  RetreivedShape->ShapeGroup.Bottom)
		{
			//Found
			//cout << " Mouse Inside Region" << endl;
			//cout << " PageItem Start : " << CurrentID - RetreivedShape->ShapeGroup.PageItem.ShapeOffset << endl;
			return CurrentID - RetreivedShape->ShapeGroup.ShapeOffset;
		}

		//Not Found Set up NextGroup
		//cout << " Out Of Mouse Region " << endl;
		int NextGroupID = RetreivedShape->ShapeGroup.ShapeCount - RetreivedShape->ShapeGroup.ShapeOffset + 1;
		CurrentID += NextGroupID;
		RetreivedShape += NextGroupID;
	}

}

glm::vec2 PageGroupItem::ConvertEndToMiddle(glm::vec2 Position, glm::vec2 Size)
{
	Position[0] -= Size[0] / 2;
	return Position;
}

glm::vec2 PageGroupItem::ConvertBeginningToMiddle(glm::vec2 Position, glm::vec2 Size)
{
	Position[0] += Size[0] / 2;
	return Position;
}

void SwithToPageItem(int ShapeID)
{
	//if (SetInStone != true && ShapeID > -1 && ShapeID < CurrentPage->MaxShapeDataCount)
	//{
	//	this->LoadedShapeData = CurrentPage->GetShapeDataR(ShapeID);
	//}
}
//void PageGroupItem::llSwitch(int Offset)
//{
//	for (int i = 0; i < Offset; i++)
//	{
//		if (Offset > 0)
//		{
//			CurrentllPageItem = CurrentllPageItem->Next;
//		}
//		else if (Offset < 0)
//		{
//			CurrentllPageItem = CurrentllPageItem->Previous;
//		}
//	}
//}




llShapeGroupData* PageGroupItem::GetShapeGroup(int Index)
{
	int LoopIndex = 0;
	llShapeGroupData* CurrentShapeGroup = CurrentllPageItem->ShapeGroup;

	//Go to head
	while (CurrentShapeGroup->Previous != nullptr)
	{
		CurrentShapeGroup = CurrentShapeGroup->Previous;
	}

	while (LoopIndex != Index && CurrentShapeGroup->Next != nullptr)
	{
		CurrentShapeGroup = CurrentShapeGroup->Next;
		LoopIndex++;
	}

	return CurrentShapeGroup;
}

llShapeData* PageGroupItem::GetShapeGroupShape(int ShapeGroupIndex, int ShapeIndex)
{
	/////////////////////////////////ShapeGroup///////////////////////////////////
	int LoopIndex = 0;
	llShapeGroupData* CurrentShapeGroup = CurrentllPageItem->ShapeGroup;

	//Go to head
	while (CurrentShapeGroup->Previous != nullptr)
	{
		CurrentShapeGroup = CurrentShapeGroup->Previous;
	}

	while (LoopIndex != ShapeGroupIndex && CurrentShapeGroup->Next != nullptr)
	{
		CurrentShapeGroup = CurrentShapeGroup->Next;
		Log::LogInt(" ", LoopIndex);
		LoopIndex++;
	}


	/////////////////////////////Shape///////////////////////////////////////////////////
	int LoopIndex2 = 0;
	llShapeData* CurrentShape = CurrentShapeGroup->Shape;

	//Go to head
	while (CurrentShape->Previous != nullptr)
	{
		CurrentShape = CurrentShape->Previous;
	}

	while (LoopIndex2 != ShapeIndex && CurrentShape->Next != nullptr)
	{
		CurrentShape = CurrentShape->Next;
		Log::LogInt(" ", LoopIndex2);
		LoopIndex2++;
	}

	return CurrentShape;
}