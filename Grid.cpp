#include "Grid.h"

//New Grid
NewGrid::NewGrid(Page& Page)
	: ShapeGroup{Page}
{
	//Group Setup
	this->LoadedShape.ShapeGroup.ShapeStart = Page.ShapeAmount();
	this->LoadedShape.ShapeGroup.ShapeCount = LoadedShape.ShapeGroup.XYShapePerRow[0] * LoadedShape.ShapeGroup.XYShapePerRow[1] - 1;
	//Out Of Bounds Check
	//if (Page.InBounds(Page.ShapeAmount() + LoadedShape.ShapeGroup.ShapeCount))
	//{this->LoadedShape.ShapeGroup.NextGroup = Page.GetNextShapeAddress(4);} //Default +4
	//Attribute Setup
	this->LoadedShape.ShapeGroup.Color = { 1.0, 1.0, 1.0, 1.0 };
	this->LoadedShape.ShapeGroup.Size = { 0.5, 0.5 };
	this->LoadedShape.ShapeGroup.Position = { 0.0, 0.0 };
	this->LoadedShape.ShapeGroup.MouseAccess = true;
	this->LoadedShape.ShapeGroup.Highlighted = false;
	this->LoadedShape.ShapeGroup.Centered = true;
	this->LoadedShape.ShapeGroup.XYShapePerRow = { 2.0, 2.0 };
	this->LoadedShape.ShapeGroup.ShapeSize = { 0.8, 0.8 };

	AddGrid();
}


NewGrid::NewGrid(Page& Page, ShapeGroupData& ShapeGroupData)
	:ShapeGroup{Page, ShapeGroupData }
{
	LoadedShape.ShapeGroup.ShapeStart = Page.ShapeAmount();
	LoadedShape.ShapeGroup.ShapeCount = LoadedShape.ShapeGroup.XYShapePerRow[0] * LoadedShape.ShapeGroup.XYShapePerRow[1] - 1;
	LoadedShape.ShapeGroup.Centered = true;

	//Out Of Bounds Check
	//if (Page.InBounds(Page.ShapeAmount() + LoadedShape.ShapeGroup.Count))
	//{ LoadedShape.ShapeGroup.NextGroup = Page.GetNextShapeAddress(4);} //Default +4
	// //Group Setup
	 AddGrid();
}

//Existing Grid
NewGrid::NewGrid(Page& Page, int GroupID)
	: ShapeGroup{Page, GroupID}
{
	//Set 1st shape of group
	LoadedShape = Page.GetShapeDataR(GroupID);
	//SetGroupData
	if (LoadedShape.ShapeGroup.Type == TYPE_GRID)
	{
		//ShapeToGroup(LoadedShape);
	}
	else
	{
		cout << "NEWGRID::ERROR::Shape is not part of grid " << endl;
		//LoadedShape.reset();
	}
}



////Add ShapeDatas to Page
int NewGrid::CreateGrid()
{
	int ShapeOffset = 0;
	LoadedShape.ShapeGroup.Type = TYPE_GRID;

	//Add ShapeDatas to Page
	for (int xQuad = 0; xQuad < this->LoadedShape.ShapeGroup.XYShapePerRow[1]; xQuad++)
	{
		for (int yQuad = 0; yQuad < this->LoadedShape.ShapeGroup.XYShapePerRow[0]; yQuad++)
		{
			//Set Per-ShapeData Details
			LoadedShape.Position = LoadShapePosition(this->LoadedShape.ShapeGroup.Position, this->LoadedShape.ShapeGroup.Size, this->LoadedShape.ShapeGroup.XYShapePerRow, { xQuad ,  yQuad }, this->LoadedShape.ShapeGroup.Centered);
			LoadedShape.ShapeGroup.ShapeOffset = ShapeOffset;
			//LoadedShape.ShapeGroup.ID = LoadedShape.ShapeGroup.ID;
			//Add Quad
			Quad Quad_Grid(*CurrentPage, LoadedShape);
			ShapeOffset++;
		}
	}
	return 0;
}

