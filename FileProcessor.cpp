#include "FileProcessor.h"


FileSystem::FileSystem()
{
	this->CurrentDirectory = "C:\\\\";

	for (int i = 0; i < 100; i++)
	{
		FileList[i] = " ";
	}
	this->ListCount = 0;
}

void FileSystem::CreateNewFile(const string& FileName)
{
	//open a file with name specified

	fstream NewFile;

	NewFile.open("ProgramFiles\\" + FileName + ".book", fstream::out); 

	NewFile << "First Time writing to files\n";

	string Words;

	NewFile >> Words;

	cout << Words << endl;

	NewFile.close();


}

void FileSystem::SaveBook(Book& Book)
{
	ofstream File;
	ofstream txtFile;
	int TotalShapeDataCount;
	int TotalVertexCount;
	int TotalIndexCount;



	File.open(Book.FilePath, ios::trunc);

	if (File.is_open())
	{
		cout << "Loading File" << endl;
		File << Book;
		cout << "Book Saved" << endl;
	}
	else
	{
		cout << "FILE ERROR::Cannot Open File"  << endl;
	}
	File.close();

	txtFile.open("ProgramFiles/GUIData.txt", ios::trunc);

	if (txtFile.is_open())
	{
		cout << "Loading File" << endl;
		txtFile << Book;
		cout << "Book Saved" << endl;
	}
	else
	{
		cout << "FILE ERROR::Cannot Open File" << endl;
	}
	txtFile.close();


}


Book FileSystem::LoadBook(Book& Book, ShaderProgram ShaderProgram)
{
	ifstream File;
	File.open(Book.FilePath);
	if (File.is_open())
	{
		cout << "Reading File.." << endl;
		Book.Erase();
		File >> Book;
		for (int i = 0; i < Book.CurrentCount; i++)
		{
			Book.Page[i].Init(ShaderProgram);
			Book.Page[i].LoadThisPage();
		}
		cout << "Book  Loaded" << endl;
	}
	else
	{
		cout << "FILE ERROR::Cannot Open File" << endl;
	}

	File.close();

	return Book;
}

ostream& operator<<(ostream& out, const ShapeData& ShapeData)
{
	out << ShapeData.ID << endl;
	out << ShapeData.Position[0] << ' ' << ShapeData.Position[1] << endl;
	out << ShapeData.Size[0] << ' ' << ShapeData.Size[1] << endl;
	out << ShapeData.Color[0] << ' ' << ShapeData.Color[1] << ' ' << ShapeData.Color[2] << ' ' << ShapeData.Color[3] << endl;
	out << ShapeData.ActiveTexture << endl;
	out << ShapeData.Top << endl;
	out << ShapeData.Bottom << endl;
	out << ShapeData.Left << endl;
	out << ShapeData.Right << endl;
	out << ShapeData.Highlighted << endl;
	out << ShapeData.MouseAccess << endl;
	out << ShapeData.ShapeDataisHighlight<< endl;
	out << ShapeData.HighlightPosition[0] << " " << ShapeData.HighlightPosition[1] << endl;
	out << ShapeData.HighlightSize[0] << " " << ShapeData.HighlightSize[1] << endl;
	out << ShapeData.HighlightColor[0] << " " << ShapeData.HighlightColor[1] << " " << ShapeData.HighlightColor[2] << " " << ShapeData.HighlightColor[3] << endl;
	out << ShapeData.PartOfGroup << endl;
	out << ShapeData.ShapeGroup.ShapeStart << endl;
	out << ShapeData.ShapeGroup.ShapeCount << endl;
	out << ShapeData.ShapeGroup.ShapeOffset << endl;
	out << ShapeData.ShapeGroup.XYShapePerRow[0] << " " << ShapeData.ShapeGroup.XYShapePerRow[1] << endl;
	out << ShapeData.ShapeGroup.Position[0] << " " << ShapeData.ShapeGroup.Position[1] << endl;
	out << ShapeData.ShapeGroup.Size[0] << " " << ShapeData.ShapeGroup.Size[1] << endl;
	out << ShapeData.ShapeGroup.ShapeSize[0] << " " << ShapeData.ShapeGroup.Size[1] << endl;
	out << ShapeData.ShapeGroup.Color[0] << " " << ShapeData.ShapeGroup.Color[1] << " " << ShapeData.ShapeGroup.Color[2] << " " << ShapeData.ShapeGroup.Color[3] << endl;
	out << ShapeData.ShapeGroup.Centered << endl;
	//out << ShapeData.ShapeDataType << endl;

	    //<< "ShapeData "
		//<< "EP "
		//<< "ES "
		//<< "EC "
		//<< "T "
		//<< "B "
		//<< "L "
		//<< "R "
		//<< "H "
		//<< "MA "
		//<< "EIH "
		//<< "HLP "
		//<< "HLS "
		//<< "HLC "
		//<< "POG "
		//<< "GST "
		//<< "GCT "
		//<< "GOF "
		//<< "GXY "
		//<< "GP "
		//<< "GS "
		//<< "GES "
		//<< "GCO "
		//<< "GCE "

	return out;
}

