#include "MenuCreator.h"

//Menu Creator
//+----------------------------+
void MenuCreator::Prepare_MenuCreator(llBookData* Restaurant_POS, ShaderProgram* ShaderProgram, RawTexture* Texture0, RawTexture* Texture1, RawTexture* Texture2)
{
	RestaurantBook = Restaurant_POS;
	CurrentShader = ShaderProgram;
	Page_MenuCreator.llInit(RestaurantBook, CurrentShader, Texture0, Texture1, Texture2);
	Prepare_Section();
	Prepare_Section_Filler();
	Prepare_Dish();
	Prepare_Dish_Form();
	Prepare_Side();
	Prepare_Side_Filler();
	Prepare_Ingredient();
	Prepare_Ingredient_Form();

	CurrentKeyBoardInput = Empty;
}

void MenuCreator::Update(KeyResult& CurrentKeyResult)
{
	Page_MenuCreator.DrawPage();
	KeyboardToCurrentText(CurrentKeyResult);
	MasterElement::FindElement(RestaurantBook, LEVEL_SHAPEGROUP, ElementsHovered);
	CurrentKeyBoardInput();
}
//+----------------------------+
	 
	 
//Side Editor
//+----------------------------+
void MenuCreator::Prepare_Section()
{
	llPageGroupData PageGroup_Template;
	llPageItemData PageItem_Template;
	NumberPrinterData NumberPrinter_Template;
	llShapeGroupData ShapeGroup_Template;
	TextData TextData_Template;

	PageGroup_Section.llInit(RestaurantBook, &PageGroup_Template);
	PageItem_Unused1.llPageItemInit(RestaurantBook, &PageItem_Template);

	//Section
	TextData_Template.Phrase = "Section";
	ShapeGroup_Template.Position = { -0.78, 0.8 };
	ShapeGroup_Template.BackGround = true;
	ShapeGroup_Template.BackGroundPadding[PADDING_LEFT] = 100;
	ShapeGroup_Template.BackGroundPadding[PADDING_RIGHT] = 100;
	ShapeGroup_Template.BackGroundPadding[PADDING_TOP] = 20;
	ShapeGroup_Template.BackGroundPadding[PADDING_BOTTOM] = 950;
	ShapeGroup_Template.BackGroundPlacementType = PLACEMENT_BELOW;
	ShapeGroup_Template.BackGroundMatchType = MATCH_CENTERS;
	ShapeGroup_Template.BackGroundColor = {0.1, 0.1, 1.0, 1.0}; //Dark Blue
	ShapeGroup_Template.Color = PageCreator::White;
	Text_Label_Section.llInit(RestaurantBook, &ShapeGroup_Template, TextData_Template);


	//Add
	TextData_Template.Phrase = "Section +";
	ShapeGroup_Template.BackGround = true;
	ShapeGroup_Template.BackGroundPlacementType = PLACEMENT_NORMAL;
	ShapeGroup_Template.BackGroundMatchType = MATCH_NONE;
	ShapeGroup_Template.BackGroundPadding[PADDING_LEFT] = 10;
	ShapeGroup_Template.BackGroundPadding[PADDING_RIGHT] = 10;
	ShapeGroup_Template.BackGroundPadding[PADDING_TOP] = 10;
	ShapeGroup_Template.BackGroundPadding[PADDING_BOTTOM] = 10;
	ShapeGroup_Template.BackGroundColor = SubmitOrder::DarkPurple;
	ShapeGroup_Template.Color = SubmitOrder::Pink;
	Button_Add_Section.LogicalActions[GUI_MOUSELEFT_CLICKED] = &Add_Section;
	Text_Add_Section.llInit(RestaurantBook, &ShapeGroup_Template, TextData_Template);
	Text_Add_Section.PlaceBelow(Text_Label_Section.GetEdges(), MATCH_CENTERS, 100);
	Text_Add_Section.AttachButton(&Button_Add_Section);

	DR_PageGroup_Section.Capture(RestaurantBook);
	first_section = true;
	last_section_edges = Text_Label_Section.GetEdges();
}

