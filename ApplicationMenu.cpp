#include "ApplicationMenu.h"

void ApplicationMenu::Prepare(llBookData* Restaurant_POS, ShaderProgram* ShaderProgram, RawTexture* Texture00, RawTexture* Texture01, RawTexture* Texture02)
{
	RestaurantBook = Restaurant_POS;
	CurrentShader = ShaderProgram;

	Texture0 = Texture00;
	Texture1 = Texture01;
	Texture2 = Texture02;

	Page_ApplicationMenu.llPageInit(Restaurant_POS, ShaderProgram, Texture0, Texture1, Texture2);
	BD_ApplicationMenu.Capture(Restaurant_POS);
	CurrentPage = PAGE_COMPLETE_ORDER;

	CreatePageSelector();
	CreateCustomerSelect();
}

void ApplicationMenu::PrepareContainers(map<string, Section>* Section, map<string, Dish>* Dish, map<string, DishSide>* Side, map<string, Ingredient>* Ingredient, map<string, SameDayOrders>* All_Orders)
{
	All_Customer_Orders = All_Orders;
	All_Sections = Section;
	All_Dishes = Dish;
	All_Sides = Side;
	All_Ingredients = Ingredient;
}

int ApplicationMenu::Update()
{
	//BD_ApplicationMenu.LoadUp(RestaurantBook);
	//RestaurantBook->Page = Page_ApplicationMenu.GetData();
	Page_ApplicationMenu.DrawPage();
	//MasterElement::FindElement(RestaurantBook, LEVEL_SHAPEGROUP, ElementsHovered);
	PageGroupGrid_All_Orders.SetllPosition({ MouseManager::xPos, (1 - (MouseManager::yPos - 0.4)) }, PageCreator::OnlyY);

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

void ApplicationMenu::CreateCustomerGraphic()
{
	TextData Customer_Data;
	llShapeGroupData Graphic_Data;
	Graphic_Data.Position = { 0.0, 0.7 };
	int GraphicSpacing = 10;
	PageItem_Customer_Graphic.llInit(RestaurantBook);

	//Name
	Customer_Data.Phrase = "Name";
	Text Name(RestaurantBook, &Graphic_Data, Customer_Data);

	// # of Items
	Customer_Data.Phrase = "0 Items Ordered";
	Text NumberItems(RestaurantBook, &Graphic_Data, Customer_Data);
	NumberItems.PlaceBelow(Name.GetEdges(), MATCH_BEGINNINGS, GraphicSpacing);

	//Address
	Customer_Data.Phrase = "Address";
	Text Address(RestaurantBook, &Graphic_Data, Customer_Data);
	Address.PlaceBelow(NumberItems.GetEdges(), MATCH_BEGINNINGS, GraphicSpacing);

	// Order Total
	Customer_Data.Phrase = "$0";
	Graphic_Data.Color = PageCreator::Green;
	Text OrderTotal(RestaurantBook, &Graphic_Data, Customer_Data);
	OrderTotal.PlaceBelow(Address.GetEdges(), MATCH_BEGINNINGS, GraphicSpacing);
}


void ApplicationMenu::CreateSameDayCustomerGraphics()
{
	PageItemGridData ItemGrid_Basic_Customer;
	ItemGrid_Basic_Customer.RowCount = 1;
	ItemGrid_Basic_Customer.ResultCount = 1; //3 Page Items Created
	ItemGrid_Basic_Customer.xPadding = 90;
	ItemGrid_Basic_Customer.yPadding = 40;
	ItemGrid_Basic_Customer.Description = "Date";
	ItemGrid_Basic_Customer.DescriptionColor = SubmitOrder::Pink;
	ItemGrid_Basic_Customer.DescriptionyPadding = 70;
	llPageGroupData PageGroup_Basic_Customer;
	PageGroup_Basic_Customer.Position = { -0.7, 0.8 };
	Log::LogString("---------------------Creating Same Day Order PageGroup--------------------");
	PageItemGrid_Orders_By_Date.llInit(RestaurantBook, &PageGroup_Basic_Customer, PageItem_Customer_Graphic.GetData(), ItemGrid_Basic_Customer);
}

void ApplicationMenu::CreateCustomerSelect()
{
	CreateCustomerGraphic();
	CreateSameDayCustomerGraphics();

	PageGroupGridData GroupGrid_BasicCustomer;
	GroupGrid_BasicCustomer.InputType = INPUT_LEFT;
	GroupGrid_BasicCustomer.Position = { -0.7, 0.7 };
	GroupGrid_BasicCustomer.ColumnCount = 1;
	GroupGrid_BasicCustomer.ResultCount = 2;
	GroupGrid_BasicCustomer.yPadding = 100;
	PageGroupGrid_All_Orders.llInit(RestaurantBook, Page_ApplicationMenu.GetData(), PageItemGrid_Orders_By_Date.GetData(), GroupGrid_BasicCustomer, CurrentShader, Texture0, Texture1, Texture2);

	UpdateCustomerSelect();
}


void ApplicationMenu::UpdateCustomerSelect()
{
	Log::LogString("---------------Updating Customer DataBase----------------");

	Log::LogInt("Number Of Dates: ", Customer_Order_DataBase.size());

	//Set Count
	PageGroupGrid_All_Orders.SetResultCount(Customer_Order_DataBase.size());
	llPageGroupData* CurrentPageGroup = PageGroupGrid_All_Orders.GetFirst();

	//Replace
	for (auto kv : Customer_Order_DataBase)
	{
		const SameDayOrders& CurrentDate =  kv.second;

		SetSameDayCustomerGraphic(CurrentDate, CurrentPageGroup);

		if (CurrentPageGroup != nullptr)
		{
			CurrentPageGroup = CurrentPageGroup->Next;
		}
	}
}

void ApplicationMenu::SetSameDayCustomerGraphic(const SameDayOrders& CurrentDate, llPageGroupData* CurrentPageGroup)
{
	if (CurrentPageGroup == nullptr) { Log::LogString("SetSameDataCustomerGraphic Failed:: null PageGroup"); return; }

	Log::LogString("-----------------------Setting " + CurrentDate.Day + " --------------------------");

	Log::LogInt("Number Of Orders: ", CurrentDate.CustomerOrders.size());

	PageItemGrid_Orders_By_Date.llSwitch(CurrentPageGroup);
	PageItemGrid_Orders_By_Date.SetResultCount(CurrentDate.CustomerOrders.size());
	PageItemGrid_Orders_By_Date.SetDescription(CurrentDate.Day);
	llPageItemData* CurrentPageItem = PageItemGrid_Orders_By_Date.GetFirst();

	//Replace
	for (auto kv : CurrentDate.CustomerOrders)
	{
		const CustomerOrder& CurrentOrder = kv.second;

		SetCustomerGraphic(CurrentOrder, CurrentPageItem);

		if (CurrentPageItem != nullptr)
		{
			CurrentPageItem = CurrentPageItem->Next;
		}
	}
}

void ApplicationMenu::SetCustomerGraphic(const CustomerOrder& CurrentOrder, llPageItemData* CurrentPageItem)
{

	//Validation
	if (CurrentPageItem == nullptr) { Log::LogString("SetCustomerGraphicFailed:: null PageItem"); return; }
	Log::LogString("------------Setting Customer-----------");
	
	//Setup 
	llShapeGroupData* CurrentShapeGroup = CurrentPageItem->ShapeGroup;
	Text CustomerData(CurrentShapeGroup);
	CustomerData.LoadedBook = RestaurantBook;
	glm::vec4 Last_Edges;
	int GraphicSpacing = 10;
	
	//Name
	CustomerData.llSwitch(CurrentShapeGroup);
	CustomerData.SetllText(CurrentOrder.CustomerDetails.FirstName + " " + CurrentOrder.CustomerDetails.LastName);
	Last_Edges = CustomerData.GetEdgesWithBackGround();
	
	// # of Items
	CurrentShapeGroup = CurrentShapeGroup->Next;
	CustomerData.llSwitch(CurrentShapeGroup);
	CustomerData.SetllText(to_string(CurrentOrder.OrderedDishes.size()));
	CustomerData.PlaceBelow(Last_Edges, MATCH_BEGINNINGS, GraphicSpacing);
	Last_Edges = CustomerData.GetEdgesWithBackGround();
	
	//Address
	CurrentShapeGroup = CurrentShapeGroup->Next;
	CustomerData.llSwitch(CurrentShapeGroup);
	CustomerData.SetllText(CurrentOrder.CustomerDetails.Address);
	CustomerData.PlaceBelow(Last_Edges, MATCH_BEGINNINGS, GraphicSpacing);
	Last_Edges = CustomerData.GetEdgesWithBackGround();
	
	// Order Total
	CurrentShapeGroup = CurrentShapeGroup->Next;
	CustomerData.llSwitch(CurrentShapeGroup);
	CustomerData.SetllText(to_string(CurrentOrder.Total));
	CustomerData.PlaceBelow(Last_Edges, MATCH_BEGINNINGS, GraphicSpacing);
	Last_Edges = CustomerData.GetEdgesWithBackGround();

}