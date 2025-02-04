#pragma once

//Inclusión de archivos propios
#include "Poligono.h"
#include "Enlace.h"

//Este objeto puede ser adjuntado a una escena
#include "Adjuntable.h"

//Clase Ragdoll: Objeto que representa un muñeco de trapo, compuesto por 6 componentes de extremidades y múltiples enlaces. Se genera
//al disparar usando el "Arma" y existe un límite definido para su instanciación
class Ragdoll : public Adjuntable {

private:

	//El ragdoll está compuesto por 6 objetos de tipo Polígono
	Poligono* componentes[6];
	Enlace* enlaces[5];

	//Métodos internos
	void inicializacionInterna(Vector2f dimensiones_poligono[6], Vector2f posicion[6], b2World* mundo, int unidad_conversion, Escena* escena);

public:

	//Constructor
	Ragdoll(Vector2f dimensiones_poligono[6], Vector2f posicion[6], b2World* mundo, int pixeles_por_metro, Escena* escena);

	//Métodos sin retorno
	void renderizar(RenderWindow* ventana);
	void actualizar(int pixeles_por_metro);
	void crearEnlaces(b2World* mundo, int pixeles_por_metro, Escena* escena);
	void aplicarFuerza(b2Vec2 magnitud);
	void aplicarFuerza(b2Vec2 magnitud, int indice_afectado);
	void rotar(float grados);
	void destruirComponentes(b2World* mundo);
	void destruirEnlaces(b2World* mundo);

	//Métodos con retorno de dato
	Poligono* retornarComponente(int indice);

};

