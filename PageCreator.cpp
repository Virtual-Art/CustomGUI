#include "PageCreator.h"



void PageCreator::llInit(llBookData* CurrentBook)
{
	//Setup all Editor Objects to get ready to create/edit the book provided either new or used

	//Defaults
	ShapeSelected.llInit(CurrentBook);
	ShapeGroupSelected.llInit(CurrentBook);
	PageItemSelected.llInit(CurrentBook);
	PageGroupSelected.llInit(CurrentBook);
	PageSelected.llInit(CurrentBook);

	//Presets
	QuadSelected.llInit(CurrentBook);
	CharacterSelected.llInit(CurrentBook);
	TextSelected.llInit(CurrentBook);
	SliderSelected.llInit(CurrentBook);



}

void PageCreator::OnUpdate(KeyResult& KeyState, int MouseState)
{
	CurrentKeyResult = &KeyState;
	CurrentMouseState = MouseState;

	if (EnableKeyBoard == true && KeyState.CurrentAscii != -1 && KeyState.Key1 != 0)
	{
		CurrentText += KeyState.CurrentAscii;
		TextSelected.SetText(CurrentText);
	}

	if (KeyState.Key1 == GUI_BACKSPACE_CLICKED || KeyState.Key1 == GUI_BACKSPACE_PRESSED)
	{
		CurrentText.erase(CurrentText.size() - 2);
		TextSelected.SetText(CurrentText);
	}
}

//void PageCreator::Init(Page& Creatorpage, Page& GUIpage, Book& Book)
//{
//	CreatorPage = &Creatorpage;
//	GUIPage = &GUIpage;
//	CurrentBook = &Book;
//	QuadSelected.Init(Creatorpage, -1);
//	//TextSelected.Init(Creatorpage, -1);
//	SliderSelected.Init(Creatorpage, -1);
//	ShapeSelected = &QuadSelected; //To Start off
//	PageItemSelected = &SliderSelected;
//	Element_Selected = &QuadSelected;
//
//	CreateFunctionContainer(); //Build "Creator" Function Table
//	SetCreatorFunctions();     //Set Functions To Function Table
//	SetKeyboardKeys();
//	
//	//Current Level
//	NewCharacter Initilization(*GUIPage, "Resources/segoe.fnt");
//
//	//Current Level
//	Text_CurrentLevel_Label.Init(*GUIPage, "Current Level: ", { -0.95, 0.8 });
//	Text_CurrentLevel.Init(*GUIPage, " Shape ", { -0.95, 0.7 });
//	Text_CurrentLevel.SetColor(Purple);
//
//	//Current Function
//	Text_CurrentFunction_Label.Init(*GUIPage, "Current Function: ", { -0.95, 0.6 });
//	Text_CurrentFunction.Init(*GUIPage, " Position ", { -0.95, 0.5 });
//	Text_CurrentFunction.SetColor(Orange);
//}

// ArrowButtonFunctions[Level][MainFunction][SubFunction];
//PageCreator::~PageCreator()
//{
//	for (int Level = 0; Level < 7; Level++)
//	{
//		for (int MainFunction = 0; MainFunction < 10; MainFunction++)
//		{
//			//Delete all Subfunctions EX: Delete all Sub Functions of (Level 0-7; MainFunctions 0-10)
//			 delete[] CreatorFunctions[Level][MainFunction];
//		}
//		//Delete all Main Functions EX: Delete all MainFunctions of (Level 0-7)
//		delete[] CreatorFunctions[Level];
//	}
//	//Delete All levels, aka everything
//	delete[] CreatorFunctions;
//}

void PageCreator::CreateFunctionContainer()
{
    CreatorFunction = new KeyFunction***[7];

	//Vertex
	for (int Level = 0; Level < 7; Level++)
	{
		CreatorFunction[Level] = new KeyFunction**[3];

		for (int Element_Type = 0; Element_Type < 4; Element_Type++)
		{
			CreatorFunction[Level][Element_Type] = new KeyFunction * [10];

			for (int Function = 0; Function < 10; Function++)
			{
				CreatorFunction[Level][Element_Type][Function] = new KeyFunction[3];
				for (int Arrow = 0; Arrow < 3; Arrow++)
				{
					CreatorFunction[Level][Element_Type][Function][Arrow] = Empty;
				}
			}
		}
	}
}

