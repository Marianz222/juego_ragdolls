#include "Poligono.h"
#include <iostream>

//Espacios de nombres
using namespace std;

//Constructor Principal: Recibe varios parámetros, entre ellos las dimensiones del polígono a crear, la posición, el mundo donde se
//creará, el color del que será pintado, si es dinámico o estático y el valor de conversión de metros a pixeles
Poligono::Poligono(String directorio_textura, Vector2f dimensiones_poligono, Vector2f posicion, float friccion, float restitucion, b2World* mundo, b2BodyType tipo, int pixeles_por_metro) {

	//Si el mundo recibido en el constructor es nulo...
	if (mundo == nullptr) {

		//Notifica por consola que no se pudo crear el Poligono
		cout << "[ERROR]: El Poligono no puede crearse debido a que el mundo recibido es inválido" << endl;

		//Sale del constructor, evitando la ejecución del resto del código de instanciación
		return;

	}

	//Establece las dimensiones del poligono con el valor recibido
	dimensiones = dimensiones_poligono;

	//Llamada a crear el objeto visual, con los parámetros personalizados
	crearVisuales(directorio_textura, posicion, pixeles_por_metro);

	//Convierte los vectores recibidos en pixeles a metros
	b2Vec2 posicion_fisica = {posicion.x / pixeles_por_metro, posicion.y / pixeles_por_metro};
	b2Vec2 dimensiones_fisicas = {dimensiones.x / pixeles_por_metro, dimensiones.y / pixeles_por_metro};

	//Llamada a crear los objetos físicos, con los parámetros personalizados
	crearFisicas(dimensiones_fisicas, posicion_fisica, friccion, restitucion, mundo, tipo);

}

//Constructor Adicional: Recibe y opera con los mismos parámetros que el constructor compuesto, pero añadiendo la escena
//A la cual el objeto se adjuntará tras ser creado
Poligono::Poligono(String directorio_textura, Vector2f dimensiones_poligono, Vector2f posicion, float friccion, float restitucion, b2World* mundo, b2BodyType tipo, int pixeles_por_metro, Escena* escena) {

	//Si el mundo recibido en el constructor es nulo...
	if (mundo == nullptr) {

		//Notifica por consola que no se pudo crear el Poligono
		cout << "[ERROR]: El Poligono no puede crearse debido a que el mundo recibido es inválido" << endl;

		//Sale del constructor, evitando la ejecución del resto del código de instanciación
		return;

	}

	//Establece las dimensiones del poligono con el valor recibido
	dimensiones = dimensiones_poligono;

	//Llamada a crear el objeto visual, con los parámetros personalizados
	crearVisuales(directorio_textura, posicion, pixeles_por_metro);

	//Convierte los vectores recibidos en pixeles a metros
	b2Vec2 posicion_fisica = { posicion.x / pixeles_por_metro, posicion.y / pixeles_por_metro };
	b2Vec2 dimensiones_fisicas = { dimensiones.x / pixeles_por_metro, dimensiones.y / pixeles_por_metro };

	//Llamada a crear los objetos físicos, con los parámetros personalizados
	crearFisicas(dimensiones_fisicas, posicion_fisica, friccion, restitucion, mundo, tipo);

	//Si la escena recibida como argumento no es nula...
	if (escena != nullptr) {

		//Inserta el objeto creado en la escena recibida por parámetro
		this->adjuntarAEscena(escena);

	}
	else {

		//Envía un mensaje a consola notificando que no se pudo enlazar el objeto
		cout << "[ERROR]: 'Poligono' intento enlazarse a una escena que no existe" << endl;

	}

}

//////////////////////////////////////////////////////////////////

//Crear Visuales: Método encargado de crear el apartado visual del polígono, recibe como parámetro el color y la conversión de metros a pixeles
void Poligono::crearVisuales(String directorio_textura, Vector2f posicion, int pixeles_por_metro) {

	//Carga la textura y la establece en modo repetición (tiling)
	textura.loadFromFile(directorio_textura);
	textura.setRepeated(true);

	//Asigna y configura la textura
	sprite.setTexture(textura);
	IntRect rectangulo_textura(0, 0, dimensiones.x, dimensiones.y);
	sprite.setTextureRect(rectangulo_textura);

	//Configura otros parámetros del sprite
	sprite.setOrigin(dimensiones.x / 2, dimensiones.y / 2);
	sprite.setPosition(posicion);

	//Guarda la hitbox del sprite en el atributo
	caja_colision = sprite.getGlobalBounds();

	//Llama a actualizar
	actualizar(pixeles_por_metro);

}

