#include "ElementGroup.h"

ShapeGroup::ShapeGroup()
	:SetInStone(true)
{
	CurrentPage = nullptr;
}

ShapeGroup::ShapeGroup(Page& Page)
	:SetInStone(true)
{
	if (&Page != nullptr)
	{
		Initialized = true;
		CurrentPage = &Page;
		CurrentPage->TotalShapeGroupCount++;
		CurrentPage->CurrentShapeGroup++;
		CurrentPage->CurrentShape = 0;
		LoadedShape.ShapeGroup.ID = CurrentPage->CurrentShapeGroup;
		LoadedShape.ShapeGroup.ShapeStart = Page.ShapeAmount();
		Log::LogString("-------Shape Added--------");
		Log::LogInt("CurrentShape     ", Page.CurrentShape);
		Log::LogInt("CurrentShapeGroup", Page.CurrentShapeGroup);
		Log::LogInt("CurrentPageItem  ", Page.CurrentPageItem);
		Log::LogInt("CurrentPageGroup ", Page.CurrentPageGroup);
		Log::LogString(" ");
	}
}

//Create a grid that is already set up & can be changed
//Group can't be switched with another
ShapeGroup::ShapeGroup(Page& Page, ShapeGroupData& ShapeGroupData)
	: SetInStone(true)
{
	if (&Page != nullptr)
	{
		Initialized = true;
		LoadedShape.ShapeGroup = ShapeGroupData;
		CurrentPage = &Page;
		//CurrentPage->ShapeGroupCount++;
	}
	//LoadedShape.ShapeGroup.ID = LoadedShape.ShapeGroup.Page->ShapeGroup.ShapeCount;
}

//New 
ShapeGroup::ShapeGroup(Page& Page, ShapeData& ShapeData)
	: SetInStone(true)
{
	if (&Page != nullptr)
	{
		Initialized = true;
		LoadedShape = ShapeData;
		CurrentPage = &Page;
		//CurrentPage->ShapeGroupCount++;
	}
	//LoadedShape.ShapeGroup.ID = LoadedShape.ShapeGroup.Page->ShapeGroup.ShapeCount;
}

//Group can be changed for another
ShapeGroup::ShapeGroup(Page& Page, int& ID)
	: SetInStone(false)
{
	if (&Page != nullptr)
	{
		Initialized = true;
		CurrentPage = &Page;
		LoadedShape = Page.GetShapeDataR(ID);
	}
}

void ShapeGroup::SetGroup(ShapeData& ShapeData)
{
	this->LoadedShape = ShapeData;
	ReCalibrateID();
	Update();
}
void ShapeGroup::SetPosition(glm::vec2 Position)
{
	this->LoadedShape.ShapeGroup.Position = Position;
//	ReCalibrateID();
	this->Update();
}
void ShapeGroup::SetPosition(glm::vec2 Position, glm::vec2 bools)
{
	if (bools[0] == true)
	{
		this->LoadedShape.ShapeGroup.Position[0] = Position[0];
	}
	if (bools[1] == true)
	{
		this->LoadedShape.ShapeGroup.Position[1] = Position[1];
	}
	ReCalibrateID();
	Update();
}


void ShapeGroup::SetPosition(glm::vec2 Position, int Conversion)
{
	//Position Converstion
	Position = ApplyPositionConversion(Position, Conversion);
	this->LoadedShape.ShapeGroup.Position = Position;
	ReCalibrateID();
	this->Update();
}

void ShapeGroup::SetPosition(glm::vec2 Position, glm::vec2 bools, int Conversion)
{
	//Position Converstion
	Position = ApplyPositionConversion(Position, Conversion);

	if (bools[0] == true)
	{
		this->LoadedShape.ShapeGroup.Position[0] = Position[0];
	}
	if (bools[1] == true)
	{
		this->LoadedShape.ShapeGroup.Position[1] = Position[1];
	}
	ReCalibrateID();
	Update();
}

void ShapeGroup::SetSize(glm::vec2 Size)
{
	this->LoadedShape.ShapeGroup.Size = Size;
	ReCalibrateID();
	Update();
}

