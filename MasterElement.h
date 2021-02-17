#ifndef MASTERELEMENT
#define MASTERELEMENT

//Level
#define LEVEL_VERTEX 0
#define LEVEL_SHAPE 1
#define LEVEL_SHAPEGROUP 2
#define LEVEL_PAGEITEM 3
#define LEVEL_PAGEGROUP 4
#define LEVEL_PAGE 5
#define LEVEL_BOOK 6



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


//Level Type
#define TYPE_VERTEX 0 
#define TYPE_SHAPE 0
#define TYPE_SHAPE_QUAD 1
#define TYPE_SHAPE_CHARACTER 2
#define TYPE_SHAPEGROUP 0
#define TYPE_SHAPEGROUP_TEXT 1
#define TYPE_PAGEITEM 0
#define TYPE_PAGEITEM_SLIDER 1
#define TYPE_PAGEITEM_NUMBER 2
#define TYPE_PAGEGROUP 0
#define TYPE_PAGE 0

//Position Conversions
#define P_PIXEL_TO_COMPUTER 1
#define MIDDLE_TO_TOPLEFT 2
#define TOPLEFT_PIXEL_TO_COMPUTER 3
#define P_COMPUTER_TO_PIXEL 4
#define P_TOP_LEFT_TO_MIDDLE 5

//Size Conversions
#define S_PIXEL_TO_COMPUTER 1
#define S_ONE_TO_COMPUTER 2
#define S_COMPUTER_TO_PIXEL 3

#define MIN_COLOR_VALUE 0.0
#define MAX_COLOR_VALUE 1.0

#define RED 0
#define GREEN 1
#define BLUE 2
#define ALPHA 3

#define X_AXIS 0
#define Y_AXIS 1

#define MIN_VALID_SIZE 0.0 
#define MAX_VALID_SIZE 2.5

#define MIN_VALID_POSITION -1.0 //-3.5 
#define MAX_VALID_POSITION  1.0 // 3.5

#define TYPE_INT 0
#define TYPE_FLOAT 1
#define TYPE_DOUBLE 2
#define TYPE_VEC2 3
#define TYPE_VEC3 4 
#define TYPE_VEC4 5

#define PIXEL 0.00166

#include <iostream>
#include "Page.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Log.h"
#include "Button.h"

using namespace std;

struct llVertexData
{
	glm::vec2 Position = { 0.0, 0.0 };
	glm::vec2 TexCoords = { 0.0, 0.0 };
	glm::vec4 Color = { 0.0, 0.0, 0.0, 0.0 };
	float TexIndex = 0.0;
	glm::vec2 CentralPoint = { 0.0, 0.0 };
	int GUIAction = 0;
	//glm::vec2 XYRatio = { 0.0, 0.0 };
	llVertexData* Next = nullptr;
	llVertexData* Previous = nullptr;
};

struct llShapeData
{
	//ShapeGroupData ShapeGroup;
	//PageItemData PageItem;
	//PageGroupData PageGroup;
	//Page* Page;
	//Shape
	int ID = -1;
	int Ascii = -1;
	int ActiveTexture = 0;
	int Action = -1;
	int Layer;
	int Type = 0;
	glm::vec2 Position = { 0.0, 0.0 };
	glm::vec2 Size = { 0.05, 0.05 };
	glm::vec4 Color = { 1.0, 1.0, 1.0, 1.0 };
	glm::vec2 PositionOffset = { 0.0, 0.0 };
	glm::vec2 SizeOffset = { 0.0, 0.0 };
	glm::vec4 ColorOffset = { 0.0, 0.0, 0.0, 0.0 };
	glm::vec2 HighlightPosition = Position;
	glm::vec2 HighlightSize = { this->Size[0] + 0.0135, this->Size[1] + 0.025 };
	glm::vec4 HighlightColor;
	bool MouseAccess = true;
	bool Centered = false;
	bool Highlighted = false;
	bool ShapeDataisHighlight = false;
	bool PartOfGroup = false;
	float Top = -3;
	float Bottom = -3;
	float Left = -3;
	float Right = -3;
	string Text = "";
	bool EndStart = false;
	bool TextCentered = true;
	ShapeVertex Vertex[4];
	llShapeData* Next = nullptr;
	llShapeData* Previous = nullptr;
	llVertexData* Vertexx = nullptr; // Child
	llVertexData* VertexxHead = nullptr; // Child
	Button ShapeButton;
};

