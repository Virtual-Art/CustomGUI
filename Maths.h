#ifndef MATHS
#define MATHS

#include <iostream>
#include <Math.h>
#include "Dependencies/GLEW/include/GL/glew.h"
#include "Dependencies/GLFW/include/GLFW/glfw3.h"
#include "Dependencies/glm/glm/GLM.HPP"
#include "Dependencies/glm/glm/gtc/type_ptr.hpp"
#include "Dependencies/glm/glm/gtc/matrix_transform.hpp"
//#include "UIElement.h"
//#include "Page.h"

struct Vertex
{
	glm::vec2 Position = { 0.0, 0.0};
	glm::vec2 TexCoords = { 0.0, 0.0};
	glm::vec4 Color = { 0.0, 0.0, 0.0, 0.0 };
	float TexIndex = 0.0;
	glm::vec2 CentralPoint = {0.0, 0.0};
	int GUIAction = 0;
};
using namespace std;

class Maths
{
public:
	/*glm::mat4 Scale(glm::vec3 Scale);

	glm::mat4 Translate(glm::vec3 Translate);

	glm::mat4 Rotate(glm::vec3 Rotate);*/

	//Vertex& SetTopRight(const Element& Element, Vertex& Vertex);
	//Vertex& SetBottomRight(const Element& Element, Vertex& Vertex);
	//Vertex& SetTopLeft(const Element& Element, Vertex& Vertex);
	//Vertex& SetBottomLeft(const Element& Element, Vertex& Vertex);

	glm::mat4 CreateTransformationMatrix(glm::vec3 Translation, float Rx, float Ry, float Rz, glm::vec3 Scale);

    //ElementVertices GetElementVertices(glm::vec3 ElementPosition, float xSize, float ySize, bool Centered);

	//ElementTexCoords GetBasicTexCoords();

	glm::vec2 GridShapeSize(glm::vec2 ShapeGroupSize, glm::vec2 XYElementsPerRow, glm::vec2 ElementSize);
	glm::vec2 GridElementPosition(glm::vec2 ShapeGroupPosition, glm::vec2 ShapeGroupSize, glm::vec2 XYElementsPerRow, glm::vec2 XYLoop, bool Centered);


	glm::vec2 TopLeftToCenter(glm::vec2 Position, glm::vec2 Size);
	glm::vec2 CenterToTopLeft(glm::vec2 Position, glm::vec2 Size);


	float sinOscillation(float Time, float Size, float Speed, float OscillationPosition);

	float cosOscillation(float Time, float Delay, float Size, float SecondsPerRevolution, float OscillationPosition);
	float cosOscillation(float Time, float Size, int RevolutionsPerSecond, float OscillationPosition);
 
	float Exponential(float Time, float StartOffset, float Speed, float Power, float Size, float AxisOfSymmetry);

private:


};

#endif