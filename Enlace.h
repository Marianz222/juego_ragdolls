#pragma once

//Inclusi�n de archivos propios
#include "Poligono.h"

//Utiliza las enumeraciones personalizadas
#include "Enumeraciones.h"

//Este objeto puede ser adjuntado a una escena
#include "Adjuntable.h"

//Clase Enlace: Un joint utilizado para unir 2 objetos. Permite elegir el tipo de joint mediante una enumeraci�n, asignar qu� objetos
//se conectan y los atributos de la conexi�n. Solo responde a f�sicas si la escena en la cual est� contenido est� activa
class Enlace : public Adjuntable {

private:

	//Arreglo de puntos representando la l�nea gr�fica
	VertexArray puntos_visuales;

	//Definici�n y Junta de Revoluci�n
	b2RevoluteJointDef definicion_junta_revolutiva;
	b2RevoluteJoint* junta_revolutiva;

	//Definici�n y Junta de Distancia
	b2DistanceJointDef definicion_junta_distancia;
	b2DistanceJoint* junta_distancia;

	//Definici�n y Junta Prism�tica
	b2PrismaticJointDef definicion_junta_prismatica;
	b2PrismaticJoint* junta_prismatica;

	//Referencias locales para objetos recibidos por par�metro al crear la junta
	Poligono* objeto_a;
	Poligono* objeto_b;
	b2Vec2 coordenadas_ancla_a;
	b2Vec2 coordenadas_ancla_b;

	//M�todos internos
	void inicializacionInterna(b2JointType tipo, b2Vec2 eje_prismatico, Poligono* objetos[], b2Vec2 coordenadas_ancla[], b2World* mundo, int unidad_conversion, Escena* escena);

public:

	//Constructores
	Enlace(b2JointType tipo, Poligono* objeto1, Poligono* objeto2, b2Vec2 coordenadas_ancla1, b2Vec2 coordenadas_ancla2, b2World* mundo, int pixeles_por_metro, Escena* escena);
	Enlace(b2JointType tipo, b2Vec2 eje_movimiento, Poligono* objeto1, Poligono* objeto2, b2Vec2 coordenadas_ancla1, b2Vec2 coordenadas_ancla2, b2World* mundo, int pixeles_por_metro, Escena* escena);

	//M�todos sin retorno
	void renderizar(RenderWindow* ventana);
	void actualizar(int pixeles_por_metro);
	void destruir(b2World* mundo);

	//M�todos para la Junta (Generales)
	void activarMotor(bool estado, float velocidad, float velocidad_maxima);
	void limitar(bool estado);

	//M�todos para "Junta de Distancia"
	void establecerLongitud(TipoLongitud operacion, float valor);
	void establecerDamping(float valor);

	//M�todos para "Junta Prism�tica"
	void establecerLimites(Vector2f valores);

	//M�todos con retorno de dato
	Poligono* retornarPoligonoA();
	Poligono* retornarPoligonoB();
	b2Joint* retornarJunta();

};

