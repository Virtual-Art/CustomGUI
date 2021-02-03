#ifndef PAGECREATOR
#define PAGECREATOR

#include <iostream>
#include <string>
#include "MasterElement.h"
#include "NewPage.h"
#include "PageGroup.h"
#include "Slider.h"
#include "MouseManager.h"
#include "KeyboardManager.h"
#include "FileProcessor.h"

using namespace std;

//Level
#define LEVEL_VERTEX 0
#define LEVEL_SHAPE 1
#define LEVEL_SHAPEGROUP 2
#define LEVEL_PAGEITEM 3
#define LEVEL_PAGEGROUP 4
#define LEVEL_PAGE 5
#define LEVEL_BOOK 6

//Level Type
#define TYPE_VERTEX 0 
#define TYPE_SHAPE 0
#define TYPE_SHAPE_QUAD 1
#define TYPE_SHAPE_CHARACTER 2
#define TYPE_SHAPEGROUP 0
#define TYPE_SHAPEGROUP_TEXT 1
#define TYPE_PAGEITEM 0
#define TYPE_PAGEITEM_SLIDER 1
#define TYPE_PAGEGROUP 0
#define TYPE_PAGE 0

//Level Type Function
#define FUNCTION_POSITION  0
#define FUNCTION_SIZE  1
#define FUNCTION_COLOR_R  2
#define FUNCTION_COLOR_G  3
#define FUNCTION_COLOR_B  4
#define FUNCTION_COLOR_A  5
#define MAINFUNCTION_6  6
#define MAINFUNCTION_7  7
#define MAINFUNCTION_8  8
#define MAINFUNCTION_9  9

#define FUNCTION_SET_TEXT 6

#define ARROW_UP 0
#define ARROW_DOWN 1
#define ARROW_RIGHT 2
#define ARROW_LEFT 3

//Can Edit all objects
//Restricted to only Position maybe size
struct GUIEditor
{
	MasterElement* AnyEditor;
	GUIEditor* Parent;
	GUIEditor* Child;
	GUIEditor* Next;
	GUIEditor* Previous;
};


//We are going to need to store functions for specific functions inside objects
//Only these objects can call these functions

namespace PageCreator
{
	// Min/Max Variables
	const int MaxLevel = 5;
	const int MinLevel = 0;
	const int MaxFunction = 5;
	const int MinFunction = 0;
	const int PixelOffsetMax = 100;
	const int PixelOffsetMin = 1;

	const glm::vec2 OnlyX = {true, false};
	const glm::vec2 OnlyY = {false, true};
	const glm::vec4 OnlyR = {true , false, false, false};
	const glm::vec4 OnlyG = {false, true , false, false};
	const glm::vec4 OnlyB = {false, false, true , false};
	const glm::vec4 OnlyA = {false, false, false, true };

	const glm::vec2 Origin = { 0.0, 0.0 };

	const glm::vec4 Red = { 1.0, 0.0, 0.0, 1.0 };
	const glm::vec4 Green = { 0.0, 1.0, 0.0, 1.0 };
	const glm::vec4 Blue = { 0.0, 0.0, 1.0, 1.0 };
	const glm::vec4 White = { 1.0, 1.0, 1.0, 1.0 };
	const glm::vec4 Yellow = { 1.0, 1.0, 0.0, 1.0 };
	const glm::vec4 Rose = { 1.0, 0.0, 1.0, 1.0 };
	const glm::vec4 Orange = { 1.0, 0.5, 0.0, 1.0 };
	const glm::vec4 Azure = { 0.0, 0.5, 1.0, 1.0 };
	const glm::vec4 Purple = { 0.5, 0.0, 1.0, 1.0 };
	const glm::vec4 Transparent = { 0.0, 0.0, 0.0, 0.0 };

	// Table of Creator Functions
	static KeyFunction**** CreatorFunction;

	//Creator Variables
	const int OnePixel = 0.00166; //1 Pixel
	static glm::vec4 PreviousColor = {0.0, 0.0, 0.0, 1.0};
	static int PixelOffset = 5;

	static Page* CreatorPage = nullptr;
	static Page* GUIPage = nullptr;
	//static Book* CurrentBook = nullptr;
	static FileSystem Filesystem;
	static string CurrentText;
	static bool EnableKeyBoard = false;

