#include "Poligono.h"
#include <iostream>

//Espacios de nombres
using namespace std;

//Constructor Principal: Recibe varios par�metros, entre ellos las dimensiones del pol�gono a crear, la posici�n, el mundo donde se
//crear�, el color del que ser� pintado, si es din�mico o est�tico y el valor de conversi�n de metros a pixeles
Poligono::Poligono(String directorio_textura, Vector2f dimensiones_poligono, Vector2f posicion, float friccion, float restitucion, b2World* mundo, b2BodyType tipo, int pixeles_por_metro) {

	//Si el mundo recibido en el constructor es nulo...
	if (mundo == nullptr) {

		//Notifica por consola que no se pudo crear el Poligono
		cout << "[ERROR]: El Poligono no puede crearse debido a que el mundo recibido es inv�lido" << endl;

		//Sale del constructor, evitando la ejecuci�n del resto del c�digo de instanciaci�n
		return;

	}

	//Establece las dimensiones del poligono con el valor recibido
	dimensiones = dimensiones_poligono;

	//Llamada a crear el objeto visual, con los par�metros personalizados
	crearVisuales(directorio_textura, posicion, pixeles_por_metro);

	//Convierte los vectores recibidos en pixeles a metros
	b2Vec2 posicion_fisica = {posicion.x / pixeles_por_metro, posicion.y / pixeles_por_metro};
	b2Vec2 dimensiones_fisicas = {dimensiones.x / pixeles_por_metro, dimensiones.y / pixeles_por_metro};

	//Llamada a crear los objetos f�sicos, con los par�metros personalizados
	crearFisicas(dimensiones_fisicas, posicion_fisica, friccion, restitucion, mundo, tipo);

}

//Constructor Adicional: Recibe y opera con los mismos par�metros que el constructor compuesto, pero a�adiendo la escena
//A la cual el objeto se adjuntar� tras ser creado
Poligono::Poligono(String directorio_textura, Vector2f dimensiones_poligono, Vector2f posicion, float friccion, float restitucion, b2World* mundo, b2BodyType tipo, int pixeles_por_metro, Escena* escena) {

	//Si el mundo recibido en el constructor es nulo...
	if (mundo == nullptr) {

		//Notifica por consola que no se pudo crear el Poligono
		cout << "[ERROR]: El Poligono no puede crearse debido a que el mundo recibido es inv�lido" << endl;

		//Sale del constructor, evitando la ejecuci�n del resto del c�digo de instanciaci�n
		return;

	}

	//Establece las dimensiones del poligono con el valor recibido
	dimensiones = dimensiones_poligono;

	//Llamada a crear el objeto visual, con los par�metros personalizados
	crearVisuales(directorio_textura, posicion, pixeles_por_metro);

	//Convierte los vectores recibidos en pixeles a metros
	b2Vec2 posicion_fisica = { posicion.x / pixeles_por_metro, posicion.y / pixeles_por_metro };
	b2Vec2 dimensiones_fisicas = { dimensiones.x / pixeles_por_metro, dimensiones.y / pixeles_por_metro };

	//Llamada a crear los objetos f�sicos, con los par�metros personalizados
	crearFisicas(dimensiones_fisicas, posicion_fisica, friccion, restitucion, mundo, tipo);

	//Si la escena recibida como argumento no es nula...
	if (escena != nullptr) {

		//Inserta el objeto creado en la escena recibida por par�metro
		this->adjuntarAEscena(escena);

	}
	else {

		//Env�a un mensaje a consola notificando que no se pudo enlazar el objeto
		cout << "[ERROR]: 'Poligono' intento enlazarse a una escena que no existe" << endl;

	}

}

//////////////////////////////////////////////////////////////////

//Crear Visuales: M�todo encargado de crear el apartado visual del pol�gono, recibe como par�metro el color y la conversi�n de metros a pixeles
void Poligono::crearVisuales(String directorio_textura, Vector2f posicion, int pixeles_por_metro) {

	//Carga la textura y la establece en modo repetici�n (tiling)
	textura.loadFromFile(directorio_textura);
	textura.setRepeated(true);

	//Asigna y configura la textura
	sprite.setTexture(textura);
	IntRect rectangulo_textura(0, 0, dimensiones.x, dimensiones.y);
	sprite.setTextureRect(rectangulo_textura);

	//Configura otros par�metros del sprite
	sprite.setOrigin(dimensiones.x / 2, dimensiones.y / 2);
	sprite.setPosition(posicion);

	//Guarda la hitbox del sprite en el atributo
	caja_colision = sprite.getGlobalBounds();

	//Llama a actualizar
	actualizar(pixeles_por_metro);

}

