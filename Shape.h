#ifndef  SHAPE
#define  SHAPE

#define	VERTEX0 0
#define	VERTEX1 1
#define	VERTEX2 2 
#define VERTEX3 3

#include <iostream>
#include "MasterElement.h"
#include "Page.h"

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

	Shape(Page& Page);                       //New Shape
	Shape(Page& Page, ShapeData& ShapeData); //New Shape with existing Data
	Shape(Page& Page, int ShapeDataID);      //Existing Shape
	~Shape();

	void Init(Page& Page, int QuadID)
	{
		this->CurrentPage = &Page;
		if (QuadID != -1)
		{
			CurrentShapeData = Page.GetShapeDataR(QuadID);
		}
		cout << "Quad Selected ID: " << QuadID << endl;
		CurrentShapeData.Position = {0.0, 0.0};
		CurrentShapeData.Size = {0.5, 0.5};
		Add_Default();
	};


	glm::vec2 TopRightXYRatio;
	glm::vec2 BottomRightXYRatio;
	glm::vec2 BottomLeftXYRatio;
	glm::vec2 TopLeftXYRatio;

	Page* CurrentPage;
	ShapeData CurrentShapeData;
	const bool SetInStone; //class cannot switch to another Shape 

    //Shape Creation functions

	virtual void Update() = 0; // All
	virtual void SetAction(int ShapeDataActionID ) = 0;
	virtual void SetShapeRatios() = 0;
	virtual void BuildShapeVertices() = 0;
	
	void PrintShape()
	{
		CurrentPage->PrintShape(CurrentShapeData.ID);
	}

	void UpdateMouseAccess();

	//ShapeData Editing
	void Add_Default() override; //Editor/None Set in Stone
	void Add_Duplicate() override; //Editor/None Set in Stone
	void Add_Insert() override; //Editor/None Set in Stone
	void DeleteShape() override;
	void SwitchToShape(int RequstedShapeID) override;
	void SwitchToShape(Page& Page, int RequstedShapeID);
	void SetShape(ShapeData& ShapeData);
	void SetShape(ShapeData& ShapeData, glm::vec2 PSConversions);
	void SetPosition(glm::vec2 Position) override;                     //Set All
	void SetPosition(glm::vec2 Position, glm::vec2 bools) override;    //Set all with true boolean(s)
	void SetSize(glm::vec2 Size) override;                             //Set All
	void SetSize(glm::vec2 Size, glm::vec2 bools) override;            //Set all with true boolean(s)
	void SetColor(glm::vec4 Color) override;                           //..
	void SetColor(glm::vec4 Color, glm::vec4 bools) override;          //...

	// W/ Conversions
	void SetPosition(glm::vec2 Position, int Conversion);                     //Set All
	void SetPosition(glm::vec2 Position, glm::vec2 bools, int Conversion);    //Set all with true boolean(s)
	void SetSize(glm::vec2 Size, int Conversion);                             //Set All
	void SetSize(glm::vec2 Size, glm::vec2 bools, int Conversion);            //Set all with true boolean(s)

	void OffsetPosition(glm::vec2 Position);                  //..
	void OffsetPosition(glm::vec2 Position, glm::vec2 bools); //...
	void OffsetSize(glm::vec2 Size);                          //..
	void OffsetSize(glm::vec2 Size, glm::vec2 bools);         //...
	void OffsetColor(glm::vec4 Color);                        //..
	void OffsetColor(glm::vec4 Color, glm::vec4 bools);       //...

	// W/ Conversions
	void OffsetPosition(glm::vec2 Position, int Conversion);                  //..
	void OffsetPosition(glm::vec2 Position, glm::vec2 bools, int Conversion); //...
	void OffsetSize(glm::vec2 Size, int Conversion);                          //..
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
	
	Shape* ShapeDataPosToMousePos(Shape* ShapeData, glm::vec2 MousePosition, bool Centered);

	glm::vec2 ApplyPositionConversion(glm::vec2 Position, int Conversion);
	glm::vec2 ApplySizeConversion(glm::vec2 Position, int Conversion);

	//Position TopLeft/BottomLeft Conversions 
	glm::vec2 PTLPixelToComputer(glm::vec2 Position); //Working
	glm::vec2 PBLPixelToComputer(glm::vec2 Position); //Working
	glm::vec2 PMiddleToTopLeft(glm::vec2 Position, glm::vec2 Size);

	glm::vec2 PComputerToTLPixel(glm::vec2 Position); //Working
	glm::vec2 PComputerToBLPixel(glm::vec2 Position); //Working
    

	//SizeConversions
	glm::vec2 SPixelToComputer(glm::vec2 Size); //Working
	glm::vec2 SOneToComputer(glm::vec2 Size);   //Working

	glm::vec2 SComputerToPixel(glm::vec2 Size); //Working
	glm::vec2 SComputerToOne(glm::vec2 Size);   //Working


private:
};


#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////HIGHLIGHT FUNCTIONS DONT DELETE/////////////////////////////////////////////////////
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