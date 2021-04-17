#include "MasterElement.h"

void MasterElement::PrintBookStats(llBookData* llBook)
{
	Log::LogString("Printing Book Stats");
	int VertexIndex = 0;
	int PageCount = -1;
	int PageGroupCount = -1;
	int PageItemCount = -1;
	int ShapeGroupCount = -1;
	int ShapeCount = -1;
	int VertexCount = -1;

	if (llBook->Page != nullptr)
	{
		//Page
		llPageData* CurrentPage = llBook->Page;

		//Set to beginning
		while (CurrentPage->Previous != nullptr)
		{
			CurrentPage = CurrentPage->Previous;
		}

		while (CurrentPage != nullptr && CurrentPage->PageGroup != nullptr)
		{
			if (PageCount == -1)
			{
				cout << " " << endl;
			}
			PageCount++;
			//Page Group
			llPageGroupData* CurrentPageGroup = CurrentPage->PageGroup;
			//Set PageGroup Beginning
			/////////////////////////////////////////////////////
			while (CurrentPageGroup->Previous != nullptr)
			{
				CurrentPageGroup = CurrentPageGroup->Previous;
			}
			/////////////////////////////////////////////////////

			while (CurrentPageGroup != nullptr && CurrentPageGroup->PageItem != nullptr)
			{
				if (PageGroupCount == -1)
				{
					cout << "----P" << endl;
				}
				PageGroupCount++;
				//PageItem
				llPageItemData* CurrentPageItem = CurrentPageGroup->PageItem;
				//Set PageItem Beginning
				/////////////////////////////////////////////////////
				while (CurrentPageItem->Previous != nullptr)
				{
					CurrentPageItem = CurrentPageItem->Previous;
				}
				/////////////////////////////////////////////////////

				while (CurrentPageItem != nullptr && CurrentPageItem->ShapeGroup != nullptr)
				{
					if (PageItemCount == -1)
					{
						cout << "----------PG" << endl;
					}
					PageItemCount++;
					//ShapeGroup
					llShapeGroupData* CurrentShapeGroup = CurrentPageItem->ShapeGroup;
					//Set ShapeGroup to beginning
					/////////////////////////////////////////////////////
					while (CurrentShapeGroup->Previous != nullptr)
					{
						CurrentShapeGroup = CurrentShapeGroup->Previous;
					}
					/////////////////////////////////////////////////////

					while (CurrentShapeGroup != nullptr)
					{
						if (ShapeGroupCount == -1)
						{
							cout << "-----------------PI" << endl;
						}
						ShapeGroupCount++;
						//Shape
						llShapeData* CurrentShape = CurrentShapeGroup->Shape;
						if (CurrentShapeGroup->Shape != nullptr)
						{
							//Set shape to beginning
							/////////////////////////////////////////////////////
							while (CurrentShape->Previous != nullptr)
							{
								CurrentShape = CurrentShape->Previous;
							}
							/////////////////////////////////////////////////////

							while (CurrentShape != nullptr && CurrentShape->Vertexx != nullptr)
							{
								if (ShapeCount == -1)
								{
									cout << "---------------------SG" << endl;
								}
								ShapeCount++;
								//PrintllShape(CurrentShape);
								//Vertex
								llVertexData* CurrentVertex = CurrentShape->Vertexx;
								/////////////////////////////////////////////////////
								while (CurrentVertex->Previous != nullptr)
								{
									CurrentVertex = CurrentVertex->Previous;
								}
								cout << "P:" << PageCount << " | PG:" << PageGroupCount << " | PI:" << PageItemCount << " | SG:" << ShapeGroupCount << " | S:" << ShapeCount << " | Char: " << char(CurrentShape->Ascii) << " | " << CurrentShape << endl;
								/////////////////////////////////////////////////////
								while (CurrentVertex != nullptr)
								{
									if (VertexCount == -1)
									{
										//cout << "------------------------------S" << endl;
									}
									VertexCount++;

									CurrentVertex = CurrentVertex->Next;
								}
								VertexCount = -1;
								CurrentShape = CurrentShape->Next;
							}
						}
						ShapeCount = -1;
						CurrentShapeGroup = CurrentShapeGroup->Next;
					}
					ShapeGroupCount = -1;
					CurrentPageItem = CurrentPageItem->Next;
				}
				PageItemCount = -1;
				CurrentPageGroup = CurrentPageGroup->Next;
			}
			PageGroupCount = -1;
			CurrentPage = CurrentPage->Next;
		}
	}
	else
	{
		Log::LogString("Print Stats Failed. No Page linked to book ");
	}
}


void MasterElement::FindElement(llBookData* llBook, int ElementLevel, BookDirectory& BookDirectory)
{
	float xMouse = MouseManager::xPos;
	float yMouse = MouseManager::yPos;

	int VertexIndex = 0;
	int PageCount = 0;
	int PageGroupCount = 0;
	int PageItemCount = 0;
	int ShapeGroupCount = 0;
	int ShapeCount = 0;
	int VertexCount = 0;

	//llVertexData* SavedVertex = GetBookVertex(llBook);
	//llShapeData* SavedShape = GetBookShape(llBook);
	//llShapeGroupData* SavedShapeGroup = GetBookShapeGroup(llBook);
	//llPageItemData* SavedPageItem = GetBookPageItem(llBook);
	//llPageGroupData* SavedPageGroup = GetBookPageGroup(llBook);
	//llPageData* SavedPage = GetBookPage(llBook);

	//Nothing in PageGroup
	llPageData* SavedPage = llBook->Page;
	llPageGroupData* SavedPageGroup = llBook->Page->PageGroup;
	llPageItemData* SavedPageItem = llBook->Page->PageGroup->PageItem;
	llShapeGroupData* SavedShapeGroup = llBook->Page->PageGroup->PageItem->ShapeGroup;
	llShapeData* SavedShape = llBook->Page->PageGroup->PageItem->ShapeGroup->Shape;
	llVertexData* SavedVertex = llBook->Page->PageGroup->PageItem->ShapeGroup->Shape->Vertexx;

	//Page
	llPageData* CurrentPage = SavedPage;

	//CurrentPage = HeadPage(CurrentPage);

	BookDirectory.Page = CurrentPage;

	while (CurrentPage != nullptr && CurrentPage->PageGroup != nullptr)
	{
		PageCount++;
		//Page Group
		llPageGroupData* CurrentPageGroup = CurrentPage->PageGroup;

		//Set PageGroup Beginning
		/////////////////////////////////////////////////////
		while (CurrentPageGroup->Previous != nullptr)
		{
			CurrentPageGroup = CurrentPageGroup->Previous;
		
		}
		/////////////////////////////////////////////////////
		while (CurrentPageGroup != nullptr && CurrentPageGroup->PageItem != nullptr)
		{
			//if (ElementLevel == LEVEL_PAGEITEM)
			//{
				if (xMouse < CurrentPageGroup->Right && xMouse >  CurrentPageGroup->Left && yMouse < CurrentPageGroup->Top && yMouse >  CurrentPageGroup->Bottom && CurrentPageGroup->MouseAccess == true)
				{
					//cout << " [PageGroup Found] | P:" << PageCount << " | PG:" << PageGroupCount << endl;
					BookDirectory.PageGroup = CurrentPageGroup;
					BookDirectory.NoDirectoryFound = false;
				}
			//}

			PageGroupCount++;
			//PageItem
			llPageItemData* CurrentPageItem = CurrentPageGroup->PageItem;
			//Set PageItem Beginning
			/////////////////////////////////////////////////////
			while (CurrentPageItem->Previous != nullptr)
			{
				CurrentPageItem = CurrentPageItem->Previous;
			}
			/////////////////////////////////////////////////////
			while (CurrentPageItem != nullptr && CurrentPageItem->ShapeGroup != nullptr)
			{
				//if (ElementLevel == LEVEL_PAGEITEM)
				//{
					if (xMouse < CurrentPageItem->Right && xMouse >  CurrentPageItem->Left&& yMouse < CurrentPageItem->Top && yMouse >  CurrentPageItem->Bottom && CurrentPageItem->MouseAccess == true)
					{
						//cout << " [PageItem Found] | P:" << PageCount << " | PG:" << PageGroupCount << " | PI:" << PageItemCount << endl;
						BookDirectory.PageItem = CurrentPageItem;
						BookDirectory.NoDirectoryFound = false;

						if (CurrentPageItem->PageItemButton != nullptr)
						{
							CurrentPageItem->PageItemButton->ProcessMouseButtons(MouseManager::CurrentMouseState);
						}
					}
				//}

				PageItemCount++;
				//ShapeGroup
				llShapeGroupData* CurrentShapeGroup = CurrentPageItem->ShapeGroup;
				//Set ShapeGroup to beginning
				/////////////////////////////////////////////////////
				while (CurrentShapeGroup->Previous != nullptr)
				{
					CurrentShapeGroup = CurrentShapeGroup->Previous;

				}
			
				/////////////////////////////////////////////////////
				while (CurrentShapeGroup != nullptr)
				{
					ShapeGroupCount++;
					//Shape
					llShapeData* CurrentShape = CurrentShapeGroup->Shape;
					if (CurrentShapeGroup->Shape != nullptr)
					{

						if (xMouse < CurrentShapeGroup->Right && xMouse >  CurrentShapeGroup->Left&& yMouse < CurrentShapeGroup->Top && yMouse >  CurrentShapeGroup->Bottom && CurrentShapeGroup->MouseAccess == true)
						{
							//if (ElementLevel == LEVEL_SHAPEGROUP)
							//{
								//cout << "[ShapeGroup Found] |P:" << PageCount << " | PG:" << PageGroupCount << " | PI:" << PageItemCount << " | SG:" << ShapeGroupCount << endl;
								BookDirectory.ShapeGroup = CurrentShapeGroup;
								BookDirectory.NoDirectoryFound = false;
								if (CurrentShapeGroup->ShapeGroupButton != nullptr)
								{
									CurrentShapeGroup->ShapeGroupButton->ProcessMouseButtons(MouseManager::CurrentMouseState);
								}
							//}
						}
						//Set shape to beginning
						/////////////////////////////////////////////////////
						while (CurrentShape->Previous != nullptr)
						{
							CurrentShape = CurrentShape->Previous;
						}
						/////////////////////////////////////////////////////
						while (CurrentShape != nullptr && CurrentShape->Vertexx != nullptr)
						{
							ShapeCount++;
							if (xMouse < CurrentShape->Right && xMouse >  CurrentShape->Left && yMouse < CurrentShape->Top && yMouse >  CurrentShape->Bottom && CurrentShape->MouseAccess == true)
							{
								BookDirectory.Shape;
								BookDirectory.NoDirectoryFound = false;
									
								if (CurrentShape->ShapeButton != nullptr)
								{
									//cout << "[Shape Found] | P:" << PageCount << " | PG:" << PageGroupCount << " | PI:" << PageItemCount << " | SG:" << ShapeGroupCount << " | S:" << ShapeCount << " | Char: " << char(CurrentShape->Ascii) << endl;
									CurrentShape->ShapeButton->ProcessMouseButtons(MouseManager::CurrentMouseState);
									
								}
								
							}
							CurrentShape = CurrentShape->Next;
						}
					}
					ShapeCount = -1;
					CurrentShapeGroup = CurrentShapeGroup->Next;
				}
				ShapeGroupCount = -1;
				CurrentPageItem = CurrentPageItem->Next;
			}
			PageItemCount = -1;
			CurrentPageGroup = CurrentPageGroup->Next;
		}
		PageGroupCount = -1;
		CurrentPage = CurrentPage->Next;
	}

	if (llBook != nullptr)
	{
		llBook->Page = SavedPage;
		if (llBook->Page != nullptr)
		{
			llBook->Page->PageGroup = SavedPageGroup;
			if (llBook->Page->PageGroup != nullptr)
			{
				llBook->Page->PageGroup->PageItem = SavedPageItem;
				if (llBook->Page->PageGroup->PageItem != nullptr)
				{
					llBook->Page->PageGroup->PageItem->ShapeGroup = SavedShapeGroup;
					if (llBook->Page->PageGroup->PageItem->ShapeGroup != nullptr)
					{
						llBook->Page->PageGroup->PageItem->ShapeGroup->Shape = SavedShape;
						if (llBook->Page->PageGroup->PageItem->ShapeGroup->Shape != nullptr)
						{
							llBook->Page->PageGroup->PageItem->ShapeGroup->Shape->Vertexx = SavedVertex;
						}
					}
				}
			}
		}
	}

}

