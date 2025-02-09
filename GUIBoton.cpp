#include "GUIBoton.h"

//Constructor por defecto: Usa valores por defecto para llamar a la inicialización
GUIBoton::GUIBoton() {

	//Llama a inicializar con valores por defecto
	inicializacionInterna({ 0.0f, 0.0f }, {1.0f, 1.0f}, nullptr, TipoSprite::CIRCULAR, nullptr);

}

//Constructor con posición y escala: Recibe las coordenadas del botón y la escala del mismo
GUIBoton::GUIBoton(Vector2f posicion, Vector2f escala) {

	//Llama a inicializar con los argumentos suministrados
	inicializacionInterna(posicion, escala, nullptr, TipoSprite::CIRCULAR, nullptr);

}

//Constructor compuesto: Recibe posición del botón, escala, cadena de texto del mismo (nulo si no usa texto) Y finalmente el tipo de sprite
GUIBoton::GUIBoton(Vector2f posicion, String* texto, TipoSprite tipo, Escena* escena) {

	//Llama a inicializar con los argumentos suministrados
	inicializacionInterna(posicion, {1.0f, 1.0f}, texto, tipo, escena);

}

//Constructor compuesto adicional: Recibe posición, escala, texto (Si es necesario), tipo y adicionalmente recibe una escena a la cual
//el objeto se adjuntará (Para los demás constructores, el no se adjunta a ninguna escena por defecto, por lo que serán interactuables y visibles constantemente)
GUIBoton::GUIBoton(Vector2f posicion, Vector2f escala, String* texto, TipoSprite tipo, Escena* escena) {

	//Llama a inicializar con los valores recibidos
	inicializacionInterna(posicion, escala, texto, tipo, escena);

}

//////////////////////////////////////////////////////////////////

//Inicialización Interna: Método encargado de inicializar los atributos de la clase, configurando todo lo necesario para que el objeto
//sea utilizable
void GUIBoton::inicializacionInterna(Vector2f posicion, Vector2f escala, String* texto, TipoSprite tipo, Escena* escena) {

	//Asigna un objeto por defecto al puntero
	texto_boton = new Text;

	//Crea la variable para almacenar la ruta hacia la textura para el boton
	String directorio_textura = "assets/images/boton_cuadrado.png";
	String directorio_textura_iluminada = "assets/images/boton_cuadrado_iluminado.png";
	String directorio_textura_desactivada = "assets/images/blank.png";

	//Switch que determina la textura del boton
	switch (tipo) {

	case TipoSprite::CUADRADO: //Forma: Cuadrado

		//Almacena la dirección de la textura cuadrada
		directorio_textura = "assets/images/boton_cuadrado.png";
		directorio_textura_iluminada = "assets/images/boton_cuadrado_iluminado.png";

		break;

	case TipoSprite::RECTANGULAR: //Forma: Rectangulo

		//Almacena la dirección de la textura rectangular
		directorio_textura = "assets/images/boton_rectangular.png";
		directorio_textura_iluminada = "assets/images/boton_rectangular_iluminado.png";

		break;

	case TipoSprite::CIRCULAR: //Forma: Circulo

		//Almacena la dirección de la textura redonda
		directorio_textura = "assets/images/boton_circular.png";
		directorio_textura_iluminada = "assets/images/boton_circular_iluminado.png";

		break;

	case TipoSprite::SALIR: //Tipo: Salir

		//Almacena la dirección de la textura de salir
		directorio_textura = "assets/images/boton_salir.png";
		directorio_textura_iluminada = "assets/images/boton_salir_iluminado.png";

		break;

	case TipoSprite::REINICIAR: //Tipo: Reiniciar

		//Almacena la dirección de la textura de reinicar
		directorio_textura = "assets/images/boton_reiniciar.png";
		directorio_textura_iluminada = "assets/images/boton_reiniciar_iluminado.png";

		break;

	case TipoSprite::AVANZAR: //Tipo: Avanzar

		//Almacena la dirección de la textura de avanzar
		directorio_textura = "assets/images/boton_avanzar.png";
		directorio_textura_iluminada = "assets/images/boton_avanzar_iluminado.png";
		directorio_textura_desactivada = "assets/images/boton_avanzar_desactivado.png";

		break;

	}

	//Configura los parámetros del sprite aplicando textura, posicion, origen, fijando el tamaño de la hitbox y escalando
	textura_boton.loadFromFile(directorio_textura);
	textura_boton_iluminado.loadFromFile(directorio_textura_iluminada);
	textura_boton_desactivado.loadFromFile(directorio_textura_desactivada);
	sprite_boton.setTexture(textura_boton);
	sprite_boton.setScale(escala);
	sprite_boton.setOrigin(sprite_boton.getGlobalBounds().width / 2, sprite_boton.getGlobalBounds().height / 2);
	sprite_boton.setPosition(posicion);
	hitbox_boton = new FloatRect(sprite_boton.getGlobalBounds());

	//Crea una variable de fuente para usarse en la configuración del texto
	fuente_boton.loadFromFile("assets/fonts/titan.otf");

	//Si el texto recibido no es nulo...
	if (texto_boton != nullptr && texto != nullptr) {

		//Configura el texto asignando fuente, cadena de texto, tamaño de letra, posición y origen
		texto_boton->setFont(fuente_boton);
		texto_boton->setString(*texto);
		texto_boton->setCharacterSize(43);
		texto_boton->setPosition(posicion.x, posicion.y - 15.0f);
		texto_boton->setOrigin(texto_boton->getGlobalBounds().width / 2, texto_boton->getGlobalBounds().height / 2);
		texto_boton->setFillColor(Color::Black);

	}

	//Si la escena recibida como argumento no es nula...
	if (escena != nullptr) {

		//Inserta el elemento a la escena pasada por parámetro
		adjuntarAEscena(escena);

	}

}

