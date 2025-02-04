#include "Arma.h"

//Constructor compuesto: Crea el arma en las coordenadas especificadas, añadiendola adicionalmente a la escena pasada por parámetro
Arma::Arma(Vector2f coordenadas, Escena* escena, int pixeles_por_metro) {

	//Llama a inicializar usando los parámetros recibidos
	inicializacionInterna(coordenadas, escena, pixeles_por_metro);

}

//////////////////////////////////////////////////////////////////

//Inicialización Interna: Método interno encargado de inicializar la clase usando los argumentos recibidos en el constructor
void Arma::inicializacionInterna(Vector2f coordenadas, Escena* escena, int unidad_conversion) {

	//Almacena las dimensiones de ambas partes
	Vector2f dimensiones_base = { 100.0f, 100.0f };
	Vector2f dimensiones_barril = { 250.0f, 100.0f };

	//Direccion de las texturas para el arma
	String directorio_textura_base = "assets/images/arma_base.png";
	String directorio_textura_barril = "assets/images/arma_barril.png";

	//Se crean los objetos dentro de sus respectivos espacios del arreglo de punteros, usando los datos previamente establecidos
	base = new FiguraVisual(coordenadas, dimensiones_base, directorio_textura_base, escena);
	barril = new FiguraVisual(coordenadas, dimensiones_barril, directorio_textura_barril, escena);

	//Cambia el origen de las figuras visuales para el arma
	barril->modificarOrigen({ -125.0f, 0.0f });

	//Llama a los métodos para adjuntar a escena el objeto y sus derivados
	adjuntarAEscena(escena);

}

//Disparar Ragdoll: Método que preconfigura y genera un ragdoll cuando el jugador dispara. Argumentos:
// 
// fuerza_impulso = vector de fuerza con el cual saldrá disparado el muñeco (Modificado por la distancia del cursor al cañon)
// unidad_conversion = la conversión de metros a pixeles del juego. Determinará el tamaño del ragdoll visualmente
// mundo = puntero al mundo físico del juego, donde se creará el ragdoll
// limite_aparicion = la cantidad máxima de ragdolls que pueden existir simultáneamente en la pantalla
// lista[] = la lista de punteros a ragdolls. En esta lista se almacena cada ragdoll nuevo y cuando el limite se supera, uno de ellos
// se borra para darle lugar al nuevo
// escena = La escena donde se adjuntará el ragdoll tras ser instanciado
void Arma::dispararRagdoll(Vector2f coordenadas_disparo, int unidad_conversion, b2World* mundo, int limite_aparicion, Ragdoll* lista[], Escena* escena) {

	//Si el mundo es nulo...
	if (mundo == nullptr) {

		//Notifica por consola que no se pudo instanciar el Ragdoll
		cout << "[ERROR]: No se pudo instanciar Ragdoll ya que el mundo recibido es invalido" << endl;

		//Sale del constructor evitando el código de inicialización
		return;

	}

	//Se asigna el valor de la reducción. Este es el valor encargado de decrementar la fuerza conforme más lejos esté
    //el cursor del usuario del centro del cañon, el cual es el punto de origen de los ragdolls
	float reduccion = 0.001f;

	//Calcula la exponencial usando la reducción junto a la distancia del cursor
	float fuerza_reducida = exp(reduccion * distancia_a_cursor);

	//Se multiplica la fuerza normal por la reducida, otorgando la fuerza final que será usada para disparar el cañon
	Vector2f fuerza_final = fuerza_total * fuerza_reducida;

	//Guarda el tamaño de cada parte del muñeco
	Vector2f dimensiones_componentes[6];
	dimensiones_componentes[0] = { 25.0f, 25.0f }; //Dimensiones: Cabeza
	dimensiones_componentes[1] = { 50.0f, 62.5f }; //Dimensiones: Cuerpo

	//Bucle de 4 iteraciones que recorre desde índice "2" hasta índice "5" para fijar el tamaño (Brazos y Piernas)
	for (int i = 2; i < 6; i++) {

		//Establece las dimensiones para cada índice
		dimensiones_componentes[i] = { 20.0f, 50.0f }; //Dimensiones: Brazos y Piernas

	}

	////////////////////////////////////////////////////////////////////////////

	//Almacena la posicion centro y en base a ella configura las posiciones iniciales para cada parte del cuerpo
	Vector2f posicion_centro = coordenadas_disparo;
	Vector2f posiciones_componentes[6];
	posiciones_componentes[0] = { posicion_centro.x, posicion_centro.y - 50.0f }; //Posicion: Cabeza
	posiciones_componentes[1] = posicion_centro; //Posicion: Cuerpo
	posiciones_componentes[2] = { posicion_centro.x - 37.5f, posicion_centro.y - 12.5f }; //Posicion: Brazo Izquierdo
	posiciones_componentes[3] = { posicion_centro.x + 37.5f, posicion_centro.y - 12.5f }; //Posicion: Brazo Derecho
	posiciones_componentes[4] = { posicion_centro.x - 25.0f, posicion_centro.y + 62.5f }; //Posicion: Pierna Izquierda
	posiciones_componentes[5] = { posicion_centro.x + 25.0f, posicion_centro.y + 62.5f }; //Posicion: Pierna Derecha

	////////////////////////////////////////////////////////////////////////////

	//Itera sobre el arreglo de ragdolls
	for (int i = 0; i < limite_aparicion; i++) {

		//Si el puntero sobre el que se itera no es nulo...
		if (lista[i] != nullptr) {

			//Pasa a la siguiente iteración del bucle (Ya que se requiere un puntero vacío para crear el objeto)
			continue;

		}

		//Si el mundo recibido no es nulo...
		if (mundo != nullptr) {

			//Inserta el nuevo objeto de ragdoll en el puntero vacío encontrado
			lista[i] = new Ragdoll(dimensiones_componentes, posiciones_componentes, mundo, unidad_conversion, escena);

		}

		//Convierte el "Vector2f" recibido a "b2Vec2" para ser suministrado como parámetro en la siguiente función.
		//Esto debido a que el método de aplicar fuerza trabaja con vectores de Box2D
		b2Vec2 fuerza_fisica = { fuerza_final.x, fuerza_final.y };

		//Le aplica la fuerza al objeto ya creado, dicha fuerza se recibe al llamar la función de creación
		lista[i]->aplicarFuerza(fuerza_fisica, 1);

		//Rompe el bucle para evitar crear múltiples ragdolls
		break;

	}

}

