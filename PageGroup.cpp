#include "PageGroup.h"

PageGroup::PageGroup()
{
	CurrentPageGroup.Page = nullptr;
}

PageGroup::PageGroup(Page& Page)
{
	if (&Page != nullptr)
	{
		cout << "PageItem Added" << endl;
		CurrentPageGroup.Page = &Page;
		CurrentPageItem.Page = &Page;
		CurrentPageGroup.Page->PageItemCount++;
	}
}

PageGroup::PageGroup(Page& Page, PageGroupData& PageGroup)
{
	//GroupData not really working which is weird cause quad is
	CurrentPageGroup = PageGroup;
	CurrentPageGroup.Page = &Page;
	CurrentPageItem.Page = &Page;
	CurrentShapeGroup.Page = &Page;
	CurrentPageItem.Page->PageItemCount++;
	//CurrentPageItem.GroupID = CurrentPageItem.Page->PageItemCount;
}

void PageGroup::ShapeToGroup(ShapeData& ShapeData)
{
	//Loading our Item data from first shape
	CurrentPageGroup.ShapeStartID = ShapeData.PageGroupID;
	CurrentPageGroup.XYShapesPerRow = ShapeData.PageGroupXYShapePerRow;
	CurrentPageGroup.ShapeDataSize = ShapeData.PageGroupShapeSize;
	CurrentPageGroup.Position = ShapeData.PageGroupPosition;
	CurrentPageGroup.Size = ShapeData.PageGroupSize;
	CurrentPageGroup.Color = ShapeData.PageGroupColor;
	CurrentPageGroup.MouseAccess = ShapeData.PageGroupMouseAccess;
	CurrentPageGroup.Centered = ShapeData.PageGroupCentered;
	CurrentPageGroup.Highlighted = ShapeData.PageGroupHighlighted;
	CurrentPageGroup.ShapeType = ShapeData.ShapeDataType;
	//CurrentPageItem.ShapeCount     = ShapeData.PageGroupItemCount;
}

