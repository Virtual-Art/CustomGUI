#ifndef BUTTON
#define BUTTON

#include <iostream>
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ElementAction.h"

using namespace std;

class Button
{
public:

	//Behaviours
	ElementAction*** TriggeredActions;
	ElementAction* AutoActions;

	Button();
	~Button();

	void PlayActions(unsigned int MouseState);


};

#endif