struct llShapeGroupData
{
	///////////////////////////////////
	//ShapeGroup
	//Page* Page;
	int ID = -1;
	int ShapeStart = 0;
	int ShapeOffset = -1;
	int ShapeCount = -1;
	int Type = 0;
	glm::vec2 XYShapePerRow = { -1.0, -1.0 };
	glm::vec2 ShapeSize = { -1.0, -1.0 };
	glm::vec2 Position = { 0.0, 0.0 };
	glm::vec2 Size = { 0.0, 0.0 };
	glm::vec4 Color = { 1.0, 1.0, 1.0, 1.0 };
	glm::vec2 PositionOffset = { 0.0, 0.0 };
	glm::vec2 SizeOffset = { 0.0, 0.0 };
	glm::vec4 ColorOffset = { 0.0, 0.0, 0.0, 0.0 };
	bool Centered = false;
	bool Highlighted = false;
	bool MouseAccess = true;
	float Top = -3;
	float Bottom = -3;
	float Left = -3;
	float Right = -3;
	llShapeGroupData* Next = nullptr;
	llShapeGroupData* Previous = nullptr;
	llShapeData* Shape = nullptr; // Child
	llShapeData* ShapeHead = nullptr; // Child
	///////////////////////////////////
};

struct llPageItemData
{
	//PageItem
	int ID = -1;
	int ShapeStart = 0;
	int ShapeCount = -1;
	int ShapeOffset = -1;
	int Type = 0;
	glm::vec2 Position = { 0.0, 0.0 };
	glm::vec2 Size = { 0.0, 0.0 };
	glm::vec4 Color = { 1.0, 1.0, 1.0, 1.0 };
	glm::vec2 PositionOffset = { 0.0, 0.0 };
	glm::vec2 SizeOffset = { 0.0, 0.0 };
	glm::vec4 ColorOffset = { 0.0, 0.0, 0.0, 0.0 };
	glm::vec2 XYShapePerRow = { -1.0, -1.0 };
	glm::vec2 ShapeSize = { -1.0, -1.0 };
	bool Centered = false;
	bool Highlighted = false;
	bool MouseAccess = true;
	float Top = -3;
	float Bottom = -3;
	float Left = -3;
	float Right = -3;
	llPageItemData* Next = nullptr;
	llPageItemData* Previous = nullptr;
	llShapeGroupData* ShapeGroup = nullptr; // Child
	llShapeGroupData* ShapeGroupHead = nullptr; // Child
};

struct llPageGroupData
{
	//PageGroup
	//Page* Page;
	int ID = -1;
	int ShapeStart = 0;     //Lowest level //EX: PageItem Starts at Shape 120
	int ShapeCount = -1;  //Lowest level //EX: PageItem owns 40 Shapes 
	int ShapeOffset = -1;      //Lowest level //EX: This Shape is 10 Shapes from PageItem start Shape (120)
	int Type = 0;
	glm::vec2 Position = { 0.0, 0.0 };
	glm::vec2 Size = { 0.0, 0.0 };
	glm::vec4 Color = { 1.0, 1.0, 1.0, 1.0 };
	glm::vec2 XYShapePerRow = { -1.0, -1.0 };
	glm::vec2 ShapeSize = { -1.0, -1.0 };
	bool Centered = false;
	bool Highlighted = false;
	bool MouseAccess = true;

	float Top = -3;
	float Bottom = -3;
	float Left = -3;
	float Right = -3;
	llPageGroupData* Next = nullptr;
	llPageGroupData* Previous = nullptr;
	llPageItemData* PageItem = nullptr; // Child
	llPageItemData* PageItemHead = nullptr; // Child
};

