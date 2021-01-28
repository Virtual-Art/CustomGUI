#ifndef PAGE
#define PAGE

#include <iostream>
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include "UIShapeData.h"
#include "ShaderProgram.h"
#include <array>
#include "Container.h"
#include "Maths.h"
#include "TextSpecification.h"
#include "FontMath.h"
#include "System.h"
#include "KeyboardManager.h"
#include "MouseManager.h"
#include "System.h"
//#include "ShapeDataAction.h"


#define PI 3.14

using namespace std;

#define TYPE_SHAPE 0
#define TYPE_GRID 1
#define TYPE_TEXT 2

#define TYPE_SLIDER 9

struct ShapeVertex
{
	glm::vec2 Position = { 0.0, 0.0 };
	glm::vec2 TexCoords = { 0.0, 0.0 };
	glm::vec4 Color = { 0.0, 0.0, 0.0, 0.0 };
	float TexIndex = 0.0;
	glm::vec2 CentralPoint = { 0.0, 0.0 };
	int GUIAction = 0;
	//glm::vec2 XYRatio = { 0.0, 0.0 };
};


struct PageData
{

};

struct PageGroupData
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

};


struct PageItemData
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
	glm::vec2 XYShapePerRow = { -1.0, -1.0 };
	glm::vec2 ShapeSize = { -1.0, -1.0 };
	bool Centered = false;
	bool Highlighted = false;
	bool MouseAccess = true;
	float Top = -3;
	float Bottom = -3;
	float Left = -3;
	float Right = -3;
	PageGroupData PageGroup;
};


struct ShapeGroupData
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
	bool Centered = false;
	bool Highlighted = false;
	bool MouseAccess = true;
	float Top = -3;
	float Bottom = -3;
	float Left = -3;
	float Right = -3;
	PageItemData PageItem;
	///////////////////////////////////
};

struct ShapeData
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
	glm::vec2 Size = { 0.25, 0.5 };
	glm::vec4 Color = { 1.0, 1.0, 1.0, 1.0 };
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
	ShapeGroupData ShapeGroup;
};






struct CShapeData
{
	CShapeData()
	{
		//ShapeData
		this->ID = -1;
		this->Ascii = 0;
		this->ActiveTexture = 0;
		this->Action = 0;
		this->GroupID = -1;
		this->ShapeDataType = TYPE_SHAPE;
		this->Position = { 0, 0 };
		this->Size = { 0.5, 0.5 };
		this->Color = { 1.0, 1.0, 1.0, 1.0 };
		this->HighlightPosition = this->Position;
		this->HighlightSize = { this->Size[0] + 0.0135, this->Size[1] + 0.025 };
		this->HighlightColor = { 0.0, 0.7156, 0.0, 1.0 };
		this->Centered = false;
		this->MouseAccess = true;
		this->Highlighted = false;
		this->ShapeDataisHighlight = false;
		this->PartOfGroup = false;
		this->Top = (Position.y - Size.y);
		this->Bottom = (Position.y);
		this->Left = (Position.x);
		this->Right = (Position.x + Size.x);
		this->Text = "Text";
		this->EndStart = false;
		this->TextCentered = true;

		//Group Data
		this->ShapeGroupStart = -100;
		this->ShapeGroupCount = -100;
		this->ShapeGroupOffset = -1;
		this->ShapeGroupXYShapePerRow = { -1, -1 };
		this->ShapeGroupShapeSize = { 0.8, 0.8 }; //as a percentage inside the grid
		this->ShapeGroupSize = { -1, -1 };
		this->ShapeGroupPosition = { -100, -100 };
		this->ShapeGroupColor = { -1, -1, -1, -1 };
		this->ShapeGroupCentered = 0;
		this->ShapeGroupHighlighted = 0;
		this->ShapeGroupMouseAccess = true;

		//PageGroupItem
		PageGroupItemID = -1;
		int PageGroupItemShapeStartID;     //Lowest level //EX: PageItem Starts at Shape 120
		int PageGroupItemShapeCount = -1;  //Lowest level //EX: PageItem owns 40 Shapes 
		int PageGroupItemShapeOffset;      //Lowest level //EX: This Shape is 10 Shapes from PageItem start Shape (120)
		int PageGroupItemCellStartID = -1; //Upper Level //EX: PageGroup Starts at shape 100 
		int PageGroupItemCellCount = -1;   //Upper Level //EX: PageGroup owns 20 PageItems	
		int PageGroupItemCellOffset = -1;  //Upper Level //EX: This PageItem is 5 PageItems from the start PageItem
		this->PageGroupItemXYShapePerRow = { -1, -1 };
		this->PageGroupItemShapeSize = { 0.8, 0.8 };
		this->PageGroupItemPosition = { -1, -1 };
		this->PageGroupItemSize = { -100, -100 };
		this->PageGroupItemColor = { -1, -1, -1, -1 };
		this->PageGroupItemCentered = 0;
		this->PageGroupItemHighlighted = 0;
		this->PageGroupItemMouseAccess = true;
		this->PageGroupItemType = 0;
	};