////Called Once on Creation
void PageCreator::SetCreatorFunctions()
{
	//All Levels and types will be given the same "function" Functions
	for (int Level = 0; Level < 7; Level++)
	{
		for (int Type = 0; Type < 3; Type++)
		{
			CreatorFunction[Level][Type][FUNCTION_POSITION][ARROW_UP] = PositionUp;
			CreatorFunction[Level][Type][FUNCTION_POSITION][ARROW_DOWN] = PositionDown;
			CreatorFunction[Level][Type][FUNCTION_POSITION][ARROW_RIGHT] = PositionRight;
			CreatorFunction[Level][Type][FUNCTION_POSITION][ARROW_LEFT] = PositionLeft;

			CreatorFunction[Level][Type][FUNCTION_SIZE][ARROW_UP]     = SizeUp;
			CreatorFunction[Level][Type][FUNCTION_SIZE][ARROW_DOWN]   = SizeDown;
			CreatorFunction[Level][Type][FUNCTION_SIZE][ARROW_RIGHT]  = SizeRight;
			CreatorFunction[Level][Type][FUNCTION_SIZE][ARROW_LEFT]   = SizeLeft;

			//R
			CreatorFunction[Level][Type][FUNCTION_COLOR_R][ARROW_UP]    = ColorRUp;
			CreatorFunction[Level][Type][FUNCTION_COLOR_R][ARROW_DOWN]  = ColorRDown;
			CreatorFunction[Level][Type][FUNCTION_COLOR_R][ARROW_RIGHT] = Empty;
			CreatorFunction[Level][Type][FUNCTION_COLOR_R][ARROW_LEFT]  = Empty;

			//G
			CreatorFunction[Level][Type][FUNCTION_COLOR_G][ARROW_UP]    = ColorGUp;
			CreatorFunction[Level][Type][FUNCTION_COLOR_G][ARROW_DOWN]  = ColorGDown;
			CreatorFunction[Level][Type][FUNCTION_COLOR_G][ARROW_RIGHT] = Empty;
			CreatorFunction[Level][Type][FUNCTION_COLOR_G][ARROW_LEFT]  = Empty;

			//B
			CreatorFunction[Level][Type][FUNCTION_COLOR_B][ARROW_UP] = ColorBUp;
			CreatorFunction[Level][Type][FUNCTION_COLOR_B][ARROW_DOWN] = ColorBDown;
			CreatorFunction[Level][Type][FUNCTION_COLOR_B][ARROW_RIGHT] = Empty;
			CreatorFunction[Level][Type][FUNCTION_COLOR_B][ARROW_LEFT] = Empty;

			//A
			CreatorFunction[Level][Type][FUNCTION_COLOR_A][ARROW_UP] = ColorAUp;
			CreatorFunction[Level][Type][FUNCTION_COLOR_A][ARROW_DOWN] = ColorADown;
			CreatorFunction[Level][Type][FUNCTION_COLOR_A][ARROW_RIGHT] = Empty;
			CreatorFunction[Level][Type][FUNCTION_COLOR_A][ARROW_LEFT] = Empty;
		}
	}
}

void PageCreator::SetArrowKeys()
{
	//A value of type blah cannot be initialized to type blah
	Keyboard::KeyButton[GUI_UP_CLICKED][WITH_DEFAULT]   = ArrowKeyUp;
	Keyboard::KeyButton[GUI_DOWN_CLICKED][WITH_DEFAULT] = ArrowKeyDown;
    Keyboard::KeyButton[GUI_RIGHT_CLICKED][WITH_DEFAULT] = ArrowKeyRight;
	Keyboard::KeyButton[GUI_LEFT_CLICKED][WITH_DEFAULT]  = ArrowKeyLeft;
	
	Keyboard::KeyButton[GUI_UP_PRESSED][WITH_DEFAULT]    = ArrowKeyUp;
	Keyboard::KeyButton[GUI_DOWN_PRESSED][WITH_DEFAULT]  = ArrowKeyDown;
	Keyboard::KeyButton[GUI_RIGHT_PRESSED][WITH_DEFAULT] = ArrowKeyRight;
	Keyboard::KeyButton[GUI_LEFT_PRESSED][WITH_DEFAULT]  = ArrowKeyLeft;
	// CreatorFunction[CurrentLevel][CurrentFunction][ARROW_UP];

	//50 - 101

	//Should actually almost every default key and + caps + shft
	for (int CharKey = 50; CharKey < 102; CharKey++)
	{
		Keyboard::KeyButton[CharKey][WITH_DEFAULT] = AddLetter;
	}

	Keyboard::KeyButton[GUI_BACKSPACE_PRESSED][WITH_DEFAULT] = BackSpace;
}

