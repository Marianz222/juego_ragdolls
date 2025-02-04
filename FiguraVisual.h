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

//Figura Visual: Clase hermana de Poligono usada para crear cuerpos que no requieren el motor de físicas para funcionar.
//Únicamente contiene un sprite con textura y los métodos necesarios para instanciarlo y manipular sus atributos
class FiguraVisual : public Adjuntable {

private:

	//Dimensiones del rectángulo
	Vector2f dimensiones;

	//Sprite y textura
	Texture textura;
	Sprite* sprite;

	//Métodos internos
	void inicializacionInterna(String direccion_textura, Vector2f posicion, Escena* escena);

public:

	//Constructores
	FiguraVisual(Vector2f posicion, Vector2f dimensiones_figura, String direccion_textura, Escena* escena);

	//Métodos sin retorno
	void renderizar(RenderWindow* ventana);
	void modificarOrigen(Vector2f offset);
	void rotar(float grados);
	void establecerRotacion(float grados);

	//Métodos con retorno
	Vector2f retornarPosicion();

};

