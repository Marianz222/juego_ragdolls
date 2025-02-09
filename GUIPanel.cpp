#include "GUIPanel.h"

//Constructor por defecto: Usa valores por defecto al llamar a la inicialización
GUIPanel::GUIPanel() {

	//Llama a inicializar con valores por defecto
	inicializacionInterna({ 0.0f, 0.0f }, "Nuevo Panel", {0.0f, 0.0f});

}

//Constructor principal: Recibe como argumento la posición, y la posición y cadena para el texto
GUIPanel::GUIPanel(Vector2f posicion_panel, String texto, Vector2f posicion_texto) {

	//Llama a inicializar con los valores recibidos
	inicializacionInterna(posicion_panel, texto, posicion_texto);

}

//Constructor compuesto: Recibe como argumento la posición, la cadena de texto y la posición del mismo. También recibe la escena donde
//el objeto será insertado tras crearse
GUIPanel::GUIPanel(Vector2f posicion_panel, String texto, Vector2f posicion_texto, Escena* escena) {

	//Llama a inicializar con los valores recibidos
	inicializacionInterna(posicion_panel, texto, posicion_texto);
	
	//Si la escena recibida como argumento no es nula...
	if (escena != nullptr) {

		//Adjunta el objeto a la escena especificada
		adjuntarAEscena(escena);

	}

	

}

//////////////////////////////////////////////////////////////////

//Inicialización Interna: Método que inicializa todos los atributos de la clase. En este caso prepara la textura, sprite y el texto
//del botón asignando posiciones, orígenes y data específica para cada tipo de objeto
void GUIPanel::inicializacionInterna(Vector2f posicion_panel, String texto, Vector2f offset_texto) {

	//Crea los objetos por defecto en cada puntero
	texto_panel = new Text;
	titan_fuente = new Font;
	textura_panel = new Texture;

	//Almacena los directorios de carga de imagen y fuente
	String directorio_textura = "assets/images/panel.png";
	String directorio_fuente = "assets/fonts/titan.otf";

	//Configura el sprite del panel textura, posicion, origen, etc...
	textura_panel->loadFromFile(directorio_textura);
	sprite_panel.setTexture(*textura_panel);
	sprite_panel.setOrigin(sprite_panel.getGlobalBounds().width / 2, sprite_panel.getGlobalBounds().height / 2);
	sprite_panel.setPosition(posicion_panel);

	//Crea una variable para almacenar la fuente, para luego usarse al configurar el texto
	titan_fuente->loadFromFile(directorio_fuente);

	//Si el texto recibido no es nulo...
	if (texto_panel != nullptr && !texto.isEmpty()) {

		//Configura el texto asignando fuente, cadena de texto, tamaño de letra, posición y origen
		texto_panel->setFont(*titan_fuente);
		texto_panel->setString(texto);
		texto_panel->setCharacterSize(42);
		texto_panel->setPosition({ posicion_panel.x + offset_texto.x, posicion_panel.y + offset_texto.y });
		texto_panel->setOrigin(texto_panel->getGlobalBounds().width / 2, texto_panel->getGlobalBounds().height / 2);
		texto_panel->setFillColor(Color::Black);
		texto_panel->setOutlineThickness(0.6f);
		texto_panel->setOutlineColor(Color::White);

	}

}

//Cambiar Visibilidad: Establece la bandera de visibilidad usando el argumento de estado suministrado
void GUIPanel::cambiarVisibilidad(bool estado) {

	//Asigna el nuevo valor booleano
	visible = estado;

}

//Cambiar Texto: Cambia el texto del panel al suministrado por parámetro
void GUIPanel::cambiarTexto(String texto_nuevo) {

	//Asigna el nuevo texto
	texto_panel->setString(texto_nuevo);

}

//Dibujar Elementos: Le pasa los elementos a dibujar a la ventana suministrada como argumento
void GUIPanel::dibujarElementos(RenderWindow* ventana) {

	//Si la ventana suministrada es nula...
	if (ventana == nullptr) {

		//Sale inmediatamente sin ejecutar directivas
		return;

	}

	//Llamadas a dibujar desde la ventana obtenida
	ventana->draw(sprite_panel);

	//Si el string del texto no está vacío...
	if (texto_panel != nullptr && !texto_panel->getString().isEmpty()) {

		//Llama a dibujar el texto desde la ventana
		ventana->draw(*texto_panel);

	}

}

//////////////////////////////////////////////////////////////////

//Retornar Sprite: Devuelve el sprite del panel para poder ser pasado a la directiva draw de la ventana principal
Sprite GUIPanel::retornarSprite() {

	return sprite_panel;

}

//Retornar Visual Texto: Devuelve el texto (No su cadena, sino el objeto dibujable)
Text GUIPanel::retornarVisualTexto() {

	return *texto_panel;

}