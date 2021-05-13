#include "IngredientListCreator.h"

void IngredientListCreator::Prepare()
{
	build_2d_conversion_map();
}

void IngredientListCreator::build_2d_conversion_map()
{
	litre_kilo_to[QUANTITY][QUANTITY] = dud;
	litre_kilo_to[LIQUID][0] = dud;
	litre_kilo_to[LIQUID][GALLON] = litre_to_gallon;
	litre_kilo_to[LIQUID][QUART] = litre_to_quart;
	litre_kilo_to[LIQUID][PINT] = litre_to_pint;
	litre_kilo_to[LIQUID][CUP] = litre_to_cup;
	litre_kilo_to[LIQUID][FUILD_OUNCE] = litre_to_fluid_ounce;
	litre_kilo_to[LIQUID][TABLESPOON] = litre_to_tablespoon;
	litre_kilo_to[LIQUID][TEASPOON] = litre_to_teaspoon;
	litre_kilo_to[LIQUID][MILLILITRE] = litre_to_millilitre;
		
	litre_kilo_to[WEIGHT][0] = dud;
	litre_kilo_to[WEIGHT][POUND] = kilo_to_pound;
	litre_kilo_to[WEIGHT][OUNCE] = kilo_to_ounce;
	litre_kilo_to[WEIGHT][TON] = kilo_to_ton;
	litre_kilo_to[WEIGHT][GRAM] = kilo_to_gram;
	litre_kilo_to[WEIGHT][MILLIGRAM] = kilo_to_milligram;

	to_litre_kilo[QUANTITY][QUANTITY] = dud;
	to_litre_kilo[LIQUID][0] = dud;
	to_litre_kilo[LIQUID][GALLON] = gallon_to_litre;
	to_litre_kilo[LIQUID][QUART] = quart_to_litre;
	to_litre_kilo[LIQUID][PINT] = pint_to_litre;
	to_litre_kilo[LIQUID][CUP] = cup_to_litre;
	to_litre_kilo[LIQUID][FUILD_OUNCE] = fluid_ounce_to_litre;
	to_litre_kilo[LIQUID][TABLESPOON] = tablespoon_to_litre;
	to_litre_kilo[LIQUID][TEASPOON] = teaspoon_to_litre;
	to_litre_kilo[LIQUID][MILLILITRE] = millilitre_to_litre;

	to_litre_kilo[WEIGHT][0] = dud;
	to_litre_kilo[WEIGHT][POUND] = pound_to_kilo;
	to_litre_kilo[WEIGHT][OUNCE] = ounce_to_kilo;
	to_litre_kilo[WEIGHT][TON] = ton_to_kilo;
	to_litre_kilo[WEIGHT][GRAM] = gram_to_kilo;
	to_litre_kilo[WEIGHT][MILLIGRAM] = milligram_to_kilo;
}


void IngredientListCreator::Prepare(llBookData* Restaurant_POS, ShaderProgram* ShaderProgram, RawTexture* Texture0, RawTexture* Texture1, RawTexture* Texture2)
{
	RestaurantBook = Restaurant_POS;
	//Prepare Submit Order Page for Usage
	CurrentShader = ShaderProgram;

	CurrentTexture0 = Texture0;
	CurrentTexture1 = Texture1;
	CurrentTexture2 = Texture2;

	Page_IngredientListCreator.llInit(RestaurantBook, CurrentShader, CurrentTexture0, CurrentTexture1, CurrentTexture2);

	IngredientListCreatorOrderDirectory = RestaurantBook->Page;

	Prepare_Customer_Orders();
	build_2d_conversion_map();
}


void IngredientListCreator::PrepareContainers(map<string, Section>* Section, map<string, Dish>* Dish, map<string, DishSide>* Side, map<string, Ingredient>* Ingredient, map<string, SameDayOrders>* All_Orders)
{
	All_Customer_Orders = All_Orders;
	All_Sections = Section;
	All_Dishes = Dish;
	All_Sides = Side;
	All_Ingredients = Ingredient;
}

void IngredientListCreator::Update(int CurrentPage, KeyResult* KeyResult)
{
	// 0 is this namespace
	if (CurrentPage != 2) { return; }

	Page_IngredientListCreator.DrawPage();
	MasterElement::FindElement(RestaurantBook, LEVEL_SHAPEGROUP, ElementsHovered);

	if (KeyResult->Key1 == GUI_X_CLICKED)
	{
		CreateShoppingList();
	}
}

