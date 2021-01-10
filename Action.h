#ifndef	SUBACTION
#define SUBACTION

#include <iostream>
#include <math.h>
#include "GLFW/glfw3.h"


using namespace std;

#define PLAY 1
#define PAUSED 2
#define STOPPED 3

class SubAction
{
public:

	//practice with pow action

	//Public
	int ID;
	int    Speed;
	double InputOffset;
	double OutputOffset;
	double ActionDuration;
	double LastCalculation;
	
    //Class use
	int    ActionState;
	double PausedTime; //everytime you pause, you would ad to this number and reset after a stop
	double TotalTimePaused;
	double ControlStart;
	double LastResult;
	double StartTime;
	


	SubAction()
	{
		this->Speed = 2.1;
		this->InputOffset = 0;
		this->OutputOffset = 0.00;
		this->LastResult = 0.0;
		this->ActionState = STOPPED;

		this->PausedTime = 0.00;
		double ControlStart = 0.0;
		double LastResult = 0.0;
		double StartTime = 0.0;
	}

	void Play();
	void Pause();
	void Stop();


	virtual double operator ()(double Control)
	{
		LastResult = Control;
		return LastResult;
	};


	//works just make sure you update paused time
	int SetControl()
	{
		return (glfwGetTime() - PausedTime) - StartTime;
	}
	

private:

	//Calculates the amount of time that was paused
	void SetPauseTime()
	{
		TotalTimePaused += glfwGetTime() - PausedTime;
		cout << TotalTimePaused << endl;
	}

	void SetStartTime()
	{
		StartTime = glfwGetTime();
	}




};


#endif