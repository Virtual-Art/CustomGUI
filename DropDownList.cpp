#include "DropDownList.h"

DropDownList::DropDownList(llBookData* llBook)
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
	CurrentllPageItem->Type = TYPE_PAGEITEM_DROPDOWNLIST;
	CreateDropDownList();
}

DropDownList::DropDownList(llBookData* llBook, llPageItemData* llPageItem, DropDownListData& DropDownListData)
	: PageGroupItem(llBook, llPageItem)
{
	CurrentDropDownListData = DropDownListData;
	CurrentllPageItem->Type = TYPE_PAGEITEM_DROPDOWNLIST;
	CreateDropDownList();
}

DropDownList::DropDownList(llPageItemData* llPageItem)
	: PageGroupItem(llPageItem)
{

}

void DropDownList::llDropDownListInit(llBookData* llBook, llPageItemData* llPageItem, DropDownListData& DropDownListData)
{
	llPageItemInit(llBook, llPageItem);
	CurrentDropDownListData = DropDownListData;
	CurrentllPageItem->Type = TYPE_PAGEITEM_DROPDOWNLIST;
	CreateDropDownList();
}


void DropDownList::CreateDropDownList()
{
	//Validate
	if (CurrentllPageItem == nullptr) { Log::LogString("ERROR:: CreateToggle FAILED:: PageItem"); return; };

	//Setup 
	llShapeGroupData CurrentShapeGroup;
	llShapeData CurrentShape;

	llShapeGroupData* BackGroundGroup;
	llShapeGroupData* CurrentDescriptionGroup;

	//Driver Text
	glm::vec2 Text_Driver_Position = CurrentllPageItem->Position;
	glm::vec4 Text_Driver_Color = { 0.0, 1.0, 1.0, 0.8 };

	//Driver Quad
	glm::vec2 Quad_Driver_BackGround_Position = CurrentllPageItem->Position;
	glm::vec4 Quad_Driver_BackGround_Color = { 0.0, 0.3, 0.3, 0.5 };

	//Create Driver BackGround
	CurrentShape.Position = Quad_Driver_BackGround_Position;
	CurrentShape.Position[Y_AXIS] += PIXEL;
	CurrentShape.Color = Quad_Driver_BackGround_Color;
	CurrentShape.Hide = CurrentDropDownListData.Hidden;
	Quad Quad_Description_Background(LoadedBook, &CurrentShape);

	BackGroundGroup = CurrentllPageItem->ShapeGroup;

	//Create Driver Text
	CurrentText.Phrase = CurrentDropDownListData.Description;
	CurrentText.Centered = true;
	CurrentText.FontSize = 12;
	CurrentShapeGroup.Position = Text_Driver_Position;
	CurrentShapeGroup.MouseAccess = false;
	CurrentShapeGroup.Hide = false;
	Text Text_Description(LoadedBook, &CurrentShapeGroup, CurrentText);

	CurrentDescriptionGroup = CurrentllPageItem->ShapeGroup;

	//Quad Size Correct Now
	Quad_Description_Background.SetSize(Text_Description.GetSize(10, 20));

	//Sub BackGround
	glm::vec2 Quad_SubList_Position = { Quad_Description_Background.GetAccessLeft(), Quad_Description_Background.GetAccessBottom() };

	//Input = INPUT_TOPLEFT;

	float MaxTextWidth = 0;

	//Create Text List
	for (int i = 0; i < CurrentDropDownListData.MaxListCount; i++)
	{
		//Only Add quads to quad group
		CurrentllPageItem->ShapeGroup = BackGroundGroup;

		CurrentShape.Position = Quad_SubList_Position;
		CurrentShape.Position[Y_AXIS] -= PIXEL * 2;
		CurrentShape.Size = Quad_Description_Background.GetSize();
		CurrentShape.Color = Quad_Driver_BackGround_Color;
		CurrentShape.InputType = INPUT_TOPLEFT;
		if (i > CurrentDropDownListData.CurrentListCount)
		{
			CurrentShape.Hide = true;
			CurrentShape.MouseAccess = false;
		}
		else
		{
			CurrentShape.Hide = CurrentDropDownListData.Hidden;
			if (CurrentDropDownListData.Hidden == true)
			{
				CurrentShape.MouseAccess = false;
			}
			else
			{
				CurrentShape.MouseAccess = true;
			}
		}
		Quad Quad_Sub(LoadedBook, &CurrentShape);

		//Sub Text
		glm::vec2 Text_SubList_Position = { Quad_Sub.GetAccessLeft(4), Quad_Sub.GetPosition()[Y_AXIS] };

		CurrentText.Phrase = CurrentDropDownListData.StringList[i];
		CurrentText.Centered = false;
		CurrentText.FontSize = 12;
		CurrentShapeGroup.Position = Text_SubList_Position;
		CurrentShapeGroup.Position[Y_AXIS] -= PIXEL * 2;
		if (i > CurrentDropDownListData.CurrentListCount)
		{
			CurrentShapeGroup.Hide = true;
		}
		else
		{
			CurrentShapeGroup.Hide = CurrentDropDownListData.Hidden;
		}
		CurrentShapeGroup.MouseAccess = false;
		Text Text_Description(LoadedBook, &CurrentShapeGroup, CurrentText);

		Quad_SubList_Position = { Quad_Description_Background.GetAccessLeft(), Quad_Sub.GetAccessBottom() };

		//Check if text is the max width
		float TestWidth = Text_Description.GetSize()[X_AXIS] + PIXEL * 10;
		if (TestWidth > MaxTextWidth)
		{
			MaxTextWidth = TestWidth;
		}
	}

	llShapeData* CurrentBackGroundShape = BackGroundGroup->Shape;

	Quad UpdateBackGround(CurrentBackGroundShape);

	while (CurrentBackGroundShape->Previous != nullptr)
	{
		CurrentBackGroundShape = CurrentBackGroundShape->Previous;
	}

	//Unionize all BackGrounds to longest text
	for (int i = 0; i < CurrentDropDownListData.MaxListCount; i++)
	{
		CurrentBackGroundShape = CurrentBackGroundShape->Next;
		UpdateBackGround.llSwitch(CurrentBackGroundShape);
		CurrentBackGroundShape->Size[X_AXIS] = MaxTextWidth;
		CurrentBackGroundShape->InputType = INPUT_LEFT;
		CurrentBackGroundShape->Position[X_AXIS] = Quad_Description_Background.GetAccessLeft();
		UpdateBackGround.SetllShape(CurrentBackGroundShape);
	}
}

