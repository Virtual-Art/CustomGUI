#include "PageCreator.h"


void PageCreator::Init(Page& Creatorpage, Page& GUIpage, Book& Book)
{
	CreatorPage = &Creatorpage;
	GUIPage = &GUIpage;
	CurrentBook = &Book;
	QuadSelected.Init(Creatorpage, -1);
	//TextSelected.Init(Creatorpage, -1);
	SliderSelected.Init(Creatorpage, -1);
	ShapeSelected = &QuadSelected; //To Start off
	PageItemSelected = &SliderSelected;
	Element_Selected = &QuadSelected;

	CreateFunctionContainer(); //Build "Creator" Function Table
	SetCreatorFunctions();     //Set Functions To Function Table
	SetKeyboardKeys();
	
	//Current Level
	NewCharacter Initilization(*GUIPage, "Resources/segoe.fnt");

	//Current Level
	Text_CurrentLevel_Label.Init(*GUIPage, "Current Level: ", { -0.95, 0.8 });
	Text_CurrentLevel.Init(*GUIPage, " Shape ", { -0.95, 0.7 });
	Text_CurrentLevel.SetColor(Purple);

	//Current Function
	Text_CurrentFunction_Label.Init(*GUIPage, "Current Function: ", { -0.95, 0.6 });
	Text_CurrentFunction.Init(*GUIPage, " Position ", { -0.95, 0.5 });
	Text_CurrentFunction.SetColor(Orange);
}

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
    CreatorFunction = new KeyFunction**[7];

	for (int Level = 0; Level < 7; Level++)
	{
		//Every Level has 10 Main Functions
		CreatorFunction[Level] = new KeyFunction *[10];
		for (int MainFunction = 0; MainFunction < 10; MainFunction++)
		{
			//Every Main Function has 4 sub functions (for our "up to 4" arrow keys)
			CreatorFunction[Level][MainFunction] = new KeyFunction[4];
		}
	}

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				CreatorFunction[i][j][k] = Empty;
			}
		}
	}
}

