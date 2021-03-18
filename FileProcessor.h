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
//#include "Page.h"
#include "Book.h"
#include "MasterElement.h"

using namespace std;

class FileSystem : public Page 
{
public:

	FileSystem();

	string CurrentDirectory;
	string FileListString;

	string FileList[100];
	string BackSlash = "\\\\";
	static llBookData* THISBOOK;
	unsigned int ListCount;

	//Change the Current Directories
	void ResetDirectory();
	void SetDirectory(string Directory);
	void ReverseDirectory();
	void ForwardDirectory(string DirectoryName);

	void LoadDirectory();

	void CreateNewFile(const string& FileName);

	void SaveBook(Book& Book);

	//This is where we load the file (through "Book" member)
	Book LoadBook(Book& Book, ShaderProgram ShaderProgram);

	void SavellBook(llBookData& Book, string FilePath);
	void LoadllBook(llBookData& Book, string FilePath);

	//void ReadShapeDataFromFile(const string FilePath);
	void DisplayDirectoryFiles();

	ostream& operator<<(ostream& hello);

	friend ostream& operator<<(ostream& out, const ShapeData& ShapeData);
	friend ostream& operator<<(ostream& out, const ShapeVertex& ShapeData);
	friend ostream& operator<<(ostream& out, const Page& Page);
	friend ostream& operator<<(ostream& out, Book& Book);

	friend istream& operator>>(istream& in, const ShapeData& ShapeData);
	friend istream& operator>>(istream& in, ShapeVertex& Vertex);
	friend istream& operator>>(istream& in, Page& Page);
	friend istream& operator>>(istream& in, Book& Book);

	// Linked List out
	friend ostream& operator<<(ostream& out, const llVertexData& ShapeData);
	friend ostream& operator<<(ostream& out, const llShapeData& ShapeData);
	friend ostream& operator<<(ostream& out, const llShapeGroupData& ShapeData);
	friend ostream& operator<<(ostream& out, const llPageItemData& ShapeData);
	friend ostream& operator<<(ostream& out, const llPageGroupData& ShapeData);
	friend ostream& operator<<(ostream& out, const llPageData& Page);
	friend ostream& operator<<(ostream& out, const llBookData& Book);

	friend ostream& operator<<(ostream& out, const glm::vec2& Vec2);
	friend ostream& operator<<(ostream& out, const glm::vec4& Vec4);

	friend istream& operator>>(istream& in, glm::vec2& Vec2);
	friend istream& operator>>(istream& in, glm::vec4& Vec4);

	// Linked List in
	friend istream& operator>>(istream& in, llVertexData& VertexData);
	friend istream& operator>>(istream& in, llShapeData& ShapeData);
	friend istream& operator>>(istream& in, llShapeGroupData& ShapeGroupData);
	friend istream& operator>>(istream& in, llPageItemData& PageItemData);
	friend istream& operator>>(istream& in, llPageGroupData& PageGroupData);
	friend istream& operator>>(istream& in, llPageData& Page);
	friend istream& operator>>(istream& in, llBookData& Book);
};

 ostream& operator<<(ostream& out, const ShapeData& ShapeData);
 ostream& operator<<(ostream& out, const ShapeVertex& ShapeData);
 ostream& operator<<(ostream& out, const Page& Page);
 ostream& operator<<(ostream& out, Book& Book);

 istream& operator>>(istream& in, const ShapeData& ShapeData);
 istream& operator>>(istream& in, ShapeVertex& Vertex);
 istream& operator>>(istream& in, Page& Page);
 istream& operator>>(istream& in, Book& Book);

 // Linked List
 ostream& operator<<(ostream& out, const llVertexData& ShapeData);
 ostream& operator<<(ostream& out, const llShapeData& ShapeData);
 ostream& operator<<(ostream& out, const llShapeGroupData& ShapeData);
 ostream& operator<<(ostream& out, const llPageItemData& ShapeData);
 ostream& operator<<(ostream& out, const llPageGroupData& ShapeData);
 ostream& operator<<(ostream& out, const llPageData& Page);
 ostream& operator<<(ostream& out, const llBookData& Book);

 ostream& operator<<(ostream& out, const glm::vec2& Vec2);
 ostream& operator<<(ostream& out, const glm::vec4& Vec4);

istream& operator>>(istream& in, glm::vec2& Vec2);
istream& operator>>(istream& in, glm::vec4& Vec4);

 // Linked List in
 istream& operator>>(istream& in, llVertexData& VertexData);
 istream& operator>>(istream& in, llShapeData& ShapeData);
 istream& operator>>(istream& in, llShapeGroupData& ShapeGroupData);
 istream& operator>>(istream& in, llPageItemData& PageItemData);
 istream& operator>>(istream& in, llPageGroupData& PageGroupData);
 istream& operator>>(istream& in, llPageData& Page);
 istream& operator>>(istream& in, llBookData& Book);


#endif
