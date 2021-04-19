#include "MenuCreator.h"

Dish MenuCreator::Eight;

//Menu Creator
//+----------------------------+
void MenuCreator::Prepare_MenuCreator(llBookData* Restaurant_POS, ShaderProgram* ShaderProgram, RawTexture* Texture0, RawTexture* Texture1, RawTexture* Texture2)
{
	Eight.Name = "I am Eight";
	RestaurantBook = Restaurant_POS;
	CurrentShader = ShaderProgram;
	Page_MenuCreator.llInit(RestaurantBook, CurrentShader, Texture0, Texture1, Texture2);

	//Prepare Sections
	Prepare_Section();
	Prepare_Dish();
	Prepare_Side();
	Prepare_Ingredient();

	//Prepare Forms
	Prepare_Section_Filler();
	Prepare_Dish_Form();
	Prepare_Side_Filler();
	Prepare_Ingredient_Form();

	CurrentKeyBoardInput = Empty;
}

void MenuCreator::PrepareMenuContainers(map<string, Section>* Section, map<string, Dish>* Dish, map<string, DishSide>* Side, map<string, Ingredient>* Ingredient)
{
	All_Sections = Section;
	All_Dishes = Dish;
	All_Sides = Side;
	All_Ingredients = Ingredient;
}


void MenuCreator::Update(KeyResult& CurrentKeyResult)
{
	Page_MenuCreator.DrawPage();
	KeyboardToCurrentText(CurrentKeyResult);
	MasterElement::FindElement(RestaurantBook, LEVEL_SHAPEGROUP, ElementsHovered);
	CurrentKeyBoardInput();

	if (ElementsHovered.PageItem != nullptr && GUI_R_CLICKED)
	{
		//cout << ElementsHovered.ShapeGroup << endl;
		//Log::LogString(ElementsHovered.PageItem->DescriptiveData);
	}

}
//+----------------------------+
	 

void MenuCreator::PrintSectionDishes(Section& Current_Section)
{
	Log::LogString("Section: " + Current_Section.Name + "-------------------------------------");
	for (auto Dish_Name : Current_Section.Dish_Names)
	{
		Log::LogString("  ");
		PrintDishSides((*All_Dishes)[Dish_Name]); //Prints the Specific Sides in this Dish
	}
}

void MenuCreator::PrintDishSides(Dish& Current_Dish)
{
	Log::LogString("  ");
	Log::LogString("Dish: " + Current_Dish.Name + "-------------------------------------");
	for (auto Side_Name : Current_Dish.Side_Names)
	{
		PrintSideIngredients((*All_Sides)[Side_Name]); //Prints the Specific Sides in this Dish
	}
}

void MenuCreator::PrintSideIngredients(DishSide& Current_Side)
{
	//Loop through all Ingredients in Side
	Log::LogString("  ");
	Log::LogString("Side: " + Current_Side.Name + "-------------------------------------");
	for (auto Ingredient_Name_Quantity : Current_Side.Ingredient_Names)
	{
		cout << "Ingredient " << Ingredient_Name_Quantity.first << " , " << Ingredient_Name_Quantity.second << endl;
	}
}
	 
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

//Sets up a new section and displays a form to fill it out
void MenuCreator::Add_Section()
{
	//Prepare a New Section
	Current_Section = &New_Section;
	Current_Section->Reset();
	CurrentText = Current_Section->Name;

	//Setup Form Input
	CurrentPrinter.LoadedBook = RestaurantBook;
	CurrentPrinter.llSwitch(Printer_Section_Name.GetData());
	CurrentKeyBoardInput = ProcessPrinterInput;

	//Display Section Form
	PageGroup_Section_Filler.UnHide();
	PageGroup_Section_Filler.PlaceBelow(last_section_edges, MATCH_CENTERS, 20);

	//Hide "Add Section" Button
	Text_Add_Section.Hide();

}

void MenuCreator::Add_Section_To_Container()
{
	(*All_Sections)[Current_Section->Name] = *Current_Section;

	Current_Section = &(*All_Sections)[Current_Section->Name];
}

void MenuCreator::Submit_Section()
{
	//Add Section to Map
	string Section_Name = Current_Section->Name;
	Section& Added_Section = (*All_Sections)[Section_Name];

	//Set New Section as Current Section
	Added_Section.Name = Section_Name;
	Current_Section = &Added_Section;

	//Display the New Section
	Add_Section_Graphic(Section_Name); //Update_Section_Graphic() instead

	llPageItemData* Last_Section_Graphic = First_Section_Graphic;

	if (Last_Section_Graphic != nullptr)
	{
	    while (Last_Section_Graphic->Next != nullptr)
	    {
	    	Last_Section_Graphic = Last_Section_Graphic->Next;
	    }

		Highlight_Section(Last_Section_Graphic);
	}

	//Display Dishes From New Section
	Update_Dish_Graphics();

	//Hide Section Form
	PageGroup_Section_Filler.Hide();

	//Cancel Section Form Input
	CurrentKeyBoardInput = Empty;

	//Display "Add Section" Button
	Text_Add_Section.UnHide();
	Text_Add_Section.PlaceBelow(last_section_edges, MATCH_CENTERS, 20);
}