////Called Once on Creation
void PageCreator::SetCreatorFunctions()
{
	//Position
	CreatorFunction[LEVEL_SHAPE][FUNCTION_POSITION][ARROW_UP]    = PositionUp;
	CreatorFunction[LEVEL_SHAPE][FUNCTION_POSITION][ARROW_DOWN]  = PositionDown;
	CreatorFunction[LEVEL_SHAPE][FUNCTION_POSITION][ARROW_RIGHT] = PositionRight;
	CreatorFunction[LEVEL_SHAPE][FUNCTION_POSITION][ARROW_LEFT]  = PositionLeft;

	//Size
	CreatorFunction[LEVEL_SHAPE][FUNCTION_SIZE][ARROW_UP]    = SizeUp;
	CreatorFunction[LEVEL_SHAPE][FUNCTION_SIZE][ARROW_DOWN]  = SizeDown;
	CreatorFunction[LEVEL_SHAPE][FUNCTION_SIZE][ARROW_RIGHT] = SizeRight;
	CreatorFunction[LEVEL_SHAPE][FUNCTION_SIZE][ARROW_LEFT]  = SizeLeft;

	//R
	CreatorFunction[LEVEL_SHAPE][FUNCTION_COLOR_R][ARROW_UP]    = ColorRUp;
	CreatorFunction[LEVEL_SHAPE][FUNCTION_COLOR_R][ARROW_DOWN]  = ColorRDown;
	CreatorFunction[LEVEL_SHAPE][FUNCTION_COLOR_R][ARROW_RIGHT] = Empty;
	CreatorFunction[LEVEL_SHAPE][FUNCTION_COLOR_R][ARROW_LEFT]  = Empty;

	//G
	CreatorFunction[LEVEL_SHAPE][FUNCTION_COLOR_G][ARROW_UP]   = ColorGUp;
	CreatorFunction[LEVEL_SHAPE][FUNCTION_COLOR_G][ARROW_DOWN] = ColorGDown;
	CreatorFunction[LEVEL_SHAPE][FUNCTION_COLOR_G][ARROW_RIGHT] = Empty;
	CreatorFunction[LEVEL_SHAPE][FUNCTION_COLOR_G][ARROW_LEFT]  = Empty;

	//B
	CreatorFunction[LEVEL_SHAPE][FUNCTION_COLOR_B][ARROW_UP]   = ColorBUp;
	CreatorFunction[LEVEL_SHAPE][FUNCTION_COLOR_B][ARROW_DOWN] = ColorBDown;
	CreatorFunction[LEVEL_SHAPE][FUNCTION_COLOR_B][ARROW_RIGHT] = Empty;
	CreatorFunction[LEVEL_SHAPE][FUNCTION_COLOR_B][ARROW_LEFT] = Empty;

	//A
	CreatorFunction[LEVEL_SHAPE][FUNCTION_COLOR_A][ARROW_UP]   = ColorAUp;
	CreatorFunction[LEVEL_SHAPE][FUNCTION_COLOR_A][ARROW_DOWN] = ColorADown;
	CreatorFunction[LEVEL_SHAPE][FUNCTION_COLOR_A][ARROW_RIGHT] = Empty;
	CreatorFunction[LEVEL_SHAPE][FUNCTION_COLOR_A][ARROW_LEFT] = Empty;

	/////////////SHAPEGROUP//////////////////

	////Position
	//CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_POSITION][ARROW_UP]    = PositionUp;
	//CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_POSITION][ARROW_DOWN]  = PositionDown;
	//CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_POSITION][ARROW_RIGHT] = PositionRight;
	//CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_POSITION][ARROW_LEFT]  = PositionLeft;
	//														
	////Size													
	//CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_SIZE][ARROW_UP]    = SizeUp;
	//CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_SIZE][ARROW_DOWN]  = SizeDown;
	//CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_SIZE][ARROW_RIGHT] = SizeRight;
	//CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_SIZE][ARROW_LEFT]  = SizeLeft;
	//																  
	////R																  
	//CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_COLOR_R][ARROW_UP]     = ColorRUp;
	//CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_COLOR_R][ARROW_DOWN]   = ColorRDown;
	//CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_COLOR_R][ARROW_RIGHT]  = Empty;
	//CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_COLOR_R][ARROW_LEFT]   = Empty;
	//														
	////G														
	//CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_COLOR_G][ARROW_UP]     = ColorGUp;
	//CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_COLOR_G][ARROW_DOWN]   = ColorGDown;
	//CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_COLOR_G][ARROW_RIGHT]  = Empty;
	//CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_COLOR_G][ARROW_LEFT]   = Empty;
	//																 
	////B																 
	//CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_COLOR_B][ARROW_UP]     = ColorBUp;
	//CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_COLOR_B][ARROW_DOWN]   = ColorBDown;
	//CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_COLOR_B][ARROW_RIGHT]  = Empty;
	//CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_COLOR_B][ARROW_LEFT]   = Empty;
	//																  
	////A																  
	//CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_COLOR_A][ARROW_UP]     = ColorAUp;
	//CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_COLOR_A][ARROW_DOWN]   = ColorADown;
	//CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_COLOR_A][ARROW_RIGHT]  = Empty;
	//CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_COLOR_A][ARROW_LEFT]   = Empty;
	//
	////																  
	//CreatorFunction[LEVEL_SHAPEGROUP][MAINFUNCTION_6][ARROW_UP] = Empty;
	//CreatorFunction[LEVEL_SHAPEGROUP][MAINFUNCTION_6][ARROW_DOWN] = Empty;
	//CreatorFunction[LEVEL_SHAPEGROUP][MAINFUNCTION_6][ARROW_RIGHT] = Empty;
	//CreatorFunction[LEVEL_SHAPEGROUP][MAINFUNCTION_6][ARROW_LEFT] = Empty;
	//
	//
	//// Page Item Group
	//CreatorFunction[LEVEL_PAGEITEM][FUNCTION_POSITION][ARROW_UP]    = PageItemPositionUp;
	//CreatorFunction[LEVEL_PAGEITEM][FUNCTION_POSITION][ARROW_DOWN]  = PageItemPositionDown;
	//CreatorFunction[LEVEL_PAGEITEM][FUNCTION_POSITION][ARROW_RIGHT] = PageItemPositionRight;
	//CreatorFunction[LEVEL_PAGEITEM][FUNCTION_POSITION][ARROW_LEFT]  = PageItemPositionLeft;
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
}

//Play Creator Function when Clicked/Pressed
void PageCreator::ArrowKeyUp()
{
	//Play
	CreatorFunction[CurrentLevel][CurrentFunction][ARROW_UP]();

}
 
void PageCreator::ArrowKeyDown()
{
	//Play
	CreatorFunction[CurrentLevel][CurrentFunction][ARROW_DOWN]();
}

void PageCreator::ArrowKeyRight()
{
	//Play
	CreatorFunction[CurrentLevel][CurrentFunction][ARROW_RIGHT]();
}

void PageCreator::ArrowKeyLeft()
{
	//Play
	CreatorFunction[CurrentLevel][CurrentFunction][ARROW_LEFT]();
}



//Arrow Keys with Shift
void PageCreator::SetShift()
{
	Keyboard::KeyButton[GUI_UP_CLICKED][WITH_SHIFT] = ShiftUp;
	Keyboard::KeyButton[GUI_DOWN_CLICKED][WITH_SHIFT] = ShiftDown;
}

void PageCreator::ShiftUp()
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

void PageCreator::ShiftDown()
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

//Arrow Key with Alt
void PageCreator::SetAlternate()
{
	Keyboard::KeyButton[GUI_UP_CLICKED][WITH_ALT] = AlternateUp;
	Keyboard::KeyButton[GUI_DOWN_CLICKED][WITH_ALT] = AlternateDown;
}


