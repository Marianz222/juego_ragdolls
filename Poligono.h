#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <box2d.h>
#include <iostream>

//Este objeto puede ser adjuntado a una escena
#include "Adjuntable.h"

//Espacios de nombre
using namespace sf;

//Clase Poligono: Un objeto que contiene un cuerpo físico, una figura gráfica y una caja de colisiones
class Poligono : public Adjuntable {

private:

	//Vector de tamaño en metros
	Vector2f dimensiones;

	//Figura visual del poligono
	Texture textura;
	Sprite sprite;

	//Colisionador del objeto visual
	FloatRect caja_colision;

	//Figura física, definicion de cuerpo y cuerpo del poligono
	b2PolygonShape figura_cuerpo;
	b2BodyDef definicion_cuerpo;
	b2Body* cuerpo;

	//Definición de fijador y fijador del poligono
	b2FixtureDef definicion_fijador;
	b2Fixture* fijador;

public:

	//Constructores
	Poligono(String directorio_textura, Vector2f dimensiones_poligono, Vector2f posicion, float friccion, float restitucion, b2World* mundo, b2BodyType tipo, int pixeles_por_metro);
	Poligono(String directorio_textura, Vector2f dimensiones_poligono, Vector2f posicion, float friccion, float restitucion, b2World* mundo, b2BodyType tipo, int pixeles_por_metro, Escena* escena);

	//Métodos sin retorno
	void renderizar(RenderWindow* ventana);
	void crearFisicas(b2Vec2 dimensiones_poligono, b2Vec2 posicion, float friccion, float restitucion, b2World* mundo, b2BodyType tipo);
	void crearVisuales(String directorio_textura, Vector2f posicion, int pixeles_por_metro);
	void actualizar(int pixeles_por_metro);
	void modificarDensidad(float nuevo_valor);
	void modificarFriccion(float nuevo_valor);
	void modificarRestitucion(float nuevo_valor);
	void modificarRotacion(float grados);
	void despertar(bool estado);
	void aplicarFuerza(b2Vec2 magnitud);
	void destruir(b2World* mundo);

	//Métodos con retorno de dato
	b2Body* retornarCuerpo();
	Sprite retornarSprite();
	FloatRect retornarHitbox();
	Vector2f retornarDimensiones();
	Vector2f retornarPosicionVisual();
	b2Vec2 retornarPosicionFisica();
	b2BodyType retornarTipo();
	float retornarDensidad();
	float retornarFriccion();
	float retornarRestitucion();

};

