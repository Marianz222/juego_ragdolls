#include "Juego.h"

//Constructor: Acepta como par�metros la dimension y el nombre de la ventana para el programa. Inicializa las variables y
//llama a m�todos de inicializaci�n
Juego::Juego(string nombre_programa) {

	//Iguala la variable de nombre
	nombre_ventana = nombre_programa;

	//Asigna una nueva ventana a la variable existente
	ventana = crearVentana(DIMENSIONES_VENTANA.x, DIMENSIONES_VENTANA.y, nombre_ventana);

	//Instancia el gestor de eventos
	gestor_eventos = new Event;

	//Llama a la creaci�n de cada escena (Men�es y Niveles)
	crearEscenas();

	//Llama a configurar el texto de victoria/derrota
	configurarTextoFinal();

}

//Crear Escenas: M�todo que se encarga de instanciar todas las escenas, tanto men�es como niveles.
void Juego::crearEscenas() {

	//inicializa el gestor de escenas
	gestor_escenas = new GestorEscenas();

	/////////////////////////////////

	//MEN� PRINCIPAL

	//Almacena la mitad de las dimensiones de la ventana
	Vector2f centro_ventana = { (float(DIMENSIONES_VENTANA.x) / 2), (float(DIMENSIONES_VENTANA.y) / 2) };

	//Datos de instanciaci�n para el men�
	string identificador_menu_principal = "menu.menu_principal";

	//Crea el men� principal, almacenandolo en el arreglo
	menues[0] = new Menu(identificador_menu_principal, true);

	//Crea el panel y todos los botones
	menues[0]->crearPanel(centro_ventana, { 0.0f, -430.0f }, "Menu Inicio");
	menues[0]->crearBoton({ centro_ventana.x, centro_ventana.y - 250.0f }, new String("Jugar"), TipoSprite::RECTANGULAR, 0);
	menues[0]->crearBoton({ centro_ventana.x, centro_ventana.y - 050.0f }, new String("Instrucciones"), TipoSprite::RECTANGULAR, 1);
	menues[0]->crearBoton({ centro_ventana.x, centro_ventana.y + 150.0f }, new String("Objetivo"), TipoSprite::RECTANGULAR, 2);
	menues[0]->crearBoton({ centro_ventana.x, centro_ventana.y + 350.0f }, new String("Salir"), TipoSprite::RECTANGULAR, 3);

	/////////////////////////////////

	//MEN� INFORMACI�N

	//Datos de instanciaci�n para el men�
	string identificador_menu_informacion = "menu.informacion";

	//Crea el men� de informaci�n
	menues[1] = new Menu(identificador_menu_informacion, false);

	//Crea el panel y a�ade un �nico bot�n de salida
	menues[1]->crearPanel(centro_ventana, { 0.0f, -430.0f }, "Instrucciones");
	menues[1]->crearBoton({ 100.0f, 100.0f }, nullptr, TipoSprite::SALIR, 0);

	//Arreglo que almacena todo el texto del panel de informaci�n
	String menu_informacion_texto[9]{

		"En este juego recorrer�s m�ltiples niveles",
		"Que tendr�s que superar en sucesi�n.",
		" ",
		"Pulsa [Click Izquierdo] para disparar.",
		"Mientras m�s alejes el cursor del ca��n",
		"m�s velocidad tomar� el mu�eco disparado",
		" ",
		"Mant�n un ojo en tu munici�n",
		"Ya que no es infinita."

	};

	//Crea cada linea de texto, haciendo un offset para las posiciones, usando la informaci�n del arreglo y variando color
	menues[1]->crearTexto({ centro_ventana.x, centro_ventana.y - 240.0f }, menu_informacion_texto[0], 36, Color::White, 0);
	menues[1]->crearTexto({ centro_ventana.x, centro_ventana.y - 180.0f }, menu_informacion_texto[1], 36, Color::White, 1);
	menues[1]->crearTexto({ centro_ventana.x, centro_ventana.y - 120.0f }, menu_informacion_texto[2], 36, Color::White, 2);
	menues[1]->crearTexto({ centro_ventana.x, centro_ventana.y - 60.0f }, menu_informacion_texto[3], 36, Color::White, 3);
	menues[1]->crearTexto(centro_ventana, menu_informacion_texto[4], 36, Color::White, 4);
	menues[1]->crearTexto({ centro_ventana.x, centro_ventana.y + 60.0f }, menu_informacion_texto[5], 36, Color::White, 5);
	menues[1]->crearTexto({ centro_ventana.x, centro_ventana.y + 120.0f }, menu_informacion_texto[6], 36, Color::White, 6);
	menues[1]->crearTexto({ centro_ventana.x, centro_ventana.y + 180.0f }, menu_informacion_texto[7], 36, Color::Yellow, 7);
	menues[1]->crearTexto({ centro_ventana.x, centro_ventana.y + 240.0f }, menu_informacion_texto[8], 36, Color(225, 140, 80), 8);

	/////////////////////////////////

	//MEN� OBJETIVOS

	//Datos de instanciaci�n para el men�
	string identificador_menu_objetivos = "menu.objetivos";

	//Crea el men� de objetivos
	menues[2] = new Menu(identificador_menu_objetivos, false);

	//Crea el panel y a�ade un �nico bot�n de salida
	menues[2]->crearPanel(centro_ventana, { 0.0f, -430.0f }, "Objetivo");
	menues[2]->crearBoton({ 100.0f, 100.0f }, nullptr, TipoSprite::SALIR, 0);

	//Arreglo que almacena todo el texto del panel de objetivos
	String menu_objetivos_texto[9]{

		"Para superar los niveles, deber�s",
		"activar todos los Puntos de Control.",
		" ",
		"Los puntos se activan si un mu�eco",
		"o una caja entran en contacto con ellos.",
		"No se requiere puntaje espec�fico",
		" ",
		"Al final del nivel, la munici�n",
		"Restante se convierte en puntos extra."

	};

	//Crea cada linea de texto, haciendo un offset para las posiciones, usando la informaci�n del arreglo y variando color
	menues[2]->crearTexto({ centro_ventana.x, centro_ventana.y - 240.0f }, menu_objetivos_texto[0], 36, Color::White, 0);
	menues[2]->crearTexto({ centro_ventana.x, centro_ventana.y - 180.0f }, menu_objetivos_texto[1], 36, Color::White, 1);
	menues[2]->crearTexto({ centro_ventana.x, centro_ventana.y - 120.0f }, menu_objetivos_texto[2], 36, Color::White, 2);
	menues[2]->crearTexto({ centro_ventana.x, centro_ventana.y - 60.0f }, menu_objetivos_texto[3], 36, Color::White, 3);
	menues[2]->crearTexto(centro_ventana, menu_objetivos_texto[4], 36, Color::White, 4);
	menues[2]->crearTexto({ centro_ventana.x, centro_ventana.y + 60.0f }, menu_objetivos_texto[5], 36, Color::White, 5);
	menues[2]->crearTexto({ centro_ventana.x, centro_ventana.y + 120.0f }, menu_objetivos_texto[6], 36, Color::White, 6);
	menues[2]->crearTexto({ centro_ventana.x, centro_ventana.y + 180.0f }, menu_objetivos_texto[7], 36, Color(120, 255, 120), 7);
	menues[2]->crearTexto({ centro_ventana.x, centro_ventana.y + 240.0f }, menu_objetivos_texto[8], 36, Color(120, 255, 120), 8);

	/////////////////////////////////

	//NIVELES

	//Datos de instanciaci�n de niveles (Posici�n del arma y cadena de texto identificadora)
	Vector2f ubicacion_arma[3] = { {200.0f, 975.0f}, {1750.0f, 975.0f}, {175.0f, 525.0f} };
	String identificador_nivel[3] = { "nivel.primer_nivel", "nivel.segundo_nivel", "nivel.tercer_nivel" };

	//Itera sobre los 3 niveles del juego
	for (int i = 0; i < 3; i++) {

		//Crea todos los niveles, almacenandolos en el arreglo y desactivandolos (se activar�n despu�s a su tiempo)
		niveles[i] = new Nivel(ubicacion_arma[i], identificador_nivel[i], PIXELES_POR_METRO, DIMENSIONES_VENTANA, false);

	}

}

//Generar Nivel: Funci�n pasamano que llama a generar los niveles (m�todos internos) Dependiendo de qu� valor reciba
void Juego::generarNivel(int numero) {

	//Switch para el valor recibido
	switch (numero) {

	case 1: //Caso: Nivel 1

		//Llama a generar el nivel 1
		generarNivel1();

		break;

	case 2: //Caso: Nivel 2

		//Llama a generar el nivel 2
		generarNivel2();

		break;

	case 3: //Caso: Nivel 3

		//Llama a generar el nivel 3
		generarNivel3();

		break;

	}

}

