#ifndef TOGGLE
#define TOGGLE

#include <iostream>
#include "Controls.h"
// ShapeGroup //
#include "ElementGroup.h"
#include "Text.h"
#include "Grid.h"
#include "CustomShape.h"
////////////////

using namespace std;

struct ToggleData
{
	Page* Page;
	int PageID;
	int ShapeCount;
	int GroupCount;
	string Name;
	bool OnOff;

};

class Toggle : public Controls
{
public:

	Toggle(Page& Page);
	Toggle(Page& Page, ToggleData& ToggleData);

	ToggleData CurrentToggleData;

	GroupData Group_ToggleText;
	TextData  Text_Name;
	ShapeData Quad_Outline;
	ShapeData Quad_BackGround;
	ShapeData Quad_OnOff;

	glm::vec4 OnColor;
	glm::vec4 OffColor;

	glm::vec2 OnPosition;
	glm::vec2 OffPosition;

	void CreateToggle();

	//void SetToggleName();
	//void SetOutline();
	//void BackGround();
	//void SetOnOff();
};

#endif