void ShapeGroup::SetSize(glm::vec2 Size, glm::vec2 bools)
{
	if (bools[0] == true)
	{
		this->LoadedShape.ShapeGroup.Size[0] = Size[0];
	}
	if (bools[1] == true)
	{
		this->LoadedShape.ShapeGroup.Size[1] = Size[1];
	}
	ReCalibrateID();
	Update();
}

void ShapeGroup::SetColor(glm::vec4 Color)
{
	this->LoadedShape.ShapeGroup.Color = Color;
	ReCalibrateID();
	Update();
}
void ShapeGroup::SetColor(glm::vec4 Color, glm::vec4 bools)
{
	if (bools[0] == true)
	{
		this->LoadedShape.ShapeGroup.Color[0] = Color[0];

	}
	if (bools[1] == true)
	{
		this->LoadedShape.ShapeGroup.Color[1] = Color[1];
	}
	if (bools[2] == true)
	{
		this->LoadedShape.ShapeGroup.Color[2] = Color[2];
	}
	if (bools[3] == true)
	{
		this->LoadedShape.ShapeGroup.Color[3] = Color[3];
	}
	ReCalibrateID();
	Update();
}


void ShapeGroup::OffsetPosition(glm::vec2 Position)
{
	this->LoadedShape.ShapeGroup.Position += Position;
	ReCalibrateID();
	Update();
}

void ShapeGroup::OffsetPosition(glm::vec2 Position, glm::vec2 bools)
{
	if (bools[0] == true)
	{
		this->LoadedShape.ShapeGroup.Position[0] += Position[0];
	}
	if (bools[1] == true)
	{
		this->LoadedShape.ShapeGroup.Position[1] += Position[1];
	}
	ReCalibrateID();
	Update();
}
void ShapeGroup::OffsetSize(glm::vec2 Size)
{
	this->LoadedShape.ShapeGroup.Size += Size;
	ReCalibrateID();
	Update();
}
void ShapeGroup::OffsetSize(glm::vec2 Size, glm::vec2 bools)
{
	if (bools[0] == true)
	{
		this->LoadedShape.ShapeGroup.Size[0] += Size[0];
	}
	if (bools[1] == true)
	{
		this->LoadedShape.ShapeGroup.Size[1] += Size[1];
	}
	ReCalibrateID();
	Update();
}

void ShapeGroup::OffsetColor(glm::vec4 Color)
{
	this->LoadedShape.ShapeGroup.Color += Color;
	ReCalibrateID();
	Update();
}
void ShapeGroup::OffsetColor(glm::vec4 Color, glm::vec4 bools)
{
	if (bools[0] == true)
	{
		this->LoadedShape.ShapeGroup.Color[0] += Color[0];

	}
	if (bools[1] == true)
	{
		this->LoadedShape.ShapeGroup.Color[1] += Color[1];
	}
	if (bools[2] == true)
	{
		this->LoadedShape.ShapeGroup.Color[2] += Color[2];
	}
	if (bools[3] == true)
	{
		this->LoadedShape.ShapeGroup.Color[3] += Color[3];
	}
	ReCalibrateID();
	Update();

}

void ShapeGroup::OffsetPosition(glm::vec2 Position, int Conversion)
{
	Position = ApplySizeConversion(Position, Conversion);
	this->LoadedShape.ShapeGroup.Position += Position;
	ReCalibrateID();
	Update();
}
void ShapeGroup::OffsetPosition(glm::vec2 Position, glm::vec2 bools, int Conversion)
{
	Position = ApplySizeConversion(Position, Conversion);

	if (bools[0] == true)
	{
		this->LoadedShape.ShapeGroup.Position[0] += Position[0];
	}
	if (bools[1] == true)
	{
		this->LoadedShape.ShapeGroup.Position[1] += Position[1];
	}
	ReCalibrateID();
	Update();
}
void ShapeGroup::OffsetSize(glm::vec2 Size, int Conversion)
{
	//Size Conversion
	Size = ApplySizeConversion(Size, Conversion);
	this->LoadedShape.ShapeGroup.Size += Size;
	ReCalibrateID();
	Update();
}
void ShapeGroup::OffsetSize(glm::vec2 Size, glm::vec2 bools, int Conversion)
{
	//Size Conversion
	Size = ApplySizeConversion(Size, Conversion);
	if (bools[0] == true)
	{
		this->LoadedShape.ShapeGroup.Size[0] += Size[0];
	}
	if (bools[1] == true)
	{
		this->LoadedShape.ShapeGroup.Size[1] += Size[1];
	}
	ReCalibrateID();
	Update();
}

