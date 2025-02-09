#include "FiguraVisual.h"

//Constructor de Sprite: Recibe par�metros de modo (Debe ser SPRITE), coordenadas, dimensiones del sprite, cadena de texto para el path de textura
//Y finalmente la escena en donde se adjuntar� el nuevo objeto creado
FiguraVisual::FiguraVisual(Vector2f posicion, Vector2f dimensiones_figura, String direccion_textura, Escena* escena) {

	//Guarda la variable recibida en el atributo propio de la clase
	dimensiones = dimensiones_figura;

	//Llama a crear con los par�metros recibidos
	inicializacionInterna(direccion_textura, posicion, escena);

}

//////////////////////////////////////////////////////////////////

//Inicializacion Interna (Sprite): M�todo interno encargado de crear el objeto dentro del puntero, usando el Sprite y configurando sus propiedades
void FiguraVisual::inicializacionInterna(String direccion_textura, Vector2f posicion, Escena* escena) {

	//Carga la textura
	textura.loadFromFile(direccion_textura);

	//Crea el sprite en el puntero
	sprite = new Sprite();

	//Asigna textura, origen y posici�n al sprite
	sprite->setTexture(textura);
	sprite->setOrigin(dimensiones.x / 2, dimensiones.y / 2);
	sprite->setPosition(posicion);

	//Si la escena recibida no es nula...
	if (escena != nullptr) {

		//Adjunta el objeto a la escena
		this->adjuntarAEscena(escena);

	}
	else {

		//Env�a un mensaje a consola notificando que no se pudo enlazar el objeto
		cout << "[ERROR]: 'Sprite' intent� enlazarse a una escena que no existe" << endl;

	}

}

//////////////////////////////////////////////////////////////////

//Renderizar: Recibe un puntero a una ventana para poder pasar la directiva de dibujar en ella
void FiguraVisual::renderizar(RenderWindow* ventana) {

	//Si la ventana suministrada es nula...
	if (ventana == nullptr) {

		//Sale inmediatamente sin ejecutar directivas
		return;

	}

	//Directiva de dibujar usando el dato alojado en el puntero sprite
	ventana->draw(*sprite);

}

//Modificar Origen: M�todo que permite modificar o cambiar el origen del objeto con uno personalizado, usando el offset suministrado como par�metro
void FiguraVisual::modificarOrigen(Vector2f offset) {

	//Calcula el nuevo origen
	Vector2f origen_nuevo = { dimensiones.x / 2 + offset.x, dimensiones.y / 2 + offset.y };

	//Asigna el nuevo origen
	sprite->setOrigin(origen_nuevo);

}

//Rotar: Permite rotar la figura definiendo los grados como par�metro recibido. A�ade a la rotaci�n base del objeto (no la sobreescribe)
void FiguraVisual::rotar(float grados) {

	//A�ade a la rotaci�n base del objeto
	sprite->rotate(grados);

}

//Establecer Rotaci�n: Permite sobreescribir la rotaci�n del objeto con el par�metro recibido. Asigna la rotaci�n del objeto en lugar de a�adir sobre ella
void FiguraVisual::establecerRotacion(float grados) {

	sprite->setRotation(grados);

}

//////////////////////////////////////////////////////////////////

//Retornar Posici�n: Retorna un vector representando la posici�n del sprite
Vector2f FiguraVisual::retornarPosicion() {

	return sprite->getPosition();

}