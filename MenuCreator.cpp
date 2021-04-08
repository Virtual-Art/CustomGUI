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
	ShapeGroup_Template.Position = { -0.8, 0.8 };
	ShapeGroup_Template.BackGround = true;
	ShapeGroup_Template.BackGroundPadding[PADDING_LEFT] = 100;
	ShapeGroup_Template.BackGroundPadding[PADDING_RIGHT] = 100;
	ShapeGroup_Template.BackGroundPadding[PADDING_TOP] = 20;
	ShapeGroup_Template.BackGroundPadding[PADDING_BOTTOM] = 950;
	ShapeGroup_Template.BackGroundPlacementType = PLACEMENT_BELOW;
	ShapeGroup_Template.BackGroundMatchType = MATCH_CENTERS;
	ShapeGroup_Template.BackGroundColor = {0.1, 0.1, 1.0, 1.0}; //Dark Blue
	ShapeGroup_Template.Color = SubmitOrder::Pink;
	Text_Label_Section.llInit(RestaurantBook, &ShapeGroup_Template, TextData_Template);
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
	ShapeGroup_Template.Color = SubmitOrder::Pink;
	Text_Label_Dish.llInit(RestaurantBook, &ShapeGroup_Template, TextData_Template);
	Text_Label_Dish.PlaceRight(Text_Label_Section.GetEdges(), MATCH_CEILINGS, 225);
	Text_Label_Dish.CopyBackGround(Text_Label_Section.GetData());
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
	Text_Label_Side.PlaceRight(Text_Label_Dish.GetEdges(), MATCH_CEILINGS, 250);
	Text_Label_Side.CopyBackGround(Text_Label_Section.GetData());

	
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
	PageItem_Template.BackGroundPadding[PADDING_LEFT]   = 20;
	PageItem_Template.BackGroundPadding[PADDING_RIGHT]  = 60;
	PageItem_Template.BackGroundPadding[PADDING_TOP]    = 40;
	PageItem_Template.BackGroundPadding[PADDING_BOTTOM] = 200;
	PageItem_Template.BackGroundColor = SubmitOrder::DarkPurple; 
	PageItem_Template.Position = { 0.1, -0.1 };
	Printer_Side_Name.llInit(RestaurantBook, &PageItem_Template, NumberPrinter_Template);

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
	Printer_Cost.PlaceBelow(Printer_Side_Name.GetEdges(), MATCH_BEGINNINGS, 40);

	PageGroup_Side_Filler.SetPosition({0.18, -0.5});
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
	Text_Label_Ingredient.PlaceRight(Text_Label_Side.GetEdges(), MATCH_CEILINGS, 225);
	Text_Label_Ingredient.CopyBackGround(Text_Label_Section.GetData());
}
void MenuCreator::Add_Ingredient() {}
void MenuCreator::Submit_Ingredient() {}
void MenuCreator::Update_Ingredient_Graphics() {}
void MenuCreator::Add_Ingredient_Graphic() {}
void MenuCreator::Remove_Ingredient_Graphic() {}
void MenuCreator::Rearrange_Ingredient_Graphics() {}
//+----------------------------+


