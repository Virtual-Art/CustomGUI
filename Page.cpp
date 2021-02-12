#include "Page.h"

//ShapeData* Page::ShapeDataPointer;
//Vertex* Page::VertexPointer;
//uint32_t* Page::IndexPointer;

GLuint Page::WhiteTexture;
//int Page::TotalShapeDataCount;
//int Page::TotalIndexCount;
int Page::PageCount = 0;

//MakeShapeContainer(NumberOfShapeDatas)
Page::Page(int NumberOfShapeDatas)
	:IndexContainer(MakeIndexContainer(NumberOfShapeDatas)), ShapeContainer(MakeShapeContainer(NumberOfShapeDatas)), VertexContainer(MakeVertexContainer(NumberOfShapeDatas))
{
	//cout << "PAGE CREATED" << endl;
	this->MaxShapeDataCount = NumberOfShapeDatas;
	this->MaxIndexCount = 6 * NumberOfShapeDatas;
	this->MaxVertexCount = 4 * NumberOfShapeDatas;
	this->PageShapeCount = 0;
	this->PageIndexCount = 0;
	//this->TotalShapeDataCount = 0;
	//this->TotalIndexCount = 0;
	this->MaxPageSize = NumberOfShapeDatas * sizeof(ShapeData);
	this->VA = 0;
	this->VB = 0;
	this->IB = 0;
	this->Name = "Enter Name";

	this->CurrentLayerCount = 1;
	this->CurrentLayer = 1;
	this->LastShapeDataHovered = 0;
	//cout << "DrawCircles init: " << DrawingCircles << endl;
    //	this->DrawCircle = DrawingCircles;
	//cout << DrawCircle << endl;
	this->PageID = PageCount;
	PageCount++;
	this->EMouseControl = false;
	this->GMouseControl = false;
	this->ClipBoard = ShapeZero;

}

Page::Page()
	:IndexContainer(MakeIndexContainer(2000)), ShapeContainer(MakeShapeContainer(2000)), VertexContainer(MakeVertexContainer(2000)), DrawCircle{ false }
{

	//cout << "PAGE CREATED" << endl;
	this->MaxShapeDataCount = 2000;
	this->MaxIndexCount = 12000;
	this->MaxVertexCount = 8000;
	this->PageShapeCount = 0;
	this->PageIndexCount = 0;
	//this->TotalShapeDataCount = 0;
	//this->TotalIndexCount = 0;
	this->MaxPageSize = 2000 * sizeof(ShapeData);
	this->VA = 0;
	this->VB = 0;
	this->IB = 0;

	this->Name = "Enter Name";
	this->CurrentLayerCount = 1;
	this->CurrentLayer = 1;
	this->LastShapeDataHovered = 0;
	this->PageID = PageCount;
	PageCount++;
	this->EMouseControl = false;
	this->GMouseControl = false;
	this->ClipBoard = ShapeZero;
}

void Page::Init(ShaderProgram ShaderProgram)
{
	//cout << "Page ShapeData Count:" << this->MaxShapeDataCount << endl;
	//cout << "Page Index Count:" << this->MaxIndexCount << endl;
	//cout << "Page Vertex Count:" << this->MaxVertexCount << endl;
	
	glGenVertexArrays(1, &this->VA);
	glBindVertexArray(this->VA);

	glGenBuffers(1, &this->VB);
	glBindBuffer(GL_ARRAY_BUFFER, this->VB);
	glBufferData(GL_ARRAY_BUFFER, MaxVertexCount * sizeof(ShapeVertex), nullptr, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const void*)offsetof(ShapeVertex, Position));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const void*)offsetof(ShapeVertex, TexCoords));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const void*)offsetof(ShapeVertex, Color));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const void*)offsetof(ShapeVertex, TexIndex));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const void*)offsetof(ShapeVertex, CentralPoint));
    glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const void*)offsetof(ShapeVertex, GUIAction));

	GLsizeiptr LastSize = 0;
	uint32_t offset = 0;

	if (DrawCircle != true)
	{
		for (int i = 0; i < MaxIndexCount; i += 6)
		{
			this->IndexContainer.Add(0 + offset);   //0
			this->IndexContainer.Add(2 + offset);	//1
			this->IndexContainer.Add(1 + offset);	//2
			this->IndexContainer.Add(3 + offset);	//0
			this->IndexContainer.Add(2 + offset);	//2
			this->IndexContainer.Add(0 + offset);   //3

			PageIndexCount += 6;
			//2, 0, 3, 3, 0, 1
			offset += 4;
			//cout << "Pass through 1" << endl;
		}
	}
	else
	{

		int Spot1 = 0;
		int Spot2 = 0;
		int Spot3 = 0;


			int TotalCirclePoints = 13;
			for (int i = 0; i < TotalCirclePoints - 1; i++)
			{
				if (i == TotalCirclePoints - 2)
				{
					Spot1 = 1;
					Spot3 = 1 + i;
					Spot2 = 0;
				}
				else
				{
					Spot1 = 0;
					Spot2 = 1 + i;
					Spot3 = 2 + i;
				}


				this->IndexContainer.Add(Spot1);
				this->IndexContainer.Add(Spot2);
				this->IndexContainer.Add(Spot3);

				PageIndexCount += 3;
			}
		
	}
	
	glGenBuffers(1, &this->IB);
	glBindBuffer(GL_Element_ARRAY_BUFFER, this->IB);
	glBufferData(GL_Element_ARRAY_BUFFER, IndexContainer.CurrentSize +2, IndexContainer.StartOfContainer, GL_STATIC_DRAW);

	glGenTextures(1, &this->WhiteTexture);
	glBindTexture(GL_TEXTURE_2D, this->WhiteTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	GLubyte Pixels[4] = { 255, 255, 255, 255 };
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &Pixels);
	glGenerateMipmap(GL_TEXTURE_2D);

	for (size_t i = 1; i < MaxTextures; i++)
	{
		this->TextureSlots[i] = 0;
	}
	
	this->TextureSlots[0] = this->WhiteTexture;
	this->TextureSlots[1] = this->WhiteTexture;
	this->TextureSlots[2] = this->WhiteTexture;//WhiteTexture is just the texture ID of image 1 (white)
	
	//this->TextureSlots[1] = RawTexture.GetTextureID();
	glUseProgram(ShaderProgram.ID);
	////this code basically converts our textureslot to an actual number we can reference in the shader 
	//ShaderProgram.LoadSample0();
	//ShaderProgram.LoadSample1();
	//ShaderProgram.LoadSample2();
	ShaderProgram.LoadAllSamples();
	glUseProgram(0);

}

void Page::LoadThisPage()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->VB);
	glBufferSubData(GL_ARRAY_BUFFER, 0, this->VertexContainer.MaxSize, this->VertexContainer.StartOfContainer); //
}


void Page::IncreaseShapeDataCount()
{
	this->PageShapeCount++;
}


void Page::DeletePage()
{
	ShapeContainer.ManualContainerDelete();
	VertexContainer.ManualContainerDelete();
	IndexContainer.ManualContainerDelete();
}

//RadiusPercentage = 1.0;; == Circle || Pill
void Page::AddCircle(glm::vec2 Position, glm::vec2 Size, float RadiusPercentage)
{
	//float AspectRatio = 2;
	//Size = 2 * Radius - Size[i]

	float Radiusx = Size[0]/2 * RadiusPercentage;
	float Radiusy = Size[1]/2 * RadiusPercentage;
	float Radius;

	if (Radiusx <= Radiusy)
	{
		Radius = Radiusx;
	}
	else
	{
		Radius = Radiusy;
	}

	float PartWidth = Size[0] - (2 * Radius);
	float PartLength = Size[1] - (2 * Radius);

	cout << "TWO " << PartWidth << PartLength << endl;

	glm::vec2 LoopClose{0.0, 0.0};

	//CreateCircleIndices
	Maths Maths;
	Vertex CircleVertex;
	float ColorCounter = 4;

	CircleVertex.Color = { 0.0, 1.0, 0.0, 1.0 };
	CircleVertex.TexCoords = { 0.0, 0.0 };
	CircleVertex.TexIndex = 0;
	CircleVertex.CentralPoint = {Position[0], Position[1]};
	CircleVertex.GUIAction = 0.0;
	glm::vec4 CircleColor = {1.0, 1.0, 1.0, 1.0};

	//Main Point
	CircleVertex.Position = {Position[0], Position[1]};
	CircleVertex.Color = {1.0, 1.0, 1.0, 1.0};
	//this->VertexContainer.Add(CircleVertex);

	//Circumference
	for (int i = 0; i < 12; i++)
	{
		
		float xPos = (Maths.cosOscillation(i, -Radius, (2 * PI) / 12, 0)) / 2;
		float yPos = Maths.sinOscillation(i, -Radius, (2 * PI) / 12, 0);

		//HOW THIS WORKS
		//First decides the vertex position based on the origin being 0.0
		//then translated to its proper position before being passed into the array

		// Right
		if (xPos > 0)
		{
			//Top
			if (yPos > 0)
			{
				xPos += PartWidth;
				yPos += PartLength;
			}
			//Bottom
			if (yPos < 0)
			{
				xPos += PartWidth;
				yPos -= PartLength;
			}
		}
		
		// Left
		if (xPos < 0)
		{
			////Top
			if (yPos > 0)
			{
			   xPos -= PartWidth;
			   yPos += PartLength;
			}
			// Bottom
			if (yPos < 0)
			{
			   xPos -= PartWidth;
			   yPos -= PartLength;
			}
		}

		if (i == 0)
		{
			xPos -= PartWidth;
			yPos = 0;
			LoopClose = {xPos, yPos};
		}
		if (i == 999)
		{
			xPos = LoopClose[0];
			yPos = LoopClose[1];
		}

		
		if (i == 0)  { CircleColor = { 1.0, 0.0, 0.0, 0.7 }; }
		if (i == 1)  { CircleColor = { 1.0, 0.0, 0.5, 0.7 }; }
		if (i == 2)  { CircleColor = { 1.0, 0.0, 1.0, 0.7 }; }
		if (i == 3)  { CircleColor = { 0.5, 0.0, 1.0, 0.7 }; }
		if (i == 4)  { CircleColor = { 0.0, 0.0, 1.0, 0.7 }; }
		if (i == 5)  { CircleColor = { 0.0, 0.5, 1.0, 0.7 }; }
		if (i == 6)  { CircleColor = { 0.0, 1.0, 1.0, 0.7 }; }
		if (i == 7)  { CircleColor = { 0.0, 1.0, 0.5, 0.7 }; }
		if (i == 8)  { CircleColor = { 0.0, 1.0, 0.0, 0.7 }; }
		if (i == 9)  { CircleColor = { 0.5, 1.0, 0.0, 0.7 }; }
		if (i == 10) { CircleColor = { 1.0, 1.0, 0.0, 0.7 }; }
		if (i == 11) { CircleColor = { 1.0, 0.5, 0.0, 0.7 }; }

		CircleVertex.Color = CircleColor;
		CircleVertex.Position = {xPos + Position[0], yPos + Position[1] };
		//this->VertexContainer.Add(CircleVertex);
		LoadThisPage();
	}
}

//if the position data is on center, flip Centered to true,
//if the position data is based on top left, flip Centered to false
//int Page::AddShapeDataGrid(Grid& Grid)
//{
//	int ID = Amount();
//	ShapeData Buffer;
//	Maths Maths;
//	if (Grid.Centered == true)
//	{
//		Grid.Position = Maths.CenterToTopLeft(Grid.Position, Grid.Size);
//	}
//
//
//	//Load ShapeData With it's Details
//	Buffer.PartOfGroup = true;
//	Buffer.GroupStart = ShapeContainer.CurrentContainerAmount;
//	Buffer.GroupCount = Grid.XYShapeDatasPerRow[0] * Grid.XYShapeDatasPerRow[1];
//
//	Buffer.ShapeGroupPosition = Grid.Position;
//	Buffer.ShapeGroupSize = Grid.Size;
//	Buffer.GridXYShapePerRow = Grid.XYShapeDatasPerRow;
//	Buffer.GridShapeSize = Grid.ShapeDataSize;
//	Buffer.ShapeGroupColor = Grid.Color;
//	Buffer.GridCentered = Grid.Centered;
//	Buffer.MouseAccess = Grid.MouseAccess;
//
//	Buffer.GroupStart = ShapeContainer.CurrentContainerAmount;
//	Buffer.ShapeDataType = TYPE_GRID;
//	//ShapeData to load 
//	
//
//	//Set Grid
//	for (int xShapeDatas = 0; xShapeDatas < Grid.XYShapeDatasPerRow[1]; xShapeDatas++)
//	{
//		for (int yShapeDatas = 0; yShapeDatas < Grid.XYShapeDatasPerRow[0]; yShapeDatas++)
//		{
//			//Load Basic data in all ShapeDatas
//			Buffer.Size = Maths.GridShapeSize(Grid.Size, Grid.XYShapeDatasPerRow, Grid.ShapeDataSize);
//			Buffer.Position = Maths.GridShapeDataPosition(Grid.Position, Grid.Size, Grid.XYShapeDatasPerRow, { yShapeDatas ,  xShapeDatas }, Grid.Centered);
//			Buffer.Color = glm::vec4(Grid.Color);
//			Buffer.GroupOffset = ShapeContainer.CurrentContainerAmount - Buffer.GroupStart;//Layer[CurrentLayer].GetGridOffset();
//			AddShapeData(Buffer, true, true);
//		}
//	}
//	return ID;
//}


