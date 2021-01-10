#include "Quad.h"

//GUI
//New Shape // SetInStone = true
Quad::Quad(Page& Page)
	: Shape{ Page }
{
	//Shape Data already created and set
	SetShapeRatios();
	BuildShapeVertices();
	Page.AddShape(this->CurrentShapeData);
}

//Helper Object
//New Shape with existing Data // SetInStone = true
Quad::Quad(Page& Page, ShapeData& ShapeData) 
	: Shape{ Page, ShapeData }
{
	//Shape Data already created and set
	SetShapeRatios();
	BuildShapeVertices();
	Page.AddShape(this->CurrentShapeData);
}

//Editor
//Existing Shape // SetInStone = false
Quad::Quad(Page& Page, int ShapeDataID)        
	: Shape{ Page, ShapeDataID }
{
	//Shape Data already created and set
	SetShapeRatios();
}

void Quad::Update()
{
	SetShapeRatios();
	BuildShapeVertices();
	UpdateMouseAccess();
	CurrentPage->ReplaceShape(CurrentShapeData);
}

void Quad::SetAction(int ShapeDataActionID) 
{
	ElementAction* Action = nullptr; // = CurrentPage->GetShapeDataAction(ShapeDataActionID);
	CurrentShapeData.Position[0] = Action->Result[POSITION][0];
	CurrentShapeData.Position[1] = Action->Result[POSITION][1];
	CurrentShapeData.Size[1] = Action->Result[SIZE][0];
	CurrentShapeData.Size[1] = Action->Result[SIZE][1];
	//CurrentShapeData.Rotation = Action->Result[ROTATION][0];
	//CurrentShapeData.Rotation = Action->Result[ROTATION][1];
	CurrentShapeData.Color[0] = Action->Result[COLOR][0];
	CurrentShapeData.Color[1] = Action->Result[COLOR][1];
	CurrentShapeData.Color[2] = Action->Result[COLOR][2];
	CurrentShapeData.Color[3] = Action->Result[COLOR][3];
	CurrentShapeData.MouseAccess = Action->MouseAccess;

	Update();
}


void Quad::SetShapeRatios()
{
	//TopRight
	TopRightXYRatio = { CurrentShapeData.Size[0] / 2, CurrentShapeData.Size[1] / 2 };
	
	BottomRightXYRatio = { CurrentShapeData.Size[0] / 2, CurrentShapeData.Size[1] / -2 };
	
	BottomLeftXYRatio = { CurrentShapeData.Size[0] / -2, CurrentShapeData.Size[1] / -2 };
	
	TopLeftXYRatio = { CurrentShapeData.Size[0] / -2, CurrentShapeData.Size[1] / 2 };
}

void Quad::BuildShapeVertices()
{
	for (int i = 0; i < 4; i++)
	{
		//Set Data
		CurrentShapeData.Vertex[i].Color = CurrentShapeData.Color;
		CurrentShapeData.Vertex[i].TexIndex = CurrentShapeData.ActiveTexture;
		CurrentShapeData.Vertex[i].CentralPoint = { CurrentShapeData.Position[0] + (CurrentShapeData.Size[0] / 2), CurrentShapeData.Position[1] - (CurrentShapeData.Size[1] / 2) };
		CurrentShapeData.Vertex[i].GUIAction = CurrentShapeData.Action;
	}

	//Set Vertex Position
	CurrentShapeData.Vertex[0].Position = CurrentShapeData.Position + TopRightXYRatio;
	CurrentShapeData.Vertex[1].Position = CurrentShapeData.Position + BottomRightXYRatio;
	CurrentShapeData.Vertex[2].Position = CurrentShapeData.Position + BottomLeftXYRatio;
	CurrentShapeData.Vertex[3].Position = CurrentShapeData.Position + TopLeftXYRatio;

	//Set Vertex TexCoords
	CurrentShapeData.Vertex[0].TexCoords = { 1.0, 0.0 };
	CurrentShapeData.Vertex[1].TexCoords = { 1.0, 1.0 };
	CurrentShapeData.Vertex[2].TexCoords = { 0.0, 1.0 };
	CurrentShapeData.Vertex[3].TexCoords = { 0.0, 0.0 };

}