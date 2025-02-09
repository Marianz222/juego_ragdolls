#include "Nivel.h"

//Constructor principal: Crea un nivel usando la unidad de conversión de pixeles a metros y el mundo físico suministrados por parámetro
Nivel::Nivel(Vector2f ubicacion_arma, string id, int unidad_conversion, Vector2i dimensiones_ventana) {

	//Llama a la inicializacion con los datos recibidos
	inicializacionInterna(id, ubicacion_arma, unidad_conversion, dimensiones_ventana);

	//Establece la escena como activa por defecto
	activa = true;

}

//Constructor secundario: Crea el nivel usando los mismos valores que el principal, pero con la diferencia de que permite definir si
//el nivel se instancia como 'activo' o 'inactivo'
Nivel::Nivel(Vector2f ubicacion_arma, string id, int unidad_conversion, Vector2i dimensiones_ventana, bool activo) {

	//Llama a la inicializacion con los datos recibidos
	inicializacionInterna(id, ubicacion_arma, unidad_conversion, dimensiones_ventana);

	//Establece la actividad de la escena usando la bandera recibida
	activa = activo;

}

//////////////////////////////////////////////////////////////////

//Inicializacion Interna: Método interno encargado de instanciar los elementos del objeto, creando el mundo, el arma, la sala y el HUD
void Nivel::inicializacionInterna(String id, Vector2f ubicacion_arma, int unidad_conversion, Vector2i dimensiones_ventana) {

	//Se establece la gravedad y se suministra al mundo físico para su creación
	gravedad = { 0.0f, 0.06f };
	mundo = new b2World(gravedad);

	//Asigna el valor recibido al atributo local
	identificador = id;

	//Crea una nueva arma usando los parámetros recibidos
	arma = new Arma(ubicacion_arma, this, unidad_conversion);

	//Llama a la creación de los bordes del nivel
	crearSala(unidad_conversion, dimensiones_ventana);

	//Llama a la creación del heads-up display (interfaz del nivel)
	crearHUD(dimensiones_ventana);

}

//////////////////////////////////////////////////////////////////

//Crear Sala: Método que llena los punteros a elementos con valores, instancia las 2 paredes y los dos techos
void Nivel::crearSala(int unidad_conversion, Vector2i dimensiones_ventana) {

	//Guarda el tamaño de una pared y un suelo, usado para generar los 4 objetos
	Vector2f dimensiones_suelo = { float(dimensiones_ventana.x), 50.0f };
	Vector2f dimensiones_pared = { 50.0f, float(dimensiones_ventana.y) };

	//Directorio de la textura utilizada
	String directorio_textura = "assets/images/ladrillos_piedra.png";

	//Pequeño arreglo de posiciones para el centro de la ventana en x e y, dividiendolo por la cantidad de pixeles por metro
	float posicion_central[2] { dimensiones_ventana.x / 2, dimensiones_ventana.y / 2 };

	//Creación de los delimitantes de la simulación
	paredes[0] = new Poligono(directorio_textura, dimensiones_suelo, {posicion_central[0], 1050.0f}, 0.2f, 0.4f, mundo, b2BodyType::b2_staticBody, unidad_conversion); //Suelo
	paredes[1] = new Poligono(directorio_textura, dimensiones_suelo, {posicion_central[0], 25.0f}, 0.2f, 0.4f, mundo, b2BodyType::b2_staticBody, unidad_conversion); //Techo
	paredes[2] = new Poligono(directorio_textura, dimensiones_pared, {25.0f, posicion_central[1]}, 0.2f, 0.4f, mundo, b2BodyType::b2_staticBody, unidad_conversion); //Pared izquierda
	paredes[3] = new Poligono(directorio_textura, dimensiones_pared, {1920.0f, posicion_central[1]}, 0.2f, 0.4f, mundo, b2BodyType::b2_staticBody, unidad_conversion); //Pared derecha

}

