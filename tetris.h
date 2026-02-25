#ifndef TETRIS_H_INCLUDED
#define TETRIS_H_INCLUDED

#include "pieza.h"
#include "escenario.h"

#define GRAVEDAD_FRAMES 60   // frames entre cada bajada autom tica (1 segundo a 60fps)

bool PuedeMoverse(const Pieza* p, int dx, int dy);

bool PuedeRotar(const Pieza* p);

void BloquearPieza(Pieza* p);

void ActualizarJuego(Pieza* p, float delta);

#endif // TETRIS_H_INCLUDED