void MenuCreator::Prepare_Section_Filler()
{
	llPageGroupData PageGroup_Template;
	llPageItemData PageItem_Template;
	NumberPrinterData NumberPrinter_Template;
	llShapeGroupData ShapeGroup_Template;
	TextData TextData_Template;
	//
	PageGroup_Section_Filler.llInit(RestaurantBook, &PageGroup_Template);
	Current_Section = &New_Section;

	//Name
	NumberPrinter_Template.AnswerFontSize = 14;
	NumberPrinter_Template.Type = TYPE_STRING;
	NumberPrinter_Template.String = &Current_Section->Name;
	NumberPrinter_Template.Below = true;
	NumberPrinter_Template.Description = "Name";
	NumberPrinter_Template.AnswerColor = SubmitOrder::Pink;
	PageItem_Template.BackGround = true;
	PageItem_Template.BackGroundPadding[PADDING_LEFT] = 20;
	PageItem_Template.BackGroundPadding[PADDING_RIGHT] = 60;
	PageItem_Template.BackGroundPadding[PADDING_TOP] = 40;
	PageItem_Template.BackGroundPadding[PADDING_BOTTOM] = 200;
	PageItem_Template.BackGroundColor = SubmitOrder::DarkPurple;
	PageItem_Template.Position = { -0.6, 0.0 };
	Printer_Section_Name.llInit(RestaurantBook, &PageItem_Template, NumberPrinter_Template);
	Printer_Section_Name.SetKeyBoardInputFunction(&Button_Section_Name, SetCurrentKeyBoardInput);

	PageGroupItem Filler(RestaurantBook);

	//Submit
	TextData_Template.Phrase = "Submit";
	ShapeGroup_Template.BackGround = true;
	ShapeGroup_Template.BackGroundPadding[PADDING_LEFT] = 40;
	ShapeGroup_Template.BackGroundPadding[PADDING_RIGHT] = 40;
	ShapeGroup_Template.BackGroundPadding[PADDING_TOP] = 20;
	ShapeGroup_Template.BackGroundPadding[PADDING_BOTTOM] = 20;
	ShapeGroup_Template.BackGroundColor = SubmitOrder::DarkPurple;
	ShapeGroup_Template.Color = PageCreator::White;
	Button_Submit_Section.LogicalActions[GUI_MOUSELEFT_CLICKED] = Submit_Section;
	Text_Submit_Section.llInit(RestaurantBook, &ShapeGroup_Template, TextData_Template);
	Text_Submit_Section.PlaceBelow(Printer_Section_Name.GetEdgesWithBackGround(), MATCH_CENTERS, 20);
	Text_Submit_Section.AttachButton(&Button_Submit_Section);

	//Hide Form 
	PageGroup_Section_Filler.Hide();

}


void MenuCreator::Add_Section()
{
	//Hide Add Button
	Text_Add_Section.Hide();

	//Display Form
	PageGroup_Section_Filler.UnHide();
	PageGroup_Section_Filler.PlaceBelow(last_section_edges, MATCH_CENTERS, 20);

	CurrentPrinter.LoadedBook = RestaurantBook;
	CurrentPrinter.llSwitch(Printer_Section_Name.GetData());
	//CurrentText = "Name";
	CurrentKeyBoardInput = ProcessPrinterInput;

}