	void reset()
	{
		//ShapeData
		this->ID = -1;
		this->ActiveTexture = 0;
		this->Action = 0;
		this->GroupID = -1;
		this->ShapeDataType = TYPE_SHAPE;
		this->Position = { 0, 0 };
		this->Size = { 0.5, 0.5 };
		this->Color = { 1.0, 1.0, 1.0, 1.0 };
		this->HighlightPosition = this->Position;
		this->HighlightSize = { this->Size[0] + 0.0135, this->Size[1] + 0.025 };
		this->HighlightColor = { 0.0, 0.7156, 0.0, 1.0 };
		this->Centered = false;
		this->MouseAccess = true;
		this->Highlighted = false;
		this->ShapeDataisHighlight = false;
		this->PartOfGroup = false;
		this->Top = (Position.y - Size.y);
		this->Bottom = (Position.y);
		this->Left = (Position.x);
		this->Right = (Position.x + Size.x);
		this->Text = "Text";

		//Group Data
		this->ShapeGroupStart = -1;
		this->ShapeGroupCount = -1;
		this->ShapeGroupOffset = -1;
		this->ShapeGroupXYShapePerRow = { -1, -1 };
		this->ShapeGroupShapeSize = { -1, -1 }; //as a percentage inside the grid
		this->ShapeGroupSize = { -1, -1 };
		this->ShapeGroupPosition = { -100, -100 };
		this->ShapeGroupColor = { -1, -1, -1, -1 };
		this->ShapeGroupCentered = 0;
		this->ShapeGroupHighlighted = 0;
		this->ShapeGroupMouseAccess = true;

		//PageGroupItem
		PageGroupItemID = -1;
		this->PageGroupItemShapeStartID = -1;
		this->PageGroupItemShapeOffset = -1;
		this->PageGroupItemShapeCount = -1;
		this->PageGroupItemCellStartID = -1;
		this->PageGroupItemCellOffset = -1;
		this->PageGroupItemCellCount = -1;
		this->PageGroupItemXYShapePerRow = { -1, -1 };
		this->PageGroupItemShapeSize = { -1, -1 };
		this->PageGroupItemPosition = { -100, -100 };
		this->PageGroupItemSize = { -1, -1 };
		this->PageGroupItemColor = { -1, -1, -1, -1 };
		this->PageGroupItemCentered = 0;
		this->PageGroupItemHighlighted = 0;
		this->PageGroupItemMouseAccess = true;
	}

	//Shape
	int ID;
	int Ascii;
	int ActiveTexture;
	int Action;
	int Layer;

	int ShapeDataType;
	glm::vec2 Position;
	glm::vec2 Size;
	glm::vec4 Color;
	glm::vec2 HighlightPosition;
	glm::vec2 HighlightSize;
	glm::vec4 HighlightColor;
	bool MouseAccess;
	bool Centered;
	bool Highlighted;
	bool ShapeDataisHighlight;
	bool PartOfGroup;
	float Top;
	float Bottom;
	float Left;
	float Right;
	string Text;
	bool EndStart;
	bool TextCentered;
	ShapeVertex Vertex[4];

	//ShapeGroup
	int GroupID;
	int ShapeGroupStart;
	int ShapeGroupOffset;
	int ShapeGroupCount;
	glm::vec2 ShapeGroupXYShapePerRow;
	glm::vec2 ShapeGroupShapeSize;
	glm::vec2 ShapeGroupPosition;
	glm::vec2 ShapeGroupSize;
	glm::vec4 ShapeGroupColor;
	bool ShapeGroupCentered;
	bool ShapeGroupHighlighted;
	bool ShapeGroupMouseAccess;
	float ShapeGroupTop;
	float ShapeGroupBottom;
	float ShapeGroupLeft;
	float ShapeGroupRight;