struct llPageData
{
	bool PageReady = false;
	llVertexData* VertexContainer = nullptr;
	int* IndexContainer = nullptr;
	llPageData* Next = nullptr;
	llPageData* Previous = nullptr;
	llPageGroupData* PageGroup = nullptr; // Child
	llPageGroupData* PageGroupHead = nullptr; // Child

	GLsizeiptr MaxSize;
	GLsizeiptr CurrentSize;
	GLuint VA;
	GLuint VB;
	GLuint IB;
	GLuint WhiteTexture;
	int MaxTextures = 8;
	int MaxShapeCount = 10000; // 10,000 Shapes
	int MaxVertexCount = MaxShapeCount * 4;
	int MaxIndexCount = MaxShapeCount * 6;
	int VertexIndex = 0;
	array<uint32_t, 16> TextureSlots;
	uint32_t TextureSlotIndex = 1;

	void CreateContainer()
	{
		VertexContainer = new llVertexData[MaxVertexCount];
		IndexContainer = new int[MaxIndexCount];
	}

	void DeleteContainer()
	{
		delete VertexContainer;
		delete IndexContainer;

		VertexContainer = nullptr;
		IndexContainer = nullptr;
		PageReady = false;
	}

	void LoadPage()
	{
		llVertexData Empty;
		for (int i = 0; i < VertexIndex; i++)
		{
			VertexContainer[i] = Empty;
		}

		VertexIndex = 0;
		int PageGroupCount = -1;
		int PageItemCount = -1;
		int ShapeGroupCount = -1;
		int ShapeCount = -1;
		int VertexCount = -1;

		//Page Group
		llPageGroupData* CurrentPageGroup = PageGroup;
		if (CurrentPageGroup != nullptr)
		{
			//Set PageGroup Beginning
			/////////////////////////////////////////////////////
			while (CurrentPageGroup->Previous != nullptr)
			{
				CurrentPageGroup = CurrentPageGroup->Previous;
			}
			/////////////////////////////////////////////////////

			while (CurrentPageGroup != nullptr && CurrentPageGroup->PageItem != nullptr)
			{
				PageGroupCount++;
				//PageItem
				llPageItemData* CurrentPageItem = CurrentPageGroup->PageItem;
				//Set PageItem Beginning
				/////////////////////////////////////////////////////
				while (CurrentPageItem->Previous != nullptr)
				{
					CurrentPageItem = CurrentPageItem->Previous;
				}
				/////////////////////////////////////////////////////

				while (CurrentPageItem != nullptr && CurrentPageItem->ShapeGroup != nullptr)
				{
					PageItemCount++;
					//ShapeGroup
					llShapeGroupData* CurrentShapeGroup = CurrentPageItem->ShapeGroup;
					//Set ShapeGroup to beginning
					/////////////////////////////////////////////////////
					while (CurrentShapeGroup->Previous != nullptr)
					{
						CurrentShapeGroup = CurrentShapeGroup->Previous;
					}
					/////////////////////////////////////////////////////

					while (CurrentShapeGroup != nullptr && CurrentShapeGroup->Shape != nullptr)
					{
						ShapeGroupCount++;
						//Shape
						llShapeData* CurrentShape = CurrentShapeGroup->Shape;
						//Set shape to beginning
						/////////////////////////////////////////////////////
						if (CurrentShapeGroup->Shape != nullptr)
						{
							while (CurrentShape->Previous != nullptr)
							{
								CurrentShape = CurrentShape->Previous;
							}
							/////////////////////////////////////////////////////

							while (CurrentShape != nullptr && CurrentShape->Vertexx != nullptr)
							{
								//cout << " | PG:" << PageGroupCount << " | PI:" << PageItemCount << " | SG:" << ShapeGroupCount << " | S:" << ShapeCount << " | Char: " << char(CurrentShape->Ascii) << endl;
								ShapeCount++;
								//PrintllShape(CurrentShape);
								//Vertex
								llVertexData* CurrentVertex = CurrentShape->Vertexx;
								/////////////////////////////////////////////////////
								while (CurrentVertex->Previous != nullptr)
								{
									CurrentVertex = CurrentVertex->Previous;
								}
								/////////////////////////////////////////////////////
								while (CurrentVertex != nullptr)
								{
									VertexCount++;
									VertexContainer[VertexIndex] = *CurrentVertex;
									VertexIndex++;
									CurrentVertex = CurrentVertex->Next;
								}
								VertexCount = -1;
								CurrentShape = CurrentShape->Next;
							}
						}
						ShapeCount = -1;
						CurrentShapeGroup = CurrentShapeGroup->Next;
					}
					ShapeGroupCount = -1;
					CurrentPageItem = CurrentPageItem->Next;
				}
				PageItemCount = -1;
				CurrentPageGroup = CurrentPageGroup->Next;
			}
		}

	}

