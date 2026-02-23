#ifndef ESCENARIO_H_INCLUDED
#define ESCENARIO_H_INCLUDED

#include "raylib.h"

#define TERRENO_ALTO 10
#define TERRENO_ANCHO 15

typedef struct {
    Texture2D fondo;
    Texture2D borde;
    Texture2D patron;
} Interfaz;

void DibujarInterface();

void Unlodear();

#endif // ESCENARIO_H_INCLUDED
