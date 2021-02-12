#include "PageCreator.h"

void PageCreator::llInit(llBookData* llBook, ShaderProgram* ShaderProgram, RawTexture* Texture0, RawTexture* Texture1, RawTexture* Texture2)
{
	TextData Text_Details;
	llShapeGroupData ShapeGroup_Details;

	CurrentBook = llBook;

	CurrentTextures[0] = Texture0;
	CurrentTextures[1] = Texture1;
	CurrentTextures[2] = Texture2;

	CurrentText = "";

	CurrentShader = ShaderProgram;
	SetElements();

	//Working Book Setup
	//Defaults
	ShapeEditor.llInit(CurrentBook);
	ShapeGroupEditor.llInit(CurrentBook);
	PageItemEditor.llInit(CurrentBook);
	PageGroupEditor.llInit(CurrentBook);
	PageEditor.llInit(CurrentBook, CurrentShader, Texture0, Texture1, Texture2);

	//Presets
	QuadEditor.llInit(CurrentBook);
	CharacterEditor.llInit(CurrentBook);
	TextEditor.llInit(CurrentBook);
	SliderEditor.llInit(CurrentBook);

	CreateFunctionContainer(); //Build "Creator" Function Table
	SetCreatorFunctions();     //Set Functions To Function Table
	SetKeyboardKeys();

	//BookEditor Setup
	BookCreatorPage.llInit(&CreatorBook, CurrentShader, Texture0, Texture1, Texture2);
	Quad DeleteWhenFixed(&CreatorBook);
	DeleteWhenFixed.SetllPosition({-2.0, 0.0});

	Quad Quad_Find(CurrentBook);
	Quad_Find.SetllPosition({-2.0, 0.0});

	//Text UniqueSlider(CurrentBook);
	//UniqueSlider.SetllPosition({0.5, 0.5});
	//Text UniqueSlider1(CurrentBook);
	//UniqueSlider1.SetllPosition({0.5, -0.5});

	EditorSelected = &QuadEditor;


	Text_Details.Phrase = "Press Shift + Up/Down or Left/Right To Switch levels or Neighbour Elements";
	Text_Details.Centered = true;
	ShapeGroup_Details.Position = { 0.0, 0.95 };
	ShapeGroup_Details.Color = Purple;
	Text_Shift.llInit(&CreatorBook, &ShapeGroup_Details, Text_Details);

	Text_Details.Phrase = "Press Alt + Up/Down or Right/Left To Switch Options or Element Types";
	Text_Details.Centered = true;
	ShapeGroup_Details.Position = { 0.0, 0.85 };
	ShapeGroup_Details.Color = Orange;
	Text_AltRightLeft.llInit(&CreatorBook, &ShapeGroup_Details, Text_Details);

	Text_Details.Phrase = "Press Ctrl + A to Add and Arrow Keys to use the Option Selected";
	Text_Details.Centered = true;
	ShapeGroup_Details.Position = { 0.0, 0.75 };
	ShapeGroup_Details.Color = Yellow;
	Text_AltUpDown.llInit(&CreatorBook, &ShapeGroup_Details, Text_Details);

	//Current Level
	//Label
	Text_Details.Phrase = "Current Level: ";
	Text_Details.Centered = false;
	ShapeGroup_Details.Position = { -0.95, 0.8 };
	ShapeGroup_Details.Color = { 0.171, 0.8461 , 0.95 , 1.0};
	Text_CurrentLevel_Label.llInit(&CreatorBook, &ShapeGroup_Details, Text_Details);

	//Level
	Text_Details.Phrase = "Shape";
	ShapeGroup_Details.Position = { -0.95, 0.7 };
	ShapeGroup_Details.Color = Black;
	Text_CurrentLevel.llInit(&CreatorBook, &ShapeGroup_Details, Text_Details);

	//Current Function
	//Label
	Text_Details.Phrase = "Current Option: ";
	ShapeGroup_Details.Position = { -0.95, 0.6 };
	ShapeGroup_Details.Color = { 0.171, 0.8461 , 0.95 , 1.0 };
	Text_CurrentFunction_Label.llInit(&CreatorBook, &ShapeGroup_Details, Text_Details);

	//Options
	Text_Details.Phrase = "Position";
	ShapeGroup_Details.Position = { -0.95, 0.5 };
	ShapeGroup_Details.Color = Black;
	Text_CurrentFunction.llInit(&CreatorBook, &ShapeGroup_Details, Text_Details);
}