void PageCreator::AddLetter()
{
	if (CurrentKeyResult->CurrentAscii != -1 && CurrentKeyResult->Key1 != 0)
	{
		CurrentText += CurrentKeyResult->CurrentAscii;
	}
}

void PageCreator::BackSpace()
{
	CurrentText.erase(CurrentText.size() - 1);
}

//Play Creator Function when Clicked/Pressed
void PageCreator::ArrowKeyUp()
{
	CreatorFunction[CurrentLevel][CurrentType][CurrentFunction][ARROW_UP]();
}

void PageCreator::ArrowKeyDown()
{
	CreatorFunction[CurrentLevel][CurrentType][CurrentFunction][ARROW_DOWN]();
}

void PageCreator::ArrowKeyRight()
{
	//Play
	CreatorFunction[CurrentLevel][CurrentType][CurrentFunction][ARROW_RIGHT]();
}

void PageCreator::ArrowKeyLeft()
{
	//Play
	CreatorFunction[CurrentLevel][CurrentType][CurrentFunction][ARROW_LEFT]();
}



//Arrow Keys with Shift
void PageCreator::SetShift()
{
	Keyboard::KeyButton[GUI_UP_CLICKED][WITH_SHIFT] = LevelUp;
	Keyboard::KeyButton[GUI_DOWN_CLICKED][WITH_SHIFT] = LevelDown;
	Keyboard::KeyButton[GUI_RIGHT_CLICKED][WITH_SHIFT] = DataRight;
	Keyboard::KeyButton[GUI_LEFT_CLICKED][WITH_SHIFT] = DataLeft;
}

void PageCreator::OptionsUp()
{
	if (CurrentFunction < MaxFunction)
	{
		CurrentFunction++;
	}
	if (CurrentFunction == 0)
	{
		Text_CurrentFunction.SetText("Position");
	}
	if (CurrentFunction == 1)
	{
		Text_CurrentFunction.SetText("Size");
	}
	if (CurrentFunction == 2)
	{
		Text_CurrentFunction.SetText("R Color");
	}
	if (CurrentFunction == 3)
	{
		Text_CurrentFunction.SetText("G Color");
	}
	if (CurrentFunction == 4)
	{
		Text_CurrentFunction.SetText("B Color");
	}
	if (CurrentFunction == 5)
	{
		Text_CurrentFunction.SetText("A Color");
	}
	if (CurrentFunction == 6)
	{
		Text_CurrentFunction.SetText("Function Not Set");
	}
	if (CurrentFunction == 7)
	{
		Text_CurrentFunction.SetText("Function Not Set");
	}
	if (CurrentFunction == 8)
	{
		Text_CurrentFunction.SetText("Function Not Set");
	}
	if (CurrentFunction == 9)
	{
		Text_CurrentFunction.SetText("Function Not Set");
	}
	cout << "CurrentFunction: " << CurrentFunction << endl;
}

void PageCreator::OptionsDown()
{
	//Shift Down
	if (CurrentFunction > MinFunction)
	{
		CurrentFunction--;
	}

	//Log To Screen
	if (CurrentFunction == 0)
	{
		Text_CurrentFunction.SetText("Position");
	}
	if (CurrentFunction == 1)
	{
		Text_CurrentFunction.SetText("Size");
	}
	if (CurrentFunction == 2)
	{
		Text_CurrentFunction.SetText("R Color");
	}
	if (CurrentFunction == 3)
	{
		Text_CurrentFunction.SetText("G Color");
	}
	if (CurrentFunction == 4)
	{
		Text_CurrentFunction.SetText("B Color");
	}
	if (CurrentFunction == 5)
	{
		Text_CurrentFunction.SetText("A Color");
	}
	if (CurrentFunction == 6)
	{
		Text_CurrentFunction.SetText("Function Not Set");
	}
	if (CurrentFunction == 7)
	{
		Text_CurrentFunction.SetText("Function Not Set");
	}
	if (CurrentFunction == 8)
	{
		Text_CurrentFunction.SetText("Function Not Set");
	}
	if (CurrentFunction == 9)
	{
		Text_CurrentFunction.SetText("Function Not Set");
	}
	cout << "CurrentFunction: " << CurrentFunction << endl;
}

