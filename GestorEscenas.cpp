#include "GestorEscenas.h"

//Cambiar Escena: Recibe 2 escenas por parámetro, desactiva la escena 1 para activar la 2
void GestorEscenas::cambiarEscena(Escena* escena_actual, Escena* escena_nueva) {

	//Si alguna de las escenas recibidas es nula...
	if (escena_actual == nullptr || escena_nueva == nullptr) {

		//Omite la ejecución, saliendo del método
		return;

	}

	//Llama a los métodos de activar y desactivar
	activarEscena(escena_nueva);
	restablecerEscena(escena_actual);
	desactivarEscena(escena_actual);

}

//Activar Escena: Activa la escena recibida por parámetro
void GestorEscenas::activarEscena(Escena* escena) {

	//Si la escena recibida es nula...
	if (escena == nullptr) {

		//Omite la ejecución, saliendo del método
		return;

	}

	//Si la escena ya está activada...
	if (escena->estaActiva()) {

		//Aborta la ejecución
		return;

	}

	//Cambia la activación a activada
	escena->estadoActivacion(true);

}

//Desactivar Escena: Desactiva la escena pasada por parámetro
void GestorEscenas::desactivarEscena(Escena* escena) {

	//Si la escena recibida es nula...
	if (escena == nullptr) {

		//Omite la ejecución, saliendo del método
		return;

	}

	//Si la escena ya está desactivada...
	if (!escena->estaActiva()) {

		//Aborta la ejecución
		return;

	}

	//Cambia la activación a desactivada
	escena->estadoActivacion(false);

}

//Restablecer Escena: Llama a la función de restablecimiento de escena desde la escena suministrada por parámetro.
void GestorEscenas::restablecerEscena(Escena* escena) {

	//Si la escena recibida es nula...
	if (escena == nullptr) {

		//Omite la ejecución, saliendo del método
		return;

	}

	//Restablece la escena
	escena->restablecer();

}