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

struct PageGroupItemData
{
	//GroupID: Group 436
	//CellID : Cell 2 of Upper Group
	//ShapeStart: Group Starts at Shape 1076
	//GroupStart Offset: Shape is 10 shapes from this group's start
	//CellCount: Group owns 6 cells
	//ShapeCount: Group owns 23 Shapes

	Page* Page;
	unsigned int ShapeStartID; //ShapeID of the first Shape
	unsigned int ShapeCount; //Item Count

	unsigned int CellCount;
	unsigned int CellID;
	int CellOffset = 0;

	int GroupID; //Item ID
	ShapeData* NextGroup;

	glm::vec2 Position;
	glm::vec2 Size;
	glm::vec4 Color;

	bool MouseAccess = true;
	bool Centered;
	bool Highlighted;
	int ShapeType;

	float Left = -3.0;
	float Right = -3.0;
	float Top = -3.0;
	float Bottom = -3.0;

	glm::vec2 XYShapesPerRow;
	glm::vec2 ShapeDataSize;

	//Page Item Details
	int PageGroupID;
	int PageGroupShapeCount;
	int PageGroupShapeOffset;
	int PageGroupShapeStartID;
};

class PageGroupItem : public MasterElement
{
public:

	PageGroupItem();
	PageGroupItem(Page& Page);
	PageGroupItem(Page& Page, PageGroupItemData& PageItem);
	PageGroupItem(Page& Page, int GroupID);

	Page* CurrentPage;
	PageGroupItemData CurrentPageItem;
	GroupData CurrentShapeGroup; 
	TextData CurrentText;
	ShapeData CurrentShape;

	virtual void Update() = 0;
	void ReCalibrateID();
	int FindNextGroup(int CurrentID, ShapeData* RetreivedShape);
	int FindPreviousGroup(int CurrentID, ShapeData* RetreivedShape);
	void ShapeToGroup(ShapeData& ShapeData);
	//void SwitchToPageItem(int ShapeID);

	//ShapeData Editing
	virtual void Add_Default(); //Editor/None Set in Stone
	virtual void Add_Duplicate(); //Editor/None Set in Stone
	virtual void Add_Insert(); //Editor/None Set in Stone
	void DeletePageGroupItem();
	void SwitchToPageGroupItem(int RequstedShapeID);
	void SwitchToPageGroupItem(Page& Page, int RequstedShapeID);
	void SetPageGroupItem(ShapeData& ShapeData);
	void SetPageGroupItem(ShapeData& ShapeData, glm::vec2 PSConversions);
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
		//ReCalibrateID();
		//cout << "Printing Starting from: " << CurrentPageItem.ShapeStartID << endl;
		//cout << "For the count: " << CurrentPageItem.ShapeCount << endl;
		for (int i = CurrentPageItem.ShapeStartID; i < CurrentPageItem.ShapeStartID + CurrentPageItem.ShapeCount + 1; i++)
		{
			CurrentPageItem.Page->PrintShape(i);
		}
	}

	void Init(Page& Page, int QuadID)
	{
		this->CurrentPageItem.Page = &Page;
		if (QuadID != -1)
		{
			CurrentShape = Page.GetShapeDataR(QuadID);
		}
		cout << "Quad Selected ID: " << QuadID << endl;
		CurrentPageItem.Position = { 0.0, 0.0 };
		Add_Default();
	};



	glm::vec2 GetBiggestMouseAccess(glm::vec2 Position, glm::vec2 Size);
};


#endif
