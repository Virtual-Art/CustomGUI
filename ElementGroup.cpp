#include "ElementGroup.h"

ShapeGroup::ShapeGroup()
	:SetInStone(true)
{
	CurrentPage = nullptr;
}


ShapeGroup::ShapeGroup(llBookData* llBook)
	:SetInStone(true)
{
	if (llBook->Page == nullptr)
	{
		Log::LogString("Book Is Brand New");
		llPageData* CreatedPage = new llPageData;
		llPageGroupData* CreatedPageGroup = new llPageGroupData;
		llPageItemData* CreatedPageItem = new llPageItemData;

		llBook->Page = CreatedPage;
		llBook->PageHead = CreatedPage;

		llBook->Page->PageGroup = CreatedPageGroup;
		llBook->Page->PageGroupHead = CreatedPageGroup;

		llBook->Page->PageGroup->PageItem = CreatedPageItem;
		llBook->Page->PageGroup->PageItemHead = CreatedPageItem;
	}

	CurrentllShapeGroup = new llShapeGroupData;

	llShapeGroupData* TestingShapeGroup = llBook->Page->PageGroup->PageItem->ShapeGroup;

	//Completely new object
	if (TestingShapeGroup == nullptr)
	{
		Log::LogString("No ShapeGroup Found In PageItem, New ShapeGroup; Set!");
		llBook->Page->PageGroup->PageItem->ShapeGroup = CurrentllShapeGroup;
		llBook->Page->PageGroup->PageItem->ShapeGroupHead = CurrentllShapeGroup;
	}
	else //Shapes already created
	{
		Log::LogString("Existing ShapeGroup Found");
		llShapeGroupData* FoundTail = TestingShapeGroup;

		//Find tail then add
		while (FoundTail->Next != nullptr)
		{
			Log::LogString("Finding Tail..");
			FoundTail = FoundTail->Next;
		}
		Log::LogString("Set");
		FoundTail->Next = CurrentllShapeGroup;
		CurrentllShapeGroup->Previous = FoundTail;
		llBook->Page->PageGroup->PageItem->ShapeGroup = CurrentllShapeGroup;
	}

	CurrentllShapeGroup->Type = TYPE_CUSTOM;
	LoadedBook = llBook;
}

ShapeGroup::ShapeGroup(llBookData* llBookData, llShapeGroupData* llShapeGroup)
	:SetInStone(true)
{
	Log::LogString("Shape Creation Request with data");
	//If it exists
	if (llShapeGroup != nullptr)
	{
		if (llBookData->Page == nullptr)
		{
			Log::LogString("Book Is Brand New");
			llPageData* CreatedPage = new llPageData;
			llPageGroupData* CreatedPageGroup = new llPageGroupData;
			llPageItemData* CreatedPageItem = new llPageItemData;

			llBookData->Page = CreatedPage;
			llBookData->PageHead = CreatedPage;

			llBookData->Page->PageGroup = CreatedPageGroup;
			llBookData->Page->PageGroupHead = CreatedPageGroup;

			llBookData->Page->PageGroup->PageItem = CreatedPageItem;
			llBookData->Page->PageGroup->PageItemHead = CreatedPageItem;
		}

		CurrentllShapeGroup = new llShapeGroupData;
		*CurrentllShapeGroup = *llShapeGroup;

		llShapeGroupData* TestingShapeGroup = llBookData->Page->PageGroup->PageItem->ShapeGroup;

		//Completely new shapegroup object
		if (TestingShapeGroup == nullptr)
		{
			Log::LogString("This Page Item is Brand new");
			llBookData->Page->PageGroup->PageItem->ShapeGroup = CurrentllShapeGroup;
			llBookData->Page->PageGroup->PageItem->ShapeGroupHead = CurrentllShapeGroup;
		}
		else //Shape groups already created
		{
		    Log::LogString("this Page Item already contains a ShapeGroup");
			llShapeGroupData* FoundTail = TestingShapeGroup;

			//Find tail then add
			while (FoundTail->Next != nullptr)
			{
				Log::LogString("Finding Tail..");
				FoundTail = FoundTail->Next;
			}

			Log::LogString("Set");
			FoundTail->Next = CurrentllShapeGroup;
			CurrentllShapeGroup->Previous = FoundTail;
			//We are setting the book to point to this new shape group because that's where we want to load shapes
			//however the previous group is not lost because we set the next and previous
			llBookData->Page->PageGroup->PageItem->ShapeGroup = CurrentllShapeGroup;
		}

		LoadedBook = llBookData;
		CurrentllShapeGroup->Type = TYPE_CUSTOM;
	}
	else
	{
		Log::LogString("Sorry llShape was nullptr");
	}
}

