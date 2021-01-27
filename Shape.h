#ifndef  SHAPE
#define  SHAPE

#define	VERTEX0 0
#define	VERTEX1 1
#define	VERTEX2 2 
#define VERTEX3 3

#include <iostream>
#include "MasterElement.h"
#include "Page.h"
#include "Log.h"

using namespace std;

//Position Conversions
#define P_PIXEL_TO_COMPUTER 1
#define MIDDLE_TO_TOPLEFT 2
#define TOPLEFT_PIXEL_TO_COMPUTER 3
#define P_COMPUTER_TO_PIXEL 4

//Size Conversions
#define S_PIXEL_TO_COMPUTER 1
#define S_ONE_TO_COMPUTER 2
#define S_COMPUTER_TO_PIXEL 3



class Shape : public MasterElement
{

public:
	glm::vec2 TopRightXYRatio;
	glm::vec2 BottomRightXYRatio;
	glm::vec2 BottomLeftXYRatio;
	glm::vec2 TopLeftXYRatio;

	ShapeData CurrentShapeData;
	llShapeData* CurrentllShape;
	
	llVertexData* VertexTopRight;
	llVertexData* VertexBottomRight;
	llVertexData* VertexBottomLeft;
	llVertexData* VertexTopLeft;

	const bool SetInStone; //class cannot switch to another Shape 

	Shape(llBookData* llBookData);
	Shape(llBookData* llBookData, llShapeData* llShapeData);
	Shape(llShapeData* llShapeData);
	Shape(Page& Page);                       //New Shape
	Shape(Page& Page, ShapeData& ShapeData); //New Shape with existing Data
	Shape(Page& Page, int ShapeDataID);      //Existing Shape
	void Init(Page& Page, int QuadID);
	~Shape();

	////Shape Editing////

	//Creator Functions
	void Add_Default() override; //Editor/None Set in Stone
	void Add_Duplicate() override; //Editor/None Set in Stone
	void Add_Insert() override; //Editor/None Set in Stone
	void Delete() override;
	ShapeData& Switch(int RequstedShapeID) override;
	ShapeData& Switch(Page& Page, int RequstedShapeID) override;
	void PrintShape();

	void PrintllVertices()
	{
		Log::LogString("Trying to print llShapes");
		llVertexData* WorkingVertex = CurrentllShape->Vertexx;
		while (WorkingVertex != nullptr)
		{
			Log::LogVec4( "llShape: ", WorkingVertex->Color);
			WorkingVertex = WorkingVertex->Next;
		}
	}

	void SetShapeGroupOffsets()
	{

		//Iteration Setup
		int PageItemID = LoadedShape.ShapeGroup.PageItem.ID;
		int ShapeGroupID = LoadedShape.ShapeGroup.ID;
		int PageGroupStart = LoadedShape.ShapeGroup.PageItem.PageGroup.ShapeStart;
		int PageGroupCount = LoadedShape.ShapeGroup.PageItem.PageGroup.ShapeStart + LoadedShape.ShapeGroup.PageItem.PageGroup.ShapeCount;

		//Resetting Group Counts
		CurrentPage->CurrentPageGroupShapeCount = -1;
		CurrentPage->CurrentPageItemShapeCount = -1;
		CurrentPage->CurrentShapeGroupShapeCount = -1;
		CurrentPage->CurrentShapeGroup = 0;

		//Setting Offsets
		for (int i = PageGroupStart; i < PageGroupCount; i++)
		{
			//PageGroup Offsets
			LoadedShape = CurrentPage->GetShapeDataR(i);
			CurrentPage->CurrentPageGroupShapeCount++;
			LoadedShape.ShapeGroup.PageItem.PageGroup.ShapeOffset = CurrentPage->CurrentPageItemShapeCount;

			//PageItem Offsets
			if (LoadedShape.ShapeGroup.PageItem.ID == PageItemID)
			{ 
				CurrentPage->CurrentPageItemShapeCount++;
				LoadedShape.ShapeGroup.PageItem.ShapeOffset = CurrentPage->CurrentPageItemShapeCount;
				Log::LogString("How many you see is page item count");

				//ShapeGroup Offsets
				if (LoadedShape.ShapeGroup.ID == PageItemID)
				{
					CurrentPage->CurrentShapeGroupShapeCount++;
					LoadedShape.ShapeGroup.ShapeOffset = CurrentPage->CurrentShapeGroupShapeCount;
				}
			}
		}
	};


