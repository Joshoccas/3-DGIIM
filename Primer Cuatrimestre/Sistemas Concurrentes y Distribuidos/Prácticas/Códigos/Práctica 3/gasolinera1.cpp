#include <mpi.h>
#include <thread> // this_thread::sleep_for
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include <iostream>

using namespace std;
using namespace std::this_thread ;
using namespace std::chrono ;


//**********************************************************************
// Variables globales

const int num_gasolina = 6; // Va a haber 6 coches que necesitan gasolina
const int id_gasolinera = 0;
const int etiq_adquirir = 0;
const int etiq_liberar = 1;
int num_procesos = num_gasolina + 1; 

template <int min, int max>
int aleatorio()
{
   static default_random_engine generador((random_device())());
   static uniform_int_distribution<int> distribucion_uniforme(min, max);
   return distribucion_uniforme(generador);
}

//**********************************************************************
// Repostar

void repostar(int i){

	cout << "Hebra " << i << " comienza a repostar gasolina" << endl;
	chrono::milliseconds duracion_produ( aleatorio<10,100>() );
	this_thread::sleep_for( duracion_produ );
	cout << "Hebra " << i << " termina de repostar gasolina" << endl;
	
}

//**********************************************************************
// Funciones hebras

void funcion_gasolinera(){

	
	int surtidores_disponibles = 3;
	int etiq_permitida,
	valor;
	MPI_Status estado;
	
	while(true){
		
		if(surtidores_disponibles == 0)
			etiq_permitida = etiq_liberar;
		else if(surtidores_disponibles == 3)
			etiq_permitida = etiq_adquirir;
		else
			etiq_permitida = MPI_ANY_TAG;
		
		MPI_Recv ( &valor, 1, MPI_INT, MPI_ANY_SOURCE, etiq_permitida, MPI_COMM_WORLD, &estado );
		
		switch( estado.MPI_TAG ){
			case etiq_adquirir:
				surtidores_disponibles--;
				break;
			case etiq_liberar:
				surtidores_disponibles++;
				break;
		}
	}
}

void funcion_coche(int id){
	
	int valor = 0;
	
	while( true ){
		
		MPI_Ssend( &valor, 1, MPI_INT, id_gasolinera, etiq_adquirir, MPI_COMM_WORLD );
		
		repostar(id);
		
		MPI_Ssend( &valor, 1, MPI_INT, id_gasolinera, etiq_liberar, MPI_COMM_WORLD );
		
		// Retraso aleatorio antes de volver a la gasolinera
		
		chrono::milliseconds duracion_produ( aleatorio<10,100>() );
		this_thread::sleep_for( duracion_produ );
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
      else                               // si no es la hebra 0
         funcion_coche( id_propio ); //   es un coche de gasolina
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