void MasterElement::PrintBook(llBookData* llBook)
{

}

 llVertexData* MasterElement::GetBookVertex(llBookData* llBook)
{
	 if (llBook == nullptr) {return nullptr; } // Log::LogString("ERROR:: GetBookVertex FAILED:: No Book Provided");           
	 if (llBook->Page == nullptr) { return nullptr; } // Log::LogString("ERROR:: GetBookVertex FAILED:: No Page in Book");            
	 if (llBook->Page->PageGroup == nullptr) { return nullptr; } // Log::LogString("ERROR:: GetBookVertex FAILED:: No PageGroup in Page");       
	 if (llBook->Page->PageGroup->PageItem->ShapeGroup == nullptr) { return nullptr; } // Log::LogString("ERROR:: GetBookVertex FAILED:: No ShapeGroup in PageItem");  
	 if (llBook->Page->PageGroup->PageItem->ShapeGroup->Shape == nullptr) { return nullptr; } // Log::LogString("ERROR:: GetBookVertex FAILED:: No Shape in ShapeGroup");     

	 return llBook->Page->PageGroup->PageItem->ShapeGroup->Shape->Vertexx;
}

 llShapeData* MasterElement::GetBookShape(llBookData* llBook)
{
	 if (llBook == nullptr) { return nullptr; } // Log::LogString("ERROR:: GetBookVertex FAILED:: No Book Provided");           
	 if (llBook->Page == nullptr) { return nullptr; } // Log::LogString("ERROR:: GetBookVertex FAILED:: No Page in Book");            
	 if (llBook->Page->PageGroup == nullptr) { return nullptr; } // Log::LogString("ERROR:: GetBookVertex FAILED:: No PageGroup in Page");       
	 if (llBook->Page->PageGroup->PageItem->ShapeGroup == nullptr) { return nullptr; } // Log::LogString("ERROR:: GetBookVertex FAILED:: No ShapeGroup in PageItem");  

	 return llBook->Page->PageGroup->PageItem->ShapeGroup->Shape;
}

 llShapeGroupData* MasterElement::GetBookShapeGroup(llBookData* llBook)
{
	 if (llBook == nullptr) { return nullptr; } // Log::LogString("ERROR:: GetBookVertex FAILED:: No Book Provided");           
	 if (llBook->Page == nullptr) { return nullptr; } // Log::LogString("ERROR:: GetBookVertex FAILED:: No Page in Book");            
	 if (llBook->Page->PageGroup == nullptr) { return nullptr; } // Log::LogString("ERROR:: GetBookVertex FAILED:: No PageGroup in Page");       
	 if (llBook->Page->PageGroup->PageItem->ShapeGroup == nullptr) { return nullptr; } // Log::LogString("ERROR:: GetBookVertex FAILED:: No ShapeGroup in PageItem");  

	 return llBook->Page->PageGroup->PageItem->ShapeGroup;
}

 llPageItemData* MasterElement::GetBookPageItem(llBookData* llBook)
{
	 if (llBook == nullptr) { Log::LogString("ERROR:: GetBookVertex FAILED:: No Book Provided"); return nullptr; } //            
	 if (llBook->Page == nullptr) {  Log::LogString("ERROR:: GetBookVertex FAILED:: No Page in Book");return nullptr; }             
	 if (llBook->Page->PageGroup == nullptr) { Log::LogString("ERROR:: GetBookVertex FAILED:: No PageGroup in Page");  return nullptr; } // Log::LogString("ERROR:: GetBookVertex FAILED:: No PageGroup in Page");       

	 return llBook->Page->PageGroup->PageItem;
}

 llPageGroupData* MasterElement::GetBookPageGroup(llBookData* llBook)
{
	 if (llBook == nullptr) { return nullptr; } // Log::LogString("ERROR:: GetBookVertex FAILED:: No Book Provided");           
	 if (llBook->Page == nullptr) { return nullptr; } // Log::LogString("ERROR:: GetBookVertex FAILED:: No Page in Book");            

	 return llBook->Page->PageGroup;
}

 llPageData* MasterElement::GetBookPage(llBookData* llBook)
{
	 if (llBook == nullptr) { return nullptr; }
	 return llBook->Page;
}


llVertexData* MasterElement::HeadVertex(llVertexData* VertexReference)
{
	//Already Head or Invalid
	if (VertexReference->Previous == nullptr) { return VertexReference; }
	if (VertexReference == nullptr) { Log::LogString("ERROR:: HeadVertex FAILED:: No Vertex Provided");  return nullptr; }

	//Setup
	llVertexData* VertexHead = VertexReference;

	//Get Head
	while (VertexHead->Previous != nullptr) { VertexHead = VertexHead->Previous; }

	return VertexHead;
}
llShapeData* MasterElement::HeadShape(llShapeData* ShapeReference)
{
	//Already Head or Invalid
	if (ShapeReference->Previous == nullptr) { return ShapeReference; }
	if (ShapeReference == nullptr) { Log::LogString("ERROR:: HeadShape FAILED:: No Shape Provided");  return nullptr; }

	//Setup
	llShapeData* ShapeHead = ShapeReference;

	//Get Head
	while (ShapeHead->Previous != nullptr) { ShapeHead = ShapeHead->Previous; }

	return ShapeHead;
}
llShapeGroupData* MasterElement::HeadShapeGroup(llShapeGroupData* ShapeGroupReference)
{
	//Already Head or Invalid
	if (ShapeGroupReference->Previous == nullptr) { return ShapeGroupReference; }
	if (ShapeGroupReference == nullptr) { Log::LogString("ERROR:: HeadShapeGroup FAILED:: No ShapeGroup Provided");  return nullptr; }

	//Setup
	llShapeGroupData* ShapeGroupHead = ShapeGroupReference;

	//Get Head
	while (ShapeGroupHead->Previous != nullptr) { ShapeGroupHead = ShapeGroupHead->Previous; }

	return ShapeGroupHead;
}
llPageItemData* MasterElement::HeadPageItem(llPageItemData* PageItemReference)
{
	//Already Head or Invalid
	if (PageItemReference->Previous == nullptr) { return PageItemReference; }
	if (PageItemReference == nullptr) { Log::LogString("ERROR:: HeadPageItem FAILED:: No PageItem Provided");  return nullptr; }

	//Setup
	llPageItemData* PageItemHead = PageItemReference;

	//Get Head
	while (PageItemHead->Previous != nullptr) { PageItemHead = PageItemHead->Previous; }

	return PageItemHead;
}
llPageGroupData* MasterElement::HeadPageGroup(llPageGroupData* PageGroupReference)
{
	//Already Head or Invalid
	if (PageGroupReference->Previous == nullptr) { return PageGroupReference; }
	if (PageGroupReference == nullptr) { Log::LogString("ERROR:: HeadPageGroup FAILED:: No PageGroup Provided");  return nullptr; }

	//Setup
	llPageGroupData* PageGroupHead = PageGroupReference;

	//Get Head
	while (PageGroupHead->Previous != nullptr) { PageGroupHead = PageGroupHead->Previous; }

	return PageGroupHead;
}
llPageData* MasterElement::HeadPage(llPageData* PageReference)
{
	//Already Head or Invalid
	if (PageReference->Previous == nullptr) { return PageReference; }
	if (PageReference == nullptr) { Log::LogString("ERROR:: HeadPage FAILED:: No Page Provided");  return nullptr; }

	//Setup
	llPageData* PageHead = PageReference;

	//Get Head
	while (PageHead->Previous != nullptr) { PageHead = PageHead->Previous; }

	return PageHead;
}

void MasterElement::NextPage(llBookData* llBook)
{
	//Book to PageItem Valid?
	if (llBook == nullptr) { Log::LogString("ERROR:: NextShape Failed:: book was nullptr");  return; };
	if (llBook->Page == nullptr) { Log::LogString("WARNING:: NextShape:: No Page");  return; }
	if (llBook->Page->Next == nullptr) { Log::LogString("Page Tail");  return; }

	//Next Page 
	llBook->Page = llBook->Page->Next;
}

void MasterElement::PreviousPage(llBookData* llBook)
{
	//Book to PageItem Valid?
	if (llBook == nullptr) { Log::LogString("ERROR:: NextShape Failed:: book was nullptr");  return; };
	if (llBook->Page == nullptr) { Log::LogString("WARNING:: NextShape:: No Page");  return; }
	if (llBook->Page->Previous == nullptr) { Log::LogString("Page Head");  return; }

	//Next Page 
	llBook->Page = llBook->Page->Previous;

}

//PageGroup
void MasterElement::NextPageGroup(llBookData* llBook)
{
	//Book to PageItem Valid?
	if (llBook == nullptr) { Log::LogString("ERROR:: NextShape Failed:: book was nullptr");  return; };
	if (llBook->Page == nullptr) { Log::LogString("WARNING:: NextShape:: No Page");  return; }
	if (llBook->Page->PageGroup == nullptr) { Log::LogString("WARNING:: NextShape:: No PageGroup");  return; }
	if (llBook->Page->PageGroup->Next == nullptr) { Log::LogString("PageGroup Tail");  return; }

	//Next Page Group
	llBook->Page->PageGroup = llBook->Page->PageGroup->Next;

}

void MasterElement::PreviousPageGroup(llBookData* llBook)
{
	//Book to PageItem Valid?
	if (llBook == nullptr) { Log::LogString("ERROR:: NextShape Failed:: book was nullptr");  return; };
	if (llBook->Page == nullptr) { Log::LogString("WARNING:: NextShape:: No Page");  return; }
	if (llBook->Page->PageGroup == nullptr) { Log::LogString("WARNING:: NextShape:: No PageGroup");  return; }
	if (llBook->Page->PageGroup->Previous== nullptr) { Log::LogString("PageGroup Head");  return; }

	//Next Page Group
	llBook->Page->PageGroup = llBook->Page->PageGroup->Previous;

}

