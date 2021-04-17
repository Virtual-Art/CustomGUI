#include "ElementGroup.h"

void ShapeGroup::llInit(llBookData* llBook)
{
	LoadedBook = llBook;
}

ShapeGroup::ShapeGroup()
	:SetInStone(true)
{
	LoadedBook = nullptr;
	CurrentllShapeGroup = nullptr;
}

ShapeGroup::ShapeGroup(llBookData* llBook)
	:SetInStone(true)
{
	//Validate
	if (llBook == nullptr)
	{
		if (llBook->Page == nullptr)
		{
			Log::LogString("Book Is Brand New");
			llPageData* CreatedPage = new llPageData;
			llPageGroupData* CreatedPageGroup = new llPageGroupData;
			llPageItemData* CreatedPageItem = new llPageItemData;

			llBook->Page = CreatedPage;
			llBook->PageHead = CreatedPage;
			llBook->PageCount++;

			llBook->Page->PageGroup = CreatedPageGroup;
			llBook->Page->PageGroupHead = CreatedPageGroup;
			llBook->Page->PageGroupCount++;

			llBook->Page->PageGroup->PageItem = CreatedPageItem;
			llBook->Page->PageGroup->PageItemHead = CreatedPageItem;
			llBook->Page->PageGroup->PageItemCount++;
		}

		if (llBook->Page->PageGroup == nullptr)
		{
			llPageGroupData* CreatedPageGroup = new llPageGroupData;
			llPageItemData* CreatedPageItem = new llPageItemData;

			llBook->Page->PageGroup = CreatedPageGroup;
			llBook->Page->PageGroupHead = CreatedPageGroup;
			llBook->Page->PageGroupCount++;

			llBook->Page->PageGroup->PageItem = CreatedPageItem;
			llBook->Page->PageGroup->PageItemHead = CreatedPageItem;
			llBook->Page->PageGroup->PageItemCount++;

		}

		if (llBook->Page->PageGroup->PageItem == nullptr)
		{
			llPageItemData* CreatedPageItem = new llPageItemData;

			llBook->Page->PageGroup->PageItem = CreatedPageItem;
			llBook->Page->PageGroup->PageItemHead = CreatedPageItem;
			llBook->Page->PageGroup->PageItemCount++;
		}

		CurrentllShapeGroup = new llShapeGroupData;

		llShapeGroupData* TestingShapeGroup = llBook->Page->PageGroup->PageItem->ShapeGroup;

		//Completely new object
		if (TestingShapeGroup == nullptr)
		{
			//Log::LogString("New ShapeGroup Linked");
			llBook->Page->PageGroup->PageItem->ShapeGroup = CurrentllShapeGroup;
			llBook->Page->PageGroup->PageItem->ShapeGroupHead = CurrentllShapeGroup;
			llBook->Page->PageGroup->PageItem->ShapeGroupCount++;
		}
		else //Shapes already created
		{
			llShapeGroupData* FoundTail = TestingShapeGroup;
			int LinkCount = 1;

			//Find tail then add
			//Log::LogString("Finding Tail..");
			while (FoundTail->Next != nullptr)
			{
				FoundTail = FoundTail->Next;
				LinkCount++;
			}
			//Log::LogString("New ShapeGroup Linked");
			FoundTail->Next = CurrentllShapeGroup;
			CurrentllShapeGroup->Previous = FoundTail;
			llBook->Page->PageGroup->PageItem->ShapeGroup = CurrentllShapeGroup;
			llBook->Page->PageGroup->PageItem->ShapeGroupCount++;
		}

		CurrentllShapeGroup->Type = TYPE_CUSTOM;
		LoadedBook = llBook;
		CurrentllShapeGroup->ParentGroup = llBook->Page->PageGroup->PageItem;
		Parent_PageItem = (llPageItemData*)CurrentllShapeGroup->ParentGroup;
		CalculateGroupOffset();
		ShapeGroupDirectory.Capture(LoadedBook);
	}
	else
	{
		Log::LogString("ERROR:: ShapeInit FAILED:: No Book Provided ");
	}
}

ShapeGroup::ShapeGroup(llBookData* llBookData, llShapeGroupData* llShapeGroup)
	:SetInStone(true)
{
	//Validate
	if (llShapeGroup != nullptr && llBookData != nullptr)
	{
		if (llBookData->Page == nullptr)
		{
			//Log::LogString("Book Is Brand New");
			llPageData* CreatedPage = new llPageData;
			llPageGroupData* CreatedPageGroup = new llPageGroupData;
			llPageItemData* CreatedPageItem = new llPageItemData;

			llBookData->Page = CreatedPage;
			llBookData->PageHead = CreatedPage;
			llBookData->PageCount++;

			llBookData->Page->PageGroup = CreatedPageGroup;
			llBookData->Page->PageGroupHead = CreatedPageGroup;
			llBookData->Page->PageGroupCount++;

			llBookData->Page->PageGroup->PageItem = CreatedPageItem;
			llBookData->Page->PageGroup->PageItemHead = CreatedPageItem;
			llBookData->Page->PageGroup->PageItemCount++;
		}

		if (llBookData->Page->PageGroup == nullptr)
		{
			llPageGroupData* CreatedPageGroup = new llPageGroupData;
			llPageItemData* CreatedPageItem = new llPageItemData;

			llBookData->Page->PageGroup = CreatedPageGroup;
			llBookData->Page->PageGroupHead = CreatedPageGroup;
			llBookData->Page->PageGroupCount++;

			llBookData->Page->PageGroup->PageItem = CreatedPageItem;
			llBookData->Page->PageGroup->PageItemHead = CreatedPageItem;
			llBookData->Page->PageGroup->PageItemCount++;
		}

		if (llBookData->Page->PageGroup->PageItem == nullptr)
		{
			llPageItemData* CreatedPageItem = new llPageItemData;

			llBookData->Page->PageGroup->PageItem = CreatedPageItem;
			llBookData->Page->PageGroup->PageItemHead = CreatedPageItem;
			llBookData->Page->PageGroup->PageItemCount++;
		}

		CurrentllShapeGroup = new llShapeGroupData;
		*CurrentllShapeGroup = *llShapeGroup;
		//Log::LogString("Shape Group Created");

		llShapeGroupData* TestingShapeGroup = llBookData->Page->PageGroup->PageItem->ShapeGroup;

		//Completely new shapegroup object
		if (TestingShapeGroup == nullptr)
		{
			//Log::LogString("New ShapeGroup Linked");
			llBookData->Page->PageGroup->PageItem->ShapeGroup = CurrentllShapeGroup;
			llBookData->Page->PageGroup->PageItem->ShapeGroupHead = CurrentllShapeGroup;
			llBookData->Page->PageGroup->PageItem->ShapeGroupCount++;
		}
		else //Shape groups already created
		{
			llShapeGroupData* FoundTail = TestingShapeGroup;
			int LinkCount = 1;

			//Find tail then add
			//Log::LogString("Finding Tail..");
			while (FoundTail->Next != nullptr)
			{
				FoundTail = FoundTail->Next;
				LinkCount++;
			}

			//Log::LogString("New ShapeGroup Linked");
			FoundTail->Next = CurrentllShapeGroup;
			CurrentllShapeGroup->Previous = FoundTail;
			//We are setting the book to point to this new shape group because that's where we want to load shapes
			//however the previous group is not lost because we set the next and previous
			llBookData->Page->PageGroup->PageItem->ShapeGroup = CurrentllShapeGroup;
			llBookData->Page->PageGroup->PageItem->ShapeGroupCount++;
		}

		LoadedBook = llBookData;
		CurrentllShapeGroup->Type = TYPE_CUSTOM;
		CurrentllShapeGroup->ParentGroup = llBookData->Page->PageGroup->PageItem;
		Parent_PageItem = (llPageItemData*)CurrentllShapeGroup->ParentGroup;
		CalculateGroupOffset();
		ShapeGroupDirectory.Capture(LoadedBook);
	}
	else{ Log::LogString("ERROR:: ShapeGroup FAILED:: No Book Provided "); }
}

