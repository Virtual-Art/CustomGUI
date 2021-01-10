#include "Text.h"

Text::Text(Page& Page)
 : ShapeGroup{Page}
{
	//DefaultTextData
	CurrentTextData.Phrase = "TEXT";

	//Group Setup
	this->CurrentGroupData.ShapeStartID = Page.ShapeAmount();
	this->CurrentGroupData.Count = CurrentTextData.Phrase.size();

	//Out Of Bounds Check
	if (Page.InBounds(Page.ShapeAmount() + CurrentGroupData.Count))
	{
		this->CurrentGroupData.NextGroup = Page.GetNextShapeAddress(4);
	} //Default +4

    //Attribute Setup
	this->CurrentGroupData.Color = { 1.0, 1.0, 1.0, 1.0 };
	this->CurrentGroupData.Size = { 0.0, 0.0 }; // all of the xadvances of all the text
	this->CurrentGroupData.Position = { 0.0, 0.0 };
	this->CurrentGroupData.MouseAccess = true;
	this->CurrentGroupData.Highlighted = false;
	this->CurrentGroupData.Centered = false;

	this->CurrentGroupData.XYShapesPerRow = { 2.0, 2.0 }; // Can use without
	this->CurrentGroupData.ShapeDataSize = { 0.8, 0.8 };  // Can use without

	AddText();
}

//using this one in application.cpp
Text::Text(Page& Page, GroupData& GroupData, TextData& TextData)
	: ShapeGroup{ Page, GroupData}
{
	CurrentTextData = TextData;
	this->CurrentGroupData.ShapeStartID = Page.ShapeAmount();
	this->CurrentGroupData.Count = TextData.Phrase.size();
	this->CurrentShape.ShapeGroupStart = CurrentGroupData.ShapeStartID;
	this->CurrentShape.ShapeGroupCount = CurrentGroupData.Count;
	AddText();
	Log::LogVec2("RatioSize grey", GroupData.Size);
	Log::LogVec2("RatioSize white", CurrentGroupData.Size);
	GroupData.Size = CurrentGroupData.Size;
}


//Simple One
Text::Text(Page& Page, string Text, glm::vec2 Position)
	: ShapeGroup{ Page }
{
	if (&Page != nullptr)
	{
		//Set TextData
		CurrentTextData.Phrase = Text;
		CurrentTextData.Centered = false;

		//Set Group Data
		this->CurrentGroupData.ShapeStartID = Page.ShapeAmount();
		this->CurrentGroupData.Count = CurrentTextData.Phrase.size();

		//Set Shape Data
		this->CurrentShape.ShapeGroupStart = CurrentGroupData.ShapeStartID;
		this->CurrentShape.ShapeGroupCount = CurrentGroupData.Count;

		//Attribute Setup
		this->CurrentGroupData.Color = { 1.0, 1.0, 1.0, 1.0 };
		this->CurrentGroupData.Size = { 0.0, 0.0 }; // all of the xadvances of all the text
		this->CurrentGroupData.Position = Position;
		this->CurrentGroupData.MouseAccess = true;
		this->CurrentGroupData.Highlighted = false;
		this->CurrentGroupData.Centered = false;

		this->CurrentGroupData.XYShapesPerRow = { 2.0, 2.0 }; // Can use without
		this->CurrentGroupData.ShapeDataSize = { 0.8, 0.8 };  // Can use without

		//Create
		AddText();
	}
	else
	{
		//Set TextData
		CurrentTextData.Phrase = Text;
		CurrentTextData.CursorPosition = Position;
		CurrentTextData.Centered = true;

		//Set Group Data

		this->CurrentGroupData.Count = CurrentTextData.Phrase.size();

		//Set Shape Data

		this->CurrentShape.ShapeGroupCount = CurrentGroupData.Count;
	}
}

Text::Text(Page& Page, int GroupID)
	: ShapeGroup( Page, GroupID )
{
	//Set 1st shape of group
	CurrentShape = Page.GetShapeDataR(GroupID);
	cout << "CurrentShape.GroupCount: "<< CurrentShape.ShapeGroupCount<< endl;
	//SetGroupData
	if (CurrentShape.ShapeDataType == TYPE_TEXT)
	{
		ShapeToGroup(CurrentShape);
		CurrentTextData.Phrase   = CurrentShape.Text;
		CurrentTextData.Centered = CurrentShape.TextCentered;
		CurrentTextData.EndStart = CurrentShape.EndStart;
	}
	else
	{
		cout << "NEWTEXT::ERROR::Shape is not part of text " << endl;
		CurrentShape.reset();
	}
}


