#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random>
#include "scd.h"
#include <atomic>

using namespace std ;
using namespace scd ;

const int num_hebras = 4;
int vidas[num_hebras];
bool acabado = false;

class Tablero : public HoareMonitor{

	private:
		
	static const int NUM_JUGADORES = 4;
	int tablero[NUM_JUGADORES][NUM_JUGADORES];
	CondVar golpeado;
	int jugando;
	
	public:
	
	Tablero();
	void mover_jugador(int *i, int *j, int id);
	void mover_enemigo();
	
};

Tablero::Tablero(){
	
	for(int j = 0; j < NUM_JUGADORES; j++){
		tablero[0][j] = j;
	}
	
	for(int i = 1; i < NUM_JUGADORES; i++){
		for(int j = 0; j < num_hebras; j++){
		
			tablero[i][j] = -1;
		}
	}
	
	golpeado = newCondVar();
	jugando = NUM_JUGADORES;
}

void Tablero::mover_jugador(int *i, int *j, int id){
	
	
	if(tablero[*i][*j] == -1 && jugando > 1){
		
		jugando--;
		vidas[id]--;
		cout << "Jugador " << id << " golpeado . Me quedan " << vidas[id] << " vidas" << endl;
		golpeado.wait();
		golpeado.signal();
	}
	else if(tablero[*i][*j] == -1 && jugando == 1){
		
		vidas[id]--;
		jugando = NUM_JUGADORES;
		golpeado.signal();
	}
	
	if(vidas[id] != 0){
		int pos_x = aleatorio<0,NUM_JUGADORES-1>();
		int pos_y = aleatorio<0,NUM_JUGADORES-1>();
		
		if(tablero[pos_x][pos_y] == -1){
			tablero[*i][*j] = -1;
			tablero[pos_x][pos_y] = id;
			*i = pos_x;
			*j = pos_y;
			
			cout << "Jugador " << id << " se mueve a la posición (" << pos_x << "," << pos_y << ")" << endl;
		}
	}
}

void Tablero::mover_enemigo(){
	
	int linea;
	linea = aleatorio<0,1>();
	
	int numero = aleatorio <0,NUM_JUGADORES-1>();
	
	// Imprimimos la situación del tablero antes de moverse el enemigo
	
	string cadena_pos, cadena_vidas;

   	 for (int i = 0; i < NUM_JUGADORES; i++){
        	for(int j = 0; j < NUM_JUGADORES; j++){
            		if (tablero[i][j] == -1)
               	 cadena_pos += "   |";
            	else
                	cadena_pos += " " + to_string(tablero[i][j]) + " |";
        	}
        	
        	cadena_pos.pop_back();
        	cadena_pos += "\n";

        	cadena_vidas += "Jugador " + to_string(i) + " : " + to_string(vidas[i]) + " vidas.\n";
    	}

    	cout << "Posicion de los jugadores en el tablero:" << endl << cadena_pos << endl;
    	cout << "Vidas restantes:" << endl << cadena_vidas << endl << endl;
    	
	if(linea == 0){
		
		cout << "El enemigo barre la fila " << numero << endl;
		for(int j = 0; j < NUM_JUGADORES; j++){
			tablero[numero][j] = -1;
		}
	}
	else{
	
		cout << "El enemigo barre la columna " << numero << endl;
		for(int i = 0; i < NUM_JUGADORES; i++){
			tablero[i][numero] = -1;
		}
	}
}

void funcion_hebra_jugadora(MRef <Tablero> monitor, int i){

	int x = 0, y = i;
	
	while(vidas[i] > 0){
		monitor->mover_jugador(&x,&y,i);
	}
	
	cout << "El jugador " << i << " ha perdido sus vidas" << endl;
	
	
}

void funcion_hebra_enemigo(MRef <Tablero> monitor){

	acabado = false;
	
	while(!acabado){
	
		monitor->mover_enemigo();
		
		acabado = true;
		for(int i = 0; i < num_hebras; i++){
			if(vidas[i] > 0){
				acabado = false;
			}
		}
	}
}

int main(){
	
	MRef<Tablero> monitor = Create<Tablero>();
	thread jugadores[num_hebras];
	thread enemigo;
	
	for(int i = 0; i < num_hebras; i++){
		vidas[i] = 3;
		jugadores[i] = thread(funcion_hebra_jugadora, monitor, i);
	}
	
	enemigo = thread(funcion_hebra_enemigo, monitor);
	
	for(int i = 0; i < num_hebras; i++){
		jugadores[i].join();
	}
	
	enemigo.join();


	return 0;
}

