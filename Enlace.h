#pragma once

//Inclusión de archivos propios
#include "Poligono.h"

//Utiliza las enumeraciones personalizadas
#include "Enumeraciones.h"

//Este objeto puede ser adjuntado a una escena
#include "Adjuntable.h"

//Clase Enlace: Un joint utilizado para unir 2 objetos. Permite elegir el tipo de joint mediante una enumeración, asignar qué objetos
//se conectan y los atributos de la conexión. Solo responde a físicas si la escena en la cual está contenido está activa
class Enlace : public Adjuntable {

private:

	//Arreglo de puntos representando la línea gráfica
	VertexArray puntos_visuales;

	//Definición y Junta de Revolución
	b2RevoluteJointDef definicion_junta_revolutiva;
	b2RevoluteJoint* junta_revolutiva;

	//Definición y Junta de Distancia
	b2DistanceJointDef definicion_junta_distancia;
	b2DistanceJoint* junta_distancia;

	//Definición y Junta Prismática
	b2PrismaticJointDef definicion_junta_prismatica;
	b2PrismaticJoint* junta_prismatica;

	//Referencias locales para objetos recibidos por parámetro al crear la junta
	Poligono* objeto_a;
	Poligono* objeto_b;
	b2Vec2 coordenadas_ancla_a;
	b2Vec2 coordenadas_ancla_b;

	//Métodos internos
	void inicializacionInterna(b2JointType tipo, b2Vec2 eje_prismatico, Poligono* objetos[], b2Vec2 coordenadas_ancla[], b2World* mundo, int unidad_conversion, Escena* escena);

public:

	//Constructores
	Enlace(b2JointType tipo, Poligono* objeto1, Poligono* objeto2, b2Vec2 coordenadas_ancla1, b2Vec2 coordenadas_ancla2, b2World* mundo, int pixeles_por_metro, Escena* escena);
	Enlace(b2JointType tipo, b2Vec2 eje_movimiento, Poligono* objeto1, Poligono* objeto2, b2Vec2 coordenadas_ancla1, b2Vec2 coordenadas_ancla2, b2World* mundo, int pixeles_por_metro, Escena* escena);

	//Métodos sin retorno
	void renderizar(RenderWindow* ventana);
	void actualizar(int pixeles_por_metro);
	void destruir(b2World* mundo);

	//Métodos para la Junta (Generales)
	void activarMotor(bool estado, float velocidad, float velocidad_maxima);
	void limitar(bool estado);

	//Métodos para "Junta de Distancia"
	void establecerLongitud(TipoLongitud operacion, float valor);
	void establecerDamping(float valor);

	//Métodos para "Junta Prismática"
	void establecerLimites(Vector2f valores);

	//Métodos con retorno de dato
	Poligono* retornarPoligonoA();
	Poligono* retornarPoligonoB();
	b2Joint* retornarJunta();

};

