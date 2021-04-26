#ifndef INGREDIENTLISTCREATOR
#define INGREDIENTLISTCREATOR

#include <iostream>
#include "SubmitOrder.h"

//Mass based from 2 kilo
#define KILO_POUND_FACTOR 2.20462262185
#define KILO_OUNCE_FACTOR 35.27396195
#define KILO_US_TON_FACTOR 0.0011
#define KILO_GRAM_FACTOR 1000
#define KILO_MILLIGRAM_FACTOR 1000000

//Volume
#define LITRE_US_GALLON_FACTOR 0.264 
#define LITRE_US_QUART_FACTOR 1.057  
#define LITRE_US_PINT_FACTOR 2.11338 
#define LITRE_US_CUP_FACTOR 4.22675 //
#define LITRE_FLUID_OUNCE_FACTOR 33.814 
#define LITRE_US_TABLESPOON_FACTOR 67.628 
#define LITRE_US_TEASPOON_FACTOR 202.884 
#define LITRE_MILLILITRE_FACTOR 1000 //

struct Ingredient_Details
{
	string Name;
	double Measurement;
	int Measurement_Type;
	int Measurmenet_Medium;
};

typedef double(*Measurement_Function)(const double&); //Points to a liquid function
typedef unordered_map<int, Measurement_Function> ConversionFunctions;
typedef unordered_map<int, ConversionFunctions> Unordered_2d_Map;
	
//The purpose of this class is to be able to select orders and display the ingredient list
namespace IngredientListCreator
{
	typedef map<string, Ingredient_Details> IngredientList;
	static Unordered_2d_Map litre_kilo_to;
	static Unordered_2d_Map to_litre_kilo;

	static llBookData* RestaurantBook;
	static ShaderProgram* CurrentShader;
	static RawTexture* CurrentTexture0;
	static RawTexture* CurrentTexture1;
	static RawTexture* CurrentTexture2;
	static NewPage Page_IngredientListCreator;
	static llPageData* IngredientListCreatorOrderDirectory;
	static BookDirectory ElementsHovered;

	void Prepare();
	void build_2d_conversion_map();
	void Prepare(llBookData* Restaurant_POS, ShaderProgram* ShaderProgram, RawTexture* Texture0, RawTexture* Texture1, RawTexture* Texture2);
	void PrepareContainers(map<string, Section>* Section, map<string, Dish>* Dish, map<string, DishSide>* Side, map<string, Ingredient>* Ingredient, map<string, SameDayOrders>* All_Orders);
	void Update(int CurrentPage, KeyResult* KeyResult);

	static IngredientList ShoppingList;
	static map<string, SameDayOrders>* All_Customer_Orders;

	static map<string, Ingredient>* All_Ingredients;
	static map<string, DishSide>* All_Sides;
	static map<string, Dish>* All_Dishes;
	static map<string, Section>* All_Sections; //Section Name | Section Object | Dish Names

    #define Section_DataBase (*All_Sections)
    #define Dish_DataBase (*All_Dishes)
    #define Side_DataBase (*All_Sides)
    #define Ingredient_DataBase (*All_Ingredients)
	#define Customer_Order_DataBase (*All_Customer_Orders)

	static glm::vec4 first_customer_order_edges;
	static glm::vec4 last_customer_order_edges;
	static llPageItemData* First_Customer_Order_Graphic;
	static bool first_customer_order;

	static Button Button_Update_Customer_Orders;
	static Text Text_Customer_Orders_Label;

	void Prepare_Ingredient_List_Creator();
	void Prepare_Customer_Orders();


	void Add_Dish_To_Shopping_List();

	//Display Customer Orders for selection
	void Update_Customer_Orders_Graphics();
	void Add_Customer_Orders_Graphic(const CustomerOrder& ordered_dish_to_add);
	void Replace_Customer_Orders_Graphic(const CustomerOrder& ordered_dish_to_replace, llPageItemData* Ordered_Dish_PageItem);
	void Hide_Customer_Orders_Graphic(llPageItemData* PageItem_Dish_Graphic);


	static glm::vec4 first_ingredient_list_edges;
	static glm::vec4 last_ingredient_list_edges;
	static llPageItemData* First_Ingredient_List_Graphic;
	static bool first_ingredient_list;

	static Text Text_Ingredient_List_Label;
	static Button Button_Update_Ingredient_List;

	//Display Ingredient List
	void Update_Ingredient_List_Graphics();
	void Add_Ingredient_List_Graphic(Ingredient_Details& Ingredient_Name, const string& Ingredient_Measurement);
	void Replace_Ingredient_List_Graphic(Ingredient_Details& Ingredient_Name, const string& Ingredient_Measurement, llPageItemData* Ordered_Dish_PageItem);
	void Hide_Ingredient_List_Graphic(llPageItemData* PageItem_Dish_Graphic);

	int Get_Conversion_Measurement(int Ingredient_Type, double Measurement_In_Millilitres);
	int Get_Liquid_Conversion_Measurement(double Measurement_In_Millilitres);
	int Get_Weight_Conversion_Measurement(double Measurement_In_Millilitres);

	//Create Ingredient List
	void CreateShoppingList();
	void ConsolidateOrderIngredients(CustomerOrder& ShoppingList);
	void ConsolidateDishIngredients(OrderedDish& Dish);
	void ConsolidateSideIngredients(DishSide& Side, int DishQuantity); //Main Function

	void PrintShoppingList();

	string what_is_the_string(int Measurement_Type);

	string get_liquid_string(int LiquidType);
	string get_weight_string(int WeightType);

	double Measurement_Conversion(const double& Measurement, int MeasurementType, int Convert_From, int Convert_To);


	//Prints all ingredients in side
	void PrintSideIngredients();


	//-----------------Mass--------------------//

	double dud(const double& dud);

	// kilo to ?
	double kilo_to_pound    (const double& kilo);
	double kilo_to_ounce    (const double& kilo);
	double kilo_to_ton      (const double& kilo);
	double kilo_to_gram     (const double& kilo);
	double kilo_to_milligram(const double& kilo);

	// ? to kilo
	double pound_to_kilo    (const double& pound);
	double ounce_to_kilo    (const double& ounce);
	double ton_to_kilo      (const double& ton);
	double gram_to_kilo     (const double& gram);
	double milligram_to_kilo(const double& milligram);


	//----------------Volume--------------------//

	double litre_to_gallon     (const double& litre);
	double litre_to_quart      (const double& litre);
	double litre_to_pint       (const double& litre);
	double litre_to_fluid_ounce(const double& litre);
	double litre_to_cup        (const double& litre);
	double litre_to_tablespoon (const double& litre);
	double litre_to_teaspoon   (const double& litre);
	double litre_to_millilitre (const double& litre);

	double gallon_to_litre     (const double& gallon);
	double quart_to_litre      (const double& quart);
	double pint_to_litre       (const double& pint);
	double fluid_ounce_to_litre(const double& fluid_ounce);
	double cup_to_litre        (const double& cup);
	double tablespoon_to_litre (const double& tablespoon);
	double teaspoon_to_litre   (const double& teaspoon);
	double millilitre_to_litre (const double& millilitre);
}

#endif

