#include "FontFileReader.h"

//returns the string of the id line and it's contents
string FontFileReader::ReadCharacterData(string File, string ASCII_ID)
{
	string CurrentFile = File;


	int Lineindex;

	//if you are getting an error here, it could be because the file is typed wrong

	Lineindex = CurrentFile.find(ASCII_ID);
 	CurrentFile = CurrentFile.substr(Lineindex, 100);

	return CurrentFile;
}

//if you get an eception, it's because the content needed is not in the file/string
int FontFileReader::GetFileData(string IDLine, string DataType)
{
	string CurrentFile = IDLine; 

	int Index = CurrentFile.find(DataType);      //ex: find "xoffset"
	string Data = CurrentFile.substr(Index, 40); //ex.    "|xoffset = 46  |"
	Index = Data.find_first_of("-1342567890");   //ex: find "46"
	string Number = Data.substr(Index, 10);      //ex:    "|46   |"
	int NumberLength = Number.find(32);          //ex: find "46| |" (first space)
	int FinalData = StringToInt(Number, NumberLength); // Turns string ex.("46") into single int ex.(46);

	//cout << "DataType: "<< DataType << ":: " << FinalData << endl;
	//cout << "CharacterLine:" << IDLine << endl;
	//cout << "index: " << Index << endl;
	//cout << "DataString|" << Data << "|" << endl;
	//cout << "NumberIndex: " << Index << endl;
	//cout << "StringNumber|" << Number << "|" << endl;
	//cout << "NumberLength: " << NumberLength;
	return FinalData;
}

//so that we load numbers as an integer in  struct not as a string (we are working with integers after this function)
int FontFileReader::StringToInt(string Number, int NumberSize)
{
	size_t Negative = Number.find('-');
	if (Negative!= string::npos)
	{
		
		if (NumberSize == 5) // really 4 because (-) is a character
		{
			//48 in code ascii is zero. Sequential numbers past 48/0 are consecutive, leading up to 57/9.
			int P2 = (Number[1] - 48);
			int P3 = (Number[2] - 48);
			int P4 = (Number[3] - 48);
			int P5 = (Number[4] - 48);

			int Thousands = P2 * 1000;
			int Hundreds = P3 * 100;
			int Tens = P4 * 10;
			int Singular = P5 * 1;
			int Integer = Thousands + Hundreds + Tens + Singular;
			return -Integer;
		}
		if (NumberSize == 4) // really 3
		{
			//48 in code ascii is zero. Sequential numbers past 48/0 are consecutive, leading up to 57/9.
		
			int P2 = Number[1] - 48;
			int P3 = Number[2] - 48;
			int P4 = Number[3] - 48;
			int Hundreds = P2 * 100;
			int Tens = P3 * 10;
			int Singular = P4 * 1;
			int Integer = Hundreds + Tens + Singular;
			return -Integer;
		}
		if (NumberSize == 3)// really 2
		{
			int P2 = Number[1] - 48; 
			int P3 = Number[2] - 48;

			int Tens = P2 * 10;
			int Singular = P3 * 1;
			int Integer = Tens + Singular;
			return -Integer;
		}
		if (NumberSize == 2) //really 1
		{
			int P2 = Number[1] - 48;

			int Singular = P2 * 1;
			int Integer = Singular;
			return -Integer;
		}
	}

	else
	{
		if (NumberSize == 4)
		{
			//48 in code ascii is zero. Sequential numbers past 48/0 are consecutive, leading up to 57/9.
			int P1 = (Number[0] - 48);
			int P2 = (Number[1] - 48);
			int P3 = (Number[2] - 48);
			int P4 = (Number[3] - 48);

			int Thousands = P1 * 1000;
			int Hundreds = P2 * 100;
			int Tens = P3 * 10;
			int Singular = P4 * 1;
			int Integer = Thousands + Hundreds + Tens + Singular;
			return Integer;
		}
		if (NumberSize == 3)
		{
			int P1 = Number[0] - 48;
			int P2 = Number[1] - 48;
			int P3 = Number[2] - 48;
			int Hundreds = P1 * 100;
			int Tens = P2 * 10;
			int Singular = P3 * 1;
			int Integer = Hundreds + Tens + Singular;
			return Integer;
		}
		if (NumberSize == 2)
		{
			int P1 = Number[0] - 48;
			int P2 = Number[1] - 48;

			int Tens = P1 * 10;
			int Singular = P2 * 1;
			int Integer = Tens + Singular;
			return Integer;
		}
		if (NumberSize == 1)
		{
			int P1 = Number[0] - 48;
			int Singular = P1 * 1;
			int Integer = Singular;
			return Integer;
		}
	}
}

//you would pass the int that the letter belongs to 
//int ASCII = 'h'; or: int ASCII = Text[i];
//pass ASCII as integer
string FontFileReader::IntToStringID(int Integer)
{
	//EX:int 99; (ASCII C)
	if (Integer> 126)
	{
		cout << "Character Type Not Supported" << endl;
		return NULL;
	}
	if (Integer > 99)
	{
		int DoubleNumber = (Integer - 100);
		int Second = DoubleNumber / 10;
		int Last = DoubleNumber - (Second * 10) ; //9
		int ASCII2 = 48 + Second;
		int ASCII3 = 48 + Last;
		//cout <<"NumberTaken: (over 100)"<<Second << Last << endl; //20,100
		string ASCIINumber = { 49, char(ASCII2), char(ASCII3) };
		string CharacterID = "id=" + ASCIINumber;
		return CharacterID;
	}
	else
	{
		int Second = Integer / 10;
		int Last = Integer - (Second * 10); //9
		int ASCII1 = 48 + Second;
		int ASCII2 = 48 + Last;
		//cout << "NumberTaken: (Under100)" << Second << Last << endl; //20,100
		string ASCIINumber = { char(ASCII1), char(ASCII2) };
		string CharacterID = "id=" + ASCIINumber;
		return CharacterID;
	}
}

