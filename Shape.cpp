#include "Shape.h"

Shape* Shape::ShapeDataPosToMousePos(Shape* Shape, glm::vec2 MousePosition, bool Centered)
{
	if (Centered == true)
	{
		MousePosition[0] -= CurrentShapeData.Size[0] / 2;
		MousePosition[1] += CurrentShapeData.Size[1] / 2;
	}
	CurrentShapeData.Position = MousePosition;
	return Shape;
}


//New Shape
Shape::Shape(Page& Page)
	:SetInStone(true)
{
	CurrentPage = &Page;
}

//New Shape with data
Shape::Shape(Page& Page, ShapeData& ShapeData)
	:SetInStone(true)
{
	this->CurrentShapeData = ShapeData;
	this->CurrentPage = &Page;
}


//Existing Shape
Shape::Shape(Page& Page, int ID)
	:SetInStone(false)
{
	//Page is good
	if (&Page != nullptr)
	{
	   this->CurrentPage = &Page;
	   if (ID > -1 && ID < Page.ShapeAmount())
	   {
	   	CurrentShapeData = Page.GetShapeDataR(ID);
	   }
	   else
	   {
	   	cout << "Shape Not Initialized ID:" << ID << endl;
	   }
	}
	else
	{
		cout << "Existing Shape initialization error:: Page is nullptr" << endl;
	}
}
Shape::~Shape()
{

}

void Shape::UpdateMouseAccess()
{
	if (CurrentShapeData.MouseAccess == true)
	{
		this->CurrentShapeData.Top = (CurrentShapeData.Position.y + CurrentShapeData.Size[1]/2);
		this->CurrentShapeData.Bottom = (CurrentShapeData.Position.y - CurrentShapeData.Size[1]/2);
		this->CurrentShapeData.Left = (CurrentShapeData.Position.x - CurrentShapeData.Size[0] / 2);
		this->CurrentShapeData.Right = (CurrentShapeData.Position.x + CurrentShapeData.Size[0] / 2);
	}
	else
	{
		this->CurrentShapeData.Top = 3.0;
		this->CurrentShapeData.Bottom = 3.0;
		this->CurrentShapeData.Left = -3.0;
		this->CurrentShapeData.Right = -3.0;
	}

	//this->MouseAccess = true;
	this->CurrentShapeData.HighlightPosition = CurrentShapeData.Position;
	this->CurrentShapeData.HighlightSize = { CurrentShapeData.Size[0] + 0.0032, CurrentShapeData.Size[1] + 0.0066 };
	this->CurrentShapeData.HighlightColor = { 0.0, 0.7156, 0.0, 1.0 };
}

void Shape::Add_Default()
{
	SetShapeRatios();
	BuildShapeVertices();
	if (CurrentPage != nullptr)
	{
		CurrentShapeData.Position = { 0.0, 0.0 };
		CurrentShapeData.Size = { 0.5, 0.5 };
		CurrentShapeData.Color = { 0.8, 0.8, 0.8, 0.8 };
		CurrentPage->AddShape(CurrentShapeData);
	}
	else
	{
		cout << "ERROR::Could not add shape. No page provided" << endl;
	}
}

void Shape::DeleteShape()
{
	CurrentPage->DeleteShapeData(CurrentShapeData.ID);
}

void Shape::Add_Duplicate()
{
	SetShapeRatios();
	BuildShapeVertices();
	if (CurrentPage != nullptr)
	{
		CurrentPage->AddShape(CurrentShapeData);
	}
	else
	{
		cout << "ERROR::Could not add shape. No page provided" << endl;
	}
}

void Shape::Add_Insert()
{
	if (CurrentPage != nullptr && CurrentShapeData.ID > 0 )
	{
		CurrentPage->InsertShapeArray(CurrentShapeData.ID - 1, 1);
	}
	else
	{
		cout << "ERROR::Could not add shape. No page provided" << endl;
	}
}

