#pragma once

//Inclusi�n de archivos propios
#include "Escena.h"
#include "GUIPanel.h"
#include "GUIBoton.h"
#include "GUITexto.h"

//Utiliza las enumeraciones personalizadas
#include "Enumeraciones.h"

//Espacios de nombres
using namespace std;

//Clase Menu: Una Escena que contiene todos los elementos necesarios para los men�es del juego (Incluyendo un panel y varios botones
//para acceder a los niveles o cerrar el programa). Usada para crear el men� principal, men� de objetivo de juego y men� de instrucciones
class Menu : public Escena {

private:

	//Constantes est�ticas que definen el tama�o de los arreglos de puntero para cada objeto usado
	const static int CANTIDAD_BOTONES = 4;
	const static int CANTIDAD_TEXTOS = 9;

	//Elementos gr�ficos de interfaz
	GUIPanel panel;
	GUIBoton* botones[CANTIDAD_BOTONES]; //Ver qu� tanta funcionalidad requiere el men� y cambiar ese valor
	GUITexto* textos[CANTIDAD_TEXTOS];

public:

	//Constructores
	Menu(String id);
	Menu(String id, bool activada);

	//M�todos sin retorno
	void crearPanel(Vector2f coordenadas_panel, Vector2f coordenadas_texto, String texto);
	void crearBoton(Vector2f coordenadas, Vector2f escala, String* texto, TipoSprite tipo);
	void crearBoton(Vector2f coordenadas, String* texto, TipoSprite tipo);
	void crearBoton(Vector2f coordenadas, String* texto, TipoSprite tipo, int indice);
	void crearTexto(Vector2f coordenadas, String texto, int dimensiones_caracter, Color color, int indice);
	void borrarBoton(int indice);
	void borrarTexto(int indice);

	//M�todos con retorno de dato
	GUIBoton* obtenerBoton(int indice);
	GUITexto* obtenerTexto(int indice);

	//Sobreescritura de m�todos heredados
	void renderizarElementosAlojados(RenderWindow* ventana) override;

};