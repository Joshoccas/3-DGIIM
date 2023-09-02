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
   num_items = 75 ;   // número de items
unsigned  
   cont_prod[num_items] = {0}, // contadores de verificación: para cada dato, número de veces que se ha producido.
   cont_cons[num_items] = {0}; // contadores de verificación: para cada dato, número de veces que se ha consumido.

int siguiente_dato[num_hebras];
const int TAMANIO = 15;
int buffer[TAMANIO] = {0};
int primera_libre = 0;
int primera_ocupada = 0;


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

//----------------------------------------------------------------------

class ProdConsSU1 : public HoareMonitor
{
	private:

	int ocupacion;
	int tam_buffer;
	bool produciendo;
	bool consumiendo;
	CondVar prod, cons;
	
	public:
	
	ProdConsSU1(int t){
		ocupacion = 0;
		tam_buffer = t;
		produciendo = false;
		consumiendo = false;
		prod = newCondVar();
		cons = newCondVar();
	}
	
	void inicio_insercion(int i, int v){
	
		if(ocupacion == tam_buffer || produciendo){
			prod.wait();
		}
		
		assert(!produciendo && ocupacion < tam_buffer);
		
		produciendo = true;
		
		cout << "Hebra productora " << i << " comienza a insertar el valor " << v << endl;
	}
	
	void fin_insercion(int i, int v){
	
		produciendo = false;
		ocupacion++;
		
		cout << "Hebra productora " << i << " ya ha insertado el valor " << v << endl;
		
		cons.signal();
	}
	
	void inicio_extraccion(int i){
	
		if(ocupacion == 0 || consumiendo){
			cons.wait();
		}
		
		assert(!consumiendo && ocupacion > 0);
		
		consumiendo = true;
		
		cout << "Hebra consumidora " << i << " comienza a extraer" << endl;
	}
	
	void fin_extraccion(int i, int v){
	
		consumiendo = false;
		ocupacion--;
		
		cout << "Hebra consumidora " << i << " ha consumido el valor " << v << endl;
		
		prod.signal();
	}
};

//----------------------------------------------------------------------

void  funcion_hebra_productora( MRef<ProdConsSU1> monitor, int id )
{
   int fin = num_items/num_hebras;
   
   for( unsigned i = 0 ; i < fin ; i++ )
   {
      int dato = producir_dato(id) ;
      monitor->inicio_insercion(id,dato);
      buffer[primera_libre] = dato;
      primera_libre = (primera_libre+1)%TAMANIO;
      monitor->fin_extraccion(id,dato);
   }
}

//----------------------------------------------------------------------

void funcion_hebra_consumidora( MRef<ProdConsSU1> monitor, int id )
{
   int fin = num_items/num_hebras;
   
   for( unsigned i = 0 ; i < fin ; i++ )
   {
      int dato ;
      monitor->inicio_extraccion(id);
      dato = buffer[primera_ocupada];
      primera_ocupada = (primera_ocupada+1)%TAMANIO;
      monitor->fin_extraccion(id,dato);
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

   MRef<ProdConsSU1> monitor = Create<ProdConsSU1>(TAMANIO) ;
   
   thread productores[num_hebras];
   thread consumidores[num_hebras];
   
   for(int i = 0; i < num_hebras; i++){
   	
   	siguiente_dato[i] = (num_items/num_hebras)*i;
   }
   
   for(int i = 0; i < num_hebras; i++){
   
          productores[i] = thread (funcion_hebra_productora, monitor, i);
          consumidores[i] = thread (funcion_hebra_consumidora, monitor, i);
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