//Replacing the entire grid everthing
//only for changing group characteristics
//void Page::ReplaceShapeDataGrid(Grid& NewGrid)
//{
//	    ShapeData Buffer;
//		Maths Maths;
//		int IDOffset = 1 + NewGrid.Highlighted;
//		int ShapeDataDifference = 0;
//
//		if (NewGrid.Centered == true)
//		{
//			NewGrid.Position = Maths.CenterToTopLeft(NewGrid.Position, NewGrid.Size);
//		}
//	
//		ShapeData* OldShapeData = GetShapeData(NewGrid.Start);
//		if (OldShapeData == nullptr) { cout << "ReplaceShapeDataGrid::ERROR::ShapeDataNULL " << endl; return; };
//		int GridInterval = OldShapeData->GroupStart + NewGrid.Highlighted; // Hilighted will be 1 or 0;
//		Buffer.GroupStart = OldShapeData->GroupStart;
//
//
//		////NewSize is bigger than the old size
//		//if (OldShapeData->GroupCount < NewGrid.Count && OldShapeData->GroupCount != NewGrid.Count)
//		//{
//		//	//insert diff
//		//	cout << "INSERT" << endl;
//		//	ShapeDataDifference = NewGrid.Count - OldShapeData->GroupCount;
//		//	InsertShapeData(OldShapeData->GroupStart + OldShapeData->GroupCount, ShapeDataDifference, Zero1, true);
//		//	OldShapeData->GroupCount = NewGrid.Count;
//		//}
//		//
//		////NewSize is smaller than the old size
//		//if (OldShapeData->GroupCount > NewGrid.Count && OldShapeData->GroupCount != NewGrid.Count)
//		//{
//		//	//deletediff
//		//	cout << "DELETE" << endl;
//		//	cout << OldShapeData->GroupCount << " " <<  NewGrid.Count << endl;
//		//	ShapeDataDifference = OldShapeData->GroupCount - NewGrid.Count;
//		//	cout << "ShapeDataDifference" << ShapeDataDifference << endl;
//	    //    DeleteShapeDataArray(OldShapeData->GroupStart, ShapeDataDifference);
//		//	OldShapeData->GroupCount = NewGrid.Count;
//		//}
//
//
//
//		////Load Group Details to each ShapeData
//
//		//Group Details
//		Buffer.GroupCount = NewGrid.Count;
//		Buffer.PartOfGroup = true;
//		Buffer.GroupCount = NewGrid.XYShapeDatasPerRow[0] * NewGrid.XYShapeDatasPerRow[1];
//
//		//GridDetails
//		Buffer.ShapeGroupPosition = NewGrid.Position;
//		Buffer.ShapeGroupSize = NewGrid.Size;
//		Buffer.GridXYShapePerRow = NewGrid.XYShapeDatasPerRow;
//		Buffer.GridShapeSize = NewGrid.ShapeDataSize;
//		Buffer.ShapeGroupColor = NewGrid.Color;
//		Buffer.GridCentered = NewGrid.Centered;
//		Buffer.MouseAccess = NewGrid.MouseAccess;
//		Buffer.ShapeDataType = TYPE_GRID;
//
//		//ShapeData to load 
//		for (int yShapeDatas = 0; yShapeDatas < NewGrid.XYShapeDatasPerRow[0]; yShapeDatas++)
//		{
//			for (int xShapeDatas = 0; xShapeDatas < NewGrid.XYShapeDatasPerRow[1]; xShapeDatas++)
//			{
//				//Load Basic data in all ShapeDatas
//				Buffer.Size = Maths.GridShapeSize(NewGrid.Size, NewGrid.XYShapeDatasPerRow, NewGrid.ShapeDataSize);
//				Buffer.Position = Maths.GridShapeDataPosition(NewGrid.Position, NewGrid.Size, NewGrid.XYShapeDatasPerRow, { yShapeDatas ,  xShapeDatas }, NewGrid.Centered);
//				Buffer.Color = glm::vec4(NewGrid.Color);
//				Buffer.GroupOffset = GridInterval;                          
//				//ReplaceShapeData(GridInterval, Buffer, true, true);
//				GridInterval += IDOffset;
//			}
//		}
//}

//This function deletes an ShapeData at any spot 
void Page::DeleteShapeArray(int Spot, int Amount)
{
	std::cout << "(" << Amount << ") Shapes Deleted at Spot: " << Spot  << endl;
	//for (int i = Spot; i < Spot + Amount; i++)
	//{
		//Deletes an ShapeData
		ShapeContainer.DeleteStripNEW(Spot, Amount, ShapeZero);
	
		//deletes the ShapeData's vertices
		VertexContainer.DeleteStripNEW(Spot * 4, Amount * 4, VertexZero);
	
//		cout << "ShapeData " << i << " Deleted" << endl;
//	}
}

void Page::DeleteShapeDataGrid(int Layers, int GridSpot, int ShapeGroupSize)
{
	//Deletes an ShapeData
	ShapeContainer.DeleteStripNEW(GridSpot, ShapeGroupSize, ShapeZero);

	//deletes the ShapeData's vertices
	//VertexContainer.DeleteStripNEW(GridSpot * 4, ShapeGroupSize * 4, Zero2);

	//Update all layers above
	//UpdateLayers(Layers, -1);
}

void Page::DeleteShapeData(int Spot)
{
	if (Spot == -1) { cout << "Failed to delete" << endl; return;};
	ShapeContainer.DeleteStripNEW(Spot, 1, ShapeZero);
	VertexContainer.DeleteStripNEW(Spot * 4, 4, VertexZero);
	cout << "ShapeData " << Spot << " Deleted" << endl;
}

//This function
void AddShapeDataNEW()
{
	//
}

//This function inserts an ShapeData in a specified spot
void Page::InsertShapeArray(int Spot, int Amount)
{
	//Log
	std::cout << "(" << Amount << ") Shapes Inserted at Spot: " << Spot << endl;

	//Insert
    ShapeContainer.InsertStripNEW(Spot, Amount, ShapeZero);
    VertexContainer.InsertStripNEW(Spot * 4, Amount * 4, VertexZero);

}



////This function copies a specified ShapeData to the space
//int Page::CopyShapeData(int Spot)
//{
//	int ID = Amount();
//	Maths Maths;
//	Vertex Vertex;
//
//
//	ShapeData* Buffer = GetShapeData(Spot);
//	if (Buffer == nullptr) { cout << "Failed to Copy" << endl; return -1; };
//
//	ClipBoard = *Buffer;
//	ClipBoard.Position[0] += 0.02;
//	ClipBoard.Position[1] -= 0.02;
//	ClipBoard.ID = ID;
//
//	//ShapeDataCopied->ID = Layer[Layers].GetShapeDataFillPosition();
//	//Layer[CurrentLayer].ShapeDataCount++;
//
//	//Adds ShapeData where the space is
//	ShapeContainer.Add(ClipBoard);
//
//	Vertex = Maths.SetTopRight(ClipBoard, Vertex);    //#0 TopRight
//	VertexContainer.Add(Vertex);
//
//	Vertex = Maths.SetBottomRight(ClipBoard, Vertex); //#1 BottomRight
//	VertexContainer.Add(Vertex);
//
//	Vertex = Maths.SetBottomLeft(ClipBoard, Vertex);  //#2 BottomLeft
//	VertexContainer.Add(Vertex);
//
//	Vertex = Maths.SetTopLeft(ClipBoard, Vertex);     //#3 TopLeft
//	VertexContainer.Add(Vertex);
//	return ID;
//}
//
//void Page::SetClipBoard(int Spot)
//{
//	ShapeData* Buffer = GetShapeData(Spot);
//	if (Buffer == nullptr) { cout << "ClipBoard Not set" << endl; return; };
//	this->ClipBoard = *Buffer;
//}
//
//int Page::ShapeDataMultiCopy(MouseManager Mouse)
//{
//	int ID = Amount();
//	Maths Maths;
//	Vertex Vertex;
//
//	ClipBoard.Position = Maths.CenterToTopLeft({ Mouse.xPos, Mouse.yPos }, ClipBoard.Size);
//
//	//ShapeDataCopied->ID = Layer[Layers].GetShapeDataFillPosition();
//	//Layer[CurrentLayer].ShapeDataCount++;
//
//	//Adds ShapeData where the space is
//	ShapeContainer.Add(ClipBoard);
//
//	Vertex = Maths.SetTopRight(ClipBoard, Vertex);    //#0 TopRight
//	VertexContainer.Add(Vertex);
//
//	Vertex = Maths.SetBottomRight(ClipBoard, Vertex); //#1 BottomRight
//	VertexContainer.Add(Vertex);
//
//	Vertex = Maths.SetBottomLeft(ClipBoard, Vertex);  //#2 BottomLeft
//	VertexContainer.Add(Vertex);
//
//	Vertex = Maths.SetTopLeft(ClipBoard, Vertex);     //#3 TopLeft
//	VertexContainer.Add(Vertex);
//	return ID;
//}

//TextBox
//void Page::AddCharacter(ShapeData& ShapeData, Character Character, bool Centered)
//{
//	FontMath Font;
//	FontVertex TempVertex;
//	Vertex Vertex;
//
//	if (Centered == true)
//	{
//		ShapeData.Position[0] -= ShapeData.Size[0] / 2;
//		ShapeData.Position[1] += ShapeData.Size[1] / 2;
//	}
//
//	ShapeData.ID = ShapeContainer.CurrentContainerAmount;
//	//ShapeData.UpdateSize(ShapeData.Size, MouseAccess);
//
//	Layer[CurrentLayer].ShapeDataCount++;
//
//	UpdateLayers(CurrentLayer, 1);
//
//	//Adds ShapeData where the space is
//	ShapeContainer.Add(ShapeData);
//
//	//Load Character Vertices
//	TempVertex = Font.SetTopRight(ShapeData, Character, TempVertex);  //#0 TopRight
//	VertexContainer.Add(TempToVertex(TempVertex));
//
//	TempVertex = Font.SetBottomRight(ShapeData, Character, TempVertex); //#1 BottomRight
//	VertexContainer.Add(TempToVertex(TempVertex));
//
//	TempVertex = Font.SetBottomLeft(ShapeData, Character, TempVertex); //#2 BottomLeft
//	VertexContainer.Add(TempToVertex(TempVertex));
//
//	TempVertex = Font.SetTopLeft(ShapeData, Character, TempVertex);  //#3 TopLeft
//	VertexContainer.Add(TempToVertex(TempVertex));
//
//}

//Vertex Page::TempToVertex(FontVertex& FontVertex)
//{
//	Vertex Vertex;
//	Vertex.Position = FontVertex.Position;
//	Vertex.TexCoords = FontVertex.TexCoords;
//	Vertex.Color = FontVertex.Color;
//	Vertex.TexIndex = FontVertex.TexIndex;
//	Vertex.CentralPoint = FontVertex.CentralPoint;
//	Vertex.GUIAction = FontVertex.GUIAction;
//	return Vertex;
//}	