void PageCreator::TypeRight()
{
	switch (CurrentLevel)
	{
	case LEVEL_VERTEX:
		//Element_Selected = &Vertex_Selected;
		break;
	case LEVEL_SHAPE:
		if (CurrentType < 2)
		{
			CurrentType++;

			switch (CurrentType)
			{
			case TYPE_SHAPE:
				Element_Selected = &ShapeSelected;
				break;
			case TYPE_SHAPE_QUAD:
				Element_Selected = &QuadSelected;
				break;
			case TYPE_SHAPE_CHARACTER:
				Element_Selected = &CharacterSelected;
				break;
			}
		}
		break;
	case LEVEL_SHAPEGROUP:
		if (CurrentType < 1)
		{
			CurrentType++;
			switch (CurrentType)
			{
			case TYPE_SHAPEGROUP:
				Element_Selected = &ShapeGroupSelected;
				break;
			case TYPE_SHAPEGROUP_TEXT:
				Element_Selected = &TextSelected;
				break;
			}
		}
		break;
	case LEVEL_PAGEITEM:
		if (CurrentType < 1)
		{
			CurrentType++;
			switch (CurrentType)
			{
			case TYPE_PAGEITEM:
				Element_Selected = &PageItemSelected;
				break;
			case TYPE_PAGEITEM_SLIDER:
				Element_Selected = &SliderSelected;
				break;
			}
		}
		break;
	case LEVEL_PAGEGROUP:
		//Only One Type
		break;
	case LEVEL_PAGE:
		//Only one type
		break;
	}
}

void PageCreator::TypeLeft()
{
	switch (CurrentLevel)
	{
	case LEVEL_VERTEX:
		//Element_Selected = &Vertex_Selected;
		break;
	case LEVEL_SHAPE:
		if (CurrentType > 0)
		{
			CurrentType--;
			switch (CurrentType)
			{
			case TYPE_SHAPE:
				Element_Selected = &ShapeSelected;
				break;
			case TYPE_SHAPE_QUAD:
				Element_Selected = &QuadSelected;
				break;
			case TYPE_SHAPE_CHARACTER:
				Element_Selected = &CharacterSelected;
				break;
			}
			break;
	case LEVEL_SHAPEGROUP:
		if (CurrentType > 0)
		{
			CurrentType--;
			switch (CurrentType)
			{
			case TYPE_SHAPEGROUP:
				Element_Selected = &ShapeGroupSelected;
				break;
			case TYPE_SHAPEGROUP_TEXT:
				Element_Selected = &TextSelected;
				break;
			}
		}
		break;
	case LEVEL_PAGEITEM:
		if (CurrentType > 0)
		{
			CurrentType--;
			switch (CurrentType)
			{
			case TYPE_PAGEITEM:
				Element_Selected = &PageItemSelected;
				break;
			case TYPE_PAGEITEM_SLIDER:
				Element_Selected = &SliderSelected;
				break;
			}
		}
		break;
	case LEVEL_PAGEGROUP:
		//Only One Type
		break;
	case LEVEL_PAGE:
		//Only one type
		break;
		}
	}
}

void PageCreator::DataRight()
{
	//We don't know how many functions each level has, however each level has one function, so set it to the first
	CurrentFunction = 0;

	switch (CurrentLevel)
	{
	case LEVEL_VERTEX:
		//Element_Selected = &Vertex_Selected;
		break;
	case LEVEL_SHAPE:
		
		if (CurrentShape->Next != nullptr)
		{
			CurrentShape = CurrentShape->Next;
			CurrentType = CurrentShape->Type;
			SetShapeType();
		}
		break;

	case LEVEL_SHAPEGROUP:
		
		if (CurrentShapeGroup->Next != nullptr)
		{
			CurrentShapeGroup = CurrentShapeGroup->Next;
			CurrentType = CurrentShapeGroup->Type;
			SetShapeGroupType();
		}
		break;

	case LEVEL_PAGEITEM:

		if (CurrentPageItem->Next != nullptr)
		{
			CurrentPageItem = CurrentPageItem->Next;
			CurrentType = CurrentPageItem->Type;
			SetPageItemType();
		}
	    break;

	case LEVEL_PAGEGROUP:

		if (CurrentPageGroup->Next != nullptr)
		{
			CurrentPageGroup = CurrentPageGroup->Next;
			SetPageGroupType();
		}
		break;

	case LEVEL_PAGE:
		if (CurrentPage->Next != nullptr)
		{
			CurrentPage = CurrentPage->Next;
			SetPageType();
		}
		break;
	}
}

