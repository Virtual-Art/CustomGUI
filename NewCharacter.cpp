#include "NewCharacter.h"

CharacterData NewCharacter::AllCharacters[94];
bool NewCharacter::FirstCreation = true;

NewCharacter::NewCharacter(llBookData* llBook)
	: Shape(llBook)
{
	SetllCharacter('T');
	CreatellCharacter();
	UpdatellMouseAccess();
}

NewCharacter::NewCharacter(llBookData* llBook, llShapeData* llShape)
	: Shape(llBook, llShape)
{
	SetllCharacter(llShape->Ascii);
	CreatellCharacter();
	UpdatellMouseAccess();
}

NewCharacter::NewCharacter(llShapeData* llShape)
	: Shape(llShape)
{
	CreatellCharacter();
}

//This one is used in Text.cpp
//this should be initialized with set size/Position
NewCharacter::NewCharacter(Page& Page) // WORKING
	: Shape(Page), LastAscii(0), CurrentAscii(0)
{
	//NEW default Shape
	if (FirstCreation == false)
	{
		SetCharacter('T');
		SetShapeRatios();
		BuildShapeVertices();
		Page.AddShape(this->LoadedShape);
	}
	else
	{
		cout << " ERROR::NEWCHARACTER::No font file to initialize with" << endl;
	}
}

NewCharacter::NewCharacter(Page& Page, ShapeData& ShapeData) //WORKING
	:Shape(Page, ShapeData), LastAscii(0), CurrentAscii(0)
{
	//NEW Shape with Custom Data
	if (FirstCreation == false)
	{
		SetCharacter(ShapeData.Ascii);
		SetShapeRatios();
		BuildShapeVertices();
		Page.AddShape(this->LoadedShape);
	}
	else
	{
		cout << " ERROR::NEWCHARACTER::No font file to initialize with" << endl;
	}

}

//Existing Character
NewCharacter::NewCharacter(Page& Page, int CharacterID) //WORKING
	:Shape(Page, CharacterID), LastAscii(0), CurrentAscii(0)
{
	if (&Page != nullptr)
	{
		CurrentPage = &Page;
	}
	//Shape Read/Write
	if (FirstCreation == false)
	{
		SetCharacter(LoadedShape.Ascii);
	}
	else
	{
		cout << " ERROR::NEWCHARACTER::No font file to initialize with" << endl;
	}
}




NewCharacter& NewCharacter::operator[] (int InputAscii)
{
	LastAscii = CurrentAscii;
	CurrentAscii = InputAscii;

	//Add character if New input
	if (InputAscii != CurrentCharacter.Ascii)
	{
		SetCharacter(InputAscii);
		Add_Duplicate();
	}
	return *this;
}

