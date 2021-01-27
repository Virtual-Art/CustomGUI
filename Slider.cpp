#include "Slider.h"

Slider::Slider(Page& Page)
 : PageGroupItem(Page)
{
	if (Initialized != false)
	{
		//Group Setup
		// null termination character and two quads cancel out //
		this->CurrentPageItem.ShapeCount = CurrentSliderData.Description.size() + CurrentSliderData.Ratio.size() + 2; 
		//this->CurrentPageItem.CellCount = 3;

		//Attribute Setup
		//CurrentPageItem.ShapeOffset = 0;
		//CurrentShapeGroup.ShapeCount = 0;
		CurrentPageItem.Color = { 1.0, 1.0, 1.0, 1.0 };
		CurrentPageItem.Size = { 0.0, 0.0 }; // all of the xadvances of all the text
		CurrentPageItem.Position = { 0.0, -0.6 };
		CurrentPageItem.MouseAccess = true;
		CurrentPageItem.Highlighted = false;
		CurrentPageItem.Centered = false;
		CurrentPageItem.XYShapePerRow = { 2.0, 2.0 }; // Can use without
		CurrentPageItem.ShapeSize = { 0.8, 0.8 };  // Can use without

		AddSlider();
	}
	else
	{
		Log::LogString("Slider Suspended");
	}
}

Slider::Slider(Page& Page, ShapeData& FullShape, SliderData& SliderData)
 : PageGroupItem(Page, FullShape)
{
	if (Initialized != false)
	{
		CurrentSliderData = SliderData;
		CurrentPageItem.ShapeOffset = 0;
		CurrentShapeGroup.ShapeCount = 0;
		CurrentPageItem.ShapeCount = CurrentSliderData.Description.size() + CurrentSliderData.Ratio.size() + 1;
		AddSlider();
	}
	else
	{
		Log::LogString("Slider Suspended");
	}
}


Slider::Slider(Page& Page, PageItemData& PageItemData, SliderData& SliderData)
	: PageGroupItem(Page, PageItemData)
{
	if (Initialized != false)
	{
		CurrentSliderData = SliderData;
		CurrentPageItem.ShapeOffset = 0;
		CurrentShapeGroup.ShapeCount = 0;
		CurrentPageItem.ShapeCount = CurrentSliderData.Description.size() + CurrentSliderData.Ratio.size() + 1;
		AddSlider();
	}
	else
	{
	Log::LogString("Slider Suspended");
	}
}

//Remeber the ID of the shape not the group
Slider::Slider(Page& Page, int PageItemStartID)
	:PageGroupItem(Page, PageItemStartID)
{
	if (&Page != nullptr)
	{
		CurrentPage = &Page;
		Initialized = true;
		//Set 1st shape of group
		if (IsInBounds(PageItemStartID) == true)
		{
			CurrentPageItem = Page.GetShapeDataR(PageItemStartID).ShapeGroup.PageItem;

			//SetGroupData
			//if (CurrentShapeDataType == TYPE_SLIDER)
			//{
			//ShapeToGroup(LoadedShape);
			int DescriptionID = GetShapeGroup(DESCRIPTION);
			int RatioID = GetShapeGroup(RATIO);
			if (IsInBounds(DescriptionID) != false && IsInBounds(RatioID) != false)
			{
				Text Description(*CurrentPage, DescriptionID);
				CurrentSliderData.Description = Description.CurrentTextData.Phrase;
				Log::LogString("Slider Description: " + CurrentSliderData.Description);

				Text Ratio(*CurrentPage, RatioID);
				CurrentSliderData.Ratio = Ratio.CurrentTextData.Phrase;
				Log::LogString("Slider Ratio: " + CurrentSliderData.Ratio);
			}
			else
			{
				Log::LogString("Slider Suspended");
			}
		}
		else
		{
			Log::LogString("Slider ID out of bounds");
		}
	}
	else
	{
	Log::LogString("Slider Suspended");
	}
}

void Slider::SwitchToSlider(int SliderStartID)
{
	if (Initialized == false) return Log::LogString("Slider Switch Error:: Slider Not Inititalized");
	if (IsInBounds(SliderStartID) == false) Log::LogString("Slider Switch Error:: ID out of bounds"); return;
	//Set 1st shape of group
	CurrentPageItem = CurrentPage->GetShapeDataR(SliderStartID).ShapeGroup.PageItem;
	//ShapeToGroup(LoadedShape);
	Text Description(*CurrentPage, GetShapeGroup(DESCRIPTION));
	CurrentSliderData.Description = Description.CurrentTextData.Phrase;
	Text Ratio(*CurrentPage, GetShapeGroup(RATIO));
	CurrentSliderData.Ratio = Ratio.CurrentTextData.Phrase;
}