//Crear HUD (Heads-Up Display): Encargado de establecer las propiedades del texto perteneciente al HUD del juego (Contador Ragdolls y Puntos)
void Nivel::crearHUD(Vector2i dimensiones_ventana) {

	//Instancia los botones, usando las dimensiones de la ventana y un offset para calcular sus posiciones, y pasando null para el texto
	botones[0] = new GUIBoton({ float(dimensiones_ventana.x) / 2 - 100.0f, 100.0f }, {0.6f, 0.6f}, nullptr, TipoSprite::SALIR, this); //Botón de Salir al Menú
	botones[1] = new GUIBoton({ float(dimensiones_ventana.x) / 2, 100.0f }, { 0.6f, 0.6f }, nullptr, TipoSprite::REINICIAR, this); //Botón de Reinicar el Nivel
	botones[2] = new GUIBoton({ float(dimensiones_ventana.x) / 2 + 100.0f, 100.0f }, { 0.6f, 0.6f }, nullptr, TipoSprite::AVANZAR, this); //Botón de Avanzar al siguiente Nivel
	
	//Desactiva el botón 2, que es el que se activará tras completar cada nivel
	botones[2]->encender(false);

	//Establece el texto por defecto para los contadores de ragdolls y puntaje
	contadores[0] = new GUITexto({float(dimensiones_ventana.x) - 175.0f, 75.0f}, "Ragdolls: N/A", 32, Color::White, this);
	contadores[1] = new GUITexto({float(dimensiones_ventana.x) - 175.f, 125.0f}, "Puntos: N/A", 32, Color::White, this);

}

//Crear Arma: Método que crea y coloca el arma en el nivel. Cada nivel requiere un arma para funcionar, y no pueden existir múltiples.
//No se llama en el constructor, por lo que hay que explícitamente llamarlo con los argumentos para crear el arma (Para permitir crear
//el arma en posiciones diferentes para cada nivel si se requiere)
void Nivel::crearArma(Vector2f coordenadas, int unidad_conversion) {

	//Se crea el arma con los argumentos recibidos
	arma = new Arma(coordenadas, this, unidad_conversion);

}

//Insertar Obstaculo: Permite crear y añadir un nuevo obstáculo al nivel, se utiliza este enfoque ya que no se puede preconfigurar la
//cantidad de obstaculos del nivel sin utilizar múltiples clases derivadas. Argumentos:
// - dimensiones = vector para el tamaño del obstáculo
// - coordenadas = vector de posición
// - mundo = puntero al mundo físico donde se alojará el objeto
// - color = el color del obstáculo
// - tipo = el tipo de respuesta a físicas del objeto (0 dinámico, 1 estático o 2 cinemático)
// - pixeles_por_metro = la unidad de conversión entre pixeles y metros
void Nivel::insertarObstaculo(String directorio_textura, Vector2f dimensiones, Vector2f coordenadas, float friccion, float restitucion, b2World* mundo, b2BodyType tipo, int pixeles_por_metro) {

	//Itera sobre el arreglo de punteros a poligonos...
	for (int i = 0; i < OBSTACULOS_MAXIMOS; i++) {

		//Si el objeto sobre el que se está iterando no es nulo
		if (obstaculos[i] != nullptr) {

			//Continua al siguiente ciclo del for, omitiendo este iterador ya que contiene un poligono ya creado
			continue;

		}

		//Crea un nuevo poligono usando los datos recibidos como parámetro, además lo adjunta a la escena de la clase actual (Este nivel)
		obstaculos[i] = new Poligono(directorio_textura, dimensiones, coordenadas, friccion, restitucion, mundo, tipo, pixeles_por_metro, this);

		break;

	}

}

//Insertar Punto de Control: Recibe las coordenadas por parámetro, y crea un punto de control en dicha posición. Lo aloja en el primer
//espacio vacío que encuentre dentro del arreglo de punteros a punto de control. Si no hay espacio vacío, se omite la creación
void Nivel::insertarPuntoControl(Vector2f coordenadas) {

	//Itera sobre el arreglo de punteros a punto de control...
	for (int i = 0; i < PUNTOS_CONTROL_MAXIMOS; i++) {

		//Si el objeto sobre el que se está iterando es nulo...
		if (puntos_control[i] != nullptr) {

			//Pasa a la siguiente iteración sin ejecutar el resto del código, ya que hay un punto de control creado
			continue;

		}

		//Crea un nuevo punto de control recibiendo las coordenadas como parámetro, y asignando la escena como la instancia de esta clase
		puntos_control[i] = new PuntoControl(coordenadas, this);

		//Sale del bucle para limitar la creación de puntos a solo uno por llamada
		break;

	}

}