NewCharacter::NewCharacter(Page& Page, string FontFilePath)
	: Shape{ Page }
{
	ifstream FontFile;
	FontFile.open(FontFilePath);
	stringstream FileStream;
	FileStream << FontFile.rdbuf();
	FontFile.close();
	string Font = FileStream.str();
	const int FIRST_ASCII = 32;
	

	if (NewCharacter::FirstCreation == true)
	{
		for (int Ascii = FIRST_ASCII; Ascii < 126; Ascii++)
		{
			//Load all the characers
			int StartFromZero = Ascii - FIRST_ASCII;
			AllCharacters[StartFromZero] = FindCharacter(Font, Ascii);
			CenterCharacter(AllCharacters[StartFromZero]);
		}

		
		
		AlignFlatBottoms(AllCharacters['w' - 32], AllCharacters['i' - 32]);
		AlignFlatBottoms(AllCharacters['o' - 32], AllCharacters['t' - 32]);
		AlignFlatBottoms(AllCharacters['w' - 32], AllCharacters['x' - 32]);
		AlignFlatBottoms(AllCharacters['w' - 32], AllCharacters['z' - 32]);
		AlignFlatBottoms(AllCharacters['w' - 32], AllCharacters['v' - 32]);
		AlignFlatBottoms(AllCharacters['w' - 32], AllCharacters['A' - 32]);
		AlignFlatBottoms(AllCharacters['w' - 32], AllCharacters['E' - 32]);
		AlignFlatBottoms(AllCharacters['w' - 32], AllCharacters['F' - 32]);
		AlignFlatBottoms(AllCharacters['w' - 32], AllCharacters['H' - 32]);
		AlignFlatBottoms(AllCharacters['w' - 32], AllCharacters['I' - 32]);
		AlignFlatBottoms(AllCharacters['w' - 32], AllCharacters['K' - 32]);
		AlignFlatBottoms(AllCharacters['w' - 32], AllCharacters['L' - 32]);
		AlignFlatBottoms(AllCharacters['w' - 32], AllCharacters['M' - 32]);
		AlignFlatBottoms(AllCharacters['w' - 32], AllCharacters['N' - 32]);
		AlignFlatBottoms(AllCharacters['w' - 32], AllCharacters['T' - 32]);
		AlignFlatBottoms(AllCharacters['w' - 32], AllCharacters['W' - 32]);
		AlignFlatBottoms(AllCharacters['w' - 32], AllCharacters['X' - 32]);
		AlignFlatBottoms(AllCharacters['w' - 32], AllCharacters['Z' - 32]);
		AlignFlatBottoms(AllCharacters['w' - 32], AllCharacters['Y' - 32]);

		AlignFlatBottoms(AllCharacters['w' - 32], AllCharacters['h' - 32]);
		AlignFlatBottoms(AllCharacters['w' - 32], AllCharacters['k' - 32]);
		AlignFlatBottoms(AllCharacters['w' - 32], AllCharacters['l' - 32]);
		AlignFlatBottoms(AllCharacters['w' - 32], AllCharacters['f' - 32]);
		AlignFlatBottoms(AllCharacters['w' - 32], AllCharacters['n' - 32]);
		AlignFlatBottoms(AllCharacters['w' - 32], AllCharacters['m' - 32]);
		AlignFlatBottoms(AllCharacters['w' - 32], AllCharacters['r' - 32]);

		AlignCurvedBottoms(AllCharacters['o' - 32], AllCharacters['a' - 32]);
		AlignCurvedBottoms(AllCharacters['o' - 32], AllCharacters['u' - 32]);
		AlignCurvedBottoms(AllCharacters['o' - 32], AllCharacters['c' - 32]);
		AlignCurvedBottoms(AllCharacters['o' - 32], AllCharacters['o' - 32]);
		AlignCurvedBottoms(AllCharacters['o' - 32], AllCharacters['e' - 32]);
		AlignCurvedBottoms(AllCharacters['o' - 32], AllCharacters['s' - 32]);

		AlignCurvedBottoms(AllCharacters['o' - 32], AllCharacters['b' - 32]);
		AlignCurvedBottoms(AllCharacters['o' - 32], AllCharacters['d' - 32]);

		AlignCurvedBottoms(AllCharacters['o' - 32], AllCharacters['C' - 32]);
		AlignCurvedBottoms(AllCharacters['o' - 32], AllCharacters['O' - 32]);
		AlignCurvedBottoms(AllCharacters['o' - 32], AllCharacters['S' - 32]);
		AlignCurvedBottoms(AllCharacters['o' - 32], AllCharacters['G' - 32]);
		AlignCurvedBottoms(AllCharacters['w' - 32], AllCharacters['B' - 32]);
		AlignCurvedBottoms(AllCharacters['w' - 32], AllCharacters['D' - 32]);

		AlignFlatTops(AllCharacters['n' - 32], AllCharacters['g' - 32]);
		AlignFlatTops(AllCharacters['n' - 32], AllCharacters['p' - 32]);
		AlignFlatTops(AllCharacters['n' - 32], AllCharacters['q' - 32]);
		AlignFlatTops(AllCharacters['w' - 32], AllCharacters['y' - 32]);

		AlignFlatTops(AllCharacters['i' - 32], AllCharacters['j' - 32]);
		AlignFlatTops(AllCharacters['I' - 32], AllCharacters['P' - 32]);
		AlignFlatTops(AllCharacters['I' - 32], AllCharacters['J' - 32]);
		AlignFlatTops(AllCharacters['O' - 32], AllCharacters['Q' - 32]);
		AlignFlatTops(AllCharacters['I' - 32], AllCharacters['R' - 32]);
		AlignFlatTops(AllCharacters['I' - 32], AllCharacters['U' - 32]);
		AlignFlatTops(AllCharacters['I' - 32], AllCharacters['V' - 32]);

		AlignFlatBottoms(AllCharacters['I' - 32], AllCharacters['0' - 32]);
		AlignFlatBottoms(AllCharacters['I' - 32], AllCharacters['1' - 32]);
		AlignFlatBottoms(AllCharacters['I' - 32], AllCharacters['2' - 32]);
		AlignFlatBottoms(AllCharacters['I' - 32], AllCharacters['3' - 32]);
		AlignFlatBottoms(AllCharacters['I' - 32], AllCharacters['4' - 32]);
		AlignFlatBottoms(AllCharacters['I' - 32], AllCharacters['5' - 32]);
		AlignFlatBottoms(AllCharacters['I' - 32], AllCharacters['6' - 32]);
		AlignFlatBottoms(AllCharacters['I' - 32], AllCharacters['7' - 32]);
		AlignFlatBottoms(AllCharacters['I' - 32], AllCharacters['8' - 32]);
		AlignFlatBottoms(AllCharacters['I' - 32], AllCharacters['9' - 32]);
		
		AlignFlatMiddlePoints(AllCharacters['0' - 32], AllCharacters['{' - 32]);
		AlignFlatMiddlePoints(AllCharacters['0' - 32], AllCharacters['}' - 32]);
		AlignFlatMiddlePoints(AllCharacters['0' - 32], AllCharacters['[' - 32]);
		AlignFlatMiddlePoints(AllCharacters['0' - 32], AllCharacters[']' - 32]);
		AlignFlatMiddlePoints(AllCharacters['0' - 32], AllCharacters['(' - 32]);
		AlignFlatMiddlePoints(AllCharacters['0' - 32], AllCharacters[')' - 32]);
		AlignFlatMiddlePoints(AllCharacters['i' - 32], AllCharacters['>' - 32]);
		AlignFlatMiddlePoints(AllCharacters['i' - 32], AllCharacters['<' - 32]);
		AlignFlatMiddlePoints(AllCharacters['0' - 32], AllCharacters['/' - 32]);
		
		AlignFlatMiddlePoints(AllCharacters['o' - 32], AllCharacters[':' - 32]);
		AlignFlatMiddlePoints(AllCharacters['o' - 32], AllCharacters['+' - 32]);
		AlignFlatMiddlePoints(AllCharacters['o' - 32], AllCharacters['-' - 32]);
		AlignFlatMiddlePoints(AllCharacters['o' - 32], AllCharacters['=' - 32]);
		AlignFlatBottoms(AllCharacters['j' - 32], AllCharacters['|' - 32]);
		AlignFlatTops(AllCharacters[':' - 32], AllCharacters[';' - 32]);


		AlignCurvedBottoms(AllCharacters[':' - 32], AllCharacters['.' - 32]);
		AlignFlatTops(AllCharacters['.' - 32], AllCharacters[',' - 32]);
		AlignFlatBottoms(AllCharacters[':' - 32], AllCharacters['?' - 32]);
		
		AlignFlatTops(AllCharacters['?' - 32], AllCharacters[ 39 - 32]);
		AlignFlatTops(AllCharacters['i' - 32], AllCharacters['*' - 32]);

		AlignFlatTops(AllCharacters['[' - 32], AllCharacters['"' - 32]);
		AlignFlatTops(AllCharacters['[' - 32], AllCharacters[ - 32]);

		//AlignBottoms(AllCharacters['n' - 32], AllCharacters['z' - 32]);

		CurrentCharacter = AllCharacters['T'];
		NewCharacter::FirstCreation = false;
	}

	SetShapeRatios();
	LastAscii = 0;
	CurrentAscii = 0;
}


