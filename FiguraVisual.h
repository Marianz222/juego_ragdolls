#pragma once
#include <SFML/Graphics.hpp>
#include <Box2d.h>
#include <iostream>

//Este objeto puede ser adjuntado a una escena
#include "Adjuntable.h"

//Utiliza las enumeraciones personalizadas
#include "Enumeraciones.h"

using namespace std;
using namespace sf;

//Figura Visual: Clase hermana de Poligono usada para crear cuerpos que no requieren el motor de f�sicas para funcionar.
//�nicamente contiene un sprite con textura y los m�todos necesarios para instanciarlo y manipular sus atributos
class FiguraVisual : public Adjuntable {

private:

	//Dimensiones del rect�ngulo
	Vector2f dimensiones;

	//Sprite y textura
	Texture textura;
	Sprite* sprite;

	//M�todos internos
	void inicializacionInterna(String direccion_textura, Vector2f posicion, Escena* escena);

public:

	//Constructores
	FiguraVisual(Vector2f posicion, Vector2f dimensiones_figura, String direccion_textura, Escena* escena);

	//M�todos sin retorno
	void renderizar(RenderWindow* ventana);
	void modificarOrigen(Vector2f offset);
	void rotar(float grados);
	void establecerRotacion(float grados);

	//M�todos con retorno
	Vector2f retornarPosicion();

};

