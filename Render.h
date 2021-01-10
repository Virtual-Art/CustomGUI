#ifndef RENDER
#define RENDER

#include <iostream>
#include <string>
#include <Math.h>
#include <array>
#include "RawModel.h"
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "RawTexture.h"
#include "FontMath.h"
#include "Maths.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "character.h"
#include "UIElement.h"
#include "Page.h"

using namespace std;

class Render
{

public:
	//RawTexture T_White;

	//
	//
	//void RenderTexture(RawTexture RawTexture, RawModel RawModel);
	//
	//void render(RawModel RawModel);

	//void RenderText(TextSpecification TextSpecs);


	//void TextInit(ShaderProgram ShaderProgram, RawTexture RawTexture);
	///void QuadInit(ShaderProgram ShaderProgram, RawTexture RawTexture);

	//void AddTextToBatch(TextSpecification TextSpecs);

	//void StoreChar(const glm::vec3& Position, CharVertices& Vertices, CharTexCoords& TexCoords, glm::vec4& Color);

	//void ReplaceQuad(int QuadIndex, QuadVertices& Vertices, QuadTexCoords& TexCoords, glm::vec4& Color, float ActiveTexture);
	void DrawPage(ShaderProgram ShaderProgram, RawTexture RawTexture1, RawTexture RawTexture2, RawTexture RawTexture3, Page& Page);
	//void DrawCircle(ShaderProgram ShaderProgram, Page Page);
	//void DrawTText(ShaderProgram ShaderProgram, RawTexture RawTexture);




	//void BeginTextBatch();
	//
	//void LoadTextBatch();
	//
	//void BeginQuadBatch();
	//
	//void LoadQuadBatch();
	//
	//void UpdateBatchQuad(int Quad);
	//
	//
	//void DrawNewTextBatch();
	//void DrawNewQuadBatch();
	//
	//
	//void ShutDown();
	//
	//
	//void ReplaceQuadData(int QuadIndex,float xPos, float yPos, float xSize, float ySize, glm::vec4 Color, int ActiveTexture);
	//
	//
	//
	//void StoreElementGrid(int xElementPerRow, int yElementPerRow, float xShapeGroupSize, float yShapeGroupSize, float xGridPos, float yGridPos, float xBorderSize, float yBorderSize ,float xSpacing, float ySpacing, glm::vec4 Color);


private:
	int SCR_Height = 600;
	int SCR_Width = 1200;

};

#endif