ShapeGroup::ShapeGroup(llShapeGroupData* ShapeGroup)
	:SetInStone(true)
{
	//If it exists
	if (ShapeGroup != nullptr && ShapeGroup->Shape != nullptr)
	{

		CurrentllShapeGroup = ShapeGroup;
	}
	else
	{
		Log::LogString("Sorry llShapeGroup was nullptr or doesnt contain shapes");
	}
}

ShapeGroup::ShapeGroup(Page& Page)
	:SetInStone(true)
{
	if (&Page != nullptr)
	{
		//Setup
		Initialized = true;
		CurrentPage = &Page;
		CurrentShapeGroup.ShapeStart = Page.ShapeAmount();

		//Track Counts
		CurrentPage->TotalShapeGroupCount++;
		CurrentPage->CurrentShapeGroup++;

		CurrentShapeGroup.ID = CurrentPage->CurrentShapeGroup;

		//Reset Lower Level Group Count / ShapeCount
		CurrentPage->CurrentShape = -1;
		CurrentPage->CurrentShapeGroupShapeCount = -1;
	}
}

//Create a grid that is already set up & can be changed
//Group can't be switched with another
ShapeGroup::ShapeGroup(Page& Page, ShapeGroupData& ShapeGroupData)
	: SetInStone(true)
{
	if (&Page != nullptr)
	{
		//Setup
		Initialized = true;
		CurrentPage = &Page;
		CurrentShapeGroup = ShapeGroupData;
		CurrentShapeGroup.ShapeStart = Page.ShapeAmount();

		//Track Counts
		CurrentPage->TotalShapeGroupCount++;
		CurrentPage->CurrentShapeGroup++;

		CurrentShapeGroup.ID = CurrentPage->CurrentShapeGroup;

		//Reset Child Group Count / Shape Counts
		CurrentPage->CurrentShape = -1;
		CurrentPage->CurrentShapeGroupShapeCount = -1;
	}
}

//New 
ShapeGroup::ShapeGroup(Page& Page, ShapeData& ShapeData)
	: SetInStone(true)
{
	if (&Page != nullptr)
	{
		//Setup
		Initialized = true;
		CurrentPage = &Page;
		LoadedShape = ShapeData;
		LoadedShape.ShapeGroup.ShapeStart = Page.ShapeAmount();

		//Track Counts
		CurrentPage->TotalShapeGroupCount++;
		CurrentPage->CurrentShapeGroup++;

		//Reset Child Group Count/ Shape Count
		CurrentPage->CurrentShape = -1;
		CurrentPage->CurrentShapeGroupShapeCount = -1;
	}
}

//Group can be changed for another
ShapeGroup::ShapeGroup(Page& Page, int ID)
	: SetInStone(false)
{
	if (&Page != nullptr)
	{
		if (IsInBounds(ID) != false || ID != -1)
		{
			Initialized = true;
			CurrentPage = &Page;
			//CurrentPage->CurrentShapeGroupShapeCount = -1;
			LoadedShape = Page.GetShapeDataR(ID);
		}
	}
}

void ShapeGroup::SetGroup(ShapeData& ShapeData)
{
	this->LoadedShape = ShapeData;
	ReCalibrateID();
	Update();
}
void ShapeGroup::SetPosition(glm::vec2 Position)
{
	this->CurrentShapeGroup.Position = Position;
//	ReCalibrateID();
	this->Update();
}
void ShapeGroup::SetPosition(glm::vec2 Position, glm::vec2 bools)
{
	if (bools[0] == true)
	{
		this->CurrentShapeGroup.Position[0] = Position[0];
	}
	if (bools[1] == true)
	{
		this->CurrentShapeGroup.Position[1] = Position[1];
	}
	ReCalibrateID();
	Update();
}


void ShapeGroup::SetPosition(glm::vec2 Position, int Conversion)
{
	//Position Converstion
	Position = ApplyPositionConversion(Position, Conversion);
	this->CurrentShapeGroup.Position = Position;
	ReCalibrateID();
	this->Update();
}