//NOTE: when you are done using 600x1200 as resolution change specs to System.Height/width
//int Page::AddTextBox(TextSpecification TextSpecs)
//{
//	int ID = ShapeAmount();
//	cout << "NextLine Spacing " << TextSpecs.LineSpacing << endl;
//	ShapeData CharShapeData;
//	FontMath Font;
//	int SCR_HEIGHT = 600;
//	int SCR_WIDTH = 1200;
//
//	bool LineRestart = true;
//	float Maxline;
//
//	CharShapeData.MouseAccess = TextSpecs.MouseAccess;
//	CharShapeData.PartOfGroup = true;
//	CharShapeData.ShapeGroupStart = ShapeContainer.CurrentContainerAmount;
//	CharShapeData.ShapeGroupCount = TextSpecs.Count;
//	CharShapeData.Text = TextSpecs.Text;
//	CharShapeData.ShapeGroupPosition = TextSpecs.Position;
//	//CharShapeData.ShapeDataType = TYPE_TEXT;
//
//	const char* FullTextString = TextSpecs.Text.c_str();
//	glm::vec2 StartPosition;
//	if (TextSpecs.Centered == true)
//	{
//		TextSpecs.CursorPosition = { TextSpecs.Position[0] - (TextSpecs.Size[0] / 2), TextSpecs.Position[1] + (TextSpecs.Size[1] / 2) };
//		StartPosition = TextSpecs.CursorPosition;
//		Maxline = (TextSpecs.Position[0] + (TextSpecs.Size[0] / 2));
//	}
//	else
//	{
//		TextSpecs.CursorPosition = TextSpecs.Position;
//		StartPosition = TextSpecs.CursorPosition;
//		Maxline = (TextSpecs.Position[0] + TextSpecs.Size[0]);
//	}
//
//
//
//	//Text Loop
//	for (int n = 0; n < TextSpecs.Text.size(); n++)
//	{
//		//Retreives Character information from file
//		Character Char(TextSpecs.FontFile, TextSpecs.Text[n]);
//
//		CharShapeData.Position = Font.GetCharacterPosition(Char, TextSpecs.CursorPosition, TextSpecs.FontSize, LineRestart);
//		CharShapeData.Size = Font.GetCharacterSize(Char, CharShapeData.Position, SCR_HEIGHT, SCR_WIDTH, TextSpecs.FontSize);
//		CharShapeData.Color = TextSpecs.Color;
//		CharShapeData.ActiveTexture = TextSpecs.FontSlot;
//		CharShapeData.ShapeGroupOffset = ShapeContainer.CurrentContainerAmount - CharShapeData.ShapeGroupStart;
//		//AddCharacter(CharShapeData, Char, false);
//
//		////Checks if line needs to be returned 
//		LineRestart = QueryLineRestart(TextSpecs.CursorPosition, Maxline);
//		
//		TextSpecs.CursorPosition = Font.AdvanceCursor(Char, TextSpecs.FontSize, TextSpecs.CursorPosition, TextSpecs.CharSpacing);
//
//		LineRestart = QueryLineRestart(TextSpecs.CursorPosition, Maxline);
//		if (TextSpecs.List == false)
//		{
//			if (LineRestart == true)
//			{   ////Move CursorPosition to the next line
//				TextSpecs.CursorPosition = Font.NextLine(StartPosition, Char, TextSpecs.CursorPosition, TextSpecs.FontSize, TextSpecs.CharSpacing, TextSpecs.Position[0]);
//			}
//		}
//		else
//		{
//		    //Next Line if Space
//	
//			if (FullTextString[n - 1] == ' ' && FullTextString[n] == ' ' && FullTextString[n + 1] != ' ')
//			{   ////Move CursorPosition to the next line
//				TextSpecs.CursorPosition = Font.NextLine(StartPosition, Char, TextSpecs.CursorPosition, TextSpecs.FontSize, TextSpecs.LineSpacing,  TextSpecs.Position[0]);
//			}
//		}
//	}
//	return ID;
//}
//
////Similar to replace grid
//void Page::ReplaceTextBox(TextSpecification NewTextSpecs)
//{
//	ShapeData CharShapeData;
//	FontMath Font;
//	int SCR_HEIGHT = 600;
//	int SCR_WIDTH = 1200;
//
//	float Maxline;
//	int ShapeDataDifference;
//	bool LineRestart = true;
//	glm::vec2 StartPosition;
//
//	ShapeData* OldShapeData = GetShapeDataP(NewTextSpecs.Start);
//	int GridInterval = OldShapeData->ShapeGroupStart;
//	CharShapeData.PartOfGroup = true;
//	CharShapeData.ShapeGroupStart = OldShapeData->ShapeGroupStart;
//	CharShapeData.Text = NewTextSpecs.Text;
//	CharShapeData.Position = NewTextSpecs.Position;
//	//CharShapeData.ShapeDataType = TYPE_TEXT;
//
//	if (NewTextSpecs.Centered == true)
//	{
//		NewTextSpecs.CursorPosition = { NewTextSpecs.Position[0] - (NewTextSpecs.Size[0] / 2), NewTextSpecs.Position[1] + (NewTextSpecs.Size[1] / 2) };
//		StartPosition = NewTextSpecs.CursorPosition;
//		Maxline = (NewTextSpecs.Position[0] + (NewTextSpecs.Size[0] / 2));
//	}
//	else
//	{
//		NewTextSpecs.CursorPosition = NewTextSpecs.Position;
//		StartPosition = NewTextSpecs.CursorPosition;
//		Maxline = (NewTextSpecs.Position[0] + NewTextSpecs.Size[0]);
//	}
//
//	////NewSize is bigger than the old size
//	//if (OldShapeData->GroupCount < NewTextSpecs.Count && OldShapeData->GroupCount != NewTextSpecs.Count)
//	//{
//	//	//insert diff
//	//	ShapeDataDifference = NewTextSpecs.Count - OldShapeData->GroupCount;
//	//	InsertShapeData(OldShapeData->GroupStart + OldShapeData->GroupCount, ShapeDataDifference, Zero1, true);
//	//	OldShapeData->GroupCount = NewTextSpecs.Count;
//	//}
//	//
//	////NewSize is smaller than the old size
//	//if (OldShapeData->GroupCount > NewTextSpecs.Count && OldShapeData->GroupCount != NewTextSpecs.Count)
//	//{
//	//	//deletediff
//	//	ShapeDataDifference = OldShapeData->GroupCount - NewTextSpecs.Count;
//	//	DeleteShapeData(OldShapeData->GroupStart + OldShapeData->GroupCount, ShapeDataDifference);
//	//	OldShapeData->GroupCount = NewTextSpecs.Count;
//	//}
//
//	//Text Loop
//	for (int n = 0; n < NewTextSpecs.Count; n++)
//	{
//		//Retreives Character information from file
//		Character Char(NewTextSpecs.FontFile, NewTextSpecs.Text[n]);
//
//		CharShapeData.Position = Font.GetCharacterPosition(Char, NewTextSpecs.CursorPosition, NewTextSpecs.FontSize, LineRestart);
//		CharShapeData.Size = Font.GetCharacterSize(Char, CharShapeData.Position, SCR_HEIGHT, SCR_WIDTH, NewTextSpecs.FontSize);
//		CharShapeData.Color = NewTextSpecs.Color;
//		CharShapeData.ActiveTexture = NewTextSpecs.FontSlot;
//		CharShapeData.ShapeGroupOffset = GridInterval;
//		//ReplaceCharacter(GridInterval, CharShapeData, Char, false);
//		LoadThisPage();
//
//		//cout << "Grid Interval" << GridInterval << endl;
//		////Checks if line needs to be returned 
//
//		NewTextSpecs.CursorPosition = Font.AdvanceCursor(Char, NewTextSpecs.FontSize, NewTextSpecs.CursorPosition, NewTextSpecs.CharSpacing);
//
//		LineRestart = QueryLineRestart(NewTextSpecs.CursorPosition, Maxline);
//
//		if (LineRestart == true)
//		{   ////Move CursorPosition to the next line
//			NewTextSpecs.CursorPosition = Font.NextLine(StartPosition, Char, NewTextSpecs.CursorPosition, NewTextSpecs.FontSize, NewTextSpecs.LineSpacing, NewTextSpecs.Position[0]);
//		}
//
//		GridInterval++;
//	}
//}
//
//Character ShapeData Fabricated here
//void Page::ReplaceCharacter(int Spot, ShapeData& NewShapeData, Character Character, bool Centered)
//{
//	FontMath Font;
//	FontVertex TempVertex;
//	Vertex Vertex;
//
//	if (Centered == true)
//	{
//		NewShapeData.Position[0] -= NewShapeData.Size[0] / 2;
//		NewShapeData.Position[1] += NewShapeData.Size[1] / 2;
//	}
//
//	//cout << "Replaced" << Spot << endl;
//
//	//Adds ShapeData where the space is
//	ShapeContainer.Replace(Spot, NewShapeData);
//
//	//Load Character Vertices
//	TempVertex = Font.SetTopRight(NewShapeData, Character, TempVertex);  //#0 TopRight
//	VertexContainer.Replace(Spot * 4, TempToVertex(TempVertex));
//
//	TempVertex = Font.SetBottomRight(NewShapeData, Character, TempVertex); //#1 BottomRight
//	VertexContainer.Replace(Spot * 4 + 1, TempToVertex(TempVertex));
//
//	TempVertex = Font.SetBottomLeft(NewShapeData, Character, TempVertex); //#2 BottomLeft
//	VertexContainer.Replace(Spot * 4 + 2, TempToVertex(TempVertex));
//
//	TempVertex = Font.SetTopLeft(NewShapeData, Character, TempVertex);  //#3 TopLeft
//	VertexContainer.Replace(Spot * 4 + 3, TempToVertex(TempVertex));
//}

bool Page::QueryLineRestart(glm::vec2 CursorPosition, float MaxLine)
{
	//float Max = xPos + 10;
	if (CursorPosition[0] > MaxLine)
	{
		return true;
	}
	else
	{
		return false;
	}

}

//int Page::AddShapeData(ShapeData& ShapeData, bool Centered, bool InsideGrid)
//{
//	int ID = Amount();
//	Maths Maths;
//	Vertex Vertex;
//	if (ShapeData.ShapeDataType == TYPE_ShapeData)
//	{
//		ShapeData.ShapeDataType = TYPE_ShapeData;
//	}
//
//	if (Centered == true)
//	{
//		ShapeData.Position[0] -= ShapeData.Size[0] / 2;
//		ShapeData.Position[1] += ShapeData.Size[1] / 2;
//	}
//	//if the ShapeData is not part of a grid
//	if (InsideGrid == false)
//	{
//		ShapeData.GroupOffset = -1; //-1 for no grid
//		ShapeData.GroupCount = -1;
//	}
//
//	ShapeData.ID = ShapeContainer.CurrentContainerAmount;
//
//	ShapeData.UpdatePosition(ShapeData.Position);
//	//ShapeData.UpdateSize(ShapeData.Size, MouseAccess);
//	
//	Layer[CurrentLayer].ShapeDataCount++;
//
//	UpdateLayers(CurrentLayer, 1);
//
//	//Adds ShapeData where the space is
//	ShapeContainer.Add(ShapeData);
//
//
//
//	Vertex = Maths.SetTopRight(ShapeData, Vertex);    //#0 TopRight
//    VertexContainer.Add(Vertex);
//
//	Vertex = Maths.SetBottomRight(ShapeData, Vertex); //#1 BottomRight
//    VertexContainer.Add(Vertex);
//
//	Vertex = Maths.SetBottomLeft(ShapeData, Vertex);  //#2 BottomLeft
//    VertexContainer.Add(Vertex);
//
//	Vertex = Maths.SetTopLeft(ShapeData, Vertex);     //#3 TopLeft
//    VertexContainer.Add(Vertex);
//
//	//0 TopRight
//	//1 BottomRight
//	//2 BottomLeft
//	//0 TopRight
//	//2 BottomLeft
//	//3 TopLeft
//	return ID;
//}

//when you are ready, you might want to get rid of the mouse access considering ShapeDatas have mouse- 
// access in them
//void Page::ReplaceShapeData(int Spot, ShapeData& NewShapeData, bool Centered, bool MouseAccess)
//{
//	Maths Maths;
//	Vertex Vertex;
//	int HighlightSpot = Spot - 1;
//	ShapeData Highlight = Zero1;
//
//	//NewShapeData = NewShapeData.ChangePosition(NewShapeData, NewShapeData.Position);
//
//	if (NewShapeData.Highlighted == true)
//	{
//		//Before the center change
//		Highlight.Position = NewShapeData.Position;
//		Highlight.Size     = NewShapeData.HighlightSize;
//		Highlight.Color = NewShapeData.HighlightColor;
//	}
//
//	//If new ShapeData is centered
//	if (Centered == true)
//	{
//		NewShapeData.Position[0] -= NewShapeData.Size[0] / 2;
//		NewShapeData.Position[1] += NewShapeData.Size[1] / 2;
//
//		if (NewShapeData.Highlighted == true)
//		{
//			Highlight.Position[0] -= NewShapeData.HighlightSize[0] / 2;
//			Highlight.Position[1] += NewShapeData.HighlightSize[1] / 2;
//		}
//	}
//
//
//
//	ShapeContainer.Replace(Spot, NewShapeData);
//
//	Vertex = Maths.SetTopRight(NewShapeData, Vertex);    //#0 TopRight
//	VertexContainer.Replace(Spot * 4, Vertex);
//
//	Vertex = Maths.SetBottomRight(NewShapeData, Vertex); //#1 BottomRight
//	VertexContainer.Replace(Spot * 4 + 1, Vertex);
//
//	Vertex = Maths.SetBottomLeft(NewShapeData, Vertex);  //#2 BottomLeft
//	VertexContainer.Replace(Spot * 4 + 2, Vertex);
//
//	Vertex = Maths.SetTopLeft(NewShapeData, Vertex);     //#3 TopLeft
//	VertexContainer.Replace(Spot * 4 + 3, Vertex);
//
//	if (NewShapeData.Highlighted == true)
//	{
//		ShapeContainer.Replace(HighlightSpot, Highlight);
//
//		Vertex = Maths.SetTopRight(Highlight, Vertex);    //#0 TopRight
//		VertexContainer.Replace(HighlightSpot * 4, Vertex);
//
//		Vertex = Maths.SetBottomRight(Highlight, Vertex); //#1 BottomRight
//		VertexContainer.Replace(HighlightSpot * 4 + 1, Vertex);
//
//		Vertex = Maths.SetBottomLeft(Highlight, Vertex);  //#2 BottomLeft
//		VertexContainer.Replace(HighlightSpot * 4 + 2, Vertex);
//
//		Vertex = Maths.SetTopLeft(Highlight, Vertex);     //#3 TopLeft
//		VertexContainer.Replace(HighlightSpot * 4 + 3, Vertex);
//	}
//	//0 TopRight
//	//1 BottomRight
//	//2 BottomLeft
//	//0 TopRight
//	//2 BottomLeft
//	//3 TopLeft
//}

////when you are ready, you might want to get rid of the mouse access considering ShapeDatas have mouse- 
//// Replacement for hidden ShapeDatas
//void Page::ReplaceShapeDataH(int Spot, ShapeData& NewShapeData, bool Centered, bool MouseAccess, bool Hidden)
//{
//	Maths Maths;
//	Vertex Vertex;
//
//	if (Centered == true)
//	{
//		NewShapeData.Position[0] -= NewShapeData.Size[0] / 2;
//		NewShapeData.Position[1] += NewShapeData.Size[1] / 2;
//	}
//
//	//NewShapeData = NewShapeData.ChangePosition(NewShapeData, NewShapeData.Position);
//
//	ShapeContainer.Replace(Spot, NewShapeData);
//
//	Vertex* Vertices = GetVertices(Spot);
//
//	//Vertex = Maths.SetTopRight(NewShapeData, Vertex);    //#0 TopRight
//	if (Hidden == true)
//	{
//		Vertices[0].Color[3] = 0.0;
//		Vertices[1].Color[3] = 0.0;
//		Vertices[2].Color[3] = 0.0;
//		Vertices[3].Color[3] = 0.0;
//	}
//	else
//	{
//		Vertices[0].Color[3] = NewShapeData.Color[3];
//		Vertices[1].Color[3] = NewShapeData.Color[3];
//		Vertices[2].Color[3] = NewShapeData.Color[3];
//		Vertices[3].Color[3] = NewShapeData.Color[3];
//	}
//	VertexContainer.Replace(Spot * 4, Vertices[0]);
//
//	//Vertex = Maths.SetBottomRight(NewShapeData, Vertex); //#1 BottomRight
//	VertexContainer.Replace(Spot * 4 + 1, Vertices[1]);
//
//	//Vertex = Maths.SetBottomLeft(NewShapeData, Vertex);  //#2 BottomLeft
//	VertexContainer.Replace(Spot * 4 + 2, Vertices[2]);
//
//	//Vertex = Maths.SetTopLeft(NewShapeData, Vertex);     //#3 TopLeft
//	VertexContainer.Replace(Spot * 4 + 3, Vertices[3]);
//
//	//0 TopRight
//	//1 BottomRight
//	//2 BottomLeft
//	//0 TopRight
//	//2 BottomLeft
//	//3 TopLeft
//}