//Revisar Puntos de Control Activados: Retorna "true" si todos los puntos del nivel fueron activados.
bool Nivel::revisarPuntosControlActivados() {

	//Bucle que itera sobre todos los puntos de control contenidos en el arreglo
	for (int i = 0; i < PUNTOS_CONTROL_MAXIMOS; i++) {

		//Si el punto de control iterador es nulo...
		if (puntos_control[i] == nullptr) {

			//Omite la ejecución y pasa a la siguiente iteración
			continue;

		}

		//Si el punto de control iterador no fue activado aún...
		if (!puntos_control[i]->fueActivado()) {

			//Retorna falso: Los puntos no fueron activados en su totalidad
			return false;

		}

	}

	//Retorna verdadero: Todos los puntos fueron activados
	return true;

}

//Obtener Boton: Devuelve el botón correspondiente al espacio 'indice' del arreglo de punteros a boton.
GUIBoton* Nivel::obtenerBoton(int indice) {

	return botones[indice];

}

//Insertar Enlace: Permite insertar enlaces independientes en el nivel. Un enlace en el nivel puede conectar 2 obstáculos entre sí, determinando
//el tipo de joint usado mediante el valor enumerativo "tipo" recibido. Sus argumentos son ambos objetos a conectar, ambas coordenadas donde se conectará
//cada objeto, el mundo donde se creará el enlace y la cantidad de pixeles por metro para cálculos visuales
void Nivel::insertarEnlace(b2JointType tipo, b2Vec2 eje_prismatico, Poligono* objeto1, Poligono* objeto2, b2Vec2 coordenadas_ancla1, b2Vec2 coordenadas_ancla2, b2World* mundo, int unidad_conversion) {

	//Itera sobre el arreglo de punteros a enlace...
	for (int i = 0; i < ENLACES_MAXIMOS; i++) {

		//Si el enlace sobre el que se está iterando es nulo...
		if (enlaces[i] != nullptr) {

			//Pasa a la siguiente iteración sin ejecutar el resto del código, ya que hay un enlace creado en esta posición
			continue;

		}

		//Crea un nuevo enlace recibiendo los parámetros necesarios, y usando este nivel como la escena objetivo
		enlaces[i] = new Enlace(tipo, eje_prismatico, objeto1, objeto2, coordenadas_ancla1, coordenadas_ancla2, mundo, unidad_conversion, this);

		//Sale del bucle para limitar la creación de enlaces a solo uno por llamada
		break;

	}

}

/////////////////////////////////////////////////////////////

//Retornar Arma: Devuelve el arma del nivel. Utilizado para determinar qué arma disparar en la lógica de juego principal
Arma* Nivel::retornarArma() {

	//Retorna el arma de la clase
	return arma;

}

//Retornar Poligono: Devuelve un puntero al poligono contenido en la posición "indice" del arreglo de obstáculos
Poligono* Nivel::retornarObstaculo(int indice) {

	//Devuelve el objeto alojado en la ubicación del indice
	return obstaculos[indice];

}

//Retornar Punto de Control: Devuelve un puntero al punto de control contenido en la posición "indice" del arreglo
PuntoControl* Nivel::retornarPuntoControl(int indice) {

	return puntos_control[indice];

}

//Retornar Pared: Usa el indice recibido por parámetro para retornar la pared correspondiente a esa posición dentro del arreglo de paredes
Poligono* Nivel::retornarPared(int indice) {

	return paredes[indice];

}

//Retornar Enlace: Usa el indice
Enlace* Nivel::retornarEnlace(int indice) {

	return enlaces[indice];

}

//Retornar Obstaculos Maximos: Devuelve el número de obstáculos máximos que pueden existir en el nivel (Igual al tamaño del arreglo)
int Nivel::retornarObstaculosMaximos() {

	return OBSTACULOS_MAXIMOS;

}

//Retornar Puntos de Control Máximos: Devuelve el número de puntos de control máximos que pueden existir en el nivel (Tamaño arreglo)
int Nivel::retornarPuntosControlMaximos() {

	return PUNTOS_CONTROL_MAXIMOS;

}

