#include "Shape.h"

//Existing Shape
Shape::Shape(llShapeData* llShapeData)
	:SetInStone(true)
{
	//If it exists
	if( llShapeData != nullptr)
	{
		if (llShapeData->Vertexx == nullptr || llShapeData->Vertexx->Next == nullptr)
		{
			//Create Vertices
			VertexTopRight = new llVertexData;
			VertexTopLeft = new llVertexData;
			VertexBottomRight = new llVertexData;
			VertexBottomLeft = new llVertexData;

			//Set Next
			VertexTopLeft->Next = VertexTopRight;
			VertexTopRight->Next = VertexBottomRight;
			VertexBottomRight->Next = VertexBottomLeft;

			//Set Previous
			VertexBottomLeft->Previous = VertexBottomRight;
			VertexBottomRight->Previous = VertexTopRight;
			VertexTopRight->Previous = VertexTopLeft;

			llShapeData->Vertexx = VertexTopLeft;
		}
		CurrentllShape = llShapeData;
	}
	else
	{
		Log::LogString("Sorry llShape was nullptr");
	}
}

//New with details
Shape::Shape(llBookData* llBookData, llShapeData* llShape)
	:SetInStone(true)
{
	//If it exists
	if (llShape != nullptr)
	{
		if (llShape->Vertexx == nullptr)
		{
			//Create Vertices
			VertexTopRight = new llVertexData;
			VertexTopLeft = new llVertexData;
			VertexBottomRight = new llVertexData;
			VertexBottomLeft = new llVertexData;

			CurrentllShape = new llShapeData;
			*CurrentllShape = *llShape;

			//Set Next
			VertexTopLeft->Next = VertexTopRight;
			VertexTopRight->Next = VertexBottomRight;
			VertexBottomRight->Next = VertexBottomLeft;

			//Set Previous
			VertexBottomLeft->Previous = VertexBottomRight;
			VertexBottomRight->Previous = VertexTopRight;
			VertexTopRight->Previous = VertexTopLeft;

			llShape->Vertexx = VertexTopLeft;
		}
		LoadedBook = llBookData;
	}
	else
	{
		Log::LogString("Sorry llShape was nullptr");
	}
}

//New Shape
Shape::Shape(llBookData* llBookData)
	:SetInStone(true)
{
	//Create Book if not created
	//Honestly this is what book class should do whatever it is in the future
	if (llBookData->Page == nullptr)
	{
		llPageData* CreatedPage =  new llPageData;
		llPageGroupData* CreatedPageGroup =  new llPageGroupData;
		llPageItemData* CreatedPageItem = new llPageItemData;
		llShapeGroupData* CreatedShapeGroup = new llShapeGroupData;

		llBookData->Page = CreatedPage;
		llBookData->Page->PageGroup = CreatedPageGroup;
		llBookData->Page->PageGroup->PageItem = CreatedPageItem;
		llBookData->Page->PageGroup->PageItem->ShapeGroup = CreatedShapeGroup;
	}

	//Create Vertex / Shape
	VertexTopRight = new llVertexData;
	VertexTopLeft = new llVertexData;
	VertexBottomRight = new llVertexData;
	VertexBottomLeft = new llVertexData;
	CurrentllShape = new llShapeData;

	//Set Next
	VertexTopLeft->Next = VertexTopRight;
	VertexTopRight->Next = VertexBottomRight;
	VertexBottomRight->Next = VertexBottomLeft;

	//Set Previous
	VertexBottomLeft->Previous = VertexBottomRight;
	VertexBottomRight->Previous = VertexTopRight;
	VertexTopRight->Previous = VertexTopLeft;

	CurrentllShape->Vertexx = VertexTopLeft;

	llShapeData* TestingShape = llBookData->Page->PageGroup->PageItem->ShapeGroup->Shape;

	//Completely new object
	if (TestingShape == nullptr)
	{
		Log::LogString("ShapeWas nullptr, just adding it");
		llBookData->Page->PageGroup->PageItem->ShapeGroup->Shape = CurrentllShape;
	}
	else //Shapes already created
	{
		llShapeData* FoundTail = TestingShape;

		//Fint tail then add
		while (FoundTail->Next != nullptr)
		{
			Log::LogString("Looping to tail");
			FoundTail = FoundTail->Next;
		}

		FoundTail->Next = CurrentllShape;
	}

	LoadedBook = llBookData;
}