ShapeGroup::ShapeGroup(llShapeGroupData* ShapeGroup)
	:SetInStone(true)
{
	//If it exists
	if (ShapeGroup != nullptr )
	{

		CurrentllShapeGroup = ShapeGroup;
	}
	else
	{
		Log::LogString("ERROR:: ShapeGroup FAILED:: ShapeGroup was nullptr ");
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

void ShapeGroup::Add_Default()
{
	//Validate
	if (LoadedBook == nullptr) { Log::LogString("ERROR:: Add_Default ShapeGroup FAILED:: No Book Provided "); return; }

	if (LoadedBook->Page == nullptr)
	{
		Log::LogString("Book Is Brand New");
		llPageData* CreatedPage = new llPageData;
		llPageGroupData* CreatedPageGroup = new llPageGroupData;
		llPageItemData* CreatedPageItem = new llPageItemData;

		LoadedBook->Page = CreatedPage;
		LoadedBook->PageHead = CreatedPage;

		LoadedBook->Page->PageGroup = CreatedPageGroup;
		LoadedBook->Page->PageGroupHead = CreatedPageGroup;

		LoadedBook->Page->PageGroup->PageItem = CreatedPageItem;
		LoadedBook->Page->PageGroup->PageItemHead = CreatedPageItem;
	}

	if (LoadedBook->Page->PageGroup == nullptr)
	{
		llPageGroupData* CreatedPageGroup = new llPageGroupData;
		llPageItemData* CreatedPageItem = new llPageItemData;

		LoadedBook->Page->PageGroup = CreatedPageGroup;
		LoadedBook->Page->PageGroupHead = CreatedPageGroup;

		LoadedBook->Page->PageGroup->PageItem = CreatedPageItem;
		LoadedBook->Page->PageGroup->PageItemHead = CreatedPageItem;

	}

	if (LoadedBook->Page->PageGroup->PageItem == nullptr)
	{
		llPageItemData* CreatedPageItem = new llPageItemData;

		LoadedBook->Page->PageGroup->PageItem = CreatedPageItem;
		LoadedBook->Page->PageGroup->PageItemHead = CreatedPageItem;

	}

	CurrentllShapeGroup = new llShapeGroupData;
	//Log::LogString("Shape Group Created");

	llShapeGroupData* TestingShapeGroup = LoadedBook->Page->PageGroup->PageItem->ShapeGroup;

	//Completely new object
	if (TestingShapeGroup == nullptr)
	{
		Log::LogString("New ShapeGroup Linked");
		LoadedBook->Page->PageGroup->PageItem->ShapeGroup = CurrentllShapeGroup;
		LoadedBook->Page->PageGroup->PageItem->ShapeGroupHead = CurrentllShapeGroup;
	}
	else //Shapes already created
	{
		llShapeGroupData* FoundTail = TestingShapeGroup;
		int LinkCount = 1;

		//Find tail then add
		//Log::LogString("Finding Tail..");
		while (FoundTail->Next != nullptr)
		{
			FoundTail = FoundTail->Next;
			LinkCount++;
		}
		Log::LogString("New ShapeGroup Linked");
		FoundTail->Next = CurrentllShapeGroup;
		CurrentllShapeGroup->Previous = FoundTail;
		LoadedBook->Page->PageGroup->PageItem->ShapeGroup = CurrentllShapeGroup;
		CurrentllShapeGroup->Type = TYPE_SHAPEGROUP;
	}

}

void ShapeGroup::Add_Duplicate()
{
	//Validate
	if (LoadedBook == nullptr) { Log::LogString("ERROR:: Add_Duplicate ShapeGroup FAILED:: No Book Provided "); return; }
	if (CurrentllShapeGroup == nullptr) { Log::LogString("ERROR:: Add_Duplicate ShapeGroup FAILED:: Invalid ShapeGroup State"); return; }

	CopyShapeGroup(LoadedBook, CurrentllShapeGroup);
}

void ShapeGroup::Add_Insert()
{

}

void ShapeGroup::Delete()
{
	//Validate
	if (CurrentllShapeGroup == nullptr) { Log::LogString("ERROR:: Delete Shape FAILED:: Invalid Shape State"); return; }
	if (CurrentllShapeGroup->Shape == nullptr) { Log::LogString("ERROR:: Delete Shape FAILED:: Shape Does not Contain Vertices"); return; }

	//Prep
	llShapeData* CurrentShape = CurrentllShapeGroup->Shape;
	llShapeData* Next = nullptr;

	//Save ShapeGroup Before and After Current
	llShapeGroupData* PreviousllShapeGroup = CurrentllShapeGroup->Previous;
	llShapeGroupData* NextllShapeGroup = CurrentllShapeGroup->Next;

	if (NextllShapeGroup != nullptr)
	{
		LoadedBook->Page->PageGroup->PageItem->ShapeGroup = NextllShapeGroup;
	}
	else
	{
		LoadedBook->Page->PageGroup->PageItem->ShapeGroup = PreviousllShapeGroup;
	}

	//Delete all Shapes
	while (CurrentShape != nullptr)
	{
		//Delete current Shape, go to next
		Next = CurrentShape->Next;
	    DeleteShape(LoadedBook, CurrentShape);
		CurrentShape = Next;
	}

	//Delete ShapeGroup
	CurrentllShapeGroup->Shape = nullptr;
	delete CurrentllShapeGroup;
	CurrentllShapeGroup = nullptr;

	//Link any valid shapegroups back together
	if (PreviousllShapeGroup != nullptr) { PreviousllShapeGroup->Next = NextllShapeGroup; }
	if (NextllShapeGroup != nullptr) { NextllShapeGroup->Previous = PreviousllShapeGroup; }
}

void ShapeGroup::HighlightShapeGroup(glm::vec4 HighlightColor)
{
	//Validate
	if (CurrentllShapeGroup == nullptr) { Log::LogString("ERROR:: HighlightShapeGroup ShapeGroup FAILED:: Invalid ShapeGroup State "); return; }

	CurrentllShapeGroup->HighlightColor = HighlightColor;
	CurrentllShapeGroup->Highlighted = true;
	llUpdate();
}

void ShapeGroup::HighlightOff()
{
	//Validate
	if (CurrentllShapeGroup == nullptr) { Log::LogString("ERROR:: HighlightOff ShapeGroup FAILED:: Invalid ShapeGroup State "); return; }

	CurrentllShapeGroup->Highlighted = false;
	llUpdate();
}

void ShapeGroup::llShapeGroupInit(llBookData* llBookData, llShapeGroupData* llShapeGroup)
{
	//Validate
	if (llShapeGroup == nullptr) { Log::LogString("ERROR:: ShapeGroupInit FAILED:: No ShapeGroup Provided"); }
	if (llBookData == nullptr) { Log::LogString("ERROR:: ShapeGroupInit FAILED:: No Book Provided "); }

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

	if (llBookData->Page->PageGroup == nullptr)
	{
		llPageGroupData* CreatedPageGroup = new llPageGroupData;
		llPageItemData* CreatedPageItem = new llPageItemData;
		llShapeGroupData* CreatedShapeGroup = new llShapeGroupData;

		llBookData->Page->PageGroup = CreatedPageGroup;
		llBookData->Page->PageGroupHead = CreatedPageGroup;

		llBookData->Page->PageGroup->PageItem = CreatedPageItem;
		llBookData->Page->PageGroup->PageItemHead = CreatedPageItem;

		llBookData->Page->PageGroup->PageItem->ShapeGroup = CreatedShapeGroup;
		llBookData->Page->PageGroup->PageItem->ShapeGroupHead = CreatedShapeGroup;
	}

	if (llBookData->Page->PageGroup->PageItem == nullptr)
	{
		llPageItemData* CreatedPageItem = new llPageItemData;
		llShapeGroupData* CreatedShapeGroup = new llShapeGroupData;

		llBookData->Page->PageGroup->PageItem = CreatedPageItem;
		llBookData->Page->PageGroup->PageItemHead = CreatedPageItem;

		llBookData->Page->PageGroup->PageItem->ShapeGroup = CreatedShapeGroup;
		llBookData->Page->PageGroup->PageItem->ShapeGroupHead = CreatedShapeGroup;
	}

	CurrentllShapeGroup = new llShapeGroupData;
	*CurrentllShapeGroup = *llShapeGroup;

	llShapeGroupData* TestingShapeGroup = llBookData->Page->PageGroup->PageItem->ShapeGroup;

	//Completely new shapegroup object
	if (TestingShapeGroup == nullptr)
	{
		Log::LogString("New ShapeGroup Linked");
		llBookData->Page->PageGroup->PageItem->ShapeGroup = CurrentllShapeGroup;
		llBookData->Page->PageGroup->PageItem->ShapeGroupHead = CurrentllShapeGroup;
	}
	else //Shape groups already created
	{
		llShapeGroupData* FoundTail = TestingShapeGroup;
		int LinkCount = 1;

		//Find tail then add
		//Log::LogString("Finding Tail..");
		while (FoundTail->Next != nullptr)
		{
			FoundTail = FoundTail->Next;
			LinkCount++;
		}

		Log::LogString("New ShapeGroup Linked");
		FoundTail->Next = CurrentllShapeGroup;
		CurrentllShapeGroup->Previous = FoundTail;
		//We are setting the book to point to this new shape group because that's where we want to load shapes
		//however the previous group is not lost because we set the next and previous
		llBookData->Page->PageGroup->PageItem->ShapeGroup = CurrentllShapeGroup;
	}

	LoadedBook = llBookData;
	CurrentllShapeGroup->Type = TYPE_CUSTOM;
	CurrentllShapeGroup->ParentGroup = llBookData->Page->PageGroup->PageItem;
	Parent_PageItem = (llPageItemData*)CurrentllShapeGroup->ParentGroup;
	CalculateGroupOffset();
}

void ShapeGroup::SetllShapeGroup(llShapeGroupData* llShapeGroup)
{
	//Validate
	if (llShapeGroup == nullptr) { Log::LogString("ERROR:: SetllShapeGroup FAILED:: No ShapeGroup Provided"); return; }
	if (CurrentllShapeGroup == nullptr) { Log::LogString("ERROR:: SetllShapeGroup FAILED:: Invalid ShapeGroup State "); return; }

	*CurrentllShapeGroup = *llShapeGroup;
	llUpdate();
}


// This shape group may have quads, characters, custom shapes
void ShapeGroup::llUpdate()
{
	if (LoadedBook == nullptr) { Log::LogString("ERROR:: llUpdate FAILED:: Invalid Book State"); return; };
	if (CurrentllShapeGroup == nullptr) { Log::LogString("ERROR:: llUpdate FAILED:: ShapeGroup nullptr"); return; };
	if (CurrentllShapeGroup->Shape == nullptr) { Log::LogString("WARNING:: llUpdate FAILED:: No Contents in Shape Group To Update"); return; };

	//CalculateGroupOffset();

	////Group is false by default
	//if (CurrentllShapeGroup->ChangeAsGroup == false)
	//{
	//	//Set PageItem Position Offset
	//	llPageItemData* CurrentPageItem = LoadedBook->Page->PageGroup->PageItem;
	//	CurrentllShapeGroup->PositionOffset = CurrentPageItem->Position - CurrentllShapeGroup->Position;
	//}

	//Log::LogString("Updating ShapeGroup");
	llShapeData* CurrentShape = CurrentllShapeGroup->Shape;

	//Go to head Shape
	while (CurrentShape->Previous != nullptr)
	{
		CurrentShape = CurrentShape->Previous;
	}

	//Set All sub group positions and call sub group functions
	while (CurrentShape != nullptr)
	{
		switch (CurrentShape->Type)
		{
		case TYPE_SHAPE:
		{
			Shape ShapeSelected(CurrentShape);
			ShapeSelected.LoadedBook = LoadedBook;
			ShapeSelected.llSwitch(CurrentShape);
			CurrentShape->Position = CurrentllShapeGroup->Position + CurrentShape->PositionOffset;
			CurrentShape->Highlighted = CurrentllShapeGroup->Highlighted;
			CurrentShape->HighlightColor = CurrentllShapeGroup->HighlightColor;
			CurrentShape->Hide = CurrentllShapeGroup->Hide;
			CurrentShape->MouseAccess = CurrentllShapeGroup->MouseAccess;
			//CurrentShape->Size = CurrentllShapeGroup->Size + CurrentShape->SizeOffset;
			//CurrentShape->Color = CurrentllShapeGroup->Color + CurrentShape->ColorOffset;
			CurrentShape->ChangeAsGroup = true;
			ShapeSelected.SetllShape(CurrentShape);
			break;
		}
		case TYPE_QUAD:
		{
			Quad QuadSelected(CurrentShape);
			QuadSelected.LoadedBook = LoadedBook;
			QuadSelected.llSwitch(CurrentShape);
			CurrentShape->Position = CurrentllShapeGroup->Position + CurrentShape->PositionOffset;
			CurrentShape->Highlighted = CurrentllShapeGroup->Highlighted;
			CurrentShape->HighlightColor = CurrentllShapeGroup->HighlightColor;
			//CurrentShape->Size = CurrentllShapeGroup->Size + CurrentShape->SizeOffset;
			//CurrentShape->Color = CurrentllShapeGroup->Color + CurrentShape->ColorOffset;
			CurrentShape->Hide = CurrentllShapeGroup->Hide;
			CurrentShape->MouseAccess = CurrentllShapeGroup->MouseAccess;
			CurrentShape->ChangeAsGroup = true;
			QuadSelected.SetllShape(CurrentShape);
			break;
		}
		case TYPE_CHARACTER:
		{
			NewCharacter CharSelected(CurrentShape);
			//CharSelected.SetParent(LoadedBook);
			CharSelected.LoadedBook = LoadedBook;
			CharSelected.llSwitch(CurrentShape);
			CurrentShape->Position = CurrentllShapeGroup->Position + CurrentShape->PositionOffset;
			CurrentShape->Highlighted = CurrentllShapeGroup->Highlighted;
			CurrentShape->HighlightColor = CurrentllShapeGroup->HighlightColor;
			//CurrentShape->Size = CurrentllShapeGroup->Size + CurrentShape->SizeOffset;
			//CurrentShape->Color = CurrentllShapeGroup->Color + CurrentShape->ColorOffset;
			CurrentShape->Hide = CurrentllShapeGroup->Hide;
			CurrentShape->MouseAccess = CurrentllShapeGroup->MouseAccess;
			CurrentShape->ChangeAsGroup = true;
			CharSelected.SetllShape(CurrentShape);
			break;
		}
		}
		CurrentShape = CurrentShape->Next;
	
	}

	SetllMouseAccess();
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
	//Validate
	if (CurrentllShapeGroup == nullptr) { Log::LogString("ERROR:: OffsetPosition FAILED:: Invalid ShapeGroup State"); return; };

	if (bools[0] == true)
	{
		CurrentllShapeGroup->Position[0] += Position[0];
	}
	if (bools[1] == true)
	{
		CurrentllShapeGroup->Position[1] += Position[1];
	}

	llUpdate();
}
void ShapeGroup::OffsetSize(glm::vec2 Size)
{
	if (CurrentllShapeGroup == nullptr) { Log::LogString("ERROR:: OffsetSize FAILED:: Invalid ShapeGroup State"); return; };
	CurrentllShapeGroup->Size += Size;
	llUpdate();
}
void ShapeGroup::OffsetSize(glm::vec2 Size, glm::vec2 bools)
{
	if (CurrentllShapeGroup == nullptr) { Log::LogString("ERROR:: OffsetSize w/ bools FAILED:: Invalid ShapeGroup State"); return; };
	if (bools[0] == true)
	{
		CurrentllShapeGroup->Size[0] += Size[0];
	}
	if (bools[1] == true)
	{
		CurrentllShapeGroup->Size[1] += Size[1];
	}
	llUpdate();
}

void ShapeGroup::OffsetColor(glm::vec4 Color)
{
	if (CurrentllShapeGroup == nullptr) { Log::LogString("ERROR:: OffsetColor FAILED:: Invalid ShapeGroup State"); return; };
	CurrentllShapeGroup->Color += Color;
	llUpdate();
}
void ShapeGroup::OffsetColor(glm::vec4 Color, glm::vec4 bools)
{
	if (CurrentllShapeGroup == nullptr) { Log::LogString("ERROR:: OffsetColor w/ bools FAILED::  Invalid ShapeGroup State"); return; };
	if (bools[0] == true)
	{
		if (CurrentllShapeGroup->Color[0] == Color[0]) { return; }
		CurrentllShapeGroup->Color[0] += Color[0];

	}
	if (bools[1] == true)
	{
		if (CurrentllShapeGroup->Color[1] == Color[1]) { return; }
		CurrentllShapeGroup->Color[1] += Color[1];
	}
	if (bools[2] == true)
	{
		if (CurrentllShapeGroup->Color[2] == Color[2]) { return; }
		CurrentllShapeGroup->Color[2] += Color[2];
	}
	if (bools[3] == true)
	{
		if (CurrentllShapeGroup->Color[3] == Color[3]) { return; }
		CurrentllShapeGroup->Color[3] += Color[3];
	}
	llUpdate();

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
	//Checks
	if (CurrentllShapeGroup == nullptr) { Log::LogString("ERROR::SetllMouseAccess FAILED::Invalid ShapeGroup State "); return; };
	if (CurrentllShapeGroup->Shape == nullptr) { Log::LogString("ERROR::SetllMouseAccess FAILED::No Shapes in ShapeGroup"); return; };

	//Setup
	llShapeData* CurrentShape = CurrentllShapeGroup->Shape;

	//Go to Head Shape
	while (CurrentShape->Previous != nullptr)
	{
		CurrentShape = CurrentShape->Previous;
	}

	//Skip BackGround Shape
	if (CurrentllShapeGroup->BackGround == true && CurrentShape->Next != nullptr)
	{
		CurrentShape = CurrentShape->Next;
	}

	//The First Shape
	float FurthestRight = CurrentShape->Right;
	float FurthestLeft = CurrentShape->Left;
	float FurthestTop = CurrentShape->Top;
	float FurthestBottom = CurrentShape->Bottom;

	if (CurrentShape->Next != nullptr)
	{
		CurrentShape = CurrentShape->Next;
	}
	//Log::LogString("Start of MouseAccess");
	//Compare CurrentShape's Access variables with all other shapes
	while (CurrentShape != nullptr)
	{
		//Log::LogFloat("Right ", CurrentllShapeGroup->Right);
		//Log::LogFloat("Left  ", CurrentllShapeGroup->Left);
		//Log::LogFloat("Top   ", CurrentllShapeGroup->Top);
		//Log::LogFloat("Bottom", CurrentllShapeGroup->Bottom);

		//Furthest Right is the most positive number
		if (FurthestRight < CurrentShape->Right) //
		{
			FurthestRight = CurrentShape->Right;
		}

		//Furthest Left is the most negative number
		if (FurthestLeft > CurrentShape->Left) //
		{
			FurthestLeft = CurrentShape->Left;
		}

		//Furthest Top is the most positive number
		if (FurthestTop < CurrentShape->Top) //
		{
			FurthestTop = CurrentShape->Top;
		}

		//Furthest Bottom is the most negative number
		if (FurthestBottom > CurrentShape->Bottom) //
		{
			FurthestBottom = CurrentShape->Bottom;
		}

		CurrentShape = CurrentShape->Next;
	}

	//Set ShapeGroup
	CurrentllShapeGroup->Right = FurthestRight;
	CurrentllShapeGroup->Left = FurthestLeft;
	CurrentllShapeGroup->Top = FurthestTop;
	CurrentllShapeGroup->Bottom = FurthestBottom;

	CurrentllShapeGroup->EdgesWithBackGround = { FurthestLeft , FurthestRight, FurthestTop, FurthestBottom };

	CurrentllShapeGroup->Size[X_AXIS] = FurthestRight - FurthestLeft; //Correct
	CurrentllShapeGroup->Size[Y_AXIS] = FurthestTop - FurthestBottom; //Correct

	//Set BackGround Will update the Mouse Access
	SetBackGround();

	//SizeFromEdges(GetEdgesWithBackGround(), CurrentllShapeGroup->Size);
	//Log::LogFloat("Right", CurrentllShapeGroup->EdgesWithBackGround[EDGE_RIGHT]);
	//Log::LogFloat("Left", CurrentllShapeGroup->EdgesWithBackGround[EDGE_LEFT]);
	//Log::LogFloat("Size = Right - Left", (CurrentllShapeGroup->EdgesWithBackGround[EDGE_RIGHT] - CurrentllShapeGroup->EdgesWithBackGround[EDGE_LEFT]));

	//CurrentllShapeGroup->Size[X_AXIS] = CurrentllShapeGroup->EdgesWithBackGround[EDGE_RIGHT] - CurrentllShapeGroup->EdgesWithBackGround[EDGE_LEFT]; //Correct
	//CurrentllShapeGroup->Size[Y_AXIS] = CurrentllShapeGroup->EdgesWithBackGround[EDGE_TOP] - CurrentllShapeGroup->EdgesWithBackGround[EDGE_BOTTOM]; //Correct
	

	//Set Input if not already set
	if (CurrentllShapeGroup->InputType != INPUT_LEFT || Input_Left_Once == true)
	{
		//Uses Size w/ BackGround
		//Uses Position
		ConvertInputToInputLeft();
		WithNewInput = true;
		llUpdate();
	}


	
}

void ShapeGroup::CalculateGroupOffset()
{
	if (LoadedBook == nullptr) { Log::LogString("ERROR:: Calculate ShapeGroup Offset FAILED:: Invalid Book State"); return; }
	if (Parent_PageItem == nullptr) { Log::LogString("ERROR:: Calculate ShapeGroup Offset FAILED:: Can't Find Parent Group"); return; }

	CurrentllShapeGroup->PositionOffset = CurrentllShapeGroup->Position - Parent_PageItem->Position;

	//cout << "ShapeGroup Position Offset: " << CurrentllShapeGroup->PositionOffset[0] << " , " << CurrentllShapeGroup->PositionOffset[1] << " = (ShapeGroup Position) " << CurrentllShapeGroup->Position[0] << " , " << CurrentllShapeGroup->Position[1] << " - " << "(Parent Position) " << Parent_PageItem->Position[0] << " , " << Parent_PageItem->Position[1] << endl;

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

//void ShapeGroup::UpdatellMouseAccess(glm::vec2 Position, glm::vec2 Size)
//{
//	if (CurrentllShapeGroup->MouseAccess == false) return;
//
//	float Left = Position[0] - (Size[0] / 2);
//	float Right = Position[0] + (Size[0] / 2);
//	float Top = Position[1] + (Size[1] / 2);
//	float Bottom = Position[1] - (Size[1] / 2);
//
//	if (Left < CurrentllShapeGroup->Left || CurrentllShapeGroup->Left == -3)
//	{
//		CurrentllShapeGroup->Left = Left;
//	}
//
//	if (Right > CurrentllShapeGroup->Right || CurrentllShapeGroup->Right == -3)
//	{
//		CurrentllShapeGroup->Right = Right;
//	}
//
//	if (Top > CurrentllShapeGroup->Top || CurrentllShapeGroup->Top == -3)
//	{
//		CurrentllShapeGroup->Top = Top;
//	}
//
//	if (Bottom < CurrentllShapeGroup->Bottom || CurrentllShapeGroup->Bottom == -3)
//	{
//		CurrentllShapeGroup->Bottom = Bottom;
//	}
//
//}

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
		Parent_PageItem = (llPageItemData*)llShapeGroup->ParentGroup;
	}
	else
	{
		Log::LogString("ERROR::ShapeGroup Switch FAILED:: ShapeGroup Provided was null");
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
	//Validate
	if (CurrentllShapeGroup == nullptr) { Log::LogString("ERROR:: NewllUpdate FAILED:: Invalid ShapeGroup State"); return; };

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

glm::vec4 ShapeGroup::GetEdges()
{
	return {CurrentllShapeGroup->Left, CurrentllShapeGroup->Right, CurrentllShapeGroup->Top, CurrentllShapeGroup->Bottom} ;
}

glm::vec4 ShapeGroup::GetEdgesWithBackGround()
{
	return CurrentllShapeGroup->EdgesWithBackGround;
}

void ShapeGroup::AttachButton(Button* Button)
{
	CurrentllShapeGroup->ShapeGroupButton = Button;
}

float ShapeGroup::GetAccessRight()
{
	//Validate 
	if (CurrentllShapeGroup == nullptr) { Log::LogString("ERROR:: GetAccessRight FAILED:: Invalid ShapeGroup State"); return 0.0; };

	return CurrentllShapeGroup->Right;
}

float ShapeGroup::GetAccessLeft()
{
	//Validate 
	if (CurrentllShapeGroup == nullptr) { Log::LogString("ERROR:: GetAccessLeft FAILED:: Invalid ShapeGroup State"); return 0.0; };

	return CurrentllShapeGroup->Left;
}


float ShapeGroup::GetAccessTop()
{
	//Validate 
	if (CurrentllShapeGroup == nullptr) { Log::LogString("ERROR:: GetAccessTop FAILED:: Invalid ShapeGroup State"); return 0.0; };

	return CurrentllShapeGroup->Top;
}


float ShapeGroup::GetAccessBottom()
{
	//Validate 
	if (CurrentllShapeGroup == nullptr) { Log::LogString("ERROR:: GetAccessBottom FAILED:: Invalid ShapeGroup State"); return 0.0; };

	return CurrentllShapeGroup->Bottom;
}


float ShapeGroup::GetAccessRight(int PixelOffset)
{
	//Validate 
	if (CurrentllShapeGroup == nullptr) { Log::LogString("ERROR:: GetAccessRight FAILED:: Invalid ShapeGroup State"); return 0.0; };

	return CurrentllShapeGroup->Right + PIXEL * PixelOffset;
}

float ShapeGroup::GetAccessLeft(int PixelOffset)
{
	//Validate 
	if (CurrentllShapeGroup == nullptr) { Log::LogString("ERROR:: GetAccessLeft FAILED:: Invalid ShapeGroup State"); return 0.0; };

	return CurrentllShapeGroup->Left + PIXEL * PixelOffset;
}


float ShapeGroup::GetAccessTop(int PixelOffset)
{
	//Validate 
	if (CurrentllShapeGroup == nullptr) { Log::LogString("ERROR:: GetAccessTop FAILED:: Invalid ShapeGroup State"); return 0.0; };

	return CurrentllShapeGroup->Top + PIXEL * PixelOffset;
}


float ShapeGroup::GetAccessBottom(int PixelOffset)
{
	//Validate 
	if (CurrentllShapeGroup == nullptr) { Log::LogString("ERROR:: GetAccessBottom FAILED:: Invalid ShapeGroup State"); return 0.0; };

	return CurrentllShapeGroup->Bottom + PIXEL * PixelOffset;
}

void ShapeGroup::Hide()
{
	if (CurrentllShapeGroup == nullptr) { Log::LogString("ERROR:: ShapeGroup Hide FAILED:: Invalid ShapeGroup State"); return; }
	if (CurrentllShapeGroup->Hide == true) { Log::LogString("Skipped"); return; }
	
	CurrentllShapeGroup->Hide = true;
	CurrentllShapeGroup->MouseAccess = false;
	llUpdate();
}

void ShapeGroup::UnHide()
{
	if (CurrentllShapeGroup == nullptr) { Log::LogString("ERROR:: ShapeGroup Hide FAILED:: Invalid ShapeGroup State"); return; }
	if (CurrentllShapeGroup->Hide == false) { return; }

	CurrentllShapeGroup->Hide = false;
	CurrentllShapeGroup->MouseAccess = true;
	llUpdate();
}

void ShapeGroup::PlaceBelow(const glm::vec4& ElementEdges, int PlacementType)
{
	if (CurrentllShapeGroup == nullptr) { Log::LogString("ERROR:: ShapeGroup Place Below FAILED:: Invalid ShapeGroup State");  return; }
	ManualPlaceBelow(PlacementType, ElementEdges, CurrentllShapeGroup->InputType, CurrentllShapeGroup->Position, 0);
	llUpdate();
}

void ShapeGroup::PlaceAbove(const glm::vec4& ElementEdges, int PlacementType)
{
	if (CurrentllShapeGroup == nullptr) { Log::LogString("ERROR:: ShapeGroup PlaceAbove FAILED:: Invalid ShapeGroup State");  return; }

	ManualPlaceAbove(PlacementType, ElementEdges, CurrentllShapeGroup->InputType, CurrentllShapeGroup->Position, 0);
	llUpdate();
}

void ShapeGroup::PlaceRight(const glm::vec4& ElementEdges, int PlacementType)
{
	if (CurrentllShapeGroup == nullptr) { Log::LogString("ERROR:: ShapeGroup PlaceRight FAILED:: Invalid ShapeGroup State");  return; }

	if (PlacementType == MATCH_CENTERS) {Input_Left_Once = true;}

	ManualPlaceRight(PlacementType, ElementEdges, CurrentllShapeGroup->InputType, CurrentllShapeGroup->Position, 0);
	llUpdate();
}

void ShapeGroup::PlaceLeft(const glm::vec4& ElementEdges, int PlacementType)
{
	if (CurrentllShapeGroup == nullptr) { Log::LogString("ERROR:: ShapeGroup PlaceLeft FAILED:: Invalid ShapeGroup State");  return; }

	ManualPlaceLeft(PlacementType, ElementEdges, CurrentllShapeGroup->InputType, CurrentllShapeGroup->Position, 0);
	llUpdate();
}

//////////////////////////////////////

void ShapeGroup::PlaceBelow(const glm::vec4& ElementEdges, int PlacementType, int PixelPadding)
{
	if (CurrentllShapeGroup == nullptr) { Log::LogString("ERROR:: ShapeGroup Place Below FAILED:: Invalid ShapeGroup State");  return; }
	ManualPlaceBelow(PlacementType, ElementEdges, CurrentllShapeGroup->InputType, CurrentllShapeGroup->Position, PixelPadding);
	llUpdate();
}

void ShapeGroup::PlaceAbove(const glm::vec4& ElementEdges, int PlacementType, int PixelPadding)
{
	if (CurrentllShapeGroup == nullptr) { Log::LogString("ERROR:: ShapeGroup PlaceAbove FAILED:: Invalid ShapeGroup State");  return; }
	ManualPlaceAbove(PlacementType, ElementEdges, CurrentllShapeGroup->InputType, CurrentllShapeGroup->Position, PixelPadding);
	llUpdate();
}

void ShapeGroup::PlaceRight(const glm::vec4& ElementEdges, int PlacementType, int PixelPadding)
{
	if (CurrentllShapeGroup == nullptr) { Log::LogString("ERROR:: ShapeGroup PlaceRight FAILED:: Invalid ShapeGroup State");  return; }

	if (PlacementType == MATCH_CENTERS) { Input_Left_Once = true; Log::LogString("Place Right Did it's job"); }

	ManualPlaceRight(PlacementType, ElementEdges, CurrentllShapeGroup->InputType, CurrentllShapeGroup->Position, PixelPadding);
	llUpdate();
}

void ShapeGroup::PlaceLeft(const glm::vec4& ElementEdges, int PlacementType, int PixelPadding)
{
	if (CurrentllShapeGroup == nullptr) { Log::LogString("ERROR:: ShapeGroup PlaceLeft FAILED:: Invalid ShapeGroup State");  return; }
	ManualPlaceLeft(PlacementType, ElementEdges, CurrentllShapeGroup->InputType, CurrentllShapeGroup->Position, PixelPadding);
	llUpdate();
}

//Function only works if there is a BackGround on each
//If you get an error here it's because this function is thinking both ShapeGroup BackGrounds are at the very beginning
void ShapeGroup::CopyBackGround(llShapeGroupData* CopyShapeGroup)
{
	//Validate
	if (CurrentllShapeGroup == nullptr) { return; }
	if (CopyShapeGroup == nullptr) { return; }
	if (CurrentllShapeGroup->BackGround == false) { return; }
	if (CopyShapeGroup->BackGround == false) { return; }

	CurrentllShapeGroup->BackGroundCopied = true;

	//Get Current BackGround
	llShapeData* Current_BackGround_Data = CurrentllShapeGroup->Shape;
	while (Current_BackGround_Data->Previous != nullptr) { Current_BackGround_Data = Current_BackGround_Data->Previous; }

	//Get Copy BackGround
	llShapeData* Copy_BackGround_Data = CopyShapeGroup->Shape;
	while (Copy_BackGround_Data->Previous != nullptr) { Copy_BackGround_Data = Copy_BackGround_Data->Previous; }

	Quad This_BackGround(Current_BackGround_Data);
	This_BackGround.llSwitch(Current_BackGround_Data);
	This_BackGround.LoadedBook = LoadedBook;
	Current_BackGround_Data->Size = Copy_BackGround_Data->Size;
	Current_BackGround_Data->InputType = INPUT_TOPLEFT;
	Current_BackGround_Data->Position = { CurrentllShapeGroup->Left - (CopyShapeGroup->BackGroundPadding[PADDING_LEFT] * PIXEL), CurrentllShapeGroup->Top + (CopyShapeGroup->BackGroundPadding[PADDING_TOP] * PIXEL) };
	CurrentllShapeGroup->BackGroundPadding[PADDING_LEFT] = CopyShapeGroup->BackGroundPadding[PADDING_LEFT];
	CurrentllShapeGroup->BackGroundPadding[PADDING_TOP] = CopyShapeGroup->BackGroundPadding[PADDING_TOP];
	CurrentllShapeGroup->BackGroundPlacementType = CopyShapeGroup->BackGroundPlacementType;
	CurrentllShapeGroup->BackGroundMatchType = CopyShapeGroup->BackGroundMatchType;
	This_BackGround.SetllShape(Current_BackGround_Data);

	//Above, Below, Leftof, Rightof
	switch (CopyShapeGroup->BackGroundPlacementType)
	{
	case PLACEMENT_ABOVE:
	{
		This_BackGround.PlaceAbove(GetEdges(), CopyShapeGroup->BackGroundMatchType, CopyShapeGroup->BackGroundPadding[PADDING_BOTTOM]);
		break;
	}
	case PLACEMENT_BELOW:
	
		This_BackGround.PlaceBelow(GetEdges(), CopyShapeGroup->BackGroundMatchType, CopyShapeGroup->BackGroundPadding[PADDING_TOP]);
		break;
	
	case PLACEMENT_LEFTOF:
	
		This_BackGround.PlaceLeft(GetEdges(), CopyShapeGroup->BackGroundMatchType, CopyShapeGroup->BackGroundPadding[PADDING_RIGHT]);
		break;
	
	case PLACEMENT_RIGHTOF:
	
		This_BackGround.PlaceRight(GetEdges(), CopyShapeGroup->BackGroundMatchType, CopyShapeGroup->BackGroundPadding[PADDING_LEFT]);
		break;
	}
	
	//Set EdgesWithBackGround
	CurrentllShapeGroup->EdgesWithBackGround = UpdateEdges(This_BackGround.GetEdges(), GetEdges());
	SizeFromEdges(CurrentllShapeGroup->EdgesWithBackGround, CurrentllShapeGroup->Size);
}



void ShapeGroup::AllignX(const float& X)
{
	CurrentllShapeGroup->Position[X_AXIS] = X;
	llUpdate();
}

void ShapeGroup::AllignY(const float& Y)
{
	CurrentllShapeGroup->Position[Y_AXIS] = Y;
	llUpdate();
}


void ShapeGroup::AllignX(const float& X, int INPUT_TYPE)
{
	CurrentllShapeGroup->Position[X_AXIS] = X;
	CurrentllShapeGroup->InputType = INPUT_TYPE;
	llUpdate();
}

void ShapeGroup::AllignY(const float& Y, int INPUT_TYPE)
{
	CurrentllShapeGroup->Position[Y_AXIS] = Y;
	CurrentllShapeGroup->InputType = INPUT_TYPE;
	llUpdate();
}


//Text is Created Based on INPUT_LEFT
//Set all Inputs to INPUT_LEFT
void ShapeGroup::ConvertInputToInputLeft()
{
	//Validate 
	if (CurrentllShapeGroup == nullptr) { Log::LogString("ERROR:: SetPositionInput FAILED:: Invalid ShapeGroup State"); return; };

	//Distance between ShapeGroup and BackGround Edge
	float LeftEdges_Distance = (CurrentllShapeGroup->Left - CurrentllShapeGroup->EdgesWithBackGround[EDGE_LEFT]);
	float RightEdges_Distance = (CurrentllShapeGroup->Right - CurrentllShapeGroup->EdgesWithBackGround[EDGE_RIGHT]);
	float TopEdges_Distance = (CurrentllShapeGroup->Top - CurrentllShapeGroup->EdgesWithBackGround[EDGE_TOP]);
	float BottomEdges_Distance = (CurrentllShapeGroup->Bottom - CurrentllShapeGroup->EdgesWithBackGround[EDGE_BOTTOM]);
	float EntireY = CurrentllShapeGroup->EdgesWithBackGround[EDGE_TOP] - CurrentllShapeGroup->EdgesWithBackGround[EDGE_BOTTOM];

	//CurrentllShapeGroup->Position[Y_AXIS] -= 0.0666; //Offseted like this for some reason

	switch (CurrentllShapeGroup->InputType)
	{
	case INPUT_LEFT: //To Left
		//Text is Created based off of INPUT_LEFT Already
		CurrentllShapeGroup->Position[Y_AXIS]  = (CurrentllShapeGroup->EdgesWithBackGround[EDGE_BOTTOM] + CurrentllShapeGroup->EdgesWithBackGround[EDGE_TOP]) / 2;// CurrentllShapeGroup->Size[X_AXIS] / 2;
		CurrentllShapeGroup->Position[X_AXIS] += LeftEdges_Distance;
		CurrentllShapeGroup->Position[Y_AXIS] -= 5 * PIXEL;
		CurrentllShapeGroup->InputType = INPUT_LEFT;
		//Not Taking into account the distance between LeftEdges and bakground left
		Input_Left_Once = false;
		break;
	case INPUT_RIGHT: //Converted to INPUT_LEFT
		//Edges Distance special case
		CurrentllShapeGroup->Position[Y_AXIS]  = (CurrentllShapeGroup->EdgesWithBackGround[EDGE_BOTTOM] + CurrentllShapeGroup->EdgesWithBackGround[EDGE_TOP]) / 2;// CurrentllShapeGroup->Size[X_AXIS] / 2;
		CurrentllShapeGroup->Position[X_AXIS] -= CurrentllShapeGroup->Size[X_AXIS];
		CurrentllShapeGroup->Position[X_AXIS] += RightEdges_Distance;
		CurrentllShapeGroup->Position[Y_AXIS] -= 5 * PIXEL;
		CurrentllShapeGroup->InputType = INPUT_LEFT;
		break;
	case INPUT_TOP: //Converted to INPUT_LEFT    ///////////////////// Not Working
		CurrentllShapeGroup->Position[Y_AXIS] -= CurrentllShapeGroup->Size[Y_AXIS] / 2;
		CurrentllShapeGroup->Position[X_AXIS] -= CurrentllShapeGroup->Size[X_AXIS] / 2;
		CurrentllShapeGroup->Position[Y_AXIS] += TopEdges_Distance;
		CurrentllShapeGroup->Position[Y_AXIS] -= 5 * PIXEL;
		CurrentllShapeGroup->InputType = INPUT_LEFT;
		break;
	case INPUT_BOTTOM: //Converted to INPUT_LEFT
		CurrentllShapeGroup->Position[Y_AXIS] += CurrentllShapeGroup->Size[Y_AXIS] / 2;
		CurrentllShapeGroup->Position[X_AXIS] -= CurrentllShapeGroup->Size[X_AXIS] / 2;
		CurrentllShapeGroup->Position[Y_AXIS] += BottomEdges_Distance;
		CurrentllShapeGroup->Position[Y_AXIS] -= 5 * PIXEL;
		CurrentllShapeGroup->InputType = INPUT_LEFT;
		break;
	case INPUT_TOPLEFT: //Converted to INPUT_LEFT     ///////////////////// Not Working
		CurrentllShapeGroup->Position[Y_AXIS] -= CurrentllShapeGroup->Size[Y_AXIS] / 2;
		CurrentllShapeGroup->Position[Y_AXIS] += TopEdges_Distance;
		CurrentllShapeGroup->Position[X_AXIS] += LeftEdges_Distance;
		CurrentllShapeGroup->Position[Y_AXIS] -= 5 * PIXEL;
		CurrentllShapeGroup->InputType = INPUT_LEFT;
		break;
	case INPUT_TOPRIGHT: //Converted to INPUT_LEFT    ///////////////////// Not Working
		CurrentllShapeGroup->Position[Y_AXIS] -= CurrentllShapeGroup->Size[Y_AXIS] / 2;
		CurrentllShapeGroup->Position[X_AXIS] -= CurrentllShapeGroup->Size[X_AXIS];
		CurrentllShapeGroup->Position[Y_AXIS] += TopEdges_Distance;
		CurrentllShapeGroup->Position[X_AXIS] += RightEdges_Distance;
		CurrentllShapeGroup->Position[Y_AXIS] -= 5 * PIXEL;
		CurrentllShapeGroup->InputType = INPUT_LEFT;
		break;
	case INPUT_BOTTOMLEFT: //Converted to INPUT_LEFT
		CurrentllShapeGroup->Position[Y_AXIS] += CurrentllShapeGroup->Size[Y_AXIS] / 2;
		//Re-Position in accordance with any background
		CurrentllShapeGroup->Position[Y_AXIS] += BottomEdges_Distance;
		CurrentllShapeGroup->Position[X_AXIS] += LeftEdges_Distance;
		CurrentllShapeGroup->Position[Y_AXIS] -= 5 * PIXEL;

		CurrentllShapeGroup->InputType = INPUT_LEFT;
		break;
	case INPUT_BOTTOMRIGHT: //Converted to INPUT_LEFT
		CurrentllShapeGroup->Position[Y_AXIS] += CurrentllShapeGroup->Size[Y_AXIS] / 2;
		CurrentllShapeGroup->Position[X_AXIS] -= CurrentllShapeGroup->Size[X_AXIS];
		CurrentllShapeGroup->Position[Y_AXIS] += BottomEdges_Distance;
		CurrentllShapeGroup->Position[X_AXIS] += RightEdges_Distance;
		CurrentllShapeGroup->Position[Y_AXIS] -= 5 * PIXEL;
		CurrentllShapeGroup->InputType = INPUT_LEFT;
		break;
	case INPUT_CENTER:
		CurrentllShapeGroup->Position[Y_AXIS] = (CurrentllShapeGroup->EdgesWithBackGround[EDGE_BOTTOM] + CurrentllShapeGroup->EdgesWithBackGround[EDGE_TOP])/2;// CurrentllShapeGroup->Size[X_AXIS] / 2;
		CurrentllShapeGroup->Position[X_AXIS] -= CurrentllShapeGroup->Size[X_AXIS] / 2;
		CurrentllShapeGroup->Position[Y_AXIS] -= 7 * PIXEL;
		CurrentllShapeGroup->InputType = INPUT_LEFT;
		Log::LogVec2("EntireY, Position.y", { EntireY, CurrentllShapeGroup->Position[Y_AXIS] });
	}

	CurrentllShapeGroup->InputType = INPUT_LEFT;
}

void ShapeGroup::ProcessBackGround()
{
	if (CurrentllShapeGroup == nullptr) { return; }

	if (CurrentllShapeGroup->BackGround == true)
	{
		Quad Quad_Reference(LoadedBook);
		Quad_Reference.SetColor(CurrentllShapeGroup->BackGroundColor);
	}
}

void ShapeGroup::SetBackGround()
{
	if (CurrentllShapeGroup == nullptr) { return; }

	if (CurrentllShapeGroup->BackGround == true )
	{

		llShapeData* BackGround = CurrentllShapeGroup->Shape;

		while (BackGround->Previous != nullptr)
		{
			BackGround = BackGround->Previous;
		}

		Quad Quad_Reference(BackGround);
		Quad_Reference.llSwitch(BackGround);
		Quad_Reference.LoadedBook = LoadedBook;

		//Normal BackGround
		if (CurrentllShapeGroup->BackGroundCopied != true)
		{
			//New Size
			BackGround->Size[X_AXIS] = CurrentllShapeGroup->Size[X_AXIS] + ((CurrentllShapeGroup->BackGroundPadding[PADDING_LEFT] + CurrentllShapeGroup->BackGroundPadding[PADDING_RIGHT]) * PIXEL);
			BackGround->Size[Y_AXIS] = CurrentllShapeGroup->Size[Y_AXIS] + ((CurrentllShapeGroup->BackGroundPadding[PADDING_TOP] + CurrentllShapeGroup->BackGroundPadding[PADDING_BOTTOM]) * PIXEL);
			//New Position
			BackGround->Position = { CurrentllShapeGroup->Left - (CurrentllShapeGroup->BackGroundPadding[PADDING_LEFT] * PIXEL), CurrentllShapeGroup->Top + (CurrentllShapeGroup->BackGroundPadding[PADDING_TOP] * PIXEL)};
		}
		//Copied BackGround Positioning
		else
		{
			//New Position
			CurrentllShapeGroup->BackGroundXDifference = CurrentllShapeGroup->Left - CurrentllShapeGroup->EdgesWithBackGround[EDGE_LEFT];
			BackGround->Position = { CurrentllShapeGroup->Left - (CurrentllShapeGroup->BackGroundPadding[PADDING_LEFT] * PIXEL), CurrentllShapeGroup->Top + (CurrentllShapeGroup->BackGroundPadding[PADDING_TOP] * PIXEL) };
			//Same Size
		}
		//BackGround->Position = { (CurrentllShapeGroup->Left + CurrentllShapeGroup->Right) / 2, (CurrentllShapeGroup->Top + CurrentllShapeGroup->Bottom) / 2 };
		BackGround->Hide = CurrentllShapeGroup->Hide;
		BackGround->InputType = INPUT_TOPLEFT;
		Quad_Reference.SetllShape(BackGround);

		//Above, Below, Leftof, Rightof
		switch (CurrentllShapeGroup->BackGroundPlacementType)
		{
		case PLACEMENT_ABOVE:
		{
			Quad_Reference.PlaceAbove(GetEdges(), CurrentllShapeGroup->BackGroundMatchType, CurrentllShapeGroup->BackGroundPadding[PADDING_BOTTOM]);
			break;
		}
		case PLACEMENT_BELOW:

			Quad_Reference.PlaceBelow(GetEdges(), CurrentllShapeGroup->BackGroundMatchType, CurrentllShapeGroup->BackGroundPadding[PADDING_TOP]);
			break;

		case PLACEMENT_LEFTOF:

			Quad_Reference.PlaceLeft(GetEdges(), CurrentllShapeGroup->BackGroundMatchType, CurrentllShapeGroup->BackGroundPadding[PADDING_RIGHT]);
			break;

		case PLACEMENT_RIGHTOF:

			Quad_Reference.PlaceRight(GetEdges(), CurrentllShapeGroup->BackGroundMatchType, CurrentllShapeGroup->BackGroundPadding[PADDING_LEFT]);
			break;
		}
		
		//Set EdgesWithBackGround
		CurrentllShapeGroup->EdgesWithBackGround = UpdateEdges(Quad_Reference.GetEdges(), GetEdges());
	}
}