PageGroup::PageGroup(Page& Page, int ID)
{
	CurrentPageGroup.Page = &Page;
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


void PageGroup::ReCalibrateID()
{
	cout << "Recalibrating Group (" << CurrentPageGroup.GroupID << ") " << endl;

	int CurrentID = 0;
	int GroupStart = 0;

	//Maintenance
	//BoundsChecks()
	if (CurrentPageGroup.ShapeStartID < CurrentPageGroup.Page->ShapeAmount())
	{
		//in range
		CurrentID = CurrentPageGroup.ShapeStartID;
		GroupStart = CurrentPageGroup.ShapeStartID;
	}
	if (CurrentPageGroup.ShapeStartID > CurrentPageGroup.Page->ShapeAmount())
	{
		//out of range
		CurrentID = CurrentPageGroup.Page->ShapeAmount();
		GroupStart = CurrentPageGroup.Page->ShapeAmount();
	}

	///Check if ID is valid
	if (CurrentID > -1)
	{
		cout << "Checking ID: " << CurrentID << "... " << endl;
		ShapeData* RetreivedShape = CurrentPageGroup.Page->GetShapeDataP(CurrentID);


		//Group Calibrated
		if (RetreivedShape->PageGroupID == CurrentPageGroup.GroupID)
		{
			//Set the ID
			CurrentPageGroup.ShapeStartID = CurrentID - RetreivedShape->PageGroupShapeOffset;
			cout << " Group: " << RetreivedShape->PageGroupID << " Match Found!" << endl;
			cout << "Group Start : " << CurrentID - RetreivedShape->PageGroupShapeOffset << endl;
			cout << "--------" << endl;
			return;
		}

		//Group UnCalibrated
		//if (RetreivedShape->PageGroupID != CurrentGroupData.GroupID)
		if (RetreivedShape->PageGroupID != CurrentPageGroup.GroupID)
		{
			//Go up
			//if(RetreivedShape->PageGroupID <CurrentGroupData.GroupID)
			if (RetreivedShape->PageGroupID < CurrentPageGroup.GroupID)
			{
				CurrentPageGroup.ShapeStartID = FindNextGroup(CurrentID, RetreivedShape);
				RetreivedShape->PageGroupShapeStartID = CurrentPageGroup.ShapeStartID;
				return;
			}

			//GO down
			if (RetreivedShape->PageGroupID > CurrentPageGroup.GroupID)
			{
				CurrentPageGroup.ShapeStartID = FindPreviousGroup(CurrentID, RetreivedShape);
				RetreivedShape->PageGroupShapeStartID = CurrentPageGroup.ShapeStartID;
				return;
			}
		}
	}
}

//Returns the ID of the first shape in the group
int PageGroup::FindNextGroup(int CurrentID, ShapeData* RetreivedShape)
{
	//Found
	if (RetreivedShape->PageGroupID == CurrentPageGroup.GroupID)
	{
		cout << " Group: " << RetreivedShape->PageGroupID << " Match Found!" << endl;
		cout << " Group Start : " << CurrentID - RetreivedShape->ShapeGroupOffset << endl;
		cout << "--------" << endl;
		return CurrentID - RetreivedShape->ShapeGroupOffset;
	};

	//Set up next group 
	cout << " Group: " << RetreivedShape->PageGroupItemID << " No Match" << endl;
	cout << "Trying Shape ID: " << RetreivedShape->ID << endl;
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


int PageGroup::FindPreviousGroup(int CurrentID, ShapeData* RetreivedShape)
{
	//Found
	if (RetreivedShape->PageGroupItemID = CurrentPageGroup.GroupID)
	{
		cout << " Group: " << RetreivedShape->PageGroupID << " Match Found!" << endl;
		cout << " Group Start : " << CurrentID - RetreivedShape->PageGroupShapeOffset << endl;
		cout << "--------" << endl;
		return CurrentID - RetreivedShape->PageGroupShapeOffset;
	};

	cout << " Group: " << RetreivedShape->PageGroupID << " No Match" << endl;
	//Set up next group / Not found
	int NextGroupTranslation = RetreivedShape->PageGroupShapeOffset - 1;
	RetreivedShape += NextGroupTranslation;
	CurrentID += NextGroupTranslation;

	//Check Next Group
	int FoundID = FindPreviousGroup(CurrentID, RetreivedShape);
	return FoundID;
}


//goal is to get page item StartID
int PageGroup::FindChildGroup(int ChildGroupID)
{
	ReCalibrateID();
	int CurrentID = CurrentPageGroup.ShapeStartID;
	bool Found = false;
	ShapeData* RetreivedShape = CurrentPageGroup.Page->GetShapeDataP(CurrentID);

	//Found
	while (RetreivedShape->PageGroupID == CurrentPageGroup.GroupID)
	{
		if (RetreivedShape->PageGroupItemID == ChildGroupID)
		{
			cout << " PageItem: " << RetreivedShape->GroupID << " Match Found!" << endl;
			cout << " PageItem Start : " << CurrentID - RetreivedShape->PageGroupItemShapeOffset << endl;
			cout << "--------" << endl;
			return CurrentID - RetreivedShape->PageGroupItemShapeOffset;
		}

		//Not Found, Next group
		cout << " No Match " << endl;
		int NextGroupID = RetreivedShape->PageGroupItemShapeCount - RetreivedShape->PageGroupItemShapeOffset + 1;
		CurrentID += NextGroupID;
		RetreivedShape += NextGroupID;
	}

	cout << "Group Not Found" << endl;
	return -1;
}

//Working
int PageGroup::FindPageItem(bool FromBottom, double xMouse, double yMouse)
{
   // ReCalibrateID();
    int CurrentID = 22;
    bool Found = false;
    ShapeData* RetreivedShape = CurrentPageGroup.Page->GetShapeDataP(CurrentID);

	//Iterate through all  
	//or start from zero, and go up till you find it...
	//or start from top and go down till you find it...
	for (int i = 0; i < CurrentPageGroup.Page->ShapeAmount(); i++)
	{
		//Log::LogInt("Checking ID", RetreivedShape->ID);
		//Log::LogInt("PageGroup:", RetreivedShape->PageGroupItemID);
		if (xMouse < RetreivedShape->PageGroupItemRight && xMouse >  RetreivedShape->PageGroupItemLeft && yMouse < RetreivedShape->PageGroupItemTop && yMouse >  RetreivedShape->PageGroupItemBottom)
		{
			//Found
			//cout << " Mouse Inside Region" << endl;
			//cout << " PageItem Start : " << CurrentID - RetreivedShape->PageGroupItemShapeOffset << endl;
			return CurrentID - RetreivedShape->PageGroupItemShapeOffset;
		}

		//Not Found Set up NextGroup
		//cout << " Out Of Mouse Region " << endl;
		int NextGroupID = RetreivedShape->PageGroupItemShapeCount - RetreivedShape->PageGroupItemShapeOffset + 1;
		CurrentID += NextGroupID;
		RetreivedShape += NextGroupID;
	}

  //  //Found
  //  while (Found == false)
  //  {
	//	
  //  	if (RetreivedShape->PageGroupItemID == ID)
  //  	{
  //  		cout << " Match Found" << endl;
  //  		cout << " PageItem Start : " << CurrentID - RetreivedShape->PageGroupItemShapeOffset << endl;
  //  		cout << "--------" << endl;
	//		Found = true;
  //  		return CurrentID - RetreivedShape->PageGroupItemShapeOffset;
  //  	}
  //  
  //  	//Not Found, Next group
  //  	cout << " No Match " << endl;
  //  	int NextGroupID = RetreivedShape->PageGroupItemShapeCount - RetreivedShape->PageGroupItemShapeOffset + 1;
  //  	CurrentID += NextGroupID;
  //  	RetreivedShape += NextGroupID;
  //  }
  //  
  //  cout << "Group Not Found" << endl;
    return -1;
}

float PageGroup::SetMouseAccess(glm::vec2 Position, glm::vec2 Size)
{
	float GroupLeft = Position[0] - Size[0] / 2;
	float GroupRight = Position[0] + Size[0] / 2;
	float GroupTop = Position[1] + Size[1] / 2;
	float GroupBottom = Position[1] - Size[1] / 2;

	if (GroupLeft > CurrentPageGroup.Left)
	{
		CurrentPageGroup.Left = GroupLeft;
	}

	if (GroupRight > CurrentPageGroup.Right)
	{
		CurrentPageGroup.Right = GroupRight;
	}

	if (GroupTop > CurrentPageGroup.Top)
	{
		CurrentPageGroup.Top = GroupTop;
	}

	if (GroupBottom > CurrentPageGroup.Bottom)
	{
		CurrentPageGroup.Bottom = GroupBottom;
	}
}

