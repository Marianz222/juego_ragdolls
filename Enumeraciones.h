#pragma once

//Enumeraci�n: Tipo de Sprite - Enumeraci�n que contiene los tipos de sprite posibles de seleccionar (Cuadrado, Circulo y Rectangulo)
enum class TipoSprite {

	CUADRADO,
	RECTANGULAR,
	CIRCULAR,
	SALIR,
	REINICIAR,
	AVANZAR

};

//Enumeraci�n: Operaci�n Puntaje - Contiene los 2 tipos de operaciones v�lidas para usar la funci�n de modificar puntaje en la clase juego
enum class OperacionPuntaje {

	SUMA,
	RESTA,
	ESTABLECER

};

//Enumeraci�n: Operaci�n Eliminaci�n Ragdoll - Contiene los 2 tipos de operaciones v�lidas para usar la funci�n de eliminaci�n de Ragdolls en la clase juego
enum class OperacionEliminacion {

	UNO,
	TODOS

};

//Enumeraci�n: Tipo de Longitud - Contiene 3 tipos de operaciones v�lidas para usar al modificar un enlace que contiene una junta de distancia
enum class TipoLongitud {

	BASE,
	MINIMA,
	MAXIMA

};