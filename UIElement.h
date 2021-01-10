#ifndef ELEMENT
#define ELEMENT

#include <iostream>
//#include "Maths.h"
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
//
//using namespace std;
//
//class Element
//{
//
//public:
//
//	glm::vec2 Position;
//	glm::vec2 Size;
//	glm::vec4 Color;
//	int ActiveTexture;
//	int ElementID;
//	int PageID;
//	Element* Address;
//
//	bool PartOfGroup;
//	int GroupStart;
//	int GroupOffset;
//	bool GridCentered;
//	bool GridHighlighted;
//
//
//	
//	int Layer;
//
//	float Top;
//	float Bottom;
//	float Left;
//	float Right;
//
//	bool MouseAccess;
//	bool ElementisHighlight;
//	bool Highlighted;
//	glm::vec2 HighlightPosition;
//	glm::vec2 HighlightSize;
//	glm::vec4 HighlightColor;
//
//	int Action;
//	string Text;
//
//	//Grid Details (if applicable)
//	glm::vec2 GridXYShapePerRow;
//	glm::vec2 GridShapeSize;
//
//	//ElementGroup Details
//	Element* ElementGroupStart;
//	int GroupCount;
//	Element* NextElementGroup;
//	glm::vec2 ShapeGroupPosition;
//	glm::vec2 ShapeGroupSize;
//	glm::vec4 ShapeGroupColor;
//
//	bool Centered;
//	bool Higlighted;
//	int ElementType;
//
//	//PageGroup Details
//
//
//
//
//	 Element(glm::vec2 Position, glm::vec2 Size);
//	 Element(glm::vec2 Position, glm::vec2 Size, bool MouseAccess, bool ElementIsHighlighted);
//	 Element();
//	 ~Element();
//
//	 //Element Editing
//	 Element* IncreaseSize(Element* Element, glm::vec2 SizeFactor);
//	 Element* DecreaseSize(Element* Element, glm::vec2 SizeFactor);
//	void UpdatePosition(glm::vec2 NewPosition);
//	void UpdateSize(glm::vec2 NewSize);
//	void ChangeColor(glm::vec4 Color);
//	void ChangeTexture(int ActTexture);
//
//	Element* ElementPosToMousePos(Element* Element, glm::vec2 MousePosition, bool Centered);
//	
//
//
//private:
//
//
//
//};
//
#endif 