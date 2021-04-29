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

#define GUI_HOVERED 10
//Level Type Function
#define FUNCTION_POSITION  9
#define FUNCTION_SIZE  8
#define FUNCTION_COLOR_R  7
#define FUNCTION_COLOR_G  6
#define FUNCTION_COLOR_B  5
#define FUNCTION_COLOR_A  4
#define MAINFUNCTION_3  3
#define MAINFUNCTION_2  2
#define MAINFUNCTION_1  1
#define MAINFUNCTION_0  0

#define FUNCTION_SET_TEXT 6

#define ARROW_UP 0
#define ARROW_DOWN 1
#define ARROW_RIGHT 2
#define ARROW_LEFT 3

#define MATCH_NONE -1
#define MATCH_CENTERS 0
#define MATCH_ENDS 1
#define MATCH_BEGINNINGS 2
#define MATCH_BEGINNING_TO_END 3
#define MATCH_END_TO_BEGINNING 4
#define MATCH_FLOORS 5
#define MATCH_CEILINGS 6

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
#define TYPE_PAGEITEM_TOGGLE 3
#define TYPE_PAGEITEM_SEARCHBAR 4
#define TYPE_PAGEITEM_DROPDOWNLIST 5
#define TYPE_PAGEITEM_SELECTOR 6
#define TYPE_PAGEGROUP 0
#define TYPE_PAGE 0
#define TYPE_BACKGROUND 33

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

#define INPUT_NONE -1
#define INPUT_CENTER 0
#define INPUT_LEFT 1
#define INPUT_RIGHT 2
#define INPUT_TOP 3
#define INPUT_BOTTOM 4
#define INPUT_TOPLEFT 5
#define INPUT_TOPRIGHT 6
#define INPUT_BOTTOMLEFT 7
#define INPUT_BOTTOMRIGHT 8


#define PADDING_LEFT 0
#define PADDING_RIGHT 1
#define PADDING_TOP 2
#define PADDING_BOTTOM 3

#define EDGE_LEFT 0
#define EDGE_RIGHT 1
#define EDGE_TOP 2
#define EDGE_BOTTOM 3

#define PLACEMENT_NORMAL 0
#define PLACEMENT_ABOVE 1
#define PLACEMENT_BELOW 2
#define PLACEMENT_RIGHTOF 3
#define PLACEMENT_LEFTOF 4

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
#define TYPE_STRING 6

#define TOPRIGHT 0
#define	TOPLEFT 1
#define BOTTOMRIGHT 2
#define	BOTTOMLEFT 3

#define PIXEL 0.00166

#include <iostream>
#include "Page.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Log.h"
#include "Button.h"

using namespace std;


struct TextData
{
	string Phrase = "Text";
	string FontFile;
	float FontSize = 16.0;
	float CharSpacing = -10.0; //in pixels 0.535
	float LineSpacing = 1.0; //in pixels
	float LineLength = 0.5; // in.....
	glm::vec2 CursorPosition = { 0.0, 0.0 };
	float FontSlot = 2;
	bool List = true;
	bool Centered = false;
	bool EndStart = false;
};


struct SliderData
{
	double Min = 0;
	double Max = 1.0;
	double Controller = 0.5;
	float* WorkingFloat;
	string Description = "HI";
	string Ratio = "0.0";
};

struct NumberPrinterData
{
	string Description = "Description";
	int FontSize = 16;
	int AnswerFontSize = 14;
	int Type = -1;
	int DecimalPlaces = 2;
	string* String = nullptr;
	int* Integer = nullptr;
	float* Float = nullptr;
	glm::vec2* VEC2 = nullptr;
	glm::vec3* VEC3 = nullptr;
	glm::vec4* VEC4 = nullptr;
	bool DescriptionHighlighted = false;
	bool DollarSign = false;
	glm::vec4 DescriptionHighlightColor = {1.0, 1.0, 1.0, 1.0};
	glm::vec4 AnswerColor = {0.0, 1.0, 1.0, 1.0};
	int AnswerSpacing = 50;
	bool Below = false;
};