//Cambiar Texto: Usado para asignar una nueva cadena de texto al texto del botón
void GUIBoton::cambiarTexto(String texto_nuevo) {

	//Asigna el nuevo texto recibido
	texto_boton->setString(texto_nuevo);

}

//Encender: Usado para encender o apagar un botón. Un botón apagado cambia de textura a una más oscura con la que el cursor no interactúa visualmente
void GUIBoton::encender(bool estado) {

	//Cambia encendido usando el estado recibido
	encendido = estado;

	//Si el botón está encendido...
	if (encendido) {

		//Aplica la textura de activado
		sprite_boton.setTexture(textura_boton);

	}
	else {

		//Aplica la textura de desactivado
		sprite_boton.setTexture(textura_boton_desactivado);

	}

}

//Iluminar: Permite intercambiar entre la textura "normal" y la variante "iluminada" de dicha textura, ambas guardadas en la clase
//Usado en conjunto al evento de movimiento de mouse para sobresaltar los botones cuando el cursor esté encima de ellos
void GUIBoton::iluminar(bool estado) {

	//Si el botón no está encendido
	if (!encendido) {

		//Omite el código, ya que un botón apagado no interactúa iluminandose cuando el cursor le pasa por encima
		return;

	}

	//Si se recibe "true"...
	if (estado) {

		//Se asigna verdadero a la iluminación
		iluminado = true;

		//Aplica la textura iluminada al sprite
		sprite_boton.setTexture(textura_boton_iluminado);

	}
	else {

		//Se asigna falso a la iluminación
		iluminado = false;

		//Aplica la textura convencional
		sprite_boton.setTexture(textura_boton);

	}

}

//Dibujar Elementos: Le pasa los elementos a dibujar a la ventana suministrada como argumento
void GUIBoton::dibujarElementos(RenderWindow* ventana) {

	//Si la ventana suministrada es nula...
	if (ventana == nullptr) {

		//Sale inmediatamente sin ejecutar directivas
		return;

	}

	//Llamadas a dibujar desde la ventana obtenida
	ventana->draw(sprite_boton);

	//Sale del método si el texto no se está usando o si su string está vacío, evitando así llamar a la directiva draw
	if (!usandoTexto() || texto_boton->getString().isEmpty()) { return; }; 

	//Si no salió, dibuja el texto del boton desde la ventana
	ventana->draw(*texto_boton);

}

//////////////////////////////////////////////////////////////////

//Esta Encendido: Retorna "true" si el botón está encendido (Puede detectar interacción únicamente al estar encendido)
bool GUIBoton::estaEncendido() {

	return encendido;

}

//Revisar Colisiones (Por Interseccion): Método que devuelve "true" si la caja de colisión del botón está solapandose con la caja
//suministrada como argumento.
bool GUIBoton::revisarColisionesPorInterseccion(FloatRect hitbox_externa) {

	//Retorna si las 2 cajas de colisión están en contacto
	return hitbox_boton->intersects(hitbox_externa);

}

//Revisar Colisiones (Por Ubicacion): Similar a la primera revisión, pero esta compara un punto en el espacio y verifica si ese
//punto está contenido dentro de la hitbox del botón, de ser así retornará "true" y habrá colision
bool GUIBoton::revisarColisionesPorUbicacion(Vector2f coordenada) {

	//Retorna si el punto de coordenada recibido está contenido en el área del sprite del botón (Su hitbox)
	return hitbox_boton->contains(coordenada);

}

//Usando Texto: Este método devolverá "true" si el botón está utilizando su atributo de texto, es decir si el texto es válido (no está
//vacío). Usado para evitar llamadas innecesarias de cambios al texto y para evitar errores
bool GUIBoton::usandoTexto() {

	//Retorna verdadero si la cadena de texto no está vacía
	return (!texto_boton->getString().isEmpty());

}

//Retornar Sprite: Devuelve el sprite del botón para poder ser pasado a la directiva draw de la ventana al renderizar
Sprite GUIBoton::retornarSprite() {

	return sprite_boton;

}

//Retornar Visual Texto: Devuelve el texto (No su cadena, sino el objeto dibujable)
Text GUIBoton::retornarVisualTexto() {

	return *texto_boton;

}

//Retornar Hitbox: Devuelve la hitbox del botón
FloatRect GUIBoton::retornarHitbox() {

	return *hitbox_boton;

}