	// Basic
	void SetPosition(glm::vec2 Position) override;                     //Set All
	void SetSize(glm::vec2 Size) override;                             //Set All
	void SetColor(glm::vec4 Color) override;                           //..
	void OffsetPosition(glm::vec2 Position);                           //..
	void OffsetSize(glm::vec2 Size);                          //..
	void OffsetColor(glm::vec4 Color);                        //..
	void SetPosition(glm::vec2 Position, glm::vec2 bools) override;    //Set all with true boolean(s)
	void SetSize(glm::vec2 Size, glm::vec2 bools) override;            //Set all with true boolean(s)
	
	// Basic + boolean
	void SetColor(glm::vec4 Color, glm::vec4 bools) override;          //...
	void OffsetPosition(glm::vec2 Position, glm::vec2 bools); //...
	void OffsetSize(glm::vec2 Size, glm::vec2 bools);         //...
	void OffsetColor(glm::vec4 Color, glm::vec4 bools);       //...

	// Basic + Conversions
	void SetPosition(glm::vec2 Position, int Conversion);                     //Set All
	void SetSize(glm::vec2 Size, int Conversion);                             //Set All
	void OffsetPosition(glm::vec2 Position, int Conversion);                  //..
	void OffsetSize(glm::vec2 Size, int Conversion);                          //..

	// Basic + Conversions + boolean
	void SetPosition(glm::vec2 Position, glm::vec2 bools, int Conversion);    //Set all with true boolean(s)
	void SetSize(glm::vec2 Size, glm::vec2 bools, int Conversion);            //Set all with true boolean(s)
	void OffsetPosition(glm::vec2 Position, glm::vec2 bools, int Conversion); //...
	void OffsetSize(glm::vec2 Size, glm::vec2 bools, int Conversion);         //...

	//Vertex Editing
	void SetVertexPosition(int Index, glm::vec2& Position);
	void SetVertexColor(int Index, glm::vec4& Color);
	void SetVertexTexCoords(int Index, glm::vec2& TextureCoordinates);
	void SetVertexGuiAction(int Index, int& Action);
	void SetVertexCentralPoint(int Index, glm::vec2& CentralPoint);
	void SetVertexTextureIndex(int Index, float& TextureIndex);
	void OffsetVertexPosition(int Index, glm::vec2& Position);
	void OffsetVertexColor(int Index, glm::vec4& Color);
	void OffsetVertexTexCoords(int Index, glm::vec2& TextureCoordinates);
	void OffsetVertexGuiAction(int Index, int& Action);
	void OffsetVertexCentralPoint(int Index, glm::vec2& CentralPoint);
	void OffsetVertexTextureIndex(int Index, float& TextureIndex);


	virtual void Update() = 0; // All
	virtual void SetAction(int ShapeDataActionID) = 0;
	virtual void SetShapeRatios() = 0;
	virtual void BuildShapeVertices() = 0;
	void UpdateMouseAccess();
	void UpdatellMouseAccess();
	void SetShape(ShapeData& ShapeData);
	void SetShape(ShapeData& ShapeData, glm::vec2 PSConversions);

protected:

	//Shape* ShapeDataPosToMousePos(Shape* ShapeData, glm::vec2 MousePosition, bool Centered);
};


#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////HIGHLIGHT FUNCTIONS DONT DELETE////////////YOU WILL NEED IT IN YOUR LIFE////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