Text::Text(Page& Page, int Integer, string Description, glm::vec2 Position)
	: ShapeGroup{ Page }
{
	string FinalPhrase = Description + " " + to_string(Integer);
	//DefaultTextData
	CurrentTextData.Phrase = FinalPhrase;

	//Group Setup
	this->CurrentGroupData.ShapeStartID = Page.ShapeAmount();
	this->CurrentGroupData.Count = CurrentTextData.Phrase.size();

	//Out Of Bounds Check
	if (Page.InBounds(Page.ShapeAmount() + CurrentGroupData.Count))
	{
		this->CurrentGroupData.NextGroup = Page.GetNextShapeAddress(4);
	} //Default +4

	//Attribute Setup
	this->CurrentGroupData.Color = { 1.0, 1.0, 1.0, 1.0 };
	this->CurrentGroupData.Size = { 0.0, 0.0 }; // all of the xadvances of all the text
	this->CurrentGroupData.Position = Position;
	this->CurrentGroupData.MouseAccess = true;
	this->CurrentGroupData.Highlighted = false;
	this->CurrentGroupData.Centered = false;

	this->CurrentGroupData.XYShapesPerRow = { 2.0, 2.0 }; // Can use without
	this->CurrentGroupData.ShapeDataSize = { 0.8, 0.8 };  // Can use without

	AddText();
}

Text::Text(Page& Page, GroupData& GroupData, TextData& TextData, int Integer, string Description)
	: ShapeGroup{ Page, GroupData }
{
	CurrentTextData = TextData;
	CurrentTextData.Phrase = Description + " " + to_string(Integer);
	this->CurrentGroupData.ShapeStartID = Page.ShapeAmount();
	this->CurrentGroupData.Count = TextData.Phrase.size();
	this->CurrentShape.ShapeGroupStart = CurrentGroupData.ShapeStartID;
	this->CurrentShape.ShapeGroupCount = CurrentGroupData.Count;
	AddText();
	GroupData.Size = CurrentGroupData.Size;
}

Text::Text() {};

Text::Text(Page& Page, int GroupID, int Integer, string Description)
	: ShapeGroup(Page, GroupID)
{

}

void Text::Init(Page& Page, string Text, glm::vec2 Position)
{
	CurrentGroupData.Page = &Page;
	CurrentGroupData.Page->ShapeGroupCount++;
	CurrentGroupData.GroupID = CurrentGroupData.Page->ShapeGroupCount;

	//Set TextData
	CurrentTextData.Phrase = Text;
	CurrentTextData.CursorPosition = Position;
	//CurrentTextData.Centered = true;

	//Set Group Data
	this->CurrentGroupData.ShapeStartID = Page.ShapeAmount();
	this->CurrentGroupData.Count = CurrentTextData.Phrase.size();

	//Set Shape Data
	this->CurrentShape.ShapeGroupStart = CurrentGroupData.ShapeStartID;
	this->CurrentShape.ShapeGroupCount = CurrentGroupData.Count;

	//Attribute Setup
	this->CurrentGroupData.Color = { 1.0, 1.0, 1.0, 1.0 };
	this->CurrentGroupData.Size = { 0.0, 0.0 }; // all of the xadvances of all the text
	this->CurrentGroupData.Position = Position;
	this->CurrentGroupData.MouseAccess = true;
	this->CurrentGroupData.Highlighted = false;
	this->CurrentGroupData.Centered = false;

	this->CurrentGroupData.XYShapesPerRow = { 2.0, 2.0 }; // Can use without
	this->CurrentGroupData.ShapeDataSize = { 0.8, 0.8 };  // Can use without

	AddText();
}

void Text::AddText()
{
	//Set's the groupdata to the shape
	SetShape();
	CreateText();
	SetMouseAccess();
}

//Loads Group Data to Shape 
void Text::SetShape()
{
	//Group Details
	CurrentShape.ShapeGroupStart = this->CurrentGroupData.ShapeStartID;
	CurrentShape.GroupID = CurrentGroupData.GroupID;
	
	CurrentShape.ShapeGroupCount = CurrentGroupData.Count -1;
	CurrentShape.ShapeGroupPosition = this->CurrentGroupData.Position;
	CurrentShape.ShapeGroupSize = this->CurrentGroupData.Size;
	CurrentShape.ShapeGroupColor = this->CurrentGroupData.Color;
	CurrentShape.ShapeGroupMouseAccess = this->CurrentGroupData.MouseAccess;
	CurrentShape.ShapeGroupCentered = this->CurrentGroupData.Centered;

	CurrentShape.PageGroupItemPosition = CurrentGroupData.PageItemPosition;
	CurrentShape.PageGroupItemPosition = CurrentGroupData.PageItemSize;
	CurrentShape.PageGroupItemShapeCount = CurrentGroupData.PageItemShapeCount;
	CurrentShape.PageGroupItemID = CurrentGroupData.PageItemID;
	CurrentShape.PageGroupItemShapeOffset = CurrentGroupData.PageItemShapeOffset;
	CurrentShape.PageGroupItemShapeStartID = CurrentGroupData.PageItemShapeStartID;

	//CurrentShape.ShapeGroupRight = CurrentGroupData.Position[0] + CurrentGroupData.Size[0]/2;
	//CurrentShape.ShapeGroupLeft = CurrentGroupData.Position[0] - CurrentGroupData.Size[0] / 2;
	//CurrentShape.ShapeGroupTop = CurrentGroupData.Position[1] + CurrentGroupData.Size[1] / 2;
	//CurrentShape.ShapeGroupBottom = CurrentGroupData.Position[1] - CurrentGroupData.Size[1] / 2;

	//Shape Details
	CurrentShape.PartOfGroup = true;
	CurrentShape.Color = CurrentGroupData.Color;
	CurrentShape.ActiveTexture = CurrentTextData.FontSlot;
	CurrentShape.ShapeDataType = TYPE_TEXT;

	//Text Details
	CurrentShape.Text = CurrentTextData.Phrase;
	CurrentShape.ShapeDataType = TYPE_TEXT;
	CurrentShape.TextCentered = CurrentTextData.Centered;
	CurrentShape.EndStart = CurrentTextData.EndStart;
}