//this does not set up page
//void ShapeGroup::ShapeToGroup(ShapeData& ShapeData)
//{
//	LoadedShape.ShapeGroup.ShapeStart   = ShapeData.ID;
//	LoadedShape.ShapeGroup.ID        = ShapeData.ID;
//	LoadedShape.ShapeGroup.Count          = ShapeData.ShapeGroup.ShapeCount + 1;
//	LoadedShape.ShapeGroup.XYShapesPerRow = ShapeData.ShapeGroupXYShapePerRow;
//	LoadedShape.ShapeGroup.ShapeDataSize  = ShapeData.ShapeGroupShapeSize;
//	LoadedShape.ShapeGroup.Position       = ShapeData.ShapeGroupPosition;
//	LoadedShape.ShapeGroup.Size           = ShapeData.ShapeGroupSize;
//	LoadedShape.ShapeGroup.Color          = ShapeData.ShapeGroupColor;
//	LoadedShape.ShapeGroup.MouseAccess    = ShapeData.ShapeGroup.MouseAccess;
//	LoadedShape.ShapeGroup.Centered       = ShapeData.ShapeGroupCentered;
//	LoadedShape.ShapeGroup.Highlighted    = ShapeData.ShapeGroupHighlighted;
//	LoadedShape.ShapeGroup.ShapeType      = ShapeData.ShapeDataType;
//
//	LoadedShape.ShapeGroup.PageItemID           = ShapeData.PageGroupItemID;
//	LoadedShape.ShapeGroup.PageItemShapeCount   = ShapeData.PageGroupItemShapeCount;
//	LoadedShape.ShapeGroup.PageItemShapeOffset  = ShapeData.PageGroupItemShapeOffset;
	//LoadedShape.ShapeGroup.PageItemShapeStart = ShapeData.PageGroupItemShapeStart;
//
//}

//this does not set up page
//void ShapeGroup::GroupToShape(GroupData& GroupData)

	//CurrentShape.ID = GroupData.ShapeStart;
	//CurrentShape.ShapeGroup.ShapeCount = GroupData.Count;
	//CurrentShape.ShapeGroup.ShapeCount = GroupData.Count;
	//CurrentShape.Position = GroupData.Position;
	//CurrentShape.Size = GroupData.Size;
	//CurrentShape.Color = GroupData.Color;
	//CurrentShape.MouseAccess = GroupData.MouseAccess;
	//CurrentShape.ShapeGroupCentered = GroupData.Centered;
	//CurrentShape.ShapeGroupHighlighted = GroupData.Highlighted;
	//CurrentShape.ShapeDataType = GroupData.ShapeType;
	//CurrentShape.ShapeGroupXYShapePerRow = GroupData.XYShapesPerRow;


