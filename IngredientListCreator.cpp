#include "IngredientListCreator.h"

void IngredientListCreator::Prepare()
{
	build_2d_conversion_map();
}

void IngredientListCreator::build_2d_conversion_map()
{
	litre_kilo_to[QUANTITY][QUANTITY] = dud;
	litre_kilo_to[LIQUID][GALLON] = litre_to_gallon;
	litre_kilo_to[LIQUID][QUART] = litre_to_quart;
	litre_kilo_to[LIQUID][PINT] = litre_to_pint;
	litre_kilo_to[LIQUID][CUP] = litre_to_cup;
	litre_kilo_to[LIQUID][FUILD_OUNCE] = litre_to_fluid_ounce;
	litre_kilo_to[LIQUID][TABLESPOON] = litre_to_tablespoon;
	litre_kilo_to[LIQUID][TEASPOON] = litre_to_teaspoon;
	litre_kilo_to[LIQUID][MILLILITRE] = litre_to_millilitre;
		
	litre_kilo_to[WEIGHT][POUND] = kilo_to_pound;
	litre_kilo_to[WEIGHT][OUNCE] = kilo_to_ounce;
	litre_kilo_to[WEIGHT][TON] = kilo_to_ton;
	litre_kilo_to[WEIGHT][GRAM] = kilo_to_gram;
	litre_kilo_to[WEIGHT][MILLIGRAM] = kilo_to_milligram;

	to_litre_kilo[QUANTITY][QUANTITY] = dud;
	to_litre_kilo[LIQUID][GALLON] = gallon_to_litre;
	to_litre_kilo[LIQUID][QUART] = quart_to_litre;
	to_litre_kilo[LIQUID][PINT] = pint_to_litre;
	to_litre_kilo[LIQUID][CUP] = cup_to_litre;
	to_litre_kilo[LIQUID][FUILD_OUNCE] = fluid_ounce_to_litre;
	to_litre_kilo[LIQUID][TABLESPOON] = tablespoon_to_litre;
	to_litre_kilo[LIQUID][TEASPOON] = teaspoon_to_litre;
	to_litre_kilo[LIQUID][MILLILITRE] = millilitre_to_litre;

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
}


void IngredientListCreator::PrepareContainers(map<string, Section>* Section, map<string, Dish>* Dish, map<string, DishSide>* Side, map<string, Ingredient>* Ingredient, map<string, CustomerOrder>* Order_By_Date)
{
	Orders_By_Date = Order_By_Date;
	All_Sections = Section;
	All_Dishes = Dish;
	All_Sides = Side;
	All_Ingredients = Ingredient;
}

void IngredientListCreator::Update(int CurrentPage)
{
	// 0 is this namespace
	if (CurrentPage != 2) { return; }

	Page_IngredientListCreator.DrawPage();
	MasterElement::FindElement(RestaurantBook, LEVEL_SHAPEGROUP, ElementsHovered);
}

void IngredientListCreator::Prepare_Customer_Orders()
{
	TextData TextData_Template;
	llShapeGroupData ShapeGroup_Template;

	PageGroupItem PageItem(RestaurantBook);

	TextData_Template.Phrase = "Customer Orders";
	ShapeGroup_Template.Position = {-0.95, 0.8};
	Button_Update_Customer_Orders.LogicalActions[GUI_MOUSELEFT_CLICKED] = Update_Customer_Orders_Graphics;
	Text_Customer_Orders_Label.llInit(RestaurantBook, &ShapeGroup_Template, TextData_Template);
	Text_Customer_Orders_Label.GetData()->ShapeGroupButton = &Button_Update_Customer_Orders;
	first_customer_order_edges = Text_Customer_Orders_Label.GetEdges();

	TextData_Template.Phrase = "Ingredient List";
	ShapeGroup_Template.Position = { 0.0, 0.8 };
	Button_Update_Ingredient_List.LogicalActions[GUI_MOUSELEFT_CLICKED] = CreateShoppingList;
	Text_Ingredient_List_Label.llInit(RestaurantBook, &ShapeGroup_Template, TextData_Template);
	Text_Ingredient_List_Label.GetData()->ShapeGroupButton = &Button_Update_Ingredient_List;
	first_ingredient_list_edges = Text_Ingredient_List_Label.GetEdges();
}

