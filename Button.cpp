#include "Button.h"


Button::Button()
{
	TriggeredActions = new ElementAction**[9];

	for (int i = 0; i < 9; i++)
	{
		TriggeredActions[i] = new ElementAction*[5];
	}

	LogicalActions = new ButtonFunction[5];

	for (int i = 0; i < 5; i++)
	{
		LogicalActions[i] = Empty;
	}
}

void Button::Empty()
{

}

Button::~Button()
{
	for (int i = 0; i < 5; i++)
	{
		//Delete the data that the 4 Attributes point to
		delete[] TriggeredActions[i];
	}

	//then delete the pointer that points to the 4 attributes
	delete[] TriggeredActions;

	delete[] LogicalActions;
}

void Button::PlayLogicalActions()
{
	for (int i = 0; i < 5; i++)
	{
		LogicalActions[i]();
	}
}

void Button::ProcessMouseButtons(int MouseState)
{
	if (MouseState == 1) //MouseLeft Clicked
	{
		LogicalActions[0]();
	}

	if (MouseState == GUI_MOUSERIGHT_CLICKED) //MouseLeft Clicked
	{
		//cout << "lalqalalalalallalala" << endl;
		LogicalActions[1]();
	}

	if (MouseState == GUI_MOUSELEFT_CLICKED) //MouseLeft Clicked
	{
		//cout << "lalqalalalalallalala" << endl;
		LogicalActions[2]();
	}

	//LogicalActions[3]();
}

//Helper Function
//Sets {1,2,3/ 7,8,9/ 13,14,15} in sqeuence from 0
int TripleToSequence(int MouseState)
{
	// 1, 2, 3
	if (MouseState > 0 && MouseState < 4)
	{
		return MouseState - 1;
	}
	if (MouseState > 6 && MouseState < 10)
	{
		return MouseState - 4;
	}
	if (MouseState > 12 && MouseState < 16)
	{
		return MouseState - 7;
	}
}


void Button::PlayActions(unsigned int MouseState)
{
	if (MouseState < 1 || MouseState > 15)
	{
		return;
	}

	int ControlState = TripleToSequence(MouseState);


	for (int i = 0; i < 5; i++)
	{
		ElementAction* CurrentAction = TriggeredActions[ControlState][i];
		if (CurrentAction)
		{
			CurrentAction->Play();
		}
	}
}



