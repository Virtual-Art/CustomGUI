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

void IngredientListCreator::PrepareContainers(map<string, Section>* Section, map<string, Dish>* Dish, map<string, DishSide>* Side, map<string, Ingredient>* Ingredient)
{
	All_Sections = Section;
	All_Dishes = Dish;
	All_Sides = Side;
	All_Ingredients = Ingredient;
}


void IngredientListCreator::ConsolidateOrderIngredients(IngredientList& ShoppingList);
void IngredientListCreator::ConsolidateDishIngredients(IngredientList& ShoppingList);

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

		//Log::LogString("Name:" + Ingredient_Name);
		//Log::LogInt("Measurement Type", Ingredient_Type);
		//Log::LogInt("Medium", Ingredient_Measurment_Medium);

		//Convert Ingredient to Litre/Kilos
		double amount_in_litre_kilo = to_litre_kilo[Ingredient_Type][Ingredient_Measurment_Medium](Ingredient_Measurment);
		double amount_in_teaspoon = litre_kilo_to[LIQUID][CUP](amount_in_litre_kilo);

		//Existing Shopping List Ingredient
		if (ShoppingList.find(Ingredient_Name) != ShoppingList.end())
		{
			//Update Ingredient
			ShoppingList[Ingredient_Name] += amount_in_teaspoon;
		}
		//New Shopping List Ingredient
		else
		{
			//Add Ingredient
			ShoppingList[Ingredient_Name] = amount_in_teaspoon;
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