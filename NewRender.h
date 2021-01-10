#ifndef NEWRENDER
#define NEWRENDER

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

class NewRender
{
public:
	void Prepare(GLclampf Red, GLclampf Green, GLclampf Blue, GLclampf Opacity);
	void DrawPage(ShaderProgram ShaderProgram, RawTexture RawTexture1, RawTexture RawTexture2, RawTexture RawTexture3, Page Page);
	void DrawCircle(ShaderProgram ShaderProgram, Page Page)
	{
	  glUseProgram(ShaderProgram.ID);
	  glBindVertexArray(Page.VA);
	  glEnable(GL_ALPHA_TEST);
	  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	  glDrawElements(GL_TRIANGLE_FAN, Page.IndexContainer.CurrentContainerAmount - 1, GL_UNSIGNED_INT, 0);
	  glBindVertexArray(0);
    }
};


#endif