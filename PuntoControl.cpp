#include "PuntoControl.h"

//Constructor principal: Toma coordenadas en forma de vector donde añadir el punto de control y un apuntador a la escena donde se alojará el objeto
PuntoControl::PuntoControl(Vector2f coordenadas, Escena* escena) {

	//Llama a la inicialización pasando los parámetros recibidos
	inicializacionInterna(coordenadas, escena);

}

//Inicialización Interna: Método interno que crea todos los elementos del objeto usando argumentos recibidos por el constructor
void PuntoControl::inicializacionInterna(Vector2f coordenadas, Escena* escena) {

	//Almacena los paths a las texturas del objeto
	String directorio_textura_base = "assets/images/punto_control.png";
	String directorio_textura_activacion = "assets/images/punto_control_activo.png";

	//Asigna ambas texturas usando el path almacenado
	textura_base.loadFromFile(directorio_textura_base);
	textura_activacion.loadFromFile(directorio_textura_activacion);

	//Asigna la textura base al sprite, su origen y su posición
	sprite.setTexture(textura_base);
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	sprite.setPosition(coordenadas);

	//Obtiene la caja de colisión del sprite y la guarda en el atributo
	caja_colision = sprite.getGlobalBounds();

	//Configura los atributos de la hitbox visual, independientemente de si se renderiza o no
	hitbox_depurado_visual.setSize({ sprite.getGlobalBounds().width, sprite.getGlobalBounds().height });
	hitbox_depurado_visual.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	hitbox_depurado_visual.setPosition(coordenadas);
	hitbox_depurado_visual.setFillColor(Color::Transparent);
	hitbox_depurado_visual.setOutlineColor(Color::White);
	hitbox_depurado_visual.setOutlineThickness(5.2f);

	//Si la escena recibida no es nula...
	if (escena != nullptr) {

		//Adjunta el objeto de la clase a la escena suministrada como parámetro
		this->adjuntarAEscena(escena);

	}
	else {

		//Envía un mensaje a consola notificando que no se pudo enlazar el objeto
		cout << "[ERROR]: 'Punto de Control' intentó enlazarse a una escena que no existe" << endl;

	}

}

//Activar: Recibe un estado booleano que se usa para activar o desactivar el punto de control
void PuntoControl::activar(bool estado) {

	//Cambia el estado de activación del objeto
	activado = estado;

	//Llama a actualizar las texturas
	actualizarTexturas(estado);

}

//Renderizar: Recibe un puntero a ventana donde se dibujará el sprite del objeto
void PuntoControl::renderizar(RenderWindow* ventana) {

	//Llama a dibujar usando el sprite de la clase
	ventana->draw(sprite);

	//DEBUG
	//ventana->draw(hitbox_depurado_visual);

}

//Actualizar Textura: Recibe "true" si la textura debe ser de activación, y "false" si debe ser normal
//Intercambia las texturas del sprite del objeto dependiendo la bandera recibida
void PuntoControl::actualizarTexturas(bool estado) {

	//Si el estado es "activado"
	if (estado) {

		//Asigna la textura de activación al sprite
		sprite.setTexture(textura_activacion);

	}
	else {

		//Asigna la textura normal
		sprite.setTexture(textura_base);

	}

}

//Asignar Activación Indirecta: Se usa para establecer la bandera de "activado indirectamente". Si esta bandera es true, quiere decir
//que el punto de control fue activado por un objeto dinámico que no fue un ragdoll del jugador
void PuntoControl::asignarActivacionIndirecta(bool estado) {

	//Asigna el nuevo valor del atributo
	activado_indirectamente = estado;

}

//Retornar Posición: Devuelve las coordenadas del sprite
Vector2f PuntoControl::retornarPosicion() {

	return sprite.getPosition();

}

//Retornar Sprite: Devuelve el sprite del objeto
Sprite PuntoControl::retornarSprite() {

	return sprite;

}

//Retornar Hitbox: Devuelve la hitbox (caja colisión) del sprite
FloatRect PuntoControl::retornarHitbox() {

	return caja_colision;

}

//Fue Activado: Devuelve "true" si el objeto ya fue activado (El punto se activa si un ragdoll u objeto dinámico lo tocó)
bool PuntoControl::fueActivado() {

	return activado;

}

//Fue Activado Indirectamente: Devuelve "true" si el punto fue activado por un objeto dinámico en lugar de un ragdoll del jugador
bool PuntoControl::fueActivadoIndirectamente() {

	return activado_indirectamente;

}

//Revisar Colisiones: Método que chequea colisiones con la hitbox suministrada por parámetro. Si la hitbox recibida y la del punto
//están en contacto, retornará "true"
bool PuntoControl::revisarColisiones(FloatRect colisionador_ajeno) {

	//Si la caja de colisión del punto está intersectando con la ajena...
	if (caja_colision.intersects(colisionador_ajeno)) {

		//Devuelve true: Hay colisión
		return true;

	}

	//No hay colisión, devuelve false
	return false;

}