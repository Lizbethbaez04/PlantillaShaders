#version 330 core
//Primera linea SIEMPRE es la version 
//Objetivo: Establecer valores de atributos de salida

//Atributos de entrada (No provienen del c++, provienen del vertex Shader)
in vec4 fragmentColor;

//Atributos de salida ()
// 1ero define la visualizacion del fragmento
out vec4 salidaColor;

void main()
{
	salidaColor = fragmentColor;
}