void MenuCreator::Submit_Section() 
{
	//Hide Form
	PageGroup_Section_Filler.Hide();

	////CHANGE THIS TO UPDATE ONCE YOU HAVE CONTAINERS FIGURED OUT
	Add_Section_Graphic(Current_Section->Name);
	//
	////Display Add Button Below All Side
	Text_Add_Section.UnHide();
	Text_Add_Section.PlaceBelow(last_section_edges, MATCH_CENTERS, 20);


	//Cancel KeyBoard Input
	CurrentKeyBoardInput = Empty;

	//Prepare Side for New Input
	Current_Section->Reset();
	CurrentText = Current_Section->Name;
	//CurrentPrinter.ChangeString(Current_Section->Name);
}
void MenuCreator::Update_Section_Graphics() {}
void MenuCreator::Add_Section_Graphic(const string Name)
{
	DR_PageGroup_Section.LoadUp(RestaurantBook);

	//Text
	TextData TextData_Template;
	TextData_Template.Centered = false;

	//PageItem
	llPageItemData PageItem_Template;
	PageItem_Template.Color = { 0.0, 0.5, 1.0, 1.0 };

	//ShapeGroup
	llShapeGroupData ShapeGroup_Template;
	ShapeGroup_Template.Position = { 0.0, 0.0 };
	ShapeGroup_Template.Color = { 0.0, 1.0, 1.0, 1.0 };
	ShapeGroup_Template.MouseAccess = true;

	//Ordered Item UI --------------------------------------------------------//
	PageItem_Template.BackGround = true;
	PageItem_Template.BackGroundColor = SubmitOrder::DarkPurple; //Dark Red
	PageItem_Template.BackGroundPadding[PADDING_LEFT] = 70;
	PageItem_Template.BackGroundPadding[PADDING_RIGHT] = 70;
	PageItem_Template.BackGroundPadding[PADDING_TOP] = 10;
	PageItem_Template.BackGroundPadding[PADDING_BOTTOM] = 10;

	PageItem_Default_Section.llPageItemInit(RestaurantBook, &PageItem_Template);
	//MenuItem.OrderedDishGraphics = PageItem_Default_Side.GetData(); 

	//Ordered Item-Section Name
	TextData_Template.Phrase = Name;
	ShapeGroup_Template.Color = PageCreator::White; 
	Text_Default_Section_Name.llInit(RestaurantBook, &ShapeGroup_Template, TextData_Template);

	//Place New Section
	int Spacing = 20;
	if (first_section == true) { Spacing = 100; first_section = false; }
	PageItem_Default_Section.PlaceBelow(last_section_edges, MATCH_CENTERS, Spacing);
	last_section_edges = PageItem_Default_Section.GetEdgesWithBackGround();

}
void MenuCreator::Remove_Section_Graphic() {}
void MenuCreator::Rearrange_Section_Graphics() {}
//+----------------------------+
	 
	 
//Dish Editor
//+----------------------------+
void MenuCreator::Prepare_Dish() 
{
	llPageGroupData PageGroup_Template;
	llPageItemData PageItem_Template;
	NumberPrinterData NumberPrinter_Template;
	llShapeGroupData ShapeGroup_Template;
	TextData TextData_Template;

	PageGroup_Dish.llInit(RestaurantBook, &PageGroup_Template);
	PageItem_Unused2.llPageItemInit(RestaurantBook, &PageItem_Template);
	
	//Dish
	TextData_Template.Phrase = "Dish";
	ShapeGroup_Template.BackGround = true;
	//ShapeGroup_Template.BackGroundPadding[PADDING_LEFT] = 40;
	//ShapeGroup_Template.BackGroundPadding[PADDING_RIGHT] = 40;
	//ShapeGroup_Template.BackGroundPadding[PADDING_TOP] = 5;
	//ShapeGroup_Template.BackGroundPadding[PADDING_BOTTOM] = 1000;
	ShapeGroup_Template.BackGroundColor = { 0.5, 0.3, 0.5, 1.0 };
	ShapeGroup_Template.Color = PageCreator::White;
	Text_Label_Dish.llInit(RestaurantBook, &ShapeGroup_Template, TextData_Template);
	Text_Label_Dish.CopyBackGround(Text_Label_Section.GetData());
	Text_Label_Dish.PlaceRight(Text_Label_Section.GetEdgesWithBackGround(), MATCH_FLOORS, 20);
	Text_Label_Dish.OffsetPosition({ 0.0, -PIXEL * 2 }, {false, true});

	//Add
	TextData_Template.Phrase = "Dish +";
	ShapeGroup_Template.BackGround = true;
	ShapeGroup_Template.BackGroundPlacementType = PLACEMENT_NORMAL;
	ShapeGroup_Template.BackGroundMatchType = MATCH_NONE;
	ShapeGroup_Template.BackGroundPadding[PADDING_LEFT] = 10;
	ShapeGroup_Template.BackGroundPadding[PADDING_RIGHT] = 10;
	ShapeGroup_Template.BackGroundPadding[PADDING_TOP] = 10;
	ShapeGroup_Template.BackGroundPadding[PADDING_BOTTOM] = 10;
	ShapeGroup_Template.BackGroundColor = SubmitOrder::DarkPurple;
	ShapeGroup_Template.Color = SubmitOrder::Pink;
	Button_Add_Dish.LogicalActions[GUI_MOUSELEFT_CLICKED] = &Add_Dish;
	Text_Add_Dish.llInit(RestaurantBook, &ShapeGroup_Template, TextData_Template);
	Text_Add_Dish.PlaceBelow(Text_Label_Dish.GetEdges(), MATCH_CENTERS, 100);
	Text_Add_Dish.AttachButton(&Button_Add_Dish);

	DR_PageGroup_Dish.Capture(RestaurantBook);
	first_dish = true;
	last_dish_edges = Text_Label_Dish.GetEdges();
}

