#pragma once
#include <iostream>
#include <box2d.h>

//Inclusión de librerias adicionales
#include "SFML/Graphics.hpp"

//Espacios de nombres
using namespace std;
using namespace sf;

//Escena: Clase utilizada para gestionar los niveles del juego, las clases contienen un identificador único y no traen objetos
//por defecto, estos deben ser añadidos de forma individual por cada escena. Gestionadas por el gestor de escenas
class Escena {

protected:

	//Variables básicas
	bool activa;
	String identificador;

	//Atributos opcionales
	b2World* mundo = nullptr;

public:

	//Constructores
	Escena();
	Escena(String id);
	Escena(String id, bool activada);

	//Funciones sin retorno
	void estadoActivacion(bool estado);

	//Funciones con retorno de dato
	bool estaActiva();
	b2World* obtenerMundoFisico(); //Método opcional, solo llamar si se utiliza el atributo de mundo (Niveles)
	String obtenerIdentificador();

	//Métodos virtuales para sobreescribir
	virtual void restablecer();
	virtual void actualizarElementosAlojados(int unidad_conversion, int ragdolls_activos, int ragdolls_maximos, int puntaje, Vector2i posicion_cursor);
	virtual void renderizarElementosAlojados(RenderWindow* ventana);

};