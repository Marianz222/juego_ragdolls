#include "GUITexto.h"

//Constructor por defecto: No recibe argumentos, y crea un texto por defecto con parámetros estandarizados
GUITexto::GUITexto() {

	//Llama a inicializar con valores por defecto
	inicializacionInterna({0.0f, 0.0f}, "default", 16, Color::White, nullptr);

}

//Constructor sencillo: Recibe la cadena de texto a insertar, el tamaño de las letras y la escala del texto en general como parámetros
GUITexto::GUITexto(Vector2f posicion, String texto, int tamanio_caracter) {

	//Llama a inicializar con algunos valores por defecto y otros recibidos por parámetro
	inicializacionInterna(posicion, texto, tamanio_caracter, Color::White, nullptr);

}

//Constructor compuesto: Recibe la cadena de texto, el tamaño de letra, el color, la escala general y la escena donde se insertará el texto
GUITexto::GUITexto(Vector2f posicion, String texto, int tamanio_caracter, Color color, Escena* escena) {

	//Llama a inicializar usando todos los valores recibidos por parámetro
	inicializacionInterna(posicion, texto, tamanio_caracter, color, escena);

}

//////////////////////////////////////////////////////////////////

//Inicialización Interna: Recibe los parámetros del constructor e instancia los elementos de la clase
void GUITexto::inicializacionInterna(Vector2f posicion, String texto, int tamanio_caracter, Color color, Escena* escena) {

	//Carga la fuente estándar usando la dirección y la asigna al atributo
	fuente.loadFromFile("assets/fonts/arial.ttf");

	//Configura los aspectos esenciales del texto, usando los argumentos recibidos
	this->texto.setFont(fuente);
	this->texto.setString(texto);
	this->texto.setFillColor(color);
	this->texto.setCharacterSize(tamanio_caracter);
	this->texto.setPosition(posicion);
	this->texto.setOrigin(this->texto.getGlobalBounds().width / 2, this->texto.getGlobalBounds().height / 2);

	//Si la escena recibida como argumento no es nula...
	if (escena != nullptr) {

		//Finalmente adjunta el texto a la escena recibida
		this->adjuntarAEscena(escena);

	}

}

//Modificar Texto: Reemplaza la cadena de texto actual por la recibida como argumento
void GUITexto::modificarTexto(String nuevo_texto) {

	//Asigna el texto al atributo de la clase y cambia el texto con "SetString()"
	cadena_texto = nuevo_texto;
	texto.setString(nuevo_texto);

}

//Dibujar Elemento: Llama a la directiva de dibujar usando la ventana recibida, suministrando el texto para el renderizado
void GUITexto::dibujarElemento(RenderWindow* ventana) {

	ventana->draw(texto);

}

//Definir Color: Recibe como argumento un color que será asignado al texto gráfico
void GUITexto::definirColor(Color color) {

	texto.setFillColor(color);

}

//Definir Color Borde: Igual que definir color, pero el color será asignado al borde (outline) del texto
void GUITexto::definirColorBorde(Color color) {

	texto.setOutlineColor(color);

}

//Definir Grosor Borde: Recibe el grosor por argumento y sirve para ajustar qué tan fina es la línea del borde (outline) del texto
void GUITexto::definirGrosorBorde(float grosor) {

	texto.setOutlineThickness(grosor);

}

//////////////////////////////////////////////////////////////////

//Retornar Texto Visual: Devuelve el objeto de texto de la clase (No confundir con la cadena de texto)
Text GUITexto::retornarTextoVisual() {

	return texto;

}

//Retornar Cadena Texto: Retorna la cadena de texto (string) de la clase
String GUITexto::retornarCadenaTexto() {

	return texto.getString();

}