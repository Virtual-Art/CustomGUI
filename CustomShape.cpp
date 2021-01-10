#include "CustomShape.h"

glm::vec2 CustomShape::AllShapeRatios[50][4];
bool CustomShape::FirstCreation = true;
int CustomShape::ShapeAmount = 0;

CustomShape::CustomShape(Page& Page)
	: Shape{ Page }
{
	CreateShapeRatioContainer();
}

//GUI
CustomShape::CustomShape(Page& Page, ShapeData& ShapeData) //New Shape with existing Data // SetInStone = true
	: Shape{ Page, ShapeData }
{
	CreateShapeRatioContainer();
	//Page.AddShapeData(ShapeData);
}

//Editor
CustomShape::CustomShape(Page& Page, int ShapeDataID)        //Existing Shape // SetInStone = false
	: Shape{ Page, ShapeDataID }
{
	CreateShapeRatioContainer();
}

void CustomShape::CreateShapeRatioContainer()
{
	if (FirstCreation == true)
	{
		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				AllShapeRatios[i][j] = { 0.0, 0.0 };
			}
		}
		FirstCreation = false;
	}
}


void CustomShape::Add(int Character)
{

}
void CustomShape::Update()
{

}
void CustomShape::SetAction(int ShapeDataActionID)
{

}

void CustomShape::SetVertex(int Index, Vertex Vertex)
{

}


void CustomShape::AddShapeToStack()
{
	for (int i = 0; i < 4; i++)
	{
        //Sets current Shape to Shape ratio stack
		//AllShapeRatios[ShapeAmount][i] = this->ShapeRatio[i];
	}
}

		