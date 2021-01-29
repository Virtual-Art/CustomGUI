#include "MasterElement.h"

void MasterElement::PrintPageItemShapes(llPageItemData* llPageItem)
{
	cout << "----------------------Trying To Print PageItem Shapes..-------------------------" << endl;
	int ShapeCount = 0;
	llShapeGroupData* CurrentShapeGroup = llPageItem->ShapeGroup;

	if (CurrentShapeGroup == nullptr) { Log::LogString(" is empty"); return; };

	//Find Head Shape
	while (CurrentShapeGroup->Previous != nullptr)
	{
		CurrentShapeGroup = CurrentShapeGroup->Previous;
	}

	//Print All Shapes
	while (CurrentShapeGroup != nullptr)
	{
		PrintShapeGroupShapes(CurrentShapeGroup);
		CurrentShapeGroup = CurrentShapeGroup->Next;
		ShapeCount++;
	}
}

void MasterElement::PrintPageItemShapeGroups(llPageItemData* llPageItem)
{
	cout << "------------Trying To Print Group Shapes..------------" << endl;
	int ShapeCount = 0;
	llShapeGroupData* CurrentShapeGroup = llPageItem->ShapeGroup;

	if (CurrentShapeGroup == nullptr) { Log::LogString("ShapeGroup is empty"); return; };

	//Find Head Shape
	while (CurrentShapeGroup->Previous != nullptr)
	{
		CurrentShapeGroup = CurrentShapeGroup->Previous;
	}

	//Print All Shapes
	while (CurrentShapeGroup != nullptr)
	{
		PrintllShapeGroup(CurrentShapeGroup, ShapeCount);
		CurrentShapeGroup = CurrentShapeGroup->Next;
		ShapeCount++;
	}
}

void MasterElement::PrintllShapeGroup(llShapeGroupData* llShapeGroup)
{
	cout <<  "------------ShapeGroup (" << llShapeGroup << ")------------------" << endl;
	Log::LogVec2("Position: ", llShapeGroup->Position);
	Log::LogVec2("Size: ", llShapeGroup->Size);
	Log::LogVec4("Color: ", llShapeGroup->Color);

	Log::LogString("------");
	Log::LogFloat("ShapeTop: ", llShapeGroup->Top);
	Log::LogFloat("ShapeBottom: ", llShapeGroup->Bottom);
	Log::LogFloat("ShapeLeft: ", llShapeGroup->Left);
	Log::LogFloat("ShapeRight: ", llShapeGroup->Right);
	Log::LogString("----------------------------------------------------------------");
	//cout << "ActiveTexture: {" << CurrentShapeData.ActiveTexture << "}" << endl;
	//cout << "Action: {" << CurrentShapeData.Action << "}" << endl;
	//cout << "MouseAccess: {" << CurrentShapeData.MouseAccess << "}" << endl;
	//cout << "Centered: {" << CurrentShapeData.Centered << "}" << endl;
	//cout << "Highlighted: {" << CurrentShapeData.Highlighted << "}" << endl;
}

void MasterElement::PrintllShapeGroup(llShapeGroupData* llShapeGroup, int Offset)
{
	cout << "------------ShapeGroup (" << llShapeGroup << ")[" << Offset << "]------------------" << endl;
	Log::LogVec2("Position: ", llShapeGroup->Position);
	Log::LogVec2("Size: ", llShapeGroup->Size);
	Log::LogVec4("Color: ", llShapeGroup->Color);

	Log::LogString("------");
	Log::LogFloat("ShapeTop: ", llShapeGroup->Top);
	Log::LogFloat("ShapeBottom: ", llShapeGroup->Bottom);
	Log::LogFloat("ShapeLeft: ", llShapeGroup->Left);
	Log::LogFloat("ShapeRight: ", llShapeGroup->Right);
	Log::LogString("----------------------------------------------------------------");
	//cout << "ActiveTexture: {" << CurrentShapeData.ActiveTexture << "}" << endl;
	//cout << "Action: {" << CurrentShapeData.Action << "}" << endl;
	//cout << "MouseAccess: {" << CurrentShapeData.MouseAccess << "}" << endl;
	//cout << "Centered: {" << CurrentShapeData.Centered << "}" << endl;
	//cout << "Highlighted: {" << CurrentShapeData.Highlighted << "}" << endl;
}