//PageItem
void MasterElement::NextPageItem(llBookData* llBook)
{
	//Book to PageItem Valid?
	if (llBook == nullptr) { Log::LogString("ERROR:: NextShape Failed:: book was nullptr");  return; };
	if (llBook->Page == nullptr) { Log::LogString("WARNING:: NextShape:: No Page");  return; }
	if (llBook->Page->PageGroup == nullptr) { Log::LogString("WARNING:: NextShape:: No PageGroup");  return; }
	if (llBook->Page->PageGroup->PageItem == nullptr) { Log::LogString("WARNING:: NextShape:: No PageItem");  return; }
	if (llBook->Page->PageGroup->PageItem->Next == nullptr) { Log::LogString("PageItem Tail");  return; }

	//Next Page Item
	llBook->Page->PageGroup->PageItem = llBook->Page->PageGroup->PageItem->Next;

}

void MasterElement::PreviousPageItem(llBookData* llBook)
{
	//Book to PageItem Valid?
	if (llBook == nullptr) { Log::LogString("ERROR:: NextShape Failed:: book was nullptr");  return; };
	if (llBook->Page == nullptr) { Log::LogString("WARNING:: NextShape:: No Page");  return; }
	if (llBook->Page->PageGroup == nullptr) { Log::LogString("WARNING:: NextShape:: No PageGroup");  return; }
	if (llBook->Page->PageGroup->PageItem == nullptr) { Log::LogString("WARNING:: NextShape:: No PageItem");  return; }
	if (llBook->Page->PageGroup->PageItem->Previous == nullptr) { Log::LogString("PageItem Head");  return; }

	//Previous Page Item
	llBook->Page->PageGroup->PageItem = llBook->Page->PageGroup->PageItem->Previous;

}

//ShapeGroup
void MasterElement::NextShapeGroup(llBookData* llBook)
{
	//Book to Shape Valid?
	if (llBook == nullptr) { Log::LogString("ERROR:: NextShape Failed:: book was nullptr");  return; };
	if (llBook->Page == nullptr) { Log::LogString("WARNING:: NextShape:: No Page");  return; }
	if (llBook->Page->PageGroup == nullptr) { Log::LogString("WARNING:: NextShape:: No PageGroup");  return; }
	if (llBook->Page->PageGroup->PageItem == nullptr) { Log::LogString("WARNING:: NextShape:: No PageItem");  return; }
	if (llBook->Page->PageGroup->PageItem->ShapeGroup == nullptr) { Log::LogString("WARNING:: NextShape:: No ShapeGroup");  return; }
	if (llBook->Page->PageGroup->PageItem->ShapeGroup->Next == nullptr) { Log::LogString("Shape Group Tail");  return; }

	//Previous Shape Group
	llBook->Page->PageGroup->PageItem->ShapeGroup = llBook->Page->PageGroup->PageItem->ShapeGroup->Next;

}

void MasterElement::PreviousShapeGroup(llBookData* llBook)
{
	//Book to Shape Valid?
	if (llBook == nullptr) { Log::LogString("ERROR:: NextShape Failed:: book was nullptr");  return; };
	if (llBook->Page == nullptr) { Log::LogString("WARNING:: NextShape:: No Page");  return; }
	if (llBook->Page->PageGroup == nullptr) { Log::LogString("WARNING:: NextShape:: No PageGroup");  return; }
	if (llBook->Page->PageGroup->PageItem == nullptr) { Log::LogString("WARNING:: NextShape:: No PageItem");  return; }
	if (llBook->Page->PageGroup->PageItem->ShapeGroup == nullptr) { Log::LogString("WARNING:: NextShape:: No ShapeGroup");  return; }
	if (llBook->Page->PageGroup->PageItem->ShapeGroup->Previous == nullptr) { Log::LogString("Shape Group Head");  return; }

	//Previous Shape Group
	llBook->Page->PageGroup->PageItem->ShapeGroup = llBook->Page->PageGroup->PageItem->ShapeGroup->Previous;

}

void MasterElement::NextShape(llBookData* llBook)
{
	//Book to Shape Valid?
	if (llBook == nullptr) { Log::LogString("ERROR:: NextShape Failed:: book was nullptr");  return; };
	if (llBook->Page == nullptr) { Log::LogString("WARNING:: NextShape:: No Page");  return; }
	if (llBook->Page->PageGroup == nullptr) { Log::LogString("WARNING:: NextShape:: No PageGroup");  return; }
	if (llBook->Page->PageGroup->PageItem == nullptr) { Log::LogString("WARNING:: NextShape:: No PageItem");  return; }
	if (llBook->Page->PageGroup->PageItem->ShapeGroup == nullptr) { Log::LogString("WARNING:: NextShape:: No ShapeGroup");  return; }
	if (llBook->Page->PageGroup->PageItem->ShapeGroup->Shape == nullptr) { Log::LogString("WARNING:: NextShape:: No Shape");  return; }
	if (llBook->Page->PageGroup->PageItem->ShapeGroup->Shape->Next == nullptr) { Log::LogString("Shape Tail");  return; }

	//Switch to Next Shape
	llBook->Page->PageGroup->PageItem->ShapeGroup->Shape = llBook->Page->PageGroup->PageItem->ShapeGroup->Shape->Next;
}

void MasterElement::PreviousShape(llBookData* llBook)
{
	//Book to Shape Valid?
	if (llBook == nullptr) { Log::LogString("ERROR:: NextShape Failed:: book was nullptr");  return; };
	if (llBook->Page == nullptr) { Log::LogString("WARNING:: NextShape:: No Page");  return; }
	if (llBook->Page->PageGroup == nullptr) { Log::LogString("WARNING:: NextShape:: No PageGroup");  return; }
	if (llBook->Page->PageGroup->PageItem == nullptr) { Log::LogString("WARNING:: NextShape:: No PageItem");  return; }
	if (llBook->Page->PageGroup->PageItem->ShapeGroup == nullptr) { Log::LogString("WARNING:: NextShape:: No ShapeGroup");  return; }
	if (llBook->Page->PageGroup->PageItem->ShapeGroup->Shape == nullptr) { Log::LogString("WARNING:: NextShape:: No Shape");  return; }
	if (llBook->Page->PageGroup->PageItem->ShapeGroup->Shape->Previous == nullptr) { Log::LogString("Shape Head");  return; }

	//Switch to Previous Shape
	llBook->Page->PageGroup->PageItem->ShapeGroup->Shape = llBook->Page->PageGroup->PageItem->ShapeGroup->Shape->Previous;

}

void MasterElement::CurrentDirectory(llBookData* llBook)
{
	if (llBook != nullptr)
	{
		//Reset Counts
		int VertexIndex = 0;
		int PageCount = 0;
		int PageGroupCount = 0;
		int PageItemCount = 0;
		int ShapeGroupCount = 0;
		int ShapeCount = 0;
		int VertexCount = 0;

		llPageData*       SavedPage       = nullptr;
		llPageGroupData * SavedPageGroup  = nullptr;
		llPageItemData*   SavedPageItem   = nullptr;
		llShapeGroupData* SavedShapeGroup = nullptr;
		llShapeData*      SavedShape	  = nullptr;
		llVertexData*     SavedVertex	  = nullptr;

		llPageData* CurrentPage = nullptr;
		llPageGroupData* CurrentPageGroup = nullptr;
		llPageItemData* CurrentPageItem = nullptr;
		llShapeGroupData* CurrentShapeGroup = nullptr;
		llShapeData* CurrentShape = nullptr;
		llVertexData* CurrentVertex = nullptr;

		//Save CurrentDirectory
		//Page
		if (llBook->Page != nullptr)
		{
			SavedPage = llBook->Page;
			CurrentPage = llBook->Page;
			//Page Group
			if (llBook->Page->PageGroup != nullptr)
			{
				SavedPageGroup = llBook->Page->PageGroup;
				CurrentPageGroup = CurrentPage->PageGroup;
				//PageItem
				if (llBook->Page->PageGroup->PageItem != nullptr)
				{
					SavedPageItem = llBook->Page->PageGroup->PageItem;
					CurrentPageItem = CurrentPageGroup->PageItem;
					//ShapeGroup
					if (llBook->Page->PageGroup->PageItem->ShapeGroup != nullptr)
					{
						SavedShapeGroup = llBook->Page->PageGroup->PageItem->ShapeGroup;
						CurrentShapeGroup = CurrentPageItem->ShapeGroup;
						//Shape
						if (llBook->Page->PageGroup->PageItem->ShapeGroup->Shape != nullptr)
						{
							SavedShape = llBook->Page->PageGroup->PageItem->ShapeGroup->Shape;
							CurrentShape = CurrentShapeGroup->Shape;
							//Vertex
							if (llBook->Page->PageGroup->PageItem->ShapeGroup->Shape->Vertexx != nullptr)
							{
								SavedVertex = llBook->Page->PageGroup->PageItem->ShapeGroup->Shape->Vertexx;
							}
						}
					}
				}
			}
		}

		//Page
		if (CurrentPage != nullptr)
		{
			//Set to beginning
			while (CurrentPage->Previous != nullptr)
			{
				CurrentPage = CurrentPage->Previous;
			}

			while (CurrentPage->Next != nullptr && CurrentPage != SavedPage)
			{
				CurrentPage = CurrentPage->Next;
				PageCount++;
			}
		}
		else
		{
			PageCount = -1;
		}
		//////////////////////////|^ Page ^|/////////////////////////

		if (CurrentPageGroup != nullptr)
		{
			//Set to beginning
			while (CurrentPageGroup->Previous != nullptr)
			{
				CurrentPageGroup = CurrentPageGroup->Previous;
			}

			while (CurrentPageGroup->Next != nullptr && CurrentPageGroup != SavedPageGroup)
			{
				CurrentPageGroup = CurrentPageGroup->Next;
				PageGroupCount++;
			}
		}
		else
		{
			PageGroupCount = -1;
		}
		/////////////////////////|^ PageGroup ^|\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

		if (CurrentPageItem != nullptr)
		{
			//Set to beginning
			while (CurrentPageItem->Previous != nullptr)
			{
				CurrentPageItem = CurrentPageItem->Previous;
			}

			while (CurrentPageItem->Next != nullptr && CurrentPageItem != SavedPageItem)
			{
				CurrentPageItem = CurrentPageItem->Next;
				PageItemCount++;
			}
		}
		else
		{
			PageItemCount = -1;
		}
		/////////////////////////|^ PageItem ^|\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

		if (CurrentShapeGroup != nullptr)
		{
			//Set to beginning
			while (CurrentShapeGroup->Previous != nullptr)
			{
				CurrentShapeGroup = CurrentShapeGroup->Previous;
			}

			while (CurrentShapeGroup->Next != nullptr && CurrentShapeGroup != SavedShapeGroup)
			{
				CurrentShapeGroup = CurrentShapeGroup->Next;
				ShapeGroupCount++;
			}
		}
		else
		{
			ShapeGroupCount = -1;
		}
		/////////////////////////|^ ShapeGroup ^|\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

		if (CurrentShape != nullptr)
		{
			//Set to beginning
			while (CurrentShape->Previous != nullptr)
			{
				CurrentShape = CurrentShape->Previous;
			}

			while (CurrentShape->Next != nullptr && CurrentShape != SavedShape)
			{
				CurrentShape = CurrentShape->Next;
				ShapeCount++;
			}
		}
		else
		{
			ShapeCount = -1;
		}
		/////////////////////////|^ ShapeGroup ^|\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

		cout << "[Current Directory] | P:" << PageCount << " | PG:" << PageGroupCount << " | PI:" << PageItemCount << " | SG:" << ShapeGroupCount << " | S:" << ShapeCount << " | Char: " << CurrentShape << endl;
	
	}
	else
	{
		Log::LogString("ERROR:: Cannot Print Book Directory:: book was nullptr");
	}

}


