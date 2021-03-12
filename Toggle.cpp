#include "Toggle.h"

Toggle::Toggle(llBookData* llBook)
	:PageGroupItem(llBook)
{
	CurrentllPageItem->Color = { 1.0, 1.0, 1.0, 1.0 };
	CurrentllPageItem->Size = { 0.40, 0.05 }; // all of the xadvances of all the text
	CurrentllPageItem->Position = { 0.0, 0.0 };
	CurrentllPageItem->MouseAccess = true;
	CurrentllPageItem->Highlighted = false;
	CurrentllPageItem->Centered = false;
	CurrentllPageItem->XYShapePerRow = { 2.0, 2.0 }; // Can use without
	CurrentllPageItem->ShapeSize = { 0.8, 0.8 };  // Can use without
	CurrentllPageItem->Type = TYPE_PAGEITEM_TOGGLE;
	CreateToggle();
}

Toggle::Toggle(llBookData* llBook, llPageItemData* llPageItem, ToggleData& ToggleData)
	: PageGroupItem(llBook, llPageItem)
{
	CurrentToggleData = ToggleData;
	CreateToggle();
}

Toggle::Toggle(llPageItemData* llPageItem)
	: PageGroupItem(llPageItem)
{

}


void Toggle::llToggleInit(llBookData* llBook, llPageItemData* llPageItem, ToggleData ToggleData)
{
	llPageItemInit(llBook, llPageItem);
	CurrentToggleData = ToggleData;
	CurrentllPageItem->Type = TYPE_PAGEITEM_TOGGLE;
	CreateToggle();
}

void Toggle::CreateToggle()
{
	//Validate
	if (CurrentllPageItem == nullptr) { Log::LogString("ERROR:: CreateToggle FAILED:: PageItem"); return; };

	//Setup 
	llShapeGroupData TextShapeGroup;
	llShapeData CurrentShape;

	glm::vec2 Description_Position = CurrentllPageItem->Position;
	glm::vec2 Toggle_Position;
	glm::vec4 Toggle_Color;
	glm::vec2 Toggle_Size = { 0.035, 0.05 };
	int ToggleInputType;

	//Description
	TextShapeGroup.Position = Description_Position;
	CurrentText.Phrase = CurrentToggleData.Description;
	CurrentText.FontSize = 12;
	Text Description(LoadedBook, &TextShapeGroup, CurrentText);

	ShapeGroup New_Empty(LoadedBook);

	glm::vec2 ToggleBackGround_Position = { Description.GetAccessRight(20), Description_Position[Y_AXIS] };
	glm::vec2 ToggleBackGround_Size = {0.06, 0.06};
	glm::vec4 ToggleBackGround_Color = { 0.0, 0.3, 0.3, 0.8 }; //Dark Cyan

	//Toggle Background
	CurrentShape.Position = ToggleBackGround_Position;
	CurrentShape.Size = ToggleBackGround_Size;
	CurrentShape.InputType = INPUT_LEFT;
	CurrentShape.Color = ToggleBackGround_Color;
	Quad ToggleBackGround(LoadedBook, &CurrentShape);

	if (CurrentToggleData.OnOff != nullptr)
	{
		if (*CurrentToggleData.OnOff == true)
		{
			//On
			Toggle_Position = { ToggleBackGround.GetAccessRight(-2), ToggleBackGround_Position[Y_AXIS] };
			Toggle_Color = { 0.0, 1.0, 1.0, 0.8 }; //Cyan
			ToggleInputType = INPUT_RIGHT;
		}
		else
		{
			//Off
			Toggle_Position = { ToggleBackGround.GetAccessLeft(2), ToggleBackGround_Position[Y_AXIS] };
			Toggle_Color = { 0.0, 0.5, 0.5, 0.3 }; //Tame Azure
			ToggleInputType = INPUT_LEFT;
		}
	}
	else
	{
		Toggle_Position = { ToggleBackGround.GetAccessLeft(2), ToggleBackGround_Position[Y_AXIS] };
		Toggle_Color = { 0.0, 0.0, 0.0, 0.0 }; //Nothing
		ToggleInputType = INPUT_LEFT;
	}

	//Toggle
	CurrentShape.Position = Toggle_Position;
	CurrentShape.Size = Toggle_Size;
	CurrentShape.Color = Toggle_Color; //Azure
	CurrentShape.InputType = ToggleInputType;
	CurrentShape.MouseAccess = false;
	Quad Toggle(LoadedBook, &CurrentShape);
}