void IngredientListCreator::Prepare_Customer_Orders()
{
	TextData TextData_Template;
	llShapeGroupData ShapeGroup_Template;

	PageGroupItem PageItem(RestaurantBook);

	TextData_Template.Phrase = "Customer Orders";
	ShapeGroup_Template.Position = {-0.95, 0.8};
	Button_Update_Customer_Orders.Add_Mouse_Action(GUI_MOUSELEFT_CLICKED, Update_Customer_Orders_Graphics);
	Text_Customer_Orders_Label.llInit(RestaurantBook, &ShapeGroup_Template, TextData_Template);
	Text_Customer_Orders_Label.GetData()->ShapeGroupButton = &Button_Update_Customer_Orders;
	first_customer_order_edges = Text_Customer_Orders_Label.GetEdges();

	TextData_Template.Phrase = "Ingredient List";
	ShapeGroup_Template.Position = { 0.0, 0.8 };
	Button_Update_Ingredient_List.Add_Mouse_Action(GUI_MOUSELEFT_CLICKED, CreateShoppingList);
	Text_Ingredient_List_Label.llInit(RestaurantBook, &ShapeGroup_Template, TextData_Template);
	Text_Ingredient_List_Label.GetData()->ShapeGroupButton = &Button_Update_Ingredient_List;
	first_ingredient_list_edges = Text_Ingredient_List_Label.GetEdges();
}

void IngredientListCreator::Update_Customer_Orders_Graphics()
{
	Log::LogString("IngredientListCreator");
	//Log::LogString("Updating Customer Order Graphics--------------------------------------------------");
	//llPageItemData* Current_Customer_Order_PageItem = First_Customer_Order_Graphic;
	//first_customer_order = true;
	//last_customer_order_edges = first_customer_order_edges;
	//bool AddOnly = false;
	//
	////Use the "Current_Section" to loop through it's dishes
	//for (const auto& Same_DayOrder : Customer_Order_DataBase)
	//{
	//	const SameDayOrders& Date = Same_DayOrder.second;
	//
	//	for (const auto& kv : Date.CustomerOrders)
	//	{
	//		const CustomerOrder& Current_Customer_Order = kv.second;
	//		//New Graphic
	//		if (Current_Customer_Order_PageItem == nullptr)
	//		{
	//
	//			//Create Graphic
	//			Add_Customer_Orders_Graphic(Current_Customer_Order);
	//			AddOnly = true;
	//		}
	//
	//		////Existing Graphic
	//		if (Current_Customer_Order_PageItem != nullptr && AddOnly != true)
	//		{
	//			//Change Graphic
	//			Replace_Customer_Orders_Graphic(Current_Customer_Order, Current_Customer_Order_PageItem);
	//		}
	//
	//		//if we add, it will go through replacing alse thats why we need this boolean
	//		AddOnly = false;
	//
	//		//Stop Cycling if there is no shapegroup
	//		if (Current_Customer_Order_PageItem != nullptr) { Current_Customer_Order_PageItem = Current_Customer_Order_PageItem->Next; }
	//	}
	//
	//	//Graphics left over
	//	////Existing? // Add // Hide
	//	while (Current_Customer_Order_PageItem != nullptr)
	//	{
	//		Hide_Customer_Orders_Graphic(Current_Customer_Order_PageItem);
	//		Current_Customer_Order_PageItem = Current_Customer_Order_PageItem->Next;
	//	}
	//}
}

