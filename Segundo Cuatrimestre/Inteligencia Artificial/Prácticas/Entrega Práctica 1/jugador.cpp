#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
#include <cmath>
using namespace std;

bool ComportamientoJugador::PuedeAvanzar(char terreno, int bateria){

	bool avanzar = true;

	if(terreno == 'P'){
		avanzar = false;
	} else if(terreno == 'M'){
		avanzar = false;
	} else if(terreno == 'A' and !bikini){
		avanzar = false;
	} else if(terreno == 'B' and !zapatillas  and bateria < 2000){
		avanzar = false;
	}

	if(bien_situado){

		if(terreno == 1){
			switch(current_state.brujula){

				case norte: if(contador[current_state.fil-1][current_state.col-1] > 20) avanzar = false; break;
				case sur: if(contador[current_state.fil+1][current_state.col+1] > 20) avanzar = false; break;
				case este: if(contador[current_state.fil-1][current_state.col+1] > 20) avanzar = false; break;
				case oeste: if(contador[current_state.fil+1][current_state.col-1] > 20) avanzar = false; break;
				case noreste: if(contador[current_state.fil-1][current_state.col] > 20) avanzar = false; break;
				case noroeste: if(contador[current_state.fil][current_state.col-1] > 20) avanzar = false; break;
				case sureste: if(contador[current_state.fil][current_state.col+1] > 20) avanzar = false; break;
				case suroeste: if(contador[current_state.fil+1][current_state.col] > 20) avanzar = false; break;
			}
		} else if(terreno == 2){

			switch(current_state.brujula){

				case norte: if(contador[current_state.fil-1][current_state.col] > 20) avanzar = false; break;
				case sur: if(contador[current_state.fil+1][current_state.col] > 20) avanzar = false; break;
				case este: if(contador[current_state.fil][current_state.col+1] > 20) avanzar = false; break;
				case oeste: if(contador[current_state.fil][current_state.col-1] > 20) avanzar = false; break;
				case noreste: if(contador[current_state.fil-1][current_state.col+1] > 20) avanzar = false; break;
				case noroeste: if(contador[current_state.fil-1][current_state.col-1] > 20) avanzar = false; break;
				case sureste: if(contador[current_state.fil+1][current_state.col+1] > 20) avanzar = false; break;
				case suroeste: if(contador[current_state.fil+1][current_state.col-1] > 20) avanzar = false; break;
			}

		} else if(terreno == 3){
			
			switch(current_state.brujula){

				case norte: if(contador[current_state.fil-1][current_state.col+1] > 20) avanzar = false; break;
				case sur: if(contador[current_state.fil+1][current_state.col-1] > 20) avanzar = false; break;
				case este: if(contador[current_state.fil+1][current_state.col+1] > 20) avanzar = false; break;
				case oeste: if(contador[current_state.fil-1][current_state.col-1] > 20) avanzar = false; break;
				case noreste: if(contador[current_state.fil][current_state.col+1] > 20) avanzar = false; break;
				case noroeste: if(contador[current_state.fil-1][current_state.col] > 20) avanzar = false; break;
				case sureste: if(contador[current_state.fil+1][current_state.col] > 20) avanzar = false; break;
				case suroeste: if(contador[current_state.fil][current_state.col-1] > 20) avanzar = false; break;
			}
		}

	} else {

		if(terreno == 1){
			switch(current_state.brujula){

				case norte: if(contador2[current_state.fil-1][current_state.col-1] > 20) avanzar = false; break;
				case sur: if(contador2[current_state.fil+1][current_state.col+1] > 20) avanzar = false; break;
				case este: if(contador2[current_state.fil-1][current_state.col+1] > 20) avanzar = false; break;
				case oeste: if(contador2[current_state.fil+1][current_state.col-1] > 20) avanzar = false; break;
				case noreste: if(contador2[current_state.fil-1][current_state.col] > 20) avanzar = false; break;
				case noroeste: if(contador2[current_state.fil][current_state.col-1] > 20) avanzar = false; break;
				case sureste: if(contador2[current_state.fil][current_state.col+1] > 20) avanzar = false; break;
				case suroeste: if(contador2[current_state.fil+1][current_state.col] > 20) avanzar = false; break;
				
			}
		} else if(terreno == 2){

			switch(current_state.brujula){

				case norte: if(contador2[current_state.fil-1][current_state.col] > 20) avanzar = false; break;
				case sur: if(contador2[current_state.fil+1][current_state.col] > 20) avanzar = false; break;
				case este: if(contador2[current_state.fil][current_state.col+1] > 20) avanzar = false; break;
				case oeste: if(contador2[current_state.fil][current_state.col-1] > 20) avanzar = false; break;
				case noreste: if(contador2[current_state.fil-1][current_state.col+1] > 20) avanzar = false; break;
				case noroeste: if(contador2[current_state.fil-1][current_state.col-1] > 20) avanzar = false; break;
				case sureste: if(contador2[current_state.fil+1][current_state.col+1] > 20) avanzar = false; break;
				case suroeste: if(contador2[current_state.fil+1][current_state.col-1] > 20) avanzar = false; break;
			}

		} else if(terreno == 3){
			
			switch(current_state.brujula){

				case norte: if(contador2[current_state.fil-1][current_state.col+1] > 20) avanzar = false; break;
				case sur: if(contador2[current_state.fil+1][current_state.col-1] > 20) avanzar = false; break;
				case este: if(contador2[current_state.fil+1][current_state.col+1] > 20) avanzar = false; break;
				case oeste: if(contador2[current_state.fil-1][current_state.col-1] > 20) avanzar = false; break;
				case noreste: if(contador2[current_state.fil][current_state.col+1] > 20) avanzar = false; break;
				case noroeste: if(contador2[current_state.fil-1][current_state.col] > 20) avanzar = false; break;
				case sureste: if(contador2[current_state.fil+1][current_state.col] > 20) avanzar = false; break;
				case suroeste: if(contador2[current_state.fil][current_state.col-1] > 20) avanzar = false; break;
			}
		}

	}
	return avanzar;
}