Shape::Shape(Page& Page)
	:SetInStone(true)
{
	if (&Page != nullptr)
	{
		//Initialization
		Initialized = true;
		CurrentPage = &Page;

		//Track Counts
		CurrentPage->CurrentShape++;
		CurrentPage->CurrentShapeGroupShapeCount++;
		CurrentPage->CurrentPageItemShapeCount++;
		CurrentPage->CurrentPageGroupShapeCount++;
		CurrentPage->TotalShapeCount++;

		//Set IDs
		LoadedShape.ID = CurrentPage->ShapeAmount();
		LoadedShape.ShapeGroup.ID = CurrentPage->CurrentShapeGroup;
		LoadedShape.ShapeGroup.PageItem.ID = CurrentPage->CurrentPageItem;
		LoadedShape.ShapeGroup.PageItem.PageGroup.ID = CurrentPage->CurrentPageGroup;

		//Set Group-Start Shape Offsets
		LoadedShape.ShapeGroup.ShapeOffset = CurrentPage->CurrentShapeGroupShapeCount;
		LoadedShape.ShapeGroup.PageItem.ShapeOffset = CurrentPage->CurrentPageItemShapeCount;
		LoadedShape.ShapeGroup.PageItem.PageGroup.ShapeOffset = CurrentPage->CurrentPageGroupShapeCount;
	}
}

//New Shape with data
Shape::Shape(Page& Page, ShapeData& ShapeData)
	:SetInStone(true)
{
	if (&Page != nullptr)
	{
		//Initialization
		Initialized = true;
		CurrentPage = &Page;
		LoadedShape = ShapeData;

		//Track Counts
		CurrentPage->CurrentShape++;
		CurrentPage->CurrentShapeGroupShapeCount++;
		CurrentPage->CurrentPageItemShapeCount++;
		CurrentPage->CurrentPageGroupShapeCount++;
		CurrentPage->TotalShapeCount++;
	
		//Set IDs
		LoadedShape.ID = CurrentPage->ShapeAmount();
		LoadedShape.ShapeGroup.ID = CurrentPage->CurrentShapeGroup;
		LoadedShape.ShapeGroup.PageItem.ID = CurrentPage->CurrentPageItem;
		LoadedShape.ShapeGroup.PageItem.PageGroup.ID = CurrentPage->CurrentPageGroup;

		//Set Offsets
		LoadedShape.ShapeGroup.ShapeOffset = CurrentPage->CurrentShapeGroupShapeCount;
		LoadedShape.ShapeGroup.PageItem.ShapeOffset = CurrentPage->CurrentPageItemShapeCount;
		LoadedShape.ShapeGroup.PageItem.PageGroup.ShapeOffset = CurrentPage->CurrentPageGroupShapeCount;
	}
}


