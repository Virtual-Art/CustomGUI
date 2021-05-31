#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Loader.h"
#include "Render.h"
#include "ShaderProgram.h"
#include "Maths.h"
#include "System.h"
#include "Texture.h"
#include "RawTexture.h"
#include "FontMath.h"
#include "FontFileReader.h"
#include "Character.h"
#include "TextSpecification.h"
#include "MouseManager.h"
#include "MemoryManagement.h"
#include "Page.h"
#include "Container.h"
#include "Selection.h"
#include "FileProcessor.h"
#include <Math.h>
#include <sstream>
#include <fileapi.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include "KeyboardManager.h"
#include "Text.h"
#include "Grid.h"
#include "ElementGroup.h"
#include "PageGroup.h"
#include "Action.h"
#include "Oscillation.h"
#include "Linear.h"
#include "Exponential.h"
#include "Logarithmic.h"
#include "ElementAction.h"
#include "Quad.h"
#include "NewCharacter.h"
#include "Slider.h"
#include "Controls.h"
#include "Toggle.h"
#include "PageCreator.h"
#include "PageGroup.h"
#include "MasterElement.h"
#include "NewPage.h"
#include "Button.h"
#include "NumberPrinter.h"
#include "Toggle.h"
#include "DropDownList.h"
#include <forward_list>
#include "SearchBar.h"
//#include "SubmitOrder.h"
#include "Selector.h"
#include "MenuCreator.h"
#include "IngredientListCreator.h"
#include "ApplicationMenu.h"
#include "CompleteOrder.h"
#include "stdExtensioon.h"
#include "PageItemGrid.h"
#include "PageGroupGrid.h"

//string ProcessInputString(GLFWwindow* window);
//void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void WordSearch(map<string, string>& map, string Search, SearchBar* WorkingSearchBar);
void AddWord(map<string, string>& map, string Search);
void PrintMap(map<string, string>& map);
string PerfectFit(string TestString, string ReferenceString);

float Top_Right_Brightness_Vector(float Root, float Top, float Right);
float First_Second_Brightness_Vector(float Root, float First, float Second, float OffsetDegree_Second);
glm::vec4 Sort_Descend(float Top, float Right, float Bottom, float Left);

struct ListNode
{
	int val = -1;
	ListNode* Next = nullptr;
};

ListNode* swapPairs(ListNode* Head);
ListNode* swapPairs2(ListNode* Head);
ListNode* SwapTwoPointers(ListNode* Head, int k);

void RandomTest1()
{
	Log::LogString("TEST 1");
}

void RandomTest2()
{
	Log::LogString("TEST 2");
}

#define RIGHT_DEGREE 0 
#define TOP_DEGREE 90
#define LEFT_DEGREE 180
#define BOTTOM_DEGREE 270

#define PIXEL_RIGHT 0
#define PIXEL_TOP 1
#define PIXEL_BOTTOM 2
#define PIXEL_RIGHT 3

struct PixelSpot
{
	float Root_Brightness;
	float Top_Brightness;
	float Right_Brightness;
	float Bottom_Brightness;
	float Left_Brightness;

	float One_Place;
	float Two_Place;
	float Three_Place;
	float Four_Place;
};

using namespace std;

