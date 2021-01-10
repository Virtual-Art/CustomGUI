#ifndef SHADER
#define SHADER

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "RawTexture.h"


using namespace std;

class ShaderProgram
{
public:

private:


public:
	unsigned int ID;
	
	ShaderProgram()
	{

	}

	ShaderProgram(const char* vertexPath, const char* fragmentPath)
	{
		// 1. retrieve the vertex/fragment source code from filePath
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// ensure ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			// read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			// convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();
		// 2. compile shaders
		unsigned int vertex, fragment;
		// vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");
		// fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");
		// shader Program
		this->ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");
		// delete the shaders as they're linked into our program now and no longer necessary
		glDeleteShader(vertex);
		glDeleteShader(fragment);

		GetAllUniformLocations();
		LoadSample1();
		LoadSample2();
	}

	void SetShaderProgram(const char* vertexPath, const char* fragmentPath)
	{
		// 1. retrieve the vertex/fragment source code from filePath
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// ensure ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			// read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			// convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();
		// 2. compile shaders
		unsigned int vertex, fragment;
		// vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");
		// fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");
		// shader Program
		this->ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");
		// delete the shaders as they're linked into our program now and no longer necessary
		glDeleteShader(vertex);
		glDeleteShader(fragment);

		GetAllUniformLocations();
		LoadSample1();
		LoadSample2();
	}


	void LoadVector3(const char* UniformName, float Uniformx, float Uniformy, float Uniformz)
	{
		glUniform3f(GetUniformLocationInt(UniformName), Uniformx, Uniformy, Uniformz); //change to vector at some point
	}

	int GetUniformLocationInt(const char* UniformName)
	{
		return glGetUniformLocation(ID, UniformName);
	}

	//this is when you make it
	void GetMatrixUniformLocation(const char* UniformName)
	{
		this->Loc_TransformationMatrix = glGetUniformLocation(ID, "TransformationMatrix");
	}

	//Loads all int Locations
	void GetAllUniformLocations()
	{
		this->Loc_TransformationMatrix = glGetUniformLocation(ID, "TransformationMatrix");
		this->Loc_Color = glGetUniformLocation(ID, "Color");
		this->Loc_FontAtlas = glGetUniformLocation(ID, "FontAtlas");
		this->Loc_ActiveTextures = glGetUniformLocation(ID, "ActiveTextures");
	}


	// activate the shader
	// ------------------------------------------------------------------------
	void StartProgram()
	{
		glUseProgram(ID);
	}
	void StopProgram()
	{
		glUseProgram(0);
	}

	//Load TransformationMatrix to Vertex Shader  Function Type (1)
	void LoadTransformationMatrix(const GLfloat* Matrix)
	{
		LoadMatrix(this->Loc_TransformationMatrix, Matrix);
	}

	//Function Type (1)
	void Load3F(glm::vec3 Float)
	{ 
		glUniform3f(this->Loc_Color, Float[0], Float[1], Float[2]);
	}

	//Load the Sample2D to Fragment Shader
	void LoadTexture(RawTexture RawTexture)                   // _
	{                                                                 // | <- see if it works with RawTexture.GetTextureSlot
		glUniform1i(glGetUniformLocation(this->ID, RawTexture.GetShaderName()), RawTexture.GetTextureSlot());
	} 

	void LoadInt(const GLint* INT)
	{
		glUniform1iv(Loc_ActiveTextures, 16, INT);
	}

	void LoadSample0()
	{
		glUniform1i(glGetUniformLocation(ID, "ActiveTextures[0]"), 0);
	}
	void LoadSample1()
	{
		glUniform1i(glGetUniformLocation(ID, "ActiveTextures[1]"), 1);
		
	}
	void LoadSample2()
	{
		glUniform1i(glGetUniformLocation(ID, "ActiveTextures[2]"), 2);

	}
	void LoadSample3()
	{
		glUniform1i(glGetUniformLocation(ID, "ActiveTextures[3]"), 3);

	}

	void LoadAllSamples()
	{
		for (int i = 0; i < 8; i++)
		{
			int Result = i;
			string Bracket = "]";
			stringstream ss;
			ss << Result;
			string Number = ss.str();
			string String = "ActiveTextures[" + Number + Bracket;
			glUniform1i(glGetUniformLocation(ID, String.c_str()), i);
		}
	}


	int Loc_TransformationMatrix;
	int Loc_Color;
	int Loc_FontAtlas;
	int Loc_ActiveTextures;



	void SetMat4fv(const char* Name, glm::mat4 Mat4);
	void SetMat3fv(const char* Name, glm::mat3 Mat3);
	void SetVec4f(const char* Name, glm::vec4 Vec4);
	void SetVec3f(const char* Name, glm::vec3 Vec3);
	void SetVec2f(const char* Name, glm::vec2 Vec2);
	void Setf(const char* Name, float Float);






protected:



	//Loads a float into the shader program
	void LoadFloat(int Location, GLfloat Value)
	{
		glUniform1f(Location, Value);
	}

	void LoadSample2D(int Location, int Slot)
	{
		glUniform1i(Location, Slot);
	}



	void LoadVector2(int Location, GLfloat x, GLfloat y)
	{
		glUniform2f(Location, x, y); //change to vector at some point
	}

	void LoadMatrix(int Location, const GLfloat* valueptr)
	{
		glUniformMatrix4fv(Location, 1, GL_FALSE, valueptr);
	}


private:


	//int Location_TransformationMatrix;
	//int Location_ColorCube;


	//retrieves all uniform locations 

	// utility function for checking shader compilation/linking errors.
	// ------------------------------------------------------------------------
	void checkCompileErrors(unsigned int shader, std::string type)
	{
		int success;
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
			else
			{
				cout << "Compile Success" << endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
			else
			{
				cout << "ProgramLink Success" << endl;
			}
		}
	}

};

#endif