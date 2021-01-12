#ifndef CONTROLS
#define CONTROLS

#include <iostream>
// ShapeGroup //
#include "ElementGroup.h"
#include "Text.h"
#include "Grid.h"
#include "CustomShape.h"
////////////////

using namespace std;

struct ControlsData
{
	Page* Page;
	int PageID;
	int ShapeCount;
	int GroupCount;

	glm::vec2 Position;
	glm::vec2 Size;
	glm::vec4 Color;

	bool MouseAccess;
	bool Centered;
	bool Highlighted;
	int ShapeType;
};

class Controls
{
public: 

	Controls(Page& Page);

	ControlsData CurrentControl;
	//GroupData CurrentGroupData;
};

#endif
