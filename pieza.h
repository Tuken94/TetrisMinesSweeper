#ifndef PIEZA_H_INCLUDED
#define PIEZA_H_INCLUDED

#include "raylib.h"
#include "escenario.h"
#include <time.h>

#define PIEZA_BLOQUES 4
#define PIEZA_TIPOS   7

typedef struct {
    int x, y;
} Bloque;

typedef struct {
    Bloque bloques[PIEZA_BLOQUES];
    Color  color;
    int    posX;   // columna del tablero donde est  el origen
    int    posY;   // fila del tablero donde est  el origen
} Pieza;

void InitPieza(Pieza* p);
void InitPiezaTipo(Pieza* p, int tipo);
int  GetTipoPieza(const Pieza* p);
void DibujarPieza(const Pieza* p);
void DibujarSiguientes();
void DibujarGuardada();
void MoverPieza(Pieza* p, int dx, int dy);
void RotarPieza(Pieza* p);

#endif // PIEZA_H_INCLUDED
