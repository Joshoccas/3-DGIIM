#include <mpi.h>
#include <thread> // this_thread::sleep_for
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include <iostream>
#include <string>

using namespace std;
using namespace std::this_thread ;
using namespace std::chrono ;

/*
MPI_Iprobe( id_emisor, tag, MPI_COMM_WORLD, &flag, &estado );
MPI_Probe( id_emisor, tag, MPI_COMM_WORLD, &estado );
MPI_Get_count( &estado, MPI_CHAR o loqsea, &size );
MPI_Ssend( &valor, 1, MPI_INT, id_receptor, tag, MPI_COMM_WORLD );
MPI_Recv ( &valor, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &estado );
MPI_Isend( &valor, size, MPI_Datatype, id_receptor, tag, MPI_COMM_WORLD, MPI_Request & request );
MPI_Irecv( &valor, size, MPI_Datatype, id_emisor, tag, MPI_COMM_WORLD, MPI_Request & request );
MPI_Wait ( &request, &estado );
*/


//**********************************************************************
// Variables globales

int num_procesos = 6;
int id_impresor = 0;


template <int min, int max>
int aleatorio()
{
   static default_random_engine generador((random_device())());
   static uniform_int_distribution<int> distribucion_uniforme(min, max);
   return distribucion_uniforme(generador);
}

/*
chrono::milliseconds duracion_produ( 20 );
this_thread::sleep_for( duracion_produ );
*/

//**********************************************************************
// 

//**********************************************************************
// Funciones hebras

void inout(){

	string cadena;
	
	do{
		cin >> cadena;
	}
	while(cadena.length() != num_procesos - 1);
	
	int id_siguiente = id_impresor+1;
	
	for(int i = 0; i < num_procesos - 1; i++){
		MPI_Ssend( &cadena.at(i), 1, MPI_CHAR, id_siguiente, 0, MPI_COMM_WORLD );
	}
	
	char recibido;
	MPI_Status estado;
	
	for(int i = num_procesos-1; i > 0; i--){
		
		MPI_Recv ( &recibido, 1, MPI_CHAR, i, 0, MPI_COMM_WORLD, &estado );
		
		cout << recibido;
	}
}

void comparar(int id){
	
	char actual = '*';
	char recibido;
	int id_siguiente = id+1;
	int id_anterior = id-1;
	MPI_Status estado;
	
	for(int i = 0; i < num_procesos-id; i++){
		
		MPI_Recv ( &recibido, 1, MPI_CHAR, id_anterior, 0, MPI_COMM_WORLD, &estado );
		
		if(actual == '*')
			actual = recibido;
		else{
			if(actual > recibido)
				MPI_Ssend( &recibido, 1, MPI_CHAR, id_siguiente, 0, MPI_COMM_WORLD );
			else{
				MPI_Ssend( &actual, 1, MPI_CHAR, id_siguiente, 0, MPI_COMM_WORLD );
				actual = recibido;
			}
		}	
	}
	
	MPI_Ssend( &actual, 1, MPI_CHAR, id_impresor, 0, MPI_COMM_WORLD );
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
   	if(id_propio == id_impresor)
   		inout();
   	else
   		comparar(id_propio);
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
