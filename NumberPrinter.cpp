#include "NumberPrinter.h"

NumberPrinter::NumberPrinter(llBookData* llBook)
	:PageGroupItem(llBook)
{
	Button_NumberPrinter.Add_Mouse_Action(GUI_MOUSELEFT_CLICKED, NumberPrinterActions::SetKeyboardInput);
	CurrentllPageItem->PageItemButton = &Button_NumberPrinter;
	CurrentllPageItem->Color = { 1.0, 1.0, 1.0, 1.0 };
	CurrentllPageItem->Size = { 0.0, 0.0 }; // all of the xadvances of all the text
	CurrentllPageItem->Position = { 0.0, 0.0 };
	CurrentllPageItem->MouseAccess = true;
	CurrentllPageItem->Highlighted = false;
	CurrentllPageItem->Centered = false;
	CurrentllPageItem->XYShapePerRow = { 2.0, 2.0 }; // Can use without
	CurrentllPageItem->ShapeSize = { 0.8, 0.8 };  // Can use without
	CurrentllPageItem->Type = TYPE_PAGEITEM_NUMBER;
	CurrentllPageItem->NumberPrinterData = CurrentNumberPrinter;
	LoadedBook = llBook;
	CreateNumber();

	CurrentllPageItem->NumberPrinterData = CurrentNumberPrinter;
}

NumberPrinter::NumberPrinter(llBookData* llBook, llPageItemData* llPageItem, NumberPrinterData NumberPrinter)
	: PageGroupItem(llBook, llPageItem)
{
	Button_NumberPrinter.Add_Mouse_Action(GUI_MOUSELEFT_CLICKED, NumberPrinterActions::SetKeyboardInput);
	CurrentllPageItem->PageItemButton = &Button_NumberPrinter;
	CurrentNumberPrinter = NumberPrinter;
	CurrentllPageItem->Type = TYPE_PAGEITEM_NUMBER;
	CurrentllPageItem->NumberPrinterData = CurrentNumberPrinter;
	LoadedBook = llBook;
	CreateNumber();
	CurrentllPageItem->NumberPrinterData = CurrentNumberPrinter;
}

NumberPrinter::NumberPrinter(llPageItemData* llPageItem)
	: PageGroupItem(llPageItem)
{

}

void NumberPrinter::llInit(llBookData* llBook, llPageItemData* llPageItem, NumberPrinterData NumberPrinter)
{
	llPageItemInit(llBook, llPageItem);
	Button_NumberPrinter.Add_Mouse_Action(GUI_MOUSELEFT_CLICKED, NumberPrinterActions::SetKeyboardInput);
	CurrentllPageItem->PageItemButton = &Button_NumberPrinter;
	CurrentNumberPrinter = NumberPrinter;
	CurrentllPageItem->Type = TYPE_PAGEITEM_NUMBER;
	CurrentllPageItem->NumberPrinterData = CurrentNumberPrinter;
	CreateNumber();
	CurrentllPageItem->NumberPrinterData = CurrentNumberPrinter;
}

void NumberPrinter::llSwitch(llPageItemData* PageItem)
{
	CurrentllPageItem = PageItem;
	CurrentNumberPrinter = PageItem->NumberPrinterData;
	Parent_PageGroup = (llPageGroupData*)PageItem->ParentGroup;
	CalculateGroupOffset();
}

void NumberPrinter::SetString(const string& NewString)
{
	if (CurrentNumberPrinter.Type != TYPE_STRING) { Log::LogString("ERROR:: Printer Set String FAILED:: Type is Not String"); return; }
	if (CurrentNumberPrinter.String == nullptr) { Log::LogString("ERROR:: Printer Set String FAILED:: No String Provided"); return;}
	//if (*CurrentNumberPrinter.String == NewString) { return; }

	Log::LogString("Changing Too :" + NewString);

	//if the string already has a string in there that isn't "Description" don't change it to discription
	*CurrentNumberPrinter.String = NewString;


	Log::LogString("Changed TOO :" + *CurrentNumberPrinter.String);

	llUpdate();
}