llShapeData* MasterElement::AddShape(llBookData* Book)
{
	//Validate
	if (Book == nullptr) { Log::LogString("ERROR:: Add EmptyShape FAILED:: No Book Provided"); return nullptr; }

	//Setup
	llShapeData* NewShape = nullptr;
	llVertexData* VertexTopRight = nullptr;
	llVertexData* VertexTopLeft = nullptr;
	llVertexData* VertexBottomRight = nullptr;
	llVertexData* VertexBottomLeft = nullptr;

	//Add Neccesary Groups if not already Created
	if (Book->Page == nullptr)
	{
		Log::LogString("Book Is Brand New");
		llPageData* CreatedPage = new llPageData;
		llPageGroupData* CreatedPageGroup = new llPageGroupData;
		llPageItemData* CreatedPageItem = new llPageItemData;
		llShapeGroupData* CreatedShapeGroup = new llShapeGroupData;

		Book->Page = CreatedPage;
		Book->PageHead = CreatedPage;

		Book->Page->PageGroup = CreatedPageGroup;
		Book->Page->PageGroupHead = CreatedPageGroup;

		Book->Page->PageGroup->PageItem = CreatedPageItem;
		Book->Page->PageGroup->PageItemHead = CreatedPageItem;

		Book->Page->PageGroup->PageItem->ShapeGroup = CreatedShapeGroup;
		Book->Page->PageGroup->PageItem->ShapeGroupHead = CreatedShapeGroup;
	}

	//Add Neccesary Groups if not already Created
	if (Book->Page->PageGroup == nullptr)
	{
		llPageGroupData* CreatedPageGroup = new llPageGroupData;
		llPageItemData* CreatedPageItem = new llPageItemData;
		llShapeGroupData* CreatedShapeGroup = new llShapeGroupData;

		Book->Page->PageGroup = CreatedPageGroup;
		Book->Page->PageGroupHead = CreatedPageGroup;

		Book->Page->PageGroup->PageItem = CreatedPageItem;
		Book->Page->PageGroup->PageItemHead = CreatedPageItem;

		Book->Page->PageGroup->PageItem->ShapeGroup = CreatedShapeGroup;
		Book->Page->PageGroup->PageItem->ShapeGroupHead = CreatedShapeGroup;
	}

	//Add Neccesary Groups if not already Created
	if (Book->Page->PageGroup->PageItem == nullptr)
	{
		llPageItemData* CreatedPageItem = new llPageItemData;
		llShapeGroupData* CreatedShapeGroup = new llShapeGroupData;

		Book->Page->PageGroup->PageItem = CreatedPageItem;
		Book->Page->PageGroup->PageItemHead = CreatedPageItem;

		Book->Page->PageGroup->PageItem->ShapeGroup = CreatedShapeGroup;
		Book->Page->PageGroup->PageItem->ShapeGroupHead = CreatedShapeGroup;
	}

	//Add Neccesary Groups if not already Created
	if (Book->Page->PageGroup->PageItem->ShapeGroup == nullptr)
	{
		llShapeGroupData* CreatedShapeGroup = new llShapeGroupData;

		Book->Page->PageGroup->PageItem->ShapeGroup = CreatedShapeGroup;
		Book->Page->PageGroup->PageItem->ShapeGroupHead = CreatedShapeGroup;
	}

	//Create Vertices
	VertexTopRight = new llVertexData;
	VertexTopLeft = new llVertexData;
	VertexBottomRight = new llVertexData;
	VertexBottomLeft = new llVertexData;

	//Create Shape
	NewShape = new llShapeData;

	//Link Vertices together and to Shape
	VertexTopLeft->Next = VertexTopRight;
	VertexTopRight->Next = VertexBottomRight;
	VertexBottomRight->Next = VertexBottomLeft;
	VertexBottomLeft->Previous = VertexBottomRight;
	VertexBottomRight->Previous = VertexTopRight;
	VertexTopRight->Previous = VertexTopLeft;
	NewShape->Vertexx = VertexTopLeft;

	//Get the Current Shape in Current ShapeGroup
	llShapeData* TestingShape = Book->Page->PageGroup->PageItem->ShapeGroup->Shape;

	//No Shapes in ShapeGroup
	if (TestingShape == nullptr)
	{
		//First Shape!
		//Log::LogChar("New Shape Linked", char(NewShape->Ascii));
		Book->Page->PageGroup->PageItem->ShapeGroup->Shape = NewShape;
		Book->Page->PageGroup->PageItem->ShapeGroup->ShapeHead = NewShape;
	}
	//Existing Shapes in ShapeGroup
	else 
	{
		//Go to Shape Tail	
		while (TestingShape->Next != nullptr) {TestingShape = TestingShape->Next;}

		//Link Shape to list 
		//Log::LogChar("New Shape Linked", char(TestingShape->Ascii));
		TestingShape->Next = NewShape;
		NewShape->Previous = TestingShape;

		//Current Shape Group points to the new Shape
		Book->Page->PageGroup->PageItem->ShapeGroup->Shape = NewShape;
		Book->Page->PageGroup->PageItem->ShapeGroup->ShapeHead = NewShape;
	}

	//Set as Default Shape Type
	NewShape->Type = TYPE_SHAPE;
	Book->Page->PageGroup->PageItem->ShapeGroup->ShapeCount++;
	return NewShape;
}

llShapeGroupData* MasterElement::AddShapeGroup(llBookData* Book)
{

	//Validate
	if (Book == nullptr) { Log::LogString("ERROR:: Add EmptyShape FAILED:: No Book Provided"); return nullptr; }

	//Setup
	llShapeGroupData* NewShapeGroup = nullptr;

	//Create Groups if none
	if (Book->Page == nullptr)
	{
		Log::LogString("Book Is Brand New");
		llPageData* CreatedPage = new llPageData;
		llPageGroupData* CreatedPageGroup = new llPageGroupData;
		llPageItemData* CreatedPageItem = new llPageItemData;

		Book->Page = CreatedPage;
		Book->PageHead = CreatedPage;

		Book->Page->PageGroup = CreatedPageGroup;
		Book->Page->PageGroupHead = CreatedPageGroup;

		Book->Page->PageGroup->PageItem = CreatedPageItem;
		Book->Page->PageGroup->PageItemHead = CreatedPageItem;
	}

	if (Book->Page->PageGroup == nullptr)
	{
		llPageGroupData* CreatedPageGroup = new llPageGroupData;
		llPageItemData* CreatedPageItem = new llPageItemData;

		Book->Page->PageGroup = CreatedPageGroup;
		Book->Page->PageGroupHead = CreatedPageGroup;

		Book->Page->PageGroup->PageItem = CreatedPageItem;
		Book->Page->PageGroup->PageItemHead = CreatedPageItem;

	}

	if (Book->Page->PageGroup->PageItem == nullptr)
	{
		llPageItemData* CreatedPageItem = new llPageItemData;

		Book->Page->PageGroup->PageItem = CreatedPageItem;
		Book->Page->PageGroup->PageItemHead = CreatedPageItem;
	}

	//Create ShapeGroup
	NewShapeGroup = new llShapeGroupData;

	//Get Current ShapeGroup in PageItem
	llShapeGroupData* TestingShapeGroup = Book->Page->PageGroup->PageItem->ShapeGroup;

	//No ShapeGroups in current PageItem
	if (TestingShapeGroup == nullptr)
	{
		//First ShapeGroup!
		//Log::LogString("New ShapeGroup Linked");
		Book->Page->PageGroup->PageItem->ShapeGroup = NewShapeGroup;
		Book->Page->PageGroup->PageItem->ShapeGroupHead = NewShapeGroup;
	}
	//ShapeGroups exist in current PageItem
	else 
	{
		//Get ShapeGroup Tail
		while (TestingShapeGroup->Next != nullptr)
		{
			TestingShapeGroup = TestingShapeGroup->Next;
		}

		//Link New ShapeGroup to Tail
		//Log::LogString("New ShapeGroup Linked");
		TestingShapeGroup->Next = NewShapeGroup;
		NewShapeGroup->Previous = TestingShapeGroup;

		//CurrentPageItem Points to New ShapeGroup
		Book->Page->PageGroup->PageItem->ShapeGroup = NewShapeGroup;
	}

	//Set As Default Shape Type
	Book->Page->PageGroup->PageItem->ShapeGroupCount++;
	NewShapeGroup->Type = TYPE_SHAPEGROUP;
	return NewShapeGroup;
}

llPageItemData* MasterElement::AddPageItem(llBookData* Book)
{
	//Validate
	if (Book == nullptr) { Log::LogString("ERROR:: Add EmptyShape FAILED:: No Book Provided"); return nullptr; }

	llPageItemData* NewPageItem = nullptr;

	if (Book->Page == nullptr)
	{
		Log::LogString("Book Is Brand New");
		llPageData* CreatedPage = new llPageData;
		llPageGroupData* CreatedPageGroup = new llPageGroupData;

		Book->Page = CreatedPage;
		Book->PageHead = CreatedPage;

		Book->Page->PageGroup = CreatedPageGroup;
		Book->Page->PageGroupHead = CreatedPageGroup;
	}

	if (Book->Page->PageGroup == nullptr)
	{
		Log::LogString("Book Is Brand New");
		llPageGroupData* CreatedPageGroup = new llPageGroupData;

		Book->Page->PageGroup = CreatedPageGroup;
		Book->Page->PageGroupHead = CreatedPageGroup;
	}

    NewPageItem = new llPageItemData;

	llPageItemData* TestingPageItem = Book->Page->PageGroup->PageItem;

	//No PageItem's in PageGroup
	if (TestingPageItem == nullptr)
	{
		//First PageGroup!
		Log::LogString("New PageItem Linked");
		Book->Page->PageGroup->PageItemHead = NewPageItem;
	}
	// PageItems exist in PageGroup
	else 
	{
		//Go to PageItem Tail
		while (TestingPageItem->Next != nullptr)
		{
			TestingPageItem = TestingPageItem->Next;
		}

		//Add PageItem to Tail
		Log::LogString("New PageItem Linked");
		TestingPageItem->Next = NewPageItem;
		NewPageItem->Previous = TestingPageItem;

		//Currenta PageGroup points to New PageItem
		Book->Page->PageGroup->PageItem = NewPageItem;
	}

	Book->Page->PageGroup->PageItemCount++;
	NewPageItem->Type = TYPE_PAGEITEM;
	return NewPageItem;
}