bool Text::QueryLineRestart(glm::vec2 CursorPosition, float MaxLine)
{
	//Pixel to computer
	glm::vec2 PositionInComputer = ApplyPositionConversion(CursorPosition, P_PIXEL_TO_COMPUTER);
	//float Max = xPos + 10;
	if (PositionInComputer[0] > MaxLine)
	{
		return true;
	}
	else
	{
		return false;
	}

}

//Returns how much the cursor has been advanced
float Text::AdvanceCursor(CharacterData& CharacterData, TextData& TextData)
{
	float SmoothingReduction = 1.19;
	float ScaleSize = TextData.FontSize * SmoothingReduction / CharacterData.LineHeight;
	float AdvanceWidth = (CharacterData.CharWidth + 2) * ScaleSize; //In Pixels
	TextData.CursorPosition[0] += AdvanceWidth;
	return AdvanceWidth;
}

//Takesin line height from textfile
//returns a position
glm::vec2 Text::NextLine(glm::vec2 StartPosition, CharacterData CharacterData, glm::vec2 CurrentPosition, float FontSize, float Spacing, float xStart)
{

	float Reverse = 1.5 - Spacing;
	float NextLine = (CharacterData.LineHeight / CharacterData.AtlasHeight) * (FontSize / Reverse); //1.5
	float FinalyPos = CurrentPosition[1] - NextLine;
	CurrentPosition[0] = xStart;
	cout << "NextLine-----" << endl;
	return { StartPosition[0], FinalyPos };
}

// for translation
glm::vec2 Text::GetCharacterPosition(CharacterData& CharacterData, glm::vec2 Pos, float FontSize, bool LineStart)
{
	//float FinalxPos = Pos[0];
	//if (LineStart == false)
	//{
	//	float xAdvance = (CharacterData.xOffset / CharacterData.AtlasWidth) * FontSize;
	//	FinalxPos = Pos[0] + xAdvance;
	//}
	//float yAdvance = (CharacterData.yOffset / CharacterData.AtlasHeight) * FontSize;
	//float FinalyPos = Pos[1] - yAdvance;

	float SmoothingReduction = 1.19; // 84% Reduction
	float ScaleSize = FontSize  * SmoothingReduction / CharacterData.LineHeight;

	float AspectRatio = 2.1; //?
	//CharacterData.Advance/2
    Pos[0] += ((CharacterData.CharWidth / 2)) * ScaleSize;//CharacterData.xOffset;// * ScaleSize;// + CurrentTextData.CharSpacing;
	Pos[1] += (CharacterData.yOffset) * ScaleSize;// * ScaleSize;// AspectRatio;

	return Pos;
}


//we need the size of each box, as well as the actual positions
glm::vec2 Text::GetCharacterSize(CharacterData& CharacterData, glm::vec2 CharPosition, int SCR_Height, int SCR_Width, float FontSize)
{
	//float AspectRatio = SCR_Width / SCR_Height;

	//int CharHeight = CharacterData.CharHeight;
	//int CharWidth = CharacterData.CharWidth;
	//int AtlasHeight = CharacterData.AtlasHeight; //500 pixels
	//int AtlasWidth = CharacterData.AtlasWidth; //500 pixels
	//
	//float xStep1 = CharWidth / 2;
	//float yStep1 = CharHeight / 2;
	//float xStep2 = xStep1 / AtlasHeight;
	//float yStep2 = yStep1 / AtlasWidth;
	//float xSize = xStep2 * FontSize;
	//float ySize = yStep2 * AspectRatio * FontSize;
	float SmoothingReduction = 1.19; // 84% Reduction
	float ScaleFactor = FontSize * SmoothingReduction / CharacterData.LineHeight; //Ex: 100 / 76 == Scale Factor of 1.31

	//In Pixels
	float x = CharacterData.CharWidth * ScaleFactor; //Ex: 35 * 1.31 = Size	Based off line height
	float y = CharacterData.CharHeight * ScaleFactor; //Ex 25 * 1.31 = Size Based off line height


	//In Pixels
	//float x = (CharacterData.CharWidth / CharacterData.LineHeight) * FontSize;
	//float y = (CharacterData.CharHeight/ CharacterData.LineHeight) * FontSize;
	//cout << x << " , " << y  << endl;
	return { x, y };
}

