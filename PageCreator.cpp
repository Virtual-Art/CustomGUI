#include "PageCreator.h"

void PageCreator::llInit(llBookData* llBook, ShaderProgram* ShaderProgram, RawTexture* Texture0, RawTexture* Texture1, RawTexture* Texture2)
{
	TextData Text_Details;
	llShapeGroupData ShapeGroup_Details;

	CurrentBook = llBook;
	CurrentFunction = 9;

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
	ToggleEditor.llInit(CurrentBook);

	CreateFunctionContainer(); //Build "Creator" Function Table
	SetCreatorFunctions();     //Set Functions To Function Table
	SetKeyboardKeys();

	//BookEditor Setup
	BookCreatorPage.llInit(&CreatorBook, CurrentShader, Texture0, Texture1, Texture2);
	//Quad DeleteWhenFixed(&CreatorBook);
	//DeleteWhenFixed.SetllPosition({-2.0, 0.0});

	//Quad Quad_Find(CurrentBook);
	//Quad_Find.SetllPosition({-2.0, 0.0});

	//Text UniqueSlider(CurrentBook);
	//UniqueSlider.SetllPosition({0.5, 0.5});
	//Text UniqueSlider1(CurrentBook);
	//UniqueSlider1.SetllPosition({0.5, -0.5});
	PrinterToEdit = Empty;
	EditorSelected = &QuadEditor;

	CustomerDetails NewCustomer;
	CustomerDataBase.push_back(NewCustomer);

	/////////////////////////////////////ElementViewer////////////////////////////////////////

	llPageItemData PageItem_Data;

	//Required Groups
	NumberPrinterData NumberPrinter_Data;
	SliderData Slider_Data;
	Quad ElementViewerBackGround(&CreatorBook);
	ElementViewerBackGround.SetPosition({-0.8, 0.0});
	ElementViewerBackGround.SetSize({0.4, 1.8});
	ElementViewerBackGround.SetColor({ 0.0, 0.0, 0.0, 0.3 });

	Quad EditorSlider(&CreatorBook);
	EditorSlider.SetPosition({ 0.195, -0.95 });
	EditorSlider.SetSize({ 1.55, 0.075 });
	EditorSlider.SetColor({ 0.0, 0.0, 0.0, 0.5 });

	Quad EditorSlider_Slider(&CreatorBook);
	EditorSlider_Slider.SetPosition({ -0.195, -0.95 });
	EditorSlider_Slider.SetSize({ 0.76, 0.05 });
	EditorSlider_Slider.SetColor({ 0.091, 0.14, 0.14, 1.0 });

	//Element Position
	NumberPrinter_Data.Description = "Position";
	NumberPrinter_Data.Type = TYPE_VEC2;
	PageItem_Data.Position = { -0.98, 0.4 };
	PageItem_Data.Color = { 0.0, 0.5, 1.0, 1.0 };
	NumberPrinter_Element_Position.llInit(&CreatorBook, &PageItem_Data, NumberPrinter_Data);
	NumberPrinter_Element_Position.HighlightDescription(HighlightColor);

	//Element Size
	NumberPrinter_Data.Description = "Size    ";
	NumberPrinter_Data.Type = TYPE_VEC2;
	PageItem_Data.Position = { -0.98, 0.3 };
	NumberPrinter_Element_Size.llInit(&CreatorBook, &PageItem_Data, NumberPrinter_Data);
	NumberPrinter_Element_Size.HighlightDescription(HighlightColor);

	//NumberPrinter_Data.Description = "Name";
	//NumberPrinter_Data.Type = TYPE_STRING;
	//PageItem_Data.Position = { -0.98, -0.3 };
	//PageItem_Data.Color = { 0.0, 0.5, 1.0, 1.0 };
	//Number_Printer_String_Helper = "Name";
	//NumberPrinter_Data.String = &Number_Printer_String_Helper;
	//NumberPrinter_Name.llInit(&CreatorBook, &PageItem_Data, NumberPrinter_Data);


	//Red
	Slider_Data.Description = 'R';
	PageItem_Data.Position = { -0.835, 0.2 };
	PageItem_Data.Size = {0.2, 0.03};
	Slider_Color_R.llSliderInit(&CreatorBook, &PageItem_Data, Slider_Data);


	//Green
	Slider_Data.Description = 'G';
	PageItem_Data.Position = { -0.835, 0.1 };
	Slider_Color_G.llSliderInit(&CreatorBook, &PageItem_Data, Slider_Data);

	//Blue
	Slider_Data.Description = 'B';
	PageItem_Data.Position = { -0.835, 0.0 };
	Slider_Color_B.llSliderInit(&CreatorBook, &PageItem_Data, Slider_Data);

	//Alpha
	Slider_Data.Description = 'A';
	PageItem_Data.Position = { -0.835, -0.1 };
	Slider_Color_A.llSliderInit(&CreatorBook, &PageItem_Data, Slider_Data);

	ToggleData Toggle_Data;

	//Toggle Hide
	Toggle_Data.Description = "Hide";
	PageItem_Data.Position = { -0.93, -0.2 };
	Toggle_Hide.llToggleInit(&CreatorBook, &PageItem_Data, Toggle_Data);



	//////////////////////////////////////Instructions//////////////////////////////////////////////

	//Shift + up, down, right, left
	Text_Details.Phrase = "Press Shift + Up/Down or Left/Right To Switch levels or Neighbour Elements";
	Text_Details.Centered = true;
	ShapeGroup_Details.Position = { 0.0, 0.95 };
	ShapeGroup_Details.Color = Purple;
	//Text_Shift.llInit(&CreatorBook, &ShapeGroup_Details, Text_Details);

	//Alt + up, down, right, left
	Text_Details.Phrase = "Press Alt + Up/Down or Right/Left To Switch Options or Element Types";
	Text_Details.Centered = true;
	ShapeGroup_Details.Position = { 0.0, 0.85 };
	ShapeGroup_Details.Color = Orange;
	//Text_AltRightLeft.llInit(&CreatorBook, &ShapeGroup_Details, Text_Details);

	//Ctrl + A & up, down, right, left
	Text_Details.Phrase = "Press Ctrl + A to Add and Arrow Keys to use the Option Selected";
	Text_Details.Centered = true;
	ShapeGroup_Details.Position = { 0.0, 0.75 };
	ShapeGroup_Details.Color = Yellow;
	//Text_AltUpDown.llInit(&CreatorBook, &ShapeGroup_Details, Text_Details);

	////////////////////////////////////////////Current Level/////////////////////////////////////
	//Label
	Text_Details.Phrase = "Current Level: ";
	Text_Details.Centered = false;
	ShapeGroup_Details.Position = { -0.95, 0.8 };
	ShapeGroup_Details.Color = { 0.171, 0.8461 , 0.95 , 1.0};
	Text_CurrentLevel_Label.llInit(&CreatorBook, &ShapeGroup_Details, Text_Details);

	//Level
	Text_Details.Phrase = "Shape";
	ShapeGroup_Details.Position = { -0.95, 0.7 };
	ShapeGroup_Details.Color = White;
	Text_CurrentLevel.llInit(&CreatorBook, &ShapeGroup_Details, Text_Details);

	llShapeData* Shape_Slider;
	Button_R_Slider.LogicalActions[GUI_MOUSELEFT_CLICKED] = SetSliderR;
	Button_G_Slider.LogicalActions[GUI_MOUSELEFT_CLICKED] = SetSliderG;
	Button_B_Slider.LogicalActions[GUI_MOUSELEFT_CLICKED] = SetSliderB;
	Button_A_Slider.LogicalActions[GUI_MOUSELEFT_CLICKED] = SetSliderA;

	Button_R_Slider.LogicalActions[GUI_MOUSELEFT_PRESSED] = SetSliderR;
	Button_G_Slider.LogicalActions[GUI_MOUSELEFT_PRESSED] = SetSliderG;
	Button_B_Slider.LogicalActions[GUI_MOUSELEFT_PRESSED] = SetSliderB;
	Button_A_Slider.LogicalActions[GUI_MOUSELEFT_PRESSED] = SetSliderA;

	//Button_Name_NumberPrinter.LogicalActions[GUI_HOVERED] = SetFirstName;
	//
	//llShapeGroupData* ShapeGroup_Name;
	//
	//ShapeGroup_Name = NumberPrinter_Name.GetShapeGroup(GROUP_DESCRIPTION);
	//ShapeGroup_Name->ShapeGroupButton = &Button_Name_NumberPrinter;

	//Set Slider Quad Button to Change Slider Position
	Shape_Slider = Slider_Color_R.GetShapeGroupShape(GROUP_SLIDER, SLIDER);
	
	//Slider_Color_R.CurrentSliderData.WorkingFloat = &Quad_Slider_Test.GetData()->Color[0];
	Shape_Slider->ShapeButton = &Button_R_Slider;

	Shape_Slider = Slider_Color_G.GetShapeGroupShape(GROUP_SLIDER, SLIDER);
	//Slider_Color_G.CurrentSliderData.WorkingFloat = &Quad_Slider_Test.GetData()->Color[1];
	Shape_Slider->ShapeButton = &Button_G_Slider;

	Shape_Slider = Slider_Color_B.GetShapeGroupShape(GROUP_SLIDER, SLIDER);
	//Slider_Color_B.CurrentSliderData.WorkingFloat = &Quad_Slider_Test.GetData()->Color[2];
	Shape_Slider->ShapeButton = &Button_B_Slider;

	Shape_Slider = Slider_Color_A.GetShapeGroupShape(GROUP_SLIDER, SLIDER);
	//Slider_Color_A.CurrentSliderData.WorkingFloat = &Quad_Slider_Test.GetData()->Color[3];
	Shape_Slider->ShapeButton = &Button_A_Slider;

	llShapeData* Shape_Toggle;

	Shape_Toggle = Toggle_Hide.GetShapeGroupShape(GROUP_TOGGLE, TOGGLE_BACKGROUND);
	//Toggle_Hide.CurrentToggleData.OnOff = &Quad_Slider_Test.GetData()->Hide;
	//Shape_Toggle->ShapeButton.LogicalActions[2] = SetCurrentToggle;

	DropDownListData DropDown_Data_File;
	string* DropList = new string[7];
	DropList[0] = "New";
	DropList[1] = "Open            Ctrl + O";
	DropList[2] = "Close";
	DropList[3] = "Save";
	DropList[4] = "Save All";
	DropList[5] = "Recent Files";
	DropList[6] = "Exit             Ctrl + E";
	DropDown_Data_File.MaxListCount = 7;
	DropDown_Data_File.CurrentListCount = 7;
	DropDown_Data_File.StringList = DropList;
	DropDown_Data_File.Hidden = true;
	DropDown_Data_File.Description = "File";
	PageItem_Data.Position = { -0.96, 0.96 };
	File.llDropDownListInit(&CreatorBook, &PageItem_Data, DropDown_Data_File);

	DropDownListData DropDown_Data_Edit;
	string* DropList2 = new string[7];
	DropList2[0] = "Undo";
	DropList2[1] = "Redo";
	DropList2[2] = "Cut";
	DropList2[3] = "Copy";
	DropList2[4] = "Paste";
	DropList2[5] = "Duplicate";
	DropList2[6] = "Delete             ";
	DropDown_Data_Edit.MaxListCount = 7;
	DropDown_Data_Edit.CurrentListCount = 7;
	DropDown_Data_Edit.StringList = DropList2;
	DropDown_Data_Edit.Hidden = true;
	DropDown_Data_Edit.Description = "Edit";
	PageItem_Data.Position = { -0.90, 0.96};
	Edit.llDropDownListInit(&CreatorBook, &PageItem_Data, DropDown_Data_Edit);

	Log::LogString("----------------------------------------------------------");

	Button_File_Driver.LogicalActions[GUI_MOUSELEFT_CLICKED] = ProcessDropDownFile;
	Button_Edit_Driver.LogicalActions[GUI_MOUSELEFT_CLICKED] = ProcessDropDownEdit;


	llShapeData* Shape_DropDown;
	Shape_DropDown = File.GetShapeGroupShape(GROUP_BACKGROUND, 0);
	Shape_DropDown->ShapeButton = &Button_File_Driver;

	Shape_DropDown = Edit.GetShapeGroupShape(GROUP_BACKGROUND, 0);
	Shape_DropDown->ShapeButton = &Button_Edit_Driver;


	//BuildCustomerDetailElements();
	//AttachCustomerDetailButtons();
	//SetCustomerDetails(&DefaultCustomer);
}

