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

void met1(){
}

void met2(){
}

void met3(){	
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
