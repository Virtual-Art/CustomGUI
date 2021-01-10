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
	CreatorFunction[LEVEL_SHAPE][FUNCTION_POSITION][ARROW_UP]    = ShapePositionUp;
	CreatorFunction[LEVEL_SHAPE][FUNCTION_POSITION][ARROW_DOWN]  = ShapePositionDown;
	CreatorFunction[LEVEL_SHAPE][FUNCTION_POSITION][ARROW_RIGHT] = ShapePositionRight;
	CreatorFunction[LEVEL_SHAPE][FUNCTION_POSITION][ARROW_LEFT]  = ShapePositionLeft;

	//Size
	CreatorFunction[LEVEL_SHAPE][FUNCTION_SIZE][ARROW_UP]    = ShapeSizeUp;
	CreatorFunction[LEVEL_SHAPE][FUNCTION_SIZE][ARROW_DOWN]  = ShapeSizeDown;
	CreatorFunction[LEVEL_SHAPE][FUNCTION_SIZE][ARROW_RIGHT] = ShapeSizeRight;
	CreatorFunction[LEVEL_SHAPE][FUNCTION_SIZE][ARROW_LEFT]  = ShapeSizeLeft;

	//R
	CreatorFunction[LEVEL_SHAPE][FUNCTION_COLOR_R][ARROW_UP]    = ShapeColorRUp;
	CreatorFunction[LEVEL_SHAPE][FUNCTION_COLOR_R][ARROW_DOWN]  = ShapeColorRDown;
	CreatorFunction[LEVEL_SHAPE][FUNCTION_COLOR_R][ARROW_RIGHT] = Empty;
	CreatorFunction[LEVEL_SHAPE][FUNCTION_COLOR_R][ARROW_LEFT]  = Empty;

	//G
	CreatorFunction[LEVEL_SHAPE][FUNCTION_COLOR_G][ARROW_UP] = ShapeColorGUp;
	CreatorFunction[LEVEL_SHAPE][FUNCTION_COLOR_G][ARROW_DOWN] = ShapeColorGDown;
	CreatorFunction[LEVEL_SHAPE][FUNCTION_COLOR_G][ARROW_RIGHT] = Empty;
	CreatorFunction[LEVEL_SHAPE][FUNCTION_COLOR_G][ARROW_LEFT]  = Empty;

	//B
	CreatorFunction[LEVEL_SHAPE][FUNCTION_COLOR_B][ARROW_UP] = ShapeColorBUp;
	CreatorFunction[LEVEL_SHAPE][FUNCTION_COLOR_B][ARROW_DOWN] = ShapeColorBDown;
	CreatorFunction[LEVEL_SHAPE][FUNCTION_COLOR_B][ARROW_RIGHT] = Empty;
	CreatorFunction[LEVEL_SHAPE][FUNCTION_COLOR_B][ARROW_LEFT] = Empty;

	//A
	CreatorFunction[LEVEL_SHAPE][FUNCTION_COLOR_A][ARROW_UP] = ShapeColorAUp;
	CreatorFunction[LEVEL_SHAPE][FUNCTION_COLOR_A][ARROW_DOWN] = ShapeColorADown;
	CreatorFunction[LEVEL_SHAPE][FUNCTION_COLOR_A][ARROW_RIGHT] = Empty;
	CreatorFunction[LEVEL_SHAPE][FUNCTION_COLOR_A][ARROW_LEFT] = Empty;

	/////////////SHAPEGROUP//////////////////

	//Position
	CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_POSITION][ARROW_UP]    = ShapeGroupPositionUp;
	CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_POSITION][ARROW_DOWN]  = ShapeGroupPositionDown;
	CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_POSITION][ARROW_RIGHT] = ShapeGroupPositionRight;
	CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_POSITION][ARROW_LEFT]  = ShapeGroupPositionLeft;
															
	//Size													
	CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_SIZE][ARROW_UP]    = ShapeGroupSizeUp;
	CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_SIZE][ARROW_DOWN]  = ShapeGroupSizeDown;
	CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_SIZE][ARROW_RIGHT] = ShapeGroupSizeRight;
	CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_SIZE][ARROW_LEFT]  = ShapeGroupSizeLeft;
																	  
	//R																  
	CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_COLOR_R][ARROW_UP]     = ShapeGroupColorRUp;
	CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_COLOR_R][ARROW_DOWN]   = ShapeGroupColorRDown;
	CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_COLOR_R][ARROW_RIGHT]  = Empty;
	CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_COLOR_R][ARROW_LEFT]   = Empty;
															
	//G														
	CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_COLOR_G][ARROW_UP]     = ShapeGroupColorGUp;
	CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_COLOR_G][ARROW_DOWN]   = ShapeGroupColorGDown;
	CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_COLOR_G][ARROW_RIGHT]  = Empty;
	CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_COLOR_G][ARROW_LEFT]   = Empty;
																	 
	//B																 
	CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_COLOR_B][ARROW_UP]     = ShapeGroupColorBUp;
	CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_COLOR_B][ARROW_DOWN]   = ShapeGroupColorBDown;
	CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_COLOR_B][ARROW_RIGHT]  = Empty;
	CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_COLOR_B][ARROW_LEFT]   = Empty;
																	  
	//A																  
	CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_COLOR_A][ARROW_UP]     = ShapeGroupColorAUp;
	CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_COLOR_A][ARROW_DOWN]   = ShapeGroupColorADown;
	CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_COLOR_A][ARROW_RIGHT]  = Empty;
	CreatorFunction[LEVEL_SHAPEGROUP][FUNCTION_COLOR_A][ARROW_LEFT]   = Empty;

	//																  
	CreatorFunction[LEVEL_SHAPEGROUP][MAINFUNCTION_6][ARROW_UP] = Empty;
	CreatorFunction[LEVEL_SHAPEGROUP][MAINFUNCTION_6][ARROW_DOWN] = Empty;
	CreatorFunction[LEVEL_SHAPEGROUP][MAINFUNCTION_6][ARROW_RIGHT] = Empty;
	CreatorFunction[LEVEL_SHAPEGROUP][MAINFUNCTION_6][ARROW_LEFT] = Empty;


	// Page Item Group
	CreatorFunction[LEVEL_PAGEITEM][FUNCTION_POSITION][ARROW_UP]    = PageItemPositionUp;
	CreatorFunction[LEVEL_PAGEITEM][FUNCTION_POSITION][ARROW_DOWN]  = PageItemPositionDown;
	CreatorFunction[LEVEL_PAGEITEM][FUNCTION_POSITION][ARROW_RIGHT] = PageItemPositionRight;
	CreatorFunction[LEVEL_PAGEITEM][FUNCTION_POSITION][ARROW_LEFT]  = PageItemPositionLeft;
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
	PageItemSelected->Add_Default();
	CurrentFunction = 0;
}

