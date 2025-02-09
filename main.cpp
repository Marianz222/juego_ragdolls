#include <iostream>

//Inclusión de archivos propios
#include "Juego.h"

//Espacios de nombres
using namespace std;

int main() {

    //Crea un objeto de clase Juego y llama a su ejecución
    Juego* juego = new Juego("Juego de Ragdolls");
    juego->ejecutar();

    return 0;

}
