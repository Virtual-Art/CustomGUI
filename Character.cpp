#include "Character.h"



Character::Character(string File, char character)
{
	FontFileReader Reader;
	//cout <<" "<<endl;	
	//cout << "Character:" << character << endl;
	int ASCIICODE = character;
	//cout << "ASCII Code: " << ASCIICODE << endl;
	//cout << " " << endl;
	//finds the data line of the ASCII code
	string CharacterID = Reader.IntToStringID(ASCIICODE);
	//cout << "CharacterID:" << CharacterID << endl;
	string IDLine = Reader.ReadCharacterData(File, CharacterID);

	this->CharWidth = Reader.GetFileData(IDLine, "width");
	this->CharHeight = Reader.GetFileData(IDLine, "height");
	this->CharxPos = Reader.GetFileData(IDLine, "x");
	this->CharyPos = Reader.GetFileData(IDLine, "y");
	this->xOffset = Reader.GetFileData(IDLine, "xoffset");
	this->yOffset = Reader.GetFileData(IDLine, "yoffset");
	this->Advance = Reader.GetFileData(IDLine, "advance");
	this->AtlasWidth = Reader.GetFileData(File, "scaleW");
	this->AtlasHeight = Reader.GetFileData(File, "scaleH");
	this->LineHeight = Reader.GetFileData(File, "lineHeight");
}