void PageCreator::Duplicate()
{
	//ShapeSelected->Add_Duplicate();
	//CurrentFunction = 0;
	PageItemSelected->Add_Duplicate();
	CurrentFunction = 0;
}

void PageCreator::Insert()
{
	//ShapeSelected->Add_Insert();
	PageItemSelected->Add_Insert();
	CurrentFunction = 0;
}

void PageCreator::Next()
{
	ShapeSelected->SwitchToShape(ShapeSelected->CurrentShapeData.ID + 1);
}

void PageCreator::Previous()
{
	ShapeSelected->SwitchToShape(ShapeSelected->CurrentShapeData.ID - 1);
}


void PageCreator::Delete()
{
	int PreviousShape = ShapeSelected->CurrentShapeData.ID - 1;
	ShapeSelected->DeleteShape();
	ShapeSelected->SwitchToShape(PreviousShape);
}

void PageCreator::SetQuadSelected(int MouseState, int ShapeHovered)
{
	if (MouseState == GUI_MOUSELEFT_CLICKED && ShapeHovered > -1 && ShapeHovered < CreatorPage->MaxShapeDataCount)
	{
		if (QuadSelected.CurrentShapeData.ID > -1)
		{
			//ShapeSelected->SetColor(PreviousColor);
			Element_Selected->SwitchToShape(ShapeHovered);
			//PreviousColor = ShapeSelected->CurrentShapeData.Color;
			//ShapeSelected->SetColor({ 0.0, 1.0, 0.0, 1.0 });
			cout << "ShapeHovered: " << ShapeHovered << endl;
			cout << "QuadSelectedID: " << QuadSelected.CurrentShapeData.ID << endl;
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
void PageCreator::ShapePositionUp()
{
	Element_Selected->OffsetPosition({ 0.0, 0.00166 * PixelOffset }, OnlyY);
}
void PageCreator::ShapePositionDown()
{
	Element_Selected->OffsetPosition({ 0.0, -0.00166 * PixelOffset }, OnlyY);
}
void PageCreator::ShapePositionRight()
{
	Element_Selected->OffsetPosition({ 0.00166 * PixelOffset, 0.0 }, OnlyX);
}
void PageCreator::ShapePositionLeft()
{
	Element_Selected->OffsetPosition({ -0.00166 * PixelOffset, 0.0 }, OnlyX);
}

//SIZE
void PageCreator::ShapeSizeUp()
{
	Element_Selected->OffsetSize({ 0.0, 0.00166 * PixelOffset }, OnlyX);
}
void PageCreator::ShapeSizeDown()
{
	Element_Selected->OffsetSize({ 0.0, 0.00166 * -PixelOffset }, OnlyY);
}
void PageCreator::ShapeSizeRight()
{
	Element_Selected->OffsetSize({ 0.00166 * PixelOffset, 0.0 }, OnlyX);
}
void PageCreator::ShapeSizeLeft()
{
	Element_Selected->OffsetSize({ 0.00166 * -PixelOffset, 0.0}, OnlyX);
}

// COLOR
void PageCreator::ShapeColorRUp()
{
	if (Element_Selected->GetColor()[0] < 1.0)
	{
		Element_Selected->OffsetColor({ 0.01 * PixelOffset, 0.0, 0.0, 0.0 }, OnlyR);
	}
}
void PageCreator::ShapeColorRDown()
{
	if (Element_Selected->GetColor()[1] > 1.0)
	{
		Element_Selected->OffsetColor({ 0.01 * -PixelOffset, 0.0, 0.0, 0.0 }, OnlyR);
	}
}

void PageCreator::ShapeColorGUp()
{
	if (Element_Selected->GetColor()[1] < 1.0)
	{
		Element_Selected->OffsetColor({ 0.0, 0.01 * PixelOffset,  0.0, 0.0 }, OnlyG);
	}
}

void PageCreator::ShapeColorGDown()
{
	if (Element_Selected->GetColor()[1] > 0.0)
	{
		Element_Selected->OffsetColor({ 0.0, 0.01 * -PixelOffset,  0.0, 0.0 }, OnlyG);
	}
}

void PageCreator::ShapeColorBUp()
{
	if (Element_Selected->GetColor()[2] < 1.0)
	{
		Element_Selected->OffsetColor({ 0.0, 0.0, 0.01 * PixelOffset, 0.0 }, OnlyB);
	}
}
void PageCreator::ShapeColorBDown()
{
	if (Element_Selected->GetColor()[2] > 1.0)
	{
		Element_Selected->OffsetColor({ 0.0, 0.0, 0.01 * -PixelOffset,  0.0 }, OnlyB);
	}
}

void PageCreator::ShapeColorAUp()
{
	if (Element_Selected->GetColor()[3] < 1.0)
	{
		Element_Selected->OffsetColor({ 0.0, 0.0, 0.0, 0.01 * PixelOffset }, OnlyA);
	}
}
void PageCreator::ShapeColorADown()
{
	if (Element_Selected->GetColor()[3] > 1.0)
	{
		Element_Selected->OffsetColor({ 0.0, 0.0, 0.0, 0.01 * -PixelOffset }, OnlyA);
	}
}

////////////////ShapeGroup////////////////////////////////////
// POSITION
void PageCreator::ShapeGroupPositionUp()
{
	ShapeSelected->CurrentShapeData.Position[1] += 0.00166 * PixelOffset;
	ShapeSelected->OffsetPosition({ 0.0, 0.00166 }, OnlyX);
}
void PageCreator::ShapeGroupPositionDown()
{
	ShapeSelected->CurrentShapeData.Position[1] -= 0.00166 * PixelOffset;
	ShapeSelected->OffsetPosition({ 0.0, -0.00166 }, OnlyX);
}
void PageCreator::ShapeGroupPositionRight()
{
	ShapeSelected->CurrentShapeData.Position[0] += 0.00166 * PixelOffset;
	ShapeSelected->OffsetPosition({ 0.00166, 0.0 }, OnlyY);
}
void PageCreator::ShapeGroupPositionLeft()
{
	ShapeSelected->CurrentShapeData.Position[0] -= 0.00166 * PixelOffset;
	ShapeSelected->OffsetPosition({ -0.00166, 0.0 }, OnlyY);
}

//SIZE
void PageCreator::ShapeGroupSizeUp()
{
	ShapeSelected->CurrentShapeData.Size[1] += 0.00166 * PixelOffset;
	ShapeSelected->OffsetSize({ OnePixel * PixelOffset, 0.0 }, OnlyY);
}
void PageCreator::ShapeGroupSizeDown()
{
	ShapeSelected->CurrentShapeData.Size[1] -= 0.00166 * PixelOffset;
	ShapeSelected->OffsetSize({ OnePixel * -PixelOffset, 0.0 }, OnlyY);
}
void PageCreator::ShapeGroupSizeRight()
{
	ShapeSelected->CurrentShapeData.Size[0] += 0.00166 * PixelOffset;
	ShapeSelected->OffsetSize({ 0.0, OnePixel * PixelOffset }, OnlyX);
}
void PageCreator::ShapeGroupSizeLeft()
{
	ShapeSelected->CurrentShapeData.Size[0] -= 0.00166 * PixelOffset;
	ShapeSelected->OffsetSize({ 0.0, OnePixel * -PixelOffset }, OnlyX);
}

// COLOR
void PageCreator::ShapeGroupColorRUp()
{
	if (ShapeSelected->CurrentShapeData.Color[0] < 1.0)
	{
		ShapeSelected->CurrentShapeData.Color[0] += 0.01;
		ShapeSelected->OffsetColor({ OnePixel * PixelOffset, 0.0, 0.0, 0.0 }, OnlyR);
		cout << "Coloring " << endl;
	}
}
void PageCreator::ShapeGroupColorRDown()
{
	if (ShapeSelected->CurrentShapeData.Color[1] > 1.0)
	{
		ShapeSelected->CurrentShapeData.Color[0] -= 0.01;
		ShapeSelected->OffsetColor({ OnePixel * -PixelOffset, 0.0, 0.0, 0.0 }, OnlyR);
	}
}

void PageCreator::ShapeGroupColorGUp()
{
	if (ShapeSelected->CurrentShapeData.Color[1] < 1.0)
	{
		ShapeSelected->CurrentShapeData.Color[1] += 0.01;
		ShapeSelected->OffsetColor({ 0.0, OnePixel * PixelOffset,  0.0, 0.0 }, OnlyG);
	}
}

void PageCreator::ShapeGroupColorGDown()
{
	if (ShapeSelected->CurrentShapeData.Color[1] > 0.0)
	{
		ShapeSelected->CurrentShapeData.Color[1] -= 0.01;
		ShapeSelected->OffsetColor({ 0.0, OnePixel * -PixelOffset,  0.0, 0.0 }, OnlyG);
	}
}

void PageCreator::ShapeGroupColorBUp()
{
	if (ShapeSelected->CurrentShapeData.Color[2] < 1.0)
	{
		ShapeSelected->CurrentShapeData.Color[2] += 0.01;
		ShapeSelected->OffsetColor({ 0.0, 0.0, OnePixel * PixelOffset, 0.0 }, OnlyB);
	}
}
void PageCreator::ShapeGroupColorBDown()
{
	if (ShapeSelected->CurrentShapeData.Color[2] > 1.0)
	{
		ShapeSelected->CurrentShapeData.Color[2] -= 0.01;
		ShapeSelected->OffsetColor({ 0.0, 0.0, OnePixel * -PixelOffset,  0.0 }, OnlyB);
	}
}

void PageCreator::ShapeGroupColorAUp()
{
	if (ShapeSelected->CurrentShapeData.Color[3] < 1.0)
	{
		ShapeSelected->CurrentShapeData.Color[3] += 0.01;
		ShapeSelected->OffsetColor({ 0.0, 0.0, 0.0, OnePixel * PixelOffset }, OnlyA);
	}
}
void PageCreator::ShapeGroupColorADown()
{
	if (ShapeSelected->CurrentShapeData.Color[3] > 1.0)
	{
		ShapeSelected->CurrentShapeData.Color[3] -= 0.01;
		ShapeSelected->OffsetColor({ 0.0, 0.0, 0.0, OnePixel * -PixelOffset }, OnlyA);
	}
}

////////////////////////////////////////////////////////////////////

// POSITION
void PageCreator::PageItemPositionUp()
{
	PageItemSelected->CurrentPageItem.Position[1] += 0.00166 * PixelOffset;
	PageItemSelected->OffsetPosition({ 0.0, 0.00166 }, OnlyX);
}
void PageCreator::PageItemPositionDown()
{
	PageItemSelected->CurrentPageItem.Position[1] -= 0.00166 * PixelOffset;
	PageItemSelected->OffsetPosition({ 0.0, -0.00166 }, OnlyX);
}
void PageCreator::PageItemPositionRight()
{
	PageItemSelected->CurrentPageItem.Position[0] += 0.00166 * PixelOffset;
	PageItemSelected->OffsetPosition({ 0.00166, 0.0 }, OnlyY);
}
void PageCreator::PageItemPositionLeft()
{
	PageItemSelected->CurrentPageItem.Position[0] -= 0.00166 * PixelOffset;
	PageItemSelected->OffsetPosition({ -0.00166, 0.0 }, OnlyY);
}