//Existing Shape
Shape::Shape(Page& Page, int ID)
	:SetInStone(false)
{
	//Page is good
	if (&Page != nullptr)
	{
	   Initialized = true;
	   this->CurrentPage = &Page;
	   if (IsInBounds(ID) == true)
	   {
	   	LoadedShape = Page.GetShapeDataR(ID);
	   }
	   else
	   {
	   	//cout << "Shape Not Initialized ID:" << ID << endl;
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

void Shape::Init(Page& Page, int QuadID)
{
	if (&Page != nullptr)
	{
		Initialized = true;
		this->CurrentPage = &Page;
		if (QuadID != -1)
		{
			LoadedShape = Page.GetShapeDataR(QuadID);
		}
		LoadedShape.Position = { 0.0, 0.0 };
		LoadedShape.Size = { 0.5, 0.5 };
		Add_Default();
	}
};

void Shape::PrintShape()
{
	if (Initialized == false) { return; }
	CurrentPage->PrintShape(LoadedShape.ID);
}

void Shape::UpdatellMouseAccess()
{
	if (CurrentllShape->MouseAccess == true)
	{
		this->CurrentllShape->Top = (CurrentllShape->Position.y + CurrentllShape->Size[1] / 2);
		this->CurrentllShape->Bottom = (CurrentllShape->Position.y - CurrentllShape->Size[1] / 2);
		this->CurrentllShape->Left = (CurrentllShape->Position.x - CurrentllShape->Size[0] / 2);
		this->CurrentllShape->Right = (CurrentllShape->Position.x + CurrentllShape->Size[0] / 2);
	}
	else
	{
		this->CurrentllShape->Top = 3.0;
		this->CurrentllShape->Bottom = 3.0;
		this->CurrentllShape->Left = -3.0;
		this->CurrentllShape->Right = -3.0;
	}

	//this->MouseAccess = true;
	this->CurrentllShape->HighlightPosition = CurrentllShape->Position;
	this->CurrentllShape->HighlightSize = { CurrentllShape->Size[0] + 0.0032, CurrentllShape->Size[1] + 0.0066 };
	this->CurrentllShape->HighlightColor = { 0.0, 0.7156, 0.0, 1.0 };
}


void Shape::UpdateMouseAccess()
{
	if (LoadedShape.MouseAccess == true)
	{
		this->LoadedShape.Top = (LoadedShape.Position.y + LoadedShape.Size[1]/2);
		this->LoadedShape.Bottom = (LoadedShape.Position.y - LoadedShape.Size[1]/2);
		this->LoadedShape.Left = (LoadedShape.Position.x - LoadedShape.Size[0] / 2);
		this->LoadedShape.Right = (LoadedShape.Position.x + LoadedShape.Size[0] / 2);
	}
	else
	{
		this->LoadedShape.Top = 3.0;
		this->LoadedShape.Bottom = 3.0;
		this->LoadedShape.Left = -3.0;
		this->LoadedShape.Right = -3.0;
	}

	//this->MouseAccess = true;
	this->LoadedShape.HighlightPosition = LoadedShape.Position;
	this->LoadedShape.HighlightSize = { LoadedShape.Size[0] + 0.0032, LoadedShape.Size[1] + 0.0066 };
	this->LoadedShape.HighlightColor = { 0.0, 0.7156, 0.0, 1.0 };
}

void Shape::Add_Default()
{
	SetShapeRatios();
	BuildShapeVertices();
	if (CurrentPage != nullptr)
	{
		LoadedShape.Position = { 0.0, 0.0 };
		LoadedShape.Size = { 0.5, 0.5 };
		LoadedShape.Color = { 0.8, 0.8, 0.8, 0.8 };
		CurrentPage->AddShape(LoadedShape);
	}
	else
	{
		cout << "ERROR::Could not add shape. No page provided" << endl;
	}
}

void Shape::Delete()
{
	CurrentPage->DeleteShapeData(LoadedShape.ID);
}

void Shape::Add_Duplicate()
{
	SetShapeRatios();
	BuildShapeVertices();
	if (CurrentPage != nullptr)
	{
		CurrentPage->AddShape(LoadedShape);
	}
	else
	{
		cout << "ERROR::Could not add shape. No page provided" << endl;
	}
}

void Shape::Add_Insert()
{
	if (CurrentPage != nullptr && LoadedShape.ID > 0 )
	{
		CurrentPage->InsertShapeArray(LoadedShape.ID - 1, 1);
	}
	else
	{
		cout << "ERROR::Could not add shape. No page provided" << endl;
	}
}

ShapeData& Shape::Switch(int ShapeID)
{
	if (Initialized == true)
	{
		if (IsInBounds(ShapeID) == true)
		{
			LoadedShape = CurrentPage->GetShapeDataR(ShapeID);
			//LoadedShape.ShapeGroup.ShapeOffset = 0;
			//LoadedShape.ShapeGroup.ShapeCount = 0;
			return LoadedShape;
		}
		else
		{
			Log::LogString("Switch Error:: ID out of bounds");
		}
	}
	else
	{
		Log::LogString("Switch Error:: Shape Not Initialized");
	}
	return LoadedShape;
}

ShapeData& Shape::Switch(Page& Page, int ShapeID)
{
	//if (&Page != nullptr)
	//{
	//	Initialized = true;
	//	CurrentPage = &Page;
	//	if (IsInBounds(ShapeID) == false) { Log::LogString("Switch Error:: ID not in bounds"); return; }
	//	LoadedShape = CurrentPage->GetShapeDataR(ShapeID);
	//	return LoadedShape;
	//}
	//return LoadedShape;
	return LoadedShape;
}

void Shape::SetShape(ShapeData& ShapeData)
{
	this->LoadedShape = ShapeData;
	this->Update();
}

void Shape::SetShape(ShapeData& ShapeData, glm::vec2 PSConversions)
{
	this->LoadedShape = ShapeData;
	ShapeData.Position = ApplyPositionConversion(ShapeData.Position, PSConversions[0], LoadedShape.Size);
	ShapeData.Size = ApplySizeConversion(ShapeData.Size, PSConversions[1]);

	this->Update();
}
void Shape::SetPosition(glm::vec2 Position)
{
		this->LoadedShape.Position = Position;
		this->Update();
}
void Shape::SetPosition(glm::vec2 Position, glm::vec2 bools)
{
	if (bools[0] == true)
	{
		this->LoadedShape.Position[0] = Position[0];
	}
	if (bools[1] == true)
	{
		this->LoadedShape.Position[1] = Position[1];
	}
	Update();
}

void Shape::SetSize(glm::vec2 Size)
{
	this->LoadedShape.Size = Size;
	Update();
}

void Shape::SetSize(glm::vec2 Size, glm::vec2 bools)
{
	if (bools[0] == true)
	{
		this->LoadedShape.Size[0] = Size[0];
	}
	if (bools[1] == true)
	{
		this->LoadedShape.Size[1] = Size[1];
	}
	Update();
}

void Shape::SetColor(glm::vec4 Color)
{
	this->LoadedShape.Color = Color;
	Update();
}
void Shape::SetColor(glm::vec4 Color, glm::vec4 bools)
{
	if (bools[0] == true)
	{
		this->LoadedShape.Color[0] = Color[0];
	
	}
	if (bools[1] == true)
	{
		this->LoadedShape.Color[1] = Color[1];
	}
	if (bools[2] == true)
	{
		this->LoadedShape.Color[2] = Color[2];
	}
	if (bools[3] == true)
	{
		this->LoadedShape.Color[3] = Color[3];
		
	}
	Update();
}


void Shape::SetPosition(glm::vec2 Position, int Conversion)
{
	ApplyPositionConversion(Position, Conversion);

	this->LoadedShape.Position = Position;
	this->Update();
}

void Shape::SetPosition(glm::vec2 Position, glm::vec2 bools, int Conversion)
{
	Position = ApplyPositionConversion(Position, Conversion);

	if (bools[0] == true)
	{
		this->LoadedShape.Position[0] = Position[0];
	}
	if (bools[1] == true)
	{
		this->LoadedShape.Position[1] = Position[1];
	}
	Update();
}

void Shape::SetSize(glm::vec2 Size, int Conversion)
{
	this->LoadedShape.Size = ApplySizeConversion(Size, Conversion);
	Update();
}

void Shape::SetSize(glm::vec2 Size, glm::vec2 bools, int Conversion)
{
	Size = ApplySizeConversion(Size, Conversion);
	if (bools[0] == true)
	{
		this->LoadedShape.Size[0] = Size[0];
	}
	if (bools[1] == true)
	{
		this->LoadedShape.Size[1] = Size[1];
	}
	Update();
}


void Shape::OffsetPosition(glm::vec2 Position)
{
	this->LoadedShape.Position += Position;
	Update();
}
void Shape::OffsetPosition(glm::vec2 Position, glm::vec2 bools)
{
	if (bools[0] == true)
	{
		this->LoadedShape.Position[0] += Position[0];
	}
	if (bools[1] == true)
	{
		this->LoadedShape.Position[1] += Position[1];
	}

	Update();
}
void Shape::OffsetSize(glm::vec2 Size)
{
	this->LoadedShape.Size += Size;
	Update();
}
void Shape::OffsetSize(glm::vec2 Size, glm::vec2 bools)
{
	if (bools[0] == true)
	{
		this->LoadedShape.Size[0] += Size[0];
	}
	if (bools[1] == true)
	{
		this->LoadedShape.Size[1] += Size[1];
	}
	Update();
}

void Shape::OffsetColor(glm::vec4 Color)
{
	this->LoadedShape.Color += Color;
	Update();
}
void Shape::OffsetColor(glm::vec4 Color, glm::vec4 bools)
{
	if (bools[0] == true)
	{
		this->LoadedShape.Color[0] += Color[0];

	}
	if (bools[1] == true)
	{
		this->LoadedShape.Color[1] += Color[1];
	}
	if (bools[2] == true)
	{
		this->LoadedShape.Color[2] += Color[2];
	}
	if (bools[3] == true)
	{
		this->LoadedShape.Color[3] += Color[3];
	}
	Update();
}

///////////////////////////////////////////////////////////////

void Shape::OffsetPosition(glm::vec2 OffsetPosition, int Conversion)
{
	OffsetPosition = ApplySizeConversion(OffsetPosition, Conversion);

	this->LoadedShape.Position += OffsetPosition;
	Update();
}
void Shape::OffsetPosition(glm::vec2 OffsetPosition, glm::vec2 bools, int Conversion)
{
	OffsetPosition = ApplySizeConversion(OffsetPosition, Conversion);

	if (bools[0] == true)
	{
		this->LoadedShape.Position[0] += OffsetPosition[0];
	}
	if (bools[1] == true)
	{
		this->LoadedShape.Position[1] += OffsetPosition[1];
	}
	Update();
}
void Shape::OffsetSize(glm::vec2 Size, int Conversion)
{
	Size = ApplySizeConversion(Size, Conversion);
	this->LoadedShape.Size += Size;
	Update();
}
void Shape::OffsetSize(glm::vec2 Size, glm::vec2 bools, int Conversion)
{
	Size = ApplySizeConversion(Size, Conversion);

	if (bools[0] == true)
	{
		this->LoadedShape.Size[0] += Size[0];
	}
	if (bools[1] == true)
	{
		this->LoadedShape.Size[1] += Size[1];
	}
	Update();
}


////////////////////////////////////////////VERTEX FUNCTIONS//////////////////////////////////////////////////

//Set Functions
void Shape::SetVertexPosition(int Index, glm::vec2& Position)
{ 	this->LoadedShape.Vertex[Index].Position = Position; };

void Shape::SetVertexColor(int Index, glm::vec4& Color)
{ this->LoadedShape.Vertex[Index].Color = Color; };

void Shape::SetVertexTexCoords(int Index, glm::vec2& TextureCoordinates)
{ this->LoadedShape.Vertex[Index].TexCoords = TextureCoordinates; };

void Shape::SetVertexGuiAction(int Index, int& Action)
{ this->LoadedShape.Vertex[Index].GUIAction = Action; };

void Shape::SetVertexCentralPoint(int Index, glm::vec2& CentralPoint)
{ this->LoadedShape.Vertex[Index].CentralPoint = CentralPoint; };

void Shape::SetVertexTextureIndex(int Index, float& TextureIndex)
{ this->LoadedShape.Vertex[Index].TexIndex = TextureIndex; };



//Offset Functions
void Shape::OffsetVertexPosition(int Index, glm::vec2& Position)
{ this->LoadedShape.Vertex[Index].Position += Position; };

void Shape::OffsetVertexColor(int Index, glm::vec4& Color)
{ this->LoadedShape.Vertex[Index].Color += Color; };

void Shape::OffsetVertexTexCoords(int Index, glm::vec2& TextureCoordinates)
{ this->LoadedShape.Vertex[Index].TexCoords += TextureCoordinates; };

void Shape::OffsetVertexGuiAction(int Index, int& Action)
{ this->LoadedShape.Vertex[Index].GUIAction += Action; };

void Shape::OffsetVertexCentralPoint(int Index, glm::vec2& CentralPoint)
{ this->LoadedShape.Vertex[Index].CentralPoint += CentralPoint; };

void Shape::OffsetVertexTextureIndex(int Index, float& TextureIndex)
{ this->LoadedShape.Vertex[Index].TexIndex += TextureIndex; };


//Shape* Shape::ShapeDataPosToMousePos(Shape* Shape, glm::vec2 MousePosition, bool Centered)
//{
//	if (Centered == true)
//	{
//		MousePosition[0] -= LoadedShape.Size[0] / 2;
//		MousePosition[1] += LoadedShape.Size[1] / 2;
//	}
//	LoadedShape.Position = MousePosition;
//	return Shape;
//}

