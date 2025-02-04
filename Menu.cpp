#include "Menu.h"

//Constructor principal: Crea la escena usando el identificador suministrado por parámetro
Menu::Menu(String id) {

	//Asigna el valor recibido al atributo local
	identificador = id;

	//Itera sobre el arreglo de botones...
	for (int i = 0; i < CANTIDAD_BOTONES; i++) {

		//Establece el puntero como nulo para poder guardar los botones dinámicamente
		botones[i] = nullptr;

	}

	//Itera sobre el arreglo de textos...
	for (int i = 0; i < CANTIDAD_TEXTOS; i++) {

		//Establece el puntero como nulo para poder guardar los textos dinámicamente
		textos[i] = nullptr;

	}

}

//Constructor de activación: Recibe tanto el identificador para la escena como si esta se creará activa o inactiva
Menu::Menu(String id, bool activada) {

	//Asigna los valores recibidos a los atributos locales
	identificador = id;
	activa = activada;

	//Itera sobre el arreglo de botones...
	for (int i = 0; i < CANTIDAD_BOTONES; i++) {

		//Establece el puntero como nulo para poder guardar los botones dinámicamente
		botones[i] = nullptr;

	}

	//Itera sobre el arreglo de textos...
	for (int i = 0; i < CANTIDAD_TEXTOS; i++) {

		//Establece el puntero como nulo para poder guardar los textos dinámicamente
		textos[i] = nullptr;

	}

}

/////////////////////////////////////////////////////////////

//Crear Panel: Método que crea el panel del menú, usando los argumentos suministrados en la llamada
void Menu::crearPanel(Vector2f coordenadas_panel, Vector2f coordenadas_texto, String texto) {

	//Se usan los parámetros recibidos, añadiendo la escena actual como la seleccionada para añadir el elemento
	panel = GUIPanel(coordenadas_panel, texto, coordenadas_texto, this);

}

//Crear Boton: Recorre el arreglo de punteros a botones, busca un lugar nulo y si lo encuentra, aloja un nuevo Boton usando los
//argumentos recibidos en la llamada
void Menu::crearBoton(Vector2f coordenadas, Vector2f escala, String* texto, TipoSprite tipo) {

	//Recorre el arreglo de punteros a boton...
	for (int i = 0; i < CANTIDAD_BOTONES; i++) {

		//Si el boton iterador es nulo (Está vacío)...
		if (botones[i] == nullptr) {

			//Crea el nuevo botón allí, usando los valores recibidos y el menú actual como la escena seleccionada
			botones[i] = new GUIBoton(coordenadas, escala, texto, tipo, this);

			break;

		}

	}

}

//Crear Boton (Sobrecarga 1): Similar al original, pero no recibe valor de escala, en su lugar estableciendo la misma a 1.0f para
//ambos ejes. Usado para crear botones que no requieran variación de escala
void Menu::crearBoton(Vector2f coordenadas, String* texto, TipoSprite tipo) {

	//Recorre el arreglo de punteros a boton...
	for (int i = 0; i < CANTIDAD_BOTONES; i++) {

		//Si el boton iterador es nulo (Está vacío)...
		if (botones[i] == nullptr) {

			//Crea el nuevo botón allí, usando los valores recibidos y el menú actual como la escena seleccionada
			botones[i] = new GUIBoton(coordenadas, {1.0f, 1.0f}, texto, tipo, this);

			break;

		}

	}

}

//Crear Boton (Sobrecarga 2): Similar al original, pero no recibe valor de escala (fijandola en 1.0f) Y además creará el botón usando
//el índice especificado, permite insertar el botón en un espacio del arreglo específico
void Menu::crearBoton(Vector2f coordenadas, String* texto, TipoSprite tipo, int indice) {

	//Si el boton iterador es nulo (Está vacío)...
	if (botones[indice] == nullptr) {

		//Crea el nuevo botón allí, usando los valores recibidos y el menú actual como la escena seleccionada
		botones[indice] = new GUIBoton(coordenadas, { 1.0f, 1.0f }, texto, tipo, this);

	}

}

//Crear Texto: Crea un texto en la dirección del arreglo recibida (indice) Usando los argumentos suministrados
void Menu::crearTexto(Vector2f coordenadas, String texto, int dimensiones_caracter, Color color, int indice) {

	//Si el texto iterador es nulo (Está vacío)...
	if (textos[indice] == nullptr) {

		//Crea el nuevo texto en dicha direccion usando valores recibidos y la escena actual como seleccionada para el objeto
		textos[indice] = new GUITexto(coordenadas, texto, dimensiones_caracter, color, this);

	}

}

//Borrar Boton: Permite eliminar el botón alojado en la dirección 'indice' del arreglo de botones
void Menu::borrarBoton(int indice) {

	//Si el indice recibido apunta a un espacio nulo...
	if (botones[indice] == nullptr) {

		//Sale del método, ya que no se puede borrar
		return;

	}

	//Libera la memoria en la ubicación obtenida
	delete botones[indice];

	//Ahora el puntero es nulo y puede volver a usarse de ser necesario
	botones[indice] == nullptr;

}

//Borrar Texto: Recibe un indice usado para borrar un texto del arreglo de punteros a texto
void Menu::borrarTexto(int indice) {

	//Si el indice recibido apunta a un espacio nulo...
	if (textos[indice] == nullptr) {

		//Sale del método debido a que no se puede borrar
		return;

	}

	//Libera la memoria asignada en la ubicación
	delete textos[indice];

	//Asigna puntero nulo, para poder reutilizar el espacio y evitar errores
	textos[indice] == nullptr;

}

/////////////////////////////////////////////////////////////

//Obtener Boton: Devuelve el botón correspondiente al espacio 'indice' del arreglo de punteros a boton.
GUIBoton* Menu::obtenerBoton(int indice) {

	return botones[indice];

}

//Obtener Texto: Devuelve el texto correspondiente al espacio 'indice' del arreglo de textos
GUITexto* Menu::obtenerTexto(int indice) {

	return textos[indice];

}

/////////////////////////////////////////////////////////////

//Override de "Renderizar Elementos Alojados"
void Menu::renderizarElementosAlojados(RenderWindow* ventana) {

	//Sale del método si la escena está desactivada o si la ventana es nula
	if (!this->estaActiva() || ventana == nullptr) { return; };

	//Llama al método de dibujar para el panel
	panel.dibujarElementos(ventana);

	//Bucle que itera sobre el arreglo de botones...
	for (int i = 0; i < CANTIDAD_BOTONES; i++) {

		//Si el boton iterador es nulo...
		if (botones[i] == nullptr) {

			//Pasa a la siguiente iteración del bucle sin ejecutar nada
			continue;

		}

		//Llama al método de dibujar para el botón iterador
		botones[i]->dibujarElementos(ventana);

	}

	//Bucle que itera sobre el arreglo de textos...
	for (int i = 0; i < CANTIDAD_TEXTOS; i++) {

		//Si el boton iterador es nulo...
		if (textos[i] == nullptr) {

			//Pasa a la siguiente iteración del bucle sin ejecutar nada
			continue;

		}

		//Llama al método de dibujar para el botón iterador
		textos[i]->dibujarElemento(ventana);

	}

}