void MenuCreator::Prepare_Dish_Form()
{
	llPageGroupData PageGroup_Template;
	llPageItemData PageItem_Template;
	NumberPrinterData NumberPrinter_Template;
	llShapeGroupData ShapeGroup_Template;
	TextData TextData_Template;
	//
	PageGroup_Dish_Filler.llInit(RestaurantBook, &PageGroup_Template);
	Current_Dish = &New_Dish;

	//Name
	NumberPrinter_Template.AnswerFontSize = 14;
	NumberPrinter_Template.Type = TYPE_STRING;
	NumberPrinter_Template.String = &Current_Dish->Name;
	NumberPrinter_Template.Below = true;
	NumberPrinter_Template.Description = "Name";
	NumberPrinter_Template.AnswerColor = SubmitOrder::Pink;
	PageItem_Template.BackGround = true;
	PageItem_Template.BackGroundPadding[PADDING_LEFT] = 20;
	PageItem_Template.BackGroundPadding[PADDING_RIGHT] = 60;
	PageItem_Template.BackGroundPadding[PADDING_TOP] = 40;
	PageItem_Template.BackGroundPadding[PADDING_BOTTOM] = 200;
	PageItem_Template.BackGroundColor = SubmitOrder::DarkPurple;
	PageItem_Template.Position = { -0.2, 0.0 };
	Printer_Dish_Name.llInit(RestaurantBook, &PageItem_Template, NumberPrinter_Template);
	Printer_Dish_Name.SetKeyBoardInputFunction(&Button_Dish_Name, SetCurrentKeyBoardInput);

	//Cost
	NumberPrinter_Template.AnswerFontSize = 12;
	NumberPrinter_Template.Type = TYPE_FLOAT;
	NumberPrinter_Template.Float = &New_Dish.Cost;
	NumberPrinter_Template.Below = true;
	NumberPrinter_Template.DollarSign = true;
	NumberPrinter_Template.Description = "Cost";
	NumberPrinter_Template.AnswerColor = SubmitOrder::Pink;
	PageItem_Template.BackGround = false;
	Printer_Cost.llInit(RestaurantBook, &PageItem_Template, NumberPrinter_Template);
	Printer_Cost.PlaceBelow(Printer_Dish_Name.GetEdges(), MATCH_BEGINNINGS, 40);
	Printer_Cost.SetKeyBoardInputFunction(&Button_Dish_Cost, SetCurrentKeyBoardInput);
	PageGroupItem Filler(RestaurantBook);

	//Submit
	TextData_Template.Phrase = "Submit";
	ShapeGroup_Template.BackGround = true;
	ShapeGroup_Template.BackGroundPadding[PADDING_LEFT] = 40;
	ShapeGroup_Template.BackGroundPadding[PADDING_RIGHT] = 40;
	ShapeGroup_Template.BackGroundPadding[PADDING_TOP] = 20;
	ShapeGroup_Template.BackGroundPadding[PADDING_BOTTOM] = 20;
	ShapeGroup_Template.BackGroundColor = SubmitOrder::DarkPurple;
	ShapeGroup_Template.Color = PageCreator::White;
	Button_Submit_Dish.LogicalActions[GUI_MOUSELEFT_CLICKED] = Submit_Dish;
	Text_Submit_Dish.llInit(RestaurantBook, &ShapeGroup_Template, TextData_Template);
	Text_Submit_Dish.PlaceBelow(Printer_Dish_Name.GetEdgesWithBackGround(), MATCH_CENTERS, 20);
	Text_Submit_Dish.AttachButton(&Button_Submit_Dish);

	//Hide Form 
	PageGroup_Dish_Filler.Hide();

}


void MenuCreator::Add_Dish()
{
	//Hide Add Button
	Text_Add_Dish.Hide();

	//Display Form
	PageGroup_Dish_Filler.UnHide();
	PageGroup_Dish_Filler.PlaceBelow(last_dish_edges, MATCH_CENTERS, 20);
}

void MenuCreator::Submit_Dish() 
{
	//Hide Form
	PageGroup_Dish_Filler.Hide();

	////CHANGE THIS TO UPDATE ONCE YOU HAVE CONTAINERS FIGURED OUT
	Add_Dish_Graphic(Current_Dish->Name);
	//
	////Display Add Button Below All Side
	Text_Add_Dish.UnHide();
	Text_Add_Dish.PlaceBelow(last_dish_edges, MATCH_CENTERS, 20);
	
	//Cancel KeyBoard Input
	CurrentKeyBoardInput = Empty;
	
	//Prepare Side for New Input
	New_Dish.Reset();
}

void MenuCreator::Update_Dish_Graphics() {}

void MenuCreator::Add_Dish_Graphic(const string Name) 
{
	DR_PageGroup_Dish.LoadUp(RestaurantBook);

	//Text
	TextData TextData_Template;
	TextData_Template.Centered = false;

	//PageItem
	llPageItemData PageItem_Template;
	PageItem_Template.Color = { 0.0, 0.5, 1.0, 1.0 };

	//ShapeGroup
	llShapeGroupData ShapeGroup_Template;
	ShapeGroup_Template.Position = { 0.0, 0.0 };
	ShapeGroup_Template.Color = { 0.0, 1.0, 1.0, 1.0 };
	ShapeGroup_Template.MouseAccess = true;

	//Ordered Item UI --------------------------------------------------------//
	PageItem_Template.BackGround = true;
	PageItem_Template.BackGroundColor = SubmitOrder::DarkPurple; //Dark Red
	PageItem_Template.BackGroundPadding[PADDING_LEFT] = 70;
	PageItem_Template.BackGroundPadding[PADDING_RIGHT] = 70;
	PageItem_Template.BackGroundPadding[PADDING_TOP] = 10;
	PageItem_Template.BackGroundPadding[PADDING_BOTTOM] = 10;

	PageItem_Default_Dish.llPageItemInit(RestaurantBook, &PageItem_Template);
	//MenuItem.OrderedDishGraphics = PageItem_Default_Side.GetData(); 

	//Ordered Item-Section Name
	TextData_Template.Phrase = Name;
	ShapeGroup_Template.Color = PageCreator::White; // Light Red
	Text_Default_Dish_Name.llInit(RestaurantBook, &ShapeGroup_Template, TextData_Template);

	//Place New Side
	int Spacing = 20;
	if (first_dish == true) { Spacing = 100; first_dish = false; }
	PageItem_Default_Dish.PlaceBelow(last_dish_edges, MATCH_CENTERS, Spacing);
	last_dish_edges = PageItem_Default_Dish.GetEdgesWithBackGround();

}
void MenuCreator::Remove_Dish_Graphic() {}
void MenuCreator::Rearrange_Dish_Graphics() {}
//+----------------------------+
	 
