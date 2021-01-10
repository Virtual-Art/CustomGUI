#include "PageGroupItem.h"

PageGroupItem::PageGroupItem()
{
	cout << "PageItem Added" << endl;
	CurrentPageItem.Page = nullptr;
	CurrentPage = nullptr;
}

PageGroupItem::PageGroupItem(Page& Page)
{
	if (&Page != nullptr)
	{
		cout << "PageItem Added" << endl;
		CurrentPage = &Page;
		CurrentPageItem.Page = &Page;
		CurrentShapeGroup.Page = &Page;
		CurrentPageItem.Page->PageItemCount++;
		CurrentPageItem.GroupID = CurrentPageItem.Page->PageItemCount;
		CurrentPageItem.GroupID = CurrentPageItem.Page->PageItemCount;
	}
}

//Create a grid that is already set up & can be changed
//Group can't be switched with another
PageGroupItem::PageGroupItem(Page& Page, PageGroupItemData& PageItemData)
{
	//GroupData not really working which is weird cause quad is
	CurrentPageItem = PageItemData;
	CurrentPage = &Page;
	CurrentPageItem.Page = &Page;
	CurrentShapeGroup.Page = &Page;
	CurrentPageItem.Page->PageItemCount++;
	CurrentPageItem.GroupID = CurrentPageItem.Page->PageItemCount;
}

