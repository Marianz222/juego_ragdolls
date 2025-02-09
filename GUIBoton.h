#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional> //Permite pasar funciones a los m�todos (No usado en version final)

//Inclusi�n de archivos propios
#include "Escena.h"

//Utiliza las enumeraciones personalizadas
#include "Enumeraciones.h"

//Este objeto puede ser adjuntado a una escena
#include "Adjuntable.h"

//Espacios de nombres
using namespace std;
using namespace sf;

//Clase Boton de Interfaz: Esta clase contiene informaci�n para funcionar como un bot�n interactuable. Contiene una caja de colisi�n
//donde se registra el click, una imagen de fondo y opcionalmente puede contener texto (Usado para botones del menu de inicio)
class GUIBoton : public Adjuntable {

private:

	//Variables booleanas
	bool encendido = true;
	bool iluminado = false;

	//Variables de SFML
	Font fuente_boton;
	Text* texto_boton;
	Texture textura_boton;
	Texture textura_boton_iluminado;
	Texture textura_boton_desactivado;
	Sprite sprite_boton;
	FloatRect* hitbox_boton;

	//M�todos internos
	void inicializacionInterna(Vector2f posicion, Vector2f escala, String* texto, TipoSprite tipo, Escena* escena);

public:

	//Constructores de la clase
	GUIBoton();
	GUIBoton(Vector2f posicion, Vector2f escala);
	GUIBoton(Vector2f posicion, String* texto, TipoSprite tipo, Escena* escena);
	GUIBoton(Vector2f posicion, Vector2f escala, String* texto, TipoSprite tipo, Escena* escena);

	//M�todos sin retorno
	void cambiarTexto(String texto_nuevo);
	void encender(bool estado);
	void iluminar(bool estado);
	void dibujarElementos(RenderWindow* ventana);

	//M�todos con retorno de dato
	bool estaEncendido();
	bool revisarColisionesPorInterseccion(FloatRect hitbox_externa);
	bool revisarColisionesPorUbicacion(Vector2f coordenada);
	bool usandoTexto();
	Sprite retornarSprite();
	Text retornarVisualTexto();
	FloatRect retornarHitbox();

	//M�todos de Evento (No usados en version final)
	//void clickear(function<void()> funcion); //Por defecto
	//void clickear(function<void(Escena, Escena)>, Escena escena_a, Escena escena_b); //Llama a la funci�n a�adiendo 2 parametros de escena

};