void Shape::SwitchToShape(int ShapeID)
{
	if (SetInStone != true && ShapeID > -1 && ShapeID < CurrentPage->MaxShapeDataCount)
	{
		this->CurrentShapeData = CurrentPage->GetShapeDataR(ShapeID);
	}
}

void Shape::SwitchToShape(Page& Page, int ShapeID)
{
	if (SetInStone != true && ShapeID != -1 && ShapeID < Page.MaxShapeDataCount)
	{
		this->CurrentPage = &Page;
		this->CurrentShapeData = CurrentPage->GetShapeDataR(ShapeID);
	}
}

void Shape::SetShape(ShapeData& ShapeData)
{
	this->CurrentShapeData = ShapeData;
	this->Update();
}

void Shape::SetShape(ShapeData& ShapeData, glm::vec2 PSConversions)
{
	this->CurrentShapeData = ShapeData;
	ShapeData.Position = ApplyPositionConversion(ShapeData.Position, PSConversions[0]);
	ShapeData.Size = ApplySizeConversion(ShapeData.Size, PSConversions[1]);

	this->Update();
}
void Shape::SetPosition(glm::vec2 Position)
{
		this->CurrentShapeData.Position = Position;
		this->Update();
}
void Shape::SetPosition(glm::vec2 Position, glm::vec2 bools)
{
	if (bools[0] == true)
	{
		this->CurrentShapeData.Position[0] = Position[0];
	}
	if (bools[1] == true)
	{
		this->CurrentShapeData.Position[1] = Position[1];
	}
	Update();
}

void Shape::SetSize(glm::vec2 Size)
{
	this->CurrentShapeData.Size = Size;
	Update();
}

void Shape::SetSize(glm::vec2 Size, glm::vec2 bools)
{
	if (bools[0] == true)
	{
		this->CurrentShapeData.Size[0] = Size[0];
	}
	if (bools[1] == true)
	{
		this->CurrentShapeData.Size[1] = Size[1];
	}
	Update();
}

void Shape::SetColor(glm::vec4 Color)
{
	this->CurrentShapeData.Color = Color;
	Update();
}
void Shape::SetColor(glm::vec4 Color, glm::vec4 bools)
{
	if (bools[0] == true)
	{
		this->CurrentShapeData.Color[0] = Color[0];
	
	}
	if (bools[1] == true)
	{
		this->CurrentShapeData.Color[1] = Color[1];
	}
	if (bools[2] == true)
	{
		this->CurrentShapeData.Color[2] = Color[2];
	}
	if (bools[3] == true)
	{
		this->CurrentShapeData.Color[3] = Color[3];
	}
	Update();
}


void Shape::SetPosition(glm::vec2 Position, int Conversion)
{
	ApplyPositionConversion(Position, Conversion);

	this->CurrentShapeData.Position = Position;
	this->Update();
}

void Shape::SetPosition(glm::vec2 Position, glm::vec2 bools, int Conversion)
{
	Position = ApplyPositionConversion(Position, Conversion);

	if (bools[0] == true)
	{
		this->CurrentShapeData.Position[0] = Position[0];
	}
	if (bools[1] == true)
	{
		this->CurrentShapeData.Position[1] = Position[1];
	}
	Update();
}

void Shape::SetSize(glm::vec2 Size, int Conversion)
{
	this->CurrentShapeData.Size = ApplySizeConversion(Size, Conversion);
	Update();
}

void Shape::SetSize(glm::vec2 Size, glm::vec2 bools, int Conversion)
{
	Size = ApplySizeConversion(Size, Conversion);
	if (bools[0] == true)
	{
		this->CurrentShapeData.Size[0] = Size[0];
	}
	if (bools[1] == true)
	{
		this->CurrentShapeData.Size[1] = Size[1];
	}
	Update();
}


