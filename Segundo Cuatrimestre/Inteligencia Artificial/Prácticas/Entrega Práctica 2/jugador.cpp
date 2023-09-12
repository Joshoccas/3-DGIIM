#include "../Comportamientos_Jugador/jugador.hpp"
#include "motorlib/util.h"

#include <iostream>
#include <cmath>
#include <set>
#include <stack>
#include <queue>
#include <cmath>

bool VeoSonambulo(ubicacion j, ubicacion s, Orientacion & o){

  bool lo_veo = false;

  switch(o){
    case norte:

      for(int k = 0; k < 3 and !lo_veo; k++){

        if((s.f == j.f - 1) and (s.c == j.c - 1 + k)){
          lo_veo = true;
        }
      }

      for(int k = 0; k < 5 and !lo_veo; k++){
        if((s.f == j.f - 2) and (s.c == j.c - 2 + k)){
          lo_veo = true;
        }
      }

      for(int k = 0; k < 7 and !lo_veo; k++){
        if((s.f == j.f - 3) and (s.c == j.c - 3 + k)){
          lo_veo = true;
        }
      }

      break;
    case sur:

      for(int k = 0; k < 3 and !lo_veo; k++){

        if((s.f == j.f + 1) and (s.c == j.c - 1 + k)){
          lo_veo = true;
        }
      }

      for(int k = 0; k < 5 and !lo_veo; k++){
        if((s.f == j.f + 2) and (s.c == j.c - 2 + k)){
          lo_veo = true;
        }
      }

      for(int k = 0; k < 7 and !lo_veo; k++){
        if((s.f == j.f + 3) and (s.c == j.c - 3 + k)){
          lo_veo = true;
        }
      }

      break;
    case este:
      for(int k = 0; k < 3 and !lo_veo; k++){

        if((s.f == j.f - 1 + k) and (s.c == j.c + 1)){
          lo_veo = true;
        }
      }

      for(int k = 0; k < 5 and !lo_veo; k++){

        if((s.f == j.f - 2 + k) and (s.c == j.c + 2)){
          lo_veo = true;
        }
      }

      for(int k = 0; k < 7 and !lo_veo; k++){

        if((s.f == j.f - 3 + k) and (s.c == j.c + 3)){
          lo_veo = true;
        }
      }
      break;
    case oeste:
      for(int k = 0; k < 3 and !lo_veo; k++){

        if((s.f == j.f - 1 + k) and (s.c == j.c - 1)){
          lo_veo = true;
        }
      }

      for(int k = 0; k < 5 and !lo_veo; k++){

        if((s.f == j.f - 2 + k) and (s.c == j.c - 2)){
          lo_veo = true;
        }
      }

      for(int k = 0; k < 7 and !lo_veo; k++){

        if((s.f == j.f - 3 + k) and (s.c == j.c - 3)){
          lo_veo = true;
        }
      }
      break;
  }

  return lo_veo;
}

void AnularMatriz(vector<vector<unsigned char>> &matriz)
{
  for (int i = 0; i < matriz.size(); i++)
    for (int j = 0; j < matriz[0].size(); j++)
      matriz[i][j] = 0;
}

/** Devuelve la ubicación siguiente según el avance del agente*/
ubicacion NextCasilla(const ubicacion &pos)
{
	ubicacion next = pos;
	switch (pos.brujula)
	{
	case norte:
		next.f = pos.f - 1;
		break;
	case noreste:
		next.f = pos.f - 1;
		next.c = pos.c + 1;
		break;
	case este:
		next.c = pos.c + 1;
		break;
	case sureste:
		next.f = pos.f + 1;
		next.c = pos.c + 1;
		break;
	case sur:
		next.f = pos.f + 1;
		break;
	case suroeste:
		next.f = pos.f + 1;
		next.c = pos.c - 1;
		break;
	case oeste:
		next.c = pos.c - 1;
		break;
	case noroeste:
		next.f = pos.f - 1;
		next.c = pos.c - 1;
		break;
	default:
		break;
	}

	return next;
}

