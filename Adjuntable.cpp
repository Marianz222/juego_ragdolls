#include "Adjuntable.h"

//Constructor principal: No recibe parámetros y establece la escena adjunta en nulo
Adjuntable::Adjuntable() {

	escena_adjunta = nullptr;

}

//////////////////////////////////////////////////////////////////

//Adjuntar a Escena: Método simple utilizado para añadir un objeto a una escena, al llamarlo se pasa un puntero a la escena a la cual
//se quiere adjuntar el objeto en cuestión
void Adjuntable::adjuntarAEscena(Escena* escena) {

	//Establece el puntero del objeto al de la escena suministrada
	escena_adjunta = escena;

}

//////////////////////////////////////////////////////////////////

//Retornar Escena Adjunta: Devuelve un puntero a la escena a la cual el objeto está adjunto. Esencialmente obtiene la escena
Escena* Adjuntable::retornarEscenaAdjunta() {

	return escena_adjunta;

}
