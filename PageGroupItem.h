#ifndef  PAGEGROUPITEM
#define  PAGEGROUPITEM

#define P_NONE 0
#define P_END_TO_MIDDLE 1
#define P_BEGINNING_TO_MIDDLE 2

#include <iostream>
#include "MasterElement.h"
#include "ElementGroup.h" //Parent
#include "Text.h" //Child
#include "Grid.h" //Child
#include "Log.h" //Child

#define TYPE_CUSTOM 0
#define TYPE_SLIDER 1

using namespace std;

//struct PageGroupItemData
//{
//	//GroupID: Group 436
//	//CellID : Cell 2 of Upper Group
//	//ShapeStart: Group Starts at Shape 1076
//	//GroupStart Offset: Shape is 10 shapes from this group's start
//	//CellCount: Group owns 6 cells
//	//ShapeCount: Group owns 23 Shapes
//
//	Page* Page;
//	unsigned int ShapeStartID; //ShapeID of the first Shape
//	unsigned int ShapeCount; //Item Count
//
//	unsigned int CellCount;
//	unsigned int CellID;
//	int CellOffset = 0;
//
//	int GroupID; //Item ID
//	ShapeData* NextGroup;
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
//	//Page Item Details
//	int PageGroupID;
//	int PageGroupShapeCount;
//	int PageGroupShapeOffset;
//	int PageGroupShapeStartID;
//};

class PageGroupItem : public MasterElement
{
public:

	//PageGroupItemData CurrentPageItem;
	//GroupData CurrentShapeGroup;
	PageItemData CurrentPageItem;
	ShapeGroupData CurrentShapeGroup;

	llPageGroupData* Parent_PageGroup;
	llPageItemData* CurrentllPageItem;
	llShapeGroupData* CurrentllShapeGroup; // for reference quad group

	TextData CurrentText;
	ShapeData CurrentShape;

	PageGroupItem();
	PageGroupItem(llBookData* llBookData);
	PageGroupItem(llBookData* llBookData, llPageItemData* llPageItem);
	PageGroupItem(llPageItemData* llPageItem);

	PageGroupItem(Page& Page);
	PageGroupItem(Page& Page, PageItemData& PageItemData);
	PageGroupItem(Page& Page, ShapeData& LoadedShape);
	PageGroupItem(Page& Page, int GroupID);
	void llInit(llBookData* llBook);
	void llPageItemInit(llBookData* llBook, llPageItemData* PageItemData);

	void SetllPageItem(llPageItemData* llPageItem);

	virtual llPageItemData* GetData() { return CurrentllPageItem; };

	llShapeGroupData* GetShapeGroup(int Index);
	llShapeData* GetShapeGroupShape(int ShapeGroupIndex, int ShapeIndex);

	llPageItemData* GetPageItem()
	{
		return CurrentllPageItem;
	}

	void Add_Default() override; //Editor/None Set in Stone
	void Add_Duplicate() override; //Editor/None Set in Stone
	void Add_Insert() override; //Editor/None Set in Stone
	void Delete();

	void Second_Add_Duplicate(llBookData* llBook)
	{
		//Validate
		if (llBook == nullptr) { Log::LogString("ERROR:: Duplicate PageItem FAILED:: Invalid Book State"); return; }
		if (CurrentllPageItem == nullptr) { Log::LogString("ERROR:: Duplicate PageItem FAILED:: Invalid PageItem State"); return; }

		CopyPageItem(llBook, CurrentllPageItem);
	}


	void HighlightPageItem(glm::vec4 Color);
	void HighlightOff();

	float GetAccessRight();
	float GetAccessLeft();
	float GetAccessTop();
	float GetAccessBottom();

	float GetAccessRight(int PixelOffset);
	float GetAccessLeft(int PixelOffset);
	float GetAccessTop(int PixelOffset);
	float GetAccessBottom(int PixelOffset);

	glm::vec4 GetEdges();
	glm::vec4 GetEdgesWithBackGround();

	void SetBackGroundColor(glm::vec4 Color);

	void Hide();
	void UnHide();

	//Shape Placement Functions + Padding
	void PlaceBelow(const glm::vec4& Edges, int PlacementType);
	void PlaceAbove(const glm::vec4& Edges, int PlacementType);
	void PlaceRight(const glm::vec4& Edges, int PlacementType);
	void PlaceLeft (const glm::vec4& Edges, int PlacementType);

	void PlaceBelow(const glm::vec4& Edges, int PlacementType, int PixelPadding);
	void PlaceAbove(const glm::vec4& Edges, int PlacementType, int PixelPadding);
	void PlaceRight(const glm::vec4& Edges, int PlacementType, int PixelPadding);
	void PlaceLeft (const glm::vec4& Edges, int PlacementType, int PixelPadding);

	void AllignX(const float& X);
	void AllignY(const float& Y);

	void AllignX(const float& X, int PlacementType);
	void AllignY(const float& Y, int PlacementType);

	void TranslateInput(); // Working Not Quite
	void UpdatellMouseAccess();

