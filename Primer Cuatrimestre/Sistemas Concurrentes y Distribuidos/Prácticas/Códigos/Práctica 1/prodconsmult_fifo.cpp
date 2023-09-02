#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random>
#include "scd.h"
#include <atomic>

using namespace std ;
using namespace scd ;

//**********************************************************************
// Variables globales

const int num_hebras = 5;
const unsigned 
   num_items = 75 ,   // número de items
	tam_vec   = 15 ;   // tamaño del buffer
unsigned  
   cont_prod[num_items] = {0}, // contadores de verificación: para cada dato, número de veces que se ha producido.
   cont_cons[num_items] = {0}; // contadores de verificación: para cada dato, número de veces que se ha consumido.

atomic<int> primera_libre(0);
atomic<int> primera_ocupada(0);
int productos[tam_vec] = {0};
Semaphore libres = tam_vec;
Semaphore ocupadas = 0;

int siguiente_dato[num_hebras];

//**********************************************************************
// funciones comunes a las dos soluciones (fifo y lifo)
//----------------------------------------------------------------------

unsigned producir_dato(int i)
{
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));
   const unsigned dato_producido = siguiente_dato[i] ;
   siguiente_dato[i]++ ;
   cont_prod[dato_producido] ++ ;
   cout << "producido: " << dato_producido << endl;
   return dato_producido ;
}
//----------------------------------------------------------------------

void consumir_dato( unsigned dato )
{
   assert( dato < num_items );
   cont_cons[dato] ++ ;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));

   cout << "                  consumido: " << dato << endl;

}


//----------------------------------------------------------------------

void test_contadores()
{
   bool ok = true ;
   cout << "comprobando contadores ...." ;
   for( unsigned i = 0 ; i < num_items ; i++ )
   {  if ( cont_prod[i] != 1 )
      {  cout << "error: valor " << i << " producido " << cont_prod[i] << " veces." << endl ;
         ok = false ;
      }
      if ( cont_cons[i] != 1 )
      {  cout << "error: valor " << i << " consumido " << cont_cons[i] << " veces" << endl ;
         ok = false ;
      }
   }
   if (ok)
      cout << endl << flush << "solución (aparentemente) correcta." << endl << flush ;
}

void  funcion_hebra_productora( int id )
{
   int fin = num_items/num_hebras;
   for( unsigned i = 0 ; i < fin ; i++ )
   {
      int dato = producir_dato(id) ;
      sem_wait(libres);
      productos[primera_libre] = dato;
      primera_libre++;
      primera_libre = primera_libre%tam_vec;
      sem_signal(ocupadas);
   }
}

//----------------------------------------------------------------------

void funcion_hebra_consumidora( )
{
   int fin = num_items/num_hebras;
   for( unsigned i = 0 ; i < fin ; i++ )
   {
      int dato ;
      sem_wait(ocupadas);
      dato = productos[primera_ocupada];
      primera_ocupada++;
      primera_ocupada = primera_ocupada%tam_vec;
      sem_signal(libres);
      consumir_dato( dato ) ;
    }
}
//----------------------------------------------------------------------

int main()
{
   cout << "-----------------------------------------------------------------" << endl
        << "Problema de los productores-consumidores (solución FIFO ?)." << endl
        << "------------------------------------------------------------------" << endl
        << flush ;

   thread productores[num_hebras];
   thread consumidores[num_hebras];
   
   for(int i = 0; i < num_hebras; i++){
   	
   	siguiente_dato[i] = (num_items/num_hebras)*i;
   }
   
   for(int i = 0; i < num_hebras; i++){
   
          productores[i] = thread (funcion_hebra_productora,i);
          consumidores[i] = thread (funcion_hebra_consumidora);
   }
   
   for(int i = 0; i < num_hebras; i++){
          productores[i].join();
   }
   
   for(int i = 0; i < num_hebras; i++){
          consumidores[i].join();
   }

    
   cout << "Fin de la ejecución de las hebras productoras y consumidoras" << endl;

   test_contadores();

   return 0;
}