	//PageGroupItem
	int PageGroupItemID;
	int PageGroupItemShapeStartID;     //Lowest level //EX: PageItem Starts at Shape 120
 	int PageGroupItemShapeCount;  //Lowest level //EX: PageItem owns 40 Shapes 
	int PageGroupItemShapeOffset;      //Lowest level //EX: This Shape is 10 Shapes from PageItem start Shape (120)
	int PageGroupItemCellStartID; //Upper Level //EX: PageGroup Starts at shape 100 
	int PageGroupItemCellCount;   //Upper Level //EX: PageGroup owns 20 PageItems	
	int PageGroupItemCellOffset;  //Upper Level //EX: This PageItem is 5 PageItems from the start PageItem
	int PageGroupItemType;
	glm::vec2 PageGroupItemXYShapePerRow;
	glm::vec2 PageGroupItemShapeSize;
	glm::vec2 PageGroupItemPosition;
	glm::vec2 PageGroupItemSize;
	glm::vec4 PageGroupItemColor;
	bool PageGroupItemCentered;
	bool PageGroupItemHighlighted;
	bool PageGroupItemMouseAccess;
	float PageGroupItemTop;
	float PageGroupItemBottom;
	float PageGroupItemLeft;
	float PageGroupItemRight;

	//Page Group
	int PageGroupID;
	int PageGroupShapeStartID;     //Lowest level //EX: PageItem Starts at Shape 120
	int PageGroupShapeCount;  //Lowest level //EX: PageItem owns 40 Shapes 
	int PageGroupShapeOffset;      //Lowest level //EX: This Shape is 10 Shapes from PageItem start Shape (120)
	int PageGroupCellStartID; //Upper Level //EX: PageGroup Starts at shape 100 
	int PageGroupCellCount;   //Upper Level //EX: PageGroup owns 20 PageItems	
	int PageGroupCellOffset;  //Upper Level //EX: This PageItem is 5 PageItems from the start PageItem
	int PageGroupType;
	glm::vec2 PageGroupXYShapePerRow;
	glm::vec2 PageGroupShapeSize;
	glm::vec2 PageGroupPosition;
	glm::vec2 PageGroupSize;
	glm::vec4 PageGroupColor;
	bool PageGroupCentered;
	bool PageGroupHighlighted;
	bool PageGroupMouseAccess;
	float PageGroupTop;
	float PageGroupBottom;
	float PageGroupLeft;
	float PageGroupRight;

};

struct Grid
{
	glm::vec2 XYShapeDatasPerRow;
	glm::vec2 Size;
	glm::vec2 Position;
	glm::vec2 ShapeDataSize;
	glm::vec4 Color;
	bool Centered;
	bool MouseAccess;
	bool Highlighted;
	int Start;
	int Count;
	//Page* Page;

	Grid() {};
	
	//void DataFromShapeData(ShapeData& ShapeData)
	//{
	//	this->XYShapeDatasPerRow = ShapeData.GridXYShapeDatasPerRow;
	//	this->Size = ShapeData.ShapeGroupSize;
	//	this->Position = ShapeData.ShapeGroupPosition;
	//	this->ShapeDataSize = ShapeData.GridShapeSize;
	//	this->Color = ShapeData.ShapeGroupColor;
	//	this->Centered = false;
	//	this->Start = ShapeData.GroupStart;
	//	this->Count = XYShapeDatasPerRow[0] * XYShapeDatasPerRow[1];
	//	this->MouseAccess = ShapeData.MouseAccess;
	//	this->Highlighted = ShapeData.Highlighted;
	//}

	Grid(glm::vec2 XYShapeDatasPerRow, glm::vec2 ShapeGroupSize, glm::vec2 ShapeGroupPosition, glm::vec2 ShapeDataSize, glm::vec4 Color, bool Centered)
	{
		this->XYShapeDatasPerRow = XYShapeDatasPerRow;
		this->Size = ShapeGroupSize;
		this->Position = ShapeGroupPosition;
		this->ShapeDataSize = ShapeDataSize;
		this->Color = Color;
		this->Centered = Centered;
		this->Start = -1;
		this->Count = XYShapeDatasPerRow[0] * XYShapeDatasPerRow[1];
		this->MouseAccess = true;
		this->Highlighted = false;
	}
};

struct Layer
{

	struct LayerGrid
	{
		int LayerOffset;
		int Size;

		void UpdatePosition(int Offset)
		{
			this->LayerOffset += Offset;
		}
		void UpdateSize(int Offset)
		{
			this->Size += Offset;
		}
	};

	//where layer starts
	int LayerID = 0;
	unsigned int ShapeDataCount = 0;
	LayerGrid GridContainer[100];
	int CurrentGridCount;

	int GetShapeDataFillPosition()
	{
		return this->LayerID + this->ShapeDataCount;
	}

	int GetVertexFillPosition()
	{
		return((this->LayerID + this->ShapeDataCount) * 4);
	}

	//return an int that is the difference between the fill position and the start of the layer
	int GetGridOffset()
	{
		int FillPos = GetShapeDataFillPosition();
		return (FillPos - LayerID);
	}
};

class Page
{
public:	

	int MaxShapeDataCount;
	int MaxIndexCount;
	int MaxVertexCount;
	int MaxTextures = 8;

