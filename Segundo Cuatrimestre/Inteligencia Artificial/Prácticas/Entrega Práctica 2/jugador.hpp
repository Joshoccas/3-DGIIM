#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"

#include <list>

struct stateN0{
    ubicacion jugador;
    ubicacion sonambulo;

    bool operator==(const stateN0 &st) const{
        return (jugador.f == st.jugador.f && jugador.c == st.jugador.c &&
        sonambulo.f == st.sonambulo.f && sonambulo.c == st.sonambulo.c &&
        jugador.brujula == st.jugador.brujula && sonambulo.brujula == st.sonambulo.brujula);
    }

    bool operator<(const stateN0 &st) const
    {
        return (jugador.f < st.jugador.f ||
               (jugador.f == st.jugador.f && jugador.c < st.jugador.c) ||
               (jugador.f == st.jugador.f && jugador.c == st.jugador.c && jugador.brujula < st.jugador.brujula));
    }
};

struct stateN1{

  ubicacion jugador;
  ubicacion sonambulo;

  bool operator==(const stateN1 &st) const{
      return (jugador.f == st.jugador.f && jugador.c == st.jugador.c &&
             sonambulo.f == st.sonambulo.f && sonambulo.c == st.sonambulo.c &&
      jugador.brujula == st.jugador.brujula && sonambulo.brujula == st.sonambulo.brujula);
  }

  bool operator<(const stateN1 &st) const
  {
     return (jugador.f < st.jugador.f || (jugador.f == st.jugador.f && jugador.c < st.jugador.c) ||
              (jugador.f == st.jugador.f && jugador.c == st.jugador.c && jugador.brujula < st.jugador.brujula)
              || (jugador.f == st.jugador.f && jugador.c == st.jugador.c && jugador.brujula == st.jugador.brujula && sonambulo.f < st.sonambulo.f)
              || (jugador.f == st.jugador.f && jugador.c == st.jugador.c && jugador.brujula == st.jugador.brujula && sonambulo.f == st.sonambulo.f && sonambulo.c < st.sonambulo.c)
              || (jugador.f == st.jugador.f && jugador.c == st.jugador.c && jugador.brujula == st.jugador.brujula && sonambulo.f == st.sonambulo.f && sonambulo.c == st.sonambulo.c && sonambulo.brujula < st.sonambulo.brujula));
  }
};

struct stateN2{

  ubicacion jugador;
  ubicacion sonambulo;
  bool bikini;
  bool zapatillas;

   bool operator==(const stateN2 &st) const{
      return (jugador.f == st.jugador.f && jugador.c == st.jugador.c &&
      sonambulo.f == st.sonambulo.f && sonambulo.c == st.sonambulo.c &&
      jugador.brujula == st.jugador.brujula && sonambulo.brujula == st.sonambulo.brujula && bikini == st.bikini && zapatillas == st.zapatillas);
    }

  bool operator<(const stateN2 &st) const
  {
      return (jugador.f < st.jugador.f ||
              (jugador.f == st.jugador.f && jugador.c < st.jugador.c) ||
              (jugador.f == st.jugador.f && jugador.c == st.jugador.c && jugador.brujula < st.jugador.brujula) ||
              (jugador.f == st.jugador.f && jugador.c == st.jugador.c && jugador.brujula == st.jugador.brujula && bikini < st.bikini) ||
              (jugador.f == st.jugador.f && jugador.c == st.jugador.c && jugador.brujula == st.jugador.brujula && bikini == st.bikini && zapatillas < st.zapatillas));
  }
};

struct stateN3{

  ubicacion jugador;
  ubicacion sonambulo;
  bool bikini_j;
  bool zapatillas_j;
  bool bikini_s;
  bool zapatillas_s;

  bool operator==(const stateN3 &st) const{
      return (jugador.f == st.jugador.f && jugador.c == st.jugador.c &&
      sonambulo.f == st.sonambulo.f && sonambulo.c == st.sonambulo.c &&
      jugador.brujula == st.jugador.brujula && sonambulo.brujula == st.sonambulo.brujula && 
      bikini_j == st.bikini_j && zapatillas_j == st.zapatillas_j && zapatillas_s == st.zapatillas_s && bikini_s == st.bikini_s);
  }