void Shape::OffsetPosition(glm::vec2 Position)
{
	this->CurrentShapeData.Position += Position;
	Update();
}
void Shape::OffsetPosition(glm::vec2 Position, glm::vec2 bools)
{
	if (bools[0] == true)
	{
		this->CurrentShapeData.Position[0] += Position[0];
	}
	if (bools[1] == true)
	{
		this->CurrentShapeData.Position[1] += Position[1];
	}

	Update();
}
void Shape::OffsetSize(glm::vec2 Size)
{
	this->CurrentShapeData.Size += Size;
	Update();
}
void Shape::OffsetSize(glm::vec2 Size, glm::vec2 bools)
{
	if (bools[0] == true)
	{
		this->CurrentShapeData.Size[0] += Size[0];
	}
	if (bools[1] == true)
	{
		this->CurrentShapeData.Size[1] += Size[1];
	}
	Update();
}

void Shape::OffsetColor(glm::vec4 Color)
{
	this->CurrentShapeData.Color += Color;
	Update();
}
void Shape::OffsetColor(glm::vec4 Color, glm::vec4 bools)
{
	if (bools[0] == true)
	{
		this->CurrentShapeData.Color[0] += Color[0];

	}
	if (bools[1] == true)
	{
		this->CurrentShapeData.Color[1] += Color[1];
	}
	if (bools[2] == true)
	{
		this->CurrentShapeData.Color[2] += Color[2];
	}
	if (bools[3] == true)
	{
		this->CurrentShapeData.Color[3] += Color[3];
	}
	Update();
}

///////////////////////////////////////////////////////////////

void Shape::OffsetPosition(glm::vec2 OffsetPosition, int Conversion)
{
	OffsetPosition = ApplySizeConversion(OffsetPosition, Conversion);

	this->CurrentShapeData.Position += OffsetPosition;
	Update();
}
void Shape::OffsetPosition(glm::vec2 OffsetPosition, glm::vec2 bools, int Conversion)
{
	OffsetPosition = ApplySizeConversion(OffsetPosition, Conversion);

	if (bools[0] == true)
	{
		this->CurrentShapeData.Position[0] += OffsetPosition[0];
	}
	if (bools[1] == true)
	{
		this->CurrentShapeData.Position[1] += OffsetPosition[1];
	}
	Update();
}
void Shape::OffsetSize(glm::vec2 Size, int Conversion)
{
	Size = ApplySizeConversion(Size, Conversion);
	this->CurrentShapeData.Size += Size;
	Update();
}
void Shape::OffsetSize(glm::vec2 Size, glm::vec2 bools, int Conversion)
{
	Size = ApplySizeConversion(Size, Conversion);

	if (bools[0] == true)
	{
		this->CurrentShapeData.Size[0] += Size[0];
	}
	if (bools[1] == true)
	{
		this->CurrentShapeData.Size[1] += Size[1];
	}
	Update();
}


////////////////////////////////////////////VERTEX FUNCTIONS//////////////////////////////////////////////////

//Set Functions
void Shape::SetVertexPosition(int Index, glm::vec2& Position)
{ 	this->CurrentShapeData.Vertex[Index].Position = Position; };

void Shape::SetVertexColor(int Index, glm::vec4& Color)
{ this->CurrentShapeData.Vertex[Index].Color = Color; };

void Shape::SetVertexTexCoords(int Index, glm::vec2& TextureCoordinates)
{ this->CurrentShapeData.Vertex[Index].TexCoords = TextureCoordinates; };

void Shape::SetVertexGuiAction(int Index, int& Action)
{ this->CurrentShapeData.Vertex[Index].GUIAction = Action; };

void Shape::SetVertexCentralPoint(int Index, glm::vec2& CentralPoint)
{ this->CurrentShapeData.Vertex[Index].CentralPoint = CentralPoint; };

void Shape::SetVertexTextureIndex(int Index, float& TextureIndex)
{ this->CurrentShapeData.Vertex[Index].TexIndex = TextureIndex; };



//Offset Functions
void Shape::OffsetVertexPosition(int Index, glm::vec2& Position)
{ this->CurrentShapeData.Vertex[Index].Position += Position; };

void Shape::OffsetVertexColor(int Index, glm::vec4& Color)
{ this->CurrentShapeData.Vertex[Index].Color += Color; };