string& NumberPrinter::GetCurrentString()
{
	if (CurrentNumberPrinter.String == nullptr) { Log::LogString("ERROR:: GetCurrentString FAILED:: No String Attached");  return Empty; }
	if (CurrentNumberPrinter.Type != TYPE_STRING) { Log::LogString("ERROR:: GetCurrentString FAILED:: Incorrect Type");  return Empty; }

	return *CurrentNumberPrinter.String;
}

void NumberPrinter::SetInt(const int& Int)
{
	if (CurrentNumberPrinter.Type != TYPE_INT) { return; }
	if (CurrentNumberPrinter.Integer == nullptr) { return; }

	*CurrentNumberPrinter.Integer = Int;
	llUpdate();
}

void NumberPrinter::SetFloat(const float& Float)
{
	if (CurrentNumberPrinter.Type != TYPE_FLOAT) { return; }
	if (CurrentNumberPrinter.Float == nullptr) { return; }

	*CurrentNumberPrinter.Float = Float;
	llUpdate();
}

void NumberPrinter::SetVec2(const glm::vec2& Vec2)
{
	if (CurrentNumberPrinter.Type != TYPE_VEC2) { return; }
	if (CurrentNumberPrinter.VEC2 == nullptr) { return; }

	*CurrentNumberPrinter.VEC2 = Vec2;
	llUpdate();
}

void NumberPrinter::ChangeString(string NewString)
{
	if (CurrentNumberPrinter.String == nullptr) { Log::LogString("ChangeString Failed:: No String Attached"); return; }

	*CurrentNumberPrinter.String = NewString;
	llUpdate();
}

void NumberPrinter::ChangeFloat(string NewFloat)
{
	if (CurrentNumberPrinter.Float == nullptr) { Log::LogString("ChangeString Failed:: No String Attached"); return; }

	if (NewFloat == " ") {NewFloat = "0.0";}
	
	Log::LogString(NewFloat);

	float StringAsFloat = stof(NewFloat);

	//Log::LogFloat(" (from string)  FLOAT", StringAsFloat);

	*CurrentNumberPrinter.Float = StringAsFloat;
	llUpdate();
}

void NumberPrinter::Set_With_Keyboard(string CurrentText)
{
	switch (CurrentNumberPrinter.Type)
	{
	case TYPE_INT:
		break;

	case TYPE_FLOAT:
		ChangeFloat(CurrentText);
		break;

	case TYPE_DOUBLE:
		//CreateDouble();
		break;

	case TYPE_VEC2:
		//ReplaceVec2();
		break;

	case TYPE_VEC3:
		//CreateVec3();
		break;

	case TYPE_VEC4:
		//CreateVec4();
		break;
	case TYPE_STRING:
		ChangeString(CurrentText);
		break;
	}
}


string NumberPrinter::Get_For_Keyboard()
{
	switch (CurrentNumberPrinter.Type)
	{
	case TYPE_INT:
		return "Incomplete";
		break;

	case TYPE_FLOAT:
		if (CurrentNumberPrinter.Float == nullptr) { Log::LogString("ERROR::Get_For_Keyboard FAILED:: Float was nullptr"); return "Incomplete"; }
		return Get_Float_As_String();
		break;
	case TYPE_DOUBLE:
		return "Incomplete";
		//CreateDouble();
		break;

	case TYPE_VEC2:
		//ReplaceVec2();
		return "Incomplete";
		break;

	case TYPE_VEC3:
		//CreateVec3();
		return "Incomplete";
		break;

	case TYPE_VEC4:
		//CreateVec4();
		return "Incomplete";
		break;
	case TYPE_STRING:
		if (CurrentNumberPrinter.String == nullptr) { Log::LogString("ERROR::Get_For_Keyboard FAILED:: string was nullptr"); return "Incomplete";}
		return *CurrentNumberPrinter.String;
		break;
	}

	return "Incomplete";
}

string NumberPrinter::Get_Float_As_String()
{
	if (CurrentNumberPrinter.Float == nullptr) { return "Error :: No Float"; }

	//Convert float to a string
	string FloatAsString = to_string(*CurrentNumberPrinter.Float);
	//get rid of all the extra decimal places
	FloatAsString = ProcessDecimalPlace(FloatAsString, false);
	return FloatAsString;
}

