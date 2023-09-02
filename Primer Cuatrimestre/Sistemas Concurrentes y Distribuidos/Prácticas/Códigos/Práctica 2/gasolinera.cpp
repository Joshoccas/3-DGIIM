#include <iostream>
#include <thread>
#include <random>
#include "scd.h"
#include <atomic>
#include <string>

using namespace std ;
using namespace scd ;

//**********************************************************************
// Variables globales

const int NUM_GASOLINA = 6;
const int NUM_GASOIL = 4;

//**********************************************************************
// Monitor Gasolinera

class Gasolinera : public HoareMonitor
{
	private:
	
	int surtidores_gasolina;
	int surtidores_gasoil;
	CondVar gasoil;
	CondVar gasolina;
	
	public:
	
	Gasolinera();
	
	void adquirir_surtidor_gasolina();
	
	void adquirir_surtidor_gasoil();
	
	void liberar_surtidor_gasolina();
	
	void liberar_surtidor_gasoil();
};

Gasolinera::Gasolinera(){

	surtidores_gasolina = 3;
	surtidores_gasoil = 2;
	gasoil = newCondVar();
	gasolina = newCondVar();
}

void Gasolinera::adquirir_surtidor_gasolina(){
	
	if(surtidores_gasolina == 0){
		gasolina.wait();
	}
	
	surtidores_gasolina--;
}

void Gasolinera::adquirir_surtidor_gasoil(){

	if(surtidores_gasoil == 0){
		gasoil.wait();
	}
	
	surtidores_gasoil--;
}

void Gasolinera::liberar_surtidor_gasolina(){

	surtidores_gasolina++;
	
	if(!gasolina.empty()){
		gasolina.signal();
	}
}

void Gasolinera::liberar_surtidor_gasoil(){

	surtidores_gasoil++;
	
	if(!gasoil.empty()){
		gasoil.signal();
	}
}

//**********************************************************************
// Repostar

void repostar(int i, string cadena){

	cout << "Hebra " << i << " comienza a repostar " << cadena << endl;
	chrono::milliseconds duracion_produ( aleatorio<10,100>() );
	this_thread::sleep_for( duracion_produ );
	cout << "Hebra " << i << " termina de repostar " << cadena << endl;
	
}

//**********************************************************************
// Funciones hebras

void funcion_hebra_gasolina(int i, MRef<Gasolinera> monitor){

	while(true){
		monitor->adquirir_surtidor_gasolina();
		repostar(i,"gasolina");
		monitor->liberar_surtidor_gasolina();
		
		// Retraso aleatorio antes de volver a la gasolinera
		
		chrono::milliseconds duracion_produ( aleatorio<10,100>() );
		this_thread::sleep_for( duracion_produ );
	}
}

void funcion_hebra_gasoil(int i, MRef<Gasolinera> monitor){

	while(true){
		monitor->adquirir_surtidor_gasoil();
		repostar(i,"gasoil");
		monitor->liberar_surtidor_gasoil();
		
		// Retraso aleatorio antes de volver a la gasolinera
		
		chrono::milliseconds duracion_produ( aleatorio<10,100>() );
		this_thread::sleep_for( duracion_produ );
	}
}

void funcion_hebra_test(MRef<Gasolinera> monitor){

	monitor->test();
}

//**********************************************************************


int main(){

	MRef<Gasolinera> monitor = Create<Gasolinera>();
	
	thread coches_gasolina[NUM_GASOLINA];
	thread coches_gasoil[NUM_GASOIL];
	
	for(int i = 0; i < NUM_GASOLINA; i++){
		coches_gasolina[i] = thread(funcion_hebra_gasolina, i, monitor);
	}
	
	for(int j = 0; j < NUM_GASOIL; j++){
		coches_gasoil[j] = thread(funcion_hebra_gasoil, j, monitor);
	}
	
	for(int i = 0; i < NUM_GASOLINA; i++){
		coches_gasolina[i].join();
	}
	
	for(int j = 0; j < NUM_GASOIL; j++){
		coches_gasoil[j].join();
	}

	return 0;
}
