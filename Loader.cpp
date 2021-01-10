#include "Loader.h"

//Calculates all data needed to be stored, Coords, Vertices etc., then stores that data
//void Loader::AddElement(Element* Element, Page &Page, bool Centered)
//{
//	if (Centered == true)
//	{
//		Element->Position[0] += Element->Size[0] / 2;
//		Element->Position[1] -= Element->Size[1] / 2;
//	}
//	Maths maths;
//
//	ElementVertices ElementVertices = maths.GetElementVertices({ Element->Position, 0 }, Element->Size[0], Element->Size[1], false);
//	ElementTexCoords ElementTexCoords = maths.GetBasicTexCoords();
//
//	StoreElement(Page, ElementVertices, ElementTexCoords, Element->Color, Element->ActiveTexture);
//}
//void Loader::EditElement(Element* Element, Page& Page, int ElementNumber, bool Centered)
//{
//	if (Centered == true)
//	{
//		Element->Position[0] += Element->Size[0] / 2;
//		Element->Position[1] -= Element->Size[1] / 2;
//	}
//	Maths maths;
//
//	ElementVertices ElementVertices = maths.GetElementVertices({ Element->Position, 0 }, Element->Size[0], Element->Size[1], false);
//	ElementTexCoords ElementTexCoords = maths.GetBasicTexCoords();
//
//	ReplaceElement(Page, Element->ElementID, ElementVertices, ElementTexCoords, Element->Color, Element->ActiveTexture);
//}





//void AddToLayer(Page& Page, Element& Element, int Layer, bool Centered)
//{
//	Maths Maths;
//	Vertex Vertex;
//
//	if (Centered == true)
//	{
//		Element.Position[0] -= Element.Size[0] / 2;
//		Element.Position[1] += Element.Size[1] / 2;
//	}
//
//	Element.UpdatePosition(Element.Position);
//
//	Element.ElementID = Page.ShapeContainer.CurrentContainerAmount;
//
//	//Page.ShapeContainer.Insert(Element, Page.Layer[Layer].GetElementFillPosition()); //loads Element
//	//might cause errors
//	//Page.VertexContainer.InsertStrip(VertexSpot, 4, Vertex); //loads empty strip in 
//
//	//Vertex = Maths.SetTopRight(Element, Vertex);
//	//Page.VertexContainer.AddSpecific(VertexSpot, Vertex); //fills empty part
//	//
//	//Vertex = Maths.SetBottomRight(Element, Vertex);
//	//Page.VertexContainer.AddSpecific(VertexSpot + 1, Vertex); //fills empty part
//	//
//	//Vertex = Maths.SetBottomLeft(Element, Vertex);
//	//Page.VertexContainer.AddSpecific(VertexSpot + 2, Vertex); //fills empty part
//	//
//	//Vertex = Maths.SetTopLeft(Element, Vertex);
//	//Page.VertexContainer.AddSpecific(VertexSpot + 3, Vertex); //fills empty part
//}



//void SwitchLayer(Page& Page, Element& Zero, int AvailableSpace)
//{
//	int FillPosition = Page.Layer[1].GetFillPosition();
//
//	//where we load the Elements
//
//	Page.Layer[1] =
//
//	//but you will have to change some normal functions
//}


//void Loader::EditElementGrid(int GridElementStart, Page& Page, glm::vec2 XYElementsPerRow, glm::vec2 ShapeGroupSize, glm::vec2 ShapeGroupPosition, glm::vec2 ElementSize, glm::vec4 Color, bool Centered)
//{
//	// Start Editing at the right start
//	Page::ElementPointer = Page.ShapeContainer;
//	Page::ElementPointer += GridElementStart;
//	Maths Maths;
//	if (Centered == true)
//	{
//		ShapeGroupPosition = Maths.CenterToTopLeft(ShapeGroupPosition, ShapeGroupSize);
//	}
//	//Element to load 
//	for (int yElements = 0; yElements < XYElementsPerRow[0]; yElements++)
//	{
//		for (int xElements = 0; xElements < XYElementsPerRow[1]; xElements++)
//		{
//			//Load Basic data in all Elements
//	
//			Page::ElementPointer->Size = Maths.GridShapeSize(ShapeGroupSize, XYElementsPerRow, ElementSize);
//			Page::ElementPointer->Position = Maths.GridElementPosition(ShapeGroupPosition, ShapeGroupSize, XYElementsPerRow, { xElements, yElements }, Centered);
//			Page::ElementPointer->Color = glm::vec4(Color);
//			EditElement(Page::ElementPointer, Page, GridElementStart, Centered);
//			GridElementStart++;
//		}
//	}
//}
//
//
////////////////////////////////////////////////////////Private function?//////////////////////////////////////////////////
//
//void Loader::LoadPage(Page &Page)
//{
//	
//	GLsizeiptr PageSize = (uint8_t*)Page.VertexPointer - (uint8_t*)Page.VertexContainer; // tracker really is where it's stored
//	Page.PageSize = PageSize;
//	Page.ElementSize = Page.PageSize / Page.PageElementCount;
//	cout << "PageSize: " << Page.PageSize << endl;
//	glBindBuffer(GL_ARRAY_BUFFER, Page.VB);
//	glBufferSubData(GL_ARRAY_BUFFER, 0, PageSize, Page.VertexContainer);
//	//we need to set the mouse events inputs
//}

