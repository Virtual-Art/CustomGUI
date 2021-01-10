#ifndef CHARACTER
#define CHARACTER

#include <iostream>
#include "FontFileReader.h"


class Character 
{
public:

	Character(string File, char character);

	float CharWidth;
	float CharHeight;
	float CharxPos;
	float CharyPos;
	float xOffset;
	float yOffset;
	float Advance;
	float AtlasWidth;
	float AtlasHeight;
	float LineHeight;

private:

};

#endif