void PageCreator::OnUpdate(KeyResult& KeyState, int MouseState)
{
	BookCreatorPage.DrawPage();
	PageEditor.DrawPage();

	CurrentKeyResult = &KeyState;
	CurrentMouseState = MouseState;

	if (CurrentLevel == LEVEL_SHAPEGROUP && CurrentType == TYPE_TEXT && KeyState.Ctrl != true && KeyState.CurrentAscii != -1 && KeyState.Key1 != 0)
	{
		CurrentText = TextEditor.GetText();
		if (CurrentText == "TEXT" || CurrentText == " ")
		{
			CurrentText = "";
		}
		CurrentText += KeyState.CurrentAscii;
		Log::LogString(CurrentText);
		TextEditor.SetllText(CurrentText);
	}

	if (CurrentLevel == LEVEL_SHAPEGROUP && CurrentType == TYPE_TEXT && KeyState.Ctrl != true &&KeyState.Key1 == GUI_BACKSPACE_CLICKED || KeyState.Key1 == GUI_BACKSPACE_PRESSED)
	{
		if (CurrentText.size() > 1)
		{
			CurrentText.erase(CurrentText.size() - 1);
		}
		else
		{
			CurrentText = " ";
		}
		TextEditor.SetllText(CurrentText);
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
		Text_CurrentFunction.SetllText("Position");
	}
	if (CurrentFunction == 1)
	{
		Text_CurrentFunction.SetllText("Size");
	}
	if (CurrentFunction == 2)
	{
		Text_CurrentFunction.SetllText("R Color");
	}
	if (CurrentFunction == 3)
	{
		Text_CurrentFunction.SetllText("G Color");
	}
	if (CurrentFunction == 4)
	{
		Text_CurrentFunction.SetllText("B Color");
	}
	if (CurrentFunction == 5)
	{
		Text_CurrentFunction.SetllText("A Color");
	}
	if (CurrentFunction == 6)
	{
		Text_CurrentFunction.SetllText("Function Not Set");
	}
	if (CurrentFunction == 7)
	{
		Text_CurrentFunction.SetllText("Function Not Set");
	}
	if (CurrentFunction == 8)
	{
		Text_CurrentFunction.SetllText("Function Not Set");
	}
	if (CurrentFunction == 9)
	{
		Text_CurrentFunction.SetllText("Function Not Set");
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
		Text_CurrentFunction.SetllText("Position");
	}
	if (CurrentFunction == 1)
	{
		Text_CurrentFunction.SetllText("Size");
	}
	if (CurrentFunction == 2)
	{
		Text_CurrentFunction.SetllText("R Color");
	}
	if (CurrentFunction == 3)
	{
		Text_CurrentFunction.SetllText("G Color");
	}
	if (CurrentFunction == 4)
	{
		Text_CurrentFunction.SetllText("B Color");
	}
	if (CurrentFunction == 5)
	{
		Text_CurrentFunction.SetllText("A Color");
	}
	if (CurrentFunction == 6)
	{
		Text_CurrentFunction.SetllText("Function Not Set");
	}
	if (CurrentFunction == 7)
	{
		Text_CurrentFunction.SetllText("Function Not Set");
	}
	if (CurrentFunction == 8)
	{
		Text_CurrentFunction.SetllText("Function Not Set");
	}
	if (CurrentFunction == 9)
	{
		Text_CurrentFunction.SetllText("Function Not Set");
	}
	cout << "CurrentFunction: " << CurrentFunction << endl;
}