//Display all the Dishes in the selected section
void MenuCreator::Select_Section()
{
	//Get Section Selected
	string Name_Selected = ElementsHovered.PageItem->DescriptiveData;
	Section* Section_Selected = &(*All_Sections)[Name_Selected];

	//Section Already Selected
	if (Current_Section == Section_Selected) { return; }

	//Set Section 
	Current_Section = Section_Selected;
	Highlight_Section(ElementsHovered.PageItem);

	//Display Dishes
	Update_Dish_Graphics();
		
	//Section Already Selected // Section Form Not Displayed
	//Dishes Already Loaded? // Section Form Already Displayed? // Hide Section Form
}

void MenuCreator::Double_Select_Dish()
{
	PageGroup_Dish_Filler.UnHide();
	PageGroup_Dish_Filler.SetllPosition({0.0, 0.0}, INPUT_CENTER);
	Update_Dish_Form();
}

void MenuCreator::Highlight_Section(llPageItemData* PageItem_Section_Graphic)
{
	//Validation & No Section_Graphic Selected 
	if (PageItem_Section_Graphic == nullptr) { Log::LogString("Highlight Section Failed"); return; }
	if (Section_Graphic_Selected == nullptr) { Section_Graphic_Selected = PageItem_Section_Graphic; }

	//Prepare Section_Graphic for Editing
	PageGroupItem Section_Graphic(PageItem_Section_Graphic);
	Section_Graphic.LoadedBook = RestaurantBook;

	//De-Highlight Previous Graphic Selected
	Section_Graphic.llSwitch(Section_Graphic_Selected);
	Section_Graphic.SetBackGroundColor(Section_Color);

	//Highlight Graphic Selected
	Section_Graphic.llSwitch(PageItem_Section_Graphic);
	Section_Graphic.SetBackGroundColor(Highlight_Section_Color);

	//Set New Graphic_Selected
	Section_Graphic_Selected = PageItem_Section_Graphic;
}

void MenuCreator::Update_Section_Graphics() 
{
	//Display All section Graphics

	//loop through all Sections
	for (auto Section : (*All_Sections))
	{
		Add_Section_Graphic(Section.first);
		Current_Section = &(*All_Sections)[Section.first]; //Set the current Section
	}


	//Nothing? //Display

	//Existing? // Add // Hide
}

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
	PageItem_Template.BackGroundPadding[PADDING_LEFT] = 30;
	PageItem_Template.BackGroundPadding[PADDING_RIGHT] = 30;
	PageItem_Template.BackGroundPadding[PADDING_TOP] = 10;
	PageItem_Template.BackGroundPadding[PADDING_BOTTOM] = 10;
	PageItem_Template.DescriptiveData = Name; //Attach Key to UIPageItem_Default_Section

	//Page Item
	Button_Select_Section.LogicalActions[GUI_MOUSELEFT_CLICKED] = Select_Section;
	PageGroupItem PageItem_Section_Graphic(RestaurantBook, &PageItem_Template);
	PageItem_Section_Graphic.GetData()->PageItemButton = &Button_Select_Section;

	//Text
	TextData_Template.Phrase = Name;
	ShapeGroup_Template.Color = PageCreator::White; // Light Red
	Text Text_Dish_Name(RestaurantBook, &ShapeGroup_Template, TextData_Template);

	if (First_Section_Graphic == nullptr)
	{
		First_Section_Graphic = PageItem_Section_Graphic.GetData();
	}



	//Place New Section
	int Spacing = 20;
	if (first_section == true) { Spacing = 100; first_section = false; }
	PageItem_Section_Graphic.PlaceBelow(last_section_edges, MATCH_CENTERS, Spacing);
	last_section_edges = PageItem_Section_Graphic.GetEdgesWithBackGround();

	Text_Add_Section.PlaceBelow(last_section_edges, MATCH_CENTERS, 20);
}
//void MenuCreator::Remove_Section_Graphic() {}
void MenuCreator::Rearrange_Section_Graphics() {}
//+----------------------------+
	 
	 
//Dish Editor
//+----------------------------+
void MenuCreator::Prepare_Dish() 
{
	First_Dish_Graphic = nullptr;

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
	current_dish_edges = Text_Label_Dish.GetEdges();
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
	NumberPrinter_Template.Float = &Current_Dish->Cost;
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
	//Prepare a New Dish
	Current_Dish = &New_Dish;
	Current_Dish->Reset();
	CurrentText = Current_Dish->Name;

	//Setup Dish Form Input
	CurrentPrinter.LoadedBook = RestaurantBook;
	CurrentPrinter.llSwitch(Printer_Dish_Name.GetData());
	CurrentKeyBoardInput = ProcessPrinterInput;

	//Display Dish Form
	PageGroup_Dish_Filler.UnHide();
	PageGroup_Dish_Filler.PlaceBelow(last_dish_edges, MATCH_CENTERS, 20);

	//Hide "Add Dish" Button
	Text_Add_Dish.Hide();
}