void ShapeGroup::SetPosition(glm::vec2 Position, glm::vec2 bools, int Conversion)
{
	//Position Converstion
	Position = ApplyPositionConversion(Position, Conversion);

	if (bools[0] == true)
	{
		this->CurrentShapeGroup.Position[0] = Position[0];
	}
	if (bools[1] == true)
	{
		this->CurrentShapeGroup.Position[1] = Position[1];
	}
	ReCalibrateID();
	Update();
}

void ShapeGroup::SetSize(glm::vec2 Size)
{
	this->CurrentShapeGroup.Size = Size;
	ReCalibrateID();
	Update();
}

void ShapeGroup::SetSize(glm::vec2 Size, glm::vec2 bools)
{
	if (bools[0] == true)
	{
		this->CurrentShapeGroup.Size[0] = Size[0];
	}
	if (bools[1] == true)
	{
		this->CurrentShapeGroup.Size[1] = Size[1];
	}
	ReCalibrateID();
	Update();
}

void ShapeGroup::SetColor(glm::vec4 Color)
{
	this->CurrentShapeGroup.Color = Color;
	ReCalibrateID();
	Update();
}
void ShapeGroup::SetColor(glm::vec4 Color, glm::vec4 bools)
{
	if (bools[0] == true)
	{
		this->CurrentShapeGroup.Color[0] = Color[0];

	}
	if (bools[1] == true)
	{
		this->CurrentShapeGroup.Color[1] = Color[1];
	}
	if (bools[2] == true)
	{
		this->CurrentShapeGroup.Color[2] = Color[2];
	}
	if (bools[3] == true)
	{
		this->CurrentShapeGroup.Color[3] = Color[3];
	}
	ReCalibrateID();
	Update();
}


void ShapeGroup::OffsetPosition(glm::vec2 Position)
{
	this->CurrentShapeGroup.Position += Position;
	ReCalibrateID();
	Update();
}

void ShapeGroup::OffsetPosition(glm::vec2 Position, glm::vec2 bools)
{
	if (bools[0] == true)
	{
		this->CurrentShapeGroup.Position[0] += Position[0];
	}
	if (bools[1] == true)
	{
		this->CurrentShapeGroup.Position[1] += Position[1];
	}
	ReCalibrateID();
	Update();
}
void ShapeGroup::OffsetSize(glm::vec2 Size)
{
	this->CurrentShapeGroup.Size += Size;
	ReCalibrateID();
	Update();
}
void ShapeGroup::OffsetSize(glm::vec2 Size, glm::vec2 bools)
{
	if (bools[0] == true)
	{
		this->CurrentShapeGroup.Size[0] += Size[0];
	}
	if (bools[1] == true)
	{
		this->CurrentShapeGroup.Size[1] += Size[1];
	}
	ReCalibrateID();
	Update();
}

void ShapeGroup::OffsetColor(glm::vec4 Color)
{
	this->CurrentShapeGroup.Color += Color;
	ReCalibrateID();
	Update();
}
void ShapeGroup::OffsetColor(glm::vec4 Color, glm::vec4 bools)
{
	if (bools[0] == true)
	{
		this->CurrentShapeGroup.Color[0] += Color[0];

	}
	if (bools[1] == true)
	{
		this->CurrentShapeGroup.Color[1] += Color[1];
	}
	if (bools[2] == true)
	{
		this->CurrentShapeGroup.Color[2] += Color[2];
	}
	if (bools[3] == true)
	{
		this->CurrentShapeGroup.Color[3] += Color[3];
	}
	ReCalibrateID();
	Update();

}

void ShapeGroup::OffsetPosition(glm::vec2 Position, int Conversion)
{
	Position = ApplySizeConversion(Position, Conversion);
	this->CurrentShapeGroup.Position += Position;
	ReCalibrateID();
	Update();
}
void ShapeGroup::OffsetPosition(glm::vec2 Position, glm::vec2 bools, int Conversion)
{
	Position = ApplySizeConversion(Position, Conversion);

	if (bools[0] == true)
	{
		this->CurrentShapeGroup.Position[0] += Position[0];
	}
	if (bools[1] == true)
	{
		this->CurrentShapeGroup.Position[1] += Position[1];
	}
	ReCalibrateID();
	Update();
}
void ShapeGroup::OffsetSize(glm::vec2 Size, int Conversion)
{
	//Size Conversion
	Size = ApplySizeConversion(Size, Conversion);
	this->CurrentShapeGroup.Size += Size;
	ReCalibrateID();
	Update();
}
void ShapeGroup::OffsetSize(glm::vec2 Size, glm::vec2 bools, int Conversion)
{
	//Size Conversion
	Size = ApplySizeConversion(Size, Conversion);
	if (bools[0] == true)
	{
		this->CurrentShapeGroup.Size[0] += Size[0];
	}
	if (bools[1] == true)
	{
		this->CurrentShapeGroup.Size[1] += Size[1];
	}
	ReCalibrateID();
	Update();
}