/** Permite pintar sobre el mapa del simulador el plan partiendo desde el estado st */
void ComportamientoJugador::VisualizaPlan(const stateN0 &st, const list<Action> &plan)
{
  AnularMatriz(mapaConPlan);
  stateN0 cst = st;

  auto it = plan.begin();
  while (it != plan.end()){
    switch (*it){
      case actFORWARD:
        cst.jugador = NextCasilla(cst.jugador);
	  mapaConPlan[cst.jugador.f][cst.jugador.c] = 1;
	  break;
	case actTURN_R:
        cst.jugador.brujula = (Orientacion)((cst.jugador.brujula + 2) % 8);
	  break;
	case actTURN_L:
	  cst.jugador.brujula = (Orientacion)((cst.jugador.brujula + 6) % 8);
	  break;
	case actSON_FORWARD:
	  cst.sonambulo = NextCasilla(cst.sonambulo);
	  mapaConPlan[cst.sonambulo.f][cst.sonambulo.c] = 2;
	  break;
	case actSON_TURN_SR:
	  cst.sonambulo.brujula = (Orientacion)((cst.sonambulo.brujula + 1) % 8);
	  break;
	case actSON_TURN_SL:
	  cst.sonambulo.brujula = (Orientacion)((cst.sonambulo.brujula + 7) % 8);
	  break;
    }
    it++;
  }
}

void ComportamientoJugador::VisualizaPlan1(const stateN1 &st, const list<Action> &plan)
{
  AnularMatriz(mapaConPlan);
  stateN1 cst = st;

  auto it = plan.begin();
  while (it != plan.end()){
    switch (*it){
      case actFORWARD:
        cst.jugador = NextCasilla(cst.jugador);
	  mapaConPlan[cst.jugador.f][cst.jugador.c] = 1;
	  break;
	case actTURN_R:
        cst.jugador.brujula = (Orientacion)((cst.jugador.brujula + 2) % 8);
	  break;
	case actTURN_L:
	  cst.jugador.brujula = (Orientacion)((cst.jugador.brujula + 6) % 8);
	  break;
	case actSON_FORWARD:
	  cst.sonambulo = NextCasilla(cst.sonambulo);
	  mapaConPlan[cst.sonambulo.f][cst.sonambulo.c] = 2;
	  break;
	case actSON_TURN_SR:
	  cst.sonambulo.brujula = (Orientacion)((cst.sonambulo.brujula + 1) % 8);
	  break;
	case actSON_TURN_SL:
	  cst.sonambulo.brujula = (Orientacion)((cst.sonambulo.brujula + 7) % 8);
	  break;
    }
    it++;
  }
}

void ComportamientoJugador::VisualizaPlan2(const stateN2 &st, const list<Action> &plan)
{
  AnularMatriz(mapaConPlan);
  stateN2 cst = st;

  auto it = plan.begin();
  while (it != plan.end()){
    switch (*it){
      case actFORWARD:
        cst.jugador = NextCasilla(cst.jugador);
	  mapaConPlan[cst.jugador.f][cst.jugador.c] = 1;
	  break;
	case actTURN_R:
        cst.jugador.brujula = (Orientacion)((cst.jugador.brujula + 2) % 8);
	  break;
	case actTURN_L:
	  cst.jugador.brujula = (Orientacion)((cst.jugador.brujula + 6) % 8);
	  break;
	case actSON_FORWARD:
	  cst.sonambulo = NextCasilla(cst.sonambulo);
	  mapaConPlan[cst.sonambulo.f][cst.sonambulo.c] = 2;
	  break;
	case actSON_TURN_SR:
	  cst.sonambulo.brujula = (Orientacion)((cst.sonambulo.brujula + 1) % 8);
	  break;
	case actSON_TURN_SL:
	  cst.sonambulo.brujula = (Orientacion)((cst.sonambulo.brujula + 7) % 8);
	  break;
    }
    it++;
  }
}

void ComportamientoJugador::VisualizaPlan3(const stateN3 &st, const list<Action> &plan)
{
  AnularMatriz(mapaConPlan);
  stateN3 cst = st;

  auto it = plan.begin();
  while (it != plan.end()){
    switch (*it){
      case actFORWARD:
        cst.jugador = NextCasilla(cst.jugador);
	  mapaConPlan[cst.jugador.f][cst.jugador.c] = 1;
	  break;
	case actTURN_R:
        cst.jugador.brujula = (Orientacion)((cst.jugador.brujula + 2) % 8);
	  break;
	case actTURN_L:
	  cst.jugador.brujula = (Orientacion)((cst.jugador.brujula + 6) % 8);
	  break;
	case actSON_FORWARD:
	  cst.sonambulo = NextCasilla(cst.sonambulo);
	  mapaConPlan[cst.sonambulo.f][cst.sonambulo.c] = 2;
	  break;
	case actSON_TURN_SR:
	  cst.sonambulo.brujula = (Orientacion)((cst.sonambulo.brujula + 1) % 8);
	  break;
	case actSON_TURN_SL:
	  cst.sonambulo.brujula = (Orientacion)((cst.sonambulo.brujula + 7) % 8);
	  break;
    }
    it++;
  }
}

