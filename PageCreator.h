#ifndef PAGECREATOR
#define PAGECREATOR

#include <iostream>
#include <list>
#include <map>
#include <string>
#include "ShaderProgram.h"
#include "RawTexture.h"
#include "MasterElement.h"
#include "NewPage.h"
#include "PageGroup.h"
#include "Slider.h"
#include "NumberPrinter.h"
#include "Toggle.h"
#include "DropDownList.h"
#include "FileProcessor.h"
#include "SearchBar.h"
#include "Selector.h"
#include "PageItemGrid.h"
#include "PageGroupGrid.h"

using namespace std;

typedef void(*PrinterFunction)();


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

struct CustomerDetails
{
	string FirstName;
	string LastName;
	string Phone;
	string Email;
	string Address;

	CustomerDetails()
	{
		FirstName = "First Name";
		LastName  = "Last Name";
		Phone     = "Phone #";
		Email     = "Email";
		Address   = "Address";
	}

	void reset()
	{
		FirstName = "First Name";
		LastName = "Last Name";
		Phone = "Phone #";
		Email = "Email";
		Address = "Address";
	}
};
//We are going to need to store functions for specific functions inside objects
//Only these objects can call these functions


//FYI Keyboard:: might not be working as expected /////////////////////////
namespace PageCreator
{
	// Min/Max Variables
	const int MaxLevel = 5;
	const int MinLevel = 0;
	const int MaxFunction = 10;
	const int MinFunction = 4;
	const int PixelOffsetMax = 100;
	const int PixelOffsetMin = 1;

	const glm::vec2 OnlyX = {true, false};
	const glm::vec2 OnlyY = {false, true};
	const glm::vec4 OnlyR = {true , false, false, false};
	const glm::vec4 OnlyG = {false, true , false, false};
	const glm::vec4 OnlyB = {false, false, true , false};
	const glm::vec4 OnlyA = {false, false, false, true };

	const glm::vec2 Origin = { 0.0, 0.0 };

	const glm::vec4 HighlightColor = { 1.0, 0.5, 0.0, 1.0 };
	const glm::vec4 DescriptionColor = {1.0, 1.0, 1.0, 1.0};


	const glm::vec4 Red = { 1.0, 0.0, 0.0, 1.0 };
	const glm::vec4 Green = { 0.0, 1.0, 0.0, 1.0 };
	const glm::vec4 Blue = { 0.0, 0.0, 1.0, 1.0 };
	const glm::vec4 White = { 1.0, 1.0, 1.0, 1.0 };
	const glm::vec4 Black = { 0.0, 0.0, 0.0, 1.0 };
	const glm::vec4 Yellow = { 1.0, 1.0, 0.0, 1.0 };
	const glm::vec4 Rose = { 1.0, 0.0, 1.0, 1.0 };
	const glm::vec4 Orange = { 1.0, 0.5, 0.0, 1.0 };
	const glm::vec4 Azure = { 0.0, 0.5, 1.0, 1.0 };
	const glm::vec4 Purple = { 0.5, 0.0, 1.0, 1.0 };
	const glm::vec4 Transparent = { 0.0, 0.0, 0.0, 0.0 };
	const glm::vec4 Favourite_Color = { 0.0, 0.29, 0.33, 1.0 };

	const glm::vec4 ShapeHighlightColor = {0.0, 0.5, 0.9, 0.8 }; // Light Blue 
	const glm::vec4 ShapeGroupHighlightColor = { 0.0, 0.9, 0.4, 0.8 }; // Medium Green
	const glm::vec4 PageItemHighlightColor = { 0.5, 0.0, 0.5, 0.8}; //Medium Purple
	const glm::vec4 PageGroupHighlightColor = Red;
	const glm::vec4 PageHighlightColor = Orange;

	// Table of Creator Functions
	static KeyFunction**** CreatorFunction;

	//Creator Variables
	static bool HideCreatorPage = false;
	static glm::vec4 PreviousColor = {0.0, 0.0, 0.0, 1.0};
	static int PixelOffset = 5;

	static Page* CreatorPage = nullptr;
	static Page* GUIPage = nullptr;
	//static Book* CurrentBook = nullptr;
	static FileSystem Filesystem;
	static string CurrentText;
	static bool EnableKeyBoard = false;
	static ShaderProgram* CurrentShader;
	static RawTexture* CurrentTextures[2];

	static llVertexData* CurrentVertex;
	static llShapeData* CurrentShape;
	static llShapeGroupData* CurrentShapeGroup;
	static llPageItemData* CurrentPageItem;
	static llPageGroupData* CurrentPageGroup;
	static llPageData* CurrentPage;
	static llBookData* CurrentBook;
	static llBookData CreatorBook;

	static BookDirectory CreatorDirectory;
	
	//These variables dictate what function we are going to call
	static int CurrentLevel = 1; //Shape
	static int CurrentType = 0;
	static int CurrentFunction = 0; //Position

	//Helper Objects

	static Text Text_CurrentLevel_Label;
	static Text Text_CurrentLevel;

	static Text Text_Shift;
	static Text Text_AltRightLeft;
	static Text Text_AltUpDown;

	//Tab Bar
	static DropDownList File;
	static DropDownList Edit;
	static Button Button_File_Driver;
	static Button Button_Edit_Driver;

