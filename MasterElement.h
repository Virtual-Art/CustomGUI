#ifndef MASTERELEMENT
#define MASTERELEMENT

//Position Conversions
#define P_PIXEL_TO_COMPUTER 1
#define MIDDLE_TO_TOPLEFT 2
#define TOPLEFT_PIXEL_TO_COMPUTER 3
#define P_COMPUTER_TO_PIXEL 4
#define P_TOP_LEFT_TO_MIDDLE 5

//Size Conversions
#define S_PIXEL_TO_COMPUTER 1
#define S_ONE_TO_COMPUTER 2
#define S_COMPUTER_TO_PIXEL 3

#include <iostream>
#include "Page.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Log.h"

using namespace std;

//All the second tier hierarchy like Shape, ShapeGroup, PageItem, PageGroup defaults will be custom for creator
class MasterElement
{
public:
	MasterElement();
	bool Initialized = false;
	Page* CurrentPage;
	ShapeData LoadedShape;

	virtual void Add_Default() {};
	virtual void Add_Duplicate() {}; 
	virtual void Add_Insert() {};
	virtual void Delete() {};
	virtual void Switch(int RequstedShapeID) {};
	virtual void Switch(Page& Page, int RequstedShapeID) {};
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

	glm::vec2 ApplyPositionConversion(glm::vec2 Position, int Conversion, glm::vec2 Size);
	glm::vec2 ApplyPositionConversion(glm::vec2 Position, int Conversion);
	glm::vec2 ApplySizeConversion(glm::vec2 Position, int Conversion);

	//Position TopLeft/BottomLeft Conversions 
	glm::vec2 PTLPixelToComputer(glm::vec2 Position); //Working
	glm::vec2 PBLPixelToComputer(glm::vec2 Position); //Working
	glm::vec2 PMiddleToTopLeft(glm::vec2 Position, glm::vec2 Size);
	glm::vec2 PTopLeftToMiddle(glm::vec2 Position, glm::vec2 Size);

	glm::vec2 PComputerToTLPixel(glm::vec2 Position); //Working
	glm::vec2 PComputerToBLPixel(glm::vec2 Position); //Working


	//SizeConversions
	glm::vec2 SPixelToComputer(glm::vec2 Size); //Working
	glm::vec2 SOneToComputer(glm::vec2 Size);   //Working

	glm::vec2 SComputerToPixel(glm::vec2 Size); //Working
	glm::vec2 SComputerToOne(glm::vec2 Size);   //Working

	bool IsInitialized();
	bool IsInBounds(int ID);

protected:

	

};

#endif
