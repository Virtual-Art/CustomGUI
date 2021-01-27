#include "Text.h"

Text::Text(Page& Page)
 : ShapeGroup{Page}
{
	//DefaultTextData
	CurrentTextData.Phrase = "TEXT";

	//Group Setup
	this->CurrentShapeGroup.ShapeCount = CurrentTextData.Phrase.size();

    //Attribute Setup
	this->CurrentShapeGroup.Color = { 1.0, 1.0, 1.0, 1.0 };
	this->CurrentShapeGroup.Size = { 0.0, 0.0 }; // all of the xadvances of all the text
	this->CurrentShapeGroup.Position = { 0.0, 0.0 };
	this->CurrentShapeGroup.MouseAccess = true;
	this->CurrentShapeGroup.Highlighted = false;
	this->CurrentShapeGroup.Centered = false;

	this->CurrentShapeGroup.XYShapePerRow = { 2.0, 2.0 }; // Can use without
	this->CurrentShapeGroup.ShapeSize = { 0.8, 0.8 };  // Can use without
	CurrentShapeGroup.Type = TYPE_TEXT;

	AddText();
}

//using this one in application.cpp
Text::Text(Page& Page, ShapeGroupData& ShapeGroupData, TextData& TextData)
	: ShapeGroup{ Page, ShapeGroupData}
{
	CurrentTextData = TextData;
	CurrentShapeGroup.ShapeCount = TextData.Phrase.size() - 1;
	CurrentShapeGroup.Type = TYPE_TEXT;
	
	AddText();
	ShapeGroupData.Size = CurrentShapeGroup.Size;
}

//using this one in application.cpp
Text::Text(Page& Page, ShapeData& ShapeData, TextData& TextData)
	: ShapeGroup{ Page, ShapeData }
{
	CurrentTextData = TextData;
	this->CurrentShapeGroup.ShapeStart = Page.ShapeAmount();
	this->CurrentShapeGroup.ShapeCount = TextData.Phrase.size() - 1;
	CurrentShapeGroup.Type = TYPE_TEXT;
	AddText();
	ShapeData.ShapeGroup.Size = CurrentShapeGroup.Size;
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
		this->CurrentShapeGroup.ShapeStart = Page.ShapeAmount();
		this->CurrentShapeGroup.ShapeCount = CurrentTextData.Phrase.size() - 1;

		//Set Shape Data
		this->CurrentShapeGroup.ShapeStart = CurrentShapeGroup.ShapeStart;
		this->CurrentShapeGroup.ShapeCount = CurrentShapeGroup.ShapeCount;

		//Attribute Setup
		this->CurrentShapeGroup.Color = { 1.0, 1.0, 1.0, 1.0 };
		this->CurrentShapeGroup.Size = { 0.0, 0.0 }; // all of the xadvances of all the text
		this->CurrentShapeGroup.Position = Position;
		this->CurrentShapeGroup.MouseAccess = true;
		this->CurrentShapeGroup.Highlighted = false;
		this->CurrentShapeGroup.Centered = false;

		this->CurrentShapeGroup.XYShapePerRow = { 2.0, 2.0 }; // Can use without
		this->CurrentShapeGroup.ShapeSize = { 0.8, 0.8 };  // Can use without

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

		this->CurrentShapeGroup.ShapeCount = CurrentTextData.Phrase.size() - 1;

		//Set Shape Data

		this->CurrentShapeGroup.ShapeCount = CurrentShapeGroup.ShapeCount;
	}
}

Text::Text(Page& Page, int GroupID)
	: ShapeGroup( Page, GroupID )
{
	if (&Page != nullptr)
	{
		CurrentPage = &Page;
		Initialized = true;
		//Set 1st shape of group
		if (IsInBounds(GroupID) == true)
		{
			//if (CurrentShapeGroup.Type == TYPE_TEXT)
			//{
			CurrentTextData.Phrase   = LoadedShape.Text;
			CurrentTextData.Centered = LoadedShape.TextCentered;
			CurrentTextData.EndStart = LoadedShape.EndStart;
			//}
			//else
			//{
			//	cout << "NEWTEXT::ERROR::Shape is not part of text " << endl;
			//	//Currentreset();
			//}
		}
		else
		{
			//Log::LogString("Text ID out of bounds");
		}
	}
	else
	{
		Log::LogString("Text Suspended");
	}
}