// Function Works
//ShapeData* Page::GetShapeData(int PageShapeData)
//{
//	ShapeData* Result;
//	//Set the pointer to the beginning of data
//	Page::ShapeDataPointer = ShapeContainer;
//	Result = Page::ShapeDataPointer + PageShapeData;
//
//	//Set the pointer back to the end
//	Page::ShapeDataPointer = ShapeDataPointer + this->PageShapeDataCount;
//	return Result;
//}
//
////To Clarify, this function can be used at any point in time


//void Page::AddLayer()
//{
//	this->CurrentLayerCount++;
//	Layer[CurrentLayerCount].LayerID = ShapeContainer.CurrentContainerAmount;
//	Layer[CurrentLayerCount].ShapeDataCount = 0;
//}
//
////call this function for insert and delete
////StartLayer is the layer you affected;
////Offset is how much the layer was changed refer to first statement ^
//void Page::UpdateLayers(int StartLayer, int Offset)
//{
//	Layer[StartLayer].ShapeDataCount += Offset;
//	for (int i = StartLayer + 1; i < CurrentLayerCount; i++)
//	{
//		//incremenet or deincrement all appllicable LayerID's by the offset of the action in the below layer
//		Layer[i].LayerID += Offset;
//		//Action could be a raise or drop such as insert and delete 
//	}
//}
//
//void Page::ChangeLayers(int Layers)
//{
//	//Get the location for the space to move
//	int EFillPos = Layer[Layers].GetShapeDataFillPosition();
//	int VFillPos = Layer[Layers].GetVertexFillPosition();
//
//	//Move the space to that location
//	//VertexContainer.MoveSpace(VFillPos, Zero2);
//
//	this->CurrentLayer = Layers;
//
//	//Ex. if we are moving the space to layer 2/5, then 3, 4, and 5 need to offset positiively by the space
//
//	//Func- UpdateLayers(3, ShapeContainer.CurrentSpaceAmount)
//}

bool Page::HighlightShapeData(ShapeData* ShapeDataSelected)
{
	if (ShapeDataSelected != NULL)
	{
		ShapeData Buffer;
		Buffer.Position = {(ShapeDataSelected->Position[0] - 0.025) , (ShapeDataSelected->Position[1]) + 0.025};

		Maths Maths;
		Buffer.Position = Maths.TopLeftToCenter(ShapeDataSelected->Position, ShapeDataSelected->Size);
		Buffer.Size = { ShapeDataSelected->Size[0] + 0.0135, ShapeDataSelected->Size[1] + 0.025 };
		Buffer.Color = { 0.0, 0.7156, 0.0, 1.0 };

		//Show the background behind the ShapeData
		int Insert;
		cout << ShapeDataSelected->ID << endl;
		if (ShapeDataSelected->ID > 0)
		{
			Insert = ShapeDataSelected->ID;
		}
		else
		{
			Insert = 0;
			cout << "Insert was Zero " << endl;
		}
		//InsertShapeData(Insert, 1, Buffer, true);
		return true;
	}
	return false;
}


bool Page::RemoveHighlight(ShapeData* ShapeDataHovered, int& HighlightCount)
{
	//only delete if this ShapeData is a highlight ShapeData
	glm::vec4 HC = { 0.0, 0.7156, 0.0, 1.0 };
	if (ShapeDataHovered != NULL && HighlightCount > 0 && ShapeDataHovered->Color == HC)
	{
		int Delete = ShapeDataHovered->ID -1;
		DeleteShapeArray(Delete, 1);
		return true;
	}
	return false;
}

//void Page::AddShapeDataLayer()
//{
//	if (CurrentLayerCount < 11)
//	{
//		//Add a layer
//		this->CurrentLayerCount++;
//		//if nothing was inserted in between the next layer and the previous layer Offset the ID by 1
//		if (Layer[CurrentLayerCount].LayerID == Layer[CurrentLayerCount - 1].LayerID)
//		{
//			//the new layerID is the current container amount + 1;
//			this->Layer[CurrentLayerCount].LayerID = ShapeContainer.CurrentContainerAmount + 1;
//			this->CurrentLayer = CurrentLayerCount;
//		}
//		else
//		{
//			//the new layerID is the current container amount;
//			this->Layer[CurrentLayerCount].LayerID = ShapeContainer.CurrentContainerAmount;
//			this->CurrentLayer = CurrentLayerCount;
//		}
//	}
//	else
//	{
//		std::cout << "LAYER ERROR::Max Count Reached" << endl;
//	}
//	
//}

//All ShapeDatas are updated as they are searched
//All ShapeDatas are constantly updated everytime the mouse hovers over nothing 
int Page::FindShapeData(double xMouse, double yMouse, bool Print)
{

	int LayerStart = 0; //this->Layer[CurrentLayer].LayerID;
	int LayerEnd = (ShapeContainer.CurrentContainerAmount -1);
	//int LayerEnd = (this->Layer[CurrentLayer].ShapeDataCount + LayerStart);
	//search for ShapeData backwards to always get the ShapeData furthest to the user screen
	for (int i = LayerEnd; i >= LayerStart; i--)
	{ 
		ShapeData* Result = ShapeContainer.RetrieveDataP(i);

		//Set the Shape ID to the layer iterator
			Result->ID = i;
			Result->ShapeGroup.ShapeStart = i - Result->ShapeGroup.ShapeOffset; 

			if (xMouse < Result->Right && xMouse >  Result->Left && yMouse < Result->Top && yMouse >  Result->Bottom)
			{
				if (Print == true)
				{
					cout << "found" << endl;
					cout << i << endl;
					LastShapeDataHovered = i;
				}

				LastShapeDataHovered = i;
				return i;
			}
	}
	LastShapeDataHovered = -1;
	return -1;

}


////////////////////////////////////////////////////
//ShapeData Editing

void Page::MoveShapeData(int CurrentSpot, int NewSpot, bool Centered, bool MouseAccess)
{
	ShapeData* Buffer = GetShapeDataP(CurrentSpot);
	if (Buffer == nullptr) { cout << "MoveShapeDataError::ERROR::Buffer Returned NULL" << endl; return;}

	//InsertShapeData(NewSpot, 1, *Buffer, true);
	DeleteShapeArray(CurrentSpot, 1);
	cout << "I've been called" << endl;
}


void Page::ClearShapeData(int Spot)
{
	ShapeData* Buffer = GetShapeDataP(Spot);
	if (Buffer == nullptr) { cout << "ClearShapeData::ERROR::Buffer Returned NULL" << endl; return;}

	ShapeData Empty;
	Empty.Position = { 0.0, 0.0 };
	Empty.Size = { 0.25, 0.25 };
	//ReplaceShapeData(Buffer->ID, Empty, true, true);
}

void Page::HideShapeData(int Spot, bool MouseAccess)
{
	ShapeData* Buffer = GetShapeDataP(Spot);
	if (Buffer == NULL) { cout << "HideShapeData::ERROR::Buffer Returned NULL" << endl; return;}

	Buffer->MouseAccess = MouseAccess;
	Buffer->Color[3] = 0.0;
	//ReplaceShapeDataH(Spot, *Buffer, false, Buffer->MouseAccess, true);
}

void Page::UnHideShapeData(int Spot, float AlphaChannel, bool MouseAccess)
{
	ShapeData* Buffer = GetShapeDataP(Spot);
	if (Buffer == nullptr) { cout << "UnHideShapeData::ERROR::Buffer Returned NULL" << endl; return;}

	Buffer->MouseAccess = MouseAccess;
	Buffer->Color[3] = AlphaChannel;
	//ReplaceShapeDataH(Spot, *Buffer, false, Buffer->MouseAccess, false);
}


//Returns the ShapeData from the container
ShapeData& Page::GetShapeDataR(int Spot)
{

	ShapeData& ShapeData = ShapeContainer.RetrieveDataR(Spot);
	ShapeData.ID = Spot;
	return ShapeData;

}

//Retreived Data returns ShapeData with accurate ID
ShapeData* Page::GetShapeDataP(int Spot)
{
	ShapeData* ShapeData = ShapeContainer.RetrieveDataP(Spot);
	ShapeData->ID = Spot;
	return ShapeData;
}

//Vertex* Page::GetVertices(int Spot)
//{
//	return VertexContainer.RetrieveData(Spot * 4);
//}


