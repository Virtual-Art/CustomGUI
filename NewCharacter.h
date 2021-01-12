#ifndef NEWCHARACTER
#define NEWCHARACTER

#include <iostream>
#include "Shape.h"
#include "FontFileReader.h"


using namespace std;


//////////////////////////////HOW TO USE THIS CLASS/////////////////////////////////////
//    A new character is created everytime  Char_Name[Letter] is envoked.
//    To add the same character again you need to call add() 

//    Type Char_Name[Letter] before edit functions are envoked for best results like this:
//    Type Char_Name['T'].SetPosition();
//    Type Char_Name['T'].SetSize();
////////////////////////////////////////////////////////////////////////////////////////


class CharacterData 
{
public: 
	int Ascii;
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
	float xSizePercentage; // what percentage of the line height the character is
	float ySizePercentage;
};

class NewCharacter : public Shape
{


public:

	//Static Members
	static bool FirstCreation;
	static CharacterData AllCharacters[94];

	//Public Members
	string CurrentFontFile;
	CharacterData CurrentCharacter;

	//Static Functions
	static CharacterData FindCharacter(string& File, int ASCII); //Finds Character in Font File
	static CharacterData& GetCharacter(int Ascii); //Returns Chosen Character's Data

    //Constructors
	NewCharacter(Page& Page);                       //New Shape
	NewCharacter(Page& Page, ShapeData& ShapeData); //New Shape with existing Data
	NewCharacter(Page& Page, int CharacterID);                 //Existing Shape
	NewCharacter(Page& Page, string File);                     //Initialization

	//Operators
	NewCharacter& operator[] (int InputAscii);

	//PureVirtuals

	void Update();
	void SetAction(int ShapeDataActionID);
	void BuildShapeVertices();
	void SetShapeRatios();

	//NewCharacter Functions
	void SetShape(ShapeData& ShapeData);
	void SetCharacter(int Ascii);
	//void SetCharacterSize(int FontSize);
	void PrintCharacter();
	static void PrintCharacter(int Ascii);



private:

	void AlignFlatBottoms(CharacterData& CharReference , CharacterData& CharEdit);
	void AlignFlatTops(CharacterData& CharReference, CharacterData& CharEdit);
	void AlignFlatMiddlePoints(CharacterData& CharReference, CharacterData& CharEdit);

	void AlignCurvedBottoms(CharacterData& CharReference, CharacterData& CharEdit);
	void AlignCurvedTops(CharacterData& CharReference, CharacterData& CharEdit);
	void AlignCurvedMiddlePoints(CharacterData& CharReference, CharacterData& CharEdit);

	void CenterCharacter(CharacterData& CharacterData);

	int OffsetFromTop(CharacterData& CharacterData);
	int OffsetFromBottom(CharacterData& CharacterData);
	int OffsetFromMiddle(CharacterData& CharacterData);

	//void ConvertTopToMiddle(CharacterData& CharacterData);
	//void ConvertBottomToMiddle(CharacterData& CharacterData);

	int LastAscii;
	int CurrentAscii;
};


#endif