void ComportamientoJugador::PintarVista(Sensores & sensores){

	if(bien_situado){
		switch(current_state.brujula){

			case norte:
				mapaResultado[current_state.fil][current_state.col] = sensores.terreno[0];
				mapaResultado[current_state.fil - 1][current_state.col - 1] = sensores.terreno[1];
				mapaResultado[current_state.fil - 1][current_state.col] = sensores.terreno[2];
				mapaResultado[current_state.fil - 1][current_state.col + 1] = sensores.terreno[3];
				mapaResultado[current_state.fil - 2][current_state.col - 2] = sensores.terreno[4];
				mapaResultado[current_state.fil - 2][current_state.col - 1] = sensores.terreno[5];
				mapaResultado[current_state.fil - 2][current_state.col] = sensores.terreno[6];
				mapaResultado[current_state.fil - 2][current_state.col + 1] = sensores.terreno[7];
				mapaResultado[current_state.fil - 2][current_state.col + 2] = sensores.terreno[8];
				mapaResultado[current_state.fil - 3][current_state.col - 3] = sensores.terreno[9];
				mapaResultado[current_state.fil - 3][current_state.col - 2] = sensores.terreno[10];
				mapaResultado[current_state.fil - 3][current_state.col - 1] = sensores.terreno[11];
				mapaResultado[current_state.fil - 3][current_state.col] = sensores.terreno[12];
				mapaResultado[current_state.fil - 3][current_state.col + 1] = sensores.terreno[13];
				mapaResultado[current_state.fil - 3][current_state.col + 2] = sensores.terreno[14];
				mapaResultado[current_state.fil - 3][current_state.col + 3] = sensores.terreno[15];
				break;
			case este:
				mapaResultado[current_state.fil][current_state.col] = sensores.terreno[0];
				mapaResultado[current_state.fil - 1][current_state.col + 1] = sensores.terreno[1];
				mapaResultado[current_state.fil][current_state.col + 1] = sensores.terreno[2];
				mapaResultado[current_state.fil + 1][current_state.col + 1] = sensores.terreno[3];
				mapaResultado[current_state.fil - 2][current_state.col + 2] = sensores.terreno[4];
				mapaResultado[current_state.fil - 1][current_state.col + 2] = sensores.terreno[5];
				mapaResultado[current_state.fil][current_state.col + 2] = sensores.terreno[6];
				mapaResultado[current_state.fil + 1][current_state.col + 2] = sensores.terreno[7];
				mapaResultado[current_state.fil + 2][current_state.col + 2] = sensores.terreno[8];
				mapaResultado[current_state.fil - 3][current_state.col + 3] = sensores.terreno[9];
				mapaResultado[current_state.fil - 2][current_state.col + 3] = sensores.terreno[10];
				mapaResultado[current_state.fil - 1][current_state.col + 3] = sensores.terreno[11];
				mapaResultado[current_state.fil][current_state.col + 3] = sensores.terreno[12];
				mapaResultado[current_state.fil + 1][current_state.col + 3] = sensores.terreno[13];
				mapaResultado[current_state.fil + 2][current_state.col + 3] = sensores.terreno[14];
				mapaResultado[current_state.fil + 3][current_state.col + 3] = sensores.terreno[15];
				break;
			case sur:
				mapaResultado[current_state.fil][current_state.col] = sensores.terreno[0];
				mapaResultado[current_state.fil + 1][current_state.col + 1] = sensores.terreno[1];
				mapaResultado[current_state.fil + 1][current_state.col] = sensores.terreno[2];
				mapaResultado[current_state.fil + 1][current_state.col - 1] = sensores.terreno[3];
				mapaResultado[current_state.fil + 2][current_state.col + 2] = sensores.terreno[4];
				mapaResultado[current_state.fil + 2][current_state.col + 1] = sensores.terreno[5];
				mapaResultado[current_state.fil + 2][current_state.col] = sensores.terreno[6];
				mapaResultado[current_state.fil + 2][current_state.col - 1] = sensores.terreno[7];
				mapaResultado[current_state.fil + 2][current_state.col - 2] = sensores.terreno[8];
				mapaResultado[current_state.fil + 3][current_state.col + 3] = sensores.terreno[9];
				mapaResultado[current_state.fil + 3][current_state.col + 2] = sensores.terreno[10];
				mapaResultado[current_state.fil + 3][current_state.col + 1] = sensores.terreno[11];
				mapaResultado[current_state.fil + 3][current_state.col] = sensores.terreno[12];
				mapaResultado[current_state.fil + 3][current_state.col - 1] = sensores.terreno[13];
				mapaResultado[current_state.fil + 3][current_state.col - 2] = sensores.terreno[14];
				mapaResultado[current_state.fil + 3][current_state.col - 3] = sensores.terreno[15];
				break;
			case oeste:
				mapaResultado[current_state.fil][current_state.col] = sensores.terreno[0];
				mapaResultado[current_state.fil + 1][current_state.col - 1] = sensores.terreno[1];
				mapaResultado[current_state.fil][current_state.col - 1] = sensores.terreno[2];
				mapaResultado[current_state.fil - 1][current_state.col - 1] = sensores.terreno[3];
				mapaResultado[current_state.fil + 2][current_state.col - 2] = sensores.terreno[4];
				mapaResultado[current_state.fil + 1][current_state.col - 2] = sensores.terreno[5];
				mapaResultado[current_state.fil][current_state.col - 2] = sensores.terreno[6];
				mapaResultado[current_state.fil - 1][current_state.col - 2] = sensores.terreno[7];
				mapaResultado[current_state.fil - 2][current_state.col - 2] = sensores.terreno[8];
				mapaResultado[current_state.fil + 3][current_state.col - 3] = sensores.terreno[9];
				mapaResultado[current_state.fil + 2][current_state.col - 3] = sensores.terreno[10];
				mapaResultado[current_state.fil + 1][current_state.col - 3] = sensores.terreno[11];
				mapaResultado[current_state.fil][current_state.col - 3] = sensores.terreno[12];
				mapaResultado[current_state.fil - 1][current_state.col - 3] = sensores.terreno[13];
				mapaResultado[current_state.fil - 2][current_state.col - 3] = sensores.terreno[14];
				mapaResultado[current_state.fil - 3][current_state.col - 3] = sensores.terreno[15];
				break;
			case noreste:
				mapaResultado[current_state.fil][current_state.col] = sensores.terreno[0];
				mapaResultado[current_state.fil - 1][current_state.col] = sensores.terreno[1];
				mapaResultado[current_state.fil - 1][current_state.col + 1] = sensores.terreno[2];
				mapaResultado[current_state.fil][current_state.col + 1] = sensores.terreno[3];
				mapaResultado[current_state.fil - 2][current_state.col] = sensores.terreno[4];
				mapaResultado[current_state.fil - 2][current_state.col + 1] = sensores.terreno[5];
				mapaResultado[current_state.fil - 2][current_state.col + 2] = sensores.terreno[6];
				mapaResultado[current_state.fil - 1][current_state.col + 2] = sensores.terreno[7];
				mapaResultado[current_state.fil][current_state.col + 2] = sensores.terreno[8];
				mapaResultado[current_state.fil - 3][current_state.col] = sensores.terreno[9];
				mapaResultado[current_state.fil - 3][current_state.col + 1] = sensores.terreno[10];
				mapaResultado[current_state.fil - 3][current_state.col + 2] = sensores.terreno[11];
				mapaResultado[current_state.fil - 3][current_state.col + 3] = sensores.terreno[12];
				mapaResultado[current_state.fil - 2][current_state.col + 3] = sensores.terreno[13];
				mapaResultado[current_state.fil - 1][current_state.col + 3] = sensores.terreno[14];
				mapaResultado[current_state.fil][current_state.col + 3] = sensores.terreno[15];
				break;
			case sureste:
				mapaResultado[current_state.fil][current_state.col] = sensores.terreno[0];
				mapaResultado[current_state.fil][current_state.col + 1] = sensores.terreno[1];
				mapaResultado[current_state.fil + 1][current_state.col + 1] = sensores.terreno[2];
				mapaResultado[current_state.fil + 1][current_state.col] = sensores.terreno[3];
				mapaResultado[current_state.fil][current_state.col + 2] = sensores.terreno[4];
				mapaResultado[current_state.fil + 1][current_state.col + 2] = sensores.terreno[5];
				mapaResultado[current_state.fil + 2][current_state.col + 2] = sensores.terreno[6];
				mapaResultado[current_state.fil + 2][current_state.col + 1] = sensores.terreno[7];
				mapaResultado[current_state.fil + 2][current_state.col] = sensores.terreno[8];
				mapaResultado[current_state.fil][current_state.col + 3] = sensores.terreno[9];
				mapaResultado[current_state.fil + 1][current_state.col + 3] = sensores.terreno[10];
				mapaResultado[current_state.fil + 2][current_state.col + 3] = sensores.terreno[11];
				mapaResultado[current_state.fil + 3][current_state.col + 3] = sensores.terreno[12];
				mapaResultado[current_state.fil + 3][current_state.col + 2] = sensores.terreno[13];
				mapaResultado[current_state.fil + 3][current_state.col + 1] = sensores.terreno[14];
				mapaResultado[current_state.fil + 3][current_state.col] = sensores.terreno[15];
				break;
			case noroeste:
				mapaResultado[current_state.fil][current_state.col] = sensores.terreno[0];
				mapaResultado[current_state.fil][current_state.col - 1] = sensores.terreno[1];
				mapaResultado[current_state.fil - 1][current_state.col - 1] = sensores.terreno[2];
				mapaResultado[current_state.fil -1][current_state.col] = sensores.terreno[3];
				mapaResultado[current_state.fil][current_state.col - 2] = sensores.terreno[4];
				mapaResultado[current_state.fil - 1][current_state.col - 2] = sensores.terreno[5];
				mapaResultado[current_state.fil - 2][current_state.col - 2] = sensores.terreno[6];
				mapaResultado[current_state.fil - 2][current_state.col - 1] = sensores.terreno[7];
				mapaResultado[current_state.fil - 2][current_state.col] = sensores.terreno[8];
				mapaResultado[current_state.fil][current_state.col - 3] = sensores.terreno[9];
				mapaResultado[current_state.fil - 1][current_state.col - 3] = sensores.terreno[10];
				mapaResultado[current_state.fil - 2][current_state.col - 3] = sensores.terreno[11];
				mapaResultado[current_state.fil - 3][current_state.col - 3] = sensores.terreno[12];
				mapaResultado[current_state.fil - 3][current_state.col - 2] = sensores.terreno[13];
				mapaResultado[current_state.fil - 3][current_state.col - 1] = sensores.terreno[14];
				mapaResultado[current_state.fil - 3][current_state.col] = sensores.terreno[15];
				break;
			case suroeste:
				mapaResultado[current_state.fil][current_state.col] = sensores.terreno[0];
				mapaResultado[current_state.fil + 1][current_state.col] = sensores.terreno[1];
				mapaResultado[current_state.fil + 1][current_state.col - 1] = sensores.terreno[2];
				mapaResultado[current_state.fil][current_state.col - 1] = sensores.terreno[3];
				mapaResultado[current_state.fil + 2][current_state.col] = sensores.terreno[4];
				mapaResultado[current_state.fil + 2][current_state.col - 1] = sensores.terreno[5];
				mapaResultado[current_state.fil + 2][current_state.col - 2] = sensores.terreno[6];
				mapaResultado[current_state.fil + 1][current_state.col - 2] = sensores.terreno[7];
				mapaResultado[current_state.fil][current_state.col - 2] = sensores.terreno[8];
				mapaResultado[current_state.fil + 3][current_state.col] = sensores.terreno[9];
				mapaResultado[current_state.fil + 3][current_state.col - 1] = sensores.terreno[10];
				mapaResultado[current_state.fil + 3][current_state.col - 2] = sensores.terreno[11];
				mapaResultado[current_state.fil + 3][current_state.col - 3] = sensores.terreno[12];
				mapaResultado[current_state.fil + 2][current_state.col - 3] = sensores.terreno[13];
				mapaResultado[current_state.fil + 1][current_state.col - 3] = sensores.terreno[14];
				mapaResultado[current_state.fil][current_state.col - 3] = sensores.terreno[15];
				break;
		}
	} else {

		switch(current_state.brujula){

			case norte:
				mapaResultado2[current_state.fil][current_state.col] = sensores.terreno[0];
				mapaResultado2[current_state.fil - 1][current_state.col - 1] = sensores.terreno[1];
				mapaResultado2[current_state.fil - 1][current_state.col] = sensores.terreno[2];
				mapaResultado2[current_state.fil - 1][current_state.col + 1] = sensores.terreno[3];
				mapaResultado2[current_state.fil - 2][current_state.col - 2] = sensores.terreno[4];
				mapaResultado2[current_state.fil - 2][current_state.col - 1] = sensores.terreno[5];
				mapaResultado2[current_state.fil - 2][current_state.col] = sensores.terreno[6];
				mapaResultado2[current_state.fil - 2][current_state.col + 1] = sensores.terreno[7];
				mapaResultado2[current_state.fil - 2][current_state.col + 2] = sensores.terreno[8];
				mapaResultado2[current_state.fil - 3][current_state.col - 3] = sensores.terreno[9];
				mapaResultado2[current_state.fil - 3][current_state.col - 2] = sensores.terreno[10];
				mapaResultado2[current_state.fil - 3][current_state.col - 1] = sensores.terreno[11];
				mapaResultado2[current_state.fil - 3][current_state.col] = sensores.terreno[12];
				mapaResultado2[current_state.fil - 3][current_state.col + 1] = sensores.terreno[13];
				mapaResultado2[current_state.fil - 3][current_state.col + 2] = sensores.terreno[14];
				mapaResultado2[current_state.fil - 3][current_state.col + 3] = sensores.terreno[15];
				break;
			case este:
				mapaResultado2[current_state.fil][current_state.col] = sensores.terreno[0];
				mapaResultado2[current_state.fil - 1][current_state.col + 1] = sensores.terreno[1];
				mapaResultado2[current_state.fil][current_state.col + 1] = sensores.terreno[2];
				mapaResultado2[current_state.fil + 1][current_state.col + 1] = sensores.terreno[3];
				mapaResultado2[current_state.fil - 2][current_state.col + 2] = sensores.terreno[4];
				mapaResultado2[current_state.fil - 1][current_state.col + 2] = sensores.terreno[5];
				mapaResultado2[current_state.fil][current_state.col + 2] = sensores.terreno[6];
				mapaResultado2[current_state.fil + 1][current_state.col + 2] = sensores.terreno[7];
				mapaResultado2[current_state.fil + 2][current_state.col + 2] = sensores.terreno[8];
				mapaResultado2[current_state.fil - 3][current_state.col + 3] = sensores.terreno[9];
				mapaResultado2[current_state.fil - 2][current_state.col + 3] = sensores.terreno[10];
				mapaResultado2[current_state.fil - 1][current_state.col + 3] = sensores.terreno[11];
				mapaResultado2[current_state.fil][current_state.col + 3] = sensores.terreno[12];
				mapaResultado2[current_state.fil + 1][current_state.col + 3] = sensores.terreno[13];
				mapaResultado2[current_state.fil + 2][current_state.col + 3] = sensores.terreno[14];
				mapaResultado2[current_state.fil + 3][current_state.col + 3] = sensores.terreno[15];
				break;
			case sur:
				mapaResultado2[current_state.fil][current_state.col] = sensores.terreno[0];
				mapaResultado2[current_state.fil + 1][current_state.col + 1] = sensores.terreno[1];
				mapaResultado2[current_state.fil + 1][current_state.col] = sensores.terreno[2];
				mapaResultado2[current_state.fil + 1][current_state.col - 1] = sensores.terreno[3];
				mapaResultado2[current_state.fil + 2][current_state.col + 2] = sensores.terreno[4];
				mapaResultado2[current_state.fil + 2][current_state.col + 1] = sensores.terreno[5];
				mapaResultado2[current_state.fil + 2][current_state.col] = sensores.terreno[6];
				mapaResultado2[current_state.fil + 2][current_state.col - 1] = sensores.terreno[7];
				mapaResultado2[current_state.fil + 2][current_state.col - 2] = sensores.terreno[8];
				mapaResultado2[current_state.fil + 3][current_state.col + 3] = sensores.terreno[9];
				mapaResultado2[current_state.fil + 3][current_state.col + 2] = sensores.terreno[10];
				mapaResultado2[current_state.fil + 3][current_state.col + 1] = sensores.terreno[11];
				mapaResultado2[current_state.fil + 3][current_state.col] = sensores.terreno[12];
				mapaResultado2[current_state.fil + 3][current_state.col - 1] = sensores.terreno[13];
				mapaResultado2[current_state.fil + 3][current_state.col - 2] = sensores.terreno[14];
				mapaResultado2[current_state.fil + 3][current_state.col - 3] = sensores.terreno[15];
				break;
			case oeste:
				mapaResultado2[current_state.fil][current_state.col] = sensores.terreno[0];
				mapaResultado2[current_state.fil + 1][current_state.col - 1] = sensores.terreno[1];
				mapaResultado2[current_state.fil][current_state.col - 1] = sensores.terreno[2];
				mapaResultado2[current_state.fil - 1][current_state.col - 1] = sensores.terreno[3];
				mapaResultado2[current_state.fil + 2][current_state.col - 2] = sensores.terreno[4];
				mapaResultado2[current_state.fil + 1][current_state.col - 2] = sensores.terreno[5];
				mapaResultado2[current_state.fil][current_state.col - 2] = sensores.terreno[6];
				mapaResultado2[current_state.fil - 1][current_state.col - 2] = sensores.terreno[7];
				mapaResultado2[current_state.fil - 2][current_state.col - 2] = sensores.terreno[8];
				mapaResultado2[current_state.fil + 3][current_state.col - 3] = sensores.terreno[9];
				mapaResultado2[current_state.fil + 2][current_state.col - 3] = sensores.terreno[10];
				mapaResultado2[current_state.fil + 1][current_state.col - 3] = sensores.terreno[11];
				mapaResultado2[current_state.fil][current_state.col - 3] = sensores.terreno[12];
				mapaResultado2[current_state.fil - 1][current_state.col - 3] = sensores.terreno[13];
				mapaResultado2[current_state.fil - 2][current_state.col - 3] = sensores.terreno[14];
				mapaResultado2[current_state.fil - 3][current_state.col - 3] = sensores.terreno[15];
				break;
			case noreste:
				mapaResultado2[current_state.fil][current_state.col] = sensores.terreno[0];
				mapaResultado2[current_state.fil - 1][current_state.col] = sensores.terreno[1];
				mapaResultado2[current_state.fil - 1][current_state.col + 1] = sensores.terreno[2];
				mapaResultado2[current_state.fil][current_state.col + 1] = sensores.terreno[3];
				mapaResultado2[current_state.fil - 2][current_state.col] = sensores.terreno[4];
				mapaResultado2[current_state.fil - 2][current_state.col + 1] = sensores.terreno[5];
				mapaResultado2[current_state.fil - 2][current_state.col + 2] = sensores.terreno[6];
				mapaResultado2[current_state.fil - 1][current_state.col + 2] = sensores.terreno[7];
				mapaResultado2[current_state.fil][current_state.col + 2] = sensores.terreno[8];
				mapaResultado2[current_state.fil - 3][current_state.col] = sensores.terreno[9];
				mapaResultado2[current_state.fil - 3][current_state.col + 1] = sensores.terreno[10];
				mapaResultado2[current_state.fil - 3][current_state.col + 2] = sensores.terreno[11];
				mapaResultado2[current_state.fil - 3][current_state.col + 3] = sensores.terreno[12];
				mapaResultado2[current_state.fil - 2][current_state.col + 3] = sensores.terreno[13];
				mapaResultado2[current_state.fil - 1][current_state.col + 3] = sensores.terreno[14];
				mapaResultado2[current_state.fil][current_state.col + 3] = sensores.terreno[15];
				break;
			case sureste:
				mapaResultado2[current_state.fil][current_state.col] = sensores.terreno[0];
				mapaResultado2[current_state.fil][current_state.col + 1] = sensores.terreno[1];
				mapaResultado2[current_state.fil + 1][current_state.col + 1] = sensores.terreno[2];
				mapaResultado2[current_state.fil + 1][current_state.col] = sensores.terreno[3];
				mapaResultado2[current_state.fil][current_state.col + 2] = sensores.terreno[4];
				mapaResultado2[current_state.fil + 1][current_state.col + 2] = sensores.terreno[5];
				mapaResultado2[current_state.fil + 2][current_state.col + 2] = sensores.terreno[6];
				mapaResultado2[current_state.fil + 2][current_state.col + 1] = sensores.terreno[7];
				mapaResultado2[current_state.fil + 2][current_state.col] = sensores.terreno[8];
				mapaResultado2[current_state.fil][current_state.col + 3] = sensores.terreno[9];
				mapaResultado2[current_state.fil + 1][current_state.col + 3] = sensores.terreno[10];
				mapaResultado2[current_state.fil + 2][current_state.col + 3] = sensores.terreno[11];
				mapaResultado2[current_state.fil + 3][current_state.col + 3] = sensores.terreno[12];
				mapaResultado2[current_state.fil + 3][current_state.col + 2] = sensores.terreno[13];
				mapaResultado2[current_state.fil + 3][current_state.col + 1] = sensores.terreno[14];
				mapaResultado2[current_state.fil + 3][current_state.col] = sensores.terreno[15];
				break;
			case noroeste:
				mapaResultado2[current_state.fil][current_state.col] = sensores.terreno[0];
				mapaResultado2[current_state.fil][current_state.col - 1] = sensores.terreno[1];
				mapaResultado2[current_state.fil - 1][current_state.col - 1] = sensores.terreno[2];
				mapaResultado2[current_state.fil -1][current_state.col] = sensores.terreno[3];
				mapaResultado2[current_state.fil][current_state.col - 2] = sensores.terreno[4];
				mapaResultado2[current_state.fil - 1][current_state.col - 2] = sensores.terreno[5];
				mapaResultado2[current_state.fil - 2][current_state.col - 2] = sensores.terreno[6];
				mapaResultado2[current_state.fil - 2][current_state.col - 1] = sensores.terreno[7];
				mapaResultado2[current_state.fil - 2][current_state.col] = sensores.terreno[8];
				mapaResultado2[current_state.fil][current_state.col - 3] = sensores.terreno[9];
				mapaResultado2[current_state.fil - 1][current_state.col - 3] = sensores.terreno[10];
				mapaResultado2[current_state.fil - 2][current_state.col - 3] = sensores.terreno[11];
				mapaResultado2[current_state.fil - 3][current_state.col - 3] = sensores.terreno[12];
				mapaResultado2[current_state.fil - 3][current_state.col - 2] = sensores.terreno[13];
				mapaResultado2[current_state.fil - 3][current_state.col - 1] = sensores.terreno[14];
				mapaResultado2[current_state.fil - 3][current_state.col] = sensores.terreno[15];
				break;
			case suroeste:
				mapaResultado2[current_state.fil][current_state.col] = sensores.terreno[0];
				mapaResultado2[current_state.fil + 1][current_state.col] = sensores.terreno[1];
				mapaResultado2[current_state.fil + 1][current_state.col - 1] = sensores.terreno[2];
				mapaResultado2[current_state.fil][current_state.col - 1] = sensores.terreno[3];
				mapaResultado2[current_state.fil + 2][current_state.col] = sensores.terreno[4];
				mapaResultado2[current_state.fil + 2][current_state.col - 1] = sensores.terreno[5];
				mapaResultado2[current_state.fil + 2][current_state.col - 2] = sensores.terreno[6];
				mapaResultado2[current_state.fil + 1][current_state.col - 2] = sensores.terreno[7];
				mapaResultado2[current_state.fil][current_state.col - 2] = sensores.terreno[8];
				mapaResultado2[current_state.fil + 3][current_state.col] = sensores.terreno[9];
				mapaResultado2[current_state.fil + 3][current_state.col - 1] = sensores.terreno[10];
				mapaResultado2[current_state.fil + 3][current_state.col - 2] = sensores.terreno[11];
				mapaResultado2[current_state.fil + 3][current_state.col - 3] = sensores.terreno[12];
				mapaResultado2[current_state.fil + 2][current_state.col - 3] = sensores.terreno[13];
				mapaResultado2[current_state.fil + 1][current_state.col - 3] = sensores.terreno[14];
				mapaResultado2[current_state.fil][current_state.col - 3] = sensores.terreno[15];
				break;
		}
	}
}