void MenuCreator::Add_Dish_To_Container()
{
	(*All_Sections)[Current_Section->Name].Dish_Names.insert(Current_Dish->Name);
	(*All_Dishes)[Current_Dish->Name] = *Current_Dish;

	//Set Dish in Container as Dish Selected
	Current_Dish = &(*All_Dishes)[Current_Dish->Name];
}

void MenuCreator::Submit_Dish() 
{
	//Hide Form
	PageGroup_Dish_Filler.Hide();

	Add_Dish_To_Container();

	Update_Dish_Graphics();
	//
	////Display Add Button Below All Side
	Text_Add_Dish.UnHide();
	Text_Add_Dish.PlaceBelow(last_dish_edges, MATCH_CENTERS, 20);
	
	//Cancel KeyBoard Input
	CurrentKeyBoardInput = Empty;
	
	//Prepare Side for New Input
	New_Dish.Reset();
}

void MenuCreator::Select_Dish()
{

	//Get Section Selected
	string Selected_Dish_Name = ElementsHovered.PageItem->DescriptiveData;

	//Set Section 
	Current_Dish = &Dish_DataBase[Selected_Dish_Name]; // Dish_Selected;

	Log::LogString("Name Hovered: " + Current_Dish->Name);
	Highlight_Dish(ElementsHovered.PageItem);

	//Hide Dish Form
	PageGroup_Dish_Filler.Hide();

	//Dish Already Selected
	//if (Current_Dish == Dish_Selected) { return; }

	//Display Dishes
	Update_Side_Graphics();

	//Section Already Selected // Section Form Not Displayed
	//Dishes Already Loaded? // Section Form Already Displayed? // Hide Section Form
}

void MenuCreator::Highlight_Dish(llPageItemData* PageItem_Dish_Graphic)
{

	//Validation & No Section_Graphic Selected 
	if (PageItem_Dish_Graphic == nullptr) { Log::LogString("Highlight Section Failed"); return; }
	if (PageItem_Dish_Graphic == nullptr) { Dish_Graphic_Selected = PageItem_Dish_Graphic; }

	//Prepare Section_Graphic for Editing
	PageGroupItem Dish_Graphic(PageItem_Dish_Graphic);
	Dish_Graphic.LoadedBook = RestaurantBook;

	//De-Highlight Previous Graphic Selected
	Dish_Graphic.llSwitch(Dish_Graphic_Selected);
	Dish_Graphic.SetBackGroundColor(Dish_Color);

	//Highlight Graphic Selected
	Dish_Graphic.llSwitch(PageItem_Dish_Graphic);
	Dish_Graphic.SetBackGroundColor(Highlight_Dish_Color);

	//Set New Graphic_Selected
	Dish_Graphic_Selected = PageItem_Dish_Graphic;
}

