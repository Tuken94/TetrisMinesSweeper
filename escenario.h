#ifndef ESCENARIO_H_INCLUDED
#define ESCENARIO_H_INCLUDED

#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define COLUMNAS       10
#define FILAS          20
#define CELDA_SIZE     40
#define PREVIEW_SIZE   20
#define PREVIEW_MARGIN 10
#define NUM_SIGUIENTES  4

typedef enum {
    CELDA_VACIA=0,
    CELDA_BLOQUEADA,
    MINA,
    CELDA_NUMERO
} EstadoCelda;

typedef struct {
    EstadoCelda estado;
    bool        tiene_mina;
    int         minas_adyacentes;
    Color       color;          // color de la pieza que la ocup¢
} Celda;

//funciones
//void LoadearTexturas();

void InitTablero();

void DibujarTablero();

int  GetTableroX();

int  GetTableroY();

bool EsCeldaLibre(int x, int y); // x=columna, y=fila

void BloquearCelda(int x, int y, Color color);

//void Unlodear();


#endif // ESCENARIO_H_INCLUDED
