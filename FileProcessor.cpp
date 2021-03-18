#include "FileProcessor.h"

llBookData* FileSystem::THISBOOK = nullptr;

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


void FileSystem::SavellBook(llBookData& Book, string FilePath)
{
	ofstream File;
	ofstream txtFile;

	THISBOOK = &Book;

	File.open(FilePath, ios::trunc);
	
	if (File.is_open())
	{
		cout << "Loading File" << endl;
		File << Book;
		cout << "Book Saved" << endl;
	}
	else
	{
		cout << "FILE ERROR::Cannot Open File" << endl;
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

void FileSystem::LoadllBook(llBookData& Book, string FilePath)
{
	THISBOOK = &Book;

	ifstream File;
	File.open(FilePath);
	if (File.is_open())
	{
		cout << "Reading File.." << endl;
		File >> Book;
		cout << "Book  Loaded" << endl;
	}
	else
	{
		cout << "FILE ERROR::Cannot Open File" << endl;
	}

	File.close();
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

ostream& operator<<(ostream& out, const glm::vec4& Vec4)
{
	out  << Vec4[0] << "  " << Vec4[1] << "  " << Vec4[2] << "  " << Vec4[3];
	return out;
}

ostream& operator<<(ostream& out, const glm::vec2& Vec2)
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
ostream& operator<<(ostream& out, const llVertexData& VertexData) 
{
	out << "VERTEX" << endl;
	out << VertexData.Position << endl;
	out << VertexData.TexCoords << endl;
	out << VertexData.Color << endl;
	out << VertexData.TexIndex << endl;
	out << VertexData.CentralPoint << endl;
	out << VertexData.GUIAction << endl;

	return out;
}

ostream& operator<<(ostream& out, const llShapeData& ShapeData) 
{
	//Write Shape Data
	out << "SHAPE" << endl;
	out << ShapeData.Ascii << endl;
	out << ShapeData.ActiveTexture << endl;
	out << ShapeData.Action << endl;
	out << ShapeData.Type << endl;
	out << ShapeData.InputType << endl;
	out << ShapeData.Position << endl;
	out << ShapeData.Size << endl;
	out << ShapeData.Color << endl;
	out << ShapeData.PositionOffset << endl;
	out << ShapeData.SizeOffset << endl;
	out << ShapeData.ColorOffset << endl;
	out << ShapeData.HighlightColor << endl;
	out << ShapeData.MouseAccess << endl;
	out << ShapeData.Centered << endl;
	out << ShapeData.Highlighted << endl;
	out << ShapeData.Hide << endl;
	out << ShapeData.Top << endl;
	out << ShapeData.Bottom << endl;
	out << ShapeData.Left << endl;
	out << ShapeData.Right<< endl;
	out << ShapeData.Text + " `" << endl; //Not Needed
	out << ShapeData.EndStart << endl; //Not Needed
	out << ShapeData.TextCentered << endl; //Not Needed
	out << ShapeData.ChangeAsGroup << endl; //Not Needed

	//Write Shape Data's Vertices (if it has any)
	if (ShapeData.Vertexx != nullptr)
	{
		//Get Shape's Vertices
		llVertexData* CurrentVertex = ShapeData.Vertexx;

		//Go to Vertex head
		while (CurrentVertex->Previous != nullptr)
		{
			CurrentVertex = CurrentVertex->Previous;
		}

		//Write All Shape Vertices
		while (CurrentVertex != nullptr)
		{
			out << *CurrentVertex;
			CurrentVertex = CurrentVertex->Next;
		}
	}

	return out;
}

ostream& operator<<(ostream& out, const llShapeGroupData& ShapeGroupData)
{
	//Write ShapeGroup Data
	out << "SHAPEGROUP" << endl;
	out << ShapeGroupData.ShapeCount << endl;
	out << ShapeGroupData.Type << endl;
	out << ShapeGroupData.XYShapePerRow << endl;
	out << ShapeGroupData.ShapeSize << endl;
	out << ShapeGroupData.Position << endl;
	out << ShapeGroupData.Size << endl;
	out << ShapeGroupData.Color << endl;
	out << ShapeGroupData.PositionOffset << endl;
	out << ShapeGroupData.SizeOffset << endl;
	out << ShapeGroupData.ColorOffset << endl;
	out << ShapeGroupData.HighlightColor << endl;
	out << ShapeGroupData.Centered << endl;
	out << ShapeGroupData.Highlighted << endl;
	out << ShapeGroupData.MouseAccess << endl;
	out << ShapeGroupData.Hide << endl;
	out << ShapeGroupData.ChangeAsGroup << endl;
	out << ShapeGroupData.Top << endl;
	out << ShapeGroupData.Bottom << endl;
	out << ShapeGroupData.Left << endl;
	out << ShapeGroupData.Right << endl;

	//Write ShapeGroup Data's Shapes (if it has any)
	if (ShapeGroupData.Shape != nullptr)
	{
		//Get ShapeGroup's Shape
		llShapeData* CurrentShape = ShapeGroupData.Shape;

		//Go to Shape head
		while (CurrentShape->Previous != nullptr) {CurrentShape = CurrentShape->Previous;}

		//Write All ShapeGroup Shape
		while (CurrentShape != nullptr)
		{
			out << *CurrentShape;
			CurrentShape = CurrentShape->Next;
		}
	}

	return out;
}

ostream& operator<<(ostream& out, const llPageItemData& PageItemData)
{
	//Write PageItem
	out << "PAGEITEM" << endl;
	out << PageItemData.ShapeGroupCount << endl;
	out << PageItemData.Type << endl;
	out << PageItemData.Position << endl;
	out << PageItemData.Size << endl;
	out << PageItemData.Color << endl;
	out << PageItemData.PositionOffset << endl;
	out << PageItemData.SizeOffset << endl;
	out << PageItemData.ColorOffset << endl;
	out << PageItemData.XYShapePerRow << endl;
	out << PageItemData.ShapeSize << endl;
	out << PageItemData.HighlightColor << endl;
	out << PageItemData.Centered << endl;
	out << PageItemData.Highlighted << endl;
	out << PageItemData.MouseAccess << endl;
	out << PageItemData.ChangeAsGroup << endl;
	out << PageItemData.Top << endl;
	out << PageItemData.Bottom << endl;
	out << PageItemData.Left << endl;
	out << PageItemData.Right << endl;


	//Write PageItem Data's ShapeGroups (if it has any)
	if (PageItemData.ShapeGroup != nullptr)
	{
		//Get ShapeGroup's Shape
		llShapeGroupData* CurrentShapeGroup = PageItemData.ShapeGroup;

		//Go to ShapeGroup head
		while (CurrentShapeGroup->Previous != nullptr) { CurrentShapeGroup = CurrentShapeGroup->Previous; }

		//Write All ShapeGroups
		while (CurrentShapeGroup != nullptr)
		{
			out << *CurrentShapeGroup;
			CurrentShapeGroup = CurrentShapeGroup->Next;
		}
	}

	return out;
	//out << PageItemData->PageItemButton;		   // PLEASE COMPLETE
	//out << PageItemData->NumberPrinterData;	   // PLEASE COMPLETE
	//out << PageItemData->SliderData;             // PLEASE COMPLETE
}

ostream& operator<<(ostream& out, const llPageGroupData& PageGroupData)
{
    out << "PAGEGROUP" << endl;
	out << PageGroupData.PageItemCount << endl;
	out << PageGroupData.Type << endl;
	out << PageGroupData.Position << endl;
	out << PageGroupData.Size << endl;
	out << PageGroupData.Color << endl;
	out << PageGroupData.XYShapePerRow << endl;
	out << PageGroupData.ShapeSize << endl;
	out << PageGroupData.HighlightColor << endl;
	out << PageGroupData.Centered << endl;
	out << PageGroupData.Highlighted << endl;
	out << PageGroupData.MouseAccess << endl;
	out << PageGroupData.ChangeAsGroup << endl;
	out << PageGroupData.Top << endl;
	out << PageGroupData.Bottom << endl;
	out << PageGroupData.Left << endl;
	out << PageGroupData.Right<< endl;


	//Write PageGroup Data's PageItems (if it has any)
	if (PageGroupData.PageItem != nullptr)
	{
		//Get ShapeGroup's Shape
		llPageItemData* CurrentPageItem = PageGroupData.PageItem;

		//Go to PageItem head
		while (CurrentPageItem->Previous != nullptr) { CurrentPageItem = CurrentPageItem->Previous; }

		//Write All PageItems
		while (CurrentPageItem != nullptr)
		{
			out << *CurrentPageItem;
			CurrentPageItem = CurrentPageItem->Next;
		}
	}


	return out;
	//out << PageGroupData->PageGroupButton;  //PLEASE COMPLETE
}

ostream& operator<<(ostream& out, const llPageData& PageData) 
{
	out << "PAGE" << endl;
	out << PageData.PageGroupCount << endl;

	//Write PageGroup Data's PageItems (if it has any)
	if (PageData.PageGroup != nullptr)
	{
		//Get ShapeGroup's Shape
		llPageGroupData* CurrentPageGroup = PageData.PageGroup;

		//Go to PageItem head
		while (CurrentPageGroup->Previous != nullptr) { CurrentPageGroup = CurrentPageGroup->Previous; }

		//Write All PageItems
		while (CurrentPageGroup != nullptr)
		{
			out << *CurrentPageGroup;
			CurrentPageGroup = CurrentPageGroup->Next;
		}
	}

	return out;
}
ostream& operator<<(ostream& out, const llBookData& BookData)
{
	out << "BOOK" << endl;
	out << BookData.PageCount << endl;

	//Write PageGroup Data's PageItems (if it has any)
	if (BookData.Page != nullptr)
	{
		//Get ShapeGroup's Shape
		llPageData* CurrentPage = BookData.Page;

		//Go to PageItem head
		while (CurrentPage->Previous != nullptr) { CurrentPage = CurrentPage->Previous; }

		//Write All PageItems
		while (CurrentPage != nullptr)
		{
			out << *CurrentPage;
			CurrentPage = CurrentPage->Next;
		}
	}

	return out;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

// Linked List in
istream& operator>>(istream& in, llVertexData& VertexData)
{
	//Read Vertex Data
	string BookMarker;
	in >> BookMarker;
	if (BookMarker == "VERTEX")
	{
		in >> VertexData.Position;
		in >> VertexData.TexCoords;
		in >> VertexData.Color;
		in >> VertexData.TexIndex;
		in >> VertexData.CentralPoint;
		in >> VertexData.GUIAction;
	}
	else
	{
	Log::LogString("Incorrect Match! Vertex not lined up");
	}

	return in;
}

istream& operator>>(istream& in, llShapeData& ShapeData)
{
	string BookMarker;
	in >> BookMarker;
	if (BookMarker == "SHAPE")
	{
		in >> ShapeData.Ascii;
		in >> ShapeData.ActiveTexture;
		in >> ShapeData.Action;
		in >> ShapeData.Type;
		in >> ShapeData.InputType;
		in >> ShapeData.Position;
		in >> ShapeData.Size;
		in >> ShapeData.Color;
		in >> ShapeData.PositionOffset;
		in >> ShapeData.SizeOffset;
		in >> ShapeData.ColorOffset;
		in >> ShapeData.HighlightColor;
		in >> ShapeData.MouseAccess;
		in >> ShapeData.Centered;
		in >> ShapeData.Highlighted;
		in >> ShapeData.Hide;
		in >> ShapeData.Top;
		in >> ShapeData.Bottom;
		in >> ShapeData.Left;
		in >> ShapeData.Right;

		string PartText;
		//Load entire string
		while(PartText != "`")
		{
			in >> PartText; //Not Needed
			ShapeData.Text += PartText;
		}

		in >> ShapeData.EndStart; //Not Needed
		in >> ShapeData.TextCentered; //Not Needed
		in >> ShapeData.ChangeAsGroup; //Not Needed
		llVertexData* CurrentVertex = nullptr;
		//Get Current Vertex
		if (ShapeData.Vertexx != nullptr) { CurrentVertex = ShapeData.Vertexx; }
		else { Log::LogString("Error no vertices in shape"); }

		//Go to Vertex head
		while (CurrentVertex->Previous != nullptr) { CurrentVertex = CurrentVertex->Previous; }

		//Load Data into all Vertices
		while (CurrentVertex != nullptr)
		{
			if (CurrentVertex != nullptr)
			{
				in >> *CurrentVertex;
			}
			else
			{
				cout << "Vertex Load error" << endl;
			}
			CurrentVertex = CurrentVertex->Next;
		}
	}
	else
	{
		Log::LogString("Incorrect Match! Shape not lined up");
	}

	return in;
}

istream& operator>>(istream& in, llShapeGroupData& ShapeGroupData)
{
	string BookMarker;
	in >> BookMarker;
	if (BookMarker == "SHAPEGROUP")
	{
		llShapeData* NewShape = nullptr;
		int PreviousShapeCount;
		//string Dead;
		//in >> Dead;
		in >> PreviousShapeCount;
		in >> ShapeGroupData.Type;
		in >> ShapeGroupData.XYShapePerRow;
		in >> ShapeGroupData.ShapeSize;
		in >> ShapeGroupData.Position;
		in >> ShapeGroupData.Size;
		in >> ShapeGroupData.Color;
		in >> ShapeGroupData.PositionOffset;
		in >> ShapeGroupData.SizeOffset;
		in >> ShapeGroupData.ColorOffset;
		in >> ShapeGroupData.HighlightColor;
		in >> ShapeGroupData.Centered;
		in >> ShapeGroupData.Highlighted;
		in >> ShapeGroupData.MouseAccess;
		in >> ShapeGroupData.Hide;
		in >> ShapeGroupData.ChangeAsGroup;
		in >> ShapeGroupData.Top;
		in >> ShapeGroupData.Bottom;
		in >> ShapeGroupData.Left;
		in >> ShapeGroupData.Right;

		ShapeGroupData.ShapeCount = 0;

		//Count needs to be >= 1
		for (int i = 0; i < PreviousShapeCount; i++)
		{
			//Add Shape
			NewShape = MasterElement::AddShape(FileSystem::THISBOOK);
			//Load Data into Shape

			if (NewShape != nullptr)
			{
				in >> *NewShape;
			}
			else
			{
				cout << "Shape Load error" << endl;
			}
		}
	}
	else
	{
		Log::LogString("Incorrect Match! ShapeGroup not lined up");
	}
	return in;
}
istream& operator>>(istream& in, llPageItemData& PageItemData)
{
	string BookMarker;
	in >> BookMarker;
	if (BookMarker == "PAGEITEM")
	{
		llShapeGroupData* NewShapeGroup = nullptr;
		int PreviousShapeGroupCount;
		//string Dead;
		//in >> Dead;
		in >> PreviousShapeGroupCount;
		in >> PageItemData.Type;
		in >> PageItemData.Position;
		in >> PageItemData.Size;
		in >> PageItemData.Color;
		in >> PageItemData.PositionOffset;
		in >> PageItemData.SizeOffset;
		in >> PageItemData.ColorOffset;
		in >> PageItemData.XYShapePerRow;
		in >> PageItemData.ShapeSize;
		in >> PageItemData.HighlightColor;
		in >> PageItemData.Centered;
		in >> PageItemData.Highlighted;
		in >> PageItemData.MouseAccess;
		in >> PageItemData.ChangeAsGroup;
		in >> PageItemData.Top;
		in >> PageItemData.Bottom;
		in >> PageItemData.Left;
		in >> PageItemData.Right;

		PageItemData.ShapeGroupCount = 0;

		for (int i = 0; i < PreviousShapeGroupCount; i++)
		{
			//Add ShapeGroup
			NewShapeGroup = MasterElement::AddShapeGroup(FileSystem::THISBOOK);

			//Load Data into ShapeGroup
			if (NewShapeGroup != nullptr)
			{
				in >> *NewShapeGroup;
			}
			else
			{
				cout << "ShapeGroup Load error" << endl;
			}
		}
	}
	else
	{
		Log::LogString("Incorrect Match! PageItem not lined up");
	}

	return in;
}
istream& operator>>(istream& in, llPageGroupData& PageGroupData)
{
	string BookMarker;
	in >> BookMarker;
	if (BookMarker == "PAGEGROUP")
	{
		int PreviousPageItemCount;
		llPageItemData* NewPageItem = nullptr;
		//string Dead;
		//in >> Dead;
		in >> PreviousPageItemCount;

		Log::LogInt("PreviousPageItemCount", PreviousPageItemCount);

		in >> PageGroupData.Type;
		in >> PageGroupData.Position;
		in >> PageGroupData.Size;
		in >> PageGroupData.Color;
		in >> PageGroupData.XYShapePerRow;
		in >> PageGroupData.ShapeSize;
		in >> PageGroupData.HighlightColor;
		in >> PageGroupData.Centered;
		in >> PageGroupData.Highlighted;
		in >> PageGroupData.MouseAccess;
		in >> PageGroupData.ChangeAsGroup;
		in >> PageGroupData.Top;
		in >> PageGroupData.Bottom;
		in >> PageGroupData.Left;
		in >> PageGroupData.Right;

		PageGroupData.PageItemCount = 0;

		for (int i = 0; i < PreviousPageItemCount; i++) 
		{
			//Add PageItem
			NewPageItem = MasterElement::AddPageItem(FileSystem::THISBOOK);

			//Load Data into PageItem
			if (NewPageItem != nullptr)
			{
				in >> *NewPageItem;
			}
			else
			{
				cout << "PageItem Load error" << endl;
			}
		
		}
	}
	else
	{
		Log::LogString("Incorrect Match! PageGroup not lined up");
	
	}
	

	return in;
}
istream& operator>>(istream& in, llPageData& Page)
{
	string BookMarker;
	in >> BookMarker;
	if (BookMarker == "PAGE")
	{
		int PreviousPageGroupCount;
		llPageGroupData* NewPageGroup = nullptr;
		//string Dead;
		//in >> Dead;
		in >> PreviousPageGroupCount;
		Page.PageGroupCount = 0;


		Log::LogInt("Previous PageGroup Count", PreviousPageGroupCount);

		for (int i = 0; i < PreviousPageGroupCount; i++)
		{
			//Add PageGroup
			NewPageGroup = MasterElement::AddPageGroup(FileSystem::THISBOOK);

			//Load Data into PageGroup
			if (NewPageGroup != nullptr)
			{
				in >> *NewPageGroup;
			}
			else
			{
				cout << "PageGroup Load error" << endl;
			}

			cout << Page.PageGroupCount << endl;
		}
	}
	else
	{
		Log::LogString("Incorrect Match! Page not lined up");
	}
	return in;
}

istream& operator>>(istream& in, llBookData& Book)
{
	string BookMarker;
	in >> BookMarker;

	cout << BookMarker << endl;
	if (BookMarker == "BOOK")
	{
		llPageData* NewPage = nullptr;
		int PreviousPageCount;
		in >> PreviousPageCount;
		Log::LogInt("Previous PageCount Count", PreviousPageCount);

		Book.PageCount = 0;

		for (int i = 0; i < PreviousPageCount; i++) //needs to at least have one to enter
		{
			//Add Page
			NewPage = MasterElement::AddPage(FileSystem::THISBOOK);

			//Load Data into Page
			if (NewPage != nullptr)
			{
				in >> *NewPage;

				cout << "PagePointer " << FileSystem::THISBOOK->Page << endl;
			}
			else
			{
				cout << "Page Load error" << endl;
			}
		}
	}
	else
	{
		Log::LogString("Incorrect Match! Book not lined up");
	}

	return in;
}