void MenuCreator::Update_Dish_Graphics()
{
	Log::LogString("Updating Dish Graphics------------------------------------------");
	llPageItemData* Current_Dish_PageItem = First_Dish_Graphic;
	first_dish = true;
	last_dish_edges = current_dish_edges; 
	bool AddOnly = false;

	//Use the "Current_Section" to loop through it's dishes
	for (auto Dish : (*All_Sections)[Current_Section->Name].Dish_Names)
	{
		//New Graphic
		if (Current_Dish_PageItem == nullptr)
		{
			//Create Graphic
			Add_Dish_Graphic(Dish);
			Current_Dish = &(*All_Dishes)[Dish];
			Log::LogString("Adding Dish Graphic-------------------------------------");
			AddOnly = true;
		}

		////Existing Graphic
		if (Current_Dish_PageItem != nullptr && AddOnly != true)
		{
			//Change Graphic
			Replace_Dish_Graphic(Dish, Current_Dish_PageItem);
			Log::LogString("Replacing-------------------------------------------------");
		}

		//Highlight Selected
		if (Current_Dish_PageItem != nullptr)
		{
			if (Current_Dish_PageItem->DescriptiveData == Current_Dish->Name)
			{
				Highlight_Dish(Current_Dish_PageItem);
			}
		}

		//if we add, it will go through replacing alse thats why we need this boolean
		AddOnly = false;

		//Stop Cycling if there is no shapegroup
		if (Current_Dish_PageItem != nullptr) { Current_Dish_PageItem = Current_Dish_PageItem->Next;}
	}

	//Graphics left over
	////Existing? // Add // Hide
	while (Current_Dish_PageItem != nullptr)
	{
		Hide_Dish_Graphic(Current_Dish_PageItem);
		Current_Dish_PageItem = Current_Dish_PageItem->Next;
	}
}

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
	PageItem_Template.BackGroundPadding[PADDING_LEFT] = 30;
	PageItem_Template.BackGroundPadding[PADDING_RIGHT] = 30;
	PageItem_Template.BackGroundPadding[PADDING_TOP] = 10;
	PageItem_Template.BackGroundPadding[PADDING_BOTTOM] = 10;
	PageItem_Template.DescriptiveData = Name; //Attach Key to UI

	//Page Item
	Button_Select_Dish.LogicalActions[GUI_MOUSELEFT_CLICKED] = Select_Dish;
	Button_Select_Dish.LogicalActions[GUI_MOUSELEFT_DOUBLECLICKED] = Double_Select_Dish;
	PageGroupItem PageItem_Dish_Graphic(RestaurantBook, &PageItem_Template);
	PageItem_Dish_Graphic.GetData()->PageItemButton = &Button_Select_Dish;
	
	//Text
	TextData_Template.Phrase = Name;
	ShapeGroup_Template.Color = PageCreator::White; // Light Red
	Text Text_Dish_Name(RestaurantBook, &ShapeGroup_Template, TextData_Template);

	if (First_Dish_Graphic == nullptr)
	{
		First_Dish_Graphic = PageItem_Dish_Graphic.GetData();
	}

	//Place New Side
	int Spacing = 20;
	if (first_dish == true) { Spacing = 100; first_dish = false; }
	PageItem_Dish_Graphic.PlaceBelow(last_dish_edges, MATCH_CENTERS, Spacing);
	last_dish_edges = PageItem_Dish_Graphic.GetEdgesWithBackGround();

	Text_Add_Dish.PlaceBelow(last_dish_edges, MATCH_CENTERS, 20);

}

//Can't Delete Right Now so we will have to hide
void MenuCreator::Replace_Dish_Graphic(string Name, llPageItemData* Dish_PageItem)
{
	if (Dish_PageItem == nullptr) { Log::LogString("replace_dish_graphic ERROR:: Dish_PageItem nullptr"); return; }

	llShapeGroupData* CurrentShapeGroup = Dish_PageItem->ShapeGroup;

	Text Dish_Graphic_Reference(CurrentShapeGroup);
	Dish_Graphic_Reference.LoadedBook = RestaurantBook;
	Dish_Graphic_Reference.llSwitch(CurrentShapeGroup);
	Dish_Graphic_Reference.SetllText(Name);

	//Place New Side
	int Spacing = 20;
	if (first_dish == true) { Spacing = 100; first_dish = false; }

	PageGroupItem PageItem_Dish_Graphic(Dish_PageItem);
	PageItem_Dish_Graphic.LoadedBook = RestaurantBook;
	PageItem_Dish_Graphic.llSwitch(Dish_PageItem);
	PageItem_Dish_Graphic.PlaceBelow(last_dish_edges, MATCH_CENTERS, Spacing);
	PageItem_Dish_Graphic.UnHide();
	Dish_PageItem->DescriptiveData = Name; //Attach Key to UI
	
	last_dish_edges = PageItem_Dish_Graphic.GetEdgesWithBackGround();

	Text_Add_Dish.PlaceBelow(last_dish_edges, MATCH_CENTERS, 20);
}


void MenuCreator::Hide_Dish_Graphic(llPageItemData* Dish_PageItem)
{
	//Set New Name
	PageGroupItem PageItem_Dish_Graphic(Dish_PageItem);
	PageItem_Dish_Graphic.LoadedBook = RestaurantBook;
	PageItem_Dish_Graphic.llSwitch(Dish_PageItem);
	PageItem_Dish_Graphic.Hide();
	Dish_PageItem->DescriptiveData = " ";

	//Place New Side
	int Spacing = 20;
	if (first_dish == true ) { Spacing = 100; first_dish = false; }
	PageItem_Dish_Graphic.PlaceBelow(last_dish_edges, MATCH_CENTERS, Spacing);

	//We are Hiding All
	if (Dish_PageItem == First_Dish_Graphic)
	{
		Text_Add_Dish.PlaceBelow(current_dish_edges, MATCH_CENTERS, 100);
	}
}