CharacterData NewCharacter::FindCharacter(string& File, int ASCII)
{
	CharacterData Data;
	FontFileReader Reader;
	string CharacterID = Reader.IntToStringID(ASCII);
	string IDLine = Reader.ReadCharacterData(File, CharacterID);

	Data.Ascii = ASCII;
	Data.CharWidth = Reader.GetFileData(IDLine, "width");
	Data.CharHeight = Reader.GetFileData(IDLine, "height");
	Data.yOffset = Reader.GetFileData(IDLine, "yoffset");
	Data.Advance = Reader.GetFileData(IDLine, "advance");
	Data.AtlasWidth = Reader.GetFileData(File, "scaleW");
	Data.AtlasHeight = Reader.GetFileData(File, "scaleH");
	Data.LineHeight = 76;// Reader.GetFileData(File, "lineHeight");
	Data.CharxPos = Reader.GetFileData(IDLine, "x")/ Data.AtlasWidth;
	Data.CharyPos = Reader.GetFileData(IDLine, "y")/ Data.AtlasHeight;
	Data.xSizePercentage = Data.CharWidth / 76; //Data.LineHeight
	Data.ySizePercentage = Data.CharHeight / 76; //Data.LineHeight
	Data.xOffset = (Data.Advance - Data.CharWidth) / 2;

	return Data;
}


