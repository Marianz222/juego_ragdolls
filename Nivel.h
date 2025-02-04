#pragma once

//Inclusión de archivos propios
#include "Escena.h"
#include "Poligono.h"
#include "Arma.h"
#include "GUIBoton.h"
#include "GUITexto.h"
#include "PuntoControl.h"

//Clase Nivel: Una Escena modificada que contiene gran cantidad de poligonos y el arma del usuario, usado para representar cada nivel
//del juego. El indicador de puntaje no está contenido en esta clase, ya que es un elemento universal, pero si contiene un boton de menu
class Nivel : public Escena {

private:

	//Constantes estáticas que definen el tamaño de los arreglos
	const static int OBSTACULOS_MAXIMOS = 30;
	const static int PUNTOS_CONTROL_MAXIMOS = 5;
	const static int ENLACES_MAXIMOS = 4;
	const static int BOTONES_MAXIMOS = 3;

	//Atributos de interfaz
	GUIBoton* botones[BOTONES_MAXIMOS];

	//Variables de mundo
	b2Vec2 gravedad;

	//Atributos de objetos
	Poligono* paredes[4];
	Poligono* obstaculos[OBSTACULOS_MAXIMOS];
	PuntoControl* puntos_control[PUNTOS_CONTROL_MAXIMOS];
	Enlace* enlaces[ENLACES_MAXIMOS];

	//Arma del nivel
	Arma* arma;

	//Texto del HUD (Contador Ragdolls y Puntaje)
	GUITexto* contadores[2];

	//Métodos internos
	void inicializacionInterna(String id, Vector2f ubicacion_arma, int unidad_conversion, Vector2i dimensiones_ventana);

public:

	//Constructores
	Nivel(Vector2f ubicacion_arma, string id, int unidad_conversion, Vector2i dimensiones_ventana);
	Nivel(Vector2f ubicacion_arma, string id, int unidad_conversion, Vector2i dimensiones_ventana, bool activo);

	//Métodos sin retorno
	void crearSala(int unidad_conversion, Vector2i dimensiones_ventana);
	void crearArma(Vector2f coordenadas, int unidad_conversion);
	void insertarObstaculo(String directorio_textura, Vector2f dimensiones, Vector2f coordenadas, float friccion, float restitucion, b2World* mundo, b2BodyType tipo, int pixeles_por_metro);
	void insertarPuntoControl(Vector2f coordenadas);
	void insertarEnlace(b2JointType tipo, b2Vec2 eje_prismatico, Poligono* objeto1, Poligono* objeto2, b2Vec2 coordenadas_ancla1, b2Vec2 coordenadas_ancla2, b2World* mundo, int unidad_conversion);
	void crearHUD(Vector2i dimensiones_ventana);

	//Métodos con retorno de dato
	Arma* retornarArma();
	Poligono* retornarObstaculo(int indice);
	PuntoControl* retornarPuntoControl(int indice);
	Poligono* retornarPared(int indice);
	Enlace* retornarEnlace(int indice);
	int retornarObstaculosMaximos();
	int retornarPuntosControlMaximos();
	int retornarBotonesMaximos();
	GUIBoton* obtenerBoton(int indice);
	bool revisarPuntosControlActivados();

	//Métodos de depuración
	void depurarEstadoObstaculos();

	//Sobreescritura de métodos heredados
	void restablecer() override;
	void actualizarElementosAlojados(int unidad_conversion, int ragdolls_activos, int ragdolls_maximos, int puntaje, Vector2i posicion_cursor) override;
	void renderizarElementosAlojados(RenderWindow* ventana) override;

};