//Método encargado de definir y modificar las variables que forman parte del disparo del cañon, asi sea rotar el arma, obtener la
//distancia entre el cursor y la base del cañon, o también hacer las operaciones que definirán la fuerza de disparo. Recibe un modificador
//de impulso como parámetro, el cual aportará al impulso final para disparar el objeto
void Arma::actualizarSistemaApuntado(float multiplicador_fuerza, Vector2i posicion_cursor) {

	FiguraVisual riel_arma_activa = obtenerRielDisparo();

	//Se actualiza la variable que almacena la distancia entre el cañon y el cursor
	distancia_a_cursor = hypot(riel_arma_activa.retornarPosicion().x - posicion_cursor.x, riel_arma_activa.retornarPosicion().y - posicion_cursor.y);

	////////////////////////////////////

	//CALCULO DEL ANGULO DEL ARMA

	//Almacena la distancia entre el cursor y la base del arma
	float distancia_x = posicion_cursor.x - riel_arma_activa.retornarPosicion().x;
	float distancia_y = posicion_cursor.y - riel_arma_activa.retornarPosicion().y;

	//Almacena el nuevo angulo, calculando la distancia entre ambos puntos y convirtiendo los radianes a angulo
	float nuevo_angulo = atan2(distancia_x, distancia_y) * (180.0f / b2_pi);

	//Finalmente cambia el angulo a negativo y le añade 90 grados para coordinar la rotación con el cursor
	angulo = -nuevo_angulo + 90.0f;

	//Fija la nueva rotación
	riel_arma_activa.establecerRotacion(angulo);

	////////////////////////////////////

	//CALCULO DE LA FUERZA DE DISPARO

	//Variables de vector para almacenar la direccion de disparo tanto cruda como normalizada
	Vector2f direccion_disparo = Vector2f(posicion_cursor) - riel_arma_activa.retornarPosicion();
	Vector2f direccion_normalizada = direccion_disparo / sqrt(direccion_disparo.x * direccion_disparo.x + direccion_disparo.y * direccion_disparo.y);

	//La fuerza se define multiplicando la nueva dirección transformada con la potencia de impulso suministrada al llamar a la función
	fuerza_total = { direccion_normalizada * multiplicador_fuerza };

}

//Actualizar Elementos: Llama a actualizar a cada elemento que requiera actualización dentro de la clase
void Arma::actualizarElementos(float potencia_impulso, Vector2i posicion_cursor) {

	//Si alguno de los dos componentes del arma es nulo...
	if (base == nullptr || barril == nullptr) {

		//Sale inmediatamente, omitiendo la actualización
		return;

	}

	//Llama a actualizar el sistema de apuntado usando los parámetros recibidos
	actualizarSistemaApuntado(potencia_impulso, posicion_cursor);

}

//Dibujar Elementos: Método simple que llama a renderizar desde cada objeto que debe dibujarse contenido en la clase
void Arma::dibujarElementos(RenderWindow* ventana) {

	//Ejecuta llamadas a renderizar para cada parte del arma, usando la ventana recibida
	base->renderizar(ventana);
	barril->renderizar(ventana);

}

//////////////////////////////////////////////////////////////////

//Obtener Riel de Disparo: Retorna la figura que representa al cañon para disparar (Riel de tiro)
FiguraVisual Arma::obtenerRielDisparo() {

	return *barril;

}