void Shape::OffsetVertexTexCoords(int Index, glm::vec2& TextureCoordinates)
{ this->CurrentShapeData.Vertex[Index].TexCoords += TextureCoordinates; };

void Shape::OffsetVertexGuiAction(int Index, int& Action)
{ this->CurrentShapeData.Vertex[Index].GUIAction += Action; };

void Shape::OffsetVertexCentralPoint(int Index, glm::vec2& CentralPoint)
{ this->CurrentShapeData.Vertex[Index].CentralPoint += CentralPoint; };

void Shape::OffsetVertexTextureIndex(int Index, float& TextureIndex)
{ this->CurrentShapeData.Vertex[Index].TexIndex += TextureIndex; };



glm::vec2 Shape::PTLPixelToComputer(glm::vec2 Position)  //Working
{
	float xPos;
	xPos = (Position[0] / (1200 / 20)) * 0.1 - 1; //System::Width
	float yPos;
	yPos = (Position[1] / (600 / 20)) * 0.1 - 1; //System::Height
	return { xPos, yPos * -1 };
}; //PTL Position, Top, Left

glm::vec2 Shape::PBLPixelToComputer(glm::vec2 Position) //Working
{
	float xPos;
	xPos = (Position[0] / (1200 / 20)) * 0.1 - 1; //System::Width
	float yPos;
	yPos = (Position[1] / (600 / 20)) * 0.1 - 1; //System::Height
	cout << xPos << " " << yPos << endl;
	return { xPos, yPos };
}


glm::vec2 Shape::SPixelToComputer(glm::vec2 Size) //Working
{
	float xSize = Size[0] / (1200 / 2); //System::Width
	float ySize = Size[1] / (600 / 2); //System::Height

	return { xSize, ySize };
};

glm::vec2 Shape::SOneToComputer(glm::vec2 Size)
{
	float AspectRatio = 1200 / 600; // Width / Height
	return { Size[0], Size[1] * AspectRatio };
}

glm::vec2 Shape::PComputerToBLPixel(glm::vec2 Position)
{
	float xPos;
	xPos = (((Position[0] + 1) / 0.1) * (1200 / 20)); //System::Width
	float yPos;
	yPos = (((Position[1] + 1) / 0.1) * (600 / 20)); //System::Height
	return { xPos, yPos };
};

glm::vec2 Shape::SComputerToPixel(glm::vec2 Size) //Working
{
	float xSize = Size[0] * (1200 / 2); //System::Width
	float ySize = Size[1] * (600 / 2); //System::Height
	return { xSize, ySize };;
}

glm::vec2 Shape::SComputerToOne(glm::vec2 Size)
{
	float AspectRatio = 1200 / 600; // Width / Height
	return { Size[0], Size[1] / AspectRatio };
}


glm::vec2 Shape::PComputerToTLPixel(glm::vec2 Position) //Working
{
	float xPos;
	xPos = (((Position[0] + 1) / 0.1) * (1200 / 20)); //System::Width
	float yPos = Position[1] * -1;
	yPos = ((yPos + 1) / 0.1) * (600 / 20); //System::Height
	return { xPos, yPos };
};


glm::vec2 Shape::PMiddleToTopLeft(glm::vec2 Position, glm::vec2 Size)
{
	//It's at the middle. put it to top left
	Position[0] -= (Size[0] / 2);
	Position[1] += (Size[1] / 2);
	return Position;
}

glm::vec2 Shape::ApplyPositionConversion(glm::vec2 Position, int Conversion)
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
		Position = PMiddleToTopLeft(Position, CurrentShapeData.Size);
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

glm::vec2 Shape::ApplySizeConversion(glm::vec2 Size, int Conversion)
{
	//Size Conversion
	switch (Conversion)
	{
	case 1:
		//Bottom Left Pixel To Computer Coordinates
		Size = SPixelToComputer(Size);
		cout << "Size: " << Size[0] << " " << Size[1] << endl;
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