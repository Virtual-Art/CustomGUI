#include "Slider.h"

Slider::Slider(Page& Page)
 : PageGroupItem(Page)
{
	//Group Setup
	this->CurrentPageItem.ShapeStartID = Page.ShapeAmount();// null termination character and two quads cancel out //
	//this->CurrentPageItem.ShapeCount = CurrentSliderData.Description.size() + CurrentSliderData.Ratio.size() + 2; 
	this->CurrentPageItem.CellCount = 3;
	cout << "Slider StartID: " << CurrentPageItem.ShapeStartID << endl;
	cout << "Slider ID: " << CurrentPageItem.GroupID << endl;
	cout << "Slider Count: " << CurrentPageItem.ShapeCount << endl;

	//Attribute Setup
	this->CurrentPageItem.Color = { 1.0, 1.0, 1.0, 1.0 };
	this->CurrentPageItem.Size = { 0.0, 0.0 }; // all of the xadvances of all the text
	this->CurrentPageItem.Position = { 0.0, -0.6 };
	this->CurrentPageItem.MouseAccess = true;
	this->CurrentPageItem.Highlighted = false;
	this->CurrentPageItem.Centered = false;
	this->CurrentPageItem.XYShapesPerRow = { 2.0, 2.0 }; // Can use without
	this->CurrentPageItem.ShapeDataSize = { 0.8, 0.8 };  // Can use without

	AddSlider();
}


Slider::Slider(Page& Page, PageGroupItemData& PageGroupItemData, SliderData& SliderData)
	: PageGroupItem(Page, PageGroupItemData)
{
	CurrentSliderData = SliderData;
	this->CurrentPageItem.ShapeStartID = Page.ShapeAmount();
	//this->CurrentPageItem.ShapeCount = SliderData.Description.size() + SliderData.Ratio.size();
	this->CurrentPageItem.CellCount = 3; //Really 4 technically
	AddSlider();
}

//Remeber the ID of the shape not the group
Slider::Slider(Page& Page, int PageItemStartID)
	:PageGroupItem(Page, PageItemStartID)
{
	if (&Page != nullptr)
	{
		cout << "Page is good in Slider" << endl;
		CurrentPage = &Page;
		//Set 1st shape of group
		if (PageItemStartID > -1)
		{
			CurrentShape = Page.GetShapeDataR(PageItemStartID);

			//SetGroupData
			//if (CurrentShape.ShapeDataType == TYPE_SLIDER)
			//{
			ShapeToGroup(CurrentShape);
			Text Description(*CurrentPage, GetShapeGroup(DESCRIPTION));
			CurrentSliderData.Description = Description.CurrentTextData.Phrase;
			Text Ratio(*CurrentPage, GetShapeGroup(RATIO));
			CurrentSliderData.Ratio = Ratio.CurrentTextData.Phrase;
		}
		else
		{
			cout << "WARNING SLIDER NOT INITIALIZED" << endl;
		}
	}
	else
	{
		cout << "Slider page was nullptr" << endl;
	}
}

void Slider::SwitchToSlider(int SliderStartID)
{
	//Set 1st shape of group
	CurrentShape = CurrentPage->GetShapeDataR(SliderStartID);

	//SetGroupData
	//if (CurrentShape.ShapeDataType == TYPE_SLIDER)
	//{
		ShapeToGroup(CurrentShape);
		Text Description(*CurrentPageItem.Page, GetShapeGroup(DESCRIPTION));
		CurrentSliderData.Description = Description.CurrentTextData.Phrase;
		Text Ratio(*CurrentPageItem.Page, GetShapeGroup(RATIO));
		CurrentSliderData.Ratio = Ratio.CurrentTextData.Phrase;
	//}
	//else
	//{
	//	cout << "NEWTEXT::ERROR::Shape is not part of text " << endl;
	//	CurrentShape.reset();
	//}
}


//Supposed to set ShapeGroup
//void Slider::SetShapeGroup()
//{
//	//PageItem
//	CurrentShape.PageGroupItemShapeStartID = this->CurrentPageItem.ShapeStartID;
//	CurrentShape.PageGroupItemShapeOffset = 0;
//	CurrentShape.PageGroupItemID          = this->CurrentPageItem.GroupID;
//	CurrentShape.PageGroupItemCellCount   = this->CurrentPageItem.CellCount - 1;
//	CurrentShape.PageGroupItemPosition    = this->CurrentPageItem.Position;
//	CurrentShape.PageGroupItemSize        = this->CurrentPageItem.Size;
//	CurrentShape.PageGroupItemColor       = this->CurrentPageItem.Color;
//	CurrentShape.PageGroupItemMouseAccess = this->CurrentPageItem.MouseAccess;
//	CurrentShape.PageGroupItemCentered    = this->CurrentPageItem.Centered;
//	//UpdateMouseAccess();
//}


void Slider::AddSlider()
{
	SetShapeGroup();
	CreateSlider();
	//UpdateMouseAccess();
}