void DropDownList::llReplaceDropDownList()
{
	//Validate
	if (CurrentllPageItem == nullptr) { Log::LogString("ERROR:: CreateToggle FAILED:: PageItem"); return; };

	//Setup 
	llShapeGroupData* CurrentShapeGroup = CurrentllPageItem->ShapeGroup;

	while (CurrentShapeGroup->Previous != nullptr)
	{
		CurrentShapeGroup = CurrentShapeGroup->Previous;
	}

	//Quad Group = first Group
	llShapeGroupData* BackGroundGroup = CurrentShapeGroup;
	//1st Text = Second Group
	llShapeGroupData* CurrentDescriptionGroup = CurrentShapeGroup->Next;
	//First Quad of Quad Group
	llShapeData* CurrentBackGroundShape = BackGroundGroup->Shape;

	while (CurrentBackGroundShape->Previous)
	{
		CurrentBackGroundShape = CurrentBackGroundShape->Previous;
	}

	Quad Quad_Reference(CurrentBackGroundShape);
	Text Text_Reference(CurrentDescriptionGroup);

	//Driver Text
	glm::vec2 Text_Driver_Position = CurrentllPageItem->Position;
	glm::vec4 Text_Driver_Color = { 0.0, 1.0, 1.0, 0.8 };

	//Driver Quad
	glm::vec2 Quad_Driver_BackGround_Position = CurrentllPageItem->Position;
	glm::vec4 Quad_Driver_BackGround_Color = { 0.0, 0.3, 0.3, 0.5 };

	//Create Driver BackGround
	Quad_Reference.llSwitch(CurrentBackGroundShape);
	CurrentBackGroundShape->Position = Quad_Driver_BackGround_Position;
	CurrentBackGroundShape->Position[Y_AXIS] += PIXEL;
	CurrentBackGroundShape->Color = Quad_Driver_BackGround_Color;
	if (HighlightDriver != true)
	{
		CurrentBackGroundShape->Hide = CurrentDropDownListData.Hidden;
	}
	else
	{
		CurrentBackGroundShape->Hide = false;
	}
	Quad_Reference.SetllShape(CurrentBackGroundShape);

	//Create Driver Text
	Text_Reference.llSwitch(CurrentDescriptionGroup);
	CurrentText.Phrase = CurrentDropDownListData.Description;
	CurrentText.Centered = true;
	CurrentText.FontSize = 12;
	CurrentDescriptionGroup->Position = Text_Driver_Position;
	CurrentDescriptionGroup->MouseAccess = false;
	Text_Reference.SetllTextGroup(CurrentDescriptionGroup, CurrentText);

	//Quad Size Correct Now
	Quad_Reference.SetSize(Text_Reference.GetSize(10, 20));

	//Sub BackGround
	glm::vec2 Quad_SubList_Position = { Quad_Reference.GetAccessLeft(), Quad_Reference.GetAccessBottom() };

	glm::vec2 Quad_Driver_Size = Quad_Reference.GetSize();
	float Quad_Driver_Left = Quad_Reference.GetAccessLeft();
	//Input = INPUT_TOPLEFT;

	float MaxTextWidth = 0;

	//Create Text List
	for (int i = 0; i < CurrentDropDownListData.MaxListCount; i++)
	{
		//Only Add quads to quad group
		CurrentBackGroundShape = CurrentBackGroundShape->Next;
		Quad_Reference.llSwitch(CurrentBackGroundShape);
		CurrentBackGroundShape->Position = Quad_SubList_Position;
		CurrentBackGroundShape->Position[Y_AXIS] -= PIXEL * 2;
		CurrentBackGroundShape->Size = Quad_Driver_Size;
		CurrentBackGroundShape->Color = Quad_Driver_BackGround_Color;
		CurrentBackGroundShape->InputType = INPUT_TOPLEFT;
		if (i > CurrentDropDownListData.CurrentListCount)
		{CurrentBackGroundShape->Hide = true;
		 CurrentBackGroundShape->MouseAccess = false;
		}
		else
		{CurrentBackGroundShape->Hide = CurrentDropDownListData.Hidden;
			if (CurrentDropDownListData.Hidden == true)
			{
				CurrentBackGroundShape->MouseAccess = false;
			}
			else
			{
				CurrentBackGroundShape->MouseAccess = true;
			}
		}
		Quad_Reference.SetllShape(CurrentBackGroundShape);

		//Sub Text
		glm::vec2 Text_SubList_Position = { Quad_Reference.GetAccessLeft(4), Quad_Reference.GetPosition()[Y_AXIS] };

		CurrentDescriptionGroup = CurrentDescriptionGroup->Next;
		Text_Reference.llSwitch(CurrentDescriptionGroup);
		CurrentText.Phrase = CurrentDropDownListData.StringList[i];
		CurrentText.Centered = false;
		CurrentText.FontSize = 12;
		CurrentDescriptionGroup->Position = Text_SubList_Position;
		CurrentDescriptionGroup->Position[Y_AXIS] -= PIXEL * 2;
		CurrentDescriptionGroup->MouseAccess = false;
		CurrentDescriptionGroup->Hide = CurrentDropDownListData.Hidden;
		Text_Reference.SetllTextGroup(CurrentDescriptionGroup, CurrentText);

		Quad_SubList_Position = { Quad_Driver_Left, Quad_Reference.GetAccessBottom() };

		//Check if text is the max width
		float TestWidth = Text_Reference.GetSize()[X_AXIS] + PIXEL * 10;
		if (TestWidth > MaxTextWidth)
		{
			MaxTextWidth = TestWidth;
		}
	}

	Quad UpdateBackGround(CurrentBackGroundShape);

	while (CurrentBackGroundShape->Previous != nullptr)
	{
		CurrentBackGroundShape = CurrentBackGroundShape->Previous;
	}

	//Unionize all BackGrounds to longest text
	for (int i = 0; i < CurrentDropDownListData.MaxListCount; i++)
	{
		CurrentBackGroundShape = CurrentBackGroundShape->Next;
		UpdateBackGround.llSwitch(CurrentBackGroundShape);
		CurrentBackGroundShape->Size[X_AXIS] = MaxTextWidth;
		CurrentBackGroundShape->InputType = INPUT_LEFT;
		CurrentBackGroundShape->Position[X_AXIS] = Quad_Driver_Left;
		UpdateBackGround.SetllShape(CurrentBackGroundShape);
	}
	HighlightDriver = false;
}


void DropDownList::llUpdate()
{
	llReplaceDropDownList();
}

void DropDownList::HoverDriver()
{
	HighlightDriver = true;
	llReplaceDropDownList();
}