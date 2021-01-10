#ifndef LOADER
#define LOADER

#include <iostream>
#include "Dependencies/GLEW/include/GL/glew.h"
#include "Dependencies/GLFW/include/GLFW/glfw3.h"
#include "Dependencies/glm/glm/GLM.HPP"
#include "Dependencies/glm/glm/gtc/type_ptr.hpp"
#include "Dependencies/glm/glm/gtc/matrix_transform.hpp"
#include "Maths.h"
#include "Page.h"


using namespace std;



class Loader 
{

public:
	int TestCount;

	//void StoreElement(Page &Page, ElementVertices& Vertices, ElementTexCoords& TexCoords, glm::vec4& Color, float ActiveTexture);


	void LoadPage(Page &Page);

	//void ElementUpload(Page Page, Element Element);

	//void DrawNewBatch(Page Page);

	//void AddElement(Element* Element, Page &Page, bool Centered);
	//void EditElement(Element* Element, Page& Page, int ElementNumber, bool Centered);

	//void AddElementGrid(Page& Page, glm::vec2 XYElementsPerRow, glm::vec2 ShapeGroupSize, glm::vec2 ShapeGroupPosition, glm::vec2 ElementSize, glm::vec4 Color, bool Centered);
	//void EditElementGrid(int GridElementStart, Page& Page, glm::vec2 XYElementsPerRow, glm::vec2 ShapeGroupSize, glm::vec2 ShapeGroupPosition, glm::vec2 ElementSize, glm::vec4 Color, bool Centered);

	//void ReplaceElement(Page Page, int ElementIndex, ElementVertices& Vertices, ElementTexCoords& TexCoords, glm::vec4& Color, float ActiveTexture);

	//void ElementIncrementor(Page &Page, bool Debug);

	//void AddElementGrid(Page& Page, glm::vec2 XYElementsPerRow, glm::vec2 ShapeGroupSize, glm::vec2 ShapeGroupPosition, glm::vec2 ElementSize, glm::vec4 Color, bool Centered);
	//void ReplaceElementGrid(Page& Page, int GridStart, glm::vec2 XYElementsPerRow, glm::vec2 ShapeGroupSize, glm::vec2 ShapeGroupPosition, glm::vec2 ElementSize, glm::vec4 Color, bool Centered);

	//void ReplaceElement(Page& Page, int ElementID, Element& NewElement, bool Centered);
	//
	//void AddElement(Page& Page, Element& Element, bool Centered);


private:

};

#endif