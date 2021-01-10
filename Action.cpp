#include "Action.h"

void SubAction::Play()
{
	//Play From Stopped
	if (ActionState == STOPPED)
	{
		ActionState = PLAY;
		SetStartTime();
	}
	//Play From Paused
	else if (ActionState == PAUSED)
	{
		ActionState = PLAY;
		SetPauseTime();
	}
}

void SubAction::Pause()
{
	if (ActionState == PLAY)
	{
		//Pause
		ActionState = PAUSED;
		PausedTime = glfwGetTime();

	}
	else if (ActionState == PAUSED)
	{
		ActionState = PLAY;
		SetPauseTime();
	}
	else if (ActionState == STOPPED)
	{
		ActionState = PAUSED;
		PausedTime = glfwGetTime();
	}

	//don't do anything for pausedstate it's already at that state
}

void SubAction::Stop()
{
	if (ActionState == PLAY)
	{
		ActionState = STOPPED;
		PausedTime = 0.00;
		TotalTimePaused = 0.00;
	}
	else if (ActionState == PAUSED)
	{
		ActionState = STOPPED;
		PausedTime = 0.00;
		TotalTimePaused = 0.00;
	}
}