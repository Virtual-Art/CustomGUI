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
	CreateNumber();
}

NumberPrinter::NumberPrinter(llBookData* llBook, llPageItemData* llPageItem, NumberPrinterData NumberPrinter)
	: PageGroupItem(llBook, llPageItem)
{
	CreateNumber();
}

NumberPrinter::NumberPrinter(llPageItemData* llPageItem)
	: PageGroupItem(llPageItem)
{

}

void NumberPrinter::llUpdate()
{

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
	llShapeGroupData TextShapeGroup;

	float x = CurrentNumberPrinter.VEC2->x;
	float y = CurrentNumberPrinter.VEC2->y;

	//SubStrings
	string X = "  X: ";
	string Y = "  Y: ";
	string floatx = to_string(x);
	string floaty = to_string(y);

	CurrentText.Centered = false;

	CurrentText.Phrase = CurrentNumberPrinter.Description;
	Text Description(LoadedBook, &TextShapeGroup, CurrentText);

	CurrentText.Phrase = X;
	Text Text_X(LoadedBook, &TextShapeGroup, CurrentText);

	CurrentText.Phrase = floatx;
	Text Text_floatx(LoadedBook, &TextShapeGroup, CurrentText);

	CurrentText.Phrase = Y;
	Text Text_Y(LoadedBook, &TextShapeGroup, CurrentText);

	CurrentText.Phrase = floaty;
	Text Text_floaty(LoadedBook, &TextShapeGroup, CurrentText);
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