//Generar Nivel 1: Crea todos los obst�culos para el primer nivel del juego, ajusta sus propiedades como rotaci�n, posici�n y dem�s
void Juego::generarNivel1() {

	//Si el nivel que est� a punto de generarse es nulo...
	if (niveles[0] == nullptr) {

		//Cancela la generaci�n, omitiendo todo el c�digo
		return;

	}

	//Guarda un arreglo que contiene el directorio de cada textura a utilizar
	String directorio_texturas[6]{

		"assets/images/ladrillos_piedra.png",
		"assets/images/metal.png",
		"assets/images/madera.png",
		"assets/images/ladrillos_piedra_dinamicos.png",
		"assets/images/rebotador_vertical.png",
		"assets/images/rebotador_horizontal.png"

	};

	//Guarda el tama�o de las plataformas
	Vector2f dimensiones_plataforma[6] = {

		{50.0f, 350.0f},
		{550.0f, 50.0f},
		{50.0f, 350.0f},
		{300.0f, 50.0f},
		{50.0f, 250.0f},
		{200.0f, 50.0f}

	};

	//Guarda el tama�o de las cajas din�micas
	Vector2f dimensiones_caja[3] = {

		{50.0f, 50.0f},
		{75.0f, 75.0f},
		{100.0f, 100.0f}

	};

	//Guarda el tama�o de las rampas
	Vector2f dimensiones_rampa[3] = {

		{450.0f, 50.0f},
		{150.0f, 50.0f},
		{200.0f, 50.0f}

	};

	//Guarda una referencia al mundo del nivel actual
	b2World* mundo_actual = niveles[0]->obtenerMundoFisico();
	
	//Inserta todos los obst�culos al nivel, usando datos recibidos y determinando la posici�n manualmente
	
	//Inserta las rampas
	niveles[0]->insertarObstaculo(directorio_texturas[1], dimensiones_rampa[0], { 1350.0f, 850.0f }, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_kinematicBody, PIXELES_POR_METRO); //Rampa larga de suelo
	niveles[0]->insertarObstaculo(directorio_texturas[5], dimensiones_rampa[2], { 1800.0f, 450.0f }, 0.5f, 1.5f, mundo_actual, b2BodyType::b2_kinematicBody, PIXELES_POR_METRO); //Trampol�n chico
	niveles[0]->insertarObstaculo(directorio_texturas[1], dimensiones_rampa[1], { 650.0f, 120.0f }, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_kinematicBody, PIXELES_POR_METRO); //Rampa chica central
	
	//Inserta los obst�culos est�ticos
	niveles[0]->insertarObstaculo(directorio_texturas[0], dimensiones_plataforma[0], {1600.0f, 850.0f}, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_staticBody, PIXELES_POR_METRO); //Pared derecha
	niveles[0]->insertarObstaculo(directorio_texturas[0], dimensiones_plataforma[1], {1000.0f, 550.0f}, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_staticBody, PIXELES_POR_METRO); //Plataforma horizontal central
	niveles[0]->insertarObstaculo(directorio_texturas[0], dimensiones_plataforma[2], {750.0f, 350.0f}, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_staticBody, PIXELES_POR_METRO); //Pared central
	niveles[0]->insertarObstaculo(directorio_texturas[0], dimensiones_plataforma[3], {300.0f, 300.0f}, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_staticBody, PIXELES_POR_METRO); //Plataforma horizontal izquierda
	niveles[0]->insertarObstaculo(directorio_texturas[0], dimensiones_plataforma[4], {250.0f, 450.0f}, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_staticBody, PIXELES_POR_METRO); //Pared izquierda
	niveles[0]->insertarObstaculo(directorio_texturas[0], dimensiones_plataforma[5], { 150.0f, 550.0f }, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_staticBody, PIXELES_POR_METRO); //Plataforma horizontal izquierda

	//Inserta las cajas
	niveles[0]->insertarObstaculo(directorio_texturas[2], dimensiones_caja[1], {350.0f, 200.0f}, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_dynamicBody, PIXELES_POR_METRO); //Caja Mediana #1
	niveles[0]->insertarObstaculo(directorio_texturas[2], dimensiones_caja[0], { 350.0f, 120.0f }, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_dynamicBody, PIXELES_POR_METRO); //Caja Chica #1
	niveles[0]->insertarObstaculo(directorio_texturas[2], dimensiones_caja[2], { 950.0f, 950.0f }, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_dynamicBody, PIXELES_POR_METRO); //Caja Grande #1
	niveles[0]->insertarObstaculo(directorio_texturas[2], dimensiones_caja[2], { 950.0f, 900.0f }, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_dynamicBody, PIXELES_POR_METRO); //Caja Grande #2
	niveles[0]->insertarObstaculo(directorio_texturas[2], dimensiones_caja[1], { 950.0f, 850.0f }, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_dynamicBody, PIXELES_POR_METRO); //Caja Mediana #2

	//Asigna la rotaci�n de las rampas
	niveles[0]->retornarObstaculo(0)->modificarRotacion(-40.0f);
	niveles[0]->retornarObstaculo(1)->modificarRotacion(80.0f);
	niveles[0]->retornarObstaculo(2)->modificarRotacion(40.0f);

	//Inserta los puntos de control
	niveles[0]->insertarPuntoControl({ 135.0f, 425.0f });
	niveles[0]->insertarPuntoControl({ 900.0f, 425.0f });
	niveles[0]->insertarPuntoControl({ 1750.0f, 925.0f });

	//Itera sobre cada elemento del arreglo de obst�culos
	for (int i = 0; i < niveles[0]->retornarObstaculosMaximos(); i++) {

		//Si el obst�culo iterador es nulo...
		if (niveles[0]->retornarObstaculo(i) == nullptr) {

			//Salta a la siguiente iteraci�n del bucle (Se omite la aplicaci�n de fuerza)
			continue;

		}

		//Aplica la fuerza inicial a todos los objetos (Solo reaccionar�n los din�micos)
		niveles[0]->retornarObstaculo(i)->aplicarFuerza({ 0.0f, 10.0f });

	}

}

//Generar Nivel 2: Crea todos los obst�culos para el primer nivel del juego, ajusta sus propiedades como rotaci�n, posici�n y dem�s
void Juego::generarNivel2() {

	//Si el nivel que est� a punto de generarse es nulo...
	if (niveles[1] == nullptr) {

		//Cancela la generaci�n, omitiendo todo el c�digo
		return;

	}

	//Guarda un arreglo que contiene el directorio de cada textura a utilizar
	String directorio_texturas[6]{

		"assets/images/ladrillos_piedra.png",
		"assets/images/metal.png",
		"assets/images/madera.png",
		"assets/images/ladrillos_piedra_dinamicos.png",
		"assets/images/rebotador_vertical.png",
		"assets/images/rebotador_horizontal.png"

	};

	//Guarda el tama�o de las plataformas
	Vector2f dimensiones_plataforma[5] = {

		{900.0f, 50.0f},
		{50.0f, 350.0f},
		{1350.0f, 50.0f},
		{50.0f, 275.0f},
		{50.0f, 300.0f},

	};

	//Guarda el tama�o de las cajas din�micas
	Vector2f dimensiones_caja[3] = {

		{50.0f, 50.0f},
		{75.0f, 75.0f},
		{100.0f, 100.0f}

	};

	//Guarda el tama�o de las rampas
	Vector2f dimensiones_rampa[1] = {

		{250.0f, 50.0f}

	};

	//Guarda una referencia al mundo del nivel actual
	b2World* mundo_actual = niveles[1]->obtenerMundoFisico();

	//Inserta todos los obst�culos al nivel, usando datos recibidos y determinando la posici�n manualmente

	//Inserta las rampas
	niveles[1]->insertarObstaculo(directorio_texturas[1], dimensiones_rampa[0], {150.0f, 450.0f}, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_kinematicBody, PIXELES_POR_METRO); //Rampa principal

	//Inserta los dispositivos
	niveles[1]->insertarObstaculo(directorio_texturas[5], dimensiones_rampa[0], { 150.0f, 900.0f }, 0.6f, 5.0f, mundo_actual, b2BodyType::b2_kinematicBody, PIXELES_POR_METRO); //Rebotador inclinado
	niveles[1]->insertarObstaculo(directorio_texturas[3], dimensiones_plataforma[3], {1250.0f, 850.0f}, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_dynamicBody, PIXELES_POR_METRO); //Pared Rotatoria #1
	niveles[1]->insertarObstaculo(directorio_texturas[3], dimensiones_plataforma[3], { 800.0f, 850.0f }, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_dynamicBody, PIXELES_POR_METRO); //Pared Rotatoria #2
	niveles[1]->insertarObstaculo(directorio_texturas[3], dimensiones_plataforma[4], { 1250.0f, 475.0f }, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_dynamicBody, PIXELES_POR_METRO); //Pared Rotatoria #3

	//Soporte est�tico de dispositivos
	niveles[1]->insertarObstaculo(directorio_texturas[0], dimensiones_caja[0], { 1250.0f, 875.0f }, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_staticBody, PIXELES_POR_METRO); //Soporte pared rotatoria #1
	niveles[1]->insertarObstaculo(directorio_texturas[0], dimensiones_caja[0], { 800.0f, 875.0f }, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_staticBody, PIXELES_POR_METRO); //Soporte pared rotatoria #2
	niveles[1]->insertarObstaculo(directorio_texturas[0], dimensiones_caja[0], { 1250.0f, 500.0f }, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_staticBody, PIXELES_POR_METRO); //Soporte pared rotatoria #3

	//Inserta y configura los enlaces para los dispositivos
	niveles[1]->insertarEnlace(b2JointType::e_revoluteJoint, {}, niveles[1]->retornarObstaculo(2), niveles[1]->retornarObstaculo(5), niveles[1]->retornarObstaculo(2)->retornarCuerpo()->GetLocalCenter(), niveles[1]->retornarObstaculo(5)->retornarCuerpo()->GetLocalCenter(), mundo_actual, PIXELES_POR_METRO); //Enlace #1
	niveles[1]->retornarEnlace(0)->activarMotor(true, 0.04f, 2.0f); //Activa el motor para que el objeto rote constantemente
	niveles[1]->retornarEnlace(0)->limitar(false); //Desactiva el l�mite para que pueda girar 360 grados
	//
	niveles[1]->insertarEnlace(b2JointType::e_revoluteJoint, {}, niveles[1]->retornarObstaculo(3), niveles[1]->retornarObstaculo(6), niveles[1]->retornarObstaculo(3)->retornarCuerpo()->GetLocalCenter(), niveles[1]->retornarObstaculo(6)->retornarCuerpo()->GetLocalCenter(), mundo_actual, PIXELES_POR_METRO); //Enlace #2
	niveles[1]->retornarEnlace(1)->activarMotor(true, 0.04f, 2.0f); //Activa el motor para que el objeto rote constantemente
	niveles[1]->retornarEnlace(1)->limitar(false); //Desactiva el l�mite para que pueda girar 360 grados
	//
	niveles[1]->insertarEnlace(b2JointType::e_revoluteJoint, {}, niveles[1]->retornarObstaculo(4), niveles[1]->retornarObstaculo(7), niveles[1]->retornarObstaculo(4)->retornarCuerpo()->GetLocalCenter(), niveles[1]->retornarObstaculo(7)->retornarCuerpo()->GetLocalCenter(), mundo_actual, PIXELES_POR_METRO); //Enlace #3
	niveles[1]->retornarEnlace(2)->activarMotor(true, 0.04f, 2.0f); //Activa el motor para que el objeto rote constantemente
	niveles[1]->retornarEnlace(2)->limitar(false); //Desactiva el l�mite para que pueda girar 360 grados

	//Inserta los obst�culos est�ticos
	niveles[1]->insertarObstaculo(directorio_texturas[0], dimensiones_plataforma[0], {1000.0f, 700.0f}, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_staticBody, PIXELES_POR_METRO); //Plataforma mediana
	niveles[1]->insertarObstaculo(directorio_texturas[0], dimensiones_plataforma[1], { 850.0f, 500.0f }, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_staticBody, PIXELES_POR_METRO); //Pared central
	niveles[1]->insertarObstaculo(directorio_texturas[0], dimensiones_plataforma[2], { 700.0f, 300.0f }, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_staticBody, PIXELES_POR_METRO); //Plataforma larga

	//Inserta las cajas 
	niveles[1]->insertarObstaculo(directorio_texturas[2], dimensiones_caja[1], {600.0f, 600.0f}, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_dynamicBody, PIXELES_POR_METRO); //Caja mediana #1
	niveles[1]->insertarObstaculo(directorio_texturas[2], dimensiones_caja[1], { 1250.0f, 175.0f }, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_dynamicBody, PIXELES_POR_METRO); //Caja mediana #2
	niveles[1]->insertarObstaculo(directorio_texturas[2], dimensiones_caja[0], { 1300.0f, 175.0f }, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_dynamicBody, PIXELES_POR_METRO); //Caja chica #1
	niveles[1]->insertarObstaculo(directorio_texturas[2], dimensiones_caja[0], { 1250.0f, 150.0f }, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_dynamicBody, PIXELES_POR_METRO); //Caja chica #2
	niveles[1]->insertarObstaculo(directorio_texturas[2], dimensiones_caja[0], { 1250.0f, 125.0f }, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_dynamicBody, PIXELES_POR_METRO); //Caja chica #3

	//Asigna la rotaci�n de las rampas
	niveles[1]->retornarObstaculo(0)->modificarRotacion(-45.0f);
	niveles[1]->retornarObstaculo(1)->modificarRotacion(55.0f);

	//Inserta los puntos de control
	niveles[1]->insertarPuntoControl({ 950.0f, 575.0f });
	niveles[1]->insertarPuntoControl({ 750.0f, 575.0f });
	niveles[1]->insertarPuntoControl({ 350.0f, 175.0f });

	//Itera sobre cada elemento del arreglo de obst�culos
	for (int i = 0; i < niveles[1]->retornarObstaculosMaximos(); i++) {

		//Si el obst�culo iterador es nulo...
		if (niveles[1]->retornarObstaculo(i) == nullptr) {

			//Salta a la siguiente iteraci�n del bucle (Se omite la aplicaci�n de fuerza)
			continue;

		}

		//Aplica la fuerza inicial a todos los objetos (Solo reaccionar�n los din�micos)
		niveles[1]->retornarObstaculo(i)->aplicarFuerza({ 0.0f, 10.0f });

	}

}

