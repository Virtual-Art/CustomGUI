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
	static BookDirectory ElementsHovered;
	static ButtonFunction CurrentKeyBoardInput;
	static string CurrentText;
	void Prepare_MenuCreator(llBookData* Restaurant_POS, ShaderProgram* ShaderProgram, RawTexture* Texture0, RawTexture* Texture1, RawTexture* Texture2);
	void Update(KeyResult& CurrentKeyResult);                    
	void PrepareMenuContainers(map<string, Section>* Section, map<string, Dish>* Dish, map<string, DishSide>* Side, map<string, Ingredient>* Ingredient);

	static map<string, Ingredient>* All_Ingredients;
	static map<string, DishSide>* All_Sides;
	static map<string, Dish>* All_Dishes;
	static map<string, Section>* All_Sections; //Section Name | Section Object | Dish Names

	//All_? Actually Contains 3 keys

	//You can get 2 Pieces of Information from Section; The Object || All the Dish NAMES accociated with the Section

	void PrintSectionDishes(Section& Current_Section);
	void PrintDishSides(Dish& Current_Dish);
	void PrintSideIngredients(DishSide& Current_Side);

	//static Menu CurrentMenu;

	extern Dish Eight;

	//void PrintTest();

	void Empty();
	void SetCurrentKeyBoardInput();
	void ProcessPrinterInput();              //Sends the User input from keyboard to String/Float Printer
	void KeyboardToCurrentText(KeyResult& CurrentKeyResult);
	void ResetCurrentText();
	//+----------------------------+



	//Section Editor

	//*Clarification* Add Section Creates a dialogue to input Section Details
	//*Clarification* Submit Section Pushes the Section Object into the vector and displays that under 
	//the section label

	//+----------------------------+
	//Section Back-End Variables
	const glm::vec4 Highlight_Section_Color = { 0.5, 0.3, 0.5, 1.0 }; //Light Purple
	const glm::vec4 Section_Color = SubmitOrder::DarkPurple;
	static Section New_Section;			       //(Object) New Section to Modify
	static Section* Current_Section;		   //(Object) Current Section to Modify
	static glm::vec4 last_section_edges;        //(Object) Graphic Reference for the form filler to position with
	static bool first_section;
	static llPageItemData* Section_Graphic_Selected;

	//Section Buttons & Graphics
	static PageGroup PageGroup_Section;	       //(Graphic) Input Section Details 
	static PageGroupItem PageItem_Unused1;     // MUST FIX
	static PageGroupItem PageItem_Default_Section;    // MUST FIX
	static PageGroup PageGroup_Section_Filler; 		   //(Graphic) All Existing Section Graphics
	static Text Text_Label_Section;		       //(Graphic) "Section" Title 
	static Text Text_Add_Section;			   //(Graphic) "Add" Button  
	static Text Text_Submit_Section;		      //(Graphic) Details Filled, Push into vector
	static Text Text_Default_Section_Name;		      //(Graphic) Details Filled, Push into vector
	static Button Button_Add_Section;          //(Direct Function) Calls the Add_Section() Method
	static Button Button_Section_Name;			  //(Button) Links SetPrinter For Keyboard Input
	static Button Button_Submit_Section;         //(Button) Links Submit_Side() to Text_Submit_Side Graphic
	static Button Button_Select_Section;         //(Button) Links Submit_Side() to Text_Submit_Side Graphic
	static NumberPrinter Printer_Section_Name; //(Graphic) Input Section Name 
	static BookDirectory DR_PageGroup_Section;   //(Graphic Helper) Holds the Directory to correctly place new graphic groups
	static llPageItemData* First_Section_Graphic;
	static llPageItemData* Last_Section_Graphic;

	void Prepare_Section();			   //Displays Section title with background
	void Prepare_Section_Filler();			   //Displays Section title with background
	void Add_Section();				   //Displays Graphics to Fill in Dish Details
	void Add_Section_To_Container();
	void Submit_Section();			   //Pushes New Section into Section & Updates Graphics
	void Select_Section();             //User can click on a name and display all dishes in section
	void Highlight_Section(llPageItemData* PageItem_Section_Graphic);
	void Update_Section_Graphics();    //Manages all Section Graphics 
	void Add_Section_Graphic(const string Name);        //Creates a Single Section Graphic
	void Rearrange_Section_Graphics(); //Rearranges the Section Graphics to a particular order
	//+----------------------------+   


	//Dish Editor
	//+----------------------------+
	const glm::vec4 Highlight_Dish_Color = PageCreator::Blue; //Light Purple
	const glm::vec4 Dish_Color = SubmitOrder::DarkPurple;
	static Dish New_Dish;					  //(Object) New Dish to Modify
	static Dish* Current_Dish;				  //(Object) Current Dish to Modify
	static glm::vec4 last_dish_edges;        //(Object) Graphic Reference for the form filler to position with
	static glm::vec4 current_dish_edges;        //(Object) Graphic Reference for the form filler to position with
	static bool first_dish;
	static llPageItemData* Dish_Graphic_Selected;

	static PageGroup PageGroup_Dish;		  //(Graphic) All Existing Dish Graphics
	static PageGroup PageGroup_Dish_Filler;   //(Graphic) Input Dish Details 
	static PageGroupItem PageItem_Unused2;    // MUST FIX
	static PageGroupItem PageItem_Default_Dish;    // MUST FIX
	static Text Text_Default_Dish_Name;       //(Graphic) Side Object Name
	static Text Text_Label_Dish;			  //(Graphic) "Dish" Title 
	static Text Text_Add_Dish;				  //(Graphic) "Add" Button, (Display's Filler)
	static Text Text_Submit_Dish;		      //(Graphic) Details Filled, Push into vector
	static Button Button_Dish_Name;			  //(Button) Links SetPrinter For Keyboard Input
	static Button Button_Add_Dish;            //(Button) Links Add_Side() to Text_Add_Side Graphic
	static Button Button_Submit_Dish;         //(Button) Links Submit_Side() to Text_Submit_Side Graphic
	static Button Button_Select_Dish;         //(Button) Links Submit_Side() to Text_Submit_Side Graphic
	static NumberPrinter Printer_Dish_Name;   //(Graphic) Input Dish Name 
	static NumberPrinter Printer_Cost;		  //(Graphic) Input Dish Cost
	static BookDirectory DR_PageGroup_Dish;   //(Graphic Helper) Holds the Directory to correctly place new graphic groups
	static llPageItemData* First_Dish_Graphic;

	void Prepare_Dish();			          //Displays Dish title with background
	void Prepare_Dish_Form();			      //Prepares Filler GUI for usage
	void Add_Dish();				          //Displays Graphics to Fill in Dish Details
	void Add_Dish_To_Container();
	void Submit_Dish();				          //Pushes New Dish into Dish & Updates Graphics
	void Select_Dish();
	void Highlight_Dish(llPageItemData* PageItem_Dish_Graphic);
	void Update_Dish_Graphics();              //Manages all Dish Graphics 
	void Add_Dish_Graphic(const string Name); //Creates a Single Side Graphic
	void Replace_Dish_Graphic(string Name, llPageItemData* Dish_PageItem);     //Removes a Single Section Graphic
	void Hide_Dish_Graphic(llPageItemData* Dish_ShapeGroup);
	void Rearrange_Dish_Graphics();           //Rearranges the Dish Graphics to a particular order
	//+----------------------------+  



	//Side Editor
	//+----------------------------+
	//Menu Creator "Side" Objects
	const glm::vec4 Highlight_Side_Color = PageCreator::Green; //Light Purple
	const glm::vec4 Side_Color = SubmitOrder::DarkPurple;
	static DishSide New_Side;				 //(Object) New Side to Modify
	static DishSide* Current_Side;			 //(Object) Current Side to Modify
	static glm::vec4 last_side_edges;        //(Object) Graphic Reference for the form filler to position with
	static glm::vec4 current_side_edges;        
	static bool first_side;        			 //TEMPORARY PLEASE REMOVE
	static string String_Default_Name;
	static llPageItemData* Side_Graphic_Selected;

	//Graphical User Interface Objects
	static PageGroup PageGroup_Side;		    //(Graphic) All Existing Side Graphics
	static PageGroup PageGroup_Side_Filler;		//(Graphic) Input Side Details
	static PageGroupItem PageItem_Unused3;      // MUST FIX
	static PageGroupItem PageItem_Default_Side; //(Graphic) 1 Side/??  in Menu->Section->Side
	static Text Text_Default_Side_Name;         //(Graphic) Side Object Name
	static Text Text_Label_Side;			    //(Graphic) "Side" Title
	static Text Text_Add_Side;				    //(Graphic) "Add" Button 
	static Text Text_Submit_Side;		        //(Graphic) Details Filled, Push into vector
	static NumberPrinter Printer_Side_Name;     //(Graphic) Input Side Name
	static Button Button_Side_Name;				//(Button) Links SetPrinter For Keyboard Input
	static Button Button_Dish_Cost;             //(Button) Links SetPrinter For Keyboard Input
	static Button Button_Add_Side;              //(Button) Links Add_Side() to Text_Add_Side Graphic
	static Button Button_Submit_Side;           //(Button) Links Submit_Side() to Text_Submit_Side Graphic
	static Button Button_Select_Side;           //(Button) Links Submit_Side() to Text_Submit_Side Graphic
	static BookDirectory DR_PageGroup_Side;     //(Graphic Helper) Holds the Directory to correctly place new graphic groups
	static NumberPrinter CurrentPrinter;       //(Graphic) Set Keyboard to any printer
	static llPageItemData* First_Side_Graphic;

	void Prepare_Side();			         //Displays Side title with background
	void Prepare_Side_Filler();			     //Prepares Filler GUI for usage
	void Add_Side();				         //Displays Graphics to Fill in Side Details
	void Add_Side_To_Container();
	void Submit_Side();                      //Pushes New Side into Side & Updates Graphics
	void Select_Side();
	void Highlight_Side(llPageItemData* PageItem_Side_Graphic);
	void Update_Side_Graphics();             //Manages all Side Graphics 
	void Add_Side_Graphic(const string Name);                 //Creates a Single Side Graphic
	void Replace_Side_Graphic(string Name, llPageItemData* Side_PageItem);              //Removes a Single Side Graphic
	void Hide_Side_Graphic(llPageItemData* Side_ShapeGroup);
	void Rearrange_Side_Graphics();          //Rearranges the Side Graphics to a particular order


	static Ingredient Editor;
	//+----------------------------+
	const glm::vec4 Highlight_Ingredient_Color = PageCreator::Green; //Light Purple
	const glm::vec4 Ingredient_Color = SubmitOrder::DarkPurple;
	static Ingredient New_Ingredient;            //(Object) New Ingredient to Modify
	static Ingredient* Current_Ingredient;       //(Object) Current Ingredient to Modify
	static glm::vec4 last_ingredient_edges;        //(Object) Graphic Reference for the form filler to position with
	static glm::vec4 current_ingredient_edges;        //(Object) Graphic Reference for the form filler to position with
	static bool first_ingredient;
	
	static PageGroup PageGroup_Ingredient;       //(Graphic) All Existing Ingredient Graphics
	static PageGroup PageGroup_Ingredient_Filler;          //(Graphic) Input Ingredient Details
	static PageGroupItem PageItem_Unused4;   // MUST FIX
	static PageGroupItem PageItem_Default_Ingredient;   // MUST FIX
	static Text Text_Label_Ingredient;           //(Graphic) "Ingredient" Title
	static Text Text_Add_Ingredient;             //(Graphic) "Add" Button 
	static Text Text_Submit_Ingredient;		        //(Graphic) Details Filled, Push into vector
	static Text Text_Default_Ingredient_Name;         //(Graphic) Side Object Name
	static NumberPrinter Printer_Ingredient_Name;     //(Graphic) Input Side Name
	static Button Button_Ingredient_Name;				//(Button) Links SetPrinter For Keyboard Input
	static Button Button_Add_Ingredient;              //(Button) Links Add_Side() to Text_Add_Side Graphic
	static Button Button_Submit_Ingredient;           //(Button) Links Submit_Side() to Text_Submit_Side Graphic
	static Button Button_Select_Ingredient;           //(Button) Links Submit_Side() to Text_Submit_Side Graphic
	static BookDirectory DR_PageGroup_Ingredient;     //(Graphic Helper) Holds the Directory to correctly 
	static llPageItemData* First_Ingredient_Graphic;

	void Prepare_Ingredient();			  //Displays Ingredient title with background
	void Prepare_Ingredient_Form();			     //Prepares Filler GUI for usage
	void Add_Ingredient();                //Displays Graphics to Fill in Ingredient Details
	void Add_Ingredient_To_Container();
	void Submit_Ingredient();			  //Pushes New Ingredient into Side & Updates Graphics
	void Update_Ingredient_Graphics();    //Manages all Ingredient Graphics 
	void Add_Ingredient_Graphic(const string Name);        //Creates a Single Ingredient Graphic
	void Replace_Ingredient_Graphic(string Name, llPageItemData* Side_PageItem);     //Removes a Single Ingredient Graphic
	void Hide_Ingredient_Graphic(llPageItemData* Side_ShapeGroup);
	void Rearrange_Ingredient_Graphics(); //Rearranges the Ingredient Graphics to a particular order
	//+----------------------------+


}

#endif
