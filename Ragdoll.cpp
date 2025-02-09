#include "Ragdoll.h"

//Constructor Principal: Recibe las dimensiones y posiciones para los 6 componentes, un mundo físico donde crear los cuerpos, un arreglo de color,
//un bool para determinar si el ragdoll será dinámico o estático, la escala de pixeles por metro y la escena donde el objeto y sus componentes serán creados
Ragdoll::Ragdoll(Vector2f dimensiones_poligono[6], Vector2f posicion[6], b2World* mundo, int pixeles_por_metro, Escena* escena) {

	//Si el mundo recibido es nulo...
	if (mundo == nullptr) {

		//Notifica por consola que no se puede instanciar el Ragdoll
		cout << "[ERROR]: No se puede instanciar Ragdoll debido a que el mundo recibido es invalido" << endl;

		//Sale del método actual
		return;

	}

	//Llamada a inicializar internamente usando los valores recibidos
	inicializacionInterna(dimensiones_poligono, posicion, mundo, pixeles_por_metro, escena);

}

//////////////////////////////////////////////////////////////////

//Inicialización Interna: Función interna que instancia y configura todos los atributos de la clase usando los valores recibidos
//desde los constructores
void Ragdoll::inicializacionInterna(Vector2f dimensiones_poligono[6], Vector2f posicion[6], b2World* mundo, int pixeles_por_metro, Escena* escena) {

	//Itera sobre cada objeto almacenado en el arreglo para insertar su nuevo elemento
	for (int i = 0; i < 6; i++) {

		//Genera los componentes del ragdoll a partir de los parámetros recibidos
		componentes[i] = new Poligono("assets/images/wool.png", dimensiones_poligono[i], posicion[i], 0.35f, 0.8f, mundo, b2BodyType::b2_dynamicBody, pixeles_por_metro, escena);

	}

	//Llamada a crear las juntas/enlaces
	crearEnlaces(mundo, pixeles_por_metro, escena);

	//Si la escena recibida no es nula...
	if (escena != nullptr) {

		//Adjunta el ragdoll a la escena recibida
		adjuntarAEscena(escena);

	}
	else {

		//Registra un mensaje por consola notificando que no se pudo adjuntar el objeto a la escena recibida
		cout << "[ERROR]: No se pudo instanciar el Ragdoll debido a que la escena recibida es invalida" << endl;

	}

}

//Renderizar: Método que se encarga de que los Poligonos componentes llamen a "renderizar", iterando sobre cada uno e iniciando la directiva
void Ragdoll::renderizar(RenderWindow* ventana) {

	//Si la ventana suministrada es nula...
	if (ventana == nullptr) {

		//Sale inmediatamente sin ejecutar directivas
		return;

	}

	//Itera sobre todos los elementos del ragdoll
	for (int i = 0; i < 6; i++) {

		//Si el componente iterador es nulo...
		if (componentes[i] == nullptr) {

			//Pasa a la siguiente iteración sin ejecutar nada
			continue;

		}

		//Llama a "renderizar" para cada componente
		componentes[i]->renderizar(ventana);

	}
	
	//Itera sobre todos los enlaces de tipo junta
	for (int i = 0; i < 5; i++) {

		//Si el enlace iterador es nulo...
		if (enlaces[i] == nullptr) {

			//Pasa a la siguiente iteración sin ejecutar nada
			continue;

		}

		//Llama a "renderizar" para cada junta
		enlaces[i]->renderizar(ventana);

	}

}

//Actualizar: Método que se encarga de ejecutar la actualización para cada componente del ragdoll
void Ragdoll::actualizar(int pixeles_por_metro) {

	//Itera sobre cada componente del ragdoll
	for (int i = 0; i < 6; i++) {

		//Si el componente iterador es nulo...
		if (componentes[i] == nullptr) {

			//Salta a la siguiente iteración del bucle, omitiendo la acción
			continue;

		}

		//Ejecuta la llamada a "actualizar"
		componentes[i]->actualizar(pixeles_por_metro);

	}

	//Itera sobre cada enlace
	for (int i = 0; i < 5; i++) {

		//Si el enlace iterador es nulo...
		if (enlaces[i] == nullptr) {

			//Salta a la siguiente iteración, omitiendo la acción
			continue;

		}

		//Ejecuta la llamada a "actualizar"
		enlaces[i]->actualizar(pixeles_por_metro);

	}

}