void Slider::SetShapeGroup()
{
    //Page Item
	CurrentPageItem.ShapeCount = CurrentSliderData.Description.size() + CurrentSliderData.Ratio.size() + 1; 

	//ShapeGroup
	CurrentShapeGroup.PageItemPosition = CurrentPageItem.Position;
	CurrentShapeGroup.PageItemSize = CurrentPageItem.Size;
	CurrentShapeGroup.PageItemID = CurrentPageItem.GroupID;
	CurrentShapeGroup.PageItemShapeStartID = CurrentPageItem.ShapeStartID;
	CurrentShapeGroup.PageItemShapeCount = CurrentPageItem.ShapeCount;
	CurrentShapeGroup.Page = CurrentPage;

	//Shape
	CurrentShape.PageGroupItemPosition = CurrentPageItem.Position;
	CurrentShape.PageGroupItemSize = CurrentPageItem.Size;
	CurrentShape.PageGroupItemShapeStartID = CurrentPageItem.ShapeStartID;
	CurrentShape.PageGroupItemShapeCount = CurrentPageItem.ShapeCount;
	CurrentShape.ShapeGroupCount = 0;
	CurrentShape.ShapeGroupOffset = 0;
	cout << "Shape Group Set" << endl;
}

void Slider::CreateSlider()
{
	//Slider Setup//
	CurrentPageItem.CellOffset = 1;

	glm::vec2 SliderPosition = CurrentPageItem.Position;
	glm::vec2 RailPosition = CurrentPageItem.Position;

	glm::vec2 SliderSize = { 0.02, 0.07 };
	glm::vec2 RailSize = { 0.40, 0.05 };

	glm::vec2 DescriptionPosition = { RailPosition[0] - (RailSize[0]/2) - 0.00664, RailPosition[1] };
	glm::vec2 RatioPosition = { RailPosition[0] + (RailSize[0]/2) + 0.00664, RailPosition[1] };

	glm::vec4 DescriptionColor = {1.0, 1.0, 1.0, 1.0}; //White
	glm::vec4 RatioColor = { 0.0, 1.0, 0.0, 0.8 }; //White
	glm::vec4 SliderColor = { 0.0, 1.0, 0.0, 0.8 }; //Light Green
	glm::vec4 RailColor = { 0.0, 0.31, 0.0, 0.8 }; //Dark Green

	//Rail Quad
	CurrentShape.Position = RailPosition;
	CurrentShape.Size = RailSize;
	CurrentShape.Color = RailColor;
	CurrentShape.PageGroupItemShapeOffset = 0;
	CurrentShape.PageGroupItemID = CurrentPageItem.GroupID;
	CurrentShape.GroupID = 0;
	Quad Rail(*CurrentPageItem.Page, CurrentShape);
	UpdateMouseAccess(CurrentShape.Position, CurrentShape.Size, P_NONE);

	//Slider Quad
	CurrentShape.Position = SliderPosition;
	CurrentShape.Size = SliderSize;
	CurrentShape.Color = SliderColor;
	CurrentShape.PageGroupItemShapeOffset = 1;
	CurrentShape.PageGroupItemID = CurrentPageItem.GroupID;
	CurrentShape.GroupID = 1;
	Quad Slider(*CurrentPageItem.Page, CurrentShape);
	UpdateMouseAccess(CurrentShape.Position, CurrentShape.Size, P_NONE);

	//Descirption Text
	CurrentShapeGroup.Position = DescriptionPosition;
	CurrentShapeGroup.Color    = DescriptionColor;
	CurrentShapeGroup.PageItemShapeOffset = 2;
	CurrentShapeGroup.GroupID = 2;
	CurrentText.Phrase = CurrentSliderData.Description;
	CurrentText.EndStart = true;
	Text Description(*CurrentPageItem.Page, CurrentShapeGroup, CurrentText);
	UpdateMouseAccess(CurrentShapeGroup.Position, CurrentShapeGroup.Size, P_END_TO_MIDDLE);

	//Ratio Text
	CurrentShapeGroup.Position = RatioPosition;
	CurrentShapeGroup.Color    = RatioColor;
	CurrentShapeGroup.PageItemShapeOffset = CurrentSliderData.Description.size() + 2;
	CurrentText.Phrase = CurrentSliderData.Ratio;
	CurrentText.Centered = false;
	CurrentText.EndStart = false;
	CurrentShapeGroup.GroupID = 3;
	Text Ratio(*CurrentPageItem.Page, CurrentShapeGroup, CurrentText);
	UpdateMouseAccess(CurrentShapeGroup.Position, CurrentShapeGroup.Size, P_BEGINNING_TO_MIDDLE);
	SetMouseAccess();
}

void Slider::Update()
{
	ReCalibrateID();
	SetShapeGroup();
	ReplaceSlider();
	SetMouseAccess();
}