void ComportamientoJugador::ActualizarContador(){

	if(bien_situado){
		switch(current_state.brujula){

			case norte:
				contador[current_state.fil][current_state.col]+=5;
				contador[current_state.fil - 1][current_state.col - 1]++;
				contador[current_state.fil - 1][current_state.col]++;
				contador[current_state.fil - 1][current_state.col + 1]++;
				contador[current_state.fil - 2][current_state.col - 2]++;
				contador[current_state.fil - 2][current_state.col - 1]++;
				contador[current_state.fil - 2][current_state.col]++;
				contador[current_state.fil - 2][current_state.col + 1]++;
				contador[current_state.fil - 2][current_state.col + 2]++;
				contador[current_state.fil - 3][current_state.col - 3]++;
				contador[current_state.fil - 3][current_state.col - 2]++;
				contador[current_state.fil - 3][current_state.col - 1]++;
				contador[current_state.fil - 3][current_state.col]++;
				contador[current_state.fil - 3][current_state.col + 1]++;
				contador[current_state.fil - 3][current_state.col + 2]++;
				contador[current_state.fil - 3][current_state.col + 3]++;
				break;
			case este:
				contador[current_state.fil][current_state.col]+=5;
				contador[current_state.fil - 1][current_state.col + 1]++;
				contador[current_state.fil][current_state.col + 1]++;
				contador[current_state.fil + 1][current_state.col + 1]++;
				contador[current_state.fil - 2][current_state.col + 2]++;
				contador[current_state.fil - 1][current_state.col + 2]++;
				contador[current_state.fil][current_state.col + 2]++;
				contador[current_state.fil + 1][current_state.col + 2]++;
				contador[current_state.fil + 2][current_state.col + 2]++;
				contador[current_state.fil - 3][current_state.col + 3]++;
				contador[current_state.fil - 2][current_state.col + 3]++;
				contador[current_state.fil - 1][current_state.col + 3]++;
				contador[current_state.fil][current_state.col + 3]++;
				contador[current_state.fil + 1][current_state.col + 3]++;
				contador[current_state.fil + 2][current_state.col + 3]++;
				contador[current_state.fil + 3][current_state.col + 3]++;
				break;
			case sur:
				contador[current_state.fil][current_state.col]+=5;
				contador[current_state.fil + 1][current_state.col + 1]++;
				contador[current_state.fil + 1][current_state.col]++;
				contador[current_state.fil + 1][current_state.col - 1]++;
				contador[current_state.fil + 2][current_state.col + 2]++;
				contador[current_state.fil + 2][current_state.col + 1]++;
				contador[current_state.fil + 2][current_state.col]++;
				contador[current_state.fil + 2][current_state.col - 1]++;
				contador[current_state.fil + 2][current_state.col - 2]++;
				contador[current_state.fil + 3][current_state.col + 3]++;
				contador[current_state.fil + 3][current_state.col + 2]++;
				contador[current_state.fil + 3][current_state.col + 1]++;
				contador[current_state.fil + 3][current_state.col]++;
				contador[current_state.fil + 3][current_state.col - 1]++;
				contador[current_state.fil + 3][current_state.col - 2]++;
				contador[current_state.fil + 3][current_state.col - 3]++;
				break;
			case oeste:
				contador[current_state.fil][current_state.col]+=5;
				contador[current_state.fil + 1][current_state.col - 1]++;
				contador[current_state.fil][current_state.col - 1]++;
				contador[current_state.fil - 1][current_state.col - 1]++;
				contador[current_state.fil + 2][current_state.col - 2]++;
				contador[current_state.fil + 1][current_state.col - 2]++;
				contador[current_state.fil][current_state.col - 2]++;
				contador[current_state.fil - 1][current_state.col - 2]++;
				contador[current_state.fil - 2][current_state.col - 2]++;
				contador[current_state.fil + 3][current_state.col - 3]++;
				contador[current_state.fil + 2][current_state.col - 3]++;
				contador[current_state.fil + 1][current_state.col - 3]++;
				contador[current_state.fil][current_state.col - 3]++;
				contador[current_state.fil - 1][current_state.col - 3]++;
				contador[current_state.fil - 2][current_state.col - 3]++;
				contador[current_state.fil - 3][current_state.col - 3]++;
				break;
			case noreste:
				contador[current_state.fil][current_state.col]+=5;
				contador[current_state.fil - 1][current_state.col]++;
				contador[current_state.fil - 1][current_state.col + 1]++;
				contador[current_state.fil][current_state.col + 1]++;
				contador[current_state.fil - 2][current_state.col]++;
				contador[current_state.fil - 2][current_state.col + 1]++;
				contador[current_state.fil - 2][current_state.col + 2]++;
				contador[current_state.fil - 1][current_state.col + 2]++;
				contador[current_state.fil][current_state.col + 2]++;
				contador[current_state.fil - 3][current_state.col]++;
				contador[current_state.fil - 3][current_state.col + 1]++;
				contador[current_state.fil - 3][current_state.col + 2]++;
				contador[current_state.fil - 3][current_state.col + 3]++;
				contador[current_state.fil - 2][current_state.col + 3]++;
				contador[current_state.fil - 1][current_state.col + 3]++;
				contador[current_state.fil][current_state.col + 3]++;
				break;
			case sureste:
				contador[current_state.fil][current_state.col]+=5;
				contador[current_state.fil][current_state.col + 1]++;
				contador[current_state.fil + 1][current_state.col + 1]++;
				contador[current_state.fil + 1][current_state.col]++;
				contador[current_state.fil][current_state.col + 2]++;
				contador[current_state.fil + 1][current_state.col + 2]++;
				contador[current_state.fil + 2][current_state.col + 2]++;
				contador[current_state.fil + 2][current_state.col + 1]++;
				contador[current_state.fil + 2][current_state.col]++;
				contador[current_state.fil][current_state.col + 3]++;
				contador[current_state.fil + 1][current_state.col + 3]++;
				contador[current_state.fil + 2][current_state.col + 3]++;
				contador[current_state.fil + 3][current_state.col + 3]++;
				contador[current_state.fil + 3][current_state.col + 2]++;
				contador[current_state.fil + 3][current_state.col + 1]++;
				contador[current_state.fil + 3][current_state.col]++;
				break;
			case noroeste:
				contador[current_state.fil][current_state.col]+=5;
				contador[current_state.fil][current_state.col - 1]++;
				contador[current_state.fil - 1][current_state.col - 1]++;
				contador[current_state.fil -1][current_state.col]++;
				contador[current_state.fil][current_state.col - 2]++;
				contador[current_state.fil - 1][current_state.col - 2]++;
				contador[current_state.fil - 2][current_state.col - 2]++;
				contador[current_state.fil - 2][current_state.col - 1]++;
				contador[current_state.fil - 2][current_state.col]++;
				contador[current_state.fil][current_state.col - 3]++;
				contador[current_state.fil - 1][current_state.col - 3]++;
				contador[current_state.fil - 2][current_state.col - 3]++;
				contador[current_state.fil - 3][current_state.col - 3]++;
				contador[current_state.fil - 3][current_state.col - 2]++;
				contador[current_state.fil - 3][current_state.col - 1]++;
				contador[current_state.fil - 3][current_state.col]++;
				break;
			case suroeste:
				contador[current_state.fil][current_state.col]+=5;
				contador[current_state.fil + 1][current_state.col]++;
				contador[current_state.fil + 1][current_state.col - 1]++;
				contador[current_state.fil][current_state.col - 1]++;
				contador[current_state.fil + 2][current_state.col]++;
				contador[current_state.fil + 2][current_state.col - 1]++;
				contador[current_state.fil + 2][current_state.col - 2]++;
				contador[current_state.fil + 1][current_state.col - 2]++;
				contador[current_state.fil][current_state.col - 2]++;
				contador[current_state.fil + 3][current_state.col]++;
				contador[current_state.fil + 3][current_state.col - 1]++;
				contador[current_state.fil + 3][current_state.col - 2]++;
				contador[current_state.fil + 3][current_state.col - 3]++;
				contador[current_state.fil + 2][current_state.col - 3]++;
				contador[current_state.fil + 1][current_state.col - 3]++;
				contador[current_state.fil][current_state.col - 3]++;
				break;
		}
	} else {

		switch(current_state.brujula){

			case norte:
				contador2[current_state.fil][current_state.col]+=5;
				contador2[current_state.fil - 1][current_state.col - 1]++;
				contador2[current_state.fil - 1][current_state.col]++;
				contador2[current_state.fil - 1][current_state.col + 1]++;
				contador2[current_state.fil - 2][current_state.col - 2]++;
				contador2[current_state.fil - 2][current_state.col - 1]++;
				contador2[current_state.fil - 2][current_state.col]++;
				contador2[current_state.fil - 2][current_state.col + 1]++;
				contador2[current_state.fil - 2][current_state.col + 2]++;
				contador2[current_state.fil - 3][current_state.col - 3]++;
				contador2[current_state.fil - 3][current_state.col - 2]++;
				contador2[current_state.fil - 3][current_state.col - 1]++;
				contador2[current_state.fil - 3][current_state.col]++;
				contador2[current_state.fil - 3][current_state.col + 1]++;
				contador2[current_state.fil - 3][current_state.col + 2]++;
				contador2[current_state.fil - 3][current_state.col + 3]++;
				break;
			case este:
				contador2[current_state.fil][current_state.col]+=5;
				contador2[current_state.fil - 1][current_state.col + 1]++;
				contador2[current_state.fil][current_state.col + 1]++;
				contador2[current_state.fil + 1][current_state.col + 1]++;
				contador2[current_state.fil - 2][current_state.col + 2]++;
				contador2[current_state.fil - 1][current_state.col + 2]++;
				contador2[current_state.fil][current_state.col + 2]++;
				contador2[current_state.fil + 1][current_state.col + 2]++;
				contador2[current_state.fil + 2][current_state.col + 2]++;
				contador2[current_state.fil - 3][current_state.col + 3]++;
				contador2[current_state.fil - 2][current_state.col + 3]++;
				contador2[current_state.fil - 1][current_state.col + 3]++;
				contador2[current_state.fil][current_state.col + 3]++;
				contador2[current_state.fil + 1][current_state.col + 3]++;
				contador2[current_state.fil + 2][current_state.col + 3]++;
				contador2[current_state.fil + 3][current_state.col + 3]++;
				break;
			case sur:
				contador2[current_state.fil][current_state.col]+=5;
				contador2[current_state.fil + 1][current_state.col + 1]++;
				contador2[current_state.fil + 1][current_state.col]++;
				contador2[current_state.fil + 1][current_state.col - 1]++;
				contador2[current_state.fil + 2][current_state.col + 2]++;
				contador2[current_state.fil + 2][current_state.col + 1]++;
				contador2[current_state.fil + 2][current_state.col]++;
				contador2[current_state.fil + 2][current_state.col - 1]++;
				contador2[current_state.fil + 2][current_state.col - 2]++;
				contador2[current_state.fil + 3][current_state.col + 3]++;
				contador2[current_state.fil + 3][current_state.col + 2]++;
				contador2[current_state.fil + 3][current_state.col + 1]++;
				contador2[current_state.fil + 3][current_state.col]++;
				contador2[current_state.fil + 3][current_state.col - 1]++;
				contador2[current_state.fil + 3][current_state.col - 2]++;
				contador2[current_state.fil + 3][current_state.col - 3]++;
				break;
			case oeste:
				contador2[current_state.fil][current_state.col]+=5;
				contador2[current_state.fil + 1][current_state.col - 1]++;
				contador2[current_state.fil][current_state.col - 1]++;
				contador2[current_state.fil - 1][current_state.col - 1]++;
				contador2[current_state.fil + 2][current_state.col - 2]++;
				contador2[current_state.fil + 1][current_state.col - 2]++;
				contador2[current_state.fil][current_state.col - 2]++;
				contador2[current_state.fil - 1][current_state.col - 2]++;
				contador2[current_state.fil - 2][current_state.col - 2]++;
				contador2[current_state.fil + 3][current_state.col - 3]++;
				contador2[current_state.fil + 2][current_state.col - 3]++;
				contador2[current_state.fil + 1][current_state.col - 3]++;
				contador2[current_state.fil][current_state.col - 3]++;
				contador2[current_state.fil - 1][current_state.col - 3]++;
				contador2[current_state.fil - 2][current_state.col - 3]++;
				contador2[current_state.fil - 3][current_state.col - 3]++;
				break;
			case noreste:
				contador2[current_state.fil][current_state.col]+=5;
				contador2[current_state.fil - 1][current_state.col]++;
				contador2[current_state.fil - 1][current_state.col + 1]++;
				contador2[current_state.fil][current_state.col + 1]++;
				contador2[current_state.fil - 2][current_state.col]++;
				contador2[current_state.fil - 2][current_state.col + 1]++;
				contador2[current_state.fil - 2][current_state.col + 2]++;
				contador2[current_state.fil - 1][current_state.col + 2]++;
				contador2[current_state.fil][current_state.col + 2]++;
				contador2[current_state.fil - 3][current_state.col]++;
				contador2[current_state.fil - 3][current_state.col + 1]++;
				contador2[current_state.fil - 3][current_state.col + 2]++;
				contador2[current_state.fil - 3][current_state.col + 3]++;
				contador2[current_state.fil - 2][current_state.col + 3]++;
				contador2[current_state.fil - 1][current_state.col + 3]++;
				contador2[current_state.fil][current_state.col + 3]++;
				break;
			case sureste:
				contador2[current_state.fil][current_state.col]+=5;
				contador2[current_state.fil][current_state.col + 1]++;
				contador2[current_state.fil + 1][current_state.col + 1]++;
				contador2[current_state.fil + 1][current_state.col]++;
				contador2[current_state.fil][current_state.col + 2]++;
				contador2[current_state.fil + 1][current_state.col + 2]++;
				contador2[current_state.fil + 2][current_state.col + 2]++;
				contador2[current_state.fil + 2][current_state.col + 1]++;
				contador2[current_state.fil + 2][current_state.col]++;
				contador2[current_state.fil][current_state.col + 3]++;
				contador2[current_state.fil + 1][current_state.col + 3]++;
				contador2[current_state.fil + 2][current_state.col + 3]++;
				contador2[current_state.fil + 3][current_state.col + 3]++;
				contador2[current_state.fil + 3][current_state.col + 2]++;
				contador2[current_state.fil + 3][current_state.col + 1]++;
				contador2[current_state.fil + 3][current_state.col]++;
				break;
			case noroeste:
				contador2[current_state.fil][current_state.col]+=5;
				contador2[current_state.fil][current_state.col - 1]++;
				contador2[current_state.fil - 1][current_state.col - 1]++;
				contador2[current_state.fil -1][current_state.col]++;
				contador2[current_state.fil][current_state.col - 2]++;
				contador2[current_state.fil - 1][current_state.col - 2]++;
				contador2[current_state.fil - 2][current_state.col - 2]++;
				contador2[current_state.fil - 2][current_state.col - 1]++;
				contador2[current_state.fil - 2][current_state.col]++;
				contador2[current_state.fil][current_state.col - 3]++;
				contador2[current_state.fil - 1][current_state.col - 3]++;
				contador2[current_state.fil - 2][current_state.col - 3]++;
				contador2[current_state.fil - 3][current_state.col - 3]++;
				contador2[current_state.fil - 3][current_state.col - 2]++;
				contador2[current_state.fil - 3][current_state.col - 1]++;
				contador2[current_state.fil - 3][current_state.col]++;
				break;
			case suroeste:
				contador2[current_state.fil][current_state.col]+=5;
				contador2[current_state.fil + 1][current_state.col]++;
				contador2[current_state.fil + 1][current_state.col - 1]++;
				contador2[current_state.fil][current_state.col - 1]++;
				contador2[current_state.fil + 2][current_state.col]++;
				contador2[current_state.fil + 2][current_state.col - 1]++;
				contador2[current_state.fil + 2][current_state.col - 2]++;
				contador2[current_state.fil + 1][current_state.col - 2]++;
				contador2[current_state.fil][current_state.col - 2]++;
				contador2[current_state.fil + 3][current_state.col]++;
				contador2[current_state.fil + 3][current_state.col - 1]++;
				contador2[current_state.fil + 3][current_state.col - 2]++;
				contador2[current_state.fil + 3][current_state.col - 3]++;
				contador2[current_state.fil + 2][current_state.col - 3]++;
				contador2[current_state.fil + 1][current_state.col - 3]++;
				contador2[current_state.fil][current_state.col - 3]++;
				break;
		}
	}
}

