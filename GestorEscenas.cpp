#include "GestorEscenas.h"

//Cambiar Escena: Recibe 2 escenas por par�metro, desactiva la escena 1 para activar la 2
void GestorEscenas::cambiarEscena(Escena* escena_actual, Escena* escena_nueva) {

	//Si alguna de las escenas recibidas es nula...
	if (escena_actual == nullptr || escena_nueva == nullptr) {

		//Omite la ejecuci�n, saliendo del m�todo
		return;

	}

	//Llama a los m�todos de activar y desactivar
	activarEscena(escena_nueva);
	restablecerEscena(escena_actual);
	desactivarEscena(escena_actual);

}

//Activar Escena: Activa la escena recibida por par�metro
void GestorEscenas::activarEscena(Escena* escena) {

	//Si la escena recibida es nula...
	if (escena == nullptr) {

		//Omite la ejecuci�n, saliendo del m�todo
		return;

	}

	//Si la escena ya est� activada...
	if (escena->estaActiva()) {

		//Aborta la ejecuci�n
		return;

	}

	//Cambia la activaci�n a activada
	escena->estadoActivacion(true);

}

//Desactivar Escena: Desactiva la escena pasada por par�metro
void GestorEscenas::desactivarEscena(Escena* escena) {

	//Si la escena recibida es nula...
	if (escena == nullptr) {

		//Omite la ejecuci�n, saliendo del m�todo
		return;

	}

	//Si la escena ya est� desactivada...
	if (!escena->estaActiva()) {

		//Aborta la ejecuci�n
		return;

	}

	//Cambia la activaci�n a desactivada
	escena->estadoActivacion(false);

}

//Restablecer Escena: Llama a la funci�n de restablecimiento de escena desde la escena suministrada por par�metro.
void GestorEscenas::restablecerEscena(Escena* escena) {

	//Si la escena recibida es nula...
	if (escena == nullptr) {

		//Omite la ejecuci�n, saliendo del m�todo
		return;

	}

	//Restablece la escena
	escena->restablecer();

}