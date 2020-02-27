#include "Shader.h"

GLuint Shader::getID()
{
	return shaderID;
}

//Constructor
Shader::Shader(const char* rutaVertexShader, const char* rutaFragmentShader)
{
	string codigoVertexShader;
	ifstream vertexShaderStream(rutaVertexShader, ios::in);
}