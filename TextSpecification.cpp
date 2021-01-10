#include "TextSpecification.h"


TextSpecification::TextSpecification(string Text, string FontFilePath, float xPos, float yPos, float FontSize, float CharSpacing, glm::vec4 Color,float MaxLine, bool Centered, float LineSpacing)
{
	ifstream FontFile;
	FontFile.open(FontFilePath);
	stringstream FileStream;
	FileStream << FontFile.rdbuf();
	FontFile.close();
	string Font = FileStream.str();
	
	this->Text = Text;
	this->FontFile = Font;
	this->FontSize = FontSize;
	this->CharSpacing = CharSpacing;
	this->LineSpacing = LineSpacing;
	this->Position = { xPos, yPos };
	this->Color = Color;
	this->LineLength = MaxLine;
    this->Centered = Centered;
	
}


TextSpecification::TextSpecification(string Text, string FontFilePath, float xPos, float yPos, float FontSize, glm::vec4 Color, bool List, float Spacing, float Maxline)
{
	ifstream FontFile;
	FontFile.open(FontFilePath);
	stringstream FileStream;
	FileStream << FontFile.rdbuf();
	FontFile.close();
	string Font = FileStream.str();

	//turn string to pointer so that
	
	this->Text = Text;
	this->FontFile = Font;
	this->FontSize = FontSize;
	this->Position = { xPos, yPos };
	this->Color = Color;
	this->LineLength = Maxline;
	this->List = List;

	if (List == true)
	{
		this->CharSpacing = 0.4;
		this->LineSpacing = Spacing;
	}
	else
	{
		this->CharSpacing = CharSpacing;
		this->LineSpacing = 1.5;
	}
}

TextSpecification::TextSpecification(string Text, float xPos, float yPos, float FontSize, float Maxline)
{
	ifstream FontFile;
	FontFile.open("Resources/arial.fnt"); // might not work with others
	stringstream FileStream;
	FileStream << FontFile.rdbuf();
	FontFile.close();
	string Font = FileStream.str();


	this->Text = Text;
	this->FontFile = Font; // Points to the StringFile
	this->FontSize = FontSize; 
	this->Position = {xPos, yPos};
	this->LineLength = Maxline;
}

//TextBox
TextSpecification::TextSpecification(string Text, string FontFilePath, glm::vec2 Position, glm::vec2 Size, float FontSize, glm::vec4 Color, unsigned int FontSlot, float CharSpacing, bool MouseAccess, bool List, bool Centered)
{
	ifstream FontFile;
	FontFile.open(FontFilePath);
	stringstream FileStream;
	FileStream << FontFile.rdbuf();
	FontFile.close();
	string Font = FileStream.str();

	//turn string to pointer so that

	this->Text = Text;
	this->FontFile = Font;
	this->FontSize = FontSize;
	this->Position = Position;
	this->Size = Size;
	this->Color = Color;
	this->FontSlot = FontSlot;

	this->Count = -1;
	this->Count = Text.size();
	this->MouseAccess = MouseAccess;
	this->List = List;
	this->Centered = Centered;

	if (List == true)
	{
		this->CharSpacing = 0.4;
		this->LineSpacing = CharSpacing;
	}
	else
	{
		this->CharSpacing = CharSpacing;
		this->LineSpacing = 1.5;
	}

}

//Newest
TextSpecification::TextSpecification(string Text, glm::vec2 Position, bool List, glm::vec4 Color)
{
	ifstream FontFile;
	FontFile.open("Resources/calibri (1).fnt");
	stringstream FileStream;
	FileStream << FontFile.rdbuf();
	FontFile.close();
	string Font = FileStream.str();

	//turn string to pointer so that

	this->Text = Text;
	this->FontFile = Font;
	this->FontSize = 0.3;
	this->Position = Position;
	this->Size = { 2.0, 0.1};
	this->Color = Color;
	this->FontSlot = 1;

	this->Count = -1;
	this->Count = Text.size();
	this->MouseAccess = true;
	this->List = List;
	this->Centered = false;
	this->CharSpacing = 0.4;
	this->LineSpacing = 0.535;

}