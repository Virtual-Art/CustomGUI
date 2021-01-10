#pragma once

#include <iostream>

class RawModel
{

public:

	RawModel(int VaoID, int VertexCount, int IndicesCount)
	{
		this->VaoID = VaoID;
		this->VertexCount = VertexCount;
		this->IndicesCount = IndicesCount;
	}

	int getVaoID()
	{
		return this->VaoID;
	}

	int getVertexCount()
	{
		return this->VertexCount;
	}

	int GetIndicesCount()
	{
		return this->IndicesCount;
	}

private:

	
	int VaoID;
	int VertexCount;
	int IndicesCount;

	

};
