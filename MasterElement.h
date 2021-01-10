#ifndef MASTERELEMENT
#define MASTERELEMENT

#include <iostream>
#include "Page.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

class MasterElement
{
public:
	MasterElement();

	virtual void Add_Default() {}; //Editor/None Set in Stone
	virtual void Add_Duplicate() {}; //Editor/None Set in Stone
	virtual void Add_Insert() {}; //Editor/None Set in Stone
	virtual void DeleteShape() {};
	virtual void SwitchToShape(int RequstedShapeID) {};
	virtual void SwitchToShape(Page& Page, int RequstedShapeID) {};
	//virtual void SetShape(ShapeData& ShapeData) {};
	//virtual void SetShape(ShapeData& ShapeData, glm::vec2 PSConversions) {};
	virtual void SetPosition(glm::vec2 Position) {};                     //Set All
	virtual void SetPosition(glm::vec2 Position, glm::vec2 bools) {};    //Set all with true boolean(s)
	virtual void SetSize(glm::vec2 Size) {};                             //Set All
	virtual void SetSize(glm::vec2 Size, glm::vec2 bools) {};            //Set all with true boolean(s)
	virtual void SetColor(glm::vec4 Color) {};                           //..
	virtual void SetColor(glm::vec4 Color, glm::vec4 bools) {};          //...
      
    // Conversions
	virtual void SetPosition(glm::vec2 Position, int Conversion) {};                     //Set All
	virtual void SetPosition(glm::vec2 Position, glm::vec2 bools, int Conversion) {};    //Set all with true boolean(s)
	virtual void SetSize(glm::vec2 Size, int Conversion) {};                             //Set All
	virtual void SetSize(glm::vec2 Size, glm::vec2 bools, int Conversion) {};            //Set all with true boolean(s)
	  
	virtual void OffsetPosition(glm::vec2 Position) {};                  //..
	virtual void OffsetPosition(glm::vec2 Position, glm::vec2 bools) {}; //...
	virtual void OffsetSize(glm::vec2 Size) {};                          //..
	virtual void OffsetSize(glm::vec2 Size, glm::vec2 bools) {};         //...
	virtual void OffsetColor(glm::vec4 Color) {};                        //..
	virtual void OffsetColor(glm::vec4 Color, glm::vec4 bools) {};       //...
	  
	//rtu Conversions
	virtual void OffsetPosition(glm::vec2 Position, int Conversion) {};                  //..
	virtual void OffsetPosition(glm::vec2 Position, glm::vec2 bools, int Conversion) {}; //...
	virtual void OffsetSize(glm::vec2 Size, int Conversion) {};                          //..
	virtual void OffsetSize(glm::vec2 Size, glm::vec2 bools, int Conversion) {};

	virtual glm::vec2 GetPosition() { return { -1.0, -1.0 }; };
	virtual glm::vec2 GetSize() { return { -1.0, -1.0 }; };
	virtual glm::vec4 GetColor() { return { -1.0, -1.0, -1.0, -1.0 }; };
	virtual bool GetMouseAccess() { return false; };
};

#endif
