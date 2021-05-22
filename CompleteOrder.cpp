#include "CompleteOrder.h"


void CompleteOrder::Prepare(llBookData* Restaurant_POS, ShaderProgram* ShaderProgram, RawTexture* Texture0, RawTexture* Texture1, RawTexture* Texture2)
{
	RestaurantBook = Restaurant_POS;
	//Prepare Submit Order Page for Usage
	CurrentShader = ShaderProgram;

	CurrentTexture0 = Texture0;
	CurrentTexture1 = Texture1;
	CurrentTexture2 = Texture2;
	Page_Complete_Order.llInit(RestaurantBook, CurrentShader, CurrentTexture0, CurrentTexture1, CurrentTexture2);
	CompleteOrderDirectory = RestaurantBook->Page;

	Quad PlaceHolder(RestaurantBook);

	Prepare_Customers();
	Prepare_Dish_Graphics();

	PageGroupItem PageItem_Grid_Template(RestaurantBook);
	TextData HUUUHH;
	HUUUHH.Phrase = "hello";
	llShapeGroupData UHHHUU;
	UHHHUU.Position = { 0.0, 0.0 };
	Text Text_Grid_Template_1(RestaurantBook, &UHHHUU, HUUUHH);
	HUUUHH.Phrase = "there";
	Text Text_Grid_Template_2(RestaurantBook, &UHHHUU, HUUUHH);
	Text_Grid_Template_2.PlaceRight(Text_Grid_Template_1.GetEdges(), MATCH_FLOORS, 10);
	HUUUHH.Phrase = "guy";
	Text Text_Grid_Template_3(RestaurantBook, &UHHHUU, HUUUHH);
	Text_Grid_Template_3.PlaceRight(Text_Grid_Template_2.GetEdges(), MATCH_FLOORS, 10);
	//UHHHUU.Color = PageCreator::Yellow;
	//HUUUHH.Phrase = "This is awesome ";
	//Text Text_Grid_Template_4(RestaurantBook, &UHHHUU, HUUUHH);
	//Text_Grid_Template_4.PlaceBelow(Text_Grid_Template_3.GetEdges(), MATCH_BEGINNINGS, 10);

	//Grid Data
	PageItemGridData First_Grid_DATA;
	First_Grid_DATA.ResultCount = 7;
	First_Grid_DATA.ColumnCount = 3; //Columns = 3
	First_Grid_DATA.RowCount = 2; //Columns = 3
	//First_Grid_DATA.AutoColumns = true;
	First_Grid_DATA.yPadding = 20;

	//Set Position Attributes
	llPageGroupData PageGroup_DATA;
	PageGroup_DATA.Position = { -0.5, 0.5 };
	PageGroup_DATA.InputType = INPUT_LEFT;

	PageItem_Grid_Template.llUpdate();
	Log::LogString("Grid");
	//PageItemGrid First_GRID(RestaurantBook, &PageGroup_DATA, PageItem_Grid_Template.GetData(), First_Grid_DATA);
	//PageItem_Grid_Template.Hide();
	//PageItem_Grid_Template.SetllPosition({-0.5, 0.0}, INPUT_TOP);


	//First_GRID.SetResultCount(5);
	//First_GRID.SetResultCount(40);
	//First_GRID.SetResultCount(12);
	//First_GRID.SetResultCount(28);

	//Log::LogString("Prove");
	//PageGroupItem Prove(PageItem_Grid_Template.GetData());
	//Prove.LoadedBook = RestaurantBook;
	//Prove.SetllPosition({ -0.5, 0.0 }, INPUT_TOP);
	//MasterElement::PrintPageGroupStats(First_GRID.GetData());
}

void CompleteOrder::PrepareContainers(map<string, Section>* Section, map<string, Dish>* Dish, map<string, DishSide>* Side, map<string, Ingredient>* Ingredient, map<string, SameDayOrders>* All_Orders)
{
	All_Customer_Orders = All_Orders;
	All_Sections = Section;
	All_Dishes = Dish;
	All_Sides = Side;
	All_Ingredients = Ingredient;
}

