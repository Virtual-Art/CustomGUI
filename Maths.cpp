#include "Maths.h"

#define PI 3.14159
//glm::mat4 Maths::Scale(glm::vec3 Scale)
//{
//	
//}
//
//glm::mat4 Maths::Translate(glm::vec3 Translate)
//{
//	
//}
//glm::mat4 Maths::Rotate(glm::vec3 Rotate)
//{
//	
//}

//all this is is a mat4
//Whatever is created here, the information-(TransMatrix) is being prepared to be fed into the VertexShader
glm::mat4 Maths::CreateTransformationMatrix(glm::vec3 Translation, float Rx, float Ry, float Rz, glm::vec3 Scale)
{

	glm::mat4 TransformationMat4 = glm::mat4(1.0f);
	TransformationMat4 = glm::translate(TransformationMat4, glm::vec3(Translation));
	TransformationMat4 = glm::rotate(TransformationMat4, glm::radians(Rx), glm::vec3(1.0, 0.0, 0.0));
	TransformationMat4 = glm::rotate(TransformationMat4, glm::radians(Ry), glm::vec3(0.0, 1.0, 0.0));
	TransformationMat4 = glm::rotate(TransformationMat4, glm::radians(Rz), glm::vec3(0.0, 0.0, 1.0));
	TransformationMat4 = glm::scale(TransformationMat4, glm::vec3(Scale));

	
	//i've called it Transformation, in video it's Matrix
	return TransformationMat4;
}


//ElementVertices Maths::GetElementVertices(glm::vec3 ElementPosition, float xSize, float ySize, bool Centered)
//{
//	if (Centered == true)
//	{
//		ElementPosition[0] += xSize / 2;
//		ElementPosition[1] -= ySize / 2;
//	}
//	//cout << "xSize: "<<xSize << endl;
//	//cout << "ySize: "<<ySize << endl;
//
//	//Producing Vertices with top left being the original x,y Pos
//	static float Vertices[8];
//	Vertices[0] = ElementPosition[0];
//	Vertices[1] = ElementPosition[1];
//	Vertices[2] = ElementPosition[0] + xSize;
//	Vertices[3] = ElementPosition[1];
//	Vertices[4] = ElementPosition[0];
//	Vertices[5] = ElementPosition[1] - ySize;
//	Vertices[6] = ElementPosition[0] + xSize;
//	Vertices[7] = ElementPosition[1] - ySize;
//
//	ElementVertices ElementVertices;
//	ElementVertices.TopLeft     = { Vertices[0], Vertices[1] };
//	ElementVertices.TopRight    = { Vertices[2], Vertices[3] };
//	ElementVertices.BottomLeft  = { Vertices[4], Vertices[5] };
//	ElementVertices.BottomRight = { Vertices[6], Vertices[7] };
//
//	    //cout << "Vertices[0]: " << Vertices[0] << endl;
//		//cout << "Vertices[1]: " << Vertices[1] << endl;
//		//cout << "Vertices[2]: " << Vertices[2] << endl;
//		//cout << "Vertices[3]: " << Vertices[3] << endl;
//		//cout << "Vertices[4]: " << Vertices[4] << endl;
//		//cout << "Vertices[5]: " << Vertices[5] << endl;
//		//cout << "Vertices[6]: " << Vertices[6] << endl;
//		//cout << "Vertices[7]: " << Vertices[7] << endl;
//
//
//	return ElementVertices;
//}

//ElementTexCoords Maths::GetBasicTexCoords()
//{
//	ElementTexCoords BasicTexCoords;
//	BasicTexCoords.TopRight    = { 1.0, 0.0 };
//	BasicTexCoords.BottomRight = { 1.0, 1.0 }; // top right
//	BasicTexCoords.TopLeft     = { 0.0, 0.0 };
//	BasicTexCoords.BottomLeft  = { 0.0, 1.0 }; // top left
//
//
//	return BasicTexCoords;
//}