//this does not set up page
//void ShapeGroup::ShapeToGroup(ShapeData& ShapeData)
//{
//	LoadedShape.ShapeGroup.ShapeStart   = ShapeData.ID;
//	LoadedShape.ShapeGroup.ID        = ShapeData.ID;
//	LoadedShape.ShapeGroup.Count          = ShapeData.ShapeGroup.ShapeCount + 1;
//	LoadedShape.ShapeGroup.XYShapesPerRow = ShapeData.ShapeGroupXYShapePerRow;
//	LoadedShape.ShapeGroup.ShapeDataSize  = ShapeData.ShapeGroupShapeSize;
//	LoadedShape.ShapeGroup.Position       = ShapeData.ShapeGroupPosition;
//	LoadedShape.ShapeGroup.Size           = ShapeData.ShapeGroupSize;
//	LoadedShape.ShapeGroup.Color          = ShapeData.ShapeGroupColor;
//	LoadedShape.ShapeGroup.MouseAccess    = ShapeData.ShapeGroup.MouseAccess;
//	LoadedShape.ShapeGroup.Centered       = ShapeData.ShapeGroupCentered;
//	LoadedShape.ShapeGroup.Highlighted    = ShapeData.ShapeGroupHighlighted;
//	LoadedShape.ShapeGroup.ShapeType      = ShapeData.ShapeDataType;
//
//	LoadedShape.ShapeGroup.PageItemID           = ShapeData.PageGroupItemID;
//	LoadedShape.ShapeGroup.PageItemShapeCount   = ShapeData.PageGroupItemShapeCount;
//	LoadedShape.ShapeGroup.PageItemShapeOffset  = ShapeData.PageGroupItemShapeOffset;
	//LoadedShape.ShapeGroup.PageItemShapeStart = ShapeData.PageGroupItemShapeStart;
//
//}

//this does not set up page
//void ShapeGroup::GroupToShape(GroupData& GroupData)

	//CurrentShape.ID = GroupData.ShapeStart;
	//CurrentShape.ShapeGroup.ShapeCount = GroupData.Count;
	//CurrentShape.ShapeGroup.ShapeCount = GroupData.Count;
	//CurrentShape.Position = GroupData.Position;
	//CurrentShape.Size = GroupData.Size;
	//CurrentShape.Color = GroupData.Color;
	//CurrentShape.MouseAccess = GroupData.MouseAccess;
	//CurrentShape.ShapeGroupCentered = GroupData.Centered;
	//CurrentShape.ShapeGroupHighlighted = GroupData.Highlighted;
	//CurrentShape.ShapeDataType = GroupData.ShapeType;
	//CurrentShape.ShapeGroupXYShapePerRow = GroupData.XYShapesPerRow;