//Side Editor
//+----------------------------+
void MenuCreator::Prepare_Side() 
{
	llPageGroupData PageGroup_Template;
	llPageItemData PageItem_Template;
	NumberPrinterData NumberPrinter_Template;
	llShapeGroupData ShapeGroup_Template;
	TextData TextData_Template;
	
	PageGroup_Side.llInit(RestaurantBook, &PageGroup_Template);
	PageItem_Unused3.llPageItemInit(RestaurantBook, &PageItem_Template);
	
	//Side
	TextData_Template.Phrase = "Side";
	ShapeGroup_Template.Position = { -0.8, 0.8 };
	ShapeGroup_Template.BackGround = true;
	ShapeGroup_Template.BackGroundPadding[PADDING_LEFT] = 40;
	ShapeGroup_Template.BackGroundPadding[PADDING_RIGHT] = 40;
	ShapeGroup_Template.BackGroundPadding[PADDING_TOP] = 5;
	ShapeGroup_Template.BackGroundPadding[PADDING_BOTTOM] = 1000;
	ShapeGroup_Template.BackGroundColor = PageCreator::Yellow;
	ShapeGroup_Template.Color = PageCreator::White;
	Text_Label_Side.llInit(RestaurantBook, &ShapeGroup_Template, TextData_Template);
	Text_Label_Side.CopyBackGround(Text_Label_Section.GetData());
	Text_Label_Side.PlaceRight(Text_Label_Dish.GetEdgesWithBackGround(), MATCH_FLOORS, 20);
	Text_Label_Side.OffsetPosition({ 0.0, -PIXEL * 2 }, { false, true });
	last_side_edges = Text_Label_Side.GetEdges();

	//Add
	TextData_Template.Phrase = "Side +";
	ShapeGroup_Template.BackGround = true;
	ShapeGroup_Template.BackGroundPlacementType = PLACEMENT_NORMAL;
	ShapeGroup_Template.BackGroundMatchType = MATCH_NONE;
	ShapeGroup_Template.BackGroundPadding[PADDING_LEFT] = 10;
	ShapeGroup_Template.BackGroundPadding[PADDING_RIGHT] = 10;
	ShapeGroup_Template.BackGroundPadding[PADDING_TOP] = 10;
	ShapeGroup_Template.BackGroundPadding[PADDING_BOTTOM] = 10;
	ShapeGroup_Template.BackGroundColor = SubmitOrder::DarkPurple;
	ShapeGroup_Template.Color = SubmitOrder::Pink;
	Button_Add_Side.LogicalActions[GUI_MOUSELEFT_CLICKED] = &Add_Side;
	Text_Add_Side.llInit(RestaurantBook, &ShapeGroup_Template, TextData_Template);
	Text_Add_Side.PlaceBelow(Text_Label_Side.GetEdges(), MATCH_CENTERS, 100);
	Text_Add_Side.AttachButton(&Button_Add_Side);

	DR_PageGroup_Side.Capture(RestaurantBook);
	first_side = true;
	String_Default_Name = "Side";
}

void MenuCreator::Prepare_Side_Filler()
{
	llPageGroupData PageGroup_Template;
	llPageItemData PageItem_Template;
	NumberPrinterData NumberPrinter_Template;
	llShapeGroupData ShapeGroup_Template;
	TextData TextData_Template;
	//
	PageGroup_Side_Filler.llInit(RestaurantBook, &PageGroup_Template);
	Current_Side = &New_Side;

	//Name
	NumberPrinter_Template.AnswerFontSize = 14;
	NumberPrinter_Template.Type = TYPE_STRING;
	NumberPrinter_Template.String = &Current_Side->Name;
	NumberPrinter_Template.Below = true;
	NumberPrinter_Template.Description = "Name";
	NumberPrinter_Template.AnswerColor = SubmitOrder::Pink;
	PageItem_Template.BackGround = true;
	PageItem_Template.BackGroundPadding[PADDING_LEFT] = 20;
	PageItem_Template.BackGroundPadding[PADDING_RIGHT] = 60;
	PageItem_Template.BackGroundPadding[PADDING_TOP] = 40;
	PageItem_Template.BackGroundPadding[PADDING_BOTTOM] = 200;
	PageItem_Template.BackGroundColor = SubmitOrder::DarkPurple;
	PageItem_Template.Position = { 0.1, -0.1 };
	Printer_Side_Name.llInit(RestaurantBook, &PageItem_Template, NumberPrinter_Template);
	Printer_Side_Name.SetKeyBoardInputFunction(&Button_Side_Name, SetCurrentKeyBoardInput);

	PageGroupItem Filler(RestaurantBook);

	//Submit
	TextData_Template.Phrase = "Submit";
	ShapeGroup_Template.BackGround = true;
	ShapeGroup_Template.BackGroundPadding[PADDING_LEFT] = 40;
	ShapeGroup_Template.BackGroundPadding[PADDING_RIGHT] = 40;
	ShapeGroup_Template.BackGroundPadding[PADDING_TOP] = 20;
	ShapeGroup_Template.BackGroundPadding[PADDING_BOTTOM] = 20;
	ShapeGroup_Template.BackGroundColor = SubmitOrder::DarkPurple;
	ShapeGroup_Template.Color = PageCreator::White;
	Button_Submit_Side.LogicalActions[GUI_MOUSELEFT_CLICKED] = Submit_Side;
	Text_Submit_Side.llInit(RestaurantBook, &ShapeGroup_Template, TextData_Template);
	Text_Submit_Side.PlaceBelow(Printer_Side_Name.GetEdgesWithBackGround(), MATCH_CENTERS, 20);
	Text_Submit_Side.AttachButton(&Button_Submit_Side);

	//Hide Form 
	PageGroup_Side_Filler.Hide();
}