void CompleteOrder::Update(KeyResult& CurrentKeyResult, int CurrentPage)
{
	if (CurrentPage == 3)
	{
		Page_Complete_Order.DrawPage();
	}
}

void CompleteOrder::SetPageDirectory()
{
	RestaurantBook->Page = CompleteOrderDirectory;
}

llPageData* CompleteOrder::GetPageData()
{
	return Page_Complete_Order.GetData();
}


void CompleteOrder::SetOrderDate(const string& OrderDateKey)
{
	Current_Day_Orders = Customer_Order_DataBase[OrderDateKey];

	//Update Customers 
	Update_Customer_Graphics();

	//Erase Condensed Dishes
	All_Ordered_Dishes.clear();
}

void CompleteOrder::Prepare_Customers()
{
	Select_Once = false;
	UnSelect_Once = false;

	//Graphics Setup
	TextData Text_Template;
	Text_Template.Phrase = "Today's Orders:";
	llShapeGroupData ShapeGroup_Template;
	ShapeGroup_Template.Position = { -0.9, 0.8 };

	//Today's Orders (Label)
	Text_Label_Todays_Orders.llInit(RestaurantBook, &ShapeGroup_Template, Text_Template);
	Button_Update_Customers.Add_Mouse_Action(GUI_MOUSELEFT_CLICKED, Update_Customer_Grid);
	Text_Label_Todays_Orders.GetData()->ShapeGroupButton = &Button_Update_Customers;

	//Customer PageGroup
	llPageGroupData PageGroup_Template;
	PageGroup_Customers.llInit(RestaurantBook, &PageGroup_Template);
	DRPageGroup_Customer.Capture(RestaurantBook);
	Current_Day_Orders = Customer_Order_DataBase["2021 4 8"];

	PageGroupItem PlaceHolder(RestaurantBook);

	//Set First Edges
	first_customer_order_edges = Text_Label_Todays_Orders.GetEdges();
	first_dish_edges = Text_Label_Todays_Orders.GetEdges();

	//SelectAllCustomers();
	//Condense_Ordered_Dishes();
	//Print_Condensed_Dishes();

	//Customer Graphics
	//Update_Customer_Graphics();
	Create_Customer_Graphic();
	Create_Customer_Grid();
}

void CompleteOrder::Create_Customer_Graphic()
{
	TextData Text_Template;
	PageItemData PageItem_Template;
	PageItem_Template.Position = {0.0, 0.0};
	llShapeGroupData ShapeGroup_Template;

	PageItem_Customer_Graphic.llInit(RestaurantBook);
	Button_Toggle_Customer.Add_Mouse_Action(GUI_MOUSELEFT_CLICKED, ToggleCustomer);
	PageItem_Customer_Graphic.GetData()->PageItemButton = &Button_Toggle_Customer;

	//Name
	Text_Template.Phrase = "Name";
	Text Text_Name(RestaurantBook, &ShapeGroup_Template, Text_Template);

	//Quantity of items
	Text_Template.Phrase = "(0) Ordered Items";
	Text Text_Item_Quantity(RestaurantBook, &ShapeGroup_Template, Text_Template);
	Text_Item_Quantity.PlaceBelow(Text_Name.GetEdges(), MATCH_BEGINNINGS, 10);

	Log::LogString("Graphic Created");
}

void CompleteOrder::Create_Customer_Grid()
{
	Log::LogString("Creating Customer Grid");
	llPageGroupData PageGroup_Template;
	PageGroup_Template.Position = { -0.7, 0.7 };

	PageItemGridData Grid_Template;
	Grid_Template.ResultCount = 0;
	Grid_Template.RowCount = 1;
	Grid_Template.yPadding = 40;

	Grid_Customers.llInit(RestaurantBook, &PageGroup_Template, PageItem_Customer_Graphic.GetData(), Grid_Template);

}

