// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Seminario 2. Introducción a los monitores en C++11.
//
// Archivo: prodcons1_su.cpp
//
// Ejemplo de un monitor en C++11 con semántica SU, para el problema
// del productor/consumidor, con múltiples productores y consumidores.
// Opcion LIFO
//
// Historial:
// Creado el 30 Sept de 2022. (adaptado de prodcons2_su.cpp)
// 20 oct 22 --> paso este archivo de FIFO a LIFO, para que se corresponda con lo que dicen las transparencias
// -----------------------------------------------------------------------------------


#include <iostream>
#include <iomanip>
#include <cassert>
#include <random>
#include <thread>
#include "scd.h"

using namespace std ;
using namespace scd ;

constexpr int
   num_items = 1000 ;   // número de items a producir/consumir
 
   
constexpr int               
   min_ms    = 5,     // tiempo minimo de espera en sleep_for
   max_ms    = 20 ;   // tiempo máximo de espera en sleep_for


mutex
   mtx ;                 // mutex de escritura en pantalla
unsigned
   cont_prod[num_items] = {0}, // contadores de verificación: producidos
   cont_cons[num_items] = {0}; // contadores de verificación: consumidos


const int num_hebras = 5;
int siguiente_dato[num_hebras]; // siguiente valor a devolver en 'producir_dato'

//**********************************************************************
// funciones comunes a las dos soluciones (fifo y lifo)
//----------------------------------------------------------------------

int producir_dato(int i)
{
   
   this_thread::sleep_for( chrono::milliseconds( aleatorio<min_ms,max_ms>() ));
   
   const int valor_producido = siguiente_dato[i] ;
   siguiente_dato[i] ++ ;
   cout << "hebra productora " << i << " produce " << valor_producido << endl << flush ;
   cont_prod[valor_producido]++ ;
   return valor_producido ;
}
//----------------------------------------------------------------------

void consumir_dato( unsigned valor_consumir )
{
   if ( num_items <= valor_consumir )
   {
      cout << " valor a consumir === " << valor_consumir << ", num_items == " << num_items << endl ;
      assert( valor_consumir < num_items );
   }
   cont_cons[valor_consumir] ++ ;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<min_ms,max_ms>() ));
   mtx.lock();
   cout << "                  hebra consumidora consume: " << valor_consumir << endl ;
   mtx.unlock();
}
//----------------------------------------------------------------------

void test_contadores()
{
   bool ok = true ;
   cout << "comprobando contadores ...." << endl ;

   for( unsigned i = 0 ; i < num_items ; i++ )
   {
      if ( cont_prod[i] != 1 )
      {
         cout << "error: valor " << i << " producido " << cont_prod[i] << " veces." << endl ;
         ok = false ;
      }
      if ( cont_cons[i] != 1 )
      {
         cout << "error: valor " << i << " consumido " << cont_cons[i] << " veces" << endl ;
         ok = false ;
      }
   }
   if (ok)
      cout << endl << flush << "solución (aparentemente) correcta." << endl << flush ;
}

// *****************************************************************************
// clase para monitor buffer, version FIFO, semántica SC, multiples prod/cons

class ProdConsSU1 : public HoareMonitor
{
	private:
	
	int primera_libre;
	static const int TAMANIO = 10;
	int buffer[TAMANIO];
	
	
	CondVar libres, ocupadas;
	
	public:
	
	ProdConsSU1(){
		primera_libre = 0;
		libres = newCondVar();
		ocupadas = newCondVar();
	}
	
	int consumir(){
	
		int resultado;
		
		if(primera_libre == 0){
			ocupadas.wait();
		}
		
		primera_libre--;
		resultado = buffer[primera_libre];
		libres.signal();
		return resultado;
	}
	
	void insertar(int dato){
		
		if(primera_libre == TAMANIO){
			libres.wait();
		}
		
		buffer[primera_libre] = dato;
		primera_libre++;
		ocupadas.signal();
	}
};

void  funcion_hebra_productora( MRef<ProdConsSU1> monitor, int i )
{
   int fin = (num_items/num_hebras);
   
   for( unsigned j = 0 ; j < fin ; j++ )
   {
      int dato = producir_dato(i) ;
      monitor->insertar(dato);
   }
}

//----------------------------------------------------------------------

void funcion_hebra_consumidora( MRef<ProdConsSU1> monitor)
{
   int fin = (num_items/num_hebras);
   for( unsigned j = 0 ; j < fin ; j++ )
   {
      int dato;
      dato = monitor->consumir();
      consumir_dato( dato );
   }
}

int main()
{
   cout << "--------------------------------------------------------------------" << endl
        << "Problema del productor-consumidor únicos (Monitor SU, buffer LIFO). " << endl
        << "--------------------------------------------------------------------" << endl
        << flush ;

   // crear monitor  ('monitor' es una referencia al mismo, de tipo MRef<...>)
   MRef<ProdConsSU1> monitor = Create<ProdConsSU1>() ;

   // crear y lanzar las hebras
   
   thread productoras[num_hebras];
   thread consumidoras[num_hebras];
   
   // Inicializamos el vector global de siguientes datos
   
   for(int i = 0; i < num_hebras; i++){
   	
   	siguiente_dato[i] = (num_items/num_hebras)*i;
   }
   
   for(int i = 0; i < num_hebras; i++){
   	productoras[i] = thread(funcion_hebra_productora, monitor, i);
   }
   
   
   for(int i = 0; i < num_hebras; i++){
   	consumidoras[i] = thread(funcion_hebra_consumidora, monitor);
   }
   
   // esperar a que terminen las hebras
   
   for(int i = 0; i < num_hebras; i++){
   	productoras[i].join();
   	consumidoras[i].join();
   }


   test_contadores() ;
}