void MenuCreator::Update_Dish_Form()
{
	Printer_Dish_Name.ChangeString(Current_Dish->Name);//llUpdate();
	Printer_Cost.SetFloat(Current_Dish->Cost);//llUpdate();
}


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
	ShapeGroup_Template.BackGroundColor = { 0.0, 0.29, 0.33, 1.0 };
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

	current_side_edges = Text_Label_Side.GetEdges();
	last_side_edges = Text_Label_Side.GetEdges();
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
	//Prepare a New Section
	Current_Side = &New_Side;
	Current_Side->Reset();
	CurrentText = Current_Side->Name;

	//Setup Form Input
	CurrentPrinter.LoadedBook = RestaurantBook;
	CurrentPrinter.llSwitch(Printer_Side_Name.GetData());
	CurrentKeyBoardInput = ProcessPrinterInput;

	//Display Section Form
	PageGroup_Side_Filler.UnHide();
	PageGroup_Side_Filler.PlaceBelow(last_side_edges, MATCH_CENTERS, 20);

	//Hide "Add Section" Button
	Text_Add_Side.Hide();
}

void MenuCreator::Add_Side_To_Container()
{
	//Add Side Name into All Dishes
	(*All_Dishes)[Current_Dish->Name].Side_Names.insert(Current_Side->Name);

	//Set the Side Data to the container
	(*All_Sides)[Current_Side->Name] = *Current_Side;

	//the current side is now whats in the container
	Current_Side = &(*All_Sides)[Current_Side->Name];

	//the reason we did the action above is because if the current side is connected to the 
	//"New" Variable when we add sides to it, it will add it to all the dishes
	//because Current_Side is now pointing to whats in the container and not to "New Side"
	//it will add sides to the container thus only adding to the container not to everything
}

//Submits Side Form
void MenuCreator::Submit_Side() 
{
	//Add Section to Map
	string Side_Name = Current_Side->Name;
	DishSide& Added_Side = (*All_Sides)[Side_Name];

	//Set New Section as Current Section
	Added_Side.Name = Side_Name;
	Current_Side = &Added_Side;

	//Set Current Section to Container
	Add_Side_To_Container();

	//Add Side and Update
	Update_Side_Graphics();// instead

	//Display Dishes From New Section
	Update_Ingredient_Graphics();

	//Hide Section Form
	PageGroup_Side_Filler.Hide();

	//Cancel Section Form Input
	CurrentKeyBoardInput = Empty;

	//Display "Add Section" Button
	Text_Add_Side.UnHide();
	Text_Add_Side.PlaceBelow(last_side_edges, MATCH_CENTERS, 20);
}


void MenuCreator::Select_Side()
{

	//Get Section Selected
	string Name_Selected = ElementsHovered.PageItem->DescriptiveData;
	DishSide* Side_Selected = &(*All_Sides)[Name_Selected];

	//Section Already Selected
	if (Current_Side == Side_Selected) { return; }

	//Set Section 
	Current_Side = Side_Selected;
	Highlight_Side(ElementsHovered.PageItem);

	//Display Ingredients
	Log::LogString("Before Ingredient update");
	Update_Ingredient_Graphics();

	//Section Already Selected // Section Form Not Displayed
	//Dishes Already Loaded? // Section Form Already Displayed? // Hide Section Form
}

void MenuCreator::Highlight_Side(llPageItemData* PageItem_Side_Graphic)
{
	//Validation & No Section_Graphic Selected 
	if (PageItem_Side_Graphic == nullptr) { Log::LogString("Highlight Section Failed"); return; }
	if (PageItem_Side_Graphic == nullptr) { Side_Graphic_Selected = PageItem_Side_Graphic; }

	//Prepare Section_Graphic for Editing
	PageGroupItem Side_Graphic(PageItem_Side_Graphic);
	Side_Graphic.LoadedBook = RestaurantBook;

	//De-Highlight Previous Graphic Selected
	Side_Graphic.llSwitch(Side_Graphic_Selected);
	Side_Graphic.SetBackGroundColor(Side_Color);

	//Highlight Graphic Selected
	Side_Graphic.llSwitch(PageItem_Side_Graphic);
	Side_Graphic.SetBackGroundColor(Highlight_Side_Color);

	//Set New Graphic_Selected
	Side_Graphic_Selected = PageItem_Side_Graphic;
}

void MenuCreator::Update_Side_Graphics() 
{

	Log::LogString("Updating Side Graphics--------------------------------------------");
	llPageItemData* Current_Side_PageItem = First_Side_Graphic;
	first_side = true;
	last_side_edges = current_side_edges;
	bool AddOnly = false;

	//Use the "Current_Section" to loop through it's dishes
	for (auto Side : (*All_Dishes)[Current_Dish->Name].Side_Names)
	{
		//New Graphic
		if (Current_Side_PageItem == nullptr)
		{
			//Create Graphic
			Add_Side_Graphic(Side);
			Current_Side = &(*All_Sides)[Side];
			AddOnly = true;
		}

		////Existing Graphic
		if (Current_Side_PageItem != nullptr && AddOnly != true)
		{
			//Change Graphic
			Replace_Side_Graphic(Side, Current_Side_PageItem);
		}

		//Highlight Selected
		if (Current_Side_PageItem != nullptr)
		{
			if (Current_Side_PageItem->DescriptiveData == Current_Side->Name)
			{
				Highlight_Side(Current_Side_PageItem);
			}
		}

		//if we add, it will go through replacing alse thats why we need this boolean
		AddOnly = false;

		//Stop Cycling if there is no shapegroup
		if (Current_Side_PageItem != nullptr) { Current_Side_PageItem = Current_Side_PageItem->Next; }
	}
	//Graphics left over
	////Existing? // Add // Hide
	while (Current_Side_PageItem != nullptr)
	{
		Hide_Side_Graphic(Current_Side_PageItem);
		Current_Side_PageItem = Current_Side_PageItem->Next;
	}
}

