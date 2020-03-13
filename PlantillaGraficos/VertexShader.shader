#version 330 core
//La primera linea SIEMPRE es la version sino marca error. Lenguaje GLSL -> parecido al C
//2 objetivos principales
// 1.- Establecer valor para gl_Position
// 2.- Enviar valores al fragment Shader

//Atributos de entrada (son los que vienen desde c++)
in vec4 posicion;
in vec4 color;

//Uniforms -> son variables de entrada tambien -> matrices
uniform mat4 transformaciones;


//Atributos de salida (son los que van a ir hacia el fragmentShader)
out vec4 fragmentColor;

//Funcion main
void main()
{
	//Posicion del vertice (vec4)
	gl_Position = transformaciones * posicion;

	//Establecer valores de atributos de salida
	fragmentColor = color;


}