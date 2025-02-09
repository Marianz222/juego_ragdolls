#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <box2d.h>
#include <iostream>
#include <cstdlib>

//Inclusión de archivos propios
#include "Poligono.h"
#include "Ragdoll.h"
#include "FiguraVisual.h"
#include "GestorEscenas.h"
#include "Menu.h"
#include "Nivel.h"
#include "GUITexto.h"

//Utiliza las enumeraciones personalizadas
#include "Enumeraciones.h"

//Espacios de nombres
using namespace std;
using namespace sf;

//Clase Juego: La clase principal que se encarga de manejar todos los objetos y la lógica del programa completo. En esta clase
//se crearán los objetos más importantes, se accedera a los eventos de entrada del usuario y se contendrá el bucle principal de juego
class Juego {

private:

	//Constante que define a cuantos pixeles equivale un metro
	const int PIXELES_POR_METRO = 50;

	//Constantes limitantes para arreglos
	static const int CANTIDAD_NIVELES = 3; //Define el limite de niveles
	const static int LIMITE_RAGDOLLS = 8; //Define el limite para el arreglo de ragdolls

	//Variables de la ventana del programa
	const Vector2i DIMENSIONES_VENTANA = {1920, 1080};
	string nombre_ventana;

	//Ventana
	RenderWindow* ventana; //Puntero a la ventana principal del juego

	//Gestor de Eventos
	Event* gestor_eventos; //Puntero a la pila de eventos de SFML

	//Escenas y Gestor de Escena
	GestorEscenas* gestor_escenas;
	Menu* menues[3]; //Contiene Menu Principal, Menu Instrucciones y Condicion de Victoria
	Nivel* niveles[3]; //Contiene los 3 niveles del juego, en orden

	//Arreglo de ragdolls general
	Ragdoll* ragdolls[LIMITE_RAGDOLLS]; //Crea el arreglo de punteros

	//Arma activa
	Arma* arma_activa = nullptr; //Puntero hacia el arma actualmente activa en el juego
	float potencia_arma = 50.0f; //Fuerza base de disparo del arma

	//Variable de puntaje
	int puntaje = 0;

	//Variables de fin de juego
	bool juego_terminado = false;
	GUITexto* texto_fin_juego;
	Clock reloj_general;
	bool chequeando_derrota = false;

	//Métodos internos
	void generarNivel1();
	void generarNivel2();
	void generarNivel3();

public:

	//Constructor
	Juego(string nombre_programa);

	//Métodos sin retorno
	void ejecutar();
	void crearEscenas();
	void configurarTextoFinal();
	void generarNivel(int numero);
	void actualizarRenderizado();
	void gestionarEventos();
	void actualizarFisicas(int iteraciones_velocidad, int iteraciones_posicion);
	void actualizarObjetos();
	void dispararArmaActiva(int unidad_conversion, b2World* mundo, int limite_aparicion);
	void eliminarRagdoll(OperacionEliminacion operacion);
	void aplicarFuerza(b2Body* cuerpo, b2Vec2 valor);
	void detectarArmaActiva();
	void manejarClickBotones(Vector2i coordenadas_mouse);
	void manejarIluminacionBotones(Vector2i coordenadas_mouse);
	void manejarColisiones();
	void modificarPuntaje(OperacionPuntaje operacion, int valor);
	void dispararVictoria();
	void dispararDerrota();
	void chequearDerrota();
	void manejarReinicioNivel();

	//Métodos con retorno de datos
	RenderWindow* crearVentana(int altura, int anchura, string nombre);
	int contarRagdollsActivos();
	Escena* obtenerEscenaActiva();

	//Métodos de depuración
	void depurarTransformacion(Poligono objeto);
	void depurarEstadoArreglo();
	void depurarPosicionCursor(Vector2i posicion_cursor, bool modo_fisico);

};