void PageCreator::TypeRight()
{
	Log::LogInt("CurrentLevel", CurrentLevel);
	Log::LogInt("CurrentType: ", CurrentType);
	switch (CurrentLevel)
	{
	case LEVEL_VERTEX:
		//Element_Selected = &Vertex_Selected;
		break;
	case LEVEL_SHAPE:
		if (CurrentType < 2)
		{
	Log::LogString("Level Shape");
			CurrentType++;
			SetShapeType();
		}
		break;
	case LEVEL_SHAPEGROUP:
		if (CurrentType < 1)
		{
			CurrentType++;
			SetShapeGroupType();
		}
		break;
	case LEVEL_PAGEITEM:
		if (CurrentType < 1)
		{
			CurrentType++;
			SetPageItemType();
		}
		break;
	case LEVEL_PAGEGROUP:
		//Only One Type
		SetPageGroupType();
		break;
	case LEVEL_PAGE:
		//Only one type
		SetPageType();
		break;
	}
}

void PageCreator::TypeLeft()
{
	Log::LogString("TypeLeft");
	switch (CurrentLevel)
	{
	case LEVEL_VERTEX:
		//Element_Selected = &Vertex_Selected;
		break;
	case LEVEL_SHAPE:
		if (CurrentType > 0)
		{
			CurrentType--;
			SetShapeType();
			break;
	case LEVEL_SHAPEGROUP:
		if (CurrentType > 0)
		{
			CurrentType--;
			SetShapeGroupType();
		}
		break;
	case LEVEL_PAGEITEM:
		if (CurrentType > 0)
		{
			CurrentType--;
			SetPageItemType();
		}
		break;
	case LEVEL_PAGEGROUP:
		//Only One Type
		SetPageGroupType();
		break;
	case LEVEL_PAGE:
		//Only one type
		SetPageType();
		break;
		}
	}
}

void PageCreator::DataRight()
{
	Log::LogString("Data Right");
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
		else
		{
			Log::LogString("Shape Edge");
		}
		break;

	case LEVEL_SHAPEGROUP:
		
		if (CurrentShapeGroup->Next != nullptr)
		{
			CurrentShapeGroup = CurrentShapeGroup->Next;
			CurrentShape = CurrentShapeGroup->Shape;
			CurrentType = CurrentShapeGroup->Type;
			SetShapeGroupType();
		}
		else
		{
			Log::LogString("ShapeGroup Edge");
		}
		break;

	case LEVEL_PAGEITEM:

		if (CurrentPageItem->Next != nullptr)
		{
			CurrentPageItem = CurrentPageItem->Next;
			CurrentShapeGroup = CurrentPageItem->ShapeGroup;
			CurrentShape = CurrentPageItem->ShapeGroup->Shape;
			cout << "PageItem Switching to: " << CurrentPageItem << endl;
			CurrentType = CurrentPageItem->Type;
			SetPageItemType();
		}
		else
		{
			Log::LogString("PageItem Edge");
		}
	    break;

	case LEVEL_PAGEGROUP:

		if (CurrentPageGroup->Next != nullptr)
		{
			CurrentPageGroup = CurrentPageGroup->Next;
			SetPageGroupType();
		}
		else
		{
			Log::LogString("PageGroup Edge");
		}
		break;

	case LEVEL_PAGE:
		if (CurrentPage->Next != nullptr)
		{
			CurrentPage = CurrentPage->Next;
			SetPageType();
		}
		else
		{
			Log::LogString("Page Edge");
		}
		break;
	}
}