void CompleteOrder::Update_Customer_Grid()
{
	Log::LogString("Updating Grid");

	int CustomerCount = 0;

	//Replace all graphics
	for (auto kv : Customer_Order_DataBase["2021 4 8"].CustomerOrders)
	{
		CustomerCount++;
	}

	Grid_Customers.SetResultCount(CustomerCount);

	llPageItemData* First_Customer_Graphic = Grid_Customers.GetFirst();

	for (auto kv : Customer_Order_DataBase["2021 4 8"].CustomerOrders)
	{
		Replace_Customer_Graphic(kv.second, First_Customer_Graphic);
		First_Customer_Graphic = First_Customer_Graphic->Next;
	}
}

void CompleteOrder::ToggleCustomer()
{
	Log::LogString("Customer Toggled");
	if (Page_Complete_Order.ElementsHovered.PageItem == nullptr) { Log::LogString("Select Failed");  return; }

	bool Graphic_Selected = Page_Complete_Order.ElementsHovered.PageItem->GraphicSelected;

	if (Graphic_Selected == false)
	{
		SelectCustomer();
		Page_Complete_Order.ElementsHovered.PageItem->GraphicSelected = true;
		return;
	}
	
	UnSelectCustomer();
	Page_Complete_Order.ElementsHovered.PageItem->GraphicSelected = false;
}

void CompleteOrder::SelectCustomer()
{

	//Print 
	Log::LogString(Page_Complete_Order.ElementsHovered.PageItem->DescriptiveData + " Order Selected");

	//Get Customer Last Name From Graphic
	const string Customer_Last_Name = Page_Complete_Order.ElementsHovered.PageItem->DescriptiveData;
	
	//Get The Customer Order
	const CustomerOrder& Customer_Order = Customer_Order_DataBase["2021 4 8"].CustomerOrders[Customer_Last_Name];//Current_Day_Orders.CustomerOrders[Customer_Last_Name];
	
	//Customer Order in the Container
	if (Orders_Selected.find(Customer_Last_Name) == Orders_Selected.end())
	{
		//Add Customer Order
		Orders_Selected[Customer_Last_Name] = Customer_Order;
		//Highlight_Customer_Graphic();
	}
	
	//Display Selected Dishes
	Update_Condensed_Dishes();
	//Update_Dish_Graphics();
	Update_Dish_Grid();
	Print_Condensed_Dishes();

}

void CompleteOrder::UnSelectCustomer()
{
	//if (UnSelect_Once == false)
	//{
		Log::LogString(Page_Complete_Order.ElementsHovered.PageItem->DescriptiveData + " Order UnSelected");

		//Get Name from Element Hovered
		const string Customer_Last_Name = Page_Complete_Order.ElementsHovered.PageItem->DescriptiveData;
		
		//Delete Selected if in there
		if (Orders_Selected.find(Customer_Last_Name) != Orders_Selected.end())
		{
			Orders_Selected.erase(Customer_Last_Name);
			DeHighlight_Customer_Graphic();
		}
		
		//Display Newly Selected Dishes
		Update_Condensed_Dishes();
		Update_Dish_Graphics();
		Print_Condensed_Dishes();
	//}
	//UnSelect_Once = true;
}

void CompleteOrder::SelectAllCustomers()
{
	for (const auto& kv : Current_Day_Orders.CustomerOrders)
	{
		const string Customer_Name = kv.first;
		const CustomerOrder& Customer_Order = kv.second;
		Orders_Selected[Customer_Name] = Customer_Order;
	}
}


int CompleteOrder::GetCustomerItemCount(const CustomerOrder& Order)
{
	int TotalItems = 0;

	for (const auto& kv : Order.OrderedDishes)
	{
		const OrderedDish& CurrentDish = kv.second;

		TotalItems += CurrentDish.Quantity;
	}

	return TotalItems;
}