//Supposed to set ShapeGroup
//void Slider::SetShapeGroup()
//{
//	//PageItem
//	CurrentPageGroupItemShapeStartID = this->CurrentPageItem.ShapeStartID;
//	CurrentPageGroupItemShapeOffset = 0;
//	CurrentPageGroupItemID          = this->CurrentPageItem.GroupID;
//	CurrentPageGroupItemCellCount   = this->CurrentPageItem.CellCount - 1;
//	CurrentPageGroupItemPosition    = this->CurrentPageItem.Position;
//	CurrentPageGroupItemSize        = this->CurrentPageItem.Size;
//	CurrentPageGroupItemColor       = this->CurrentPageItem.Color;
//	CurrentPageGroupItemMouseAccess = this->CurrentPageItem.MouseAccess;
//	CurrentPageGroupItemCentered    = this->CurrentPageItem.Centered;
//	//UpdateMouseAccess();
//}


void Slider::AddSlider()
{
	//SetShapeGroup();
	CreateSlider();
}

void Slider::SetShapeGroup()
{
    //Page Item
	

	//ShapeGroup
	//CurrentShapeGroup.PageItemPosition = CurrentPageItem.Position;
	//CurrentShapeGroup.PageItemSize = CurrentPageItem.Size;
	//CurrentShapeGroup.PageItemID = CurrentPageItem.ID;
	//CurrentShapeGroup.PageItemShapeStartID = CurrentPageItem.ShapeStart;
	//CurrentShapeGroup.PageItemShapeCount = CurrentPageItem.ShapeCount;

	//Shape
	//CurrentPageGroupItemPosition = CurrentPageItem.Position;
	//CurrentPageGroupItemSize = CurrentPageItem.Size;
	//CurrentPageGroupItemShapeStartID = CurrentPageItem.ShapeStartID;
//	CurrentPageGroupItemShapeCount = CurrentPageItem.ShapeCount;

	//For the quads

	cout << "Shape Group Set" << endl;
}

void Slider::CreateSlider()
{
	//Slider Setup//

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

	LoadedShape.ShapeGroup.PageItem = CurrentPageItem;
	CurrentShapeGroup.PageItem = CurrentPageItem;

	//Rail Quad
	LoadedShape.Position = RailPosition;
	LoadedShape.Size = RailSize;
	LoadedShape.Color = RailColor;
	CurrentShapeGroup.Position = RailPosition;
	CurrentShapeGroup.Size = RailSize;
	CurrentShapeGroup.ShapeStart = CurrentPage->ShapeAmount();
	CurrentShapeGroup.ShapeCount = 1;
	LoadedShape.ShapeGroup = CurrentShapeGroup;
	Quad Rail(*CurrentPage, LoadedShape);
	UpdateMouseAccess(LoadedShape.Position, LoadedShape.Size, P_NONE);

	//Slider Quad
	LoadedShape.Position = SliderPosition;
	LoadedShape.Size = SliderSize;
	LoadedShape.Color = SliderColor;
	CurrentShapeGroup.Position = SliderPosition;
    CurrentShapeGroup.Size = SliderSize;
	Quad Slider(*CurrentPage, LoadedShape);
	UpdateMouseAccess(LoadedShape.Position, LoadedShape.Size, P_NONE);

	//Description Text
	CurrentShapeGroup.Position = DescriptionPosition;
	CurrentShapeGroup.Color    = DescriptionColor;
	CurrentText.Phrase = CurrentSliderData.Description;
	CurrentText.EndStart = true;
	Text Description(*CurrentPage, CurrentShapeGroup, CurrentText);
	UpdateMouseAccess(CurrentShapeGroup.Position, CurrentShapeGroup.Size, P_END_TO_MIDDLE);

	//Ratio Text
	CurrentShapeGroup.Position = RatioPosition;
	CurrentShapeGroup.Color    = RatioColor;
	CurrentText.Phrase = CurrentSliderData.Ratio;
	CurrentText.Centered = false;
	CurrentText.EndStart = false;
	Text Ratio(*CurrentPage, CurrentShapeGroup, CurrentText);
	UpdateMouseAccess(CurrentShapeGroup.Position, CurrentShapeGroup.Size, P_BEGINNING_TO_MIDDLE);
	SetMouseAccess();
}