void IngredientListCreator::Add_Customer_Orders_Graphic(const CustomerOrder& Current_Customer_Order)
{

	const string& Customer_Last_Name = Current_Customer_Order.CustomerDetails.LastName;
	const string& Customer_First_Name = Current_Customer_Order.CustomerDetails.FirstName;

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
	PageItem_Template.BackGroundColor = PageCreator::Favourite_Color; //Dark Red
	PageItem_Template.BackGroundPadding[PADDING_LEFT] = 30;
	PageItem_Template.BackGroundPadding[PADDING_RIGHT] = 30;
	PageItem_Template.BackGroundPadding[PADDING_TOP] = 10;
	PageItem_Template.BackGroundPadding[PADDING_BOTTOM] = 10;
	PageItem_Template.DescriptiveData = Customer_Last_Name;

	//Page Item
	PageGroupItem PageItem_Ingredient_Graphic(RestaurantBook, &PageItem_Template);

	//Text
	TextData_Template.Phrase = Customer_First_Name + " " + Customer_Last_Name;
	ShapeGroup_Template.Color = PageCreator::White; // Light Red
	Text Text_Side_Name(RestaurantBook, &ShapeGroup_Template, TextData_Template);

	if (First_Customer_Order_Graphic == nullptr)
	{
		First_Customer_Order_Graphic = PageItem_Ingredient_Graphic.GetData();
	}

	//Place New Side
	int Spacing = 20;
	if (first_customer_order == true) { Spacing = 100; first_customer_order = false; }
	PageItem_Ingredient_Graphic.PlaceBelow(last_customer_order_edges, MATCH_BEGINNINGS, Spacing);
	last_customer_order_edges = PageItem_Ingredient_Graphic.GetEdgesWithBackGround();

}

void IngredientListCreator::Replace_Customer_Orders_Graphic(const CustomerOrder& Current_Customer_Order, llPageItemData* Customer_Order_Graphic_Data)
{
	if (Customer_Order_Graphic_Data == nullptr) { Log::LogString("replace_customer_order_graphic ERROR:: Dish_PageItem nullptr"); return; }

	const string& Customer_First_Name = Current_Customer_Order.CustomerDetails.FirstName;
	const string& Customer_Last_Name = Current_Customer_Order.CustomerDetails.LastName;

	llShapeGroupData* CurrentShapeGroup = Customer_Order_Graphic_Data->ShapeGroup;

	Text Customer_Order_Name(CurrentShapeGroup);
	Customer_Order_Name.LoadedBook = RestaurantBook;
	Customer_Order_Name.llSwitch(CurrentShapeGroup);
	Customer_Order_Name.SetllText(Customer_First_Name + " " + Customer_Last_Name);

	//Place New Side
	int Spacing = 20;
	if (first_customer_order == true) { Spacing = 100; first_customer_order = false; }

	PageGroupItem Customer_Order_Graphic(Customer_Order_Graphic_Data);
	Customer_Order_Graphic.LoadedBook = RestaurantBook;
	Customer_Order_Graphic.llSwitch(Customer_Order_Graphic_Data);
	Customer_Order_Graphic.PlaceBelow(last_customer_order_edges, MATCH_CENTERS, Spacing);
	Customer_Order_Graphic.UnHide();
	Customer_Order_Graphic_Data->DescriptiveData = Customer_Last_Name; //Attach Key to UI

	last_customer_order_edges = Customer_Order_Graphic.GetEdgesWithBackGround();
}

void IngredientListCreator::Hide_Customer_Orders_Graphic(llPageItemData* PageItem_Customer_Order_Graphic)
{
	//Set New Name
	PageGroupItem Customer_Order_Graphic(PageItem_Customer_Order_Graphic);
	Customer_Order_Graphic.LoadedBook = RestaurantBook;
	Customer_Order_Graphic.llSwitch(PageItem_Customer_Order_Graphic);
	Customer_Order_Graphic.Hide();
	PageItem_Customer_Order_Graphic->DescriptiveData = " ";

	//Place New Side
	int Spacing = 20;
	if (first_customer_order == true) { Spacing = 100; first_customer_order = false; }
	Customer_Order_Graphic.PlaceBelow(last_customer_order_edges, MATCH_CENTERS, Spacing);

}