//ShapeData needs to have ID initialized.
void NewCharacter::SetShape(ShapeData& ShapeData)
{
	if (ShapeData.ID > -1 && ShapeData.ID < CurrentPage->ShapeAmount())
	{
		LoadedShape = ShapeData;
		Update();
	}
	else
	{
		cout << "ERROR::SETSHAPE()::ID not set" << endl;
	}
}

//ShapeData needs to have ID initialized.
void NewCharacter::SetllShape(llShapeData* llShapeData)
{
	if (llShapeData != nullptr)
	{
		*CurrentllShape = *llShapeData;
		llUpdate();
	}
	else
	{
		cout << "ERROR::SETSHAPE():: ShapeData was nullptr" << endl;
	}
}

void NewCharacter::SetllCharacter(int Ascii)
{
	this->CurrentCharacter = NewCharacter::AllCharacters[Ascii - 32];
	CurrentllShape->Ascii = Ascii;
	
}

void NewCharacter::SetCharacter(int Ascii)
{
	this->CurrentCharacter = NewCharacter::AllCharacters[Ascii - 32];
	LoadedShape.Ascii = Ascii;
	SetShapeRatios();
}

void NewCharacter::SetAction(int ShapeDataActionID){};


void NewCharacter::CreatellCharacter()
{
	TopRightXYRatio = { CurrentllShape->Size[0] / 2, CurrentllShape->Size[1] / 2 };
	BottomRightXYRatio = { CurrentllShape->Size[0] / 2, CurrentllShape->Size[1] / -2 };
	BottomLeftXYRatio = { CurrentllShape->Size[0] / -2, CurrentllShape->Size[1] / -2 };
	TopLeftXYRatio = { CurrentllShape->Size[0] / -2, CurrentllShape->Size[1] / 2 };

	llVertexData* CurrentVertex = VertexTopLeft;

	while (CurrentVertex->Next != nullptr)
	{
		//Set Data
		CurrentVertex->Color = CurrentllShape->Color;
		CurrentVertex->TexIndex = 1;
		CurrentVertex->CentralPoint = { CurrentllShape->Position[0] + (CurrentllShape->Size[0] / 2), CurrentllShape->Position[1] - (CurrentllShape->Size[1] / 2) };
		CurrentVertex->GUIAction = CurrentllShape->Action;
		CurrentVertex = CurrentVertex->Next;
	}

	//Set Vertex Position
	VertexTopRight->Position = CurrentllShape->Position + TopRightXYRatio;
	VertexBottomRight->Position = CurrentllShape->Position + BottomRightXYRatio;
	VertexBottomLeft->Position = CurrentllShape->Position + BottomLeftXYRatio;
	VertexTopLeft->Position = CurrentllShape->Position + TopLeftXYRatio;

	//Set Vertex TexCoords
	//TopRight
	VertexTopRight->TexCoords = { CurrentCharacter.CharxPos + (CurrentCharacter.CharWidth / CurrentCharacter.AtlasWidth), CurrentCharacter.CharyPos };
	//BottomRight
	VertexBottomRight->TexCoords = { CurrentCharacter.CharxPos + (CurrentCharacter.CharWidth / CurrentCharacter.AtlasWidth), CurrentCharacter.CharyPos + (CurrentCharacter.CharHeight / CurrentCharacter.AtlasWidth) };
	//BottomLeft
	VertexBottomLeft->TexCoords = { CurrentCharacter.CharxPos, CurrentCharacter.CharyPos + (CurrentCharacter.CharHeight / CurrentCharacter.AtlasWidth) };
	//TopLeft
	VertexTopLeft->TexCoords = { CurrentCharacter.CharxPos, CurrentCharacter.CharyPos };

}

