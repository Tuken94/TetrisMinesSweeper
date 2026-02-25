#include "tetris.h"

#define GRAVEDAD_INTERVALO  1.0f    // segundos entre bajadas autom ticas
#define SOFTDROP_INTERVALO  0.05f   // segundos entre bajadas con S/DOWN mantenido

static float tiempoGravedad = 0.0f;
static float tiempoSoftDrop = 0.0f;

bool PuedeMoverse(const Pieza* p, int dx, int dy){
    for (int i = 0; i < PIEZA_BLOQUES; i++){
        int nx = p->posX + p->bloques[i].x + dx;
        int ny = p->posY + p->bloques[i].y + dy;
        if (!EsCeldaLibre(nx, ny)) return false;
    }
    return true;
}

bool PuedeRotar(const Pieza* p){
    int minX = p->bloques[0].x, minY = p->bloques[0].y;
    int maxX = p->bloques[0].x, maxY = p->bloques[0].y;
    for (int i = 1; i < PIEZA_BLOQUES; i++){
        if (p->bloques[i].x < minX) minX = p->bloques[i].x;
        if (p->bloques[i].y < minY) minY = p->bloques[i].y;
        if (p->bloques[i].x > maxX) maxX = p->bloques[i].x;
        if (p->bloques[i].y > maxY) maxY = p->bloques[i].y;
    }

    for (int i = 0; i < PIEZA_BLOQUES; i++){
        int rx = p->bloques[i].x - minX;
        int ry = p->bloques[i].y - minY;
        int nx = p->posX + (maxY - minY) - ry;
        int ny = p->posY + rx;
        if (!EsCeldaLibre(nx, ny)) return false;
    }
    return true;
}

void BloquearPieza(Pieza* p){
    for (int i = 0; i < PIEZA_BLOQUES; i++){
        int x = p->posX + p->bloques[i].x;
        int y = p->posY + p->bloques[i].y;
        BloquearCelda(x, y, p->color);
    }
    tiempoGravedad = 0.0f;
    tiempoSoftDrop = 0.0f;
    InitPieza(p);
}

void ActualizarJuego(Pieza* p, float delta){

    // Movimiento lateral
    if (IsKeyDown(KEY_LEFT)  || IsKeyDown(KEY_A)){
        if (PuedeMoverse(p, -1, 0)) MoverPieza(p, -1, 0);
    }
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)){
        if (PuedeMoverse(p,  1, 0)) MoverPieza(p,  1, 0);
    }

    // Bajada instant nea (hard drop)
    if (IsKeyPressed(KEY_SPACE)){
        while (PuedeMoverse(p, 0, 1)) MoverPieza(p, 0, 1);
        BloquearPieza(p);
        return;   // saltamos gravedad este frame
    }

    // Soft drop (manteniendo S/DOWN)
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)){
        tiempoSoftDrop += delta;
        if (tiempoSoftDrop >= SOFTDROP_INTERVALO){
            tiempoSoftDrop = 0.0f;
            if (PuedeMoverse(p, 0, 1)) MoverPieza(p, 0, 1);
        }
    } else {
        tiempoSoftDrop = 0.0f;
    }

    // Rotaci¢n
    if (IsKeyPressed(KEY_Q)){
        if (PuedeRotar(p)) RotarPieza(p);
    }

    // Gravedad autom tica
    tiempoGravedad += delta;
    if (tiempoGravedad >= GRAVEDAD_INTERVALO){
        tiempoGravedad = 0.0f;
        if (PuedeMoverse(p, 0, 1)){
            MoverPieza(p, 0, 1);
        } else {
            BloquearPieza(p);
        }
    }
}