void ComportamientoJugador::PrecipiciosIniciales(){

	// Precipicios de las tres primeras filas

		for(int i = 0; i < 3; i++){

			for(int j = 0; j < mapaResultado.size(); j++){
				mapaResultado[i][j] = 'P';
			}
		}

		// Precipicios de las tres últimas filas

		for(int i = mapaResultado.size()-3; i < mapaResultado.size(); i++){

			for(int j = 0; j < mapaResultado.size(); j++){
				mapaResultado[i][j] = 'P';
			}
		}

		// Precipicios de las tres primeras columnas

		for(int j = 0; j < 3; j++){

			for(int i = 0; i < mapaResultado.size(); i++){
				mapaResultado[i][j] = 'P';
			}
		}

		// Precipicios de las tres últimas columnas

		for(int j = mapaResultado.size()-3; j < mapaResultado.size(); j++){

			for(int i = 0; i < mapaResultado.size(); i++){
				mapaResultado[i][j] = 'P';
			}
		}

		precipicios = true;
}

bool ComportamientoJugador::RecargaCerca(Sensores & sensores){

	bool recarga = false;

	for(int i = 1; i < sensores.terreno.size(); i++){

		if(sensores.terreno[i] == 'X')
			recarga = true;
	}

	return recarga;
}

int ComportamientoJugador::NoAguaCerca(Sensores & sensores){

	int resultado = -1;

	for(int i = 1; i < 16; i++){

		if(sensores.terreno[i] != 'A' and sensores.terreno[i] != 'M' and sensores.terreno[i] != 'P'){
			resultado = i;
			break;
		}
	}

	return resultado;
}

