#pragma once

//Enumeración: Tipo de Sprite - Enumeración que contiene los tipos de sprite posibles de seleccionar (Cuadrado, Circulo y Rectangulo)
enum class TipoSprite {

	CUADRADO,
	RECTANGULAR,
	CIRCULAR,
	SALIR,
	REINICIAR,
	AVANZAR

};

//Enumeración: Operación Puntaje - Contiene los 2 tipos de operaciones válidas para usar la función de modificar puntaje en la clase juego
enum class OperacionPuntaje {

	SUMA,
	RESTA,
	ESTABLECER

};

//Enumeración: Operación Eliminación Ragdoll - Contiene los 2 tipos de operaciones válidas para usar la función de eliminación de Ragdolls en la clase juego
enum class OperacionEliminacion {

	UNO,
	TODOS

};

//Enumeración: Tipo de Longitud - Contiene 3 tipos de operaciones válidas para usar al modificar un enlace que contiene una junta de distancia
enum class TipoLongitud {

	BASE,
	MINIMA,
	MAXIMA

};