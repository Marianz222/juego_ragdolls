#include "Ragdoll.h"

//Constructor Principal: Recibe las dimensiones y posiciones para los 6 componentes, un mundo f�sico donde crear los cuerpos, un arreglo de color,
//un bool para determinar si el ragdoll ser� din�mico o est�tico, la escala de pixeles por metro y la escena donde el objeto y sus componentes ser�n creados
Ragdoll::Ragdoll(Vector2f dimensiones_poligono[6], Vector2f posicion[6], b2World* mundo, int pixeles_por_metro, Escena* escena) {

	//Si el mundo recibido es nulo...
	if (mundo == nullptr) {

		//Notifica por consola que no se puede instanciar el Ragdoll
		cout << "[ERROR]: No se puede instanciar Ragdoll debido a que el mundo recibido es invalido" << endl;

		//Sale del m�todo actual
		return;

	}

	//Llamada a inicializar internamente usando los valores recibidos
	inicializacionInterna(dimensiones_poligono, posicion, mundo, pixeles_por_metro, escena);

}

//////////////////////////////////////////////////////////////////

//Inicializaci�n Interna: Funci�n interna que instancia y configura todos los atributos de la clase usando los valores recibidos
//desde los constructores
void Ragdoll::inicializacionInterna(Vector2f dimensiones_poligono[6], Vector2f posicion[6], b2World* mundo, int pixeles_por_metro, Escena* escena) {

	//Itera sobre cada objeto almacenado en el arreglo para insertar su nuevo elemento
	for (int i = 0; i < 6; i++) {

		//Genera los componentes del ragdoll a partir de los par�metros recibidos
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

//Renderizar: M�todo que se encarga de que los Poligonos componentes llamen a "renderizar", iterando sobre cada uno e iniciando la directiva
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

			//Pasa a la siguiente iteraci�n sin ejecutar nada
			continue;

		}

		//Llama a "renderizar" para cada componente
		componentes[i]->renderizar(ventana);

	}
	
	//Itera sobre todos los enlaces de tipo junta
	for (int i = 0; i < 5; i++) {

		//Si el enlace iterador es nulo...
		if (enlaces[i] == nullptr) {

			//Pasa a la siguiente iteraci�n sin ejecutar nada
			continue;

		}

		//Llama a "renderizar" para cada junta
		enlaces[i]->renderizar(ventana);

	}

}

//Actualizar: M�todo que se encarga de ejecutar la actualizaci�n para cada componente del ragdoll
void Ragdoll::actualizar(int pixeles_por_metro) {

	//Itera sobre cada componente del ragdoll
	for (int i = 0; i < 6; i++) {

		//Si el componente iterador es nulo...
		if (componentes[i] == nullptr) {

			//Salta a la siguiente iteraci�n del bucle, omitiendo la acci�n
			continue;

		}

		//Ejecuta la llamada a "actualizar"
		componentes[i]->actualizar(pixeles_por_metro);

	}

	//Itera sobre cada enlace
	for (int i = 0; i < 5; i++) {

		//Si el enlace iterador es nulo...
		if (enlaces[i] == nullptr) {

			//Salta a la siguiente iteraci�n, omitiendo la acci�n
			continue;

		}

		//Ejecuta la llamada a "actualizar"
		enlaces[i]->actualizar(pixeles_por_metro);

	}

}

//Crear Enlaces: M�todo encargado de generar los enlaces usados para conectar las partes del ragdoll
void Ragdoll::crearEnlaces(b2World* mundo, int pixeles_por_metro, Escena* escena) {
	
	//Se crean los enlaces y se almacenan en su arreglo. Las coordenadas de anclaje se pasan por valor, mientras que los dem�s
	//valores se pasan por referencia. Cada linea contiene un comentario para determinar qu� poligonos se unen
	enlaces[0] = new Enlace(b2JointType::e_revoluteJoint, componentes[1], componentes[0], { 0.0f, -0.7f }, { 0.0f, 0.2f }, mundo, pixeles_por_metro, escena); //Cuerpo a Cabeza
	enlaces[1] = new Enlace(b2JointType::e_revoluteJoint, componentes[1], componentes[2], { -0.42f, -0.7f }, { 0.12f, -0.45f }, mundo, pixeles_por_metro, escena); //Cuerpo a Brazo Izq.
	enlaces[2] = new Enlace(b2JointType::e_revoluteJoint, componentes[1], componentes[3], { 0.42f, -0.7f }, { -0.12f, -0.45f }, mundo, pixeles_por_metro, escena); //Cuerpo a Brazo Der.
	enlaces[3] = new Enlace(b2JointType::e_revoluteJoint, componentes[1], componentes[4], { -0.45f, 0.7f }, { 0.0f, -0.45f }, mundo, pixeles_por_metro, escena); //Cuerpo a Pierna Izq.
	enlaces[4] = new Enlace(b2JointType::e_revoluteJoint, componentes[1], componentes[5], { 0.45f, 0.7f }, { 0.0f, -0.45f }, mundo, pixeles_por_metro, escena); //Cuerpo a Pierna Der.

}

//Aplicar Fuerza: M�todo que aplica una fuerza a todas las partes del ragdoll
void Ragdoll::aplicarFuerza(b2Vec2 magnitud) {

	//Itera sobre los 6 componentes
	for (int i = 0; i < 6; i++) {

		//Aplica una fuerza al componente sobre el que se est� iterando
		componentes[i]->aplicarFuerza(magnitud);

	}

}

//Aplicar Fuerza (2): M�todo que permite aplicar una fuerza a una �nica parte del ragdoll, usando la magnitud y el �ndice pasados por par�metro
void Ragdoll::aplicarFuerza(b2Vec2 magnitud, int indice_afectado) {

	//Aplica la fuerza al componente alojado en el �ndice afectado del arreglo
	componentes[indice_afectado]->aplicarFuerza(magnitud);

}

//Rotar: M�todo que rota el ragdoll cambiando los grados de rotaci�n del cuerpo, el cual al estar conectado con las dem�s partes har�
//que todo el mu�eco rote en dicha direcci�n
void Ragdoll::rotar(float grados) {

	//Aplica la modificaci�n de rotaci�n
	componentes[1]->modificarRotacion(grados);

}

//Destruir Componentes: M�todo que destruye los poligonos que conforman el ragdoll, usado para destruir de forma correcta el objeto
//Sin causar problemas de infracci�n de lectura
void Ragdoll::destruirComponentes(b2World* mundo) {

	//Recorre los 6 componentes del ragdoll...
	for (int i = 0; i < 6; i++) {

		//Elimina el componente iterador del mundo recibido
		componentes[i]->destruir(mundo);

	}

}

//Destruir Enlaces: Llama a la destrucci�n de las juntas contenidas en los objetos enlace. Recibe el mundo desde donde se llamar� la
//eliminaci�n
void Ragdoll::destruirEnlaces(b2World* mundo) {

	//Bucle que itera sobre todos los objetos de enlace
	for (int i = 0; i < 5; i++) {

		//Si el enlace iterador es nulo...
		if (enlaces[i] == nullptr) {

			//Continua con la siguiente iteraci�n sin ejecutar c�digo
			continue;

		}

		//Llama al m�todo de destrucci�n desde el enlace iterador pasandole el mundo
		enlaces[i]->destruir(mundo);

	}


}

//////////////////////////////////////////////////////////////////

//Retornar Componente: Retorna un puntero a un componente del ragdoll, para ello se usa el �ndice suministrado por par�metro
Poligono* Ragdoll::retornarComponente(int indice) {

	//Retorna el componente usando el indice recibido
	return componentes[indice];

}