//Generar Nivel 3: Crea todos los obst�culos para el primer nivel del juego, ajusta sus propiedades como rotaci�n, posici�n y dem�s
void Juego::generarNivel3() {

	//Si el nivel que est� a punto de generarse es nulo...
	if (niveles[2] == nullptr) {

		//Cancela la generaci�n, omitiendo todo el c�digo
		return;

	}

	//Guarda un arreglo que contiene el directorio de cada textura a utilizar
	String directorio_texturas[6]{

		"assets/images/ladrillos_piedra.png",
		"assets/images/metal.png",
		"assets/images/madera.png",
		"assets/images/ladrillos_piedra_dinamicos.png",
		"assets/images/rebotador_vertical.png",
		"assets/images/rebotador_horizontal.png"

	};

	//Guarda el tama�o de las plataformas
	Vector2f dimensiones_plataforma[9] = {

		{300.0f, 50.0f},
		{50.0f, 450.0f},
		{150.0f, 50.0f},
		{50.0f, 150.0f},
		{900.0f, 50.0f},
		{50.0f, 200.0f},
		{350.0f, 50.0f},
		{250.0f, 50.0f},
		{50.0f, 250.0f}

	};

	//Guarda el tama�o de las cajas din�micas
	Vector2f dimensiones_caja[3] = {

		{50.0f, 50.0f},
		{75.0f, 75.0f},
		{100.0f, 100.0f}

	};

	//Guarda el tama�o de las rampas
	Vector2f dimensiones_rampa[1] = {

		{250.0f, 50.0f}

	};

	//Guarda una referencia al mundo del nivel actual
	b2World* mundo_actual = niveles[2]->obtenerMundoFisico();

	//Inserta todos los obst�culos al nivel, usando datos recibidos y determinando la posici�n manualmente

	//Inserta las rampas
	niveles[2]->insertarObstaculo(directorio_texturas[1], dimensiones_rampa[0], {1575.0f, 650.0f}, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_kinematicBody, PIXELES_POR_METRO); //Rampa

	//Inserta los dispositivos
	niveles[2]->insertarObstaculo(directorio_texturas[3], dimensiones_caja[1], { 400.0f, 375.0f }, 0.3f, 0.8f, mundo_actual, b2BodyType::b2_dynamicBody, PIXELES_POR_METRO); //Cubo suspendido
	niveles[2]->insertarObstaculo(directorio_texturas[4], dimensiones_plataforma[1], {75.0f, 800.0f}, 0.8f, 3.0f, mundo_actual, b2BodyType::b2_staticBody, PIXELES_POR_METRO); //Rebotador grande
	niveles[2]->insertarObstaculo(directorio_texturas[4], dimensiones_plataforma[3], { 800.0f, 750.0f }, 0.8f, 3.0f, mundo_actual, b2BodyType::b2_staticBody, PIXELES_POR_METRO); //Rebotador chico
	niveles[2]->insertarObstaculo(directorio_texturas[3], dimensiones_plataforma[5], {1300.0f, 200.0f}, 0.3f, 0.8f, mundo_actual, b2BodyType::b2_dynamicBody, PIXELES_POR_METRO); //Plataforma rotatoria
	niveles[2]->insertarObstaculo(directorio_texturas[3], dimensiones_plataforma[6], {1162.5f, 750.0f}, 0.3f, 0.2f, mundo_actual, b2BodyType::b2_dynamicBody, PIXELES_POR_METRO); //Plataforma de presi�n
	
	//Edita los dispositivos
	niveles[2]->retornarObstaculo(5)->modificarDensidad(0.2f);

	//Soporte est�tico para dispositivos
	niveles[2]->insertarObstaculo(directorio_texturas[0], dimensiones_caja[0], { 400.0f, 250.0f }, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_staticBody, PIXELES_POR_METRO); //Base para cubo suspendido
	niveles[2]->insertarObstaculo(directorio_texturas[0], dimensiones_caja[0], {1300.0f, 200.0f}, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_staticBody, PIXELES_POR_METRO); //Base para plataforma rotatoria
	niveles[2]->insertarObstaculo(directorio_texturas[0], dimensiones_caja[0], { 1162.5f, 600.0f }, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_staticBody, PIXELES_POR_METRO); //Base para plataforma a presi�n

	//Inserta y configura los enlaces para los dispositivos
	niveles[2]->insertarEnlace(b2JointType::e_distanceJoint, {}, niveles[2]->retornarObstaculo(1), niveles[2]->retornarObstaculo(6), niveles[2]->retornarObstaculo(1)->retornarCuerpo()->GetLocalCenter(), niveles[2]->retornarObstaculo(6)->retornarCuerpo()->GetLocalCenter(), mundo_actual, PIXELES_POR_METRO); //Enlace cubo suspendido
	niveles[2]->retornarEnlace(0)->establecerLongitud(TipoLongitud::MINIMA, 3.25f); //Asigna la longitud minima
	niveles[2]->retornarEnlace(0)->establecerLongitud(TipoLongitud::MAXIMA, 3.5f); //Asigna la longitud m�xima

	//Inserta y configura los enlaces para los dispositivos
	niveles[2]->insertarEnlace(b2JointType::e_revoluteJoint, {}, niveles[2]->retornarObstaculo(4), niveles[2]->retornarObstaculo(7), niveles[2]->retornarObstaculo(4)->retornarCuerpo()->GetLocalCenter(), niveles[2]->retornarObstaculo(7)->retornarCuerpo()->GetLocalCenter(), mundo_actual, PIXELES_POR_METRO); //Enlace plataforma rotatoria
	niveles[2]->retornarEnlace(1)->activarMotor(true, -0.05f, 2.0f); //Activa el motor para que el objeto rote constantemente
	niveles[2]->retornarEnlace(1)->limitar(false); //Desactiva el l�mite

	niveles[2]->insertarEnlace(b2JointType::e_prismaticJoint, {0.0f, 1.0f}, niveles[2]->retornarObstaculo(5), niveles[2]->retornarObstaculo(8), niveles[2]->retornarObstaculo(5)->retornarCuerpo()->GetLocalCenter(), niveles[2]->retornarObstaculo(8)->retornarCuerpo()->GetLocalCenter(), mundo_actual, PIXELES_POR_METRO); //Enlace plataforma a presi�n
	niveles[2]->retornarEnlace(2)->limitar(true); //Activa los l�mites
	niveles[2]->retornarEnlace(2)->establecerLimites({-10.0f, -3.0f}); //Establece el l�mite en metros
	niveles[2]->retornarEnlace(2)->activarMotor(true, 0.001f, 0.08f); //Activa el motor para que la plataforma pueda volver a subir tras recibir presi�n

	//Crea los obst�culos est�ticos
	niveles[2]->insertarObstaculo(directorio_texturas[0], dimensiones_plataforma[0], {175.0f, 300.0f}, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_staticBody, PIXELES_POR_METRO);
	niveles[2]->insertarObstaculo(directorio_texturas[0], dimensiones_caja[0], {300.0f, 250.0f}, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_staticBody, PIXELES_POR_METRO);
	niveles[2]->insertarObstaculo(directorio_texturas[0], dimensiones_caja[2], { 75.0f, 525.0f }, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_staticBody, PIXELES_POR_METRO);
	niveles[2]->insertarObstaculo(directorio_texturas[0], dimensiones_plataforma[2], { 900.0f, 750.0f }, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_staticBody, PIXELES_POR_METRO);
	niveles[2]->insertarObstaculo(directorio_texturas[0], dimensiones_plataforma[4], { 1450.0f, 350.0f }, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_staticBody, PIXELES_POR_METRO);
	niveles[2]->insertarObstaculo(directorio_texturas[0], dimensiones_plataforma[6], { 1525.0f, 750.0f }, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_staticBody, PIXELES_POR_METRO);
	niveles[2]->insertarObstaculo(directorio_texturas[0], dimensiones_plataforma[7], { 1775.0f, 700.0f }, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_staticBody, PIXELES_POR_METRO);
	niveles[2]->insertarObstaculo(directorio_texturas[0], dimensiones_plataforma[5], { 1675.0f, 575.0f }, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_staticBody, PIXELES_POR_METRO);
	niveles[2]->insertarObstaculo(directorio_texturas[0], dimensiones_plataforma[8], { 850.0f, 900.0f }, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_staticBody, PIXELES_POR_METRO);

	//Crea las cajas
	niveles[2]->insertarObstaculo(directorio_texturas[2], dimensiones_caja[0], {300.0f, 175.0f}, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_dynamicBody, PIXELES_POR_METRO); //Caja chica #1
	niveles[2]->insertarObstaculo(directorio_texturas[2], dimensiones_caja[0], { 300.0f, 150.0f }, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_dynamicBody, PIXELES_POR_METRO); //Caja chica #2
	niveles[2]->insertarObstaculo(directorio_texturas[2], dimensiones_caja[0], { 1500.0f, 250.0f }, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_dynamicBody, PIXELES_POR_METRO); //Caja chica #3
	niveles[2]->insertarObstaculo(directorio_texturas[2], dimensiones_caja[2], { 900.0f, 600.0f }, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_dynamicBody, PIXELES_POR_METRO); //Caja grande #1
	niveles[2]->insertarObstaculo(directorio_texturas[2], dimensiones_caja[0], { 1675.0f, 400.0f }, 0.12f, 0.8f, mundo_actual, b2BodyType::b2_dynamicBody, PIXELES_POR_METRO); //Caja chica #4

	//Asigna la rotaci�n de las rampas
	niveles[2]->retornarObstaculo(0)->modificarRotacion(-45.0f);

	//Inserta los puntos de control
	niveles[2]->insertarPuntoControl({ 158.0f, 175.0f });
	niveles[2]->insertarPuntoControl({ 200.0f, 925.0f });
	niveles[2]->insertarPuntoControl({ 1800.0f, 225.0f });
	niveles[2]->insertarPuntoControl({ 1800.0f, 925.0f });
	niveles[2]->insertarPuntoControl({ 1800.0f, 575.0f });

	//Itera sobre cada elemento del arreglo de obst�culos
	for (int i = 0; i < niveles[2]->retornarObstaculosMaximos(); i++) {

		//Si el obst�culo iterador es nulo...
		if (niveles[2]->retornarObstaculo(i) == nullptr) {

			//Salta a la siguiente iteraci�n del bucle (Se omite la aplicaci�n de fuerza)
			continue;

		}

		//Aplica la fuerza inicial a todos los objetos (Solo reaccionar�n los din�micos)
		niveles[2]->retornarObstaculo(i)->aplicarFuerza({ 0.0f, 10.0f });

	}

}