void ShapeGroup::ReCalibrateID()
{
	if (Initialized == false) { Log::LogString("ReCalibrateID Failed:: ShapeGroup Not Initialized"); return; };

	cout << "Recalibrating Group (" << LoadedShape.ShapeGroup.ID << ") " << endl;

	int CurrentID = 0;
	int GroupStart = 0;

	//Maintenance
	if (IsInBounds(LoadedShape.ShapeGroup.ShapeStart) == true) // LoadedShape.ShapeGroup.ShapeStart < LoadedShape.ShapeGroup.Page->ShapeAmount())
	{
		//in range
		CurrentID = LoadedShape.ShapeGroup.ShapeStart;
		GroupStart = LoadedShape.ShapeGroup.ShapeStart;
	}
	if (IsInBounds(LoadedShape.ShapeGroup.ShapeStart) == false)
	{
		//out of range
		CurrentID = CurrentPage->ShapeAmount();
		GroupStart = CurrentPage->ShapeAmount();
	}

	///Check if ID is valid
	if (CurrentID > -1)
	{
		cout << "Checking ID: " << CurrentID << "... " << endl;
		ShapeData* RetreivedShape = CurrentPage->GetShapeDataP(CurrentID);

		//Group Calibrated
		if (RetreivedShape->ID == LoadedShape.ShapeGroup.ID)
		{
			//Set the ID
			LoadedShape.ShapeGroup.ShapeStart = CurrentID - RetreivedShape->ShapeGroup.ShapeOffset;
			cout << " Group: " << RetreivedShape->ID << " Match Found!" << endl;
			cout << "Group Start : " << CurrentID - RetreivedShape->ShapeGroup.ShapeOffset << endl;
			cout << "--------" << endl;
			return;
		}

		//Group UnCalibrated
		//if (RetreivedShape->PageID != LoadedShape.ShapeGroup.ID)
		if (RetreivedShape->ID != LoadedShape.ShapeGroup.ID)
		{
			//Go up
			//if(RetreivedShape->PageID <LoadedShape.ShapeGroup.ID)
			if (RetreivedShape->ID < LoadedShape.ShapeGroup.ID)
			{
				int Result = FindNextGroup(CurrentID, RetreivedShape);
				if (Result != -1)
				{
					LoadedShape.ShapeGroup.ShapeStart = Result;
					RetreivedShape->ShapeGroup.ShapeStart = Result;
					return;
				}
				Log::LogString("FindNextGroupError:: Returned -1"); return;
			}

			//GO down
			if (RetreivedShape->ID > LoadedShape.ShapeGroup.ID)
			{
				int Result = FindPreviousGroup(CurrentID, RetreivedShape);
				if (Result != -1)
				{
					LoadedShape.ShapeGroup.ShapeStart = Result;
					RetreivedShape->ShapeGroup.ShapeStart = LoadedShape.ShapeGroup.ShapeStart;
					return;
				}
				Log::LogString("FindPreviousGroupError:: Returned -1"); return;
			}
		}
	}
}

//Returns the ID of the first shape in the group
int ShapeGroup::FindNextGroup(int CurrentID, ShapeData* RetreivedShape)
{
	if (RetreivedShape == nullptr) return -1;
	//Found
 	if (RetreivedShape->ID == LoadedShape.ShapeGroup.ID) 
	{
		cout << " Group: " << RetreivedShape->ID << " Match Found!" << endl;
		cout << " Group Start : " << CurrentID - RetreivedShape->ShapeGroup.ShapeOffset << endl; 
		cout << "--------" << endl;
		return CurrentID - RetreivedShape->ShapeGroup.ShapeOffset;
	};

	//Set up next group 
	cout << " Group: " << RetreivedShape->ID << " No Match" << endl;
	int NextGroupTranslation = RetreivedShape->ShapeGroup.ShapeCount - RetreivedShape->ShapeGroup.ShapeOffset + 1;
	RetreivedShape += NextGroupTranslation;
	CurrentID += NextGroupTranslation;
	if (NextGroupTranslation == 0) Log::LogString("FindNextGroup Error:: Cancelled Bootloop"); return -1;
	
	//Check Next Group
	int FoundID = FindNextGroup(CurrentID, RetreivedShape);
	return FoundID;
}


int ShapeGroup::FindPreviousGroup(int CurrentID, ShapeData* RetreivedShape)
{
	if (RetreivedShape == nullptr) return -1;
	//Found
	if (RetreivedShape->ID = LoadedShape.ShapeGroup.ID)
	{
		cout << " Group: " << RetreivedShape->ID << " Match Found!" << endl;
		cout << " Group Start : " << CurrentID - RetreivedShape->ShapeGroup.ShapeOffset << endl;
		cout << "--------" << endl;
		return CurrentID - RetreivedShape->ShapeGroup.ShapeOffset; 
	};

	cout << " Group: " << RetreivedShape->ID << " No Match" << endl;
	//Set up next group / Not found
	int NextGroupTranslation = RetreivedShape->ShapeGroup.ShapeOffset - 1;
	RetreivedShape += NextGroupTranslation;
	CurrentID += NextGroupTranslation;

	if (NextGroupTranslation == 0) Log::LogString("FindPreviousGroup Error:: Cancelled Bootloop"); return -1;

	//Check Next Group
	int FoundID = FindPreviousGroup(CurrentID, RetreivedShape);
	return FoundID;
}

