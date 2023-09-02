#include <iostream>
#include <thread>
#include <random>
#include "scd.h"
#include <atomic>

using namespace std ;
using namespace scd ;

//**********************************************************************
// Variables globales

const int NUM_GASOIL = 4;
const int NUM_GASOLINA = 6;
atomic<int> NUM_SURTIDORES_EN_USO(0);

Semaphore gasoil = 2;
Semaphore gasolina = 3;

//**********************************************************************

// Repostar

void repostar(int i){

	cout << "Hebra " << i << " comienza a repostar " << endl;
	chrono::milliseconds duracion_produ( aleatorio<10,100>() );
	this_thread::sleep_for( duracion_produ );
	cout << "Hebra " << i << " termina de repostar " << endl;
	
}

// Funciones hebras
//----------------------------------------------------------------------

void funcion_hebra_gasolina(int i){

	while(true){
		sem_wait(gasolina);
		NUM_SURTIDORES_EN_USO++;
		repostar(i);
		NUM_SURTIDORES_EN_USO--;
		sem_signal(gasolina);
		
		// Retraso aleatorio antes de volver a la gasolinera
		
		chrono::milliseconds duracion_produ( aleatorio<10,100>() );
		this_thread::sleep_for( duracion_produ );
	}
}
//----------------------------------------------------------------------

void funcion_hebra_gasoil(int i){

	while(true){
		sem_wait(gasoil);
		NUM_SURTIDORES_EN_USO++;
		repostar(i);
		NUM_SURTIDORES_EN_USO--;
		sem_signal(gasoil);
		
		// Retraso aleatorio antes de volver a la gasolinera
		
		chrono::milliseconds duracion_produ( aleatorio<10,100>() );
		this_thread::sleep_for( duracion_produ );
	}
}

//----------------------------------------------------------------------

void test(){
	
	while(true){
		chrono::seconds tiempo(2);
		this_thread::sleep_for(tiempo);
		cout << "Surtidores en uso: " << NUM_SURTIDORES_EN_USO << endl;
	}
}

//----------------------------------------------------------------------

int main(){
	
	thread coches_gasolina[NUM_GASOLINA];
	thread coches_gasoil[NUM_GASOIL];
	
	for(int i = 0; i < NUM_GASOLINA; i++){
		coches_gasolina[i] = thread(funcion_hebra_gasolina, i);
	}
	
	for(int j = 0; j < NUM_GASOIL; j++){
		coches_gasoil[j] = thread(funcion_hebra_gasoil, j);
	}
	
	test();
	
	for(int i = 0; i < NUM_GASOLINA; i++){
		coches_gasolina[i].join();
	}
	
	for(int j = 0; j < NUM_GASOIL; j++){
		coches_gasoil[j].join();
	}


return 0;
}