void NumberPrinter::ChangeVec2(glm::vec2* NewVec2)
{
	CurrentNumberPrinter.VEC2 = NewVec2;
}

void NumberPrinter::llUpdate()
{
	CalculateGroupOffset();

	switch (CurrentNumberPrinter.Type)
	{
	case TYPE_INT:
		ReplaceInteger();
		break;

	case TYPE_FLOAT:
		ReplaceFloat();
		break;

	case TYPE_DOUBLE:
		//CreateDouble();
		break;

	case TYPE_VEC2:
		ReplaceVec2();
		break;

	case TYPE_VEC3:
		//CreateVec3();
		break;

	case TYPE_VEC4:
		//CreateVec4();
		break;
	case TYPE_STRING:
		ReplaceString();
	}

	UpdatellMouseAccess();
}

void NumberPrinter::CreateNumber()
{
	switch (CurrentNumberPrinter.Type)
	{
	case TYPE_INT:
		CreateInt();
		break;

	case TYPE_FLOAT:
		CreateFloat();
		break;

	case TYPE_DOUBLE:
		CreateDouble();
		break;

	case TYPE_VEC2:
		CreateVec2();
		break;

	case TYPE_VEC3:
		CreateVec3();
		break;

	case TYPE_VEC4:
		CreateVec4();
		break;
	case TYPE_STRING:
		CreateString();
		break;
	}

	UpdatellMouseAccess(); 
}

void NumberPrinter::CreateString()
{
	llShapeGroupData TextShapeGroup;
	TextShapeGroup.Position = CurrentllPageItem->Position;
	TextShapeGroup.Color = CurrentllPageItem->Color;

	string MainString = CurrentNumberPrinter.Description;
	bool StringConnected = false;

	if (CurrentNumberPrinter.String != nullptr)
	{
		StringConnected = true;
		MainString = *CurrentNumberPrinter.String;
	}

	CurrentText.Centered = false;
	CurrentText.FontSize = 16;

	//Description
	CurrentText.Phrase = CurrentNumberPrinter.Description;
	TextShapeGroup.Color = { 1.0, 1.0, 1.0, 1.0 }; // White
	ProcessDescriptionHighlight(&TextShapeGroup);
	Log::LogString("CreateString ShapeGroup 1st");
	Text Description(LoadedBook, &TextShapeGroup, CurrentText);
	Log::LogString("CreateString ShapeGroup 2st");

	//Main String
	CurrentText.Phrase = MainString;
	//TextShapeGroup.Position = { Description.GetAccessRight(10), CurrentllPageItem->Position[Y_AXIS] };
	TextShapeGroup.Position = ProcessAnswerPlacement(&Description);
	TextShapeGroup.Color = CurrentNumberPrinter.AnswerColor;
	if (StringConnected == false) { TextShapeGroup.Color[3] = 0.3;}	//Dim Color
	CurrentText.FontSize = 14;
	Log::LogString("CreateString ShapeGroup 3st");
	Text MainText(LoadedBook, &TextShapeGroup, CurrentText);
	Log::LogString("CreateString ShapeGroup 4st");
	//MainText.PlaceRight(Description.GetEdges(), MATCH_CENTERS, 10);
}

void NumberPrinter::CreateInt()
{
	llShapeGroupData TextShapeGroup;
	TextShapeGroup.Position = CurrentllPageItem->Position;
	TextShapeGroup.Color = CurrentllPageItem->Color;

	int MainInteger = 0.0;
	bool IntegerConnected = false;

	//Make Sure we are connected 
	if (CurrentNumberPrinter.Integer != nullptr)
	{
		IntegerConnected = true;
		MainInteger = *CurrentNumberPrinter.Integer;
	}

	CurrentText.Centered = false;
	CurrentText.FontSize = CurrentNumberPrinter.FontSize;

	//Description
	CurrentText.Phrase = CurrentNumberPrinter.Description;
	TextShapeGroup.Color = { 1.0, 1.0, 1.0, 1.0 }; // White
	ProcessDescriptionHighlight(&TextShapeGroup);
	Text Description(LoadedBook, &TextShapeGroup, CurrentText);

	//Main String
	CurrentText.Phrase = to_string(MainInteger);
	//TextShapeGroup.Position = { Description.GetAccessRight(10), CurrentllPageItem->Position[Y_AXIS] };
	if (IntegerConnected == true)
	{
		TextShapeGroup.Color = { 0.0, 1.0, 1.0, 0.8 }; // Azure
	}
	else
	{
		TextShapeGroup.Color = { 0.0, 1.0, 1.0, 0.3 }; // Azure
	}
	CurrentText.FontSize = CurrentNumberPrinter.AnswerFontSize;
	TextShapeGroup.Position = ProcessAnswerPlacement(&Description);
	Text MainText(LoadedBook, &TextShapeGroup, CurrentText);
	MainText.PlaceRight(Description.GetEdges(), MATCH_CENTERS, 10);
}