void ShapeGroup::SetMouseAccess()
{
	if (Initialized == false) { Log::LogString("SetMouseAccess Failed:: ShapeGroup Not Initialized"); return; };

	if (LoadedShape.ShapeGroup.MouseAccess == true)
	{
	
		//this->CurrentShape.ShapeGroup.Top = (LoadedShape.ShapeGroup.Position[1] + (LoadedShape.ShapeGroup.Size[1] / 2));
		//this->CurrentShape.ShapeGroup.Bottom = (LoadedShape.ShapeGroup.Position[1] - (LoadedShape.ShapeGroup.Size[1] / 2));
		//this->CurrentShape.ShapeGroup.Left = (LoadedShape.ShapeGroup.Position[0] - (LoadedShape.ShapeGroup.Size[0] / 2));
		//this->CurrentShape.ShapeGroup.Right = (LoadedShape.ShapeGroup.Position[0] + (LoadedShape.ShapeGroup.Size[0] / 2));

		for (int i = LoadedShape.ShapeGroup.ShapeStart; i < LoadedShape.ShapeGroup.ShapeStart + LoadedShape.ShapeGroup.ShapeCount; i++)
		{
			if(IsInBounds(i) != true) { Log::LogString("SetMouseAccess Failed:: ID out of bounds"); return; };

			//Set entire shape group 
			ShapeData& RetreivedShape = CurrentPage->GetShapeDataR(i);
			RetreivedShape.ShapeGroup.Top = LoadedShape.ShapeGroup.Top;
			RetreivedShape.ShapeGroup.Bottom = LoadedShape.ShapeGroup.Bottom;
			RetreivedShape.ShapeGroup.Left = LoadedShape.ShapeGroup.Left;
			RetreivedShape.ShapeGroup.Right = LoadedShape.ShapeGroup.Right;

			LoadedShape.ShapeGroup.Size[0] = LoadedShape.ShapeGroup.Right - LoadedShape.ShapeGroup.Left;
			LoadedShape.ShapeGroup.Size[1] = LoadedShape.ShapeGroup.Top - LoadedShape.ShapeGroup.Bottom;
		}
	}
}

void ShapeGroup::UpdateMouseAccess(glm::vec2 Position, glm::vec2 Size)
{
	if (LoadedShape.ShapeGroup.MouseAccess == false) return;

	float Left = Position[0] - (Size[0] / 2);
	float Right = Position[0] + (Size[0] / 2);
	float Top = Position[1] + (Size[1] / 2);
	float Bottom = Position[1] - (Size[1] / 2);

	if (Left < LoadedShape.ShapeGroup.Left || LoadedShape.ShapeGroup.Left == -3)
	{
		LoadedShape.ShapeGroup.Left = Left;
	}

	if (Right > LoadedShape.ShapeGroup.Right || LoadedShape.ShapeGroup.Right == -3)
	{
		LoadedShape.ShapeGroup.Right = Right;
	}

	if (Top > LoadedShape.ShapeGroup.Top || LoadedShape.ShapeGroup.Top == -3)
	{
		LoadedShape.ShapeGroup.Top = Top;
	}

	if (Bottom < LoadedShape.ShapeGroup.Bottom || LoadedShape.ShapeGroup.Bottom == -3)
	{
		LoadedShape.ShapeGroup.Bottom = Bottom;
	}

}

void ShapeGroup::PrintGroupShapes()
{
	if (Initialized == false) return;
	
	for (int i = LoadedShape.ShapeGroup.ShapeStart; i < LoadedShape.ShapeGroup.ShapeStart + LoadedShape.ShapeGroup.ShapeCount - 1; i++)
	{
		if (IsInBounds(i) == false) return;
		CurrentPage->PrintShape(i);
	}
}

int ShapeGroup::GetCount()
{
	return LoadedShape.ShapeGroup.ShapeCount;
}