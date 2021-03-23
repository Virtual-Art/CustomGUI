#ifndef BUTTON
#define BUTTON

#include <iostream>
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "MouseManager.h"
#include "KeyboardManager.h"
#include "ElementAction.h"
#include <vector>


using namespace std;

typedef void(*ButtonFunction)();

class Button 
{
public:

	static vector<ButtonFunction*> ActiveFunctions;

	//Behaviours
	ElementAction*** TriggeredActions;
	ElementAction* AutoActions;

	//Static Actions
	ButtonFunction* LogicalActions;

	//Continuous Actions
	ButtonFunction* ContinuousActions;

	void PlayLogicalActions();
	void PlayActiveActions();

	void ProcessMouseButtons(int MouseState);

	Button();
	~Button();

	void PlayActions(unsigned int MouseState);

	static void Empty();

};

#endif