void NumberPrinter::CreateFloat()
{
	llShapeGroupData TextShapeGroup;
	TextShapeGroup.Position = CurrentllPageItem->Position;
	TextShapeGroup.Color = CurrentllPageItem->Color;

	float MainFloat = 0.0;
	bool FloatConnected = false;

	//Make Sure we are connected 
	if (CurrentNumberPrinter.Float != nullptr)
	{
		FloatConnected = true;
		MainFloat = *CurrentNumberPrinter.Float;
	}

	CurrentText.Centered = false;
	CurrentText.FontSize = CurrentNumberPrinter.FontSize;

	//Description
	CurrentText.Phrase = CurrentNumberPrinter.Description;
	TextShapeGroup.Color = CurrentllPageItem->Color; // White
	ProcessDescriptionHighlight(&TextShapeGroup);
	Log::LogString("Float Printer 1st");
	Text Description(LoadedBook, &TextShapeGroup, CurrentText);  // 0.0, 0.0
	Log::LogString("Float Printer 2nd");

	//Main String
	string RawString = to_string(MainFloat);
	CurrentText.Phrase = ProcessDecimalPlace(RawString, CurrentNumberPrinter.DollarSign);
	//TextShapeGroup.Position = { Description.GetAccessRight(10), CurrentllPageItem->Position[Y_AXIS] };
	TextShapeGroup.Color = CurrentNumberPrinter.AnswerColor;
	if (FloatConnected != true)
	{
		//Dim
		TextShapeGroup.Color[3] = 0.3;
	}
	CurrentText.FontSize = CurrentNumberPrinter.AnswerFontSize;
	TextShapeGroup.Position = ProcessAnswerPlacement(&Description);
	Log::LogString("Float Printer 3rd");
	Text MainText(LoadedBook, &TextShapeGroup, CurrentText); // CAUSES THE ISSUE
	//Log::LogString("Float Printer 4th");
	//MainText.PlaceRight(Description.GetEdges(), MATCH_CENTERS, 87); //0.21, -0.026
	//Log::LogString("Float Printer 5th");
}

void NumberPrinter::CreateDouble()
{

}


void NumberPrinter::CreateVec2()
{

	cout << "Creating Vec2" << endl;
	llShapeGroupData TextShapeGroup;
	TextShapeGroup.Position = CurrentllPageItem->Position;
	TextShapeGroup.Color = CurrentllPageItem->Color;

	float x = -0.0000000;
	float y = -0.0000000;

	if (CurrentNumberPrinter.VEC2 != nullptr)
	{
		x = CurrentNumberPrinter.VEC2->x;
		y = CurrentNumberPrinter.VEC2->y;

	}

	//SubStrings
	string X = "  X: ";
	string Y = "  Y: ";
	string floatx = to_string(x);
	string floaty = to_string(y);
	floatx.erase(5);
	floaty.erase(5);

	CurrentText.Centered = false;
	CurrentText.FontSize = 12;

	//Description
	CurrentText.Phrase = CurrentNumberPrinter.Description;
	TextShapeGroup.Color = {1.0, 1.0, 1.0, 1.0}; // White
	Text Description(LoadedBook, &TextShapeGroup, CurrentText);

	// X:
	CurrentText.Phrase = X;
	TextShapeGroup.Position = { Description.GetAccessLeft(50), CurrentllPageItem->Position[Y_AXIS] };
	TextShapeGroup.Color = { 0.0, 0.5, 1.0, 0.8 }; // Azure
	Text Text_X(LoadedBook, &TextShapeGroup, CurrentText);

	// X Answer
	CurrentText.Phrase = floatx;
	TextShapeGroup.Position = { Text_X.GetAccessRight(), CurrentllPageItem->Position[Y_AXIS] };
	TextShapeGroup.Color = { 0.171, 0.8461 , 0.95 , 0.8 }; //Nice Blue
	Text Text_floatx(LoadedBook, &TextShapeGroup, CurrentText);

	// Y:
	CurrentText.Phrase = Y;
	TextShapeGroup.Position = { Text_floatx.GetAccessRight(), CurrentllPageItem->Position[Y_AXIS] };
	TextShapeGroup.Color = { 0.0, 0.5, 1.0, 0.8 }; // Azure
	Text Text_Y(LoadedBook, &TextShapeGroup, CurrentText);

	// Y Answer
	CurrentText.Phrase = floaty;
	TextShapeGroup.Position = { Text_Y.GetAccessRight(), CurrentllPageItem->Position[Y_AXIS] };
	TextShapeGroup.Color = { 0.171, 0.8461 , 0.95 , 0.8 }; //Nice Blue
	Text Text_floaty(LoadedBook, &TextShapeGroup, CurrentText);

}