//Displays a Side
void MenuCreator::Add_Side_Graphic(const string Name) 
{
	Log::LogString("Adding Side Graphic");
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
	PageItem_Template.BackGroundPadding[PADDING_LEFT]   = 30; 
	PageItem_Template.BackGroundPadding[PADDING_RIGHT]  = 30;
	PageItem_Template.BackGroundPadding[PADDING_TOP]    = 10;
	PageItem_Template.BackGroundPadding[PADDING_BOTTOM] = 10;
	PageItem_Template.DescriptiveData = Name; //Attach Key to UI

	//Page Item
	Button_Select_Side.LogicalActions[GUI_MOUSELEFT_CLICKED] = Select_Side;
	PageGroupItem PageItem_Side_Graphic(RestaurantBook, &PageItem_Template);
	PageItem_Side_Graphic.GetData()->PageItemButton = &Button_Select_Side;

	//Text
	TextData_Template.Phrase = Name;
	ShapeGroup_Template.Color = PageCreator::White; // Light Red
	Text Text_Side_Name(RestaurantBook, &ShapeGroup_Template, TextData_Template);

	if (First_Side_Graphic == nullptr)
	{
		First_Side_Graphic = PageItem_Side_Graphic.GetData();
	}

	//Place New Side
	int Spacing = 20;
	if (first_side == true) { Spacing = 100; first_side = false; }
	PageItem_Side_Graphic.PlaceBelow(last_side_edges, MATCH_CENTERS, Spacing);
	last_side_edges = PageItem_Side_Graphic.GetEdgesWithBackGround();

	Text_Add_Side.PlaceBelow(last_side_edges, MATCH_CENTERS, 20);
	Log::LogString("Add Complete");
}

void MenuCreator::Replace_Side_Graphic(string Name, llPageItemData* Side_PageItem)
{
	Log::LogString("Replacing Side Graphic");
	if (Side_PageItem == nullptr) { Log::LogString("replace_side_graphic ERROR:: Side_PageItem nullptr"); return; }
	if (Side_PageItem->ShapeGroup == nullptr) { Log::LogString("replace_side_graphic ERROR:: Side_PageItem->ShapeGroup nullptr"); return; }

	llShapeGroupData* CurrentShapeGroup = Side_PageItem->ShapeGroup;

	Text Side_Graphic_Reference(CurrentShapeGroup);
	Side_Graphic_Reference.LoadedBook = RestaurantBook;
	Side_Graphic_Reference.llSwitch(CurrentShapeGroup);
	Side_Graphic_Reference.SetllText(Name);

	//Place New Side
	int Spacing = 20;
	if (first_side == true) { Spacing = 100; first_side = false; }

	PageGroupItem PageItem_Side_Graphic(Side_PageItem);
	PageItem_Side_Graphic.LoadedBook = RestaurantBook;
	PageItem_Side_Graphic.llSwitch(Side_PageItem);
	PageItem_Side_Graphic.PlaceBelow(last_side_edges, MATCH_CENTERS, Spacing);
	PageItem_Side_Graphic.UnHide();
	Side_PageItem->DescriptiveData = Name; //Attach Key to UI

	last_side_edges = PageItem_Side_Graphic.GetEdgesWithBackGround();

	Text_Add_Side.PlaceBelow(last_side_edges, MATCH_CENTERS, 20);
}

void MenuCreator::Hide_Side_Graphic(llPageItemData* Side_PageItem)
{
	//Set New Name
	PageGroupItem PageItem_Side_Graphic(Side_PageItem);
	PageItem_Side_Graphic.LoadedBook = RestaurantBook;
	PageItem_Side_Graphic.llSwitch(Side_PageItem);
	PageItem_Side_Graphic.Hide();
	Side_PageItem->DescriptiveData = " ";

	//Place New Side
	int Spacing = 20;
	if (first_side == true) { Spacing = 100; first_side = false; }
	PageItem_Side_Graphic.PlaceBelow(last_side_edges, MATCH_CENTERS, Spacing);

	//We are Hiding All
	if (Side_PageItem == First_Side_Graphic)
	{
		Text_Add_Side.PlaceBelow(current_side_edges, MATCH_CENTERS, 100);
	}
}