int main(int argc, char** argv)
{
	Keyboard::Prepare();
	Keyboard::CreateKeyFuncContainer();

	MemoryManagment<int> VertexContainer;
	System System;

	FileSystem FileSystem;
	Book MainBook("ProgramFiles/FirstGUI.Book");

	cout << " System: Width:  " << System.Width << endl;
	cout << " System: Height:  " << System.Height << endl;
	cout << " System: MouseButtonNumber  " << System.MouseButtonNumber << endl;
	cout << " System: last thing  " << System.NumberofMonitors << endl;
	GLFWwindow* window;
	int SCR_WIDTH = 1200; // System.Width; //
	int SCR_HEIGHT = 600; // System.Height - 100; // 

	/* Initialize the library */
	if (!glfwInit())
		return -1;


	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "GUI Library", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glewInit();
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	MouseManager::ScrollInput(window);
	Maths Maths;
	FontMath Font;
	Render Renderer;
	Texture Texture;

	ShaderProgram FontShader("Shaders/FontVS.txt", "Shaders/FontFS.txt");
	ShaderProgram ShapeShader("Shaders/VertexShader.txt", "Shaders/FragmentShader.txt");
	Page GUI(4000);
	GUI.Init(ShapeShader);

	llBookData EditorBook;

	//FileSystem.LoadBook(MainBook, ShapeShader);

	RawTexture Segoe = Texture.CreateTexture("Resources/segoe.png", "FontAtlas", GL_TEXTURE0, 0, GL_RGBA);
	RawTexture RoundedCorners = Texture.CreateTexture("1_SkFEBcaoea9WXIdQg2GsTw.png", "FontAtlas", GL_TEXTURE2, 2, GL_ALPHA);
	NewCharacter AnyCharacter(MainBook.Page[0], "Resources/segoe.fnt");

	Page Editor(400);
	Editor.Init(ShapeShader);

	Page* PageSelected = &MainBook.Page[0];

	//NewPage EditorPage(&EditorBook, &ShapeShader, &ColorCube, &Segoe, &ColorCube);
	//Quad WHY(&EditorBook);
	//WHY.SetPosition({-2.0, 0.0});
	////Text WHYY(&EditorBook);
	PageCreator::llInit(&EditorBook, &ShapeShader, &RoundedCorners, &Segoe, &RoundedCorners);

	//string hiya = "Hello there";
	//llPageItemData Grid_Quad;
	//Grid_Quad.Position = { 0.0, 0.6 };
	//Grid_Quad.InputType = INPUT_LEFT;
	//NumberPrinterData DataText_Grid;
	//DataText_Grid.Description = "Desp";
	//DataText_Grid.Type = TYPE_STRING;
	//DataText_Grid.String = &hiya;
	//NumberPrinter SLIDER_1(&EditorBook, &Grid_Quad, DataText_Grid);
	//
	//NumberPrinterData DataText_Grid1;
	//DataText_Grid1.Description = "Desp";
	////SLIDER_1.SetllPosition({0.5, 0.5});
	////Grid_Quad.InputType = INPUT_CENTER;
	////Grid_Quad.Position = { 0.0, 0.5 };
	//DataText_Grid.Description = "what is going on";
	//NumberPrinter SLIDER_2(&EditorBook, &Grid_Quad, DataText_Grid1);
	////SLIDER_2.OffsetPosition({ 0.0, -0.3 }, {false, true});
	//SLIDER_2.PlaceLeft(SLIDER_1, MATCH_CEILINGS, 10);


	//DataText_Grid.Phrase = "H";
	//DataText_Grid.FontSize = 16;
	////Grid_Quad.Color = PageCreator::Blue;
	//Text TEXT3(&EditorBook, &Grid_Quad, DataText_Grid);
	//TEXT3.PlaceLeft(TEXT2, MATCH_CEILINGS);

	llBookData FILEBook;

	Slider FileTester(&FILEBook);
	Slider FileTester2(&FILEBook);
	Slider FileTester3(&FILEBook);
	llShapeGroupData fail_data;
	TextData Fail_text;
	Fail_text.Phrase = "This will not fail no matter ";
	Text Thiswillfail(&FILEBook, &fail_data, Fail_text);

	CustomerDetails JohnDoe;
	//JohnDoe.FirstName = "First Name";
	//JohnDoe.LastName = "Doe";
	//JohnDoe.Phone = "012 345 6789";
	//JohnDoe.Email = "JohnDoe@hotmail.com";
	//JohnDoe.Address = "465 SomeStreet Dr, Peterborough, ON";

	CustomerDetails KadenCardenasMarett;
	KadenCardenasMarett.FirstName = "Random";
	KadenCardenasMarett.LastName = "Asshole";
	KadenCardenasMarett.Phone = "78454789537";
	KadenCardenasMarett.Email = "Example@gmail.com";
	KadenCardenasMarett.Address = "Weird";

	CustomerDetails Customer1;
	Customer1.FirstName = "sandy";
	CustomerDetails Customer2;
	Customer2.FirstName = "sara";
	CustomerDetails Customer3;
	Customer3.FirstName = "slow";
	CustomerDetails Customer4;
	Customer4.FirstName = "smere";

	using DataBase = map<string, CustomerDetails>;
	DataBase CustomerDataBase;

	using StringBase = map<string, string>;
	StringBase StringDataBase;

	StringDataBase["Sally"] = "Sally";

	AddWord(StringDataBase, "Hello");
	AddWord(StringDataBase, "Sally");
	AddWord(StringDataBase, "Mary");
	AddWord(StringDataBase, "Monday");
	AddWord(StringDataBase, "Home");
	AddWord(StringDataBase, "Perfect");
	AddWord(StringDataBase, "joy");
	AddWord(StringDataBase, "Comfort");
	AddWord(StringDataBase, "Saling");
	AddWord(StringDataBase, "Store");
	AddWord(StringDataBase, "Walmart");
	AddWord(StringDataBase, "Bullshit");
	AddWord(StringDataBase, "wtf");
	AddWord(StringDataBase, "Random");
	AddWord(StringDataBase, "Computer");
	AddWord(StringDataBase, "Order");
	AddWord(StringDataBase, "Judge");
	AddWord(StringDataBase, "Judy");
	AddWord(StringDataBase, "Shly");
	AddWord(StringDataBase, "Shy");
	AddWord(StringDataBase, "BaseBall");



	CustomerDataBase[KadenCardenasMarett.FirstName] = KadenCardenasMarett;
	CustomerDataBase[JohnDoe.FirstName] = JohnDoe;
	CustomerDataBase[Customer1.FirstName] = Customer1;
	CustomerDataBase[Customer2.FirstName] = Customer2;
	CustomerDataBase[Customer3.FirstName] = Customer3;
	CustomerDataBase[Customer4.FirstName] = Customer4;



	for (auto kv : CustomerDataBase)
	{
		auto& Key = kv.first;

		if (Key[0] == 's' && Key[1] == 'a')
		{
			cout << "Key:" << Key << endl;
		}
	}

	//WHYY.SetllText("WHYYYYYYYYYY");
	//WHYY.SetllPosition({0.0, 0.9});

	PageItemData PageItem_FirstSlider;
	SliderData Slider_FirstSlider;

	//Slider 1
	PageItem_FirstSlider.Position = { 0.0, -0.2 };
	Slider_FirstSlider.Description = "Hello";
	Slider_FirstSlider.Ratio = "14.35";
	PageItem_FirstSlider.Position = { 0.0, -0.3 };
	Slider FirstSlider1(MainBook.Page[0], PageItem_FirstSlider, Slider_FirstSlider);

	//Slider 2
	Slider_FirstSlider.Description = "Hello";
	Slider_FirstSlider.Ratio = "14.37";
	PageItem_FirstSlider.Position = { 0.0, -0.4 };
	Slider FirstSlider2(MainBook.Page[0], PageItem_FirstSlider, Slider_FirstSlider);

	//Slider 3
	Slider_FirstSlider.Description = "Hello";
	Slider_FirstSlider.Ratio = "14.38";
	PageItem_FirstSlider.Position = { 0.0, -0.5 };
	Slider FirstSlider3(MainBook.Page[0], PageItem_FirstSlider, Slider_FirstSlider);

	PageItem_FirstSlider.Position = { 0.0, -0.6 };
	Slider UnusedSlider(GUI, PageItem_FirstSlider, Slider_FirstSlider);
	//UnusedSlider.SetPosition({ 0.6, -0.7 });
	//UnusedSlider.SetPosition({ 0.6, -0.7 }); // Slider Replace adds 10 shape offset every replace
	//UnusedSlider.SetPosition({ 0.6, -0.7 }); // to fix this we need to have the slider shape group count go back to it's spot in the shape group
	UnusedSlider.SetSize({ 0.2, 0.1 });
	UnusedSlider.SetDescription("HelloWorld");
	//	UnusedSlider.PrintGroupShapes();
		//UnusedSlider.ReCalibrateID();

	float Time;
	float PreviousTime;
	unsigned int EditorShapeDataHovered;
	unsigned int GUIShapeDataHovered;

	llBookData Gamee;


	NewPage FistPage(&Gamee, &ShapeShader, &RoundedCorners, &Segoe, &RoundedCorners);

	//MasterElement::AddPageToBook(&Gamee);
	//MasterElement::AddPageToBook(&Gamee);
	//MasterElement::AddPageToBook(&Gamee);
	//MasterElement::AddPageToBook(&Gamee);
	//MasterElement::AddPageToBook(&Gamee);
	//MasterElement::AddPageToBook(&Gamee);
	//MasterElement::AddPageToBook(&Gamee);
	//MasterElement::AddPageToBook(&Gamee);
	//MasterElement::AddPageToBook(&Gamee);
	//MasterElement::AddPageToBook(&Gamee);
	//MasterElement::AddPageToBook(&Gamee);
	//MasterElement::AddPageToBook(&Gamee);
	//MasterElement::AddPageToBook(&Gamee);
	//MasterElement::AddPageToBook(&Gamee);
	//MasterElement::PrintBook(&Gamee);
	//
	////Gamee would keep track of the counts 
	////As well as the current element it's on regardless on insertion and deletion
	//Slider llSlider(&Gamee);
	TextData yaat_t;
	yaat_t.Phrase = "PeeMart";
	llShapeGroupData yaat;
	yaat.Position = { 0.0, 0.9 };
	//-----------------------------------//
	Quad llQuad0(&Gamee); //TYPE_QUAD
	Quad llQuad1(&Gamee); //TYPE_QUAD
	Quad llQuad3(&Gamee); //TYPE_QUAD
	Quad llQuad2(&Gamee); //TYPE_QUAD
	Text llText0(&Gamee, &yaat, yaat_t); //TYPE_TEXT_QUAD * 10
	//-----------------------------------//
	//Text llText1(&EditorBook, &yaat, yaat_t);
	//Quad llQuad10(&EditorBook);
	//Quad llQuad11(&EditorBook);
	//-----------------------------------//

	//llQuad10.SetPosition({0.8, 0.9});
	//llQuad11.SetPosition({0.8, 0.8});

	//llText1.SetllPosition({ 0.0, -0.888 });

	//MasterElement::PrintShapeGroupShapes(*llText1);

	SliderData llSD;
	llSD.Description = "Desp";
	llSD.Ratio = "34.3";
	llPageItemData PID;
	PID.Position = { 0.3, 0.3 };

	Slider llSlider(&Gamee, &PID, llSD);

	////////Last Spot//////////
	//llSlider.SetllPosition({ - 0.7, 0.7, });
	///////////////////////////

	//NewCharacter SwitchChar(llText1.GetShapeGroup()->Shape);

	llPageItemData* CurrentWorkingPageItem = Gamee.Page->PageGroup->PageItem;

	//Print As Second
	//MasterElement::PrintPageItemShapeGroups(llSlider.GetPageItem());
	//MasterElement::PrintPageItemShapes(llSlider.GetPageItem());
	//MasterElement::PrintBookStats(&Gamee);

	//Find Head
	while (CurrentWorkingPageItem->Previous != nullptr)
	{
		CurrentWorkingPageItem = CurrentWorkingPageItem->Previous;
	}
	int ShapeGroupCount = 0;
	//Print to tail
	while (CurrentWorkingPageItem != nullptr)
	{
		//MasterElement::PrintPageItemShapes(CurrentWorkingPageItem);
		CurrentWorkingPageItem = CurrentWorkingPageItem->Next;
		cout << ShapeGroupCount++ << endl;
	}

	//MasterElement::PrintBookStats(&Gamee);

	for (int i = 0; i < argc; i++)
	{
		argv[i];
	}

	glm::vec2 MousePosition = { MouseManager::xPos, MouseManager::yPos };

	llPageItemData NumberGroup;
	NumberGroup.Position = { -0.98, -0.94 };
	NumberGroup.Color = { 0.0, 0.5, 1.0, 1.0 };

	NumberPrinterData NewVec2_Data;
	NewVec2_Data.Description = "Mouse";
	NewVec2_Data.Type = TYPE_VEC2;
	NewVec2_Data.VEC2 = &MousePosition;

	//NumberPrinter NewVec2(&EditorBook, &NumberGroup, NewVec2_Data);

	llPageItemData PageItem_Toggle;
	PageItem_Toggle.Position = { -0.89, -0.3 };

	llBookData NEWBOOK;

	//FileSystem.SavellBook(FILEBook, "ProgramFiles/FirstGUI.Book");

	cout << "+--------------------------------+" << endl;
	//FileSystem.LoadllBook(FILEBook, "ProgramFiles/FirstGUI.Book");

	//MasterElement::PrintBookStats(&FILEBook);

	//Create
	/*ListNode* One = new ListNode;
	ListNode* Two = new ListNode;
	ListNode* Three = new ListNode;
	ListNode* Four = new ListNode;
	ListNode* Five = new ListNode;
	ListNode* Six = new ListNode;

	//Set and Link
	One->val = 1;
	One->Next = Two;
	Two->val = 2;
	Two->Next = Three;
	Three->val = 3;
	Three->Next = Four;
	Four->val = 4;
	Four->Next = Five;
	Five->val = 5;
	Five->Next = Six;
	Six->val = 6;



	ListNode* NewList = One;
	forward_list<ListNode*> Node_List = {One};

	auto iter = Node_List.begin();

	iter = Node_List.insert_after(iter, Two);
	iter = Node_List.insert_after(iter, Three);
	iter = Node_List.insert_after(iter, Four);
	iter = Node_List.insert_after(iter, Five);
	iter = Node_List.insert_after(iter, Six);

	while (NewList != nullptr)
	{
		NewList = NewList->Next;
	}

	for (auto it: Node_List)
	{
		cout << "val in container " << it->val << endl;
	}

	NewList = SwapTwoPointers(One, 2);

	while (NewList != nullptr)
	{
		cout << NewList->val << endl;
		NewList = NewList->Next;
	} */

	llBookData Book_Restaurant_POS;

	////////////////////////////////////////////////////////////////////////////////////////

	//Order Containers
	map<string, SameDayOrders> All_Customer_Orders;

	//Menu Containers
	map<string, Ingredient> All_Ingredients; // Key: Name | Value: Ingredient Measurement Type, Gluten
	map<string, DishSide> All_Sides;   //Holds Side Name   : Side Data : Set of Ingdt Names
	map<string, Dish> All_Dishes;      //Holds Dish Name   : Dish Data : Set of Side  Names
	map<string, Section> All_Sections; //Holds Sctn Name   : Sctn Data : Set of Dish  Names

	////////////////////////////////////////////////////////////////////////////////////////


	llPageItemData PageItem_Template;
	PageItem_Template.Position = { -0.3, 0.95 };
	//PageItem_Template.BackGround = true;
	PageItem_Template.BackGroundColor = { 1.0, 0.0, 1.0, 1.0 };
	PageItem_Template.BackGroundPadding = { 20, 20, 20, 20 };
	SelectorData Selector_Template;
	Selector_Template.Selector[0] = "Soups";
	Selector_Template.Selector[1] = "Frozen";
	Selector_Template.Selector[2] = "Hot Ready";
	Selector_Template.Selector[3] = "Food Box";
	Selector_Template.Selector[4] = "Smoked Meat";
	Selector_Template.Selector[5] = "Keto Diet";
	Selector_Template.Selector[6] = "Vegetarian";
	Selector_Template.Selector[7] = "Gluten Free";
	Selector_Template.ColumnsRows = { 4, 2 };
	Selector_Template.XSpacing = 120;
	Selector_Template.YSpacing = 50;
	Selector First_Selector(&Book_Restaurant_POS, &PageItem_Template, Selector_Template);

	NumberPrinterData Tiredofthis;
	Tiredofthis.Type = TYPE_VEC2;
	Tiredofthis.VEC2 = &MousePosition;

	llPageItemData boooo;
	boooo.Position = { 0.9, 0.95 };

	NumberPrinter sigh_MousePosition(&Book_Restaurant_POS, &boooo, Tiredofthis);

	SubmitOrder::PrepareSubmitContainers(&All_Sections, &All_Dishes, &All_Sides, &All_Ingredients, &All_Customer_Orders);
	SubmitOrder::Prepare(&Book_Restaurant_POS, &ShapeShader, &RoundedCorners, &Segoe, &RoundedCorners);

	//SelectorActions::Prepare(&Book_Restaurant_POS); //ElementsHovered would be in Book
	SelectorActions::Prepare(&Book_Restaurant_POS);
	SearchBarActions::Prepare(&Book_Restaurant_POS);
	NumberPrinterActions::Prepare(&Book_Restaurant_POS);

	ApplicationMenu::PrepareContainers(&All_Sections, &All_Dishes, &All_Sides, &All_Ingredients, &All_Customer_Orders);
	ApplicationMenu::Prepare(&Book_Restaurant_POS, &ShapeShader, &RoundedCorners, &Segoe, &RoundedCorners);

	MenuCreator::Prepare_MenuCreator(&Book_Restaurant_POS, &ShapeShader, &RoundedCorners, &Segoe, &RoundedCorners);
	MenuCreator::PrepareMenuContainers(&All_Sections, &All_Dishes, &All_Sides, &All_Ingredients);
	MenuCreator::Update_Section_Graphics();

	IngredientListCreator::PrepareContainers(&All_Sections, &All_Dishes, &All_Sides, &All_Ingredients, &All_Customer_Orders);
	IngredientListCreator::Prepare(&Book_Restaurant_POS, &ShapeShader, &RoundedCorners, &Segoe, &RoundedCorners);



	Log::LogString("start---------------------------------end");

	double Tons;
	double Kilos;
	double Ounces = 4567;
	double Grams;
	double Milligrams;

	double Litre;
	double TableSpoon = 7;
	double Teaspoon;
	double Quart;

	//map<string, double> IngredientList;
	//IngredientList["Lemon"] = 2;
	//IngredientList["Orange"] = 3.453;
	//IngredientList["Strawberry"] = 4578.45;
	//IngredientList["BlueBerry"] = 56;

	//IngredientListCreator::PrintShoppingList(IngredientList);

	double Measurement = 4;

	//double Result = IngredientListCreator::Measurement_Conversion(Measurement, LIQUID, CUP, MILLILITRE);
	//Log::LogDouble("Result: ", Result);

	Ingredient Lemon;
	Lemon.Name = "Lemon";
	Lemon.MeasurementType = QUANTITY;
	
	Ingredient Milk;
	Milk.Name = "Milk";
	Milk.MeasurementType = LIQUID;
	
	Ingredient Olive_Oil;
	Olive_Oil.Name = "Olive Oil";
	Olive_Oil.MeasurementType = LIQUID;
	
	Ingredient Soya_Sauce;
	Soya_Sauce.Name = "Soya Sauce";
	Soya_Sauce.MeasurementType = LIQUID;
	
	Ingredient Water;
	Water.Name = "Water";
	Water.MeasurementType = LIQUID;
	
	Ingredient Sesame_Oil;
	Sesame_Oil.Name = "Sesame Oil";
	Sesame_Oil.MeasurementType = LIQUID;
	
	All_Ingredients[Lemon.Name] = Lemon;
	
	All_Ingredients[Milk.Name] = Milk;
	All_Ingredients[Olive_Oil.Name] = Olive_Oil;
	All_Ingredients[Soya_Sauce.Name] = Soya_Sauce;
	All_Ingredients[Water.Name] = Water;
	All_Ingredients[Sesame_Oil.Name] = Sesame_Oil;


	//
	//
	//DishSide FirstIngredientSide;
	//FirstIngredientSide.Name = "First Side!";
	//FirstIngredientSide.Ingredient_Names[Lemon.Name] = {0.5, QUANTITY};
	//FirstIngredientSide.Ingredient_Names[Milk.Name] = {1.0, CUP};
	//FirstIngredientSide.Ingredient_Names[Olive_Oil.Name] = {3.0, TABLESPOON};
	//FirstIngredientSide.Ingredient_Names[Soya_Sauce.Name] = {1.5, TABLESPOON};
	//FirstIngredientSide.Ingredient_Names[Water.Name] = {4, CUP};
	//
	//DishSide SecondIngredientSide;
	//SecondIngredientSide.Name = "First Side!";
	//SecondIngredientSide.Ingredient_Names[Lemon.Name] = { 2, QUANTITY };
	//SecondIngredientSide.Ingredient_Names[Milk.Name] = { 3.0, TABLESPOON};
	//SecondIngredientSide.Ingredient_Names[Olive_Oil.Name] = { 2, TABLESPOON };
	//SecondIngredientSide.Ingredient_Names[Soya_Sauce.Name] = { 1, TEASPOON};
	//SecondIngredientSide.Ingredient_Names[Water.Name] = { 1, CUP };
	//SecondIngredientSide.Ingredient_Names[Sesame_Oil.Name] = { 0.5, TEASPOON};

	//IngredientListCreator::ConsolidateSideIngredients(FirstIngredientSide);
	//IngredientListCreator::ConsolidateSideIngredients(SecondIngredientSide);
	//IngredientListCreator::PrintShoppingList();

	//Add some Dishes




	float LEFT_BRIGHTNESS = 40;

	float TOP_BRIGHTNESS = 60;
	float RIGHT_BRIGHTNESS = 30; //Right is Brighter than top
	float ROOT_BRIGHTNESS = 0;
	//*--------------------------------------------------------*//
	float COUNTER_BRIGHTNESS = 60; //top
	float CLOCKWISE_BRIGHTNESS = 0; //right
	//*--------------------------------------------------------*//

	float DegreeInput_Clockwise = 0; // 0 | 90 | 180 | 270

	//Log::LogFloat("Top_Right Direction (Deg): ", Top_Right_Brightness_Vector(ROOT_BRIGHTNESS, RIGHT_BRIGHTNESS, TOP_BRIGHTNESS)); //Difference in pixel brightness between rig
	//Log::LogFloat("Left_Top Direction (Deg): ", Left_Top_Brightness_Vector(ROOT_BRIGHTNESS, LEFT_BRIGHTNESS, TOP_BRIGHTNESS));
	//Log::LogFloat("First_Second Direction (Deg): ", First_Second_Brightness_Vector(ROOT_BRIGHTNESS, COUNTER_BRIGHTNESS, CLOCKWISE_BRIGHTNESS, DegreeInput_Clockwise));

	float Top = 0.0;
	float Right = 0.0;
	float Bottom = 0.0;
	float Left = 0.0;

	//We can sort pixels
	Log::LogString("Sort Descend");
	glm::vec4 Sorted_Pixels = Sort_Descend(Top, Right, Bottom, Left);

	//how do we know which spot got switched too?

	//Map_Test<string, Dish> CopyMap;
	//CopyMap.Current_Map = &All_Dishes;
	//
	//Log::LogString("Printing Map");
	//for (auto it : *CopyMap.Current_Map)
	//{
	//	Log::LogString(it.first);
	//}
	//
	//Log::LogString("Extracting Keys");
	//for (const auto& Element : search_map("O", All_Dishes))
	//{
	//	Log::LogString(Element);
	//}

	llBookData Book_Trash;
	NewPage Page_Trash(&Book_Trash, &ShapeShader, &RoundedCorners, &Segoe, &RoundedCorners);

	//Example Customer
	//TextData Basic_Cusomter;
	//llShapeGroupData ShapeGroup_Basic_Customer;
	//ShapeGroup_Basic_Customer.Position = {0.0, 0.0};
	//PageGroupItem PageItem_Trash(&Book_Trash);
	//Basic_Cusomter.Phrase = "Kaden Cardenas-Marett";//"Kaden Cardenas-Marett";
	//Text Text_ONE(&Book_Trash, &ShapeGroup_Basic_Customer, Basic_Cusomter);
	//Basic_Cusomter.Phrase = "10 Items Ordered";//"10 Ordered Items";
	//Text Text_TWO(&Book_Trash, &ShapeGroup_Basic_Customer, Basic_Cusomter);
	//Text_TWO.PlaceBelow(Text_ONE.GetEdges(), MATCH_BEGINNINGS, 10);
	//Basic_Cusomter.Phrase = "836 Talwood Dr";//"10 Ordered Items";
	//Text Text_THREE(&Book_Trash, &ShapeGroup_Basic_Customer, Basic_Cusomter);
	//Text_THREE.PlaceBelow(Text_TWO.GetEdges(), MATCH_BEGINNINGS, 10);
	//Basic_Cusomter.Phrase = "$157";//"10 Ordered Items";
	//ShapeGroup_Basic_Customer.Color = PageCreator::Green;
	//Text Text_FOUR(&Book_Trash, &ShapeGroup_Basic_Customer, Basic_Cusomter);
	//Text_FOUR.PlaceBelow(Text_THREE.GetEdges(), MATCH_BEGINNINGS, 10);
	////PageItem_Trash.SetllPosition({0.0, 0.0});
	////Example Customer
	//
	//////Exmaple Day
	//PageItemGridData ItemGrid_Basic_Customer;
	//ItemGrid_Basic_Customer.RowCount = 1;
	//ItemGrid_Basic_Customer.ResultCount = 3; //3 Page Items Created
	//ItemGrid_Basic_Customer.xPadding = 90;
	//ItemGrid_Basic_Customer.yPadding = 40;
	//ItemGrid_Basic_Customer.Description = "Thursday, January 1st 2021 ------------------------------------------------------------------------------";
	//ItemGrid_Basic_Customer.DescriptionColor = SubmitOrder::Pink;
	//ItemGrid_Basic_Customer.DescriptionyPadding = 70;
	//llPageGroupData PageGroup_Basic_Customer;
	//PageGroup_Basic_Customer.Position = {-0.7, 0.0};
	//Log::LogString("---------------------Creating Same Day Order PageGroup--------------------");
	//PageItemGrid PageItemGrid_Trash(&Book_Trash, &PageGroup_Basic_Customer, PageItem_Trash.GetData(), ItemGrid_Basic_Customer);
	//
	//
	//PageItemGrid PageItemGrid_Copy(PageItemGrid_Trash.GetData()); //Working
	//PageItemGrid_Copy.LoadedBook = &Book_Trash;
	//PageItemGrid_Copy.SetDescription("February 2nd YOLO");
	//PageItemGrid_Copy.SetResultCount(6);
	//
	////Log::LogString("Setting PAGEGROUP1");
	////PageItemGrid_Trash.SetllPosition({-0.1, 0.3}, INPUT_LEFT); //position is doubled
	////Log::LogString("Finished Setting PAGEGROUP1");
	//////Exmaple Day
	//
	//////Example DataBase
	//PageGroupGridData GroupGrid_BasicCustomer;
	//GroupGrid_BasicCustomer.InputType = INPUT_LEFT;
	//GroupGrid_BasicCustomer.Position = {-0.7, 0.5};
	//GroupGrid_BasicCustomer.ColumnCount = 1;
	//GroupGrid_BasicCustomer.ResultCount = 4;
	//GroupGrid_BasicCustomer.yPadding = 100;
	//PageGroupGrid PageGroupGrid_Trash(&Book_Trash, Page_Trash.GetData(), PageItemGrid_Trash.GetData(), GroupGrid_BasicCustomer, &ShapeShader, &RoundedCorners, &Segoe, &RoundedCorners);

	////Example DataBase


	Log::LogString("Before Containers Prepare");
	CompleteOrder::PrepareContainers(&All_Sections, &All_Dishes, &All_Sides, &All_Ingredients, &All_Customer_Orders);
	CompleteOrder::Prepare(&Book_Restaurant_POS, &ShapeShader, &RoundedCorners, &Segoe, &RoundedCorners);


	typedef void(*Master_P)();
	while (!glfwWindowShouldClose(window))
	{
		MousePosition = { MouseManager::xPos, MouseManager::yPos };

		Time = glfwGetTime();
		PreviousTime = glfwGetTime();
		glClearColor(0.08, 0.05, 0.07, 1.0); //{} 0.091, 0.14, 0.14, 1.0
		glClear(GL_COLOR_BUFFER_BIT);

		//Setup
		int MouseState = MouseManager::GetMouseState(window, glfwGetTime(), 0.3, 0.4);
		Keyboard::GetKeyBoardState(window, glfwGetTime(), 0.3, 0.4);
		KeyResult& KeyState = Keyboard::GetState();
		//EditorShapeDataHovered = MainBook.Page[0].FindShapeData(MouseManager::xPos, MouseManager::yPos, false);
		//GUIShapeDataHovered = GUI.FindShapeData(MouseManager::xPos, MouseManager::yPos, false);
		PageCreator::OnUpdate(KeyState, MouseState);
	
		Keyboard::TextKeepTrack();
		//sigh_MousePosition.SetVec2(MousePosition);
		//Restaurant POS
		//+-------------------------+
			                                             
		int Page_To_Render = ApplicationMenu::Update();
		//SubmitOrder::Update(Page_To_Render, KeyState);            
		//IngredientListCreator::Update(Page_To_Render, &KeyState); 
		//MenuCreator::Update(KeyState, Page_To_Render);            
		////Log::LogString("Complete Order");
		//CompleteOrder::Update(KeyState, Page_To_Render);	      
		//Book_Restaurant_POS.Update();					          
		//NumberPrinterActions::Update();					 
		//SearchBarActions::Update();						 
		//Page_Trash.DrawPage();
		//+-------------------------+

		PageGroupItem* jaj = &llSlider;
		Slider Complex(jaj->GetData());

		//MasterElement::FindElement(&EditorBook, LEVEL_SHAPE);

		//NewVec2.llUpdate();

		//EditorPage.DrawPage();

		if (KeyState.Key1 == GUI_I_CLICKED && KeyState.Ctrl == true)
		{
			SubmitOrder::PrintAllOrders();
		}
		
		if (KeyState.Key1 == GUI_O_CLICKED)
		{
			//MasterElement::PrintBookStats(&PageCreator::CreatorBook);
		}

		if (KeyState.Key1 == GUI_M_CLICKED)
		{
			//PageCreator::PrintCreatorStats();
		}

		//Log::LogVec2("", MousePosition);

		//a SliderPointer points to a function that belongs to slider
		typedef void(MasterElement::* MasterElementFunction)();

		//Create a SliderPointer
		MasterElementFunction VirtualTest_Function;

		//Set the Slider Pointer to point to a one of the Sliders functions
		//SetSlider is the Slider function that Slider Pointer will point to
		VirtualTest_Function = &MasterElement::VirtualTest;
		
		//Create a Slider to use
		Slider SliderExecute;

		//Slider to use -> Play whatever Slider Function SliderTable is pointing too
		//(SliderExecute.*VirtualTest_Function)();
		//this exact line of code can play any Slider Function

		//Working
		if (KeyState.Key1 == GUI_P_CLICKED && KeyState.Ctrl == true)
		{
			PageCreator::SetCustomerDetails(&JohnDoe);
		}

		//Working
		if (KeyState.Key1 == GUI_H_CLICKED && KeyState.Ctrl == true)
		{
			PageCreator::SetCustomerDetails(&KadenCardenasMarett);
		}

		//Working
		//if (KeyState.Key1 == GUI_G_CLICKED)
		//{
		//	PageCreator::SetCustomerDetails(nullptr);
		//}


		if (KeyState.Key1 == GUI_G_CLICKED)
		{
			//MasterElement::PrintBookStats(&EditorBook);
			//ComputerButton.PlayLogicalActions();
			//Log::LogString("Up with shift");
		}
		//Renderer.DrawPage(ShapeShader, ColorCube, Segoe, ColorCube, GUI);
		//Renderer.DrawPage(ShapeShader, ColorCube, Segoe, ColorCube, *PageSelected);

		MouseManager::GetMousePosition(window);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	Editor.DeletePage();
	GUI.DeletePage();
	MasterElement::EraseBook(&EditorBook);
	MasterElement::EraseBook(&Book_Restaurant_POS);
	MasterElement::EraseBook(&PageCreator::CreatorBook);
	return 0;
}


ListNode* swapPairs(ListNode* Head)
{
	//Validate
	if (Head == nullptr) { return Head; }
	if (Head->Next == nullptr) { return Head; }

	ListNode* NewHead = Head->Next;
	ListNode* CurrentPair = Head;
	ListNode* LastPairSecond = nullptr;

	while (CurrentPair != nullptr && CurrentPair->Next != nullptr)
	{
		//Working
		ListNode* First   = CurrentPair;
		ListNode* Second  = CurrentPair->Next;
		ListNode* NextPair = Second->Next;

		//Swaps
		First->Next = NextPair;
		Second->Next = First;

		if (LastPairSecond != nullptr)
		{
			LastPairSecond->Next = Second;
		}

		//Working
		LastPairSecond = First;
		CurrentPair = NextPair;
	}

	//1234 //Start
	//2134 //Transition
	//2143 //Answer
	return NewHead;
}


ListNode* swapPairs2(ListNode* Head)
{
	//Validate
	if (Head == nullptr) { return Head; }


	//Loop through Swaps

	//Swap

	//Prev
	ListNode* FirstPrevious;
	ListNode* SecondPrevious;

	//Actuals
	ListNode* First;
	ListNode* Second;
	ListNode* CopySecond = Second;

	//Attach New Beginning
	FirstPrevious->Next = Second; // Second Must Be Valid
	Second->Next = First->Next; //First Must Be Valid 

	//Attach New End
	First->Next = CopySecond->Next;
	SecondPrevious = First;

	return Head;
}



ListNode* SwapTwoPointers(ListNode* Head, int k)
{
	if (Head == nullptr) { return Head; }


	//My Attempt at starting to use STL//


	ListNode* First = nullptr;
	ListNode* FirstPrev = nullptr;

	ListNode* Second = nullptr;
	ListNode* SecondPrev = nullptr;
	ListNode* LastLink = nullptr;

	ListNode* Sift = Head;

	int Track = 0;

	map<int, ListNode*> NodeList;

	while (Sift != nullptr)
	{
		NodeList[Track] = Sift;
		Track++;
		Sift = Sift->Next;
	}

	int SwapPosition = k;

	while (SwapPosition != (NodeList.size()/2))
	{

		//Setup Pointers
		First = NodeList[SwapPosition - 1];
		FirstPrev = NodeList[SwapPosition - 2];
		Second = NodeList[NodeList.size() - SwapPosition];
		SecondPrev = NodeList[NodeList.size() - SwapPosition - 1];
		LastLink = Second->Next;


		//////////////////////SWAP:

		//Attach New Beginning
		FirstPrev->Next = Second; // Second Must Be Valid

		//Non Side by Side Case
		if (Second->Next != First->Next)
		{
			//Normal
			Second->Next = First->Next; //First Must Be Valid 
			First->Next = LastLink;
			SecondPrev->Next = First;
		}
		else
		{
			//Side By Side case
			First->Next = LastLink;
			Second->Next = First;
		}

		//Attach New End

		++SwapPosition;
	}
	
	///////////////////END SWAP

	return Head;
}

void AddWord(map<string, string>& map, string Word)
{
	map[Word] = Word;
}

void WordSearch(map<string, string>& map, string Search, SearchBar* WorkingSearchBar)
{
	Log::LogString("WordSearch");
	float Time1 = glfwGetTime();
	int Count = 0;
	//WorkingSearchBar->SetCount(Count);
	WorkingSearchBar->CurrentSearchBar.SearchString = Search;
	//Go through Entire List
	for (auto kv : map)
	{
		auto& Key = kv.first;

		string Match;
		//Check to see if the string matches up 


		Match = PerfectFit(Key, Search);

		if (Match != " " && Count < 19)
		{
			WorkingSearchBar->CurrentSearchBar.Results[Count] = Match;
			//WorkingSearchBar->SetCount(Count + 1);
			Log::LogString("Adding Match");
			Log::LogString(Match);
			Log::LogInt(" ", Count);
			Count++;
		}
	}
	float Time2 = glfwGetTime();

	Log::LogFloat("Execution Time", Time2 - Time1);
}

string PerfectFit(string TestString, string ReferenceString)
{
	if (TestString.size() < ReferenceString.size()) { return " "; }

	//Go through all Characters in Reference String 
	for (int i = 0; i < ReferenceString.size(); ++i)
	{
		int AddorSub = 0;

		if (ReferenceString[i] > 97)
		{
			AddorSub = -32;
		}
		else
		{
			AddorSub = 32;
		}

		//Compare letters
		if (TestString[i] != ReferenceString[i] && TestString[0] != ReferenceString[i] + AddorSub)
		{
			//Exit if strings stop matching
			return " ";
		}
	}

	return TestString;
}

void PrintMap(map<string, string>& map)
{
	for (auto kv : map)
	{
		auto& Key = kv.first;


		cout << "Key:" << Key << endl;
	}

}



//Working
//Returns the direction (vector Deg) of the brightest node
//if both nodes are brighter than the root, interpolation occurs to the vector

//Top  == 40
//Left == 0
//Root == 0

//Working
//Returns the direction (vector Deg) of the brightest node
//if both nodes are brighter than the root, interpolation occurs to the vector
float Top_Right_Brightness_Vector(float Root, float Right, float Top)
{
	float Percentage_0_45;
	float Root_Right_Diff;
	float Root_Top_Diff;
	float MAX_RIGHT_ANGLE_DEG = 45.0;
	float MAX_TOP_ANGLE_DEG = 90.0;
	int EQUAL_ANGLE = 45;

	//Compare Difference in brightness between root and node
	Root_Right_Diff = Right - Root;
	Root_Top_Diff = Top - Root;

	//if both nodes are darker than the root node
	//*there is no valid vector as we want to point to brightness*//
	if (Root_Right_Diff < 0 && Root_Top_Diff < 0) { return -1.0; } //No Appropriate vector angle

	//One Node can be darker than the root thats fine
	//but we need to set that darkness node to zero for proper calucalation of brightness vector
	if (Root_Right_Diff < 0) { Root_Right_Diff = 0; } //No Negatives for calculations
	if (Root_Top_Diff < 0) { Root_Top_Diff = 0; } //No Appropriate vector angle



	//Right is the brighter than top   //DONE
	if (Root_Right_Diff > Root_Top_Diff)
	{
		Percentage_0_45 = Root_Top_Diff / Root_Right_Diff;
		return Percentage_0_45 * MAX_RIGHT_ANGLE_DEG;
	}

	//Top is brighter than right //DONE
	if (Root_Top_Diff > Root_Right_Diff)
	{
		Percentage_0_45 = Root_Right_Diff / Root_Top_Diff;
		float Vector_Angle = Percentage_0_45 * MAX_RIGHT_ANGLE_DEG;
		return MAX_TOP_ANGLE_DEG - Vector_Angle;
	}

	//Both are equal in brightness //DONE
	if (Root_Top_Diff == Root_Right_Diff)
	{
		return EQUAL_ANGLE;
	}

}



//Working
//Returns the direction (vector Deg) of the brightest node
//if both nodes are brighter than the root, interpolation occurs to the vector
//offset in degrees = 0 (right) | 90 (top) | 180 (left) | 270 (bottom) 
float First_Second_Brightness_Vector(float Root, float First, float Second, float OffsetDegree_Second)
{
	float Percentage_0_45;
	float Root_Second_Diff;
	float Root_First_Diff;
	float MAX_SECOND_ANGLE_DEG = 45.0;
	float MAX_FIRST_ANGLE_DEG = 90.0;
	int EQUAL_ANGLE = OffsetDegree_Second + 45;

	//Compare Difference in brightness between root and node
	Root_Second_Diff = Second - Root;
	Root_First_Diff = First - Root;

	//if both nodes are darker than the root node
	//*there is no valid vector as we want to point to brightness*//
	if (Root_Second_Diff < 0 && Root_First_Diff < 0) { return -1.0; } //No Appropriate vector angle

	//One Node can be darker than the root thats fine
	//but we need to set that darkness node to zero for proper calucalation of brightness vector
	if (Root_Second_Diff < 0) { Root_Second_Diff = 0; } //No Negatives for calculations
	if (Root_First_Diff < 0) { Root_First_Diff = 0; } //No Appropriate vector angle



	//Right is the brighter than top   //DONE
	if (Root_Second_Diff > Root_First_Diff)
	{
		Percentage_0_45 = Root_First_Diff / Root_Second_Diff;
		return (Percentage_0_45 * MAX_SECOND_ANGLE_DEG) + OffsetDegree_Second;
	}

	//Top is brighter than right //DONE
	if (Root_First_Diff > Root_Second_Diff)
	{
		Percentage_0_45 = Root_Second_Diff / Root_First_Diff;
		float Vector_Angle = Percentage_0_45 * MAX_SECOND_ANGLE_DEG;
		return (MAX_FIRST_ANGLE_DEG - Vector_Angle + OffsetDegree_Second);
	}

	//Both are equal in brightness //DONE
	if (Root_First_Diff == Root_Second_Diff)
	{
		return EQUAL_ANGLE;
	}

}

glm::vec4 Sort_Descend(float Top, float Right, float Bottom, float Left)
{
	vector<float> Four_Pedals = { Top, Right, Bottom, Left };

	sort(Four_Pedals.begin(), Four_Pedals.end());
	reverse(Four_Pedals.begin(), Four_Pedals.end());
	return { Four_Pedals[0], Four_Pedals[1], Four_Pedals[2], Four_Pedals[3]};
}
