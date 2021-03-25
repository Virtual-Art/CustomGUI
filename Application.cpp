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

//string ProcessInputString(GLFWwindow* window);
//void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void WordSearch(map<string, string>& map, string Search);
void AddWord(map<string, string>& map, string Search);
void PrintMap(map<string, string>& map);
void PerfectFit(string TestString, string ReferenceString);

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

using namespace std;

int main(int argc, char** argv)
{
	Keyboard Keyboard;
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

	string hiya = "Hello there";

	llPageItemData Grid_Quad;
	Grid_Quad.Position = { 0.0, 0.6 };
	Grid_Quad.InputType = INPUT_CENTER;
	NumberPrinterData DataText_Grid;
	DataText_Grid.Description = "Desp";
	DataText_Grid.Type = TYPE_STRING;
	DataText_Grid.String = &hiya;
	NumberPrinter SLIDER_1(&EditorBook, &Grid_Quad, DataText_Grid);


	Grid_Quad.Position = { 0.0, 0.5 };
	DataText_Grid.Description = "Desp22";
	NumberPrinter SLIDER_2(&EditorBook, &Grid_Quad, DataText_Grid);
	//SLIDER_2.OffsetPosition({ 0.0, -0.3 }, {false, true});
	//SLIDER_2.PlaceRight(SLIDER_1, MATCH_CENTERS, 100);

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

	PageCreator::BuildCustomerDetailElements();
	PageCreator::AttachCustomerDetailButtons();

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
	PID.Position = {0.3, 0.3};

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
	PageItem_Toggle.Position = {-0.89, -0.3};

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


	//PrintMap(StringDataBase);
	WordSearch(StringDataBase, "Mo");

	typedef void(*Master_P)();
	while (!glfwWindowShouldClose(window))
	{
		MousePosition = { MouseManager::xPos, MouseManager::yPos };

		Time = glfwGetTime();
		PreviousTime = glfwGetTime();
		glClearColor(0.091, 0.14, 0.14, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		//Setup
		int MouseState = MouseManager::GetMouseState(window, glfwGetTime(), 0.3, 0.4);
		KeyResult KeyState = Keyboard.GetKeyBoardState(window, glfwGetTime(), 0.3, 0.4);
		EditorShapeDataHovered = MainBook.Page[0].FindShapeData(MouseManager::xPos, MouseManager::yPos, false);
		GUIShapeDataHovered = GUI.FindShapeData(MouseManager::xPos, MouseManager::yPos, false);
		PageCreator::OnUpdate(KeyState, MouseState);

		PageGroupItem* jaj = &llSlider;
		Slider Complex(jaj->GetData());

		//MasterElement::FindElement(&EditorBook, LEVEL_SHAPE);

		//NewVec2.llUpdate();

		//EditorPage.DrawPage();

		if (KeyState.Key1 == GUI_I_CLICKED)
		{
			MasterElement::CurrentDirectory(&EditorBook);
		}
		
		if (KeyState.Key1 == GUI_O_CLICKED)
		{
			MasterElement::PrintBookStats(&PageCreator::CreatorBook);
		}

		if (KeyState.Key1 == GUI_M_CLICKED)
		{
			PageCreator::PrintCreatorStats();
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

void WordSearch(map<string, string>& map, string Search)
{
	float Time1 = glfwGetTime();
	//Go through Entire List
	for (auto kv : map)
	{
		auto& Key = kv.first;

		//Check to see if the string matches up 
		PerfectFit(Key, Search);
	}
	float Time2 = glfwGetTime();

	Log::LogFloat("Execution Time", Time2 - Time1);
}

void PrintMap(map<string, string>& map)
{
	for (auto kv : map)
	{
		auto& Key = kv.first;


		cout << "Key:" << Key << endl;
	}

}

void PerfectFit(string TestString, string ReferenceString)
{

	if (TestString.size() < ReferenceString.size()) {return;}

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
			return;
		}
	}

	cout << "Key:" << TestString << endl;
}