	static llShapeData* CurrentShape;
	static llShapeGroupData* CurrentShapeGroup;
	static llPageItemData* CurrentPageItem;
	static llPageGroupData* CurrentPageGroup;
	static llPageData* CurrentPage;
	static llBookData* CurrentBook;
	
	//These variables dictate what function we are going to call
	static int CurrentLevel = 1; //Shape
	static int CurrentType = 0;
	static int CurrentFunction = 0; //Position

	//Helper Objects

	static Text Text_CurrentLevel_Label;// (*GUIPage, "Current Function: ", { 0.0, 1.0 });
	static Text Text_CurrentFunction_Label;// (*GUIPage, "Current Function: ", { 0.0, 1.0 });
	
	static Text Text_CurrentLevel;// (*GUIPage, "Shape ", { -0.75, 1.0 });
	static Text Text_CurrentFunction;// (*GUIPage, "Position", { -0.25, 1.0 });

	//Rememeber we are not ever using a pointer to point to data in the book
    //The Editor Objects edit all the books and switch between books on their own

	//This points to every type of object we can edit
	static MasterElement* Element_Selected;
	static int CurrentMouseState;
	static KeyResult* CurrentKeyResult;

	//Defaults
	static Shape ShapeSelected;
	static ShapeGroup ShapeGroupSelected;
	static PageGroupItem PageItemSelected;
	static PageGroup PageGroupSelected;
	static NewPage PageSelected; //Maybe no constructor is what we want

	//Presets
	static Quad QuadSelected;
	static NewCharacter CharacterSelected;
	static Text TextSelected;
	static Slider SliderSelected;
	
	void OnUpdate(KeyResult& KeyState, int MouseState);
	void Init(Page& Creatorpage, Page& GUIPage, Book& Book);
	void llInit(llBookData* CurrentBook);
    void CreateFunctionContainer();
	void SetCreatorFunctions();
	void CreateGUIObjects();
	///////////////////////////////////////////////KEYBOARD FUNCTIONS////////////////////////////////

	void SetKeyboardKeys();

	// Arrow Key Default
	void SetArrowKeys();
	void SetShift();
	void SetAlternate();
	void SetKeyAdd(); 
	void SetKeyDuplicate();
	void SetPixelOffsetKeys();
	void SetDeleteKey();
	void SetSaveKey(); // Ctrl + S
	void SetEraseKey(); // Ctrl + S
	void SetInsertKey(); // Insert Key
	void SetKeyNext(); // Ctrl + ->
	void SetKeyPrevious(); // Ctrl + <-

	void ErasePage();
	void SavePage();

	//Arrow Key default
	void ArrowKeyUp();
	void ArrowKeyDown();
	void ArrowKeyRight();
	void ArrowKeyLeft();

	//BOOK TRAVERSING FUNCTIONS
	void DataRight();   //Shift + Right
	void DataLeft();    //Shift + Left

	//BOOK/TYPE TRAVERSING FUNCTIONS
	void LevelUp();     //Shift + Up
	void LevelDown();   //Shift + Down

	//TYPE TRAVERSING FUNCTIONS
	void TypeRight();   //Alt + Right
	void TypeLeft();    //Alt + Left

	//OPTION TRAVERSING FUNCTIONS
	void OptionsUp();   //Alt + Up
	void OptionsDown(); //Alt + Down

	void SetShapeType();
	void SetShapeGroupType();
	void SetPageItemType();
	void SetPageGroupType();
	void SetPageType();

	void AddLetter();
	void BackSpace();


	//Make Sure these functions work on ALL levels not just shape
	void Add();//Ctrl + a
	void Duplicate(); //Ctrl + d
	void Insert(); //Insert Key
	void Delete(); // Delete key
	//void Next();
	//void Previous();

	void SetQuadSelected(int MouseState, int ShapeHovered);

	void IncreasePixelOffset();
	void DecreasePixelOffset();

	//////////////////////////////////////////////////////////////////////////////////////////////////

	void Empty();

	//ShapeFunctions
	void PositionUp();
	void PositionDown();
	void PositionRight();
	void PositionLeft();

	//Size
	void SizeUp();
	void SizeDown();
	void SizeRight();
	void SizeLeft();

	//RGBA
	void ColorRUp();
	void ColorRDown();
	void ColorGUp();
	void ColorGDown();
	void ColorBUp();
	void ColorBDown();
	void ColorAUp();
	void ColorADown();

	//Specific Functions
	void SetText();
}

#endif