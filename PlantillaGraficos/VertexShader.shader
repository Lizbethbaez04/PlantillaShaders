#version 330 core
//La primera linea SIEMPRE es la version sino marca error. Lenguaje GLSL -> parecido al C
//2 objetivos principales
// 1.- Establecer valor para gl_Position
// 2.- Enviar valores al fragment Shader

//Atributos de entrada (son los que vienen desde c++)
in vec3 posicion;
in vec4 color;

//Atributos de salida (son los que van a ir hacia el fragmentShader)
out vec4 fragmentColor;

//Funcion main
void main()
{
	//Posicion del vertice (vec4)
	gl_Position.xyz = posicion;
	gl_Position.w = 1.0;

	//Establecer valores de atributos de salida
	fragmentColor = color;


}