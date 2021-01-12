#include "MouseManager.h"

//In this class we will be managing mouse input including left, right. scroll, position

//our static variable

//MouseStats MouseManager::Stats;
//M_InputSpecs MouseManager::EventTracker;
int MouseManager::CurrentMouseState;
double MouseManager::ScrollX;
double MouseManager::ScrollY;
double MouseManager::ScrollPosition;
int MouseManager::ScrollTally;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

MouseManager::MouseManager()
{
	this-> xPos = 0;
	this-> yPos = 0;
	this-> MouseState = GUI_MOUSE_NULL; // 0 = click, 1 = pressed, 2 = nothing
	this-> TotalClicks = 0;
	this-> RightClicks = 0;
	this-> LeftClicks = 0;
	this-> TotalPresses = 0;
	this-> RightPresses = 0;
	this-> LeftPresses = 0;
	this-> LastRightPressTime = 0.0;
	this-> LastLeftPressTime = 0.0;

	this->DoubleInit = false;
	this->TimerReady = false;
	this->SingleClick = true;
	this->PressState = false;
	this->RightStartTime = 0.0;
	this->LeftStartTime = 0.0;
	this->MiddleStartTime = 0.0;

	this-> ScrollTally = 0;
	this-> ScrollPosition = 0;
	this-> ScrollX = 0.0;
	this-> ScrollY = 0.0;
}

void MouseManager::MouseInit(GLFWwindow* window)
{
	this->window = window;
}

float MouseManager::TimeStamp()
{
	float Time = glfwGetTime();
	return Time;
}

//Check if clicked, pressed, nothing, moving
void MouseManager::MouseInput()
{
	float StartTime = TimeStamp();
}


//ouseStats MouseManager::GetMouseState(GLFWwindow* window, float Time, float ClickLength, float PressLength)
//
//	GetMousePosition(window);
//
//	float RightPressTime = Stats.LastLeftPressTime;
//	float LeftPressTime = Stats.LastLeftPressTime;
//	float RightStartTime = EventTracker.RightStartTime;
//	float LeftStartTime = EventTracker.LeftStartTime;
//	float SingleClick = EventTracker.SingleClick;
//	float SinglePress = EventTracker.SinglePress;
//	float TimerReady  = EventTracker.TimerReady;
//	int State;
//
//	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
//	{
//		TimerReady = true;
//		Stats.MouseState = GUI_MOUSE_NULL;
//	}
//
//		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
//		{
//			if (TimerReady == true)
//			{
//				LeftStartTime = TimeStamp();
//				TimerReady = false;
//				SinglePress = true;
//				SingleClick = true;
//			}
//
//			float LeftClickTime = LeftStartTime + PressLength;
//
//
//			if (Time < LeftClickTime)
//			{
//				Stats.MouseState = GUI_MOUSE_NULL;
//				if (SingleClick == true)
//				{
//					Stats.MouseState = GUI_MOUSELEFT_CLICKED;
//					cout << "SinglePress" << endl;
//					SingleClick = false;
//				}
//				Stats.MouseState = GUI_MOUSE_NULL;
//			}
//			if (Time > LeftClickTime)
//			{
//				//Left-Pressed-State
//				Stats.MouseState = GUI_MOUSELEFT_PRESSED;
//			}
//		}
//
//		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
//		{
//			//Initiate Mouse Buttons 
//			if (TimerReady == true)
//			{
//				RightStartTime = TimeStamp();
//				SingleClick = true;
//				TimerReady = false;
//			}
//
//			//Determines wether or not the current action is a press or a click based off of input time
//			float RightClickTime = RightStartTime + PressLength;
//			if (Time < RightClickTime)
//			{
//				if (SingleClick == true)
//				{
//					//Right-Clicked-State
//					Stats.MouseState = GUI_MOUSERIGHT_CLICKED;
//					SingleClick = false;
//				}
//			}
//			if (Time > RightClickTime)
//			{
//				//Right-Pressed-State
//				Stats.MouseState = GUI_MOUSERIGHT_PRESSED;
//			}
//		}
//
//
//
//	MouseManager::CurrentMouseState = Stats.MouseState;
//	Stats.LastLeftPressTime = LeftPressTime;
//	Stats.LastRightPressTime = RightPressTime;
//	EventTracker.TimerReady  = TimerReady;
//   EventTracker.SingleClick = SingleClick;
//	EventTracker.SinglePress = SinglePress;
//	EventTracker.LeftStartTime  = LeftStartTime;
//	EventTracker.RightStartTime = RightStartTime;
//
//	return Stats;
//  