void CompleteOrder::Highlight_Customer_Graphic()
{
	llPageItemData* PageItem = RestaurantBook->PageItem_Hovered;

	PageGroupItem PageItem_Reference(PageItem);
	PageItem_Reference.LoadedBook = RestaurantBook;
	PageItem_Reference.llSwitch(PageItem);
	PageItem_Reference.HighlightPageItem(PageCreator::Blue);
}

void CompleteOrder::DeHighlight_Customer_Graphic()
{
	llPageItemData* PageItem = RestaurantBook->PageItem_Hovered;

	PageGroupItem PageItem_Reference(PageItem);
	PageItem_Reference.LoadedBook = RestaurantBook;
	PageItem_Reference.llSwitch(PageItem);
	PageItem_Reference.HighlightOff();
}

void CompleteOrder::Update_Complete_Order()
{
	Update_Customer_Graphics();
	MasterElement::PrintPageStats(Page_Complete_Order.GetData());
}

void CompleteOrder::Update_Customer_Graphics()
{
	Current_Day_Orders = Customer_Order_DataBase["2021 4 8"];

	Log::LogString("Complete Order");
	Log::LogString("Updating Customer Order Graphics--------------------------------------------------");
	llPageItemData* Current_Customer_Order_Graphic = First_Customer_Order_Graphic;
	first_customer_order = true;
	last_customer_order_edges = first_customer_order_edges;
	float Order_Total = 0.0;
	bool AddOnly = false;

	//Loop Through Today's Customers
	for (const auto& kv : Current_Day_Orders.CustomerOrders)
	{
		const CustomerOrder& Current_Customer_Order = kv.second;
		Log::LogString("Customer: " + Current_Customer_Order.CustomerDetails.FirstName);
		//New Graphic
		if (Current_Customer_Order_Graphic == nullptr)
		{
			//Create Graphic
			Log::LogString("Adding Customer Graphic");
			Add_Customer_Graphic(Current_Customer_Order);
			AddOnly = true;
		}

		////Existing Graphic
		if (Current_Customer_Order_Graphic != nullptr && AddOnly != true)
		{
			//Change Graphic
			Log::LogString("Replacing Customer Graphic");
			Replace_Customer_Graphic(Current_Customer_Order, Current_Customer_Order_Graphic);
		}

		//if we add, it will go through replacing alse thats why we need this boolean
		AddOnly = false;


		//Go to next graphic if there is one
		if (Current_Customer_Order_Graphic != nullptr) { Current_Customer_Order_Graphic = Current_Customer_Order_Graphic->Next; }

	}


	//Graphics Left Over
	//while (Current_Customer_Order_Graphic != nullptr)
	//{
	//	Log::LogString("Hiding Customer Graphic");
	//	Hide_Customer_Graphic(Current_Customer_Order_Graphic);
	//	Current_Customer_Order_Graphic = Current_Customer_Order_Graphic->Next;
	//}
}