	//For Stats
	int TotalShapeGroupCount = 0;
	int TotalPageItemCount = 0;
	int TotalPageGroupCount = 0;
	int TotalShapeCount = 0;

	//For IDs
	int CurrentPageGroup = -1;
	int CurrentPageItem = -1;
	int CurrentShapeGroup = -1;
	int CurrentShape = -1;

	//For Shape Offsets
	int CurrentPageGroupShapeCount = -1; 
	int CurrentPageItemShapeCount = -1;
	int CurrentShapeGroupShapeCount = -1; //there might be 10 shape groups but the 10th group might have 100 shapes in it
	int CurrentShapeCount = -1;

	static GLuint WhiteTexture;


	//static ShapeData* ShapeDataPointer;
	//static Vertex* VertexPointer;
	//static uint32_t* IndexPointer;
	//ShapeData* ShapeContainer; //ShapeDataData
	//Vertex* VertexContainer; //ShapeDataDataContainer
    //uint32_t* IndexContainer; // IndexContainer
	//Container<Vertex>* VertexContainer;

	//Building Maitnence don't touch
	Container<unsigned int> MakeIndexContainer(int ContainerSize)
	{
		Container<unsigned int> ArrUint8_ts(ContainerSize * 6);
		return ArrUint8_ts;
	}
	Container<ShapeVertex> MakeVertexContainer(int ContainerSize)
	{
		Container<ShapeVertex> ArrVertices(ContainerSize * 4);
		return ArrVertices;
	}

	Container<ShapeData> MakeShapeContainer(int ContainerSize)
	{
		Container<ShapeData> ArrShapeDatas(ContainerSize);
		return ArrShapeDatas;
	}


	Container<unsigned int> IndexContainer;
	Container<ShapeData> ShapeContainer;
	Container<ShapeVertex> VertexContainer;	
	//Container<ShapeDataAction> ActionContainer;
	bool DrawCircle;
	//Container<float>& FloatContainer;

	string Name;
	size_t PageSize;
	size_t MaxPageSize;
	size_t ShapeDataSize;
    int PageShapeCount;
    int PageIndexCount;



	//static int TotalIndexCount;
	//static int TotalShapeDataCount;

	GLuint VA;
	GLuint VB;
	GLuint IB;

	static int PageCount;
	int PageID;

	array<uint32_t, 16> TextureSlots;

	uint32_t TextureSlotIndex = 1;

	//How many layers we are currently using 
	int CurrentLayerCount;
	//what layer are we on
	int CurrentLayer;

	//Layer Layer[10];
	ShapeData ShapeZero;
	ShapeVertex VertexZero;
	int LastShapeDataHovered;
	bool EMouseControl;
	bool GMouseControl;

	ShapeData ClipBoard;
	
	int VertexCount()
	{
		return VertexContainer.CurrentContainerAmount;
	}

	int ShapeCount()
	{
		return ShapeContainer.CurrentContainerAmount;
	}


	Page(int NumberOfShapeDatas);
	Page();


	void DeletePage();
	void Init(ShaderProgram ShaderProgram);
	void IncreaseShapeDataCount();

