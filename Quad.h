#ifndef QUAD
#define QUAD


#include <iostream>
#include <string>
#include "Shape.h"
#include "ElementAction.h"

using namespace std;

class Quad : public Shape
{
public:

	//Linked List Constructors
	Quad(llBookData* llBook);
	Quad(llBookData* llBook, llShapeData* llShape);
	Quad(llShapeData* llShape);

	//Constructors
	Quad(Page& Page);                         //New Shape
	Quad(Page& Page, ShapeData& ShapeData);   //New Shape with existing Data
	Quad(Page& Page, int ShapeDataID);        //Existing Shape

	//Representing an unkown future quad

	//PureVirtual Functions
	void Update();
	void SetllQuad();

	void BuildShapeVertices();
	void SetShapeRatios();
	void SetAction(int ShapeDataActionID);

private:

};

#endif