void IngredientListCreator::Update_Customer_Orders_Graphics()
{
	Log::LogString("Updating Customer Order Graphics--------------------------------------------------");
	llPageItemData* Current_Customer_Order_PageItem = First_Customer_Order_Graphic;
	first_customer_order = true;
	last_customer_order_edges = first_customer_order_edges;
	bool AddOnly = false;

	//Use the "Current_Section" to loop through it's dishes
	for (auto& kv : Customer_Order_DataBase)
	{
		const CustomerOrder& Current_Customer_Order = kv.second;

		//New Graphic
		if (Current_Customer_Order_PageItem == nullptr)
		{

			//Create Graphic
			Add_Customer_Orders_Graphic(Current_Customer_Order);
			AddOnly = true;
		}

		////Existing Graphic
		if (Current_Customer_Order_PageItem != nullptr && AddOnly != true)
		{
			//Change Graphic
			Replace_Customer_Orders_Graphic(Current_Customer_Order, Current_Customer_Order_PageItem);
		}

		//if we add, it will go through replacing alse thats why we need this boolean
		AddOnly = false;

		//Stop Cycling if there is no shapegroup
		if (Current_Customer_Order_PageItem != nullptr) { Current_Customer_Order_PageItem = Current_Customer_Order_PageItem->Next; }
	}

	//Graphics left over
	////Existing? // Add // Hide
	while (Current_Customer_Order_PageItem != nullptr)
	{
		Hide_Customer_Orders_Graphic(Current_Customer_Order_PageItem);
		Current_Customer_Order_PageItem = Current_Customer_Order_PageItem->Next;
	}
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
		const string& Current_Ingredient_Name = kv.first;
		string Current_Ingredient_Measurement  = SubmitOrder::ProcessDecimalPlace(kv.second, false, 4);

		//New Graphic
		if (Current_Ingredient_List_PageItem == nullptr)
		{

			//Create Graphic
			Add_Ingredient_List_Graphic(Current_Ingredient_Name, Current_Ingredient_Measurement);
			AddOnly = true;
		}

		////Existing Graphic
		if (Current_Ingredient_List_PageItem != nullptr && AddOnly != true)
		{
			//Change Graphic
			Replace_Ingredient_List_Graphic(Current_Ingredient_Name, Current_Ingredient_Measurement, Current_Ingredient_List_PageItem);
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

void IngredientListCreator::Add_Ingredient_List_Graphic(const string& Ingredient_Name, const string& Ingredient_Measurement)
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
	PageItem_Template.DescriptiveData = Ingredient_Name;

	//Page Item
	PageGroupItem PageItem_Ingredient_Graphic(RestaurantBook, &PageItem_Template);

	//Ingredient Name
	TextData_Template.Phrase = Ingredient_Name;
	ShapeGroup_Template.Color = PageCreator::White; // Light Red
	Text Text_Ingredient_Name(RestaurantBook, &ShapeGroup_Template, TextData_Template);

	//Ingredient Measurement
	TextData_Template.Phrase = Ingredient_Measurement + " ml";
	ShapeGroup_Template.Color = PageCreator::White; // Light Red
	Text Text_Ingredient_Measurement(RestaurantBook, &ShapeGroup_Template, TextData_Template);

	if (First_Ingredient_List_Graphic == nullptr)
	{
		First_Ingredient_List_Graphic = PageItem_Ingredient_Graphic.GetData();
	}

	//Place New Side
	int Spacing = 20;
	if (first_ingredient_list == true) { Spacing = 100; first_ingredient_list = false; }
	PageItem_Ingredient_Graphic.PlaceBelow(last_ingredient_list_edges, MATCH_BEGINNINGS, Spacing);
	last_ingredient_list_edges = PageItem_Ingredient_Graphic.GetEdgesWithBackGround();

}

void IngredientListCreator::Replace_Ingredient_List_Graphic(const string& Ingredient_Name, const string& Ingredient_Measurement, llPageItemData* Ingredient_List_Graphic_Data)
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
	Ordered_Dish_Graphic_Attribute.SetllText(Ingredient_Name);
	Ordered_Dish_Graphic_Attribute.PlaceRight(last_shapegroup_edges, MATCH_CENTERS, 20);
	last_shapegroup_edges = Ordered_Dish_Graphic_Attribute.GetEdgesWithBackGround();

	//Replace Ingredient List Measurement
	Attribute_Graphic_Data = Attribute_Graphic_Data->Next;
	Ordered_Dish_Graphic_Attribute.llSwitch(Attribute_Graphic_Data);
	Ordered_Dish_Graphic_Attribute.SetllText(Ingredient_Measurement + " ml");
	Ordered_Dish_Graphic_Attribute.PlaceRight(last_shapegroup_edges, MATCH_CENTERS, 10);
	last_shapegroup_edges = Ordered_Dish_Graphic_Attribute.GetEdgesWithBackGround();


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
	Ordered_Dish_Graphic.UnHide();

	last_ingredient_list_edges = Ordered_Dish_Graphic.GetEdges();
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

void IngredientListCreator::CreateShoppingList()
{
	for (auto kv : Customer_Order_DataBase)
	{
		CustomerOrder& Current_Order = kv.second;
		ConsolidateOrderIngredients(Current_Order);
	}

	Update_Ingredient_List_Graphics();
}

void IngredientListCreator::ConsolidateOrderIngredients(CustomerOrder& Customer_Order)
{
	for (auto kv : Customer_Order.OrderedDishes)
	{
		const OrderedDish& Customers_Ordered_Dish = kv.second;
		Dish& Current_Dish = Dish_DataBase[Customers_Ordered_Dish.Name];
		ConsolidateDishIngredients(Current_Dish);
	}
}

void IngredientListCreator::ConsolidateDishIngredients(Dish& Dish)
{
	//Go through all the side names
	for (auto& Side_Name : Dish_DataBase[Dish.Name].Side_Names)
	{
		DishSide& Current_Side = Side_DataBase[Side_Name];
		ConsolidateSideIngredients(Current_Side);
	}
}

void IngredientListCreator::ConsolidateSideIngredients(DishSide& Side)
{
	//Go Through All Ingredients in "Side"
	for (auto ingredient : Side.Ingredient_Names)
	{
		//Get Ingredient Details
		const string& Ingredient_Name           =  ingredient.first;
		const double& Ingredient_Measurment     =  ingredient.second.Measurement;
		const int& Ingredient_Measurment_Medium =  ingredient.second.MeasurementMedium;
		const int& Ingredient_Type              =  Ingredient_DataBase[Ingredient_Name].MeasurementType;
		
		Log::LogString("Name: " + Ingredient_Name);
		Log::LogInt("Ingredient Type", Ingredient_Type);
		Log::LogInt("Ingredient_Measurment_Medium", Ingredient_Measurment_Medium);
		Log::LogInt("Ingredient_Measurment", Ingredient_Measurment);

		//Convert Ingredient to Litre/Kilos
		double amount_in_litre_kilo = Ingredient_Measurment;// = to_litre_kilo[Ingredient_Type][Ingredient_Measurment_Medium](Ingredient_Measurment);
		//double amount_in_teaspoon = litre_kilo_to[LIQUID][CUP](amount_in_litre_kilo);

		//Existing Shopping List Ingredient
		if (ShoppingList.find(Ingredient_Name) != ShoppingList.end())
		{
			//Update Ingredient
			ShoppingList[Ingredient_Name] += amount_in_litre_kilo;
		}
		//New Shopping List Ingredient
		else
		{
			//Add Ingredient
			ShoppingList[Ingredient_Name] = amount_in_litre_kilo;
		}
	}

}

void IngredientListCreator::PrintShoppingList()
{
	for (auto Ingredient : ShoppingList)
	{
		string MeasurementType = "L";
		const string& Ingredient_Name = Ingredient.first;
		const double& Ingredient_Quantity = Ingredient.second;

		string Quantity = SubmitOrder::ProcessDecimalPlace(Ingredient_Quantity, false, 3);

		cout << Ingredient_Name << " | " << Quantity << " " << MeasurementType << endl;
	}
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