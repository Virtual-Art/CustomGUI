#include "PageGroup.h"

PageGroup::PageGroup()
{
	Initialized = false;
	CurrentPage = nullptr;
}

PageGroup::PageGroup(Page& Page)
{
	if (&Page != nullptr)
	{
		Initialized = true;
		CurrentPage = &Page;
		CurrentPage->TotalPageGroupCount++;
		Page.CurrentPageGroup = Page.TotalPageGroupCount;
		Page.CurrentPageItem = 0;
		Page.CurrentShapeGroup = 0;
		Page.CurrentShape = 0;
		Log::LogString("-------Shape Added--------");
		Log::LogInt("CurrentShape     ", Page.CurrentShape);
		Log::LogInt("CurrentShapeGroup", Page.CurrentShapeGroup);
		Log::LogInt("CurrentPageItem  ", Page.CurrentPageItem);
		Log::LogInt("CurrentPageGroup ", Page.CurrentPageGroup);
		Log::LogString(" ");
	}
}

PageGroup::PageGroup(Page& Page, PageGroupData& PageGroup)
{
	if (&Page != nullptr)
	{
		Initialized = true;
		CurrentPage = &Page;
		LoadedShape.PageGroup = PageGroup;
		//CurrentPage->PageItemCount++;
		//LoadedShape.PageItem.ID = CurrentPage->PageItemCount;
		Page.CurrentPageGroup = Page.TotalPageItemCount;
		Page.CurrentPageItem = 0;
		Page.CurrentShapeGroup = 0;
		Page.CurrentShape = 0;
	}
	//;
}

PageGroup::PageGroup(Page& Page, ShapeData& ShapeData)
{
	if (&Page != nullptr)
	{
		Initialized = true;
		CurrentPage = &Page;
		LoadedShape = ShapeData;
		//CurrentPage->PageItemCount++;
		//Page.CurrentPageGroup = Page.PageItemCount;
		Page.CurrentPageItem = 0;
		Page.CurrentShapeGroup = 0;
		Page.CurrentShape = 0;
	}
	//CurrentPageItem.GroupID = CurrentPageItem.Page->PageItemCount;
}

void PageGroup::ShapeToGroup(ShapeData& ShapeData)
{
	//Loading our Item data from first shape
	//LoadedShape.PageGroup.ShapeStartID = ShapeData.PageGroupID;
	//LoadedShape.PageGroup.XYShapesPerRow = ShapeData.PageGroupXYShapePerRow;
	//LoadedShape.PageGroup.ShapeDataSize = ShapeData.PageGroupShapeSize;
	//LoadedShape.PageGroup.Position = ShapeData.PageGroupPosition;
	//LoadedShape.PageGroup.Size = ShapeData.PageGroupSize;
	//LoadedShape.PageGroup.Color = ShapeData.PageGroupColor;
	//LoadedShape.PageGroup.MouseAccess = ShapeData.PageGroupMouseAccess;
	//LoadedShape.PageGroup.Centered = ShapeData.PageGroupCentered;
	//LoadedShape.PageGroup.Highlighted = ShapeData.PageGroupHighlighted;
	//LoadedShape.PageGroup.ShapeType = ShapeData.ShapeDataType;
	//CurrentPageItem.ShapeCount     = ShapeData.PageGroupItemCount;
}

PageGroup::PageGroup(Page& Page, int ID)
{
	if (&Page != nullptr)
	{
		Initialized = true;
		CurrentPage = &Page;
		if (IsInBounds(ID) == false) Log::LogString("Shape Group Initialization failed:: ID out of bounds"); return;
		LoadedShape = Page.GetShapeDataR(ID);
		Page.CurrentPageGroup = LoadedShape.PageGroup.ID;
		Page.CurrentPageItem = 0;
		Page.CurrentShapeGroup = 0;
		Page.CurrentShape = 0;
	}
	Log::LogString("Page Item Not Initialized");
}


void PageGroup::ReCalibrateID()
{
	cout << "Recalibrating Group (" << LoadedShape.PageGroup.ID << ") " << endl;

	int CurrentID = 0;
	int GroupStart = 0;

	//Maintenance
	//BoundsChecks()
	if (LoadedShape.PageGroup.ShapeStart < CurrentPage->ShapeAmount())
	{
		//in range
		CurrentID = LoadedShape.PageGroup.ShapeStart;
		GroupStart = LoadedShape.PageGroup.ShapeStart;
	}
	if (LoadedShape.PageGroup.ShapeStart> CurrentPage->ShapeAmount())
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
		if (RetreivedShape->ShapeGroup.ID == LoadedShape.PageGroup.ID)
		{
			//Set the ID
			LoadedShape.PageGroup.ShapeStart = CurrentID - RetreivedShape->PageGroup.ShapeOffset;
			cout << " Group: " << RetreivedShape->PageGroup.ID << " Match Found!" << endl;
			cout << "Group Start : " << CurrentID - RetreivedShape->PageGroup.ShapeOffset << endl;
			cout << "--------" << endl;
			return;
		}

		//Group UnCalibrated
		//if (RetreivedShape->PageGroupID != CurrentGroupData.GroupID)
		if (RetreivedShape->PageGroup.ID != LoadedShape.PageGroup.ID)
		{
			//Go up
			//if(RetreivedShape->PageGroupID <CurrentGroupData.GroupID)
			if (RetreivedShape->PageGroup.ID < LoadedShape.PageGroup.ID)
			{
				LoadedShape.PageGroup.ShapeStart = FindNextGroup(CurrentID, RetreivedShape);
				RetreivedShape->PageGroup.ShapeStart = LoadedShape.PageGroup.ShapeStart;
				return;
			}

			//GO down
			if (RetreivedShape->PageGroup.ID > LoadedShape.PageGroup.ID)
			{
				LoadedShape.PageGroup.ShapeStart = FindPreviousGroup(CurrentID, RetreivedShape);
				RetreivedShape->PageGroup.ShapeStart = LoadedShape.PageGroup.ShapeStart;
				return;
			}
		}
	}
}