void PageCreator::DataLeft()
{
	//We don't know how many functions each level has, however each level has one function, so set it to the first
	CurrentFunction = 0;

	switch (CurrentLevel)
	{
	case LEVEL_VERTEX:
		//Element_Selected = &Vertex_Selected;
		break;
	case LEVEL_SHAPE:

		if (CurrentShape->Previous != nullptr)
		{
			CurrentShape = CurrentShape->Previous;
			SetPageGroupType();
		}
		break;

	case LEVEL_SHAPEGROUP:

		if (CurrentShapeGroup->Previous != nullptr)
		{
			CurrentShapeGroup = CurrentShapeGroup->Previous;
			SetPageGroupType();
		}
		break;

	case LEVEL_PAGEITEM:

		if (CurrentPageItem->Previous != nullptr)
		{
			CurrentPageItem = CurrentPageItem->Previous;
			SetPageGroupType();
		}
		break;

	case LEVEL_PAGEGROUP:

		if (CurrentPageGroup->Previous != nullptr)
		{
			CurrentPageGroup = CurrentPageGroup->Previous;
			SetPageGroupType();
		}
		break;

	case LEVEL_PAGE:
		if (CurrentPage->Previous != nullptr)
		{
			CurrentPage = CurrentPage->Previous;
			SetPageGroupType();
		}
		break;
	}
}

void PageCreator::SetShapeType()
{
	switch (CurrentType)
	{
	case TYPE_SHAPE:
		Element_Selected = &ShapeSelected;
		break;
	case TYPE_SHAPE_QUAD:
		Element_Selected = &QuadSelected;
		break;
	case TYPE_SHAPE_CHARACTER:
		Element_Selected = &CharacterSelected;
		break;
	}
}

void PageCreator::SetShapeGroupType()
{
	switch (CurrentType)
	{
	case TYPE_SHAPEGROUP:
		Element_Selected = &ShapeGroupSelected;
		break;
	case TYPE_SHAPEGROUP_TEXT:
		Element_Selected = &TextSelected;
		break;
	}
}

void PageCreator::SetPageItemType()
{
	switch (CurrentType)
	{
	case TYPE_PAGEITEM:
		Element_Selected = &PageItemSelected;
		break;
	case TYPE_PAGEITEM_SLIDER:
		Element_Selected = &SliderSelected;
		break;
	}
}

void PageCreator::SetPageGroupType()
{
	switch (CurrentType)
	{
	case TYPE_PAGEGROUP:
		Element_Selected = &PageGroupSelected;
		break;
	}
}

void PageCreator::SetPageType()
{
	switch (CurrentType)
	{
	case TYPE_PAGE:
		Element_Selected = &PageSelected;
		break;
	}
}

//Arrow Key with Alt
void PageCreator::SetAlternate()
{
	Keyboard::KeyButton[GUI_UP_CLICKED][WITH_ALT] = OptionsUp;
	Keyboard::KeyButton[GUI_DOWN_CLICKED][WITH_ALT] = OptionsDown;
}


void PageCreator::LevelUp()
{
	if (CurrentLevel < MaxLevel)
	{
		CurrentLevel++;
	}
	
	switch (CurrentLevel)
	{
	case LEVEL_VERTEX:
		//Element_Selected = &Vertex_Selected;
		break;
	case LEVEL_SHAPE:
		CurrentShape = CurrentBook->Page->PageGroup->PageItem->ShapeGroup->Shape;
		ShapeSelected.llSwitch(CurrentShape);
		CurrentType = CurrentShape->Type; 
		Element_Selected = &ShapeSelected; //Supposed to set type here, won't always be basic type
		break;
	case LEVEL_SHAPEGROUP:
		CurrentShapeGroup = CurrentBook->Page->PageGroup->PageItem->ShapeGroup;
		ShapeGroupSelected.llSwitch(CurrentShapeGroup);
		CurrentType = CurrentShapeGroup->Type; 
		Element_Selected = &ShapeGroupSelected; //Supposed to set type here, won't always be basic type
		break;
	case LEVEL_PAGEITEM:
		CurrentPageItem = CurrentBook->Page->PageGroup->PageItem;
		PageItemSelected.llSwitch(CurrentPageItem);
		CurrentType = CurrentPageItem->Type; 
		Element_Selected = &PageItemSelected; //Supposed to set type here, won't always be basic type
		break;
	case LEVEL_PAGEGROUP:
		CurrentPageGroup = CurrentBook->Page->PageGroup;
		PageGroupSelected.llSwitch(CurrentPageGroup);
		CurrentType = CurrentPageGroup->Type;
		Element_Selected = &PageGroupSelected; //Supposed to set type here, won't always be basic type
		break;
	case LEVEL_PAGE:
		CurrentPage = CurrentBook->Page;
		PageSelected.llSwitch(CurrentPage);
		CurrentType = 0;
		Element_Selected = &PageSelected;//Supposed to set type here, won't always be basic type
		break;
	}
}