Text::Text(Page& Page, int Integer, string Description, glm::vec2 Position)
	: ShapeGroup{ Page }
{
	string FinalPhrase = Description + " " + to_string(Integer);
	//DefaultTextData
	CurrentTextData.Phrase = FinalPhrase;

	//Group Setup
	this->CurrentShapeGroup.ShapeStart = Page.ShapeAmount();
	this->CurrentShapeGroup.ShapeCount = CurrentTextData.Phrase.size();

	//Out Of Bounds Check
	if (Page.InBounds(Page.ShapeAmount() + CurrentShapeGroup.ShapeCount))
	{
		//this->CurrentShapeGroup.NextGroup = Page.GetNextShapeAddress(4);
	} //Default +4

	//Attribute Setup
	this->CurrentShapeGroup.Color = { 1.0, 1.0, 1.0, 1.0 };
	this->CurrentShapeGroup.Size = { 0.0, 0.0 }; // all of the xadvances of all the text
	this->CurrentShapeGroup.Position = Position;
	this->CurrentShapeGroup.MouseAccess = true;
	this->CurrentShapeGroup.Highlighted = false;
	this->CurrentShapeGroup.Centered = false;

	this->CurrentShapeGroup.XYShapePerRow = { 2.0, 2.0 }; // Can use without
	this->CurrentShapeGroup.ShapeSize = { 0.8, 0.8 };  // Can use without

	AddText();
}

//Text::Text(Page& Page, GroupData& GroupData, TextData& TextData, int Integer, string Description)
//	: ShapeGroup{ Page, GroupData }
//{
//	CurrentTextData = TextData;
//	CurrentTextData.Phrase = Description + " " + to_string(Integer);
//	this->CurrentShapeGroup.ShapeStart = Page.ShapeAmount();
//	this->CurrentShapeGroup.ShapeCount = TextData.Phrase.size();
//	this->CurrentShapeGroup.ShapeStart = CurrentShapeGroup.ShapeStart;
//	this->CurrentShapeGroup.ShapeCount = CurrentShapeGroup.ShapeCount;
//	AddText();
//	GroupData.Size = CurrentShapeGroup.Size;
//}
//
Text::Text() {};

Text::Text(Page& Page, int GroupID, int Integer, string Description)
	: ShapeGroup(Page, GroupID)
{

}

void Text::Init(Page& Page, string Text, glm::vec2 Position)
{
	CurrentPage = &Page;
	CurrentPage->TotalShapeGroupCount++;
	CurrentShapeGroup.ID = CurrentPage->TotalShapeGroupCount;

	//Set TextData
	CurrentTextData.Phrase = Text;
	CurrentTextData.CursorPosition = Position;
	//CurrentTextData.Centered = true;

	//Set Group Data
	this->CurrentShapeGroup.ShapeStart = Page.ShapeAmount();
	this->CurrentShapeGroup.ShapeCount = CurrentTextData.Phrase.size();

	//Set Shape Data
	//this->CurrentShapeGroup.ShapeStart = CurrentShapeGroup.ShapeStart;
	//this->CurrentShapeGroup.ShapeCount = CurrentShapeGroup.ShapeCount;

	//Attribute Setup
	this->CurrentShapeGroup.Color = { 1.0, 1.0, 1.0, 1.0 };
	this->CurrentShapeGroup.Size = { 0.0, 0.0 }; // all of the xadvances of all the text
	this->CurrentShapeGroup.Position = Position;
	this->CurrentShapeGroup.MouseAccess = true;
	this->CurrentShapeGroup.Highlighted = false;
	this->CurrentShapeGroup.Centered = false;

	this->CurrentShapeGroup.XYShapePerRow = { 2.0, 2.0 }; // Can use without
	this->CurrentShapeGroup.ShapeSize = { 0.8, 0.8 };  // Can use without

	AddText();
}