void MenuCreator::Rearrange_Side_Graphics() {}
//+----------------------------+
	 

//What Does this Do? Sets which Printer Data to change so that when we type on the keyboard it changes 
//the printer we selected
void MenuCreator::SetCurrentKeyBoardInput()
{
	if (ElementsHovered.PageItem != nullptr)
	{
		//User Clicks the Printer Answer
		if (ElementsHovered.PageItem->Type == TYPE_PAGEITEM_NUMBER)
		{
			Log::LogString("Found a Printer!");
			CurrentPrinter.llSwitch(ElementsHovered.PageItem);
			CurrentPrinter.LoadedBook = RestaurantBook;
			CurrentText = CurrentPrinter.Get_For_Keyboard();
			//CurrentText = "Name";
			CurrentPrinter.SetString(CurrentText);
			CurrentKeyBoardInput = ProcessPrinterInput;
		}
	}

}

//Responsible for Setting Text in elements from user input
void MenuCreator::ProcessPrinterInput()
{
	//CurrentPrinter.ChangeString(CurrentText);
	CurrentPrinter.Set_With_Keyboard(CurrentText);
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
	current_ingredient_edges = Text_Label_Ingredient.GetEdges();

	Text_Add_Ingredient.PlaceBelow(last_ingredient_edges, MATCH_CENTERS, 100);
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
	//Prepare a New Section
	Current_Ingredient = &New_Ingredient;
	Current_Ingredient->Reset();
	CurrentText = Current_Ingredient->Name;

	//Setup Form Input
	CurrentPrinter.LoadedBook = RestaurantBook;
	CurrentPrinter.llSwitch(Printer_Ingredient_Name.GetData());
	CurrentKeyBoardInput = ProcessPrinterInput;

	//Display Section Form
	PageGroup_Ingredient_Filler.UnHide();
	PageGroup_Ingredient_Filler.PlaceBelow(last_ingredient_edges, MATCH_CENTERS, 20);

	//Hide "Add Section" Button
	Text_Add_Ingredient.Hide();
}

void MenuCreator::Add_Ingredient_To_Container()
{
	//Dishes = Sides
	//Sides = Ingredients

	//Add Side Name into All Dishes
	(*All_Sides)[Current_Side->Name].Ingredient_Names[Current_Ingredient->Name] = Current_Ingredient->Measurement;

	//Add the Data from Current Side into All Sides
	(*All_Ingredients)[Current_Ingredient->Name] = *Current_Ingredient;

	//the current side is now whats in the container
	Current_Ingredient = &(*All_Ingredients)[Current_Ingredient->Name];
}

void MenuCreator::Submit_Ingredient()
{
	//Add Section to Map
	string Ingredient_Name = Current_Ingredient->Name;
	Ingredient& Added_Ingredient = (*All_Ingredients)[Ingredient_Name];

	//Set New Section as Current Section
	Added_Ingredient.Name = Ingredient_Name;
	Current_Ingredient = &Added_Ingredient;

	//Set Current Section to Container
	Add_Ingredient_To_Container();

	//Display the New Section
	Add_Ingredient_Graphic(Ingredient_Name); //Update_Section_Graphic() instead

	//Hide Section Form
	PageGroup_Ingredient_Filler.Hide();

	//Cancel Section Form Input
	CurrentKeyBoardInput = Empty;

	//Display "Add Section" Button
	Text_Add_Ingredient.UnHide();
	Text_Add_Ingredient.PlaceBelow(last_ingredient_edges, MATCH_CENTERS, 20);
}

void MenuCreator::Update_Ingredient_Graphics() 
{
	Log::LogString("Updating Ingredient Graphics--------------------------------------------------");
	llPageItemData* Current_Ingredient_PageItem = First_Ingredient_Graphic;
	first_ingredient = true;
	last_ingredient_edges = current_ingredient_edges;
	bool AddOnly = false;

	//Use the "Current_Section" to loop through it's dishes
	for (auto Ingredient : (*All_Sides)[Current_Side->Name].Ingredient_Names)
	{
		//New Graphic
		if (Current_Ingredient_PageItem == nullptr)
		{
			//Create Graphic
			Add_Ingredient_Graphic(Ingredient.first);
			Current_Ingredient = &(*All_Ingredients)[Ingredient.first];
			AddOnly = true;
		}

		////Existing Graphic
		if (Current_Ingredient_PageItem != nullptr && AddOnly != true)
		{
			//Change Graphic
			Replace_Ingredient_Graphic(Ingredient.first, Current_Ingredient_PageItem);
		}

		//if we add, it will go through replacing alse thats why we need this boolean
		AddOnly = false;

		//Stop Cycling if there is no shapegroup
		if (Current_Ingredient_PageItem != nullptr) { Current_Ingredient_PageItem = Current_Ingredient_PageItem->Next; }
	}

	//Graphics left over
	////Existing? // Add // Hide
	while (Current_Ingredient_PageItem != nullptr)
	{
		Hide_Ingredient_Graphic(Current_Ingredient_PageItem);
		Current_Ingredient_PageItem = Current_Ingredient_PageItem->Next;
	}
}

