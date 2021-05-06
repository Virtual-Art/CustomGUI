#include "Button.h"


Button::Button()
{
	TriggeredActions = new ElementAction**[9];

	for (int i = 0; i < 9; i++)
	{
		TriggeredActions[i] = new ElementAction*[5];
	}

	LogicalActions = new ButtonFunction[11];

	for (int i = 0; i < 11; i++)
	{
		LogicalActions[i] = Empty;
	}

	ContinuousActions = new ButtonFunction[11];

	for (int i = 0; i < 11; i++)
	{
		ContinuousActions[i] = Empty;
	}


	for (int i = 0; i < 10; i++)
	{
		Single_Mouse_Actions Temp;
		MouseActions.emplace_back(Temp);
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

	delete[] ContinuousActions;
}


void Button::Add_Mouse_Action(int Mouse_Key, ButtonFunction Button_Function)
{

	//Add list if none
	
	Single_Mouse_Actions Temp;
	MouseActions[Mouse_Key].push_back(Button_Function);



	//Add Action
	//MouseActions[Mouse_Key].push_back(Button_Function);
	//Left_Actions.push_back(Button_Function);
}


void Button::PlayLogicalActions()
{
	//Before
	for (int i = 0; i < 11; i++)
	{
		LogicalActions[i]();
	}

	//NEW
	//Go through all Mouse
	for (const auto& ActionList : MouseActions)
	{
		for (const auto& Action : ActionList)
		{
			Action();
		}
	}
}

void Button::PlayActiveActions()
{
	for (int i = 0; i < 11; i++)
	{
		LogicalActions[i]();
	}
}

void Button::ProcessMouseButtons(int MouseState)
{
	LogicalActions[MouseState]();

	LogicalActions[10]();

	if (ContinuousActions[MouseState] != Empty)
	{
	//	ActiveFunctions[ActiveFunctions.size()] = ContinuousActions[MouseState];
	}

	//EX: Play all actions for MouseState = GUI_LEFT_CLICKED
	//Go through action list
	for (const auto& Action : MouseActions[MouseState])
	{
		Action();
	}
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