void Text::AddText()
{
	CreateText();
	SetMouseAccess();
}

//Loads Group Data to Shape 
void Text::SetShape()
{
	//Group Details
	//CurrentShapeGroup.ShapeStart = this->CurrentShapeGroup.ShapeStart;
	//CurrentGroupID = CurrentShapeGroup.GroupID;
	//
	//CurrentShapeGroup.ShapeCount = CurrentShapeGroup.ShapeCount -1;
	//CurrentShapeGroupPosition = this->CurrentShapeGroup.Position;
	//CurrentShapeGroupSize = this->CurrentShapeGroup.Size;
	//CurrentShapeGroupColor = this->CurrentShapeGroup.Color;
	//CurrentShapeGroupMouseAccess = this->CurrentShapeGroup.MouseAccess;
	//CurrentShapeGroupCentered = this->CurrentShapeGroup.Centered;
	//
	//CurrentPageGroupItemPosition = CurrentShapeGroup.PageItemPosition;
	//CurrentPageGroupItemPosition = CurrentShapeGroup.PageItemSize;
	//CurrentPageGroupItemShapeCount = CurrentShapeGroup.PageItemShapeCount;
	//CurrentPageGroupItemID = CurrentShapeGroup.PageItemID;
	//CurrentPageGroupItemShapeOffset = CurrentShapeGroup.PageItemShapeOffset;
	//CurrentPageItem.ShapeStart = CurrentPageItem.ShapeStart;

	//CurrentShapeGroupRight = CurrentShapeGroup.Position[0] + CurrentShapeGroup.Size[0]/2;
	//CurrentShapeGroupLeft = CurrentShapeGroup.Position[0] - CurrentShapeGroup.Size[0] / 2;
	//CurrentShapeGroupTop = CurrentShapeGroup.Position[1] + CurrentShapeGroup.Size[1] / 2;
	//CurrentShapeGroupBottom = CurrentShapeGroup.Position[1] - CurrentShapeGroup.Size[1] / 2;

	//Shape Details
	LoadedShape.PartOfGroup = true;
	LoadedShape.Color = CurrentShapeGroup.Color;
	LoadedShape.ActiveTexture = CurrentTextData.FontSlot;

	//Text Details
	LoadedShape.Text = CurrentTextData.Phrase;
	LoadedShape.ShapeGroup.Type = TYPE_TEXT;
	LoadedShape.TextCentered = CurrentTextData.Centered;
	LoadedShape.EndStart = CurrentTextData.EndStart;
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
	glm::vec2 StartPosition = CurrentShapeGroup.Position;
	
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
		StartPosition[0] -= CurrentShapeGroup.Size[0] / 2;
	}

	if (CurrentTextData.EndStart == true && CurrentTextData.Centered != true)
	{
		StartPosition[0] -= CurrentShapeGroup.Size[0];
	}

	LoadedShape.ShapeGroup = CurrentShapeGroup;
	CurrentTextData.CursorPosition = ApplyPositionConversion(StartPosition, P_COMPUTER_TO_PIXEL);

	glm::vec4 CharLineColor = {0.3, 0.5, 0.4, 1.0};

	//Text Loop
	for (int n = 0; n < CurrentTextData.Phrase.size(); n++)
	{
		char CurrentChar = CurrentTextData.Phrase[n];

		CurrentCharacterData = NewCharacter::GetCharacter(CurrentChar);
		//Retreives Character information from file
		//CurrentShapeGroup.ID = CurrentShapeGroup.ID;
	    LoadedShape.Ascii = CurrentChar;
	    LoadedShape.Position = GetCharacterPosition(CurrentCharacterData, CurrentTextData.CursorPosition, CurrentTextData.FontSize, LineRestart);
	    LoadedShape.Size     = GetCharacterSize(CurrentCharacterData, LoadedShape.Position, SCR_HEIGHT, SCR_WIDTH, CurrentTextData.FontSize);

		//Apply Conversions
		LoadedShape.Position = ApplyPositionConversion(LoadedShape.Position, P_PIXEL_TO_COMPUTER);
		LoadedShape.Size = ApplySizeConversion(LoadedShape.Size, S_PIXEL_TO_COMPUTER);
		//CurrentShapeGroup.ShapeOffset = ShapeOffset;
				//Shape Details
		LoadedShape.PartOfGroup = true;
		LoadedShape.Color = CurrentShapeGroup.Color;
		LoadedShape.ActiveTexture = CurrentTextData.FontSlot;
		LoadedShape.ShapeGroup.ShapeCount = CurrentTextData.Phrase.size() - 1;

		//Text Details
		LoadedShape.Text = CurrentTextData.Phrase;
		LoadedShape.ShapeGroup.Type = TYPE_TEXT;
		LoadedShape.TextCentered = CurrentTextData.Centered;
		LoadedShape.EndStart = CurrentTextData.EndStart;

		//Char Position
		TempShapeX.Position = LoadedShape.Position;
		TempShapeY.Position = LoadedShape.Position;
		//CharLineColor[2] += 0.25;
		TempShapeX.Color = {0.0, 1.0, 0.0, 1.0 }; //Green
		TempShapeY.Color = {0.0, 1.0, 0.0, 1.0 }; //Green
	    //Quad CharPositionX(*CurrentShapeGroup.Page, TempShapeX);
	    //Quad CharPositionY(*CurrentShapeGroup.Page, TempShapeY);
		
		
		//Cursor Position
		TempShapex.Position = ApplyPositionConversion(CurrentTextData.CursorPosition, P_PIXEL_TO_COMPUTER);
		
		TempShapey.Position = ApplyPositionConversion(CurrentTextData.CursorPosition, P_PIXEL_TO_COMPUTER);
		
		TempShapex.Color = { 0.5, 0.0, 1.0, 1.0 }; //Purple
		TempShapey.Color = { 0.5, 0.0, 1.0, 1.0 }; //Purple
		//Quad CursorX(*CurrentShapeGroup.Page, TempShapex);
		//Quad CursorY(*CurrentShapeGroup.Page, TempShapey);
		
		UpdateMouseAccess(LoadedShape.Position, LoadedShape.Size);
		NewCharacter Char_Text(*CurrentPage, LoadedShape);
		//CurrentPageItem.ShapeOffset++;
		
		//Cursor Position is still in pixel space
	
		//////Checks if line needs to be returned 
		//LineRestart = QueryLineRestart(CurrentTextData.CursorPosition, Maxline);

		//Cusror still in pixels

	    //In pixels
	//	CurrentShapeGroup.Size[0] += AdvanceCursor(CurrentCharacterData, CurrentTextData);
		AdvanceCursor(CurrentCharacterData, CurrentTextData);
	//	CurrentShapeGroup.Size[1] = CurrentTextData.FontSize / CurrentCharacterData.LineHeight;
		
		//LineRestart = QueryLineRestart(CurrentTextData.CursorPosition, Maxline);
		//if (CurrentTextData.List == false)
		//{
		//	if (LineRestart == true)
		//	{   ////Move CursorPosition to the next line
		//		CurrentTextData.CursorPosition = NextLine(StartPosition, CurrentCharacterData, CurrentTextData.CursorPosition, CurrentTextData.FontSize, CurrentTextData.CharSpacing, CurrentShapeGroup.Position[0]);
		//	}
		//}
		//else
		//{
		//	//Next Line if Space
		//	if (FullTextString[n - 1] == ' ' && FullTextString[n] == ' ' && FullTextString[n + 1] != ' ')
		//	{   ////Move CursorPosition to the next line
		//		CurrentTextData.CursorPosition = NextLine(StartPosition, CurrentCharacterData, CurrentTextData.CursorPosition, CurrentTextData.FontSize, CurrentTextData.LineSpacing, CurrentShapeGroup.Position[0]);
		//	}
		//}
		//ShapeOffset++;
	}
}