//Crear Fisicas: Método encargado de generar la definición de cuerpo, figura física, cuerpo, definición de fijador y fijador del poligono.
//Recibe como parámetros la posición donde se creará el cuerpo, el mundo donde se creará y un bool para determinar si es dinámico o no.
void Poligono::crearFisicas(b2Vec2 dimensiones_poligono, b2Vec2 posicion, float friccion, float restitucion, b2World* mundo, b2BodyType tipo_cuerpo) {

	//Si el mundo suministrado es nulo...
	if (mundo == nullptr) {

		//Aborta la creación del poligono por completo
		return;

	}

	//Se establece la dimensión de la figura
	figura_cuerpo.SetAsBox(dimensiones_poligono.x / 2, dimensiones_poligono.y / 2);

	//Switch para los valores del tipo
	switch (tipo_cuerpo) {

		
	case b2BodyType::b2_staticBody: //Valor: Estático

		//Asigna el tipo de cuerpo a estático
		definicion_cuerpo.type = b2_staticBody;

		break;

		
	case b2BodyType::b2_dynamicBody: //Valor: Dinámico

		//Asigna el tipo de cuerpo a dinámico
		definicion_cuerpo.type = b2_dynamicBody;

		break;

		
	case b2BodyType::b2_kinematicBody: //Valor: Cinemático

		//Asigna el tipo de cuerpo a cinemático
		definicion_cuerpo.type = b2_kinematicBody;

		break;

	}

	//Asigna la nueva posición para el cuerpo
	definicion_cuerpo.position.Set(posicion.x, posicion.y);
	definicion_cuerpo.gravityScale = 0.8f;

	//Crea el cuerpo a partir de la definición y lo almacena en su variable
	cuerpo = mundo->CreateBody(&definicion_cuerpo);

	//Asigna la figura a la definición del fijador y lo crea usando la misma
	definicion_fijador.shape = &figura_cuerpo;
	definicion_fijador.density = 0.45f;
	definicion_fijador.restitution = restitucion;
	definicion_fijador.friction = friccion;
	fijador = cuerpo->CreateFixture(&definicion_fijador);

}

//Renderizar: Este método usa la ventana recibida como parámetro para dibujar el sprite del objeto
void Poligono::renderizar(RenderWindow* ventana) {

	//Si la ventana suministrada es nula...
	if (ventana == nullptr) {

		//Sale inmediatamente sin ejecutar directivas
		return;

	}

	//Llama a dibujar desde la ventana pasando la figura visual
	ventana->draw(sprite);

}

//Actualizar: Este método actualiza los estados del poligono, principalmente la posición del objeto visual para que encaje
//con la del objeto físico. Llamado tras avanzar un paso en la simulación del mundo (Método "Step")
void Poligono::actualizar(int pixeles_por_metro) {

	//Si el cuerpo físico es nulo...
	if (cuerpo == nullptr) {

		//Sale inmediatamente y aborta la ejecución del código
		return;

	}

	//Almacena la posición física convertida a posición visual (de "b2Vec2" a "Vector2f") y la rotación convertida (radianes a grados)
	Vector2f posicion_fisica_convertida = { cuerpo->GetPosition().x * pixeles_por_metro, cuerpo->GetPosition().y * pixeles_por_metro};
	float rotacion_convertida = cuerpo->GetAngle() * (180.0f / b2_pi);

	//Establece la posición y rotación con las unidades convertidas
	sprite.setPosition(posicion_fisica_convertida);
	sprite.setRotation(rotacion_convertida);

	//Actualiza la posición de la hitbox
	caja_colision = sprite.getGlobalBounds();

}

//Modificar Densidad: Permite cambiar la densidad del fijador, usando el valor recibido por parámetro
void Poligono::modificarDensidad(float nuevo_valor) {

	fijador->SetDensity(nuevo_valor);

}

//Modificar Fricción: Cambia la fricción con el valor suministrado por parámetro
void Poligono::modificarFriccion(float nuevo_valor) {

	fijador->SetFriction(nuevo_valor);

}

