#include "Book.h"

Book::Book(string FilePath)
{
	this->CurrentCount = 1;
	this->FilePath = FilePath;
}

void Book::AddPage(string Name, ShaderProgram ShapeShader)
{
	Page[CurrentCount].Name = Name;
	Page[CurrentCount].Init(ShapeShader);
	this->CurrentCount++;
}

void Book::Erase()
{
	for (int i = 0; i < CurrentCount; i++)
	{
	   Page[i].ErasePage();
	}
}

void Book::Update()
{
	for (int i = 0; i < CurrentCount; i++)
	{
		Page[i].LoadThisPage();
	}
}