/** Devuelve si una ubicación en el mapa es transitable para el agente */
bool CasillaTransitable(const ubicacion &x, const vector<vector<unsigned char>> &mapa)
{
	return (mapa[x.f][x.c] != 'P' and mapa[x.f][x.c] != 'M');
}

stateN0 apply(const Action &a, const stateN0 &st, const vector<vector<unsigned char>> &mapa)
{
  stateN0 st_result = st;
  ubicacion sig_ubicacion;
  switch (a){
  case actFORWARD: // si casilla delante es transitable y no está ocupada por el sonámbulo
    sig_ubicacion = NextCasilla(st.jugador);
    if (CasillaTransitable(sig_ubicacion, mapa) and !(sig_ubicacion == st.sonambulo)){
      st_result.jugador = sig_ubicacion;
    }
    break;
  case actTURN_L:
    st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula + 6) % 8);
    break;

  case actTURN_R:
    st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula + 2) % 8);
    break;
  }
  return st_result;
}

stateN1 apply1(const Action &a, const stateN1 &st, const vector<vector<unsigned char>> &mapa)
{
  stateN1 st_result = st;
  ubicacion sig_ubicacion;
  switch (a){
  case actFORWARD: // si casilla delante es transitable y no está ocupada por el sonámbulo
    sig_ubicacion = NextCasilla(st.jugador);
    if (CasillaTransitable(sig_ubicacion, mapa) and !(sig_ubicacion == st.sonambulo)){
      st_result.jugador = sig_ubicacion;
    }
    break;
  case actTURN_L:
    st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula + 6) % 8);
    break;

  case actTURN_R:
    st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula + 2) % 8);
    break;
  
  case actSON_FORWARD:
    sig_ubicacion = NextCasilla(st.sonambulo);
    if(CasillaTransitable(sig_ubicacion, mapa) and !(sig_ubicacion == st.jugador)){
      st_result.sonambulo = sig_ubicacion;
    }
    break;
  case actSON_TURN_SL:
    st_result.sonambulo.brujula = static_cast<Orientacion>((st_result.sonambulo.brujula + 7) % 8);
    break;
  
  case actSON_TURN_SR:
    st_result.sonambulo.brujula = static_cast<Orientacion>((st_result.sonambulo.brujula + 1) % 8);
    break;
  }
  return st_result;
}

stateN2 apply2(const Action &a, const stateN2 &st, const vector<vector<unsigned char>> &mapa)
{
  stateN2 st_result = st;
  ubicacion sig_ubicacion;
  switch (a){
  case actFORWARD: // si casilla delante es transitable y no está ocupada por el sonámbulo
    sig_ubicacion = NextCasilla(st.jugador);
    st_result.jugador = sig_ubicacion;
    if(mapa[sig_ubicacion.f][sig_ubicacion.c] == 'K'){
      st_result.bikini = true;
      st_result.zapatillas = false;
    } else if(mapa[sig_ubicacion.f][sig_ubicacion.c] == 'D'){
      st_result.bikini = false;
      st_result.zapatillas = true;
    }
    break;
  case actTURN_L:
    st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula + 6) % 8);
    break;

  case actTURN_R:
    st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula + 2) % 8);
    break;
  }
  return st_result;
}

stateN3 apply3(const Action &a, const stateN3 &st, const vector<vector<unsigned char>> &mapa)
{
  stateN3 st_result = st;
  ubicacion sig_ubicacion;
  switch (a){
  case actFORWARD: // si casilla delante es transitable y no está ocupada por el sonámbulo
    sig_ubicacion = NextCasilla(st.jugador);
    st_result.jugador = sig_ubicacion;
    if(mapa[sig_ubicacion.f][sig_ubicacion.c] == 'K'){
      st_result.bikini_j = true;
      st_result.zapatillas_j = false;
    } else if(mapa[sig_ubicacion.f][sig_ubicacion.c] == 'D'){
      st_result.bikini_j = false;
      st_result.zapatillas_j = true;
    }
    break;

  case actSON_FORWARD:
    sig_ubicacion = NextCasilla(st.sonambulo);
    st_result.sonambulo = sig_ubicacion;
    if(mapa[sig_ubicacion.f][sig_ubicacion.c] == 'K'){
      st_result.bikini_s = true;
      st_result.zapatillas_s = false;
    } else if(mapa[sig_ubicacion.f][sig_ubicacion.c] == 'D'){
      st_result.bikini_s = false;
      st_result.zapatillas_s = true;
    }
    break;

  case actTURN_L:
    st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula + 6) % 8);
    break;

  case actTURN_R:
    st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula + 2) % 8);
    break;

  case actSON_TURN_SL:
    st_result.sonambulo.brujula = static_cast<Orientacion>((st_result.sonambulo.brujula + 7) % 8);
    break;

  case actSON_TURN_SR:
    st_result.sonambulo.brujula = static_cast<Orientacion>((st_result.sonambulo.brujula + 1) % 8);
    break;
  }
  return st_result;
}