//Functions To Display Orders Based on Current_Day_Orders
void CompleteOrder::Add_Customer_Graphic(const CustomerOrder& Customer_Order_To_Add) 
{
	//DRPageGroup_Customer.LoadUp(RestaurantBook);

	//Text
	TextData TextData_Template;
	TextData_Template.Centered = false;

	//PageItem
	llPageItemData PageItem_Template;
	PageItem_Template.Position = {0.0, 0.0};
	PageItem_Template.Color = { 0.0, 0.5, 1.0, 1.0 };
	PageItem_Template.BackGround = true;
	PageItem_Template.DescriptiveData = Customer_Order_To_Add.CustomerDetails.LastName;
	PageItem_Template.GraphicSelected = false;

	//ShapeGroup
	llShapeGroupData ShapeGroup_Template;
	ShapeGroup_Template.Position = { 0.0, 0.0 };
	ShapeGroup_Template.Color = { 0.0, 1.0, 1.0, 1.0 };
	ShapeGroup_Template.MouseAccess = true;

	//PageGroupItem PlaceHolder(RestaurantBook);
	PageGroupItem PlaceHolder(RestaurantBook, &PageItem_Template);
	Button_Toggle_Customer.Add_Mouse_Action(GUI_MOUSELEFT_CLICKED, ToggleCustomer);
	PlaceHolder.GetData()->PageItemButton = &Button_Toggle_Customer;

	//Customer Full Name
	TextData_Template.Phrase = Customer_Order_To_Add.CustomerDetails.FirstName + " " +  Customer_Order_To_Add.CustomerDetails.LastName;
	Text Ordered_Dish_Section_Name(RestaurantBook, &ShapeGroup_Template, TextData_Template);

	//Customer Items Ordered Quantity
	TextData_Template.Phrase = to_string(GetCustomerItemCount(Customer_Order_To_Add)) + " Ordered Items";
	Text Ordered_Dish_Name(RestaurantBook, &ShapeGroup_Template, TextData_Template);
	Ordered_Dish_Name.PlaceBelow(Ordered_Dish_Section_Name.GetEdges(), MATCH_BEGINNINGS, 10);


	if (First_Customer_Order_Graphic == nullptr)
	{
		First_Customer_Order_Graphic = PlaceHolder.GetData();
	}

	//Temporary Fix
	int AlignmentType = MATCH_CENTERS;
	int Padding = 20;

	//Only the first item has a centered alignment type
	if (first_customer_order == true) 
	{
		AlignmentType = MATCH_BEGINNINGS;
		first_customer_order = false; 

		PlaceHolder.PlaceBelow(last_customer_order_edges, AlignmentType, Padding);
		last_customer_order_edges = PlaceHolder.GetEdgesWithBackGround();
	}
	else
	{
		AlignmentType = MATCH_CENTERS;
		PlaceHolder.PlaceRight(last_customer_order_edges, AlignmentType, Padding);
		last_customer_order_edges = PlaceHolder.GetEdgesWithBackGround();
	}
	MasterElement::PrintPageItemStats(PlaceHolder.GetData());
}

void CompleteOrder::Replace_Customer_Graphic(const CustomerOrder& Customer_Order_To_Replace, llPageItemData* Customer_Order_PageItem)
{
	if (Customer_Order_PageItem == nullptr) { Log::LogString("replace_ordered_dish_graphic ERROR:: ordered_dish_Graphic nullptr"); return; }

	//SetPageDirectory();
	//Prepare Ordered Dish Attribute Graphic Data 
	glm::vec4 last_shapegroup_edges;
	llShapeGroupData* Attribute_Graphic_Data = Customer_Order_PageItem->ShapeGroup;
	Attribute_Graphic_Data = MasterElement::HeadShapeGroup(Attribute_Graphic_Data);

	//Prepare Ordered Dish Attribute Graphics for editing
	Text Ordered_Dish_Graphic_Attribute(Attribute_Graphic_Data);
	Ordered_Dish_Graphic_Attribute.LoadedBook = RestaurantBook;

	//Customer Name
	//Attribute_Graphic_Data = Attribute_Graphic_Data->Next; //FIX THIS
	Ordered_Dish_Graphic_Attribute.llSwitch(Attribute_Graphic_Data);
	Ordered_Dish_Graphic_Attribute.SetllText(Customer_Order_To_Replace.CustomerDetails.FirstName + " " + Customer_Order_To_Replace.CustomerDetails.LastName);
	last_shapegroup_edges = Ordered_Dish_Graphic_Attribute.GetEdgesWithBackGround();

	//Customer Items Quantity
	Attribute_Graphic_Data = Attribute_Graphic_Data->Next;
	Ordered_Dish_Graphic_Attribute.llSwitch(Attribute_Graphic_Data);
	Ordered_Dish_Graphic_Attribute.SetllText(to_string(GetCustomerItemCount(Customer_Order_To_Replace)) + " Items Ordered");
	Ordered_Dish_Graphic_Attribute.PlaceRight(last_shapegroup_edges, MATCH_BEGINNINGS, 10);
	last_shapegroup_edges = Ordered_Dish_Graphic_Attribute.GetEdgesWithBackGround();

	//Prepare Ordered Dish Graphic for editing
	PageGroupItem Ordered_Dish_Graphic(Customer_Order_PageItem);
	Ordered_Dish_Graphic.LoadedBook = RestaurantBook;
	Ordered_Dish_Graphic.llSwitch(Customer_Order_PageItem);
	Ordered_Dish_Graphic.GetData()->DescriptiveData = Customer_Order_To_Replace.CustomerDetails.LastName;

	//int Padding = 20;
	//int AlignmentType;
	//if (first_customer_order == true)
	//{
	//	AlignmentType = MATCH_BEGINNINGS;
	//	first_customer_order = false;
	//
	//	Log::LogString("Yes First");
	//	Ordered_Dish_Graphic.PlaceBelow(last_customer_order_edges, AlignmentType, Padding);
	//	Ordered_Dish_Graphic.UnHide();
	//	last_customer_order_edges = Ordered_Dish_Graphic.GetEdgesWithBackGround();
	//}
	//else
	//{
	//	Log::LogString("Not First");
	//	AlignmentType = MATCH_CENTERS;
	//	Ordered_Dish_Graphic.PlaceRight(last_customer_order_edges, AlignmentType, Padding);
	//	Ordered_Dish_Graphic.UnHide();
	//	last_customer_order_edges = Ordered_Dish_Graphic.GetEdgesWithBackGround();
	//}
}

