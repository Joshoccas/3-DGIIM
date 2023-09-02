//**********************************************************************//
// Sistemas Concurrentes y Distribuidos - 3ºDGIIM.
//
// Nombre y apellidos: José Alberto Hoces Castro
// Grupo: 1
// Archivo: sol_HocesCastroJoseAlberto.cpp
//**********************************************************************//

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
const int id_yoshi = 0;
const int id_mario = 1;
const int id_peach = 2;
const int num_procesos = 3;
const int x = 2; // Número de rondas

template <int min, int max>
int aleatorio()
{
   static default_random_engine generador((random_device())());
   static uniform_int_distribution<int> distribucion_uniforme(min, max);
   return distribucion_uniforme(generador);
}

//**********************************************************************
// 

//**********************************************************************
// Funciones hebras

void yoshi(){
	
	int puntos[num_procesos-1] = {0};
	int num_tartas;
	int id_equipo;
	
	
	for(int i = 0; i < x; i++){
		
		// Se deciden cuántas tartas se le mandan a qué equipo
		
		num_tartas = aleatorio<1,2>();
		id_equipo = aleatorio<1,2>();
		
		int * buffer1 = new int[num_tartas];
		
		for(int i = 0; i < num_tartas; i++){
			buffer1[i] = aleatorio<1,10>();
		}
		
		cout << "El equipo " << id_equipo << " se lleva " << num_tartas << " tartas en la tanda " << i+1 << endl;
		
		// Yoshi tarda en fabricar las tartas
		
		chrono::milliseconds duracion_produ( aleatorio<0,20>() );
		this_thread::sleep_for( duracion_produ );
		
		MPI_Send( buffer1, num_tartas, MPI_INT, id_equipo, 0, MPI_COMM_WORLD);
		
		// Y ahora lo mismo para el otro equipo que faltaba
		
		num_tartas = aleatorio<1,2>();
		id_equipo = (id_equipo+1)%2;
		
		if(id_equipo == 0)
			id_equipo = id_peach;
		
		int * buffer2 = new int[num_tartas];
		
		for(int i = 0; i < num_tartas; i++){
			buffer2[i] = aleatorio<1,10>();
		}
		
		cout << "El equipo " << id_equipo << " se lleva " << num_tartas << " tartas en la tanda " << i+1 << endl;
		
		// Yoshi tarda en fabricar las tartas
		
		chrono::milliseconds duracion_produ2( aleatorio<0,20>() );
		this_thread::sleep_for( duracion_produ2 );
		
		MPI_Send( buffer2, num_tartas, MPI_INT, id_equipo, 0, MPI_COMM_WORLD);
		
		delete [] buffer1;
		delete [] buffer2;
		
	}
	
	// Tras los envíos de las tartas, esperamos a recibir los mensajes de los equipos
	
	int valor1;
	int valor2;
	MPI_Status estado;
	
	for(int i = 0; i < x; i++){
	
		MPI_Recv ( &valor1, 1, MPI_INT, id_mario, 0, MPI_COMM_WORLD, &estado );
		MPI_Recv ( &valor2, 1, MPI_INT, id_peach, 0, MPI_COMM_WORLD, &estado );
		
		if(valor1 < valor2)
			puntos[id_peach-1]++;
		else if(valor2 < valor1)
			puntos[id_mario-1]++;
		
		// He decidido no sumarles nada si empatan
	}
	
	// Finalmente decidimos quién gana
	
	if(puntos[id_mario-1] > puntos[id_peach-1])
		cout << "Gana el equipo Mario con " << puntos[id_mario-1] << " puntos" << endl;
	else if(puntos[id_peach-1] > puntos[id_mario-1])
		cout << "Gana el equipo Peach con " << puntos[id_peach-1] << " puntos" << endl;
	else
		cout << "Ha habido empate con " << puntos[id_mario-1] << " puntos" << endl;
}

void equipo(int id){
	
	MPI_Status estado;
	int tamanio;
	int total = 0;
	int valor;
	
	for(int i = 0; i < x; i++){
		
		// Esperamos hasta que haya mensajes y vemos si nos pasan 1 o 2 tartas
		
		MPI_Probe(id_yoshi, 0, MPI_COMM_WORLD, &estado);
		MPI_Get_count( &estado, MPI_INT, &tamanio);
		
		int * buffer = new int[tamanio];
		
		MPI_Recv ( buffer, tamanio, MPI_INT, id_yoshi, 0, MPI_COMM_WORLD, &estado );
		
		// Mostramos por pantalla los pesos de las tartas recibidas
		
		for(int i = 0; i < tamanio; i++){
			
			cout << "Tarta " << i+1 << " del equipo " << id << " de la tanda " << x << ": " << buffer[i] << endl;
		}
		
		// Sumamos las cantidades de las tartas que nos han pasado
		
		for(int i = 0; i < tamanio; i++){
			total+=buffer[i];
		}
		
		// Hacemos un retraso aleatorio para simular el tiempo que comen
		
		chrono::milliseconds duracion_produ( 20 );
		this_thread::sleep_for( duracion_produ );

		// Decidimos cuántos de los kilos de tarta se come el equipo
		
		valor = total*(aleatorio<0,100>()/100.0);
		
		cout << "Equipo " << id << " se ha comido " << valor << " kg en la tanda " << i+1 << endl;
		
		// Notificamos a Yoshi 
		
		MPI_Send( &valor, 1, MPI_INT, id_yoshi, 0, MPI_COMM_WORLD);
		
		// Borramos el buffer, total y valor para la siguiente iteración
		
		delete [] buffer;
		valor = 0;
		total = 0;
		
		
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
   	if(id_propio == id_yoshi)
   		yoshi();
   	else
   		equipo(id_propio);
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
