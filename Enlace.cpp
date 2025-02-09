#include "Enlace.h"

//Constructor Principal: Recibe como parámetros los 2 Poligonos a conectar, un par de coordenadas representando el punto de anclaje de cada
//cuerpo, una referencia al mundo y la unidad de pixeles por metro para el renderizado en pantalla. Crea el enlace en la escena suministrada
Enlace::Enlace(b2JointType tipo, Poligono* objeto1, Poligono* objeto2, b2Vec2 coordenadas_ancla1, b2Vec2 coordenadas_ancla2, b2World* mundo, int pixeles_por_metro, Escena* escena) {

	//Se convierten los argumentos individuales recibidos en arreglos para suministrarlos al método de inicialización
	Poligono* objetos[2]{ objeto1, objeto2 };
	b2Vec2 coordenadas_ancla[2] = { coordenadas_ancla1, coordenadas_ancla2 };

	//Se llama a inicializar con los valores obtenidos (Usando valor nulo para la escena)
	inicializacionInterna(tipo, {0.0f, 1.0f}, objetos, coordenadas_ancla, mundo, pixeles_por_metro, escena);

	//Si la escena recibida no es nula...
	if (escena != nullptr) {

		//Se adjunta el objeto a la escena recibida
		adjuntarAEscena(escena);

	}
	else {

		//Se notifica por consola que no se pudo adjuntar el objeto a la escena recibida
		cout << "[ERROR]: No se pudo instanciar Enlace debido a que la escena recibida es invalida" << endl;

	}

}

//Constructor de Junta Prismática: Recibe los mismos parámetros que el constructor principal, con la diferencia de también recibir el eje con el cual
//Se creará la definición de la junta prismática, y ese eje será el eje en el cual se moverán los objetos conectados
Enlace::Enlace(b2JointType tipo, b2Vec2 eje_movimiento, Poligono* objeto1, Poligono* objeto2, b2Vec2 coordenadas_ancla1, b2Vec2 coordenadas_ancla2, b2World* mundo, int pixeles_por_metro, Escena* escena) {

	//Se convierten los argumentos individuales recibidos en arreglos para suministrarlos al método de inicialización
	Poligono* objetos[2]{ objeto1, objeto2 };
	b2Vec2 coordenadas_ancla[2] = { coordenadas_ancla1, coordenadas_ancla2 };

	//Se llama a inicializar con los valores obtenidos (Usando valor nulo para la escena)
	inicializacionInterna(tipo, eje_movimiento, objetos, coordenadas_ancla, mundo, pixeles_por_metro, escena);

	//Si la escena recibida no es nula...
	if (escena != nullptr) {

		//Se adjunta el objeto a la escena recibida
		adjuntarAEscena(escena);

	}
	else {

		//Se notifica por consola que no se pudo adjuntar el objeto a la escena recibida
		cout << "[ERROR]: No se pudo instanciar Enlace debido a que la escena recibida es invalida" << endl;

	}

}

//////////////////////////////////////////////////////////////////

