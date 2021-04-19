#ifndef LOG
#define LOG

#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string.h>

using namespace std;

namespace Log
{
	void LogInt(string Description, int Int);
	void LogChar(string Description, char Char);
	void LogFloat(string Description, float Float);
	void LogDouble(string Description, const double& Double);
	void LogBool(string Description, bool Bool);
	void LogVec2(string Description, glm::vec2);
	void LogVec3(string Description, glm::vec3);
	void LogVec4(string Description, glm::vec4);
	void LogString(string Description);

}
#endif 