int CosteAccion(stateN2 st, Action accion, const vector<vector<unsigned char>> &mapa){

  int coste = 0;

  switch(mapa[st.jugador.f][st.jugador.c]){
    case 'A':
      if(accion == actFORWARD){
        if(st.bikini){
          coste = 10;
        }else{
          coste = 100;
        }
      }else{
        if(st.bikini){
          coste = 5;
        }else{
          coste = 25;
        }
      }
      break;
    case 'B':
      if(accion == actFORWARD){
        if(st.zapatillas){
          coste = 15;
        }else{
          coste = 50;
        }
      }else{
        if(st.zapatillas){
          coste = 1;
        }else{
          coste = 5;
        }
      }
      break;
    case 'T':
      coste = 2;
      break;
    default:
      coste = 1;
      break;
  }

  return coste;
}

int CosteAccion3(stateN3 st, Action accion, const vector<vector<unsigned char>> &mapa, char tipo){

  int coste = 0;

  if(tipo == 'j'){
    switch(mapa[st.jugador.f][st.jugador.c]){
      case 'A':
        if(accion == actFORWARD){
          if(st.bikini_j){
            coste = 10;
          }else{
            coste = 100;
          }
        }else{
          if(st.bikini_j){
            coste = 5;
          }else{
            coste = 25;
          }
        }
        break;
      case 'B':
        if(accion == actFORWARD){
          if(st.zapatillas_j){
            coste = 15;
          }else{
            coste = 50;
          }
        }else{
          if(st.zapatillas_j){
            coste = 1;
          }else{
            coste = 5;
          }
        }
        break;
      case 'T':
        coste = 2;
        break;
      default:
        coste = 1;
        break;
    }
  } else {
    switch(mapa[st.sonambulo.f][st.sonambulo.c]){
      case 'A':
        if(accion == actSON_FORWARD){
          if(st.bikini_s){
            coste = 10;
          }else{
            coste = 100;
          }
        }else{
          if(st.bikini_s){
            coste = 2;
          }else{
            coste = 7;
          }
        }
        break;
      case 'B':
        if(accion == actSON_FORWARD){
          if(st.zapatillas_s){
            coste = 15;
          }else{
            coste = 50;
          }
        }else{
          if(st.zapatillas_s){
            coste = 1;
          }else{
            coste = 3;
          }
        }
        break;
      case 'T':
        if(accion == actSON_FORWARD){
          coste = 2;
        } else {
          coste = 1;
        }
        break;
      default:
        coste = 1;
        break;
    }

  }

  return coste;
}

int CalcularHeuristica(int f, int c, const ubicacion &final){

  int dist_filas = abs(f - final.f);
  int dist_columnas = abs(c - final.c);
  int resultado = dist_filas;

  if(resultado < dist_columnas){
    resultado = dist_columnas;
  }

  return resultado;
}

/** Encuentra si el elmento item está en lista */
bool Find(const stateN0 &item, const list<nodeN0> &lista)
{
  auto it = lista.begin();
  while (it != lista.end() and !(it->st == item))
    it++;

  return (!(it == lista.end()));
}