//Configurar Texto Final: Se encarga de establecer los atributos del texto de condici�n de victoria
void Juego::configurarTextoFinal() {

	//Crea el texto de victoria/derrota centrado en pantalla, sin texto ni color y con tama�o de 64 pixeles
	texto_fin_juego = new GUITexto({float(DIMENSIONES_VENTANA.x) / 2, float(DIMENSIONES_VENTANA.y) / 2 }, "Default", 128, Color::White, nullptr);
	texto_fin_juego->definirColorBorde(Color::Black);
	texto_fin_juego->definirGrosorBorde(5.0f);

}

//Eliminar Ragdoll: M�todo simple que permite eliminar ragdolls del arreglo de apuntadores, llamando a la eliminaci�n de sus componentes y enlaces.
//Recibe como par�metro el tipo de operaci�n (enumeracion) usada para la ejecuci�n. Se puede usar "UNO" para borrar el ragdoll m�s nuevo.
//O se puede utilizar "TODOS" para eliminar todos los ragdolls del arreglo a la vez
void Juego::eliminarRagdoll(OperacionEliminacion operacion) {

	// Itera sobre todo el arreglo de ragdolls
	for (int i = 0; i < LIMITE_RAGDOLLS; i++) {

		//Si el ragdoll iterador es nulo...
		if (ragdolls[i] == nullptr) {

			//Aborta el procedimiento, evitando el c�digo restante. El espacio seleccionado no tiene ningun ragdoll para eliminar
			continue;

		}

		// Obtener la escena del ragdoll
		Escena* escena_ragdoll = ragdolls[i]->retornarEscenaAdjunta();

		//Si la escena del ragdoll iterador es nula...
		if (escena_ragdoll == nullptr) {

			//Aborta el procedimiento, evitando el c�digo restante
			continue;

		}

		//Recupera y almacena el mundo del ragdoll iterador para acceso r�pido
		b2World* mundo_ragdoll = escena_ragdoll->obtenerMundoFisico();

		//Si el mundo del ragdoll iterador es nulo...
		if (mundo_ragdoll == nullptr) {

			//Omite la ejecuci�n del c�digo restante, saliendo inmediatamente
			continue;

		}

		//Llama a eliminar los poligonos y los enlaces que conforman el ragdoll
		ragdolls[i]->destruirEnlaces(mundo_ragdoll);
		ragdolls[i]->destruirComponentes(mundo_ragdoll);

		//Libera la memoria del espacio ocupado por el ragdoll iterador
		delete ragdolls[i];

		//Establece el ragdoll iterador como nulo
		ragdolls[i] = nullptr;

		//Si la operaci�n es de eliminar un �nico Ragdoll...
		if (operacion == OperacionEliminacion::UNO) {

			//Rompe el bucle, para evitar que se siga iterando sobre los dem�s ragdolls
			break;

		}
	}
}

//Disparar Arma Activa: Este m�todo crea un arreglo de punteros a arma, obtiene todas las armas de todos los niveles para luego
//verificar cu�l de todas ellas est� en una escena activa. La que est� activa recibir� la directiva de disparar (Ignorando las dem�s)
void Juego::dispararArmaActiva(int unidad_conversion, b2World* mundo, int limite_aparicion) {

	//Si el arma activa no es nula...
	if (arma_activa != nullptr) {

		//Bucle que itera sobre los niveles del juego
		for (int i = 0; i < CANTIDAD_NIVELES; i++) {

			//Bucle que itera sobre cada bot�n dentro del nivel iterador
			for (int k = 0; k < niveles[i]->retornarBotonesMaximos(); k++) {

				//Si el bot�n iterador est� en contacto con el cursor...
				if (niveles[i]->obtenerBoton(k)->revisarColisionesPorUbicacion(Vector2f(Mouse::getPosition()))) {

					//Anula el disparo del ragdoll, notificandolo por consola y usando return para salir del m�todo
					cout << "[INFO]: Anulando disparo - Motivo: Disparo sobre un bot�n" << endl;

					return;

				}

			}

		}

		//Almacena la escena y el mundo f�sico donde est� alojada el arma iteradora
		Escena* escena_arma = arma_activa->retornarEscenaAdjunta();

		//Si el arma sobre la que se itera est� en una escena activa y su mundo no es nulo...
		if (escena_arma != nullptr && escena_arma->estaActiva() && mundo != nullptr) {

			//Ejecuta el disparo del arma seleccionada, pasando los argumentos necesarios
			arma_activa->dispararRagdoll(arma_activa->obtenerRielDisparo().retornarPosicion(), unidad_conversion, mundo, limite_aparicion, ragdolls, escena_arma);

		}

	}

}

//Aplicar Fuerza: M�todo que permite aplicar una fuerza lineal al cuerpo suministrado por par�metro, usando el valor
void Juego::aplicarFuerza(b2Body* cuerpo, b2Vec2 valor) {

	//Se aplica el impulso lineal (valor) al cuerpo en el punto de origen elegido, despertandolo si est� dormido
	cuerpo->ApplyForceToCenter(valor, true);

}

//Ejecutar: M�todo de bucle principal, en �l ocurre todo el manejo de la l�gica
void Juego::ejecutar() {

	//Mientras la ventana est� abierta...
	while (ventana->isOpen()) {

		//Llama a actualizar las f�sicas
		actualizarFisicas(10,8);

		//Llama a actualizar los elementos
		actualizarObjetos();

		//Ejecuta la gesti�n de eventos
		gestionarEventos();

		//Llama al manejo de colisiones entre objetos
		manejarColisiones();

		//Llama a la revisi�n para disparar la derrota
		chequearDerrota();

		//Ejecuta la actualizaci�n del renderizado en la ventana
		actualizarRenderizado();

	}

}

//Gestionar Eventos: M�todo encargado de procesar todos los inputs eventos del jugador sobre la ventana.
void Juego::gestionarEventos() {

	//Crea las variables a usar fuera de los estados switch para evitar errores
	b2World* mundo_arma;

	//Almacena la posici�n del cursor en la ventana
	Vector2i posicion_cursor = Mouse::getPosition(*ventana);

	//Bucle de recepci�n de eventos
	while (ventana->pollEvent(*gestor_eventos)) {

		//Switch para el tipo de evento
		switch (gestor_eventos->type) {

			//Evento: Cerrar ventana
		case Event::Closed:

			//Cierra la ventana
			ventana->close();

			break;

			//Evento: Tecla Presionada
		case Event::KeyPressed:

			//Switch para el codigo (tipo) de tecla
			switch (gestor_eventos->key.code) {

				//Tecla: Escape - Cerrar la ventana
			case Keyboard::Escape:

				//Cierra la ventana
				ventana->close();

				break;
			    
				//Tecla: M - Regresa al Men� Principal
			case Keyboard::M:

				//Si el jugador no est� en el men� principal...
				if (obtenerEscenaActiva() != menues[0]) {

					//Cambia la escena desde la actual al men� principal
					gestor_escenas->cambiarEscena(obtenerEscenaActiva(), menues[0]);

				}

				//Define juego terminado en "false" y reinicia el puntaje a 0
				juego_terminado = false;
				modificarPuntaje(OperacionPuntaje::ESTABLECER, 0);

				break;

			case Keyboard::R: //Tecla: R - Reinicia el nivel que se est� jugando

				//Llama al manejo de reinicio para todos los niveles
				manejarReinicioNivel();

				break;

			case Keyboard::Enter: //Tecla: Intro/Enter - Permite ingresar al juego directamente sin usar el bot�n de jugar

				//Si la escena activa es el men� principal (Solo se accede al nivel 1 desde el menu inicio)
				if (obtenerEscenaActiva() == menues[0]) {

					//Cambia desde la escena actual al nivel 1, elimina los ragdolls, borra los elementos de nivel y los vuelve a crear
					gestor_escenas->cambiarEscena(obtenerEscenaActiva(), niveles[0]);
					eliminarRagdoll(OperacionEliminacion::TODOS);
					niveles[0]->restablecer();
					niveles[0]->crearSala(PIXELES_POR_METRO, DIMENSIONES_VENTANA);
					generarNivel(1);

				}

				break;

			}

			//Evento: Bot�n del Cursor presionado
		case Event::MouseButtonPressed:

			//Switch para el tipo de bot�n de mouse
			switch (gestor_eventos->mouseButton.button) {

				//Boton: Izquierdo
			case Mouse::Left:

				//Detecta cual es el arma activa y la guarda antes de llamar a disparar
				detectarArmaActiva();

				//Si el arma seleccionada ni su escena son nulas...
				if (arma_activa != nullptr && arma_activa->retornarEscenaAdjunta() != nullptr && !juego_terminado) {

					//Llama a disparar el arma activa usando los valores pasados por par�metro
					dispararArmaActiva(PIXELES_POR_METRO, arma_activa->retornarEscenaAdjunta()->obtenerMundoFisico(), LIMITE_RAGDOLLS);

				}

				//Llamada a gestionar el evento de click de los botones
				manejarClickBotones(posicion_cursor);

				//DEBUG
				//depurarPosicionCursor(posicion_cursor, false);

				break;

				//Boton: Derecho
			case Mouse::Right:

				//Elimina el �ltimo ragdoll del arreglo, para poder generar uno nuevo
				eliminarRagdoll(OperacionEliminacion::UNO);

				//DEBUG
				//depurarEstadoArreglo();

				break;

			}

		    //Evento: Al Mover el Cursor
		case Event::MouseMoved:

			//Llama a la actualizaci�n visual de los botones
			manejarIluminacionBotones(posicion_cursor);

			break;

		}

	}

}

