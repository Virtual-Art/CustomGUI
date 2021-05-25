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


typedef double(*Measurement_Function)(const double&); //Points to a liquid function
typedef unordered_map<int, Measurement_Function> ConversionFunctions;
typedef unordered_map<int, ConversionFunctions> Unordered_2d_Map;
	
//The purpose of this class is to be able to select orders and display the ingredient list
namespace IngredientListCreator
{

	static Unordered_2d_Map litre_kilo_to;
	static Unordered_2d_Map to_litre_kilo;

	string get_measurement_label(int Ex_Cup, int Ex_LIQUID);
	int PreferredLiquidforCooking(float MeasurementinLitres); //Ex: Litres -> Cup/Tablespoons/Teaspoon
	int PreferredLiquid(float MeasurementinLitres);           //Ex: Litres -> Mililetres/Litres
	int PreferredWeightMetric(float MeasurementinKilo);       //Ex: Kilo -> Kilo/Grams/Miligrams
	int PreferredWeightImperial(float MeasurementinKilo);     //Ex: Kilo -> Pound/Ounce


	//All you have to set is the Name, Measurement in Default Form and the type
	struct Ingredient_Details
	{
		//Needed for Details
		string Name;						  // Soya Sauce
		double Measurement_Default;		      // 1.0L
		int Measurement_Type;			      // LIQUID	

		//Needed for graphic
		double Basic_Measurement;			  // 23 
		int    Basic_Medium_Type;			  //MILILITRE
		double Descriptive_Measurement;		  // 40
		int    Descriptive_Medium_Type;	      //TEASPOON

		void CalculateMeasurements()
		{
			SetBasicMeasurement();
			SetDescriptiveMeasurement();
		}

		string GetBasicMeasurement()
		{
			string string_Basic_Measurment       = SubmitOrder::ProcessDecimalPlaceWhole(Basic_Measurement, false, 2);
			string string_Basic_Measurment_Label = get_measurement_label(Basic_Medium_Type, Measurement_Type);
			return string_Basic_Measurment + string_Basic_Measurment_Label;
		}

		string GetDescriptiveMeasurement()
		{
			if (Basic_Medium_Type == Descriptive_Medium_Type) { return " "; }

			string string_Descriptive_Measurment = SubmitOrder::ProcessDecimalPlaceWhole(Descriptive_Measurement, false, 2);
			string string_Descriptive_Measurment_Label = get_measurement_label(Descriptive_Medium_Type, Measurement_Type);
			return string_Descriptive_Measurment + string_Descriptive_Measurment_Label;
		}

	private:
		void SetBasicMeasurement()
		{
			if (Measurement_Type == LIQUID)
			{
				//Ex: MILLILITRE
				Basic_Medium_Type = PreferredLiquid(Measurement_Default); //Won't Fail
			}
			if (Measurement_Type == WEIGHT)
			{
				//Ex: MILLIGRAM
				Basic_Medium_Type = PreferredWeightMetric(Measurement_Default); //Possible Fail
			}
			if (Measurement_Type == QUANTITY)
			{
				//Ex: QUANTITY
				Basic_Medium_Type = QUANTITY;
			}

			//Ex: 1000 = [LIQUID][MILLILITRE](1.0L)
			Basic_Measurement = litre_kilo_to[Measurement_Type][Basic_Medium_Type](Measurement_Default);
		}

		void SetDescriptiveMeasurement()
		{
			if (Measurement_Type == LIQUID)
			{
				//Ex: MILLILITRE
				Descriptive_Medium_Type = PreferredLiquidforCooking(Measurement_Default); //won't fail
			}
			if (Measurement_Type == WEIGHT)
			{
				//Ex: MILLIGRAM
				Descriptive_Medium_Type = PreferredWeightImperial(Measurement_Default); //won't fail
			}
			if (Measurement_Type == QUANTITY)
			{
				//Ex: QUANTITY
				Descriptive_Medium_Type = QUANTITY;
			}

			//Ex: 1000 = [LIQUID][MILLILITRE](1.0L)
			Descriptive_Measurement = litre_kilo_to[Measurement_Type][Descriptive_Medium_Type](Measurement_Default);
		}
	};

	static map<string, Ingredient_Details> ShoppingList;

	static llBookData* RestaurantBook;
	static ShaderProgram* CurrentShader;
	static RawTexture* CurrentTexture0;
	static RawTexture* CurrentTexture1;
	static RawTexture* CurrentTexture2;
	static NewPage Page_IngredientListCreator;
	static llPageData* IngredientListCreatorOrderDirectory;
//	static BookDirectory ElementsHovered;

	void Prepare();
	void build_2d_conversion_map();
	void Prepare(llBookData* Restaurant_POS, ShaderProgram* ShaderProgram, RawTexture* Texture0, RawTexture* Texture1, RawTexture* Texture2);
	void PrepareContainers(map<string, Section>* Section, map<string, Dish>* Dish, map<string, DishSide>* Side, map<string, Ingredient>* Ingredient, map<string, SameDayOrders>* All_Orders);
	void Update(int CurrentPage, KeyResult* KeyResult);

	//static IngredientList ShoppingList;
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
	static map<string, CustomerOrder> Orders_Selected;
	static PageItemGrid Grid_Shopping_List;
	static Button Button_Remove_Item;
	static PageGroupItem PageItem_Shopping_List_Item;

	void Prepare_Ingredient_List_Creator();

	void Prepare_Customer_Orders();
	void Create_Shopping_List_Item();
	void Create_Shopping_List_Grid();


	void Add_Dish_To_Shopping_List();

	void LoadShoppingList();
	void UpdateShoppingList();
	void Remove_Shopping_list_Item();

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
	void Replace_Ingredient_List_Graphic(Ingredient_Details& Ingredient_Name, llPageItemData* Ordered_Dish_PageItem);
	void Hide_Ingredient_List_Graphic(llPageItemData* PageItem_Dish_Graphic);

	int Get_Conversion_Measurement(int Ingredient_Type, double Measurement_In_Millilitres);
	int Get_Liquid_Conversion_Measurement(double Measurement_In_Millilitres);
	int Get_Weight_Conversion_Measurement(double Measurement_In_Millilitres);

	//Create Ingredient List
	void ConsolidateOrderIngredients(CustomerOrder& ShoppingList);
	void ConsolidateDishIngredients(OrderedDish& Dish);
	void ConsolidateSideIngredients(DishSide& Side, int DishQuantity); //Main Function

	void PrintShoppingList();

	string what_is_the_string(int Measurement_Type);


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

