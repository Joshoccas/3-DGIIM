//**********************************************************************//
// Sistemas Concurrentes y Distribuidos - 3ºDGIIM.
//
// Nombre y apellidos: José Alberto Hoces Castro
// Grupo: 1
// Archivo: plantilla.cpp
// NO LE HAGÁIS MUCHO CASO PORQUE ME SALIÓ REGULAR Y NI SIQUIERA CONSEGUÍ
// EL ENUNCIADO. EN EL EXAMEN DE LA PRÁCTICA 3 SÍ QUE HAY ENUNCIADO Y LO HICE
// BIEN, DE ESE SÍ OS PODÉIS FIAR
//**********************************************************************//
#include <iostream>
#include <iomanip>
#include <cassert>
#include <random>
#include <thread>
#include "scd.h"


using namespace std ;
using namespace scd ;


//**********************************************************************
// Variables globales
//----------------------------------------------------------------------

const int 
    num_hebras = 5,              // Número de jugadores
    min_ms    = 5,              // Tiempo minimo de espera en sleep_for
    max_ms    = 30 ,            // Tiempo máximo de espera en sleep_for
    num_rondas = 10;

//**********************************************************************
// Funciones comunes
//----------------------------------------------------------------------

void dormir()
{
    this_thread::sleep_for( chrono::milliseconds( aleatorio<min_ms,max_ms>() ));
}

//**********************************************************************
// Monitor
//----------------------------------------------------------------------


class Heart : public HoareMonitor
{
 private:
 static const int               // Constantes ('static' ya que no dependen de la instancia):
   NUM_JUGADORES = num_hebras,                 //   Descripcion
   POSICIONES = 4;
   
 const int PRIMERO = 5,
   SEGUNDO = 3,
   TERCERO = 2,
   RESTO = 1;

 int                            // Variables
   han_mirado,                       // Contador de cuántos jugadores han mirado en la ronda
   posiciones[POSICIONES],	   // Vector con las posiciones donde se va a ir moviendo el corazón
   puntos[NUM_JUGADORES];	// Recuento de puntos de cada jugador

 CondVar                        // Colas condición
   esperando,                     // Cola para que el NPC espere a que los jugadores hagan su turno (se le llamará cuando han_mirado es igual al número de jugadores
   ya_mirado; // Cola para que las hebras que ya han mirado esperen a que terminen las otras
   
   
 bool primera_ronda; // Variable que es true al principio para que el NPC mueva el corazón en 
 			// la primera ronda sin tener que esperar


 public:                        // Constructor y métodos públicos:
   Heart() ;                  //   Constructor
   void buscar_corazon(int &x, int i);            
   void mover_corazon(int &x);
   void imprimir();
} ;

//----------------------------------------------------------------------

Heart::Heart()
{

    // En este constructor inicializamos los puntos a 0, las posiciones a 0 y las colas condición
    for(int i = 0; i < NUM_JUGADORES; i++){
    	
    	puntos[i] = 0;
    }
    
    for(int j = 0; j < POSICIONES; j++){
    	
    	posiciones[j] = 0;
    }
   
    han_mirado = 0;
    primera_ronda = true;
    esperando = newCondVar();
    ya_mirado = newCondVar();
}

//----------------------------------------------------------------------

void Heart::buscar_corazon(int &x, int i)
{

	// Dependiendo de lo que haya en la posicion x, actualizamos el la casilla del corazon
	// al valor de puntos que da ahora. Además,se suman los puntos conseguidos y se actualiza
	// han_mirado
	
	if(posiciones[x] == PRIMERO){
	
		posiciones[x] = SEGUNDO;
		puntos[i] += PRIMERO;
		han_mirado++;
	}
	else if(posiciones[x] == SEGUNDO){
	
		posiciones[x] = TERCERO;
		puntos[i] += SEGUNDO;
		han_mirado++;
	}
	else if(posiciones[x] == TERCERO){
		
		posiciones[x] = RESTO;
		puntos[i] += TERCERO;
		han_mirado++;
	}
	else if(posiciones[x] == RESTO){
		puntos[i] += RESTO;
		han_mirado++;
	}
	else{
		han_mirado++;
	}
	
	cout << "El jugador " << i << " ha mirado en la posición " << x << endl;
	
	// Imprimimos la situación actual de puntos y posiciones
	
	imprimir();
		
	
	// Si es la última hebra en mirar, notifica al NPC para que actúe y cuando
	// esta termina, sale de la cola de urgentes para sacar de la cola ya_mirado
	// al resto de jugadores
	
	if(han_mirado == NUM_JUGADORES){
		esperando.signal();
		han_mirado = 0;
		ya_mirado.signal();
	}
	else{
	
		// Si no es la última en mirar, se bloquea hasta que la última la desbloquee
		// y se haga desbloqueo en cadena
		
		ya_mirado.wait();
		ya_mirado.signal();
	}
    
}

void Heart::mover_corazon(int &x)
{
	if(han_mirado == 0 && primera_ronda){
	
		posiciones[x] = PRIMERO;
		primera_ronda = false;
	}
	else if(han_mirado < NUM_JUGADORES){
		
		esperando.wait();
	}
	
	for(int i = 0; i < POSICIONES; i++){
		if(i == x){
			posiciones[i] = PRIMERO;
		}
		else{
			posiciones[i] = 0;
		}
	}
	
	cout << "El NPC cambia el corazón a la posición " << x << endl;
	
	
}

void Heart::imprimir(){

	string cadena, cadena_puntos;

   	 for (int i = 0; i < num_hebras; i++){
                	
               cadena_puntos += "Jugador " + to_string(i) + " : " + to_string(puntos[i]) + " puntos.\n";
    	}
    	
    	for(int i = 0; i < POSICIONES; i++){
    		
    		cadena += " " + to_string(posiciones[i]) + " |";
        	
        	cadena.pop_back();
    	}

    	cout << "Vector de posiciones:" << endl << cadena << endl;
    	cout << "Puntos de cada jugador:" << endl << cadena_puntos << endl << endl;
}

//**********************************************************************
// Funciones hebras
//----------------------------------------------------------------------

void funcion_hebra_jugador( MRef<Heart> monitor , int i)
{

   int x;
   
   for(int j = 0; j < num_rondas; j++){
   	
   	x = aleatorio<0,3>();
   	monitor->buscar_corazon(x,i);
   	
   }
}

void funcion_hebra_NPC( MRef<Heart> monitor )
{
	
	int x;

	for(int i = 0; i < num_rondas; i++){
		
		x = aleatorio<0,3>();
		monitor->mover_corazon(x);
	}
}

//**********************************************************************
// Función principal
//----------------------------------------------------------------------

int main()
{
   cout << "--------------------------------------------------------------------" << endl
        << "Problema Corazón. " << endl
        << "--------------------------------------------------------------------" << endl << endl;

   // Crear monitor 
   
   MRef<Heart> monitor = Create<Heart>() ;

    // Crear y lanzar las hebras
    
   thread jugadores[num_hebras];
   thread NPC;
      
   NPC = thread(funcion_hebra_NPC, monitor); 
        
   for (int i=0; i<num_hebras; i++)
      jugadores[i] = thread(funcion_hebra_jugador, monitor , i);


   
   
   // Esperar a que terminen las hebras
   
   for (int i=0; i<num_hebras; i++)
      jugadores[i].join();
      
   NPC.join();

   return 0;
}
