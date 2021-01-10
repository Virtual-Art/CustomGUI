#ifndef	LINEAR
#define LINEAR

#include <iostream>
#include <math.h>
#include "Action.h"

using namespace std;

//y = mx + b
class Linear : public SubAction
{
   public:

	 int Speed;

	 Linear();


	 double operator()(double Control)
	 {
		 return Control + 10;
	 }


};


#endif