void MenuCreator::Add_Ingredient_Graphic(const string Name)
{
	Log::LogString("Adding Ingredient Graphic");
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
	PageItem_Template.BackGroundPadding[PADDING_LEFT]  = 30;
	PageItem_Template.BackGroundPadding[PADDING_RIGHT] = 30;
	PageItem_Template.BackGroundPadding[PADDING_TOP] = 10;
	PageItem_Template.BackGroundPadding[PADDING_BOTTOM] = 10;
	PageItem_Template.DescriptiveData = Name;

	//Page Item
	//Button_Select_Ingredient.LogicalActions[GUI_MOUSELEFT_CLICKED] = Select_Side;
	PageGroupItem PageItem_Ingredient_Graphic(RestaurantBook, &PageItem_Template);
	//PageItem_Ingredient_Graphic.GetData()->PageItemButton = &Button_Select_Side;

	//Text
	TextData_Template.Phrase = Name;
	ShapeGroup_Template.Color = PageCreator::White; // Light Red
	Text Text_Side_Name(RestaurantBook, &ShapeGroup_Template, TextData_Template);

	if (First_Ingredient_Graphic == nullptr)
	{
		First_Ingredient_Graphic = PageItem_Ingredient_Graphic.GetData();
	}
	//Place New Side
	int Spacing = 20;
	if (first_ingredient == true) { Spacing = 100; first_ingredient = false; }
	Log::LogVec4("Vec4 Going in last Add", last_ingredient_edges);
	PageItem_Ingredient_Graphic.PlaceBelow(last_ingredient_edges, MATCH_CENTERS, Spacing);
	last_ingredient_edges = PageItem_Ingredient_Graphic.GetEdgesWithBackGround();

	Text_Add_Ingredient.PlaceBelow(last_ingredient_edges, MATCH_CENTERS, 20);
}

void MenuCreator::Replace_Ingredient_Graphic(string Name, llPageItemData* Ingredient_PageItem) 
{
	Log::LogString("Replace Ingredient Graphic");
	if (Ingredient_PageItem == nullptr) { Log::LogString("replace_ingredent_graphic ERROR:: Ingredient_PageItem nullptr"); return; }

	llShapeGroupData* CurrentShapeGroup = Ingredient_PageItem->ShapeGroup;

	Text Text_Ingredient_Graphic(CurrentShapeGroup);
	Text_Ingredient_Graphic.LoadedBook = RestaurantBook;
	Text_Ingredient_Graphic.llSwitch(CurrentShapeGroup);
	Text_Ingredient_Graphic.SetllText(Name);

	//Place New Side
	int Spacing = 20;
	if (first_ingredient == true) { Spacing = 100; first_ingredient = false; }

	PageGroupItem PageItem_Ingredient_Graphic(Ingredient_PageItem);
	PageItem_Ingredient_Graphic.LoadedBook = RestaurantBook;
	PageItem_Ingredient_Graphic.llSwitch(Ingredient_PageItem);
	PageItem_Ingredient_Graphic.PlaceBelow(last_ingredient_edges, MATCH_CENTERS, Spacing);
	PageItem_Ingredient_Graphic.UnHide();
	Ingredient_PageItem->DescriptiveData = Name; //Attach Key to UI

	last_ingredient_edges = PageItem_Ingredient_Graphic.GetEdgesWithBackGround();

	Text_Add_Ingredient.PlaceBelow(last_ingredient_edges, MATCH_CENTERS, 20);
}

void MenuCreator::Hide_Ingredient_Graphic(llPageItemData* Ingredient_ShapeGroup)
{
	//Set New Name
	PageGroupItem PageItem_Ingredient_Graphic(Ingredient_ShapeGroup);
	PageItem_Ingredient_Graphic.LoadedBook = RestaurantBook;
	PageItem_Ingredient_Graphic.llSwitch(Ingredient_ShapeGroup);
	PageItem_Ingredient_Graphic.Hide();

	//Place New Side
	int Spacing = 20;
	if (first_ingredient == true) { Spacing = 100; first_ingredient = false; }
	PageItem_Ingredient_Graphic.PlaceBelow(last_ingredient_edges, MATCH_CENTERS, Spacing);

	//We are Hiding All
	if (Ingredient_ShapeGroup == First_Ingredient_Graphic)
	{
		Text_Add_Ingredient.PlaceBelow(current_ingredient_edges, MATCH_CENTERS, 100);
	}
}

void MenuCreator::Rearrange_Ingredient_Graphics() {}
//+----------------------------+


void MenuCreator::Empty() {}