//Shape is already set
void Text::CreateText()
{
	int SCR_HEIGHT = 600;
	int SCR_WIDTH = 1200;
	int ShapeOffset = 0;
	bool LineRestart = true;
	float Maxline = 1.0;
	glm::vec2 StartPosition = CurrentGroupData.Position;
	
	////////////////////////////////////
	ShapeData TempShapex;
	ShapeData TempShapey;
	TempShapex.Size = ApplySizeConversion({4000, 1}, S_PIXEL_TO_COMPUTER);
	TempShapey.Size = ApplySizeConversion({1, 4000}, S_PIXEL_TO_COMPUTER);
	TempShapex.Centered = true;
	TempShapey.Centered = true;
	
	ShapeData TempShapeX;
	ShapeData TempShapeY;
	TempShapeX.Size = ApplySizeConversion({ 300, 1 }, S_PIXEL_TO_COMPUTER);
	TempShapeY.Size = ApplySizeConversion({ 1, 300 }, S_PIXEL_TO_COMPUTER);
	TempShapeX.Centered = true;
	TempShapeY.Centered = true;
	////////////////////////////////////
	SetTextSize();


	if (CurrentTextData.EndStart != true && CurrentTextData.Centered == true )
	{
		StartPosition[0] -= CurrentGroupData.Size[0] / 2;
	}

	if (CurrentTextData.EndStart == true && CurrentTextData.Centered != true)
	{
		StartPosition[0] -= CurrentGroupData.Size[0];
	}


	CurrentTextData.CursorPosition = ApplyPositionConversion(StartPosition, P_COMPUTER_TO_PIXEL);

	glm::vec4 CharLineColor = {0.3, 0.5, 0.4, 1.0};

	//Text Loop
	for (int n = 0; n < CurrentTextData.Phrase.size(); n++)
	{
		char CurrentChar = CurrentTextData.Phrase[n];

		CurrentCharacterData = NewCharacter::GetCharacter(CurrentChar);
		//Retreives Character information from file
		CurrentShape.GroupID = CurrentGroupData.GroupID;
		CurrentShape.Ascii = CurrentChar;
		CurrentShape.Position = GetCharacterPosition(CurrentCharacterData, CurrentTextData.CursorPosition, CurrentTextData.FontSize, LineRestart);
		CurrentShape.Size     = GetCharacterSize(CurrentCharacterData, CurrentShape.Position, SCR_HEIGHT, SCR_WIDTH, CurrentTextData.FontSize);

		// Debug Suggestion
		//CurrentShape.Position = ApplyPositionConversion(CurrentShape.Position, P_TOP_LEFT_TO_MIDDLE, CurrentShape.Size);

		//Apply Conversions
		CurrentShape.Position = ApplyPositionConversion(CurrentShape.Position, P_PIXEL_TO_COMPUTER);
		CurrentShape.Size = ApplySizeConversion(CurrentShape.Size, S_PIXEL_TO_COMPUTER);
		CurrentShape.ShapeGroupOffset = ShapeOffset;
		CurrentShape.PageGroupItemShapeOffset = CurrentGroupData.PageItemShapeOffset++;

		//Char Position
		TempShapeX.Position = CurrentShape.Position;
		TempShapeY.Position = CurrentShape.Position;
		//CharLineColor[2] += 0.25;
		TempShapeX.Color = {0.0, 1.0, 0.0, 1.0 }; //Green
		TempShapeY.Color = {0.0, 1.0, 0.0, 1.0 }; //Green
	    //Quad CharPositionX(*CurrentGroupData.Page, TempShapeX);
	    //Quad CharPositionY(*CurrentGroupData.Page, TempShapeY);
		

		//Cursor Position
		TempShapex.Position = ApplyPositionConversion(CurrentTextData.CursorPosition, P_PIXEL_TO_COMPUTER);
		TempShapey.Position = ApplyPositionConversion(CurrentTextData.CursorPosition, P_PIXEL_TO_COMPUTER);
		TempShapex.Color = { 0.5, 0.0, 1.0, 1.0 }; //Purple
		TempShapey.Color = { 0.5, 0.0, 1.0, 1.0 }; //Purple
		//Quad CursorX(*CurrentGroupData.Page, TempShapex);
		//Quad CursorY(*CurrentGroupData.Page, TempShapey);
		UpdateMouseAccess(CurrentShape.Position, CurrentShape.Size);
		NewCharacter Char_Text(*CurrentGroupData.Page, CurrentShape);
	
		//Cursor Position is still in pixel space
	
		//////Checks if line needs to be returned 
		//LineRestart = QueryLineRestart(CurrentTextData.CursorPosition, Maxline);

		//Cusror still in pixels

	    //In pixels
	//	CurrentGroupData.Size[0] += AdvanceCursor(CurrentCharacterData, CurrentTextData);
		AdvanceCursor(CurrentCharacterData, CurrentTextData);
	//	CurrentGroupData.Size[1] = CurrentTextData.FontSize / CurrentCharacterData.LineHeight;
		
		//LineRestart = QueryLineRestart(CurrentTextData.CursorPosition, Maxline);
		//if (CurrentTextData.List == false)
		//{
		//	if (LineRestart == true)
		//	{   ////Move CursorPosition to the next line
		//		CurrentTextData.CursorPosition = NextLine(StartPosition, CurrentCharacterData, CurrentTextData.CursorPosition, CurrentTextData.FontSize, CurrentTextData.CharSpacing, CurrentGroupData.Position[0]);
		//	}
		//}
		//else
		//{
		//	//Next Line if Space
		//	if (FullTextString[n - 1] == ' ' && FullTextString[n] == ' ' && FullTextString[n + 1] != ' ')
		//	{   ////Move CursorPosition to the next line
		//		CurrentTextData.CursorPosition = NextLine(StartPosition, CurrentCharacterData, CurrentTextData.CursorPosition, CurrentTextData.FontSize, CurrentTextData.LineSpacing, CurrentGroupData.Position[0]);
		//	}
		//}
		ShapeOffset++;
	}


}