//Retornar Botones Máximos: Retorna la cantidad máxima de botones que pueden existir en el nivel
int Nivel::retornarBotonesMaximos() {

	return BOTONES_MAXIMOS;

}

/////////////////////////////////////////////////////////////

//Depurar Estado Obstáculos: Método de depuración que imprime "valid" para cada obstáculo con dato alojado o "null" para cada puntero
//nulo contenido dentro del arreglo de punteros a poligonos
void Nivel::depurarEstadoObstaculos() {

	//Crea un arreglo de texto para almacenar el valor de cada iterador
	string estados[OBSTACULOS_MAXIMOS];

	//Cadena base de texto
	cout << "Estado Obstaculos: ";

	//Recorre el arreglo de obstáculos
	for (int i = 0; i < OBSTACULOS_MAXIMOS; i++) {

		//Si el obstáculo es nulo...
		if (obstaculos[i] == nullptr) {

			//Asigna "null" como el estado del iterador
			estados[i] = "null";

		}
		else {

			//Asigna "valid" como el estado del iterador
			estados[i] = "valid";

		}

		//Separa cada entrada de texto al iterar
		cout << estados[i] << ", ";

	}

}

/////////////////////////////////////////////////////////////

//Override de "Restablecer": La sobreescritura del método permite eliminar los objetos del nivel, y dejarlo vacío para poder re-crearse
//Cuando el jugador reinica el nivel o sale al menú
void Nivel::restablecer() {

	//Bucle que itera sobre las 4 paredes
	for (int i = 0; i < 4; i++) {

		//Si la pared iteradora es nulo...
		if (paredes[i] == nullptr) {

			//Omite la ejecución y pasa a la siguiente iteración
			continue;

		}

		//Destruye la pared
		paredes[i]->destruir(obtenerMundoFisico());

	}

	//Bucle que itera sobre los enlaces
	for (int i = 0; i < ENLACES_MAXIMOS; i++) {

		//Si el enlace iterador es nulo...
		if (enlaces[i] == nullptr) {

			//Omite la ejecución
			continue;

		}

		//Destruye el enlace iterador
		enlaces[i]->destruir(obtenerMundoFisico());

		//Nulifica el puntero
		enlaces[i] = nullptr;

	}

	//Bucle que itera sobre los obstáculos
	for (int i = 0; i < OBSTACULOS_MAXIMOS; i++) {

		//Si el obstáculo iterador es nulo...
		if (obstaculos[i] == nullptr) {

			//Omite la ejecución
			continue;

		}

		//Destruye el obstáculo iterador
		obstaculos[i]->destruir(obtenerMundoFisico());

		//Nulifica el puntero
		obstaculos[i] = nullptr;
 
	}

	//Bucle que itera sobre los puntos de control
	for (int i = 0; i < PUNTOS_CONTROL_MAXIMOS; i++) {

		//Si el punto iterador es nulo...
		if (puntos_control[i] == nullptr) {

			//Omite la ejecución
			continue;

		}

		//Destruye el punto iterador
		delete puntos_control[i];

		//Nulifica el puntero
		puntos_control[i] = nullptr;

	}

}

