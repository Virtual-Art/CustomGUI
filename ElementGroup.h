#ifndef SHAPEGROUP
#define SHAPEGROUP

#include <iostream>
#include "MasterElement.h"
#include "Log.h" 
#include <math.h>
//---Shape Interface---|
#include "Shape.h"
#include "NewCharacter.h"
#include "Quad.h"
#include "CustomShape.h"
//---------------------|



using namespace std;

//struct GroupData
//{
//	Page* Page;
//	unsigned int ShapeStartID;
//	int GroupID;
//	int ShapeOffset; //Offset from start ID
//	unsigned int Count;
//	ShapeData* NextGroup;
//
//	int CellOffset;
//
//	glm::vec2 Position;
//	glm::vec2 Size;
//	glm::vec4 Color;
//
//	bool MouseAccess = true;
//	bool Centered;
//	bool Highlighted;
//	int ShapeType;
//
//	float Left = -3.0;
//	float Right = -3.0;
//	float Top = -3.0;
//	float Bottom = -3.0;
//
//	glm::vec2 XYShapesPerRow;
//	glm::vec2 ShapeDataSize;
//
//	//PageItem
//	glm::vec2 PageItemPosition;
//	glm::vec2 PageItemSize;
//	int PageItemID;
//	int PageItemShapeCount;
//	int PageItemShapeOffset;
//	int PageItemShapeStartID;
//
//	//PageGroup
//	glm::vec2 PageGroupPosition;
//	glm::vec2 PageGroupSize;
//	int PageGroupID;
//	int PageGroupShapeCount;
//	int PageGroupShapeOffset;
//	int PageGroupShapeStartID;
//
//};


class ShapeGroup : public MasterElement
{

 public:


	const bool SetInStone; //class cannot switch to another Shape 

	ShapeGroup();
	ShapeGroup(Page& Page);
	ShapeGroup(Page& Page, ShapeGroupData& ShapeGroupData);
	ShapeGroup(Page& Page, ShapeData& ShapeGroup);
	ShapeGroup(Page& Page, int& GroupID);
	void Init(Page& Page, int GroupID) {};

	void Add_Default() override {};
	void Add_Duplicate() override {};
	void Add_Insert() override {};
	void Delete() override {};
	void Switch(Page& Page, int RequstedShapeID) override {};
	void Switch(int ShapeID) override
	{
		if (Initialized == false) Log::LogString("Switch Error:: Shape Group Not Initialized");  return;
		if (IsInBounds(ShapeID) == false) Log::LogString("Switch Error:: ID out of bounds");
		if (SetInStone != true)
		{
			LoadedShape = CurrentPage->GetShapeDataR(ShapeID);
		}
	}
	void PrintGroupShapes();

	// Basic
	void SetPosition(glm::vec2 Position) override;                    
	void SetSize(glm::vec2 Size) override;                            
	void SetColor(glm::vec4 Color) override;                          
	void OffsetPosition(glm::vec2 Position);                          
	void OffsetSize(glm::vec2 Size);                         
	void OffsetColor(glm::vec4 Color);                       
	void SetPosition(glm::vec2 Position, glm::vec2 bools) override;    
	void SetSize(glm::vec2 Size, glm::vec2 bools) override;            

	// Basic + boolean
	void SetColor(glm::vec4 Color, glm::vec4 bools) override;  
	void OffsetPosition(glm::vec2 Position, glm::vec2 bools); 
	void OffsetSize(glm::vec2 Size, glm::vec2 bools);         
	void OffsetColor(glm::vec4 Color, glm::vec4 bools);       

	// Basic + Conversions
	void SetPosition(glm::vec2 Position, int Conversion);  
	void SetSize(glm::vec2 Size, int Conversion) {};
	void OffsetPosition(glm::vec2 Position, int Conversion);
	void OffsetSize(glm::vec2 Size, int Conversion);       

	// Basic + Conversions + boolean
	void SetPosition(glm::vec2 Position, glm::vec2 bools, int Conversion);    
	void SetSize(glm::vec2 Size, glm::vec2 bools, int Conversion) {};
	void OffsetPosition(glm::vec2 Position, glm::vec2 bools, int Conversion); 
	void OffsetSize(glm::vec2 Size, glm::vec2 bools, int Conversion);         

	int FindNextGroup(int CurrentID, ShapeData* RetreivedShape);
	int FindPreviousGroup(int CurrentID, ShapeData* RetreivedShape);

protected:
	virtual void Update() {};
	void ReCalibrateID();
	//void ShapeToGroup(ShapeData& ShapeData);
	//void GroupToShape(GroupData& GroupData);
	void SetGroup(ShapeData& ShapeData);
	void SetMouseAccess();
	void UpdateMouseAccess(glm::vec2 Position, glm::vec2 Size);

private:

};

#endif