void PageCreator::DataLeft()
{
	Log::LogString("Data Left");
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
			SetShapeType();
		}
		else
		{
			Log::LogString("Shape Edge");
		}
		break;

	case LEVEL_SHAPEGROUP:
		if (CurrentShapeGroup->Previous != nullptr)
		{
			CurrentShapeGroup = CurrentShapeGroup->Previous;
			CurrentShape = CurrentShapeGroup->Shape;
			CurrentType = CurrentShapeGroup->Type;
			SetShapeGroupType();
		}
		else
		{
			Log::LogString("ShapeGroup Edge");
		}
		break;

	case LEVEL_PAGEITEM:

		if (CurrentPageItem->Previous != nullptr)
		{
			//Go To previous PageItem if that page item is slider go to slider editor, or if its page item go to 
			//page item editor
			CurrentPageItem = CurrentPageItem->Previous;
			CurrentShapeGroup = CurrentPageItem->ShapeGroup;
			CurrentShape = CurrentPageItem->ShapeGroup->Shape;
			cout << "PageItem Now:" << CurrentPageItem << endl;
			CurrentType = CurrentPageItem->Type;
			SetPageItemType();
		}
		else
		{
			Log::LogString("PageItem Edge");
		}
		break;

	case LEVEL_PAGEGROUP:

		if (CurrentPageGroup->Previous != nullptr)
		{
			CurrentPageGroup = CurrentPageGroup->Previous;
			SetPageGroupType();
		}
		else
		{
			Log::LogString("PageGroup Edge");
		}
		break;

	case LEVEL_PAGE:
		if (CurrentPage->Previous != nullptr)
		{
			CurrentPage = CurrentPage->Previous;
			SetPageType();
		}
		else
		{
			Log::LogString("Page Edge");
		}
		break;
	}
}

void PageCreator::SetShapeType()
{
	switch (CurrentType)
	{
	case TYPE_SHAPE:
		EditorSelected = &ShapeEditor;
		//SetElements();
		ShapeEditor.llSwitch(CurrentShape);
		Text_CurrentLevel.SetllText("Shape");
		break;

	case TYPE_SHAPE_QUAD:
		EditorSelected = &QuadEditor;
		//SetElements();
		QuadEditor.llSwitch(CurrentShape);
		Text_CurrentLevel.SetllText("Quad");
		break;

	case TYPE_SHAPE_CHARACTER:
		EditorSelected = &CharacterEditor;
		//SetElements();
		CharacterEditor.llSwitch(CurrentShape);
		Text_CurrentLevel.SetllText("Character");
		break;
	}
}

void PageCreator::SetShapeGroupType()
{
	switch (CurrentType)
	{
	case TYPE_SHAPEGROUP:
		EditorSelected = &ShapeGroupEditor;
		ShapeGroupEditor.llSwitch(CurrentShapeGroup);
		Text_CurrentLevel.SetllText("ShapeGroup");
		break;
	case TYPE_SHAPEGROUP_TEXT:
		EditorSelected = &TextEditor;
		TextEditor.llSwitch(CurrentShapeGroup);
		Text_CurrentLevel.SetllText("Text");
		break;
	}
}

void PageCreator::SetPageItemType()
{
	switch (CurrentType)
	{
	case TYPE_PAGEITEM:
		EditorSelected = &PageItemEditor;
		//SetElements();
		PageItemEditor.llSwitch(CurrentPageItem);
		Text_CurrentLevel.SetllText("PageItem");
		break;
	case TYPE_PAGEITEM_SLIDER:
		EditorSelected = &SliderEditor;
		cout << "PageItem Switching to: " << CurrentPageItem << endl;
		//SetElements();
		SliderEditor.llSwitch(CurrentPageItem);
		Text_CurrentLevel.SetllText("Slider");
		break;
	}
}

void PageCreator::SetPageGroupType()
{
	switch (CurrentType)
	{
	case TYPE_PAGEGROUP:
		EditorSelected = &PageGroupEditor;
		//SetElements();
		PageGroupEditor.llSwitch(CurrentPageGroup);
		Text_CurrentLevel.SetllText("PageGroup");
		break;
	}
}

void PageCreator::SetPageType()
{
	switch (CurrentType)
	{
	case TYPE_PAGE:
		EditorSelected = &PageEditor;
		SetElements();
		PageEditor.llSwitch(CurrentPage);
		Text_CurrentLevel.SetllText("Page");
		break;
	}
}

//Arrow Key with Alt
void PageCreator::SetAlternate()
{
	Keyboard::KeyButton[GUI_UP_CLICKED][WITH_ALT] = OptionsUp;
	Keyboard::KeyButton[GUI_DOWN_CLICKED][WITH_ALT] = OptionsDown;
	Keyboard::KeyButton[GUI_RIGHT_CLICKED][WITH_ALT] = TypeRight;
	Keyboard::KeyButton[GUI_LEFT_CLICKED][WITH_ALT] = TypeLeft;
}


