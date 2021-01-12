#ifndef  PAGEGROUPITEM
#define  PAGEGROUPITEM

#define P_NONE 0
#define P_END_TO_MIDDLE 1
#define P_BEGINNING_TO_MIDDLE 2


#include <iostream>
#include "MasterElement.h"
#include "ElementGroup.h"
#include "Text.h"
#include "Grid.h"
#include "Log.h"

using namespace std;

//struct PageGroupItemData
//{
//	//GroupID: Group 436
//	//CellID : Cell 2 of Upper Group
//	//ShapeStart: Group Starts at Shape 1076
//	//GroupStart Offset: Shape is 10 shapes from this group's start
//	//CellCount: Group owns 6 cells
//	//ShapeCount: Group owns 23 Shapes
//
//	Page* Page;
//	unsigned int ShapeStartID; //ShapeID of the first Shape
//	unsigned int ShapeCount; //Item Count
//
//	unsigned int CellCount;
//	unsigned int CellID;
//	int CellOffset = 0;
//
//	int GroupID; //Item ID
//	ShapeData* NextGroup;
//
//	glm::vec2 Position;
//	glm::vec2 Size;
//	glm::vec4 Color;
//
//	bool MouseAccess = true;
//	bool Centered;
//	bool Highlighted;
//	int ShapeType;
//
//	float Left = -3.0;
//	float Right = -3.0;
//	float Top = -3.0;
//	float Bottom = -3.0;
//
//	glm::vec2 XYShapesPerRow;
//	glm::vec2 ShapeDataSize;
//
//	//Page Item Details
//	int PageGroupID;
//	int PageGroupShapeCount;
//	int PageGroupShapeOffset;
//	int PageGroupShapeStartID;
//};

class PageGroupItem : public MasterElement
{
public:

	//PageGroupItemData LoadedShape.PageItem;
	//GroupData CurrentShapeGroup;
	TextData CurrentText;
	ShapeData CurrentShape;

	PageGroupItem();
	PageGroupItem(Page& Page);
	PageGroupItem(Page& Page, PageItemData& PageItemData);
	PageGroupItem(Page& Page, ShapeData& LoadedShape);
	PageGroupItem(Page& Page, int GroupID);

	void Add_Default() override; //Editor/None Set in Stone
	void Add_Duplicate() override; //Editor/None Set in Stone
	void Add_Insert() override; //Editor/None Set in Stone
	void Delete();

	virtual void Update() = 0;
	void ReCalibrateID();
	int FindNextGroup(int CurrentID, ShapeData* RetreivedShape);
	int FindPreviousGroup(int CurrentID, ShapeData* RetreivedShape);
	void ShapeToGroup(ShapeData& ShapeData);
	//void SwitchToPageItem(int ShapeID);

	//ShapeData Editing

	void Switch(int RequstedShapeID);
	void Switch(Page& Page, int RequstedShapeID);
	void SetPageItem(ShapeData& ShapeData);
	void SetPageItem(ShapeData& ShapeData, glm::vec2 PSConversions);
	void SetPosition(glm::vec2 Position);
	void OffsetPosition(glm::vec2 PositionOffset);
	void OffsetPosition(glm::vec2 PositionOffset, glm::vec2 bools);

	void UpdateMouseAccess(glm::vec2 Position, glm::vec2 Size, int PositionConversion);
	void SetMouseAccess();
	glm::vec2 ConvertEndToMiddle(glm::vec2 Position, glm::vec2 Size);
	glm::vec2 ConvertBeginningToMiddle(glm::vec2 Position, glm::vec2 Size);
	int FindShapeGroup(bool FromBottom, double xMouse, double yMouse);
	int GetShapeGroup(int ChildGroupID);

	void PrintGroupShapes()
	{
		if (Initialized == false)
		{
			Log::LogString("Cannot Print Shapes:: PageItem Not Initialized"); 
			return;
		}
		else
		{
			Log::LogString("NO SHAPE WAS INITIALIZED");
		}
		//ReCalibrateID();
		//cout << "Printing Starting from: " << LoadedShape.PageItem.ShapeStartID << endl;
		//cout << "For the count: " << LoadedShape.PageItem.ShapeCount << endl;
		for (int i = LoadedShape.PageItem.ShapeStart; i < LoadedShape.PageItem.ShapeStart + LoadedShape.PageItem.ShapeCount + 1; i++)
		{
			
			CurrentPage->PrintShape(i);
		}
	}

	void Init(Page& Page, int QuadID)
	{
		if (&Page != nullptr)
		{
			Initialized = true;
			CurrentPage = &Page;
			if (QuadID != -1)
			{
				LoadedShape = Page.GetShapeDataR(QuadID);
			}
			LoadedShape.PageItem.Position = { 0.0, 0.0 };
			Add_Default();
		}
	};



	glm::vec2 GetBiggestMouseAccess(glm::vec2 Position, glm::vec2 Size);
};


#endif