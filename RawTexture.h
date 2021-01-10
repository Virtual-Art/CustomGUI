#ifndef RAWTEXTURE
#define RAWTEXTURE

#pragma once

class RawTexture
{
public:

	RawTexture(const char* ImagePath, const char* ShaderName, int TextureID, int ActiveTexture, int TextureSlot)
	{
		this->ImagePath = ImagePath;
		this->ShaderName = ShaderName;
		this->TextureID = TextureID;
		this->ActiveTexture = ActiveTexture;
		this->TextureSlot = TextureSlot;
	}


	const char* GetImagePath()
	{
		return this->ImagePath;
	}

	const char* GetShaderName()
	{
		return this->ShaderName;
	}

	int GetTextureID()
	{
		return this->TextureID;
	}

	int GetActiveTexture()
	{
		return this->ActiveTexture;
	}

	int GetTextureSlot()
	{
		return this->TextureSlot;
	}

private:

	const char* ImagePath;
	const char* ShaderName;
	int TextureID;
	int ActiveTexture;
	int TextureSlot;
}; 

#endif