void PageCreator::LevelUp()
{
	cout << "Switching level" << endl;
	if (CurrentLevel < MaxLevel)
	{
		CurrentLevel++;
	}

	CurrentType = 0;
	
	switch (CurrentLevel)
	{
	case LEVEL_VERTEX:
		//Element_Selected = &Vertex_Selected;
		Text_CurrentLevel.SetllText("Vertex");
		break;
	case LEVEL_SHAPE:
		EditorSelected = &ShapeEditor; //Supposed to set type here, won't always be basic type
		if (CurrentShape != nullptr)
		{
			CurrentType = CurrentShape->Type;
		}
		Text_CurrentLevel.SetllText("Shape");
		SetShapeType();
		break;
	case LEVEL_SHAPEGROUP:
		EditorSelected = &ShapeGroupEditor; //Supposed to set type here, won't always be basic type
		if (CurrentShapeGroup != nullptr)
		{
			CurrentType = CurrentShapeGroup->Type;
		}
		Text_CurrentLevel.SetllText("ShapeGroup");
		SetShapeGroupType();
		break;
	case LEVEL_PAGEITEM:
		EditorSelected = &PageItemEditor; //Supposed to set type here, won't always be basic type
		if (CurrentShapeGroup != nullptr)
		{
			CurrentType = CurrentShapeGroup->Type;
		}
		Text_CurrentLevel.SetllText("PageItem");
		SetPageItemType();
		break;
	case LEVEL_PAGEGROUP:
		//CurrentPageGroup = CurrentBook->Page->PageGroup;
		//PageGroupSelected.llSwitch(CurrentPageGroup);
		//CurrentType = CurrentPageGroup->Type;
		EditorSelected = &PageGroupEditor; //Supposed to set type here, won't always be basic type
		Text_CurrentLevel.SetllText("PageGroup");
		break;
	case LEVEL_PAGE:
		//CurrentPage = CurrentBook->Page;
		//PageSelected.llSwitch(CurrentPage);
		//CurrentType = 0;
	    EditorSelected = &PageEditor;//Supposed to set type here, won't always be basic type
		Text_CurrentLevel.SetllText("Page");
		break;
	}
}

void PageCreator::LevelDown()
{
	cout << "Switching level" << endl;
	if (CurrentLevel > MinLevel)
	{
		CurrentLevel--;
	}

	CurrentType = 0;

	switch (CurrentLevel)
	{
	case LEVEL_VERTEX:
		//Element_Selected = &Vertex_Selected;
		Text_CurrentLevel.SetllText("Vertex");
		break;
	case LEVEL_SHAPE:
		EditorSelected = &ShapeEditor;
		if (CurrentShape != nullptr)
		{
			CurrentType = CurrentShape->Type;
		}
		Text_CurrentLevel.SetllText("Shape");
		SetShapeType();
		break;
	case LEVEL_SHAPEGROUP:
		EditorSelected = &ShapeGroupEditor;
		if (CurrentShapeGroup != nullptr)
		{
			CurrentType = CurrentShapeGroup->Type;
		}
		SetShapeGroupType();
		Text_CurrentLevel.SetllText("ShapeGroup");
		break;
	case LEVEL_PAGEITEM:
		EditorSelected = &PageItemEditor;
		if (CurrentPageItem != nullptr)
		{
			CurrentType = CurrentPageItem->Type;
		}
		Text_CurrentLevel.SetllText("PageItem");
		SetPageItemType();
		break;
	case LEVEL_PAGEGROUP:
		//Element_Selected = &PageGroupSelected;
		Text_CurrentLevel.SetllText("PageGroup");
		break;
	case LEVEL_PAGE:
		//Element_Selected = &PageSelected;
		Text_CurrentLevel.SetllText("Page");
		break;
	}
}




