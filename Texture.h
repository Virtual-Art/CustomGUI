#ifndef TEXTURE 
#define TEXTURE

#pragma once
#include <iostream>
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "RawTexture.h"

using namespace std;

class Texture
{

public:

		//Texture(const char* ImagePath);
	RawTexture CreateTexture(const char* ImagePath, const char* ShaderName, int ActiveTexture, int TextureSlot, int Format);


	int Create2DTexture();


	private:

		const char* ImagePath;
		const char* NameInShader;
		int TextureID;
		int NumberOfVertices;
		int NumberOfIndicies;

};


#endif