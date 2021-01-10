#ifndef  PAGEGROUP
#define  PAGEGROUP

#include <iostream>
#include "Log.h"
#include "PageGroupItem.h"
#include "Slider.h"
//#include "ProgressBar.h"

struct PageGroupData
{
	Page* Page;
	glm::vec2 Position;
	glm::vec2 Size;
	glm::vec2 Color;

	bool MouseAccess;
	bool Centered;
	bool Highlighted;
	int ShapeType;

	glm::vec2 XYShapesPerRow;
	glm::vec2 ShapeDataSize;

	float Left;
	float Right;
	float Top;
	float Bottom;

	//PageGroup Shape
	int GroupID;
	int ShapeCount;
	int ShapeOffset;
	int ShapeStartID;

	//PageGroup Group
	int PageGroupCount;

};

class PageGroup
{
public:

	PageGroup();
	PageGroup(Page& Page);
	PageGroup(Page& Page, PageGroupData& PageGroup);
	PageGroup(Page& Page, int ID);

	void ReCalibrateID();

	//PageGroupItemData CurrentPageItem;
	//GroupData CurrentShapeGroup;
	//TextData CurrentText;
	//ShapeData CurrentShape;

	PageGroupData CurrentPageGroup;
	PageGroupItemData CurrentPageItem;
	GroupData CurrentShapeGroup;
	TextData CurrentText;
	ShapeData CurrentShape;
	SliderData CurrentSliderData; //?

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