// PlantillaGraficos.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <math.h>
#include <iostream>

#include "Shader.h"
#include "Vertice.h"
#include <vector>

using namespace std;

//Cada elemento que se quiera renderear necesita un vertex arrary y un buffer
vector<Vertice> triangulo;
GLuint vertexArrayTrianguloID;
GLuint bufferTrianguloID;

//Instancia del shader
Shader *shader;
//Identificadores para mapeo de atributos de entrada del vertex shader
GLuint posicionID;
GLuint colorID;

void inicializarTriangulo()
{
	Vertice v1 =
	{
		vec3(0.0f, 0.3f, 0.0f), 
		vec4(0.8f, 0.1f, 0.0f, 1.0f)
	};
	Vertice v2 =
	{
		vec3(-0.3f, -0.3f, 0.0f),
		vec4(0.8f, 0.1f, 0.0f, 1.0f)
	};
	Vertice v3 =
	{
		vec3(0.3f, -0.3f, 0.0f),
		vec4(0.8f, 0.1f, 0.0f, 1.0f)
	};
	triangulo.push_back(v1);
	triangulo.push_back(v2);
	triangulo.push_back(v3);
}

void dibujar()
{
		
}

int main()
{
    //Declarar una ventana
	GLFWwindow* window;

	//Si no se pudo iniciar GLFW terminamos ejecucion
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}
	//Si se pudo iniciar GLFW, inicializamos la ventana
	window = glfwCreateWindow(800, 600, "Ventana", NULL, NULL);
	//Si no se pudo crear la ventana, terminamos la ejecucion
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//Establecemos la ventana como contexto
	glfwMakeContextCurrent(window);

	//Una vez establecido el contexto, se activan las funciones "modernas" (gpu)
	glewExperimental = true;

	GLenum errores = glewInit();
	if (errores != GLEW_OK)
	{
		glewGetErrorString(errores);
	}

	const GLubyte* versionGL = glGetString(GL_VERSION);

	cout << "Version OpenGL: " << versionGL;

	inicializarTriangulo();

	const char* rutaVertexShader = "VertexShader.shader";
	const char* rutaFragmentShader = "FragmentShader.shader";
	shader = new Shader(rutaVertexShader, rutaFragmentShader);


	//Ciclo de dibujo (Draw loop)
	while (!glfwWindowShouldClose(window))
	{
		//Establecer region de dibujo
		glViewport(0, 0, 600, 600);
		//Establecemos el color de borrado
		//Valores RGBA
		glClearColor(1, 0.7, 0.9, 1);
		//Borrar
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Actualizar valores y dibujar
		dibujar();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	//Despues del ciclo de dibujo, eliminamos venta y procesos de glfw
	glfwDestroyWindow(window);
	glfwTerminate();
}