llPageGroupData* MasterElement::AddPageGroup(llBookData* Book)
{
	//Validate
	if (Book == nullptr) { Log::LogString("ERROR:: Add EmptyShape FAILED:: No Book Provided"); return nullptr; }

	//Setup
	llPageGroupData* NewPageGroup = nullptr;

	//Create a Page if none exists
	if (Book->Page == nullptr)
	{
		Log::LogString("Book Is Brand New");
		llPageData* CreatedPage = new llPageData;
		llPageGroupData* CreatedPageGroup = new llPageGroupData;

		Book->Page = CreatedPage;
		Book->PageHead = CreatedPage;

		Book->Page->PageGroup = CreatedPageGroup;
		Book->Page->PageGroupHead = CreatedPageGroup;
	}

	//Create New PageGroup
	NewPageGroup = new llPageGroupData;

	//Get Current Page Group
	llPageGroupData* CurrentPageGroup = Book->Page->PageGroup;

	//No PageGroups in Page
	if (CurrentPageGroup == nullptr)
	{
		Log::LogString("New PageGroup Linked");
		Book->Page->PageGroup = NewPageGroup;
		Book->Page->PageGroupHead = NewPageGroup;
	}
	//PageGroups exist in Page
	else 
	{
		//Go to last PageGroup
		while (CurrentPageGroup->Next != nullptr)
		{
			CurrentPageGroup = CurrentPageGroup->Next;
		}

		//Link new PageGroup at the end of Page
		Log::LogString("New PageGroup Linked");
		CurrentPageGroup->Next = NewPageGroup;
		NewPageGroup->Previous = CurrentPageGroup;

		//Set the new PageGroup as the current PageGroup
		Book->Page->PageGroup = NewPageGroup;
	}

	Book->Page->PageGroupCount++;
	NewPageGroup->Type = TYPE_PAGEGROUP;
	return NewPageGroup;
}

llPageData* MasterElement::AddPage(llBookData* Book)
{
	//Validate
	if (Book == nullptr) { Log::LogString("ERROR:: Add EmptyShape FAILED:: No Book Provided"); return nullptr; }

	//Setup
	llPageData* NewPage = nullptr;

	//Create Page
	NewPage = new llPageData;

	//Get Current Page
	llPageData* CurrentPage = Book->Page;

	//No Pages in book
	if (CurrentPage == nullptr)
	{
		//Link First Page!
		Log::LogString("New Page Linked");
		Book->Page = NewPage;
		Book->PageHead = NewPage;
	}
	//Pages Exist in Book
	else 
	{
		//Go To last Page
		while (CurrentPage->Next != nullptr)
		{
			CurrentPage = CurrentPage->Next;
		}

	    //Link new Page at the end of the book
		Log::LogString("New Page Linked");
		CurrentPage->Next = NewPage;
		NewPage->Previous = CurrentPage;

		//Set the New Page as the Current Page
		Book->Page = NewPage;
	}

	Book->PageCount++;
	return NewPage;
}

llBookData* MasterElement::AddBook()
{

}

//Copy Shape to new Shape in the same ShapeGroup
void MasterElement::CopyShape(llBookData* Book, llShapeData* ShapeReference)
{
	llVertexData* TopRight = new llVertexData;
	llVertexData* TopLeft = new llVertexData;
	llVertexData* BottomRight = new llVertexData;
	llVertexData* BottomLeft = new llVertexData;

	//Log::LogString("Shape Created");
	llShapeData* NewShape = new llShapeData;
	*NewShape = *ShapeReference;

	//Reset any links
	NewShape->Next = nullptr;
	NewShape->Previous = nullptr;
	NewShape->Vertexx = nullptr;

	llShapeData* FoundTail = Book->Page->PageGroup->PageItem->ShapeGroup->Shape;

	//Find tail then add
	if (FoundTail == nullptr)
	{
		Log::LogString("New ShapeGroup Linked");
		Book->Page->PageGroup->PageItem->ShapeGroup->Shape = NewShape;
		Book->Page->PageGroup->PageItem->ShapeGroup->ShapeHead = NewShape;
	}
	else
	{
		while (FoundTail->Next != nullptr)
		{
			FoundTail = FoundTail->Next;
		}

		FoundTail->Next = NewShape;
		NewShape->Previous = FoundTail;
	}

	llVertexData* CurrentReferenceVertex = ShapeReference->Vertexx;
	llVertexData* CurrentCopyVertex = TopLeft;

	//Go to first vertex of the reference
	while (CurrentReferenceVertex->Previous != nullptr)
	{
		CurrentReferenceVertex = CurrentReferenceVertex->Previous;
	}

	//Top Left
	*TopLeft = *CurrentReferenceVertex;

	//Top Right
	CurrentReferenceVertex = CurrentReferenceVertex->Next;
	*TopRight = *CurrentReferenceVertex;

	//Bottom Right
	CurrentReferenceVertex = CurrentReferenceVertex->Next;
	*BottomRight = *CurrentReferenceVertex;

	//Bottom Left
	CurrentReferenceVertex = CurrentReferenceVertex->Next;
	*BottomLeft = *CurrentReferenceVertex;

	//Set Next
	TopLeft->Next = TopRight;
	TopRight->Next = BottomRight;
	BottomRight->Next = BottomLeft;

	//Set Previous
	BottomLeft->Previous = BottomRight;
	BottomRight->Previous = TopRight;
	TopRight->Previous = TopLeft;

	//Attach Vertices to Shape
	NewShape->Vertexx = TopLeft;
}

//Copy ShapeGroup to new ShapeGroup in the same PageItem
void MasterElement::CopyShapeGroup(llBookData* Book, llShapeGroupData* ShapeGroupReference)
{
	//Create a New Shape Group and Set it's data
	llShapeGroupData* NewShapeGroup = new llShapeGroupData;
	*NewShapeGroup = *ShapeGroupReference;

	//Reset Links
	NewShapeGroup->Next = nullptr;
	NewShapeGroup->Previous = nullptr;
	NewShapeGroup->Shape = nullptr;

	//See if there is an Existing shape group inside page item
	llShapeGroupData* FoundTail = Book->Page->PageGroup->PageItem->ShapeGroup;
	if (FoundTail == nullptr)
	{
		Book->Page->PageGroup->PageItem->ShapeGroup = NewShapeGroup;
		Book->Page->PageGroup->PageItem->ShapeGroupHead = NewShapeGroup;
	}
	else
	{
		while (FoundTail->Next != nullptr)
		{
			FoundTail = FoundTail->Next;
		}

		FoundTail->Next = NewShapeGroup;
		NewShapeGroup->Previous = FoundTail;
	}

	Book->Page->PageGroup->PageItem->ShapeGroup = NewShapeGroup;

	//Go to first Shape of the Shape Group reference
	llShapeData* CurrentReferenceShape = ShapeGroupReference->Shape;
	while (CurrentReferenceShape->Previous != nullptr)
	{
		CurrentReferenceShape = CurrentReferenceShape->Previous;
	}

	while (CurrentReferenceShape != nullptr)
	{
		CopyShape(Book, CurrentReferenceShape);
		CurrentReferenceShape = CurrentReferenceShape->Next;
	}
}

//Copy PageItem to new PageItem in the same PageGroup
void MasterElement::CopyPageItem(llBookData* Book, llPageItemData* PageItemReference)
{
	Log::LogString("Copying Page Item");
	//Create a New Shape Group and Set it's data
	llPageItemData* NewPageItem = new llPageItemData;
	*NewPageItem = *PageItemReference;

	//Reset Links
	NewPageItem->Next = nullptr;
	NewPageItem->Previous = nullptr;
	NewPageItem->ShapeGroup = nullptr;

	int Count = 0;

	//Find tail then add
	llPageItemData* FoundTail = Book->Page->PageGroup->PageItem;
	if (FoundTail == nullptr)
	{
		Book->Page->PageGroup->PageItem = NewPageItem;
		Book->Page->PageGroup->PageItemHead = NewPageItem;
	}
	else
	{
		while (FoundTail->Next != nullptr)
		{
			FoundTail = FoundTail->Next;
		}
		FoundTail->Next = NewPageItem;
		NewPageItem->Previous = FoundTail;
	}

	Book->Page->PageGroup->PageItem = NewPageItem;

	//Go to first Shape of the Shape Group reference
	llShapeGroupData* CurrentReferenceShapeGroup = PageItemReference->ShapeGroup;
	while (CurrentReferenceShapeGroup->Previous != nullptr)
	{
		CurrentReferenceShapeGroup = CurrentReferenceShapeGroup->Previous;
	}

	while (CurrentReferenceShapeGroup != nullptr)
	{
		CopyShapeGroup(Book, CurrentReferenceShapeGroup);
		CurrentReferenceShapeGroup = CurrentReferenceShapeGroup->Next;
	}

	PageItemReference = Book->Page->PageGroup->PageItem;
}

//Copy the same PageGroup into new PageGroup in the same page
//Book->Page could be nullptr
void MasterElement::CopyPageGroup(llBookData* Book, llPageGroupData* PageGroupReference)
{
	//Validate
	if(Book == nullptr) {Log::LogString("ERROR:: CopyPageGroup FAILED:: No PageGroup Provided"); return;};
    if(PageGroupReference == nullptr) {Log::LogString("ERROR:: CopyPageGroup FAILED:: No Book Provided"); return;};

	//Create a New Shape Group and Set it's data
	llPageGroupData* NewPageGroup = new llPageGroupData;
	*NewPageGroup = *PageGroupReference;

	//Reset Links
	NewPageGroup->Next = nullptr;
	NewPageGroup->Previous = nullptr;
	NewPageGroup->PageItem = nullptr;


	//Find tail then add
	llPageGroupData* FoundTail = Book->Page->PageGroup;
	while (FoundTail->Next != nullptr)
	{
		FoundTail = FoundTail->Next;
	}
	FoundTail->Next = NewPageGroup;
	NewPageGroup->Previous = FoundTail;

	Book->Page->PageGroup = NewPageGroup;

	//Go to first Shape of the Shape Group reference
	llPageItemData* CurrentReferencePageItem = PageGroupReference->PageItem;
	while (CurrentReferencePageItem->Previous != nullptr)
	{
		CurrentReferencePageItem = CurrentReferencePageItem->Previous;
	}

	while (CurrentReferencePageItem != nullptr)
	{
		CopyPageItem(Book, CurrentReferencePageItem);
		CurrentReferencePageItem = CurrentReferencePageItem->Next;
	}
}

//copy the same Page into a new page in the same book
void MasterElement::CopyPage(llBookData* Book, llBookData* PageReference)
{

}

//copy book into new book
void MasterElement::CopyBook(llBookData* NewBook, llBookData* BookReference)
{

}

