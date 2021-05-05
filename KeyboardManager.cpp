#include "KeyboardManager.h"


void Keyboard::Prepare()
{
	KeyAStartTimer = false;
	KeyAClickTime = 0.0;
	KeyAMultiTrack = 0.0;
	KeyAStartTime = 0.0;
	KeyADoubleClickLength = 0.0;

	Key Sample;
	Key Sample2;

	//Alt, shift, and control keys and caps locks come first
	for (int i = 340; i < 347; i++)
	{
		Sample.KeyType = i;
		KeyContainer.Add(Sample);
	}

	//Caps lockk
	Sample.KeyType = 280;
	KeyContainer.Add(Sample);
	//Space
	Sample2.KeyType = 32;
	KeyContainer.Add(Sample2);

	for (int k = 44; k < 94; k++)
	{
		if (k != 58 && k != 60 && k != 62 && k != 63 && k != 64  )
		{
			//EX: GLFW_KEY_A
			Sample.KeyType = k;
			KeyContainer.Add(Sample);
		}
	}

	for (int j = 256; j < 340; j++)
	{
		if (j < 270 || j > 280 )
		{
			if (j < 285 || j > 289)
			{
				if (j < 315 || j > 319)
				{
					Sample2.KeyType = j;
					KeyContainer.Add(Sample2);
				}
			}
		}
	}
	cout << "Prepare End" << endl;
	CreateKeyFuncContainer();
}

const string& Keyboard::GetText()
{
	return CurrentText;
}

void Keyboard::ResetText()
{
	CurrentText = "";
}

void Keyboard::SetText(string string)
{
	CurrentText = string;
}

void Keyboard::TextKeepTrack()
{

	//Type Letters
	if (KeyBoard_State.Ctrl != true && KeyBoard_State.CurrentAscii != -1 && KeyBoard_State.Key1 != 0)
	{
		CurrentText += KeyBoard_State.CurrentAscii;
	}

	//Process BackSpace
	if (KeyBoard_State.Ctrl != true && KeyBoard_State.Key1 == GUI_BACKSPACE_CLICKED)
	{
		if (CurrentText.size() > 0)
		{
			CurrentText.erase(CurrentText.size() - 1);
		}
	}
}

void Keyboard::PrintKeySheet()
{
	cout << "---------------------------------Key-Sheet------------------------------------" << endl;
	for (int i = 0; i < KeyContainer.CurrentContainerAmount; i++)
	{
		PrintKey(i);
	}
}

void Keyboard::PrintKey(int Spot)
{
	Key* Buffer = KeyContainer.RetrieveDataP(Spot);
 
	cout << "------------Key-Data--(" << Spot << ")---------------" << endl;
	cout << "KeyID " << Buffer->KeyType << endl;
	cout << "ClickTime "<< Buffer->ClickTime << endl;
	cout << "DoubleClickLength " << Buffer->DoubleClickLength << endl;
	cout << "MultiTrack "<< Buffer->MultiTrack << endl;
	cout << "StartTime " << Buffer->StartTime << endl;

	if (Buffer->StartTimer == true)
	{
		cout << "StartTimer " << "True "  << endl;
	}
	else
	{
		cout << "StartTimer " << "False " << endl;
	}

}

float Keyboard::TimeStamp()
{
	return glfwGetTime();
}

