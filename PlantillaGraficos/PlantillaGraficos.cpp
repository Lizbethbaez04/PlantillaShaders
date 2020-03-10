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

vector<Vertice> cuadrado;
GLuint vertexArrayCuadradoID;
GLuint bufferCuadradoID;

//Instancia del shader
Shader *shader;
//Identificadores para mapeo de atributos de entrada del vertex shader
GLuint posicionID;
GLuint colorID;

void inicializarCuadrado()
{
	Vertice v1 =
	{
		vec3(-0.2f, 0.2f, 0.0f),
		vec4(0.1f, 0.8f, 0.2f, 1.0f)
	};
	Vertice v2 =
	{
		vec3(0.2f, 0.2f, 0.0f),
		vec4(0.1f, 0.8f, 0.2f, 1.0f)
	};
	Vertice v3 =
	{
		vec3(0.2f, -0.2f, 0.0f),
		vec4(0.1f, 0.8f, 0.2f, 1.0f)
	};
	Vertice v4 =
	{
		vec3(-0.2f, -0.2f, 0.0f),
		vec4(0.1f, 0.8f, 0.2f, 1.0f)
	};
	cuadrado.push_back(v1);
	cuadrado.push_back(v2);
	cuadrado.push_back(v3);
	cuadrado.push_back(v4);
}

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
	//Elegir shader
	shader->enlazar();
	//Elegir el vertexArray 
	glBindVertexArray(vertexArrayTrianguloID);
	//Llamar la funcion de dibujo-Dibujar
	glDrawArrays(GL_TRIANGLES, 0, triangulo.size());

	//Proceso dibujo de cuadrado
	glBindVertexArray(vertexArrayCuadradoID);
	glDrawArrays(GL_QUADS, 0, cuadrado.size());//tipo de primitiva de dibujo, leerlo desde el principio, cuantos elementos tiene el vertexarray

	//Soltar Bind
	glBindVertexArray(0);
	//Soltar/desenlazar Shader
	shader->desenlazar();
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
	window = glfwCreateWindow(600, 600, "Ventana", NULL, NULL);
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
	inicializarCuadrado();

	const char* rutaVertexShader = "VertexShader.shader";
	const char* rutaFragmentShader = "FragmentShader.shader";
	shader = new Shader(rutaVertexShader, rutaFragmentShader);

	//Mapeo de atributos
	posicionID = glGetAttribLocation(shader->getID(), "posicion");
	colorID = glGetAttribLocation(shader->getID(), "color");

	shader->desenlazar();

	//Crear el vertex array del triangulo
	glGenVertexArrays(1, &vertexArrayTrianguloID);
	glBindVertexArray(vertexArrayTrianguloID);
	//Vertex buffer
	glGenBuffers(1, &bufferTrianguloID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferTrianguloID);
	//Asociar datos al buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertice) * triangulo.size(), triangulo.data(), GL_STATIC_DRAW);
	//Habilitar atributos de shader
	glEnableVertexAttribArray(posicionID);
	glEnableVertexAttribArray(colorID);
	//Especificar a openGL cómo comunicarse
	glVertexAttribPointer(posicionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertice), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertice), (void*)sizeof(vec3));
	
	//Proceso de incializar vertex array para el cuadrado
	glGenVertexArrays(1, &vertexArrayCuadradoID);//cuantos vertexarray quiero y en que direccion de memoria la quiero guardar
	glBindVertexArray(vertexArrayCuadradoID);//empiece a trabajar con el vertex array del cuadrado
	glGenBuffers(1, &bufferCuadradoID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferCuadradoID); //Que tipo de buffer es
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertice) * cuadrado.size(), cuadrado.data, GL_STATIC_DRAW);//te pide l tamaño del cuadrado, tamaño de espacio de informacion y para qué lo quieres (dibujar)
	glEnableVertexAttribArray(posicionID);//con que atributos del shader se va a comunicar
	glEnableVertexAttribArray(colorID);
	glVertexAttribPointer(posicionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertice), 0);//Cómo le va a mandar la info, 3 por las flotantes que hicimos
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertice), (void*)sizeof(vec3));

	//Soltar el vertexArray y el buffer
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

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


