#ifndef COMPLETEORDER
#define COMPLETEORDER

#include <iostream>
#include "SubmitOrder.h"

namespace CompleteOrder
{
	//+-------------------------Complete Order--------------------------+//
	static llBookData* RestaurantBook;
	static NewPage Page_Complete_Order;
	static RawTexture* CurrentTexture0;
	static RawTexture* CurrentTexture1;
	static RawTexture* CurrentTexture2;
	static llPageData* SubmitOrderDirectory;
	static ShaderProgram* CurrentShader;

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

	//+-------------------------Customer Orders-------------------------+//
	static SameDayOrders Current_Day_Orders;		//Drives the graphics
	static map<string, CustomerOrder> Orders_Selected;

	static glm::vec4 last_customer_order_edges;        //(Object) Graphic Reference for the form filler to position with
	static glm::vec4 first_customer_order_edges;        //(Object) Graphic Reference for the form filler to position with
	static bool first_customer_order;

	static llPageItemData* First_Customer_Order_Graphic;
	static llPageItemData* Customer_Order_Selected;

	static PageGroup PageGroup_Orders_To_Complete;
	static PageGroupItem PageItem_Customer_Order;
	static Text Text_Customer_Name;
	static Text Text_Customer_Item_Quantity;
	static Text Text_Label_Todays_Orders;

	//Building Block Functions
	void Prepare_Customer_Orders();

	//Manage Customers
	int GetCustomerItemCount(const CustomerOrder& Order);
	void ToggleCustomer();
	void SelectCustomer();
	void UnSelectCustomer();

	void SelectAllCustomers();

	//Display Customers
	void Update_Customer_Graphics();
	void Add_Customer_Graphic(const CustomerOrder& Customer_Order_To_Add);
	void Replace_Customer_Graphic(const CustomerOrder& Customer_Order_To_Replace, llPageItemData* Customer_Order_PageItem);
	void Hide_Customer_Graphic(llPageItemData* PageItem_Dish_Graphic);
	//+------------------------------------------------------------------+//


	//+-------------------Items from Orders Selected---------------------+//
	static map<string, int> All_Ordered_Dishes; //Name, quntity

	static PageGroup PageGroup_Ordered_Dishes;
	static PageGroupItem PageItem_Ordered_Dish;
	static Text Text_Dish_Name;
	static Text Text_Dish_Quantity;
	static Quad Quad_CheckBox;

	void Condense_Ordered_Dishes();
	void Print_Condensed_Dishes();
	//+------------------------------------------------------------------+//


	//+-----------------------Display Item--Details----------------------+//
	static PageGroup PageGroup_Dish_Display;
	static Text Text_Display_Dish_Name;
	static Selector Selector_Sides;
	//+------------------------------------------------------------------+//
}

#endif