//Makeup of a Square
void NewCharacter::SetShapeRatios()
{
	TopRightXYRatio = { LoadedShape.Size[0] / 2, LoadedShape.Size[1] / 2 };
	BottomRightXYRatio = { LoadedShape.Size[0] / 2, LoadedShape.Size[1] / -2 };
	BottomLeftXYRatio = { LoadedShape.Size[0] / -2, LoadedShape.Size[1] / -2 };
	TopLeftXYRatio = { LoadedShape.Size[0] / -2, LoadedShape.Size[1] / 2 };
}

//ShapePosition, Color, character needs to be set for this to work properly
void NewCharacter::BuildShapeVertices()
{
	for (int i = 0; i < 4; i++)
	{
		LoadedShape.Vertex[i].Color = LoadedShape.Color;
		LoadedShape.Vertex[i].TexIndex = 1;
		LoadedShape.Vertex[i].CentralPoint = { LoadedShape.Position[0] + (LoadedShape.Size[0] / 2), LoadedShape.Position[1] - (LoadedShape.Size[1] / 2) };
		LoadedShape.Vertex[i].GUIAction = LoadedShape.Action;
	}

	LoadedShape.Vertex[0].Position = LoadedShape.Position + TopRightXYRatio;
	LoadedShape.Vertex[1].Position = LoadedShape.Position + BottomRightXYRatio;
	LoadedShape.Vertex[2].Position = LoadedShape.Position + BottomLeftXYRatio;
	LoadedShape.Vertex[3].Position = LoadedShape.Position + TopLeftXYRatio;

	//TopRight
	LoadedShape.Vertex[0].TexCoords = { CurrentCharacter.CharxPos + (CurrentCharacter.CharWidth / CurrentCharacter.AtlasWidth), CurrentCharacter.CharyPos};
	//BottomRight
	LoadedShape.Vertex[1].TexCoords = { CurrentCharacter.CharxPos + (CurrentCharacter.CharWidth / CurrentCharacter.AtlasWidth), CurrentCharacter.CharyPos + (CurrentCharacter.CharHeight/ CurrentCharacter.AtlasWidth)};
	//BottomLeft
	LoadedShape.Vertex[2].TexCoords = { CurrentCharacter.CharxPos, CurrentCharacter.CharyPos + (CurrentCharacter.CharHeight / CurrentCharacter.AtlasWidth) };
	//TopLeft
	LoadedShape.Vertex[3].TexCoords = { CurrentCharacter.CharxPos, CurrentCharacter.CharyPos};
}

//void NewCharacter::SetCharacterSize(int FontSize)
//{
//	//Different characters have different heights. SizePercentage is how tall it is based on the lineHeight ex = 60/95;
//	int xSizeInPixels = CurrentCharacter.xSizePercentage * FontSize;
//	int ySizeInPixels = CurrentCharacter.ySizePercentage * FontSize;
//	this->LoadedShape.Size = ConvertPixelSize({ xSizeInPixels, ySizeInPixels });
//}

void NewCharacter::llUpdate()
{
	CurrentCharacter = GetCharacter(CurrentllShape->Ascii);
	CreatellCharacter();
	UpdatellMouseAccess();
}

void NewCharacter::Update()
{
	CurrentCharacter = GetCharacter(LoadedShape.Ascii);
	SetShapeRatios();
	BuildShapeVertices();
	UpdateMouseAccess();
	CurrentPage->ReplaceShape(LoadedShape);
}

CharacterData& NewCharacter::GetCharacter(int Ascii)
{
	return AllCharacters[Ascii - 32];
}

void NewCharacter::PrintCharacter()
{
	cout << "Current Character Ascii: " << CurrentCharacter.Ascii << endl;
	cout << "Current Character CharWidth: " << CurrentCharacter.CharWidth << endl;
	cout << "Current Character CharHeight: " << CurrentCharacter.CharHeight << endl;
	cout << "Current Character CharxPos: " << CurrentCharacter.CharxPos << endl;
	cout << "Current Character CharyPos: " << CurrentCharacter.CharyPos << endl;
	cout << "Current Character xOffset: " << CurrentCharacter.xOffset << endl;
	cout << "Current Character yOffset: " << CurrentCharacter.yOffset << endl;
	cout << "Current Character Advance: " << CurrentCharacter.Advance << endl;
	cout << "Current Character AtlasWidt: " << CurrentCharacter.AtlasWidth << endl;
	cout << "Current Character AtlasHeight: " << CurrentCharacter.AtlasHeight << endl;
	cout << "Current Character LineHeight: " << CurrentCharacter.LineHeight << endl;
}

