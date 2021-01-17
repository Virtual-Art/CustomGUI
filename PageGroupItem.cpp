#include "PageGroupItem.h"

//Uninitialized PageItem
PageGroupItem::PageGroupItem()
{
	CurrentPage = nullptr;
}

//New Page Item with data provided by derived class
PageGroupItem::PageGroupItem(Page& Page)
{
	if (&Page != nullptr)
	{
		//Setup
		Initialized = true;
		CurrentPage = &Page;
		LoadedShape.PageItem.ShapeStart = Page.ShapeAmount();

		//Track Counts
		CurrentPage->CurrentPageItem++;
		CurrentPage->TotalPageItemCount++;

		//Reset Child Group Counts / Shape Counts
		CurrentPage->CurrentShapeGroup = 0;
		CurrentPage->CurrentShape = -1;
		CurrentPage->CurrentPageItemShapeCount = -1;
		CurrentPage->CurrentShapeGroupShapeCount = -1;
	}
}

//New PageItem initialized by group data
PageGroupItem::PageGroupItem(Page& Page, PageItemData& PageItemData)
{
	if (&Page != nullptr)
	{
		//Setup
		Initialized = true;
		CurrentPage = &Page;
		LoadedShape.PageItem = PageItemData;
		LoadedShape.PageItem.ShapeStart = Page.ShapeAmount();

		//Track Counts
        CurrentPage->CurrentPageItem++;
		CurrentPage->TotalPageItemCount++;

		//Reset Child Group Counts / Shape Counts
		CurrentPage->CurrentShapeGroup = 0;
		CurrentPage->CurrentShape = -1;
		CurrentPage->CurrentPageItemShapeCount = -1;
		CurrentPage->CurrentShapeGroupShapeCount = -1;
	}
}

//New Page Item initialized by FullShape Data
PageGroupItem::PageGroupItem(Page& Page, ShapeData& FullShape)
{
	if (&Page != nullptr)
	{
		//Setup
		Initialized = true;
		CurrentPage = &Page;
		LoadedShape = FullShape;
		LoadedShape.PageItem.ShapeStart = Page.ShapeAmount();
		
		//Track Counts
		CurrentPage->TotalPageItemCount++;
		CurrentPage->CurrentPageItem++;

		//Reset Child Group Counts
		CurrentPage->CurrentShapeGroup = 0;
		CurrentPage->CurrentShape = -1;
		CurrentPage->CurrentPageItemShapeCount = -1;
		CurrentPage->CurrentShapeGroupShapeCount = -1;

	}
}

//Group can be changed for another
PageGroupItem::PageGroupItem(Page& Page, int ID)
{
	if (&Page != nullptr)
	{
		Initialized = true;
		CurrentPage = &Page;
		if (ID != -1)
		{
			LoadedShape = Page.GetShapeDataR(ID);
			CurrentPage->CurrentPageItem = LoadedShape.PageItem.ID;
			CurrentPage->CurrentShapeGroup = 0;
			CurrentPage->CurrentShape = 0;
		}
		else
		{
			cout << "Page Item Not Initialized " << endl;
		}
	}
	else
	{
		cout << "PageGroup Not Ready:: error page is nullptr" << endl;
	}

}

void PageGroupItem::SetPosition(glm::vec2 Position)
{
	this->LoadedShape.PageItem.Position = Position;
	//ReCalibrateID();
	Update();
}

void PageGroupItem::OffsetPosition(glm::vec2 Position)
{
	this->LoadedShape.PageItem.Position += Position;
	//ReCalibrateID();
	Update();
}

void PageGroupItem::OffsetPosition(glm::vec2 Position, glm::vec2 bools)
{

	this->LoadedShape.PageItem.Position += Position;
	ReCalibrateID();
}