struct SelectorData
{
	glm::vec2 ColumnsRows = { 1, 2 };
	bool BackGround = true;
	glm::vec4 BackGroundColor = { 0.5, 0.5, 0.5, 0.5 };
	glm::vec4 BackGroundPadding = { 0, 0, 0, 0 };
	glm::vec4 HighlightColor = { 0.3, 0.3, 0.3, 0.3 };
	bool UniformBackGround = true;
	string Selector[20] = { "Selection1", "Selection2", "Selection3", "Selection4" };
	int Key[20] = { 1, 2,3, 4 };
	string ResultSelected = "404";
	int AmountOfResults;
	int XSpacing = 10;
	int YSpacing = 10;
	void* SelecteeHighlighted = nullptr;
};


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
	int VertexCount = 4;
	//ShapeGroupData ShapeGroup;
	//PageItemData PageItem;
	//PageGroupData PageGroup;
	//Page* Page;
	//Shape
	int ID = -1;
	int Ascii = -1;
	int ActiveTexture = 0;
	int Action = -1;
	int Layer = 0;
	int Type = 0;
	int InputType = INPUT_CENTER;
	bool IsBackGround = false;
	glm::vec2 Position = { 0.0, 0.0 };
	glm::vec2 Size = { 0.05, 0.05 };
	glm::vec4 Color = { 1.0, 1.0, 1.0, 1.0 };
	glm::vec2 PositionOffset = { 0.0, 0.0 };
	glm::vec2 SizeOffset = { 0.0, 0.0 };
	glm::vec4 ColorOffset = { 0.0, 0.0, 0.0, 0.0 };
	glm::vec2 HighlightPosition = { 0.0, 0.0 };
	glm::vec2 HighlightSize = { this->Size[0] + 0.0135, this->Size[1] + 0.025 };
	glm::vec4 HighlightColor = {0.0, 0.0, 0.0, 1.0};
	bool MouseAccess = true;
	bool Centered = false;
	bool Highlighted = false;
	bool ShapeDataisHighlight = false;
	bool PartOfGroup = false;
	bool Hide = false;
	float Top = -3;
	float Bottom = -3;
	float Left = -3;
	float Right = -3;
	string Text = "ll";
	bool EndStart = false;
	bool TextCentered = true;
	bool ChangeAsGroup = false;
	ShapeVertex Vertex[4];
	void* ParentGroup = nullptr;
	llShapeData* Next = nullptr;
	llShapeData* Previous = nullptr;
	llVertexData* Vertexx = nullptr; // Child
	llVertexData* VertexxHead = nullptr; // Child
	Button* ShapeButton = nullptr;
	string DescriptiveData;
};

struct llShapeGroupData
{
	int ShapeCount = 0;
	///////////////////////////////////
	//ShapeGroup
	//Page* Page;
	int ID = -1;
	int Type = 0;
	int InputType = INPUT_LEFT;
	bool BackGround = false;
	bool BackGroundCopied = false;
	int BackGroundPlacementType = PLACEMENT_NORMAL; //Place Background above, below..
	int BackGroundMatchType = MATCH_NONE; //MATCH_CENTERS (BackGround Center to Group Center)
	float BackGroundXDifference = 0.0;
	float BackGroundYDifference = 0.0;
	glm::vec4 BackGroundColor = {0.5, 0.5, 0.5, 0.5};
	glm::vec4 BackGroundPadding = {4,4,4,4};
	glm::vec2 XYShapePerRow = { -1.0, -1.0 };
	glm::vec2 ShapeSize = { -1.0, -1.0 };
	glm::vec2 Position = { 0.0, 0.0 };
	glm::vec2 Size = { 0.0, 0.0 };
	glm::vec4 Color = { 1.0, 1.0, 1.0, 1.0 };
	glm::vec2 PositionOffset = { 0.0, 0.0 };
	glm::vec2 SizeOffset = { 0.0, 0.0 };
	glm::vec4 ColorOffset = { 0.0, 0.0, 0.0, 0.0 };
	glm::vec4 HighlightColor = { 0.0, 0.0, 0.0, 1.0 };
	bool Centered = false;
	bool Highlighted = false;
	bool MouseAccess = true;
	bool Hide = false;
	bool ChangeAsGroup = false;
	float Top = -3;
	float Bottom = -3;
	float Left = -3;
	float Right = -3;
	glm::vec4 EdgesWithBackGround = {3, -3, -3, 3};
	void* ParentGroup = nullptr;
	llShapeGroupData* Next = nullptr;
	llShapeGroupData* Previous = nullptr;
	llShapeData* Shape = nullptr; // Child
	llShapeData* ShapeHead = nullptr; // Child
	
	///////////////////////////////////
	llShapeData* operator[] (int i)
	{
		llShapeData* ToReturn = Shape;
		return ToReturn;
	}

