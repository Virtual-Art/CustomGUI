#ifndef PAGECREATOR
#define PAGECREATOR

#include <iostream>
#include "MasterElement.h"
#include "PageGroup.h"
#include "Slider.h"
#include "MouseManager.h"
#include "KeyboardManager.h"
#include "FileProcessor.h"

using namespace std;

#define LEVEL_VERTEX 0
#define LEVEL_SHAPE 1
#define LEVEL_SHAPEGROUP 2
#define LEVEL_PAGEITEM 3
#define LEVEL_PAGEGROUP 4
#define LEVEL_PAGE 5
#define LEVEL_BOOK 6

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

#define ARROW_UP 0
#define ARROW_DOWN 1
#define ARROW_RIGHT 2
#define ARROW_LEFT 3


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
	static KeyFunction*** CreatorFunction;

	//Creator Variables
	const int OnePixel = 0.00166; //1 Pixel
	static glm::vec4 PreviousColor = {0.0, 0.0, 0.0, 1.0};
	static int PixelOffset = 5;
	static int CurrentLevel = 1; //Shape
	static int CurrentFunction = 0; //Position
	static Page* CreatorPage = nullptr;
	static Page* GUIPage = nullptr;
	static Book* CurrentBook = nullptr;
	static FileSystem Filesystem;

	//Helper Objects

	static Text Text_CurrentLevel_Label;// (*GUIPage, "Current Function: ", { 0.0, 1.0 });
	static Text Text_CurrentFunction_Label;// (*GUIPage, "Current Function: ", { 0.0, 1.0 });
	
	static Text Text_CurrentLevel;// (*GUIPage, "Shape ", { -0.75, 1.0 });
	static Text Text_CurrentFunction;// (*GUIPage, "Position", { -0.25, 1.0 });

	//Selected
	static Shape* ShapeSelected;
	//static ShapeGroup* ShapeGroupSelected;
	static PageGroupItem* PageItemSelected;
	//static PageGroup* PageGroupSelected;
	static MasterElement* Element_Selected;

	static Quad QuadSelected(*CreatorPage, -1);
	//static Text TextSelected(*CreatorPage, -1);
	static Slider SliderSelected(*CreatorPage, -1);
	



	void Init(Page& Creatorpage, Page& GUIPage, Book& Book);
    void CreateFunctionContainer();
	void SetCreatorFunctions();

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

	//Arrow Key with Alt
	void AlternateUp(); // Alternate between Hierarchy
	void AlternateDown(); // Alternate between Hierarchy
	//void AlternateRight();//Right //Switch between Derived'
	//void AlternateLeft();//Down  //Switch between Derived'

	//Arrow Keys with Shift
	void ShiftUp(); //Shift through functions
	void ShiftDown(); //Shift through functions


	//Make Sure these functions work on ALL levels not just shape
	void Add();//Ctrl + a
	void Duplicate(); //Ctrl + d
	void Insert(); //Insert Key
	void Delete(); // Delete key
	void Previous();
	void Next();

	void SetQuadSelected(int MouseState, int ShapeHovered);

	void IncreasePixelOffset();
	void DecreasePixelOffset();

	//////////////////////////////////////////////////////////////////////////////////////////////////

	void Empty();

	//ShapeFunctions
	void ShapePositionUp();
	void ShapePositionDown();
	void ShapePositionRight();
	void ShapePositionLeft();

	void ShapeSizeUp();
	void ShapeSizeDown();
	void ShapeSizeRight();
	void ShapeSizeLeft();

	void ShapeColorRUp();
	void ShapeColorRDown();

	void ShapeColorGUp();
	void ShapeColorGDown();

	void ShapeColorBUp();
	void ShapeColorBDown();

	void ShapeColorAUp();
	void ShapeColorADown();

	//ShapeGroup Functions 
	void ShapeGroupPositionUp();
	void ShapeGroupPositionDown();
	void ShapeGroupPositionRight();
	void ShapeGroupPositionLeft();
			  
	void ShapeGroupSizeUp();
	void ShapeGroupSizeDown();
	void ShapeGroupSizeRight();
	void ShapeGroupSizeLeft();
			  
	void ShapeGroupColorRUp();
	void ShapeGroupColorRDown();
			  
	void ShapeGroupColorGUp();
	void ShapeGroupColorGDown();
			  
	void ShapeGroupColorBUp();
	void ShapeGroupColorBDown();
			  
	void ShapeGroupColorAUp();
	void ShapeGroupColorADown();


	// Page item Group
	void PageItemPositionUp();
	void PageItemPositionDown();
	void PageItemPositionRight();
	void PageItemPositionLeft();

}

#endif