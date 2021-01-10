#ifndef	OSCILLATION
#define OSCILLATION

#include <iostream>
#include <math.h>
#include "Action.h"

using namespace std;

class Oscillation : public SubAction
{

public:


	Oscillation();

	bool Clockwise;
	int OscillationType;

	 double operator ()(double Control)
	 {
		 if (ActionState == PLAY)
		 {
			 LastResult = Speed * sin(((Control - TotalTimePaused) - StartTime) - InputOffset) + OutputOffset;
		 }
		 if (ActionState == STOPPED)
		 {
			 return OutputOffset;
		 }

		 return LastResult;
	 };


};


#endif