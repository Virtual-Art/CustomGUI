#ifndef	APPMENU
#define APPMENU

#include <iostream>
#include "SubmitOrder.h"


#define PAGE_SUBMIT_ORDER 0
#define PAGE_MENU_CREATOR 1
#define PAGE_INGREDIENT_LIST 2
#define PAGE_COMPLETE_ORDER 3


namespace ApplicationMenu
{
	static Selector Selector_App_Menu;
	static Button Button_Set_Current_Page;
	static int CurrentPage;
	static NewPage Page_ApplicationMenu;
	static BookDirectory BD_ApplicationMenu;
	//static BookDirectory ElementsHovered;
	static llBookData* RestaurantBook;
	static ShaderProgram* CurrentShader;
	static RawTexture* Texture0;
	static RawTexture* Texture1;
	static RawTexture* Texture2;

	void Prepare(llBookData* Restaurant_POS, ShaderProgram* ShaderProgram, RawTexture* Texture0, RawTexture* Texture1, RawTexture* Texture2);
	void PrepareContainers(map<string, Section>* Section, map<string, Dish>* Dish, map<string, DishSide>* Side, map<string, Ingredient>* Ingredient, map<string, SameDayOrders>* All_Customer_Orders);

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

	int Update();

	void CreatePageSelector();

	//---------Customer Selector------------//

	static PageGroupItem PageItem_Customer_Graphic;
	static PageItemGrid PageItemGrid_Orders_By_Date;
	static PageGroupGrid PageGroupGrid_All_Orders;

	void CreateCustomerGraphic();
	void CreateSameDayCustomerGraphics();
	void CreateCustomerSelect();


	void UpdateCustomerSelect();
	void SetSameDayCustomerGraphic(const SameDayOrders& CurrentDate, llPageGroupData* CurrentPageGroup);
	void SetCustomerGraphic(const CustomerOrder& CurrentOrder, llPageItemData* CurrentPageItem);

	//---------Customer Selector------------//


	void Highlight_Page_Selector(llShapeGroupData* ShapeGroup_Section_Graphic);
	void Select_Page();

	const glm::vec4 Page_Color = { 0.52, 0.41, 0.0, 1.0 };
	const glm::vec4 Page_Highlight_Color = { 0.77, 0.66, 0.0, 1.0 };
	static llShapeGroupData* ShapeGroup_Page_Graphic_Selected;

}

#endif