void IngredientListCreator::Update_Ingredient_List_Graphics()
{
	Log::LogString("Updating Customer Order Graphics--------------------------------------------------");
	llPageItemData* Current_Ingredient_List_PageItem = First_Ingredient_List_Graphic;
	first_ingredient_list  = true;
	last_ingredient_list_edges = first_ingredient_list_edges;
	bool AddOnly = false;

	//Use the "Current_Section" to loop through it's dishes
	for (auto& kv : ShoppingList)
	{
		Ingredient_Details& Current_Ingredient_Details = kv.second;
		string Current_Ingredient_Measurement  = SubmitOrder::ProcessDecimalPlace(Current_Ingredient_Details.Measurement, false, 2);

		//New Graphic
		if (Current_Ingredient_List_PageItem == nullptr)
		{

			//Create Graphic
			Log::LogString("Adding list ingredient");
			Add_Ingredient_List_Graphic(Current_Ingredient_Details, Current_Ingredient_Measurement);
			AddOnly = true;
		}

		////Existing Graphic
		if (Current_Ingredient_List_PageItem != nullptr && AddOnly != true)
		{
			//Change Graphic
			Log::LogString("replacing list ingredient");
			Replace_Ingredient_List_Graphic(Current_Ingredient_Details, Current_Ingredient_Measurement, Current_Ingredient_List_PageItem);
		}

		//if we add, it will go through replacing alse thats why we need this boolean
		AddOnly = false;

		//Stop Cycling if there is no shapegroup
		if (Current_Ingredient_List_PageItem != nullptr) { Current_Ingredient_List_PageItem = Current_Ingredient_List_PageItem->Next; }
	}

	//Graphics left over
	////Existing? // Add // Hide
	while (Current_Ingredient_List_PageItem != nullptr)
	{
		Hide_Ingredient_List_Graphic(Current_Ingredient_List_PageItem);
		Current_Ingredient_List_PageItem = Current_Ingredient_List_PageItem->Next;
	}
}

void IngredientListCreator::Add_Ingredient_List_Graphic(Ingredient_Details& Ingredient_Details, const string& Ingredient_Measurement)
{

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
	PageItem_Template.BackGroundColor = PageCreator::Favourite_Color; //Dark Red
	PageItem_Template.BackGroundPadding[PADDING_LEFT] = 30;
	PageItem_Template.BackGroundPadding[PADDING_RIGHT] = 30;
	PageItem_Template.BackGroundPadding[PADDING_TOP] = 10;
	PageItem_Template.BackGroundPadding[PADDING_BOTTOM] = 10;
	PageItem_Template.DescriptiveData = Ingredient_Details.Name;

	//Page Item
	PageGroupItem PageItem_Ingredient_Graphic(RestaurantBook, &PageItem_Template);

	//Ingredient Name
	TextData_Template.Phrase = Ingredient_Details.Name;
	ShapeGroup_Template.Color = PageCreator::White; // Light Red
	Text Text_Ingredient_Name(RestaurantBook, &ShapeGroup_Template, TextData_Template);

	string gettingannoyed = what_is_the_string(Ingredient_Details.Measurement_Type);

	Log::LogString(gettingannoyed);

	//Ingredient Measurement
	TextData_Template.Phrase = Ingredient_Measurement + gettingannoyed;
	ShapeGroup_Template.Color = PageCreator::White; // Light Red
	Text Text_Ingredient_Measurement(RestaurantBook, &ShapeGroup_Template, TextData_Template);
	Text_Ingredient_Measurement.PlaceRight(Text_Ingredient_Name.GetEdgesWithBackGround(), MATCH_CENTERS, 10);

	if (First_Ingredient_List_Graphic == nullptr)
	{
		First_Ingredient_List_Graphic = PageItem_Ingredient_Graphic.GetData();
	}

	//Place New Side
	int Spacing = 30;
	if (first_ingredient_list == true) { Spacing = 100; first_ingredient_list = false; }
	PageItem_Ingredient_Graphic.PlaceBelow(last_ingredient_list_edges, MATCH_BEGINNINGS, Spacing);
	last_ingredient_list_edges = PageItem_Ingredient_Graphic.GetEdgesWithBackGround();

}