void Text::NewReplaceText()
{
	//cout << "REPLACE COLOR " << CurrentGroupData.Color[0] << " , " << CurrentGroupData.Color[1] << " , " << CurrentGroupData.Color[2] << " , " << CurrentGroupData.Color[3] << " , " << endl;
	int SCR_HEIGHT = 600;
	int SCR_WIDTH = 1200;
	int CurrentID = CurrentGroupData.ShapeStartID;
	int ShapeOffset = 0;
	glm::vec2 StartPosition = CurrentGroupData.Position;

	bool LineRestart = true;
	float Maxline;

	const char* FullTextString = CurrentTextData.Phrase.c_str();

	SetTextSize();

	if (CurrentTextData.Centered == true && CurrentTextData.EndStart != true)
	{
		StartPosition[0] -= CurrentGroupData.Size[0] / 2;
	}

	if (CurrentTextData.EndStart == true && CurrentTextData.Centered != true)
	{
		StartPosition[0] -= CurrentGroupData.Size[0];
	}

	CurrentTextData.CursorPosition = ApplyPositionConversion(StartPosition, P_COMPUTER_TO_PIXEL);

	NewCharacter TextCharacter(*CurrentGroupData.Page, CurrentID);
	//Text Loop
	for (int n = 0; n < CurrentTextData.Phrase.size(); n++)
	{
		char CurrentChar = CurrentTextData.Phrase[n];
		CurrentCharacterData = NewCharacter::GetCharacter(CurrentChar);
		
		//Retreives Character information from file
		TextCharacter.SwitchToShape(CurrentID); // Working
		CurrentShape.ID = CurrentID;
		CurrentShape.Ascii = CurrentChar;
		CurrentShape.Position = GetCharacterPosition(CurrentCharacterData, CurrentTextData.CursorPosition, CurrentTextData.FontSize, LineRestart);
		CurrentShape.Size = GetCharacterSize(CurrentCharacterData, CurrentShape.Position, SCR_HEIGHT, SCR_WIDTH, CurrentTextData.FontSize);

		CurrentShape.Position = ApplyPositionConversion(CurrentShape.Position, P_PIXEL_TO_COMPUTER);
		CurrentShape.Size = ApplySizeConversion(CurrentShape.Size, S_PIXEL_TO_COMPUTER);
		CurrentShape.ShapeGroupOffset = ShapeOffset;
		CurrentShape.PageGroupItemShapeOffset = CurrentGroupData.PageItemShapeOffset++;
		cout << "ReplacedColor: " << CurrentShape.Color[0] << " , " << CurrentShape.Color[1] << " , " << CurrentShape.Color[2] << " , "<< CurrentShape.Color[3] << " , " << endl;
		UpdateMouseAccess(CurrentShape.Position, CurrentShape.Size);
		TextCharacter.SetShape(CurrentShape);

		////Checks if line needs to be returned 
		//LineRestart = QueryLineRestart(CurrentTextData.CursorPosition, Maxline);

		//CurrentGroupData.Size[0] += AdvanceCursor(CurrentCharacterData, CurrentTextData);
		AdvanceCursor(CurrentCharacterData, CurrentTextData);
		//CurrentGroupData.Size[1] = CurrentTextData.FontSize / CurrentCharacterData.LineHeight;
		//LineRestart = QueryLineRestart(CurrentTextData.CursorPosition, Maxline);
		//if (CurrentTextData.List == false)
		//{
		//	if (LineRestart == true)
		//	{   ////Move CursorPosition to the next line
		//		CurrentTextData.CursorPosition = NextLine(StartPosition, CurrentCharacterData, CurrentTextData.CursorPosition, CurrentTextData.FontSize, CurrentTextData.CharSpacing, CurrentGroupData.Position[0]);
		//	}
		//}
		//else
		//{
		//	//Next Line if Space
		//	if (FullTextString[n - 1] == ' ' && FullTextString[n] == ' ' && FullTextString[n + 1] != ' ')
		//	{   ////Move CursorPosition to the next line
		//		CurrentTextData.CursorPosition = NextLine(StartPosition, CurrentCharacterData, CurrentTextData.CursorPosition, CurrentTextData.FontSize, CurrentTextData.LineSpacing, CurrentGroupData.Position[0]);
		//	}
		//}
		ShapeOffset++;
		CurrentID++;
	}
}