void PageCreator::OnUpdate(KeyResult& KeyState, int MouseState)
{
	if (KeyState.Key1 == GUI_S_CLICKED && KeyState.Ctrl == true)
	{
		MasterElement::ToggleToggle(HideCreatorPage);
	}
	
	//if (HideCreatorPage == false)
	//{
	//	BookCreatorPage.DrawPage();
	//}

	//PageEditor.DrawPage();

	CurrentKeyResult = &KeyState;
	CurrentMouseState = MouseState;
	
	if (CurrentLevel == LEVEL_SHAPEGROUP && CurrentType == TYPE_TEXT && KeyState.Ctrl != true && KeyState.CurrentAscii != -1 && KeyState.Key1 != 0)
	{
		cout << "Editing Text" << endl;
		//CurrentText = TextEditor.GetText();
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
	
	PrinterToEdit();

	//MasterElement::FindElement(&CreatorBook, 2, CreatorDirectory);
	//MasterElement::FindElement(CurrentBook, CurrentLevel);
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
			CreatorFunction[Level][Type][FUNCTION_COLOR_R][ARROW_UP] = Empty;
			CreatorFunction[Level][Type][FUNCTION_COLOR_R][ARROW_DOWN] = Empty;
			CreatorFunction[Level][Type][FUNCTION_COLOR_R][ARROW_RIGHT] = ColorRUp;
			CreatorFunction[Level][Type][FUNCTION_COLOR_R][ARROW_LEFT]  = ColorRDown;

			//G
			CreatorFunction[Level][Type][FUNCTION_COLOR_G][ARROW_UP] = Empty;
			CreatorFunction[Level][Type][FUNCTION_COLOR_G][ARROW_DOWN] = Empty;
			CreatorFunction[Level][Type][FUNCTION_COLOR_G][ARROW_RIGHT] = ColorGUp;
			CreatorFunction[Level][Type][FUNCTION_COLOR_G][ARROW_LEFT] = ColorGDown;

			//B
			CreatorFunction[Level][Type][FUNCTION_COLOR_B][ARROW_UP] = Empty;
			CreatorFunction[Level][Type][FUNCTION_COLOR_B][ARROW_DOWN] = Empty;
			CreatorFunction[Level][Type][FUNCTION_COLOR_B][ARROW_RIGHT] = ColorBUp;
			CreatorFunction[Level][Type][FUNCTION_COLOR_B][ARROW_LEFT] = ColorBDown;

			//A
			CreatorFunction[Level][Type][FUNCTION_COLOR_A][ARROW_UP] = Empty;
			CreatorFunction[Level][Type][FUNCTION_COLOR_A][ARROW_DOWN] = Empty;
			CreatorFunction[Level][Type][FUNCTION_COLOR_A][ARROW_RIGHT] = ColorAUp;
			CreatorFunction[Level][Type][FUNCTION_COLOR_A][ARROW_LEFT] = ColorADown;
		}
	}
}