	void PrintShape(int ID)
	{
		if (InBounds(ID) == false) 
		{ cout << "Print Shape Error::ID Out Of Bounds" << endl; return; }

		ShapeData& CurrentShapeData = GetShapeDataR(ID);
		cout << "------------PageGroup-Data (" << CurrentShapeData.ShapeGroup.PageItem.PageGroup.ID << ")------------------" << endl;
		cout << "Position: {" << CurrentShapeData.ShapeGroup.PageItem.PageGroup.Position[0] << " , " << CurrentShapeData.Position[1] << "}" << endl;
		cout << "Size: {" << CurrentShapeData.ShapeGroup.PageItem.PageGroup.Size[0] << " , " << CurrentShapeData.ShapeGroup.PageItem.PageGroup.Size[1] << "}" << endl;
		cout << "Color: {" << CurrentShapeData.ShapeGroup.PageItem.PageGroup.Color[0] << " , " << CurrentShapeData.ShapeGroup.PageItem.PageGroup.Color[1] << " , " << CurrentShapeData.ShapeGroup.PageItem.PageGroup.Color[2] << " , " << CurrentShapeData.ShapeGroup.PageItem.PageGroup.Color[3] << "}" << endl;
		
	    cout << "------------PageItem-Data (" << CurrentShapeData.ShapeGroup.PageItem.ID << ")------------------" << endl;
		cout << "Position: {" << CurrentShapeData.ShapeGroup.PageItem.Position[0] << " , " << CurrentShapeData.ShapeGroup.PageItem.Position[1] << "}" << endl;
		cout << "Size: {" << CurrentShapeData.ShapeGroup.PageItem.Size[0] << " , " << CurrentShapeData.ShapeGroup.PageItem.Size[1] << "}" << endl;
		cout << "Color: {" << CurrentShapeData.ShapeGroup.PageItem.Color[0] << " , " << CurrentShapeData.ShapeGroup.PageItem.Color[1] << " , " << CurrentShapeData.ShapeGroup.PageItem.Color[2] << " , " << CurrentShapeData.ShapeGroup.PageItem.Color[3] << "}" << endl;
		
		cout << "------------ShapeGroup-Data (" << CurrentShapeData.ShapeGroup.ID << ")------------------" << endl;
		cout << "Position: {" << CurrentShapeData.ShapeGroup.Position[0] << " , " << CurrentShapeData.ShapeGroup.Position[1] << "}" << endl;
		cout << "Size: {" << CurrentShapeData.ShapeGroup.Size[0] << " , " << CurrentShapeData.ShapeGroup.Size[1] << "}" << endl;
		cout << "Color: {" << CurrentShapeData.ShapeGroup.Color[0] << " , " << CurrentShapeData.ShapeGroup.Color[1] << " , " << CurrentShapeData.ShapeGroup.Color[2] << " , " << CurrentShapeData.ShapeGroup.Color[3] << "}" << endl;

		cout << "------------ShapeData-Data (" << CurrentShapeData.ID << ")------------------" << endl;
		cout << "Position: {" << CurrentShapeData.Position[0] << " , " << CurrentShapeData.Position[1] << "}" << endl;
		cout << "Size: {" << CurrentShapeData.Size[0] << " , " << CurrentShapeData.Size[1] << "}" << endl;
		cout << "Color: {" << CurrentShapeData.Color[0] << " , " << CurrentShapeData.Color[1] << " , " << CurrentShapeData.Color[2] << " , " << CurrentShapeData.Color[3] << "}" << endl;

		//cout << "ActiveTexture: {" << CurrentShapeData.ActiveTexture << "}" << endl;
		//cout << "Action: {" << CurrentShapeData.Action << "}" << endl;
		//cout << "MouseAccess: {" << CurrentShapeData.MouseAccess << "}" << endl;
		//cout << "Centered: {" << CurrentShapeData.Centered << "}" << endl;
		//cout << "Highlighted: {" << CurrentShapeData.Highlighted << "}" << endl;
		cout << "-------" << endl;
		cout << "Text: " << CurrentShapeData.Text << endl;
		cout << "Ascii: " << char(CurrentShapeData.Ascii) << endl;
		cout << "------" << endl;
		if (CurrentShapeData.ShapeGroup.PageItem.PageGroup.ShapeStart == CurrentShapeData.ID)
		{
			cout << "PageGroup Start: {STARTS AT THIS SHAPE}" << endl;
		}
		else
		{
			cout << "PageGroup Start: {" << CurrentShapeData.ShapeGroup.PageItem.PageGroup.ShapeStart << "}" << endl;
		}

		if (CurrentShapeData.ShapeGroup.PageItem.ShapeStart == CurrentShapeData.ID)
		{
			cout << "PageItem Start: {STARTS AT THIS SHAPE}" << endl;
		}
		else
		{
			cout << "PageItem Start: {" << CurrentShapeData.ShapeGroup.PageItem.ShapeStart << "}" << endl;
		}

		if (CurrentShapeData.ShapeGroup.ShapeStart == CurrentShapeData.ID)
		{
			cout << "ShapeGroup Start: {STARTS AT THIS SHAPE}" << endl;
		}
		else
		{
			cout << "ShapeGroup Start: {" << CurrentShapeData.ShapeGroup.ShapeStart << "}" << endl;
		}
		cout << "---PageGroup- " << "(" << CurrentShapeData.ShapeGroup.PageItem.PageGroup.ID << ")" << " Shape (" << CurrentShapeData.ShapeGroup.PageItem.PageGroup.ShapeOffset << "/" << CurrentShapeData.ShapeGroup.PageItem.PageGroup.ShapeCount << ")----" << endl;
		cout << "---PageItem- " << "(" << CurrentShapeData.ShapeGroup.PageItem.ID << ")" << " Shape (" << CurrentShapeData.ShapeGroup.PageItem.ShapeOffset << "/" << CurrentShapeData.ShapeGroup.PageItem.ShapeCount << ")----" << endl;
		cout << "---ShapeGroup- "<< "(" << CurrentShapeData.ShapeGroup.ID << ")" << " Shape (" << CurrentShapeData.ShapeGroup.ShapeOffset << "/"<< CurrentShapeData.ShapeGroup.ShapeCount << ")----" << endl;
		cout << "------" << endl;

		//cout << "ShapeTop: " << CurrentShapeData.Top << endl;
		//cout << "ShapeBottom: " << CurrentShapeData.Bottom << endl;
		//cout << "ShapeLeft: " << CurrentShapeData.Left << endl;
		//cout << "ShapeRight: " << CurrentShapeData.Right << endl;
		//cout << "------" << endl;
		//cout << "ShapeGroup Top: " << CurrentShapeData.ShapeGroup.Top << endl;
		//cout << "ShapeGroup Bottom: " << CurrentShapeData.ShapeGroup.Bottom << endl;
		//cout << "ShapeGroup Left: " << CurrentShapeData.ShapeGroup.Left << endl;
		//cout << "ShapeGroup Right: " << CurrentShapeData.ShapeGroup.Right << endl;
		//cout << "------" << endl;
		//cout << "PageItem Top: " << CurrentShapeData.ShapeGroup.PageItem.Top << endl;
		//cout << "PageItem Bottom: " << CurrentShapeData.ShapeGroup.PageItem.Bottom << endl;
		//cout << "PageItem Left: " << CurrentShapeData.ShapeGroup.PageItem.Left << endl;
		//cout << "PageItem Right: " << CurrentShapeData.ShapeGroup.PageItem.Right << endl;
		cout << "------------------------------------------------------------------------------------------------" << endl;
	};


