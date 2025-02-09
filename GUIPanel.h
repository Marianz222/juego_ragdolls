#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

//Este objeto puede ser adjuntado a una escena
#include "Adjuntable.h"

//Espacios de nombres
using namespace std;
using namespace sf;

//Clase Panel: Similar a bot�n, es un elemento de interfaz con la diferencia de que no usa colisiones, por ende solo funciona como
//base gr�fica sobre la cual a�adir botones u otros indicadores visuales. El panel puede tener texto al igual que el bot�n
class GUIPanel : public Adjuntable {

private:

	//Variables simples
	bool visible = true;

	//Variables de SFML
	Font* titan_fuente;
	Text* texto_panel;
	Texture* textura_panel;
	Sprite sprite_panel;;

	//M�todos internos
	void inicializacionInterna(Vector2f posicion_panel, String texto, Vector2f offset_texto);

public:

	//Constructores de la clase
	GUIPanel();
	GUIPanel(Vector2f posicion_panel, String texto, Vector2f offset_texto);
	GUIPanel(Vector2f posicion_panel, String texto, Vector2f offset_texto, Escena* escena);

	//M�todos sin retorno
	void cambiarTexto(String nuevo_texto);
	void cambiarVisibilidad(bool estado);
	void dibujarElementos(RenderWindow* ventana);

	//M�todos con retorno de dato
	Sprite retornarSprite();
	Text retornarVisualTexto();

};