void Toggle::llUpdate()
{
	llReplaceToggle();
}

void Toggle::llReplaceToggle()
{
	//Validate
	if (CurrentllPageItem == nullptr) { Log::LogString("ERROR:: CreateToggle FAILED:: PageItem nullptr"); return; };
	if (CurrentllPageItem->ShapeGroup == nullptr) { Log::LogString("ERROR:: CreateToggle FAILED:: ShapeGroup nullptr"); return; };

	llShapeGroupData* CurrentShapeGroup = CurrentllPageItem->ShapeGroup;
	llShapeData* CurrentShape;

	while (CurrentShapeGroup->Previous != nullptr)
	{
		CurrentShapeGroup = CurrentShapeGroup->Previous;
	}

	//llShapeGroupData TextShapeGroup;

	Text Text_Reference(CurrentShapeGroup);

	glm::vec2 Description_Position = CurrentllPageItem->Position;
	glm::vec2 Toggle_Position;
	glm::vec4 Toggle_Color;
	glm::vec2 Toggle_Size = { 0.035, 0.04 };
	int ToggleInputType;


	//Description
	CurrentText.Phrase = CurrentToggleData.Description;
	Text_Reference.llSwitch(CurrentShapeGroup);
	CurrentShapeGroup->Position = Description_Position;
	Text_Reference.SetllTextGroup(CurrentShapeGroup, CurrentText);

	glm::vec2 ToggleBackGround_Position = { Text_Reference.GetAccessRight(20), Description_Position[Y_AXIS] };
	glm::vec2 ToggleBackGround_Size = { 0.06, 0.06 };
	glm::vec4 ToggleBackGround_Color = { 0.0, 0.3, 0.3, 0.8 }; //Dark Cyan

	CurrentShapeGroup = CurrentShapeGroup->Next;
	CurrentShape = CurrentShapeGroup->Shape;

	Quad Quad_Reference(CurrentShape);

	//Toggle Background
	Quad_Reference.llSwitch(CurrentShape);
	CurrentShape->Position = ToggleBackGround_Position;
	CurrentShape->Size = ToggleBackGround_Size;
	CurrentShape->InputType = INPUT_LEFT;
	CurrentShape->Color = ToggleBackGround_Color;
	Quad_Reference.SetllShape(CurrentShape);

	if (CurrentToggleData.OnOff != nullptr)
	{
		if (*CurrentToggleData.OnOff == true)
		{
			//On
			Toggle_Position = { Quad_Reference.GetAccessRight(-2), ToggleBackGround_Position[Y_AXIS] };
			Toggle_Color = { 0.0, 1.0, 1.0, 0.8 }; //Cyan
			ToggleInputType = INPUT_RIGHT;
		}
		else
		{
			//Off
			Toggle_Position = { Quad_Reference.GetAccessLeft(2), ToggleBackGround_Position[Y_AXIS] };
			Toggle_Color = { 0.0, 0.5, 0.5, 0.3 }; //Tame Azure
			ToggleInputType = INPUT_LEFT;
		}
	}
	else
	{
		Toggle_Position = { Quad_Reference.GetAccessLeft(2), ToggleBackGround_Position[Y_AXIS] };
		Toggle_Color = { 0.0, 0.0, 0.0, 0.0 }; //Azure
		ToggleInputType = INPUT_LEFT;
	}


	//Toggle
	CurrentShape = CurrentShape->Next;
	Quad_Reference.llSwitch(CurrentShape);
	CurrentShape->Position = Toggle_Position;
	CurrentShape->Size = Toggle_Size;
	CurrentShape->Color = Toggle_Color; //Azure
	CurrentShape->InputType = ToggleInputType;
	Quad_Reference.SetllShape(CurrentShape);
}

void Toggle::ClickToggle()
{
	ToggleToggle(*CurrentToggleData.OnOff);
	llUpdate();
}



//Reference Functions
void Toggle::Add_Default()  
{

}

void Toggle::Add_Duplicate()
{

}

void Toggle::Add_Insert()
{

}