//Display Form
void MenuCreator::Add_Side()
{
	//Hide Add Button
	Text_Add_Side.Hide();

	//Display Form
	PageGroup_Side_Filler.UnHide();
	PageGroup_Side_Filler.PlaceBelow(last_side_edges, MATCH_CENTERS, 20);
}

//Submits Side Form
void MenuCreator::Submit_Side() 
{
	//Hide Form
	PageGroup_Side_Filler.Hide();

	//CHANGE THIS TO UPDATE ONCE YOU HAVE CONTAINERS FIGURED OUT
	Add_Side_Graphic(Current_Side->Name);

	//Display Add Button Below All Side
	Text_Add_Side.UnHide();
	Text_Add_Side.PlaceBelow(last_side_edges, MATCH_CENTERS, 20);

	//Cancel KeyBoard Input
	CurrentKeyBoardInput = Empty;

	//Prepare Side for New Input
	New_Side.Reset();
}

void MenuCreator::Update_Side_Graphics() {}

//Displays a Side
void MenuCreator::Add_Side_Graphic(const string Name) 
{
	DR_PageGroup_Side.LoadUp(RestaurantBook);

	//Text
	TextData TextData_Template;
	TextData_Template.Centered = false;

	//PageItem
	llPageItemData PageItem_Template;
	PageItem_Template.Color = { 0.0, 0.5, 1.0, 1.0 };

	//ShapeGroup
	llShapeGroupData ShapeGroup_Template;
	ShapeGroup_Template.Position = { 0.0, 0.0 };
	ShapeGroup_Template.Color = { 0.0, 1.0, 1.0, 1.0 };
	ShapeGroup_Template.MouseAccess = true;

	//Ordered Item UI --------------------------------------------------------//
	PageItem_Template.BackGround = true;
	PageItem_Template.BackGroundColor = SubmitOrder::DarkPurple; //Dark Red
	PageItem_Template.BackGroundPadding[PADDING_LEFT]   = 70; 
	PageItem_Template.BackGroundPadding[PADDING_RIGHT]  = 70;
	PageItem_Template.BackGroundPadding[PADDING_TOP]    = 10;
	PageItem_Template.BackGroundPadding[PADDING_BOTTOM] = 10;
	PageItem_Default_Side.llPageItemInit(RestaurantBook, &PageItem_Template);
	//MenuItem.OrderedDishGraphics = PageItem_Default_Side.GetData(); 

	//Ordered Item-Section Name
	TextData_Template.Phrase = Name;
	ShapeGroup_Template.Color = PageCreator::White; // Light Red
	Text_Default_Side_Name.llInit(RestaurantBook, &ShapeGroup_Template, TextData_Template);

	//Place New Side
	int Spacing = 20;
	if (first_side == true) { Spacing = 100; first_side = false; }
	PageItem_Default_Side.PlaceBelow(last_side_edges, MATCH_CENTERS, Spacing);
	last_side_edges = PageItem_Default_Side.GetEdgesWithBackGround();
}

void MenuCreator::Remove_Side_Graphic() {}
void MenuCreator::Rearrange_Side_Graphics() {}
//+----------------------------+
	 

//What Does this Do? Sets which Printer Data to change so that when we type on the keyboard it changes 
//the printer we selected
void MenuCreator::SetCurrentKeyBoardInput()
{
	Log::LogString("Going in because of background");
	if (ElementsHovered.PageItem != nullptr)
	{
		//User Clicks the Printer Answer
		if (ElementsHovered.PageItem->Type == TYPE_PAGEITEM_NUMBER)
		{
			Log::LogString("Found a Printer!");
			CurrentPrinter.llSwitch(ElementsHovered.PageItem);
			CurrentPrinter.LoadedBook = RestaurantBook;
			CurrentText = *CurrentPrinter.CurrentNumberPrinter.String;
			//CurrentText = "Name";
			CurrentPrinter.SetString(CurrentText);
			CurrentKeyBoardInput = ProcessPrinterInput;
		}
	}

}

void MenuCreator::ProcessPrinterInput()
{
	CurrentPrinter.ChangeString(CurrentText);
}