list<Action> AnchuraSoloJugador0(const stateN0 &inicio, const ubicacion &final, const vector<vector<unsigned char>> &mapa)
{
  nodeN0 current_node;
  list<nodeN0> frontier;
  set<nodeN0> explored;
  list<Action> plan;
  current_node.st = inicio;
	bool SolutionFound = (current_node.st.jugador.f == final.f
  and current_node.st.jugador.c == final.c);
  frontier.push_back(current_node);

  while (!frontier.empty() and !SolutionFound) {
    frontier.pop_front();
    explored.insert(current_node);

    // Generar hijo actFORWARD
    nodeN0 child_forward = current_node;
    child_forward.st = apply(actFORWARD, current_node.st, mapa);
    if (child_forward.st.jugador.f == final.f and child_forward.st.jugador.c == final.c){
      child_forward.secuencia.push_back(actFORWARD);
      current_node = child_forward;
      SolutionFound = true;
    }
    else if (explored.find(child_forward) == explored.end()){
      child_forward.secuencia.push_back(actFORWARD);
		  frontier.push_back(child_forward);
    }

    if (!SolutionFound) {
      // Generar hijo actTURN_L
      nodeN0 child_turnl = current_node;
      child_turnl.st = apply(actTURN_L, current_node.st, mapa);
      if (explored.find(child_turnl) == explored.end()){
        child_turnl.secuencia.push_back(actTURN_L);
        frontier.push_back(child_turnl);
      }
      // Generar hijo actTURN_R
      nodeN0 child_turnr = current_node;
      child_turnr.st = apply(actTURN_R, current_node.st, mapa);
      if (explored.find(child_turnr) == explored.end()){
        child_turnr.secuencia.push_back(actTURN_R);
        frontier.push_back(child_turnr);
      }
    }

    if (!SolutionFound and !frontier.empty()){
      current_node = frontier.front();
      while(!frontier.empty() and explored.find(current_node) != explored.end()){
        frontier.pop_front();
        if(!frontier.empty())
          current_node = frontier.front();

      }
    }
  }

  if(SolutionFound){
    plan = current_node.secuencia;
  }

  return plan;
}

list<Action> AnchuraSoloJugador1(const stateN1 &inicio, const ubicacion &final, const vector<vector<unsigned char>> &mapa)
{
  nodeN1 current_node;
  list<nodeN1> frontier;
  set<nodeN1> explored;
  list<Action> plan;
  bool veo_sonambulo = false;
  current_node.st = inicio;
	bool SolutionFound = (current_node.st.sonambulo.f == final.f
  and current_node.st.sonambulo.c == final.c);
  frontier.push_back(current_node);

  while (!frontier.empty() and !SolutionFound) {
    frontier.pop_front();
    explored.insert(current_node);

    // Generar hijo actSON_FORWARD si es posible

    veo_sonambulo = VeoSonambulo(current_node.st.jugador, current_node.st.sonambulo, current_node.st.jugador.brujula);

    if(veo_sonambulo){
      nodeN1 child_sonforward = current_node;
      child_sonforward.st = apply1(actSON_FORWARD, current_node.st, mapa);
      if (child_sonforward.st.sonambulo.f == final.f and child_sonforward.st.sonambulo.c == final.c){
        child_sonforward.secuencia.push_back(actSON_FORWARD);
        current_node = child_sonforward;
        SolutionFound = true;
      }
      else if (explored.find(child_sonforward) == explored.end()){
        child_sonforward.secuencia.push_back(actSON_FORWARD);
		    frontier.push_back(child_sonforward);
      }
    }

    if (!SolutionFound) {
      // Generar hijo actFORWARD
      nodeN1 child_forward = current_node;
      child_forward.st = apply1(actFORWARD, current_node.st, mapa);
      if (explored.find(child_forward) == explored.end()){
        child_forward.secuencia.push_back(actFORWARD);
        frontier.push_back(child_forward);
      }
      // Generar hijo actTURN_L
      nodeN1 child_turnl = current_node;
      child_turnl.st = apply1(actTURN_L, current_node.st, mapa);
      if (explored.find(child_turnl) == explored.end()){
        child_turnl.secuencia.push_back(actTURN_L);
        frontier.push_back(child_turnl);
      }
      // Generar hijo actTURN_R
      nodeN1 child_turnr = current_node;
      child_turnr.st = apply1(actTURN_R, current_node.st, mapa);
      if (explored.find(child_turnr) == explored.end()){
        child_turnr.secuencia.push_back(actTURN_R);
        frontier.push_back(child_turnr);
      }

      // En caso de ver al sonámbulo, también se deben generar los hijos de los giros
      // del sonámbulo

      if(veo_sonambulo){
        // Generar hijo actSON_TURN_SL
        nodeN1 child_sonturnsl = current_node;
        child_sonturnsl.st = apply1(actSON_TURN_SL, current_node.st, mapa);
        if (explored.find(child_sonturnsl) == explored.end()){
          child_sonturnsl.secuencia.push_back(actSON_TURN_SL);
          frontier.push_back(child_sonturnsl);
        }
        // Generar hijo actSON_TURN_SR
        nodeN1 child_sonturnsr = current_node;
        child_sonturnsr.st = apply1(actSON_TURN_SR, current_node.st, mapa);
        if (explored.find(child_sonturnsr) == explored.end()){
          child_sonturnsr.secuencia.push_back(actSON_TURN_SR);
          frontier.push_back(child_sonturnsr);
        }
      }
    }

    if (!SolutionFound and !frontier.empty()){
      current_node = frontier.front();
      while(!frontier.empty() and explored.find(current_node) != explored.end()){
        frontier.pop_front();
        if(!frontier.empty())
          current_node = frontier.front();

      }
    }
  }

  if(SolutionFound){
    plan = current_node.secuencia;
  }

  return plan;
}