//Completely changes ShapeData in container
//void Page::ChangeShapeData(int Spot, ShapeData& NewShapeData, bool MouseAccess)
//{
//	ShapeData* Buffer = ShapeContainer.RetrieveData(Spot);
//	if (Buffer == nullptr) { cout << "ChangeShapeData::ERROR::Buffer Returned NULL" << endl; return;}
//
//	*Buffer = NewShapeData;
//	//ReplaceShapeData(Spot, *Buffer, false, MouseAccess);
//}
//
////Changes only the color of a specific ShapeData
//void Page::ChangeShapeDataColor(int Spot, glm::vec4 Color, bool MouseAccess)
//{
//	if (Spot != -1)
//	{
//		ShapeData* Buffer = GetShapeData(Spot);
//		if (Buffer == nullptr) { cout << "ChangeShapeDataColor2?::ERROR::Buffer Returned NULL" << endl; return;}
//
//		//Avoid Redundancy
//		if (Buffer->Color != Color)
//		{
//			Buffer->Color = Color;
//			
//			//ReplaceShapeData(Spot, *Buffer, false, MouseAccess);
//		}
//	}
//}
//
////Change only: 'y' (change only y) 'x' (Change only x) 'B' (Change Both)
//void Page::ChangeShapeDataPosition(int Spot, glm::vec2 Position, char ChangeOnly, bool OnCenter, bool MouseAccess)
//{
//	//Get the ShapeData Safely
//	ShapeData* Buffer = GetShapeData(Spot);
//	if (Buffer == nullptr) { cout << "ChangeShapeDataPosition::ERROR::Buffer Returned NULL" << endl; return;}
//
//	//Adjust Position for center accuracy
//    glm::vec2 CenteredPosition = { Buffer->Position[0] + Buffer->Size[0] / 2,  Buffer->Position[0] - Buffer->Size[0] / 2 };
//	if ((CenteredPosition != Position && OnCenter == true) || Buffer->Position != Position && OnCenter == false)
//	{
//		if (ChangeOnly == 'x')
//		{
//			Buffer->Position = { Position[0], Buffer->Position[1] };
//			//ReplaceShapeData(Spot, *Buffer, OnCenter, MouseAccess);
//		}
//		if (ChangeOnly == 'y')
//		{
//			Buffer->Position[1] = Position[1];
//			//ReplaceShapeData(Spot, *Buffer, OnCenter, MouseAccess);
//		}
//		if (ChangeOnly != 'x' && ChangeOnly != 'y')
//		{
//			Buffer->Position = Position;
//			//ReplaceShapeData(Spot, *Buffer, OnCenter, MouseAccess);
//		}
//
//
//		if (Buffer->Highlighted == true && ChangeOnly == 'x')
//		{
//			ShapeData* BufferHighlight = GetShapeData(Spot - 1);
//			BufferHighlight->Position[0] = Position[0];
//			BufferHighlight->Size = Buffer->HighlightSize;
//			//ReplaceShapeData(Spot - 1, *BufferHighlight, false, false);
//			//cout << "yes11" << endl;
//		}
//		if (Buffer->Highlighted == true && ChangeOnly == 'y')
//		{
//			ShapeData* BufferHighlight = GetShapeData(Spot - 1);
//			BufferHighlight->Position[1] = Position[1];
//			BufferHighlight->Size = Buffer->HighlightSize;
//			//ReplaceShapeData(Spot - 1, *BufferHighlight, false, false);
//			//cout << "yes12" << endl;
//		}
//		if (Buffer->Highlighted == true && ChangeOnly != 'x' && ChangeOnly != 'y')
//		{
//			ShapeData* BufferHighlight = GetShapeData(Spot - 1);
//			BufferHighlight->Position = Position;
//			BufferHighlight->Size = Buffer->HighlightSize;
//			//ReplaceShapeData(Spot - 1, *BufferHighlight, true, false);
//			//cout << "yes13" << endl;
//		}
//	}
//}
//
//void Page::ChangeHighlight(int Spot, bool Highlight)
//{
//	
//	ShapeData* Buffer = GetShapeData(Spot);
//	if (Buffer == nullptr) { cout << "ChangeHilight::ERROR::Buffer Returned NULL" << endl; return;}
//
//	if (Buffer->Highlighted != Highlight)
//	{
//		Buffer->Highlighted = Highlight;
//		//ReplaceShapeData(Spot, *Buffer, false, true);
//	}
//}
//
////Changes only the color of a specific ShapeData
//void Page::ChangeShapeDataSize(int Spot, glm::vec2 Size, char ChangeOnly, bool OnCenter, bool MouseAccess)
//{
//	ShapeData* Buffer = GetShapeData(Spot);
//	if (Buffer == nullptr) { cout << "ChangeShapeDataSize::ERROR::Buffer Returned NULL" << endl; return;}
//
//	if (Buffer->Size != Size)
//	{
//		if (ChangeOnly == 'x')
//		{
//			if (OnCenter == true)
//			{
//				Buffer->Position[0] = Buffer->Position[0] + Buffer->Size[0] / 2;
//				Buffer->Position[1] = Buffer->Position[1] - Buffer->Size[1] / 2;
//			}
//			Buffer->Size = { Size[0], Buffer->Size[1] };
//			//ReplaceShapeData(Spot, *Buffer, OnCenter, MouseAccess);
//			//cout << "BufferPosition:" << Buffer->Position[0] << " " << Buffer->Position[1] << endl;
//		}
//		if (ChangeOnly == 'y')
//		{
//			if (OnCenter == true)
//			{
//				Buffer->Position[0] = Buffer->Position[0] + Buffer->Size[0] / 2;
//				Buffer->Position[1] = Buffer->Position[1] - Buffer->Size[1] / 2;
//			}
//			Buffer->Size[1] = Size[1];
//			//ReplaceShapeData(Spot, *Buffer, OnCenter, MouseAccess);
//			///cout << "BufferPosition:" << Position[0] << " " << Position[1] << endl;
//			///cout << "yes2" << endl;
//		}
//		if (ChangeOnly != 'x' && ChangeOnly != 'y')
//		{
//			if (OnCenter == true)
//			{
//				Buffer->Position[0] = Buffer->Position[0] + Buffer->Size[0] / 2;
//				Buffer->Position[1] = Buffer->Position[1] - Buffer->Size[1] / 2;
//			}
//			Buffer->Size = Size;
//			ReplaceShapeData(Spot, *Buffer, OnCenter, MouseAccess);
//			//cout << "BufferPosition:" << Position[0] << " " << Position[1] << endl;
//			//cout << "yes3" << endl;
//		}
//
//		ShapeData* BufferHighlight = GetShapeData(Spot - 1);
//
//		if (Buffer->Highlighted == true && ChangeOnly == 'x')
//		{
//			if (OnCenter == true)
//			{
//				BufferHighlight->Position[0] = BufferHighlight->Position[0] + BufferHighlight->Size[0] / 2;
//				BufferHighlight->Position[1] = BufferHighlight->Position[1] - BufferHighlight->Size[1] / 2;
//			}
//			ReplaceShapeData(Spot - 1, *BufferHighlight, OnCenter, false);
//			//	cout << "yes11" << endl;
//		}
//		if (Buffer->Highlighted == true && ChangeOnly == 'y')
//		{
//			if (OnCenter == true)
//			{
//				BufferHighlight->Position[0] = BufferHighlight->Position[0] + BufferHighlight->Size[0] / 2;
//				BufferHighlight->Position[1] = BufferHighlight->Position[1] - BufferHighlight->Size[1] / 2;
//			}
//			BufferHighlight->Size[1] = Buffer->HighlightSize[1];
//			ReplaceShapeData(Spot - 1, *BufferHighlight, OnCenter, false);
//			//	cout << "yes12" << endl;
//		}
//		if (Buffer->Highlighted == true && ChangeOnly != 'x' && ChangeOnly != 'y')
//		{
//			if (OnCenter == true)
//			{
//				BufferHighlight->Position[0] = BufferHighlight->Position[0] + BufferHighlight->Size[0] / 2;
//				BufferHighlight->Position[1] = BufferHighlight->Position[1] - BufferHighlight->Size[1] / 2;
//			}
//			BufferHighlight->Size = Buffer->HighlightSize;
//			ReplaceShapeData(Spot - 1, *BufferHighlight, OnCenter, false);
//			//	cout << "yes13" << endl;
//		}
//	}
//}
//
////Changes only the color of a specific ShapeData
//void Page::ChangeShapeDataTexture(int Spot, int TextureSlot, bool MouseAccess)
//{
//	ShapeData* Buffer = GetShapeData(Spot);
//	if (Buffer == nullptr) { cout << "ChangeShapeDataTexture::ERROR::Buffer Returned NULL" << endl; return; }
//
//	if (Buffer->ActiveTexture != TextureSlot)
//	{
//		Buffer->ActiveTexture = TextureSlot;
//		Buffer->Color = { 1.0, 1.0, 1.0, 1.0 };
//		ReplaceShapeData(Spot, *Buffer, false, MouseAccess);
//	}
//}
//
//
//////////////
//
//void Page::OffsetShapeDataColor(int Spot, glm::vec4 ColorOffset, bool MouseAccess)
//{
//	ShapeData* Buffer = GetShapeData(Spot);
//	if (Buffer == nullptr) { cout << "OffsetShapeDataColor::ERROR::Buffer Returned NULL" << endl; return;}
//	//Buffer->Color += ColorOffset;
//	ReplaceShapeData(Spot, *Buffer, false, MouseAccess);
//}
//
////Changes only the color of a specific ShapeData
//void Page::OffsetShapeDataPosition(int Spot, glm::vec2 PositionOffset, char ChangeOnly, bool MouseAccess)
//{
//	ShapeData* Buffer = ShapeContainer.RetrieveData(Spot);
//	if (Buffer == nullptr) { cout << "OffsetShapeDataPosition::ERROR::Buffer Returned NULL" << endl; return;}
//
//	if (ChangeOnly == 'x')
//	{
//		Buffer->Position[0] += PositionOffset[0];
//		ReplaceShapeData(Spot, *Buffer, false, MouseAccess);
//		//cout << "BufferPosition:" << Buffer->Position[0] << " " << Buffer->Position[1] << endl;
//	}
//	if (ChangeOnly == 'y')
//	{
//		Buffer->Position[1] += PositionOffset[1];
//		ReplaceShapeData(Spot, *Buffer, false, MouseAccess);
//		//cout << "BufferPosition:" << Position[0] << " " << Position[1] << endl;
//		//cout << "yes2" << endl;
//	}
//	if (ChangeOnly != 'x' && ChangeOnly != 'y')
//	{
//		Buffer->Position += PositionOffset;
//		ReplaceShapeData(Spot, *Buffer, false, MouseAccess);
//		//cout << "BufferPosition:" << Position[0] << " " << Position[1] << endl;
//		//cout << "yes3" << endl;
//	}
//	///////////////////////////////////////////
//	///////////////////////////////////////////
//	//Highlight ShapeData not completed
//	ShapeData* BufferHighlight = GetShapeData(Spot - 1);
//	if (Buffer->Highlighted == true && ChangeOnly == 'x')
//	{
//		BufferHighlight->Position[0] += PositionOffset[0];
//		BufferHighlight->Size = Buffer->HighlightSize;
//		ReplaceShapeData(Spot - 1, *BufferHighlight, false, false);
//		//cout << "yes11" << endl;
//	}
//	if (Buffer->Highlighted == true && ChangeOnly == 'y')
//	{
//		BufferHighlight->Position[1] += PositionOffset[1];
//		BufferHighlight->Size = Buffer->HighlightSize;
//		ReplaceShapeData(Spot - 1, *BufferHighlight, false, false);
//		//cout << "yes12" << endl;
//	}
//	if (Buffer->Highlighted == true && ChangeOnly != 'x' && ChangeOnly != 'y')
//	{
//		BufferHighlight->Position += PositionOffset;
//		BufferHighlight->Size = Buffer->HighlightSize;
//		ReplaceShapeData(Spot - 1, *BufferHighlight, false, false);
//		//cout << "yes13" << endl;
//	}///////////////////////////////////////////////////////////////////////////
//}
//
////Changes only the color of a specific ShapeData
//void Page::OffsetShapeDataSize(int Spot, glm::vec2 SizeOffset, char ChangeOnly, bool OnCenter, bool MouseAccess)
//{
//	//cout << SizeOffset[0] << SizeOffset[1]<< endl;
//	ShapeData* Buffer = GetShapeData(Spot);
//	if (Buffer == nullptr) { cout << "OffsetShapeDataSize::ERROR::Buffer Returned NULL" << endl; return;}
//
//	//Offset Restriction to prevent negative size
//	if (Buffer->Size[0] + SizeOffset[0] < 0 || Buffer->Size[1] + SizeOffset[1] < 0) return;
//
//	if (ChangeOnly == 'x')
//	{
//		if (OnCenter == true)
//		{
//			Buffer->Position[0] = Buffer->Position[0] + (Buffer->Size[0] + SizeOffset[0]) / 2;
//			Buffer->Position[1] = Buffer->Position[1] - (Buffer->Size[1] + SizeOffset[1]) / 2;
//		}
//		Buffer->Size[0] += SizeOffset[0];
//		ReplaceShapeData(Spot, *Buffer, OnCenter, MouseAccess);
//		//cout << "BufferPosition:" << Buffer->Position[0] << " " << Buffer->Position[1] << endl;
//	}
//	if (ChangeOnly == 'y')
//	{
//		if (OnCenter == true)
//		{
//			Buffer->Position[0] = Buffer->Position[0] + (Buffer->Size[0] + SizeOffset[0]) / 2;
//			Buffer->Position[1] = Buffer->Position[1] - (Buffer->Size[1] + SizeOffset[1]) / 2;
//		}
//		Buffer->Size[1] += SizeOffset[1];
//		ReplaceShapeData(Spot, *Buffer, OnCenter, MouseAccess);
//		///cout << "BufferPosition:" << Position[0] << " " << Position[1] << endl;
//		///cout << "yes2" << endl;
//	}
//	if (ChangeOnly != 'x' && ChangeOnly != 'y')
//	{
//		if (OnCenter == true)
//		{
//			Buffer->Position[0] = Buffer->Position[0] + (Buffer->Size[0] + SizeOffset[0]) / 2;
//			Buffer->Position[1] = Buffer->Position[1] - (Buffer->Size[1] + SizeOffset[1]) / 2;
//		}
//		Buffer->Size += SizeOffset;
//		ReplaceShapeData(Spot, *Buffer, OnCenter, MouseAccess);
//		//cout << "BufferPosition:" << Position[0] << " " << Position[1] << endl;
//		//cout << "yes3" << endl;
//	}
//
//	ShapeData* BufferHighlight = GetShapeData(Spot - 1);
//
//	if (Buffer->Highlighted == true && ChangeOnly == 'x')
//	{
//		ShapeData* BufferHighlight = GetShapeData(Spot - 1);
//		BufferHighlight->Size[0] = Buffer->HighlightSize[0];
//		ReplaceShapeData(Spot - 1, *BufferHighlight, false, false);
//		//	cout << "yes11" << endl;
//	}
//	if (Buffer->Highlighted == true && ChangeOnly == 'y')
//	{
//		ShapeData* BufferHighlight = GetShapeData(Spot - 1);
//		BufferHighlight->Size[1] = Buffer->HighlightSize[1];
//		ReplaceShapeData(Spot - 1, *BufferHighlight, false, false);
//		//	cout << "yes12" << endl;
//	}
//	if (Buffer->Highlighted == true && ChangeOnly != 'x' && ChangeOnly != 'y')
//	{
//		ShapeData* BufferHighlight = GetShapeData(Spot - 1);
//		BufferHighlight->Size = Buffer->HighlightSize;
//		ReplaceShapeData(Spot - 1, *BufferHighlight, false, false);
//		//	cout << "yes13" << endl;
//	}
//}
//
////Changes only the color of a specific ShapeData
//void Page::OffsetShapeDataTexture(int Spot, int TextureSlotOffset, bool MouseAccess)
//{
//	ShapeData* Buffer = ShapeContainer.RetrieveData(Spot);
//	if (Buffer == nullptr) { cout << "OffsetShapeDataColor::ERROR::Buffer Returned NULL" << endl; return;}
//
//	Buffer->ActiveTexture += TextureSlotOffset;
//	ReplaceShapeData(Spot, *Buffer, false, MouseAccess);
//}



int Page::ShapeDataCount()
{
	return this->ShapeContainer.CurrentContainerAmount - 1;
}

//////////////////////////////
//Group Editing

//void Page::ClearSelectionGroup(int* Selections, int SelectionsSize)
//{
//	for (int i = 0; i < SelectionsSize; i++)
//	{
//		ClearShapeData(Selections[i]);
//	}
//}
//
//// HIDE
//void Page::HideSelectionGroup(int* Selections, int SelectionsSize, bool MouseAccess)
//{
//	for (int i = 0; i < SelectionsSize; i++)
//	{
//		HideShapeData(Selections[i], MouseAccess);
//	}
//}
//
////UN HIDE
//void Page::UnHideSelectionGroup(int* Selections, int SelectionsSize, float AlphaChannel, bool MouseAccess)
//{
//	for (int i = 0; i < SelectionsSize; i++)
//	{
//		UnHideShapeData(Selections[i], AlphaChannel, MouseAccess);
//	}
//}
//void Page::ChangeSelectionColor(int* Selections, int SelectionsSize, glm::vec4 Color, bool MouseAccess)
//{
//	for (int i = 0; i < SelectionsSize; i++)
//	{
//		ChangeShapeDataColor(Selections[i], Color, MouseAccess);
//	}
//}
//void Page::ChangeSelectionPosition(int* Selections, int SelectionsSize, glm::vec2 Position, char ChangeOnly, bool OnCenter, bool MouseAccess)
//{
//	for (int i = 0; i < SelectionsSize; i++)
//	{
//		ChangeShapeDataPosition(Selections[i], Position, ChangeOnly, OnCenter, MouseAccess);
//	}
//}
//void Page::ChangeSelectionSize(int* Selections, int SelectionsSize, glm::vec2 Size, bool OnCenter, char ChangeOnly, bool MouseAccess)
//{
//	for (int i = 0; i < SelectionsSize; i++)
//	{
//		ChangeShapeDataSize(Selections[i], Size, ChangeOnly, OnCenter, MouseAccess);
//	}
//}
//void Page::ChangeSelectionTexture(int* Selections, int SelectionsSize, int TextureSlot, bool MouseAccess)
//{
//	for (int i = 0; i < SelectionsSize; i++)
//	{
//		ChangeShapeDataTexture(Selections[i], TextureSlot, MouseAccess);
//	}
//}
//void Page::ChangeSelectionHighlight(int* Selections, int SelectionsSize, bool Highlight)
//{
//	for (int i = 0; i < SelectionsSize; i++)
//	{
//		ChangeHighlight(Selections[i], Highlight);
//	}
//}