ostream& operator<<(ostream& out, const ShapeVertex& Vertex)
{
	out  << Vertex.Position[0] << " " << Vertex.Position[1] << endl;
	out  << Vertex.TexCoords[0] << " " << Vertex.TexCoords[1] << endl;
	out  << Vertex.Color[0] << " " << Vertex.Color[1] << " " << Vertex.Color[2] << " " << Vertex.Color[3] << endl;
	out  << Vertex.TexIndex << endl;

	//<< "POS "
	//<< "TXC "
	//<< "COL "
	//<< "TXI "
	return out;
}

ostream& operator<<(ostream& out, const Page& Page)
{
	int ShapeDataCount = Page.ShapeContainer.CurrentContainerAmount;
	int VertexCount = ShapeDataCount * 4;
	int IndexCount = ShapeDataCount * 6;

	out << " " << Page.PageID << endl;
	out << " " << ShapeDataCount << "  " << VertexCount << "  " << IndexCount << endl;
	for (int i = 0; i < ShapeDataCount; i++)
	{
		out << Page.ShapeContainer.StartOfContainer[i] << endl;
	}

	for (int i = 0; i < VertexCount; i++)
	{
		out << Page.VertexContainer.StartOfContainer[i] << endl;
	}

	//for (int i = 0; i < IndexCount; i++)
	//{
	//	out << Page.IndexContainer.StartOfContainer[i] << endl;
	//}

	return out;
}

ostream& operator<<(ostream& out, Book& Book)
{
	out << Book.CurrentCount << endl;
	for (int i = 0; i < Book.CurrentCount; i++)
	{
		out << Book.Page[i];
	}
	return out;
}

istream& operator>>(istream& in, ShapeData& ShapeData)
{

	in >> ShapeData.ID;
	in >> ShapeData.Position[0] >> ShapeData.Position[1];
	in >> ShapeData.Size[0] >> ShapeData.Size[1];
	in >> ShapeData.Color[0] >> ShapeData.Color[1] >> ShapeData.Color[2] >> ShapeData.Color[3];
	in >> ShapeData.ActiveTexture;
	in >> ShapeData.Top;
	in >> ShapeData.Bottom;
	in >> ShapeData.Left;
	in >> ShapeData.Right;
	in >> ShapeData.Highlighted;
	in >> ShapeData.MouseAccess;
	in >> ShapeData.ShapeDataisHighlight;
	in >> ShapeData.HighlightPosition[0] >> ShapeData.HighlightPosition[1];
	in >> ShapeData.HighlightSize[0] >> ShapeData.HighlightSize[1];
	in >> ShapeData.HighlightColor[0] >> ShapeData.HighlightColor[1] >> ShapeData.HighlightColor[2] >> ShapeData.HighlightColor[3];
	in >> ShapeData.PartOfGroup;
	in >> ShapeData.ShapeGroup.ShapeStart;
	in >> ShapeData.ShapeGroup.ShapeCount;
	in >> ShapeData.ShapeGroup.ShapeOffset;
	in >> ShapeData.ShapeGroup.XYShapePerRow[0] >> ShapeData.ShapeGroup.XYShapePerRow[1];
	in >> ShapeData.ShapeGroup.Position[0] >> ShapeData.ShapeGroup.Position[1];
	in >> ShapeData.ShapeGroup.Size[0] >> ShapeData.ShapeGroup.Size[1];
	in >> ShapeData.ShapeGroup.ShapeSize[0] >> ShapeData.ShapeGroup.Size[1];
	in >> ShapeData.ShapeGroup.Color[0] >> ShapeData.ShapeGroup.Color[1] >> ShapeData.ShapeGroup.Color[2] >> ShapeData.ShapeGroup.Color[3];
	in >> ShapeData.ShapeGroup.Centered;
	//in >> ShapeData.ShapeDataType;

	return in;
}

