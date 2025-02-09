#pragma once

//Inclusión de archivos propios
#include "FiguraVisual.h"
#include "Ragdoll.h"
#include "Escena.h"

//Este objeto puede ser adjuntado a una escena
#include "Adjuntable.h"

//Clase Arma: Una clase que representa el cañon que dispara el usuario. Cada nivel contiene un arma, y esta generará ragdolls al disparar
class Arma : public Adjuntable {

private:

	//Variables gráficas
	FiguraVisual* base;
	FiguraVisual* barril;

	//Variables físicas generales
	Vector2f fuerza_total;
	float distancia_a_cursor;
	float angulo;

	//Métodos internos
	void inicializacionInterna(Vector2f coordenadas, Escena* escena, int unidad_conversion);

public:

	//Constructor
	Arma(Vector2f coordenadas, Escena* escena, int pixeles_por_metro);

	//Métodos sin retorno
	void dispararRagdoll(Vector2f coordenadas_disparo, int unidad_conversion, b2World* mundo, int limite_aparicion, Ragdoll* lista[], Escena* escena);
	void actualizarElementos(float multiplicador_fuerza, Vector2i posicion_cursor);
	void actualizarSistemaApuntado(float multiplicador_fuerza, Vector2i posicion_cursor);
	void dibujarElementos(RenderWindow* ventana);

	//Métodos con retorno de dato
	FiguraVisual obtenerRielDisparo();

};