void MasterElement::PrintShapeGroupShapes(llShapeGroupData* llShapeGroup)
{
	cout << "------------Trying To Print Group Shapes..------------" << endl;
	int ShapeCount = 0;
	llShapeData* CurrentShape = llShapeGroup->Shape;

	if (CurrentShape == nullptr) { Log::LogString("ShapeGroup is empty"); return; };

	//Find Head Shape
	while (CurrentShape->Previous != nullptr)
	{
		CurrentShape = CurrentShape->Previous;
	}

	//Print All Shapes
	while (CurrentShape != nullptr)
	{
		
		PrintllShape(CurrentShape, ShapeCount);
		CurrentShape = CurrentShape->Next;
		ShapeCount++;
	}
}

void MasterElement::PrintllShape(llShapeData* llShape)
{
	Log::LogString("Trying To Print llShape");
	cout << "------------ShapeData-Data (" << llShape << ")------------------" << endl;
	Log::LogVec2("Position: ", llShape->Position);
	Log::LogVec2("Size: ", llShape->Size);
	Log::LogVec4("Color: ", llShape->Color);


	cout << "-------" << endl;
	Log::LogString("Text: " + llShape->Text);
	cout << "Ascii: " << char(llShape->Ascii) << endl;
	Log::LogString("------");
	Log::LogFloat("ShapeTop: ", llShape->Top);
	Log::LogFloat("ShapeBottom: ", llShape->Bottom);
	Log::LogFloat("ShapeLeft: ", llShape->Left);
	Log::LogFloat("ShapeRight: ", llShape->Right);
	Log::LogString("-------------------------------------------------");
	//cout << "ActiveTexture: {" << CurrentShapeData.ActiveTexture << "}" << endl;
	//cout << "Action: {" << CurrentShapeData.Action << "}" << endl;
	//cout << "MouseAccess: {" << CurrentShapeData.MouseAccess << "}" << endl;
	//cout << "Centered: {" << CurrentShapeData.Centered << "}" << endl;
	//cout << "Highlighted: {" << CurrentShapeData.Highlighted << "}" << endl;
}

void MasterElement::PrintllShape(llShapeData* llShape, int Offset)
{
	Log::LogString("Trying To Print llShape");
	cout << "------------ShapeData-Data (" << llShape << ") [" << Offset << "] ------------------" << endl;
	Log::LogVec2("Position: ", llShape->Position);
	Log::LogVec2("Size: ", llShape->Size);
	Log::LogVec4("Color: ", llShape->Color);


	cout << "-------" << endl;
	Log::LogString("Text: " + llShape->Text);
	cout << "Ascii: " << char(llShape->Ascii) << endl;
	Log::LogString("------");
	Log::LogFloat("ShapeTop: ", llShape->Top);
	Log::LogFloat("ShapeBottom: ", llShape->Bottom);
	Log::LogFloat("ShapeLeft: ", llShape->Left);
	Log::LogFloat("ShapeRight: ", llShape->Right);
	Log::LogString("-------------------------------------------------");
	//cout << "ActiveTexture: {" << CurrentShapeData.ActiveTexture << "}" << endl;
	//cout << "Action: {" << CurrentShapeData.Action << "}" << endl;
	//cout << "MouseAccess: {" << CurrentShapeData.MouseAccess << "}" << endl;
	//cout << "Centered: {" << CurrentShapeData.Centered << "}" << endl;
	//cout << "Highlighted: {" << CurrentShapeData.Highlighted << "}" << endl;
}


bool MasterElement::IsInitialized()
{
	return Initialized;
}

bool MasterElement::IsInBounds(int ID)
{
	if (Initialized == true)
	{
		return CurrentPage->InBounds(ID);
	}
   // Log::LogString("Bounds Error:: Element Not Initialized"); return false;
}


MasterElement::MasterElement()
{

}



glm::vec2 MasterElement::PTLPixelToComputer(glm::vec2 Position)  //Working
{
	float xPos;
	xPos = (Position[0] / (1200 / 20)) * 0.1 - 1; //System::Width
	float yPos;
	yPos = (Position[1] / (600 / 20)) * 0.1 - 1; //System::Height
	return { xPos, yPos * -1 };
}; //PTL Position, Top, Left