///////////////////////////////////////
//Grid Editing

//Grid& Page::GetGrid(int GroupShapeData)
//{
//	Grid Grid;
//	ShapeData* Buffer;
//
//	//Get Grid Data
//	Buffer = GetShapeData(GroupShapeData);
//
//    //Load Grid Data
//	Grid.DataFromShapeData(*Buffer);
//
//	return Grid;
//}



//void Page::HideGrid(int GroupShapeData)
//{
//	Grid NewGrid;
//	ShapeData* Buffer;
//	
//	Buffer = GetShapeData(GroupShapeData);
//
//	NewGrid.DataFromShapeData(*Buffer);
//	NewGrid.MouseAccess = false;
//	NewGrid.Color[3] = 0.0;
//
//	ReplaceShapeDataGrid(NewGrid);
//}
//
//void Page::UnHideGrid(int GroupShapeData, float AlphaChannel)
//{
//	Grid NewGrid;
//	ShapeData* Buffer;
//
//	Buffer = GetShapeData(GroupShapeData);
//
//	NewGrid.DataFromShapeData(*Buffer);
//	NewGrid.MouseAccess = true;
//	NewGrid.Color[3] = AlphaChannel;
//
//	ReplaceShapeDataGrid(NewGrid);
//}
//
//void Page::ChangeGridXYShapePerRow(int GroupShapeData, glm::vec2 NewXYShapeDatasPerRow)
//{
//	Grid NewGrid;
//
//	//Get Group Data From group ShapeData
//	ShapeData* Buffer = GetShapeData(GroupShapeData);
//
//	//Load The grid data from group ShapeData
//    NewGrid.DataFromShapeData(*Buffer);
//	//NewGrid.MouseAccess = true;
//	
//
//	if (NewGrid.XYShapeDatasPerRow != NewXYShapeDatasPerRow)
//	{
//		NewGrid.XYShapeDatasPerRow = NewXYShapeDatasPerRow;
//		NewGrid.Count = NewXYShapeDatasPerRow[0] * NewXYShapeDatasPerRow[1];
//
//		ReplaceShapeDataGrid(NewGrid);
//	}
//}
//void Page::ChangeShapeGroupSize(int GroupShapeData, glm::vec2 NewSize)
//{
//	ShapeData* Buffer = GetShapeData(GroupShapeData);
//	Grid NewGrid;
//
//	NewGrid.DataFromShapeData(*Buffer);
//	if (NewGrid.Size != NewSize)
//	{
//		NewGrid.Size = NewSize;
//
//		NewGrid.Centered = true;
//		if (NewGrid.Centered == true)
//		{
//			//set from top left to middle
//			NewGrid.Position[0] = NewGrid.Position[0] + NewGrid.Size[0] / 2;
//			NewGrid.Position[1] = NewGrid.Position[1] - NewGrid.Size[1] / 2;
//		}
//
//		ReplaceShapeDataGrid(NewGrid);
//	}
//}
//
//void Page::ChangeShapeGroupPosition(int GroupShapeData, glm::vec2 NewShapeGroupPosition, char ChangeOnly, bool Centered)
//{
//
//	Grid NewGrid = GetGrid(GroupShapeData);
//
//	if (NewGrid.Position != NewShapeGroupPosition)
//	{
//		if (Centered == true)
//		{
//			//Translate
//			NewGrid.Position[0] += NewGrid.Size[0] / 2;
//			NewGrid.Position[1] -= NewGrid.Size[1] / 2;
//			NewGrid.Centered = true;
//		}
//		else { NewGrid.Centered = false; };
//
//
//		// yRestriction
//		if (ChangeOnly == 'x')
//		{
//			NewGrid.Position[0] = NewShapeGroupPosition[0];
//			ReplaceShapeDataGrid(NewGrid); //NewGrid.Start,
//		}
//
//		// xRestriction
//		if (ChangeOnly == 'y')
//		{
//			NewGrid.Position[1] = NewShapeGroupPosition[1];
//			ReplaceShapeDataGrid(NewGrid);
//		}
//
//		// No Restrictions
//		if (ChangeOnly != 'x' && ChangeOnly != 'y')
//		{
//			NewGrid.Position = NewShapeGroupPosition;
//			ReplaceShapeDataGrid(NewGrid);
//		}
//	}
//
//}
//
//
//
//
//void Page::ChangeGridShapeSize(int GroupShapeData, glm::vec2 NewGridShapeSize)
//{
//	ShapeData* Buffer = GetShapeData(GroupShapeData);
//	int GridStart = Buffer->GroupStart;
//
//	Grid NewGrid;
//	NewGrid.DataFromShapeData(*Buffer);
//
//
//
//	if (NewGrid.ShapeDataSize != NewGridShapeSize)
//	{
//		NewGrid.Centered = true;
//		if (NewGrid.Centered == true)
//		{
//			//set from top left to middle
//			NewGrid.Position[0] = NewGrid.Position[0] + NewGrid.Size[0] / 2;
//			NewGrid.Position[1] = NewGrid.Position[1] - NewGrid.Size[1] / 2;
//			//cout << "haqlellgfjugis" << endl;
//		}
//
//		NewGrid.ShapeDataSize = NewGridShapeSize;
//
//
//		ReplaceShapeDataGrid(NewGrid);
//	}
//}
//void Page::ChangeShapeGroupColor(int GroupShapeData, glm::vec4 NewColor)
//{
//	ShapeData* Buffer = GetShapeData(GroupShapeData);
//	int GridStart = Buffer->GroupStart;
//
//	Grid NewGrid;
//	NewGrid.DataFromShapeData(*Buffer);
//	if (NewGrid.Color != NewColor)
//	{
//		NewGrid.Color = NewColor;
//		NewGrid.Centered = true;
//
//
//		ReplaceShapeDataGrid(NewGrid);
//	}
//}
//
//
//
//
////////////////////////////////////////////////////////////////////////////////
//
//void Page::OffsetGridXYShapePerRow(int GroupShapeData, glm::vec2 NewXYShapeDatasPerRow, char ChangeOnly)
//{
//	Grid NewGrid;
//	ShapeData* Buffer = GetShapeData(GroupShapeData);
//	NewGrid.DataFromShapeData(*Buffer);
//
//	if (NewGrid.XYShapeDatasPerRow[0] == 1 && NewXYShapeDatasPerRow[0] < 0) return;
//	if (NewGrid.XYShapeDatasPerRow[1] == 1 && NewXYShapeDatasPerRow[1] < 0) return;
//
//	if (ChangeOnly == 'x')
//	{
//		NewGrid.XYShapeDatasPerRow[0] += NewXYShapeDatasPerRow[0];
//		NewGrid.Count = NewGrid.XYShapeDatasPerRow[0] * NewGrid.XYShapeDatasPerRow[1];
//		ReplaceShapeDataGrid(NewGrid);
//	}
//	if (ChangeOnly == 'y')
//	{
//		NewGrid.XYShapeDatasPerRow[1] += NewXYShapeDatasPerRow[1];
//		NewGrid.Count = NewGrid.XYShapeDatasPerRow[0] * NewGrid.XYShapeDatasPerRow[1];
//		ReplaceShapeDataGrid(NewGrid);
//
//	}
//	if (ChangeOnly != 'x' && ChangeOnly != 'y')
//	{
//		NewGrid.XYShapeDatasPerRow += NewXYShapeDatasPerRow;
//		NewGrid.Count = NewGrid.XYShapeDatasPerRow[0] * NewGrid.XYShapeDatasPerRow[1];
//		ReplaceShapeDataGrid(NewGrid);
//	}
//}
//void Page::OffsetShapeGroupSize(int GroupShapeData, glm::vec2 NewShapeGroupSize, char ChangeOnly, bool Centered)
//{
//	Grid NewGrid;
//	ShapeData* Buffer = GetShapeData(GroupShapeData);
//	NewGrid.DataFromShapeData(*Buffer);
//	NewGrid.Centered = Centered;
//
//	if (Centered == true)
//	{
//		NewGrid.Position[0] += Buffer->ShapeGroupSize[0] / 2;
//		NewGrid.Position[1] -= Buffer->ShapeGroupSize[1] / 2;
//	}
//
//	if (ChangeOnly == 'x')
//	{
//		NewGrid.Size[0] += NewShapeGroupSize[0];
//		ReplaceShapeDataGrid(NewGrid);
//	}
//	if (ChangeOnly == 'y')
//	{
//		NewGrid.Size[1] += NewShapeGroupSize[1];
//		ReplaceShapeDataGrid(NewGrid);
//	}
//	if (ChangeOnly != 'x' && ChangeOnly != 'y')
//	{
//		NewGrid.Size += NewShapeGroupSize;
//		ReplaceShapeDataGrid(NewGrid);
//	}
//}
//
//
//void Page::OffsetShapeGroupPosition(int GroupShapeData, glm::vec2 NewShapeGroupPosition, char ChangeOnly, bool Centered)
//{
//	Grid NewGrid;
//	ShapeData* Buffer = GetShapeData(GroupShapeData);
//	NewGrid.DataFromShapeData(*Buffer);
//	NewGrid.Centered = Centered;
//
//	if (Centered == true)
//	{
//		NewGrid.Position[0] += Buffer->ShapeGroupSize[0]/2;
//		NewGrid.Position[1] -= Buffer->ShapeGroupSize[1]/2;
//	}
//
//	if (ChangeOnly == 'x')
//	{
//		NewGrid.Position[0] += NewShapeGroupPosition[0];
//		ReplaceShapeDataGrid( NewGrid);
//	}
//	if (ChangeOnly == 'y')
//	{
//		NewGrid.Position[1] += NewShapeGroupPosition[1];
//		ReplaceShapeDataGrid( NewGrid);
//	}
//	if (ChangeOnly != 'x' && ChangeOnly != 'y')
//	{
//		NewGrid.Position += NewShapeGroupPosition;
//		ReplaceShapeDataGrid( NewGrid);
//	}
//}
//
//
//void Page::OffsetGridShapeSize(int GroupShapeData, glm::vec2 NewGridShapeSize, char ChangeOnly)
//{
//	Grid NewGrid;
//	ShapeData* Buffer = GetShapeData(GroupShapeData);
//	NewGrid.DataFromShapeData(*Buffer);
//
//	if (ChangeOnly == 'x')
//	{
//		NewGrid.ShapeDataSize[0] += NewGridShapeSize[0];
//		ReplaceShapeDataGrid(NewGrid);
//	}
//	if (ChangeOnly == 'y')
//	{
//		NewGrid.ShapeDataSize[1] += NewGridShapeSize[1];
//		ReplaceShapeDataGrid(NewGrid);
//	}
//	if (ChangeOnly != 'x' && ChangeOnly != 'y')
//	{
//		NewGrid.ShapeDataSize += NewGridShapeSize;
//		ReplaceShapeDataGrid(NewGrid);
//	}
//}
//
//////////////////////////////////////////////////////////////////////
//
int Page::PrintVector2(glm::vec2 Vector, glm::vec2 Position, glm::vec4 Color)
{ 
	int ID = Amount();
	//Vector
	float x = Vector[0];
	float y = Vector[1];

	//SubStrings
	string X = "  X: ";
	string Y = "  Y: ";
	string floatx = to_string(x);
	string floaty = to_string(y);
	
	string Text = X + floatx + Y + floaty;
	TextSpecification Vector2( Text, Position, false, Color);

	AddTextBox(Vector2);

	return ID;
}
int Page::PrintVector3(glm::vec3 Vector, glm::vec2 Position, glm::vec4 Color)
{
	int ID = Amount();
	//Vector
	float x = Vector[0];
	float y = Vector[1];
	float z = Vector[2];

	//SubStrings
	string X = "  X: ";
	string Y = "  Y: ";
	string Z = "  Z: ";
	string floatx = to_string(x);
	string floaty = to_string(y);
	string floatz = to_string(z);

	//Display 5 Characters only
	floatx.erase(5);
	floaty.erase(5);
	floatz.erase(5);

	
	string Text = X + floatx + Y + floaty + Z + floatz;
	TextSpecification Vector3( Text, Position, false, Color);
	AddTextBox(Vector3);

	return ID;
}

int Page::PrintVector4(glm::vec4 Vector, glm::vec2 Position, glm::vec4 Color)
{
	int ID = Amount();
	//Vector
	float r = Vector[0];
	float g = Vector[1];
	float b = Vector[2];
	float a = Vector[3];

	//SubStrings
	string R = "  R ";
	string G = "  G ";
	string B = "  B ";
	string A = "  A ";
	string floatr = to_string(r);
	string floatg = to_string(g);
	string floatb = to_string(b);
	string floata = to_string(a);

	//Display 5 Characters only
	floatr.erase(5);
	floatg.erase(5);
	floatb.erase(5);
	floata.erase(5);

	string Text =  R + floatr + G + floatg + B + floatb + A + floata;
	TextSpecification Vector4( Text, Position, false, Color);
	AddTextBox(Vector4);

	return ID;
}

