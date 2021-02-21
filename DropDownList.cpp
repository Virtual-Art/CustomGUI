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

	glm::vec2 ListDriver_Text_Position = CurrentllPageItem->Position;

	glm::vec2 ListDriver_BackGround_Position = CurrentllPageItem->Position;
	glm::vec4 ListDriver_BackGround_Color = { 0.0, 0.3, 0.3, 0.5};
	glm::vec4 ListDriver_Text_Color = { 0.0, 1.0, 1.0, 0.8 };

	glm::vec2 SubList_Position;
	glm::vec2 SubList_Size;

	CurrentShape.Position = ListDriver_BackGround_Position;
	CurrentShape.Position[Y_AXIS] += PIXEL;
	CurrentShape.Color = ListDriver_BackGround_Color;
	Quad Quad_Description_Background(LoadedBook, &CurrentShape);

	//ListDriver Description
	CurrentText.Phrase = CurrentDropDownListData.Description;
	CurrentText.Centered = true;
	CurrentText.FontSize = 12;
	CurrentShapeGroup.Position = ListDriver_Text_Position;
	Text Text_Description(LoadedBook, &CurrentShapeGroup, CurrentText);

	//Conform Quad around Text
	Quad_Description_Background.SetSize(Text_Description.GetSize(10,10));

	//Position as bottom
	glm::vec2 Quad_Previous_Sub_Position = { ListDriver_BackGround_Position[X_AXIS], Quad_Description_Background.GetAccessBottom()};
	glm::vec2 Quad_Previous_Sub_Size;

	//Position as left
	glm::vec2 Text_Previous_Sub_Position = ListDriver_Text_Position;
	glm::vec2 Text_Previous_Sub_Size = Text_Description.GetSize();

	for (int i = 0; i < CurrentDropDownListData.ListCount; i++)
	{
		//Sub BackGround
		CurrentShape.Position = Quad_Previous_Sub_Position; //Next Quad Position = Previous Quad's Bottom - 2 Pixels
		CurrentShape.Position[Y_AXIS] -= PIXEL * 2;
		CurrentShape.Size = Text_Description.GetSize(10, 10); 
		CurrentShape.Color = ListDriver_BackGround_Color;
		CurrentShape.InputType = INPUT_TOP; //Position provided is the top of the new quad
		Quad Quad_Sub_Background(LoadedBook, &CurrentShape);

		//The quad just created is now the previous quad and it's position is it's bottom
		Quad_Previous_Sub_Position[Y_AXIS] = Quad_Sub_Background.GetAccessBottom();

		float Sub_X_AsLeft = Quad_Sub_Background.GetAccessLeft();

		//ListDriver Description
		CurrentText.Phrase = CurrentDropDownListData.StringList[i];
		CurrentText.FontSize = 12;
		CurrentText.Centered = false;
		CurrentShapeGroup.Position = { Quad_Sub_Background.GetAccessLeft(5), Quad_Sub_Background.GetPosition()[Y_AXIS]};
		CurrentShapeGroup.Color = ListDriver_Text_Color;
		Text Text_Sub(LoadedBook, &CurrentShapeGroup, CurrentText);

		//WORKING//
		//Conform BackGround to it's Text
		//Quad_Sub_Background.SetSize(Text_Sub.GetSize(10, 10), {true, false}); //Size correct
		//Quad_Sub_Background.GetData()->InputType = INPUT_LEFT;
		//Quad_Sub_Background.SetPosition({ Sub_X_AsLeft, 0.0}, {true, false});
	}

	//Set Congruent size for all subs

}

void DropDownList::llReplaceDropDownList()
{

}

void DropDownList::llUpdate()
{

}

