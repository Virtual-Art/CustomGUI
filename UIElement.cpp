//#include "UIElement.h"
//
//
//
//Element::Element(glm::vec2 Position, glm::vec2 Size)
//{
//	this->Size = Size;
//	this->Position = Position;
//	this->Color = { 1.0, 1.0, 1.0, 1.0 };
//	this->ActiveTexture = 0;
//	this->PageID = 0;
//	this->ElementID = 0;
//	this->Address = 0;
//	this->Top = (Position.y - Size.y);
//	this->Bottom = (Position.y);
//	this->Left = (Position.x);
//	this->Right = (Position.x + Size.x);
//
//	this->MouseAccess = true;
//	this->ElementisHighlight = false;
//	this->HighlightPosition = this->Position;
//	this->HighlightSize = { this->Size[0] + 0.0135, this->Size[1] + 0.025 };
//	this->HighlightColor = { 0.0, 0.7156, 0.0, 1.0 };
//	this->Highlighted = false;
//
//	this->PartOfGroup = false;
//	this->GroupStart = -1;
//	this->GroupCount = -1;
//	this->GroupOffset = -1;
//	this->GridXYShapePerRow = { -1, -1 };
//	this->ShapeGroupSize = { -1, -1 };
//	this->ShapeGroupPosition = { -100, -100 };
//	this->GridShapeSize = {-1, -1}; //as a percentage inside the grid
//	this->ShapeGroupColor = { -1, -1, -1, -1};
//	this->GridCentered = 0;
//	this->GridHighlighted = 0;
//	this->Action = 0;
//	this->Text = "Text";
//	this->ElementType = 0;
//}
//
//Element::Element(glm::vec2 Position, glm::vec2 Size, bool MouseAccess, bool ElementIsHighlight)
//{
//	this->Size = Size;
//	this->Position = Position;
//	this->Color = { 0.0, 0.0, 0.0, 0.0 };
//	this->ActiveTexture = 0;
//	this->PageID = 0;
//	this->ElementID = 0;
//	this->Address = 0;
//	if (MouseAccess == true)
//	{
//		this->Top = (Position.y - Size.y);
//		this->Bottom = (Position.y);
//		this->Left = (Position.x);
//		this->Right = (Position.x + Size.x);
//	}
//	else
//	{
//		this->Top = 3.0;
//		this->Bottom = 3.0;
//		this->Left = -3.0;
//		this->Right = -3.0;
//	}
//
//	this->MouseAccess = false;
//	this->ElementisHighlight = ElementIsHighlight;
//	this->HighlightPosition = this->Position;
//	this->HighlightSize = { this->Size[0] + 0.0135, this->Size[1] + 0.025 };
//	this->HighlightColor = { 0.0, 0.7156, 0.0, 1.0 };
//	this->Highlighted = false;
//
//	this->PartOfGroup = false;
//	this->GroupStart = -1;
//	this->GroupCount = -1;
//	this->GroupOffset = -1;
//	this->GridXYShapePerRow = { -1, -1 };
//	this->ShapeGroupSize = { -1, -1 };
//	this->ShapeGroupPosition = { -100, -100 };
//	this->GridShapeSize = { -1, -1 }; //as a percentage inside the grid
//	this->ShapeGroupColor = { -1, -1, -1, -1 };
//	this->GridCentered = 0;
//	this->GridHighlighted = 0;
//	this->Action = 0;
//	this->Text = "Text";
//	this->ElementType = 0;
//}
//
//Element::Element()
//{
//	this->Size = { 0,0 };
//	this->Position = {0, 0};
//	this->Color = { 1.0, 1.0, 1.0, 1.0 };
//	this->ActiveTexture = 0;
//	this->ElementID = 0;
//	this->Address = 0;
//	this->Top = (Position.y - Size.y);
//	this->Bottom = (Position.y);
//	this->Left = (Position.x);
//	this->Right = (Position.x + Size.x);
//
//	this->MouseAccess = true;
//	this->ElementisHighlight = false;
//	this->HighlightPosition = this->Position;
//	this->HighlightSize = { this->Size[0] + 0.0135, this->Size[1] + 0.025 };
//	this->HighlightColor = { 0.0, 0.7156, 0.0, 1.0 };
//	this->Highlighted = false;
//
//	this->PartOfGroup = false;
//	this->GroupStart = -1;
//	this->GroupCount = -1;
//	this->GroupOffset = -1;
//	this->GridXYShapePerRow = { -1, -1 };
//	this->ShapeGroupSize = { -1, -1 };
//	this->ShapeGroupPosition = { -100, -100 };
//	this->GridShapeSize = { -1, -1 }; //as a percentage inside the grid
//	this->ShapeGroupColor = { -1, -1, -1, -1 };
//	this->GridCentered = 0;
//	this->GridHighlighted = 0;
//	this->Action = 0; 
//	this->Text = "Text";
//	this->ElementType = 0;
//}
//
//Element::~Element()
//{
//	
//}
//
//
//
//bool MouseCheck(float xPos, float yPos, Element Element)
//{
//	return false;
//}
//
//
//
//void SecondElementEditor()
//{
//
//}
//
//Element* Element::IncreaseSize(Element* Element, glm::vec2 SizeFactor)
//{
//	Element->Size += SizeFactor;
//	return Element;
//}
//
//Element* Element::DecreaseSize(Element* Element, glm::vec2 SizeFactor)
//{
//	Element->Size -= SizeFactor;
//	return Element;
//}
//
//void Element::UpdatePosition( glm::vec2 NewPosition)
//{
//	this->Position = NewPosition;
//
//	if (MouseAccess == true)
//	{
//		this->Top = (NewPosition.y);
//		this->Bottom = (NewPosition.y - this->Size[1]);
//		this->Left = (NewPosition.x);
//		this->Right = (NewPosition.x + this->Size[0]);
//	}
//	else
//	{
//		this->Top = 3.0;
//		this->Bottom = 3.0;
//		this->Left = -3.0;
//		this->Right = -3.0;
//	}
//
//	//this->MouseAccess = true;
//	this->HighlightPosition = NewPosition;
//	this->HighlightSize = { this->Size[0] + 0.0032, this->Size[1] + 0.0066 };
//	this->HighlightColor = { 0.0, 0.7156, 0.0, 1.0 };
//}
//
//void Element::UpdateSize(glm::vec2 NewSize)
//{
//
//	this->Size = NewSize;
//	if (MouseAccess == true)
//	{
//		this->Top = (this->Position[1]);
//		this->Bottom = (this->Position[1] - this->Size[1]);
//		this->Left = (this->Position[0]);
//		this->Right = (this->Position[0] + this->Size[0]);
//	}
//	else
//	{
//		this->Top = 3.0;
//		this->Bottom = 3.0;
//		this->Left = -3.0;
//		this->Right = -3.0;
//	}
//
//	this->MouseAccess = MouseAccess;
//	this->HighlightPosition = this->Position;
//	this->HighlightSize = { this->Size[0] + 0.0135, this->Size[1] + 0.025 };
//	this->HighlightColor = { 0.0, 0.7156, 0.0, 1.0 };
//}
//
//
//
//Element* Element::ElementPosToMousePos(Element* Element, glm::vec2 MousePosition, bool Centered)
//{
//	if (Centered == true)
//	{
//		MousePosition[0] -= Element->Size[0] / 2;
//		MousePosition[1] += Element->Size[1] / 2;
//	}
//	Element->Position = MousePosition;
//	return Element;
//}
//void Element::ChangeColor(glm::vec4 Color)
//{
//	this->Color = {Color};
//
//}
//
//void Element::ChangeTexture( int ActTexture)
//{
//	this->ActiveTexture = ActTexture;
//}
//
//