void PageGroupItem::ShapeToGroup(ShapeData& ShapeData)
{
	////PageItem
	//LoadedShape.PageItem.GroupID        = ShapeData.PageItem.ID;
	//LoadedShape.PageItem.ShapeStartID   = ShapeData.PageItem.ShapeStartID;
	//LoadedShape.PageItem.ShapeCount     = ShapeData.PageGroupShapeCount;
	//LoadedShape.PageItem.Position       = ShapeData.PageItem.Position;
	//cout << "POSITON GOT BACK = " << LoadedShape.PageItem.Position[0] << " , " << LoadedShape.PageItem.Position[1] << endl;
	//LoadedShape.PageItem.Size           = ShapeData.PageItem.Size;
	//LoadedShape.PageItem.Color          = ShapeData.PageItem.Color;
	//LoadedShape.PageItem.MouseAccess    = ShapeData.PageItem.MouseAccess;
	//LoadedShape.PageItem.Centered       = ShapeData.PageItem.Centered;
	//LoadedShape.PageItem.Highlighted    = ShapeData.PageItem.Highlighted;
	//LoadedShape.PageItem.ShapeType      = ShapeData.ShapeDataType;
	//LoadedShape.PageItem.XYShapesPerRow = ShapeData.PageItem.XYShapePerRow;
	//LoadedShape.PageItem.ShapeDataSize  = ShapeData.PageItem.ShapeSize;
	//LoadedShape.PageItem.Left           = ShapeData.PageItem.Left;
	//LoadedShape.PageItem.Right          = ShapeData.PageItem.Right;
	//LoadedShape.PageItem.Top            = ShapeData.PageItem.Top;
	//LoadedShape.PageItem.Bottom         = ShapeData.PageItem.Bottom;
	//
	////ShapeGroup
	//LoadedShapeGroup.PageItemID           = ShapeData.PageItem.ID;
	//LoadedShapeGroup.PageItemShapeStartID = ShapeData.PageItem.ShapeStartID;
	//LoadedShapeGroup.PageItemShapeCount   = ShapeData.PageItem.ShapeCount;

}

//ShapeData Editing
void PageGroupItem::Add_Default()
{

}

void PageGroupItem::Add_Duplicate()
{

}

void PageGroupItem::Add_Insert()
{

}

void PageGroupItem::Delete()
{

}

ShapeData& PageGroupItem::Switch(int RequstedShapeID)
{
	if (Initialized == true)
	{
		if (IsInBounds(RequstedShapeID) == true)
		{
		     LoadedShape = CurrentPage->GetShapeDataR(RequstedShapeID);
		     return LoadedShape;
		}
		else
		{
			Log::LogString("Switch Error:: ID out of bounds");
		}
	}
	else
	{
		Log::LogString("Switch Error:: Page Item Not Initialized");
	}
	return LoadedShape;
}

ShapeData& PageGroupItem::Switch(Page& Page, int RequstedShapeID)
{
	return LoadedShape;
}

void PageGroupItem::SetPageItem(ShapeData& ShapeData)
{

}

void PageGroupItem::SetPageItem(ShapeData& ShapeData, glm::vec2 PSConversions)
{

}

void PageGroupItem::UpdateMouseAccess(glm::vec2 Position, glm::vec2 Size, int PositionConversion)
{
	switch(PositionConversion)
	{
	case 1:
		Position = ConvertEndToMiddle(Position, Size);
		break;
	case 2:
		Position = ConvertBeginningToMiddle(Position, Size);
		break;
	}

	float Left = Position[0] - (Size[0] / 2);
	float Right = Position[0] + (Size[0] / 2);
	float Top = Position[1] + (Size[1] / 2);
	float Bottom = Position[1] - (Size[1] / 2);

	if (Left < LoadedShape.PageItem.Left || LoadedShape.PageItem.Left == -3.0)
	{
		LoadedShape.PageItem.Left = Left;
	}

	if (Right > LoadedShape.PageItem.Right || LoadedShape.PageItem.Right == -3.0)
	{
		LoadedShape.PageItem.Right = Right;
	}

	if (Top > LoadedShape.PageItem.Top || LoadedShape.PageItem.Top == -3.0)
	{
		LoadedShape.PageItem.Top = Top;
	}

	if (Bottom < LoadedShape.PageItem.Bottom || LoadedShape.PageItem.Bottom == -3.0)
	{
		LoadedShape.PageItem.Bottom = Bottom;
	}

}