void ShapeGroup::ReCalibrateID()
{
	if (Initialized == false) { Log::LogString("ReCalibrateID Failed:: ShapeGroup Not Initialized"); return; };

	cout << "Recalibrating Group (" << CurrentShapeGroup.ID << ") " << endl;

	int CurrentID = 0;
	int GroupStart = 0;

	//Maintenance
	if (IsInBounds(CurrentShapeGroup.ShapeStart) == true) // LoadedShape.ShapeGroup.ShapeStart < LoadedShape.ShapeGroup.Page->ShapeAmount())
	{
		//in range
		CurrentID = CurrentShapeGroup.ShapeStart;
		GroupStart = CurrentShapeGroup.ShapeStart;
	}
	if (IsInBounds(CurrentShapeGroup.ShapeStart) == false)
	{
		//out of range
		CurrentID = CurrentPage->ShapeAmount();
		GroupStart = CurrentPage->ShapeAmount();
	}

	///Check if ID is valid
	if (CurrentID > -1)
	{
		cout << "Checking ID: " << CurrentID << "... " << endl;
		ShapeData* RetreivedShape = CurrentPage->GetShapeDataP(CurrentID);

		//Group Calibrated
		if (RetreivedShape->ID == CurrentShapeGroup.ID)
		{
			//Set the ID
			CurrentShapeGroup.ShapeStart = CurrentID - RetreivedShape->ShapeGroup.ShapeOffset;
			cout << " Group: " << RetreivedShape->ID << " Match Found!" << endl;
			cout << "Group Start : " << CurrentID - RetreivedShape->ShapeGroup.ShapeOffset << endl;
			cout << "--------" << endl;
			return;
		}

		//Group UnCalibrated
		//if (RetreivedShape->PageID != LoadedShape.ShapeGroup.ID)
		if (RetreivedShape->ID != CurrentShapeGroup.ID)
		{
			//Go up
			//if(RetreivedShape->PageID <LoadedShape.ShapeGroup.ID)
			if (RetreivedShape->ID < CurrentShapeGroup.ID)
			{
				int Result = FindNextGroup(CurrentID, RetreivedShape);
				if (Result != -1)
				{
					CurrentShapeGroup.ShapeStart = Result;
					RetreivedShape->ShapeGroup.ShapeStart = Result;
					return;
				}
				Log::LogString("FindNextGroupError:: Returned -1"); return;
			}

			//GO down
			if (RetreivedShape->ID > CurrentShapeGroup.ID)
			{
				int Result = FindPreviousGroup(CurrentID, RetreivedShape);
				if (Result != -1)
				{
					CurrentShapeGroup.ShapeStart = Result;
					RetreivedShape->ShapeGroup.ShapeStart = CurrentShapeGroup.ShapeStart;
					return;
				}
				Log::LogString("FindPreviousGroupError:: Returned -1"); return;
			}
		}
	}
}

//Returns the ID of the first shape in the group
int ShapeGroup::FindNextGroup(int CurrentID, ShapeData* RetreivedShape)
{
	if (RetreivedShape == nullptr) return -1;
	//Found
 	if (RetreivedShape->ID == CurrentShapeGroup.ID) 
	{
		cout << " Group: " << RetreivedShape->ID << " Match Found!" << endl;
		cout << " Group Start : " << CurrentID - RetreivedShape->ShapeGroup.ShapeOffset << endl; 
		cout << "--------" << endl;
		return CurrentID - RetreivedShape->ShapeGroup.ShapeOffset;
	};

	//Set up next group 
	cout << " Group: " << RetreivedShape->ID << " No Match" << endl;
	int NextGroupTranslation = RetreivedShape->ShapeGroup.ShapeCount - RetreivedShape->ShapeGroup.ShapeOffset + 1;
	RetreivedShape += NextGroupTranslation;
	CurrentID += NextGroupTranslation;
	if (NextGroupTranslation == 0) Log::LogString("FindNextGroup Error:: Cancelled Bootloop"); return -1;
	
	//Check Next Group
	int FoundID = FindNextGroup(CurrentID, RetreivedShape);
	return FoundID;
}


int ShapeGroup::FindPreviousGroup(int CurrentID, ShapeData* RetreivedShape)
{
	if (RetreivedShape == nullptr) return -1;
	//Found
	if (RetreivedShape->ID = CurrentShapeGroup.ID)
	{
		cout << " Group: " << RetreivedShape->ID << " Match Found!" << endl;
		cout << " Group Start : " << CurrentID - RetreivedShape->ShapeGroup.ShapeOffset << endl;
		cout << "--------" << endl;
		return CurrentID - RetreivedShape->ShapeGroup.ShapeOffset; 
	};

	cout << " Group: " << RetreivedShape->ID << " No Match" << endl;
	//Set up next group / Not found
	int NextGroupTranslation = RetreivedShape->ShapeGroup.ShapeOffset - 1;
	RetreivedShape += NextGroupTranslation;
	CurrentID += NextGroupTranslation;

	if (NextGroupTranslation == 0) Log::LogString("FindPreviousGroup Error:: Cancelled Bootloop"); return -1;

	//Check Next Group
	int FoundID = FindPreviousGroup(CurrentID, RetreivedShape);
	return FoundID;
}

