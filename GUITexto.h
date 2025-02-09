#pragma once

//Inclusi�n de librerias adicionales
#include <SFML/Graphics.hpp>
#include <iostream>

//Este objeto puede ser adjuntado a una escena
#include "Adjuntable.h"

//Espacios de nombres
using namespace std;
using namespace sf;

//Clase Texto: Permite crear un texto por separado de los botones y los paneles. �til para escribir sin que ese texto est� enlazado
//A un objeto de interfaz interactuable o a un panel de fondo
class GUITexto : public Adjuntable {

private:

	//Atributos de texto
	Font fuente;
	String cadena_texto;
	Text texto;

	//M�todos internos
	void inicializacionInterna(Vector2f posicion, String texto, int tamanio_caracter, Color color, Escena* escena);

public:

	//Constructores
	GUITexto();
	GUITexto(Vector2f posicion, String texto, int tamanio_caracter);
	GUITexto(Vector2f posicion, String texto, int tamanio_caracter, Color color, Escena* escena);

	//M�todos sin retorno
	void modificarTexto(String nuevo_texto);
	void dibujarElemento(RenderWindow* ventana);
	void definirColor(Color color);
	void definirGrosorBorde(float grosor);
	void definirColorBorde(Color color);

	//M�todos con retorno
	Text retornarTextoVisual();
	String retornarCadenaTexto();

};