istream& operator>>(istream& in, ShapeVertex& Vertex)
{
    in >> Vertex.Position[0] >> Vertex.Position[1];
    in >> Vertex.TexCoords[0] >> Vertex.TexCoords[1];
    in >> Vertex.Color[0] >> Vertex.Color[1] >> Vertex.Color[2] >> Vertex.Color[3];
    in >> Vertex.TexIndex;
	return in;
}

istream& operator>>(istream& in, Page& Page)
{
	ShapeData ShapeData;
	ShapeVertex Vertex;
	int Index;

	int ShapeDataCount;
	int VertexCount;
	int IndexCount;

	in >> Page.PageID;
	//cout << Page.PageID << endl;
	in >> ShapeDataCount >> VertexCount >> IndexCount;
	//cout << ShapeDataCount << " " << VertexCount << " " << IndexCount << endl;

	for (int i = 0; i < ShapeDataCount; i++)
	{
		in >> ShapeData;
		Page.LoadShapeDataFromFile(ShapeData);

	}

	for (int i = 0; i < VertexCount; i++)
	{
     in >> Vertex;
     Page.LoadVertexFromFile(Vertex);

	}

	//for (int i = 0; i < IndexCount; i++)
	//{
	//	in >> Index;
	//	Page.LoadIndexFromFile(Index);
	//
	//}

	return in;
}

istream& operator>>(istream& in, Book& Book)
{
	in >> Book.CurrentCount;
	if (!Book.CurrentCount) { Book.CurrentCount = 1;};
	for (int i = 0; i < Book.CurrentCount; i++)
	{
		in >> Book.Page[i];
	}
	return in;
}


//with double backslashes
//EX C:\\VisualizationImages\\..
void FileSystem::DisplayDirectoryFiles()
{
	cout << "Printing Directory: " << CurrentDirectory << endl;
	for (int i = 0; i < ListCount; i++)
	{
		cout << "File: " << FileList[i] << endl;
	}

}

//Go back a Directory
void FileSystem::ReverseDirectory()
{
	//= "C:\\\\OpenCVProject\\\\Opencv\\\\";//
	string CurrentString = this->CurrentDirectory;
	int LastDS = CurrentString.rfind(this->BackSlash, CurrentString.size() - 4);
	//Output EX: C:\\ProgramFiles\\.
	string NewDirectory = CurrentString.substr(0, LastDS);
	NewDirectory += BackSlash;
	//cout << "NewDirectory: " << NewDirectory << endl;
	this->CurrentDirectory = NewDirectory;
	LoadDirectory();
}
//Go Forward a Directory
void FileSystem::ForwardDirectory(string DirectoryName)
{
	//EX: C:\\ProgramFiles\\ += ImportantFiles + \\.
	this->CurrentDirectory += DirectoryName + BackSlash;
	cout << CurrentDirectory << endl;
	LoadDirectory();
}

void FileSystem::ResetDirectory()
{
	this->CurrentDirectory = "C:\\";
	LoadDirectory();
}

//
void FileSystem::SetDirectory(string Directory)
{
	this->CurrentDirectory += Directory + BackSlash;
	LoadDirectory();
}


void FileSystem::LoadDirectory()
{
	this->ListCount = 0;
	WIN32_FIND_DATAA FileData;
	HANDLE hFind;
	string Astris = "*";
	string NewDirectory = this->CurrentDirectory + Astris;
	LPCSTR file = NewDirectory.c_str();

	hFind = FindFirstFileA(file, &FileData);

	if (INVALID_HANDLE_VALUE == hFind)
	{
		cout << "error" << endl;
	}
	else
	{
		//wcout << "FileName: " << FileData.cFileName << endl;
		FileList[ListCount] = FileData.cFileName;
		ListCount++;
		this->FileListString = FileData.cFileName;
		//wcout << "FileName" << FileData.ftLastAccessTime << endl;
	}

	while (FindNextFileA(hFind, &FileData))
	{
		//wcout << "FileName: " << FileData.cFileName << endl;
		FileList[ListCount] = FileData.cFileName;
		FileListString += FileData.cFileName + '  ';
		ListCount++;
	}

	FindClose(hFind);
}

istream& operator>>(istream& in, glm::vec4& Vec4)
{
	in >> Vec4[0] >> Vec4[1] >> Vec4[2] >> Vec4[3];

	return in;
}

