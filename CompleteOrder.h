#ifndef COMPLETEORDER
#define COMPLETEORDER

#include <iostream>
#include "SubmitOrder.h"

namespace CompleteOrder
{
	void SetOrderDate(const string& OrderDateKey); //Main Driver

	//+-------------------------Complete Order--------------------------+//
	static llBookData* RestaurantBook;
	static NewPage Page_Complete_Order;
	static RawTexture* CurrentTexture0;
	static RawTexture* CurrentTexture1;
	static RawTexture* CurrentTexture2;
	static llPageData* CompleteOrderDirectory;
	static ShaderProgram* CurrentShader;
	static BookDirectory DRPageGroup_Customer;
	static BookDirectory DRPageGroup_Dish;
	//static BookDirectory ElementsHovered;

	static map<string, SameDayOrders>* All_Customer_Orders;
	static map<string, Ingredient>* All_Ingredients;
	static map<string, DishSide>* All_Sides;
	static map<string, Dish>* All_Dishes;
	static map<string, Section>* All_Sections;

	#define Section_DataBase (*All_Sections) //Search by Section Name (string)
	#define Dish_DataBase (*All_Dishes) //Search by Dish Name (string)
	#define DishSide_DataBase (*All_Sides) //Search by Side Name (string)
	#define Ingredient_DataBase (*All_Ingredients) //Search by Ingredient Name (string)
	#define Customer_Order_DataBase (*All_Customer_Orders) //Search by Data (string)


	void Prepare(llBookData* Restaurant_POS, ShaderProgram* ShaderProgram, RawTexture* Texture0, RawTexture* Texture1, RawTexture* Texture2);
	void PrepareContainers(map<string, Section>* Section, map<string, Dish>* Dish, map<string, DishSide>* Side, map<string, Ingredient>* Ingredient, map<string, SameDayOrders>* All_Customer_Orders);
	void Update(KeyResult& CurrentKeyResult, int CurrentPage);
	void SetPageDirectory();
	llPageData* GetPageData();

	//+-------------------------Customer Orders-------------------------+//
	static SameDayOrders Current_Day_Orders;		//Drives the graphics
	static map<string, CustomerOrder> Orders_Selected;

	static glm::vec4 last_customer_order_edges;        //(Object) Graphic Reference for the form filler to position with
	static glm::vec4 first_customer_order_edges;        //(Object) Graphic Reference for the form filler to position with
	static bool first_customer_order;

	static llPageItemData* First_Customer_Order_Graphic;
	static llPageItemData* Customer_Order_Selected;
	static PageGroup PageGroup_Customers;
	static PageGroupItem PageItem_Customer_Order;
	static PageItemGrid Grid_Customers;
	static PageGroupItem PageItem_Customer_Graphic;
	static Text Text_Customer_Name;
	static Text Text_Customer_Item_Quantity;
	static Text Text_Label_Todays_Orders;
	static Button Button_Update_Customers;
	static Button Button_Toggle_Customer;
	static Button Button_Select_All_Customers;

	//Building Block Functions
	void Prepare_Customers();

	void Create_Customer_Graphic();
	void Create_Customer_Grid();
	void Update_Customer_Grid();

	//Manage Customers
	int  GetCustomerItemCount(const CustomerOrder& Order);

	static bool Select_Once;
	static bool UnSelect_Once;

	void ToggleCustomer();		// This Works but it gets called like 4 times in a row
	void SelectCustomer();		// This Works but it gets called like 4 times in a row
	void UnSelectCustomer();	// This Works but it gets called like 4 times in a row
	void SelectAllCustomers();	// This Works but it gets called like 4 times in a row

	//Display Customers
	void Highlight_Customer_Graphic();
	void DeHighlight_Customer_Graphic();
	void Update_Complete_Order();
	void Update_Customer_Graphics();
	void Add_Customer_Graphic(const CustomerOrder& Customer_Order_To_Add);
	void Replace_Customer_Graphic(const CustomerOrder& Customer_Order_To_Replace, llPageItemData* Customer_Order_PageItem);
	void Hide_Customer_Graphic(llPageItemData* PageItem_Dish_Graphic);
	//+------------------------------------------------------------------+//


	//+-------------------Items from Orders Selected---------------------+//
	static map<string, int> All_Ordered_Dishes; //Name, quntity

	static glm::vec4 last_dish_edges;        //(Object) Graphic Reference for the form filler to position with
	static glm::vec4 first_dish_edges;        //(Object) Graphic Reference for the form filler to position with
	static bool first_dish;

	static llPageItemData* First_Dish_Graphic;
	static llPageItemData* Dish_Selected;

	static PageGroup PageGroup_Ordered_Dishes;
	static PageGroupItem PageItem_Ordered_Dish;
	static Text Text_Dish_Name;
	static Text Text_Dish_Quantity;
	static Quad Quad_CheckBox;

	void Prepare_Dish_Graphics();

	void Condense_Ordered_Dishes();
	void Print_Condensed_Dishes();
	void Update_Condensed_Dishes();

	void Update_Dish_Graphics();              //Manages all Dish Graphics 
	void Add_Dish_Graphic(const string& Name, const int& Quantity); //Creates a Single Side Graphic
	void Replace_Dish_Graphic(string Name, const int& Quantity, llPageItemData* Dish_PageItem);     //Removes a Single Section Graphic
	void Hide_Dish_Graphic(llPageItemData* Dish_ShapeGroup);
	//+------------------------------------------------------------------+//


	//+-----------------------Display Item--Details----------------------+//
	static PageGroup PageGroup_Dish_Display;
	static Text Text_Display_Dish_Name;
	static Selector Selector_Sides;
	//+------------------------------------------------------------------+//
}

#endif