void PageCreator::SetArrowKeys()
{
	//A value of type blah cannot be initialized to type blah
	Keyboard::GetKeyButton()[GUI_UP_CLICKED][WITH_DEFAULT]   = ArrowKeyUp;
	Keyboard::GetKeyButton()[GUI_DOWN_CLICKED][WITH_DEFAULT] = ArrowKeyDown;
    Keyboard::GetKeyButton()[GUI_RIGHT_CLICKED][WITH_DEFAULT] = ArrowKeyRight;
	Keyboard::GetKeyButton()[GUI_LEFT_CLICKED][WITH_DEFAULT]  = ArrowKeyLeft;
			  			  
	Keyboard::GetKeyButton()[GUI_UP_PRESSED][WITH_DEFAULT]    = ArrowKeyUp;
	Keyboard::GetKeyButton()[GUI_DOWN_PRESSED][WITH_DEFAULT]  = ArrowKeyDown;
	Keyboard::GetKeyButton()[GUI_RIGHT_PRESSED][WITH_DEFAULT] = ArrowKeyRight;
	Keyboard::GetKeyButton()[GUI_LEFT_PRESSED][WITH_DEFAULT]  = ArrowKeyLeft;
	// CreatorFunction[CurrentLevel][CurrentFunction][ARROW_UP];

	//50 - 101

	//Should actually almost every default key and + caps + shft
	for (int CharKey = 50; CharKey < 102; CharKey++)
	{
		Keyboard::GetKeyButton()[CharKey][WITH_DEFAULT] = AddLetter;
	}

	//Keyboard::GetKeyButton()[GUI_BACKSPACE_PRESSED][WITH_DEFAULT] = BackSpace;
}

void PageCreator::AddLetter()
{
	//if (CurrentKeyResult->CurrentAscii != -1 && CurrentKeyResult->Key1 != 0)
	//{
	//	CurrentText += CurrentKeyResult->CurrentAscii;
	//}
}

void PageCreator::BackSpace()
{
	Log::LogString("Backspace function");
	CurrentText.erase(CurrentText.size() - 1);
}

//Play Creator Function when Clicked/Pressed
void PageCreator::ArrowKeyUp()
{
	Log::LogString("Arrow Key Up");
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
	Keyboard::GetKeyButton()[GUI_UP_CLICKED][WITH_SHIFT] = LevelUp;
	Keyboard::GetKeyButton()[GUI_DOWN_CLICKED][WITH_SHIFT] = LevelDown;
	Keyboard::GetKeyButton()[GUI_RIGHT_CLICKED][WITH_SHIFT] = DataRight;
	Keyboard::GetKeyButton()[GUI_LEFT_CLICKED][WITH_SHIFT] = DataLeft;
}