//int* FindMultiSelect(int Layer, ShapeData MultiSelect, bool Print, int* ShapeDatasSelected, int SelectionLimit);
//int MultiFindx(ShapeData* Result, float x1, float x2);
//int MultiFindy(ShapeData* Result, float y1, float y2);
//int* Page::FindMultiSelect(int Layer, ShapeData MultiSelect, bool Print, int* ShapeDatasSelected, int SelectionLimit)
//{
//	if (Layer < 10)
//	{
//		int SelectionCount = 0;
//		//loop Setup
//		int LayerStart = this->Layer[CurrentLayer].LayerID;
//		int LayerEnd = ((ShapeContainer.CurrentContainerAmount + LayerStart) - 1);
//		//	cout << "ShapeDataCount: " << this->Layer[CurrentLayer].ShapeDataCount << endl;
//			//cout << "Layer Start: "<< LayerStart << endl;
//			//cout << "Layer End: "<< LayerEnd << endl;
//			//search for ShapeData backwards to always get the ShapeData furthest to the user screen
//			//and skip the MultiSelect ShapeData
//		for (int i = LayerEnd; i >= LayerStart; i--)
//		{
//			//cout << "HAPPENING" << endl;
//			ShapeData* Result = ShapeContainer.RetrieveDataP(i);
//			Result->ID = i;
//
//			float x1 = MultiSelect.Position[0];
//			float x2 = MultiSelect.Position[0] + MultiSelect.Size[0];
//			float y1 = MultiSelect.Position[1];
//			float y2 = MultiSelect.Position[1] - MultiSelect.Size[1];
//
//			int Outputx = MultiFindx(Result, x1, x2);
//			int Outputy = MultiFindy(Result, y1, y2);
//
//
//			if (SelectionCount == SelectionLimit - 1)
//			{
//				return ShapeDatasSelected;
//			}
//			else if (Outputx == Outputy && Outputx != -1)
//			{
//				//cout << "Found Multi:" << Outputy << endl;
//				ShapeDatasSelected[SelectionCount] = Outputx; //can be output x or y doesn't matter
//				//ShapeDatasSelected++;
//				SelectionCount++;
//			}
//		}
//		return ShapeDatasSelected;
//	}
//	return nullptr;
//}
//
//int Page::MultiFindx(ShapeData* Result, float x1, float x2)
//{
//	//cout << "------------------------------------------------------------------------------" << endl;
//	//cout << "Left: " << Result->Left << endl;
//	//cout << "Right: " << Result->Right << endl;
//	//cout << "x1: " << x1 << endl;
//	//cout << "x2: " << x2 << endl;
//
//
//	//Return ID if in bounds (All Paths)
//	if (x1 > Result->Left&& x1 < Result->Right) //(Result->Right > x1 && Result->Right < x2
//	{
//		//ShapeData Within xbounds
//		//cout << "Found(x1): " << Result->ID << endl;
//		return Result->ID;
//	}
//
//	if (x2 > Result->Left&& x2 < Result->Right) //Result->Left > x1 && Result->Left < x2
//	{
//		//ShapeData Within xbounds
//	 // cout << "Found(x2): " << Result->ID << endl;
//		return Result->ID;
//	}
//
//	//cout << "None in the x for ShapeData:" << Result->ID << endl;
//
//	return -1;
//}
//
//int Page::MultiFindy(ShapeData* Result, float y1, float y2)
//{
//
//	//cout << "Top: " << Result->Top << endl;
//	//cout << "Bottom: " << Result->Bottom << endl;
//	//cout << "y1: " << y1 << endl;
//	//cout << "y2: " << y2 << endl;
//
//
//	if (y1 > Result->Bottom&& y1 < Result->Top) //Result->Top < y1 && Result->Top > y2
//	{
//		//ShapeData Within ybounds
//		//cout << "Found(y1): " << Result->ID << endl;
//		return Result->ID;
//	}
//
//	if (y2 > Result->Bottom&& y2 < Result->Top) //Result->Bottom < y1 && Result->Top > y2
//	{
//		//ShapeData Within ybounds
//		//cout << "Found(y2): " << Result->ID << endl;
//		return Result->ID;
//	}
//	//cout << "None in the y for ShapeData:" << Result->ID << endl;
//
//	return -1;
//}
//
//