#include "ShaderProgram.h"


void ShaderProgram::SetVec4f(const char* Name, glm::vec4 Vec4)
{
	glUniform4f(glGetUniformLocation(this->ID, Name), Vec4[0], Vec4[1], Vec4[2], Vec4[3]);
}

void ShaderProgram::SetVec3f(const char* Name, glm::vec3 Vec3)
{
	glUniform3f(glGetUniformLocation(this->ID, Name), Vec3[0], Vec3[1], Vec3[2]);
}

void ShaderProgram::SetVec2f(const char* Name, glm::vec2 Vec2)
{
	glUniform2f(glGetUniformLocation(this->ID, Name), Vec2[0], Vec2[1]);
}

void ShaderProgram::Setf(const char* Name, float Float)
{
	glUniform1f(glGetUniformLocation(this->ID, Name),Float);
}


void ShaderProgram::SetMat4fv(const char* Name, glm::mat4 Mat4)
{
	glUniformMatrix4fv(glGetUniformLocation(this->ID, Name), 1, GL_FALSE, glm::value_ptr(Mat4));
}

void ShaderProgram::SetMat3fv(const char* Name, glm::mat3 Mat3)
{
	glUniformMatrix3fv(glGetUniformLocation(this->ID, Name), 1, GL_FALSE, glm::value_ptr(Mat3));
}