void NewCharacter::PrintCharacter(int Ascii)
{
	const int FIRST_ASCII = 32;
	cout << "----------------------Character: " << char(AllCharacters[Ascii - FIRST_ASCII].Ascii) << " ------------------------" << endl;
	cout << "Ascii: " << AllCharacters[Ascii - FIRST_ASCII].Ascii << endl;
	cout << "CharWidth: " << AllCharacters[Ascii - FIRST_ASCII].CharWidth << endl;
	cout << "CharHeight: " << AllCharacters[Ascii - FIRST_ASCII].CharHeight << endl;
	cout << "CharxPos: " << AllCharacters[Ascii - FIRST_ASCII].CharxPos << endl;
	cout << "CharyPos: " << AllCharacters[Ascii - FIRST_ASCII].CharyPos << endl;
	cout << "xOffset: " << AllCharacters[Ascii - FIRST_ASCII].xOffset << endl;
	cout << "yOffset: " << AllCharacters[Ascii - FIRST_ASCII].yOffset << endl;
	cout << "Advance: " << AllCharacters[Ascii - FIRST_ASCII].Advance << endl;
	cout << "AtlasWidt: " << AllCharacters[Ascii - FIRST_ASCII].AtlasWidth << endl;
	cout << "AtlasHeight: " << AllCharacters[Ascii - FIRST_ASCII].AtlasHeight << endl;
	cout << "LineHeight: " << AllCharacters[Ascii - FIRST_ASCII].LineHeight << endl;
}

//All inputs are as a middle point
void NewCharacter::CenterCharacter(CharacterData& CharacterData)
{
	CharacterData.yOffset = 0;
}

//The bottom of the edit needs to be aligned with the bottom of the ref
void NewCharacter::AlignFlatBottoms(CharacterData& CharReference, CharacterData& CharEdit)
{
	//dis between cursor and bottom of o
	int RefCharBottom = OffsetFromBottom(CharReference);

	//Edit new position = Bottom of ref character + half the size of new character
	CharEdit.yOffset = RefCharBottom + (CharEdit.CharHeight / 2); //This Works for flat bottoms
}

void NewCharacter::AlignFlatTops(CharacterData& CharReference, CharacterData& CharEdit)
{
	//dis between cursor and bottom of o
	int RefCharTop = OffsetFromTop(CharReference);

	//Edit new position = Bottom of ref character + half the size of new character
    CharEdit.yOffset = RefCharTop - (CharEdit.CharHeight / 2); // This works with flat tops
}

void NewCharacter::AlignFlatMiddlePoints(CharacterData& CharReference, CharacterData& CharEdit)
{
	                   //dis between cursor and middle of character
	CharEdit.yOffset = OffsetFromMiddle(CharReference);
}

//The bottom of the edit needs to be aligned with the bottom of the ref
void NewCharacter::AlignCurvedBottoms(CharacterData& CharReference, CharacterData& CharEdit)
{
	//dis between cursor and bottom of o
	int RefCharBottom = OffsetFromBottom(CharReference);

	//Edit new position = Bottom of ref character + half the size of new character
	CharEdit.yOffset = RefCharBottom + (CharEdit.CharHeight / 2); 
}

void NewCharacter::AlignCurvedTops(CharacterData& CharReference, CharacterData& CharEdit)
{

}

void NewCharacter::AlignCurvedMiddlePoints(CharacterData& CharReference, CharacterData& CharEdit)
{

}
//Assuming CursorLine is ZERO
//Returns distance between the cursor line and the top of the character
int NewCharacter::OffsetFromTop(CharacterData& CharacterData)
{
	return CharacterData.yOffset + (CharacterData.CharHeight / 2);
}

//Returns distance between the cursor line and the bottom of the character
int NewCharacter::OffsetFromBottom(CharacterData& CharacterData)
{
	return CharacterData.yOffset - (CharacterData.CharHeight / 2);
}

//Returns distance between the cursor line and the middle of the character
int NewCharacter::OffsetFromMiddle(CharacterData& CharacterData)
{
	return CharacterData.yOffset;
}