//Crear Enlaces: Método encargado de generar los enlaces usados para conectar las partes del ragdoll
void Ragdoll::crearEnlaces(b2World* mundo, int pixeles_por_metro, Escena* escena) {
	
	//Se crean los enlaces y se almacenan en su arreglo. Las coordenadas de anclaje se pasan por valor, mientras que los demás
	//valores se pasan por referencia. Cada linea contiene un comentario para determinar qué poligonos se unen
	enlaces[0] = new Enlace(b2JointType::e_revoluteJoint, componentes[1], componentes[0], { 0.0f, -0.7f }, { 0.0f, 0.2f }, mundo, pixeles_por_metro, escena); //Cuerpo a Cabeza
	enlaces[1] = new Enlace(b2JointType::e_revoluteJoint, componentes[1], componentes[2], { -0.42f, -0.7f }, { 0.12f, -0.45f }, mundo, pixeles_por_metro, escena); //Cuerpo a Brazo Izq.
	enlaces[2] = new Enlace(b2JointType::e_revoluteJoint, componentes[1], componentes[3], { 0.42f, -0.7f }, { -0.12f, -0.45f }, mundo, pixeles_por_metro, escena); //Cuerpo a Brazo Der.
	enlaces[3] = new Enlace(b2JointType::e_revoluteJoint, componentes[1], componentes[4], { -0.45f, 0.7f }, { 0.0f, -0.45f }, mundo, pixeles_por_metro, escena); //Cuerpo a Pierna Izq.
	enlaces[4] = new Enlace(b2JointType::e_revoluteJoint, componentes[1], componentes[5], { 0.45f, 0.7f }, { 0.0f, -0.45f }, mundo, pixeles_por_metro, escena); //Cuerpo a Pierna Der.

}

//Aplicar Fuerza: Método que aplica una fuerza a todas las partes del ragdoll
void Ragdoll::aplicarFuerza(b2Vec2 magnitud) {

	//Itera sobre los 6 componentes
	for (int i = 0; i < 6; i++) {

		//Aplica una fuerza al componente sobre el que se está iterando
		componentes[i]->aplicarFuerza(magnitud);

	}

}

//Aplicar Fuerza (2): Método que permite aplicar una fuerza a una única parte del ragdoll, usando la magnitud y el índice pasados por parámetro
void Ragdoll::aplicarFuerza(b2Vec2 magnitud, int indice_afectado) {

	//Aplica la fuerza al componente alojado en el índice afectado del arreglo
	componentes[indice_afectado]->aplicarFuerza(magnitud);

}

//Rotar: Método que rota el ragdoll cambiando los grados de rotación del cuerpo, el cual al estar conectado con las demás partes hará
//que todo el muñeco rote en dicha dirección
void Ragdoll::rotar(float grados) {

	//Aplica la modificación de rotación
	componentes[1]->modificarRotacion(grados);

}

//Destruir Componentes: Método que destruye los poligonos que conforman el ragdoll, usado para destruir de forma correcta el objeto
//Sin causar problemas de infracción de lectura
void Ragdoll::destruirComponentes(b2World* mundo) {

	//Recorre los 6 componentes del ragdoll...
	for (int i = 0; i < 6; i++) {

		//Elimina el componente iterador del mundo recibido
		componentes[i]->destruir(mundo);

	}

}

//Destruir Enlaces: Llama a la destrucción de las juntas contenidas en los objetos enlace. Recibe el mundo desde donde se llamará la
//eliminación
void Ragdoll::destruirEnlaces(b2World* mundo) {

	//Bucle que itera sobre todos los objetos de enlace
	for (int i = 0; i < 5; i++) {

		//Si el enlace iterador es nulo...
		if (enlaces[i] == nullptr) {

			//Continua con la siguiente iteración sin ejecutar código
			continue;

		}

		//Llama al método de destrucción desde el enlace iterador pasandole el mundo
		enlaces[i]->destruir(mundo);

	}


}

//////////////////////////////////////////////////////////////////

//Retornar Componente: Retorna un puntero a un componente del ragdoll, para ello se usa el índice suministrado por parámetro
Poligono* Ragdoll::retornarComponente(int indice) {

	//Retorna el componente usando el indice recibido
	return componentes[indice];

}
