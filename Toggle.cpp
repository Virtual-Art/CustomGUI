#include "Toggle.h"

Toggle::Toggle(Page& Page)
	:Controls(Page)
{
	//Control Details
	CurrentControl.Position = {0.0, 0.0};
	CurrentControl.Size = {0.4, 0.1};

    //Text Details
	Text_Name.Phrase = "Toggle";
	Text_Name.Centered = false;
	Text_Name.FontSize = 0.3;
	Group_ToggleText.Position[0] = CurrentControl.Position[0] - CurrentControl.Size[0] / 4;
	Group_ToggleText.Position[1] = CurrentControl.Position[1];
	Group_ToggleText.Color = {1.0, 0.0, 1.0, 1.0};
	Group_ToggleText.MouseAccess = false;

	//Outline Details
	Quad_Outline.Position[0] = (CurrentControl.Position[0] + CurrentControl.Size[0] / 8);
	Quad_Outline.Position[1] = CurrentControl.Position[1] + 0.1;
	Quad_Outline.Size = { CurrentControl.Size[0] / 3 + 0.00166, CurrentControl.Size[1]/4 + 0.00166 };
	Quad_Outline.Color = {0.3, 0.3, 0.8, 1.0};
	Quad_Outline.MouseAccess = false;

	//Background Details
	Quad_BackGround.Position[0] = CurrentControl.Position[0] + CurrentControl.Size[0] / 8;
	Quad_BackGround.Position[1] = CurrentControl.Position[1] + 0.2;
	Quad_BackGround.Size  = { CurrentControl.Size[0] / 3 , CurrentControl.Size[1] / 4};
	Quad_BackGround.Color = { 1.0, 1.0, 0.8, 1.0 };
	Quad_BackGround.MouseAccess = false;

	//OnOff Details
	Quad_OnOff.Position[0] = CurrentControl.Position[0] + CurrentControl.Size[0]/2;
	Quad_OnOff.Position[1] = CurrentControl.Position[1] + 0.3;
	Quad_OnOff.Size = { CurrentControl.Size[0] / 6, Quad_BackGround.Size[1] * 0.98 };
	Quad_OnOff.Color = {0.0, 1.0, 0.0, 1.0};
	Quad_OnOff.MouseAccess = true;

	OnColor = {};
	OffColor = {};

	OnPosition = {};
	OffPosition = {};

	//GroupData
	this->CurrentGroupData.Color = { 1.0, 1.0, 1.0, 1.0 };
	this->CurrentGroupData.Size = { 0.2, 0.1 }; // all of the xadvances of all the text
	this->CurrentGroupData.Position = { 0.0, 0.0 };
	this->CurrentGroupData.MouseAccess = true;
	this->CurrentGroupData.Highlighted = false;
	this->CurrentGroupData.Centered = false;

	this->CurrentGroupData.XYShapesPerRow = { 2.0, 2.0 }; // Can use without
	this->CurrentGroupData.ShapeDataSize = { 0.8, 0.8 };  // Can use without

	CreateToggle();
}

Toggle::Toggle(Page& Page, ToggleData& ToggleData)
	:Controls(Page)
{

}


void Toggle::CreateToggle()
{
	Text Name(*CurrentControl.Page, Group_ToggleText, Text_Name);
	Quad Outline(*CurrentControl.Page, Quad_Outline);
	Quad BackGround(*CurrentControl.Page, Quad_BackGround);
	Quad OnOff(*CurrentControl.Page, Quad_OnOff);
}