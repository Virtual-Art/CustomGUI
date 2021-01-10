#ifndef FILEPROCESS
#define FILEPROCESS
#include <iostream>
//#include <Windows.h>
#include <string>
#include <fstream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/GLM.HPP"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Page.h"
#include "Book.h"

using namespace std;

class FileSystem : public Page 
{
public:

	FileSystem();

	string CurrentDirectory;
	string FileListString;

	string FileList[100];
	string BackSlash = "\\\\";
	unsigned int ListCount;

	//Change the Current Directories
	void ResetDirectory();
	void SetDirectory(string Directory);
	void ReverseDirectory();
	void ForwardDirectory(string DirectoryName);

	void LoadDirectory();

	void CreateNewFile(const string& FileName);

	void SaveBook(Book& Book);

	Book LoadBook(Book& Book, ShaderProgram ShaderProgram);

	//void ReadShapeDataFromFile(const string FilePath);
	void DisplayDirectoryFiles();

	friend ostream& operator<<(ostream& out, const ShapeData& ShapeData);
	friend ostream& operator<<(ostream& out, const ShapeVertex& ShapeData);
	friend ostream& operator<<(ostream& out, const Page& Page);
	friend ostream& operator<<(ostream& out, Book& Book);

	friend istream& operator>>(istream& in, const ShapeData& ShapeData);
	friend istream& operator>>(istream& in, ShapeVertex& Vertex);
	friend istream& operator>>(istream& in, Page& Page);
	friend istream& operator>>(istream& in, Book& Book);

};

 ostream& operator<<(ostream& out, const ShapeData& ShapeData);
 ostream& operator<<(ostream& out, const ShapeVertex& ShapeData);
 ostream& operator<<(ostream& out, const Page& Page);
 ostream& operator<<(ostream& out, Book& Book);

 istream& operator>>(istream& in, const ShapeData& ShapeData);
 istream& operator>>(istream& in, ShapeVertex& Vertex);
 istream& operator>>(istream& in, Page& Page);
 istream& operator>>(istream& in, Book& Book);




#endif