  bool operator<(const stateN3 &st) const
  {
     return (jugador.f < st.jugador.f || (jugador.f == st.jugador.f && jugador.c < st.jugador.c) ||
              (jugador.f == st.jugador.f && jugador.c == st.jugador.c && jugador.brujula < st.jugador.brujula)
              || (jugador.f == st.jugador.f && jugador.c == st.jugador.c && jugador.brujula == st.jugador.brujula && sonambulo.f < st.sonambulo.f)
              || (jugador.f == st.jugador.f && jugador.c == st.jugador.c && jugador.brujula == st.jugador.brujula && sonambulo.f == st.sonambulo.f && sonambulo.c < st.sonambulo.c)
              || (jugador.f == st.jugador.f && jugador.c == st.jugador.c && jugador.brujula == st.jugador.brujula && sonambulo.f == st.sonambulo.f && sonambulo.c == st.sonambulo.c && sonambulo.brujula < st.sonambulo.brujula)
              || (jugador.f == st.jugador.f && jugador.c == st.jugador.c && jugador.brujula == st.jugador.brujula && sonambulo.f == st.sonambulo.f && sonambulo.c == st.sonambulo.c && sonambulo.brujula == st.sonambulo.brujula && zapatillas_j < st.zapatillas_j)
              || (jugador.f == st.jugador.f && jugador.c == st.jugador.c && jugador.brujula == st.jugador.brujula && sonambulo.f == st.sonambulo.f && sonambulo.c == st.sonambulo.c && sonambulo.brujula == st.sonambulo.brujula && zapatillas_j == st.zapatillas_j && bikini_j < st.bikini_j)
              || (jugador.f == st.jugador.f && jugador.c == st.jugador.c && jugador.brujula == st.jugador.brujula && sonambulo.f == st.sonambulo.f && sonambulo.c == st.sonambulo.c && sonambulo.brujula == st.sonambulo.brujula && zapatillas_j == st.zapatillas_j && bikini_j == st.bikini_j && zapatillas_s < st.zapatillas_s)
              || (jugador.f == st.jugador.f && jugador.c == st.jugador.c && jugador.brujula == st.jugador.brujula && sonambulo.f == st.sonambulo.f && sonambulo.c == st.sonambulo.c && sonambulo.brujula == st.sonambulo.brujula && zapatillas_j == st.zapatillas_j && bikini_j == st.bikini_j && zapatillas_s == st.zapatillas_s && bikini_s < st.bikini_s));

  }
};


struct nodeN0{
  stateN0 st;
  list<Action> secuencia;

  bool operator==(const nodeN0 &n) const{
    return (st == n.st);
  }

  bool operator<(const nodeN0 &n) const{
    return st < n.st;
  }
};

struct nodeN1{
  stateN1 st;
  list<Action> secuencia;

  bool operator==(const nodeN1 &n) const{
    return (st == n.st);
  }

  bool operator<(const nodeN1 &n) const{
    return st < n.st;
  }
};

struct nodeN2{
  stateN2 st;
  list<Action> secuencia;
  int bateria;

  bool operator==(const nodeN2 &n) const{
    return (st == n.st);
  }

  bool operator<(const nodeN2 &n) const{

    return n.bateria > bateria;
  }
};

struct nodeN3{
  stateN3 st;
  list<Action> secuencia;
  int coste;
  int heuristica;

  bool operator==(const nodeN3 &n) const{
    return (st == n.st);
  }

  bool operator<(const nodeN3 &n) const{

    return ((n.coste + n.heuristica) < (coste + heuristica));
  }
};

class ComportamientoJugador : public Comportamiento {
  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size) {
      // Inicializar Variables de Estado
    }
    ComportamientoJugador(std::vector< std::vector< unsigned char> > mapaR) : Comportamiento(mapaR) {
      // Inicializar Variables de Estado
      hayPlan = false;
    }
    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);
    void VisualizaPlan(const stateN0 &st, const list<Action> &plan);
    void VisualizaPlan1(const stateN1 &st, const list<Action> &plan);
    void VisualizaPlan2(const stateN2 &st, const list<Action> &plan);
    void VisualizaPlan3(const stateN3 &st, const list<Action> &plan);

  private:
    // Declarar Variables de Estado

  stateN0 c_state0;
  stateN1 c_state1;
  stateN2 c_state2;
  stateN3 c_state3;
  ubicacion goal;
  list<Action> plan;
  bool hayPlan;
};

#endif
