//#ifndef SELECTION
//#define SELECTION
//
//#include <iostream>
//#include "Page.h"
//#include "Container.h"
//#include "MouseManager.h"
//#include <GL/glew.h>
//#include "GLFW/glfw3.h"
//#include <glm/GLM.HPP>
//#include <glm/gtc/type_ptr.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include "KeyboardManager.h"
//
//using namespace std;
//
//#define SELECTION_Element 0
//#define SELECTION_GRID 1
//#define SELECTION_TEXT 2
//#define SELECTION_GROUP 3
//
//class Selection : public Page
//{
//public:
//
//	int MaxSelectionCount;
//	int SelectionCount;
//	int* Selections;
//	int SelectionContainer[100];
//	int ElementHovered;
//	int TypeSelected;
//	bool SelectorActive;
//	bool SingleSelection;
//	float xMouse;
//	float yMouse;
//	bool SkipToElement;
//	bool SkipToGroup;
//	bool OverrideSelect;
//	int ForceElement;
//	int ForceType;
//	Element BlueSelector;
//	Page* SelectorPage;
//
//	Selection(Page& Page);
//	int* ProcessSelection(int MouseState, KeyResult KeyState, int ElementHovered, float xMouse, float yMouse);
//	void ForceSelect(int Type, int Element);
//	void LoadType(int Type);
//	void LoadType(int Type, int Element);
//	
//	void AddSelection(int Selected);
//	void GetElementHovered();
//	void HighlightSelections();
//	void DeHighlightSelections();
//	void UpdateSelector();
//
//	void DeHighlightElement(int Selections);
//	void DeHighlightElementNEW();
//	void HighlightSelection(int SelectionSpot);
//	void HighlightElement(int Selection, bool Centered);
//	void ResetSelections();
//	void CreateSelector();
//
//	void LocateSelections();
//	int CompareSelector(Element* Result);
//	void DeleteSelector();
//	int FindElement(double xMouse, double yMouse, bool Print);
//
//
//	void PrintSelectionSheet()
//	{
//		cout << "------------------Selection Sheet---------------------" << endl;
//		for (int i = 0; i < SelectionCount; i++)
//		{
//			cout << "Selection(" << i << "): " << Selections[i] << endl;
//		}
//	}
//
//	void PrintSelectionSheet(int Amount)
//	{
//		cout << "------------------Selection Sheet---------------------" << endl;
//		for (int i = 0; i < Amount; i++)
//		{
//			cout << "Selection(" << i << "): " << Selections[i] << endl;
//		}
//	}
//
//	void PrintSelection(int Selection)
//	{
//		cout << "Selection(" << Selection << "): " << Selections[Selection] << endl;
//	}
//
//private:
//
//	int GetBlueID()
//	{
//		this->BlueSelector.ElementID = this->SelectorPage->ShapeContainer.CurrentContainerAmount - 1;
//		return BlueSelector.ElementID;
//	}
//
//	Element& GetBlueSelector()
//	{
//		this->BlueSelector.ElementID = this->SelectorPage->ShapeContainer.CurrentContainerAmount - 1;
//		return this->BlueSelector;
//	}
//
//	int FindType();
//
//	
//
//
//};
//
//
//#endif
//