	//////////////////////////////////NEW SHAPE FUNCTIONS///////////////////////////////////////
	void AddShape(ShapeData& Shape);
	void ReplaceShape(ShapeData& Shape);

	//void DeleteShape(ShapeData& Shape);
	ShapeData* GetShapeDataP(int ID);
	ShapeData& GetShapeDataR(int ID);

	//Get's the address of the Next available Shape in the container
	ShapeData* GetNextShapeAddress();
	ShapeData* GetNextShapeAddress(int Offset);

	bool InBounds(int RequestedID)
	{
		return ShapeContainer.CheckBounds(RequestedID);
	}

	////////////////////////////////////////////////////////////////////////////////////////////

	//Grids
	//int AddShapeDataGrid(Grid& Grid);
	//void ReplaceShapeDataGrid(Grid& NewGrid);
	void DeleteShapeDataGrid(int Layers, int GridSpot, int ShapeGroupSize);
	
	//ShapeDatas
	//int AddShapeData(ShapeData& ShapeData, bool Centered, bool InsideGrid);
	void MoveShapeData(int CurrentSpot, int NewSpot, bool Centered, bool MouseAccess);
//	void ReplaceShapeData(int Spot, ShapeData& NewShapeData, bool Centered, bool MouseAccess);
	//With the same vertices
//	void ReplaceShapeDataH(int Spot, ShapeData& NewShapeData, bool Centered, bool MouseAccess, bool Hidden);
//	int CopyShapeData(int Spot);
//	void SetClipBoard(int Spot);
//	int ShapeDataMultiCopy(MouseManager Mouse);
	void InsertShapeArray(int Spot, int Amount);
	void DeleteShapeArray(int Spot, int Amount);
	void DeleteShapeData(int Spot);
	
	//Layers
	//void AddLayer();
	//void ChangeLayers(int Layers);
	//void AddShapeDataLayer();

	void HideTextBox(int TextStart, bool MouseAccess);
	void UnHideTextBox(int TextStart, float AlphaChannel, bool MouseAccess);
	//Text Class
	//void AddCharacter(ShapeData& ShapeData, Character Character, bool InsideGrid);
	int AddTextBox(TextSpecification TextSpecs);
	//void ReplaceCharacter(int Spot, ShapeData& NewShapeData, Character Character, bool Centered);
	void ReplaceTextBox(TextSpecification NewTextSpecs);
	bool QueryLineRestart(glm::vec2 CursorPosition, float MaxLine);

	bool HighlightShapeData(ShapeData* ShapeDataSelected);
	bool RemoveHighlight(ShapeData* ShapeDataHovered, int& HighlightCount);


	//ShapeData Editing Functions