void IngredientListCreator::Replace_Ingredient_List_Graphic(Ingredient_Details& Ingredient_Details, const string& Ingredient_Measurement, llPageItemData* Ingredient_List_Graphic_Data)
{
	if (Ingredient_List_Graphic_Data == nullptr) { Log::LogString("replace_ordered_dish_graphic ERROR:: ordered_dish_Graphic nullptr"); return; }
	void SetPageDirectory();

	//Prepare Ordered Dish Attribute Graphic Data 
	glm::vec4 last_shapegroup_edges;
	llShapeGroupData* Attribute_Graphic_Data = Ingredient_List_Graphic_Data->ShapeGroup;
	Attribute_Graphic_Data = MasterElement::HeadShapeGroup(Attribute_Graphic_Data);

	//Prepare Ingredient List Attribute Graphics for editing
	Text Ordered_Dish_Graphic_Attribute(Attribute_Graphic_Data);
	Ordered_Dish_Graphic_Attribute.LoadedBook = RestaurantBook;

	//Replace Ingredient List Name
	Attribute_Graphic_Data = Attribute_Graphic_Data->Next; //FIX THIS
	Ordered_Dish_Graphic_Attribute.llSwitch(Attribute_Graphic_Data);
	Ordered_Dish_Graphic_Attribute.SetllText(Ingredient_Details.Name);
	Ordered_Dish_Graphic_Attribute.PlaceRight(last_shapegroup_edges, MATCH_CENTERS, 20);
	last_shapegroup_edges = Ordered_Dish_Graphic_Attribute.GetEdges();
	string gettingannoyed = what_is_the_string(Ingredient_Details.Measurement_Type);

	//Replace Ingredient List Measurement
	Attribute_Graphic_Data = Attribute_Graphic_Data->Next;
	Ordered_Dish_Graphic_Attribute.llSwitch(Attribute_Graphic_Data);
	Ordered_Dish_Graphic_Attribute.SetllText(Ingredient_Measurement + gettingannoyed);
	Ordered_Dish_Graphic_Attribute.PlaceRight(last_shapegroup_edges, MATCH_CENTERS, 10);
	last_shapegroup_edges = Ordered_Dish_Graphic_Attribute.GetEdges();


	//Temporary Fix
	int AlignmentType = MATCH_CENTERS;
	int Padding = 20;

	//Only the first item has a centered alignment type
	if (first_ingredient_list == true) { AlignmentType = MATCH_CENTERS; first_ingredient_list = false; Padding = 40; }

	//Prepare Ordered Dish Graphic for editing
	PageGroupItem Ordered_Dish_Graphic(Ingredient_List_Graphic_Data);
	Ordered_Dish_Graphic.LoadedBook = RestaurantBook;
	Ordered_Dish_Graphic.llSwitch(Ingredient_List_Graphic_Data);
	Ordered_Dish_Graphic.PlaceBelow(last_ingredient_list_edges, AlignmentType, Padding);
	//Ordered_Dish_Graphic.UnHide();

	last_ingredient_list_edges = Ordered_Dish_Graphic.GetEdgesWithBackGround();
}

void IngredientListCreator::Hide_Ingredient_List_Graphic(llPageItemData* Ingredient_List_Graphic_Data)
{
	//Set New Name
	PageGroupItem Ingredient_List_Graphic(Ingredient_List_Graphic_Data);
	Ingredient_List_Graphic.LoadedBook = RestaurantBook;
	Ingredient_List_Graphic.llSwitch(Ingredient_List_Graphic_Data);
	Ingredient_List_Graphic.Hide();
	Ingredient_List_Graphic_Data->DescriptiveData = " ";


	//Place New Side
	int Spacing = 20;
	if (first_ingredient_list == true) { Spacing = 100; first_ingredient_list = false; }
	Ingredient_List_Graphic.PlaceBelow(last_ingredient_list_edges, MATCH_CENTERS, Spacing);
}



int IngredientListCreator::Get_Conversion_Measurement(int Ingredient_Type, double Measurement_In_Grams_Liquid)
{
	if (Ingredient_Type == LIQUID)
	{
		return Get_Liquid_Conversion_Measurement(Measurement_In_Grams_Liquid);
	}

	if (Ingredient_Type == WEIGHT)
	{
		return Get_Weight_Conversion_Measurement(Measurement_In_Grams_Liquid);
	}

	return QUANTITY;
}

int IngredientListCreator::Get_Liquid_Conversion_Measurement(double Measurement_In_Millilitres)
{
	if (Measurement_In_Millilitres < 4.929) //millilitres
	{
		return TEASPOON;
	}

	if (Measurement_In_Millilitres < 59.148) //millilitres
	{
		return TABLESPOON;
	}
	if (Measurement_In_Millilitres > 59.148)// 944) //millilitres
	{
		return CUP;
	}
	//if (Measurement_In_Millilitres > 944)
	//{
	//	return LITRE;
	//}
}

int IngredientListCreator::Get_Weight_Conversion_Measurement(double Measurement_In_Grams)
{

}

