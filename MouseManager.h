#ifndef MOUSECLASS
#define MOUSECLASS

#include <iostream>
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Log.h"

using namespace std;

#define GUI_MOUSE_NULL 0

#define GUI_MOUSELEFT_CLICKED 1
#define GUI_MOUSELEFT_PRESSED 2
#define GUI_MOUSELEFT_DOUBLECLICKED 3
#define GUI_MOUSERIGHT_CLICKED 4
#define GUI_MOUSERIGHT_PRESSED 5
#define GUI_MOUSERIGHT_DOUBLECLICKED 6
#define GUI_MOUSEMIDDLE_CLICKED 7
#define GUI_MOUSEMIDDLE_PRESSED 8
#define GUI_MOUSEMIDDLE_DOUBLECLICKED 9


namespace MouseManager
{

	extern double xPos;
	extern double yPos;
	extern int CurrentMouseState;

	static int TotalClicks = 0;
	static int RightClicks = 0;
	static int LeftClicks = 0;
	static int TotalPresses = 0;
	static int RightPresses = 0;
	static int LeftPresses = 0;
	static float LastRightPressTime = 0;
	static float LastLeftPressTime = 0;

	static bool DoubleInit = false;
	static bool TimerReady = false;
	static bool SingleClick = true;
	static bool PressState = false;
	//Start Time
	static float RightStartTime = 0.0;
	static float LeftStartTime = 0.0;
	static float MiddleStartTime = 0.0;

	static int MiddleMultiTrack = 0;
	static int RightMultiTrack = 0;
	static int LeftMultiTrack = 0;

	static float StartTimer;

	static float RightDoubleStartTime;
	static float LeftDoubleStartTime;
	static float MiddleDoubleStartTime;
		   
	//Click Time
	static float RightClickTime;
	static float LeftClickTime;
	static float MiddleClickTime;
		   
	static float RightDoubleClickTime;
	static float LeftDoubleClickTime;
	static float MiddleDoubleClickTime;

	static int ScrollTally = 0;
	static double ScrollPosition = 0.0;
    static double ScrollX = 0.0;
    static double ScrollY = 0.0;

	static int increment;

	void MouseInit(GLFWwindow* window);
	float TimeStamp();
	void MouseInput();

	void GetMousePosition(GLFWwindow* window);

	//MouseStats GetMouseState(GLFWwindow* window, float Time, float ClickLength, float PressLength);

	int GetMouseState(GLFWwindow* window, float Time, float ClickLength, float PressLength);

	bool Toggle(bool& Toggle);

	static double MouseX, MouseY;

	static GLFWwindow* window;

	void ScrollInput(GLFWwindow* window);

	//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	void MousePosition();

	double PrintScrollWheel();

	void ScrollTopCap(unsigned int cap);

	void ScrollBottomCap(signed int cap);

	void ScrollAutoSet(int cap);

	void ScrollReset();

	glm::vec2 MousePositionGet();

}

#endif 