	//Vertex* GetVertices(int Spot);
	void ClearShapeData(int Spot);
	void HideShapeData(int Spot, bool MouseAccess);
	void UnHideShapeData(int Spot, float AlphaChannel, bool MouseAccess);
	//void ChangeShapeData(int Spot, ShapeData& NewShapeData, bool MouseAccess);
	//void ChangeShapeDataColor(int Spot, glm::vec4 Color, bool MouseAccess);
	//void ChangeShapeDataPosition(int Spot, glm::vec2 Position, char ChangeOnly, bool OnCenter, bool MouseAccess);
	//void ChangeShapeDataSize(int Spot, glm::vec2 Size, char ChangeOnly, bool OnCenter, bool MouseAccess);
	//void ChangeShapeDataTexture(int Spot, int TextureSlot, bool MouseAccess);
    //void ChangeHighlight(int Spot, bool Highlight);
	//
	//void OffsetShapeDataColor(int Spot, glm::vec4 ColorOffset, bool MouseAccess);
	//void OffsetShapeDataPosition(int Spot, glm::vec2 PositionOffset, char ChangeOnly, bool MouseAccess);
	//void OffsetShapeDataSize(int Spot, glm::vec2 SizeOffset, char ChangeOnly, bool OnCenter, bool MouseAccess);
	//void OffsetShapeDataTexture(int Spot, int TextureSlotOffset, bool MouseAccess);
	//void ProcessShapeDataSelection(int ShapeData, int PixelOffset, int MouseState, KeyResult KeyState, MouseManager Mouse, glm::vec2 Scroll);
	//glm::vec4 ProcessColorSelection(int ColorShapeData, int ColorSelectID, int BarID, int MouseState, MouseManager Mouse, Page& Page);
	//glm::vec4 SetColorBars(glm::vec4 Color, int ColorSelectID);
	//glm::vec4 UserBarSetter(Page& Page, int ColorShapeData, int MouseState, MouseManager Mouse, int BarID, int ColorSelectID);
	//
	////ShapeData Group Editing Functions 
	//void ClearSelectionGroup(int* Selections, int SelectionsSize);
	//void HideSelectionGroup(int* Selections, int SelectionsSize, bool MouseAccess);
	//void UnHideSelectionGroup(int* Selections, int SelectionsSize, float AlphaChannel, bool MouseAccess);
	//void ChangeSelectionColor(int* Selections, int SelectionsSize, glm::vec4 Color, bool MouseAccess);
	//void ChangeSelectionPosition(int* Selections, int SelectionsSize, glm::vec2 Position, char ChangeOnly, bool OnCenter, bool MouseAccess);
	//void ChangeSelectionSize(int* Selections, int SelectionsSize, glm::vec2 Size, bool OnCenter, char ChangeOnly, bool MouseAccess);
	//void ChangeSelectionTexture(int* Selections, int SelectionsSize, int TextureSlot, bool MouseAccess);
	//void ChangeSelectionHighlight(int* Selections, int SelectionsSize, bool Highlight);
	//
	//Grid& GetGrid(int GroupShapeData);
	//
	////Grid Editing Functions
	//void HideGrid(int GroupShapeData);
	//void UnHideGrid(int GroupShapeData, float AlphaChannel);
	//void ChangeGridXYShapeDatasPerRow(int GroupShapeData, glm::vec2 NewXYShapeDatasPerRow);
	//void ChangeShapeGroupSize(int GroupShapeData, glm::vec2 NewShapeGroupSize);
	//void ChangeShapeGroupPosition(int GroupShapeData, glm::vec2 NewShapeGroupPosition, char ChangeOnly, bool Centered);
	//void ChangeGridShapeSize(int GroupShapeData, glm::vec2 NewGridShapeSize);
	//void ChangeShapeGroupColor(int GroupShapeData, glm::vec4 NewColor);
	//
	////Grid Editing Functions
	//void OffsetGridXYShapeDatasPerRow(int GroupShapeData, glm::vec2 NewXYShapeDatasPerRow, char ChangeOnly);
	//void OffsetShapeGroupSize(int GroupShapeData, glm::vec2 NewShapeGroupSize, char ChangeOnly, bool Centered);
	//void OffsetShapeGroupPosition(int GroupShapeData, glm::vec2 NewShapeGroupPosition, char ChangeOnly, bool Centered);
	//void OffsetGridShapeSize(int GroupShapeData, glm::vec2 NewGridShapeSize, char ChangeOnly);
	//
	//void ProccessGridSelection(int GridShapeData, int PixelOffset, int MouseState, KeyResult KeyState, MouseManager Mouse, glm::vec2 Scroll);
	//void ShapeGroupPositionDetailed(int Grid, int PixelOffset, KeyResult KeyState);
	//void ShapeGroupSizeDetailed(int GridShapeData, int PixelOffset, KeyResult KeyState);
	//void GridMouseControl(int Grid, MouseManager Mouse, glm::vec2 Scroll, bool Shift);
	//void GridShapeSizeDetailed(int Grid, int PixelOffset, KeyResult KeyState);
	//void GridXYDetailed(int Grid, int PixelOffset, KeyResult KeyState);
	//
	//void ShapeDataMouseControl(int ShapeData, MouseManager Mouse, glm::vec2 Scroll);
	//void ShapeDataPositionDetailed(int ShapeData, int PixelOffset, KeyResult KeyState); 
	//void ShapeDataSizeDetailed(int ShapeData, int PixelOffset, KeyResult KeyState);
	//
	//
	////TextBoxFunctions
	//int PrintVector2(glm::vec2 Vector, glm::vec2 Position, glm::vec4 Color);
	//int PrintVector3(glm::vec3 Vector, glm::vec2 Position, glm::vec4 Color);
	//int PrintVector4(glm::vec4 Vector, glm::vec2 Position, glm::vec4 Color);
	//int PrintFloat(float Float, glm::vec2 Position, glm::vec4 Color);
	//int PrintInt(int Int, glm::vec2 Position, glm::vec4 Color);
	//int PrintBool(bool Bool, glm::vec2 Position, glm::vec4 Color);
	//
	//void ChangeVector2(int TextStart, glm::vec2 Vector, glm::vec2 Position, glm::vec4 Color);
	//void ChangeVector3(int TextStart, glm::vec2 Vector, glm::vec2 Position, glm::vec4 Color);
	//void ChangeVector4(int TextStart, glm::vec4 Vector, glm::vec2 Position, glm::vec4 Color);
	//void ChangeFloat  (int TextStart, float Float, glm::vec2 Position, glm::vec4 Color);
	//void ChangeInt    (int TextStart, int Int, glm::vec2 Position, glm::vec4 Color);


