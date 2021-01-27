#include "Quad.h"

//GUI
Quad::Quad(llBookData* llBook)
  :  Shape(llBook)
{
	CurrentllShape->Position = { 0.0, 0.0 };
	CurrentllShape->Size = { 0.5, 0.5 };
	CurrentllShape->Color = { 1.0, 1.0, 1.0, 1.0 };
	SetllQuad();
}


Quad(llBookData* llBook, llShapeData* llShape)
	: Shape(llBook, llShape)
{
	SetllQuad();
}


//or passing the Shape data for it's data but doesnt have a spot
//Either Passing in a completed existing shape data
Quad::Quad(llShapeData* ShapeData)
	: Shape(ShapeData)
{
	SetllQuad();

}
//
//New Shape // SetInStone = true
Quad::Quad(Page& Page)
	: Shape{ Page }
{
	//Shape Data already created and set
	LoadedShape.Position = { 0.0, 0.0 };
	LoadedShape.Size = { 0.5, 0.5 };
	LoadedShape.Color = { 1.0, 1.0, 1.0, 1.0 };
	SetShapeRatios();
	BuildShapeVertices();
	Page.AddShape(this->LoadedShape);
}

//Helper Object
//New Shape with existing Data // SetInStone = true
Quad::Quad(Page& Page, ShapeData& ShapeData) 
	: Shape{ Page, ShapeData }
{
	//Shape Data already created and set
	SetShapeRatios();
	BuildShapeVertices();
	Page.AddShape(this->LoadedShape);
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
	CurrentPage->ReplaceShape(LoadedShape);
}

void Quad::SetAction(int ShapeDataActionID) 
{
	ElementAction* Action = nullptr; // = CurrentPage->GetShapeDataAction(ShapeDataActionID);
	LoadedShape.Position[0] = Action->Result[POSITION][0];
	LoadedShape.Position[1] = Action->Result[POSITION][1];
	LoadedShape.Size[1] = Action->Result[SIZE][0];
	LoadedShape.Size[1] = Action->Result[SIZE][1];
	//LoadedShape.Rotation = Action->Result[ROTATION][0];
	//LoadedShape.Rotation = Action->Result[ROTATION][1];
	LoadedShape.Color[0] = Action->Result[COLOR][0];
	LoadedShape.Color[1] = Action->Result[COLOR][1];
	LoadedShape.Color[2] = Action->Result[COLOR][2];
	LoadedShape.Color[3] = Action->Result[COLOR][3];
	LoadedShape.MouseAccess = Action->MouseAccess;

	Update();
}


void Quad::SetllQuad()
{
	TopRightXYRatio = { CurrentllShape->Size[0] / 2, CurrentllShape->Size[1] / 2 };

	BottomRightXYRatio = { CurrentllShape->Size[0] / 2, CurrentllShape->Size[1] / -2 };

	BottomLeftXYRatio = { CurrentllShape->Size[0] / -2, CurrentllShape->Size[1] / -2 };

	TopLeftXYRatio = { CurrentllShape->Size[0] / -2, CurrentllShape->Size[1] / 2 };

	llVertexData* CurrentVertex = VertexTopLeft;

	while (CurrentVertex->Next != nullptr)
	{
		//Set Data
		CurrentVertex->Color = CurrentllShape->Color;
		CurrentVertex->TexIndex = CurrentllShape->ActiveTexture;
		CurrentVertex->CentralPoint = { CurrentllShape->Position[0] + (CurrentllShape->Size[0] / 2), CurrentllShape->Position[1] - (CurrentllShape->Size[1] / 2) };
		CurrentVertex->GUIAction = CurrentllShape->Action;
		CurrentVertex = CurrentVertex->Next;
	}

	//Set Vertex Position
	VertexTopRight->Position = CurrentllShape->Position + TopRightXYRatio;
	VertexBottomRight->Position = CurrentllShape->Position + BottomRightXYRatio;
	VertexBottomLeft->Position = CurrentllShape->Position + BottomLeftXYRatio;
	VertexTopLeft->Position = CurrentllShape->Position + TopLeftXYRatio;

	//Set Vertex TexCoords
	VertexTopRight->TexCoords = { 1.0, 0.0 };
	VertexBottomRight->TexCoords = { 1.0, 1.0 };
	VertexBottomLeft->TexCoords = { 0.0, 1.0 };
	VertexTopLeft->TexCoords = { 0.0, 0.0 };

	UpdatellMouseAccess();
}

void Quad::SetShapeRatios()
{
	//TopRight
	TopRightXYRatio = { LoadedShape.Size[0] / 2, LoadedShape.Size[1] / 2 };

	BottomRightXYRatio = { LoadedShape.Size[0] / 2, LoadedShape.Size[1] / -2 };

	BottomLeftXYRatio = { LoadedShape.Size[0] / -2, LoadedShape.Size[1] / -2 };

	TopLeftXYRatio = { LoadedShape.Size[0] / -2, LoadedShape.Size[1] / 2 };

}

void Quad::BuildShapeVertices()
{
	for (int i = 0; i < 4; i++)
	{
		//Set Data
		LoadedShape.Vertex[i].Color = LoadedShape.Color;
		LoadedShape.Vertex[i].TexIndex = LoadedShape.ActiveTexture;
		LoadedShape.Vertex[i].CentralPoint = { LoadedShape.Position[0] + (LoadedShape.Size[0] / 2), LoadedShape.Position[1] - (LoadedShape.Size[1] / 2) };
		LoadedShape.Vertex[i].GUIAction = LoadedShape.Action;
	}

	//Set Vertex Position
	LoadedShape.Vertex[0].Position = LoadedShape.Position + TopRightXYRatio;
	LoadedShape.Vertex[1].Position = LoadedShape.Position + BottomRightXYRatio;
	LoadedShape.Vertex[2].Position = LoadedShape.Position + BottomLeftXYRatio;
	LoadedShape.Vertex[3].Position = LoadedShape.Position + TopLeftXYRatio;

	//Set Vertex TexCoords
	LoadedShape.Vertex[0].TexCoords = { 1.0, 0.0 };
	LoadedShape.Vertex[1].TexCoords = { 1.0, 1.0 };
	LoadedShape.Vertex[2].TexCoords = { 0.0, 1.0 };
	LoadedShape.Vertex[3].TexCoords = { 0.0, 0.0 };

}