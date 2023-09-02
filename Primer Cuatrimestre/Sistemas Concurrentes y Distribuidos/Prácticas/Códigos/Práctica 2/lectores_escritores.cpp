#include <iostream>
#include <iomanip>
#include <cassert>
#include <random>
#include <thread>
#include <mutex>
#include "scd.h"

using namespace std ;
using namespace scd ;

const int num_lectores = 2;
const int num_escritores = 3;
mutex salida;

void leer(int i)
{
   // calcular milisegundos aleatorios de duración de la acción de leer)
   chrono::milliseconds duracion_produ( aleatorio<10,100>() );

   // informa de que comienza a leer
   
   cout << "Lector " << i << ": comienza a leer (" << duracion_produ.count() << " milisegundos)" << endl;
   

   // espera bloqueada un tiempo igual a ''duracion_produ' milisegundos
   this_thread::sleep_for( duracion_produ );
}

void escribir(int i)
{
   // calcular milisegundos aleatorios de duración de la acción de escribir)
   chrono::milliseconds duracion_produ( aleatorio<10,100>() );

   // informa de que comienza a escribir
  
   cout << "Escritor " << i << ": comienza a escribir (" << duracion_produ.count() << " milisegundos)" << endl;
   

   // espera bloqueada un tiempo igual a ''duracion_produ' milisegundos
   this_thread::sleep_for( duracion_produ );
}

void retraso_aleatorio(){

   // calcular milisegundos aleatorios de duración de la acción de leer)
   chrono::milliseconds duracion_produ( aleatorio<10,100>() );

   // espera bloqueada un tiempo igual a ''duracion_produ' milisegundos
   this_thread::sleep_for( duracion_produ );
}

class Lec_Esc : public HoareMonitor{

	private:
	
	int nlec;
	bool escrib;
	CondVar lectores, escritores;
	
	public:
	
	Lec_Esc(){
		
		nlec = 0;
		escrib = false;
		lectores = newCondVar();
		escritores = newCondVar();
	}
	
	void inicio_lectura(){
		
		if(escrib){
			lectores.wait();
		}
		
		nlec++;
		lectores.signal();
	}
	
	void fin_lectura(){
	
		nlec--;
		
		if(nlec == 0){
			escritores.signal();
		}
		
	}
	
	void inicio_escritura(){
	
		if(escrib || nlec > 0){
			escritores.wait();
		}
		
		escrib = true;
	}
	
	void fin_escritura(){
	
		escrib = false;
		
		if(!lectores.empty()){
			lectores.signal();
		}
		else{
			escritores.signal();
		}
	}
};

void funcion_hebra_escritora(int num_escritor, MRef<Lec_Esc> monitor){
   
   while(true){
      monitor->inicio_escritura();
      escribir(num_escritor);
      monitor->fin_escritura();
      retraso_aleatorio();
   }
}

void funcion_hebra_lectora(int num_lector, MRef<Lec_Esc> monitor){
   
   while(true){
      monitor->inicio_lectura();
      leer(num_lector);
      monitor->fin_lectura();
      retraso_aleatorio();
   }
}

int main(){

    MRef<Lec_Esc> monitor = Create<Lec_Esc>();
    
    thread lectores[num_lectores];
    thread escritores[num_escritores];
    
    for(int i = 0; i < num_escritores; i++){
       
       escritores[i] = thread(funcion_hebra_escritora,i,monitor);
    }
    
    for(int i = 0; i < num_lectores; i++){
       
       lectores[i] = thread(funcion_hebra_lectora,i,monitor);
    }


   for(int i = 0; i < num_escritores; i++){
   	
   	escritores[i].join();
   }
   
   for(int i = 0; i < num_lectores; i++){
   	
   	lectores[i].join();
   }

    return 0;
}
