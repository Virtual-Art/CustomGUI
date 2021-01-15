#include "PageGroupItem.h"

PageGroupItem::PageGroupItem()
{
	CurrentPage = nullptr;
}

PageGroupItem::PageGroupItem(Page& Page)
{
	if (&Page != nullptr)
	{
		Initialized = true;
		CurrentPage = &Page;
		CurrentPage->TotalPageItemCount++;
		CurrentPage->CurrentPageItem++;
		CurrentPage->CurrentShapeGroup = 0;
		CurrentPage->CurrentShape = 0;
		LoadedShape.PageItem.ID = CurrentPage->CurrentPageItem;
		LoadedShape.PageItem.ShapeStart = Page.ShapeAmount();
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
PageGroupItem::PageGroupItem(Page& Page, PageItemData& PageItemData)
{
	if (&Page != nullptr)
	{
		Initialized = true;
		CurrentPage = &Page;
		LoadedShape.PageItem = PageItemData;
		//CurrentPage->PageItemCount++;
		//LoadedShape.PageItem.ID = CurrentPage->PageItemCount;
		LoadedShape.PageItem.ShapeStart = Page.ShapeAmount();
		//CurrentPage->CurrentPageItemCount++;
		//CurrentPage->CurrentPageItem = CurrentPage->CurrentPageItemCount;
		CurrentPage->CurrentShape = 0;
	}
}

PageGroupItem::PageGroupItem(Page& Page, ShapeData& FullShape)
{
	
	if (&Page != nullptr)
	{
		Initialized = true;
		CurrentPage = &Page;
		LoadedShape = FullShape;
		//Book Keeping
		//CurrentPage->PageItemCount++;
		//LoadedShape.PageItem.ID = CurrentPage->PageItemCount;
		LoadedShape.PageItem.ShapeStart = Page.ShapeAmount();
		//CurrentPage->CurrentPageItemCount++;
		//CurrentPage->CurrentPageItem = CurrentPage->CurrentPageItemCount;
		CurrentPage->CurrentShape = 0;
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

void PageGroupItem::Switch(int RequstedShapeID)
{
	if (RequstedShapeID != -1 && RequstedShapeID < CurrentPage->ShapeAmount())
	{
		LoadedShape = CurrentPage->GetShapeDataR(RequstedShapeID);
		ShapeToGroup(LoadedShape);
	}
	else
	{
		cout << "ERROR::Could Not Switch To PageItem.::ID not valid" << endl;
	}
}

void PageGroupItem::Switch(Page& Page, int RequstedShapeID)
{

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
	cout << "Recalibrating Group (" << LoadedShape.PageItem.ID << ") " << endl;

	int CurrentID = 0;
	int GroupStart = 0;

	//Maintenance
	//BoundsChecks()
	if (LoadedShape.PageItem.ShapeStart < CurrentPage->ShapeAmount())
	{
		//in range
		CurrentID = LoadedShape.PageItem.ShapeStart;
		GroupStart = LoadedShape.PageItem.ShapeStart;
	}
	if (LoadedShape.PageItem.ShapeStart > CurrentPage->ShapeAmount())
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
				LoadedShape.PageItem.ShapeStart = FindNextGroup(CurrentID, RetreivedShape);
				RetreivedShape->PageItem.ShapeStart = LoadedShape.PageItem.ShapeStart;
				return;
			}

			//GO down
			if (RetreivedShape->PageItem.ID > LoadedShape.PageItem.ID)
			{
				LoadedShape.PageItem.ShapeStart = FindPreviousGroup(CurrentID, RetreivedShape);
				RetreivedShape->PageItem.ShapeStart = LoadedShape.PageItem.ShapeStart;
				return;
			}
		}
	}
}

//Returns the ID of the first shape in the group
int PageGroupItem::FindNextGroup(int CurrentID, ShapeData* RetreivedShape)
{
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
	cout << "Trying Shape ID: " << RetreivedShape->ID  << endl;
	int NextGroupID = RetreivedShape->PageItem.ShapeCount - RetreivedShape->PageItem.ShapeOffset + 1;
	Log::LogInt("Shape Count", RetreivedShape->PageItem.ShapeCount);
	Log::LogInt("Page Group Item Offset", RetreivedShape->PageItem.ShapeOffset);
	cout << "Shapes to hop: " << NextGroupID << endl;
	RetreivedShape += NextGroupID;
	CurrentID += NextGroupID;

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