void MenuCreator::KeyboardToCurrentText(KeyResult& CurrentKeyResult)
{
	//Type Letters
	if (CurrentKeyResult.Ctrl != true && CurrentKeyResult.CurrentAscii != -1 && CurrentKeyResult.Key1 != 0)
	{
		if (CurrentText == "")
		{
			CurrentText = " ";
		}

		CurrentText += CurrentKeyResult.CurrentAscii;
	}

	//Process BackSpace
	if (CurrentKeyResult.Ctrl != true && CurrentKeyResult.Key1 == GUI_BACKSPACE_CLICKED)
	{
		if (CurrentText.size() > 1)
		{
			CurrentText.erase(CurrentText.size() - 1);
		}
		else
		{
			CurrentText = " ";
		}
	}

}

void MenuCreator::ResetCurrentText()
{
	CurrentText = " ";
}
	 
//Ingredient Editor
//+----------------------------+
void MenuCreator::Prepare_Ingredient() 
{
	llPageGroupData PageGroup_Template;
	llPageItemData PageItem_Template;
	NumberPrinterData NumberPrinter_Template;
	llShapeGroupData ShapeGroup_Template;
	TextData TextData_Template;

	PageGroup_Ingredient.llInit(RestaurantBook, &PageGroup_Template);
	PageItem_Unused4.llPageItemInit(RestaurantBook, &PageItem_Template);

	//Section
	TextData_Template.Phrase = "Ingredient";
	ShapeGroup_Template.Position = { -0.8, 0.8 };
	ShapeGroup_Template.BackGround = true;
	ShapeGroup_Template.BackGroundPadding[PADDING_LEFT] = 100;
	ShapeGroup_Template.BackGroundPadding[PADDING_RIGHT] = 100;
	ShapeGroup_Template.BackGroundPadding[PADDING_TOP] = 5;
	ShapeGroup_Template.BackGroundPadding[PADDING_BOTTOM] = 1200;
	ShapeGroup_Template.BackGroundColor = { 0.6, 0.1, 0.1, 1.0 };
	ShapeGroup_Template.Color = SubmitOrder::Pink;
	Text_Label_Ingredient.llInit(RestaurantBook, &ShapeGroup_Template, TextData_Template);
	Text_Label_Ingredient.CopyBackGround(Text_Label_Section.GetData());
	Text_Label_Ingredient.PlaceRight(Text_Label_Side.GetEdgesWithBackGround(), MATCH_FLOORS, 20);

	//Add
	TextData_Template.Phrase = "Ingredient +";
	ShapeGroup_Template.BackGround = true;
	ShapeGroup_Template.BackGroundPlacementType = PLACEMENT_NORMAL;
	ShapeGroup_Template.BackGroundMatchType = MATCH_NONE;
	ShapeGroup_Template.BackGroundPadding[PADDING_LEFT] = 10;
	ShapeGroup_Template.BackGroundPadding[PADDING_RIGHT] = 10;
	ShapeGroup_Template.BackGroundPadding[PADDING_TOP] = 10;
	ShapeGroup_Template.BackGroundPadding[PADDING_BOTTOM] = 10;
	ShapeGroup_Template.BackGroundColor = SubmitOrder::DarkPurple;
	ShapeGroup_Template.Color = SubmitOrder::Pink;
	Text_Add_Ingredient.llInit(RestaurantBook, &ShapeGroup_Template, TextData_Template);
	Text_Add_Ingredient.PlaceBelow(Text_Label_Ingredient.GetEdges(), MATCH_CENTERS, 100);
	Button_Add_Ingredient.LogicalActions[GUI_MOUSELEFT_CLICKED] = &Add_Ingredient;
	Text_Add_Ingredient.AttachButton(&Button_Add_Ingredient);

	DR_PageGroup_Ingredient.Capture(RestaurantBook);
	first_ingredient = true;
	last_ingredient_edges = Text_Label_Ingredient.GetEdges();
}