ostream& operator<<(ostream& out, glm::vec4& Vec4)
{
	out << Vec4[0] << " " << Vec4[1] << " " << Vec4[2] << " " << Vec4[3];
	return out;
}

ostream& operator<<(ostream& out, glm::vec2& Vec2)
{
	out << Vec2[0] << " " << Vec2[1];
	return out;
}
istream& operator>>(istream& in, glm::vec2& Vec2)
{
	in >> Vec2[0] >> Vec2[1];
	return in;
}

// Linked List
ostream& operator<<(ostream& out, llVertexData* VertexData) 
{
	out << VertexData->Position;
	out << VertexData->TexCoords;
	out << VertexData->Color;
	out << VertexData->TexIndex;
	out << VertexData->CentralPoint;
	out << VertexData->GUIAction;

	return out;
}

ostream& operator<<(ostream& out, llShapeData* ShapeData) 
{
	out << ShapeData->Ascii;
	out << ShapeData->ActiveTexture;
	out << ShapeData->Action;
	out << ShapeData->Type;
	out << ShapeData->InputType;
	out << ShapeData->Position;
	out << ShapeData->Size;
	out << ShapeData->Color;
	out << ShapeData->PositionOffset;
	out << ShapeData->SizeOffset;
	out << ShapeData->ColorOffset;
	out << ShapeData->HighlightColor;
	out << ShapeData->MouseAccess;
	out << ShapeData->Centered;
	out << ShapeData->Highlighted;
	out << ShapeData->Hide;
	out << ShapeData->Top;
	out << ShapeData->Bottom;
	out << ShapeData->Left;
	out << ShapeData->Right;
	out << ShapeData->Text; //Not Needed
	out << ShapeData->EndStart; //Not Needed
	out << ShapeData->TextCentered; //Not Needed
	out << ShapeData->ChangeAsGroup; //Not Needed

	return out;
}

ostream& operator<<(ostream& out, llShapeGroupData* ShapeGroupData)
{
	out << ShapeGroupData->Type;
	out << ShapeGroupData->XYShapePerRow;
	out << ShapeGroupData->ShapeSize;
	out << ShapeGroupData->Position;
	out << ShapeGroupData->Size;
	out << ShapeGroupData->Color;
	out << ShapeGroupData->PositionOffset;
	out << ShapeGroupData->SizeOffset;
	out << ShapeGroupData->ColorOffset;
	out << ShapeGroupData->HighlightColor;
	out << ShapeGroupData->Centered;
	out << ShapeGroupData->Highlighted;
	out << ShapeGroupData->MouseAccess;
	out << ShapeGroupData->Hide;
	out << ShapeGroupData->ChangeAsGroup;
	out << ShapeGroupData->Top;
	out << ShapeGroupData->Bottom;
	out << ShapeGroupData->Left;
	out << ShapeGroupData->Right;

	return out;
}

ostream& operator<<(ostream& out, llPageItemData* PageItemData)
{
	//PageItem
	out << PageItemData->Type;
	out << PageItemData->Position;
	out << PageItemData->Size;
	out << PageItemData->Color;
	out << PageItemData->PositionOffset;
	out << PageItemData->SizeOffset;
	out << PageItemData->ColorOffset;
	out << PageItemData->XYShapePerRow;
	out << PageItemData->ShapeSize;
	out << PageItemData->HighlightColor;
	out << PageItemData->Centered;
	out << PageItemData->Highlighted;
	out << PageItemData->MouseAccess;
	out << PageItemData->ChangeAsGroup;
	out << PageItemData->Top;
	out << PageItemData->Bottom;
	out << PageItemData->Left;
	out << PageItemData->Right;

	return out;
	//out << PageItemData->PageItemButton;		   // PLEASE COMPLETE
	//out << PageItemData->NumberPrinterData;	   // PLEASE COMPLETE
	//out << PageItemData->SliderData;             // PLEASE COMPLETE
}

ostream& operator<<(ostream& out, llPageGroupData* PageGroupData)
{
	out << PageGroupData->Type;
	out << PageGroupData->Position;
	out << PageGroupData->Size;
	out << PageGroupData->Color;
	out << PageGroupData->XYShapePerRow;
	out << PageGroupData->ShapeSize;
	out << PageGroupData->HighlightColor;
	out << PageGroupData->Centered;
	out << PageGroupData->Highlighted;
	out << PageGroupData->MouseAccess;
	out << PageGroupData->ChangeAsGroup;
	out << PageGroupData->Top;
	out << PageGroupData->Bottom;
	out << PageGroupData->Left;
	out << PageGroupData->Right;

	return out;
	//out << PageGroupData->PageGroupButton;  //PLEASE COMPLETE
}

