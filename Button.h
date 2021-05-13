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
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <set>


using namespace std;
typedef void(*ButtonFunction)();

//typedef list<ButtonFunction> Single_Mouse_Actions;
typedef set<ButtonFunction> Single_Mouse_Actions;

class Button 
{
public:

	//Key = Mouse Key Pressed // Value: Set of Actions ( void() Functions )
	vector<Single_Mouse_Actions> MouseActions;

	//a vector with each slot container a list of actions

	Single_Mouse_Actions Left_Actions; //This Works i can add 1 action

	//Behaviours
	ElementAction*** TriggeredActions;
	ElementAction* AutoActions;

	//Static Actions
	ButtonFunction* LogicalActions;

	//Continuous Actions
	ButtonFunction* ContinuousActions;

	void Add_Mouse_Action(int Mouse_Key, ButtonFunction Button_Function);

	void PlayLogicalActions();
	void PlayActiveActions();

	void ProcessMouseButtons(int MouseState);

	Button();
	~Button();

	void PlayActions(unsigned int MouseState);

	static void Empty();

};

#endif