//Override de "Actualizar Elementos Alojados":
void Nivel::actualizarElementosAlojados(int unidad_conversion, float potencia_disparo, int ragdolls_activos, int ragdolls_maximos, int puntaje, Vector2i posicion_cursor) {

	//Sale del método si la escena está desactivada
	if (!this->estaActiva()) { return; };

	//Bucle que itera sobre el arreglo de paredes
	for (int i = 0; i < 4; i++) {

		//Directiva de dibujar la pared iteradora
		paredes[i]->actualizar(unidad_conversion);

	}

	//Bucle que itera sobre el arreglo de punteros a obstaculo...
	for (int k = 0; k < OBSTACULOS_MAXIMOS; k++) {

		//Si el obstaculo iterador es nulo...
		if (obstaculos[k] == nullptr) {

			//Omite la iteración actual y pasa a la siguiente (No dibuja el elemento)
			continue;

		}

		//Directiva de dibujar el obstáculo iterador
		obstaculos[k]->actualizar(unidad_conversion);

	}

	//Bucle que itera sobre el arreglo de punteros a enlace...
	for (int j = 0; j < ENLACES_MAXIMOS; j++) {

		//Si el obstaculo iterador es nulo...
		if (enlaces[j] == nullptr) {

			//Omite la iteración actual y pasa a la siguiente (No dibuja el elemento)
			continue;

		}

		//Directiva de dibujar el obstáculo iterador
		enlaces[j]->actualizar(unidad_conversion);

	}

	//Crea las cadenas de texto para el hud y las almacena
	String texto_contador_ragdoll = String("Ragdolls: " + to_string(ragdolls_activos) + '/' + to_string(ragdolls_maximos));
	String texto_contador_puntaje = String("Puntos: " + to_string(puntaje));

	//Actualiza el texto de los contadores, usando el nuevo texto generado
	contadores[0]->modificarTexto(texto_contador_ragdoll);
	contadores[1]->modificarTexto(texto_contador_puntaje);

	//Ver si el arma necesita actualizarse
	arma->actualizarElementos(potencia_disparo, posicion_cursor);

	//Si todos los puntos de control fueron activados...
	if (revisarPuntosControlActivados()) {

		//Si el botón #3 (Boton de Avanzar al siguiente Nivel) no es nulo...
		if (botones[2] != nullptr) {

			//Si el botón no está encendido...
			if (!botones[2]->estaEncendido()) {

				//Enciende el botón, permitiendo la interacción con él
				botones[2]->encender(true);

			}

		}

	}
	else {

		//Apaga el botón, ya que solo se enciende si todos los puntos fueron activados
		botones[2]->encender(false);

	}

}

//Override de "Renderizar Elementos Alojados"
void Nivel::renderizarElementosAlojados(RenderWindow* ventana) {

	//Sale del método si la escena está desactivada o si la ventana es nula
	if (!this->estaActiva() || ventana == nullptr) { return; };

	//Bucle que itera sobre el arreglo de paredes
	for (int i = 0; i < 4; i++) {

		//Directiva de dibujar la pared iteradora
		paredes[i]->renderizar(ventana);

	}

	//Bucle que itera sobre el arreglo de apuntadores a punto de control...
	for (int j = 0; j < PUNTOS_CONTROL_MAXIMOS; j++) {

		//Si el punto de control iterador es nulo...
		if (puntos_control[j] == nullptr) {

			//Omite la iteración actual y pasa a la siguiente (No dibuja el elemento)
			continue;

		}

		//Directiva de dibujar el punto de control iterador
		puntos_control[j]->renderizar(ventana);

	}

	//Bucle que itera sobre el arreglo de punteros a obstaculo...
	for (int k = 0; k < OBSTACULOS_MAXIMOS; k++) {

		//Si el obstaculo iterador es nulo...
		if (obstaculos[k] == nullptr) {

			//Omite la iteración actual y pasa a la siguiente (No dibuja el elemento)
			continue;

		}

		//Directiva de dibujar el obstáculo iterador
		obstaculos[k]->renderizar(ventana);

	}

	//Bucle que itera sobre el arreglo de punteros a enlace...
	for (int s = 0; s < ENLACES_MAXIMOS; s++) {

		//Si el enlace iterador es nulo...
		if (enlaces[s] == nullptr) {

			//Omite la iteración actual y pasa a la siguiente (No dibuja)
			continue;

		}

		//Directiva de dibujar el enlace iterador
		enlaces[s]->renderizar(ventana);

	}

	//Directiva de dibujar el arma y sus componentes
	arma->dibujarElementos(ventana);

	//Bucle que itera sobre los elementos del HUD
	for (int i = 0; i < 2; i++) {

		//Llama al dibujado de los elementos HUD en la ventana
		contadores[i]->dibujarElemento(ventana);

	}

	//Bucle que itera sobre el arreglo de botones
	for (int i = 0; i < BOTONES_MAXIMOS; i++) {

		//Si el botón iterador es nulo...
		if (botones[i] == nullptr) {

			//Omite el ciclo actual
			continue;

		}

		//Directiva de dibujar el boton y sus componentes
		botones[i]->dibujarElementos(ventana);

	}

}