//Crear Fisicas: M�todo encargado de generar la definici�n de cuerpo, figura f�sica, cuerpo, definici�n de fijador y fijador del poligono.
//Recibe como par�metros la posici�n donde se crear� el cuerpo, el mundo donde se crear� y un bool para determinar si es din�mico o no.
void Poligono::crearFisicas(b2Vec2 dimensiones_poligono, b2Vec2 posicion, float friccion, float restitucion, b2World* mundo, b2BodyType tipo_cuerpo) {

	//Si el mundo suministrado es nulo...
	if (mundo == nullptr) {

		//Aborta la creaci�n del poligono por completo
		return;

	}

	//Se establece la dimensi�n de la figura
	figura_cuerpo.SetAsBox(dimensiones_poligono.x / 2, dimensiones_poligono.y / 2);

	//Switch para los valores del tipo
	switch (tipo_cuerpo) {

		
	case b2BodyType::b2_staticBody: //Valor: Est�tico

		//Asigna el tipo de cuerpo a est�tico
		definicion_cuerpo.type = b2_staticBody;

		break;

		
	case b2BodyType::b2_dynamicBody: //Valor: Din�mico

		//Asigna el tipo de cuerpo a din�mico
		definicion_cuerpo.type = b2_dynamicBody;

		break;

		
	case b2BodyType::b2_kinematicBody: //Valor: Cinem�tico

		//Asigna el tipo de cuerpo a cinem�tico
		definicion_cuerpo.type = b2_kinematicBody;

		break;

	}

	//Asigna la nueva posici�n para el cuerpo
	definicion_cuerpo.position.Set(posicion.x, posicion.y);
	definicion_cuerpo.gravityScale = 0.8f;

	//Crea el cuerpo a partir de la definici�n y lo almacena en su variable
	cuerpo = mundo->CreateBody(&definicion_cuerpo);

	//Asigna la figura a la definici�n del fijador y lo crea usando la misma
	definicion_fijador.shape = &figura_cuerpo;
	definicion_fijador.density = 0.45f;
	definicion_fijador.restitution = restitucion;
	definicion_fijador.friction = friccion;
	fijador = cuerpo->CreateFixture(&definicion_fijador);

}

//Renderizar: Este m�todo usa la ventana recibida como par�metro para dibujar el sprite del objeto
void Poligono::renderizar(RenderWindow* ventana) {

	//Si la ventana suministrada es nula...
	if (ventana == nullptr) {

		//Sale inmediatamente sin ejecutar directivas
		return;

	}

	//Llama a dibujar desde la ventana pasando la figura visual
	ventana->draw(sprite);

}

//Actualizar: Este m�todo actualiza los estados del poligono, principalmente la posici�n del objeto visual para que encaje
//con la del objeto f�sico. Llamado tras avanzar un paso en la simulaci�n del mundo (M�todo "Step")
void Poligono::actualizar(int pixeles_por_metro) {

	//Si el cuerpo f�sico es nulo...
	if (cuerpo == nullptr) {

		//Sale inmediatamente y aborta la ejecuci�n del c�digo
		return;

	}

	//Almacena la posici�n f�sica convertida a posici�n visual (de "b2Vec2" a "Vector2f") y la rotaci�n convertida (radianes a grados)
	Vector2f posicion_fisica_convertida = { cuerpo->GetPosition().x * pixeles_por_metro, cuerpo->GetPosition().y * pixeles_por_metro};
	float rotacion_convertida = cuerpo->GetAngle() * (180.0f / b2_pi);

	//Establece la posici�n y rotaci�n con las unidades convertidas
	sprite.setPosition(posicion_fisica_convertida);
	sprite.setRotation(rotacion_convertida);

	//Actualiza la posici�n de la hitbox
	caja_colision = sprite.getGlobalBounds();

}

//Modificar Densidad: Permite cambiar la densidad del fijador, usando el valor recibido por par�metro
void Poligono::modificarDensidad(float nuevo_valor) {

	fijador->SetDensity(nuevo_valor);

}

//Modificar Fricci�n: Cambia la fricci�n con el valor suministrado por par�metro
void Poligono::modificarFriccion(float nuevo_valor) {

	fijador->SetFriction(nuevo_valor);

}

