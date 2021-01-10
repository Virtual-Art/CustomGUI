#include "FontMath.h"

//Takes a texture coordinate and calculates to an OpenGL screen coordinate
//Where Top Left is (0,0)
float TextureToGLx(float TextureWidth, float xTexture)
{
	return (xTexture / TextureWidth) - 1;
}

//Where Top Left is (0,0)
float TextureToGLy(float TextureHeight,  float yTexture)
{
	return (yTexture / TextureHeight) - 1;
}
//Where Bottom Left is (0,0)
float ViewPortToGLx(float ViewPortWidth, float ViewPortx)
{
	return 0.0;                           ///NOT DONE
}
//Where Bottom Left is (0,0)
float ViewPortToGLy(float ViewPortHeight, float ViewPorty)
{
	return 0.0;                           ///NOT DONE
}

//returns a position
//float xPos, float TextureAdvance, float TextureWidth, float FontSize
glm::vec2 FontMath::AdvanceCursor(Character character, float FontSize, glm::vec2 CursorPos, float CharSpacing) 
{
	float Advance = (character.Advance / character.AtlasWidth)* CharSpacing * FontSize;
	float FinalxPos = CursorPos[0] + Advance;
	//cout << "Character Advance to:" << FinalxPos  << "," << CursorPos[1] << endl;
	return {FinalxPos, CursorPos[1] };
}

//Takesin line height from textfile
//returns a position
glm::vec2 FontMath::NextLine(glm::vec2 StartPosition, Character Character, glm::vec2 CurrentPosition, float FontSize, float Spacing, float xStart)
{
	float Reverse = 1.5 - Spacing;
	float NextLine = (Character.LineHeight / Character.AtlasHeight) * (FontSize / Reverse); //1.5
	float FinalyPos = CurrentPosition[1] - NextLine;
	CurrentPosition[0] = xStart;
	cout << "NextLine-----" << endl;
	return {StartPosition[0], FinalyPos };
}

// for translation
glm::vec2 FontMath::GetCharacterPosition(Character Character, glm::vec2 Pos, float FontSize, bool LineStart)
{
	float FinalxPos = Pos[0];
	if (LineStart == false)
	{
		float xAdvance = (Character.xOffset / Character.AtlasWidth) * FontSize;
		FinalxPos = Pos[0] + xAdvance;
	}
	float yAdvance = (Character.yOffset / Character.AtlasHeight) * FontSize;
	float FinalyPos = Pos[1] - yAdvance;
	return {FinalxPos, FinalyPos};
}


//we need the size of each box, as well as the actual positions
glm::vec2 FontMath::GetCharacterSize(Character Character, glm::vec2 CharPosition, int SCR_Height, int SCR_Width, float FontSize)
{
	float AspectRatio = SCR_Width / SCR_Height;

	int CharHeight = Character.CharHeight;
	int CharWidth = Character.CharWidth;
	int AtlasHeight = Character.AtlasHeight; //500 pixels
	int AtlasWidth = Character.AtlasWidth; //500 pixels

	float xStep1 = CharWidth / 2;
	float yStep1 = CharHeight / 2;
	float xStep2 = xStep1 / AtlasHeight;
	float yStep2 = yStep1 / AtlasWidth;
	float xSize = xStep2 * FontSize;
	float ySize = yStep2 * AspectRatio * FontSize;

	return { xSize, ySize };
}
//Offset in screen coordinates
//probably want to return a vertices struct? 
CharTexCoords FontMath::GetCharacterTexCoords(Character Character)
{
	//ex: xPos = 401, yPos = 448, Width = 15, Height = 26
	//BL = Bottom Left

	float ModifiedxPos = Character.CharxPos;

	static float TexCoord[8];

	//Texture Coordinates
	float TLX = Character.CharxPos;                              // top left             // 401  // 
	float TLY = Character.CharyPos;                                  // top left             // 448  // 
	float TRX = Character.CharxPos + Character.CharWidth;        // top right			   // 416  // 
	float TRY = Character.CharyPos;                                  // top right			   // 448  // 
	float BRX = Character.CharxPos;                              // bottom right		   // 401  // 
	float BRY = Character.CharyPos + Character.CharHeight;           // bottom right		   // 474  // 
	float BLX = Character.CharxPos + Character.CharWidth;        // bottom left		   // 416  // 
	float BLY = Character.CharyPos + Character.CharHeight;           // bottom left		   // 474  // 

	//Convert Atlas Coordinates to TexturCoordinates   EX: AtlasHeight = 512
	TexCoord[0] = TLX / Character.AtlasWidth;                      // 0.783 //
	TexCoord[1] = TLY / Character.AtlasHeight;					   // 0.875	//
	TexCoord[2] = TRX / Character.AtlasWidth;					   // 0.813	//
	TexCoord[3] = TRY / Character.AtlasHeight;					   // 0.875	//
	TexCoord[4] = BRX / Character.AtlasWidth;				       // 0.783	//
	TexCoord[5] = BRY / Character.AtlasHeight;				       // 0.926 //
	TexCoord[6] = BLX / Character.AtlasWidth;				       // 0.813	//
	TexCoord[7] = BLY / Character.AtlasHeight;				       // 0.926 //
	
	CharTexCoords CharacterTex;
	CharacterTex.TopLeft = { TexCoord[0], TexCoord[1] };
	CharacterTex.TopRight = { TexCoord[2], TexCoord[3] };
	CharacterTex.BottomLeft = { TexCoord[4], TexCoord[5] };
	CharacterTex.BottomRight = { TexCoord[6], TexCoord[7] };
	
	

	//cout << "TexCoords0: " << TexCoord[0] << endl;
	//cout << "TexCoords1: " << TexCoord[1] << endl;
	//cout << "TexCoords2: " << TexCoord[2] << endl;
	//cout << "TexCoords3: " << TexCoord[3] << endl;
	//cout << "TexCoords4: " << TexCoord[4] << endl;
	//cout << "TexCoords5: " << TexCoord[5] << endl;
	//cout << "TexCoords6: " << TexCoord[6] << endl;
	//cout << "TexCoords7: " << TexCoord[7] << endl;
	//These 8 floats is your textureCoordinates
	return CharacterTex;
}