void PageCreator::Add()
{
	SetBookFromElements();
	EditorSelected->Add_Default();
	CurrentFunction = 0;
	SetElements();
}

void PageCreator::Duplicate()
{
	EditorSelected->Add_Duplicate();
	CurrentFunction = 0;
	//SetElements();
}

void PageCreator::Insert()
{
	EditorSelected->Add_Insert();
	CurrentFunction = 0;
	//SetElements();
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
	EditorSelected->Delete();
	//Element_Selected->Switch(PreviousShape);
}

void PageCreator::SetQuadSelected(int MouseState, int ShapeHovered)
{
	if (MouseState == GUI_MOUSELEFT_CLICKED && ShapeHovered > -1 && ShapeHovered < CreatorPage->MaxShapeDataCount)
	{
		if (QuadEditor.CurrentShapeData.ID > -1)
		{
			EditorSelected->Switch(ShapeHovered);
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
	//SetKeyNext(); 
	//SetKeyPrevious(); 
}

void PageCreator::Empty()
{

}

void PageCreator::SetBookFromElements()
{
	if (CurrentPage != nullptr)
	{
		CurrentBook->Page = CurrentPage;

		if (CurrentPageGroup != nullptr)
		{
			CurrentBook->Page->PageGroup = CurrentPageGroup;

			if (CurrentPageItem != nullptr)
			{
				CurrentBook->Page->PageGroup->PageItem = CurrentPageItem;

				if (CurrentShapeGroup != nullptr)
				{
					CurrentBook->Page->PageGroup->PageItem->ShapeGroup = CurrentShapeGroup;

					if (CurrentShape != nullptr)
					{
						CurrentBook->Page->PageGroup->PageItem->ShapeGroup->Shape = CurrentShape;

						if (CurrentVertex != nullptr)
						{
							CurrentBook->Page->PageGroup->PageItem->ShapeGroup->Shape->Vertexx = CurrentShape->Vertexx;
						}
					}
				}
			}
		}
	}
}

void PageCreator::SetElements()
{
	Log::LogString("Setting Elements");
	//Page
	if (CurrentBook->Page != nullptr)
	{
		//Log::LogString("Page Set");
		CurrentPage = CurrentBook->Page;
		cout << "Page Set" << CurrentPage << endl;

		//PageGroup
		if (CurrentBook->Page->PageGroup != nullptr)
		{
			//Log::LogString("PageGroup Set");
			CurrentPageGroup = CurrentBook->Page->PageGroup;
			cout << "PageGroup Set" << CurrentPageGroup << endl;

			//PageItem
			if (CurrentBook->Page->PageGroup->PageItem != nullptr)
			{
				//Log::LogString("PageItem Set");
				CurrentPageItem = CurrentBook->Page->PageGroup->PageItem;
				cout << "PageItem Set" << CurrentPageItem << endl;
			
				//ShapeGroup
				if (CurrentBook->Page->PageGroup->PageItem->ShapeGroup != nullptr)
				{
					//Log::LogString("ShapeGroup Set");
					CurrentShapeGroup = CurrentBook->Page->PageGroup->PageItem->ShapeGroup;
					cout << "ShapeGroup Set" << CurrentShapeGroup << endl;

					//Shape
					if (CurrentBook->Page->PageGroup->PageItem->ShapeGroup->Shape != nullptr)
					{
						//Log::LogString("Shape Set");
						CurrentShape = CurrentBook->Page->PageGroup->PageItem->ShapeGroup->Shape;
						cout << "Shape Set" << CurrentShape << endl;

						//Vertex
						if (CurrentBook->Page->PageGroup->PageItem->ShapeGroup->Shape->Vertexx != nullptr)
						{
							//Log::LogString("Vertex Set");
							CurrentVertex = CurrentBook->Page->PageGroup->PageItem->ShapeGroup->Shape->Vertexx;
							cout << "Vertex Set" << CurrentVertex << endl;
						}
						else
						{
							Log::LogString("Rest of Elements Empty");
							CurrentVertex = nullptr;
						}
					}
					else
					{
						Log::LogString("Rest of Elements Empty");
						CurrentVertex = nullptr;
						CurrentShape = nullptr;
					}
				}
				else
				{
					Log::LogString("Rest of Elements Empty");
					CurrentVertex = nullptr;
					CurrentShape = nullptr;
					CurrentShapeGroup = nullptr;
				}
			}
			else
			{
				Log::LogString("Rest of Elements Empty");
				CurrentVertex = nullptr;
				CurrentShape = nullptr;
				CurrentShapeGroup = nullptr;
				CurrentPageItem = nullptr;
			}
		}
		else
		{
			Log::LogString("Rest of Elements Empty");
			CurrentVertex = nullptr;
			CurrentShape = nullptr;
			CurrentShapeGroup = nullptr;
			CurrentPageItem = nullptr;
			CurrentPageGroup = nullptr;
		}
	}
	else
	{
		Log::LogString("All Elements Empty");
		CurrentVertex = nullptr;
		CurrentShape = nullptr;
		CurrentShapeGroup = nullptr;
		CurrentPageItem = nullptr;
		CurrentPageGroup = nullptr;
		CurrentPage = nullptr;
	}
}

// POSITION
void PageCreator::PositionUp()
{
	EditorSelected->OffsetPosition({ 0.0, 0.00166 * PixelOffset }, OnlyY);
}
void PageCreator::PositionDown()
{
	EditorSelected->OffsetPosition({ 0.0, -0.00166 * PixelOffset }, OnlyY);
}
void PageCreator::PositionRight()
{
	EditorSelected->OffsetPosition({ 0.00166 * PixelOffset, 0.0 }, OnlyX);
}
void PageCreator::PositionLeft()
{
	EditorSelected->OffsetPosition({ -0.00166 * PixelOffset, 0.0 }, OnlyX);
}

//SIZE
void PageCreator::SizeDown()
{
	EditorSelected->OffsetSize({ 0.0, 0.00166 * PixelOffset }, OnlyY);
}
void PageCreator::SizeUp()
{
	EditorSelected->OffsetSize({ 0.0, 0.00166 * -PixelOffset }, OnlyY);
}
void PageCreator::SizeRight()
{
	EditorSelected->OffsetSize({ 0.00166 * PixelOffset, 0.0 }, OnlyX);
}
void PageCreator::SizeLeft()
{
	EditorSelected->OffsetSize({ 0.00166 * -PixelOffset, 0.0}, OnlyX);
}

// COLOR
void PageCreator::ColorRUp()
{
	EditorSelected->OffsetColor({ 0.01 * PixelOffset, 0.0, 0.0, 0.0 }, OnlyR);
}
void PageCreator::ColorRDown()
{
	EditorSelected->OffsetColor({ 0.01 * -PixelOffset, 0.0, 0.0, 0.0 }, OnlyR);
}

void PageCreator::ColorGUp()
{
	EditorSelected->OffsetColor({ 0.0, 0.01 * PixelOffset,  0.0, 0.0 }, OnlyG);
}

void PageCreator::ColorGDown()
{
	EditorSelected->OffsetColor({ 0.0, 0.01 * -PixelOffset,  0.0, 0.0 }, OnlyG);
}

void PageCreator::ColorBUp()
{
	EditorSelected->OffsetColor({ 0.0, 0.0, 0.01 * PixelOffset, 0.0 }, OnlyB);
}
void PageCreator::ColorBDown()
{
	EditorSelected->OffsetColor({ 0.0, 0.0, 0.01 * -PixelOffset,  0.0 }, OnlyB);
}

void PageCreator::ColorAUp()
{
	EditorSelected->OffsetColor({ 0.0, 0.0, 0.0, 0.01 * PixelOffset }, OnlyA);
}
void PageCreator::ColorADown()
{
	EditorSelected->OffsetColor({ 0.0, 0.0, 0.0, 0.01 * -PixelOffset }, OnlyA);
}

void PageCreator::SetText()
{
	string GetString = "";
	TextEditor.SetText(GetString);

}


void PageCreator::PointerTest()
{
	Log::LogString("Pointer Test is working");
}

