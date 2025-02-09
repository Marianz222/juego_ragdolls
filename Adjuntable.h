#pragma once

//Inclusión de archivos propios
#include "Escena.h"

//Clase Adjuntable: Clase estática cuyo único propósito es otorgar funcionalidad para que los objetos que heredan de esta clase
//tengan la capacidad de ser añadidos a objetos de tipo "Escena". Poligonos, Ragdolls, Figuras Visuales y elementos de interfaz todos
//deben estar adjuntos a una escena para poder actualizarse y visualizarse condicionalmente. Objetos sin escena siempre se visualizan/actualizan
class Adjuntable {

protected:

	//Puntero a la escena a la que el objeto está enlazado
	Escena* escena_adjunta;

public:

	//Constructor
	Adjuntable();

	//Métodos sin retorno
	void adjuntarAEscena(Escena* escena);

	//Métodos con retorno de dato
	Escena* retornarEscenaAdjunta();

};

