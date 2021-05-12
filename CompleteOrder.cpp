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

	SubmitOrderDirectory = RestaurantBook->Page;

	Quad PlaceHolder(RestaurantBook);

	Prepare_Customer_Orders();
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
	if (CurrentPage != 3) { return; }
	Page_Complete_Order.DrawPage();
}




void CompleteOrder::Prepare_Customer_Orders()
{
	Log::LogString("Preparing Customer Orders");
	Current_Day_Orders = Customer_Order_DataBase["2021 04 27"];

	TextData Text_Template;
	Text_Template.Phrase = "Today's Orders:";
	llShapeGroupData ShapeGroup_Template;
	ShapeGroup_Template.Position = { -0.9, 0.8 };

	Text_Label_Todays_Orders.llInit(RestaurantBook, &ShapeGroup_Template, Text_Template);
	first_customer_order_edges = Text_Label_Todays_Orders.GetEdges();

	Update_Customer_Graphics();

	SelectAllCustomers();
	Condense_Ordered_Dishes();
	Print_Condensed_Dishes();
}

void CompleteOrder::ToggleCustomer()
{
	bool Graphic_Selected = true; // ElementsHovered.PageItem.GraphicSelected;

	if (Graphic_Selected == false)
	{
		SelectCustomer();
		return;
	}

	UnSelectCustomer();
}

void CompleteOrder::SelectCustomer()
{
	//Get Name from Element Hovered
	const string Customer_Name = "Sara";
	const CustomerOrder& Customer_Order = Current_Day_Orders.CustomerOrders[Customer_Name];
	Orders_Selected[Customer_Name] = Customer_Order;
}

void CompleteOrder::UnSelectCustomer()
{
	//Get Name from Element Hovered
	const string Customer_Name = "Sara";
	Orders_Selected.erase(Customer_Name);
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

void CompleteOrder::Update_Customer_Graphics()
{
	Log::LogString("Inside Update");
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
		Log::LogString("Order For: " + Current_Customer_Order.CustomerDetails.FirstName);
		//New Graphic
		if (Current_Customer_Order_Graphic == nullptr)
		{
			//Create Graphic
			Log::LogString("Adding Ordered Dish Graphic");
			Add_Customer_Graphic(Current_Customer_Order);
			AddOnly = true;
		}

		////Existing Graphic
		if (Current_Customer_Order_Graphic != nullptr && AddOnly != true)
		{
			//Change Graphic
			Log::LogString("Replacing Ordered Dish Graphic");
			Replace_Customer_Graphic(Current_Customer_Order, Current_Customer_Order_Graphic);
		}

		//if we add, it will go through replacing alse thats why we need this boolean
		AddOnly = false;


		//Go to next graphic if there is one
		if (Current_Customer_Order_Graphic != nullptr) { Current_Customer_Order_Graphic = Current_Customer_Order_Graphic->Next; }

	}


	//Graphics Left Over
	while (Current_Customer_Order_Graphic != nullptr)
	{
		Log::LogString("Hiding Customer Order Graphic");
		Hide_Customer_Graphic(Current_Customer_Order_Graphic);
		Current_Customer_Order_Graphic = Current_Customer_Order_Graphic->Next;
	}
}


//Functions To Display Orders Based on Current_Day_Orders
void CompleteOrder::Add_Customer_Graphic(const CustomerOrder& Customer_Order_To_Add) 
{
	//void SetPageDirectory();
	//Text
	TextData TextData_Template;
	TextData_Template.Centered = false;

	//PageItem
	llPageItemData PageItem_Template;
	PageItem_Template.Position = {0.0, 0.0};
	PageItem_Template.Color = { 0.0, 0.5, 1.0, 1.0 };
	PageItem_Template.BackGround = true;

	//ShapeGroup
	llShapeGroupData ShapeGroup_Template;
	ShapeGroup_Template.Position = { 0.0, 0.0 };
	ShapeGroup_Template.Color = { 0.0, 1.0, 1.0, 1.0 };
	ShapeGroup_Template.MouseAccess = true;

	//PageGroupItem PlaceHolder(RestaurantBook);
	PageGroupItem PlaceHolder(RestaurantBook, &PageItem_Template);

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
		last_customer_order_edges = PlaceHolder.GetEdges();
	}
	else
	{
		AlignmentType = MATCH_CENTERS;
		PlaceHolder.PlaceRight(last_customer_order_edges, AlignmentType, Padding);
		last_customer_order_edges = PlaceHolder.GetEdges();
	}
	MasterElement::PrintPageItemStats(PlaceHolder.GetData());
}

