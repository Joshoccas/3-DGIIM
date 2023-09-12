#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"
#include <set>
#include <utility>
using namespace std;

struct state{
	int fil;
	int col;
	Orientacion brujula;
};

class ComportamientoJugador : public Comportamiento{

  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size){
      // Constructor de la clase
      current_state.fil = current_state.col = size;
      current_state.brujula = norte;
      last_action = actIDLE;
      bien_situado = false;
      precipicios = false;
      bikini = false;
      zapatillas = false;
      contador = vector<vector<int>>(mapaResultado.size(), vector<int>(mapaResultado.size(),0));
      contador_auxiliar = vector<vector<int>>(mapaResultado.size(), vector<int>(mapaResultado.size(),0));
      mapaResultado2 = vector<vector<unsigned char>>(2*mapaResultado.size(),vector<unsigned char>(2*mapaResultado.size(), '?'));
      contador2 = vector<vector<int>>(2*mapaResultado.size(), vector<int>(2*mapaResultado.size(),0));
      contador_auxiliar2 = vector<vector<int>>(2*mapaResultado.size(), vector<int>(2*mapaResultado.size(),0));
      giros = 0;
      muros = -1;
      bajo_bateria = false;
      en_busqueda = -1;
      objetivo = pair<int,int>(-1,-1);
    }

    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    bool PuedeAvanzar(char terreno, int bateria);
    void PintarVista(Sensores & sensores);
    bool RecargaCerca(Sensores & sensores);
    void IrseARecargar();
    void IrseAlObjetivo();
    bool BikiniCerca(Sensores & sensores);
    bool ZapatillasCerca(Sensores & sensores);
    bool PosicionamientoCerca(Sensores & sensores);
    int NoAguaCerca(Sensores & sensores);
    int NoBosqueCerca(Sensores & sensores);
    void ComprobarMuros(Sensores & sensores);
    void PrecipiciosIniciales();
    int CasillaMasPrioritaria(Orientacion o, Sensores & sensores);
    void ActualizarContador();
    void GuardarContador();
    void RecuperarContador();
    void GuardarContador2();
    void RecuperarContador2();
    void Traslacion(int f, int c);
    int interact(Action accion, int valor);

  private:
  
  // Declarar aquí las variables de estado
  state current_state;
  Action last_action;
  bool bien_situado;
  bool precipicios;
  bool bikini;
  bool zapatillas;
  vector<vector<int>> contador; 
  vector<vector<unsigned char>> mapaResultado2; // Mientras no se esté bien situado, se escribe todo lo que se ve aquí
  vector<vector<int>> contador2; // Contador de frecuencias de mapaResultado2
  int giros;
  int muros; // Variable entera que representa el estado en el que se encuentra al recorrer muros (entre -1 y 6)
  set<pair<int,int>> recargas; // Conjunto de posiciones que son casillas de recarga cuando está bien situado
  set<pair<int,int>> recargas2; // Conjunto de posiciones que son casillas de recarga cuando está mal situado
  bool bajo_bateria;
  int en_busqueda;
  vector<vector<int>> contador_auxiliar;
  vector<vector<int>> contador_auxiliar2;
  pair<int,int> objetivo; // Par que guarda la posición a la que se quiere ir
};

#endif
