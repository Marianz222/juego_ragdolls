#pragma once

//Inclusión de librerias adicionales
#include <SFML/Graphics.hpp>
#include <iostream>

//Este objeto puede ser adjuntado a una escena
#include "Adjuntable.h"

//Espacios de nombres
using namespace std;
using namespace sf;

//Clase Texto: Permite crear un texto por separado de los botones y los paneles. Útil para escribir sin que ese texto esté enlazado
//A un objeto de interfaz interactuable o a un panel de fondo
class GUITexto : public Adjuntable {

private:

	//Atributos de texto
	Font fuente;
	String cadena_texto;
	Text texto;

	//Métodos internos
	void inicializacionInterna(Vector2f posicion, String texto, int tamanio_caracter, Color color, Escena* escena);

public:

	//Constructores
	GUITexto();
	GUITexto(Vector2f posicion, String texto, int tamanio_caracter);
	GUITexto(Vector2f posicion, String texto, int tamanio_caracter, Color color, Escena* escena);

	//Métodos sin retorno
	void modificarTexto(String nuevo_texto);
	void dibujarElemento(RenderWindow* ventana);
	void definirColor(Color color);
	void definirGrosorBorde(float grosor);
	void definirColorBorde(Color color);

	//Métodos con retorno
	Text retornarTextoVisual();
	String retornarCadenaTexto();

};