//Group can be changed for another
PageGroupItem::PageGroupItem(Page& Page, int ID)
{
	if (&Page != nullptr)
	{
		CurrentPageItem.Page = &Page;
		CurrentPage = &Page;
		cout << "yay " << endl;
		if (ID != -1)
		{
			CurrentShape = Page.GetShapeDataR(ID);
			ShapeToGroup(CurrentShape);
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
	this->CurrentPageItem.Position = Position;
	//ReCalibrateID();
	Update();
}

void PageGroupItem::OffsetPosition(glm::vec2 Position)
{
	this->CurrentPageItem.Position += Position;
	//ReCalibrateID();
	Update();
}

void PageGroupItem::OffsetPosition(glm::vec2 Position, glm::vec2 bools)
{

	this->CurrentPageItem.Position += Position;
	ReCalibrateID();
	for (int CurrentShapeID = CurrentPageItem.GroupID; CurrentShapeID < CurrentPageItem.GroupID + CurrentPageItem.ShapeCount; CurrentShapeID++)
	{
		CurrentShape = CurrentPageItem.Page->GetShapeDataR(CurrentShapeID);
	}
}

void PageGroupItem::ShapeToGroup(ShapeData& ShapeData)
{
	//PageItem
	CurrentPageItem.GroupID        = ShapeData.PageGroupItemID;
	CurrentPageItem.ShapeStartID   = ShapeData.PageGroupItemShapeStartID;
	CurrentPageItem.ShapeCount     = ShapeData.PageGroupShapeCount;
	CurrentPageItem.Position       = ShapeData.PageGroupItemPosition;
	cout << "POSITON GOT BACK = " << CurrentPageItem.Position[0] << " , " << CurrentPageItem.Position[1] << endl;
	CurrentPageItem.Size           = ShapeData.PageGroupItemSize;
	CurrentPageItem.Color          = ShapeData.PageGroupItemColor;
	CurrentPageItem.MouseAccess    = ShapeData.PageGroupItemMouseAccess;
	CurrentPageItem.Centered       = ShapeData.PageGroupItemCentered;
	CurrentPageItem.Highlighted    = ShapeData.PageGroupItemHighlighted;
	CurrentPageItem.ShapeType      = ShapeData.ShapeDataType;
	CurrentPageItem.XYShapesPerRow = ShapeData.PageGroupItemXYShapePerRow;
	CurrentPageItem.ShapeDataSize  = ShapeData.PageGroupItemShapeSize;
	CurrentPageItem.Left           = ShapeData.PageGroupItemLeft;
	CurrentPageItem.Right          = ShapeData.PageGroupItemRight;
	CurrentPageItem.Top            = ShapeData.PageGroupItemTop;
	CurrentPageItem.Bottom         = ShapeData.PageGroupItemBottom;

	//ShapeGroup
	CurrentShapeGroup.PageItemID           = ShapeData.PageGroupItemID;
	CurrentShapeGroup.PageItemShapeStartID = ShapeData.PageGroupItemShapeStartID;
	CurrentShapeGroup.PageItemShapeCount   = ShapeData.PageGroupItemShapeCount;

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

void PageGroupItem::DeletePageGroupItem()
{

}

void PageGroupItem::SwitchToPageGroupItem(int RequstedShapeID)
{
	if (RequstedShapeID != -1 && RequstedShapeID < CurrentPageItem.Page->ShapeAmount())
	{
		CurrentShape = CurrentPageItem.Page->GetShapeDataR(RequstedShapeID);
		ShapeToGroup(CurrentShape);
	}
	else
	{
		cout << "ERROR::Could Not Switch To PageGroupItem::ID not valid" << endl;
	}
}

void PageGroupItem::SwitchToPageGroupItem(Page& Page, int RequstedShapeID)
{

}

void PageGroupItem::SetPageGroupItem(ShapeData& ShapeData)
{

}

void PageGroupItem::SetPageGroupItem(ShapeData& ShapeData, glm::vec2 PSConversions)
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

	if (Left < CurrentPageItem.Left || CurrentPageItem.Left == -3.0)
	{
		CurrentPageItem.Left = Left;
	}

	if (Right > CurrentPageItem.Right || CurrentPageItem.Right == -3.0)
	{
		CurrentPageItem.Right = Right;
	}

	if (Top > CurrentPageItem.Top || CurrentPageItem.Top == -3.0)
	{
		CurrentPageItem.Top = Top;
	}

	if (Bottom < CurrentPageItem.Bottom || CurrentPageItem.Bottom == -3.0)
	{
		CurrentPageItem.Bottom = Bottom;
	}

}

void PageGroupItem::ReCalibrateID()
{
	cout << "Recalibrating Group (" << CurrentPageItem.GroupID << ") " << endl;

	int CurrentID = 0;
	int GroupStart = 0;

	//Maintenance
	//BoundsChecks()
	if (CurrentPageItem.ShapeStartID < CurrentPageItem.Page->ShapeAmount())
	{
		//in range
		CurrentID = CurrentPageItem.ShapeStartID;
		GroupStart = CurrentPageItem.ShapeStartID;
	}
	if (CurrentPageItem.ShapeStartID > CurrentPageItem.Page->ShapeAmount())
	{
		//out of range
		CurrentID = CurrentPageItem.Page->ShapeAmount();
		GroupStart = CurrentPageItem.Page->ShapeAmount();
	}

	///Check if ID is valid
	if (CurrentID > -1)
	{
		cout << "Checking ID: " << CurrentID << "... " << endl;
		ShapeData* RetreivedShape = CurrentPageItem.Page->GetShapeDataP(CurrentID);


		//Group Calibrated
		if (RetreivedShape->PageGroupItemID == CurrentPageItem.GroupID)
		{
			//Set the ID
			CurrentPageItem.ShapeStartID = CurrentID - RetreivedShape->PageGroupItemShapeOffset;
			cout << " Group: " << RetreivedShape->PageGroupItemID << " Match Successfully Found!" << endl;
			cout << "Group Start : " << CurrentID - RetreivedShape->PageGroupItemShapeOffset << endl;
			cout << "--------" << endl;
			return;
		}

		//Group UnCalibrated
		//if (RetreivedShape->PageGroupID != CurrentGroupData.GroupID)
		if (RetreivedShape->PageGroupItemID != CurrentPageItem.GroupID)
		{
			//Go up
			//if(RetreivedShape->PageGroupID <CurrentGroupData.GroupID)
			if (RetreivedShape->PageGroupItemID < CurrentPageItem.GroupID)
			{
				CurrentPageItem.ShapeStartID = FindNextGroup(CurrentID, RetreivedShape);
				RetreivedShape->PageGroupItemShapeStartID = CurrentPageItem.ShapeStartID;
				return;
			}

			//GO down
			if (RetreivedShape->PageGroupItemID > CurrentPageItem.GroupID)
			{
				CurrentPageItem.ShapeStartID = FindPreviousGroup(CurrentID, RetreivedShape);
				RetreivedShape->PageGroupItemShapeStartID = CurrentPageItem.ShapeStartID;
				return;
			}
		}
	}
}

//Returns the ID of the first shape in the group
int PageGroupItem::FindNextGroup(int CurrentID, ShapeData* RetreivedShape)
{
	//Found
	if (RetreivedShape->PageGroupItemID == CurrentPageItem.GroupID)
	{
		cout << " Group: " << RetreivedShape->PageGroupItemID << " Match Found!" << endl;
		cout << " Group Start : " << CurrentID - RetreivedShape->ShapeGroupOffset << endl;
		cout << "--------" << endl;
		return CurrentID - RetreivedShape->ShapeGroupOffset;
	};

	//Set up next group 
	cout << " Group: " << RetreivedShape->PageGroupItemID << " No Match" << endl;
	cout << "Trying Shape ID: " << RetreivedShape->ID  << endl;
	int NextGroupID = RetreivedShape->PageGroupItemShapeCount - RetreivedShape->PageGroupItemShapeOffset + 1;
	Log::LogInt("Shape Count", RetreivedShape->PageGroupItemShapeCount);
	Log::LogInt("Page Group Item Offset", RetreivedShape->PageGroupItemShapeOffset);
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
	if (RetreivedShape->PageGroupItemID = CurrentPageItem.GroupID)
	{
		cout << " Group: " << RetreivedShape->PageGroupItemID << " Match Found!" << endl;
		cout << " Group Start : " << CurrentID - RetreivedShape->PageGroupItemShapeOffset << endl;
		cout << "--------" << endl;
		return CurrentID - RetreivedShape->PageGroupItemShapeOffset;
	};

	cout << " Group: " << RetreivedShape->PageGroupItemID << " No Match" << endl;
	//Set up next group / Not found
	int NextGroupTranslation = RetreivedShape->PageGroupItemShapeOffset - 1;
	RetreivedShape += NextGroupTranslation;
	CurrentID += NextGroupTranslation;

	//Check Next Group
	int FoundID = FindPreviousGroup(CurrentID, RetreivedShape);
	return FoundID;
}

int PageGroupItem::GetShapeGroup(int ChildGroupID)
{
	ReCalibrateID();
	int CurrentID = CurrentPageItem.ShapeStartID;
	bool Found = false;
	ShapeData* RetreivedShape = CurrentPageItem.Page->GetShapeDataP(CurrentID);

	//Found
	while (RetreivedShape->PageGroupItemID == CurrentPageItem.GroupID)
	{
		if (RetreivedShape->GroupID == ChildGroupID)
		{
			cout << " ShapeGroup: " << RetreivedShape->GroupID << " Match Found!" << endl;
			cout << " ShapeGroup Start : " << CurrentID - RetreivedShape->ShapeGroupOffset << endl;
			cout << "--------" << endl;
			return CurrentID - RetreivedShape->ShapeGroupOffset;
		}

		//Not Found, Next group
		cout << " No Match " << endl;
		int NextGroupID = RetreivedShape->ShapeGroupCount - RetreivedShape->ShapeGroupOffset + 1;
		CurrentID += NextGroupID;
		RetreivedShape += NextGroupID;
	}

	cout << "Group Not Found" << endl;
	return -1;
}

void PageGroupItem::SetMouseAccess()
{
	if (CurrentPageItem.MouseAccess == true)
	{
		//cout << "PageItem Mouse access!" << endl;
		//Log::LogVec2("PageItem Position", CurrentShape.ShapeGroupPosition);
		//Log::LogVec2("PageItem Size", CurrentShape.ShapeGroupSize);

		//this->CurrentShape.PageGroupItemTop = (CurrentPageItem.Position[1] + (CurrentPageItem.Size[1] / 2));
		//this->CurrentShape.PageGroupItemBottom = (CurrentPageItem.Position[1] - (CurrentPageItem.Size[1] / 2));
		//this->CurrentShape.PageGroupItemLeft = (CurrentPageItem.Position[0] - (CurrentPageItem.Size[0] / 2));
		//this->CurrentShape.PageGroupItemRight = (CurrentPageItem.Position[0] + (CurrentPageItem.Size[0] / 2));

		for (int i = CurrentPageItem.ShapeStartID; i < CurrentPageItem.ShapeStartID + CurrentPageItem.ShapeCount + 1; i++)
		{
			//Log::LogString("yes mouse access");
			ShapeData* RetreivedShape = CurrentPageItem.Page->GetShapeDataP(i);
			//RetreivedShape->PageGroupItemTop = CurrentShape.ShapeGroupTop;
			//RetreivedShape->PageGroupItemBottom = CurrentShape.ShapeGroupBottom;
			//RetreivedShape->PageGroupItemLeft = CurrentShape.ShapeGroupLeft;
			//RetreivedShape->PageGroupItemRight = CurrentShape.ShapeGroupRight;

			RetreivedShape->PageGroupItemTop = CurrentPageItem.Top;
			RetreivedShape->PageGroupItemBottom = CurrentPageItem.Bottom;
			RetreivedShape->PageGroupItemLeft = CurrentPageItem.Left;
			RetreivedShape->PageGroupItemRight = CurrentPageItem.Right;

			//cout << "GroupItem: " << RetreivedShape->GroupID << endl;
			//cout << "GroupItemTop " << RetreivedShape->PageGroupItemTop << endl;
			//cout << "GroupItemBottom " << RetreivedShape->PageGroupItemBottom << endl;
			//cout << "GroupItemLeft " << RetreivedShape->PageGroupItemLeft << endl;
			//cout << "GroupItemRight " << RetreivedShape->PageGroupItemRight << endl;
			//cout << "---- " << endl;
		}
	}
	else
	{
		for (int i = CurrentPageItem.ShapeStartID; i < CurrentPageItem.ShapeStartID + CurrentPageItem.ShapeCount; i++)
		{
			Log::LogString("no mouse access");
			ShapeData* RetreivedShape = CurrentPageItem.Page->GetShapeDataP(i);
			RetreivedShape->PageGroupItemTop = -3;
			RetreivedShape->PageGroupItemBottom = -3;
			RetreivedShape->PageGroupItemLeft = 3;
			RetreivedShape->PageGroupItemRight = 3;
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
	ShapeData* RetreivedShape = CurrentPageItem.Page->GetShapeDataP(CurrentID);

	//Iterate through all  
	//or start from zero, and go up till you find it...
	//or start from top and go down till you find it...
	for (int i = 0; i < CurrentPageItem.Page->ShapeAmount(); i++)
	{
		//Log::LogInt("Checking ID", RetreivedShape->ID);
		//Log::LogInt("PageGroup:", RetreivedShape->PageGroupItemID);
		if (xMouse < RetreivedShape->ShapeGroupRight && xMouse >  RetreivedShape->ShapeGroupLeft&& yMouse < RetreivedShape->ShapeGroupTop && yMouse >  RetreivedShape->ShapeGroupBottom)
		{
			//Found
			//cout << " Mouse Inside Region" << endl;
			//cout << " PageItem Start : " << CurrentID - RetreivedShape->PageGroupItemShapeOffset << endl;
			return CurrentID - RetreivedShape->ShapeGroupOffset;
		}

		//Not Found Set up NextGroup
		//cout << " Out Of Mouse Region " << endl;
		int NextGroupID = RetreivedShape->ShapeGroupCount - RetreivedShape->ShapeGroupOffset + 1;
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
	//	this->CurrentShapeData = CurrentPage->GetShapeDataR(ShapeID);
	//}
}
