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

#define QUANTITY 0
#define LIQUID 1
#define WEIGHT 2

#define POUND 0
#define OUNCE 1
#define TON 2
#define GRAM 3
#define MILLIGRAM 4

#define GALLON 5
#define QUART 6
#define PINT 7
#define CUP 8 
#define FUILD_OUNCE 9
#define TABLESPOON 10
#define TEASPOON 11
#define MILLILITRE 12 

typedef double(*Measurement_Function)(const double&); //Points to a liquid function
typedef unordered_map<int, Measurement_Function> ConversionFunctions;
typedef unordered_map<int, ConversionFunctions> Unordered_2d_Map;
	

namespace IngredientListCreator
{
	typedef map<string, double> IngredientList;
	static Unordered_2d_Map litre_kilo_to;
	static Unordered_2d_Map to_litre_kilo;

	void Prepare();

	void build_2d_conversion_map();

	void ConsolidateOrderIngredients(IngredientList& ShoppingList);
	void ConsolidateDishIngredients(IngredientList& ShoppingList);

	void PrintShoppingList(IngredientList& ShoppingList);

	string get_liquid_string(int LiquidType);
	string get_weight_string(int WeightType);

	double Measurement_Conversion(const double& Measurement, int MeasurementType, int Convert_From, int Convert_To);


	//Prints all ingredients in side
	void PrintSideIngredients();


	//-----------------Mass--------------------//

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

