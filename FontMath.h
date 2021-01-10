#ifndef FONTMATH
#define FONTMATH


#include <iostream>
#include "Dependencies/GLEW/include/GL/glew.h"
#include "Dependencies/GLFW/include/GLFW/glfw3.h"
#include "Dependencies/glm/glm/GLM.HPP"
#include "Dependencies/glm/glm/gtc/type_ptr.hpp"
#include "Dependencies/glm/glm/gtc/matrix_transform.hpp"
#include "TextSpecification.h"
#include "Character.h"
//#include "UIElement.h"

using namespace std;

struct FontVertex
{
	glm::vec2 Position = { 0.0, 0.0};
	glm::vec2 TexCoords = { 0.0, 0.0 };
	glm::vec4 Color = { 0.0, 0.0, 0.0, 0.0 };
	float TexIndex = 0.0;
	glm::vec2 CentralPoint = {0.0, 0.0};
	float GUIAction = 0.0;

};

struct CharTexCoords
{
	glm::vec2 TopLeft;
	glm::vec2 BottomLeft;
	glm::vec2 TopRight;
	glm::vec2 BottomRight;

};

struct CharVertices
{
	glm::vec2 TopLeft;
	glm::vec2 BottomLeft;
	glm::vec2 TopRight;
	glm::vec2 BottomRight;

};
class FontMath
{

public:
	//can't decifer 'Character' for whatever reason

	glm::vec2 AdvanceCursor(Character character, float FontSize, glm::vec2 Pos, float CharSpacing);

	glm::vec2 NextLine(glm::vec2 StartPosition, Character Character, glm::vec2 CurrentPosition, float FontSize, float Spacing, float xStart);

	glm::vec2 GetCharacterPosition(Character Character, glm::vec2 Pos, float FontSize, bool LineStart);

	CharTexCoords GetCharacterTexCoords(Character Character);
	
	glm::vec2 GetCharacterSize(Character Character, glm::vec2 CharPosition, int SCR_Height, int SCR_Width, float FontSize);

	//FontVertex& SetTopRight(const Element& Element, Character Character, FontVertex& Vertex);
	//
	//FontVertex& SetBottomRight(const Element& Element, Character Character, FontVertex& Vertex);
	//
	//FontVertex& SetTopLeft(const Element& Element, Character Character, FontVertex& Vertex);
	//
	//FontVertex& SetBottomLeft(const Element& Element, Character Character, FontVertex& Vertex);
		

private:


};

#endif