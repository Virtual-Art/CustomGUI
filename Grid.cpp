#include "Grid.h"

//New Grid
NewGrid::NewGrid(Page& Page)
	: ShapeGroup{Page}
{
	//Group Setup
	this->CurrentGroupData.ShapeStartID = Page.ShapeAmount();
	this->CurrentGroupData.Count = CurrentGroupData.XYShapesPerRow[0] * CurrentGroupData.XYShapesPerRow[1] - 1;
	//Out Of Bounds Check
	if (Page.InBounds(Page.ShapeAmount() + CurrentGroupData.Count))
	{this->CurrentGroupData.NextGroup = Page.GetNextShapeAddress(4);} //Default +4
	//Attribute Setup
	this->CurrentGroupData.Color = { 1.0, 1.0, 1.0, 1.0 };
	this->CurrentGroupData.Size = { 0.5, 0.5 };
	this->CurrentGroupData.Position = { 0.0, 0.0 };
	this->CurrentGroupData.MouseAccess = true;
	this->CurrentGroupData.Highlighted = false;
	this->CurrentGroupData.Centered = true;
	this->CurrentGroupData.XYShapesPerRow = { 2.0, 2.0 };
	this->CurrentGroupData.ShapeDataSize = { 0.8, 0.8 };

	AddGrid();
}


NewGrid::NewGrid(Page& Page, GroupData& GroupData)
	:ShapeGroup{Page, GroupData}
{
	CurrentGroupData.ShapeStartID = Page.ShapeAmount();
	CurrentGroupData.Count = CurrentGroupData.XYShapesPerRow[0] * CurrentGroupData.XYShapesPerRow[1] - 1;
	CurrentGroupData.Centered = true;

	//Out Of Bounds Check
	if (Page.InBounds(Page.ShapeAmount() + CurrentGroupData.Count))
	{ CurrentGroupData.NextGroup = Page.GetNextShapeAddress(4);} //Default +4
	 //Group Setup
	 AddGrid();
}

//Existing Grid
NewGrid::NewGrid(Page& Page, int GroupID)
	: ShapeGroup{Page, GroupID}
{
	//Set 1st shape of group
	CurrentShape = Page.GetShapeDataR(GroupID);
	//SetGroupData
	if (CurrentShape.ShapeDataType == TYPE_GRID)
	{
		ShapeToGroup(CurrentShape);
	}
	else
	{
		cout << "NEWGRID::ERROR::Shape is not part of grid " << endl;
		CurrentShape.reset();
	}
}



////Add ShapeDatas to Page
int NewGrid::CreateGrid()
{
	int ShapeOffset = 0;
	CurrentShape.ShapeDataType = TYPE_GRID;

	//Add ShapeDatas to Page
	for (int xQuad = 0; xQuad < this->CurrentGroupData.XYShapesPerRow[1]; xQuad++)
	{
		for (int yQuad = 0; yQuad < this->CurrentGroupData.XYShapesPerRow[0]; yQuad++)
		{
			//Set Per-ShapeData Details
			CurrentShape.Position = LoadShapePosition(this->CurrentGroupData.Position, this->CurrentGroupData.Size, this->CurrentGroupData.XYShapesPerRow, { xQuad ,  yQuad }, this->CurrentGroupData.Centered);
			CurrentShape.ShapeGroupOffset = ShapeOffset;
			CurrentShape.GroupID = CurrentGroupData.GroupID;
			//Add Quad
			Quad Quad_Grid(*CurrentGroupData.Page, CurrentShape);
			ShapeOffset++;
		}
	}
	return 0;
}

