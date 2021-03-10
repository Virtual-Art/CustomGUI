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

	//Page
	llPageData* CurrentPage = llBook->Page;

	//Set to beginning
	while (CurrentPage->Previous != nullptr)
	{
		CurrentPage = CurrentPage->Previous;
	}

	while(CurrentPage != nullptr && CurrentPage->PageGroup != nullptr)
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


void MasterElement::FindElement(llBookData* llBook, int ElementLevel)
{
	//if (llBook->Page == nullptr) { return; };
	//Log::LogString("Printing Book Stats");

	float xMouse = MouseManager::xPos;
	float yMouse = MouseManager::yPos;

	int VertexIndex = 0;
	int PageCount = 0;
	int PageGroupCount = 0;
	int PageItemCount = 0;
	int ShapeGroupCount = 0;
	int ShapeCount = 0;
	int VertexCount = 0;

	llVertexData* SavedVertex = llBook->Page->PageGroup->PageItem->ShapeGroup->Shape->Vertexx;
	llShapeData* SavedShape = llBook->Page->PageGroup->PageItem->ShapeGroup->Shape;
	llShapeGroupData* SavedShapeGroup = llBook->Page->PageGroup->PageItem->ShapeGroup;
	llPageItemData* SavedPageItem = llBook->Page->PageGroup->PageItem;
	llPageGroupData* SavedPageGroup = llBook->Page->PageGroup;
	llPageData* SavedPage = llBook->Page;

	//Page
	llPageData* CurrentPage = llBook->Page;

	//Set to beginning
	while (CurrentPage->Previous != nullptr)
	{
		CurrentPage = CurrentPage->Previous;
	}

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
				if (ElementLevel == LEVEL_PAGEITEM)
				{
					if (xMouse < CurrentPageItem->Right && xMouse >  CurrentPageItem->Left&& yMouse < CurrentPageItem->Top && yMouse >  CurrentPageItem->Bottom)
					{
						cout << " [PageItem Found] | P:" << PageCount << " | PG:" << PageGroupCount << " | PI:" << PageItemCount << endl;
					}
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
					ShapeGroupCount++;
					//Shape
					llShapeData* CurrentShape = CurrentShapeGroup->Shape;
					if (CurrentShapeGroup->Shape != nullptr)
					{

						if (xMouse < CurrentShapeGroup->Right && xMouse >  CurrentShapeGroup->Left&& yMouse < CurrentShapeGroup->Top && yMouse >  CurrentShapeGroup->Bottom)
						{
							if (ElementLevel == LEVEL_SHAPEGROUP)
							{
								cout << "[ShapeGroup Found] |P:" << PageCount << " | PG:" << PageGroupCount << " | PI:" << PageItemCount << " | SG:" << ShapeGroupCount << endl;
							}
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
								if (ElementLevel == LEVEL_SHAPE)
								{
									
									if (CurrentShape->ShapeButton != nullptr)
									{
										cout << "[Shape Found] | P:" << PageCount << " | PG:" << PageGroupCount << " | PI:" << PageItemCount << " | SG:" << ShapeGroupCount << " | S:" << ShapeCount << " | Char: " << char(CurrentShape->Ascii) << endl;
										CurrentShape->ShapeButton->ProcessMouseButtons(MouseManager::CurrentMouseState);
									}
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


	llBook->Page = SavedPage;
	llBook->Page->PageGroup = SavedPageGroup;
	llBook->Page->PageGroup->PageItem = SavedPageItem;
	llBook->Page->PageGroup->PageItem->ShapeGroup = SavedShapeGroup;
	llBook->Page->PageGroup->PageItem->ShapeGroup->Shape = SavedShape;
	llBook->Page->PageGroup->PageItem->ShapeGroup->Shape->Vertexx = SavedVertex;
}

void MasterElement::PrintBook(llBookData* llBook)
{

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
			//Log::LogChar("Finding ttail..", FoundTail->Ascii);
			cout << "Finding TTail " << FoundTail << endl;
		}
		Log::LogChar("New Shape Linked", char(FoundTail->Ascii));
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

	int Count = 0;

	//Find tail then add
	llShapeGroupData* FoundTail = Book->Page->PageGroup->PageItem->ShapeGroup;
	while (FoundTail->Next != nullptr)
	{
		FoundTail = FoundTail->Next;
		Log::LogInt("Count ", Count);
	}
	Log::LogString("New ShapeGroup Linked");
	FoundTail->Next = NewShapeGroup;
	NewShapeGroup->Previous = FoundTail;

	Book->Page->PageGroup->PageItem->ShapeGroup = NewShapeGroup;

	//Go to first Shape of the Shape Group reference
	llShapeData* CurrentReferenceShape = ShapeGroupReference->Shape;
	while (CurrentReferenceShape->Previous != nullptr)
	{
		CurrentReferenceShape = CurrentReferenceShape->Previous;
	}

	//while (CurrentReferenceShape != nullptr)
	//{
		CopyShape(Book, CurrentReferenceShape);
		CurrentReferenceShape = CurrentReferenceShape->Next;

		CopyShape(Book, CurrentReferenceShape);
		CurrentReferenceShape = CurrentReferenceShape->Next;

		CopyShape(Book, CurrentReferenceShape);
		CurrentReferenceShape = CurrentReferenceShape->Next;

		CopyShape(Book, CurrentReferenceShape);
		CurrentReferenceShape = CurrentReferenceShape->Next;
	//}
}

//Copy PageItem to new PageItem in the same PageGroup
void MasterElement::CopyPageItem(llBookData* Book, llPageItemData* PageItemReference)
{

}

//Copy the same PageGroup into new PageGroup in the same page
void MasterElement::CopyPageGroup(llBookData* Book, llPageGroupData* PageGroupReference)
{

}

//copy the same Page into a new page in the same book
void MasterElement::CopyPage(llBookData* Book, llBookData* PageReference)
{

}

//copy book into new book
void MasterElement::CopyBook(llBookData* NewBook, llBookData* BookReference)
{

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