list<Action> AnchuraSoloJugador2(const stateN2 &inicio, const ubicacion &final, const vector<vector<unsigned char>> &mapa, int bateria)
{
  nodeN2 current_node;
  priority_queue<nodeN2> frontier;
  set<stateN2> explored;
  list<Action> plan;
  current_node.st = inicio;
  current_node.bateria = bateria;
	bool SolutionFound = (current_node.st.jugador.f == final.f
  and current_node.st.jugador.c == final.c);
  frontier.push(current_node);

  while (!frontier.empty() and !SolutionFound) {
    frontier.pop();
    explored.insert(current_node.st);
    if (current_node.st.jugador.f == final.f and current_node.st.jugador.c == final.c){
      SolutionFound = true;
    }

    // Generar hijo actFORWARD

    if (!SolutionFound) {
      // Generar hijo actFORWARD (si el sonámbulo no está delante)
      ubicacion aux = NextCasilla(current_node.st.jugador);
      if(((aux.f != current_node.st.sonambulo.f) || (aux.c != current_node.st.sonambulo.c)) && CasillaTransitable(aux,mapa)){
        nodeN2 child_forward = current_node;
        child_forward.bateria-=CosteAccion(child_forward.st,actFORWARD, mapa);
        child_forward.st = apply2(actFORWARD, current_node.st, mapa);
        if (explored.find(child_forward.st) == explored.end()){
          child_forward.secuencia.push_back(actFORWARD);
          frontier.push(child_forward);
        }
      }
      // Generar hijo actTURN_L
      nodeN2 child_turnl = current_node;
      child_turnl.bateria-=CosteAccion(child_turnl.st,actTURN_L, mapa);
      child_turnl.st = apply2(actTURN_L, current_node.st, mapa);
      if (explored.find(child_turnl.st) == explored.end()){
        child_turnl.secuencia.push_back(actTURN_L);
        frontier.push(child_turnl);
      }
      // Generar hijo actTURN_R
      nodeN2 child_turnr = current_node;
      child_turnr.bateria-=CosteAccion(child_turnr.st,actTURN_R, mapa);
      child_turnr.st = apply2(actTURN_R, current_node.st, mapa);
      if (explored.find(child_turnr.st) == explored.end()){
        child_turnr.secuencia.push_back(actTURN_R);
        frontier.push(child_turnr);
      }
    }

    if (!SolutionFound and !frontier.empty()){
      current_node = frontier.top();
      while(!frontier.empty() and explored.find(current_node.st) != explored.end()){
        frontier.pop();
        if(!frontier.empty())
          current_node = frontier.top();

      }
    }
  }

  if(SolutionFound){
    plan = current_node.secuencia;
  }

  return plan;
}