//This function runs it's tasks based on a timer
//so focus on the StartTime boolean 
void Keyboard::GetKeyBoardState(GLFWwindow* window, float Time, float ClickLength, float PressLength)
{

	Key* KEY;
	Key* KEY1;
	Key* KEY2;

	//Alt
	KEY1 = KeyContainer.RetrieveDataP(2);
	KEY2 = KeyContainer.RetrieveDataP(6);
	//KeyBoard_State.Alt = ProcessDoubleKeys(window , *KEY1, *KEY2,  Time);

	//Shift
	KEY1 = KeyContainer.RetrieveDataP(0);
	KEY2 = KeyContainer.RetrieveDataP(4);
	//KeyBoard_State.Shift = ProcessDoubleKeys(window, *KEY1, *KEY2, Time);

	//Ctrl
	KEY1 = KeyContainer.RetrieveDataP(1);
	KEY2 = KeyContainer.RetrieveDataP(5);
	//KeyBoard_State.Ctrl = ProcessDoubleKeys(window, *KEY1, *KEY2, Time);

	KeyBoard_State.Key1 = -1;
	//Go through all the keys
	for (int i = 8; i < 144; i++)
	{
		//Get Active Key Info
		KEY = KeyContainer.RetrieveDataP(i);

		//start the timer if the current k is released
		if (glfwGetKey(window, KEY->KeyType) == GLFW_RELEASE)
		{
			KEY->StartTimer = true;
		}

		//KEY->Type === GLFW_KEY_TYPE (EX: GLFW_KEY_A)
		//if a key is currently pressed, what happens
		if (glfwGetKey(window, KEY->KeyType) == GLFW_PRESS)
		{
			//Press
			if (Time > KEY->ClickTime && KEY->StartTimer != true)
			{
				KEY->MultiTrack = 0;
				KeyBoard_State.Key1 = i * 2 + 1;
			}

			//Click
			if (KEY->StartTimer == true && Time - KEY->StartTime > KEY->DoubleClickLength)
			{
				KEY->StartTime = TimeStamp(); //Log Time when first clicked
				KEY->ClickTime = KEY->StartTime + PressLength; //Establish how many miliseconds is a click (controller by user)
				if (PressLength != 0.0) // Click is an impoosible state when PressState is Instant
				{
					KEY->StartTimer = false; 
					cout << "Key Clicked " << i << endl;
					KEY->MultiTrack = 1;
					KeyBoard_State.Key1 = i * 2;
				}
				KEY->StartTimer = false;
			}

			// Double
			if (KEY->StartTimer == true && Time - KEY->StartTime < KEY->DoubleClickLength)
			{
				cout << "YEAH" << endl;
				KEY->StartTimer = false;
				KEY->StartTime = TimeStamp();
				KEY->ClickTime = KeyAStartTime + PressLength;
				KEY->MultiTrack++;
				if (KEY->MultiTrack < 6)
				{
				//	Result.Key2 = i + KEY->MultiTrack;
				}
			}
			KEY->StartTimer = false;
		}
	}

	CurrentLastAscii();
	PlayFunction();	
}

//Call this after every result
void Keyboard::CurrentLastAscii()
{
	int Ascii = KeyToAscii();

	KeyBoard_State.CurrentAscii = Ascii; //returns -1 if no key pressed
	if (KeyBoard_State.CurrentAscii != -1)
	{
		KeyBoard_State.LastAscii = KeyBoard_State.CurrentAscii;
	}
}


bool Keyboard::ProcessDoubleKeys(GLFWwindow* window, Key& First, Key& Second, float Time)
{

	//We do not want to simulate a click only a press
	float PressLength = 0.0;

	if (glfwGetKey(window, First.KeyType) == GLFW_RELEASE || glfwGetKey(window, Second.KeyType) == GLFW_RELEASE)
	{
		First.StartTimer = true;
		Second = First;
	
	}

	//KEY->Type === GLFW_KEY_TYPE (EX: GLFW_KEY_A)
	if (glfwGetKey(window, First.KeyType) == GLFW_PRESS || glfwGetKey(window, Second.KeyType) == GLFW_PRESS)
	{
		
		if (Time > First.ClickTime && First.StartTimer != true)
		{
			//cout << "Key Pressed "  << endl;
			First.MultiTrack = 0;
			Second = First;
			return true;
		}

		if (First.StartTimer == true && Time - First.StartTime > First.DoubleClickLength)
		{
			First.StartTime = TimeStamp();
			First.ClickTime = First.StartTime + PressLength;
			if (PressLength != 0.0) // Click is an impoosible state when PressState is Instant
			{
				First.StartTimer = false;
				//cout << " FIX! error in keyboard " << endl;
				First.MultiTrack = 1;
				Second = First;
				return false;
			}
			First.StartTimer = false;
		}

		if (First.StartTimer == true && Time - First.StartTime < First.DoubleClickLength)
		{
			First.StartTimer = false;
			First.StartTime = TimeStamp();
			First.ClickTime = First.StartTime + PressLength;
			First.MultiTrack++;
			if (First.MultiTrack < 6)
			{
				//cout << First.MultiTrack << " Key Clicks" << endl;
				Second = First;
				//return 1 + KEY->MultiTrack;
			}
		}
		First.StartTimer = false;

		Second = First;
		return false;
	}

	Second = First;
	return false;
}