void Text::SetText(string Text)
{
	//ReCalibrateID();

	int NewCount = Text.size();
	
	int OldCount = CurrentGroupData.Count;
	
	int NumShapesToAlter = NewCount - OldCount;
	cout << "-----------------------" << endl;
	cout << "New Count: " << NewCount << endl;
	cout << "Old Count: " << OldCount << endl;
	cout << "Num Shapes to alter: " << NumShapesToAlter << endl;
	cout << "-----------------------" << endl;
	CurrentGroupData.Count = NewCount;
	CurrentTextData.Phrase = Text;

	//Add More Shapes
	if (NumShapesToAlter > 0)
	{
		CurrentGroupData.Page->InsertShapeArray(CurrentGroupData.ShapeStartID, NumShapesToAlter);
	}
	//RemoveShapes
	else if (NumShapesToAlter < 0)
	{
		CurrentGroupData.Page->DeleteShapeArray(CurrentGroupData.ShapeStartID, (NumShapesToAlter * -1));
	}
	Update();
}

void Text::SetFont(int FontSize)
{
	ReCalibrateID();
	CurrentTextData.FontSize = FontSize;
	Update();
}


void Text::OffsetFont(int FontSize)
{
	ReCalibrateID();
	CurrentTextData.FontSize += FontSize;
	Update();
	cout << "FontSize: " << CurrentTextData.FontSize << endl;
}

void Text::Update()
{
	SetShape();
	NewReplaceText();
	SetMouseAccess();
}

void Text::SetTextSize()
{
	float TextWidth = 0.0;
	float SmoothingReduction = 1.19;
	for (int n = 0; n < CurrentTextData.Phrase.size(); n++)
	{
		CharacterData CurrentChar = NewCharacter::GetCharacter(CurrentTextData.Phrase[n]);
		
		float ScaleSize = CurrentTextData.FontSize * SmoothingReduction / CurrentChar.LineHeight;
		float AdvanceWidth = (CurrentChar.CharWidth + 2) * ScaleSize; //In Pixels
		TextWidth += AdvanceWidth;
	}
	
	CurrentGroupData.Size = ApplySizeConversion({TextWidth, CurrentTextData.FontSize }, S_PIXEL_TO_COMPUTER);
	CurrentShape.ShapeGroupSize = CurrentGroupData.Size;
}

//GroupData must have an initialized ID
void Text::SetTextGroup(GroupData& GroupData, TextData& TextData)
{
	////for some reason if you put > -1 instead of != -1 it doesnt work 
	if (GroupData.ShapeStartID != -1 && GroupData.ShapeStartID < CurrentGroupData.Page->ShapeAmount())
	{
		SetText(TextData.Phrase);
		CurrentGroupData = GroupData;
		CurrentTextData = TextData;
		CurrentGroupData.Count = CurrentTextData.Phrase.size();
		Update();
	}
	else
	{
		cout << "ERROR::SETTEXTGROUP()::ID not set " << GroupData.ShapeStartID << endl;
	}
}

void Text::ShapeToGroup(ShapeData& ShapeData)
{
	CurrentGroupData.ShapeStartID = ShapeData.ID;
	CurrentGroupData.GroupID = ShapeData.GroupID;
	CurrentGroupData.Count = ShapeData.ShapeGroupCount + 1;
	CurrentGroupData.XYShapesPerRow = ShapeData.ShapeGroupXYShapePerRow;
	CurrentGroupData.ShapeDataSize = ShapeData.ShapeGroupShapeSize;
	CurrentGroupData.Position = ShapeData.ShapeGroupPosition;
	CurrentGroupData.Size = ShapeData.ShapeGroupSize;
	CurrentGroupData.Color = ShapeData.ShapeGroupColor;
	CurrentGroupData.MouseAccess = ShapeData.ShapeGroupMouseAccess;
	CurrentGroupData.Centered = ShapeData.ShapeGroupCentered;
	CurrentGroupData.Highlighted = ShapeData.ShapeGroupHighlighted;
	CurrentGroupData.ShapeType = ShapeData.ShapeDataType;

	CurrentGroupData.PageItemID = ShapeData.PageGroupItemID;
	CurrentGroupData.PageItemShapeCount = ShapeData.PageGroupItemShapeCount;
	CurrentGroupData.PageItemShapeOffset = ShapeData.PageGroupItemShapeOffset;
	CurrentGroupData.PageItemShapeStartID = ShapeData.PageGroupItemShapeStartID;


}








































































