	GLsizeiptr GetCurrentSize()
	{
		llVertexData* UsagePointer = VertexContainer + VertexIndex;

		CurrentSize = (uint8_t*)UsagePointer - (uint8_t*)VertexContainer;
		return CurrentSize;
	}

	GLsizeiptr GetMaxSize()
	{
		llVertexData* UsagePointer = VertexContainer + MaxVertexCount;
		MaxSize = (uint8_t*)UsagePointer - (uint8_t*)VertexContainer;
		return MaxSize;
	}


};

struct llBookData
{

	llBookData* Next = nullptr;
	llBookData* Previous = nullptr;
	llPageData* Page = nullptr; // = nullptr; // Child
	llPageData* PageHead = nullptr;
};


//////////////////////////////////////////////////////////////////////////////////////

//All the second tier hierarchy like Shape, ShapeGroup, PageItem, PageGroup defaults will be custom for creator
class MasterElement
{
public:
	MasterElement();
	bool Initialized = false;
	Page* CurrentPage;
	ShapeData LoadedShape;
	llShapeData lllShape;
	llBookData* LoadedBook;

	//static void AddPageToBook(llBook* Book)
	//{
	//	if (Book->Page == nullptr)
	//	{
	//		cout << "PageAdded yes" << endl;
	//		Book->Page = new llPage;
	//		Book->Page->val = 0;
	//		//Book->Page->PageGroup->PageItem->ShapeGroup->Shape->Vertex;
	//	}
	//	else
	//	{
	//		
	//		cout << "PageAdded no" << endl;
	//		llPage* CurrentPage = Book->Page;
	//		int ValValue = CurrentPage->val;
	//		//Get Last Element
	//		while (CurrentPage->Next != nullptr)
	//		{
	//			CurrentPage = CurrentPage->Next;
	//			ValValue++;
	//		}
	//
	//		CurrentPage->Next = new llPage;
	//		CurrentPage->Next->val = ValValue;
	//	}
	//}
	//
	//static void PrintBook(llBook* Book)
	//{
	//	llPage* CurrentPage = Book->Page;
	//	while (CurrentPage != nullptr)
	//	{
	//		cout << CurrentPage->val << endl;
	//		CurrentPage = CurrentPage->Next;
	//	}
	//}
	static void Toggle(bool& ToToggle);
	static void FindShape(llBookData* llBook, float xMouse, float yMouse, int ElementLevel, int MouseState);

	//Print Book
	static void PrintBookStats(llBookData* llBook);
	static void PrintBook(llBookData* llBook);

	//Print Group Shapes
	static void PrintPageItemShapes(llPageItemData* llShapeGroup);
	static void PrintShapeGroupShapes(llShapeGroupData* llShapeGroup);
	
	//Print Sub Groups
	static void PrintPageItemShapeGroups(llPageItemData* llShapeGroup);

	//Print ShapeGorup
	static void PrintllShapeGroup(llShapeGroupData* llShapeGroup);
	static void PrintllShapeGroup(llShapeGroupData* llShapeGroup, int Offset);

	//Print Shape
	static void PrintllShape(llShapeData* llShape);
	static void PrintllShape(llShapeData* llShape, int Offset);

	static int GetShapeCount(llShapeGroupData* llShapeGroup);
	static int GetShapeGroupCount(llPageItemData* llShapeGroupData);
	static int GetPageItemCount(llPageGroupData* llShapeGroupData);