void CompleteOrder::Replace_Customer_Graphic(const CustomerOrder& Customer_Order_To_Replace, llPageItemData* Customer_Order_PageItem)
{
	if (Customer_Order_PageItem == nullptr) { Log::LogString("replace_ordered_dish_graphic ERROR:: ordered_dish_Graphic nullptr"); return; }

	//Prepare Ordered Dish Attribute Graphic Data 
	glm::vec4 last_shapegroup_edges;
	llShapeGroupData* Attribute_Graphic_Data = Customer_Order_PageItem->ShapeGroup;
	Attribute_Graphic_Data = MasterElement::HeadShapeGroup(Attribute_Graphic_Data);

	//Prepare Ordered Dish Attribute Graphics for editing
	Text Ordered_Dish_Graphic_Attribute(Attribute_Graphic_Data);
	Ordered_Dish_Graphic_Attribute.LoadedBook = RestaurantBook;

	//Customer Name
	Attribute_Graphic_Data = Attribute_Graphic_Data->Next; //FIX THIS
	Ordered_Dish_Graphic_Attribute.llSwitch(Attribute_Graphic_Data);
	Ordered_Dish_Graphic_Attribute.SetllText(Customer_Order_To_Replace.CustomerDetails.FirstName + " " + Customer_Order_To_Replace.CustomerDetails.LastName);
	Ordered_Dish_Graphic_Attribute.PlaceBelow(last_shapegroup_edges, MATCH_BEGINNINGS, 20);
	last_shapegroup_edges = Ordered_Dish_Graphic_Attribute.GetEdgesWithBackGround();

	//Customer Items Quantity
	Attribute_Graphic_Data = Attribute_Graphic_Data->Next;
	Ordered_Dish_Graphic_Attribute.llSwitch(Attribute_Graphic_Data);
	Ordered_Dish_Graphic_Attribute.SetllText("(10) Items Ordered");
	Ordered_Dish_Graphic_Attribute.PlaceRight(last_shapegroup_edges, MATCH_BEGINNINGS, 10);
	last_shapegroup_edges = Ordered_Dish_Graphic_Attribute.GetEdgesWithBackGround();

	//Temporary Fix
	int AlignmentType = MATCH_CENTERS;
	int Padding = 20;

	//Only the first item has a centered alignment type
	if (first_customer_order == true) { AlignmentType = MATCH_CENTERS; first_customer_order = false; Padding = 40; }

	//Prepare Ordered Dish Graphic for editing
	PageGroupItem Ordered_Dish_Graphic(Customer_Order_PageItem);
	Ordered_Dish_Graphic.LoadedBook = RestaurantBook;
	Ordered_Dish_Graphic.llSwitch(Customer_Order_PageItem);
	Ordered_Dish_Graphic.PlaceRight(last_customer_order_edges, AlignmentType, Padding);
	Ordered_Dish_Graphic.UnHide();

	last_customer_order_edges = Ordered_Dish_Graphic.GetEdges();
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

void CompleteOrder::Print_Condensed_Dishes()
{
	Log::LogString("Printing Condensed Dishes");

	for (auto CondensedDish : All_Ordered_Dishes)
	{
		Log::LogString(CondensedDish.first + " Quantity:" + to_string(CondensedDish.second));
	}
}
