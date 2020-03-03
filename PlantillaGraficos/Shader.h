#pragma once

//Input Output
#include <stdio.h>
#include <stdlib.h>

//OpenGL
#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

//Manejo archivos
#include <iostream>
#include <fstream>

//Manejo de textos
#include <string>
#include <vector>

using namespace std;

class Shader
{
public:
	Shader(const char* rutaVertexShader, const char* rutaFragmentShader);
	GLuint getID();
	void enlazar();
	void desenlazar();

private:
	GLuint shaderID;
	
	//Funciones
	void verificarCompilacion(GLuint id);
	void verificarVinculacion(GLuint id);


};