void MasterElement::DeleteShape(llBookData* llBook, llShapeData* ReferenceShape)
{
	//Validate
	//if (llBook == nullptr) { Log::LogString("ERROR:: Delete Shape FAILED:: No Book Provided"); return; }
	if (ReferenceShape == nullptr) { Log::LogString("ERROR:: Delete Shape FAILED:: No Shape Provided"); return; }
	if (ReferenceShape->Vertexx == nullptr) { Log::LogString("ERROR:: Delete Shape FAILED:: Shape Does not Contain Vertices"); return; }

	//Prep
	llVertexData* CurrentVertex = HeadVertex(ReferenceShape->Vertexx);
	llVertexData* Next = nullptr;

	//Save Shape Before and After Current
	llShapeData* PreviousllShape = ReferenceShape->Previous;
	llShapeData* NextllShape = ReferenceShape->Next;

	//Delete all 4 vertices
	while (CurrentVertex != nullptr)
	{
		//Delete current vertex, go to next
		Next = CurrentVertex->Next;
		delete CurrentVertex;
		CurrentVertex = nullptr;
		CurrentVertex = Next;
	}

	//Delete Shape
	ReferenceShape->Vertexx = nullptr;
	delete ReferenceShape;
	ReferenceShape = nullptr;

	//Link any valid shapes back together
	if (PreviousllShape != nullptr) { PreviousllShape->Next = NextllShape; }
	if (NextllShape != nullptr) { NextllShape->Previous = PreviousllShape; }


	//Log::LogString("Shape & Vertices Deleted");
}

void MasterElement::DeleteShapeGroup(llBookData* llBook, llShapeGroupData* ShapeGroupReference)
{
	//Validate
	if (llBook == nullptr) { Log::LogString("ERROR:: Delete ShapeGroup FAILED:: No Book Provided"); return; }
	if (ShapeGroupReference == nullptr) { Log::LogString("ERROR:: Delete ShapeGroup FAILED:: No ShapeGroup Provided"); return; }
	if (ShapeGroupReference->Shape == nullptr) { Log::LogString("ERROR:: Delete ShapeGroup FAILED:: ShapeGroup Does not Contain Shapes"); return; }

	//Prep
	llShapeData* CurrentShape = HeadShape(ShapeGroupReference->Shape);
	llShapeData* Next = nullptr;

	//Save ShapeGroup Before and After Current
	llShapeGroupData* PreviousllShapeGroup = ShapeGroupReference->Previous;
	llShapeGroupData* NextllShapeGroup = ShapeGroupReference->Next;

	//Delete all Shapes
	while (CurrentShape != nullptr)
	{
		//Delete current Shape, go to next
		Next = CurrentShape->Next;
		DeleteShape(llBook, CurrentShape);
		CurrentShape = Next;
	}

	//Delete ShapeGroup
	ShapeGroupReference->Shape = nullptr;
	delete ShapeGroupReference;
	ShapeGroupReference = nullptr;

	//Link any valid shapegroups back together
	if (PreviousllShapeGroup != nullptr) { PreviousllShapeGroup->Next = NextllShapeGroup; }
	if (NextllShapeGroup != nullptr) { NextllShapeGroup->Previous = PreviousllShapeGroup; }

	//Log::LogString("ShapeGroup Deleted");
}


void MasterElement::DeletePageItem(llBookData* llBook, llPageItemData* PageItemReference)
{
	//Validate
	if (llBook == nullptr) { Log::LogString("ERROR:: Delete Shape FAILED:: No Book Provided"); return; }
	if (PageItemReference == nullptr) { Log::LogString("ERROR:: Delete Shape FAILED:: Invalid Shape State"); return; }
	if (PageItemReference->ShapeGroup == nullptr) { Log::LogString("ERROR:: Delete Shape FAILED:: Shape Does not Contain Vertices"); return; }

	//Prep
	llShapeGroupData* CurrentShapeGroup = HeadShapeGroup(PageItemReference->ShapeGroup);
	llShapeGroupData* Next = nullptr;

	//Save PageItem Before and After Current
	llPageItemData* PreviousllPageItem = PageItemReference->Previous;
	llPageItemData* NextllPageItem = PageItemReference->Next;

	//Delete all Shapes
	while (CurrentShapeGroup != nullptr)
	{
		//Delete current ShapeGroup, go to next
		Next = CurrentShapeGroup->Next;
		DeleteShapeGroup(llBook, CurrentShapeGroup);
		CurrentShapeGroup = Next;
	}

	Log::LogString("Passed ShapeGroup Delete");

	//Delete PageItem
	PageItemReference->ShapeGroup = nullptr;
	delete PageItemReference;
	PageItemReference = nullptr;

	//Link any valid shapegroups back together
	if (PreviousllPageItem != nullptr) { PreviousllPageItem->Next = NextllPageItem; }
	if (NextllPageItem != nullptr) { NextllPageItem->Previous = PreviousllPageItem; }

	//Log::LogString("PageItem Deleted");
}

void MasterElement::DeletePageGroup(llBookData* llBook, llPageGroupData* PageGroupReference)
{
	//Validate
	if (llBook == nullptr) { Log::LogString("ERROR:: Delete PageItem FAILED:: No Book Provided"); return; }
	if (PageGroupReference == nullptr) { Log::LogString("ERROR:: Delete PageItem FAILED:: No PageItem Provided"); return; }
	if (PageGroupReference->PageItem == nullptr) { Log::LogString("ERROR:: Delete PageItem FAILED:: PageItem Does not Contain ShapeGroups"); return; }

	//Prep
	llPageItemData* CurrentPageItem = HeadPageItem(PageGroupReference->PageItem);
	llPageItemData* Next = nullptr;

	//Save PageGroup Before and After Current
	llPageGroupData* PreviousllPageGroup = PageGroupReference->Previous;
	llPageGroupData* NextllPageGroup = PageGroupReference->Next;

	//Delete all Shapes
	while (CurrentPageItem != nullptr)
	{
		//Delete current PageItem, go to next
		Next = CurrentPageItem->Next;
		DeletePageItem(llBook, CurrentPageItem);
		CurrentPageItem = Next;
	}

	//Delete PageGroup
	PageGroupReference->PageItem = nullptr;
	delete PageGroupReference;
	PageGroupReference = nullptr;

	//Link any valid shapegroups back together
	if (PreviousllPageGroup != nullptr) { PreviousllPageGroup->Next = NextllPageGroup; }
	if (NextllPageGroup != nullptr) { NextllPageGroup->Previous = PreviousllPageGroup; }

	//Log::LogString("PageGroup Deleted");
}
///////////////////////////////////////////////////////////////
void MasterElement::DeletePage(llBookData* llBook, llPageData* PageReference)
{
	//Validate
	if (llBook == nullptr) { Log::LogString("ERROR:: Delete PageItem FAILED:: No Book Provided"); return; }
	if (PageReference == nullptr) { Log::LogString("ERROR:: Delete PageItem FAILED:: No PageItem Provided"); return; }
	if (PageReference->PageGroup == nullptr) { Log::LogString("ERROR:: Delete PageItem FAILED:: PageItem Does not Contain ShapeGroups"); return; }

	//Prep
	llPageGroupData* CurrentPageGroup = HeadPageGroup(PageReference->PageGroup);
	llPageGroupData* Next = nullptr;

	//Save Page Before and After Current
	llPageData* PreviousllPage = PageReference->Previous;
	llPageData* NextllPage = PageReference->Next;

	//Delete all Shapes
	while (CurrentPageGroup != nullptr)
	{
		//Delete current PageGroup, go to next
		Next = CurrentPageGroup->Next;
		DeletePageGroup(llBook, CurrentPageGroup);
		CurrentPageGroup = Next;
	}

	//Delete Page
	PageReference->PageGroup = nullptr;
	delete PageReference;
	PageReference = nullptr;

	//Link any valid shapegroups back together
	if (PreviousllPage != nullptr) { PreviousllPage->Next = NextllPage; }
	if (NextllPage != nullptr) { NextllPage->Previous = PreviousllPage; }

	//Log::LogString("Page Deleted");
}

void MasterElement::EraseBook(llBookData* llBook)
{

	//Validate
	if (llBook == nullptr) { Log::LogString("ERROR:: Delete Book FAILED:: No Book Provided"); return; }
	if (llBook->Page == nullptr) { Log::LogString("ERROR:: Delete Book FAILED:: No Pages in Book"); return; }


	//Prep
	llPageData* CurrentPage = HeadPage(llBook->Page);
	llPageData* Next = nullptr;

	//Save ShapeGroup Before and After Current
	//llBookData* PreviousllBook = llBook->Previous;
	//llBookData* NextllBook = llBook->Next;

	//Delete all Shapes
	while (CurrentPage != nullptr)
	{
		//Delete current Page, go to next
		Next = CurrentPage->Next;
		DeletePage(llBook, CurrentPage);
		CurrentPage = Next;
	}

	llBook->Page = nullptr;

	Log::LogString("Book Erased");

	/////////////////////////Un-Comment Code if you choose t link books together////////////////////

	//Delete Book
	//delete llBook;
	//llBook = nullptr;

	//Link any valid Books back together
	//if (PreviousllBook != nullptr) { PreviousllBook->Next = NextllBook; }
	//if (NextllBook != nullptr) { NextllBook->Previous = PreviousllBoook; }

}

void MasterElement::ToggleToggle(bool& ToToggle)
{
	if (ToToggle == false)
	{
		ToToggle = true;
		return;
	}

	if (ToToggle == true)
	{
		ToToggle = false;
		return;
	}
}

int MasterElement::GetShapeCount(llShapeGroupData* llShapeGroup)
{
	int Count = 0;
	if (llShapeGroup != nullptr)
	{
		llShapeData* CurrentShape = llShapeGroup->Shape;

		while (CurrentShape->Previous != nullptr)
		{
			CurrentShape = CurrentShape->Previous;
		}

		while (CurrentShape->Previous != nullptr)
		{
			CurrentShape = CurrentShape->Next;
			Count++;
		}

		return Count;
	}
	else
	{
		cout << "Cannot compute Shape count:: No Shape Group Provided" << endl;
	}
}

int MasterElement::GetShapeGroupCount(llPageItemData* llPageItem)
{
	int Count = 0;
	if (llPageItem != nullptr)
	{
		llShapeGroupData* CurrentShapeGroup = llPageItem->ShapeGroup;

		while (CurrentShapeGroup->Previous != nullptr)
		{
			CurrentShapeGroup = CurrentShapeGroup->Previous;
		}

		while (CurrentShapeGroup->Previous != nullptr)
		{
			CurrentShapeGroup = CurrentShapeGroup->Next;
			Count++;
		}

		return Count;
	}
	else
	{
		cout << "Cannot compute ShapeGroup count:: No PageItem Provided" << endl;
	}
}

int MasterElement::GetPageItemCount(llPageGroupData* llPageGroup)
{
	int Count = 0;
	if (llPageGroup != nullptr)
	{
		llPageItemData* CurrentPageItem = llPageGroup->PageItem;

		while (CurrentPageItem->Previous != nullptr)
		{
			CurrentPageItem = CurrentPageItem->Previous;
		}

		while (CurrentPageItem->Previous != nullptr)
		{
			CurrentPageItem = CurrentPageItem->Next;
			Count++;
		}

		return Count;
	}
	else
	{
		cout << "Cannot compute PageItem count:: No PageGroup Found" << endl;
	}
}