list<Action> AlgoritmoAE(const stateN3 &inicio, const ubicacion &final, const vector<vector<unsigned char>> &mapa, int coste){

  nodeN3 current_node;
  priority_queue<nodeN3> frontier;
  set<stateN3> explored;
  list<Action> plan;
  bool veo_sonambulo;
  current_node.st = inicio;
  current_node.coste = coste;
  current_node.heuristica = CalcularHeuristica(inicio.sonambulo.f,inicio.sonambulo.c,final);
	bool SolutionFound = (current_node.st.sonambulo.f == final.f
  and current_node.st.sonambulo.c == final.c);
  frontier.push(current_node);

  while (!frontier.empty() and !SolutionFound) {
    frontier.pop();
    explored.insert(current_node.st);
    if (current_node.st.sonambulo.f == final.f and current_node.st.sonambulo.c == final.c){
      SolutionFound = true;
    }

    // Generar hijo actSON_FORWARD si es posible

    veo_sonambulo = VeoSonambulo(current_node.st.jugador, current_node.st.sonambulo, current_node.st.jugador.brujula);

    if (!SolutionFound) {
      // Generar hijo actFORWARD (si el sonámbulo no está delante)
      ubicacion aux = NextCasilla(current_node.st.jugador);
      if(((aux.f != current_node.st.sonambulo.f) || (aux.c != current_node.st.sonambulo.c)) && CasillaTransitable(aux,mapa)){
        nodeN3 child_forward = current_node;
        child_forward.coste+=CosteAccion3(child_forward.st,actFORWARD, mapa, 'j');
        child_forward.st = apply3(actFORWARD, current_node.st, mapa);
        if (explored.find(child_forward.st) == explored.end()){
          child_forward.secuencia.push_back(actFORWARD);
          frontier.push(child_forward);
        }
      }
      // Generar hijo actTURN_L
      nodeN3 child_turnl = current_node;
      child_turnl.coste+=CosteAccion3(child_turnl.st,actTURN_L, mapa, 'j');
      child_turnl.st = apply3(actTURN_L, current_node.st, mapa);
      if (explored.find(child_turnl.st) == explored.end()){
        child_turnl.secuencia.push_back(actTURN_L);
        frontier.push(child_turnl);
      }
      // Generar hijo actTURN_R
      nodeN3 child_turnr = current_node;
      child_turnr.coste+=CosteAccion3(child_turnr.st,actTURN_R, mapa, 'j');
      child_turnr.st = apply3(actTURN_R, current_node.st, mapa);
      if (explored.find(child_turnr.st) == explored.end()){
        child_turnr.secuencia.push_back(actTURN_R);
        frontier.push(child_turnr);
      }

      veo_sonambulo = VeoSonambulo(current_node.st.jugador, current_node.st.sonambulo, current_node.st.jugador.brujula);

      // En caso de ver al sonámbulo, también se deben generar los hijos de los giros
      // del sonámbulo

      if(veo_sonambulo){
        // Generar hijo actSON_FORWARD
        aux = NextCasilla(current_node.st.sonambulo);
        if(((aux.f != current_node.st.jugador.f) || (aux.c != current_node.st.jugador.c)) && CasillaTransitable(aux,mapa)){
          nodeN3 child_sonforward = current_node;
          child_sonforward.coste+=CosteAccion3(child_sonforward.st,actSON_FORWARD, mapa, 's');
          child_sonforward.st = apply3(actSON_FORWARD, current_node.st, mapa);
          child_sonforward.heuristica = CalcularHeuristica(child_sonforward.st.sonambulo.f, child_sonforward.st.sonambulo.c,final);
          if (explored.find(child_sonforward.st) == explored.end()){
            child_sonforward.secuencia.push_back(actSON_FORWARD);
            frontier.push(child_sonforward);
          }
        }

        // Generar hijo actSON_TURN_SL
        nodeN3 child_sonturnsl = current_node;
        child_sonturnsl.coste+=CosteAccion3(child_sonturnsl.st,actSON_TURN_SL, mapa, 's');
        child_sonturnsl.st = apply3(actSON_TURN_SL, current_node.st, mapa);
        if (explored.find(child_sonturnsl.st) == explored.end()){
          child_sonturnsl.secuencia.push_back(actSON_TURN_SL);
          frontier.push(child_sonturnsl);
        }
        // Generar hijo actSON_TURN_SR
        nodeN3 child_sonturnsr = current_node;
        child_sonturnsr.coste+=CosteAccion3(child_sonturnsr.st,actSON_TURN_SR, mapa, 's');
        child_sonturnsr.st = apply3(actSON_TURN_SR, current_node.st, mapa);
        if (explored.find(child_sonturnsr.st) == explored.end()){
          child_sonturnsr.secuencia.push_back(actSON_TURN_SR);
          frontier.push(child_sonturnsr);
        }
      }
    }

    if (!SolutionFound and !frontier.empty()){
      current_node = frontier.top();
      while(!frontier.empty() and explored.find(current_node.st) != explored.end()){
        frontier.pop();
        if(!frontier.empty())
          current_node = frontier.top();

      }
    }
  }

  if(SolutionFound){
    plan = current_node.secuencia;
  }

  return plan;
}