void PageGroupItem::ReCalibrateID()
{
	if (Initialized == false) { Log::LogString("ReCalibrateID Failed:: ShapeGroup Not Initialized"); return; };
	cout << "Recalibrating Group (" << LoadedShape.PageItem.ID << ") " << endl;

	int CurrentID = 0;
	int GroupStart = 0;

	//Maintenance
	//BoundsChecks()
	if (IsInBounds(LoadedShape.PageItem.ShapeStart) == true)
	{
		//in range
		CurrentID = LoadedShape.PageItem.ShapeStart;
		GroupStart = LoadedShape.PageItem.ShapeStart;
	}
	if (IsInBounds(LoadedShape.PageItem.ShapeStart) == false)
	{
		//out of range
		CurrentID  = CurrentPage->ShapeAmount();
		GroupStart = CurrentPage->ShapeAmount();
	}

	///Check if ID is valid
	if (CurrentID > -1)
	{
		cout << "Checking ID: " << CurrentID << "... " << endl;
		ShapeData* RetreivedShape = CurrentPage->GetShapeDataP(CurrentID);


		//Group Calibrated
		if (RetreivedShape->PageItem.ID == LoadedShape.PageItem.ID)
		{
			//Set the ID
			LoadedShape.PageItem.ShapeStart = CurrentID - RetreivedShape->PageItem.ShapeOffset;
			cout << " Group: " << RetreivedShape->PageItem.ID << " Match Successfully Found!" << endl;
			cout << "Group Start : " << CurrentID - RetreivedShape->PageItem.ShapeOffset << endl;
			cout << "--------" << endl;
			return;
		}

		//Group UnCalibrated
		//if (RetreivedShape->PageGroupID != CurrentGroupData.GroupID)
		if (RetreivedShape->PageItem.ID != LoadedShape.PageItem.ID)
		{
			//Go up
			//if(RetreivedShape->PageGroupID <CurrentGroupData.GroupID)
			if (RetreivedShape->PageItem.ID < LoadedShape.PageItem.ID)
			{
				int Result = FindNextGroup(CurrentID, RetreivedShape);
				if (Result != -1)
				{
					RetreivedShape->PageItem.ShapeStart = LoadedShape.PageItem.ShapeStart;
					return;
				}
				Log::LogString("FindNextGroupError:: Returned -1"); return;
			}

			//GO down
			if (RetreivedShape->PageItem.ID > LoadedShape.PageItem.ID)
			{
				int Result = FindPreviousGroup(CurrentID, RetreivedShape);
				if (Result != -1)
				{
					RetreivedShape->PageItem.ShapeStart = LoadedShape.PageItem.ShapeStart;
					return;
				}
				Log::LogString("FindPreviousGroupError:: Returned -1"); return;
			}
		}
	}
}

//Returns the ID of the first shape in the group
int PageGroupItem::FindNextGroup(int CurrentID, ShapeData* RetreivedShape)
{
	if (RetreivedShape == nullptr) return -1;
	//Found
	if (RetreivedShape->PageItem.ID == LoadedShape.PageItem.ID)
	{
		cout << " Group: " << RetreivedShape->PageItem.ID << " Match Found!" << endl;
		cout << " Group Start : " << CurrentID - RetreivedShape->ShapeGroup.ShapeOffset << endl;
		cout << "--------" << endl;
		return CurrentID - RetreivedShape->ShapeGroup.ShapeOffset;
	};

	//Set up next group 
	cout << " Group: " << RetreivedShape->PageItem.ID << " No Match" << endl;
	int NextGroupID = RetreivedShape->PageItem.ShapeCount - RetreivedShape->PageItem.ShapeOffset + 1;
	RetreivedShape += NextGroupID;
	CurrentID += NextGroupID;
	if (NextGroupID == 0) Log::LogString("FindNextGroup Error:: Cancelled Bootloop"); return -1;

	//Check Next Group
	int FoundID = FindNextGroup(CurrentID, RetreivedShape);
	return FoundID;
}