void MasterElement::PrintPageItemShapes(llPageItemData* llPageItem)
{
	cout << "----------------------Trying To Print PageItem Shapes..-------------------------" << endl;
	int ShapeCount = 0;
	llShapeGroupData* CurrentShapeGroup = llPageItem->ShapeGroup;

	if (CurrentShapeGroup == nullptr) { Log::LogString(" is empty"); return; };

	//Find Head Shape
	while (CurrentShapeGroup->Previous != nullptr)
	{
		CurrentShapeGroup = CurrentShapeGroup->Previous;
	}

	//Print All Shapes
	while (CurrentShapeGroup != nullptr)
	{
		PrintShapeGroupShapes(CurrentShapeGroup);
		CurrentShapeGroup = CurrentShapeGroup->Next;
		ShapeCount++;
	}
}

void MasterElement::PrintPageItemShapeGroups(llPageItemData* llPageItem)
{
	cout << "------------Trying To Print Group Shapes..------------" << endl;
	int ShapeCount = 0;
	llShapeGroupData* CurrentShapeGroup = llPageItem->ShapeGroup;

	if (CurrentShapeGroup == nullptr) { Log::LogString("ShapeGroup is empty"); return; };

	//Find Head Shape
	while (CurrentShapeGroup->Previous != nullptr)
	{
		CurrentShapeGroup = CurrentShapeGroup->Previous;
	}

	//Print All Shapes
	while (CurrentShapeGroup != nullptr)
	{
		PrintllShapeGroup(CurrentShapeGroup, ShapeCount);
		CurrentShapeGroup = CurrentShapeGroup->Next;
		ShapeCount++;
	}
}

void MasterElement::PrintllShapeGroup(llShapeGroupData* llShapeGroup)
{
	cout <<  "------------ShapeGroup (" << llShapeGroup << ")------------------" << endl;
	Log::LogVec2("Position: ", llShapeGroup->Position);
	Log::LogVec2("Size: ", llShapeGroup->Size);
	Log::LogVec4("Color: ", llShapeGroup->Color);

	Log::LogString("------");
	Log::LogFloat("ShapeTop: ", llShapeGroup->Top);
	Log::LogFloat("ShapeBottom: ", llShapeGroup->Bottom);
	Log::LogFloat("ShapeLeft: ", llShapeGroup->Left);
	Log::LogFloat("ShapeRight: ", llShapeGroup->Right);
	Log::LogString("----------------------------------------------------------------");
	//cout << "ActiveTexture: {" << CurrentShapeData.ActiveTexture << "}" << endl;
	//cout << "Action: {" << CurrentShapeData.Action << "}" << endl;
	//cout << "MouseAccess: {" << CurrentShapeData.MouseAccess << "}" << endl;
	//cout << "Centered: {" << CurrentShapeData.Centered << "}" << endl;
	//cout << "Highlighted: {" << CurrentShapeData.Highlighted << "}" << endl;
}

void MasterElement::PrintllShapeGroup(llShapeGroupData* llShapeGroup, int Offset)
{
	cout << "------------ShapeGroup (" << llShapeGroup << ")[" << Offset << "]------------------" << endl;
	Log::LogVec2("Position: ", llShapeGroup->Position);
	Log::LogVec2("Size: ", llShapeGroup->Size);
	Log::LogVec4("Color: ", llShapeGroup->Color);

	Log::LogString("------");
	Log::LogFloat("ShapeTop: ", llShapeGroup->Top);
	Log::LogFloat("ShapeBottom: ", llShapeGroup->Bottom);
	Log::LogFloat("ShapeLeft: ", llShapeGroup->Left);
	Log::LogFloat("ShapeRight: ", llShapeGroup->Right);
	Log::LogString("----------------------------------------------------------------");
	//cout << "ActiveTexture: {" << CurrentShapeData.ActiveTexture << "}" << endl;
	//cout << "Action: {" << CurrentShapeData.Action << "}" << endl;
	//cout << "MouseAccess: {" << CurrentShapeData.MouseAccess << "}" << endl;
	//cout << "Centered: {" << CurrentShapeData.Centered << "}" << endl;
	//cout << "Highlighted: {" << CurrentShapeData.Highlighted << "}" << endl;
}

void MasterElement::PrintShapeGroupShapes(llShapeGroupData* llShapeGroup)
{
	cout << "------------Trying To Print Group Shapes..------------" << endl;
	int ShapeCount = 0;
	llShapeData* CurrentShape = llShapeGroup->Shape;

	if (CurrentShape == nullptr) { Log::LogString("ShapeGroup is empty"); return; };

	//Find Head Shape
	while (CurrentShape->Previous != nullptr)
	{
		CurrentShape = CurrentShape->Previous;
	}

	//Print All Shapes
	while (CurrentShape != nullptr)
	{
		
		PrintllShape(CurrentShape, ShapeCount);
		CurrentShape = CurrentShape->Next;
		ShapeCount++;
	}
}

void MasterElement::PrintllShape(llShapeData* llShape)
{
	Log::LogString("Trying To Print llShape");
	cout << "------------ShapeData-Data (" << llShape << ")------------------" << endl;
	Log::LogVec2("Position: ", llShape->Position);
	Log::LogVec2("Size: ", llShape->Size);
	Log::LogVec4("Color: ", llShape->Color);


	cout << "-------" << endl;
	Log::LogString("Text: " + llShape->Text);
	cout << "Ascii: " << char(llShape->Ascii) << endl;
	Log::LogString("------");
	Log::LogFloat("ShapeTop: ", llShape->Top);
	Log::LogFloat("ShapeBottom: ", llShape->Bottom);
	Log::LogFloat("ShapeLeft: ", llShape->Left);
	Log::LogFloat("ShapeRight: ", llShape->Right);
	Log::LogString("-------------------------------------------------");
	//cout << "ActiveTexture: {" << CurrentShapeData.ActiveTexture << "}" << endl;
	//cout << "Action: {" << CurrentShapeData.Action << "}" << endl;
	//cout << "MouseAccess: {" << CurrentShapeData.MouseAccess << "}" << endl;
	//cout << "Centered: {" << CurrentShapeData.Centered << "}" << endl;
	//cout << "Highlighted: {" << CurrentShapeData.Highlighted << "}" << endl;
}

void MasterElement::PrintllShape(llShapeData* llShape, int Offset)
{
	Log::LogString("Trying To Print llShape");
	cout << "------------ShapeData-Data (" << llShape << ") [" << Offset << "] ------------------" << endl;
	Log::LogVec2("Position: ", llShape->Position);
	Log::LogVec2("Size: ", llShape->Size);
	Log::LogVec4("Color: ", llShape->Color);


	cout << "-------" << endl;
	Log::LogString("Text: " + llShape->Text);
	cout << "Ascii: " << char(llShape->Ascii) << endl;
	Log::LogString("------");
	Log::LogFloat("ShapeTop: ", llShape->Top);
	Log::LogFloat("ShapeBottom: ", llShape->Bottom);
	Log::LogFloat("ShapeLeft: ", llShape->Left);
	Log::LogFloat("ShapeRight: ", llShape->Right);
	Log::LogString("-------------------------------------------------");
	//cout << "ActiveTexture: {" << CurrentShapeData.ActiveTexture << "}" << endl;
	//cout << "Action: {" << CurrentShapeData.Action << "}" << endl;
	//cout << "MouseAccess: {" << CurrentShapeData.MouseAccess << "}" << endl;
	//cout << "Centered: {" << CurrentShapeData.Centered << "}" << endl;
	//cout << "Highlighted: {" << CurrentShapeData.Highlighted << "}" << endl;
}


bool MasterElement::IsInitialized()
{
	return Initialized;
}

bool MasterElement::IsInBounds(int ID)
{
	if (Initialized == true)
	{
		return CurrentPage->InBounds(ID);
	}
   // Log::LogString("Bounds Error:: Element Not Initialized"); return false;
}


MasterElement::MasterElement()
{

}



glm::vec2 MasterElement::PTLPixelToComputer(glm::vec2 Position)  //Working
{
	float xPos;
	xPos = (Position[0] / (1200 / 20)) * 0.1 - 1; //System::Width
	float yPos;
	yPos = (Position[1] / (600 / 20)) * 0.1 - 1; //System::Height
	return { xPos, yPos * -1 };
}; //PTL Position, Top, Left

glm::vec2 MasterElement::PBLPixelToComputer(glm::vec2 Position) //Working
{
	float xPos;
	xPos = (Position[0] / (1200 / 20)) * 0.1 - 1; //System::Width
	float yPos;
	yPos = (Position[1] / (600 / 20)) * 0.1 - 1; //System::Height
	return { xPos, yPos };
}


glm::vec2 MasterElement::SPixelToComputer(glm::vec2 Size) //Working
{
	float xSize = Size[0] / (1200 / 2); //System::Width
	float ySize = Size[1] / (600 / 2); //System::Height

	return { xSize, ySize };
};

glm::vec2 MasterElement::SOneToComputer(glm::vec2 Size)
{
	float AspectRatio = 1200 / 600; // Width / Height
	return { Size[0], Size[1] * AspectRatio };
}

glm::vec2 MasterElement::PComputerToBLPixel(glm::vec2 Position)
{
	float xPos;
	xPos = (((Position[0] + 1) / 0.1) * (1200 / 20)); //System::Width
	float yPos;
	yPos = (((Position[1] + 1) / 0.1) * (600 / 20)); //System::Height
	return { xPos, yPos };
};

glm::vec2 MasterElement::SComputerToPixel(glm::vec2 Size) //Working
{
	float xSize = Size[0] * (1200 / 2); //System::Width
	float ySize = Size[1] * (600 / 2); //System::Height
	return { xSize, ySize };;
}

glm::vec2 MasterElement::SComputerToOne(glm::vec2 Size)
{
	float AspectRatio = 1200 / 600; // Width / Height
	return { Size[0], Size[1] / AspectRatio };
}


glm::vec2 MasterElement::PComputerToTLPixel(glm::vec2 Position) //Working
{
	float xPos;
	xPos = (((Position[0] + 1) / 0.1) * (1200 / 20)); //System::Width
	float yPos = Position[1] * -1;
	yPos = ((yPos + 1) / 0.1) * (600 / 20); //System::Height
	return { xPos, yPos };
};


glm::vec2 MasterElement::PMiddleToTopLeft(glm::vec2 Position, glm::vec2 Size)
{
	//It's at the middle. put it to top left
	Position[0] -= (Size[0] / 2);
	Position[1] += (Size[1] / 2);
	return Position;
}

glm::vec2 MasterElement::PTopLeftToMiddle(glm::vec2 Position, glm::vec2 Size)
{
	//It's at the top left, put it to the middle
	Position[0] += (Size[0] / 2);
	Position[1] -= (Size[1] / 2);
	return Position;
}