glm::vec2 Maths::GridShapeSize(glm::vec2 ShapeGroupSize, glm::vec2 XYElementsPerRow, glm::vec2 ElementSize)
{

	//cout << (ShapeGroupSize[0] / (XYElementsPerRow[0])) << endl;
    //cout << (ShapeGroupSize[1] / (XYElementsPerRow[1])) << endl;

	//cout << "XYElements per row " << XYElementsPerRow[0] << XYElementsPerRow[1] << endl;
	float xElementSize = (ShapeGroupSize[0] / (XYElementsPerRow[0]));
	float yElementSize = (ShapeGroupSize[1] / (XYElementsPerRow[1]));

	xElementSize *= ElementSize[0]; // we don't want the tiles to be full size, or else we can't see anything
	yElementSize *= ElementSize[1]; // so we are reducing the size to 75 percent

	//cout << "ElementSIZE " << xElementSize << endl;
	//cout << "ElementSIZE " << yElementSize << endl;

	return {xElementSize, yElementSize};
}



glm::vec2 Maths::GridElementPosition(glm::vec2 ShapeGroupPosition, glm::vec2 ShapeGroupSize, glm::vec2 XYElementsPerRow, glm::vec2 XYLoop, bool Centered)
{
	//means the position origin is in the middle of the Element, if thats the case, needs to be moved to top left for data writing
	//if (Centered == true)
	//{
	//	ShapeGroupPositionCenterToTopLeft(ShapeGroupPosition, ShapeGroupSize);
	//}
	
	//The reason i'm doing this again is because i need the full size of the Element to calculate the proper position
	glm::vec2 ElementSize = GridShapeSize(ShapeGroupSize, XYElementsPerRow, { 1, 1 });
	
	float xStartOffset = ElementSize[0] /2;
	float yStartOffset = ElementSize[1] /2;
	float xRegOffset = ElementSize[0];
	float yRegOffset = ElementSize[1];
	ShapeGroupPosition.x += (xStartOffset + xRegOffset * XYLoop.x);
	ShapeGroupPosition.y -= (yStartOffset + yRegOffset * XYLoop.y);
	return ShapeGroupPosition;
}

//sets actual position to center
glm::vec2 Maths::TopLeftToCenter(glm::vec2 Position, glm::vec2 Size)
{
	Position.x += (Size.x / 2);
	Position.y -= (Size.y / 2);
	return Position;
}

//sets the centered position to top left
glm::vec2 Maths::CenterToTopLeft(glm::vec2 Position, glm::vec2 Size)
{
	Position.x -= (Size.x / 2);
	Position.y += (Size.y / 2);
	return Position;
}

// you will need to convert from middle to Top Left when you pass in data to the buffer


//Vertex& Maths::SetTopRight(const Element& Element, Vertex& Vertex)
//{
//	Vertex.Position  = { Element.Position[0] + Element.Size[0],Element.Position[1]};
//	Vertex.TexCoords = { 1.0, 0.0 }; //top right
//	Vertex.Color     = Element.Color;
//	Vertex.TexIndex  = Element.ActiveTexture;  
//	Vertex.CentralPoint = {Element.Position[0] + (Element.Size[0]/2), Element.Position[1] - (Element.Size[1]/2)};
//	Vertex.GUIAction = Element.Action;
//
//	return Vertex;
//}