void IngredientListCreator::CreateShoppingList()
{
	//Log::LogString("Creating Shopping List");
	//for (auto kv : Customer_Order_DataBase)
	//{
	//	CustomerOrder& Current_Order = kv.second;
	//	ConsolidateOrderIngredients(Current_Order);
	//}
	//
	//Update_Ingredient_List_Graphics();
	//Log::LogString("Done Creating Shopping List and updating graphics");
}

void IngredientListCreator::ConsolidateOrderIngredients(CustomerOrder& Customer_Order)
{
	Log::LogString("Consolidating Customer Order" + Customer_Order.CustomerDetails.LastName);
	//Loop through customer's ordered dishes
	for (auto kv : Customer_Order.OrderedDishes)
	{
		OrderedDish& Customers_Ordered_Dish = kv.second;
		ConsolidateDishIngredients(Customers_Ordered_Dish);
	}
}

void IngredientListCreator::ConsolidateDishIngredients(OrderedDish& OrderedDish)
{
	Log::LogString("Consolidating Dish" + OrderedDish.Name);
	//Loop through ordered dish's sides
	for (auto& Side_Name : Dish_DataBase[OrderedDish.Name].Side_Names)
	{
		DishSide& Current_Side = Side_DataBase[Side_Name];
		ConsolidateSideIngredients(Current_Side, OrderedDish.Quantity);
	}
}

void IngredientListCreator::ConsolidateSideIngredients(DishSide& Side, int DishQuantity)
{
	Log::LogString("Adding Side Ingredients to Shopping List");
	//Go Through All Ingredients in "Side"
	for (auto ingredient : Side.Ingredient_Names)
	{
		//Get Ingredient Details
		const string& Ingredient_Name           =  ingredient.first;
		const double& Ingredient_Measurment     =  ingredient.second.Measurement;
		const int& Ingredient_Measurment_Medium =  ingredient.second.MeasurementMedium;
		const int& Measurment_Type              =  Ingredient_DataBase[Ingredient_Name].MeasurementType;
		
		//Log::LogString("Name: " + Ingredient_Name);
		//Log::LogInt("Measurment_Type", Measurment_Type);
		//Log::LogInt("Ingredient_Measurment_Medium", Ingredient_Measurment_Medium);
		//Log::LogInt("Ingredient_Measurment", Ingredient_Measurment);

		//Convert Ingredient to Litre/Kilos
		double amount_in_litre_kilo = to_litre_kilo[Measurment_Type][Ingredient_Measurment_Medium](Ingredient_Measurment* DishQuantity);
		//double amount_in_litre_kilo = to_litre_kilo[LIQUID][CUP](Ingredient_Measurment* DishQuantity);

		Ingredient_Details List_Ingredient;
		List_Ingredient.Name = Ingredient_Name;
		List_Ingredient.Measurement = amount_in_litre_kilo;
		List_Ingredient.Measurement_Type = Measurment_Type;

		//Existing Shopping List Ingredient
		if (ShoppingList.find(Ingredient_Name) != ShoppingList.end())
		{
			//Update Ingredient
			ShoppingList[Ingredient_Name].Measurement += amount_in_litre_kilo;
		}
		//New Shopping List Ingredient
		else
		{
			//Add Ingredient
			ShoppingList[Ingredient_Name] = List_Ingredient;
		}
	}

}

void IngredientListCreator::PrintShoppingList()
{
	for (auto Ingredient : ShoppingList)
	{
		string MeasurementType = "L";
		const string& Ingredient_Name = Ingredient.first;
		const double& Ingredient_Measurment = Ingredient.second.Measurement;

		string Quantity = SubmitOrder::ProcessDecimalPlace(Ingredient_Measurment, false, 3);

		cout << Ingredient_Name << " | " << Quantity << " " << MeasurementType << endl;
	}
}

string IngredientListCreator::what_is_the_string(int Measurement_Type)
{
	string Result;
	if (Measurement_Type == LIQUID)
	{
		Result = " L";
		return Result;
	}
	if (Measurement_Type == WEIGHT)
	{
		Result = " kg";
		return Result;
	}
	if (Measurement_Type == QUANTITY)
	{
		Result = " Q";
		return Result;
	}

	Result = "Didn't Work";
	return Result;
}