//Inicialización Interna: Método que establece todos los valores del enlace y los ajusta a los recibidos por parámetro
void Enlace::inicializacionInterna(b2JointType tipo, b2Vec2 eje_prismatico, Poligono* objetos[], b2Vec2 coordenadas_ancla[], b2World* mundo, int unidad_conversion, Escena* escena) {

	//Si el mundo recibido o alguno de los dos poligonos a conectar es nulo...
	if (mundo == nullptr || objetos[0] == nullptr || objetos[1] == nullptr) {

		//Aborta la creación del enlace
		return;

	}

	//CONFIGURACION DE ENLACE

	//Se asignan los valores recibidos a sus variables de la clase, para manipulación más eficiente de los datos
	objeto_a = objetos[0];
	objeto_b = objetos[1];
	coordenadas_ancla_a = coordenadas_ancla[0];
	coordenadas_ancla_b = coordenadas_ancla[1];

	//CONFIGURACION DE JUNTA

	//Variable que establece el ángulo máximo (Solo para Junta Revolutiva)
	float angulo_maximo;

	//Switch para el tipo de junta
	switch (tipo) {

	case b2JointType::e_revoluteJoint: //Si el tipo de junta a crear es "Revolución"

		//Se asignan los cuerpos a conectar
		definicion_junta_revolutiva.bodyA = objeto_a->retornarCuerpo();
		definicion_junta_revolutiva.bodyB = objeto_b->retornarCuerpo();

		//Se asignan los puntos de anclaje (coordenadas de offset)
		definicion_junta_revolutiva.localAnchorA = coordenadas_ancla_a;
		definicion_junta_revolutiva.localAnchorB = coordenadas_ancla_b;

		//Establece el angulo maximo de rotación en grados
		angulo_maximo = 45.0f * (b2_pi / 180.0f);

		//Convierte los grados a radianes y fija los límites de rotación superiores e inferiores usando dicha conversión, activa los limites
		definicion_junta_revolutiva.lowerAngle = -angulo_maximo;
		definicion_junta_revolutiva.upperAngle = angulo_maximo;
		definicion_junta_revolutiva.enableLimit = true;

		//Se activa la colisión entre los cuerpos anclados
		definicion_junta_revolutiva.collideConnected = false;

		//Se crea la junta, enviandole al mundo la directiva para crear el joint usando su definición
		junta_revolutiva = (b2RevoluteJoint*)mundo->CreateJoint(&definicion_junta_revolutiva);

		break;

	case b2JointType::e_distanceJoint: //Si el tipo de junta a crear es "Distancia"

		//Se asignan los cuerpos a conectar
		definicion_junta_distancia.bodyA = objeto_a->retornarCuerpo();
		definicion_junta_distancia.bodyB = objeto_b->retornarCuerpo();

		//Se asignan los puntos de anclaje (coordenadas de offset)
		definicion_junta_distancia.localAnchorA = coordenadas_ancla_a;
		definicion_junta_distancia.localAnchorB = coordenadas_ancla_b;

		//Convierte los grados a radianes y fija los límites de rotación superiores e inferiores usando dicha conversión, activa los limites
		definicion_junta_distancia.maxLength = 2.0f;
		definicion_junta_distancia.minLength = 1.0f;
		definicion_junta_distancia.length = 1.0f;

		//Se activa la colisión entre los cuerpos anclados
		definicion_junta_distancia.collideConnected = true;

		//Se crea la junta, enviandole al mundo la directiva para crear el joint usando su definición
		junta_distancia = (b2DistanceJoint*)mundo->CreateJoint(&definicion_junta_distancia);

		break;

	case b2JointType::e_prismaticJoint: //Si el tipo de junta a crear es "Prismática"

		//Se asignan los cuerpos a conectar
		definicion_junta_prismatica.bodyA = objeto_a->retornarCuerpo();
		definicion_junta_prismatica.bodyB = objeto_b->retornarCuerpo();

		//Se asignan los puntos de anclaje (coordenadas de offset)
		definicion_junta_prismatica.localAnchorA = coordenadas_ancla_a;
		definicion_junta_prismatica.localAnchorB = coordenadas_ancla_b;

		//Configura si hay limites y si los cuerpos enlazados colisionan o no entre sí
		definicion_junta_prismatica.enableLimit = false;
		definicion_junta_prismatica.collideConnected = true;
		//Asigna el eje de movimiento usado por la junta
		definicion_junta_prismatica.localAxisA.Set(eje_prismatico.x, eje_prismatico.y);

		//Se crea la junta, enviandole al mundo la directiva de creación usando la definicion
		junta_prismatica = (b2PrismaticJoint*)mundo->CreateJoint(&definicion_junta_prismatica);

		break;

	}

	//CONFIGURACION VISUAL

	//Configura la Primitiva de Linea y la cantidad de vértices para los visuales
	puntos_visuales.setPrimitiveType(Lines);
	puntos_visuales.resize(2);

	//Bucle que itera sobre ambos puntos de la primitiva visual
	for (int i = 0; i < 2; i++) {

		//Asigna el color rojo al elemento sobre el que se itera
		puntos_visuales[i].color = Color::Red;

	}

	//Se llama a actualizar para posicionar los puntos correctamente en la pantalla
	actualizar(unidad_conversion);

	//Si la escena recibida como argumento no es nula...
	if (escena != nullptr) {

		//Adjunta el enlace a la escena suministrada
		this->adjuntarAEscena(escena);

	}
	else {

		//Envía un mensaje a consola notificando que no se pudo enlazar el objeto
		cout << "[ERROR]: 'Enlace' intentó enlazarse a una escena que no existe" << endl;

	}

}

//////////////////////////////////////////////////////////////////

//Renderizar: Método que recibe una ventana como parámetro, en la cual se dibuja la directiva gráfica utilizada para mostrar la linea del enlace
void Enlace::renderizar(RenderWindow* ventana) {

	//Llama a dibujar en la ventana pasada, suministrando el arreglo de vértices
	ventana->draw(puntos_visuales);

}

//Actualizar: Método que actualiza la posición de los vértices de la linea visual para que encajen con la posición física de los mismos
void Enlace::actualizar(int pixeles_por_metro) {

	//Guarda la posición visual, usando la posición física y sumandole el offset de los puntos de anclaje
	Vector2f posicion_visual[2];
	posicion_visual[0] = { (objeto_a->retornarCuerpo()->GetPosition().x + coordenadas_ancla_a.x) * pixeles_por_metro, (objeto_a->retornarCuerpo()->GetPosition().y + coordenadas_ancla_a.y) * pixeles_por_metro };
	posicion_visual[1] = { (objeto_b->retornarCuerpo()->GetPosition().x + coordenadas_ancla_b.x) * pixeles_por_metro, (objeto_b->retornarCuerpo()->GetPosition().y + coordenadas_ancla_b.y) * pixeles_por_metro };

	//Itera sobre ambos puntos visuales
	for (int i = 0; i < 2; i++) {

		//Establece la posición nueva
		puntos_visuales[i].position = posicion_visual[i];

	}

}