	virtual void Add_Default()
	{
	
	};
	virtual void Add_Duplicate() {}; 
	virtual void Add_Insert() {};
	virtual void Delete() {};

	virtual void lllSwitch(int Offset) {};
	virtual ShapeData& Switch(int RequstedShapeID) { return LoadedShape; };
	virtual ShapeData& Switch(Page& Page, int RequstedShapeID) { return LoadedShape; };
	//virtual void SetShape(ShapeData& ShapeData) {};
	//virtual void SetShape(ShapeData& ShapeData, glm::vec2 PSConversions) {};
	virtual void SetPosition(glm::vec2 Position) {};                     //Set All
	virtual void SetPosition(glm::vec2 Position, glm::vec2 bools) {};    //Set all with true boolean(s)
	virtual void SetSize(glm::vec2 Size) {};                             //Set All
	virtual void SetSize(glm::vec2 Size, glm::vec2 bools) {};            //Set all with true boolean(s)
	virtual void SetColor(glm::vec4 Color) {};                           //..
	virtual void SetColor(glm::vec4 Color, glm::vec4 bools) {};          //...
      
    // Conversions
	virtual void SetPosition(glm::vec2 Position, int Conversion) {};                     //Set All
	virtual void SetPosition(glm::vec2 Position, glm::vec2 bools, int Conversion) {};    //Set all with true boolean(s)
	virtual void SetSize(glm::vec2 Size, int Conversion) {};                             //Set All
	virtual void SetSize(glm::vec2 Size, glm::vec2 bools, int Conversion) {};            //Set all with true boolean(s)
	  
	virtual void OffsetPosition(glm::vec2 Position) {};                  //..
	virtual void OffsetPosition(glm::vec2 Position, glm::vec2 bools) {}; //...
	virtual void OffsetSize(glm::vec2 Size) {};                          //..
	virtual void OffsetSize(glm::vec2 Size, glm::vec2 bools) {};         //...
	virtual void OffsetColor(glm::vec4 Color) {};                        //..
	virtual void OffsetColor(glm::vec4 Color, glm::vec4 bools) {};       //...
	  
	//rtu Conversions
	virtual void OffsetPosition(glm::vec2 Position, int Conversion) {};                  //..
	virtual void OffsetPosition(glm::vec2 Position, glm::vec2 bools, int Conversion) {}; //...
	virtual void OffsetSize(glm::vec2 Size, int Conversion) {};                          //..
	virtual void OffsetSize(glm::vec2 Size, glm::vec2 bools, int Conversion) {};

	virtual glm::vec2 GetPosition() { return { -1.0, -1.0 }; };
	virtual glm::vec2 GetSize() { return { -1.0, -1.0 }; };
	virtual glm::vec4 GetColor() { return { -1.0, -1.0, -1.0, -1.0 }; };
	virtual bool GetMouseAccess() { return false; };

	glm::vec2 ApplyPositionConversion(glm::vec2 Position, int Conversion, glm::vec2 Size);
	glm::vec2 ApplyPositionConversion(glm::vec2 Position, int Conversion);
	glm::vec2 ApplySizeConversion(glm::vec2 Position, int Conversion);

	//Position TopLeft/BottomLeft Conversions 
	glm::vec2 PTLPixelToComputer(glm::vec2 Position); //Working
	glm::vec2 PBLPixelToComputer(glm::vec2 Position); //Working
	glm::vec2 PMiddleToTopLeft(glm::vec2 Position, glm::vec2 Size);
	glm::vec2 PTopLeftToMiddle(glm::vec2 Position, glm::vec2 Size);

	glm::vec2 PComputerToTLPixel(glm::vec2 Position); //Working
	glm::vec2 PComputerToBLPixel(glm::vec2 Position); //Working


	//SizeConversions
	glm::vec2 SPixelToComputer(glm::vec2 Size); //Working
	glm::vec2 SOneToComputer(glm::vec2 Size);   //Working

	glm::vec2 SComputerToPixel(glm::vec2 Size); //Working
	glm::vec2 SComputerToOne(glm::vec2 Size);   //Working

	bool IsInitialized();
	bool IsInBounds(int ID);

protected:

	

};

#endif