void CompleteOrder::Hide_Customer_Graphic(llPageItemData* PageItem_Customer_Graphic_Data)
{
	//Set New Name
	PageGroupItem PageItem_Customer_Graphic(PageItem_Customer_Graphic_Data);
	PageItem_Customer_Graphic.LoadedBook = RestaurantBook;
	PageItem_Customer_Graphic.llSwitch(PageItem_Customer_Graphic_Data);
	PageItem_Customer_Graphic.Hide();
	PageItem_Customer_Graphic_Data->DescriptiveData = " ";

}


//Condense Orders Selected
void CompleteOrder::Condense_Ordered_Dishes()
{
	//Get all Ordered Dishes From Every Order Selected
	for (const auto& kv: Orders_Selected)
	{
		const CustomerOrder Order_Selected = kv.second;

		for (auto Dish : Order_Selected.OrderedDishes)
		{
			const string& DishName = Dish.first;
			const OrderedDish& Dish_Ordered = Dish.second;

			//Not in map
			if (All_Ordered_Dishes.find(DishName) == All_Ordered_Dishes.end())
			{
				//Set Quantity
				All_Ordered_Dishes[DishName] = Dish_Ordered.Quantity;
			}
			//in Map
			else
			{
				//Update Quantity
				All_Ordered_Dishes[DishName] += Dish_Ordered.Quantity;
			}
		}
	}
}

void CompleteOrder::Update_Condensed_Dishes()
{
	//Condense Again with a Clean Slate 
	//All_Ordered_Dishes.clear();
	Condense_Ordered_Dishes();
}

void CompleteOrder::Create_Dish_Graphic()
{
	TextData Text_Template;
	PageItemData PageItem_Template;
	PageItem_Template.Position = { 0.0, 0.0 };
	llShapeGroupData ShapeGroup_Template;

	PageItem_Ordered_Dish.llInit(RestaurantBook);

	//Name
	Text_Template.Phrase = "Name";
	Text Text_Name(RestaurantBook, &ShapeGroup_Template, Text_Template);

	//Quantity of items
	Text_Template.Phrase = " 0";
	Text Text_Item_Quantity(RestaurantBook, &ShapeGroup_Template, Text_Template);
	Text_Item_Quantity.PlaceLeft(Text_Name.GetEdges(), MATCH_BEGINNINGS, 10);

	Log::LogString("Graphic Created");
}

