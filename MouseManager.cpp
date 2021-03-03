#include "MouseManager.h"

//In this class we will be managing mouse input including left, right. scroll, position

//our static variable

//MouseStats MouseManager::Stats;
//M_InputSpecs MouseManager::EventTracker;
double MouseManager::xPos = 0.0;
double MouseManager::yPos = 0.0;
int MouseManager::CurrentMouseState = GUI_MOUSE_NULL; // 0 = click, 1 = pressed, 2 = nothing

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void MouseManager::MouseInit(GLFWwindow* window)
{
	window = window;
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
			if (LeftMultiTrack < 3)
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
			if (RightMultiTrack < 7)
			{
				cout << RightMultiTrack << " Right Clicks" << endl;
				CurrentMouseState = 4 + RightMultiTrack;
				return 4 + RightMultiTrack;
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
			if (MiddleMultiTrack < 10)
			{
				cout <<  MiddleMultiTrack << " Middle Clicks" << endl;
				CurrentMouseState = 7 + MiddleMultiTrack;
				return 7 + MiddleMultiTrack;
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

	//Log::LogVec2("MousePostion", { MouseX, MouseY });
	double SomeRatiox = 2.0 / 1200.0;
	double SomeRatioy = 2.0 / 600.0;
	double Differencex = SomeRatiox * MouseX;
	double Differencey = SomeRatioy * MouseY;
	xPos = Differencex - 1.0;
	yPos = (Differencey - 1.0) * -1.0;


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


double MouseManager::PrintScrollWheel()
{
	cout << ScrollPosition << endl;
	return ScrollPosition;
}

void MouseManager::ScrollTopCap(unsigned int cap)
{
	if (ScrollPosition >= cap)
	{
		ScrollTally = cap;
		ScrollPosition = cap;
	}

}

void MouseManager::ScrollBottomCap(signed int cap)
{
	if (ScrollPosition <= cap)
	{
		ScrollTally = cap;
		ScrollPosition = cap;
	}
}

void MouseManager::ScrollAutoSet(int cap)
{
	ScrollTally = cap;
	ScrollPosition = cap;
}

void MouseManager::ScrollReset()
{
	ScrollTally = 0;
	ScrollPosition = 0;
}
glm::vec2  MouseManager::MousePositionGet()
{
	return {xPos, yPos};
}