	int FindShapeData(double xMouse, double yMouse, bool Print);
	void LoadThisPage();

	int ShapeDataCount();

	void PrintVertices(int ID)
	{
			ShapeVertex* Selected;
			Selected = this->VertexContainer.RetrieveDataP(ID);
			cout << "------------Vertex-Data--(" << ID << ")---------------" << endl;
			cout << "Position: {"   << Selected->Position[0]  << " , " << Selected->Position[1]  << "}"   << endl;
			cout << "TexCoords: {"  << Selected->TexCoords[0] << " , " << Selected->TexCoords[1] << "}"   << endl;
			cout << "Color: {"      << Selected->Color[0]     << " , " << Selected->Color[1]     << " , " << Selected->Color[2] << "," << Selected->Color[3] << "}" << endl;
			cout << "TexIndex: {"   << Selected->TexIndex     << "}" << endl;
			cout << "CentralPoint: {" << Selected->CentralPoint[0] << " , " << Selected->CentralPoint[1] << "}" << endl;
			cout << "GUIAction: {" << Selected->GUIAction << "}" << endl;
	}


	void PrintIndex(int ID)
	{
		uint32_t* Selected;
		Selected = IndexContainer.RetrieveDataP(ID);
		cout << "Index (" << ID << "): "<< *Selected << endl;
	}

	void PrintShapeSheet()
	{
			cout << "---------------------------------ShapeData-Sheet------------------------------------" << endl;
			cout << ShapeContainer.CurrentContainerAmount << endl;
			for (int i = 0; i < ShapeContainer.CurrentContainerAmount; i++)
			{
				PrintShape(i);
			}
	}
	void PrintVertexSheet(int TimesAmount)
	{
		cout << "---------------------------------Vertex-Sheet------------------------------------" << endl;
		for (int i = 0; i < (VertexContainer.CurrentContainerAmount * TimesAmount) ; i++)
		{
			PrintVertices(i);
		}
	}

	void PrintIndexSheet()
	{
		cout << "---------------------------------Index-Sheet------------------------------------" << endl;
		for (int i = 0; i < IndexContainer.CurrentContainerAmount; i++)
		{
			PrintIndex(i);
		}
		cout << "--------------------------------------------------------------------------------" << endl;
	}
	//ShapeData* GetShapeData(int ID);
	//

	//sets top left to middle
	glm::vec2 ConvertToMiddle(glm::vec2 Position, glm::vec2 Size)
	{
		return {Position[0] + (Size[0]/2), Position[1] - (Size[1] / 2)};
	}

	//sets top middle to left
	glm::vec2 ConvertToLeft(glm::vec2 Position, glm::vec2 Size)
	{
		return { Position[0] - (Size[0] / 2), Position[1] + (Size[1] / 2) };
	}

	//also this function should always be called before an find ShapeData requests
	//call this function after you add an ShapeData or grid to a layer
	//void UpdateLayers(int StartLayer, int Offset);
	
	void LoadShapeDataFromFile(ShapeData& ShapeData);
	void LoadVertexFromFile(ShapeVertex& Vertex);
	void LoadIndexFromFile(int& Index);

	void ErasePage();

	~Page()
	{
	  //cout << "PAGE DELETED" << endl;
	}

	//Vertex TempToVertex(FontVertex& FontVertex);

	void AddCircle(glm::vec2 Position, glm::vec2 Size, float RadiusPercentage);


	int ShapeAmount();


	//void ReplaceWithHighlight(int ID);
	
};


#endif 



