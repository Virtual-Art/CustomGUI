#ifndef NEWPAGE
#define NEWPAGE

#include <iostream>
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "MasterElement.h"
#include "ShaderProgram.h"

using namespace std;

class NewPage : public MasterElement
{
   public:

	   NewPage(llBookData* llBook, ShaderProgram* ShaderProgram);
	   
	   void InitiatePage(llBookData* llBook, ShaderProgram ShaderProgram);

	   void LoadGPU();

	   void DrawPage();

	   llPageData* CurrentllPage;
	   llBookData* CurrentBook;
	   ShaderProgram* CurrentShader;
};

#endif 