int Page::PrintFloat(float Float, glm::vec2 Position, glm::vec4 Color)
{
	int ID = Amount();
	//Vector
	float x = Float;

	string floatx = to_string(x);

	string Devision = "  ";

	//Display 5 Characters only
	floatx.erase(5);

	string Text = Devision + floatx;
	TextSpecification Float1(Text, Position, false, Color);
	AddTextBox(Float1);

	return ID;
}
int Page::PrintInt(int Int, glm::vec2 Position, glm::vec4 Color)
{
	int ID = Amount();
	//Vector
	int x = Int;

	string Intx = to_string(x);
	string Text;
	string Zero = " ";

	if (Intx.size() == 1)
	{
	   Text = Zero + Zero + Zero + Intx;
	}
	
	if (Intx.size() == 2)
	{
		Text = Zero + Zero + Intx;
	}

	if (Intx.size() == 3)
	{
		Text = Zero + Intx;
	}

	if (Intx.size() == 4)
	{
		Text = Intx;
	}

	if (Intx.size() > 4)
	{
		Text = Intx.erase(4);
	}
	TextSpecification Int1(Text, Position, false, Color);
	AddTextBox(Int1);

	return ID;
}
//
//int Page::PrintBool(bool Bool, glm::vec2 Position, glm::vec4 Color)
//{
//	int ID = Amount();
//	string Boolx;
//
//	//Vector
//	if (Bool == true)
//	{
//		Boolx = "True ";
//	}
//	else
//	{
//		Boolx = "False";
//	}
//
//	string Devision = "  ";
//
//
//	string Text = Devision + Boolx;
//	TextSpecification Bool1(Text, Position, false, Color);
//	AddTextBox(Bool1);
//
//	return ID;
//}
//
//
//
//void Page::ChangeVector2(int TextStart, glm::vec2 Vector, glm::vec2 Position, glm::vec4 Color)
//{
//	ShapeData* Check = GetShapeData(TextStart);
//
//		//Vector
//		float x = Vector[0];
//		float y = Vector[1];
//
//		//SubStrings
//		string X = "  X: ";
//		string Y = "  Y: ";
//		string floatx = to_string(x);
//		string floaty = to_string(y);
//
//		//Display 5 Characters only
//		floatx.erase(5);
//		floaty.erase(5);
//
//		string NewText = X + floatx + Y + floaty;
//
//		if (Check->Text != NewText || Check->ShapeGroupPosition != Position)
//		{
//			TextSpecification NewVector2(NewText, Position, false, Color);
//			NewVector2.Start = TextStart;
//			NewVector2.Count = NewText.size();
//
//			ReplaceTextBox(NewVector2);
//		}
//	
//}
//
//void Page::ChangeVector3(int TextStart, glm::vec2 Vector, glm::vec2 Position, glm::vec4 Color)
//{
//	ShapeData* Check = GetShapeData(TextStart);
//	//Vector
//	float x = Vector[0];
//	float y = Vector[1];
//	float z = Vector[2];
//
//	//SubStrings
//	string X = "  X: ";
//	string Y = "  Y: ";
//	string Z = "  Z: ";
//	string floatx = to_string(x);
//	string floaty = to_string(y);
//	string floatz = to_string(z);
//
//	//Display 5 Characters only
//	floatx.erase(5);
//	floaty.erase(5);
//	floatz.erase(5);
//
//	string NewText = X + floatx + Y + floaty + Z + floatz;
//	if (Check->Text != NewText || Check->ShapeGroupPosition != Position)
//	{
//		TextSpecification NewVector3(NewText, Position, false, Color);
//		NewVector3.Start = TextStart;
//		ReplaceTextBox(NewVector3);
//	}
//}
//
//void Page::ChangeVector4(int TextStart, glm::vec4 Vector, glm::vec2 Position, glm::vec4 Color)
//{
//	ShapeData* Check = GetShapeData(TextStart);
//	//Vector
//	float r = Vector[0];
//	float g = Vector[1];
//	float b = Vector[2];
//	float a = Vector[3];
//
//	//SubStrings
//	string R = "  R ";
//	string G = "  G ";
//	string B = "  B ";
//	string A = "  A ";
//	string floatr = to_string(r);
//	string floatg = to_string(g);
//	string floatb = to_string(b);
//	string floata = to_string(a);
//
//	//Display 5 Characters only
//	floatr.erase(5);
//	floatg.erase(5);
//	floatb.erase(5);
//	floata.erase(5);
//
//	string NewText = R + floatr + G + floatg + B + floatb + A + floata;
//	if (Check->Text != NewText || Check->ShapeGroupPosition != Position)
//	{
//		TextSpecification NewVector4(NewText, Position, false, Color);
//		NewVector4.Count = NewText.size();
//		NewVector4.Start = TextStart;
//		ReplaceTextBox(NewVector4);
//	}
//}
//
//void Page::ChangeFloat(int TextStart, float Float, glm::vec2 Position, glm::vec4 Color)
//{
//	ShapeData* Check = GetShapeData(TextStart);
//	//Vector
//	float x = Float;
//
//	string floatx = to_string(x);
//
//	string Devision = " ";
//
//
//	//Display 5 Characters only
//	floatx.erase(5);
//
//	string NewText = Devision + floatx;
//	if (Check->Text != NewText || Check->ShapeGroupPosition != Position)
//	{
//		TextSpecification NewFloat1(NewText, Position, false, Color);
//		NewFloat1.Count = NewText.size();
//		NewFloat1.Start = TextStart;
//		ReplaceTextBox(NewFloat1);
//	}
//}
//
//void Page::ChangeInt(int TextStart, int Int, glm::vec2 Position, glm::vec4 Color)
//{
//	ShapeData* Check = GetShapeData(TextStart);
//	//Vector
//	int x = Int;
//
//	string Intx = to_string(x);
//	string Text;
//
//	string Zero = " ";
//
//	if (Intx.size() == 1)
//	{
//		Text = Zero + Zero + Zero + Intx;
//	}
//
//	if (Intx.size() == 2)
//	{
//		Text = Zero + Zero + Intx;
//	}
//
//	if (Intx.size() == 3)
//	{
//		Text = Zero + Intx;
//	}
//
//	if (Intx.size() == 4)
//	{
//		Text = Intx;
//	}
//
//	if (Intx.size() > 4)
//	{
//		Text = Intx.erase(4);
//	}
//
//	if (Check->Text != Text || Check->ShapeGroupPosition != Position)
//	{
//		TextSpecification Int1(Text, Position, false, Color);
//		Int1.Count = Text.size();
//		Int1.Start = TextStart;
//		ReplaceTextBox(Int1);
//	}
//}


void Page::LoadShapeDataFromFile(ShapeData& ShapeData)
{
	ShapeContainer.Add(ShapeData);
}

void Page::LoadVertexFromFile(ShapeVertex& Vertex)
{
	VertexContainer.Add(Vertex);
}

void Page::LoadIndexFromFile(int& Index)
{
	IndexContainer.Add(Index);
}

void Page::ErasePage()
{
	ShapeContainer.DeleteStripNEW(0, ShapeContainer.CurrentContainerAmount, ShapeZero);
	VertexContainer.DeleteStripNEW(0, VertexContainer.CurrentContainerAmount, VertexZero);
	IndexContainer.DeleteStripNEW(0, IndexContainer.CurrentContainerAmount, 0);
	LoadThisPage();
}


void Page::HideTextBox(int TextStart, bool MouseAccess)
{
	ShapeData* Buffer = GetShapeDataP(TextStart);

	for (int i = TextStart; i < TextStart + Buffer->ShapeGroup.ShapeCount; i++)
	{
		HideShapeData(i, MouseAccess);
	}

}

void Page::UnHideTextBox(int TextStart, float AlphaChannel , bool MouseAccess)
{
	ShapeData* Buffer = GetShapeDataP(TextStart);

	for (int i = TextStart; i < TextStart + Buffer->ShapeGroup.ShapeCount; i++)
	{
		UnHideShapeData(i, AlphaChannel, MouseAccess);
	}


}


int Page::ShapeAmount()
{
	return this->ShapeContainer.CurrentContainerAmount;
}



// Scroll is(ScrollOffset * ResizeSpeed)