int ComportamientoJugador::NoBosqueCerca(Sensores & sensores){

	int resultado = -1;

	for(int i = 1; i < 16; i++){

		if(sensores.terreno[i] != 'B' and sensores.terreno[i] != 'A' and sensores.terreno[i] != 'M' and sensores.terreno[i] != 'P'){
			resultado = i;
			break;
		}
	}

	return resultado;
}

void ComportamientoJugador::IrseARecargar(){

	// Se llama cuando se tiene poca batería (menor o igual de 1500).
	// Solo se llama a este método cuando al menos hay una batería
	// registrada en "recargas".
	// Comenzamos determinando cuál de las recargas registradas es la
	// más cercana.

	// Inicializamos a 5000 las coordenadas para que en caso de estar
	// bien situado, se deshaga de este valor por defecto por estar muy
	// lejos de cualquier posición en la que se encuentre el agente

	pair<int, int> recarga(5000,5000);

	if(bien_situado){

		if(recargas.size() == 1){
			recarga = *(recargas.begin());
		} else {

			int distancia_min = abs(current_state.fil - recarga.first) + abs(current_state.col - recarga.second);

			for (auto it = recargas.begin(); it != recargas.end(); ++it) {
				
				int distancia = abs(current_state.fil - it->first) + abs(current_state.col - it->second);
				if(distancia <= distancia_min){

					distancia_min = distancia;
					recarga = *it;
				}
			}
		}

		// Tras calcular el mínimo, asignamos las frecuencias

		for(int i = 3; i < mapaResultado.size()-3; i++){

			for(int j = 3; j < mapaResultado.size()-3; j++){
				
				// Solo variamos el contador de las casillas ya registradas

				if(mapaResultado[i][j] != '?'){
					
					// Cuanto más lejos está la casilla, menos prioridad tendrá (contador más alto).
					// Así, solo la casilla de recarga tendrá el valor de contador a 0, mientras que
					// el resto mayor que 0

					contador[i][j] = abs(i - recarga.first) + abs(j - recarga.second);
				}
			}
		}
	} else {

		if(recargas2.size() == 1){
			recarga = *(recargas2.begin());
		} else {

			int distancia_min = abs(current_state.fil - recarga.first) + abs(current_state.col - recarga.second);

			for (auto it = recargas2.begin(); it != recargas2.end(); ++it) {
				
				int distancia = abs(current_state.fil - it->first) + abs(current_state.col - it->second);
				if(distancia <= distancia_min){

					distancia_min = distancia;
					recarga = *it;
				}
			}
		}

		for(int i = 3; i < mapaResultado2.size()-3; i++){

			for(int j = 3; j < mapaResultado2.size()-3; j++){
				
				// Solo variamos el contador de las casillas ya registradas

				if(mapaResultado2[i][j] != '?'){
					
					// Cuanto más lejos está la casilla, menos prioridad tendrá (contador más alto)

					contador2[i][j] = abs(i - recarga.first) + abs(j - recarga.second);
				}
			}
		}

	}
}