//Manejar Colisiones: Funci�n que se llama en bucle y se encarga de controlar si los ragdolls y objetos din�micos de cada nivel est�n
//En contacto con los puntos de control de dichos niveles. De ser as�, se activan los puntos de control y se a�ade puntaje.
void Juego::manejarColisiones() {

	//Bucle que itera sobre la cantidad de niveles...
	for (int i = 0; i < 3; i++) {

		//Si el nivel sobre el que se est� iterando es nulo...
		if (niveles[i] == nullptr) {

			//Omite la ejecuci�n actual del bucle y pasa a la siguiente sin ejecutar el resto del c�digo
			continue;

		}

		//Si el nivel sobre el que se est� iterando no est� activo...
		if (!niveles[i]->estaActiva()) {

			//Omite la ejecuci�n actual del bucle y pasa a la siguiente sin ejecutar el resto del c�digo
			continue;

		}

		//COLISIONES CON OBJETOS DINAMICOS

		//Itera sobre todos los obst�culos del nivel actual
		for (int j = 0; j < niveles[i]->retornarObstaculosMaximos(); j++) {

			//Si el obst�culo iterador del nivel iterador es nulo...
			if (niveles[i]->retornarObstaculo(j) == nullptr) {

				//Omite la ejecuci�n
				continue;

			}

			//Si el tipo del obst�culo iterador no es "din�mico"...
			if (niveles[i]->retornarObstaculo(j)->retornarTipo() != b2_dynamicBody) {

				//Omite la ejecuci�n
				continue;

			}

			//Itera sobre los puntos de control del nivel
			for (int k = 0; k < niveles[i]->retornarPuntosControlMaximos(); k++) {

				//Si el punto iterador es nulo...
				if (niveles[i]->retornarPuntoControl(k) == nullptr) {

					//Omite la ejecuci�n
					continue;

				}

				//Llama a gestionar colisiones para el nivel iterador
				if (niveles[i]->retornarPuntoControl(k)->revisarColisiones(niveles[i]->retornarObstaculo(j)->retornarHitbox()) && !niveles[i]->retornarPuntoControl(k)->fueActivado()) {

					//Activa el punto de forma indirecta y suma puntos
					niveles[i]->retornarPuntoControl(k)->activar(true);
					niveles[i]->retornarPuntoControl(k)->asignarActivacionIndirecta(true);
					modificarPuntaje(OperacionPuntaje::SUMA, 100);

				}

			}

		}

		//COLISIONES CON RAGDOLLS

		//Itera sobre los ragdolls
		for (int s = 0; s < LIMITE_RAGDOLLS; s++) {

			//Si el ragdoll iterador es nulo...
			if (ragdolls[s] == nullptr) {

				//Omite la ejecuci�n
				continue;

			}

			//Itera sobre los puntos de control del nivel
			for (int k = 0; k < niveles[i]->retornarPuntosControlMaximos(); k++) {

				//Si el punto iterador es nulo...
				if (niveles[i]->retornarPuntoControl(k) == nullptr) {

					//Omite la ejecuci�n
					continue;

				}

				//Llama a gestionar colisiones para el nivel iterador
				if (niveles[i]->retornarPuntoControl(k)->revisarColisiones(ragdolls[s]->retornarComponente(1)->retornarHitbox()) && !niveles[i]->retornarPuntoControl(k)->fueActivado()) {

					//Activa el punto de control (De forma directa) y suma puntaje
					niveles[i]->retornarPuntoControl(k)->activar(true);
					modificarPuntaje(OperacionPuntaje::SUMA, 200);

				}

			}

		}

	}

}

//Manejar Reinicio del Nivel: M�todo encargado del reinicio de los niveles. Este se llama tanto usando la tecla 'R' como presionando
//el bot�n de reinicio dentro del respectivo nivel, y borrar� los ragdolls creados, regenerar� la sala y los elementos de juego, y restar�
//el puntaje conseguido en el nivel en cuesti�n
void Juego::manejarReinicioNivel() {

	//Bucle que itera sobre los 3 niveles del juego...
	for (int x = 0; x < 3; x++) {

		//Si la escena activa es el Nivel 1...
		if (obtenerEscenaActiva() == niveles[x]) {

			//Itera sobre todos los puntos de control del nivel iterador
			for (int i = 0; i < niveles[x]->retornarPuntosControlMaximos(); i++) {

				//Almacena el punto de control iterador para acceso r�pido
				PuntoControl* punto_iterador = niveles[x]->retornarPuntoControl(i);

				//Si el punto es nulo...
				if (punto_iterador == nullptr) {

					//Omite la ejecuci�n de esta iteraci�n
					continue;

				}

				//Si el punto iterador no fue activado
				if (!punto_iterador->fueActivado()) {

					//Omite la ejecuci�n de esta iteraci�n
					continue;

				}

				//Si el punto fue activado de forma indirecta (Siendo golpeado por un objeto del nivel en lugar de un mu�eco)
				if (punto_iterador->fueActivadoIndirectamente()) {

					//Reduce 100 puntos del puntaje general
					modificarPuntaje(OperacionPuntaje::RESTA, 100);

				}
				else {

					//Reduce 200 puntos, debido a que el impacto fue de un ragdoll, lo cual otorga 200 puntos en lugar de 100
					modificarPuntaje(OperacionPuntaje::RESTA, 200);

				}

			}

			//Elimina todos los ragdolls creados, borra y re-genera los elementos de juego y la sala del nivel
			eliminarRagdoll(OperacionEliminacion::TODOS);
			niveles[x]->restablecer();
			niveles[x]->crearSala(PIXELES_POR_METRO, DIMENSIONES_VENTANA);
			generarNivel(x + 1);

		}

	}

}

//Chequear Derrota: M�todo disparado en bucle que revisa si el jugador ya dispar� todos los ragdolls. De ser as� se dispara un timer que
//al terminar, ejecutar� el c�digo de derrota, terminando el nivel. Esta funci�n se anula si el jugador ya activ� todos los puntos de
//control del nivel en cuesti�n
void Juego::chequearDerrota() {

	//Itera sobre los niveles del juego
	for (int i = 0; i < CANTIDAD_NIVELES; i++) {

		//Si la escena activa es un nivel y los puntos de control no fueron activados en su totalidad...
		if (obtenerEscenaActiva() == niveles[i] && !niveles[i]->revisarPuntosControlActivados()) {

			//Si la cantidad de ragdolls activos es menor al l�mite...
			if (contarRagdollsActivos() < LIMITE_RAGDOLLS) {

				//No se revisa la derrota. Reinicia el reloj y regresa
				chequeando_derrota = false;
				reloj_general.restart();
				return;
			}

			//Si no se est� chequeando la derrota...
			if (!chequeando_derrota) {

				//Reinicia el reloj, y se habilita la bandera de chequeo
				reloj_general.restart();
				chequeando_derrota = true;
			}

			//Si el tiempo transcurrido es mayor o igual a 8 segundos y el juego todav�a no termino...
			if (reloj_general.getElapsedTime().asSeconds() >= 8 && !juego_terminado) {

				//Dispara la derrota
				dispararDerrota();

			}

		}

	}

	


}

//Disparar Victoria: Modifica el texto de fin de juego, definiendo su color y marca la bandera de juego terminado como "true"
//Se dispara cuando el jugador gana el �ltimo nivel del juego. Impide que el jugador siga disparando
void Juego::dispararVictoria() {

	//Configura el texto con color verde y cambiando el string
	texto_fin_juego->modificarTexto("�Victoria!");
	texto_fin_juego->definirColor(Color(125, 255, 125, 255));

	//Registra en consola que se dispar� el evento
	cout << "[INFO] Evento - General: El jugador gan�" << endl;

	//Asigna true a juego terminado
	juego_terminado = true;

}

//Disparar Derrota: Modifica el texto de fin de juego, definiendo su color y marca la bandera de juego terminado como "true"
//Se dispara cuando el jugador usa todos sus ragdolls y no logra completar un nivel (Aplica en todos). Impide que el jugador siga disparando
void Juego::dispararDerrota() {

	//Configura el texto con color rojo y cambiando el string
	texto_fin_juego->modificarTexto("�Derrota!");
	texto_fin_juego->definirColor(Color::Red);

	//Registra en consola que se dispar� el evento
	cout << "[INFO] Evento - General: El jugador perdi�. En el nivel " << string(obtenerEscenaActiva()->obtenerIdentificador()) << endl;

	//Asigna true a juego terminado
	juego_terminado = true;

}

//Modificar Puntaje: M�todo que recibe un tipo de operaci�n y el valor con el cual operar. Suma o resta el valor al puntaje actual, o
//reemplaza el puntaje actual con valor usando el modo Establecer
void Juego::modificarPuntaje(OperacionPuntaje operacion, int valor) {

	//Si la operaci�n recibida es Suma
	if (operacion == OperacionPuntaje::SUMA) {

		//A�ade el valor al puntaje base
		puntaje += valor;

	} //Sino si la operaci�n es Resta
	else if (operacion == OperacionPuntaje::RESTA) {

		//Resta el valor al puntaje base
		puntaje -= valor;

	} //Sino si la operaci�n es de Establecimiento
	else if (operacion == OperacionPuntaje::ESTABLECER) {

		//Establece el valor como el nuevo puntaje base
		puntaje = valor;

	}

	//Si el resultado de la operaci�n di� menos que 0...
	if (puntaje < 0) {

		//Asigna 0 al puntaje, para evitar numeros negativos
		puntaje = 0;

	}

}

