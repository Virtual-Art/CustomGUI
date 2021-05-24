#include "ApplicationMenu.h"

void ApplicationMenu::Prepare(llBookData* Restaurant_POS, ShaderProgram* ShaderProgram, RawTexture* Texture0, RawTexture* Texture1, RawTexture* Texture2)
{
	RestaurantBook = Restaurant_POS;

	Page_ApplicationMenu.llInit(Restaurant_POS, ShaderProgram, Texture0, Texture1, Texture2);
	BD_ApplicationMenu.Capture(Restaurant_POS);
	CurrentPage = PAGE_COMPLETE_ORDER;

	CreatePageSelector();
}

int ApplicationMenu::Update()
{
	//BD_ApplicationMenu.LoadUp(RestaurantBook);
	//RestaurantBook->Page = Page_ApplicationMenu.GetData();
	Page_ApplicationMenu.DrawPage();
	//MasterElement::FindElement(RestaurantBook, LEVEL_SHAPEGROUP, ElementsHovered);
	return CurrentPage;
}

void ApplicationMenu::CreatePageSelector()
{
	SelectorData Selector_Template;
	llPageItemData PageItem_Template;
	PageItem_Template.Position = { -0.4, 0.95 };
	Selector_Template.ColumnsRows = { 4, 1 };
	Selector_Template.BackGroundColor = {0.52, 0.41, 0.0, 1.0}; //Amber Color
	Selector_Template.BackGroundPadding = {15, 15, 15, 15}; 
	Selector_Template.Selector[0] = "Submit Order";
	Selector_Template.Selector[1] = "Menu Creator";
	Selector_Template.Selector[2] = "Ingredient List";
	Selector_Template.Selector[3] = "Complete Order";
	Selector_Template.Key[0] = PAGE_SUBMIT_ORDER;
	Selector_Template.Key[1] = PAGE_MENU_CREATOR;
	Selector_Template.Key[2] = PAGE_INGREDIENT_LIST;
	Selector_Template.Key[3] = PAGE_COMPLETE_ORDER;

	Selector Selector_Menu(RestaurantBook, &PageItem_Template, Selector_Template);
	//Button_Set_Current_Page.LogicalActions[GUI_MOUSELEFT_CLICKED] = Select_Page;
	Button_Set_Current_Page.Add_Mouse_Action(GUI_MOUSELEFT_CLICKED, Select_Page);
	Selector_Menu.SetButton(&Button_Set_Current_Page);

	//Setup Default Page to Highlight
	llShapeGroupData* First_Selector_ShapeGroup = Selector_Menu.GetData()->ShapeGroup;
	First_Selector_ShapeGroup = MasterElement::HeadShapeGroup(First_Selector_ShapeGroup);
	Highlight_Page_Selector(First_Selector_ShapeGroup);

}


void ApplicationMenu::Highlight_Page_Selector(llShapeGroupData* ShapeGroup_Section_Graphic)
{
	//Validation & No Graphic Previously Selected 
	if (ShapeGroup_Section_Graphic == nullptr) { Log::LogString("Highlight Section Failed"); return; }
	if (ShapeGroup_Page_Graphic_Selected == nullptr) { ShapeGroup_Page_Graphic_Selected = ShapeGroup_Section_Graphic; }

	//Prepare Section_Graphic for Editing
	ShapeGroup Section_Graphic(ShapeGroup_Section_Graphic);
	Section_Graphic.LoadedBook = RestaurantBook;

	//De-Highlight Previous Graphic Selected
	Section_Graphic.llSwitch(ShapeGroup_Page_Graphic_Selected);
	Section_Graphic.SetBackGroundColor(Page_Color);

	//Highlight Graphic Selected
	Section_Graphic.llSwitch(ShapeGroup_Section_Graphic);
	Section_Graphic.SetBackGroundColor(Page_Highlight_Color);

	//Set New Graphic_Selected
	ShapeGroup_Page_Graphic_Selected = ShapeGroup_Section_Graphic;
}

void ApplicationMenu::Select_Page()
{
	
	CurrentPage = Page_ApplicationMenu.ElementsHovered.ShapeGroup->Key;
	llShapeGroupData* ShapeGroup_Hovered = Page_ApplicationMenu.ElementsHovered.ShapeGroup;
	Highlight_Page_Selector(ShapeGroup_Hovered);

}