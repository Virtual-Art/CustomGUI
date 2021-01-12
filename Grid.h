#ifndef NEWGRID
#define NEWGRID

#include <iostream>
#include <string.h>
#include "ElementGroup.h"

using namespace std;

class NewGrid : public ShapeGroup
{
public: 

	NewGrid(Page& Page);
	NewGrid(Page& Page, ShapeGroupData& ShapeGroupData);
	NewGrid(Page& Page, ShapeData& ShapeData);
	NewGrid(Page& Page, int GroupID);

	void AddGrid();////
	///
	void SetShapeData();
	int CreateGrid();
	///

	void Update();////
	///
	//SetShapeData
	void ReplaceGrid();
	///

	void SetGridXY(glm::vec2 XY);

	//As a PErcentage out of 100
	void SetShapeSize(glm::vec2 ShapeSize);

private:


	void LoadGrid(Page* Page, int ShapeDataID);

	//Grid Setup Functions 
	glm::vec2 LoadShapeSize(glm::vec2 ShapeGroupSize, glm::vec2 XYShapesPerRow, glm::vec2 ShapeDataSize);
	glm::vec2 LoadShapePosition(glm::vec2 ShapeGroupPosition, glm::vec2 ShapeGroupSize, glm::vec2 XYShapesPerRow, glm::vec2 XYLoop, bool Centered);


};


#endif