	TextData TextData;
	Button* ShapeGroupButton = nullptr;
	string DescriptiveData;
	int Key;
};

struct llPageItemData
{
	//PageItem
	int ShapeGroupCount = 0;
	int ID = -1;
	int ShapeStart = 0;
	int ShapeCount = -1;
	int ShapeOffset = -1;
	int Type = 0;
	int InputType = INPUT_CENTER;
	bool BackGround = false;
	int BackGroundPlacementType = PLACEMENT_NORMAL; //Place Background above, below..
	int BackGroundMatchType = MATCH_NONE; //MATCH_CENTERS (BackGround Center to Group Center)
	glm::vec4 BackGroundColor = { 0.5, 0.5, 0.5, 0.5 };
	glm::vec4 BackGroundPadding = { 4,4,4,4 };
	glm::vec2 Position = { 0.0, 0.0 };
	glm::vec2 Size = { 0.0, 0.0 };
	glm::vec4 Color = { 1.0, 1.0, 1.0, 1.0 };
	glm::vec2 PositionOffset = { 0.0, 0.0 };
	glm::vec2 SizeOffset = { 0.0, 0.0 };
	glm::vec4 ColorOffset = { 0.0, 0.0, 0.0, 0.0 };
	glm::vec2 XYShapePerRow = { -1.0, -1.0 };
	glm::vec2 ShapeSize = { -1.0, -1.0 };
	glm::vec4 HighlightColor = { 0.0, 0.0, 0.0, 0.0 };
	bool Centered = false;
	bool Highlighted = false;
	bool MouseAccess = true;
	bool Hide = false;
	bool ChangeAsGroup = false;
	float Top = -3;
	float Bottom = -3;
	float Left = -3;
	float Right = -3;
	glm::vec4 EdgesWithBackGround = { 3, -3, -3, 3 };
	void* ParentGroup = nullptr;
	llPageItemData* Next = nullptr;
	llPageItemData* Previous = nullptr;
	llShapeGroupData* ShapeGroup = nullptr; // Child
	llShapeGroupData* ShapeGroupHead = nullptr; // Child
	Button* PageItemButton = nullptr;

	NumberPrinterData NumberPrinterData;
	SliderData SliderData;
	SelectorData SelectorData;
	string DescriptiveData = " ";
};

struct llPageGroupData
{
	int PageItemCount = 0;
	//PageGroup
	//Page* Page;
	int ID = -1;
	int ShapeStart = 0;     //Lowest level //EX: PageItem Starts at Shape 120
	int ShapeCount = -1;  //Lowest level //EX: PageItem owns 40 Shapes 
	int ShapeOffset = -1;      //Lowest level //EX: This Shape is 10 Shapes from PageItem start Shape (120)
	int Type = 0;
	int InputType = INPUT_CENTER;
	bool BackGround = false;
	int BackGroundPlacementType = PLACEMENT_NORMAL; //Place Background above, below..
	int BackGroundMatchType = MATCH_NONE; //MATCH_CENTERS (BackGround Center to Group Center)
	glm::vec4 BackGroundColor = { 0.5, 0.5, 0.5, 0.5 };
	glm::vec4 BackGroundPadding = { 4,4,4,4 };
	glm::vec2 Position = { 0.0, 0.0 };
	glm::vec2 Size = { 0.0, 0.0 };
	glm::vec4 Color = { 1.0, 1.0, 1.0, 1.0 };
	glm::vec2 XYShapePerRow = { -1.0, -1.0 };
	glm::vec2 ShapeSize = { -1.0, -1.0 };
	glm::vec4 HighlightColor = { 0.0, 0.0, 0.0, 0.0 };
	bool Centered = false;
	bool Highlighted = false;
	bool MouseAccess = true;
	bool Hide = false;
	bool ChangeAsGroup = false;
	float Top = -3;
	float Bottom = -3;
	float Left = -3;
	float Right = -3;
	glm::vec4 EdgesWithBackGround = { 3, -3, -3, 3 };
	void* ParentGroup = nullptr;
	llPageGroupData* Next = nullptr;
	llPageGroupData* Previous = nullptr;
	llPageItemData* PageItem = nullptr; // Child
	llPageItemData* PageItemHead = nullptr; // Child
	Button PageGroupButton;
	string DescriptiveData;
};

