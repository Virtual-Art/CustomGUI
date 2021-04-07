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
#define TYPE_CUSTOM 0
#define TYPE_TEXT 1

using namespace std;

class ShapeGroup : public MasterElement
{

 public:

	ShapeGroupData CurrentShapeGroup;
	llShapeGroupData* CurrentllShapeGroup;
	const bool SetInStone; //class cannot switch to another Shape 

	ShapeGroup();
	ShapeGroup(llBookData* llBook);
	ShapeGroup(llBookData* llBook, llShapeGroupData* ShapeGroup);
	ShapeGroup(llShapeGroupData* ShapeGroup);

	ShapeGroup(Page& Page);
	ShapeGroup(Page& Page, ShapeGroupData& ShapeGroupData);
	ShapeGroup(Page& Page, ShapeData& ShapeGroup);
	ShapeGroup(Page& Page, int GroupID);


	//Call function after Edges have been updated
	void ProcessBackGround();
	void SetBackGround();


	glm::vec4 GetEdges();
	glm::vec4 GetBackGroundEdges();
	//glm::vec2 GetPosition(int OutputType);
	void ConvertInputToInputLeft();


	//Shape Placement Functions + Padding
	void PlaceBelow(const glm::vec4& ElementEdges, int PlacementType);
	void PlaceAbove(const glm::vec4& ElementEdges, int PlacementType);
	void PlaceRight(const glm::vec4& ElementEdges, int PlacementType);
	void PlaceLeft (const glm::vec4& ElementEdges, int PlacementType);

	void PlaceBelow(const glm::vec4& ElementEdges, int PlacementType, int PixelPadding);
	void PlaceAbove(const glm::vec4& ElementEdges, int PlacementType, int PixelPadding);
	void PlaceRight(const glm::vec4& ElementEdges, int PlacementType, int PixelPadding);
	void PlaceLeft (const glm::vec4& ElementEdges, int PlacementType, int PixelPadding);

	void CopyBackGround(llShapeGroupData* CopyShapeGroup);

	void AllignX(const float& X);
	void AllignY(const float& Y);

	void AllignX(const float& X, int PlacementType);
	void AllignY(const float& Y, int PlacementType);


	void llInit(llBookData* llBook);
	void llShapeGroupInit(llBookData* llBook, llShapeGroupData* ShapeGroup);
	llShapeGroupData* GetData() { return CurrentllShapeGroup; };

	llShapeGroupData* operator*()
	{
		return CurrentllShapeGroup;
	}

	llShapeGroupData* GetShapeGroup()
	{
		return CurrentllShapeGroup;
	}

	float GetAccessRight();
	float GetAccessLeft();
	float GetAccessTop();
	float GetAccessBottom();

	float GetAccessRight(int PixelOffset);
	float GetAccessLeft(int PixelOffset);
	float GetAccessTop(int PixelOffset);
	float GetAccessBottom(int PixelOffset);

	//float* GetColorR() { return &CurrentllShapeGroup->Color[0]; };
	//float* GetColorG() { return &CurrentllShapeGroup->Color[1]; };
	//float* GetColorB() { return &CurrentllShapeGroup->Color[2]; };
	//float* GetColorA() { return &CurrentllShapeGroup->Color[3]; };
	//glm::vec2* GetPosition() override;
	//glm::vec2* GetSize() override;

	void Init(Page& Page, int GroupID) {};

	void Add_Default();
	void Add_Duplicate();
	void Add_Insert();
	void Delete();

	void HighlightShapeGroup(glm::vec4 Color);
	void HighlightOff();

	void SetllShapeGroup(llShapeGroupData* llShapeGroup);
	void llUpdate() override;
	virtual void llSwitch(llShapeGroupData* llShapeGroup);

	void SetllPosition(glm::vec2 Position)
	{
		CurrentllShapeGroup->Position = Position;
		llUpdate();
	}


	ShapeData& Switch(Page& Page, int RequstedShapeID) override { return LoadedShape; };
	ShapeData& Switch(int ShapeID) override
	{
		if (Initialized == true)
		{
			if (IsInBounds(ShapeID) == true) 
			{
				if (SetInStone != true)
				{
					//CurrentPage->CurrentShapeGroupShapeCount = -1;
					LoadedShape = CurrentPage->GetShapeDataR(ShapeID);
					return LoadedShape;
				}
			}
			else
			{
				Log::LogString("Switch Error:: ID out of bounds");
			}
		}
		else
		{
			Log::LogString("Switch Error:: Shape Group Not Initialized");
		}
		return LoadedShape;
	}
	void PrintGroupShapes();
	int GetCount();

	void SetPageItemOffsets()
	{
		//Iteration Setup
		int PageItemID = CurrentShapeGroup.PageItem.ID;
		int PageGroupStart = CurrentShapeGroup.PageItem.PageGroup.ShapeStart;
		int PageGroupCount = CurrentShapeGroup.PageItem.PageGroup.ShapeStart + CurrentShapeGroup.PageItem.PageGroup.ShapeCount;
		
		//Reset Group Counts
		CurrentPage->CurrentPageGroupShapeCount = -1;
		CurrentPage->CurrentPageItemShapeCount = -1;
		CurrentPage->CurrentPageItem = 0;

		//Set Offsets
		for (int i = PageGroupStart; i < PageGroupCount; i++)
		{
			//Set PageGroup Offsets
			LoadedShape = CurrentPage->GetShapeDataR(i);
			CurrentPage->CurrentPageGroupShapeCount++;
			CurrentShapeGroup.PageItem.PageGroup.ShapeOffset = CurrentPage->CurrentPageItemShapeCount;

			//Set PageItem Offsets
			if (CurrentShapeGroup.PageItem.ID == PageItemID)
			{ 
				CurrentPage->CurrentPageItemShapeCount++;
				CurrentShapeGroup.PageItem.ShapeOffset = CurrentPage->CurrentPageItemShapeCount;
				Log::LogString("How many you see is page item count");
			}
		}
	};


	// Basic
	void SetPosition(glm::vec2 Position) override;                    
	void SetSize(glm::vec2 Size) override;                            
	void SetColor(glm::vec4 Color) override;                          
	void OffsetPosition(glm::vec2 Position);                          
	void OffsetSize(glm::vec2 Size);                         
	void OffsetColor(glm::vec4 Color);                       

	// Basic + boolean
	void SetPosition(glm::vec2 Position, glm::vec2 bools) override;    
	void SetSize(glm::vec2 Size, glm::vec2 bools) override;            
	void SetColor(glm::vec4 Color, glm::vec4 bools) override;  
	void OffsetPosition(glm::vec2 Position, glm::vec2 bools) override; 
	void OffsetSize(glm::vec2 Size, glm::vec2 bools) override;         
	void OffsetColor(glm::vec4 Color, glm::vec4 bools) override;       

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


	//glm::vec2 GetPosition() override { return CurrentllShapeGroup->Position; };
	//glm::vec2 GetSize() override { return CurrentllShapeGroup->Size; };
	//glm::vec4 GetColor() override { return  CurrentllShapeGroup->Color; };


protected:
	virtual void Update() {};
	void NewllUpdate();
	void ReCalibrateID();

	bool WithNewInput = false;
	//void ShapeToGroup(ShapeData& ShapeData);
	//void GroupToShape(GroupData& GroupData);
	void SetGroup(ShapeData& ShapeData);
	void SetMouseAccess();
	void SetllMouseAccess();
	void UpdateMouseAccess(glm::vec2 Position, glm::vec2 Size);
	//void UpdatellMouseAccess(glm::vec2 Position, glm::vec2 Size);

private:

};

#endif