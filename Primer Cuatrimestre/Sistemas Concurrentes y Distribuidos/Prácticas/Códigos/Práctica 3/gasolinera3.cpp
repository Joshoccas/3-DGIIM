#include <mpi.h>
#include <thread> // this_thread::sleep_for
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include <iostream>
#include <string>

using namespace std;
using namespace std::this_thread ;
using namespace std::chrono ;


//**********************************************************************
// Variables globales

const int num_coches = 6; 
const int id_gasolinera = 0;
const int id_impresor = 1;
const int num_combustibles = 3;
const int SURTIDORES[num_combustibles] = {3,2,3};
const int etiq_adquirir[num_combustibles] = {0,1,2};
const int etiq_liberar = 3;
int num_procesos = num_coches + 2;

template <int min, int max>
int aleatorio()
{
   static default_random_engine generador((random_device())());
   static uniform_int_distribution<int> distribucion_uniforme(min, max);
   return distribucion_uniforme(generador);
}

//**********************************************************************
// Imprimir

void imprimir(const string & mensaje){
	
	MPI_Ssend(mensaje.c_str(), mensaje.length(), MPI_CHAR, id_impresor, 0, MPI_COMM_WORLD);
}

//**********************************************************************
// Funciones hebras

void funcion_gasolinera(){

	
	int surtidores[num_combustibles];
	
	for(int i = 0; i < num_combustibles; i++){
		surtidores[i] = SURTIDORES[i];
	}
	
	
	int flag,
	valor,
	contador_mensajes = 0;
	MPI_Status estado;
	
	while(true){
		
		MPI_Iprobe( MPI_ANY_SOURCE, etiq_liberar, MPI_COMM_WORLD, &flag, &estado );
		
		if(flag > 0){
		
			MPI_Recv ( &valor, 1, MPI_INT, MPI_ANY_SOURCE, etiq_liberar, MPI_COMM_WORLD, &estado );
			
			surtidores[valor]++;
			
			contador_mensajes++;
		}
		
		for(int i = 0; i < num_combustibles; i++){
			
			MPI_Iprobe( MPI_ANY_SOURCE, etiq_adquirir[i], MPI_COMM_WORLD, &flag, &estado );
			
			if(flag > 0 && surtidores[i] > 0){
			
				MPI_Recv ( &valor, 1, MPI_INT, MPI_ANY_SOURCE, etiq_adquirir[i], MPI_COMM_WORLD, &estado );
				surtidores[i]--;
				contador_mensajes++;
			}
		}
		
		
		if(contador_mensajes > 0){
			
			// Si no hay mensajes aceptables, espera 20 milisegundos
			
			chrono::milliseconds duracion_produ( 20 );
			this_thread::sleep_for( duracion_produ );
		}
		
		// Actualizamos el contador de mensajes aceptables a 0 para la siguiente iteración
		
		contador_mensajes = 0;	
	}
}

void funcion_coche(int id){
	
	int valor = 0;
	int etiqueta;
	string mensaje;
	
	while( true ){
	
		// Determinamos el tipo de combustible que necesita el coche
		
		etiqueta = aleatorio<0,2>();
		
		MPI_Ssend( &valor, 1, MPI_INT, id_gasolinera, etiqueta, MPI_COMM_WORLD );
		
		valor = etiqueta;
		
		mensaje = "Coche " + to_string(id) + " comienza a repostar combustible " + to_string(etiqueta);
		
		imprimir(mensaje);
		
		// Hacemos una espera aleatoria
		
		chrono::milliseconds duracion_produ( aleatorio<10,100>() );
		this_thread::sleep_for( duracion_produ );
		
		// Liberamos el surtidor y mandamos el mensaje para imprimir
		
		MPI_Ssend( &valor, 1, MPI_INT, id_gasolinera, etiq_liberar, MPI_COMM_WORLD );
		
		mensaje = "Coche " + to_string(id) + " termina de repostar combustible " + to_string(etiqueta);
		
		imprimir(mensaje);
		
		// Retraso aleatorio antes de volver a la gasolinera
		
		chrono::milliseconds duracion_produ2( aleatorio<10,100>() );
		this_thread::sleep_for( duracion_produ2 );
	}
}

void funcion_impresor(){
	
	int tamanio;
	MPI_Status estado;
	
	while(true){
	
		MPI_Probe( MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &estado );
		MPI_Get_count( &estado, MPI_CHAR, &tamanio );
		
		char * buffer = new char[tamanio+1];
		MPI_Recv( buffer, tamanio, MPI_CHAR, estado.MPI_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &estado );
		
		buffer[tamanio] = '\0';
		
		cout << buffer << endl;
		delete [] buffer;
	}
	
	
	
}

//**********************************************************************

int main( int argc, char** argv )
{
   int id_propio, num_procesos_actual ;

   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &id_propio );
   MPI_Comm_size( MPI_COMM_WORLD, &num_procesos_actual );


   if ( num_procesos == num_procesos_actual )
   {
      // ejecutar la función correspondiente a 'id_propio'
      if ( id_propio == id_gasolinera )          // si es la hebra 0
         funcion_gasolinera(); //   es la gasolinera
      else if( id_propio == id_impresor )                    // si es la hebra 1
         funcion_impresor(); //   es el impresor
      else					// si no es la hebra 0 ni 1
         funcion_coche( id_propio );          // es un coche
   }
   else
   {
      if ( id_propio == 0 ) // solo el primero escribe error, indep. del rol
      { cout << "el número de procesos esperados es:    " << num_procesos << endl
             << "el número de procesos en ejecución es: " << num_procesos_actual << endl
             << "(programa abortado)" << endl ;
      }
   }

   MPI_Finalize( );
   return 0;
}
