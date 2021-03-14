#include "NumberPrinter.h"

NumberPrinter::NumberPrinter(llBookData* llBook)
	:PageGroupItem(llBook)
{
	CurrentllPageItem->Color = { 1.0, 1.0, 1.0, 1.0 };
	CurrentllPageItem->Size = { 0.0, 0.0 }; // all of the xadvances of all the text
	CurrentllPageItem->Position = { 0.0, 0.0 };
	CurrentllPageItem->MouseAccess = true;
	CurrentllPageItem->Highlighted = false;
	CurrentllPageItem->Centered = false;
	CurrentllPageItem->XYShapePerRow = { 2.0, 2.0 }; // Can use without
	CurrentllPageItem->ShapeSize = { 0.8, 0.8 };  // Can use without
	CurrentllPageItem->Type = TYPE_PAGEITEM_NUMBER;
	LoadedBook = llBook;
	CreateNumber();
}

NumberPrinter::NumberPrinter(llBookData* llBook, llPageItemData* llPageItem, NumberPrinterData NumberPrinter)
	: PageGroupItem(llBook, llPageItem)
{
	CurrentNumberPrinter = NumberPrinter;
	LoadedBook = llBook;
	CreateNumber();
}

NumberPrinter::NumberPrinter(llPageItemData* llPageItem)
	: PageGroupItem(llPageItem)
{

}

void NumberPrinter::llInit(llBookData* llBook, llPageItemData* llPageItem, NumberPrinterData NumberPrinter)
{
	llPageItemInit(llBook, llPageItem);
	CurrentNumberPrinter = NumberPrinter;
	CreateNumber();
}


void NumberPrinter::SetVec2(glm::vec2* NewVec2)
{
	CurrentNumberPrinter.VEC2 = NewVec2;
}

void NumberPrinter::llUpdate()
{
	switch (CurrentNumberPrinter.Type)
	{
	case TYPE_INT:
		//CreateInt();
		break;

	case TYPE_FLOAT:
		//CreateFloat();
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
	}
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
	}
}

void NumberPrinter::CreateInt()
{

}

void NumberPrinter::CreateFloat()
{

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
	TextShapeGroup.Position = { Description.GetAccessRight(), CurrentllPageItem->Position[Y_AXIS] };
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

void NumberPrinter::SetDescriptionColor(glm::vec4 Color)
{
	llShapeGroupData* CurrentShapeGroup = CurrentllPageItem->ShapeGroup;

	while (CurrentShapeGroup->Previous != nullptr)
	{
		CurrentShapeGroup = CurrentShapeGroup->Previous;
	}

	Text Description(CurrentShapeGroup);
	Description.llSwitch(CurrentShapeGroup);
	CurrentShapeGroup->Color = Color;
	CurrentText.Phrase = CurrentNumberPrinter.Description;
	Description.SetllTextGroup(CurrentShapeGroup, CurrentText);
	
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

void NumberPrinter::CreateVec3()
{

}

void NumberPrinter::CreateVec4()
{

}

void NumberPrinter::ReplaceNumber()
{

}