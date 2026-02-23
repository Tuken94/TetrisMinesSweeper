#ifndef PIEZA_H_INCLUDED
#define PIEZA_H_INCLUDED

#include "raylib.h"
#include "escenario.h"
#include <time.h>

#define PIEZA_BLOQUES 4   // toda pieza ocupa 4 bloques
#define PIEZA_TIPOS   7

// Forma de una pieza: 4 bloques, cada uno con offset (x, y) respecto al origen
typedef struct {
    int x, y;
} Bloque;

typedef struct {
    Bloque  bloques[PIEZA_BLOQUES];
    Color   color;
    int     posX;   // columna del tablero donde est  el origen
    int     posY;   // fila del tablero donde est  el origen
} Pieza;

//funciones
void InitPieza(Pieza* p);
void ActualizarPieza(Pieza* p);
void DibujarPieza(const Pieza* p);
void MoverPieza(Pieza* p, int dx, int dy);
void RotarPieza(Pieza* p);

#endif // PIEZA_H_INCLUDED