struct llPageData
{
	int PageGroupCount = 0;
	bool PageReady = false;
	string DescriptiveData;
	llVertexData* VertexContainer = nullptr;
	int* IndexContainer = nullptr;
	void* ParentGroup = nullptr;
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
	int PageCount = 0;
	llBookData* Next = nullptr;
	llBookData* Previous = nullptr;
	llPageData* Page = nullptr; // = nullptr; // Child
	llPageData* PageHead = nullptr;
};

struct BookDirectory
{
	llVertexData* Vertex = nullptr;
	llShapeData* Shape = nullptr;
	llShapeGroupData* ShapeGroup = nullptr;
	llPageItemData* PageItem = nullptr;
	llPageGroupData* PageGroup = nullptr;
	llPageData* Page = nullptr;
	bool NoDirectoryFound = true;

	void LoadUp(llBookData* llBook)
	{
		//Book
		if (llBook == nullptr) { Log::LogString("ERROR:: Capture Directory FAILED:: No Book To Capture"); return; }
		//Page
		llBook->Page = Page;
		if (llBook->Page == nullptr) { return; }
		//PageGroup
		llBook->Page->PageGroup = PageGroup;
		if (llBook->Page->PageGroup == nullptr) { return; }
		//PageItem
		llBook->Page->PageGroup->PageItem = PageItem;
		if (llBook->Page->PageGroup->PageItem == nullptr) { return; }
		//ShapeGroup
		llBook->Page->PageGroup->PageItem->ShapeGroup = ShapeGroup;
		if (llBook->Page->PageGroup->PageItem->ShapeGroup == nullptr) { return; }
		//Shape
		llBook->Page->PageGroup->PageItem->ShapeGroup->Shape = Shape;
		if (llBook->Page->PageGroup->PageItem->ShapeGroup->Shape == nullptr) { return; }
	}


	void Capture(llBookData* llBook)
	{
		//Book
		if (llBook == nullptr) { Log::LogString("ERROR:: Capture Directory FAILED:: No Book To Capture"); return; }
		//Page
		Page = llBook->Page;
		if (llBook->Page == nullptr) { return; }
		//PageGroup
		PageGroup = llBook->Page->PageGroup;
		if (llBook->Page->PageGroup == nullptr) { return; }
		//PageItem
		PageItem = llBook->Page->PageGroup->PageItem;
		if (llBook->Page->PageGroup->PageItem == nullptr) { return; }
		//ShapeGroup
		ShapeGroup = llBook->Page->PageGroup->PageItem->ShapeGroup;
		if (llBook->Page->PageGroup->PageItem->ShapeGroup == nullptr) { return; }
		//Shape
		Shape = llBook->Page->PageGroup->PageItem->ShapeGroup->Shape;
		if (llBook->Page->PageGroup->PageItem->ShapeGroup->Shape == nullptr) { return; }
	}
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

	static void CurrentDirectory(llBookData* llBook);

	//Quick Element Placement
	static void ManualPlaceBelow(const int PlacementType, const glm::vec4& ElementEdges, int& NewInputType, glm::vec2& NewPosition, int PixelPadding); //MatchEnds, MatchCenters, MatchBeginnings, MatchBeginningtoEnd, MatchEndtoBeginning
	static void ManualPlaceAbove(const int PlacementType, const glm::vec4& ElementEdges, int& NewInputType, glm::vec2& NewPosition, int PixelPadding); //MatchEnds, MatchCenters, MatchBeginnings, MatchBeginningtoEnd, MatchEndtoBeginning
	static void ManualPlaceRight(const int PlacementType, const glm::vec4& ElementEdges, int& NewInputType, glm::vec2& NewPosition, int PixelPadding); //MatchCenters
	static void ManualPlaceLeft(const int PlacementType, const glm::vec4& ElementEdges, int& NewInputType, glm::vec2& NewPosition, int PixelPadding);  //MatchCenters

	static void TextPlaceRight(const int PlacementType, const glm::vec4& ElementEdges, int& NewInputType, glm::vec2& NewPosition, int PixelPadding); //MatchCenters
	static void TextPlaceLeft(const int PlacementType, const glm::vec4& ElementEdges, int& NewInputType, glm::vec2& NewPosition, int PixelPadding);  //MatchCenters


	static glm::vec4 UpdateEdges(glm::vec4 TestEdges, glm::vec4 EdgesToUpdate);
	static void SizeFromEdges(glm::vec4 Edges, glm::vec2& Size);

