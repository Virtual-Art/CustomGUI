#ifndef CUSTOMSHAPE
#define CUSTOMSHAPE

#include <iostream>
#include "Shape.h"

class CustomShape : public Shape
{
public:

	CustomShape(Page& Page);
	CustomShape(Page& Page, ShapeData& ShapeData); //New Shape with existing Data
	CustomShape(Page& Page, int ShapeDataID);        //Existing Shape


	static glm::vec2 AllShapeRatios[50][4];
	static bool FirstCreation;
	static int ShapeAmount;

	void Add(int Character); 
	void Update(); 
	void SetAction(int ShapeDataActionID);
	void MakeShape(){};
	void SetVertex(int Index, Vertex Vertex);
	void SetVertices() {};
	void SetShapeRatios() {};

	void AddShapeToStack();

private:
	void CreateShapeRatioContainer();
};


#endif