//void NumberPrinter::SetDescriptionColor(glm::vec4 Color)
//{
//	llShapeGroupData* CurrentShapeGroup = CurrentllPageItem->ShapeGroup;
//
//	while (CurrentShapeGroup->Previous != nullptr)
//	{
//		CurrentShapeGroup = CurrentShapeGroup->Previous;
//	}
//
//	Text Description(CurrentShapeGroup);
//	Description.llSwitch(CurrentShapeGroup);
//	CurrentShapeGroup->Color = Color;
//	CurrentText.Phrase = CurrentNumberPrinter.Description;
//	Description.SetllTextGroup(CurrentShapeGroup, CurrentText);
//	
//}


void NumberPrinter::ReplaceString()
{
	//Validate
	if (LoadedBook == nullptr) { Log::LogString("ERROR:: ReplaceVec2 FAILED:: Invalid Book State"); return; }
	if (CurrentllPageItem == nullptr) { Log::LogString("ERROR:: ReplaceVec2 FAILED:: Invalid PageItem State"); return; }
	if (CurrentllPageItem->ShapeGroup == nullptr) { Log::LogString("ERROR:: ReplaceVec2 FAILED:: No Contents Found in PageItem"); return; }
	//if (CurrentNumberPrinter.String == nullptr) { Log::LogString("ERROR:: ReplaceVec2 FAILED:: No Vector Provided"); return; }


	llShapeGroupData* CurrentShapeGroup = CurrentllPageItem->ShapeGroup;
	string MainString;
	bool StringConnected = false;

	if (CurrentNumberPrinter.String != nullptr)
	{
		StringConnected = true;
		MainString = *CurrentNumberPrinter.String;
	}
	else
	{
		MainString = CurrentNumberPrinter.Description;
	}
	CurrentShapeGroup = HeadShapeGroup(CurrentShapeGroup);

	Text Text_Reference(CurrentShapeGroup);
	Text_Reference.LoadedBook = LoadedBook;
	//Text Second_Text_Reference(CurrentShapeGroup->Next);
	
	if (CurrentllPageItem->BackGround == true)
	{
		CurrentShapeGroup = CurrentShapeGroup->Next;
	}

	//Description
	Text_Reference.llSwitch(CurrentShapeGroup);
	CurrentText = CurrentShapeGroup->TextData;
	ProcessDescriptionHighlight(CurrentShapeGroup);
	CurrentShapeGroup->Position = CurrentllPageItem->Position;
	CurrentShapeGroup->Color = CurrentllPageItem->Color;
	CurrentText.FontSize = CurrentNumberPrinter.FontSize;
	Text_Reference.SetllTextGroup(CurrentShapeGroup, CurrentText);

	CurrentText.Phrase = MainString;
	CurrentShapeGroup = CurrentShapeGroup->Next;
	CurrentShapeGroup->Color = CurrentNumberPrinter.AnswerColor;
	CurrentShapeGroup->Position = ProcessAnswerPlacement(&Text_Reference);
	Text_Reference.llSwitch(CurrentShapeGroup);
	//TextPlaceRight(MATCH_CENTERS, PreviousGroupEdges, CurrentShapeGroup->InputType, CurrentShapeGroup->Position, 0);
	CurrentText.FontSize = CurrentNumberPrinter.AnswerFontSize;
	Text_Reference.SetllTextGroup(CurrentShapeGroup, CurrentText);
	//Second_Text_Reference.PlaceRight(Text_Reference, MATCH_CENTERS);
}


