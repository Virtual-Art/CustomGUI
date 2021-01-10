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

class Keyboard
{
   public:


	   void PlayFunction();
    

	   //Set
       //Keyboard::KeyBoardButton[ARROW_UP][DEFAULT][PRESSED] = ShapePositionUp;
       
       //Call
       //KeyBoard::KeyButton[ARROW_UP][ALT_SHIFT][PRESSED]();
	   static KeyFunction** KeyButton;


	   static void CreateKeyFuncContainer()
	   {
		   //EX: 'h' : 'Alt, shift" : "KEY_CLICKED"
		   int AmountofKeys = 227; 
		   int AmountofControllers = 9;

		   //Create Key Container
		   KeyButton = new KeyFunction*[AmountofKeys];
		   for (int CurrentKey = 0; CurrentKey < AmountofKeys; CurrentKey++)
		   {
			   //Every Key gets 9 Controllers
			   KeyButton[CurrentKey] = new KeyFunction[9];
		   }

		   for (int i = 0; i < AmountofKeys;i++)
		   {
			   for (int j = 0; j < 9; j++)
			   {
				   KeyButton[i][j] = Empty;
			   }
		   }
		   //Set: KeyButton[ARROW_UP_CLICKED][ALT_SHIFT] = Non_Member_Function;
		   //Call: KeyButton[ARROW_UP_CLICKED][ALT_SHIFT]();
	   }

	   Container<Key> MakeKeyContainer(int ContainerSize)
	   {
		   Container<Key> ArrElements(ContainerSize);
		   return ArrElements;
	   }

	   Container<Key> KeyContainer;

	   KeyResult ManagerResult;
	   // Key A
	   bool KeyAStartTimer;
	   float KeyAClickTime;
	   float KeyAMultiTrack;
	   float KeyAStartTime;
	   float KeyADoubleClickLength;
	   // Key D
	   bool  KeyDStartTimer;
	   float KeyDClickTime;
	   float KeyDMultiTrack;
	   float KeyDStartTime;
	   float KeyDDoubleClickLength;
	   // Key W
	   bool  KeyWStartTimer;
	   float KeyWClickTime;
	   float KeyWMultiTrack;
	   float KeyWStartTime;
	   float KeyWDoubleClickLength;
	   // Key S
	   bool  KeySStartTimer;
	   float KeySClickTime;
	   float KeySMultiTrack;
	   float KeySStartTime;
	   float KeySDoubleClickLength;

	   Keyboard();

	   void PlayButton();
	   void CurrentLastAscii();

	   float TimeStamp();

	   KeyResult& GetKeyBoardState(GLFWwindow* window, float Time, float ClickLength, float PressLength);
	   bool ProcessDoubleKeys(GLFWwindow* window, Key& First, Key& Second, float Time);

	   void PrintKey(int KeyID);
	   void PrintKeySheet();

	   int KeyToAscii();

	   static void Empty() {};
};



#endif 