void Slider::Update()
{
	if (Initialized == false) { Log::LogString("Slider Update Error:: PageItem not Initialized"); return; }
	
	ReCalibrateID();
	//SetShapeGroup();
	ReplaceSlider();
	SetMouseAccess();
	//SetPageGroupOffsets();
}

void Slider::ReplaceSlider()
{ 
	//Log::LogInt("Slider Shape");
	//Slider Setup//
	Quad Quad_Reference(*CurrentPage, 0);
	Text Text_Reference(*CurrentPage, 0);

	CurrentPage->CurrentPageItemShapeCount = -1;

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
	int RailID = CurrentPageItem.ShapeStart;
	int SliderID = CurrentPageItem.ShapeStart + 1;
	int DescriptionID = CurrentPageItem.ShapeStart + 2;
	int RatioID = CurrentPageItem.ShapeStart + CurrentSliderData.Description.size() + 2;  

	CurrentPageItem.ShapeCount = CurrentSliderData.Description.size() + CurrentSliderData.Ratio.size() + 1;
	CurrentShapeGroup.PageItem = CurrentPageItem;
	LoadedShape.ShapeGroup = CurrentShapeGroup;

	//Slider ReCreation//
	//Rail
	Quad_Reference.Switch(RailID);
	LoadedShape.ID = RailID;
	LoadedShape.Position = RailPosition;
	LoadedShape.Size = RailSize;
	LoadedShape.Color = RailColor;
	CurrentShapeGroup.ShapeStart = RailID;
	CurrentShapeGroup.Position = RailPosition;
	CurrentShapeGroup.Size = RailSize;
	CurrentPage->CurrentPageItemShapeCount++;
	CurrentPageItem.ShapeOffset = CurrentPage->CurrentPageItemShapeCount;
	CurrentPage->CurrentPageGroupShapeCount++;
	LoadedShape.ShapeGroup.PageItem.ShapeOffset = CurrentPage->CurrentPageItemShapeCount;
	Quad_Reference.SetShape(LoadedShape);
	UpdateMouseAccess(CurrentShapeGroup.Position, CurrentShapeGroup.Size, P_NONE);

	//Slider
	LoadedShape = Quad_Reference.Switch(SliderID);
	LoadedShape.ID = SliderID;
	LoadedShape.Position = SliderPosition;
	LoadedShape.Size = SliderSize;
	LoadedShape.Color = SliderColor;
	CurrentShapeGroup.Position = SliderPosition;
	CurrentShapeGroup.Size = SliderSize;
	CurrentPage->CurrentPageItemShapeCount++;
	CurrentPageItem.ShapeOffset = CurrentPage->CurrentPageItemShapeCount;
	CurrentPage->CurrentPageGroupShapeCount++;
	LoadedShape.ShapeGroup.PageItem.PageGroup.ShapeOffset = CurrentPage->CurrentPageGroupShapeCount;
	Quad_Reference.SetShape(LoadedShape);
	UpdateMouseAccess(CurrentShapeGroup.Position, CurrentShapeGroup.Size, P_NONE);

	////Description
	//CurrentPage->CurrentPageItemShapeCount++;
	Text_Reference.Switch(DescriptionID);
	CurrentShapeGroup.ShapeStart = DescriptionID;
	CurrentShapeGroup.Position = DescriptionPosition;
	CurrentShapeGroup.Color = DescriptionColor;
	CurrentShapeGroup.ShapeCount = CurrentSliderData.Description.size() - 1;
	CurrentText.EndStart = true;
	CurrentText.Phrase = CurrentSliderData.Description;
	Text_Reference.SetTextGroup(CurrentShapeGroup, CurrentText);
	UpdateMouseAccess(CurrentShapeGroup.Position, CurrentShapeGroup.Size, P_END_TO_MIDDLE);
	//
	////Ratio
	//CurrentPage->CurrentPageItemShapeCount = CurrentSliderData.Description.size() + 1;
	Text_Reference.Switch(RatioID);
	CurrentShapeGroup.ShapeStart = RatioID;
	CurrentShapeGroup.Position = RatioPosition;
	CurrentShapeGroup.Color = RatioColor;
	CurrentText.Centered = false;
	CurrentText.EndStart = false;
	CurrentText.Phrase = CurrentSliderData.Ratio;
	////May be a source of error
	Text_Reference.SetTextGroup(CurrentShapeGroup, CurrentText);
	//UpdateMouseAccess(CurrentShapeGroup.Position, CurrentShapeGroup.Size, P_BEGINNING_TO_MIDDLE);

}


//ShapeData Editing
void Slider::Add_Default()
{
	if (CurrentPage != nullptr)
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
	if (CurrentPage != nullptr)
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

