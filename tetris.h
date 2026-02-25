#ifndef TETRIS_H_INCLUDED
#define TETRIS_H_INCLUDED

#include "pieza.h"
#include "escenario.h"

int  GetTipoGuardado();
bool PuedeMoverse(const Pieza* p, int dx, int dy);
bool IntentarRotar(Pieza* p);
void GuardarPieza(Pieza* p);
void BloquearPieza(Pieza* p);
void ActualizarJuego(Pieza* p, float dt);

#endif // TETRIS_H_INCLUDED
