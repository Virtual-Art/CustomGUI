#ifndef MENUCREATOR
#define MENUCREATOR

#include <iostream>
#include "SubmitOrder.h"

namespace MenuCreator
{
	//Menu Creator
	//+----------------------------+
	static NewPage Page_MenuCreator;          //(Graphic) All Graphics on the Menu Creator Page 
	static llBookData* RestaurantBook;
	static ShaderProgram* CurrentShader;
	void Prepare_MenuCreator(llBookData* Restaurant_POS, ShaderProgram* ShaderProgram, RawTexture* Texture0, RawTexture* Texture1, RawTexture* Texture2);
	void Update();                     
	//+----------------------------+


	//Section Editor
	//+----------------------------+
	static Section New_Section;			   //(Object) New Section to Modify
	static Section* Current_Section;		   //(Object) Current Section to Modify
	
	static PageGroup PageGroup_Section;	   //(Graphic) Input Section Details 
	static PageGroupItem PageItem_Unused1;    // MUST FIX
	static PageGroup Section_Filler; 		   //(Graphic) All Existing Section Graphics
	static Text Text_Label_Section;		   //(Graphic) "Section" Title 
	static Text Text_Add_Section;			   //(Graphic) "Add" Button  
	static NumberPrinter Printer_Section_Name;		   //(Graphic) Input Section Name 

	void Prepare_Section();			   //Displays Section title with background
	void Add_Section();				   //Displays Graphics to Fill in Dish Details
	void Submit_Section();			   //Pushes New Section into Section & Updates Graphics
	void Update_Section_Graphics();    //Manages all Section Graphics 
	void Add_Section_Graphic();        //Creates a Single Section Graphic
	void Remove_Section_Graphic();     //Removes a Single Section Graphic
	void Rearrange_Section_Graphics(); //Rearranges the Section Graphics to a particular order
	//+----------------------------+   


	//Dish Editor
	//+----------------------------+
	static Dish New_Dish;					  //(Object) New Dish to Modify
	static Dish* Current_Dish;				  //(Object) Current Dish to Modify

	static PageGroup PageGroup_Dish;		  //(Graphic) All Existing Dish Graphics
	static PageGroup Dish_Filler;  		      //(Graphic) Input Dish Details 
	static PageGroupItem PageItem_Unused2;    // MUST FIX
	static Text Text_Label_Dish;			  //(Graphic) "Dish" Title 
	static Text Text_Add_Dish;				  //(Graphic) "Add" Button  
	static NumberPrinter Printer_Dish_Name;   //(Graphic) Input Dish Name 
	static NumberPrinter Printer_Cost;		  //(Graphic) Input Dish Cost

	void Prepare_Dish();			  //Displays Dish title with background
	void Add_Dish();				  //Displays Graphics to Fill in Dish Details
	void Submit_Dish();				  //Pushes New Dish into Dish & Updates Graphics
	void Update_Dish_Graphics();      //Manages all Dish Graphics 
	void Add_Dish_Graphic();          //Creates a Single Dish Graphic
	void Remove_Dish_Graphic();       //Removes a Single Dish Graphic
	void Rearrange_Dish_Graphics();   //Rearranges the Dish Graphics to a particular order
	//+----------------------------+  



	//Side Editor
	//+----------------------------+
	static DishSide New_Side;				 //(Object) New Side to Modify
	static DishSide* Current_Side;			 //(Object) Current Side to Modify
	
	static PageGroup PageGroup_Side;		 //(Graphic) All Existing Side Graphics
	static PageGroup PageGroup_Side_Filler;		     //(Graphic) Input Side Details
	static PageGroupItem PageItem_Unused3;   // MUST FIX
	static Text Text_Label_Side;			 //(Graphic) "Side" Title
	static Text Text_Add_Side;				 //(Graphic) "Add" Button 
	static NumberPrinter Printer_Side_Name;  //(Graphic) Input Side Name

	void Prepare_Side();			         //Displays Side title with background
	void Prepare_Side_Filler();			     //Prepares Filler GUI for usage
	void Add_Side();				         //Displays Graphics to Fill in Side Details
	void Submit_Side();                      //Pushes New Side into Side & Updates Graphics
	void Update_Side_Graphics();             //Manages all Side Graphics 
	void Add_Side_Graphic();                 //Creates a Single Side Graphic
	void Remove_Side_Graphic();              //Removes a Single Side Graphic
	void Rearrange_Side_Graphics();          //Rearranges the Side Graphics to a particular order
	//+----------------------------+



	static Ingredient Editor;
	//+----------------------------+
	static Ingredient New_Ingredient;            //(Object) New Ingredient to Modify
	static Ingredient* Current_Ingredient;       //(Object) Current Ingredient to Modify
	
	static PageGroup PageGroup_Ingredient;       //(Graphic) All Existing Ingredient Graphics
	static PageGroup Ingredient_Filler;          //(Graphic) Input Ingredient Details
	static PageGroupItem PageItem_Unused4
		;   // MUST FIX
	static Text Text_Label_Ingredient;           //(Graphic) "Ingredient" Title
	static Text Text_Add_Ingredient;             //(Graphic) "Add" Button 

	void Prepare_Ingredient();			  //Displays Ingredient title with background
	void Add_Ingredient();                //Displays Graphics to Fill in Ingredient Details
	void Submit_Ingredient();			  //Pushes New Ingredient into Side & Updates Graphics
	void Update_Ingredient_Graphics();    //Manages all Ingredient Graphics 
	void Add_Ingredient_Graphic();        //Creates a Single Ingredient Graphic
	void Remove_Ingredient_Graphic();     //Removes a Single Ingredient Graphic
	void Rearrange_Ingredient_Graphics(); //Rearranges the Ingredient Graphics to a particular order
	//+----------------------------+


}

#endif