void NumberPrinter::ReplaceVec2()
{
	//Validate
	if (LoadedBook == nullptr) { Log::LogString("ERROR:: ReplaceVec2 FAILED:: Invalid Book State"); return; }
	if (CurrentllPageItem == nullptr) { Log::LogString("ERROR:: ReplaceVec2 FAILED:: Invalid PageItem State"); return; }
	if (CurrentllPageItem->ShapeGroup == nullptr) { Log::LogString("ERROR:: ReplaceVec2 FAILED:: No Contents Found in PageItem"); return; }
	if (CurrentNumberPrinter.VEC2 == nullptr) { Log::LogString("ERROR:: ReplaceVec2 FAILED:: No Vector Provided"); return; }

	llShapeGroupData* CurrentShapeGroup = CurrentllPageItem->ShapeGroup;
	float x = -0.0000000;
	float y = -0.0000000;

	while (CurrentShapeGroup->Previous != nullptr)
	{
		CurrentShapeGroup = CurrentShapeGroup->Previous;
	}

	Text Text_Reference(CurrentShapeGroup);


	x = CurrentNumberPrinter.VEC2->x;
	y = CurrentNumberPrinter.VEC2->y;

	//SubStrings
	string X = "  X: ";
	string Y = "  Y: ";
	string floatx = to_string(x);
	string floaty = to_string(y);
	floatx.erase(5);
	floaty.erase(5);

	int NumBeforeDec = 0;
	int Count = 0;

	//Description
	Text_Reference.llSwitch(CurrentShapeGroup);

	// X:
	CurrentText.Phrase = X;
	CurrentShapeGroup = CurrentShapeGroup->Next;
	Text_Reference.llSwitch(CurrentShapeGroup);

	// X Answer
	CurrentText.Phrase = floatx;
	CurrentShapeGroup = CurrentShapeGroup->Next;
	CurrentShapeGroup->Position = { Text_Reference.GetAccessRight(), CurrentllPageItem->Position[Y_AXIS] };
	Text_Reference.llSwitch(CurrentShapeGroup);
	Text_Reference.SetllTextGroup(CurrentShapeGroup, CurrentText);

	// Y:
	CurrentText.Phrase = Y;
	CurrentShapeGroup = CurrentShapeGroup->Next;
	Text_Reference.llSwitch(CurrentShapeGroup);

	// Y Answer
	CurrentText.Phrase = floaty;
	CurrentShapeGroup = CurrentShapeGroup->Next;
	CurrentShapeGroup->Position = { Text_Reference.GetAccessRight(), CurrentllPageItem->Position[Y_AXIS] };
	Text_Reference.llSwitch(CurrentShapeGroup);
	Text_Reference.SetllTextGroup(CurrentShapeGroup, CurrentText);
}