glm::vec2 MasterElement::ApplyPositionConversion(glm::vec2 Position, int Conversion, glm::vec2 Size)
{
	//Position Conversion
	switch (Conversion)
	{
	case 1:
		//Bottom Left Pixel To Computer Coordinates
		Position = PBLPixelToComputer(Position);
		break;
	case 2:
		//Middle To Top Left
		Position = PMiddleToTopLeft(Position, Size);
		break;
	case 3:
		//Top Left Pixel To Computer Coordinates
		Position = PTLPixelToComputer(Position);
		break;
	case 4:
		Position = PComputerToBLPixel(Position);
		break;
	case 5:
		Position = PTopLeftToMiddle(Position, Size);
		break;
	}
	return Position;
}

glm::vec2 MasterElement::ApplyPositionConversion(glm::vec2 Position, int Conversion)
{
	//Position Conversion
	switch (Conversion)
	{
	case 1:
		//Bottom Left Pixel To Computer Coordinates
		Position = PBLPixelToComputer(Position);
		break;
	case 2:
		//Middle To Top Left
		//Position = PMiddleToTopLeft(Position, CurrentShapeData.Size);
		break;
	case 3:
		//Top Left Pixel To Computer Coordinates
		Position = PTLPixelToComputer(Position);
		break;
	case 4:
		Position = PComputerToBLPixel(Position);
		break;
	}
	return Position;
}

glm::vec2 MasterElement::ApplySizeConversion(glm::vec2 Size, int Conversion)
{
	//Size Conversion
	switch (Conversion)
	{
	case 1:
		//Bottom Left Pixel To Computer Coordinates
		Size = SPixelToComputer(Size);

		break;
	case 2:
		//Middle To Top Left
		Size = SOneToComputer(Size);
		break;
	case 3:
		Size = SComputerToPixel(Size);

		break;
	}

	return Size;
}

void MasterElement::ManualPlaceBelow(const int PlacementType, const glm::vec4& ElementEdges, int& NewInputType, glm::vec2& NewPosition, int PixelPadding)
{
	switch (PlacementType)
	{
	case MATCH_BEGINNINGS:
	{
		float Left = ElementEdges[0];
		float Bottom = ElementEdges[3] - (PixelPadding * PIXEL);
		NewPosition = { Left, Bottom };
		NewInputType = INPUT_TOPLEFT;
		break;
	}
	case MATCH_ENDS:
	{
		float Right = ElementEdges[1];
		float Bottom = ElementEdges[3] - (PixelPadding * PIXEL);
		NewPosition = { Right, Bottom };
		NewInputType = INPUT_TOPRIGHT;
		break;
	}
	{
	case MATCH_CENTERS:
		float Center_x = (ElementEdges[1] + ElementEdges[0]) / 2; // (Left + Right) / Half
		float Bottom = ElementEdges[3] - (PixelPadding * PIXEL);
		NewPosition = { Center_x, Bottom };
		NewInputType = INPUT_TOP;
		break;
	}
	case MATCH_BEGINNING_TO_END:
	{
		float Left = ElementEdges[0];
		float Bottom = ElementEdges[3] - (PixelPadding * PIXEL);
		NewPosition = { Left, Bottom };
		NewInputType = INPUT_TOPRIGHT; //New Position is the new element's Top Right
		break;
	}
	case MATCH_END_TO_BEGINNING:
	{
		float Right = ElementEdges[1];
		float Bottom = ElementEdges[3] - (PixelPadding * PIXEL);
		NewPosition = { Right, Bottom };
		NewInputType = INPUT_TOPLEFT; //New Position is the new element's Top Right
		break;
	}
	}
}
void MasterElement::ManualPlaceAbove(const int PlacementType, const glm::vec4& ElementEdges, int& NewInputType, glm::vec2& NewPosition, int PixelPadding)
{
	switch (PlacementType)
	{
	case MATCH_BEGINNINGS:
	{
		float Left = ElementEdges[0];
		float Top = ElementEdges[2] + (PixelPadding * PIXEL);
		NewPosition = { Left, Top };
		NewInputType = INPUT_BOTTOMLEFT; //
		break;
	}
	case MATCH_ENDS:
	{
		float Right = ElementEdges[1];
		float Top = ElementEdges[2] + (PixelPadding * PIXEL);
		NewPosition = { Right, Top };
		NewInputType = INPUT_BOTTOMRIGHT;
		break;
	}
	case MATCH_CENTERS:
	{
		float Center_x = (ElementEdges[1] + ElementEdges[0]) / 2; // (Left + Right) / Half
		float Top = ElementEdges[2] + (PixelPadding * PIXEL);
		NewPosition = { Center_x, Top };
		NewInputType = INPUT_BOTTOM;
		break;
	}
	case MATCH_BEGINNING_TO_END:
	{
		float Left = ElementEdges[0];
		float Top = ElementEdges[2] + (PixelPadding * PIXEL);
		NewPosition = { Left, Top };
		NewInputType = INPUT_BOTTOMRIGHT; //New Position is the new element's Top Right
		break;
	}
	case MATCH_END_TO_BEGINNING:
	{
		float Right = ElementEdges[1];
		float Top = ElementEdges[2] + (PixelPadding * PIXEL);
		NewPosition = { Right, Top };
		NewInputType = INPUT_BOTTOMLEFT; //New Position is the new element's Top Right
		break;
	}
	}
}

//Left. Right. Top. Bottom
void MasterElement::ManualPlaceRight(const int PlacementType, const glm::vec4& ElementEdges, int& NewInputType, glm::vec2& NewPosition, int PixelPadding)
{
	switch (PlacementType)
	{
	case MATCH_FLOORS:
	{
		float Right = ElementEdges[1] + (PixelPadding * PIXEL);
		float Bottom = ElementEdges[3];
		NewPosition = { Right, Bottom };
		NewInputType = INPUT_BOTTOMLEFT; 
		break;
	}
	case MATCH_CEILINGS:
	{
		float Right = ElementEdges[1] + (PixelPadding * PIXEL);
		float Top = ElementEdges[2];
		NewPosition = { Right, Top };
		NewInputType = INPUT_TOPLEFT;
		break;
	}
	case MATCH_CENTERS:
	{
		float Right = ElementEdges[1] + (PixelPadding * PIXEL); // (Left + Right) / Half
		float Center_y = (ElementEdges[3] + ElementEdges[2]) / 2;
		NewPosition = { Right, Center_y };
		NewInputType = INPUT_LEFT;
		break;
	}
	}
}

void MasterElement::ManualPlaceLeft(const int PlacementType, const glm::vec4& ElementEdges, int& NewInputType, glm::vec2& NewPosition, int PixelPadding)
{
	switch (PlacementType)
	{
	case MATCH_FLOORS:
	{
		float Left = ElementEdges[0] - (PixelPadding * PIXEL);
		float Bottom = ElementEdges[3];
		NewPosition = { Left, Bottom };
		NewInputType = INPUT_BOTTOMRIGHT; 
		break;
	}
	case MATCH_CEILINGS:
	{
		float Left = ElementEdges[0] - (PixelPadding * PIXEL);
		float Top = ElementEdges[2];
		NewPosition = { Left, Top };
		NewInputType = INPUT_TOPRIGHT;
		break;
	}
	case MATCH_CENTERS:
	{
		float Left = ElementEdges[0] - (PixelPadding * PIXEL); // (Left + Right) / Half
		float Center_y = (ElementEdges[3] + ElementEdges[2]) / 2;
		NewPosition = { Left, Center_y };
		NewInputType = INPUT_RIGHT;
		break;
	}
	}
}


void MasterElement::TextPlaceRight(const int PlacementType, const glm::vec4& ElementEdges, int& NewInputType, glm::vec2& NewPosition, int PixelPadding)
{
	switch (PlacementType)
	{
	case MATCH_FLOORS:
	{
		float Right = ElementEdges[1] + (PixelPadding * PIXEL);
		float Bottom = ElementEdges[3];
		NewPosition = { Right, Bottom };
		NewInputType = INPUT_BOTTOMLEFT; 
		break;
	}
	case MATCH_CEILINGS:
	{
		float Right = ElementEdges[1] + (PixelPadding * PIXEL);
		float Top = ElementEdges[2];
		NewPosition = { Right, Top };
		NewInputType = INPUT_TOPLEFT;
		break;
	}
	case MATCH_CENTERS:
	{
		float Right = ElementEdges[1] + (PixelPadding * PIXEL); // (Left + Right) / Half
		NewPosition[X_AXIS] = Right;
		NewInputType = INPUT_LEFT;
		break;
	}
	}
}

void MasterElement::TextPlaceLeft(const int PlacementType, const glm::vec4& ElementEdges, int& NewInputType, glm::vec2& NewPosition, int PixelPadding)
{
	switch (PlacementType)
	{
	case MATCH_FLOORS:
	{
		float Left = ElementEdges[0] - (PixelPadding * PIXEL);
		float Bottom = ElementEdges[3];
		NewPosition = { Left, Bottom };
		NewInputType = INPUT_BOTTOMRIGHT;
		break;
	}
	case MATCH_CEILINGS:
	{
		float Left = ElementEdges[0] - (PixelPadding * PIXEL);
		float Top = ElementEdges[2];
		NewPosition = { Left, Top };
		NewInputType = INPUT_TOPRIGHT;
		break;
	}
	case MATCH_CENTERS:
	{
		float Left = ElementEdges[0] - (PixelPadding * PIXEL); // (Left + Right) / Half
		float Center_y = NewPosition[Y_AXIS];
		NewPosition = { Left, Center_y };
		NewInputType = INPUT_RIGHT;
		break;
	}
	}
}


glm::vec4 MasterElement::UpdateEdges(glm::vec4 TestEdges, glm::vec4 EdgesToUpdate)
{
	//Most Positive == Most Right
	if (EdgesToUpdate[EDGE_RIGHT] < TestEdges[EDGE_RIGHT]) 
	{
		//Set Most Right
		EdgesToUpdate[EDGE_RIGHT] = TestEdges[EDGE_RIGHT];
	}

	//Most Negative == Most Left
	if (EdgesToUpdate[EDGE_LEFT] > TestEdges[EDGE_LEFT]) 
	{
		//Set Most Left
		EdgesToUpdate[EDGE_LEFT] = TestEdges[EDGE_LEFT];
	}

	//Most Positive == Most Top
	if (EdgesToUpdate[EDGE_TOP] < TestEdges[EDGE_TOP]) //
	{
		//Set Most Top
		EdgesToUpdate[EDGE_TOP] = TestEdges[EDGE_TOP];
	}

	//Most Negative == Most Bottom
	if (EdgesToUpdate[EDGE_BOTTOM] > TestEdges[EDGE_BOTTOM]) //
	{
		//Set Most Bottom
		EdgesToUpdate[EDGE_BOTTOM] = TestEdges[EDGE_BOTTOM];
	}

	return EdgesToUpdate;
}

void MasterElement::SizeFromEdges(glm::vec4 Edges, glm::vec2& Size)
{
	Size[X_AXIS] = Edges[EDGE_RIGHT] - Edges[EDGE_LEFT]; //Correct
	Size[Y_AXIS] = Edges[EDGE_TOP] - Edges[EDGE_BOTTOM]; //Correct
}