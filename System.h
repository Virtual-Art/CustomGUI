#ifndef SYSTEM
#define SYSTEM

#pragma once
#include <iostream>
#include <windows.h>
#include <sys/stat.h>

//#include <afxadv.h>
#include <stdio.h>
#pragma comment(lib, "user32.lib")

using namespace std;

class System
{

public:

	static int Width;
	static int Height;
	static int MouseButtonNumber;
	static int NumberofMonitors;


	    //Constructor
		System()
		{

		}


private:


};


#endif