// Ex: Convert 7 TableSpoons to Teaspoons (7, MEASUREMENT_LIQUID, LIQUID_TABLESPOON, LIQUID_TEASPOON)
double IngredientListCreator::Measurement_Conversion(const double& Measurement, int MeasurementType, int Convert_From, int Convert_To)
{
	//Ex: Convert Tablespoon to litres
	double Litres_or_Kilo = to_litre_kilo[MeasurementType][Convert_From](Measurement);

	//Ex: Convert litres to Teaspoons
	return litre_kilo_to[MeasurementType][Convert_To](Litres_or_Kilo);

}//Be Careful of out of bounds, 

string IngredientListCreator::get_liquid_string(int LiquidType) {return " ";}
string IngredientListCreator::get_weight_string(int WeightType) {return " ";}

// kilo to
double IngredientListCreator::dud(const double& dud) { return dud; }
double IngredientListCreator::kilo_to_pound(const double& kilo)  { return kilo  * KILO_POUND_FACTOR; }
double IngredientListCreator::kilo_to_ounce(const double& kilo)  { return kilo  * KILO_OUNCE_FACTOR; }
double IngredientListCreator::kilo_to_ton  (const double& kilo)  { return kilo  * KILO_US_TON_FACTOR;}
double IngredientListCreator::kilo_to_gram  (const double& kilo) { return kilo  * KILO_GRAM_FACTOR;  }
double IngredientListCreator::kilo_to_milligram (const double& kilo)  
{ return kilo  * KILO_MILLIGRAM_FACTOR;}

// to kilo 
double IngredientListCreator::pound_to_kilo(const double& pound) { return pound / KILO_POUND_FACTOR; }
double IngredientListCreator::ounce_to_kilo(const double& ounce) { return ounce / KILO_OUNCE_FACTOR; }
double IngredientListCreator::ton_to_kilo  (const double& ton)   { return ton   / KILO_US_TON_FACTOR;}
double IngredientListCreator::gram_to_kilo (const double& gram)  { return gram  / KILO_GRAM_FACTOR;  }
double IngredientListCreator::milligram_to_kilo(const double& milligram)
{ return milligram  / KILO_MILLIGRAM_FACTOR;}
																												  
double IngredientListCreator::litre_to_gallon(const double& litre)      { return litre * LITRE_US_GALLON_FACTOR;    }
double IngredientListCreator::litre_to_quart(const double& litre)       { return litre * LITRE_US_QUART_FACTOR;     }
double IngredientListCreator::litre_to_pint(const double& litre)        { return litre * LITRE_US_PINT_FACTOR;      }
double IngredientListCreator::litre_to_fluid_ounce(const double& litre) { return litre * LITRE_FLUID_OUNCE_FACTOR;  }
double IngredientListCreator::litre_to_cup(const double& litre)         { return litre * LITRE_US_CUP_FACTOR;       }
double IngredientListCreator::litre_to_tablespoon(const double& litre)  { return litre * LITRE_US_TABLESPOON_FACTOR;}
double IngredientListCreator::litre_to_teaspoon(const double& litre)    { return litre * LITRE_US_TEASPOON_FACTOR;  }
double IngredientListCreator::litre_to_millilitre(const double& litre)  { return litre * LITRE_MILLILITRE_FACTOR;   }

double IngredientListCreator::gallon_to_litre(const double& gallom)          { return gallom     / LITRE_US_GALLON_FACTOR;    }
double IngredientListCreator::quart_to_litre(const double& quart)            { return quart      / LITRE_US_QUART_FACTOR;     }
double IngredientListCreator::pint_to_litre(const double& pint)              { return pint       / LITRE_US_PINT_FACTOR;      }
double IngredientListCreator::fluid_ounce_to_litre(const double& fluid_ounce){ return fluid_ounce/ LITRE_FLUID_OUNCE_FACTOR;  }
double IngredientListCreator::cup_to_litre(const double& cup)                { return cup        / LITRE_US_CUP_FACTOR;       }
double IngredientListCreator::tablespoon_to_litre(const double& tablespoon)  { return tablespoon / LITRE_US_TABLESPOON_FACTOR;}
double IngredientListCreator::teaspoon_to_litre(const double& teaspoon)      { return teaspoon   / LITRE_US_TEASPOON_FACTOR;  }
double IngredientListCreator::millilitre_to_litre(const double& millilitre)  { return millilitre / LITRE_MILLILITRE_FACTOR;   }