int Keyboard::KeyToAscii()
{
	int AsciiCarry = 0;
	int KeyNumber = KeyBoard_State.Key1;

	if (KeyNumber == 16 || KeyNumber == 17)
	{
		return 32;
	}

	//0 - 9
	if (KeyNumber > 25 && KeyNumber < 45)
	{
		AsciiCarry = float((KeyNumber / 2) + 35);

		if (KeyBoard_State.Shift == true || KeyBoard_State.Caps == true)
		{
			
			AsciiCarry = float((KeyNumber / 2) + 1);

			// )
			if (AsciiCarry == 14)
			{
				return 41;
			}

			// !
			if (AsciiCarry == 15)
			{

				cout << "yee " << endl;
				return 33;
			}

			// @
			if (AsciiCarry == 16)
			{
				return 64;
			}

			// #
			if (AsciiCarry == 17)
			{
				return 35;
			}

			// $
			if (AsciiCarry == 18)
			{
				return 36;
			}

			// %
			if (AsciiCarry == 19)
			{
				return 37;
			}

			// ^ 
			if (AsciiCarry == 20)
			{
				return 94;
			}

			// &
			if (AsciiCarry == 21)
			{
				return 38;
			}

			// *
			if (AsciiCarry == 22)
			{
				return 42;
			}

			// (
			if (AsciiCarry == 23)
			{
				return 40;
			}
		}
		return AsciiCarry;
	}

	//KP 0 - 9
	if (KeyNumber >  193 && KeyNumber < 214)
	{
		AsciiCarry = float(KeyNumber / 2) - 49;
		return AsciiCarry;
	}

	//a-z
	if (KeyNumber > 49 && KeyNumber < 101)
	{
		// (a- z) GUI KEYNUMBER conversion to ascii
		AsciiCarry = float(KeyNumber / 2) + 72;

		//(A - Z)
		if (KeyBoard_State.Shift == true)
		{
			AsciiCarry -= 32;
		}
		return AsciiCarry;
	}

	AsciiCarry = float(KeyNumber / 2) + 1;

	// ,
	if (AsciiCarry == 10)
	{

		// <
		if (KeyBoard_State.Shift == true || KeyBoard_State.Caps == true)
		{
			return 60;
		}
		return 44;

	}

	// /
	if (AsciiCarry == 13)
	{
		// ?
		if (KeyBoard_State.Shift == true || KeyBoard_State.Caps == true)
		{
			return 63;
		}

		return 47;
	}

	// - 
	if (AsciiCarry == 11)
	{
		return 45;

	}

	// .
	if (AsciiCarry == 12)
	{
	
		// >
		if (KeyBoard_State.Shift == true || KeyBoard_State.Caps == true)
		{
			return 62;
		}

		return 46;
	}


	// ;
	if (AsciiCarry == 24)
	{
		// :
		if (KeyBoard_State.Shift == true || KeyBoard_State.Caps == true)
		{
			return 58;
		}

	   return 59;
	}

	// =
	if (AsciiCarry == 25)
	{
		// +
		if (KeyBoard_State.Shift == true || KeyBoard_State.Caps == true)
		{
			return 43;
		}

		return 61;
	}

	//[
	if (AsciiCarry == 52)
	{

		// {
		if (KeyBoard_State.Shift == true || KeyBoard_State.Caps == true)
		{
			return 123;
		}

		return 91;
	}

	// \ //
	if (AsciiCarry == 53)
	{

		// |
		if (KeyBoard_State.Shift == true || KeyBoard_State.Caps == true)
		{
			return 124;
		}

		return 92;
	}

	// ]
	if (AsciiCarry == 54)
	{


		// }
		if (KeyBoard_State.Shift == true || KeyBoard_State.Caps == true)
		{
			return 125;
		}

		return 93;
	}


	///////////////KEYPAD////////////////////

	// .
	if (AsciiCarry == 108)
	{
		return 46;
	}

	// /
	if (AsciiCarry == 109)
	{
		return 47;
	}

	// *
	if (AsciiCarry == 110)
	{
		return 42;
	}

	// -
	if (AsciiCarry == 111)
	{
		return 45;
	}

	// +
	if (AsciiCarry == 112)
	{
		return 43;
	}


	return -1;
}