// Este es el método principal que se piden en la practica.
// Tiene como entrada la información de los sensores y devuelve la acción a realizar.
// Para ver los distintos sensores mirar fichero "comportamiento.hpp"
Action ComportamientoJugador::think(Sensores sensores)
{
	Action accion = actIDLE;

  if(sensores.nivel != 4){
    if (!hayPlan){
      
      cout  << "Calculando un nuevo plan\n";

      switch(sensores.nivel){
        case 0:
          c_state0.jugador.f = sensores.posF;
          c_state0.jugador.c = sensores.posC;
          c_state0.jugador.brujula = sensores.sentido;
          c_state0.sonambulo.f = sensores.SONposF;
          c_state0.sonambulo.c = sensores.SONposC;
          c_state0.sonambulo.brujula = sensores.SONsentido;
          goal.f = sensores.destinoF;
          goal.c = sensores.destinoC;
        case 1:
          c_state1.jugador.f = sensores.posF;
          c_state1.jugador.c = sensores.posC;
          c_state1.jugador.brujula = sensores.sentido;
          c_state1.sonambulo.f = sensores.SONposF;
          c_state1.sonambulo.c = sensores.SONposC;
          c_state1.sonambulo.brujula = sensores.SONsentido;
          goal.f = sensores.destinoF;
          goal.c = sensores.destinoC;
        case 2:
          c_state2.jugador.f = sensores.posF;
          c_state2.jugador.c = sensores.posC;
          c_state2.jugador.brujula = sensores.sentido;
          c_state2.sonambulo.f = sensores.SONposF;
          c_state2.sonambulo.c = sensores.SONposC;
          c_state2.sonambulo.brujula = sensores.SONsentido;

          if(sensores.terreno[0] == 'K'){
            c_state2.bikini = true;
          }else{
            c_state2.bikini = false;
          }

          if(sensores.terreno[0] == 'D'){
            c_state2.zapatillas = true;
          } else {
            c_state2.zapatillas = false;
          }

          goal.f = sensores.destinoF;
          goal.c = sensores.destinoC;
        case 3:
          c_state3.jugador.f = sensores.posF;
          c_state3.jugador.c = sensores.posC;
          c_state3.jugador.brujula = sensores.sentido;
          c_state3.sonambulo.f = sensores.SONposF;
          c_state3.sonambulo.c = sensores.SONposC;
          c_state3.sonambulo.brujula = sensores.SONsentido;

          if(sensores.terreno[0] == 'K'){
            c_state3.bikini_j = true;
          }else{
            c_state3.bikini_j = false;
          }

          if(sensores.terreno[0] == 'D'){
            c_state3.zapatillas_j = true;
          } else {
            c_state3.zapatillas_j = false;
          }

          if(mapaResultado[c_state3.sonambulo.f][c_state3.sonambulo.c] == 'K'){
            c_state3.bikini_s = true;
          }else{
            c_state3.bikini_s = false;
          }

          if(mapaResultado[c_state3.sonambulo.f][c_state3.sonambulo.c] == 'D'){
            c_state3.zapatillas_s = true;
          }else{
            c_state3.zapatillas_s = false;
          }

          goal.f = sensores.destinoF;
          goal.c = sensores.destinoC;
      }

      switch(sensores.nivel){
        
        case 0:
          plan = AnchuraSoloJugador0(c_state0, goal, mapaResultado);
          break;
        case 1:
          plan = AnchuraSoloJugador1(c_state1, goal, mapaResultado);
          break;
        case 2:
          plan = AnchuraSoloJugador2(c_state2, goal, mapaResultado, sensores.bateria);
          break;
        case 3:
          plan = AlgoritmoAE(c_state3, goal, mapaResultado, 0);
          break;
      }
      
      if(plan.size() > 0){

        switch(sensores.nivel){
        
          case 0:
            VisualizaPlan(c_state0,plan);
            break;
          case 1:
            VisualizaPlan1(c_state1,plan);
            break;
          case 2:
            VisualizaPlan2(c_state2,plan);
            break;
          case 3:
            VisualizaPlan3(c_state3,plan);
            break;
      }
        
        hayPlan = true;
        cout << "Se encontró un plan\n";
    }
    }
    if (hayPlan and plan.size()>0){

      cout << "Ejecutando la siguiente acción del plan\n";
      accion = plan.front();
      plan.pop_front();
    }
    if (plan.size()== 0){

      cout << "Se completó el plan \n";
      hayPlan = false;
    }
  }
  else {

    // Incluir aquí la implementación del nivel 4

  }

	return accion;
}

int ComportamientoJugador::interact(Action accion, int valor)
{
	return false;
}