void Loader::LoadPage(Page& Page)
{
	glBindBuffer(GL_ARRAY_BUFFER, Page.VB);
	glBufferSubData(GL_ARRAY_BUFFER, 0, Page.VertexContainer.MaxSize, Page.VertexContainer.StartOfContainer); //
}
//
//
////where to replace, how much do you want to replace, the newdata that is replacing the old one 
//void Loader::ElementUpload(Page Page, Element Element)
//{
//	//Size (in bytes)
//	GLsizeiptr PageByteSize = (uint8_t*)Page.VertexPointer - (uint8_t*)Page.VertexContainer; // tracker really is where it's stored
//	GLsizeiptr ElementByteSize = PageByteSize / Page.PageElementCount; //MIGHT BE WRONG 
//	int Offset = ElementByteSize * Element.ElementID;
//	glBindBuffer(GL_ARRAY_BUFFER, Page.VB);
//	glBufferSubData(GL_ARRAY_BUFFER, Offset, ElementByteSize, Page.VertexPointer);
//}
//
//void Loader::DrawNewBatch(Page Page)
//{
//	glBindVertexArray(Page.VA);
//	glDrawElements(GL_TRIANGLES, Page.MaxIndexCount, GL_UNSIGNED_INT, nullptr);
//	Page.PageElementCount = 0;
//	Page.PageIndexCount = 0;
//}
//
////for adding single Elements
//
////NO need for BOOL Centering. Data Position needs to come in as top left
//void Loader::StoreElement(Page &Page, ElementVertices& Vertices, ElementTexCoords& TexCoords, glm::vec4& Color, float ActiveTexture)
//{
//	if (Page.PageElementCount >= Page.MaxElementCount)
//	{
//		cout << "Element Capacity Reached :: More Memory Required" << endl;
//		return;
//	}
//
//	Page::VertexPointer->Position = { Vertices.BottomLeft, 0.0 };  //bottom left
//	Page::VertexPointer->TexCoords = { TexCoords.BottomLeft };     //Top Left
//	Page::VertexPointer->Color = { Color };
//	Page::VertexPointer->TexIndex = ActiveTexture;
//	Page::VertexPointer++; // + address of 1 verticy // we are controlling the address of each vertex
//	
//	Page::VertexPointer->Position = { Vertices.BottomRight, 0.0 }; // bottom right
//	Page::VertexPointer->TexCoords = { TexCoords.BottomRight };       //Top Right
//	Page::VertexPointer->Color = { Color };
//	Page::VertexPointer->TexIndex = ActiveTexture;
//	Page::VertexPointer++;
//
//	Page::VertexPointer->Position = { Vertices.TopRight, 0.0 }; // Top Right
//	Page::VertexPointer->TexCoords = { TexCoords.TopRight };        //Bottom Right
//	Page::VertexPointer->Color = { Color };
//	Page::VertexPointer->TexIndex = ActiveTexture;
//	Page::VertexPointer++;
//	
//	Page::VertexPointer->Position = { Vertices.TopLeft, 0.0 }; // Top left
//	Page::VertexPointer->TexCoords = { TexCoords.TopLeft }; // Bottom Lef
//	Page::VertexPointer->TexIndex = ActiveTexture;
//	Page::VertexPointer->Color = { Color };
//
//	
//
//	Page::ElementPointer->PageID = Page.PageElementCount;
//	Page::ElementPointer->ElementID = Page::TotalElementCount;
//	Page::ElementPointer->Address = Page::ElementPointer;
//	Page::ElementPointer->ActiveTexture = ActiveTexture;
//	Page::ElementPointer->Left = Vertices.BottomLeft[0];
//	Page::ElementPointer->Right = Vertices.BottomRight[0];
//	Page::ElementPointer->Top = Vertices.TopLeft[1];
//	Page::ElementPointer->Bottom = Vertices.BottomLeft[1];
//
//	Page::ElementPointer++;
//	Page::VertexPointer++;
//	Page.PageElementCount++;
//	Page::TotalElementCount++;
//
//	//cout << "Page ElementCount: " << Page.PageElementCount << " || Total ElementCount: " << Page::TotalElementCount << endl;
//	//cout << "ElementPointer Address: " << Page::ElementPointer << endl;
//	//cout << "pointer minus cotainer "<< Page::ElementPointer - Page.ShapeContainer << endl;
//
//	// 0, 1, 2, 3, 2, 0
//}
//
//
//
//void Loader::ReplaceElement(Page Page, int PageElementIndex, ElementVertices& Vertices, ElementTexCoords& TexCoords, glm::vec4& Color, float ActiveTexture)
//{
//	cout << Page.PageElementCount << endl;
//	if (Page.PageElementCount >= Page.MaxElementCount)
//	{
//		cout << "Element Capacity Reached :: More Memory Required" << endl;
//		return;
//	}
//
//	Element* ElementBookMark = Page::ElementPointer;
//	Vertex* VertexBookMark = Page::VertexPointer;
//
//	Page::VertexPointer  = Page.VertexContainer; //set pointer to the start
//	//Page::ElementPointer = Page.ShapeContainer; // set pointer to the start
//	Page::VertexPointer += PageElementIndex * 4; // sets pointer to the right spot for writing
//	//Page::ElementPointer += PageElementIndex; // sets pointer to the right spot for writing
//		
//	Page::VertexPointer->Position = { Vertices.BottomLeft, 0.0 };  //bottom left
//	Page::VertexPointer->TexCoords = { TexCoords.BottomLeft };     //Top Left
//	Page::VertexPointer->Color = { Color };
//	Page::VertexPointer->TexIndex = ActiveTexture;
//	Page::VertexPointer++; // + address of 1 verticy // we are controlling the address of each vertex
//		
//	Page::VertexPointer->Position = { Vertices.BottomRight, 0.0 }; // bottom right
//	Page::VertexPointer->TexCoords = { TexCoords.BottomRight };       //Top Right
//	Page::VertexPointer->Color = { Color };
//	Page::VertexPointer->TexIndex = ActiveTexture;
//	Page::VertexPointer++;
//		
//	Page::VertexPointer->Position = { Vertices.TopRight, 0.0 };   // Top Right
//	Page::VertexPointer->TexCoords = { TexCoords.TopRight };        //Bottom Right
//	Page::VertexPointer->Color = { Color };
//	Page::VertexPointer->TexIndex = ActiveTexture;
//	Page::VertexPointer++;
//		
//	Page::VertexPointer->Position = { Vertices.TopLeft, 0.0 };    // Top left
//	Page::VertexPointer->TexCoords = { TexCoords.TopLeft }; // Bottom Lef
//	Page::VertexPointer->TexIndex = ActiveTexture;
//	Page::VertexPointer->Color = { Color };
//	Page::VertexPointer++;
//
//	Page::ElementPointer->PageID = Page.PageElementCount;
//	Page::ElementPointer->ElementID = Page::TotalElementCount;
//	Page::ElementPointer->Address = Page::ElementPointer;
//	Page::ElementPointer->Color = Color;
//	Page::ElementPointer->ActiveTexture = ActiveTexture;
//	Page::ElementPointer->Left = Vertices.BottomLeft[0];
//	Page::ElementPointer->Right = Vertices.BottomRight[0];
//	Page::ElementPointer->Top = Vertices.TopLeft[1];
//	Page::ElementPointer->Bottom = Vertices.BottomLeft[1];
//
//	Page::ElementPointer++;
//	Page::VertexPointer++;
//
//    //sets the Page back to it's position at the end of the batch before the function started 
//	Page::VertexPointer = VertexBookMark;
//	Page::ElementPointer = ElementBookMark;
//}





