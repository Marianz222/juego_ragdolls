#pragma once

//Inclusión de librerias adicionales
#include <SFML/Graphics.hpp>
#include <iostream>

//Este objeto puede ser adjuntado a una escena
#include "Adjuntable.h"

//Espacios de nombres
using namespace std;
using namespace sf;

//Punto de Control: Un objeto que contiene un sprite, hitbox y estados para saber si fue activado y cómo lo fue. Este objeto funciona
//como el objetivo principal del juego, una caja o ragdoll activa el punto cuando entra en contacto con el mismo.
class PuntoControl : public Adjuntable {

private:

	//Estado activación
	bool activado = false;
	bool activado_indirectamente = false;

	//Texturas y Sprite
	Texture textura_base;
	Texture textura_activacion;
	Sprite sprite;

	//Hitbox
	FloatRect caja_colision;
	RectangleShape hitbox_depurado_visual;

	//Métodos internos
	void inicializacionInterna(Vector2f coordenadas, Escena* escena);

public:

	//Constructor
	PuntoControl(Vector2f coordenadas, Escena* escena);

	//Métodos sin retorno de dato
	void activar(bool estado);
	void actualizarTexturas(bool estado);
	void renderizar(RenderWindow* ventana);
	void asignarActivacionIndirecta(bool estado);

	//Métodos con retorno de dato
	bool fueActivado();
	bool fueActivadoIndirectamente();
	bool revisarColisiones(FloatRect colisionador_ajeno);
	Vector2f retornarPosicion();
	Sprite retornarSprite();
	FloatRect retornarHitbox();

};