void CompleteOrder::Create_Dish_Grid()
{
	Log::LogString("Creating Customer Grid");
	llPageGroupData PageGroup_Template;
	PageGroup_Template.Position = { -0.8, 0.5 };

	PageItemGridData Grid_Template;
	Grid_Template.ResultCount = 0;
	Grid_Template.ColumnCount = 1;
	Grid_Template.yPadding = 40;

	Grid_Dishes.llInit(RestaurantBook, &PageGroup_Template, PageItem_Ordered_Dish.GetData(), Grid_Template);

}

void CompleteOrder::Update_Dish_Grid()
{
	Log::LogString("Updating Grid");

	int DishCount = 0;

	//Replace all graphics
	for (auto kv : All_Ordered_Dishes)
	{
		DishCount++;
	}

	Grid_Dishes.SetResultCount(DishCount);

	//llPageItemData* First_Dish_Graphic = Grid_Dishes.GetFirst();
	//
	//for (auto kv : All_Ordered_Dishes)
	//{
	//	Replace_Dish_Graphic(kv.first, kv.second, First_Dish_Graphic);
	//	First_Dish_Graphic = First_Dish_Graphic->Next;
	//}
}


void CompleteOrder::Print_Condensed_Dishes()
{
	Log::LogString("Printing Condensed Dishes");

	for (auto CondensedDish : All_Ordered_Dishes)
	{
		Log::LogString(CondensedDish.first + " Quantity:" + to_string(CondensedDish.second));
	}
}

void CompleteOrder::Prepare_Dish_Graphics()
{
	llPageGroupData PageGroup_Template;
	PageGroup_Dish_Display.llInit(RestaurantBook, &PageGroup_Template);
	DRPageGroup_Dish.Capture(RestaurantBook);

	//Condensed Dish Graphics
	//Update_Dish_Graphics();
	Create_Dish_Graphic();
	Create_Dish_Grid();
}

void CompleteOrder::Update_Dish_Graphics()
{
	Log::LogString("Updating Dish Graphics------------------------------------------");
	llPageItemData* Current_Dish_PageItem = First_Dish_Graphic;
	first_dish = true;
	last_dish_edges = first_dish_edges;
	bool AddOnly = false;

	//Use the "Current_Section" to loop through it's dishes
	for (const auto& kv : All_Ordered_Dishes)
	{
		const string& DishName = kv.first;
		const int& DishQuantity = kv.second;

		//New Graphic
		if (Current_Dish_PageItem == nullptr)
		{
			//Create Graphic
			Add_Dish_Graphic(DishName, DishQuantity);
			Log::LogString("Adding Dish Graphic-------------------------------------");
			AddOnly = true;
		}

		////Existing Graphic
		if (Current_Dish_PageItem != nullptr && AddOnly != true)
		{
			//Change Graphic
			Replace_Dish_Graphic(DishName, DishQuantity, Current_Dish_PageItem);
			Log::LogString("Replacing-------------------------------------------------");
		}

		//if we add, it will go through replacing alse thats why we need this boolean
		AddOnly = false;

		//Stop Cycling if there is no shapegroup
		if (Current_Dish_PageItem != nullptr) { Current_Dish_PageItem = Current_Dish_PageItem->Next; }
	}

	//Graphics left over
	////Existing? // Add // Hide
	while (Current_Dish_PageItem != nullptr)
	{
		Hide_Dish_Graphic(Current_Dish_PageItem);
		Current_Dish_PageItem = Current_Dish_PageItem->Next;
	}
}