void PageCreator::AlternateUp()
{
	if (CurrentLevel < MaxLevel)
	{
		CurrentLevel++;
	}
	if (CurrentLevel == 0)
	{
		Text_CurrentLevel.SetText("Vertex");
	}
	if (CurrentLevel == 1)
	{
		Text_CurrentLevel.SetText("Shape");

	}
	if (CurrentLevel == 2)
	{
		Text_CurrentLevel.SetText("ShapeGroup");
	}
	if (CurrentLevel == 3)
	{
		Text_CurrentLevel.SetText("PageItem");
	}
	if (CurrentLevel == 4)
	{
		Text_CurrentLevel.SetText("PageGroup");
	}
	if (CurrentLevel == 5)
	{
		Text_CurrentLevel.SetText("Page");
	}
	if (CurrentLevel == 6)
	{
		Text_CurrentLevel.SetText("Book");
	}
	cout << "CurrentLevel: " << CurrentLevel << endl;
}

void PageCreator::AlternateDown()
{
	if (CurrentLevel > MinLevel)
	{
		CurrentLevel--;
	}
	if (CurrentLevel == 0)
	{
		Text_CurrentLevel.SetText("Vertex");
	}
	if (CurrentLevel == 1)
	{
		Text_CurrentLevel.SetText("Shape");
	}
	if (CurrentLevel == 2)
	{
		Text_CurrentLevel.SetText("ShapeGroup");
	}
	if (CurrentLevel == 3)
	{
		Text_CurrentLevel.SetText("PageGroup");
	}
	if (CurrentLevel == 4)
	{
		Text_CurrentLevel.SetText("Page");
	}
	if (CurrentLevel == 5)
	{
		Text_CurrentLevel.SetText("Book");
	}
	cout << "CurrentLevel: " << CurrentLevel << endl;
}



void PageCreator::Add()
{
	//ShapeSelected->Add_Default();
	//CurrentFunction = 0;
	Element_Selected->Add_Default();
	CurrentFunction = 0;
}

void PageCreator::Duplicate()
{
	//ShapeSelected->Add_Duplicate();
	//CurrentFunction = 0;
	Element_Selected->Add_Duplicate();
	CurrentFunction = 0;
}

void PageCreator::Insert()
{
	//ShapeSelected->Add_Insert();
	Element_Selected->Add_Insert();
	CurrentFunction = 0;
}

void PageCreator::Next()
{
	Element_Selected->Switch(ShapeSelected->CurrentShapeData.ID + 1);
}

void PageCreator::Previous()
{
	Element_Selected->Switch(ShapeSelected->CurrentShapeData.ID - 1);
}


void PageCreator::Delete()
{
	int PreviousShape = ShapeSelected->CurrentShapeData.ID - 1;
	Element_Selected->Delete();
	Element_Selected->Switch(PreviousShape);
}

void PageCreator::SetQuadSelected(int MouseState, int ShapeHovered)
{
	if (MouseState == GUI_MOUSELEFT_CLICKED && ShapeHovered > -1 && ShapeHovered < CreatorPage->MaxShapeDataCount)
	{
		if (QuadSelected.CurrentShapeData.ID > -1)
		{
			//ShapeSelected->SetColor(PreviousColor);
			Element_Selected->Switch(ShapeHovered);
			//PreviousColor = ShapeSelected->CurrentShapeData.Color;
			//ShapeSelected->SetColor({ 0.0, 1.0, 0.0, 1.0 });
			//cout << "ShapeHovered: " << ShapeHovered << endl;
			//cout << "QuadSelectedID: " << QuadSelected.CurrentShapeData.ID << endl;
		}
	}

}

void PageCreator::SetKeyAdd() { Keyboard::KeyButton[GUI_A_CLICKED][WITH_CTRL] = Add; }
void PageCreator::SetInsertKey() { Keyboard::KeyButton[GUI_INSERT_CLICKED][WITH_DEFAULT] = Insert; }
void PageCreator::SetEraseKey() { Keyboard::KeyButton[GUI_E_CLICKED][WITH_CTRL] = ErasePage; }
void PageCreator::SetSaveKey() { Keyboard::KeyButton[GUI_S_CLICKED][WITH_CTRL] = SavePage; }
void PageCreator::SetKeyDuplicate() { Keyboard::KeyButton[GUI_D_CLICKED][WITH_CTRL] = Duplicate; }
void PageCreator::SetDeleteKey() { Keyboard::KeyButton[GUI_DELETE_CLICKED][WITH_DEFAULT] = Delete; }
void PageCreator::SetKeyNext() { Keyboard::KeyButton[GUI_RIGHT_CLICKED][WITH_CTRL] = Next; }
void PageCreator::SetKeyPrevious() { Keyboard::KeyButton[GUI_LEFT_CLICKED][WITH_CTRL] = Previous; }


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
	Filesystem.SaveBook(*CurrentBook);
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