void ComportamientoJugador::IrseAlObjetivo(){

	if(bien_situado){
		for(int i = 3; i < contador.size()-3; i++){

			for(int j = 3; j < contador.size()-3; j++){
				
				// Solo variamos el contador de las casillas ya registradas

				if(mapaResultado[i][j] != '?'){
					
					// Cuanto más lejos está la casilla, menos prioridad tendrá (contador más alto)

					contador[i][j] = abs(i - objetivo.first) + abs(j - objetivo.second);
				} else if(i == objetivo.first and j == objetivo.second){
					contador[i][j] = 0;
				}
			}
		}
	} else {

		for(int i = 3; i < contador2.size()-3; i++){

			for(int j = 3; j < contador2.size()-3; j++){
				
				// Solo variamos el contador de las casillas ya registradas

				if(mapaResultado2[i][j] != '?'){
					
					// Cuanto más lejos está la casilla, menos prioridad tendrá (contador más alto)

					contador2[i][j] = abs(i - objetivo.first) + abs(j - objetivo.second);
				} else if(i == objetivo.first and j == objetivo.second){
					contador2[i][j] = 0;
				}
			}
		}
	}
}

bool ComportamientoJugador::BikiniCerca(Sensores & sensores){

	bool bikini_cerca = false;

	for(int i = 1; i < sensores.terreno.size(); i++){

		if(sensores.terreno[i] == 'K')
			bikini_cerca = true;
	}

	return bikini_cerca;
}

bool ComportamientoJugador::ZapatillasCerca(Sensores & sensores){

	bool zapatillas_cerca = false;

	for(int i = 1; i < sensores.terreno.size(); i++){

		if(sensores.terreno[i] == 'D')
			zapatillas_cerca = true;
	}

	return zapatillas_cerca;
}

bool ComportamientoJugador::PosicionamientoCerca(Sensores & sensores){

	bool pos_cerca = false;

	for(int i = 1; i < sensores.terreno.size(); i++){

		if(sensores.terreno[i] == 'G')
			pos_cerca = true;
	}

	return pos_cerca;
}

int ComportamientoJugador::CasillaMasPrioritaria(Orientacion o, Sensores & sensores){

	int resultado;
	int minimo;
	vector<int> aux(3);


	// Con la ayuda de contador, obtenemos los valores del número de visitas de las
	// 3 casillas de enfrente. Dependiendo de la orientación, estas casillas serán
	// unas u otras en la matriz contador 

	if(bien_situado){
		switch(o){

			case norte:

				aux[0] = contador[current_state.fil - 1][current_state.col - 1];
				aux[1] = contador[current_state.fil - 1][current_state.col];
				aux[2] = contador[current_state.fil - 1][current_state.col + 1];
				break;
			case este:

				aux[0] = contador[current_state.fil - 1][current_state.col + 1];
				aux[1] = contador[current_state.fil][current_state.col + 1];
				aux[2] = contador[current_state.fil + 1][current_state.col + 1];
				break;
			case oeste:

				aux[0] = contador[current_state.fil + 1][current_state.col - 1];
				aux[1] = contador[current_state.fil][current_state.col - 1];
				aux[2] = contador[current_state.fil - 1][current_state.col - 1];
				break;
			case sur:

				aux[0] = contador[current_state.fil + 1][current_state.col + 1];
				aux[1] = contador[current_state.fil + 1][current_state.col];
				aux[2] = contador[current_state.fil + 1][current_state.col - 1];
				break;
			case noreste:

				aux[0] = contador[current_state.fil - 1][current_state.col];
				aux[1] = contador[current_state.fil - 1][current_state.col + 1];
				aux[2] = contador[current_state.fil][current_state.col + 1];
				break;
			case noroeste:

				aux[0] = contador[current_state.fil][current_state.col - 1];
				aux[1] = contador[current_state.fil - 1][current_state.col - 1];
				aux[2] = contador[current_state.fil - 1][current_state.col];
				break;
			case sureste:

				aux[0] = contador[current_state.fil][current_state.col + 1];
				aux[1] = contador[current_state.fil + 1][current_state.col + 1];
				aux[2] = contador[current_state.fil + 1][current_state.col];
				break;
			case suroeste:

				aux[0] = contador[current_state.fil + 1][current_state.col];
				aux[1] = contador[current_state.fil + 1][current_state.col - 1];
				aux[2] = contador[current_state.fil][current_state.col - 1];
				break;
		}
	} else {

		switch(o){

			case norte:

				aux[0] = contador2[current_state.fil - 1][current_state.col - 1];
				aux[1] = contador2[current_state.fil - 1][current_state.col];
				aux[2] = contador2[current_state.fil - 1][current_state.col + 1];
				break;
			case este:

				aux[0] = contador2[current_state.fil - 1][current_state.col + 1];
				aux[1] = contador2[current_state.fil][current_state.col + 1];
				aux[2] = contador2[current_state.fil + 1][current_state.col + 1];
				break;
			case oeste:

				aux[0] = contador2[current_state.fil + 1][current_state.col - 1];
				aux[1] = contador2[current_state.fil][current_state.col - 1];
				aux[2] = contador2[current_state.fil - 1][current_state.col - 1];
				break;
			case sur:

				aux[0] = contador2[current_state.fil + 1][current_state.col + 1];
				aux[1] = contador2[current_state.fil + 1][current_state.col];
				aux[2] = contador2[current_state.fil + 1][current_state.col - 1];
				break;
			case noreste:

				aux[0] = contador2[current_state.fil - 1][current_state.col];
				aux[1] = contador2[current_state.fil - 1][current_state.col + 1];
				aux[2] = contador2[current_state.fil][current_state.col + 1];
				break;
			case noroeste:

				aux[0] = contador2[current_state.fil][current_state.col - 1];
				aux[1] = contador2[current_state.fil - 1][current_state.col - 1];
				aux[2] = contador2[current_state.fil - 1][current_state.col];
				break;
			case sureste:

				aux[0] = contador2[current_state.fil][current_state.col + 1];
				aux[1] = contador2[current_state.fil + 1][current_state.col + 1];
				aux[2] = contador2[current_state.fil + 1][current_state.col];
				break;
			case suroeste:

				aux[0] = contador2[current_state.fil + 1][current_state.col];
				aux[1] = contador2[current_state.fil + 1][current_state.col - 1];
				aux[2] = contador2[current_state.fil][current_state.col - 1];
				break;
		}
	}

	// Ponemos prioridad muy alta a las casillas que no son accesibles

	for(int i = 1; i < 4; i++){

		if(!PuedeAvanzar(sensores.terreno[i], sensores.bateria))
			aux[i-1] = 5000;
	}

	// Buscamos el mínimo. En caso de tener la misma prioridad, se devuelve la casilla
	// de enfrente para avanzar. De lo contrario, se estaría siempre girando a la derecha
	// en caso de estar rodeado de casillas con la misma prioridad y accesibles

	if((aux[0] == aux[1]) and (aux[1] == aux[2])){
		resultado = 2;
	} else {
		resultado = 1;
		minimo = aux[resultado - 1];

		for(int i = 1; i < 3; i++){

			if(aux[i] < minimo){
				resultado = i + 1;
				minimo = aux[i];
			}
		}
	}
	

	return resultado;
}

void ComportamientoJugador::ComprobarMuros(Sensores & sensores){

	switch(current_state.brujula){

		case norte:
		case sur:
		case este:
		case oeste:

			if(sensores.terreno[2] == 'M'){

				if(muros == 4){
					muros = 7;
				} else {
					muros = 0;
				}
			}

			break;
		case noreste:
		case suroeste:

			if(sensores.terreno[1] == 'M' and sensores.terreno[2] == 'M' and sensores.terreno[3] != 'A' and 
			!(sensores.terreno[3] == 'B' and sensores.bateria < 2500) and sensores.terreno[3] != 'M'){

				muros = 1;
			} else if(sensores.terreno[1] == 'M' and sensores.terreno[2] == 'M' and sensores.terreno[3] == 'M'){

				// Este caso es para tratar las esquinas de un muro por el interior. Giro grande a la derecha y
				// se pasa al estado 2

				muros = 6;
			}

			break;
		case noroeste:
		case sureste:

			if(sensores.terreno[2] == 'M' and sensores.terreno[3] == 'M' and sensores.terreno[1] != 'A' and 
			!(sensores.terreno[1] == 'B' and sensores.bateria < 2500) and sensores.terreno[1] != 'M'){

				muros = 3;
			} else if(sensores.terreno[1] == 'M' and sensores.terreno[2] == 'M' and sensores.terreno[3] == 'M'){

				// Este caso es para tratar las esquinas de un muro por el interior. Giro grande a la derecha y
				// se pasa al estado 2

				muros = 6;
			}

			break;
	}

}

void ComportamientoJugador::GuardarContador(){

	for (int i = 0; i < contador.size(); i++) {
    	for (int j = 0; j < contador.size(); j++) {
    		contador_auxiliar[i][j] = contador[i][j];
    	}
	}
}

void ComportamientoJugador::RecuperarContador(){

	for (int i = 0; i < contador.size(); i++) {
    	for (int j = 0; j < contador.size(); j++) {
        	contador[i][j] = contador_auxiliar[i][j];
    	}
	}
}

void ComportamientoJugador::GuardarContador2(){

	for (int i = 0; i < contador2.size(); i++) {
    	for (int j = 0; j < contador2.size(); j++) {
    		contador_auxiliar2[i][j] = contador2[i][j];
    	}
	}
}

void ComportamientoJugador::RecuperarContador2(){

	for (int i = 0; i < contador2.size(); i++) {
    	for (int j = 0; j < contador2.size(); j++) {
        	contador2[i][j] = contador_auxiliar2[i][j];
    	}
	}
}

void ComportamientoJugador::Traslacion(int f, int c){

	int despx = current_state.fil - f;
	int despy = current_state.col - c;

	for(int i = 3; i < mapaResultado.size() - 3; i++){

		for(int j = 3; j < mapaResultado.size() - 3; j++){
			
			// De no hacer esto, cuando un lobo reinicia al agente y este
			// se vuelve a posicionar, borra algunas de las casillas que
			// ya estaban registradas

			if(mapaResultado[i][j] == '?'){
				mapaResultado[i][j] = mapaResultado2[i + despx][j + despy];
			}

			contador[i][j] = contador2[i + despx][j + despy];
			contador_auxiliar[i][j] = contador_auxiliar2[i + despx][j + despy];
		}
	}

	// Y también calculamos las posiciones reales de las recargas que se hayan 
	// encontrado por el momento, así como del objetivo que se esté buscando
	// en caso de haberlo

	if(recargas2.size() > 0){

		for (auto it = recargas2.begin(); it != recargas2.end(); ++it) {

			recargas.insert(make_pair(it->first - despx, it->second - despy));
    	}
	}

	if(objetivo.first != -1){

		objetivo.first = objetivo.first - despx;
		objetivo.second = objetivo.second - despy;
	}
	
}

