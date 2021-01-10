#ifndef TEXTSPECIFICATION
#define TEXTSPECIFICATION

#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

class TextSpecification
{
public:

	bool Centered;
	string Text;
	string FontFile;
	float FontSize;
	float CharSpacing;
	float LineSpacing;
	glm::vec2 Position;
	glm::vec2 Size;
	glm::vec4 Color;
	float LineLength;
	glm::vec2 CursorPosition;
	float FontSlot;
	bool MouseAccess;
	bool List;


	int Start;
	int Count;
	
	//full specs
	TextSpecification(string Text, string FontFilePath, float xPos, float yPos, float FontSize, float CharSpacing, glm::vec4 Color, float MaxLine, bool Centered, float LineSpacing);
   
	TextSpecification(string Text, string FontFilePath, float xPos, float yPos, float FontSize, glm::vec4 Color, bool List, float Spacing, float Maxline);

	TextSpecification(string Text, float xPos, float yPos, float FontSize, float Maxline);

	//Newest
	TextSpecification(string Text, glm::vec2 Position, bool List, glm::vec4 Color);
	//TextBox
	TextSpecification(string Text, string FontFilePath, glm::vec2 Position, glm::vec2 Size, float FontSize, glm::vec4 Color, unsigned int FontSlot, float CharSpacing, bool MouseAccess, bool List, bool Centered);


};

#endif 