////Add ShapeDatas to Page
void NewGrid::ReplaceGrid()
{
	int ShapeOffset = 0;
	int LoadedShapeID = LoadedShape.ShapeGroup.ShapeStart;
	Quad QuadP_Replace(*CurrentPage, LoadedShapeID);
	//Add ShapeDatas to Page
	for (int xQuad = 0; xQuad < this->LoadedShape.ShapeGroup.XYShapePerRow[1]; xQuad++)
	{
		for (int yQuad = 0; yQuad < this->LoadedShape.ShapeGroup.XYShapePerRow[0]; yQuad++)
		{
			QuadP_Replace.Switch(LoadedShapeID);
			//Set Per-ShapeData Details
			LoadedShape.ID = LoadedShapeID;
			cout << "CurrenShapeID" << LoadedShapeID << endl;
			//cout << "CurrentGroup ShapeSize " << LoadedShape.ShapeGroup.ShapeDataSize[0] << " " << LoadedShape.ShapeGroup.ShapeDataSize[1]  << endl;
			LoadedShape.Position = LoadShapePosition(this->LoadedShape.ShapeGroup.Position, this->LoadedShape.ShapeGroup.Size, this->LoadedShape.ShapeGroup.XYShapePerRow, { xQuad ,  yQuad }, this->LoadedShape.ShapeGroup.Centered);
			LoadedShape.ShapeGroup.ShapeOffset = ShapeOffset;
			//ReplaceQuad
			QuadP_Replace.SetShape(LoadedShape);
			LoadedShapeID++;
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

	//cout << (LoadedShape.ShapeGroup.ShapeGroupSize[0] / (LoadedShape.ShapeGroup.XYShapesPerRow[0])) << endl;
	//cout << (LoadedShape.ShapeGroup.ShapeGroupSize[1] / (LoadedShape.ShapeGroup.XYShapesPerRow[1])) << endl;

	//cout << "XYShapeDatas per row " << LoadedShape.ShapeGroup.XYShapesPerRow[0] << LoadedShape.ShapeGroup.XYShapesPerRow[1] << endl;
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
	//LoadedShape.ShapeGroup.XYShapePerRow = LoadedShape.ShapeGroup.XYShapePerRow;
	//LoadedShape.ShapeGroup.ShapeSize = LoadedShape.ShapeGroup.ShapeSize;

	//Group Details
	//LoadedShape.ShapeGroup.ShapeStart = this->LoadedShape.ShapeGroup.ShapeStart;
	LoadedShape.ShapeGroup.ShapeCount = this->LoadedShape.ShapeGroup.XYShapePerRow[0] * this->LoadedShape.ShapeGroup.XYShapePerRow[1] - 1;
	//LoadedShape.ShapeGroup.Position = this->LoadedShape.ShapeGroup.Position;
	//LoadedShape.ShapeGroup.Size = this->LoadedShape.ShapeGroup.Size;
	//LoadedShape.ShapeGroup.Color = this->LoadedShape.ShapeGroup.Color;
	//LoadedShape.ShapeGroup.MouseAccess = this->LoadedShape.ShapeGroup.MouseAccess;
	//LoadedShape.ShapeGroup.Centered = this->LoadedShape.ShapeGroup.Centered;
	LoadedShape.ShapeGroup.Type = TYPE_GRID;

	//Shape Details
	LoadedShape.Size = LoadShapeSize(this->LoadedShape.ShapeGroup.Size, this->LoadedShape.ShapeGroup.XYShapePerRow, this->LoadedShape.ShapeGroup.ShapeSize);
	LoadedShape.Color = this->LoadedShape.ShapeGroup.Color;
}


void NewGrid::SetGridXY(glm::vec2 XY)
{
	int NewCount = XY[0] * XY[1];
	int NumShapesToAlter = NewCount - LoadedShape.ShapeGroup.ShapeCount;
	LoadedShape.ShapeGroup.XYShapePerRow = XY;
	LoadedShape.ShapeGroup.ShapeCount = NewCount;

	//Add More Shapes
	if (NumShapesToAlter > 0)
	{
		cout << "Inserted" << endl;
		CurrentPage->InsertShapeArray(LoadedShape.ShapeGroup.ShapeStart, NumShapesToAlter);
	}
	//RemoveShapes
	else if (NumShapesToAlter < 0)
	{
		cout << "Removed " << endl;
		CurrentPage->DeleteShapeArray(LoadedShape.ShapeGroup.ShapeStart, (NumShapesToAlter * -1));
	}
	Update();
}

void NewGrid::SetShapeSize(glm::vec2 ShapeSize)
{
	this->LoadedShape.ShapeGroup.ShapeSize = ShapeSize;
	Update();

}

//For Editing functions 
void NewGrid::LoadGrid(Page* Page, int ShapeDataID)
{
	ShapeData* ShapeDataDetails = Page->GetShapeDataP(ShapeDataID);

	//Grid Details
	this->LoadedShape.ShapeGroup.XYShapePerRow = ShapeDataDetails->ShapeGroup.XYShapePerRow;
	this->LoadedShape.ShapeGroup.ShapeSize = ShapeDataDetails->ShapeGroup.ShapeSize;

	//Group Details
	this->LoadedShape.ShapeGroup.ShapeStart = Page->ShapeAmount();
	this->LoadedShape.ID = LoadedShape.ShapeGroup.ID;
	this->LoadedShape.ShapeGroup.ShapeCount = ShapeDataDetails->ShapeGroup.ShapeCount;
	//this->NextShapeDataGroup = ShapeDataDetails->NextShapeGroup;
	this->LoadedShape.ShapeGroup.Position = ShapeDataDetails->ShapeGroup.Position;
    this->LoadedShape.ShapeGroup.Size = ShapeDataDetails->ShapeGroup.Size;
    this->LoadedShape.ShapeGroup.Color = ShapeDataDetails->ShapeGroup.Color;
	this->LoadedShape.ShapeGroup.MouseAccess = ShapeDataDetails->MouseAccess;
	this->LoadedShape.ShapeGroup.Centered = ShapeDataDetails->Centered;
	this->LoadedShape.ShapeGroup.Highlighted = ShapeDataDetails->Highlighted;
	//this->ShapeDataGroupType = ShapeDataDetails->ShapeDataType;
	this->LoadedShape.ShapeGroup.ShapeStart = ShapeDataDetails->ShapeGroup.ShapeStart;
}