void Keyboard::PlayFunction()
{
	if (KeyBoard_State.Key1 != 0)
	{
		int SpecialKeysPressed = KeyBoard_State.Ctrl + KeyBoard_State.Shift + KeyBoard_State.Alt;

		if (KeyBoard_State.Caps != 0 && KeyButton[KeyBoard_State.Key1][9] != nullptr)
		{
			KeyButton[KeyBoard_State.Key1][9]();
			return;
		}

		//if (KeyResult.Tab != 0)
		//{
		//	FunctionState[8];
		//  return;
		//}
		//Default
		if (SpecialKeysPressed == 0 && KeyButton[KeyBoard_State.Key1][0] != nullptr)
		{
			KeyButton[KeyBoard_State.Key1][0]();
			return;
		}

		if (SpecialKeysPressed == 1)
		{
			if (KeyBoard_State.Alt == true && KeyButton[KeyBoard_State.Key1][3] != nullptr)
			{
				KeyButton[KeyBoard_State.Key1][3]();
				return;
			}

			if (KeyBoard_State.Shift == true && KeyButton[KeyBoard_State.Key1][1] != nullptr)
			{
				KeyButton[KeyBoard_State.Key1][1]();
				return;
			}

			if (KeyBoard_State.Ctrl == true && KeyButton[KeyBoard_State.Key1][2] != nullptr)
			{
				KeyButton[KeyBoard_State.Key1][2]();
				return;
			}
		}

		if (SpecialKeysPressed == 2)
		{
			if (KeyBoard_State.Ctrl == true && KeyBoard_State.Alt == true && KeyButton[KeyBoard_State.Key1][6] != nullptr)
			{
				KeyButton[KeyBoard_State.Key1][6]();
				return;
			}

			if (KeyBoard_State.Ctrl == true && KeyBoard_State.Shift == true && KeyButton[KeyBoard_State.Key1][4] != nullptr)
			{
				KeyButton[KeyBoard_State.Key1][4]();
				return;
			}
			if (KeyBoard_State.Alt == true && KeyBoard_State.Shift == true && KeyButton[KeyBoard_State.Key1][5] != nullptr)
			{
				KeyButton[KeyBoard_State.Key1][5]();
				return;
			}
		}

		if (SpecialKeysPressed == 3)
		{
			KeyButton[KeyBoard_State.Key1][5]();
			return;
		}
	}

}


void Keyboard::Empty()
{

}

KeyFunction** Keyboard::GetKeyButton()
{
	return KeyButton;
}

KeyResult& Keyboard::GetState()
{
	return KeyBoard_State;
}

void Keyboard::CreateKeyFuncContainer()
{
	//EX: 'h' : 'Alt, shift" : "KEY_CLICKED"
	int AmountofKeys = 227;
	int AmountofControllers = 9;

	//Create Key Container
	KeyButton = new KeyFunction * [AmountofKeys];
	for (int CurrentKey = 0; CurrentKey < AmountofKeys; CurrentKey++)
	{
		//Every Key gets 9 Controllers
		KeyButton[CurrentKey] = new KeyFunction[9];
	}

	for (int i = 0; i < AmountofKeys; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			KeyButton[i][j] = Empty;
		}
	}

	cout << "Calling FUNCTION" << endl;
	KeyButton[0][0]();
	//Set: KeyButton[ARROW_UP_CLICKED][ALT_SHIFT] = Non_Member_Function;
	//Call: KeyButton[ARROW_UP_CLICKED][ALT_SHIFT]();
}

Container<Key> Keyboard::MakeKeyContainer(int ContainerSize)
{
	Container<Key> ArrElements(ContainerSize);
	return ArrElements;
}