//void Page::ProccessGridSelection(int GridShapeData, int PixelOffset, int MouseState, KeyResult KeyState, MouseManager Mouse, glm::vec2 Scroll)
//{
//
//	
//	//Safety Check
//	if (GridShapeData == -1) return;
//
//	//Mouse Toggle
//	if (MouseState == GUI_MOUSELEFT_CLICKED && KeyState.Shift == true) { Mouse.Toggle(this->GMouseControl); };
//
//	//Mouse Control
//	if (GMouseControl == true) { GridMouseControl(GridShapeData, Mouse, Scroll, KeyState.Shift); };
//
//	//Control Grid Position
//	ShapeGroupPositionDetailed(GridShapeData, PixelOffset, KeyState); // Always
//
//	//Control Grid Size
//	ShapeGroupSizeDetailed(GridShapeData, PixelOffset, KeyState);  // with None
//
//	//Control Grid ShapeData Size
//    GridShapeSizeDetailed(GridShapeData, PixelOffset, KeyState); //  with Shift
//
//	//Control Grid XY ShapeDatasPerRow
//	GridXYDetailed(GridShapeData, PixelOffset, KeyState); // with Ctrl
//}
//
//
//
//void Page::GridMouseControl(int Grid, MouseManager Mouse, glm::vec2 Scroll, bool Shift)
//{
//	ChangeShapeGroupPosition(Grid, {Mouse.xPos, Mouse.yPos}, 'B', true);
//	
//	if (Shift == false)
//	{
//		OffsetShapeGroupSize(Grid, Scroll, 'B', true);
//	}
//	else
//	{
//		OffsetGridShapeSize(Grid, Scroll, 'B');
//	}
//}
//
//
//void Page::ShapeGroupPositionDetailed(int Grid, int PixelOffset, KeyResult KeyState)
//{
//	//Move Up
//	if (KeyState.Key1 == GUI_UP_CLICKED || KeyState.Key1 == GUI_UP_PRESSED)
//	{
//		OffsetShapeGroupPosition(Grid, glm::vec2(0.0, PixelOffset * 0.0033), 'y', true);
//	}
//
//	//Move Down
//	if (KeyState.Key1 == GUI_DOWN_CLICKED || KeyState.Key1 == GUI_DOWN_PRESSED)
//	{
//		OffsetShapeGroupPosition(Grid, glm::vec2(0.0, -PixelOffset * 0.0033), 'y', true);
//	}
//
//	//Move Right
//	if (KeyState.Key1 == GUI_RIGHT_CLICKED || KeyState.Key1 == GUI_RIGHT_PRESSED)
//	{
//		OffsetShapeGroupPosition(Grid, glm::vec2(PixelOffset * 0.00165, 0.0), 'x', true);
//	}
//
//	//Move Left
//	if (KeyState.Key1 == GUI_LEFT_CLICKED || KeyState.Key1 == GUI_LEFT_PRESSED)
//	{
//		OffsetShapeGroupPosition(Grid, glm::vec2(-PixelOffset * 0.00165, 0.0), 'x', true);
//	}
//}
//
//void Page::ShapeGroupSizeDetailed(int Grid, int PixelOffset, KeyResult KeyState)
//{
//	//Check
//	if (KeyState.Shift == true || KeyState.Ctrl == true) return;
//
//	//Move Up
//	if (KeyState.Key1 == GUI_W_CLICKED || KeyState.Key1 == GUI_W_PRESSED)
//	{
//		OffsetShapeGroupSize(Grid, glm::vec2(0.0, -PixelOffset * 0.0033), 'y', true);
//	}
//
//	//Move Down
//	if (KeyState.Key1 == GUI_S_CLICKED || KeyState.Key1 == GUI_S_PRESSED)
//	{
//		OffsetShapeGroupSize(Grid, glm::vec2(0.0, PixelOffset * 0.0033), 'y', true);
//	}
//
//	//Move Right
//	if (KeyState.Key1 == GUI_D_CLICKED || KeyState.Key1 == GUI_D_PRESSED)
//	{
//		OffsetShapeGroupSize(Grid, glm::vec2(PixelOffset * 0.0033, 0.0), 'x', true);
//	}
//
//	//Move Left
//	if (KeyState.Key1 == GUI_A_CLICKED || KeyState.Key1 == GUI_A_PRESSED)
//	{
//		OffsetShapeGroupSize(Grid, glm::vec2(-PixelOffset * 0.0033, 0.0), 'x', true);
//	}
//}
//
//
//
//void Page::GridShapeSizeDetailed(int Grid, int PixelOffset, KeyResult KeyState)
//{   
//	//Check
//	if (KeyState.Shift == false || KeyState.Ctrl == true) return;
//
//	//Y Size Increase
//	if (KeyState.Key1 == GUI_W_CLICKED || KeyState.Key1 == GUI_W_PRESSED)
//	{
//		OffsetGridShapeSize(Grid, glm::vec2(0.0, -PixelOffset * 0.01), 'y');
//	}
//	//Y Size Decrease
//	if (KeyState.Key1 == GUI_S_CLICKED || KeyState.Key1 == GUI_S_PRESSED)
//	{
//		OffsetGridShapeSize(Grid, glm::vec2(0.0, PixelOffset * 0.01), 'y');
//	}
//	//X Size Increase
//	if (KeyState.Key1 == GUI_D_CLICKED || KeyState.Key1 == GUI_D_PRESSED)
//	{
//		OffsetGridShapeSize(Grid, glm::vec2(PixelOffset * 0.01, 0.0), 'x');
//	}
//	//X Size Decrease
//	if (KeyState.Key1 == GUI_A_CLICKED || KeyState.Key1 == GUI_A_PRESSED)
//	{
//		OffsetGridShapeSize(Grid, glm::vec2(-PixelOffset * 0.01, 0.0), 'x');
//	}
//}
//
//void Page::GridXYDetailed(int Grid, int PixelOffset, KeyResult KeyState)
//{
//	//Function Pass
//	if (KeyState.Ctrl == false) return;
//
//	//Y Row Increase
//	if (KeyState.Key1 == GUI_W_CLICKED || KeyState.Key1 == GUI_W_PRESSED)
//	{
//		OffsetGridXYShapePerRow(Grid, glm::vec2(0.0, -1.0), 'y');
//	}
//
//	//Y Row Decrease
//	if (KeyState.Key1 == GUI_S_CLICKED || KeyState.Key1 == GUI_S_PRESSED)
//	{
//		OffsetGridXYShapePerRow(Grid, glm::vec2(0.0, 1.0), 'y');
//	}
//
//	//X Row Increase
//	if (KeyState.Key1 == GUI_D_CLICKED || KeyState.Key1 == GUI_D_PRESSED)
//	{
//		OffsetGridXYShapePerRow(Grid, glm::vec2(1.0, 0.0), 'x');
//	}
//
//	//X Row Decrease
//	if (KeyState.Key1 == GUI_A_CLICKED || KeyState.Key1 == GUI_A_PRESSED)
//	{
//		OffsetGridXYShapePerRow(Grid, glm::vec2(-1.0, 0.0), 'x');
//	}
//}
//
//////////////////////////////////////////////////////////////
///////////////////////
//void Page::ProcessShapeDataSelection(int ShapeData, int PixelOffset, int MouseState, KeyResult KeyState, MouseManager Mouse, glm::vec2 Scroll)
//{
//	if (ShapeData == -1) return;
//
//	//Mouse Toggle
//	if (MouseState == GUI_MOUSELEFT_CLICKED && KeyState.Shift == false && LastShapeDataHovered != -1) { Mouse.Toggle(this->EMouseControl); };
//
//	//Mouse Control
//	if (EMouseControl == true) { ShapeDataMouseControl(ShapeData, Mouse, Scroll); };
//
//	//Control ShapeData Position
//	ShapeDataPositionDetailed(ShapeData, PixelOffset, KeyState); // Always
//
//	//Control ShapeData Size
//	ShapeDataSizeDetailed(ShapeData, PixelOffset, KeyState);  // with None
//}
//
//
//void Page::ShapeDataMouseControl(int ShapeData, MouseManager Mouse, glm::vec2 Scroll)
//{
//	ChangeShapeDataPosition(ShapeData, { Mouse.xPos, Mouse.yPos }, 'B', true, true);
//
//	OffsetShapeDataSize(ShapeData, Scroll, 'B', true, true);
//}
//
//void Page::ShapeDataPositionDetailed(int ShapeData, int PixelOffset, KeyResult KeyState)
//{
//	//Move Up
//	if (KeyState.Key1 == GUI_UP_CLICKED || KeyState.Key1 == GUI_UP_PRESSED)
//	{
//		OffsetShapeDataPosition(ShapeData, glm::vec2(0.0, PixelOffset * 0.0033), 'y', true);
//	}
//
//	//Move Down
//	if (KeyState.Key1 == GUI_DOWN_CLICKED || KeyState.Key1 == GUI_DOWN_PRESSED)
//	{
//		OffsetShapeDataPosition(ShapeData, glm::vec2(0.0, -PixelOffset * 0.0033), 'y', true);
//	}
//
//	//Move Right
//	if (KeyState.Key1 == GUI_RIGHT_CLICKED || KeyState.Key1 == GUI_RIGHT_PRESSED)
//	{
//		OffsetShapeDataPosition(ShapeData, glm::vec2(PixelOffset * 0.00165, 0.0), 'x', true);
//	}
//
//	//Move Left
//	if (KeyState.Key1 == GUI_LEFT_CLICKED || KeyState.Key1 == GUI_LEFT_PRESSED)
//	{
//		OffsetShapeDataPosition(ShapeData, glm::vec2(-PixelOffset * 0.00165, 0.0), 'x', true);
//	}
//}
//
//void Page::ShapeDataSizeDetailed(int ShapeData, int PixelOffset, KeyResult KeyState)
//{
//	
//	//Move Up
//	if (KeyState.Key1 == GUI_W_CLICKED || KeyState.Key1 == GUI_W_PRESSED)
//	{
//		OffsetShapeDataSize(ShapeData, glm::vec2(0.0, -PixelOffset * 0.0033), 'y', true, true);
//	}
//
//	//Move Down
//	if (KeyState.Key1 == GUI_S_CLICKED || KeyState.Key1 == GUI_S_PRESSED)
//	{
//		OffsetShapeDataSize(ShapeData, glm::vec2(0.0, PixelOffset * 0.0033), 'y', true, true);
//	}
//
//	//Move Right
//	if (KeyState.Key1 == GUI_D_CLICKED || KeyState.Key1 == GUI_D_PRESSED)
//	{
//		OffsetShapeDataSize(ShapeData, glm::vec2(PixelOffset * 0.0033, 0.0), 'x', true, true);
//	}
//
//	//Move Left
//	if (KeyState.Key1 == GUI_A_CLICKED || KeyState.Key1 == GUI_A_PRESSED)
//	{
//		OffsetShapeDataSize(ShapeData, glm::vec2(-PixelOffset * 0.0033, 0.0), 'x', true, true);
//	}
//
//}
//
//
//glm::vec4 Page::ProcessColorSelection(int ColorShapeData, int ColorSelectID, int BarID, int MouseState, MouseManager Mouse, Page& Page)
//{
//	if (ColorShapeData == -1) return {0.0, 0.0, 0.0, 0.0};
//	ShapeData* Buffer = Page.GetShapeData(ColorShapeData);
//
//	//Place the bars according to the ShapeDatas color
//	SetColorBars(Buffer->Color, ColorSelectID);
//
//	//Process User input for changing the bars
//	glm::vec4 NewColor = UserBarSetter(Page, ColorShapeData, MouseState, Mouse, BarID, ColorSelectID);
//
//	//Set the Details Color box
//	ChangeShapeDataColor(BarID - 1, NewColor, true);
//
//	//Set the User input color
//	Page.ChangeShapeDataColor(ColorShapeData, NewColor, true);
//
//	//cout << "New Color: " << NewColor[0] << " " << NewColor[1] << " " << NewColor[2] << " " << NewColor[3] << endl;
//
//	return NewColor;
//}
//
////returns Position of ratios
//glm::vec4 Page::SetColorBars(glm::vec4 Color, int ColorSelectID)
//{
//
//	//Get the Ratio between the max and mix of each bar
//	float RedSelectPosition = -0.0896 + Color[0] * 0.179;
//	float GreenSelectPosition = -0.0896 + Color[1] * 0.179;
//	float BlueSelectPosition = -0.0896 + Color[2] * 0.179;
//	float AlphaSelectPosition = -0.0896 + Color[3] * 0.179;
//
//	ChangeShapeDataPosition(ColorSelectID, {0.0, RedSelectPosition}, 'y', false, true);
//	ChangeShapeDataPosition(ColorSelectID + 1, { 0.0, GreenSelectPosition }, 'y', false, true);
//	ChangeShapeDataPosition(ColorSelectID + 2, { 0.0, BlueSelectPosition }, 'y', false, true);
//	ChangeShapeDataPosition(ColorSelectID + 3, { 0.0, AlphaSelectPosition }, 'y', false, true);
//
//	return { RedSelectPosition, GreenSelectPosition , BlueSelectPosition , AlphaSelectPosition };
//}
//
//glm::vec4 Page::UserBarSetter(Page& Page, int ColorShapeData, int MouseState, MouseManager Mouse, int BarID, int ColorSelectID)
//{
//	//Editor Side
//	ShapeData* Buffer = Page.GetShapeData(ColorShapeData);
//
//	//GUI Side
//	if (MouseState == GUI_MOUSELEFT_CLICKED || MouseState == GUI_MOUSELEFT_PRESSED)
//	{
//		//GUI Side
//		if (Mouse.yPos < 0.0896 && Mouse.yPos > -0.0896 && LastShapeDataHovered == BarID)
//		{
//			ChangeShapeDataPosition(ColorSelectID, { 0.0, Mouse.yPos }, 'y', false, true);
//			
//			Buffer->Color[0] = (Mouse.yPos + 0.0896) / 0.179;
//		}
//
//		//GUI Side
//		if (Mouse.yPos < 0.0896 && Mouse.yPos > -0.0896 && LastShapeDataHovered == BarID + 1)
//		{
//			ChangeShapeDataPosition(ColorSelectID + 1, { 0.0, Mouse.yPos }, 'y', false, true);
//			Buffer->Color[1] = (Mouse.yPos + 0.0896) / 0.179;
//		}
//
//		//GUI Side
//		if (Mouse.yPos < 0.0896 && Mouse.yPos > -0.0896 && LastShapeDataHovered == BarID + 2)
//		{
//			ChangeShapeDataPosition(ColorSelectID + 2, { 0.0, Mouse.yPos }, 'y', false, true);
//			Buffer->Color[2] = (Mouse.yPos + 0.0896) / 0.179;
//		}
//		
//		//GUI Side
//		if (Mouse.yPos < 0.0896 && Mouse.yPos > -0.0896 && LastShapeDataHovered == BarID + 3)
//		{
//			ChangeShapeDataPosition(ColorSelectID + 3, { 0.0, Mouse.yPos }, 'y', false, true);
//			Buffer->Color[3] = (Mouse.yPos + 0.0896) / 0.179;
//		}
//	}
//
//	////EditorSide
//	//Page.ChangeShapeDataColor(ColorShapeData, Buffer->Color, true);
//	//cout << Buffer->Color[0] << " " << Buffer->Color[1] << " " << Buffer->Color[2] << " " << Buffer->Color[3] << endl;
//	return  Buffer->Color;
//}

//void Page::ReplaceWithHighlight(ShapeData& CurrentShapeData)
//{
//
//	if (CurrentShapeData.ShapeDataisHighlight) return;
//
//	if (CurrentShapeData.Highlighted)
//	{
//		ShapeData* Highlight = GetShapeData(CurrentShapeData.ID - 1);
//		if (Highlight->ShapeDataisHighlight == true)
//		{
//			Highlight->Position = CurrentShapeData.Position;
//			Highlight->Size = CurrentShapeData.HighlightSize;
//			ReplaceShapeData(CurrentShapeData.ID - 1, *Highlight, true, false);
//		}
//
//		
//		ReplaceShapeData();
//	}
//	else
//	{
//
//	}
//
//}


void Page::AddShape(ShapeData& Shape)
{

	//Really Amount + 1 //
	Shape.ID = ShapeAmount();

	//if (Shape.Type == TYPE_SHAPE)
	//{
	//	this->ShapeGroupCount++;
	//    Shape.ShapeGroup.ID = this->ShapeGroupCount;
	//	Shape.ShapeGroup.ShapeStart = Shape.ID;
	//	Shape.ShapeGroup.ShapeCount = 0;
	//	Shape.ShapeGroup.ShapeOffset = 0;
	//}

	Shape.Top = (Shape.Position.y + Shape.Size.y/2);
	Shape.Bottom = (Shape.Position.y - Shape.Size.y/2);
	Shape.Left = (Shape.Position.x - Shape.Size.x/2);
	Shape.Right = (Shape.Position.x + Shape.Size.x/2);

	ShapeContainer.Add(Shape);
	VertexContainer.Add(Shape.Vertex[0]);
	VertexContainer.Add(Shape.Vertex[1]);
	VertexContainer.Add(Shape.Vertex[2]);
	VertexContainer.Add(Shape.Vertex[3]);
}

void Page::ReplaceShape(ShapeData& Shape)
{
	int VertexCount = 4;

	//Replace if Shape Exists & in Bounds
	if (Shape.ID != -1 && Shape.ID < ShapeAmount())
	{
		//Replace Shape
		ShapeContainer.Replace(Shape.ID, Shape);

		//Replace Shape Vertices
		VertexContainer.Replace(Shape.ID * VertexCount + 0, Shape.Vertex[0]);
		VertexContainer.Replace(Shape.ID * VertexCount + 1, Shape.Vertex[1]);
		VertexContainer.Replace(Shape.ID * VertexCount + 2, Shape.Vertex[2]);
		VertexContainer.Replace(Shape.ID * VertexCount + 3, Shape.Vertex[3]);
	}
	else
	{
		cout << "REPLACE::SHAPE::ERROR::Shape Not Set " << "ID: " << Shape.ID << endl;
	}
}



//void Page::DeleteShape(ShapeData& Shape)
//{
//	ShapeContainer.DeleteStripNEW(Shape.ID, 1, Zero1);
//	VertexContainer.DeleteStripNEW(Shape.ID * 4, 4, Zero2);
//}

//ShapeData* Page::GetShape(int& ID)
//{
//	return ShapeContainer.RetrieveDataP(ID);
//}

ShapeData* Page::GetNextShapeAddress()
{
	return ShapeContainer.StartOfContainer + ShapeAmount();
}

ShapeData* Page::GetNextShapeAddress(int Offset)
{
	return ShapeContainer.StartOfContainer + ShapeAmount() + Offset;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