ostream& operator<<(ostream& out, llPageData* PageData) {}
ostream& operator<<(ostream& out, llBookData* BookData) {}



// Linked List in
istream& operator>>(istream& in, llVertexData* VertexData)
{
	in >> VertexData->Position;
	in >> VertexData->TexCoords;
	in >> VertexData->Color;
	in >> VertexData->TexIndex;
	in >> VertexData->CentralPoint;
	in >> VertexData->GUIAction;

	return in;
}
istream& operator>>(istream& in, llShapeData* ShapeData)
{
	in >> ShapeData->Ascii;
	in >> ShapeData->ActiveTexture;
	in >> ShapeData->Action;
	in >> ShapeData->Type;
	in >> ShapeData->InputType;
	in >> ShapeData->Position;
	in >> ShapeData->Size;
	in >> ShapeData->Color;
	in >> ShapeData->PositionOffset;
	in >> ShapeData->SizeOffset;
	in >> ShapeData->ColorOffset;
	in >> ShapeData->HighlightColor;
	in >> ShapeData->MouseAccess;
	in >> ShapeData->Centered;
	in >> ShapeData->Highlighted;
	in >> ShapeData->Hide;
	in >> ShapeData->Top;
	in >> ShapeData->Bottom;
	in >> ShapeData->Left;
	in >> ShapeData->Right;
	in >> ShapeData->Text; //Not Needed
	in >> ShapeData->EndStart; //Not Needed
	in >> ShapeData->TextCentered; //Not Needed
	in >> ShapeData->ChangeAsGroup; //Not Needed
	return in;
}
istream& operator>>(istream& in, llShapeGroupData* ShapeGroupData)
{
	in >> ShapeGroupData->Type;
	in >> ShapeGroupData->XYShapePerRow;
	in >> ShapeGroupData->ShapeSize;
	in >> ShapeGroupData->Position;
	in >> ShapeGroupData->Size;
	in >> ShapeGroupData->Color;
	in >> ShapeGroupData->PositionOffset;
	in >> ShapeGroupData->SizeOffset;
	in >> ShapeGroupData->ColorOffset;
	in >> ShapeGroupData->HighlightColor;
	in >> ShapeGroupData->Centered;
	in >> ShapeGroupData->Highlighted;
	in >> ShapeGroupData->MouseAccess;
	in >> ShapeGroupData->Hide;
	in >> ShapeGroupData->ChangeAsGroup;
	in >> ShapeGroupData->Top;
	in >> ShapeGroupData->Bottom;
	in >> ShapeGroupData->Left;
	in >> ShapeGroupData->Right;
	return in;
}
istream& operator>>(istream& in, llPageItemData* PageItemData)
{
	in >> PageItemData->Type;
	in >> PageItemData->Position;
	in >> PageItemData->Size;
	in >> PageItemData->Color;
	in >> PageItemData->PositionOffset;
	in >> PageItemData->SizeOffset;
	in >> PageItemData->ColorOffset;
	in >> PageItemData->XYShapePerRow;
	in >> PageItemData->ShapeSize;
	in >> PageItemData->HighlightColor;
	in >> PageItemData->Centered;
	in >> PageItemData->Highlighted;
	in >> PageItemData->MouseAccess;
	in >> PageItemData->ChangeAsGroup;
	in >> PageItemData->Top;
	in >> PageItemData->Bottom;
	in >> PageItemData->Left;
	in >> PageItemData->Right;
	return in;
}
istream& operator>>(istream& in, llPageGroupData* PageGroupData)
{
	in >> PageGroupData->Type;
	in >> PageGroupData->Position;
	in >> PageGroupData->Size;
	in >> PageGroupData->Color;
	in >> PageGroupData->XYShapePerRow;
	in >> PageGroupData->ShapeSize;
	in >> PageGroupData->HighlightColor;
	in >> PageGroupData->Centered;
	in >> PageGroupData->Highlighted;
	in >> PageGroupData->MouseAccess;
	in >> PageGroupData->ChangeAsGroup;
	in >> PageGroupData->Top;
	in >> PageGroupData->Bottom;
	in >> PageGroupData->Left;
	in >> PageGroupData->Right;
	return in;
}
istream& operator>>(istream& in, llPageData* Page) {}
istream& operator>>(istream& in, llBookData* Book) {}