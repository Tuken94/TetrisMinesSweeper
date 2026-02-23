#include "tetris.h"

static int frameGravedad = 0;

// Comprueba si la pieza puede moverse (dx, dy) sin salir del tablero ni chocar
bool PuedeMoverse(const Pieza* p, int dx, int dy){
    for (int i = 0; i < PIEZA_BLOQUES; i++){
        int nx = p->posX + p->bloques[i].x + dx;
        int ny = p->posY + p->bloques[i].y + dy;
        if (!EsCeldaLibre(nx, ny)) return false;
    }
    return true;
}

// Comprueba si la pieza puede rotar calculando los bloques rotados
bool PuedeRotar(const Pieza* p){
    // Replicamos la l¢gica de RotarPieza para obtener las posiciones resultantes
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

// Escribe la pieza en el tablero y genera una nueva
void BloquearPieza(Pieza* p){
    for (int i = 0; i < PIEZA_BLOQUES; i++){
        int x = p->posX + p->bloques[i].x;
        int y = p->posY + p->bloques[i].y;
        BloquearCelda(x, y, p->color);
    }
    frameGravedad = 0;
    InitPieza(p);
}

// Input + gravedad + bloqueo autom tico
void ActualizarJuego(Pieza* p){
    // Movimiento lateral
    if (IsKeyPressed(KEY_LEFT)  || IsKeyPressed(KEY_A)){
        if (PuedeMoverse(p, -1, 0)) MoverPieza(p, -1, 0);
    }
    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)){
        if (PuedeMoverse(p,  1, 0)) MoverPieza(p,  1, 0);
    }

    // Bajada r pida
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)){
        if (PuedeMoverse(p, 0, 1)) MoverPieza(p, 0, 1);
    }

    // Rotaci¢n
    if (IsKeyPressed(KEY_Q)){
        if (PuedeRotar(p)) RotarPieza(p);
    }

    // Gravedad autom tica
    frameGravedad++;
    if (frameGravedad >= GRAVEDAD_FRAMES){
        frameGravedad = 0;
        if (PuedeMoverse(p, 0, 1)){
            MoverPieza(p, 0, 1);
        } else {
            BloquearPieza(p);
        }
    }
}