//Manejar Click de Botones: M�todo que se encarga de revisar colisiones con todos los botones disponibles en el juego. Si la encuentra
//llama a la ejecuci�n de eventos de click para el bot�n seleccionado
void Juego::manejarClickBotones(Vector2i coordenadas_mouse) {

	//Almacena las coordenadas del mouse y las convierte a coordenadas dentro de la ventana
	Vector2f posicion_convertida = { float(coordenadas_mouse.x), float(coordenadas_mouse.y) };

	//////////////////
	//MEN� PRINCIPAL//
	//////////////////

	//Si el men� principal no es nulo...
	if (menues[0] != nullptr) {

		//Almacena referencias a cada bot�n con el que se har� revisi�n de colisiones
		GUIBoton* boton_menu_jugar = menues[0]->obtenerBoton(0);
		GUIBoton* boton_menu_instrucciones = menues[0]->obtenerBoton(1);
		GUIBoton* boton_menu_objetivo = menues[0]->obtenerBoton(2);
		GUIBoton* boton_menu_salir = menues[0]->obtenerBoton(3);

		//Si el bot�n "Jugar" del men� inicio no es nulo y su escena est� activa...
		if (boton_menu_jugar != nullptr && menues[0]->estaActiva()) {

			//Si hay colisi�n entre el boton y el cursor...
			if (boton_menu_jugar->revisarColisionesPorUbicacion(posicion_convertida)) {

				//Registra en consola que se presion� el bot�n
				cout << "[INFO] Evento - Boton Clickeado: Jugar / En Interfaz: " << string(menues[0]->obtenerIdentificador()) << endl;

				//Cambia la escena desde "Menu Inicio" a "Nivel 1"
				gestor_escenas->cambiarEscena(menues[0], niveles[0]); //Desactiva el men� y activa el nivel 1
				eliminarRagdoll(OperacionEliminacion::TODOS); //Elimina todos los ragdolls
				niveles[0]->restablecer(); //Borra los elementos del nivel
				niveles[0]->crearSala(PIXELES_POR_METRO, DIMENSIONES_VENTANA); //Re-genera la sala
				generarNivel(1); //Re-genera los elementos del nivel

				//Crea un reloj para el delay
				Clock reloj;

				//Bucle while que retrasa el juego por la cantidad definida (0.25) de segundos...
				while (reloj.getElapsedTime().asSeconds() < 0.25f) {

					//Delay de 1/4 de segundo para que los eventos de click para disparar y click para presionar el bot�n
					//No se mezclen, lo que causa que se dispare un ragdoll inmediatamente tras apretar "jugar"
					//Este delay no se ejecuta si el jugador ingresa al nivel 1 usando la tecla "Intro"

				}

			}

		}

		//Si el bot�n "Instrucciones" del men� inicio no es nulo y su escena est� activa...
		if (boton_menu_instrucciones != nullptr && menues[0]->estaActiva()) {

			//Si hay colisi�n entre el boton y el cursor...
			if (boton_menu_instrucciones->revisarColisionesPorUbicacion(posicion_convertida)) {

				//Registra en consola que se presion� el bot�n
				cout << "[INFO] Evento - Boton Clickeado: Instrucciones / En Interfaz: " << string(menues[0]->obtenerIdentificador()) << endl;

				//Cambia la escena desde "Menu Inicio" a "Instrucciones"
				gestor_escenas->cambiarEscena(menues[0], menues[1]);

			}

		}

		//Si el bot�n "Salir" del men� inicio no es nulo y su escena est� activa...
		if (boton_menu_objetivo != nullptr && menues[0]->estaActiva()) {

			//Si hay colisi�n entre el boton y el cursor...
			if (boton_menu_objetivo->revisarColisionesPorUbicacion(posicion_convertida)) {

				//Registra en consola que se presion� el bot�n
				cout << "[INFO] Evento - Boton Clickeado: Objetivo / En Interfaz: " << string(menues[0]->obtenerIdentificador()) << endl;

				//Cambia la escena desde "Menu Inicio" a "Objetivos"
				gestor_escenas->cambiarEscena(menues[0], menues[2]);

			}

		}

		//Si el bot�n "Salir" del men� inicio no es nulo y su escena est� activa...
		if (boton_menu_salir != nullptr && menues[0]->estaActiva()) {

			//Si hay colisi�n entre el boton y el cursor...
			if (boton_menu_salir->revisarColisionesPorUbicacion(posicion_convertida)) {

				//Registra en consola que se presion� el bot�n
				cout << "[INFO] Evento - Boton Clickeado: Salir / En Interfaz: " << string(menues[0]->obtenerIdentificador()) << endl;

				//Cierra la ventana
				ventana->close();

			}

		}

	}

	//////////////////////
	//MENUES ADICIONALES//
	//////////////////////

	//Si el men� principal no es nulo...
	if (menues[1] != nullptr) {

		//Almacena una referencia al bot�n de salir
		GUIBoton* boton_instrucciones_salir = menues[1]->obtenerBoton(0);

		//Si el bot�n "Salir" del men� de instrucciones no es nulo y su escena est� activa...
		if (boton_instrucciones_salir != nullptr && menues[1]->estaActiva()) {

			//Si hay colisi�n entre el boton y el cursor...
			if (boton_instrucciones_salir->revisarColisionesPorUbicacion(posicion_convertida)) {

				//Registra en consola que se presion� el bot�n
				cout << "[INFO] Evento - Boton Clickeado: Regresar / En Interfaz: " << string(menues[1]->obtenerIdentificador()) << endl;

				//Cambia la escena desde "Instrucciones" a "Menu Inicio"
				gestor_escenas->cambiarEscena(menues[1], menues[0]);

			}

		}

	}

	//Si el men� principal no es nulo...
	if (menues[2] != nullptr) {

		//Almacena una referencia al bot�n de salir
		GUIBoton* boton_objetivo_salir = menues[2]->obtenerBoton(0);

		//Si el bot�n "Salir" del men� de instrucciones no es nulo y su escena est� activa...
		if (boton_objetivo_salir != nullptr && menues[2]->estaActiva()) {

			//Si hay colisi�n entre el boton y el cursor...
			if (boton_objetivo_salir->revisarColisionesPorUbicacion(posicion_convertida)) {

				//Registra en consola que se presion� el bot�n
				cout << "[INFO] Evento - Boton Clickeado: Regresar / En Interfaz: " << string(menues[2]->obtenerIdentificador()) << endl;

				//Cambia la escena desde "Instrucciones" a "Menu Inicio"
				gestor_escenas->cambiarEscena(menues[2], menues[0]);

			}

		}

	}

	///////////
	//NIVELES//
	///////////

	//NIVELES 1 y 2
	
	//Bucle que itera sobre todos los niveles, excepto el �ltimo (Ya que es un caso especial)
	for (int x = 0; x < (CANTIDAD_NIVELES - 1); x++) {

		//Si el nivel iterador no es nulo...
		if (niveles[x] != nullptr) {

			//Almacena referencias para todos los botones
			GUIBoton* boton_salir = niveles[x]->obtenerBoton(0);
			GUIBoton* boton_reiniciar = niveles[x]->obtenerBoton(1);
			GUIBoton* boton_avanzar = niveles[x]->obtenerBoton(2);

			//BOTON SALIR

			//Si el bot�n de salir no es nulo y el nivel est� activo...
			if (boton_salir != nullptr && niveles[x]->estaActiva()) {

				//Si hay colisi�n entre el boton y el cursor...
				if (boton_salir->revisarColisionesPorUbicacion(posicion_convertida)) {

					//Registra en consola que se presion� el bot�n
					cout << "[INFO] Evento - Boton Clickeado: Salir al Men� / En Nivel: " << string(niveles[x]->obtenerIdentificador()) << endl;

					//Sale del nivel hacia el men� principal
					gestor_escenas->cambiarEscena(niveles[x], menues[0]);

					//Asigna false a juego terminado y establece el puntaje
					juego_terminado = false;
					modificarPuntaje(OperacionPuntaje::ESTABLECER, 0);

				}

			}

			//BOTON REINICIAR

			//Si el bot�n de reiniciar no es nulo y el nivel est� activo...
			if (boton_reiniciar != nullptr && niveles[x]->estaActiva()) {

				//Si hay colisi�n entre el boton y el cursor...
				if (boton_reiniciar->revisarColisionesPorUbicacion(posicion_convertida)) {

					//Registra en consola que se presion� el bot�n
					cout << "[INFO] Evento - Boton Clickeado: Reiniciar / En Nivel: " << string(niveles[x]->obtenerIdentificador()) << endl;

					//Llama a reiniciar
					manejarReinicioNivel();

				}

			}

			//BOTON AVANZAR

			//Si el bot�n de avanzar no es nulo y el nivel est� activo...
			if (boton_avanzar != nullptr && boton_avanzar->estaEncendido() && niveles[x]->estaActiva()) {

				//Si hay colisi�n entre el boton y el cursor...
				if (boton_avanzar->revisarColisionesPorUbicacion(posicion_convertida)) {

					//Registra en consola que se presion� el bot�n
					cout << "[INFO] Evento - Boton Clickeado: Avanzar / En Nivel: " << string(niveles[x]->obtenerIdentificador()) << endl;

					//Crea un reloj para el delay
					Clock reloj;

					//Bucle while que retrasa el juego por la cantidad definida (0.25) de segundos...
					while (reloj.getElapsedTime().asSeconds() < 0.5f) {

						//Delay de 1/2 de segundo para que el evento de click para este bot�n no interfiera
						//Con el bot�n del siguiente nivel (Como ambos est�n en el mismo lugar, clickear este cambiar� de
						//escena y despu�s clickear� instant�neamente el segundo ya que el evento de click se sigue registrando
						//Este delay evita esto, retrasando el inicio del siguiente nivel para que el evento click deje de llamarse

					}

					//Convierte los ragdolls extras sin usar en puntaje que se suma a los puntos base
					modificarPuntaje(OperacionPuntaje::SUMA, 50 * (LIMITE_RAGDOLLS - contarRagdollsActivos()));

					//Avanza del nivel actual hacia el siguiente
					gestor_escenas->cambiarEscena(niveles[x], niveles[x + 1]);
					eliminarRagdoll(OperacionEliminacion::TODOS);
					niveles[x + 1]->restablecer();
					niveles[x + 1]->crearSala(PIXELES_POR_METRO, DIMENSIONES_VENTANA);
					generarNivel(x + 2);

				}

			}

		}

	}

	////////////////////////////////////

	//NIVEL 3

	//Si el nivel 3 no es nulo...
	if (niveles[2] != nullptr) {

		//Almacena referencias para todos los botones
		GUIBoton* boton_salir = niveles[2]->obtenerBoton(0);
		GUIBoton* boton_reiniciar = niveles[2]->obtenerBoton(1);
		GUIBoton* boton_avanzar = niveles[2]->obtenerBoton(2);

		//BOTON SALIR

		//Si el bot�n de salir no es nulo y el nivel est� activo...
		if (boton_salir != nullptr && niveles[2]->estaActiva()) {

			//Si hay colisi�n entre el boton y el cursor...
			if (boton_salir->revisarColisionesPorUbicacion(posicion_convertida)) {

				//Registra en consola que se presion� el bot�n
				cout << "[INFO] Evento - Boton Clickeado: Salir al Men� / En Nivel: " << string(niveles[2]->obtenerIdentificador()) << endl;

				//Sale del nivel hacia el men� principal
				gestor_escenas->cambiarEscena(niveles[2], menues[0]);

				//Asigna false a juego terminado y restablece el puntaje
				juego_terminado = false;
				modificarPuntaje(OperacionPuntaje::ESTABLECER, 0);

			}

		}

		//BOTON REINICIAR

		//Si el bot�n de reinicio no es nulo y el nivel est� activo...
		if (boton_reiniciar != nullptr && niveles[2]->estaActiva()) {

			//Si hay colisi�n entre el boton y el cursor...
			if (boton_reiniciar->revisarColisionesPorUbicacion(posicion_convertida)) {

				//Registra en consola que se presion� el bot�n
				cout << "[INFO] Evento - Boton Clickeado: Salir al Men� / En Nivel: " << string(niveles[2]->obtenerIdentificador()) << endl;

				//Llama a reiniciar
				manejarReinicioNivel();

				//Si el jugador ya gan� y trata de reiniciar tras ganar...
				if (juego_terminado) {

					//Se resta puntaje adicional, correspondiente a la cantidad de ragdolls no usados
					modificarPuntaje(OperacionPuntaje::RESTA, 50 * (LIMITE_RAGDOLLS - contarRagdollsActivos()));

					//Restablece el valor de juego terminado, para permitir reiniciar si el jugador ya gan� el nivel
					juego_terminado = false;

				}

			}

		}

		//BOTON FINALIZAR JUEGO

		//Si el bot�n de terminar juego no es nulo y el nivel est� activo...
		if (boton_avanzar != nullptr && boton_avanzar->estaEncendido() && niveles[2]->estaActiva()) {

			//Si hay colisi�n entre el boton y el cursor...
			if (boton_avanzar->revisarColisionesPorUbicacion(posicion_convertida) && !juego_terminado) {

				//Registra en consola que se presion� el bot�n
				cout << "[INFO] Evento - Boton Clickeado: Avanzar / En Nivel: " << string(niveles[2]->obtenerIdentificador()) << endl;

				//Convierte los ragdolls extras sin usar en puntaje que se suma a los puntos base
				modificarPuntaje(OperacionPuntaje::SUMA, 50 * (LIMITE_RAGDOLLS - contarRagdollsActivos()));

				//Dispara la victoria
				dispararVictoria();

			}

		}

	}

}