int PageGroupItem::FindPreviousGroup(int CurrentID, ShapeData* RetreivedShape)
{
	//Found
	if (RetreivedShape->PageItem.ID = LoadedShape.PageItem.ID)
	{
		cout << " Group: " << RetreivedShape->PageItem.ID << " Match Found!" << endl;
		cout << " Group Start : " << CurrentID - RetreivedShape->PageItem.ShapeOffset << endl;
		cout << "--------" << endl;
		return CurrentID - RetreivedShape->PageItem.ShapeOffset;
	};

	cout << " Group: " << RetreivedShape->PageItem.ID << " No Match" << endl;
	//Set up next group / Not found
	int NextGroupTranslation = RetreivedShape->PageItem.ShapeOffset - 1;
	RetreivedShape += NextGroupTranslation;
	CurrentID += NextGroupTranslation;

	//Check Next Group
	int FoundID = FindPreviousGroup(CurrentID, RetreivedShape);
	return FoundID;
}

int PageGroupItem::GetShapeGroup(int ChildGroupID)
{
	if (Initialized != true) { Log::LogString("GetShapeGroup Failed:: ShapeGroup Not Initialized"); return -1; }
	ReCalibrateID();
	int CurrentID = LoadedShape.PageItem.ShapeStart;
	bool Found = false;
	ShapeData* RetreivedShape = CurrentPage->GetShapeDataP(CurrentID);

	//Found
	while (RetreivedShape->PageItem.ID == LoadedShape.PageItem.ID)
	{
		cout << "Checking..." << RetreivedShape->ShapeGroup.ID  << " == " << ChildGroupID << endl;
		if (RetreivedShape->ShapeGroup.ID == ChildGroupID)
		{
			cout << " ShapeGroup: " << RetreivedShape->ShapeGroup.ID << " Match Found!" << endl;
			cout << " ShapeGroup Start : " << CurrentID - RetreivedShape->ShapeGroup.ShapeOffset << endl;
			cout << "--------" << endl;
			return CurrentID - RetreivedShape->ShapeGroup.ShapeOffset;
		}

		//Not Found, Next group
		cout << " No Match " << endl;
		int NextGroupID = RetreivedShape->ShapeGroup.ShapeCount - RetreivedShape->ShapeGroup.ShapeOffset + 1;
		CurrentID += NextGroupID;
		RetreivedShape += NextGroupID;
	}

	cout << "Group Not Found" << endl;
	return -1;
}