Action ComportamientoJugador::think(Sensores sensores){

	Action accion = actIDLE;

	// Comprobamos si ha habido algún reinicio a causa de los lobos

	if(sensores.reset){

		// Reestablecemos la orientación al norte y la fila y columna para
		// colocar al agente en el centro de la matriz de mapaResultado2

		current_state.fil = current_state.col = mapaResultado.size();
		current_state.brujula = norte;

		// Si estaba bien situado, ponemos a false la variable bool

		if(bien_situado){
			
			bien_situado = false;
		} 

		// Se reinician los contadores y mapaResultado2 porque ya no sabemos dónde estamos

		contador = vector<vector<int>>(mapaResultado.size(), vector<int>(mapaResultado.size(),0));
      	contador_auxiliar = vector<vector<int>>(mapaResultado.size(), vector<int>(mapaResultado.size(),0));
		mapaResultado2 = vector<vector<unsigned char>>(2*mapaResultado.size(),vector<unsigned char>(2*mapaResultado.size(), '?'));
      	contador2 = vector<vector<int>>(2*mapaResultado.size(), vector<int>(2*mapaResultado.size(),0));
		contador_auxiliar2 = vector<vector<int>>(2*mapaResultado.size(), vector<int>(2*mapaResultado.size(),0));

		// En caso de que estuviese en búsqueda de la casilla desconocida más cercana, se anula ese estado de 
		// búsqueda ya que ya no sabemos dónde está esa casilla 

		if(en_busqueda != -1){
			
			objetivo = pair<int,int>(-1,-1);
			en_busqueda = -1;
		}

		// Si está bajo_bateria a true es porque había alguna casilla de recarga registrada y
		// o bien se estaba dirigiendo a ella o bien ya estaba en ella recargando. Como hemos
		// perdido la posición, lo ponemos a false

		if(bajo_bateria){
			bajo_bateria = false;
		}

		// Borrar las casillas de recarga de cuando se está mal situado

		recargas2.clear();

		// Si teníamos las zapatillas y/o el bikini, dejamos de tenerlos

		zapatillas = false;
		bikini = false;

		// Y la última acción se borra

		last_action = actIDLE;
	}

	cout << "Posicion: fila " << sensores.posF << " columna " << sensores.posC << " ";
	switch(sensores.sentido){
		case 0: cout << "Norte" << endl; break;
		case 1: cout << "Noreste" << endl; break;
		case 2: cout << "Este" << endl; break;
		case 3: cout << "Sureste" << endl; break;
		case 4: cout << "Sur " << endl; break;
		case 5: cout << "Suroeste" << endl; break;
		case 6: cout << "Oeste" << endl; break;
		case 7: cout << "Noroeste" << endl; break;
	}
	cout << "Terreno: ";
	for (int i=0; i<sensores.terreno.size(); i++)
		cout << sensores.terreno[i];
	cout << endl;

	cout << "Superficie: ";
	for (int i=0; i<sensores.superficie.size(); i++)
		cout << sensores.superficie[i];
	cout << endl;

	cout << "Colisión: " << sensores.colision << endl;
	cout << "Reset: " << sensores.reset << endl;
	cout << "Vida: " << sensores.vida << endl;
	cout << endl;


	// Comenzamos dibujando los precipicios

	if(!precipicios){

		PrecipiciosIniciales();
	}

	// Determinar el efecto de la ultima accion enviada
	
	switch(last_action){
		case actFORWARD:
			
			switch(current_state.brujula){
				
				case norte:	current_state.fil--; break;
				case noreste:	current_state.fil--; current_state.col++; break;
				case este:	current_state.col++;	break;
				case sureste:	current_state.fil++; current_state.col++; break;
				case sur:	current_state.fil++;	break;
				case suroeste:	current_state.fil++; current_state.col--; break;
				case oeste:	current_state.col--;	break;
				case noroeste:	current_state.fil--; current_state.col--; break;
			}
			
			break;
		case actTURN_SL:
			current_state.brujula = static_cast<Orientacion>((current_state.brujula+7)%8);
			break;
		case actTURN_SR:
			current_state.brujula = static_cast<Orientacion>((current_state.brujula+1)%8);
			break;
		case actTURN_BL:
			current_state.brujula = static_cast<Orientacion>((current_state.brujula+5)%8);
			break;
		case actTURN_BR:
			current_state.brujula = static_cast<Orientacion>((current_state.brujula+3)%8);
			break;
	}
	
	if((sensores.terreno[0]=='G' and !bien_situado) or (sensores.nivel == 0)){
		
		Traslacion(sensores.posF, sensores.posC);
		current_state.fil = sensores.posF;
		current_state.col = sensores.posC;
		current_state.brujula = sensores.sentido;
		bien_situado = true;
	}

	// Actualizar el contador de visitas. Pintamos la vista que tiene el robot


	PintarVista(sensores);

	// En caso de estar yendo a por recarga, las prioridades conseguidas con
	// IrseARecargar no se modifican (se mantienen fijas para asegurar que llega)

	ActualizarContador();

	if(sensores.terreno[0] == 'X'){

		// Si estamos encima de una casilla de recarga, la guardamos en memoria

		if(bien_situado){
			recargas.insert(make_pair(current_state.fil, current_state.col));
		} else {
			recargas2.insert(make_pair(current_state.fil, current_state.col));
		}
	}

	// Comprobamos si hay un bikini o zapatillas en la casilla en la que nos encontramos

	if(sensores.terreno[0] == 'K'){
		bikini = true;
	} else if(sensores.terreno[0] == 'D'){
		zapatillas = true;
	}

	// Si tenemos poca batería, activamos nuestro protocolo para ir a recargar. Tener cuidado con que no
	// esté activado el protocolo de búsqueda
	
	if(sensores.bateria < 1500 and !bajo_bateria){

		if((bien_situado and recargas.size() >= 1) or (!bien_situado and recargas2.size() >= 1)){

			// Si el protocolo de búsqueda estaba activado, se anula ya que es más pririotario no morir
			// por batería
			
			if(en_busqueda != -1){

				en_busqueda = -1;
				objetivo = pair<int,int>(-1,-1);

				if(bien_situado){
					RecuperarContador();
				} else {
					RecuperarContador2();
				}
			}

			bajo_bateria = true;

			// Antes de llamar a IrseARecargar, guardamos los valores de contador en
			// contador_auxiliar para recuperarlos una vez recargada la batería

			if(bien_situado){
				GuardarContador();
			} else {
				GuardarContador2();
			}

			IrseARecargar();
		}
	}

	// Cada 250 instantes de ejecución, se activa el protocolo de búsqueda de la casilla
	// menos explorada del mapa. 0 significa espera a la finalización del protocolo de
	// recarga y 1 significa que se activa del todo.

	if(sensores.vida%250 == 0){

		if(bajo_bateria){
			en_busqueda = 0;
		} else {
			en_busqueda = 1;
		}
	}
	
	// Comprobamos si estamos delante de una pared de muros

	ComprobarMuros(sensores);

	// Si han pasado 500 instantes y no está activado el protocolo de recarga, guardamos los
	// valores de contador

	if(en_busqueda == 1){
		
		// Determinamos cuál es la casilla objetivo. La vamos a determinar como la casilla
		// desconocida más cercana

		int distancia_min = 1000;

		if(bien_situado){
			for(int i = 3; i < mapaResultado.size()-3; i++){

				for(int j = 3; j < mapaResultado.size()-3; j++){
					if(mapaResultado[i][j] == '?' and (abs(i - current_state.fil) + abs(j - current_state.col) < distancia_min)){
						objetivo.first = i;
						objetivo.second = j;
						distancia_min = abs(i - current_state.fil) + abs(j - current_state.col);
					}
				}
			}
		} else {

			for(int i = 3; i < mapaResultado2.size()-3; i++){

				for(int j = 3; j < mapaResultado2.size()-3; j++){
					if(mapaResultado2[i][j] == '?' and (abs(i - current_state.fil) + abs(j - current_state.col) < distancia_min)){
						objetivo.first = i;
						objetivo.second = j;
						distancia_min = abs(i - current_state.fil) + abs(j - current_state.col);
					}
				}
			}

		}

		// Si ha encontrado una casilla sin explorar, se guarda contador, se llama a IrseAlObjetivo 
		// y en_busqueda pasa a valer 2. Si no, en_busqueda vuelve a valer -1.

		if(objetivo.first != -1){

			if(bien_situado){
				GuardarContador();
			} else {
				GuardarContador2();
			}

			IrseAlObjetivo();
			en_busqueda = 2;

		} else {
			en_busqueda = -1;
		}

	} else if (en_busqueda == 2){
		
			// Mientras que estamos en el estado 2 de la búsqueda, si resulta que el
			// agente logra registrar la casilla, entonces la búsqueda ha terminado,
			// así que el par vuelve a tener los valores por defecto y la búsqueda se
			// concluye volviendo al estado -1.

			if(bien_situado){
				if(mapaResultado[objetivo.first][objetivo.second] != '?'){

					objetivo = pair<int,int>(-1,-1);
					en_busqueda = -1;

					// Copiamos en contador las prioridades reales que guardamos antes para 
					// seguir descubriendo mapa una vez se ha visto el objetivo

					RecuperarContador();
					
				}
			} else {

				if(mapaResultado2[objetivo.first][objetivo.second] != '?'){

					objetivo = pair<int,int>(-1,-1);
					en_busqueda = -1;
					RecuperarContador2();
				}

			}

	} 

	if(muros != -1){
		
		// Hay que dejar un lado las prioridades si hay que sortear muros primero

		switch (muros)
		{
			case 0:

				accion = actTURN_SR; muros++;
				break;
			case 1:

				accion = actTURN_SR; muros++;
				break;
			case 2:

				if(sensores.terreno[2] != 'P' and sensores.terreno[1] == 'M'){
					
					accion = actFORWARD;
				} else if (PuedeAvanzar(sensores.terreno[1], sensores.bateria)){

					accion = actTURN_SL;
					muros = 5;
				} else if (!PuedeAvanzar(sensores.terreno[2],sensores.bateria)and sensores.terreno[2] != 'M'){

					accion = actTURN_BL;
					muros++;
				}

				break;
			case 3:

				accion = actTURN_SL;
				muros++;
				break;
			case 4:

				if(sensores.terreno[2] != 'P' and sensores.terreno[3] == 'M'){
					
					accion = actFORWARD;
				} else if (PuedeAvanzar(sensores.terreno[3], sensores.bateria)){

					accion = actTURN_SR;
					muros = 5;
				} else if (!PuedeAvanzar(sensores.terreno[2], sensores.bateria) and sensores.terreno[2] != 'M'){

					accion = actTURN_SL;
					muros = -1;
				}
				
				break;
			case 5:

				accion = actFORWARD;
				muros = -1;
				break;
			case 6:

				accion = actTURN_BR;
				muros = 2;
				break;
			case 7:

				accion = actTURN_SL;
				muros = 3;
		}
		
	} else if(!bikini and BikiniCerca(sensores)){

		if(sensores.terreno[2] == 'K' or sensores.terreno[6] == 'K' or sensores.terreno[12] == 'K'
		or sensores.terreno[5] == 'K' or sensores.terreno[11] == 'K' or sensores.terreno[7] == 'K'
		or sensores.terreno[13] == 'K' or sensores.terreno[10] == 'K' or sensores.terreno[14] == 'K'){
			accion = actFORWARD;
		} else if(sensores.terreno[1] == 'K' or sensores.terreno[4] == 'K' or sensores.terreno[9] == 'K'){
			accion = actTURN_SL;
		} else if(sensores.terreno[3] == 'K' or sensores.terreno[8] == 'K' or sensores.terreno[15] == 'K'){
			accion = actTURN_SR;
		}
	} else if(sensores.terreno[0] == 'A' and !bikini){

		int terreno = NoAguaCerca(sensores);

		if(terreno == 2 or terreno == 6 or terreno == 12
		or terreno == 5 or terreno == 11 or terreno == 7
		or terreno == 13 or terreno == 10 or terreno == 14){
			accion = actFORWARD;
		} else if(terreno == 1 or terreno == 4 or terreno == 9){
			if(last_action == actTURN_SL){
				accion = actFORWARD;
			} else {
				accion = actTURN_SL;
			}
		} else if(terreno == 3 or terreno == 8 or terreno == 15){
			if(last_action == actTURN_SR){
				accion = actFORWARD;
			} else {
				accion = actTURN_SR;
			}
		} else {
			accion = actTURN_BR;
		}

		// Si justo la de delante fuese buena, avanzamos, porque en caso de que siempre haya en 1 una
		// casilla buena, se quedará dando vueltas todo el rato. Lo mismo con el bosque (siguiente else if)

		if(sensores.terreno[2] != 'A' and sensores.terreno[2] != 'M' and sensores.terreno[2] != 'P'){
			accion = actFORWARD;
		}
		
	} else if(!zapatillas and ZapatillasCerca(sensores)){

		if(sensores.terreno[2] == 'D' or sensores.terreno[6] == 'D' or sensores.terreno[12] == 'D'
		or sensores.terreno[5] == 'D' or sensores.terreno[11] == 'D' or sensores.terreno[7] == 'D'
		or sensores.terreno[13] == 'D' or sensores.terreno[10] == 'D' or sensores.terreno[14] == 'D'){
			accion = actFORWARD;
		} else if(sensores.terreno[1] == 'D' or sensores.terreno[4] == 'D' or sensores.terreno[9] == 'D'){
			accion = actTURN_SL;
		} else if(sensores.terreno[3] == 'D' or sensores.terreno[8] == 'D' or sensores.terreno[15] == 'D'){
			accion = actTURN_SR;
		}
	} else if((sensores.terreno[0] == 'B' or (sensores.terreno[1] == 'B' and sensores.terreno[2] == 'B' and sensores.terreno[3] == 'B')
	or (sensores.terreno[1] == 'B' and sensores.terreno[2] == 'B' and sensores.terreno[3] == 'P') or
	(sensores.terreno[1] == 'P' and sensores.terreno[2] == 'B' and sensores.terreno[3] == 'B'))and !zapatillas){

		int terreno = NoBosqueCerca(sensores);

		if(terreno == 2 or terreno == 6 or terreno == 12
		or terreno == 5 or terreno == 11 or terreno == 7
		or terreno == 13 or terreno == 10 or terreno == 14){
			accion = actFORWARD;
		} else if(terreno == 1 or terreno == 4 or terreno == 9){

			if(last_action == actTURN_SL){
				accion = actFORWARD;
			} else {
				accion = actTURN_SL;
			}
		} else if(terreno == 3 or terreno == 8 or terreno == 15){

			if(last_action == actTURN_SR){
				accion = actFORWARD;
			} else {
				accion = actTURN_SR;
			}
		} else {
			accion = actTURN_SR;
		}

		if(sensores.terreno[2] != 'A' and sensores.terreno[2] != 'M' and sensores.terreno[2] != 'P' and sensores.terreno[2] != 'B'){
			accion = actFORWARD;
		}
	
	} else if(!bien_situado and PosicionamientoCerca(sensores)){

		if(sensores.terreno[2] == 'G' or sensores.terreno[6] == 'G' or sensores.terreno[12] == 'G'
		or sensores.terreno[5] == 'G' or sensores.terreno[11] == 'G' or sensores.terreno[7] == 'G'
		or sensores.terreno[13] == 'G' or sensores.terreno[10] == 'G' or sensores.terreno[14] == 'G'){
			accion = actFORWARD;
		} else if(sensores.terreno[1] == 'G' or sensores.terreno[4] == 'G' or sensores.terreno[9] == 'G'){
			accion = actTURN_SL;
		} else if(sensores.terreno[3] == 'G' or sensores.terreno[8] == 'G' or sensores.terreno[15] == 'G'){
			accion = actTURN_SR;
		}

	} else if(sensores.terreno[0] == 'X' and sensores.bateria < 3000 and bajo_bateria){

		accion = actIDLE;
	} else if(sensores.terreno[0] == 'X' and sensores.bateria >= 3000 and bajo_bateria){

		bajo_bateria = false;

		// Copiamos en contador las prioridades reales que guardamos antes para 
		// seguir descubriendo mapa una vez se ha recargado lo suficiente

		if(bien_situado){
			RecuperarContador();
		} else {
			RecuperarContador2();
		}

		// En caso de que el protocolo de búsqueda de la casilla menos frecuentada
		// esté en espera, se le da vía libre poniendo en_busqueda a 1

		if(en_busqueda == 0)
			en_busqueda = 1;
	
	} else if(RecargaCerca(sensores) and recargas.size() == 0){

		if(sensores.terreno[2] == 'X' or sensores.terreno[6] == 'X' or sensores.terreno[12] == 'X'
		or sensores.terreno[5] == 'X' or sensores.terreno[11] == 'X' or sensores.terreno[7] == 'X'
		or sensores.terreno[13] == 'X' or sensores.terreno[10] == 'X' or sensores.terreno[14] == 'X'){
			accion = actFORWARD;
		} else if(sensores.terreno[1] == 'X' or sensores.terreno[4] == 'X' or sensores.terreno[9] == 'X'){
			accion = actTURN_SL;
		} else if(sensores.terreno[3] == 'X' or sensores.terreno[8] == 'X' or sensores.terreno[15] == 'X'){
			accion = actTURN_SR;
		}
	
	}
	
	// Esto es una chapuza. Antes formaba parte de todo lo anterior con un else if, pero cuando se
	// activaba el protocolo de búsqueda, nunca se movía porque esta rama no se ejecutaba. Para 
	// apañarlo, lo que he hecho ha sido decir que se mueva a la casilla más prioritaria en caso
	// de que no haya habido ninguna acción antes (es decir, si es actIDLE y no está esperando en la
	// casilla de recarga, se moverá, ya que el resto de las otras ramas nunca asignan actIDLE)

	if((PuedeAvanzar(sensores.terreno[1], sensores.bateria) or PuedeAvanzar(sensores.terreno[2], sensores.bateria) 
	or PuedeAvanzar(sensores.terreno[3], sensores.bateria)) and !(bajo_bateria and sensores.terreno[0] == 'X') and accion == actIDLE){
		
		  int siguiente = CasillaMasPrioritaria(current_state.brujula, sensores);

		  switch(siguiente){

			  case 1: 
			  	accion = actTURN_SL; 
				
				// Si no se hace esto, a veces se queda dando vueltas

				if(last_action == actTURN_SL and PuedeAvanzar(sensores.terreno[2], sensores.bateria)){
					accion = actFORWARD;
				}

				break;
			  case 2: accion = actFORWARD; break;
			  case 3: 
			  	accion = actTURN_SR;

				// Si no se hace esto, a veces se queda dando vueltas

				if(last_action == actTURN_SR and PuedeAvanzar(sensores.terreno[2], sensores.bateria)){
					accion = actFORWARD;
				}

				break;
		  }
	} else if(!(bajo_bateria and sensores.terreno[0] == 'X') and accion == actIDLE){

		if(giros == 2){
			giros = 0;
		}

		switch(giros){

			case 0: accion = actTURN_BR; giros++; break;
			case 1: accion = actTURN_BL; giros++; break;
		}
	} 

	// Hay veces que se queda en actIDLE continuamente y no sé por qué. Uso un parche.
	// Solo puede quedarse en actIDLE si está recargando batería o esperando a que
	// un aldeano se quite de delante para poder avanzar

	if(accion == actFORWARD and (sensores.superficie[2] == 'a' or sensores.superficie[2] == 'l')){
		accion = actIDLE;
	}

	if(accion == actIDLE and last_action == actIDLE and !(bajo_bateria and sensores.terreno[0] == 'X') 
	and sensores.superficie[2] != 'a' and sensores.superficie[2] != 'l'){

		if(PuedeAvanzar(sensores.terreno[2], sensores.bateria)){
			accion = actFORWARD;
		} else if(PuedeAvanzar(sensores.terreno[1], sensores.bateria)){
			accion = actTURN_SL;
		} else if(PuedeAvanzar(sensores.terreno[3], sensores.bateria)){
			accion = actTURN_SR;
		} else {
			accion = actTURN_BR;
		}
	}

	last_action = accion;
	return accion;
}

int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}