//Manejar Iluminaci�n Botones: Contiene l�gica para activar o desactivar la iluminaci�n de los botones dependiendo de si el cursor
//est� o no encima de ellos. Opera usando las coordenadas del mouse
void Juego::manejarIluminacionBotones(Vector2i coordenadas_mouse) {

	//Almacena las coordenadas del mouse y las convierte a coordenadas dentro de la ventana
	Vector2f posicion_convertida = { float(coordenadas_mouse.x), float(coordenadas_mouse.y) };

	//////////////////
	//MEN� PRINCIPAL//
	//////////////////

	//Si el men� principal no es nulo...
	if (menues[0] != nullptr) {

		//Almacena referencias a cada bot�n con el que se har� revisi�n de colisiones
		GUIBoton* boton_menu_jugar = menues[0]->obtenerBoton(0);
		GUIBoton* boton_menu_instrucciones = menues[0]->obtenerBoton(1);
		GUIBoton* boton_menu_objetivo = menues[0]->obtenerBoton(2);
		GUIBoton* boton_menu_salir = menues[0]->obtenerBoton(3);

		//Si el bot�n "Jugar" del men� inicio no es nulo y su escena est� activa...
		if (boton_menu_jugar != nullptr && menues[0]->estaActiva()) {

			//Si hay colisi�n entre el boton y el cursor...
			if (boton_menu_jugar->revisarColisionesPorUbicacion(posicion_convertida)) {

				//Cambia la textura del sprite del bot�n a su versi�n iluminada
				boton_menu_jugar->iluminar(true);

			}
			else {

				//Cambia la textura del bot�n a su versi�n normal
				boton_menu_jugar->iluminar(false);

			}

		}

		//Si el bot�n "Jugar" del men� inicio no es nulo y su escena est� activa...
		if (boton_menu_instrucciones != nullptr && menues[0]->estaActiva()) {

			//Si hay colisi�n entre el boton y el cursor...
			if (boton_menu_instrucciones->revisarColisionesPorUbicacion(posicion_convertida)) {

				//Cambia la textura del sprite del bot�n a su versi�n iluminada
				boton_menu_instrucciones->iluminar(true);

			}
			else {

				//Cambia la textura del bot�n a su versi�n normal
				boton_menu_instrucciones->iluminar(false);

			}

		}

		//Si el bot�n "Jugar" del men� inicio no es nulo y su escena est� activa...
		if (boton_menu_objetivo != nullptr && menues[0]->estaActiva()) {

			//Si hay colisi�n entre el boton y el cursor...
			if (boton_menu_objetivo->revisarColisionesPorUbicacion(posicion_convertida)) {

				//Cambia la textura del sprite del bot�n a su versi�n iluminada
				boton_menu_objetivo->iluminar(true);

			}
			else {

				//Cambia la textura del bot�n a su versi�n normal
				boton_menu_objetivo->iluminar(false);

			}

		}

		//Si el bot�n "Jugar" del men� inicio no es nulo y su escena est� activa...
		if (boton_menu_salir != nullptr && menues[0]->estaActiva()) {

			//Si hay colisi�n entre el boton y el cursor...
			if (boton_menu_salir->revisarColisionesPorUbicacion(posicion_convertida)) {

				//Cambia la textura del sprite del bot�n a su versi�n iluminada
				boton_menu_salir->iluminar(true);

			}
			else {

				//Cambia la textura del bot�n a su versi�n normal
				boton_menu_salir->iluminar(false);

			}

		}

	}

	//////////////////////
	//MENUES ADICIONALES//
	//////////////////////

	//Si el men� instrucciones no es nulo...
	if (menues[1] != nullptr) {

		//Almacena referencias al �nico bot�n de la escena
		GUIBoton* boton_instrucciones_salir = menues[1]->obtenerBoton(0);

		//Si el bot�n "Salir" del men� instrucciones no es nulo y su escena est� activa...
		if (boton_instrucciones_salir != nullptr && menues[1]->estaActiva()) {

			//Si hay colisi�n entre el boton y el cursor...
			if (boton_instrucciones_salir->revisarColisionesPorUbicacion(posicion_convertida)) {

				//Cambia la textura del sprite del bot�n a su versi�n iluminada
				boton_instrucciones_salir->iluminar(true);

			}
			else {

				//Cambia la textura del bot�n a su versi�n normal
				boton_instrucciones_salir->iluminar(false);

			}

		}

	}

	//Si el men� instrucciones no es nulo...
	if (menues[2] != nullptr) {

		//Almacena referencias al �nico bot�n de la escena
		GUIBoton* boton_objetivo_salir = menues[2]->obtenerBoton(0);

		//Si el bot�n "Salir" del men� instrucciones no es nulo y su escena est� activa...
		if (boton_objetivo_salir != nullptr && menues[2]->estaActiva()) {

			//Si hay colisi�n entre el boton y el cursor...
			if (boton_objetivo_salir->revisarColisionesPorUbicacion(posicion_convertida)) {

				//Cambia la textura del sprite del bot�n a su versi�n iluminada
				boton_objetivo_salir->iluminar(true);

			}
			else {

				//Cambia la textura del bot�n a su versi�n normal
				boton_objetivo_salir->iluminar(false);

			}

		}

	}

	///////////
	//NIVELES//
	///////////

	//Itera sobre todos los niveles
	for (int x = 0; x < CANTIDAD_NIVELES; x++) {

		//Si el men� instrucciones no es nulo...
		if (niveles[x] != nullptr) {

			//Itera sobre todos los botones del nivel iterador
			for (int i = 0; i < niveles[x]->retornarBotonesMaximos(); i++) {

				//Almacena referencias al �nico bot�n de la escena
				GUIBoton* boton_iterador = niveles[x]->obtenerBoton(i);

				//Si el bot�n "Salir" no es nulo y el nivel est� activo...
				if (boton_iterador != nullptr && niveles[x]->estaActiva()) {

					//Si hay colisi�n entre el boton y el cursor...
					if (boton_iterador->revisarColisionesPorUbicacion(posicion_convertida)) {

						//Cambia la textura del sprite del bot�n a su versi�n iluminada
						boton_iterador->iluminar(true);

					}
					else {

						//Cambia la textura del bot�n a su versi�n normal
						boton_iterador->iluminar(false);

					}

				}

			}

			

		}

	}

}