void ShapeGroup::SetMouseAccess()
{
	if (Initialized == false) { Log::LogString("SetMouseAccess Failed:: ShapeGroup Not Initialized"); return; };

	if (CurrentShapeGroup.MouseAccess == true)
	{
	
		//this->CurrentShape.ShapeGroup.Top = (LoadedShape.ShapeGroup.Position[1] + (LoadedShape.ShapeGroup.Size[1] / 2));
		//this->CurrentShape.ShapeGroup.Bottom = (LoadedShape.ShapeGroup.Position[1] - (LoadedShape.ShapeGroup.Size[1] / 2));
		//this->CurrentShape.ShapeGroup.Left = (LoadedShape.ShapeGroup.Position[0] - (LoadedShape.ShapeGroup.Size[0] / 2));
		//this->CurrentShape.ShapeGroup.Right = (LoadedShape.ShapeGroup.Position[0] + (LoadedShape.ShapeGroup.Size[0] / 2));

		for (int i = CurrentShapeGroup.ShapeStart; i < CurrentShapeGroup.ShapeStart + CurrentShapeGroup.ShapeCount; i++)
		{
			if(IsInBounds(i) != true) { Log::LogString("SetMouseAccess Failed:: ID out of bounds"); return; };

			//Set entire shape group 
			ShapeData& RetreivedShape = CurrentPage->GetShapeDataR(i);
			RetreivedShape.ShapeGroup.Top = CurrentShapeGroup.Top;
			RetreivedShape.ShapeGroup.Bottom = CurrentShapeGroup.Bottom;
			RetreivedShape.ShapeGroup.Left = CurrentShapeGroup.Left;
			RetreivedShape.ShapeGroup.Right = CurrentShapeGroup.Right;

			CurrentShapeGroup.Size[0] = CurrentShapeGroup.Right - CurrentShapeGroup.Left;
			CurrentShapeGroup.Size[1] = CurrentShapeGroup.Top - CurrentShapeGroup.Bottom;
		}
	}
}

void ShapeGroup::SetllMouseAccess()
{
	if (Initialized == false) { Log::LogString("SetMouseAccess Failed:: ShapeGroup Not Initialized"); return; };

	//if (CurrentllShapeGroup->MouseAccess == true)
	//{
	//
	//	//this->CurrentShape.ShapeGroup.Top = (LoadedShape.ShapeGroup.Position[1] + (LoadedShape.ShapeGroup.Size[1] / 2));
	//	//this->CurrentShape.ShapeGroup.Bottom = (LoadedShape.ShapeGroup.Position[1] - (LoadedShape.ShapeGroup.Size[1] / 2));
	//	//this->CurrentShape.ShapeGroup.Left = (LoadedShape.ShapeGroup.Position[0] - (LoadedShape.ShapeGroup.Size[0] / 2));
	//	//this->CurrentShape.ShapeGroup.Right = (LoadedShape.ShapeGroup.Position[0] + (LoadedShape.ShapeGroup.Size[0] / 2));
	//
	//	for (int i = CurrentShapeGroup.ShapeStart; i < CurrentShapeGroup.ShapeStart + CurrentShapeGroup.ShapeCount; i++)
	//	{
	//		if (IsInBounds(i) != true) { Log::LogString("SetMouseAccess Failed:: ID out of bounds"); return; };
	//
	//		//Set entire shape group 
	//		ShapeData& RetreivedShape = CurrentPage->GetShapeDataR(i);
	//		RetreivedShape.ShapeGroup.Top = CurrentShapeGroup.Top;
	//		RetreivedShape.ShapeGroup.Bottom = CurrentShapeGroup.Bottom;
	//		RetreivedShape.ShapeGroup.Left = CurrentShapeGroup.Left;
	//		RetreivedShape.ShapeGroup.Right = CurrentShapeGroup.Right;
	//
	//		CurrentShapeGroup.Size[0] = CurrentShapeGroup.Right - CurrentShapeGroup.Left;
	//		CurrentShapeGroup.Size[1] = CurrentShapeGroup.Top - CurrentShapeGroup.Bottom;
	//	}
	//}
}