////Add ShapeDatas to Page
void NewGrid::ReplaceGrid()
{
	int ShapeOffset = 0;
	int CurrentShapeID = CurrentGroupData.ShapeStartID;
	Quad QuadP_Replace(*CurrentGroupData.Page, CurrentShapeID);
	//Add ShapeDatas to Page
	for (int xQuad = 0; xQuad < this->CurrentGroupData.XYShapesPerRow[1]; xQuad++)
	{
		for (int yQuad = 0; yQuad < this->CurrentGroupData.XYShapesPerRow[0]; yQuad++)
		{
			QuadP_Replace.SwitchToShape(CurrentShapeID);
			//Set Per-ShapeData Details
			CurrentShape.ID = CurrentShapeID;
			cout << "CurrenShapeID" << CurrentShapeID << endl;
			//cout << "CurrentGroup ShapeSize " << CurrentGroupData.ShapeDataSize[0] << " " << CurrentGroupData.ShapeDataSize[1]  << endl;
			CurrentShape.Position = LoadShapePosition(this->CurrentGroupData.Position, this->CurrentGroupData.Size, this->CurrentGroupData.XYShapesPerRow, { xQuad ,  yQuad }, this->CurrentGroupData.Centered);
			CurrentShape.ShapeGroupOffset = ShapeOffset;
			//ReplaceQuad
			QuadP_Replace.SetShape(CurrentShape);
			CurrentShapeID++;
			ShapeOffset++;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////

//Manager Functions 
void NewGrid::AddGrid()
{
	//Convert to GPU Cooridnates
	//Take All Members and load into ShapeData
	SetShapeData();
	//Create and add to Page 
	CreateGrid();
}

//Object-Type Function
//UpdateGrid()?
void NewGrid::Update()
{
	//Takes Object members into grid ShapeDate
	SetShapeData();
	ReplaceGrid();
}

glm::vec2 NewGrid::LoadShapePosition(glm::vec2 GroupPosition, glm::vec2 GroupSize, glm::vec2 XYShapesPerRow, glm::vec2 XYLoop, bool Centered)
{
	if (Centered == true)
	{
		GroupPosition[0] -= (GroupSize[0] / 2);
		GroupPosition[1] += (GroupSize[1] / 2);
	}

	//The reason i'm doing this again is because i need the full size of the ShapeData to calculate the proper position
	glm::vec2 ShapeDataSize = LoadShapeSize(GroupSize, XYShapesPerRow, { 1.0, 1.0 });

	float xStartOffset = ShapeDataSize[0] / 2;
	float yStartOffset = ShapeDataSize[1] / 2;
	float xRegOffset = ShapeDataSize[0];
	float yRegOffset = ShapeDataSize[1];
	GroupPosition.x += (xStartOffset + xRegOffset * XYLoop.x);
	GroupPosition.y -= (yStartOffset + yRegOffset * XYLoop.y);
	return GroupPosition;
}


glm::vec2 NewGrid::LoadShapeSize(glm::vec2 GroupSize, glm::vec2 XYShapesPerRow, glm::vec2 ShapeDataSize)
{

	//cout << (CurrentGroupData.ShapeGroupSize[0] / (CurrentGroupData.XYShapesPerRow[0])) << endl;
	//cout << (CurrentGroupData.ShapeGroupSize[1] / (CurrentGroupData.XYShapesPerRow[1])) << endl;

	//cout << "XYShapeDatas per row " << CurrentGroupData.XYShapesPerRow[0] << CurrentGroupData.XYShapesPerRow[1] << endl;
	float xShapeDataSize = (GroupSize[0] / (XYShapesPerRow[0]));
	float yShapeDataSize = (GroupSize[1] / (XYShapesPerRow[1]));

	xShapeDataSize *= ShapeDataSize[0]; // we don't want the tiles to be full size, or else we can't see anything
	yShapeDataSize *= ShapeDataSize[1]; // so we are reducing the size to 75 percent

	//cout << "ShapeDataSIZE " << xShapeDataSize << endl;
	//cout << "ShapeDataSIZE " << yShapeDataSize << endl;



	return { xShapeDataSize, yShapeDataSize };
}

//Sets the Shape details based from GroupData/GridData
void NewGrid::SetShapeData()
{
	//Grid Details
	CurrentShape.ShapeGroupXYShapePerRow = CurrentGroupData.XYShapesPerRow;
	CurrentShape.ShapeGroupShapeSize = CurrentGroupData.ShapeDataSize;

	//Group Details
	CurrentShape.ShapeGroupStart = this->CurrentGroupData.ShapeStartID;
	CurrentShape.ShapeGroupCount = this->CurrentGroupData.XYShapesPerRow[0] * this->CurrentGroupData.XYShapesPerRow[1] - 1;
	CurrentShape.ShapeGroupPosition = this->CurrentGroupData.Position;
	CurrentShape.ShapeGroupSize = this->CurrentGroupData.Size;
	CurrentShape.ShapeGroupColor = this->CurrentGroupData.Color;
	CurrentShape.ShapeGroupMouseAccess = this->CurrentGroupData.MouseAccess;
	CurrentShape.ShapeGroupCentered = this->CurrentGroupData.Centered;
	CurrentShape.ShapeDataType = TYPE_GRID;

	//Shape Details
	CurrentShape.Size = LoadShapeSize(this->CurrentGroupData.Size, this->CurrentGroupData.XYShapesPerRow, this->CurrentGroupData.ShapeDataSize);
	CurrentShape.Color = this->CurrentGroupData.Color;
}


void NewGrid::SetGridXY(glm::vec2 XY)
{
	int NewCount = XY[0] * XY[1];
	int NumShapesToAlter = NewCount - CurrentGroupData.Count;
	CurrentGroupData.XYShapesPerRow = XY;
	CurrentGroupData.Count = NewCount;

	//Add More Shapes
	if (NumShapesToAlter > 0)
	{
		cout << "Inserted" << endl;
		CurrentGroupData.Page->InsertShapeArray(CurrentGroupData.ShapeStartID, NumShapesToAlter);
	}
	//RemoveShapes
	else if (NumShapesToAlter < 0)
	{
		cout << "Removed " << endl;
		CurrentGroupData.Page->DeleteShapeArray(CurrentGroupData.ShapeStartID, (NumShapesToAlter * -1));
	}
	Update();
}

void NewGrid::SetShapeSize(glm::vec2 ShapeSize)
{
	this->CurrentGroupData.ShapeDataSize = ShapeSize;
	Update();

}

//For Editing functions 
void NewGrid::LoadGrid(Page* Page, int ShapeDataID)
{
	ShapeData* ShapeDataDetails = Page->GetShapeDataP(ShapeDataID);

	//Grid Details
	this->CurrentGroupData.XYShapesPerRow = ShapeDataDetails->ShapeGroupXYShapePerRow;
	this->CurrentGroupData.ShapeDataSize = ShapeDataDetails->ShapeGroupShapeSize;

	//Group Details
	this->CurrentGroupData.ShapeStartID = Page->ShapeAmount();
	this->CurrentShape.GroupID = CurrentGroupData.GroupID;
	this->CurrentGroupData.Count = ShapeDataDetails->ShapeGroupCount;
	//this->NextShapeDataGroup = ShapeDataDetails->NextShapeGroup;
	this->CurrentGroupData.Position = ShapeDataDetails->ShapeGroupPosition;
    this->CurrentGroupData.Size = ShapeDataDetails->ShapeGroupSize;
    this->CurrentGroupData.Color = ShapeDataDetails->ShapeGroupColor;
	this->CurrentGroupData.MouseAccess = ShapeDataDetails->MouseAccess;
	this->CurrentGroupData.Centered = ShapeDataDetails->Centered;
	this->CurrentGroupData.Highlighted = ShapeDataDetails->Highlighted;
	//this->ShapeDataGroupType = ShapeDataDetails->ShapeDataType;
	this->CurrentGroupData.ShapeStartID = ShapeDataDetails->ShapeGroupStart;
}