//Actualizar Renderizado: M�todo que recibe inserciones para dibujarlas en la pantalla, limpia y actualiza el contenido de la misma
void Juego::actualizarRenderizado() {

	//Limpia la pantalla
	ventana->clear();

	//MEN�ES

	//Itera sobre los 3 elementos contenidos en el arreglo de men�es
	for (int i = 0; i < 3; i++) {

		//Si el men� iterador es nulo o est� desactivado...
		if (menues[i] == nullptr) {

			//Pasa a la siguiente iteraci�n del bucle (No dibuja el elemento)
			continue;

		}

		//Llama a dibujar los elementos alojados en el men� iterador
		menues[i]->renderizarElementosAlojados(ventana);

	}

	//NIVELES

	//Itera sobre los 3 elementos contenidos en el arreglo de niveles
	for (int k = 0; k < 3; k++) {

		//Si el men� iterador es nulo...
		if (niveles[k] == nullptr) {

			//Pasa a la siguiente iteraci�n del bucle (No dibuja el elemento)
			continue;

		}

		//Llama a dibujar los elementos alojados en el men� iterador
		niveles[k]->renderizarElementosAlojados(ventana);

	}

	//RAGDOLLS

	//Carga el arreglo de ragdolls para dibujar
	for (int i = 0; i < LIMITE_RAGDOLLS; i++) {

		//Si el ragdoll iterador no es nulo...
		if (ragdolls[i] != nullptr) {

			//Almacena una referencia a la escena del ragdoll iterador
			Escena* escena_ragdoll = ragdolls[i]->retornarEscenaAdjunta();

			//Si la escena no es nula y est� activa...
			if (escena_ragdoll != nullptr && escena_ragdoll->estaActiva()) {

				//Actualiza el ragdoll en el espacio iterado
				ragdolls[i]->renderizar(ventana);

			}

		}

	}

	//Si el texto de fin de juego no es nulo...
	if (texto_fin_juego != nullptr) {

		//Si el juego termin�...
		if (juego_terminado) {

			//Se renderiza directamente sin revisar su escena, puesto que el elemento es persistente entre escenas
			texto_fin_juego->dibujarElemento(ventana);

		}

	}

	//Muestra el contenido cargado
	ventana->display();

}

//Actualizar F�sicas: M�todo que actualiza la simulaci�n fisica usando las iteraciones suministradas por par�metro
void Juego::actualizarFisicas(int iteraciones_velocidad, int iteraciones_posicion) {

	//Almacena el tiempo
	float tiempo = 1.2f / 60.0f;

	//Bucle que itera sobre todos los niveles...
	for (int i = 0; i < 3; i++) {

		//Si el mundo contenido en el iterador de nivel es nulo
		if (niveles[i] == nullptr || niveles[i]->obtenerMundoFisico() == nullptr) {

			//Omite el procesamiento del iterador, pasando al siguiente elemento
			continue;

		}

		//Si el mundo iterador est� activo...
		if (niveles[i]->estaActiva()) {

			//Llama a actualizar las f�sicas del mundo del nivel iterador
			niveles[i]->obtenerMundoFisico()->Step(tiempo, iteraciones_velocidad, iteraciones_posicion);

		}

	}

}

//Actualizar Objetos: Encargado de actualizar la posici�n de los objetos visuales para encajar con la de sus contrapartes f�sicas
void Juego::actualizarObjetos() {

	//RAGDOLLS
	
	//Actualiza el arreglo de ragdolls
	for (int i = 0; i < LIMITE_RAGDOLLS; i++) {

		//Si el ragdoll iterador es nulo...
		if (ragdolls[i] == nullptr) {

			//Se omite esta iteraci�n del bucle, pasando a la siguiente sin ejecutar acciones
			continue;

		}

		//Almacena puntero a escena y mundo del iterador para acceso f�cil y r�pido
		Escena* escena_ragdoll_iterador = ragdolls[i]->retornarEscenaAdjunta();

		//Si la escena no es nula...
		if (escena_ragdoll_iterador != nullptr) {

			//Almacena referencia al mundo de la escena del ragdoll
			b2World* mundo_ragdoll_iterador = escena_ragdoll_iterador->obtenerMundoFisico();

			//Si el mundo almacenado no es nulo...
			if (mundo_ragdoll_iterador != nullptr) {

				//Bandera que determina si la escena es v�lida (Est� activa y no es nula)
				bool escena_valida = escena_ragdoll_iterador->estaActiva();

				//Si el puntero sobre el que se itera es nulo, el ragdoll est� en una escena desactivada o el mundo f�sico es nulo...
				if (escena_valida) {

					//Actualiza el ragdoll en el espacio iterado
					ragdolls[i]->actualizar(PIXELES_POR_METRO);

				}

			}

		}

	}

	//NIVELES

	//Bucle que itera sobre el arreglo de punteros a niveles
	for (int k = 0; k < 3; k++) {

		//Si el puntero es nulo o si el nivel est� desactivado...
		if (niveles[k] == nullptr || !niveles[k]->estaActiva() || niveles[k]->obtenerMundoFisico() == nullptr) {

			//Omite la acci�n y pasa a la siguiente iteraci�n (No actualiza los elementos del nivel)
			continue;

		}

		//Llama a actualizar los elementos alojados para el iterador de nivel
		niveles[k]->actualizarElementosAlojados(PIXELES_POR_METRO, contarRagdollsActivos(), LIMITE_RAGDOLLS, puntaje, Mouse::getPosition());

	}

}

//Detectar Arma Activa: Detecta cu�l de las armas est� activa recorriendo cada nivel y consultando si dicho nivel est� activo. De
//esta forma solo se har�n los calculos de apuntado con el arma activada en lugar de con todas. Debido a que el arreglo se recorre de
//menor a mayor valor (�ndice 0 en adelante) Si hay m�s de 1 arma activada, la que se usar� para disparar siempre ser� la de indice menor
void Juego::detectarArmaActiva() {

	//Si el nivel 1 no es nulo, est� activado y su arma tampoco es nula...
	if (niveles[0] != nullptr && niveles[0]->estaActiva() && niveles[0]->retornarArma() != nullptr) {

		//Asigna el arma activa como la del nivel 1
		arma_activa = niveles[0]->retornarArma();

	} //Si el nivel 2 no es nulo, est� activado y su arma tampoco es nula...
	else if (niveles[1] != nullptr && niveles[1]->estaActiva() && niveles[1]->retornarArma() != nullptr) {

		//Asigna el arma activa como la del nivel 2
		arma_activa = niveles[1]->retornarArma();

	} //Finalmente, si el nivel 3 no es nulo, est� activado y su arma tampoco es nula...
	else if (niveles[2] != nullptr && niveles[2]->estaActiva() && niveles[2]->retornarArma() != nullptr) {

		//Asigna el arma activa como la del nivel 3
		arma_activa = niveles[2]->retornarArma();

	}

}

/////////////////////////////////////////////////////////////

//Crear Ventana: M�todo que genera una ventana con las dimensiones y nombre especificadas y luego la retorna para ser almacenada y usada
RenderWindow* Juego::crearVentana(int anchura, int altura, string nombre) {

	//Retorna una nueva ventana con los par�metros recibidos
	return new RenderWindow(VideoMode(anchura, altura), nombre);

}

//Contar Ragdolls Activos: Retorna un entero que representa la cantidad de mu�ecos que est�n activos en general, es decir que est�n
//ocupando un espacio en el arreglo de punteros
int Juego::contarRagdollsActivos() {

	//Crea una variable para el manejo de la cantidad
	int cantidad = 0;

	//Bucle que itera sobre el arreglo de punteros a ragdoll...
	for (int i = 0; i < LIMITE_RAGDOLLS; i++) {

		//Si el ragdoll iterador no es nulo...
		if (ragdolls[i] != nullptr) {

			//Incrementa la cantidad en 1
			cantidad++;

		}

	}

	//Devuelve el valor de cantidad
	return cantidad;

}

//Obtener Escena Activa: Recorre todas las escenas del juego y retorna la primera que se encuentre activa, el orden va desde los
//primeros men�es hasta el �ltimo nivel, por ende si hay 2 escenas activas (un men� y un nivel por ejemplo) Siempre se retornar� el menu
Escena* Juego::obtenerEscenaActiva() {

	//Crea un arreglo de punteros a escena para almacenar todas las escenas del juego (No hice tiempo a modificarlo, deber�a usar las constantes para definir din�micamente el tama�o)
	Escena* conjunto_escenas[6]{

		menues[0],
		menues[1],
		menues[2],
		niveles[0],
		niveles[1],
		niveles[2]

	};

	//Recorre el arreglo previamente creado con un bucle...
	for (int i = 0; i < 6; i++) {

		//Si la escena iteradora no es nula y est� activada
		if (conjunto_escenas[i] != nullptr && conjunto_escenas[i]->estaActiva()) {

			//Se retorna dicha escena
			return conjunto_escenas[i];

		}

	}

	//Retorna nulo ya que no se encontraron escenas activas
	return nullptr;

}

/////////////////////////////////////////////////////////////

//Depurar Transformaci�n: M�todo debug que imprime la posici�n y rotaci�n de un objeto por consola
void Juego::depurarTransformacion(Poligono objeto) {

	//Depura la posici�n f�sica y visual
	cout << "P. Fisica: " << objeto.retornarCuerpo()->GetPosition().x * PIXELES_POR_METRO << ", " << objeto.retornarCuerpo()->GetPosition().y * PIXELES_POR_METRO << endl;
	cout << "P. Visual: " << objeto.retornarSprite().getPosition().x << ", " << objeto.retornarSprite().getPosition().y << endl;

	//Depura la rotaci�n f�sica y visual
	cout << "R. Fisica: " << objeto.retornarCuerpo()->GetAngle() << endl;
	cout << "R. Visual: " << objeto.retornarSprite().getRotation() * (b2_pi / 180.0f) << endl;

}

//Depurar Estado Arreglo: M�todo debug que revisa cada posici�n del arreglo de ragdolls e imprime 1 o 0 si el espacio tiene o no un dato respectivamente
void Juego::depurarEstadoArreglo() {

	//Itera sobre el arreglo usando la constante est�tica definida en la cabecera de la clase
	for (int i = 0; i < LIMITE_RAGDOLLS; i++) {

		//Variable local bool
		bool tiene_dato = false;

		//Si el puntero seleccionado no es nulo...
		if (ragdolls[i] != nullptr) {

			//Hay un dato en el puntero
			tiene_dato = true;

		}

		//Depura dicha informaci�n en la consola
		cout << "[DEBUG]: Ragdoll - Espacio '" << i << "' = " << tiene_dato << endl;

	}

}

//Depurar Posici�n Cursor: M�todo debug que muestra las coordenadas del cursor al presionar el click izquierdo
//Activar el modo f�sico pasando 'true' har� que las coordenadas se conviertan a m�trica de Box2d (Metros en lugar de Pixeles)
void Juego::depurarPosicionCursor(Vector2i posicion_cursor, bool modo_fisico) {

	//Revisa si est� desactivado el modo f�sico
	if (!modo_fisico) {

		//Muestra las coordenadas en consola (En pixeles)
		cout << "Posicion Mouse: X = " << posicion_cursor.x << " Y = " << posicion_cursor.y << endl;

	}
	else {

		//Muestra las coordenadas en consola (En metros)
		cout << "Posicion Mouse: X = " << posicion_cursor.x / PIXELES_POR_METRO << " Y = " << posicion_cursor.y / PIXELES_POR_METRO << endl;

	}

}