void Text::NewReplaceText()
{
	//cout << "REPLACE COLOR " << CurrentShapeGroup.Color[0] << " , " << CurrentShapeGroup.Color[1] << " , " << CurrentShapeGroup.Color[2] << " , " << CurrentShapeGroup.Color[3] << " , " << endl;
	int SCR_HEIGHT = 600;
	int SCR_WIDTH = 1200;
	int CurrentID = CurrentShapeGroup.ShapeStart;
	int ShapeOffset = 0;
	glm::vec2 StartPosition = CurrentShapeGroup.Position;

	bool LineRestart = true;
	float Maxline;

	const char* FullTextString = CurrentTextData.Phrase.c_str();


	SetTextSize();

	if (CurrentTextData.Centered == true && CurrentTextData.EndStart != true)
	{
		StartPosition[0] -= CurrentShapeGroup.Size[0] / 2;
	}

	if (CurrentTextData.EndStart == true && CurrentTextData.Centered != true)
	{
		StartPosition[0] -= CurrentShapeGroup.Size[0];
	}

	CurrentTextData.CursorPosition = ApplyPositionConversion(StartPosition, P_COMPUTER_TO_PIXEL);

	//CurrentShape.ShapeGroup = CurrentShapeGroup;
	LoadedShape.ShapeGroup = CurrentShapeGroup;

	//

	NewCharacter TextCharacter(*CurrentPage, 0);
	//Text Loop
	for (int n = 0; n < CurrentTextData.Phrase.size(); n++)
	{
		char CurrentChar = CurrentTextData.Phrase[n];
		CurrentCharacterData = NewCharacter::GetCharacter(CurrentChar);
		
		//Retreives Character information from file
		//if i load shape here it just overrides what i put through slider
		Log::LogInt("Editing" , CurrentID);
		TextCharacter.Switch(CurrentID); // Working
		LoadedShape.ID = CurrentID;
		LoadedShape.Ascii = CurrentChar;
		LoadedShape.Position = GetCharacterPosition(CurrentCharacterData, CurrentTextData.CursorPosition, CurrentTextData.FontSize, LineRestart);
		LoadedShape.Size = GetCharacterSize(CurrentCharacterData, LoadedShape.Position, SCR_HEIGHT, SCR_WIDTH, CurrentTextData.FontSize);
		

		LoadedShape.Position = ApplyPositionConversion(LoadedShape.Position, P_PIXEL_TO_COMPUTER);
		LoadedShape.Size = ApplySizeConversion(LoadedShape.Size, S_PIXEL_TO_COMPUTER);

		Log::LogVec2("Shape Position  y", LoadedShape.Position);

		CurrentPage->CurrentPageItemShapeCount++;
		LoadedShape.ShapeGroup.PageItem.ShapeOffset = CurrentPage->CurrentPageItemShapeCount;
		CurrentPage->CurrentPageGroupShapeCount++;
		LoadedShape.ShapeGroup.PageItem.PageGroup.ShapeOffset = CurrentPage->CurrentPageGroupShapeCount;
		LoadedShape.ShapeGroup.ShapeOffset = ShapeOffset;

		//Shape Details
		LoadedShape.PartOfGroup = true;
		LoadedShape.Color = CurrentShapeGroup.Color;
		LoadedShape.ActiveTexture = CurrentTextData.FontSlot;
		LoadedShape.ShapeGroup.ShapeCount = CurrentTextData.Phrase.size() - 1;

		//Text Details
		LoadedShape.Text = CurrentTextData.Phrase;
		LoadedShape.ShapeGroup.Type = TYPE_TEXT;
		LoadedShape.TextCentered = CurrentTextData.Centered;
		LoadedShape.EndStart = CurrentTextData.EndStart;

		

		UpdateMouseAccess(LoadedShape.Position, LoadedShape.Size);
		TextCharacter.SetShape(LoadedShape);

	    Log::LogString("Text in TextData: " + CurrentTextData.Phrase);
		Log::LogString("Text in Shape   : " + LoadedShape.Text);

		////Checks if line needs to be returned 
		//LineRestart = QueryLineRestart(CurrentTextData.CursorPosition, Maxline);

		//CurrentShapeGroup.Size[0] += AdvanceCursor(CurrentCharacterData, CurrentTextData);
		AdvanceCursor(CurrentCharacterData, CurrentTextData);
		//CurrentShapeGroup.Size[1] = CurrentTextData.FontSize / CurrentCharacterData.LineHeight;
		//LineRestart = QueryLineRestart(CurrentTextData.CursorPosition, Maxline);
		//if (CurrentTextData.List == false)
		//{
		//	if (LineRestart == true)
		//	{   ////Move CursorPosition to the next line
		//		CurrentTextData.CursorPosition = NextLine(StartPosition, CurrentCharacterData, CurrentTextData.CursorPosition, CurrentTextData.FontSize, CurrentTextData.CharSpacing, CurrentShapeGroup.Position[0]);
		//	}
		//}
		//else
		//{
		//	//Next Line if Space
		//	if (FullTextString[n - 1] == ' ' && FullTextString[n] == ' ' && FullTextString[n + 1] != ' ')
		//	{   ////Move CursorPosition to the next line
		//		CurrentTextData.CursorPosition = NextLine(StartPosition, CurrentCharacterData, CurrentTextData.CursorPosition, CurrentTextData.FontSize, CurrentTextData.LineSpacing, CurrentShapeGroup.Position[0]);
		//	}
		//}
		ShapeOffset++;
		CurrentID++;
	}
}