void ShapeGroup::UpdateMouseAccess(glm::vec2 Position, glm::vec2 Size)
{
	if (CurrentShapeGroup.MouseAccess == false) return;

	float Left = Position[0] - (Size[0] / 2);
	float Right = Position[0] + (Size[0] / 2);
	float Top = Position[1] + (Size[1] / 2);
	float Bottom = Position[1] - (Size[1] / 2);

	if (Left < CurrentShapeGroup.Left || CurrentShapeGroup.Left == -3)
	{
		CurrentShapeGroup.Left = Left;
	}

	if (Right > CurrentShapeGroup.Right || CurrentShapeGroup.Right == -3)
	{
		CurrentShapeGroup.Right = Right;
	}

	if (Top > CurrentShapeGroup.Top || CurrentShapeGroup.Top == -3)
	{
		CurrentShapeGroup.Top = Top;
	}

	if (Bottom < CurrentShapeGroup.Bottom || CurrentShapeGroup.Bottom == -3)
	{
		CurrentShapeGroup.Bottom = Bottom;
	}

}

void ShapeGroup::UpdatellMouseAccess(glm::vec2 Position, glm::vec2 Size)
{
	if (CurrentllShapeGroup->MouseAccess == false) return;

	float Left = Position[0] - (Size[0] / 2);
	float Right = Position[0] + (Size[0] / 2);
	float Top = Position[1] + (Size[1] / 2);
	float Bottom = Position[1] - (Size[1] / 2);

	if (Left < CurrentllShapeGroup->Left || CurrentllShapeGroup->Left == -3)
	{
		CurrentllShapeGroup->Left = Left;
	}

	if (Right > CurrentllShapeGroup->Right || CurrentllShapeGroup->Right == -3)
	{
		CurrentllShapeGroup->Right = Right;
	}

	if (Top > CurrentllShapeGroup->Top || CurrentllShapeGroup->Top == -3)
	{
		CurrentllShapeGroup->Top = Top;
	}

	if (Bottom < CurrentllShapeGroup->Bottom || CurrentllShapeGroup->Bottom == -3)
	{
		CurrentllShapeGroup->Bottom = Bottom;
	}

}

void ShapeGroup::PrintGroupShapes()
{
	if (Initialized == false) return;
	
	for (int i = CurrentShapeGroup.ShapeStart; i < CurrentShapeGroup.ShapeStart + CurrentShapeGroup.ShapeCount - 1; i++)
	{
		if (IsInBounds(i) == false) return;
		CurrentPage->PrintShape(i);
	}
}

int ShapeGroup::GetCount()
{
	return CurrentShapeGroup.ShapeCount;
}

void ShapeGroup::llSwitch(llShapeGroupData* llShapeGroup)
{
	//If it exists
	if (llShapeGroup != nullptr)
	{
		CurrentllShapeGroup = llShapeGroup;
	}
	else
	{
		Log::LogString("Sorry llShapeGroup was nullptr or does not contain existing vertices");
	}
}

//void ShapeGroup::llSwitch(int Offset)
//{
//	for (int i = 0; i <Offset; i++)
//	{
//		if (Offset > 0)
//		{
//			CurrentllShapeGroup = CurrentllShapeGroup->Next;
//		}
//		else if(Offset < 0)
//		{
//			CurrentllShapeGroup = CurrentllShapeGroup->Previous;
//		}
//	}
//}

void ShapeGroup::NewllUpdate()
{
	llShapeData* CurrentShape = CurrentllShapeGroup->Shape;
	llShapeData* NullShape = nullptr;
	llShapeData UpdatedShape = *CurrentShape;
	Quad QuadRef(NullShape);
	NewCharacter CharRef(NullShape);

	while (CurrentShape->Next != nullptr)
	{
		UpdatedShape = *CurrentShape;
		UpdatedShape.Position = CurrentllShapeGroup->Position - CurrentShape->PositionOffset;
		UpdatedShape.Size = CurrentllShapeGroup->Size - CurrentShape->SizeOffset;
		UpdatedShape.Color = CurrentllShapeGroup->Color -  CurrentShape->ColorOffset;

		switch (CurrentShape->Type)
		{
		case TYPE_QUAD:
			//QuadRef.llSwitch(CurrentShape);
			QuadRef.SetllShape(&UpdatedShape);
			break;

		case TYPE_CHARACTER:
			//CharRef.llSwitch(CurrentShape);
			CharRef.SetllShape(&UpdatedShape);
			break;
		case TYPE_CUSTOM:
			//CustomRef.llSwitch(CurrentShape);
			//CustomRef.SetllShape(&UpdatedShape);
			break;
		}
	}
}