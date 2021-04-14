#include "MenuCreator.h"

//Menu Creator
//+----------------------------+
void MenuCreator::Prepare_MenuCreator(llBookData* Restaurant_POS, ShaderProgram* ShaderProgram, RawTexture* Texture0, RawTexture* Texture1, RawTexture* Texture2)
{
	RestaurantBook = Restaurant_POS;
	CurrentShader = ShaderProgram;
	Page_MenuCreator.llInit(RestaurantBook, CurrentShader, Texture0, Texture1, Texture2);
	Prepare_Section();
	Prepare_Dish();
	Prepare_Side();
	Prepare_Side_Filler();
	Prepare_Ingredient();
}

void MenuCreator::Update()
{
	Page_MenuCreator.DrawPage();
	BookDirectory Random;
	//MasterElement::FindElement(RestaurantBook, LEVEL_PAGEITEM, Random);
	//PageGroup_Side_Filler.SetPosition({ MouseManager::xPos, MouseManager::yPos});
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
	Text_Add_Section.llInit(RestaurantBook, &ShapeGroup_Template, TextData_Template);
	Text_Add_Section.PlaceBelow(Text_Label_Section.GetEdges(), MATCH_CENTERS, 100);
}


void MenuCreator::Add_Section() {}
void MenuCreator::Submit_Section() {}
void MenuCreator::Update_Section_Graphics() {}
void MenuCreator::Add_Section_Graphic() {}
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
	Text_Add_Dish.llInit(RestaurantBook, &ShapeGroup_Template, TextData_Template);
	Text_Add_Dish.PlaceBelow(Text_Label_Dish.GetEdges(), MATCH_CENTERS, 100);
}

void MenuCreator::Add_Dish() {}
void MenuCreator::Submit_Dish() {}
void MenuCreator::Update_Dish_Graphics() {}
void MenuCreator::Add_Dish_Graphic() {}
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
	Text_Add_Side.llInit(RestaurantBook, &ShapeGroup_Template, TextData_Template);
	Text_Add_Side.PlaceBelow(Text_Label_Side.GetEdges(), MATCH_CENTERS, 100);
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
	NumberPrinter_Template.String = &New_Dish.Name;
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
	Log::LogString("SETTING NAME 1st---------------------------------------------------------------------------------");
	Printer_Side_Name.llInit(RestaurantBook, &PageItem_Template, NumberPrinter_Template);
	Log::LogString("SETTING NAME 2nd---------------------------------------------------------------------------------");


	//Cost
	NumberPrinter_Template.AnswerFontSize = 12;
	NumberPrinter_Template.Type = TYPE_FLOAT;
	NumberPrinter_Template.Float = &New_Dish.Cost;
	NumberPrinter_Template.Below = true;
	NumberPrinter_Template.DollarSign = true;
	NumberPrinter_Template.Description = "Cost";
	NumberPrinter_Template.AnswerColor = SubmitOrder::Pink;
	PageItem_Template.BackGround = false;
	Log::LogString("SETTING COST 1st---------------------------------------------------------------------------------");
	Printer_Cost.llInit(RestaurantBook, &PageItem_Template, NumberPrinter_Template);
	Log::LogString("SETTING COST 2nd---------------------------------------------------------------------------------");
	Printer_Cost.PlaceBelow(Printer_Side_Name.GetEdges(), MATCH_BEGINNINGS, 40);
	Log::LogString("SETTING COST 3rd---------------------------------------------------------------------------------");
	//Log::LogString("BETWEEN CREATION 2nd");

	PageGroupItem Filler(RestaurantBook);

	//////Submit
	TextData_Template.Phrase = "Submit";
	ShapeGroup_Template.BackGround = true;
	ShapeGroup_Template.BackGroundPadding[PADDING_LEFT] = 40;
	ShapeGroup_Template.BackGroundPadding[PADDING_RIGHT] = 40;
	ShapeGroup_Template.BackGroundPadding[PADDING_TOP] = 20;
	ShapeGroup_Template.BackGroundPadding[PADDING_BOTTOM] = 20;
	ShapeGroup_Template.BackGroundColor = SubmitOrder::DarkPurple;
	ShapeGroup_Template.Color = PageCreator::White;
	Log::LogString("BETWEEN TEXT SUBMIT 1st");
	Text_Submit_Dish.llInit(RestaurantBook, &ShapeGroup_Template, TextData_Template);
	Log::LogString("BETWEEN TEXT SUBMIT 2nd");
	Text_Submit_Dish.PlaceBelow(Printer_Side_Name.GetEdgesWithBackGround(), MATCH_CENTERS, 20);
	Log::LogString("BETWEEN TEXT SUBMIT 3rd-------------------------------------------------------------------------------------------------");


	//glm::vec4 useless = { Printer_Cost.GetData()->Left, Printer_Cost.GetData()->Right, Printer_Cost.GetData()->Top, Printer_Cost.GetData()->Bottom };
	//Log::LogVec4("Left, Right, Top, Bottom", useless);

	//Log::LogFloat("Difference", Printer_Cost.GetData()->Position[X_AXIS] - Printer_Cost.GetData()->Right);

	//Printer_Cost.SetllPosition({ -0.7, 0.0 });

	//useless = { Printer_Cost.GetData()->Left, Printer_Cost.GetData()->Right, Printer_Cost.GetData()->Top, Printer_Cost.GetData()->Bottom };
	//Log::LogVec4("Left, Right, Top, Bottom", useless);

	//PageGroupItem Reference_PageItem(Printer_Cost.GetData());
	//Reference_PageItem.LoadedBook = RestaurantBook;
	//Reference_PageItem.SetllPosition({-0.7, 0.0}, INPUT_TOP); //Not Working with extra

	//PageGroup_Side_Filler.llUpdate();
	//Log::LogString("This is where i set Position");
	PageGroup_Side_Filler.PlaceRight(Text_Add_Dish.GetEdgesWithBackGround(), MATCH_CEILINGS, 10);
	
	//IT WORKS!!!!
	
}

void MenuCreator::Add_Side() {}
void MenuCreator::Submit_Side() {}
void MenuCreator::Update_Side_Graphics() {}
void MenuCreator::Add_Side_Graphic() {}
void MenuCreator::Remove_Side_Graphic() {}
void MenuCreator::Rearrange_Side_Graphics() {}
//+----------------------------+
	 
	 
	 
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
}
void MenuCreator::Add_Ingredient() {}
void MenuCreator::Submit_Ingredient() {}
void MenuCreator::Update_Ingredient_Graphics() {}
void MenuCreator::Add_Ingredient_Graphic() {}
void MenuCreator::Remove_Ingredient_Graphic() {}
void MenuCreator::Rearrange_Ingredient_Graphics() {}
//+----------------------------+