//Vertex& Maths::SetBottomRight(const Element& Element, Vertex& Vertex)
//{
//	Vertex.Position = { Element.Position[0] + Element.Size[0], Element.Position[1] - Element.Size[1]};
//	Vertex.TexCoords = { 1.0, 1.0 }; //bottom right
//	Vertex.Color = Element.Color;
//	Vertex.TexIndex = Element.ActiveTexture;
//	Vertex.CentralPoint = { Element.Position[0] + (Element.Size[0] / 2), Element.Position[1] - (Element.Size[1] / 2) };
//	Vertex.GUIAction = Element.Action;
//
//	return Vertex;
//	//#2
//}
//Vertex& Maths::SetTopLeft(const Element& Element, Vertex& Vertex)
//{
//	Vertex.Position = { Element.Position[0], Element.Position[1]};
//	Vertex.TexCoords = { 0.0, 0.0 };  //topleft
//	Vertex.Color = Element.Color;
//	Vertex.TexIndex = Element.ActiveTexture;
//	Vertex.CentralPoint = { Element.Position[0] + (Element.Size[0] / 2), Element.Position[1] - (Element.Size[1] / 2) };
//	Vertex.GUIAction = Element.Action;
//
//	return Vertex;
//	//#3
//}
//Vertex& Maths::SetBottomLeft(const Element& Element, Vertex& Vertex)
//{
//	Vertex.Position = { Element.Position[0], Element.Position[1] - Element.Size[1]};
//	Vertex.TexCoords = { 0.0, 1.0 };
//	Vertex.Color = Element.Color; //bottom left
//	Vertex.TexIndex = Element.ActiveTexture;
//	Vertex.CentralPoint = { Element.Position[0] + (Element.Size[0] / 2), Element.Position[1] - (Element.Size[1] / 2) };
//	Vertex.GUIAction = Element.Action;
//
//	return Vertex;
//	//#4
//}


//cos Path starts at 1
float Maths::cosOscillation(float Time, float Delay, float Size, float SecondsPerRevolution, float OscillationPosition)
{
	//We are deviding by two because the input is what the user wants but the function wants half
	//Size in between 0 - 1
	float FunctionSize = Size / 2;
	float OneRevolution = (2 * PI);
	float RevolutionsPerSecond = OneRevolution / SecondsPerRevolution;
	return FunctionSize * cos(RevolutionsPerSecond * (Time - Delay)) + OscillationPosition;

	// y = A * cos( 2 * PI * x/ Lambda) + BasePosition
	// Function Size = cos only outputs a number between -1 and 1; So function size can be between -5 and 5 or -.42 ans .42
	// y = result( x Amount left, x Amount right, x Amount top, x Amount bottom, x Amount back, x Amount forth).
	// cos Starting direction( Left or Right, Top or Bottom, Front or Back)
	// 2 * PI = 1 Revolution(1 Turn/ 1 Lap/ 1 Back and then forth/ 1 Top and then Bottom/ ONE Left and then right)
	// Lambda = The time it takes for 1 revolution(Time for 1 lap/ 1 back and forth)
	// 2 * PI * x/ Lamba = How Many Revolutions per second (ex: 0.1 Revolutions per second)
	// + Base Position = Self Explanatory
}  

float Maths::cosOscillation(float Time, float Size, int RevolutionsPerSecond, float OscillationPosition)
{
	//We are deviding by two because the input is what the user wants but the function wants half
	//Size in between 0 - 1
	float FunctionSize = Size / 2;
	float OneRevolution = (2 * PI);
	return FunctionSize * cos(RevolutionsPerSecond * Time) + OscillationPosition;

	// y = A * cos( 2 * PI * x/ Lambda) + BasePosition
	// y = result( x Amount left, x Amount right, x Amount top, x Amount bottom, x Amount back, x Amount forth).
	// cos Starting direction( Left or Right, Top or Bottom, Front or Back)
	// 2 * PI = 1 Revolution(1 Turn/ 1 Lap/ 1 Back and then forth/ 1 Top and then Bottom/ ONE Left and then right)
	// Lambda = The time it takes for 1 revolution(Time for 1 lap/ 1 back and forth)
	// 2 * PI * x/ Lamba = How Many Revolutions per second (ex: 0.1 Revolutions per second)
	// + Base Position = Self Explanatory
}

//sin Path starts as 0
float Maths::sinOscillation(float Time, float Size, float Speed, float OscillationPosition)
{
	return (Size * (sin(Time * Speed))) + OscillationPosition;
}

float Maths::Exponential(float Time, float StartOffset, float Speed, float Power, float Size, float AxisOfSymmetry)
{
	//Size = How Big the Porablo is in width
	//StartOffset = 
	//Power = the Power that Time is Being Multiplied by 
	//AxisOfSymmetry = When the loop stops for odd powers, and when the loop changes direction for even powers 
	return (Size * (pow((Time * Speed) - StartOffset, Power)) + AxisOfSymmetry);
}
