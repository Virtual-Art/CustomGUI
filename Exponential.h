#ifndef EXPONENTIAL
#define EXPONENTIAL

#include <iostream>
#include <math.h>
#include "Action.h"

using namespace std;

class Exponential : public SubAction
{
	public:
	unsigned int Pow;
	double Size;

	Exponential();

	double operator ()(double Control)
	{
		if (ActionState == PLAY)
		{
			//Include Pause/Play procedures into control
			int ModifiedControl = ((Control - TotalTimePaused) - StartTime);
			LastResult = pow(((ModifiedControl - InputOffset) * Speed), Pow) + OutputOffset;
		}
		if (ActionState == STOPPED)
		{
			return OutputOffset;
		}

		return LastResult;
	};

};


#endif 