void CompleteOrder::Add_Dish_Graphic(const string& Name, const int& Quantity)
{
	DRPageGroup_Dish.LoadUp(RestaurantBook);

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
	//PageItem_Template.BackGroundColor = SubmitOrder::DarkPurple; //Dark Red
	//PageItem_Template.BackGroundPadding[PADDING_LEFT] = 30;
	//PageItem_Template.BackGroundPadding[PADDING_RIGHT] = 30;
	//PageItem_Template.BackGroundPadding[PADDING_TOP] = 10;
	//PageItem_Template.BackGroundPadding[PADDING_BOTTOM] = 10;
	//PageItem_Template.DescriptiveData = Name; //Attach Key to UI

	//Page Item
	PageGroupItem PageItem_Dish_Graphic(RestaurantBook, &PageItem_Template);
	//PageItem_Dish_Graphic.GetData()->PageItemButton = &Button_Select_Dish;

	//Dish Name
	TextData_Template.Phrase = to_string(Quantity);
	ShapeGroup_Template.Color = PageCreator::Yellow; // Light Red
	Text Text_Dish_Name(RestaurantBook, &ShapeGroup_Template, TextData_Template);

	//Dish Quantity
	TextData_Template.Phrase = Name;
	ShapeGroup_Template.Color = PageCreator::White; // Light Red
	Text Text_Dish_Quantity(RestaurantBook, &ShapeGroup_Template, TextData_Template);
	Text_Dish_Quantity.PlaceRight(Text_Dish_Name.GetEdges(), MATCH_FLOORS, 10);

	if (First_Dish_Graphic == nullptr)
	{
		First_Dish_Graphic = PageItem_Dish_Graphic.GetData();
	}

	//Place New Side
	int Spacing = 20;
	if (first_dish == true) { Spacing = 200; first_dish = false; }
	PageItem_Dish_Graphic.PlaceBelow(last_dish_edges, MATCH_BEGINNINGS, Spacing);
	last_dish_edges = PageItem_Dish_Graphic.GetEdgesWithBackGround();

}

//Can't Delete Right Now so we will have to hide
void CompleteOrder::Replace_Dish_Graphic(string Name, const int& Quantity, llPageItemData* Dish_PageItem)
{
	if (Dish_PageItem == nullptr) { Log::LogString("replace_dish_graphic ERROR:: Dish_PageItem nullptr"); return; }

	glm::vec4 CurrentEdges;
	llShapeGroupData* CurrentShapeGroup = Dish_PageItem->ShapeGroup;

	//Dish Name
	Text Dish_Graphic_Reference(CurrentShapeGroup);
	Dish_Graphic_Reference.LoadedBook = RestaurantBook;
	Dish_Graphic_Reference.llSwitch(CurrentShapeGroup);
	Dish_Graphic_Reference.SetllText(to_string(Quantity));
	//CurrentEdges = Dish_Graphic_Reference.GetEdges();

	//Dish Quantity
	CurrentShapeGroup = CurrentShapeGroup->Next;
	Dish_Graphic_Reference.llSwitch(CurrentShapeGroup);
	Dish_Graphic_Reference.SetllText(Name);
	Dish_Graphic_Reference.PlaceRight(CurrentEdges, MATCH_FLOORS);

	//Place New Side
	//int Spacing = 20;
	//if (first_dish == true) { Spacing = 200; first_dish = false; }

	//PageGroupItem PageItem_Dish_Graphic(Dish_PageItem);
	//PageItem_Dish_Graphic.LoadedBook = RestaurantBook;
	//PageItem_Dish_Graphic.llSwitch(Dish_PageItem);
	//PageItem_Dish_Graphic.PlaceBelow(last_dish_edges, MATCH_BEGINNINGS, Spacing);
	//PageItem_Dish_Graphic.UnHide();
	Dish_PageItem->DescriptiveData = Name; //Attach Key to UI

	//last_dish_edges = PageItem_Dish_Graphic.GetEdgesWithBackGround();

}


void CompleteOrder::Hide_Dish_Graphic(llPageItemData* Dish_PageItem)
{
	//Set New Name
	PageGroupItem PageItem_Dish_Graphic(Dish_PageItem);
	PageItem_Dish_Graphic.LoadedBook = RestaurantBook;
	PageItem_Dish_Graphic.llSwitch(Dish_PageItem);
	PageItem_Dish_Graphic.Hide();
	Dish_PageItem->DescriptiveData = " ";

	//Place New Side
	int Spacing = 20;
	if (first_dish == true) { Spacing = 100; first_dish = false; }
	PageItem_Dish_Graphic.PlaceBelow(last_dish_edges, MATCH_CENTERS, Spacing);

}

