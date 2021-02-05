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

	   NewPage();
	   NewPage(llBookData* llBook, ShaderProgram* ShaderProgram, RawTexture* Texture0, RawTexture* Texture1, RawTexture* Texture2);
	   void llInit(llBookData* llBook);
	   llPageData* GetData() { return CurrentllPage; };

	   llPageData* llSwitch(llPageData* llPage) {};
	   
	   void InitiatePage(llBookData* llBook, ShaderProgram ShaderProgram);

	   void LoadGPU();

	   void DrawPage(ShaderProgram ShaderProgram, RawTexture RawTexture1, RawTexture RawTexture2, RawTexture RawTexture3);
	   void DrawPage();




	   llPageData* CurrentllPage;
	   llBookData* CurrentBook;
	   ShaderProgram* CurrentShader;

	   RawTexture* Texture0;
	   RawTexture* Texture1;
	   RawTexture* Texture2;
};

#endif 

