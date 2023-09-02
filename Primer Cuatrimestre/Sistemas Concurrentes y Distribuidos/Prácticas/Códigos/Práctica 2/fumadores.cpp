#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include "scd.h"

using namespace std ;
using namespace scd ;

// numero de fumadores 

const int num_fumadores = 3 ;

//-------------------------------------------------------------------------
// Función que simula la acción de producir un ingrediente, como un retardo
// aleatorio de la hebra (devuelve número de ingrediente producido)

int producir_ingrediente()
{
   // calcular milisegundos aleatorios de duración de la acción de fumar)
   chrono::milliseconds duracion_produ( aleatorio<10,100>() );

   // informa de que comienza a producir
   cout << "Estanquero : empieza a producir ingrediente (" << duracion_produ.count() << " milisegundos)" << endl;

   // espera bloqueada un tiempo igual a ''duracion_produ' milisegundos
   this_thread::sleep_for( duracion_produ );

   const int num_ingrediente = aleatorio<0,num_fumadores-1>() ;

   // informa de que ha terminado de producir
   cout << "Estanquero : termina de producir ingrediente " << num_ingrediente << endl;

   return num_ingrediente ;
}


//----------------------------------------------------------------------

class Estanco : public HoareMonitor{
	
	private:
	
	CondVar vacio;
	CondVar ingredientes[num_fumadores];
	int ingrediente;
	
	public:
	
	Estanco(){
		ingrediente = -1;
		vacio = newCondVar();
		for(int i = 0; i < num_fumadores; i++){
			ingredientes[i] = newCondVar();
		}
	}
	
	void poner_ingrediente(int i){
		
		ingrediente = i;
		cout << "puesto ingr.: " << i << endl;
		
		if(!ingredientes[i].empty()){
			ingredientes[i].signal();
		}
		
	}
	
	void coger_ingrediente(int i){
		
		if(ingrediente != i){
			ingredientes[i].wait();
		}
		
		ingrediente = -1;
		cout << "retirado ingr.: " << i << endl;
		vacio.signal();
	}
	
	void esperar_recogida_ingrediente(){
		if(ingrediente >= 0){
			cout << "Estanquero espera a que se coja un ingrediente" << endl;
			vacio.wait();
		}
	}
};

//----------------------------------------------------------------------
// función que ejecuta la hebra del estanquero

void funcion_hebra_estanquero( MRef <Estanco> monitor )
{

   int i;
   while(true){
      
      i = producir_ingrediente();
      monitor->poner_ingrediente(i);
      monitor->esperar_recogida_ingrediente();
   } 

}

//-------------------------------------------------------------------------
// Función que simula la acción de fumar, como un retardo aleatoria de la hebra

void fumar( int num_fumador )
{

   // calcular milisegundos aleatorios de duración de la acción de fumar)
   chrono::milliseconds duracion_fumar( aleatorio<20,200>() );

   // informa de que comienza a fumar

    cout << "Fumador " << num_fumador << "  :"
          << " empieza a fumar (" << duracion_fumar.count() << " milisegundos)" << endl;

   // espera bloqueada un tiempo igual a ''duracion_fumar' milisegundos
   this_thread::sleep_for( duracion_fumar );

   // informa de que ha terminado de fumar

    cout << "Fumador " << num_fumador << "  : termina de fumar, comienza espera de ingrediente." << endl;

}

//----------------------------------------------------------------------
// función que ejecuta la hebra del fumador
void  funcion_hebra_fumador( int num_fumador, MRef<Estanco> monitor )
{
   while( true )
   {
       monitor->coger_ingrediente(num_fumador);
       fumar(num_fumador);
   }
}

//----------------------------------------------------------------------

int main()
{

   MRef<Estanco> monitor = Create<Estanco>();
   
   thread estanquero(funcion_hebra_estanquero,monitor);
   thread fumadores[num_fumadores];
   
   for(int i = 0; i < num_fumadores; i++){
      fumadores[i] = thread(funcion_hebra_fumador,i,monitor);
   }
   
   // No iba a poner los join ya que nunca terminan de ejecutarse las hebras, pero el
   // profesor me recomendó ponerlo igualmente
   
   estanquero.join();
   for(int i = 0; i < num_fumadores; i++){
      fumadores[i].join();
   }
   
   return 0;
}
