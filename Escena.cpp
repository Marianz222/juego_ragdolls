#include "Escena.h"

//Constructor por defecto: Crea la escena con un identificador default (Sin usar)
Escena::Escena() {

	//Asigna el id como default
	identificador = "default";

}

//Constructor principal: Recibe el identificador de la escena como argumento, y la crea asignando dicho id.
Escena::Escena(String id) {

	//Asigna el valor recibido a los atributos de clase
	identificador = id;

}

//Constructor adicional: Recibe tanto el id como si est� activada o no como argumento. �til para escenas inactivas por defecto
Escena::Escena(String id, bool activada) {

	//Asigna los valores recibidos a los atributos de clase
	identificador = id;
	activa = activada;

}

//////////////////////////////////////////////////////////////////

//Estado Activacion: M�todo que recibe un bool como par�metro, y define si la escena est� o no activa en base al mismo
void Escena::estadoActivacion(bool estado) {

	activa = estado;

}

//////////////////////////////////////////////////////////////////

//Esta Activa: Retorna true si la escena est� actualmente activa, y false si no lo est�
bool Escena::estaActiva() {

	return activa;

}

//Obtener Mundo F�sico: Devuelve el mundo f�sico alojado en el puntero. Si el mundo no se usa (Men� de interfaz) Devuelve puntero nulo
b2World* Escena::obtenerMundoFisico() {

	return mundo;

}

//Obtener identificador: Devuelve la cadena de texto que identifica a esta escena, usando el siguiente formato "tipo.nombre"
String Escena::obtenerIdentificador() {

	return identificador;

}

//////////////////////////////////////////////////////////////////

//Restablecer: M�todo virtual que debe sobreescribirse. Este m�todo se usa para reiniciar todos los estados y variables de una escena
//a su estado original. Llamado siempre al cambiar de escena (Con la escena anterior) y puede llamarse en cualquier momento de ser necesario
void Escena::restablecer() {

	//Solo sobreescritura (override)

}

//Actualizar Elementos Alojados: M�todo sencillo en el cual se deben incluir llamadas de actualizaci�n visual y f�sica para los objetos
//que est�n adjuntados a la escena. Este m�todo se ejecuta en bucle, y no se ejecutar� si la escena est� desactivada
void Escena::actualizarElementosAlojados(int unidad_conversion, int ragdolls_activos, int ragdolls_maximos, int puntaje, Vector2i posicion_cursor) {

	//Solo sobreescritura (override)

}

//Renderizar Elementos Alojados: Este m�todo se llama desde la llamada principal a renderizar dentro del bucle del juego, y es el
//encargado de suministrarle a la ventana los elementos dibujables de la escena para poder renderizarlos
void Escena::renderizarElementosAlojados(RenderWindow* ventana) {

	//Solo sobreescritura (override)

}