void MenuCreator::Prepare_Ingredient_Form()
{

	llPageGroupData PageGroup_Template;
	llPageItemData PageItem_Template;
	NumberPrinterData NumberPrinter_Template;
	llShapeGroupData ShapeGroup_Template;
	TextData TextData_Template;
	//
	PageGroup_Ingredient_Filler.llInit(RestaurantBook, &PageGroup_Template);
	Current_Ingredient = &New_Ingredient;

	//Name
	NumberPrinter_Template.AnswerFontSize = 14;
	NumberPrinter_Template.Type = TYPE_STRING;
	NumberPrinter_Template.String = &Current_Ingredient->Name;
	NumberPrinter_Template.Below = true;
	NumberPrinter_Template.Description = "Name";
	NumberPrinter_Template.AnswerColor = SubmitOrder::Pink;
	PageItem_Template.BackGround = true;
	PageItem_Template.BackGroundPadding[PADDING_LEFT] = 20;
	PageItem_Template.BackGroundPadding[PADDING_RIGHT] = 60;
	PageItem_Template.BackGroundPadding[PADDING_TOP] = 40;
	PageItem_Template.BackGroundPadding[PADDING_BOTTOM] = 200;
	PageItem_Template.BackGroundColor = SubmitOrder::DarkPurple;
	PageItem_Template.Position = { 0.1, -0.1 };
	Printer_Ingredient_Name.llInit(RestaurantBook, &PageItem_Template, NumberPrinter_Template);
	Printer_Ingredient_Name.SetKeyBoardInputFunction(&Button_Ingredient_Name, SetCurrentKeyBoardInput);

	PageGroupItem Filler(RestaurantBook);

	//Submit
	TextData_Template.Phrase = "Submit";
	ShapeGroup_Template.BackGround = true;
	ShapeGroup_Template.BackGroundPadding[PADDING_LEFT] = 40;
	ShapeGroup_Template.BackGroundPadding[PADDING_RIGHT] = 40;
	ShapeGroup_Template.BackGroundPadding[PADDING_TOP] = 20;
	ShapeGroup_Template.BackGroundPadding[PADDING_BOTTOM] = 20;
	ShapeGroup_Template.BackGroundColor = SubmitOrder::DarkPurple;
	ShapeGroup_Template.Color = PageCreator::White;
	Button_Submit_Ingredient.LogicalActions[GUI_MOUSELEFT_CLICKED] = Submit_Ingredient;
	Text_Submit_Ingredient.llInit(RestaurantBook, &ShapeGroup_Template, TextData_Template);
	Text_Submit_Ingredient.PlaceBelow(Printer_Ingredient_Name.GetEdgesWithBackGround(), MATCH_CENTERS, 20);
	Text_Submit_Ingredient.AttachButton(&Button_Submit_Ingredient);

	//Hide Form 
	PageGroup_Ingredient_Filler.Hide();

}

void MenuCreator::Add_Ingredient()
{
	//Hide Add Button
	Text_Add_Ingredient.Hide();

	//Display Form
	PageGroup_Ingredient_Filler.UnHide();
	PageGroup_Ingredient_Filler.PlaceBelow(last_ingredient_edges, MATCH_CENTERS, 20);
}

void MenuCreator::Submit_Ingredient()
{

	//Hide Form
	PageGroup_Ingredient_Filler.Hide();

	//CHANGE THIS TO UPDATE ONCE YOU HAVE CONTAINERS FIGURED OUT
	Add_Ingredient_Graphic(Current_Ingredient->Name);

	//Display Add Button Below All Side
	Text_Add_Ingredient.UnHide();
	Text_Add_Ingredient.PlaceBelow(last_ingredient_edges, MATCH_CENTERS, 20);

	//Cancel KeyBoard Input
	CurrentKeyBoardInput = Empty;

	//Prepare Side for New Input
	Current_Ingredient->Reset();
}

void MenuCreator::Update_Ingredient_Graphics() {}
void MenuCreator::Add_Ingredient_Graphic(const string Name)
{
	
	DR_PageGroup_Ingredient.LoadUp(RestaurantBook);

	//Text
	TextData TextData_Template;
	TextData_Template.Centered = false;

	//PageItem
	llPageItemData PageItem_Template;
	PageItem_Template.Color = { 0.0, 0.5, 1.0, 1.0 };

	//ShapeGroup
	llShapeGroupData ShapeGroup_Template;
	ShapeGroup_Template.Position = { 0.0, 0.0 };
	ShapeGroup_Template.Color = { 0.0, 1.0, 1.0, 1.0 };
	ShapeGroup_Template.MouseAccess = true;

	//Ordered Item UI --------------------------------------------------------//
	PageItem_Template.BackGround = true;
	PageItem_Template.BackGroundColor = SubmitOrder::DarkPurple; //Dark Red
	PageItem_Template.BackGroundPadding[PADDING_LEFT] = 70;
	PageItem_Template.BackGroundPadding[PADDING_RIGHT] = 70;
	PageItem_Template.BackGroundPadding[PADDING_TOP] = 10;
	PageItem_Template.BackGroundPadding[PADDING_BOTTOM] = 10;
	PageItem_Default_Ingredient.llPageItemInit(RestaurantBook, &PageItem_Template);
	//MenuItem.OrderedDishGraphics = PageItem_Default_Side.GetData(); 

	//Ordered Item-Section Name
	TextData_Template.Phrase = Name;
	ShapeGroup_Template.Color = PageCreator::White; // Light Red
	Text_Default_Ingredient_Name.llInit(RestaurantBook, &ShapeGroup_Template, TextData_Template);

	//Place New Side
	int Spacing = 20;
	if (first_ingredient == true) { Spacing = 100; first_ingredient = false; }
	PageItem_Default_Ingredient.PlaceBelow(last_ingredient_edges, MATCH_CENTERS, Spacing);
	last_ingredient_edges = PageItem_Default_Ingredient.GetEdgesWithBackGround();
}

void MenuCreator::Remove_Ingredient_Graphic() {}
void MenuCreator::Rearrange_Ingredient_Graphics() {}
//+----------------------------+


void MenuCreator::Empty() {}