void PageGroupItem::SetMouseAccess()
{
	if (LoadedShape.PageItem.MouseAccess == true)
	{
		//cout << "PageItem Mouse access!" << endl;
		//Log::LogVec2("PageItem Position", LoadedShape.ShapeGroupPosition);
		//Log::LogVec2("PageItem Size", LoadedShape.ShapeGroupSize);

		//this->LoadedShape.PageItem.Top = (LoadedShape.PageItem.Position[1] + (LoadedShape.PageItem.Size[1] / 2));
		//this->LoadedShape.PageItem.Bottom = (LoadedShape.PageItem.Position[1] - (LoadedShape.PageItem.Size[1] / 2));
		//this->LoadedShape.PageItem.Left = (LoadedShape.PageItem.Position[0] - (LoadedShape.PageItem.Size[0] / 2));
		//this->LoadedShape.PageItem.Right = (LoadedShape.PageItem.Position[0] + (LoadedShape.PageItem.Size[0] / 2));

		for (int i = LoadedShape.PageItem.ShapeStart; i < LoadedShape.PageItem.ShapeStart + LoadedShape.PageItem.ShapeCount + 1; i++)
		{
			//Log::LogString("yes mouse access");
			ShapeData* RetreivedShape = CurrentPage->GetShapeDataP(i);
			//RetreivedShape->PageItem.Top = LoadedShape.ShapeGroupTop;
			//RetreivedShape->PageItem.Bottom = LoadedShape.ShapeGroupBottom;
			//RetreivedShape->PageItem.Left = LoadedShape.ShapeGroupLeft;
			//RetreivedShape->PageItem.Right = LoadedShape.ShapeGroupRight;

			RetreivedShape->PageItem.Top = LoadedShape.PageItem.Top;
			RetreivedShape->PageItem.Bottom = LoadedShape.PageItem.Bottom;
			RetreivedShape->PageItem.Left = LoadedShape.PageItem.Left;
			RetreivedShape->PageItem.Right = LoadedShape.PageItem.Right;

			//cout << "GroupItem: " << RetreivedShape->GroupID << endl;
			//cout << "GroupItemTop " << RetreivedShape->PageItem.Top << endl;
			//cout << "GroupItemBottom " << RetreivedShape->PageItem.Bottom << endl;
			//cout << "GroupItemLeft " << RetreivedShape->PageItem.Left << endl;
			//cout << "GroupItemRight " << RetreivedShape->PageItem.Right << endl;
			//cout << "---- " << endl;
		}
	}
	else
	{
		for (int i = LoadedShape.PageItem.ShapeStart; i < LoadedShape.PageItem.ShapeStart + LoadedShape.PageItem.ShapeCount; i++)
		{
			Log::LogString("no mouse access");
			ShapeData* RetreivedShape = CurrentPage->GetShapeDataP(i);
			RetreivedShape->PageItem.Top = -3;
			RetreivedShape->PageItem.Bottom = -3;
			RetreivedShape->PageItem.Left = 3;
			RetreivedShape->PageItem.Right = 3;
		}
	}


}

glm::vec2 PageGroupItem::GetBiggestMouseAccess(glm::vec2 Position, glm::vec2 Size)
{


}


//Working
int PageGroupItem::FindShapeGroup(bool FromBottom, double xMouse, double yMouse)
{
	// ReCalibrateID();
	int CurrentID = 22;
	bool Found = false;
	ShapeData* RetreivedShape = CurrentPage->GetShapeDataP(CurrentID);

	//Iterate through all  
	//or start from zero, and go up till you find it...
	//or start from top and go down till you find it...
	for (int i = 0; i < CurrentPage->ShapeAmount(); i++)
	{
		//Log::LogInt("Checking ID", RetreivedShape->ID);
		//Log::LogInt("PageGroup:", RetreivedShape->PageItem.ID);
		if (xMouse < RetreivedShape->ShapeGroup.Right && xMouse >  RetreivedShape->ShapeGroup.Left&& yMouse < RetreivedShape->ShapeGroup.Top && yMouse >  RetreivedShape->ShapeGroup.Bottom)
		{
			//Found
			//cout << " Mouse Inside Region" << endl;
			//cout << " PageItem Start : " << CurrentID - RetreivedShape->PageItem.ShapeOffset << endl;
			return CurrentID - RetreivedShape->ShapeGroup.ShapeOffset;
		}

		//Not Found Set up NextGroup
		//cout << " Out Of Mouse Region " << endl;
		int NextGroupID = RetreivedShape->ShapeGroup.ShapeCount - RetreivedShape->ShapeGroup.ShapeOffset + 1;
		CurrentID += NextGroupID;
		RetreivedShape += NextGroupID;
	}

}

glm::vec2 PageGroupItem::ConvertEndToMiddle(glm::vec2 Position, glm::vec2 Size)
{
	Position[0] -= Size[0] / 2;
	return Position;
}

glm::vec2 PageGroupItem::ConvertBeginningToMiddle(glm::vec2 Position, glm::vec2 Size)
{
	Position[0] += Size[0] / 2;
	return Position;
}

void SwithToPageItem(int ShapeID)
{
	//if (SetInStone != true && ShapeID > -1 && ShapeID < CurrentPage->MaxShapeDataCount)
	//{
	//	this->LoadedShapeData = CurrentPage->GetShapeDataR(ShapeID);
	//}
}
