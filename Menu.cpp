#include "Menu.h"

//Constructor principal: Crea la escena usando el identificador suministrado por par�metro
Menu::Menu(String id) {

	//Asigna el valor recibido al atributo local
	identificador = id;

	//Itera sobre el arreglo de botones...
	for (int i = 0; i < CANTIDAD_BOTONES; i++) {

		//Establece el puntero como nulo para poder guardar los botones din�micamente
		botones[i] = nullptr;

	}

	//Itera sobre el arreglo de textos...
	for (int i = 0; i < CANTIDAD_TEXTOS; i++) {

		//Establece el puntero como nulo para poder guardar los textos din�micamente
		textos[i] = nullptr;

	}

}

//Constructor de activaci�n: Recibe tanto el identificador para la escena como si esta se crear� activa o inactiva
Menu::Menu(String id, bool activada) {

	//Asigna los valores recibidos a los atributos locales
	identificador = id;
	activa = activada;

	//Itera sobre el arreglo de botones...
	for (int i = 0; i < CANTIDAD_BOTONES; i++) {

		//Establece el puntero como nulo para poder guardar los botones din�micamente
		botones[i] = nullptr;

	}

	//Itera sobre el arreglo de textos...
	for (int i = 0; i < CANTIDAD_TEXTOS; i++) {

		//Establece el puntero como nulo para poder guardar los textos din�micamente
		textos[i] = nullptr;

	}

}

/////////////////////////////////////////////////////////////

//Crear Panel: M�todo que crea el panel del men�, usando los argumentos suministrados en la llamada
void Menu::crearPanel(Vector2f coordenadas_panel, Vector2f coordenadas_texto, String texto) {

	//Se usan los par�metros recibidos, a�adiendo la escena actual como la seleccionada para a�adir el elemento
	panel = GUIPanel(coordenadas_panel, texto, coordenadas_texto, this);

}

//Crear Boton: Recorre el arreglo de punteros a botones, busca un lugar nulo y si lo encuentra, aloja un nuevo Boton usando los
//argumentos recibidos en la llamada
void Menu::crearBoton(Vector2f coordenadas, Vector2f escala, String* texto, TipoSprite tipo) {

	//Recorre el arreglo de punteros a boton...
	for (int i = 0; i < CANTIDAD_BOTONES; i++) {

		//Si el boton iterador es nulo (Est� vac�o)...
		if (botones[i] == nullptr) {

			//Crea el nuevo bot�n all�, usando los valores recibidos y el men� actual como la escena seleccionada
			botones[i] = new GUIBoton(coordenadas, escala, texto, tipo, this);

			break;

		}

	}

}

//Crear Boton (Sobrecarga 1): Similar al original, pero no recibe valor de escala, en su lugar estableciendo la misma a 1.0f para
//ambos ejes. Usado para crear botones que no requieran variaci�n de escala
void Menu::crearBoton(Vector2f coordenadas, String* texto, TipoSprite tipo) {

	//Recorre el arreglo de punteros a boton...
	for (int i = 0; i < CANTIDAD_BOTONES; i++) {

		//Si el boton iterador es nulo (Est� vac�o)...
		if (botones[i] == nullptr) {

			//Crea el nuevo bot�n all�, usando los valores recibidos y el men� actual como la escena seleccionada
			botones[i] = new GUIBoton(coordenadas, {1.0f, 1.0f}, texto, tipo, this);

			break;

		}

	}

}

//Crear Boton (Sobrecarga 2): Similar al original, pero no recibe valor de escala (fijandola en 1.0f) Y adem�s crear� el bot�n usando
//el �ndice especificado, permite insertar el bot�n en un espacio del arreglo espec�fico
void Menu::crearBoton(Vector2f coordenadas, String* texto, TipoSprite tipo, int indice) {

	//Si el boton iterador es nulo (Est� vac�o)...
	if (botones[indice] == nullptr) {

		//Crea el nuevo bot�n all�, usando los valores recibidos y el men� actual como la escena seleccionada
		botones[indice] = new GUIBoton(coordenadas, { 1.0f, 1.0f }, texto, tipo, this);

	}

}

//Crear Texto: Crea un texto en la direcci�n del arreglo recibida (indice) Usando los argumentos suministrados
void Menu::crearTexto(Vector2f coordenadas, String texto, int dimensiones_caracter, Color color, int indice) {

	//Si el texto iterador es nulo (Est� vac�o)...
	if (textos[indice] == nullptr) {

		//Crea el nuevo texto en dicha direccion usando valores recibidos y la escena actual como seleccionada para el objeto
		textos[indice] = new GUITexto(coordenadas, texto, dimensiones_caracter, color, this);

	}

}

//Borrar Boton: Permite eliminar el bot�n alojado en la direcci�n 'indice' del arreglo de botones
void Menu::borrarBoton(int indice) {

	//Si el indice recibido apunta a un espacio nulo...
	if (botones[indice] == nullptr) {

		//Sale del m�todo, ya que no se puede borrar
		return;

	}

	//Libera la memoria en la ubicaci�n obtenida
	delete botones[indice];

	//Ahora el puntero es nulo y puede volver a usarse de ser necesario
	botones[indice] == nullptr;

}

//Borrar Texto: Recibe un indice usado para borrar un texto del arreglo de punteros a texto
void Menu::borrarTexto(int indice) {

	//Si el indice recibido apunta a un espacio nulo...
	if (textos[indice] == nullptr) {

		//Sale del m�todo debido a que no se puede borrar
		return;

	}

	//Libera la memoria asignada en la ubicaci�n
	delete textos[indice];

	//Asigna puntero nulo, para poder reutilizar el espacio y evitar errores
	textos[indice] == nullptr;

}

/////////////////////////////////////////////////////////////

//Obtener Boton: Devuelve el bot�n correspondiente al espacio 'indice' del arreglo de punteros a boton.
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

	//Sale del m�todo si la escena est� desactivada o si la ventana es nula
	if (!this->estaActiva() || ventana == nullptr) { return; };

	//Llama al m�todo de dibujar para el panel
	panel.dibujarElementos(ventana);

	//Bucle que itera sobre el arreglo de botones...
	for (int i = 0; i < CANTIDAD_BOTONES; i++) {

		//Si el boton iterador es nulo...
		if (botones[i] == nullptr) {

			//Pasa a la siguiente iteraci�n del bucle sin ejecutar nada
			continue;

		}

		//Llama al m�todo de dibujar para el bot�n iterador
		botones[i]->dibujarElementos(ventana);

	}

	//Bucle que itera sobre el arreglo de textos...
	for (int i = 0; i < CANTIDAD_TEXTOS; i++) {

		//Si el boton iterador es nulo...
		if (textos[i] == nullptr) {

			//Pasa a la siguiente iteraci�n del bucle sin ejecutar nada
			continue;

		}

		//Llama al m�todo de dibujar para el bot�n iterador
		textos[i]->dibujarElemento(ventana);

	}

}