void PageCreator::OptionsUp()
{
	if (CurrentFunction < MaxFunction)
	{
		CurrentFunction++;
	}
	if (CurrentFunction == 9)
	{
		//Text_CurrentFunction.SetllText("Position");
		NumberPrinter_Element_Position.HighlightDescription(HighlightColor); //
		NumberPrinter_Element_Size.HighlightDescriptionOff();
	}
	if (CurrentFunction == 8)
	{
		//Text_CurrentFunction.SetllText("Size");
		NumberPrinter_Element_Size.HighlightDescription(HighlightColor); //
		Slider_Color_R.SetDescriptionColor(DescriptionColor);
	}
	if (CurrentFunction == 7)
	{
		//Text_CurrentFunction.SetllText("R Color");
		Slider_Color_R.SetDescriptionColor(HighlightColor); //
		Slider_Color_G.SetDescriptionColor(DescriptionColor);
	}
	if (CurrentFunction == 6)
	{
		//Text_CurrentFunction.SetllText("G Color");
		Slider_Color_G.SetDescriptionColor(HighlightColor); //
		Slider_Color_B.SetDescriptionColor(DescriptionColor);
	}
	if (CurrentFunction == 5)
	{
		//Text_CurrentFunction.SetllText("B Color");
		Slider_Color_B.SetDescriptionColor(HighlightColor); //
		Slider_Color_A.SetDescriptionColor(DescriptionColor);
	}
	if (CurrentFunction == 4)
	{
		//Text_CurrentFunction.SetllText("A Color");
		Slider_Color_A.SetDescriptionColor(HighlightColor); //
	}
	if (CurrentFunction == 3)
	{
		//Text_CurrentFunction.SetllText("Function Not Set");
	}
	if (CurrentFunction == 2)
	{
		//Text_CurrentFunction.SetllText("Function Not Set");
	}
	if (CurrentFunction == 1)
	{
		//Text_CurrentFunction.SetllText("Function Not Set");
	}
	if (CurrentFunction == 0)
	{
		//Text_CurrentFunction.SetllText("Function Not Set");
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
	if (CurrentFunction == 9)
	{
		//Text_CurrentFunction.SetllText("Position");
		NumberPrinter_Element_Position.HighlightDescription(HighlightColor); //
	}
	if (CurrentFunction == 8)
	{
		//Text_CurrentFunction.SetllText("Size");
		NumberPrinter_Element_Position.HighlightDescription(DescriptionColor);
		NumberPrinter_Element_Size.HighlightDescriptionOff(); //
	}
	if (CurrentFunction == 7)
	{
		//Text_CurrentFunction.SetllText("R Color");
		NumberPrinter_Element_Size.HighlightDescription(DescriptionColor);
		Slider_Color_R.SetDescriptionColor(HighlightColor); //
	}
	if (CurrentFunction == 6)
	{
		//Text_CurrentFunction.SetllText("G Color");
		Slider_Color_R.SetDescriptionColor(DescriptionColor);
		Slider_Color_G.SetDescriptionColor(HighlightColor); //
	}
	if (CurrentFunction == 5)
	{
		//Text_CurrentFunction.SetllText("B Color");
		Slider_Color_G.SetDescriptionColor(DescriptionColor);
		Slider_Color_B.SetDescriptionColor(HighlightColor); //
	}
	if (CurrentFunction == 4)
	{
		//Text_CurrentFunction.SetllText("A Color");
		Slider_Color_B.SetDescriptionColor(DescriptionColor);
		Slider_Color_A.SetDescriptionColor(HighlightColor); //
	}
	if (CurrentFunction == 3)
	{
		//Text_CurrentFunction.SetllText("Function Not Set");
	}
	if (CurrentFunction == 2)
	{
		//Text_CurrentFunction.SetllText("Function Not Set");
	}
	if (CurrentFunction == 1)
	{
		//Text_CurrentFunction.SetllText("Function Not Set");
	}
	if (CurrentFunction == 0)
	{
		//Text_CurrentFunction.SetllText("Function Not Set");
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
	CurrentFunction = 9;

	switch (CurrentLevel)
	{
	case LEVEL_VERTEX:
		//Element_Selected = &Vertex_Selected;
		break;
	case LEVEL_SHAPE:
		
		MasterElement::NextShape(CurrentBook);
		SetElements();
		if (CurrentShape != nullptr) { CurrentType = CurrentShape->Type; }
		SetShapeType();
		break;

	case LEVEL_SHAPEGROUP:
		MasterElement::NextShapeGroup(CurrentBook);
		SetElements();
		if (CurrentShapeGroup != nullptr) { CurrentType = CurrentShapeGroup->Type; }
		SetShapeGroupType();
		break;

	case LEVEL_PAGEITEM:
		MasterElement::NextPageItem(CurrentBook);
		SetElements();
		if (CurrentPageItem != nullptr) { CurrentType = CurrentPageItem->Type; }
		SetPageItemType();
	    break;

	case LEVEL_PAGEGROUP:
		MasterElement::NextPageGroup(CurrentBook);
		SetElements();
		if (CurrentPageGroup != nullptr) { CurrentType = CurrentPageGroup->Type; }
		SetPageGroupType();
		break;

	case LEVEL_PAGE:
		MasterElement::NextPage(CurrentBook);
		SetElements();
		SetPageType();
		break;
	}
}

void PageCreator::DataLeft()
{
	Log::LogString("Data Left");
	//We don't know how many functions each level has, however each level has one function, so set it to the first
	CurrentFunction = 9;

	switch (CurrentLevel)
	{
	case LEVEL_VERTEX:
		//Element_Selected = &Vertex_Selected;
		break;
	case LEVEL_SHAPE:
		MasterElement::PreviousShape(CurrentBook);
		if (CurrentShape != nullptr) { CurrentType = CurrentShape->Type; }
		SetElements();
		SetShapeType();
		break;

	case LEVEL_SHAPEGROUP:
		MasterElement::PreviousShapeGroup(CurrentBook);
		SetElements();
		if (CurrentShapeGroup != nullptr) { CurrentType = CurrentShapeGroup->Type; }
		SetShapeGroupType();
		break;

	case LEVEL_PAGEITEM:
		MasterElement::PreviousPageItem(CurrentBook);
		SetElements();
		if (CurrentPageItem != nullptr) { CurrentType = CurrentPageItem->Type; }
		SetPageItemType();
		break;

	case LEVEL_PAGEGROUP:

		MasterElement::PreviousPageGroup(CurrentBook);
		SetElements();
		if (CurrentPageGroup != nullptr) { CurrentType = CurrentPageGroup->Type; }
		SetPageGroupType();
		break;

	case LEVEL_PAGE:

		MasterElement::PreviousPage(CurrentBook);
		SetPageType();
		break;
	}
}

void PageCreator::SetShapeType()
{
	//Set Type Based on Shape
	switch (CurrentType)
	{
	case TYPE_SHAPE:
		EditorSelected = &ShapeEditor;
		ShapeEditor.HighlightOff();
		ShapeEditor.llSwitch(CurrentShape);
		ShapeEditor.HighlightShape(ShapeHighlightColor);
		Text_CurrentLevel.SetllText("Shape");
		break;

	case TYPE_SHAPE_QUAD:
		EditorSelected = &QuadEditor;
		SetElements();
		QuadEditor.HighlightOff();
		QuadEditor.llSwitch(CurrentShape);
		QuadEditor.HighlightShape(ShapeHighlightColor);
		Text_CurrentLevel.SetllText("Quad");
		break;

	case TYPE_SHAPE_CHARACTER:
		EditorSelected = &CharacterEditor;
		SetElements();
		CharacterEditor.HighlightOff();
		CharacterEditor.llSwitch(CurrentShape);
		CharacterEditor.HighlightShape(ShapeHighlightColor);
		Text_CurrentLevel.SetllText("Character");
		break;
	}
	MasterElement::CurrentDirectory(CurrentBook);
	//UpdateColorSliders();
}

void PageCreator::PrintCreatorStats()
{
	Log::LogInt("CurrentLevel", CurrentLevel);
	Log::LogInt("CurrentFunction", CurrentFunction);
	Log::LogInt("CurrentType", CurrentType);
}

void PageCreator::SetShapeGroupType()
{
	switch (CurrentType)
	{
	case TYPE_SHAPEGROUP:
		EditorSelected = &ShapeGroupEditor;
		ShapeGroupEditor.HighlightOff();
		ShapeGroupEditor.llSwitch(CurrentShapeGroup);
		ShapeGroupEditor.HighlightShapeGroup(ShapeGroupHighlightColor);
		Text_CurrentLevel.SetllText("ShapeGroup");
		break;
	case TYPE_SHAPEGROUP_TEXT:
		EditorSelected = &TextEditor;
		TextEditor.HighlightOff();
		TextEditor.llSwitch(CurrentShapeGroup);
		TextEditor.HighlightShapeGroup(ShapeGroupHighlightColor);
		Text_CurrentLevel.SetllText("Text");
		break;
	}
	MasterElement::CurrentDirectory(CurrentBook);
	//UpdateColorSliders();
}

void PageCreator::SetPageItemType()
{
	Log::LogString("Inside Page Item type");
	switch (CurrentType)
	{
	case TYPE_PAGEITEM:
		EditorSelected = &PageItemEditor;
		SetElements();
		Log::LogString("in Page Item");
		PageItemEditor.HighlightOff();
		PageItemEditor.llSwitch(CurrentPageItem);
		PageItemEditor.HighlightPageItem(PageItemHighlightColor);
		Text_CurrentLevel.SetllText("PageItem");
		break;
	case TYPE_PAGEITEM_SLIDER:
		EditorSelected = &SliderEditor;
		SetElements();
		Log::LogString("in Slider");
		SliderEditor.HighlightOff();
		SliderEditor.llSwitch(CurrentPageItem);
		SliderEditor.HighlightPageItem(PageItemHighlightColor);
		Text_CurrentLevel.SetllText("Slider");
		break;
	}
	MasterElement::CurrentDirectory(CurrentBook);
	//UpdateColorSliders();
}

void PageCreator::SetPageGroupType()
{
	switch (CurrentType)
	{
	case TYPE_PAGEGROUP:
		EditorSelected = &PageGroupEditor;
		SetElements();
		PageGroupEditor.HighlightOff();
		PageGroupEditor.llSwitch(CurrentPageGroup);
		PageGroupEditor.HighlightPageGroup(PageGroupHighlightColor);
		Text_CurrentLevel.SetllText("PageGroup");
		break;
	}
	MasterElement::CurrentDirectory(CurrentBook);
	//UpdateColorSliders();
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
	MasterElement::CurrentDirectory(CurrentBook);
	//UpdateColorSliders();
}

//Arrow Key with Alt
void PageCreator::SetAlternate()
{
	Keyboard::GetKeyButton()[GUI_UP_CLICKED][WITH_ALT] = OptionsUp;
	Keyboard::GetKeyButton()[GUI_DOWN_CLICKED][WITH_ALT] = OptionsDown;
	Keyboard::GetKeyButton()[GUI_RIGHT_CLICKED][WITH_ALT] = TypeRight;
	Keyboard::GetKeyButton()[GUI_LEFT_CLICKED][WITH_ALT] = TypeLeft;
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
		SetElements();
		if (CurrentShape != nullptr) { CurrentType = CurrentShape->Type; }
		Text_CurrentLevel.SetllText("Shape");
		SetShapeType();
		break;
	case LEVEL_SHAPEGROUP:
		EditorSelected = &ShapeGroupEditor; //Supposed to set type here, won't always be basic type
		SetElements();
		if (CurrentShapeGroup != nullptr)
		{
			CurrentType = CurrentShapeGroup->Type;
		}
		Text_CurrentLevel.SetllText("ShapeGroup");
		SetShapeGroupType();
		break;
	case LEVEL_PAGEITEM:
		EditorSelected = &PageItemEditor; //Supposed to set type here, won't always be basic type
		SetElements();
		if (CurrentShapeGroup != nullptr)
		{
			CurrentType = CurrentPageItem->Type;
		}
		Text_CurrentLevel.SetllText("PageItem");
		SetPageItemType();
		break;
	case LEVEL_PAGEGROUP:
		//CurrentPageGroup = CurrentBook->Page->PageGroup;
		//PageGroupSelected.llSwitch(CurrentPageGroup);
		//CurrentType = CurrentPageGroup->Type;
		SetElements();
		EditorSelected = &PageGroupEditor; //Supposed to set type here, won't always be basic type
		Text_CurrentLevel.SetllText("PageGroup");
		SetPageGroupType();
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
		SetElements();
		if (CurrentShape != nullptr)
		{
			CurrentType = CurrentShape->Type;
		}
		Text_CurrentLevel.SetllText("Shape");
		SetShapeType();
		break;
	case LEVEL_SHAPEGROUP:
		EditorSelected = &ShapeGroupEditor;
		SetElements();
		if (CurrentShapeGroup != nullptr)
		{
			CurrentType = CurrentShapeGroup->Type;
		}
		SetShapeGroupType();
		Text_CurrentLevel.SetllText("ShapeGroup");
		break;
	case LEVEL_PAGEITEM:
		EditorSelected = &PageItemEditor;
		SetElements();
		if (CurrentPageItem != nullptr)
		{
			CurrentType = CurrentPageItem->Type;
		}
		Text_CurrentLevel.SetllText("PageItem");
		SetPageItemType();
		break;
	case LEVEL_PAGEGROUP:
		EditorSelected = &PageGroupEditor;
		SetElements();
		Text_CurrentLevel.SetllText("PageGroup");
		SetPageGroupType();
		break;
	case LEVEL_PAGE:
		//Element_Selected = &PageSelected;
		Text_CurrentLevel.SetllText("Page");
		break;
	}
}




void PageCreator::Add()
{
	//SetBookFromElements();
	EditorSelected->Add_Default();
	//CurrentFunction = 9;
	//SetElements();
	//UpdateColorSliders();
}

void PageCreator::Duplicate()
{
	SetBookFromElements();
	EditorSelected->Add_Duplicate();
	//CurrentFunction = 9;
	SetElements();
	//UpdateColorSliders();
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
	SetElements();
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

void PageCreator::SetKeyAdd() { Keyboard::GetKeyButton()[GUI_A_CLICKED][WITH_CTRL] = Add; }
void PageCreator::SetInsertKey() { Keyboard::GetKeyButton()[GUI_INSERT_CLICKED][WITH_DEFAULT] = Insert; }
void PageCreator::SetEraseKey() { Keyboard::GetKeyButton()[GUI_E_CLICKED][WITH_CTRL] = ErasePage; }
void PageCreator::SetSaveKey() { Keyboard::GetKeyButton()[GUI_S_CLICKED][WITH_CTRL] = SavePage; }
void PageCreator::SetKeyDuplicate() { Keyboard::GetKeyButton()[GUI_D_CLICKED][WITH_CTRL] = Duplicate; }
void PageCreator::SetDeleteKey() { Keyboard::GetKeyButton()[GUI_DELETE_CLICKED][WITH_DEFAULT] = Delete; }
//void PageCreator::SetKeyNext() { Keyboard::KeyButton[GUI_RIGHT_CLICKED][WITH_CTRL] = Next; }
//void PageCreator::SetKeyPrevious() { Keyboard::KeyButton[GUI_LEFT_CLICKED][WITH_CTRL] = Previous; }


void PageCreator::SetPixelOffsetKeys()
{
	Keyboard::GetKeyButton()[GUI_F1_CLICKED][WITH_DEFAULT] = IncreasePixelOffset;
	Keyboard::GetKeyButton()[GUI_F2_CLICKED][WITH_DEFAULT] = DecreasePixelOffset;
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


	MasterElement::CurrentDirectory(CurrentBook);
}

void PageCreator::SetElements()
{
	Log::LogString("Setting Elements");
	//Page
	if (CurrentBook->Page != nullptr)
	{
		CurrentPage = CurrentBook->Page;

		//PageGroup
		if (CurrentBook->Page->PageGroup != nullptr)
		{
			CurrentPageGroup = CurrentBook->Page->PageGroup;

			//PageItem
			if (CurrentBook->Page->PageGroup->PageItem != nullptr)
			{
				CurrentPageItem = CurrentBook->Page->PageGroup->PageItem;
			
				//ShapeGroup
				if (CurrentBook->Page->PageGroup->PageItem->ShapeGroup != nullptr)
				{
					CurrentShapeGroup = CurrentBook->Page->PageGroup->PageItem->ShapeGroup;

					//Shape
					if (CurrentBook->Page->PageGroup->PageItem->ShapeGroup->Shape != nullptr)
					{
						CurrentShape = CurrentBook->Page->PageGroup->PageItem->ShapeGroup->Shape;
							CurrentShape = CurrentShape->Next;

						//Vertex
						if (CurrentBook->Page->PageGroup->PageItem->ShapeGroup->Shape->Vertexx != nullptr)
						{
							CurrentVertex = CurrentBook->Page->PageGroup->PageItem->ShapeGroup->Shape->Vertexx;
						}
						else
						{
							CurrentVertex = nullptr;
						}
					}
					else
					{
						CurrentVertex = nullptr;
						CurrentShape = nullptr;
					}
				}
				else
				{
					CurrentVertex = nullptr;
					CurrentShape = nullptr;
					CurrentShapeGroup = nullptr;
				}
			}
			else
			{
				CurrentVertex = nullptr;
				CurrentShape = nullptr;
				CurrentShapeGroup = nullptr;
				CurrentPageItem = nullptr;
			}
		}
		else
		{
			CurrentVertex = nullptr;
			CurrentShape = nullptr;
			CurrentShapeGroup = nullptr;
			CurrentPageItem = nullptr;
			CurrentPageGroup = nullptr;
		}
	}
	else
	{
		CurrentVertex = nullptr;
		CurrentShape = nullptr;
		CurrentShapeGroup = nullptr;
		CurrentPageItem = nullptr;
		CurrentPageGroup = nullptr;
		CurrentPage = nullptr;
	}

	MasterElement::CurrentDirectory(CurrentBook);
}

void PageCreator::ResetElements()
{
	CurrentVertex = nullptr;
	CurrentShape = nullptr;
	CurrentShapeGroup = nullptr;
	CurrentPageItem = nullptr;
	CurrentPageGroup = nullptr;
	CurrentPage = nullptr;
}

// POSITION
void PageCreator::PositionUp()
{
	Log::LogString("position up");
	EditorSelected->OffsetPosition({ 0.0, 0.00166 * PixelOffset }, OnlyY);
	//UpdateColorSliders();
}
void PageCreator::PositionDown()
{
	EditorSelected->OffsetPosition({ 0.0, -0.00166 * PixelOffset }, OnlyY);
	//UpdateColorSliders();
}
void PageCreator::PositionRight()
{
	EditorSelected->OffsetPosition({ 0.00166 * PixelOffset, 0.0 }, OnlyX);
	//UpdateColorSliders();
}
void PageCreator::PositionLeft()
{
	EditorSelected->OffsetPosition({ -0.00166 * PixelOffset, 0.0 }, OnlyX);
	//UpdateColorSliders();
}

//SIZE
void PageCreator::SizeDown()
{
	EditorSelected->OffsetSize({ 0.0, 0.00166 * PixelOffset }, OnlyY);
	//UpdateColorSliders();
}
void PageCreator::SizeUp()
{
	EditorSelected->OffsetSize({ 0.0, 0.00166 * -PixelOffset }, OnlyY);
	//UpdateColorSliders();
}
void PageCreator::SizeRight()
{
	EditorSelected->OffsetSize({ 0.00166 * PixelOffset, 0.0 }, OnlyX);
	//UpdateColorSliders();
}
void PageCreator::SizeLeft()
{
	EditorSelected->OffsetSize({ 0.00166 * -PixelOffset, 0.0}, OnlyX);
	//UpdateColorSliders();
}

// COLOR
void PageCreator::ColorRUp()
{
	EditorSelected->OffsetColor({ 0.005 * PixelOffset, 0.0, 0.0, 0.0 }, OnlyR);
	//UpdateSliderR();
}
void PageCreator::ColorRDown()
{
	EditorSelected->OffsetColor({ 0.005 * -PixelOffset, 0.0, 0.0, 0.0 }, OnlyR);
	//UpdateSliderR();
}

void PageCreator::ColorGUp()
{
	EditorSelected->OffsetColor({ 0.0, 0.005 * PixelOffset,  0.0, 0.0 }, OnlyG);
	//UpdateSliderG();
}

void PageCreator::ColorGDown()
{
	EditorSelected->OffsetColor({ 0.0, 0.005 * -PixelOffset,  0.0, 0.0 }, OnlyG);
	//UpdateSliderG();
}

void PageCreator::ColorBUp()
{
	EditorSelected->OffsetColor({ 0.0, 0.0, 0.005 * PixelOffset, 0.0 }, OnlyB);
	//UpdateSliderB();
}
void PageCreator::ColorBDown()
{
	EditorSelected->OffsetColor({ 0.0, 0.0, 0.005 * -PixelOffset,  0.0 }, OnlyB);
	//UpdateSliderB();
}

void PageCreator::ColorAUp()
{
	EditorSelected->OffsetColor({ 0.0, 0.0, 0.0, 0.005 * PixelOffset }, OnlyA);
	//UpdateSliderA();
}
void PageCreator::ColorADown()
{
	EditorSelected->OffsetColor({ 0.0, 0.0, 0.0, 0.005 * -PixelOffset }, OnlyA);
	//UpdateSliderA();
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

void PageCreator::UpdateColorSliders()
{
	switch (CurrentLevel)
	{
	case LEVEL_VERTEX:

		break;

	case LEVEL_SHAPE:
		Log::LogString("Level Shape");
		NumberPrinter_Element_Position.CurrentNumberPrinter.VEC2 = &CurrentShape->Position;
		NumberPrinter_Element_Size.CurrentNumberPrinter.VEC2 = &CurrentShape->Size;
		Slider_Color_R.CurrentSliderData.WorkingFloat = &CurrentShape->Color[0];
		Slider_Color_G.CurrentSliderData.WorkingFloat = &CurrentShape->Color[1];
		Slider_Color_B.CurrentSliderData.WorkingFloat = &CurrentShape->Color[2];
		Slider_Color_A.CurrentSliderData.WorkingFloat = &CurrentShape->Color[3];
		break;

	case LEVEL_SHAPEGROUP:
		NumberPrinter_Element_Position.CurrentNumberPrinter.VEC2 = &CurrentShapeGroup->Position;
		NumberPrinter_Element_Size.CurrentNumberPrinter.VEC2 = &CurrentShapeGroup->Size;
		Slider_Color_R.CurrentSliderData.WorkingFloat = &CurrentShapeGroup->Color[0];
		Slider_Color_G.CurrentSliderData.WorkingFloat = &CurrentShapeGroup->Color[1];
		Slider_Color_B.CurrentSliderData.WorkingFloat = &CurrentShapeGroup->Color[2];
		Slider_Color_A.CurrentSliderData.WorkingFloat = &CurrentShapeGroup->Color[3];
		break;

	case LEVEL_PAGEITEM:
		Slider_Color_R.CurrentSliderData.WorkingFloat = &CurrentPageItem->Color[0];
		Slider_Color_G.CurrentSliderData.WorkingFloat = &CurrentPageItem->Color[1];
		Slider_Color_B.CurrentSliderData.WorkingFloat = &CurrentPageItem->Color[2];
		Slider_Color_A.CurrentSliderData.WorkingFloat = &CurrentPageItem->Color[3];
		break;

	case LEVEL_PAGEGROUP:
		Slider_Color_R.CurrentSliderData.WorkingFloat = &CurrentPageGroup->Color[0];
		Slider_Color_G.CurrentSliderData.WorkingFloat = &CurrentPageGroup->Color[1];
		Slider_Color_B.CurrentSliderData.WorkingFloat = &CurrentPageGroup->Color[2];
		Slider_Color_A.CurrentSliderData.WorkingFloat = &CurrentPageGroup->Color[3];
		break;
	}

	cout << "SHAPE CONNECTED TO SLIDERS: " << CurrentShape << endl;

	UpdateSliderR();
	UpdateSliderG();
	UpdateSliderB();
	UpdateSliderA();
	NumberPrinter_Element_Position.llUpdate();
	NumberPrinter_Element_Size.llUpdate();
}

/////////////Set//////////////////////

void PageCreator::SetSliderR()
{
	Slider_Color_R.SetSlider();
	EditorSelected->llUpdate();
}

void PageCreator::SetSliderG()
{
	Slider_Color_G.SetSlider();
	EditorSelected->llUpdate();
}

void PageCreator::SetSliderB()
{
	Slider_Color_B.SetSlider();
	EditorSelected->llUpdate();
}

void PageCreator::SetSliderA()
{
	Slider_Color_A.SetSlider();
	EditorSelected->llUpdate();
}

void PageCreator::ResetKeyboardText()
{
	CurrentText = "";
}

void PageCreator::ResetSearch()
{
	SearchBar_Customer_Search.ResetSearchBar();
}

void PageCreator::ResetCustomerDetails()
{
	//Reset 
	Printer_First_Name.SetString("First Name");
	Printer_Last_Name.SetString("Last Name");
	Printer_Phone.SetString("Phone #");
	Printer_Address.SetString("Address");
	Printer_Email.SetString("Email");
}

//Reset any blank spaces to default string
void PageCreator::SetCustomerDetailDefaults()
{
	//Reset First Name
	if (Printer_First_Name.GetCurrentString() == " ")
	{
		Printer_First_Name.SetString("First Name");
	}

	if (Printer_Last_Name.GetCurrentString() == " ")
	{
		Printer_Last_Name.SetString("Last Name");
	}

	if (Printer_Phone.GetCurrentString() == " ")
	{
		Printer_Phone.SetString("Phone #");
	}

	if (Printer_Address.GetCurrentString() == " ")
	{
		Printer_Address.SetString("Address");
	}

	if (Printer_Email.GetCurrentString() == " ")
	{
		Printer_Email.SetString("Email");
	}

}

void PageCreator::ResetCustomerDetailHighlights()
{
	Printer_First_Name.HighlightDescriptionOff();
	Printer_Last_Name.HighlightDescriptionOff();
	Printer_Phone.HighlightDescriptionOff();
	Printer_Address.HighlightDescriptionOff();
	Printer_Email.HighlightDescriptionOff();
}

void PageCreator::SwitchStringPrinter()
{
	CreatorNumberPrinterSelected.llSwitch(CreatorDirectory.PageItem);
}

void PageCreator::SetCustomerSearch()
{
	PrinterToEdit = ProcessCustomerSearch;
	//SetCustomerDetailDefaults();
	CurrentText = " ";
	string Search = CurrentText;

	//Keep Valid State
	if (CurrentText == "") { Search = " "; }

	if (CurrentText == SearchBar_Customer_Search.CurrentSearchBar.SearchString)
	{
		Search = " "; CurrentText = " ";
	}

	SearchBar_Customer_Search.SetSearch(Search);
}

void PageCreator::SetFirstName()
{
	PrinterToEdit = ProcessFirstName;
	SetCustomerDetailDefaults();
	ResetSearch();
	CurrentText = Printer_First_Name.GetCurrentString();
	string FirstName = CurrentText;

	//Keep Valid State
	if (CurrentText == "") {FirstName = " ";}

	if (CurrentText == Printer_First_Name.CurrentNumberPrinter.Description)
	{FirstName = " "; CurrentText = " ";}

	//Set the string to the current printer
	ResetCustomerDetailHighlights();
	Printer_First_Name.HighlightDescription(CustomerInfoHighlightColor);
	Printer_First_Name.SetString(FirstName);
}

void PageCreator::SetLastName()
{
	PrinterToEdit = ProcessLastName;
	SetCustomerDetailDefaults();
	ResetSearch();
	CurrentText = Printer_Last_Name.GetCurrentString();
	string LastName = CurrentText;
	if (CurrentText == "")
	{
		LastName = " ";
	}

	if (CurrentText == Printer_Last_Name.CurrentNumberPrinter.Description)
	{
		LastName = " ";
		CurrentText = " ";
	}

	//Set the string to the current printer
	ResetCustomerDetailHighlights();
	Printer_Last_Name.HighlightDescription(CustomerInfoHighlightColor);
	Printer_Last_Name.SetString(LastName);
}

void PageCreator::SetPhone()
{
	PrinterToEdit = ProcessPhone;
	SetCustomerDetailDefaults();
	ResetSearch();
	CurrentText = Printer_Phone.GetCurrentString();
	string Phone = CurrentText;
	if (CurrentText == "")
	{
		Phone = " ";
	}

	if (CurrentText == Printer_Phone.CurrentNumberPrinter.Description)
	{
		Phone = " ";
		CurrentText = " ";
	}

	//Set the string to the current printer
	ResetCustomerDetailHighlights();
	Printer_Phone.HighlightDescription(CustomerInfoHighlightColor);
	Printer_Phone.SetString(Phone);
}

void PageCreator::SetAddress()
{
	PrinterToEdit = ProcessAddress;
	SetCustomerDetailDefaults();
	ResetSearch();
	CurrentText = Printer_Address.GetCurrentString();
	string Address = CurrentText;
	if (CurrentText == "")
	{
		Address = " ";
	}

	if (CurrentText == Printer_Address.CurrentNumberPrinter.Description)
	{
		Address = " ";
		CurrentText = " ";
	}

	//Set the string to the current printer
	ResetCustomerDetailHighlights();
	Printer_Address.HighlightDescription(CustomerInfoHighlightColor);
	Printer_Address.SetString(Address);
}

void PageCreator::SetEmail()
{
	PrinterToEdit = ProcessEmail;
	SetCustomerDetailDefaults();
	ResetSearch();
	CurrentText = Printer_Email.GetCurrentString();
	string Email = CurrentText;
	if (CurrentText == "")
	{
		Email = " ";
	}

	if (CurrentText == Printer_Email.CurrentNumberPrinter.Description)
	{
		Email = " ";
		CurrentText = " ";
	}

	//Set the string to the current printer
	ResetCustomerDetailHighlights();
	Printer_Email.HighlightDescription(CustomerInfoHighlightColor);
	Printer_Email.SetString(CurrentText);
}


void PageCreator::AddCustomer()
{
	if (DefaultCustomer.FirstName !=  "First Name")
	{
		map_CustomerDataBase[DefaultCustomer.FirstName] = DefaultCustomer;
	}

	PrinterToEdit = Empty;
	ResetCustomerDetails();
	ResetCustomerDetailHighlights();
}

void PageCreator::ProcessCustomerSearch()
{
	//Never Allow Text to go to zero
	if (CurrentText == "")
	{
		CurrentText = " ";
	}

	WordSearch(CurrentText);
}

void PageCreator::ProcessFirstName()
{
	//Never Allow Text to go to zero
	if (CurrentText == "")
	{
		CurrentText = " ";
	}

	Printer_First_Name.SetString(CurrentText);
}

void PageCreator::ProcessLastName()
{
	//Never Allow Text to go to zero
	if (CurrentText == "")
	{
		CurrentText = " ";
	}

	Printer_Last_Name.SetString(CurrentText);
}

void PageCreator::ProcessPhone()
{
	//Never Allow Text to go to zero
	if (CurrentText == "")
	{
		CurrentText = " ";
	}

	Printer_Phone.SetString(CurrentText);
}

void PageCreator::ProcessAddress()
{
	//Never Allow Text to go to zero
	if (CurrentText == "")
	{
		CurrentText = " ";
	}

	Printer_Address.SetString(CurrentText);
}

void PageCreator::ProcessEmail()
{
	//Never Allow Text to go to zero
	if (CurrentText == "")
	{
		CurrentText = " ";
	}

	Printer_Email.SetString(CurrentText);
}


///////////Update////////

void PageCreator::UpdateSliderR()
{
	Slider_Color_R.SetAnswer();
	EditorSelected->llUpdate();
}

void PageCreator::UpdateSliderG()
{
	Slider_Color_G.SetAnswer();
	EditorSelected->llUpdate();
}

void PageCreator::UpdateSliderB()
{
	Slider_Color_B.SetAnswer();
	EditorSelected->llUpdate();
}

void PageCreator::UpdateSliderA()
{
	Slider_Color_A.SetAnswer();
	EditorSelected->llUpdate();
}

void PageCreator::SetCurrentSlider()
{
	SliderEditor.llSwitch(CurrentPageItem);
	SliderEditor.SetSlider();
}

void PageCreator::SetCurrentToggle()
{
	Toggle_Hide.ClickToggle();
	//Quad_Slider_Test.llUpdate();
}

void PageCreator::ProcessDropDownFile()
{
	File.ToggleShow();
}

void PageCreator::ProcessDropDownEdit()
{
	Edit.ToggleShow();
}


void PageCreator::HighlightDropDownDriver()
{
	File.HoverDriver();
}


void PageCreator::TestFunction()
{
	Log::LogString("TestFunction");
}


void PageCreator::WordSearch(string Search)
{
	Log::LogString("Inside Word Search");
	int Count = 0;
	string Match;
	SearchBar_Customer_Search.SetResultCount(Count);
	SearchBar_Customer_Search.CurrentSearchBar.SearchString = Search;

	//Go through entire CustomerDataBase
	for (auto kv : map_CustomerDataBase)
	{
		auto& Key = kv.first;

		//Check to see if the string matches up 
		Match = PerfectFit(Key, Search);

		if (Match != " " && Count < 19)
		{
			SearchBar_Customer_Search.CurrentSearchBar.Results[Count] = Match;
			SearchBar_Customer_Search.SetResultCount(Count + 1);
			SearchBar_Customer_Search.GetShapeGroup(Count + 1)->ShapeGroupButton = &Button_Customer_Search_Result;
			Count++;
		}
	}

}

string PageCreator::PerfectFit(string TestString, string ReferenceString)
{
	if (TestString.size() < ReferenceString.size()) { return " "; }

	//Go through all Characters in Reference String 
	for (int i = 0; i < ReferenceString.size(); ++i)
	{
		int AddorSub = 0;

		if (ReferenceString[i] > 97)
		{
			AddorSub = -32;
		}
		else
		{
			AddorSub = 32;
		}

		//Compare letters
		if (TestString[i] != ReferenceString[i] && TestString[0] != ReferenceString[i] + AddorSub)
		{
			//Exit if strings stop matching
			return " ";
		}
	}

	return TestString;
}

void PageCreator::SetSearchResult()
{
	Log::LogString("Set Search Result");

	if (CreatorDirectory.ShapeGroup != nullptr)
	{
		SearchBar_Customer_Search.SetResultSelected(CreatorDirectory.ShapeGroup);
		CustomerDetails* CustomerSelected = &map_CustomerDataBase[SearchBar_Customer_Search.CurrentSearchBar.ResultSelected];
		SetCustomerDetails(CustomerSelected);
		//ResetSearch();
	}
}

void PageCreator::BuildCustomerDetailElements()
{
	//Basic Printer Data Setup
	NumberPrinterData PrinterData_Customer_Details;
	PrinterData_Customer_Details.Type = TYPE_STRING;

	//Basic SearchBar Data Setup
	SearchBarData SearchBarData_Customer_Search;
	SearchBarData_Customer_Search.AmountOfResults = 0;

	//Basic Text Data Setup
	TextData TextData_Customer_Details;
	TextData_Customer_Details.Phrase = "Add Customer";
	TextData_Customer_Details.Centered = false;

	//Basic PageItem Data Setup
	llPageItemData PageItem_Customer_Details;
	PageItem_Customer_Details.Color = { 0.0, 0.5, 1.0, 1.0 };

	//Basic ShapeGroup Data Setup
	llShapeGroupData ShapeGroup_Customer_Details;
	ShapeGroup_Customer_Details.Position = {0.15, -0.5};
	ShapeGroup_Customer_Details.Color = {0.0, 1.0, 1.0, 1.0};
	ShapeGroup_Customer_Details.MouseAccess = true;

	//////////////*------- GUI --------*////////////////

	//Add Customer
	Text_Add_Customer.llInit(&CreatorBook, &ShapeGroup_Customer_Details, TextData_Customer_Details);


	//First Name
	PageItem_Customer_Details.Position = Origin;
	PrinterData_Customer_Details.Description = "First Name";
	Printer_First_Name.llInit(&CreatorBook, &PageItem_Customer_Details, PrinterData_Customer_Details);

	//Last Name
	PageItem_Customer_Details.Position = {0.0, -0.1};
	PrinterData_Customer_Details.Description = "Last Name";
	Printer_Last_Name.llInit(&CreatorBook, &PageItem_Customer_Details, PrinterData_Customer_Details);

	//Phone
	PageItem_Customer_Details.Position = { 0.0, -0.2 };
	PrinterData_Customer_Details.Description = "Phone #";
	Printer_Phone.llInit(&CreatorBook, &PageItem_Customer_Details, PrinterData_Customer_Details);

	//Email
	PageItem_Customer_Details.Position = { 0.0, -0.3 };
	PrinterData_Customer_Details.Description = "Email";
	Printer_Email.llInit(&CreatorBook, &PageItem_Customer_Details, PrinterData_Customer_Details);

	//Address
	PageItem_Customer_Details.Position = { 0.0, -0.4 };
	PrinterData_Customer_Details.Description = "Address";
	Printer_Address.llInit(&CreatorBook, &PageItem_Customer_Details, PrinterData_Customer_Details);

	////Customer Search
	PageItem_Customer_Details.Position = {0.0, 0.5};
	SearchBar_Customer_Search.llInit(&CreatorBook, &PageItem_Customer_Details, SearchBarData_Customer_Search);

	DefaultCustomer.FirstName = "Kaden";
	DefaultCustomer.LastName = "Cardenas-Marett";
	DefaultCustomer.Address = "836 Talwood Dr, Peterborough, ON";
	DefaultCustomer.Phone = "905 269 4265";
	map_CustomerDataBase[DefaultCustomer.FirstName] = DefaultCustomer;
	ResetCustomerDetails();
	DefaultCustomer.FirstName = "Jarret";
	DefaultCustomer.LastName = "Oak";
	DefaultCustomer.Address = "Toronto Ontario";
	DefaultCustomer.Phone = "Phone";
	map_CustomerDataBase[DefaultCustomer.FirstName] = DefaultCustomer;
	ResetCustomerDetails();
	DefaultCustomer.FirstName = "Walmart";
	DefaultCustomer.LastName = "Last Name";
	DefaultCustomer.Address = "73 Strathy rd, cobourg, ON, Canada";
	DefaultCustomer.Phone = "Phone";
	map_CustomerDataBase[DefaultCustomer.FirstName] = DefaultCustomer;
	ResetCustomerDetails();
}

void PageCreator::AttachCustomerDetailButtons()
{
	//Build Buttons
	Button_First_Name.LogicalActions[GUI_MOUSELEFT_CLICKED] = SetFirstName;
	Button_Last_Name.LogicalActions[GUI_MOUSELEFT_CLICKED] = SetLastName;
	Button_Phone.LogicalActions[GUI_MOUSELEFT_CLICKED] = SetPhone;
	Button_Address.LogicalActions[GUI_MOUSELEFT_CLICKED] = SetAddress;
	Button_Email.LogicalActions[GUI_MOUSELEFT_CLICKED] = SetEmail;
	Button_Add_Customer.LogicalActions[GUI_MOUSELEFT_CLICKED] = AddCustomer;
	Button_Customer_Search.LogicalActions[GUI_MOUSELEFT_CLICKED] = SetCustomerSearch;
	Button_Customer_Search_Result.LogicalActions[GUI_MOUSELEFT_CLICKED] = SetSearchResult;

	//Attach Buttons to Print-Text UI 
	Printer_First_Name.GetShapeGroup(GROUP_PRINT)->ShapeGroupButton = &Button_First_Name;
	Printer_Last_Name.GetShapeGroup(GROUP_PRINT)->ShapeGroupButton = &Button_Last_Name;
	Printer_Phone.GetShapeGroup(GROUP_PRINT)->ShapeGroupButton = &Button_Phone;
	Printer_Address.GetShapeGroup(GROUP_PRINT)->ShapeGroupButton = &Button_Address;
	Printer_Email.GetShapeGroup(GROUP_PRINT)->ShapeGroupButton = &Button_Email;
	Text_Add_Customer.GetShapeGroup()->ShapeGroupButton = &Button_Add_Customer;
	SearchBar_Customer_Search.GetShapeGroup(GROUP_SEARCH)->ShapeGroupButton = &Button_Customer_Search;
}

void PageCreator::SetCustomerDetails(CustomerDetails* CustomerDetails)
{
	if (CustomerDetails != nullptr)
	{
		PrinterToEdit = Empty;
		ResetCustomerDetailHighlights();

		Printer_First_Name.ChangeString(CustomerDetails->FirstName);
		Printer_Last_Name.ChangeString(CustomerDetails->LastName);
		Printer_Phone.ChangeString(CustomerDetails->Phone);
		Printer_Email.ChangeString(CustomerDetails->Email);
		Printer_Address.ChangeString(CustomerDetails->Address);
	}
	else
	{
		PrinterToEdit = Empty;
		ResetCustomerDetailHighlights();

		Printer_First_Name.ChangeString(nullptr);
		Printer_Last_Name.ChangeString(nullptr);
		Printer_Phone.ChangeString(nullptr);
		Printer_Email.ChangeString(nullptr);
		Printer_Address.ChangeString(nullptr);
	}
}