//FontVertex& FontMath::SetTopRight(const Element& Element, Character Character, FontVertex& Vertex)
//{
//
//	Vertex.Position = { Element.Position[0] + Element.Size[0],Element.Position[1] };
//	Vertex.TexCoords = { (Character.CharxPos + Character.CharWidth) / Character.AtlasWidth, (Character.CharyPos)/ Character.AtlasHeight }; //top right
//	Vertex.Color = Element.Color;
//	Vertex.TexIndex = Element.ActiveTexture;
//	Vertex.CentralPoint = { Element.Position[0] + (Element.Size[0] / 2), Element.Position[1] - (Element.Size[1] / 2) };
//	Vertex.GUIAction = Element.Action;
//
//	return Vertex;
//}

///FontVertex& FontMath::SetBottomRight(const Element& Element, Character Character, FontVertex& Vertex)
//{ 
//Vertex.Position = { Element.Position[0] + Element.Size[0], Element.Position[1] - Element.Size[1]};
//Vertex.TexCoords = { (Character.CharxPos + Character.CharWidth)/Character.AtlasWidth, (Character.CharyPos + Character.CharHeight) / Character.AtlasHeight }; //bottom right
//Vertex.Color = Element.Color;
//Vertex.TexIndex = Element.ActiveTexture;
//Vertex.CentralPoint = { Element.Position[0] + (Element.Size[0] / 2), Element.Position[1] - (Element.Size[1] / 2) };
//Vertex.GUIAction = Element.Action;
 //
//return Vertex;
////#2
//} /
///FontVertex& FontMath::SetTopLeft(const Element& Element, Character Character, FontVertex& Vertex)
//{ /
//Vertex.Position = { Element.Position[0], Element.Position[1]};
//Vertex.TexCoords = {Character.CharxPos / Character.AtlasWidth, Character.CharyPos/ Character.AtlasHeight };  //topleft
//Vertex.Color = Element.Color;
//Vertex.TexIndex = Element.ActiveTexture;
//Vertex.CentralPoint = { Element.Position[0] + (Element.Size[0] / 2), Element.Position[1] - (Element.Size[1] / 2) };
//Vertex.GUIAction = Element.Action;
  //
//return Vertex;
////#3
//} /
///FontVertex& FontMath::SetBottomLeft(const Element& Element, Character Character, FontVertex& Vertex)
//{
//	Vertex.Position = { Element.Position[0], Element.Position[1] - Element.Size[1]};
//	Vertex.TexCoords = { Character.CharxPos / Character.AtlasWidth, (Character.CharyPos + Character.CharHeight) / Character.AtlasHeight };
//	Vertex.Color = Element.Color; //bottom left
//	Vertex.TexIndex = Element.ActiveTexture;
//	Vertex.CentralPoint = { Element.Position[0] + (Element.Size[0] / 2), Element.Position[1] - (Element.Size[1] / 2) };
//	Vertex.GUIAction = Element.Action;
//
//	return Vertex;
//	//#4
//}