void PageCreator::LevelDown()
{
	if (CurrentLevel > MinLevel)
	{
		CurrentLevel--;
	}
	switch (CurrentLevel)
	{
	case LEVEL_VERTEX:
		//Element_Selected = &Vertex_Selected;
		break;
	case LEVEL_SHAPE:
		Element_Selected = &ShapeSelected;
		break;
	case LEVEL_SHAPEGROUP:
		Element_Selected = &ShapeGroupSelected;
		break;
	case LEVEL_PAGEITEM:
		Element_Selected = &PageItemSelected;
		break;
	case LEVEL_PAGEGROUP:
		Element_Selected = &PageGroupSelected;
		break;
	case LEVEL_PAGE:
		Element_Selected = &PageSelected;
		break;
	}
}




void PageCreator::Add()
{
	Element_Selected->Add_Default();
	CurrentFunction = 0;
}

void PageCreator::Duplicate()
{
	Element_Selected->Add_Duplicate();
	CurrentFunction = 0;
}

void PageCreator::Insert()
{
	Element_Selected->Add_Insert();
	CurrentFunction = 0;
}

//void PageCreator::Next()
//{
//	Element_Selected->llSwitch(1);
//}
//
//void PageCreator::Previous()
//{
//	Element_Selected->llSwitch(-11);
//	Element_Selected->GetType;
//	if (Type == Text)
//	{
//		Element_Selected = &TextSelected;
//	}
//}


void PageCreator::Delete()
{
	//int PreviousShape = ShapeSelected->CurrentShapeData.ID - 1;
	Element_Selected->Delete();
	//Element_Selected->Switch(PreviousShape);
}

void PageCreator::SetQuadSelected(int MouseState, int ShapeHovered)
{
	if (MouseState == GUI_MOUSELEFT_CLICKED && ShapeHovered > -1 && ShapeHovered < CreatorPage->MaxShapeDataCount)
	{
		if (QuadSelected.CurrentShapeData.ID > -1)
		{
			Element_Selected->Switch(ShapeHovered);
		}
	}

}

void PageCreator::SetKeyAdd() { Keyboard::KeyButton[GUI_A_CLICKED][WITH_CTRL] = Add; }
void PageCreator::SetInsertKey() { Keyboard::KeyButton[GUI_INSERT_CLICKED][WITH_DEFAULT] = Insert; }
void PageCreator::SetEraseKey() { Keyboard::KeyButton[GUI_E_CLICKED][WITH_CTRL] = ErasePage; }
void PageCreator::SetSaveKey() { Keyboard::KeyButton[GUI_S_CLICKED][WITH_CTRL] = SavePage; }
void PageCreator::SetKeyDuplicate() { Keyboard::KeyButton[GUI_D_CLICKED][WITH_CTRL] = Duplicate; }
void PageCreator::SetDeleteKey() { Keyboard::KeyButton[GUI_DELETE_CLICKED][WITH_DEFAULT] = Delete; }
//void PageCreator::SetKeyNext() { Keyboard::KeyButton[GUI_RIGHT_CLICKED][WITH_CTRL] = Next; }
//void PageCreator::SetKeyPrevious() { Keyboard::KeyButton[GUI_LEFT_CLICKED][WITH_CTRL] = Previous; }


void PageCreator::SetPixelOffsetKeys()
{
	Keyboard::KeyButton[GUI_F1_CLICKED][WITH_DEFAULT] = IncreasePixelOffset;
	Keyboard::KeyButton[GUI_F2_CLICKED][WITH_DEFAULT] = DecreasePixelOffset;
}