	void RePositionToCenter() //Sets the group position to the center of the product of combined edges
	{
		///////////////////////In Parent/Current//////////////////////////
		//CurrentPosition
		glm::vec2 ActualPosition = CurrentllPageItem->Position; //CurrentllPageItem

		//Center of Group
		glm::vec2 CenterPosition = { (CurrentllPageItem->Left + CurrentllPageItem->Right)/2, (CurrentllPageItem->Top + CurrentllPageItem->Bottom)/2}; //Center Of PageItem

		//Vector to go from Center of group position to Actual position
		glm::vec2 CenterToActualTranslation = ActualPosition - CenterPosition;

		///////////////////////Parent/Current Finished//////////////////////////

		////////////////////////In Child///////////////////////////////
		llShapeGroupData* CurrentShapeGroup = CurrentllPageItem->ShapeGroup;

		while (CurrentShapeGroup != nullptr)
		{

			//Previous Offset
			glm::vec2 ActualOffset = CurrentShapeGroup->PositionOffset; //CurrentllShapeGroup->PositionOffset

			//New Offset
			glm::vec2 CenterOffset = ActualOffset + CenterToActualTranslation;

			CurrentShapeGroup->PositionOffset = CenterOffset;

			CurrentShapeGroup = CurrentShapeGroup->Next;
		}

		///////////////////////Child Finished

		//Actual Position + Offset = FinalPosition (Same)    //Group Pos  +   GroupOffset  = Where the Group will be positioned
		//Log::LogVec2("Group Position From Actual Position", ActualPosition + ActualOffset);
		//Log::LogVec2("Group Position From Center Position", CenterPosition + CenterOffset);
		//Center Position + Offset = FinalPosition (Same)
	}

	//Call function after Edges have been updated
	void ProcessBackGround();
	void SetBackGround();
	void CalculateGroupOffset();

	//float* GetColorR() { return &CurrentllPageItem->Color[0]; };
	//float* GetColorG() { return &CurrentllPageItem->Color[1]; };
	//float* GetColorB() { return &CurrentllPageItem->Color[2]; };
	//float* GetColorA() { return &CurrentllPageItem->Color[3]; };
	//glm::vec2* GetPosition() override;
	//glm::vec2* GetSize() override;

	void llUpdate() override;
	virtual void Update() {};
	void ReCalibrateID();
	int FindNextGroup(int CurrentID, ShapeData* RetreivedShape);
	int FindPreviousGroup(int CurrentID, ShapeData* RetreivedShape);
	void ShapeToGroup(ShapeData& ShapeData);

	//glm::vec2 GetPosition() override { return CurrentllPageItem->Position; };
	//glm::vec2 GetSize() override { return CurrentllPageItem->Size; };
	//glm::vec4 GetColor() override { return  CurrentllPageItem->Color; };

	void SetllPosition(glm::vec2 Position);
	void SetllPosition(glm::vec2 Position, int InputType);

	void OffsetPosition(glm::vec2 Position, glm::vec2 bools) override; //...
	void OffsetSize(glm::vec2 Size, glm::vec2 bools) override;         //...
	void OffsetColor(glm::vec4 Color, glm::vec4 bools) override;       //...
	//void SwitchToPageItem(int ShapeID);

	//void llSwitch(int Offset) override;

	void PrintllShapes()
	{
		PrintPageItemShapes(CurrentllPageItem);
	}

	void SetPageGroupOffsets() 
	{
		//Setup
		CurrentPage->CurrentPageGroupShapeCount = -1;

		//Set PageGroup Offset
		for (int i = CurrentPageItem.PageGroup.ShapeStart; i < CurrentPageItem.PageGroup.ShapeStart + CurrentPageItem.PageGroup.ShapeCount; i++)
		{
			CurrentPageItem = CurrentPage->GetShapeDataR(i).ShapeGroup.PageItem;
			CurrentPage->CurrentPageGroupShapeCount++;
			CurrentPageItem.PageGroup.ShapeOffset = CurrentPage->CurrentPageGroupShapeCount;
		}
	};

	//ShapeData Editing
	virtual void llSwitch(llPageItemData* llPageItem);
	ShapeData& Switch(int RequstedShapeID);
	ShapeData& Switch(Page& Page, int RequstedShapeID);
	void SetPageItem(ShapeData& ShapeData);
	void SetPageItem(ShapeData& ShapeData, glm::vec2 PSConversions);
	void SetPosition(glm::vec2 Position);
	void OffsetPosition(glm::vec2 PositionOffset);

	void UpdateMouseAccess(glm::vec2 Position, glm::vec2 Size, int PositionConversion);

	//void SetllMouseAccess(); //This one
	void SetMouseAccess();
	glm::vec2 ConvertEndToMiddle(glm::vec2 Position, glm::vec2 Size);
	glm::vec2 ConvertBeginningToMiddle(glm::vec2 Position, glm::vec2 Size);
	int FindShapeGroup(bool FromBottom, double xMouse, double yMouse);

	void PrintGroupShapes()
	{
		if (Initialized == false) {Log::LogString("Cannot Print Shapes:: PageItem Not Initialized"); return;}

		//ReCalibrateID();
		//CurrentPageItem.ShapeCount -= 10;
		for (int i = CurrentPageItem.ShapeStart; i < CurrentPageItem.ShapeStart + CurrentPageItem.ShapeCount + 1; i++)
		{
			CurrentPage->PrintShape(i);
		}
		cout << "Printing Starting from: " << CurrentPageItem.ShapeStart << endl;
		cout << "For the count: " << CurrentPageItem.ShapeCount << endl;
	}

	void Init(Page& Page, int QuadID)
	{
		if (&Page != nullptr)
		{
			Initialized = true;
			CurrentPage = &Page;
			if (QuadID != -1)
			{
				CurrentPageItem = Page.GetShapeDataR(QuadID).ShapeGroup.PageItem;
				
			}
			CurrentPageItem.Position = { 0.0, 0.0 };
			Add_Default();
		}
	};



	glm::vec2 GetBiggestMouseAccess(glm::vec2 Position, glm::vec2 Size);

	private:

		bool WithNewInput = false;
		bool Input_Left_Once = false;
		glm::vec2 PreviousPosition = {0.0, 0.0};
};


#endif