//Modificar Restituci�n: Cambia la restituci�n con el valor suministrado por par�metro
void Poligono::modificarRestitucion(float nuevo_valor) {

	fijador->SetRestitution(nuevo_valor);

}

//Modificar Rotaci�n: Permite modificar la rotaci�n del cuerpo, en esencia rotarlo usando el valor suministrado por par�metro (EL valor se define y no se
//suma o resta, por lo que asignar 90 asignar� la rotaci�n del objeto como 90 convertido a radianes
void Poligono::modificarRotacion(float grados) {

	//Almacena los �ngulos convertidos a radianes (Para rotar el cuerpo f�sico, ya que el visual depende del mismo)
	float rotacion_radianes = grados * (b2_pi / 180.0f);

	//Si el cuerpo f�sico es nulo...
	if (cuerpo == nullptr) {

		//Sale inmediatamente y aborta la ejecuci�n del c�digo
		return;

	}

	//Asigna la rotaci�n
	cuerpo->SetTransform(cuerpo->GetPosition(), rotacion_radianes);

}

//Despertar: M�todo que despierta o duerme al cuerpo, dependiendo el estado suministrado por par�metro
void Poligono::despertar(bool estado) {

	//Si el cuerpo f�sico es nulo...
	if (cuerpo == nullptr) {

		//Sale inmediatamente y aborta la ejecuci�n del c�digo
		return;

	}

	//Asigna el estado con la llamada "SetAwake()"
	cuerpo->SetAwake(estado);

}

//Aplicar Fuerza: Permite aplicar una fuerza al centro del cuerpo f�sico. Se pasa la magnitud por par�metro
void Poligono::aplicarFuerza(b2Vec2 magnitud) {

	//Si el cuerpo f�sico es nulo...
	if (cuerpo == nullptr) {

		//Sale inmediatamente y aborta la ejecuci�n del c�digo
		return;

	}

	//Aplica la fuerza suministrada al centro, despierta el cuerpo si no lo est�
	cuerpo->ApplyForceToCenter(magnitud, true);

}

//Destruir: M�todo que accede al mundo suministrado por par�metro para destruir el objeto f�sico alojado en �l. Debe llamarse previo a la
//destrucci�n de un Poligono con "delete"
void Poligono::destruir(b2World* mundo) {

	//Si el cuerpo f�sico es nulo...
	if (cuerpo == nullptr) {

		//Sale inmediatamente y aborta la ejecuci�n del c�digo
		return;

	}

	//Si el mundo donde est� contenido el poligono no es nulo...
	if (mundo != nullptr) {

		//Destruye el cuerpo contenido en el mundo y le asigna nulo a su puntero
		mundo->DestroyBody(cuerpo);
		cuerpo = nullptr;

	}

}

//////////////////////////////////////////////////////////////////

//Retornar Cuerpo: M�todo que devuelve el cuerpo f�sico del Poligono
b2Body* Poligono::retornarCuerpo() {

	return cuerpo;

}

//Retornar Visual: M�todo que devuelve el cuerpo visual del Poligono
Sprite Poligono::retornarSprite() {

	return sprite;

}

FloatRect Poligono::retornarHitbox() {

	return caja_colision;

}

//Retornar Posici�n Visual: Devuelve un vector que contiene las coordenadas del sprite
Vector2f Poligono::retornarPosicionVisual() {

	return sprite.getPosition();

}

//Retornar Dimensiones: Devuelve un vector que contiene las dimensiones del poligono
Vector2f Poligono::retornarDimensiones() {

	return dimensiones;

}

//Retornar Posici�n: Devuelve un vector que contiene las coordenadas del cuerpo f�sico
b2Vec2 Poligono::retornarPosicionFisica() {

	return cuerpo->GetPosition();

}

//Retornar Tipo: Devuelve el tipo de cuerpo f�sico, usando la enumeraci�n "din�mico", "est�tico" o "cinem�tico"
b2BodyType Poligono::retornarTipo() {

	return cuerpo->GetType();

}

//Retornar Densidad: M�todo que devuelve la densidad del cuerpo f�sico
float Poligono::retornarDensidad() {

	return fijador->GetDensity();

}

//Retornar Fricci�n: M�todo que devuelve la fricci�n del cuerpo f�sico
float Poligono::retornarFriccion() {

	return fijador->GetFriction();

}

//Retornar Restituci�n: M�todo que devuelve la restituci�n del cuerpo f�sico
float Poligono::retornarRestitucion() {

	return fijador->GetRestitution();

}