	static llVertexData* GetBookVertex(llBookData* llBook);
	static llShapeData* GetBookShape(llBookData* llBook);
	static llShapeGroupData* GetBookShapeGroup(llBookData* llBook);
	static llPageItemData* GetBookPageItem(llBookData* llBook);
	static llPageGroupData* GetBookPageGroup(llBookData* llBook);
	static llPageData* GetBookPage(llBookData* llBook);

	//Get Head Element
	static llVertexData* HeadVertex(llVertexData* VertexReference);
	static llShapeData* HeadShape(llShapeData* ShapeReference);
	static llShapeGroupData* HeadShapeGroup(llShapeGroupData* ShapeGroupReference);
	static llPageItemData* HeadPageItem(llPageItemData* PageItemReference);
	static llPageGroupData* HeadPageGroup(llPageGroupData* PageGroupReference);
	static llPageData* HeadPage(llPageData* PageReference);

	//Book Traversing Functions
	static void NextPage(llBookData* llBook);
	static void PreviousPage(llBookData* llBook);
	static void NextPageGroup(llBookData* llBook);
	static void PreviousPageGroup(llBookData* llBook);
	static void NextPageItem(llBookData* llBook);
	static void PreviousPageItem(llBookData* llBook);
	static void NextShapeGroup(llBookData* llBook);
	static void PreviousShapeGroup(llBookData* llBook);
	static void NextShape(llBookData* llBook);
	static void PreviousShape(llBookData* llBook);

	//Add Empty
	//Returns nullptr if no book provided
	static llShapeData* AddShape(llBookData* Book);
	static llShapeGroupData* AddShapeGroup(llBookData* Book);
	static llPageItemData* AddPageItem(llBookData* Book);
	static llPageGroupData* AddPageGroup(llBookData* Book);
	static llPageData* AddPage(llBookData* Book);
	static llBookData* AddBook();

	//Duplicate
	static void CopyShape(llBookData* Book, llShapeData* ShapeReference);
	static void CopyShapeGroup(llBookData* Book, llShapeGroupData* ShapeGroupReference);
	static void CopyPageItem(llBookData* Book, llPageItemData* PageItemReference);
	static void CopyPageGroup(llBookData* Book, llPageGroupData* PageGroupReference);
	static void CopyPage(llBookData* Book, llBookData* PageReference);
	static void CopyBook(llBookData* NewBook, llBookData* BookReference);

	//Delete
	static void DeleteShape(llBookData* NewBook, llShapeData* ShapeReference);
	static void DeleteShapeGroup(llBookData* NewBook, llShapeGroupData* ShapeReference);
	static void DeletePageItem(llBookData* llBook, llPageItemData* PageItemReference);
	static void DeletePageGroup(llBookData* llBook, llPageGroupData* PageGroupReference);
	static void DeletePage(llBookData* llBook, llPageData* PageReference);
	static void EraseBook(llBookData* llBook);

	static void ToggleToggle(bool& ToToggle);
	static void FindElement(llBookData* llBook, int ElementLevel, BookDirectory& BookDirectory);

	//Print Book
	static void PrintBookStats(llBookData* llBook);
	static void PrintPageItemStats(llPageItemData* llPageItem);

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

	virtual void VirtualTest() { Log::LogString("I am a Master Element"); };

	virtual void Add_Duplicate() {}; 
	virtual void Add_Insert() {};
	virtual void Delete() {};

	virtual void llUpdate() {};
	virtual void lllSwitch(int Offset) {};
	virtual ShapeData& Switch(int RequstedShapeID) { return LoadedShape; };
	virtual ShapeData& Switch(Page& Page, int RequstedShapeID) { return LoadedShape; };
	//virtual void SetShape(ShapeData& ShapeData) {};
	//virtual void SetShape(ShapeData& ShapeData, glm::vec2 PSConversions) {};

	//virtual float* GetColorR() {};
	//virtual float* GetColorG() {};
	//virtual float* GetColorB() {};
	//virtual float* GetColorA() {};
	//virtual glm::vec2* GetPosition() {};
	//virtual glm::vec2* GetSize() {};
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

	//virtual glm::vec2 GetPosition() { return { -1.0, -1.0 }; };
	virtual glm::vec2 GetSize() { return { -1.0, -1.0 }; };
	//virtual glm::vec4 GetColor() { return { -1.0, -1.0, -1.0, -1.0 }; };
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
