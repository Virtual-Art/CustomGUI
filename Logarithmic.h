#ifndef LOGARITHMIC
#define LOGARITHMIC

#include <iostream>
#include <math.h>
#include "Action.h"

using namespace std;

class Logarithmic : public SubAction
{
public:

	Logarithmic();

	double operator ()(double Control)
	{
		if (ActionState == PLAY)
		{
			//Include Pause/Play procedures into control
			int ModifiedControl = ((Control - TotalTimePaused) - StartTime);
			LastResult = log((ModifiedControl - InputOffset) * Speed) + OutputOffset;
		}
		if (ActionState == STOPPED)
		{
			return OutputOffset;
		}

		return LastResult;
	};

};


#endif