#ifndef  PAGEGROUP
#define  PAGEGROUP

#include <iostream>
#include "Log.h"
#include "PageGroupItem.h"
#include "Slider.h"
#include "MasterElement.h"
//#include "ProgressBar.h"

//struct CPageGroupData
//{
//	Page* Page;
//	glm::vec2 Position;
//	glm::vec2 Size;
//	glm::vec2 Color;
//
//	bool MouseAccess;
//	bool Centered;
//	bool Highlighted;
//	int ShapeType;
//
//	glm::vec2 XYShapesPerRow;
//	glm::vec2 ShapeDataSize;
//
//	float Left;
//	float Right;
//	float Top;
//	float Bottom;
//
//	//PageGroup Shape
//	int GroupID;
//	int ShapeCount;
//	int ShapeOffset;
//	int ShapeStartID;
//
//	//PageGroup Group
//	int PageGroupCount;
//
//};

class PageGroup : public MasterElement
{
public:

	//PageGroupData LoadedShape.PageGroup;
	//PageGroupItemData CurrentPageItem;
	//GroupData CurrentShapeGroup;
	TextData CurrentText;
	SliderData CurrentSliderData; //?

	PageGroup();
	PageGroup(Page& Page);
	PageGroup(Page& Page, PageGroupData& PageGroup);
	PageGroup(Page& Page, ShapeData& ShapeData);
	PageGroup(Page& Page, int ID);

	void Add_Default() {}; //Editor/None Set in Stone
	void Add_Duplicate() {}; //Editor/None Set in Stone
	void Add_Insert() {}; //Editor/None Set in Stone
	void Delete() {};

	void ReCalibrateID();

	//PageGroupItemData CurrentPageItem;
	//GroupData CurrentShapeGroup;
	//TextData CurrentText;
	//ShapeData CurrentShape;

	//SetPosition();
	//SetSize();
	void ShapeToGroup(ShapeData& ShapeData);
	int FindNextGroup(int CurrentID, ShapeData* RetreivedShape);
	int FindPreviousGroup(int CurrentID, ShapeData* RetreivedShape);
	int FindChildGroup(int ChildGroupID);
	int FindPageItem(bool FromBottom, double xMouse, double yMouse);

	float SetMouseAccess(glm::vec2 Position, glm::vec2 Size);
};

#endif