glm::vec2 MasterElement::PBLPixelToComputer(glm::vec2 Position) //Working
{
	float xPos;
	xPos = (Position[0] / (1200 / 20)) * 0.1 - 1; //System::Width
	float yPos;
	yPos = (Position[1] / (600 / 20)) * 0.1 - 1; //System::Height
	return { xPos, yPos };
}


glm::vec2 MasterElement::SPixelToComputer(glm::vec2 Size) //Working
{
	float xSize = Size[0] / (1200 / 2); //System::Width
	float ySize = Size[1] / (600 / 2); //System::Height

	return { xSize, ySize };
};

glm::vec2 MasterElement::SOneToComputer(glm::vec2 Size)
{
	float AspectRatio = 1200 / 600; // Width / Height
	return { Size[0], Size[1] * AspectRatio };
}

glm::vec2 MasterElement::PComputerToBLPixel(glm::vec2 Position)
{
	float xPos;
	xPos = (((Position[0] + 1) / 0.1) * (1200 / 20)); //System::Width
	float yPos;
	yPos = (((Position[1] + 1) / 0.1) * (600 / 20)); //System::Height
	return { xPos, yPos };
};

glm::vec2 MasterElement::SComputerToPixel(glm::vec2 Size) //Working
{
	float xSize = Size[0] * (1200 / 2); //System::Width
	float ySize = Size[1] * (600 / 2); //System::Height
	return { xSize, ySize };;
}

glm::vec2 MasterElement::SComputerToOne(glm::vec2 Size)
{
	float AspectRatio = 1200 / 600; // Width / Height
	return { Size[0], Size[1] / AspectRatio };
}


glm::vec2 MasterElement::PComputerToTLPixel(glm::vec2 Position) //Working
{
	float xPos;
	xPos = (((Position[0] + 1) / 0.1) * (1200 / 20)); //System::Width
	float yPos = Position[1] * -1;
	yPos = ((yPos + 1) / 0.1) * (600 / 20); //System::Height
	return { xPos, yPos };
};


glm::vec2 MasterElement::PMiddleToTopLeft(glm::vec2 Position, glm::vec2 Size)
{
	//It's at the middle. put it to top left
	Position[0] -= (Size[0] / 2);
	Position[1] += (Size[1] / 2);
	return Position;
}

glm::vec2 MasterElement::PTopLeftToMiddle(glm::vec2 Position, glm::vec2 Size)
{
	//It's at the top left, put it to the middle
	Position[0] += (Size[0] / 2);
	Position[1] -= (Size[1] / 2);
	return Position;
}

glm::vec2 MasterElement::ApplyPositionConversion(glm::vec2 Position, int Conversion, glm::vec2 Size)
{
	//Position Conversion
	switch (Conversion)
	{
	case 1:
		//Bottom Left Pixel To Computer Coordinates
		Position = PBLPixelToComputer(Position);
		break;
	case 2:
		//Middle To Top Left
		Position = PMiddleToTopLeft(Position, Size);
		break;
	case 3:
		//Top Left Pixel To Computer Coordinates
		Position = PTLPixelToComputer(Position);
		break;
	case 4:
		Position = PComputerToBLPixel(Position);
		break;
	case 5:
		Position = PTopLeftToMiddle(Position, Size);
		break;
	}
	return Position;
}

glm::vec2 MasterElement::ApplyPositionConversion(glm::vec2 Position, int Conversion)
{
	//Position Conversion
	switch (Conversion)
	{
	case 1:
		//Bottom Left Pixel To Computer Coordinates
		Position = PBLPixelToComputer(Position);
		break;
	case 2:
		//Middle To Top Left
		//Position = PMiddleToTopLeft(Position, CurrentShapeData.Size);
		break;
	case 3:
		//Top Left Pixel To Computer Coordinates
		Position = PTLPixelToComputer(Position);
		break;
	case 4:
		Position = PComputerToBLPixel(Position);
		break;
	}
	return Position;
}

glm::vec2 MasterElement::ApplySizeConversion(glm::vec2 Size, int Conversion)
{
	//Size Conversion
	switch (Conversion)
	{
	case 1:
		//Bottom Left Pixel To Computer Coordinates
		Size = SPixelToComputer(Size);

		break;
	case 2:
		//Middle To Top Left
		Size = SOneToComputer(Size);
		break;
	case 3:
		Size = SComputerToPixel(Size);

		break;
	}

	return Size;
}