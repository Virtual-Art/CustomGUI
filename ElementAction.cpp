#include "ElementAction.h"



ElementAction::ElementAction()
{
	//Create the pointer that points to the attributes
	SubActionSet = new SubAction**[4];
	Result = new double* [4];
	CurrentIDCount = 0;

	for (int i = 0; i < 4; i++)
	{
		//Create the pointers (our data in this case) that the Attribute pointers will point too 
		SubActionSet[i] = new SubAction*[4];
		Result[i] = new double[4];
	}

	for (int r = 0; r < 20; r++)
	{
		ElementIDs[r] = -1;
	}

	//please note, this matrix just holds a bunch of pointers.
	//to our data type. there is no action data type hardcoded in the matrix.
}



ElementAction::ElementAction(SubAction*& Preset)
{
	//Create the pointer that points to the attributes
	SubActionSet = new SubAction **[4];
	CurrentIDCount = 0;

	for (int i = 0; i < 4; i++)
	{
		//Create the pointers (our data in this case) that the Attribute pointers will point too 
		SubActionSet[i] = new SubAction * [4];
	}

	//Set All pointers to the same subaction
	if (Preset != nullptr)
	{
		for (int k = 0; k < 4; k++)
		{
			for (int j = 0; j < 4; j++)
			{
				SubActionSet[k][j] = Preset;
			}
		}
	}
	else
	{
		cout << "Could not properly initialize Action List" << endl;
	}

	for (int r = 0; r < 20; r++)
	{
		ElementIDs[r] = -1;
	}

	//please note, this matrix just holds a bunch of pointers.
	//to our data type. there is no action data type hardcoded in the matrix.
}

ElementAction::~ElementAction()
{
	for (int i = 0; i < 4; i++)
	{
		//Delete the data that the 4 Attributes point to
		delete[] Result[i];
		delete[] SubActionSet[i];
	}

	//then delete the pointer that points to the 4 attributes
	delete[] Result;
	delete[] SubActionSet;
}




SubAction**& ElementAction::operator[] (int Position)
{
	if (Position > 16)
	{
		cout << "Action Position out of bounds" << endl;
		return SubActionSet[0];
	}
	else
	{
		return SubActionSet[Position];
	
	}
}


void ElementAction::Play()
{
	SubAction* CurrentSubAction = nullptr;

	//Iterate through and calculate all action
	for (int k = 0; k < 4; k++)
	{ for (int j = 0; j < 4; j++)
	 {
		CurrentSubAction = SubActionSet[k][j];
		if (CurrentSubAction) //Null Check
		{
			CurrentSubAction->Play();
		}
	 }
	}
}