void NumberPrinter::ReplaceFloat()
{
	//Validate
	if (LoadedBook == nullptr) { Log::LogString("ERROR:: ReplaceVec2 FAILED:: Invalid Book State"); return; }
	if (CurrentllPageItem == nullptr) { Log::LogString("ERROR:: ReplaceVec2 FAILED:: Invalid PageItem State"); return; }
	if (CurrentllPageItem->ShapeGroup == nullptr) { Log::LogString("ERROR:: ReplaceVec2 FAILED:: No Contents Found in PageItem"); return; }
	//if (CurrentNumberPrinter.String == nullptr) { Log::LogString("ERROR:: ReplaceVec2 FAILED:: No Vector Provided"); return; }

	llShapeGroupData* CurrentShapeGroup = CurrentllPageItem->ShapeGroup;
	float MainFloat = 0.0;
	bool FloatConnected = false;

	if (CurrentNumberPrinter.Float != nullptr)
	{
		FloatConnected = true;
		MainFloat = *CurrentNumberPrinter.Float;
	}

	CurrentShapeGroup = HeadShapeGroup(CurrentShapeGroup);

	Text Text_Reference(CurrentShapeGroup);
	Text_Reference.LoadedBook = LoadedBook;
	//Text Second_Text_Reference(CurrentShapeGroup->Next);

	//Description
	Text_Reference.llSwitch(CurrentShapeGroup);
	CurrentText = CurrentShapeGroup->TextData;
	ProcessDescriptionHighlight(CurrentShapeGroup);
	CurrentShapeGroup->Position = CurrentllPageItem->Position;
	CurrentShapeGroup->Color = CurrentllPageItem->Color;
	CurrentText.FontSize = CurrentNumberPrinter.FontSize;
	Text_Reference.SetllTextGroup(CurrentShapeGroup, CurrentText);

	string RawString = to_string(MainFloat);
	CurrentText.Phrase = ProcessDecimalPlace(RawString, CurrentNumberPrinter.DollarSign);
	CurrentShapeGroup = CurrentShapeGroup->Next;
	CurrentShapeGroup->Position = ProcessAnswerPlacement(&Text_Reference);
	//CurrentShapeGroup->Position = { Text_Reference.GetAccessLeft(CurrentNumberPrinter.AnswerSpacing), CurrentllPageItem->Position[Y_AXIS] };
	Text_Reference.llSwitch(CurrentShapeGroup);
	CurrentShapeGroup->Color = CurrentNumberPrinter.AnswerColor;

	//Dim
	if (FloatConnected != true) { CurrentShapeGroup->Color[3] = 0.3;}

	CurrentText.FontSize = CurrentNumberPrinter.AnswerFontSize;
	//TextPlaceRight(MATCH_CENTERS, PreviousGroupEdges, CurrentShapeGroup->InputType, CurrentShapeGroup->Position, 0);
	Text_Reference.SetllTextGroup(CurrentShapeGroup, CurrentText);
	//Second_Text_Reference.PlaceRight(Text_Reference, MATCH_CENTERS);
}

void NumberPrinter::ReplaceInteger()
{

	llShapeGroupData* CurrentShapeGroup = CurrentllPageItem->ShapeGroup;
	int MainInteger = 0;
	bool IntegerConnected = false;

	if (CurrentNumberPrinter.String != nullptr)
	{
		IntegerConnected = true;
		MainInteger = *CurrentNumberPrinter.Integer;
	}

	CurrentShapeGroup = HeadShapeGroup(CurrentShapeGroup);

	Text Text_Reference(CurrentShapeGroup);
	//Text Second_Text_Reference(CurrentShapeGroup->Next);

	//Description
	Text_Reference.llSwitch(CurrentShapeGroup);
	CurrentText = CurrentShapeGroup->TextData;
	ProcessDescriptionHighlight(CurrentShapeGroup);
	CurrentShapeGroup->Position = CurrentllPageItem->Position;
	CurrentShapeGroup->Color = CurrentllPageItem->Color;
	Text_Reference.SetllTextGroup(CurrentShapeGroup, CurrentText);

	CurrentText.Phrase = to_string(MainInteger);
	CurrentShapeGroup = CurrentShapeGroup->Next;
	CurrentShapeGroup->Position = { Text_Reference.GetAccessLeft(CurrentNumberPrinter.AnswerSpacing), CurrentllPageItem->Position[Y_AXIS] };
	Text_Reference.llSwitch(CurrentShapeGroup);
	//TextPlaceRight(MATCH_CENTERS, PreviousGroupEdges, CurrentShapeGroup->InputType, CurrentShapeGroup->Position, 0);
	Text_Reference.SetllTextGroup(CurrentShapeGroup, CurrentText);
	//Second_Text_Reference.PlaceRight(Text_Reference, MATCH_CENTERS);
}


void NumberPrinter::CreateVec3()
{
	llShapeGroupData TextShapeGroup;
}

void NumberPrinter::CreateVec4()
{
	llShapeGroupData TextShapeGroup;
}