void Slider::ReplaceSlider()
{ 
	cout << "Replacing Slider" << endl;
	if (&CurrentPage == nullptr)
	{
		cout << "Replace Slider shouldn't be happening its null" << endl;
	}
	else
	{
		cout << "Replace Slider IS FINE" << endl;
	}
	//Slider Setup//
	glm::vec2 SliderPosition = CurrentPageItem.Position;
	glm::vec2 RailPosition = CurrentPageItem.Position;

	glm::vec2 SliderSize = { 0.02, 0.07 };
	glm::vec2 RailSize = { 0.40, 0.05 };

	glm::vec2 DescriptionPosition = { RailPosition[0] - (RailSize[0] / 2) - 0.00664, RailPosition[1] };
	glm::vec2 RatioPosition = { RailPosition[0] + (RailSize[0] / 2) + 0.00664, RailPosition[1] };

	glm::vec4 DescriptionColor = { 1.0, 1.0, 1.0, 1.0 }; //White
	glm::vec4 RatioColor = { 0.0, 1.0, 0.0, 0.8 }; //White
	glm::vec4 SliderColor = { 0.0, 1.0, 0.0, 0.8 }; //Light Green
	glm::vec4 RailColor = { 0.0, 0.31, 0.0, 0.8 }; //Dark Green

	//ID as in ShapeID
	int RailID = CurrentPageItem.ShapeStartID;
	int SliderID = CurrentPageItem.ShapeStartID + 1;
	int DescriptionID = CurrentPageItem.ShapeStartID + 2;
	int RatioID = CurrentPageItem.ShapeStartID + CurrentSliderData.Description.size() + 2;  

	//Slider Creation//

	//Rail
	Quad Rail(*CurrentPageItem.Page, RailID);
	CurrentShape.ID = RailID;
	CurrentShape.Position = RailPosition;
	CurrentShape.Size = RailSize;
	CurrentShape.Color = RailColor;
	CurrentShape.ShapeGroupStart = RailID;
	CurrentShape.PageGroupItemShapeOffset = 0;
	CurrentShape.GroupID = 0;
	Rail.SetShape(CurrentShape);

	UpdateMouseAccess(CurrentShapeGroup.Position, CurrentShapeGroup.Size, P_NONE);
	

	//Slider
	Quad Slider(*CurrentPageItem.Page, SliderID);
	CurrentShape.ID = SliderID;
	CurrentShape.Position = SliderPosition;
	CurrentShape.Size = SliderSize;
	CurrentShape.Color = SliderColor;
	CurrentShape.ShapeGroupStart = SliderID;
	CurrentShape.PageGroupItemShapeOffset = 1;
	CurrentShape.GroupID = 1;

	Slider.SetShape(CurrentShape);

	UpdateMouseAccess(CurrentShapeGroup.Position, CurrentShapeGroup.Size, P_NONE);
	
	////Description
	cout << "Replacing Slider finished " << endl;
	Text Description(*CurrentPage, DescriptionID);
	CurrentShapeGroup.ShapeStartID = DescriptionID;
	CurrentShapeGroup.Position = DescriptionPosition;
	CurrentShapeGroup.Color = DescriptionColor;
	CurrentShapeGroup.PageItemShapeOffset = 2;
	CurrentShapeGroup.GroupID = 2;
	CurrentText.EndStart = true;
	CurrentText.Phrase = CurrentSliderData.Description;
	Description.SetTextGroup(CurrentShapeGroup, CurrentText);
	UpdateMouseAccess(CurrentShapeGroup.Position, CurrentShapeGroup.Size, P_END_TO_MIDDLE);
	cout << "Replacing Slider finished " << endl;
	//Ratio
	Text Ratio(*CurrentPage, RatioID);
	CurrentShapeGroup.ShapeStartID = RatioID;
	CurrentShapeGroup.Position = RatioPosition;
	CurrentShapeGroup.Color = RatioColor;
	CurrentShapeGroup.PageItemShapeOffset = CurrentSliderData.Description.size() + 2;
	CurrentShapeGroup.GroupID = 3;
	CurrentText.Centered = false;
	CurrentText.EndStart = false;
	CurrentText.Phrase = CurrentSliderData.Ratio;
	Ratio.SetTextGroup(CurrentShapeGroup, CurrentText);
	UpdateMouseAccess(CurrentShapeGroup.Position, CurrentShapeGroup.Size, P_BEGINNING_TO_MIDDLE);
	
}


//ShapeData Editing
void Slider::Add_Default()
{
	if (CurrentPageItem.Page != nullptr)
	{
		this->CurrentPageItem.Position = { 0.0, 0.0 };
		this->CurrentPageItem.MouseAccess = true;
		this->CurrentPageItem.Highlighted = false;
		this->CurrentPageItem.Centered = false;
		AddSlider();
	}
	else
	{
		cout << "ERROR::Could not add Slider. No page provided" << endl;
	}
}

void Slider::Add_Duplicate()
{
	if (CurrentPageItem.Page != nullptr)
	{
		AddSlider();
	}
	else
	{
		cout << "ERROR::Could not add Slider. No page provided" << endl;
	}
}

void Slider::Add_Insert()
{

}

void Slider::SetDescription(string Description)
{
	CurrentSliderData.Description = Description;
	Update();
}