int MouseManager::GetMouseState(GLFWwindow* window, float Time, float DoubleClickLength, float PressLength)
{

	GetMousePosition(window);

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_RELEASE)
	{
		StartTimer = true;
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) != GLFW_PRESS && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) != GLFW_PRESS)
	{
		
		//Press
		if (Time > LeftClickTime && StartTimer != true)
		{
			cout << "LeftPressed" << endl;
			LeftMultiTrack = 0;
			CurrentMouseState = GUI_MOUSELEFT_PRESSED;
			return GUI_MOUSELEFT_PRESSED;
		}

		//Click
		if (StartTimer == true && Time - LeftStartTime > DoubleClickLength)
		{
			LeftStartTime = TimeStamp();
			LeftClickTime = LeftStartTime + PressLength;
			if (PressLength != 0.0) // Click is an impossible state when PressState is Instant
			{
				StartTimer = false;
				cout << "Left Clicked" << endl;
				LeftMultiTrack = 1;
				CurrentMouseState = GUI_MOUSELEFT_CLICKED;
				return CurrentMouseState;// GUI_MOUSELEFT_CLICKED;
			}
			StartTimer = false;
		}

		// Double, Triple...Clicks
		if (StartTimer == true && Time - LeftStartTime < DoubleClickLength)
		{
			StartTimer = false;
			LeftStartTime = TimeStamp();
			LeftClickTime = LeftStartTime + PressLength;
			LeftMultiTrack++;
			if (LeftMultiTrack < 6)
			{
				cout << LeftMultiTrack << " Left Clicks" << endl;
				CurrentMouseState = 1 + LeftMultiTrack;
				return 1 + LeftMultiTrack;
			}
		}
		StartTimer = false;

	CurrentMouseState = GUI_MOUSE_NULL;
	return GUI_MOUSE_NULL;
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) != GLFW_PRESS && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) != GLFW_PRESS)
	{
		//if (StartTimer == true)
		//{
		//	RightStartTime = TimeStamp();
		//	RightClickTime = RightStartTime + PressLength;
		//	if (PressLength != 0.0)
		//	{
		//		StartTimer = false;
		//		cout << "RightClicked" << endl;
		//		return GUI_MOUSERIGHT_CLICKED;
		//	}
		//	StartTimer = false;
		//}
		//
		//if (Time > RightClickTime)
		//{
		//	cout << "RightPressed" << endl;
		//	return GUI_MOUSERIGHT_PRESSED;
		//}
		///////////////////////////////////////////////////////////
		if (Time > RightClickTime && StartTimer != true)
		{
			cout << "RightPressed" << endl;
			RightMultiTrack = 0;
			CurrentMouseState = GUI_MOUSERIGHT_PRESSED;
			return GUI_MOUSERIGHT_PRESSED;
		}

		if (StartTimer == true && Time - RightStartTime > DoubleClickLength)
		{
			RightStartTime = TimeStamp();
			RightClickTime = RightStartTime + PressLength;
			if (PressLength != 0.0) // Click is an impoosible state when PressState is Instant
			{
				StartTimer = false;
				cout << "Right Clicked" << endl;
				RightMultiTrack = 1;
				CurrentMouseState = GUI_MOUSERIGHT_CLICKED;
				return GUI_MOUSERIGHT_CLICKED;
			}
			StartTimer = false;
		}

		if (StartTimer == true && Time - RightStartTime < DoubleClickLength)
		{
			StartTimer = false;
			RightStartTime = TimeStamp();
			RightClickTime = RightStartTime + PressLength;
			RightMultiTrack++;
			if (RightMultiTrack < 6)
			{
				cout << RightMultiTrack << " Right Clicks" << endl;
				CurrentMouseState = 7 + RightMultiTrack;
				return 7 + RightMultiTrack;
			}
		}

	StartTimer = false;
	CurrentMouseState = GUI_MOUSE_NULL;
	return GUI_MOUSE_NULL;
	}


	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) != GLFW_PRESS && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) != GLFW_PRESS)
	{

		if (Time > MiddleClickTime && StartTimer != true)
		{
			cout << "MiddlePressed" << endl;
			MiddleMultiTrack = 0;
			CurrentMouseState = GUI_MOUSEMIDDLE_PRESSED;
			return GUI_MOUSEMIDDLE_PRESSED;
		}

		if (StartTimer == true && Time - MiddleStartTime > DoubleClickLength)
		{
			MiddleStartTime = TimeStamp();
			MiddleClickTime = MiddleStartTime + PressLength;
			if (PressLength != 0.0) // Click is an impoosible state when PressState is Instant
			{
				StartTimer = false;
				cout << "Middle Clicked" << endl;
				MiddleMultiTrack = 1;
				CurrentMouseState = GUI_MOUSEMIDDLE_CLICKED;
				return GUI_MOUSEMIDDLE_CLICKED;
			}
			StartTimer = false;
		}

		if (StartTimer == true && Time - MiddleStartTime < DoubleClickLength)
		{
			StartTimer = false;
			MiddleStartTime = TimeStamp();
			MiddleClickTime = MiddleStartTime + PressLength;
			MiddleMultiTrack++;
			if (MiddleMultiTrack < 6)
			{
				cout <<  MiddleMultiTrack << " Middle Clicks" << endl;
				CurrentMouseState = 13 + MiddleMultiTrack;
				return 13 + MiddleMultiTrack;
			}
		}

		StartTimer = false;
		
	}
	CurrentMouseState = GUI_MOUSE_NULL;
	return GUI_MOUSE_NULL;
}