void NumberPrinter::ProcessDescriptionHighlight(llShapeGroupData* DescriptionGroup)
{

	//Should Description be Highlighted?
	if (CurrentNumberPrinter.DescriptionHighlighted == true)
	{
		//Yes
		DescriptionGroup->HighlightColor = CurrentNumberPrinter.DescriptionHighlightColor;
		DescriptionGroup->Highlighted = true;
	}
	else
	{
		//No
		DescriptionGroup->Highlighted = false;
	}


}

void NumberPrinter::HighlightDescription(glm::vec4 Color)
{
	//Already in desired state
	if (CurrentNumberPrinter.DescriptionHighlighted == true) { return; }

	//Set Highlight Variables
	CurrentNumberPrinter.DescriptionHighlighted = true;
	CurrentNumberPrinter.DescriptionHighlightColor = Color;

	llUpdate();
}

void NumberPrinter::HighlightDescriptionOff()
{
	//Already in desired state
	if (CurrentNumberPrinter.DescriptionHighlighted = false) { return; }

	//Set Highlight Data
	CurrentNumberPrinter.DescriptionHighlighted = false;

	llUpdate();
}

glm::vec2 NumberPrinter::ProcessAnswerPlacement(Text* Text_Reference)
{
	//Place below
	if (CurrentNumberPrinter.Below == true)
	{
		return  { Text_Reference->GetAccessLeft(0), Text_Reference->GetAccessBottom(-30)};
	}
	
	//Place Right
	return  { Text_Reference->GetAccessLeft(CurrentNumberPrinter.AnswerSpacing), CurrentllPageItem->Position[Y_AXIS] };
}

string NumberPrinter::ProcessDecimalPlace(string& Reference_String, bool DollarSign)
{
	int EraseCount = 1;

	for (char& c : Reference_String)
	{
		if (c == '.')
		{
			//String with decimal
			Reference_String.erase(EraseCount + CurrentNumberPrinter.DecimalPlaces);
			
			//Process Dolar Sign
			if (DollarSign == true)
			{
				Reference_String = '$' + Reference_String;
			}

			return Reference_String;
		}
		EraseCount++;
	}

	return Reference_String;
}

//We are setting it to the second shapegroup
void NumberPrinter::SetKeyBoardInputFunction(Button* Button, ButtonFunction SetFunction)
{
	llShapeGroupData* CurrentShapeGroup = CurrentllPageItem->ShapeGroup;

	CurrentShapeGroup = HeadShapeGroup(CurrentShapeGroup);

	if (CurrentllPageItem->BackGround == true)
	{
		CurrentShapeGroup = CurrentShapeGroup->Next;
	}

	//Answer Shape Group
	CurrentShapeGroup = CurrentShapeGroup->Next;

	CurrentShapeGroup->ShapeGroupButton = Button;
	Button->LogicalActions[GUI_MOUSELEFT_CLICKED] = SetFunction;
}

/////////////////////////////////////////////////////////////////////////////////////

void NumberPrinterActions::Prepare(llBookData* Book)
{
	CurrentBook = Book;
	RunningFunction = Empty;
}

void NumberPrinterActions::SetKeyboardInput()
{
	llPageItemData* Hovered_PageItem = CurrentBook->PageItem_Hovered;

	if (Hovered_PageItem != nullptr)
	{
		//User Clicks the Printer Answer
		if (Hovered_PageItem->Type == TYPE_PAGEITEM_NUMBER)
		{
			Log::LogString("Found a Printer!");
			CurrentPrinter.LoadedBook = CurrentBook;
			CurrentPrinter.llSwitch(Hovered_PageItem);
			Keyboard::SetText(CurrentPrinter.Get_For_Keyboard());
			CurrentPrinter.SetString(Keyboard::GetText());
			RunningFunction = Run;
		}
	}
}

void NumberPrinterActions::Update()
{
	RunningFunction();
}

void NumberPrinterActions::Run()
{
	CurrentPrinter.Set_With_Keyboard(Keyboard::GetText());
}

void NumberPrinterActions::Stop()
{
	//RunningFunction = Empty;
}

void NumberPrinterActions::Empty()
{

}