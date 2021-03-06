#include <iostream> 
#include <cstdlib>

#include "../include/posicion.h"
#include "../include/movimiento.h"
#include "../include/reglas.h"
#include "../include/celda.h"
#include "../include/hormiga.h"
#include "../include/vector.h"
#include "../include/mundo.h"


Hormiga::Hormiga(Mundo& mundo, int semilla): direccion_(izquierda), mundo_(&mundo) {
  srand(semilla);
  posicion_actual_.set_x((rand() % mundo_->get_size().filas_) + mundo_->get_size().Xmin);
  posicion_actual_.set_y((rand() % mundo_->get_size().columnas_) + mundo_->get_size().Ymin);
  set_posicion_siguiente();
} //En esta semilla del random

Hormiga::Hormiga(Mundo& mundo, Posicion posicion)
    : direccion_(izquierda), posicion_actual_(posicion), mundo_(&mundo) {
  set_posicion_siguiente();
}

Hormiga::Hormiga(Mundo& mundo): direccion_(izquierda), mundo_(&mundo) {
  posicion_actual_.set_x(0);
  posicion_actual_.set_y(0);
  //mundo_->get_tablero()[0][0]->set_color(1);
  set_posicion_siguiente();
}


Direcciones Hormiga::get_direccion(void) const {
  return direccion_;
}
Posicion Hormiga::get_posicion_actual(void) const {
  return posicion_actual_;
}
Posicion Hormiga::get_posicion_siguiente(void) const {
  return posicion_siguiente_;
}
Regla Hormiga::get_movimiento(void) const {
  return movimiento_;
}
Mundo* Hormiga::get_mundo(void) const {
  return mundo_;
}

void Hormiga::set_direccion(const Direcciones& kNewDireccion) {
  direccion_ = kNewDireccion;
}
void Hormiga::set_posicion_actual(const Posicion& kNewPosicion) {
  posicion_actual_ = kNewPosicion;
}
void Hormiga::set_posicion_actual(const int& i, const int& j) {
  posicion_actual_.set_x(i);
  posicion_actual_.set_y(j);
}
void Hormiga::set_posicion_siguiente(const Posicion& kNewPosicion) {
  posicion_siguiente_ = kNewPosicion;
}
void Hormiga::set_posicion_siguiente(void) {
  Movimiento move;
  posicion_siguiente_ = *move.get_next_pos(direccion_);  
  posicion_siguiente_ = get_posicion_actual() + posicion_siguiente_;
}
void Hormiga::set_movimiento(const Regla& kNewMovimiento) {
  movimiento_ = kNewMovimiento;
}
void Hormiga::set_mundo(Mundo* const& kNewMundo) {
  mundo_ = kNewMundo;
}


void Hormiga::actualizar_posiciones(const Posicion& kNewPosicion) {
  set_posicion_actual(kNewPosicion);
  set_posicion_siguiente();
}
void Hormiga::actualizar_posiciones(const int& i, const int& j) {
  set_posicion_actual(i, j);
  set_posicion_siguiente();
}

void Hormiga::cerebro(void) {
  Regla regla;
  /*if (regla.regla1(this)) {
    return;
  } else */if (regla.regla2(this)) {
    return;
  } else if (regla.regla3(this)) {
    return;
  }
}

std::ostream& operator<<(std::ostream& os, const Hormiga& kHormiga) {
  if (kHormiga.get_direccion() == arriba) {
    return os << "⬆️ ";
  } else if (kHormiga.get_direccion() == arriba_derecha) {
    return os << "↗ ";
  } else if (kHormiga.get_direccion() == derecha) {
    return os << "➡️ ";
  } else if (kHormiga.get_direccion() == abajo_derecha) {
    return os << "↘ ";
  } else if (kHormiga.get_direccion() == abajo) {
    return os << "⬇️ ";
  } else if (kHormiga.get_direccion() == abajo_izquierda) {
    return os << "↙ ";
  } else if (kHormiga.get_direccion() == izquierda) {
    return os << "⬅️ ";
  } else if (kHormiga.get_direccion() == arriba_izquierda) {
    return os << "↖ ";
  } else return os;
}