void Text::SetText(string Text)
{
	//ReCalibrateID();

	int NewCount = Text.size() - 1; //-1 added fyi
	
	int OldCount = CurrentShapeGroup.ShapeCount;
	
	int NumShapesToAlter = NewCount - OldCount;
	cout << "-----------------------" << endl;
	cout << "New Count: " << NewCount << endl;
	cout << "Old Count: " << OldCount << endl;
	cout << "Num Shapes to alter: " << NumShapesToAlter << endl;
	cout << "-----------------------" << endl;
	CurrentShapeGroup.ShapeCount = NewCount;
	CurrentTextData.Phrase = Text;

	//Add More Shapes
	if (NumShapesToAlter > 0)
	{
		CurrentPage->InsertShapeArray(CurrentShapeGroup.ShapeStart, NumShapesToAlter);
	}
	//RemoveShapes
	else if (NumShapesToAlter < 0)
	{
		CurrentPage->DeleteShapeArray(CurrentShapeGroup.ShapeStart, (NumShapesToAlter * -1));
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
	if (Initialized == false) return Log::LogString("Text Update Error:: Group Not Initialized");
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
	
	CurrentShapeGroup.Size = ApplySizeConversion({TextWidth, CurrentTextData.FontSize }, S_PIXEL_TO_COMPUTER);
}

//GroupData must have an initialized ID
void Text::SetTextGroup(ShapeData& ShapeData, TextData& TextData)
{
	////for some reason if you put > -1 instead of != -1 it doesnt work 
	if (ShapeData.ShapeGroup.ShapeStart != -1 && ShapeData.ShapeGroup.ShapeStart < CurrentPage->ShapeAmount())
	{

		int NewCount = TextData.Phrase.size() - 1; //-1 added fyi

		int OldCount = CurrentTextData.Phrase.size() - 1;// CurrentShapeGroup.ShapeCount;

		int NumShapesToAlter = NewCount - OldCount;
		cout << "-----------------------" << endl;
		cout << "New Count: " << NewCount << endl;
		cout << "Old Count: " << OldCount << endl;
		cout << "Num Shapes to alter: " << NumShapesToAlter << endl;
		cout << "-----------------------" << endl;


		//Add More Shapes
		if (NumShapesToAlter > 0)
		{
			CurrentPage->InsertShapeArray(CurrentShapeGroup.ShapeStart, NumShapesToAlter);
		}
		//RemoveShapes
		else if (NumShapesToAlter < 0)
		{
			CurrentPage->DeleteShapeArray(CurrentShapeGroup.ShapeStart, (NumShapesToAlter * -1));
		}

		LoadedShape = ShapeData;
		//SetText(TextData.Phrase);
		CurrentTextData = TextData;
		CurrentShapeGroup.ShapeCount = NewCount;
		Update();
	}
	else
	{
		cout << "ERROR::SETTEXTGROUP()::ID not set " << ShapeData.ShapeGroup.ShapeStart << endl;
	}
}

void Text::SetTextGroup(ShapeGroupData& ShapeGroup, TextData& TextData)
{
	////for some reason if you put > -1 instead of != -1 it doesnt work 
	if (ShapeGroup.ShapeStart != -1 && ShapeGroup.ShapeStart < CurrentPage->ShapeAmount())
	{
		CurrentShapeGroup = ShapeGroup;
		int NewCount = TextData.Phrase.size() - 1; //-1 added fyi
		int OldCount = CurrentTextData.Phrase.size() - 1;// CurrentShapeGroup.ShapeCount;

		int NumShapesToAlter = NewCount - OldCount;
		cout << "-----------------------" << endl;
		cout << "New Count: " << NewCount << endl;
		cout << "Old Count: " << OldCount << endl;
		cout << "Num Shapes to alter: " << NumShapesToAlter << endl;
		cout << "-----------------------" << endl;


		//Add More Shapes
		if (NumShapesToAlter > 0)
		{
			CurrentPage->InsertShapeArray(CurrentShapeGroup.ShapeStart, NumShapesToAlter);
		}
		//RemoveShapes
		else if (NumShapesToAlter < 0)
		{
			CurrentPage->DeleteShapeArray(CurrentShapeGroup.ShapeStart, (NumShapesToAlter * -1));
		}
		
		//SetText(TextData.Phrase);
		CurrentTextData = TextData;
		CurrentShapeGroup.ShapeCount = NewCount;
		Update();
	}
	else
	{
		cout << "ERROR::SETTEXTGROUP()::ID not set " << ShapeGroup.ShapeStart << endl;
	}
}

void Text::ShapeToGroup(ShapeData& ShapeData)
{
	//CurrentShapeGroup.ShapeStart = ShapeData.ID;
	//CurrentShapeGroup.GroupID = ShapeData.GroupID;
	//CurrentShapeGroup.ShapeCount = ShapeData.ShapeGroup.ShapeCount + 1;
	//CurrentShapeGroup.XYShapesPerRow = ShapeData.ShapeGroupXYShapePerRow;
	//CurrentShapeGroup.ShapeDataSize = ShapeData.ShapeGroupShapeSize;
	//CurrentShapeGroup.Position = ShapeData.ShapeGroupPosition;
	//CurrentShapeGroup.Size = ShapeData.ShapeGroupSize;
	//CurrentShapeGroup.Color = ShapeData.ShapeGroupColor;
	//CurrentShapeGroup.MouseAccess = ShapeData.ShapeGroupMouseAccess;
	//CurrentShapeGroup.Centered = ShapeData.ShapeGroupCentered;
	//CurrentShapeGroup.Highlighted = ShapeData.ShapeGroupHighlighted;
	//CurrentShapeGroup.ShapeType = ShapeData.ShapeDataType;
	//
	//CurrentShapeGroup.PageItemID = ShapeData.PageGroupItemID;
	//CurrentShapeGroup.PageItemShapeCount = ShapeData.PageGroupItemShapeCount;
	//CurrentShapeGroup.PageItemShapeOffset = ShapeData.PageGroupItemShapeOffset;
	//CurrentPageItem.ShapeStart = ShapeData.PageItem.ShapeStart;


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