void PageCreator::IncreasePixelOffset()
{
	if (PixelOffset < PixelOffsetMax)
	{
		PixelOffset++;
	}
}

void PageCreator::DecreasePixelOffset()
{
	if (PixelOffset > PixelOffsetMin)
	{
		PixelOffset--;
	}

	
}

void PageCreator::ErasePage()
{
	CreatorPage->ErasePage();
}

void PageCreator::SavePage()
{
	//Filesystem.SaveBook(*CurrentBook);
}

void PageCreator::SetKeyboardKeys()
{
	SetArrowKeys();            //Set KeyBoard ArrowKeys
	SetAlternate();
	SetShift();
	SetKeyAdd();
	SetKeyDuplicate();
	SetPixelOffsetKeys();
	SetDeleteKey();
	SetEraseKey();
	SetSaveKey();
	SetInsertKey();
	SetKeyNext(); 
	SetKeyPrevious(); 
}

void PageCreator::Empty()
{

}

// POSITION
void PageCreator::PositionUp()
{
	Element_Selected->OffsetPosition({ 0.0, 0.00166 * PixelOffset }, OnlyY);
}
void PageCreator::PositionDown()
{
	Element_Selected->OffsetPosition({ 0.0, -0.00166 * PixelOffset }, OnlyY);
}
void PageCreator::PositionRight()
{
	Element_Selected->OffsetPosition({ 0.00166 * PixelOffset, 0.0 }, OnlyX);
}
void PageCreator::PositionLeft()
{
	Element_Selected->OffsetPosition({ -0.00166 * PixelOffset, 0.0 }, OnlyX);
}

//SIZE
void PageCreator::SizeUp()
{
	Element_Selected->OffsetSize({ 0.0, 0.00166 * PixelOffset }, OnlyY);
}
void PageCreator::SizeDown()
{
	Element_Selected->OffsetSize({ 0.0, 0.00166 * -PixelOffset }, OnlyY);
}
void PageCreator::SizeRight()
{
	Element_Selected->OffsetSize({ 0.00166 * PixelOffset, 0.0 }, OnlyX);
}
void PageCreator::SizeLeft()
{
	Element_Selected->OffsetSize({ 0.00166 * -PixelOffset, 0.0}, OnlyX);
}

// COLOR
void PageCreator::ColorRUp()
{
	if (Element_Selected->GetColor()[0] < 1.0)
	{
		Element_Selected->OffsetColor({ 0.01 * PixelOffset, 0.0, 0.0, 0.0 }, OnlyR);
	}
}
void PageCreator::ColorRDown()
{
	if (Element_Selected->GetColor()[1] > 1.0)
	{
		Element_Selected->OffsetColor({ 0.01 * -PixelOffset, 0.0, 0.0, 0.0 }, OnlyR);
	}
}

void PageCreator::ColorGUp()
{
	if (Element_Selected->GetColor()[1] < 1.0)
	{
		Element_Selected->OffsetColor({ 0.0, 0.01 * PixelOffset,  0.0, 0.0 }, OnlyG);
	}
}

void PageCreator::ColorGDown()
{
	if (Element_Selected->GetColor()[1] > 0.0)
	{
		Element_Selected->OffsetColor({ 0.0, 0.01 * -PixelOffset,  0.0, 0.0 }, OnlyG);
	}
}

void PageCreator::ColorBUp()
{
	if (Element_Selected->GetColor()[2] < 1.0)
	{
		Element_Selected->OffsetColor({ 0.0, 0.0, 0.01 * PixelOffset, 0.0 }, OnlyB);
	}
}
void PageCreator::ColorBDown()
{
	if (Element_Selected->GetColor()[2] > 1.0)
	{
		Element_Selected->OffsetColor({ 0.0, 0.0, 0.01 * -PixelOffset,  0.0 }, OnlyB);
	}
}

void PageCreator::ColorAUp()
{
	if (Element_Selected->GetColor()[3] < 1.0)
	{
		Element_Selected->OffsetColor({ 0.0, 0.0, 0.0, 0.01 * PixelOffset }, OnlyA);
	}
}
void PageCreator::ColorADown()
{
	if (Element_Selected->GetColor()[3] > 1.0)
	{
		Element_Selected->OffsetColor({ 0.0, 0.0, 0.0, 0.01 * -PixelOffset }, OnlyA);
	}
}

void PageCreator::SetText()
{
	string GetString = "";
	TextSelected.SetText(GetString);

}
