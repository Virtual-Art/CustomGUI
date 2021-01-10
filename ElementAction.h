#ifndef	ElementACTION
#define ElementACTION

#define POSITION 1
#define SIZE 2
#define ROTATION 3
#define COLOR 4

#include <iostream>
#include "Action.h"
#include "Oscillation.h"
#include "Linear.h"
#include "Exponential.h"
#include "Logarithmic.h"

using namespace std;

// Input =< [4][4]
class ElementAction
{

public:

	// subaction is all Exp, Log, Lin, Cos
	// [ATTRIBUTE][0-3]
	SubAction*** SubActionSet;
	double** Result;
	int CurrentIDCount;
	int ElementIDs[20];
	bool MouseAccess;


	//Have to set it to something
	ElementAction();
	ElementAction(SubAction*& Preset);
	~ElementAction();

	void Play();

	SubAction**& operator[] (int Position);

	//////////////////Task////////////////////

	//Calculate all actions without doubling//

	//////////////////Task////////////////////


};


#endif
