#pragma once

//Inclusi�n de archivos propios
#include "Escena.h"

//Clase Adjuntable: Clase est�tica cuyo �nico prop�sito es otorgar funcionalidad para que los objetos que heredan de esta clase
//tengan la capacidad de ser a�adidos a objetos de tipo "Escena". Poligonos, Ragdolls, Figuras Visuales y elementos de interfaz todos
//deben estar adjuntos a una escena para poder actualizarse y visualizarse condicionalmente. Objetos sin escena siempre se visualizan/actualizan
class Adjuntable {

protected:

	//Puntero a la escena a la que el objeto est� enlazado
	Escena* escena_adjunta;

public:

	//Constructor
	Adjuntable();

	//M�todos sin retorno
	void adjuntarAEscena(Escena* escena);

	//M�todos con retorno de dato
	Escena* retornarEscenaAdjunta();

};