	//Element Viewer
	static NumberPrinter NumberPrinter_Element_Position;
	static NumberPrinter NumberPrinter_Element_Size;
	static Slider Slider_Color_R;
	static Slider Slider_Color_G;
	static Slider Slider_Color_B;
	static Slider Slider_Color_A;
	static Toggle Toggle_Hide;
	static NumberPrinter Mouse_Position;
	static NumberPrinter NumberPrinter_Name;
	static string Number_Printer_String_Helper;

	static Button Button_R_Slider;
	static Button Button_G_Slider;
	static Button Button_B_Slider;
	static Button Button_A_Slider;
	static Button Button_Name_NumberPrinter;

	//Rememeber we are not ever using a pointer to point to data in the book
    //The Editor Objects edit all the books and switch between books on their own

	//This points to every type of object we can edit
	static MasterElement* EditorSelected;
	static int CurrentMouseState;
	static KeyResult* CurrentKeyResult;

	//
	static NewPage BookCreatorPage;

	//For Creator
	//Defaults
	static Shape ShapeEditor;
	static ShapeGroup ShapeGroupEditor;
	static PageGroupItem PageItemEditor;
	static PageGroup PageGroupEditor;
	static NewPage PageEditor; //Maybe no constructor is what we want

	//Presets
	static Quad QuadEditor;
	static NewCharacter CharacterEditor;
	static Text TextEditor;
	static Slider SliderEditor;
	static Toggle ToggleEditor;
	
	void OnUpdate(KeyResult& KeyState, int MouseState);
	//void Init(Page& Creatorpage, Page& GUIPage, Book& Book);
	void llInit(llBookData* CurrentBook, ShaderProgram* ShaderProgram, RawTexture* Texture0, RawTexture* Texture1, RawTexture* Texture2);
    void CreateFunctionContainer();
	void SetCreatorFunctions();
	//void CreateGUIObjects();
	///////////////////////////////////////////////KEYBOARD FUNCTIONS////////////////////////////////

	const static glm::vec4 CustomerInfoHighlightColor = {0.0, 1.0, 0.0, 1.0};

	//Customer Details Page Group
	static NumberPrinter CreatorNumberPrinterSelected;

	//Customer Details with Add Button
	static NumberPrinter Printer_First_Name;
	static NumberPrinter Printer_Last_Name;
	static NumberPrinter Printer_Phone;
	static NumberPrinter Printer_Email;
	static NumberPrinter Printer_Address;
	static Text Text_Add_Customer;
	static SearchBar SearchBar_Customer_Search;

	static Button Button_First_Name;
	static Button Button_Last_Name;
	static Button Button_Phone;
	static Button Button_Email;
	static Button Button_Address;
	static Button Button_Add_Customer;
	static Button Button_Customer_Search;
	static Button Button_Customer_Search_Result;

	static list<CustomerDetails> CustomerDataBase;
	static map<string, CustomerDetails> map_CustomerDataBase;
	static CustomerDetails DefaultCustomer;

	static PrinterFunction PrinterToEdit;

	void ResetKeyboardText();

	//SwitchPrinters
	void SwitchStringPrinter();



	//Set Customer Details with keyboard & Mouse
	void SetCustomerSearch();
	void SetFirstName();
	void SetLastName();
	void SetPhone();
	void SetEmail();
	void SetAddress();


	void ProcessCustomerSearch();
	void ProcessFirstName();
	void ProcessLastName();
	void ProcessPhone();
	void ProcessEmail();
	void ProcessAddress();
	
	//Search Customer DataBase
	void WordSearch(string Search);
	string PerfectFit(string TestString, string ReferenceString);
	void BuildCustomerDetailElements();
	void AttachCustomerDetailButtons();
	void SetCustomerDetails(CustomerDetails* Reference);
	void ResetSearch();
	void ResetCustomerDetails();
	void SetSearchResult();
	void ResetCustomerDetailHighlights();
	void SetCustomerDetailDefaults();
	void AddCustomer();

	void PointerTest();
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
	//void SetKeyNext(); // Ctrl + ->
	//void SetKeyPrevious(); // Ctrl + <-

	void ErasePage();
	void SavePage();

	//Arrow Key default
	void ArrowKeyUp();
	void ArrowKeyDown();
	void ArrowKeyRight();
	void ArrowKeyLeft();

	//Make Sure these functions work on ALL levels not just shape
	void Add();//Ctrl + a
	void Duplicate(); //Ctrl + d
	void Insert(); //Insert Key
	void Delete(); // Delete key

	//BOOK TRAVERSING FUNCTIONS
	void DataLeft();    //Shift + Left
	void DataRight();   //Shift + Right

	void PrintCreatorStats();

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


	void SetQuadSelected(int MouseState, int ShapeHovered);

	void IncreasePixelOffset();
	void DecreasePixelOffset();

	void SetElements();
	void ResetElements();

	void SetBookFromElements();

	void UpdateColorSliders();

	void SetSliderR();
	void SetSliderG();
	void SetSliderB();
	void SetSliderA();


	void UpdateSliderR();
	void UpdateSliderG();
	void UpdateSliderB();
	void UpdateSliderA();

	void SetCurrentSlider();
	void SetCurrentToggle();
	void ProcessDropDownFile();
	void ProcessDropDownEdit();

	void TestFunction();

	void HighlightDropDownDriver();

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