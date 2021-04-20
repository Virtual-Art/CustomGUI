#include "ApplicationMenu.h"

void ApplicationMenu::Prepare(llBookData* Restaurant_POS, ShaderProgram* ShaderProgram, RawTexture* Texture0, RawTexture* Texture1, RawTexture* Texture2)
{
	RestaurantBook = Restaurant_POS;

	Page_ApplicationMenu.llInit(Restaurant_POS, ShaderProgram, Texture0, Texture1, Texture2);
	BD_ApplicationMenu.Capture(Restaurant_POS);
	CurrentPage = PAGE_SUBMIT_ORDER;

	CreateSelectorMenu();
}

int ApplicationMenu::Update()
{
	//BD_ApplicationMenu.LoadUp(RestaurantBook);
	RestaurantBook->Page = Page_ApplicationMenu.GetData();
	MasterElement::FindElement(RestaurantBook, LEVEL_SHAPEGROUP, ElementsHovered);
	Page_ApplicationMenu.DrawPage();
	return CurrentPage;
}

void ApplicationMenu::CreateSelectorMenu()
{
	SelectorData Selector_Template;
	llPageItemData PageItem_Template;
	PageItem_Template.Position = { 0.3, 0.95 };
	Selector_Template.ColumnsRows = { 3, 1 };
	Selector_Template.Selector[0] = "Submit Order";
	Selector_Template.Selector[1] = "Menu Creator";
	Selector_Template.Selector[2] = "Ingredient List";
	Selector_Template.Key[0] = PAGE_SUBMIT_ORDER;
	Selector_Template.Key[1] = PAGE_MENU_CREATOR;
	Selector_Template.Key[2] = PAGE_INGREDIENT_LIST;

	Selector Selector_Menu(RestaurantBook, &PageItem_Template, Selector_Template);
	Button_Set_Current_Page.LogicalActions[GUI_MOUSELEFT_CLICKED] = SetCurrentPage;
	Selector_Menu.SetButton(&Button_Set_Current_Page);
}
void ApplicationMenu::SetCurrentPage()
{
	CurrentPage = ElementsHovered.ShapeGroup->Key;
	Log::LogInt("Key", CurrentPage);
}