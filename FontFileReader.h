#ifndef FONTREADER
#define FONTREADER

#include <iostream>
#include <string>

using namespace std;

class FontFileReader
{
public:

	string IntToStringID(int Integer); //doesn't need to be a pointer because the string isn't long

	int StringToInt(string Number, int NumberSize);

	string ReadCharacterData(string File, string ASCII_ID);

	int GetFileData(string IDLine, string DataType);


private:

};

#endif