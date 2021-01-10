#ifndef MOUSECLASS
#define MOUSECLASS

#include <iostream>
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

#define GUI_MOUSE_NULL 0

#define GUI_MOUSELEFT_CLICKED 1
#define GUI_MOUSELEFT_PRESSED 2
#define GUI_MOUSELEFT_DOUBLECLICKED 3
#define GUI_MOUSELEFT_TRIPLECLICKED 4
#define GUI_MOUSELEFT_QUADRUPLECLICKED 5
#define GUI_MOUSELEFT_QUITUPLECLICKED 6

#define GUI_MOUSERIGHT_CLICKED 7
#define GUI_MOUSERIGHT_PRESSED 8
#define GUI_MOUSERIGHT_DOUBLECLICKED 9
#define GUI_MOUSERIGHT_TRIPLECLICKED 10
#define GUI_MOUSERIGHT_QUADRUPLECLICKED 11
#define GUI_MOUSERIGHT_QUITUPLECLICKED 12

#define GUI_MOUSEMIDDLE_CLICKED 13
#define GUI_MOUSEMIDDLE_PRESSED 14
#define GUI_MOUSEMIDDLE_DOUBLECLICKED 15
#define GUI_MOUSEMIDDLE_TRIPLECLICKED 16
#define GUI_MOUSEMIDDLE_QUADRUPLECLICKED 17
#define GUI_MOUSEMIDDLE_QUINTUPLECLICKED 18




class MouseManager
{
public:

	double xPos;
	double yPos;
	int MouseState; // 0 = click, 1 = pressed, 2 = nothing
	int TotalClicks;
	int RightClicks;
	int LeftClicks;
	int TotalPresses;
	int RightPresses;
	int LeftPresses;
	float LastRightPressTime;
	float LastLeftPressTime;

	static int ScrollTally;
	static double ScrollPosition;
    static double ScrollX;
    static double ScrollY;

	static int CurrentMouseState;

	static int increment;

	MouseManager();
	void MouseInit(GLFWwindow* window);
	float TimeStamp();
	void MouseInput();

	void GetMousePosition(GLFWwindow* window);

	//MouseStats GetMouseState(GLFWwindow* window, float Time, float ClickLength, float PressLength);

	int GetMouseState(GLFWwindow* window, float Time, float ClickLength, float PressLength);

	bool Toggle(bool& Toggle);

	double MouseX, MouseY;

	GLFWwindow* window;

	void ScrollInput(GLFWwindow* window);

	//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	void MousePosition();

	double PrintScrollWheel()
	{
		cout << ScrollPosition << endl;
		return ScrollPosition;
	}

	void ScrollTopCap(unsigned int cap)
	{
		if (ScrollPosition >= cap)
		{
			ScrollTally = cap;
			ScrollPosition = cap; 
		}

	}

	void ScrollBottomCap(signed int cap)
	{
		if (ScrollPosition <= cap)
		{
			ScrollTally = cap;
			ScrollPosition = cap;
		}
	}

	void ScrollAutoSet(int cap)
	{
		ScrollTally = cap;
		ScrollPosition = cap;
	}

	void ScrollReset()
	{
		ScrollTally = 0;
		ScrollPosition = 0;
	}

private:
	bool TimerReady;
	bool SingleClick;
	bool PressState;
	bool DoubleInit;
	int MiddleMultiTrack;
	int RightMultiTrack;
	int LeftMultiTrack;

	float StartTimer;

	//Start Time
	float RightStartTime;
	float LeftStartTime;
	float MiddleStartTime;

	float RightDoubleStartTime;
	float LeftDoubleStartTime;
	float MiddleDoubleStartTime;

	//Click Time
	float RightClickTime;
	float LeftClickTime;
	float MiddleClickTime;

	float RightDoubleClickTime;
	float LeftDoubleClickTime;
	float MiddleDoubleClickTime;

};

#endif 