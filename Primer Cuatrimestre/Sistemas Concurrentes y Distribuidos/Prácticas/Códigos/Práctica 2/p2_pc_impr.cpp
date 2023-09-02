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

//----------------------------------------------------------------------

class ProdConsSU1 : public HoareMonitor
{
	private:
	
	int primera_libre;
	int primera_ocupada;
	int ocupacion;
	int multiplos;
	static const int TAMANIO = 10;
	int buffer[TAMANIO];
	
	
	CondVar libres, ocupadas, multiplos5;
	
	public:
	
	ProdConsSU1(){
		primera_libre = 0;
		primera_ocupada = 0;
		multiplos = 0;
		ocupacion = 0;
		libres = newCondVar();
		ocupadas = newCondVar();
		multiplos5 = newCondVar();
	}
	
	int consumir(){
	
		int resultado;
		
		if(ocupacion == 0){
			ocupadas.wait();
		}
		
		resultado = buffer[primera_ocupada];
		
		primera_ocupada++;
		primera_ocupada = primera_ocupada%TAMANIO;
		ocupacion--;
		libres.signal();
		
		return resultado;
	}
	
	void insertar(int dato){
		
		if(ocupacion == TAMANIO){
			libres.wait();
		}
		
		buffer[primera_libre] = dato;
		
		primera_libre++;
		primera_libre = primera_libre%TAMANIO;
		ocupacion++;
		
		if(dato % 5 == 0){
		
			multiplos++;
			multiplos5.signal();
		}
		
		ocupadas.signal();
	}
	
	bool metodo_impresora(int *auxiliar){
	
		bool resultado = true;
		if (multiplos == num_items/5){
			resultado = false;
		}
		else{
			
			if(*auxiliar - multiplos == 0){
				multiplos5.wait();
			}
			
			cout << "Se han producido " << multiplos - *auxiliar << " múltiplos de 5 nuevos " << endl;
			*auxiliar = multiplos;
		}
		
		return resultado;
	}
};

//----------------------------------------------------------------------

void  funcion_hebra_productora( MRef<ProdConsSU1> monitor, int id )
{
   int fin = num_items/num_hebras;
   
   for( unsigned i = 0 ; i < fin ; i++ )
   {
      int dato = producir_dato(id) ;
      monitor->insertar(dato);
   }
}

//----------------------------------------------------------------------

void funcion_hebra_consumidora( MRef<ProdConsSU1> monitor )
{
   int fin = num_items/num_hebras;
   
   for( unsigned i = 0 ; i < fin ; i++ )
   {
      int dato ;
      dato = monitor->consumir();
      consumir_dato( dato ) ;
    }
}
//----------------------------------------------------------------------

void funcion_hebra_impresora( MRef<ProdConsSU1> monitor )
{

	int auxiliar = 0;
	while(monitor->metodo_impresora(&auxiliar)){
	}
	
	cout << "Ya se han producido todos los múltiplos de 5" << endl;
}

//----------------------------------------------------------------------

int main()
{
   cout << "-----------------------------------------------------------------" << endl
        << "Problema de los productores-consumidores (solución FIFO ?)." << endl
        << "------------------------------------------------------------------" << endl
        << flush ;

   MRef<ProdConsSU1> monitor = Create<ProdConsSU1>() ;
   
   thread productores[num_hebras];
   thread consumidores[num_hebras];
   thread impresora;
   
   for(int i = 0; i < num_hebras; i++){
   	
   	siguiente_dato[i] = (num_items/num_hebras)*i;
   }
   
   impresora = thread(funcion_hebra_impresora, monitor);
   
   for(int i = 0; i < num_hebras; i++){
   
          productores[i] = thread (funcion_hebra_productora, monitor, i);
          consumidores[i] = thread (funcion_hebra_consumidora, monitor);
   }
   
   for(int i = 0; i < num_hebras; i++){
          productores[i].join();
   }
   
   for(int i = 0; i < num_hebras; i++){
          consumidores[i].join();
   }
   
   impresora.join();

    
   cout << "Fin de la ejecución de las hebras productoras y consumidoras" << endl;

   test_contadores();

   return 0;
}