//Destruir: Método que destruye la junta del enlace, llamando a su destrucción desde el mundo físico recibido por argumento
void Enlace::destruir(b2World* mundo) {

	//Si la junta de revolución no es nula...
	if (junta_revolutiva != nullptr) {

		//Destruye la junta desde el mundo y asigna nulo a su puntero
		mundo->DestroyJoint(junta_revolutiva);
		junta_revolutiva = nullptr;

	}

	//Si la junta de distancia no es nula...
	if (junta_distancia != nullptr) {

		//Destruye la junta desde el mundo y asigna nulo a su puntero
		mundo->DestroyJoint(junta_distancia);
		junta_distancia = nullptr;

	}

	//Si la junta de distancia no es nula...
	if (junta_prismatica != nullptr) {

		//Destruye la junta desde el mundo y asigna nulo a su puntero
		mundo->DestroyJoint(junta_prismatica);
		junta_prismatica = nullptr;

	}

}

//////////////////////////////////////////////////////////////////

//Activar Motor: Activa el modo motor para las juntas que lo soportan (Revolute y Prismatic). El modo motor aplica fuerza constante
//para que los objetos enlazados permanezcan en movimiento
void Enlace::activarMotor(bool estado, float velocidad, float velocidad_maxima) {

	//Si la junta de revolución no es nula...
	if (junta_revolutiva != nullptr) {

		//Activa el motor y establece la velocidad
		junta_revolutiva->EnableMotor(estado);
		junta_revolutiva->SetMotorSpeed(velocidad);
		junta_revolutiva->SetMaxMotorTorque(velocidad_maxima);

	}

	//Si la junta prismática no es nula...
	if (junta_prismatica != nullptr) {
	
		//Activa el motor y establece la velocidad
		junta_prismatica->EnableMotor(estado);
		junta_prismatica->SetMotorSpeed(velocidad);
		junta_prismatica->SetMaxMotorForce(velocidad_maxima);

	}

}

//Limitar: Define si se limita o no la junta que soporte límites (Revolutiva y Prismática)
void Enlace::limitar(bool estado) {

	//Si la junta revolutiva no es nula...
	if (junta_revolutiva != nullptr) {

		//Activa el límite
		junta_revolutiva->EnableLimit(estado);

	}

	//Si la junta prismática no es nula...
	if (junta_prismatica != nullptr) {

		//Activa el límite
		junta_prismatica->EnableLimit(estado);

	}

}

//////////////////////////////////////////////////////////////////

//Establecer Longitud: Método exclusivo para la junta de distancia. Recibe un parámetro de operacion para determinar si afecta a la
//distancia base, la máxima o la mínima, además de el valor que se asignará
void Enlace::establecerLongitud(TipoLongitud operacion, float valor) {

	//Si la junta de distancia no es nula...
	if (junta_distancia != nullptr) {

		//Switch para operacion
		switch (operacion) {

		case TipoLongitud::BASE: //Si la operación es "Base"

			//Asigna la distancia base
			junta_distancia->SetLength(valor);

			break;

		case TipoLongitud::MINIMA: //Si la operación es "Minima"

			//Asigna la distancia minima
			junta_distancia->SetMinLength(valor);

			break;

		case TipoLongitud::MAXIMA: //Si la operación es "Máxima"

			//Asigna la distancia maxima
			junta_distancia->SetMaxLength(valor);

			break;

		}

	}

}

//Establecer Damping: Fija el nuevo valor de damping para la junta de distancia
void Enlace::establecerDamping(float valor) {

	//Si la junta de distancia no es nula...
	if (junta_distancia != nullptr) {

		//Asigna el nuevo damping
		junta_distancia->SetDamping(valor);
	}

}

//////////////////////////////////////////////////////////////////

//Establecer Limites: Fija el nuevo valor para los limites en ambas coordenadas de la junta prismática
void Enlace::establecerLimites(Vector2f valores) {

	//Si la junta de distancia no es nula...
	if (junta_prismatica != nullptr) {

		//Asigna el nuevo limite y lo activa
		junta_prismatica->EnableLimit(true);
		junta_prismatica->SetLimits(valores.x, valores.y);

	}

}

//////////////////////////////////////////////////////////////////

//Retornar Poligono 'A': Devuelve un puntero al primer polígono conectado
Poligono* Enlace::retornarPoligonoA() {

	return objeto_a;

}

//Retornar Poligono 'B': Devuelve un puntero al segundo polígono conectado
Poligono* Enlace::retornarPoligonoB() {

	return objeto_b;

}

//Retornar Junta: Devuelve la junta, seleccionando el tipo basado en qué junta es válida y cual no. La primera junta que no sea nula
//Será retornada en este método, y si no hay ninguna encontrada siempre se retornará "null"
b2Joint* Enlace::retornarJunta() {

	//Devuelve la primera junta que no sea nula, siendo el orden distancia, revolutiva y luego prismática
	if (junta_distancia != nullptr) { return junta_distancia; }
	if (junta_revolutiva != nullptr) { return junta_revolutiva; }
	if (junta_prismatica != nullptr) { return junta_prismatica; }

	//Si por algún motivo no hay junta activa, retorna un puntero nulo
	return nullptr;

}
