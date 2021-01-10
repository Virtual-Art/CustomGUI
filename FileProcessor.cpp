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
	out << ShapeData.ShapeGroupStart << endl;
	out << ShapeData.ShapeGroupCount << endl;
	out << ShapeData.ShapeGroupOffset << endl;
	out << ShapeData.ShapeGroupXYShapePerRow[0] << " " << ShapeData.ShapeGroupXYShapePerRow[1] << endl;
	out << ShapeData.ShapeGroupPosition[0] << " " << ShapeData.ShapeGroupPosition[1] << endl;
	out << ShapeData.ShapeGroupSize[0] << " " << ShapeData.ShapeGroupSize[1] << endl;
	out << ShapeData.ShapeGroupShapeSize[0] << " " << ShapeData.ShapeGroupShapeSize[1] << endl;
	out << ShapeData.ShapeGroupColor[0] << " " << ShapeData.ShapeGroupColor[1] << " " << ShapeData.ShapeGroupColor[2] << " " << ShapeData.ShapeGroupColor[3] << endl;
	out << ShapeData.ShapeGroupCentered << endl;
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
	in >> ShapeData.ShapeGroupStart;
	in >> ShapeData.ShapeGroupCount;
	in >> ShapeData.ShapeGroupOffset;
	in >> ShapeData.ShapeGroupXYShapePerRow[0] >> ShapeData.ShapeGroupXYShapePerRow[1];
	in >> ShapeData.ShapeGroupPosition[0] >> ShapeData.ShapeGroupPosition[1];
	in >> ShapeData.ShapeGroupSize[0] >> ShapeData.ShapeGroupSize[1];
	in >> ShapeData.ShapeGroupShapeSize[0] >> ShapeData.ShapeGroupShapeSize[1];
	in >> ShapeData.ShapeGroupColor[0] >> ShapeData.ShapeGroupColor[1] >> ShapeData.ShapeGroupColor[2] >> ShapeData.ShapeGroupColor[3];
	in >> ShapeData.ShapeGroupCentered;
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