#include "tetris.h"

#define GRAVEDAD_INTERVALO  1.0f
#define SOFTDROP_INTERVALO  0.05f
#define LATERAL_INTERVALO   0.08f

static float tiempoGravedad = 0.0f;
static float tiempoSoftDrop = 0.0f;
static float tiempoLateral  = 0.0f;
static int   tipoGuardado   = -1;   // -1 = vac¡o

void GuardarPieza(Pieza* p){
    int tipoActual = GetTipoPieza(p);
    if (tipoGuardado == -1){
        // No hay pieza guardada: guardar y pasar a la siguiente
        tipoGuardado = tipoActual;
        InitPieza(p);
    } else {
        // Hay pieza guardada: intercambiar
        int tmp = tipoGuardado;
        tipoGuardado = tipoActual;
        InitPiezaTipo(p, tmp);
    }
}

int GetTipoGuardado(){ return tipoGuardado; }

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
    tiempoLateral  = 0.0f;
    InitPieza(p);
}

void ActualizarJuego(Pieza* p, float delta){

    // Guardar pieza
    if (IsKeyPressed(KEY_LEFT_SHIFT) || IsKeyPressed(KEY_RIGHT_SHIFT)){
        GuardarPieza(p);
        return;
    }

    // Movimiento lateral
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)){
        tiempoLateral += delta;
        if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A) || tiempoLateral >= LATERAL_INTERVALO){
            tiempoLateral = 0.0f;
            if (PuedeMoverse(p, -1, 0)) MoverPieza(p, -1, 0);
        }
    } else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)){
        tiempoLateral += delta;
        if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D) || tiempoLateral >= LATERAL_INTERVALO){
            tiempoLateral = 0.0f;
            if (PuedeMoverse(p,  1, 0)) MoverPieza(p,  1, 0);
        }
    } else {
        tiempoLateral = 0.0f;
    }

    // Bajada instant nea (hard drop)
    if (IsKeyPressed(KEY_SPACE)){
        while (PuedeMoverse(p, 0, 1)) MoverPieza(p, 0, 1);
        BloquearPieza(p);
        return;
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
    if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)){
        int cont = 0;
        while (!PuedeRotar(p) && cont < 3){
            MoverPieza(p, -1, 0);
            cont++;
        }
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
