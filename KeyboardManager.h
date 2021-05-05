#ifndef KEYBOARD
#define KEYBOARD

#include <iostream>
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Container.h"
#include "Define.h"
//#include "PageCreator.h"

using namespace std;

typedef void(*KeyFunction)();

//struct KeyBoardButton
//{
//	//8 Function states
//
//	CreatorFunctionPointer** FunctionState;
//
//	KeyBoardButton()
//	{
//		//Create 8 State Functions to point to
//		//User needs to assign the functions
//		FunctionState = new CreatorFunctionPointer*[9];
//	}
//
//	//void PlayFunction(KeyResult KeyResult)
//	//{
//	//	int KeysPressed = KeyResult.Ctrl + KeyResult.Shift + KeyResult.Alt;
//	//	int KeyWeight = KeyResult.Ctrl;
//	//	KeyWeight += KeyResult.Shift + 1;
//	//	KeyWeight += KeyResult.Alt + 2;
//	//
//	//	if (KeyResult.Caps != 0)
//	//	{
//	//		FunctionState[9];
//	//		return;
//	//	}
//	//
//	//	//if (KeyResult.Tab != 0)
//	//	//{
//	//	//	FunctionState[8];
//	//	//  return;
//	//	//}
//	//
//	//	//Default
//	//	if (KeysPressed <= 1)
//	//	{
//	//		FunctionState[KeyWeight];
//	//		return;
//	//	}
//	//
//	//	if (KeysPressed >= 2 )
//	//	{
//	//		FunctionState[KeyWeight + 1];
//	//		return;
//	//	}
//	//}
//};

struct Key
{
	Key()
	{
		this->KeyType = 0;
		this->StartTimer = false;
		this->ClickTime = 0.0;
		this->MultiTrack = 0.0;
		this->StartTime = 0.0;
		this->DoubleClickLength = 0.0;
	}

	int KeyType;
	bool  StartTimer;
	float ClickTime;
	float MultiTrack;
	float StartTime;
	float DoubleClickLength;
};

struct KeyResult
{
	bool Ctrl = false;
	bool Shift = false;
	bool Alt = false;
	bool Caps = false;
	int Key1 = 0;
	int Key2 = 0;
	int CurrentAscii = -1;
	int LastAscii = -1;
};

namespace Keyboard
{

	void PlayFunction();
	void Empty();

	//Set
    //Keyboard::KeyBoardButton[ARROW_UP][DEFAULT][PRESSED] = ShapePositionUp;
    
    //Call
    //KeyBoard::KeyButton[ARROW_UP][ALT_SHIFT][PRESSED]();
	static KeyFunction** KeyButton;
	KeyFunction** GetKeyButton();
	KeyResult& GetState();

	void CreateKeyFuncContainer();
	Container<Key> MakeKeyContainer(int ContainerSize);

	static Container<Key> KeyContainer(MakeKeyContainer(144));

	static KeyResult KeyBoard_State; //Most Used Vairable
	static string CurrentText;

	const string& GetText();
	void ResetText();
	void SetText(string string);
	void TextKeepTrack();


	// Key A
	static bool KeyAStartTimer;
	static float KeyAClickTime;
	static float KeyAMultiTrack;
	static float KeyAStartTime;
	static float KeyADoubleClickLength;
	// Key D
	static bool  KeyDStartTimer;
	static float KeyDClickTime;
	static float KeyDMultiTrack;
	static float KeyDStartTime;
	static float KeyDDoubleClickLength;
	// Key W
	static bool  KeyWStartTimer;
	static float KeyWClickTime;
	static float KeyWMultiTrack;
	static float KeyWStartTime;
	static float KeyWDoubleClickLength;
	// Key S
	static bool  KeySStartTimer;
	static float KeySClickTime;
	static float KeySMultiTrack;
	static float KeySStartTime;
	static float KeySDoubleClickLength;

	void Prepare();

	void CurrentLastAscii();

	float TimeStamp();

	void GetKeyBoardState(GLFWwindow* window, float Time, float ClickLength, float PressLength);
	bool ProcessDoubleKeys(GLFWwindow* window, Key& First, Key& Second, float Time);

	void PrintKey(int KeyID);
	void PrintKeySheet();

	int KeyToAscii();

	
};



#endif 