//Modificar Restitución: Cambia la restitución con el valor suministrado por parámetro
void Poligono::modificarRestitucion(float nuevo_valor) {

	fijador->SetRestitution(nuevo_valor);

}

//Modificar Rotación: Permite modificar la rotación del cuerpo, en esencia rotarlo usando el valor suministrado por parámetro (EL valor se define y no se
//suma o resta, por lo que asignar 90 asignará la rotación del objeto como 90 convertido a radianes
void Poligono::modificarRotacion(float grados) {

	//Almacena los ángulos convertidos a radianes (Para rotar el cuerpo físico, ya que el visual depende del mismo)
	float rotacion_radianes = grados * (b2_pi / 180.0f);

	//Si el cuerpo físico es nulo...
	if (cuerpo == nullptr) {

		//Sale inmediatamente y aborta la ejecución del código
		return;

	}

	//Asigna la rotación
	cuerpo->SetTransform(cuerpo->GetPosition(), rotacion_radianes);

}

//Despertar: Método que despierta o duerme al cuerpo, dependiendo el estado suministrado por parámetro
void Poligono::despertar(bool estado) {

	//Si el cuerpo físico es nulo...
	if (cuerpo == nullptr) {

		//Sale inmediatamente y aborta la ejecución del código
		return;

	}

	//Asigna el estado con la llamada "SetAwake()"
	cuerpo->SetAwake(estado);

}

//Aplicar Fuerza: Permite aplicar una fuerza al centro del cuerpo físico. Se pasa la magnitud por parámetro
void Poligono::aplicarFuerza(b2Vec2 magnitud) {

	//Si el cuerpo físico es nulo...
	if (cuerpo == nullptr) {

		//Sale inmediatamente y aborta la ejecución del código
		return;

	}

	//Aplica la fuerza suministrada al centro, despierta el cuerpo si no lo está
	cuerpo->ApplyForceToCenter(magnitud, true);

}

//Destruir: Método que accede al mundo suministrado por parámetro para destruir el objeto físico alojado en él. Debe llamarse previo a la
//destrucción de un Poligono con "delete"
void Poligono::destruir(b2World* mundo) {

	//Si el cuerpo físico es nulo...
	if (cuerpo == nullptr) {

		//Sale inmediatamente y aborta la ejecución del código
		return;

	}

	//Si el mundo donde está contenido el poligono no es nulo...
	if (mundo != nullptr) {

		//Destruye el cuerpo contenido en el mundo y le asigna nulo a su puntero
		mundo->DestroyBody(cuerpo);
		cuerpo = nullptr;

	}

}

//////////////////////////////////////////////////////////////////

//Retornar Cuerpo: Método que devuelve el cuerpo físico del Poligono
b2Body* Poligono::retornarCuerpo() {

	return cuerpo;

}

//Retornar Visual: Método que devuelve el cuerpo visual del Poligono
Sprite Poligono::retornarSprite() {

	return sprite;

}

FloatRect Poligono::retornarHitbox() {

	return caja_colision;

}

//Retornar Posición Visual: Devuelve un vector que contiene las coordenadas del sprite
Vector2f Poligono::retornarPosicionVisual() {

	return sprite.getPosition();

}

//Retornar Dimensiones: Devuelve un vector que contiene las dimensiones del poligono
Vector2f Poligono::retornarDimensiones() {

	return dimensiones;

}

//Retornar Posición: Devuelve un vector que contiene las coordenadas del cuerpo físico
b2Vec2 Poligono::retornarPosicionFisica() {

	return cuerpo->GetPosition();

}

//Retornar Tipo: Devuelve el tipo de cuerpo físico, usando la enumeración "dinámico", "estático" o "cinemático"
b2BodyType Poligono::retornarTipo() {

	return cuerpo->GetType();

}

//Retornar Densidad: Método que devuelve la densidad del cuerpo físico
float Poligono::retornarDensidad() {

	return fijador->GetDensity();

}

//Retornar Fricción: Método que devuelve la fricción del cuerpo físico
float Poligono::retornarFriccion() {

	return fijador->GetFriction();

}

//Retornar Restitución: Método que devuelve la restitución del cuerpo físico
float Poligono::retornarRestitucion() {

	return fijador->GetRestitution();

}
