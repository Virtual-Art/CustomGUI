#include "Texture.h"
// Make sure this is here and not in Texture.h
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"



int Texture::Create2DTexture()
{
	GLuint ID;
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	return ID;
}


RawTexture Texture::CreateTexture(const char* ImagePath, const char* ShaderName, int ActiveTexture, int TextureSlot, int Format)
{
	int TextureID = Create2DTexture();
	int width, height, nrChannels;
	glBindTexture(GL_TEXTURE_2D, TextureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	unsigned char* ImageData = stbi_load(ImagePath, &width, &height, &nrChannels, 0);
	cout << nrChannels << endl;
	if (!ImageData)
	{
		cout << "CreateTexture(); ERROR: Unable to load file path" << endl;

	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, Format ,width, height, 0, Format, GL_UNSIGNED_BYTE, ImageData);
		glGenerateMipmap(GL_TEXTURE_2D);
		
	}
	//glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(ImageData);
	return RawTexture(ImagePath, ShaderName, TextureID, ActiveTexture, TextureSlot);
}