//Returns the ID of the first shape in the group
int PageGroup::FindNextGroup(int CurrentID, ShapeData* RetreivedShape)
{
	//Found
	if (RetreivedShape->PageGroup.ID == LoadedShape.PageGroup.ID)
	{
		cout << " Group: " << RetreivedShape->PageGroup.ID << " Match Found!" << endl;
		cout << " Group Start : " << CurrentID - RetreivedShape->ShapeGroup.ShapeOffset << endl;
		cout << "--------" << endl;
		return CurrentID - RetreivedShape->ShapeGroup.ShapeOffset;
	};

	//Set up next group 
	cout << " Group: " << RetreivedShape->PageItem.ID << " No Match" << endl;
	cout << "Trying Shape ID: " << RetreivedShape->ID << endl;
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


int PageGroup::FindPreviousGroup(int CurrentID, ShapeData* RetreivedShape)
{
	//Found
	if (RetreivedShape->PageGroup.ID = LoadedShape.PageGroup.ID)
	{
		cout << " Group: " << RetreivedShape->PageGroup.ID << " Match Found!" << endl;
		cout << " Group Start : " << CurrentID - RetreivedShape->PageGroup.ShapeOffset << endl;
		cout << "--------" << endl;
		return CurrentID - RetreivedShape->PageGroup.ShapeOffset;
	};

	cout << " Group: " << RetreivedShape->PageGroup.ID << " No Match" << endl;
	//Set up next group / Not found
	int NextGroupTranslation = RetreivedShape->PageGroup.ShapeOffset - 1;
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
	int CurrentID = LoadedShape.PageGroup.ShapeStart;
	bool Found = false;
	ShapeData* RetreivedShape = CurrentPage->GetShapeDataP(CurrentID);

	//Found
	while (RetreivedShape->PageGroup.ID == LoadedShape.PageGroup.ID)
	{
		if (RetreivedShape->PageItem.ID == ChildGroupID)
		{
			cout << " PageItem: " << RetreivedShape->ShapeGroup.ID << " Match Found!" << endl;
			cout << " PageItem Start : " << CurrentID - RetreivedShape->PageItem.ShapeOffset << endl;
			cout << "--------" << endl;
			return CurrentID - RetreivedShape->PageItem.ShapeOffset;
		}

		//Not Found, Next group
		cout << " No Match " << endl;
		int NextGroupID = RetreivedShape->PageItem.ShapeCount - RetreivedShape->PageItem.ShapeOffset + 1;
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
    ShapeData* RetreivedShape = CurrentPage->GetShapeDataP(CurrentID);

	//Iterate through all  
	//or start from zero, and go up till you find it...
	//or start from top and go down till you find it...
	for (int i = 0; i < CurrentPage->ShapeAmount(); i++)
	{
		//Log::LogInt("Checking ID", RetreivedShape->ID);
		//Log::LogInt("PageGroup:", RetreivedShape->PageGroupItemID);
		if (xMouse < RetreivedShape->PageItem.Right && xMouse >  RetreivedShape->PageItem.Left && yMouse < RetreivedShape->PageItem.Top && yMouse >  RetreivedShape->PageItem.Bottom)
		{
			//Found
			//cout << " Mouse Inside Region" << endl;
			//cout << " PageItem Start : " << CurrentID - RetreivedShape->PageGroupItemShapeOffset << endl;
			return CurrentID - RetreivedShape->PageItem.ShapeOffset;
		}

		//Not Found Set up NextGroup
		//cout << " Out Of Mouse Region " << endl;
		int NextGroupID = RetreivedShape->PageItem.ShapeCount - RetreivedShape->PageItem.ShapeOffset + 1;
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

	if (GroupLeft > LoadedShape.PageGroup.Left)
	{
		LoadedShape.PageGroup.Left = GroupLeft;
	}

	if (GroupRight > LoadedShape.PageGroup.Right)
	{
		LoadedShape.PageGroup.Right = GroupRight;
	}

	if (GroupTop > LoadedShape.PageGroup.Top)
	{
		LoadedShape.PageGroup.Top = GroupTop;
	}

	if (GroupBottom > LoadedShape.PageGroup.Bottom)
	{
		LoadedShape.PageGroup.Bottom = GroupBottom;
	}
}

