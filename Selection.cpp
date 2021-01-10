#include "Selection.h"

//Selection::Selection(Page& Page)
//{
//	
//	for (int i = 0; i < 100; i++)
//	{
//		this->SelectionContainer[i] = -1;
//	}
//
//	this->SelectorPage = &Page;
//	this->Selections = SelectionContainer;
//	this->xMouse = 0;
//	this->yMouse = 0;
//	this->SelectorActive = false;
//	this->MaxSelectionCount = 100;
//	this->SelectionCount = 0;
//	this->TypeSelected = -1;
//	this->SingleSelection = true;
//	this->OverrideSelect = false;
//	this->ForceElement = -1;
//	this->ForceType = -1;
//
//	ElementHovered = -1;
//}
//
////this is in the loop
//int* Selection::ProcessSelection(int MouseState, KeyResult KeyState, int ElementHovered, float xMouse, float yMouse)
//{
//	this->xMouse = xMouse;
//	this->yMouse = yMouse;
//	//GetElementHovered();
//	this->ElementHovered = ElementHovered;
//
//	//if GUI_MOUSERIGHT_PRESSED
//	//BlueSelector
//	//Only Activate the blue selector when there isnt any Element hovered
//	if (MouseState == GUI_MOUSERIGHT_PRESSED)
//	{
//			TypeSelected = SELECTION_GROUP;
//			//Create the Blue MultiSelector & manage it
//			UpdateSelector();
//			//Find all Elements within the Selector
//			LocateSelections();
//			//Highlight the Elements selected 
//			HighlightSelections();
//			//return the ID's of all Elements highlighted
//			cout << "BlueSelector Loaded " << endl;
//	}
//	else
//	{
//		//Proceed if there is an active BlueSelector
//		if (SelectorActive == true)
//		{
//			//Delete the BlueSelector
//			DeleteSelector();
//		}
//	}
//
//	//Select Element (no movement)
//	//Only Activate the Element if there is an Element hovered
//	if (MouseState == GUI_MOUSERIGHT_CLICKED && KeyState.Shift == false && KeyState.Ctrl == false && KeyState.Alt == false && ElementHovered != -1 || SkipToElement == true)
//	{
//		//New Selection
//		if (SelectionCount == 0)
//		{
//			cout << "ElementHovered " << ElementHovered << endl;
//			LoadType(TYPE_Element);
//			HighlightSelections();
//			cout << "ElementType Loaded " << endl;
//			SkipToElement = false;
//		}
//		//terminate active selection
//		else
//		{
//			DeHighlightElementNEW();
//			ResetSelections();
//			SkipToElement = true;
//			return Selections;
//		}
//		
//	}
//
//	//Select Text or Grid
//	//OnlyActivate if there is an Element hovered and that Element actual is a grid or text
//	if (MouseState == GUI_MOUSERIGHT_CLICKED && KeyState.Shift == true && KeyState.Ctrl == false && KeyState.Alt == false && ElementHovered != -1 || SkipToGroup == true)
//	{
//		//New Selection
//	if (SelectionCount == 0)
//	{
//			int Type = FindType();
//
//			cout << "I've gone in tghe right way" << endl;
//			cout << Type << endl;
//			Element* Buffer = SelectorPage->GetElement(ElementHovered);
//			if (Type == TYPE_GRID || Type == TYPE_TEXT || Buffer->PartOfGroup == true)
//			{
//				LoadType(Type);
//				HighlightSelections();
//				cout << Type << " Loaded  1 = Grid 2 = Text" << endl;
//				//cout << Selections[0] << Selections[1] << Selections[2] << endl;
//				cout << SelectionCount << endl;
//				SkipToGroup = false;
//			}
//		}
//		else
//		{
//			DeHighlightElementNEW();
//			ResetSelections();
//			SkipToGroup = true;
//			return Selections;
//		}
//
//	}
//
//	if (this->OverrideSelect == true)
//	{
//		cout << " FORCE SELECT " << endl;
//		ForceSelect(this->ForceType, this->ForceElement);
//		return Selections;
//	}
//
//	//If GUI_MOUSERIGHT_CLICKED && Ctrl
//	//highlight it is select but does not move
//	//Return Grid or text
//
//	//PrintSelectionSheet();
//	return Selections;
//}
//
//void Selection::ForceSelect(int Type, int Element)
//{
//	//New Selection
//	if (SelectionCount == 0)
//	{
//		cout << "ElementHovered " << ElementHovered << endl;
//		LoadType(Type, Element);
//		HighlightSelections();
//		cout << "ElementType Loaded " << endl;
//		this->OverrideSelect = false;
//		this->ForceElement = -1;
//		this->ForceType = -1;
//	}
//	//terminate active selection
//	else
//	{
//		DeHighlightElementNEW();
//		ResetSelections();
//		this->OverrideSelect = true;
//	}
//
//}
//
////OFFSET SAFE
//void Selection::AddSelection(int ElementSelected)
//{
//	
//	// + 1 so that when the highlight is inserted we are clear that we want to modify the selected Element not the highlight
//	Selections[SelectionCount] = ElementSelected; //ID reference
//	SelectionCount++;
//	cout << "Selection Added" << "(" << SelectionCount << ")" << endl;
//}
//
//void Selection::GetElementHovered()
//{
//	this->ElementHovered = SelectorPage->FindElement(this->xMouse, this->yMouse, false);
//}
//
//void Selection::HighlightSelections()
//{
//	if (SelectionCount > 0)
//	{
//		for (int i = SelectionCount; i >= 0; i--)
//		{
//			if (Selections[i] != -1)
//			{
//				
//				HighlightSelection(i);	//Selections <- Pointer
//				cout << Selections[0] << " , " << Selections[1] << " , " << Selections[2] << " , " << Selections[3] << " , " << Selections[4] << " , " << Selections[5] << endl;
//			}
//		}
//	}
//}
//
////Which Selection we want to highlight
//void Selection::HighlightSelection(int SelectionSpot)
//{
//	int ElementUsing = Selections[SelectionSpot];
//	if (ElementUsing == -1) { cout << "Tried To Higlight but was -1" << endl; return; };
//	cout << "ElementUsing " << ElementUsing << endl;
//	Element* Element = SelectorPage->GetElement(Selections[SelectionSpot]);
//	//if the Element is not already highlighted
//	if (Element->Highlighted == false)
//	{
//		Element Highlight;
//		Highlight.Position = { Element->Position[0] - 0.00166, Element->Position[1] + 0.0033 };
//		Highlight.Size     = Element->HighlightSize;
//		Highlight.Color    = Element->HighlightColor;
//		Highlight.Highlighted = true;
//		Highlight.ElementisHighlight = true;
//	
//		Element->Highlighted = true;
//		//Update Element
//		this->SelectorPage->ChangeHighlight(ElementUsing, true);
//		//MakeHighlight
//		this->SelectorPage->InsertElement(ElementUsing, 1, Highlight, false);
//
//		//Selection-Number += ContainerSpot + 1
//		Selections[SelectionSpot] += SelectionSpot + 1;
//	
//		//When the ID was input into selections, it added one because it will be offset by one when we insert hihglihgt
//		//however, the Element hasnt been inserted yet so we have to backtrack - 1
//	}
//	
//}
//
////OFFSET SAFE
//void Selection::HighlightElement(int Selection, bool Centered)
//{
//	if (Selection == -1) return;
//	cout << "Element Highlighted" << endl;
//	Element* Element = SelectorPage->GetElement(Selection);
//	//if the Element is not already highlighted
//	if (Element->Highlighted == false)
//	{
//		Element Highlight;
//		Highlight.Position = { Element->Position[0] - 0.006, Element->Position[1] + 0.0125 };
//		Highlight.Size = Element->HighlightSize;
//		Highlight.Color = Element->HighlightColor;
//		Highlight.Highlighted = true;
//		Highlight.ElementisHighlight = true;
//
//		Element->Highlighted = true;
//		//Update Element
//		this->SelectorPage->ChangeHighlight(Selection, true);
//		//MakeHighlight
//		this->SelectorPage->InsertElement(Selection, 1, Highlight, Centered);
//		this->SelectorPage->LoadThisPage();
//
//		//When the ID was input into selections, it added one because it will be offset by one when we insert hihglihgt
//		//however, the Element hasnt been inserted yet so we have to backtrack - 1
//	}
//
//}
//
//void Selection::DeHighlightSelections()
//{
//	for (int i = 0; i < SelectionCount; i++)
//	{
//		if (Selections[i] != -1)
//		{
//				DeHighlightElement(Selections[i]);	
//		}
//	}
//	SelectorPage->LoadThisPage();
//}
//
////dehighlight all Elements
//void Selection::DeHighlightElementNEW()
//{
//	for (int i = SelectorPage->ShapeContainer.CurrentContainerAmount; i >= 0; i--)
//	{
//		Element* Element = SelectorPage->GetElement(i);
//		//if (Element == nullptr) break;
//		if (Element->ElementisHighlight == true && Element->Color == Element->HighlightColor)
//		{
//			this->SelectorPage->ChangeHighlight(i + 1, false);
//			this->SelectorPage->DeleteElementArray(i, 1);
//		}
//	}
//	cout << "Finished" << endl;
//}
//
//void Selection::DeHighlightElement(int Selection)
//{
//	if (Selection == -1) return;
//	Element* Element = SelectorPage->GetElement(Selection);
//	Element* Highlight = SelectorPage->GetElement(Selection - 1);
//	//only dehilight if the Element is highlighted
//	if (Element->Highlighted == true && Highlight->Color == Element->HighlightColor)
//	{
//		this->SelectorPage->ChangeHighlight(Selection, false);
//		this->SelectorPage->DeleteElementArray(Selection - 1, 1);
//		//this->SelectorPage->LoadThisPage();
//	}
//}
//
//void Selection::ResetSelections()
//{
//	for (int i = 0; i < 100; i++)
//	{
//		Selections[i] = -1;
//	}
//	this->SelectionCount = 0;
//}
//
//void Selection::CreateSelector()
//{
//	//Draw the Blue MultiSelector
//
//}
//
//
////Manage MultiSelector 
//void Selection::UpdateSelector()
//{
//	//No Selector
//	if (SelectorActive != true)
//	{
//		//Reset previous Selections
//		DeHighlightElementNEW();
//		ResetSelections();
//		//Create BlueSelector
//		BlueSelector.Position = { xMouse, yMouse};
//	    BlueSelector.Size = {  0.0, 0.0 };
//	    BlueSelector.Color = { 0.0, 0.3, 1.0, 0.4 };
//	    BlueSelector.Highlighted = false;
//		BlueSelector.MouseAccess = false; //This is just so that the selector can't be selected
//
//		//Load BlueSelector
//		this->SelectorPage->AddElement(BlueSelector, false, false);
//
//		SelectorActive = true;
//	}
//	//Yes current selector
//	else
//	{
//		//Update and load BlueSelector
//		BlueSelector.Size = { xMouse - BlueSelector.Position[0], -yMouse + BlueSelector.Position[1]};
//		SelectorPage->ChangeElementSize(SelectorPage->ShapeContainer.CurrentContainerAmount - 1, BlueSelector.Size, 'B' , false, false);
//	}
//}
//
////Finding MultiSelect Elements
//void Selection::LocateSelections()
//{
//	//DeHighlightElementNEW(-1000);
//	ResetSelections();
//
//	//cout << "-------------------------------" << endl;
//	//cout << "LocatingSelections.... " << endl;
//	//cout << "-------------------------------" << endl;
//
//	   // this->SelectionCount = 0;
//		//loop Setup
//		int LayerStart = this->SelectorPage->Layer[CurrentLayer].LayerID;
//		int LayerEnd = ((this->SelectorPage->ShapeContainer.CurrentContainerAmount + LayerStart) - 1);
//		 //	cout << "ElementCount: " << this->SelectorPage->ShapeContainer.CurrentContainerAmount - 1 << endl;
//			//cout << "Layer Start: "<< LayerStart << endl;
//			//cout << "Layer End: "<< LayerEnd << endl;
//			//search for Element backwards to always get the Element furthest to the user screen
//			//and skip the MultiSelect Element
//		for (int i = LayerStart; i < LayerEnd; i++)
//		{
//			Element* TestElement = this->SelectorPage->ShapeContainer.RetrieveData(i);
//			TestElement->ElementID = i;
//
//			//cout << "LoopCount " << i << endl;
//			int Result = CompareSelector(TestElement);
//
//
//	        if (Result != -1 && TestElement->Color != TestElement->HighlightColor)
//			{
//				Selections[SelectionCount] = i;
//				SelectionCount++;
//			}
//		}
//
//		cout << Selections[0] << " , " << Selections[1] << " , " << Selections[2] << " , " << Selections[3] << " , " << Selections[4] << " , " << Selections[5] << endl;
//		
//}
//
//void Selection::DeleteSelector()
//{
//	SelectorPage->DeleteElementArray(SelectorPage->ShapeContainer.CurrentContainerAmount - 1, 1); //BlueSelector.ElementID
//	SelectorActive = false;
//}
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//int Selection::CompareSelector(Element* Result)
//{
//	//cout << "Comparing Selector.." << endl;
//	//cout << "--------------------" << endl;
//	
//	float BSL = 0.0;
//	float BSR = 0.0;
//	float BST = 0.0;
//	float BSB = 0.0;
//
//// Set of IF's determines which way the mouse is moving 
//	//Left Side
//	if (BlueSelector.Position[0] + BlueSelector.Size[0] > BlueSelector.Position[0] || BlueSelector.Size[0] == 0)
//	{
//		//Top Left (Default)
//		if (BlueSelector.Position[1] - BlueSelector.Size[1] < BlueSelector.Position[1] || BlueSelector.Size[0] == 0)
//		{
//			BSL = this->BlueSelector.Position[0];                        //Left
//			BSR = this->BlueSelector.Position[0] + BlueSelector.Size[0]; //Right
//			BST = this->BlueSelector.Position[1];                        //Top
//			BSB = this->BlueSelector.Position[1] - BlueSelector.Size[1]; //Bottom
//		}
//		//Bottom Left
//		if (BlueSelector.Position[1] - BlueSelector.Size[1] > BlueSelector.Position[1])
//		{
//			BSL = this->BlueSelector.Position[0];                        //Left
//			BSR = this->BlueSelector.Position[0] + BlueSelector.Size[0]; //Right
//			BST = this->BlueSelector.Position[1] - BlueSelector.Size[1]; //Top
//			BSB = this->BlueSelector.Position[1];                        //Bottom
//		}
//	}
//
//	//Right Side
//	if (BlueSelector.Position[0] + BlueSelector.Size[0] < BlueSelector.Position[0])
//	{
//		//Top Right
//		if (BlueSelector.Position[1] - BlueSelector.Size[1] < BlueSelector.Position[1])
//		{
//			BSL = this->BlueSelector.Position[0] + BlueSelector.Size[0]; //Left
//			BSR = this->BlueSelector.Position[0];                        //Right
//			BST = this->BlueSelector.Position[1];                        //Top
//			BSB = this->BlueSelector.Position[1] - BlueSelector.Size[1]; //Bottom
//		}
//
//		//Bottom Right
//		if (BlueSelector.Position[1] - BlueSelector.Size[1] > BlueSelector.Position[1])
//		{
//			
//			BSL = this->BlueSelector.Position[0] + BlueSelector.Size[0]; //Left
//			BSR = this->BlueSelector.Position[0];                        //Right
//			BST = this->BlueSelector.Position[1] - BlueSelector.Size[1]; //Top
//			BSB = this->BlueSelector.Position[1];                        //Bottom
//
//		}
//	}
//
//
//	bool xAxis1 = false;
//	bool yAxis1 = false;
//	bool xAxis2 = false;
//	bool yAxis2 = false;
//	
//
//	//These if's determine if a part of an Element is within the selector
//	//(1/2)
//	if (BSL > Result->Left && BSL < Result->Right) //Result->Right > BSL && Result->Right < BSR ) //) //) 
//	{
//		xAxis1 = true;
//		
//	}
//	//cout << "X1: " << xAxis << endl;
//
//	//(2/2)
//	if (BSR > Result->Left && BSR < Result->Right ) //Result->Left > BSL && Result->Left < BSR  ) //BSR > Result->Left && BSR < Result->Right)   //) 
//	{
//		xAxis1 = true;
//		
//	}
//	//cout << "X2: " << xAxis << endl;
//
//	//(1/2)
//	if (BST > Result->Bottom && BST < Result->Top )//Result->Top < BST && Result->Top > BSB) //  ) // ) 
//	{
//		yAxis1 = true;
//	}
//	//cout << "Y1: " << yAxis << endl;
//
//	//(2/2)
//	if (BSB > Result->Bottom && BSB < Result->Top ) //Result->Bottom < BST && Result->Bottom > BSB) // )
//	{
//		yAxis1 = true;
//		
//	}
//	//cout << "Y2: " << yAxis << endl;
//
//	//////////////////////////////////////////////////////////////////////////////////////
//		//(1/2)
//	if (Result->Right > BSL && Result->Right < BSR) 
//	{
//		xAxis2 = true;
//	}
//	//cout << "X1: " << xAxis << endl;
//
//	//(2/2)
//	if (Result->Left > BSL && Result->Left < BSR  ) 
//	{
//		xAxis2 = true;
//	}
//	//cout << "X2: " << xAxis << endl;
//
//	//(1/2)
//	if (Result->Top < BST && Result->Top > BSB) 
//	{
//		yAxis2 = true;
//	}
//	//cout << "Y1: " << yAxis << endl;
//
//	//(2/2)
//	if (Result->Bottom < BST && Result->Bottom > BSB) 
//	{
//		yAxis2 = true;
//	}
//
//
//	//Determines if the parts of Element found are due to being inside the Element
//	if (xAxis1 == true && yAxis1 == true)
//	{
//		//cout << "MATCH!!!!: " << Result->ElementID << endl;
//		return Result->ElementID;
//	}
//	if (xAxis2 == true && yAxis2 == true)
//	{
//		//cout << "MATCH!!!!: " << Result->ElementID << endl;
//		return Result->ElementID;
//	}
//	if (xAxis2 == true && yAxis1 == true)
//	{
//		//cout << "MATCH!!!!: " << Result->ElementID << endl;
//		return Result->ElementID;
//	}
//	if (xAxis1 == true && yAxis2 == true)
//	{
//		//cout << "MATCH!!!!: " << Result->ElementID << endl;
//		return Result->ElementID;
//	}
//
//
//	else
//	{
//		//cout << "NO MATCH " << Result->ElementID << endl;
//		return -1;
//	}
//}
//
//
//int Selection::FindElement(double xMouse, double yMouse, bool Print)
//{
//	if (CurrentLayer < 10)
//	{
//		int LayerStart = this->Layer[CurrentLayer].LayerID;
//		int LayerEnd = (this->Layer[CurrentLayer].ElementCount + LayerStart);
//		//search for Element backwards to always get the Element furthest to the user screen
//		for (int i = LayerEnd; i >= LayerStart; i--)
//		{
//			Element* Result = SelectorPage->ShapeContainer.RetrieveData(i);
//			Result->ElementID = i;
//
//			if (xMouse < Result->Right && xMouse >  Result->Left&& yMouse < Result->Top && yMouse >  Result->Bottom)
//			{
//				if (Print == true)
//				{
//					cout << "found" << endl;
//					cout << i << endl;
//					LastElementHovered = i;
//				}
//				return i;
//			}
//
//		}
//	}
//	return -1;
//
//}
//
//
//int Selection::FindType()
//{
//	//Find Type
//    if (this->ElementHovered == -1) { cout << "LoadFindType couldn't find type because Element hovered was -1" << endl; return - 1; };
//
//	Element* TypeBuffer = SelectorPage->GetElement(this->ElementHovered);
//    return TypeBuffer->ElementType;
//}
//
//void Selection::LoadType(int Type)
//{
//	//Retrieve Data
//	Element* TypeStart = SelectorPage->GetElement(this->ElementHovered);
//
//	//LoadType
//	if (Type == TYPE_Element)
//	{
//		//Load 
//		AddSelection(ElementHovered);
//		TypeSelected = Type;
//	}
//	if (Type == TYPE_GRID)
//	{
//		//Load
//		for (int i = TypeStart->GroupStart; i < TypeStart->GroupStart + TypeStart->GroupCount; i++)
//		{
//			cout << "i" << i << endl;
//			AddSelection(i);
//			TypeStart++;
//			TypeStart->GridHighlighted = true;
//		}
//
//		TypeSelected = Type;
//	}
//	if (Type == TYPE_TEXT)
//	{
//		//Load
//		for (int i = TypeStart->GroupStart; i < TypeStart->GroupStart + TypeStart->GroupCount; i++)
//		{
//			AddSelection(i);
//		}
//
//		TypeSelected = Type;
//	}
//
//}
//
//void Selection::LoadType(int Type, int GroupElement)
//{
//	//Retrieve Data
//	Element* TypeBuffer = SelectorPage->GetElement(GroupElement);
//
//	//LoadType
//	if (Type == TYPE_Element)
//	{
//		//Load 
//		AddSelection(ElementHovered);
//		TypeSelected = Type;
//	}
//	if (Type == TYPE_GRID)
//	{
//		//Load
//		for (int i = TypeBuffer->GroupStart; i < TypeBuffer->GroupStart + TypeBuffer->GroupCount; i++)
//		{
//			cout << "i" << i << endl;
//			AddSelection(i);
//		}
//
//		TypeSelected = Type;
//	}
//	if (Type == TYPE_TEXT)
//	{
//		//Load
//		for (int i = TypeBuffer->GroupStart; i < TypeBuffer->GroupStart + TypeBuffer->GroupCount; i++)
//		{
//			AddSelection(i);
//		}
//
//		TypeSelected = Type;
//	}
//
//}