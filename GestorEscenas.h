#pragma once

//Inclusión de archivos propios
#include "Escena.h"

//Gestor de Escenas: Clase que se encarga de manejar las escenas, ya sea activandolas o intercambiando entre ellas.
//Contiene métodos que permiten activar, desactivar y restablecer escenas
class GestorEscenas {

	//Esta clase no contiene atributos

public:

	//Funciones sin retorno
	void cambiarEscena(Escena* escena_actual, Escena* escena_nueva);
	void activarEscena(Escena* escena);
	void desactivarEscena(Escena* escena);
	void restablecerEscena(Escena* escena);

};