//Text::Text()
//{
//}
//
//void Text::ChangeVector2(int TextStart, glm::vec2 Vector, glm::vec2 Position, glm::vec4 Color)
//{
//	Element* Check = CurrentPage->GetElement(TextStart);
//
//
//
//	//Vector
//	float x = Vector[0];
//	float y = Vector[1];
//
//	//SubStrings
//	string X = "  X: ";
//	string Y = "  Y: ";
//	string floatx = to_string(x);
//	string floaty = to_string(y);
//
//	//Display 5 Characters only
//	floatx.erase(5);
//	floaty.erase(5);
//
//	string NewText = X + floatx + Y + floaty;
//
//	if (Check->Text != NewText || Check->ShapeGroupPosition != Position)
//	{
//		TextSpecification NewVector2(NewText, Position, false, Color);
//		NewVector2.Start = TextStart;
//		NewVector2.Count = NewText.size();
//
//		ReplaceTextBox(NewVector2);
//	}
//
//}
//
//void Text::ChangeVector3(int TextStart, glm::vec2 Vector, glm::vec2 Position, glm::vec4 Color)
//{
//	Element* Check = GetElement(TextStart);
//	//Vector
//	float x = Vector[0];
//	float y = Vector[1];
//	float z = Vector[2];
//
//	//SubStrings
//	string X = "  X: ";
//	string Y = "  Y: ";
//	string Z = "  Z: ";
//	string floatx = to_string(x);
//	string floaty = to_string(y);
//	string floatz = to_string(z);
//
//	//Display 5 Characters only
//	floatx.erase(5);
//	floaty.erase(5);
//	floatz.erase(5);
//
//	string NewText = X + floatx + Y + floaty + Z + floatz;
//	if (Check->Text != NewText || Check->ShapeGroupPosition != Position)
//	{
//		TextSpecification NewVector3(NewText, Position, false, Color);
//		NewVector3.Start = TextStart;
//		ReplaceTextBox(NewVector3);
//	}
//}
//
//void Text::ChangeVector4(int TextStart, glm::vec4 Vector, glm::vec2 Position, glm::vec4 Color)
//{
//	Element* Check = GetElement(TextStart);
//	//Vector
//	float r = Vector[0];
//	float g = Vector[1];
//	float b = Vector[2];
//	float a = Vector[3];
//
//	//SubStrings
//	string R = "  R ";
//	string G = "  G ";
//	string B = "  B ";
//	string A = "  A ";
//	string floatr = to_string(r);
//	string floatg = to_string(g);
//	string floatb = to_string(b);
//	string floata = to_string(a);
//
//	//Display 5 Characters only
//	floatr.erase(5);
//	floatg.erase(5);
//	floatb.erase(5);
//	floata.erase(5);
//
//	string NewText = R + floatr + G + floatg + B + floatb + A + floata;
//	if (Check->Text != NewText || Check->ShapeGroupPosition != Position)
//	{
//		TextSpecification NewVector4(NewText, Position, false, Color);
//		NewVector4.Count = NewText.size();
//		NewVector4.Start = TextStart;
//		ReplaceTextBox(NewVector4);
//	}
//}
//
//void Text::ChangeFloat(int TextStart, float Float, glm::vec2 Position, glm::vec4 Color)
//{
//	Element* Check = GetElement(TextStart);
//	//Vector
//	float x = Float;
//
//	string floatx = to_string(x);
//
//	string Devision = " ";
//
//
//	//Display 5 Characters only
//	floatx.erase(5);
//
//	string NewText = Devision + floatx;
//	if (Check->Text != NewText || Check->ShapeGroupPosition != Position)
//	{
//		TextSpecification NewFloat1(NewText, Position, false, Color);
//		NewFloat1.Count = NewText.size();
//		NewFloat1.Start = TextStart;
//		ReplaceTextBox(NewFloat1);
//	}
//}
//
//void Text::ChangeInt(int TextStart, int Int, glm::vec2 Position, glm::vec4 Color)
//{
//	Element* Check = GetElement(TextStart);
//	//Vector
//	int x = Int;
//
//	string Intx = to_string(x);
//	string Text;
//
//	string Zero = " ";
//
//	if (Intx.size() == 1)
//	{
//		Text = Zero + Zero + Zero + Intx;
//	}
//
//	if (Intx.size() == 2)
//	{
//		Text = Zero + Zero + Intx;
//	}
//
//	if (Intx.size() == 3)
//	{
//		Text = Zero + Intx;
//	}
//
//	if (Intx.size() == 4)
//	{
//		Text = Intx;
//	}
//
//	if (Intx.size() > 4)
//	{
//		Text = Intx.erase(4);
//	}
//
//	if (Check->Text != Text || Check->ShapeGroupPosition != Position)
//	{
//		TextSpecification Int1(Text, Position, false, Color);
//		Int1.Count = Text.size();
//		Int1.Start = TextStart;
//		ReplaceTextBox(Int1);
//	}
//}
//
//int Text::PrintVector2(glm::vec2 Vector, glm::vec2 Position, glm::vec4 Color)
//{
//	int ID = Amount();
//	//Vector
//	float x = Vector[0];
//	float y = Vector[1];
//
//	//SubStrings
//	string X = "  X: ";
//	string Y = "  Y: ";
//	string floatx = to_string(x);
//	string floaty = to_string(y);
//
//	//Display 5 Characters only
//	floatx.erase(5);
//	floaty.erase(5);
//
//	string Text = X + floatx + Y + floaty;
//	TextSpecification Vector2(Text, Position, false, Color);
//
//	AddTextBox(Vector2);
//
//	return ID;
//}
//
//int Text::PrintVector3(glm::vec3 Vector, glm::vec2 Position, glm::vec4 Color)
//{
//	int ID = Amount();
//	//Vector
//	float x = Vector[0];
//	float y = Vector[1];
//	float z = Vector[2];
//
//	//SubStrings
//	string X = "  X: ";
//	string Y = "  Y: ";
//	string Z = "  Z: ";
//	string floatx = to_string(x);
//	string floaty = to_string(y);
//	string floatz = to_string(z);
//
//	//Display 5 Characters only
//	floatx.erase(5);
//	floaty.erase(5);
//	floatz.erase(5);
//
//
//	string Text = X + floatx + Y + floaty + Z + floatz;
//	TextSpecification Vector3(Text, Position, false, Color);
//	AddTextBox(Vector3);
//
//	return ID;
//}
//
//int Text::PrintVector4(glm::vec4 Vector, glm::vec2 Position, glm::vec4 Color)
//{
//	int ID = Amount();
//	//Vector
//	float r = Vector[0];
//	float g = Vector[1];
//	float b = Vector[2];
//	float a = Vector[3];
//
//	//SubStrings
//	string R = "  R ";
//	string G = "  G ";
//	string B = "  B ";
//	string A = "  A ";
//	string floatr = to_string(r);
//	string floatg = to_string(g);
//	string floatb = to_string(b);
//	string floata = to_string(a);
//
//	//Display 5 Characters only
//	floatr.erase(5);
//	floatg.erase(5);
//	floatb.erase(5);
//	floata.erase(5);
//
//	string Text = R + floatr + G + floatg + B + floatb + A + floata;
//	TextSpecification Vector4(Text, Position, false, Color);
//	AddTextBox(Vector4);
//
//	return ID;
//}
//
//int Text::PrintFloat(float Float, glm::vec2 Position, glm::vec4 Color)
//{
//	int ID = Amount();
//	//Vector
//	float x = Float;
//
//	string floatx = to_string(x);
//
//	string Devision = "  ";
//
//	//Display 5 Characters only
//	floatx.erase(5);
//
//	string Text = Devision + floatx;
//	TextSpecification Float1(Text, Position, false, Color);
//	AddTextBox(Float1);
//
//	return ID;
//}
//
//int Text::PrintInt(int Int, glm::vec2 Position, glm::vec4 Color)
//{
//	int ID = Amount();
//	//Vector
//	int x = Int;
//
//	string Intx = to_string(x);
//	string Text;
//	string Zero = " ";
//
//	if (Intx.size() == 1)
//	{
//		Text = Zero + Zero + Zero + Intx;
//	}
//
//	if (Intx.size() == 2)
//	{
//		Text = Zero + Zero + Intx;
//	}
//
//	if (Intx.size() == 3)
//	{
//		Text = Zero + Intx;
//	}
//
//	if (Intx.size() == 4)
//	{
//		Text = Intx;
//	}
//
//	if (Intx.size() > 4)
//	{
//		Text = Intx.erase(4);
//	}
//	TextSpecification Int1(Text, Position, false, Color);
//	AddTextBox(Int1);
//
//	return ID;
//}
//
//int Text::PrintBool(bool Bool, glm::vec2 Position, glm::vec4 Color)
//{
//	int ID = Amount();
//	string Boolx;
//
//	//Vector
//	if (Bool == true)
//	{
//		Boolx = "True ";
//	}
//	else
//	{
//		Boolx = "False";
//	}
//
//	string Devision = "  ";
//
//
//	string Text = Devision + Boolx;
//	TextSpecification Bool1(Text, Position, false, Color);
//	AddTextBox(Bool1);
//
//	return ID;
//}
//
//void Text::LoadText(Page* Page, int ElementID)
//{
//	Element* ElementDetails = Page->GetElement(ElementID);
//
//	//Text Details
//	this->XYElementsPerRow = ElementDetails->GridXYShapePerRow;
//	this->ElementSize = ElementDetails->GridShapeSize;
//
//	//Group Details
//	this->ElementGroupStart = Page->ShapeContainer.StartOfContainer + ElementDetails->GroupStart;
//	this->ElementGroupCount = ElementDetails->GroupCount;
//	this->NextElementGroup = ElementDetails->NextElementGroup;
//	this->ShapeGroupPosition = ElementDetails->ShapeGroupPosition;
//	this->ShapeGroupSize = ElementDetails->ShapeGroupSize;
//	this->ShapeGroupColor = ElementDetails->ShapeGroupColor;
//	this->MouseAccess = ElementDetails->MouseAccess;
//	this->Centered = ElementDetails->Centered;
//	this->Higlighted = ElementDetails->Highlighted;
//	this->GroupType = ElementDetails->ElementType;
//}