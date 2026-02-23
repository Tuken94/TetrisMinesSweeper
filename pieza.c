#include "pieza.h"

static const Bloque FORMAS[PIEZA_TIPOS][PIEZA_BLOQUES] = {
    {{0,0},{1,0},{2,0},{3,0}},   // I
    {{0,0},{1,0},{0,1},{1,1}},   // O
    {{1,0},{0,1},{1,1},{2,1}},   // T
    {{1,0},{2,0},{0,1},{1,1}},   // S
    {{0,0},{1,0},{1,1},{2,1}},   // Z
    {{0,0},{0,1},{1,1},{2,1}},   // J
    {{2,0},{0,1},{1,1},{2,1}},   // L
};

static const Color COLORES[PIEZA_TIPOS] = {
    SKYBLUE,    // I
    YELLOW,     // O
    PURPLE,     // T
    GREEN,      // S
    RED,        // Z
    BLUE,       // J
    ORANGE,     // L
};

void InitPieza(Pieza* p){
    int tipo = rand() % 7;

    for (int i = 0; i < PIEZA_BLOQUES; i++){
        p->bloques[i] = FORMAS[tipo][i];
    }
    p->color = COLORES[tipo];
    p->posX  = COLUMNAS / 2 - 2;
    p->posY  = 0;
}



void MoverPieza(Pieza* p, int dx, int dy){ //la hago por separado a Actualizar para luego calcular la colision mas facil
    p->posX += dx;
    p->posY += dy;
}


void DibujarPieza(const Pieza* p){
    int tableroX = GetTableroX();
    int tableroY = GetTableroY();
    for (int i = 0; i < PIEZA_BLOQUES; i++){
        int px = tableroX + (p->posX + p->bloques[i].x) * CELDA_SIZE;
        int py = tableroY + (p->posY + p->bloques[i].y) * CELDA_SIZE;
        DrawRectangle(px, py, CELDA_SIZE, CELDA_SIZE, p->color);
        DrawRectangleLinesEx((Rectangle){(float)px, (float)py, CELDA_SIZE, CELDA_SIZE},1, (Color){80, 80, 80, 255});
    }
}

void RotarPieza(Pieza* p){
    int minX = p->bloques[0].x, minY = p->bloques[0].y;
    int maxX = p->bloques[0].x, maxY = p->bloques[0].y;
    for (int i = 1; i < PIEZA_BLOQUES; i++){
        if (p->bloques[i].x < minX) minX = p->bloques[i].x;
        if (p->bloques[i].y < minY) minY = p->bloques[i].y;
        if (p->bloques[i].x > maxX) maxX = p->bloques[i].x;
        if (p->bloques[i].y > maxY) maxY = p->bloques[i].y;
    }

    Bloque rotados[PIEZA_BLOQUES];
    for (int i = 0; i < PIEZA_BLOQUES; i++){
        int rx = p->bloques[i].x - minX;
        int ry = p->bloques[i].y - minY;
        rotados[i].x = (maxY - minY) - ry;
        rotados[i].y = rx;
    }
    for (int i = 0; i < PIEZA_BLOQUES; i++){
        p->bloques[i] = rotados[i];
    }
}
