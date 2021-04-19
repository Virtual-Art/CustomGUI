#include "Log.h"


void Log::LogInt(string Description, int Int)
{
	cout << Description << ": " << Int << endl;
}

void Log::LogChar(string Description, char Char)
{
	cout << Description << ": " << Char << endl;
}

void Log::LogFloat(string Description, float Float)
{
	cout << Description << ": " << Float << endl;
}

void Log::LogDouble(string Description, const double& Double)
{

	cout << Description << ": " << Double << endl;
}

void Log::LogBool(string Description, bool Bool)
{
	if (Bool == true)
	{
		cout << Description << ": " << "true" << endl;
	}
	else 
	{
		cout << Description << ": " << "false" << endl;
	}
}

void Log::LogVec2(string Description, glm::vec2 Vec2)
{
	cout << Description << ": " << Vec2[0] << " | " << Vec2[1] << endl;
}

void Log::LogVec3(string Description, glm::vec3 Vec3)
{
	cout << Description << ": " << Vec3[0] << " | " << Vec3[1] << " | " << Vec3[2] << endl;
}

void Log::LogVec4(string Description, glm::vec4 Vec4)
{
	cout << Description << ": " << Vec4[0] << " | " << Vec4[1] << " | " << Vec4[2] << " | " << Vec4[3] << endl;
}

void Log::LogString(string Description)
{
	cout << Description <<  endl;
}