void MouseManager::GetMousePosition(GLFWwindow* window)
{
	double MouseX, MouseY;
	glfwGetCursorPos(window, &MouseX, &MouseY);




	float SomeRatiox = 2.0 / 1200.0;
	float SomeRatioy = 2.0 / 600.0;
	float Differencex = SomeRatiox * MouseX;
	float Differencey = SomeRatioy * MouseY;
	this->xPos = Differencex - 1.0;
	this->yPos = (Differencey - 1.0) * -1.0;
}



void MouseManager::MousePosition()
{
//	GetMousePosition();
//	Stats.xPos = MouseX;
//	Stats.yPos = MouseY;
}

//changes and returns toggle
bool MouseManager::Toggle(bool& Toggle)
{
	//if (Controller == true)
	//{ cout << "ToggleChanged" << endl;
	//
		if (Toggle == false)
		{
			Toggle = true;
			cout << "ToggleState: " << Toggle << endl;
			return Toggle;
		}
		if (Toggle == true)
		{
			Toggle = false;
			cout << "ToggleState: " << Toggle << endl;
			return Toggle;
		}
	
	//}
	//Controller = false;
	//return Toggle;
}

//false

void MouseManager::ScrollInput(GLFWwindow* window)
{
	glfwSetScrollCallback(window, scroll_callback);
}




//ScrollX = xoffset;
//ScrollY = yoffset;
//if (ScrollY == 1)
//{
//	Tally += 1;
//	cout << "Tally: " << Tally << endl;
//	ScrollPosition = ScrollY + Tally;
//	cout << ScrollPosition << endl;
//}
//if (ScrollY == -1)
//{
//	//Tally = 0;
//	//ScrollPosition = Tally;
//}
//
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	MouseManager::ScrollX = xoffset;
	MouseManager::ScrollY = yoffset;

	if (yoffset == 1)
	{
		MouseManager::ScrollTally++;
	}

	if (yoffset == -1)
	{
		MouseManager::ScrollTally--;
	}
	//provide mouse scroll reset

	//this should tell you exactly where the current mouse scroll is 
	MouseManager::ScrollPosition = MouseManager::ScrollTally;
}