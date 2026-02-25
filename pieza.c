#include "pieza.h"
#include "tetris.h"

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

// --- Sistema de doble bolsa ---
static int bolsa[PIEZA_TIPOS];
static int bolsaSiguiente[PIEZA_TIPOS];
static int indiceBolsa = 0;
static int siguientes[NUM_SIGUIENTES];
static bool inicializado = false;

static void BajarBolsa(int* b){
    for (int i = 0; i < PIEZA_TIPOS; i++) b[i] = i;
    for (int i = PIEZA_TIPOS - 1; i > 0; i--){
        int j = rand() % (i + 1);
        int tmp = b[i]; b[i] = b[j]; b[j] = tmp;
    }
}

static int SiguienteDeBolsa(){
    if (indiceBolsa >= PIEZA_TIPOS){
        // La bolsa actual se agot¢: la siguiente pasa a ser la actual
        for (int i = 0; i < PIEZA_TIPOS; i++) bolsa[i] = bolsaSiguiente[i];
        BajarBolsa(bolsaSiguiente);
        indiceBolsa = 0;
    }
    return bolsa[indiceBolsa++];
}

static void InitBolsas(){
    BajarBolsa(bolsa);
    BajarBolsa(bolsaSiguiente);
    indiceBolsa = 0;
    for (int i = 0; i < NUM_SIGUIENTES; i++) siguientes[i] = SiguienteDeBolsa();
}

// --- Funciones p£blicas ---

void InitPieza(Pieza* p){
    if (!inicializado){ InitBolsas(); inicializado = true; }

    // La pieza actual es la primera de la cola
    int tipo = siguientes[0];

    // Desplazamos la cola y a¤adimos la siguiente
    for (int i = 0; i < NUM_SIGUIENTES - 1; i++) siguientes[i] = siguientes[i+1];
    siguientes[NUM_SIGUIENTES - 1] = SiguienteDeBolsa();

    for (int i = 0; i < PIEZA_BLOQUES; i++) p->bloques[i] = FORMAS[tipo][i];
    p->color = COLORES[tipo];
    p->posX  = COLUMNAS / 2 - 2;
    p->posY  = 0;
}

// Devuelve el tipo de pieza comparando sus bloques en estado inicial
int GetTipoPieza(const Pieza* p){
    for (int t = 0; t < PIEZA_TIPOS; t++){
        if (p->color.r == COLORES[t].r &&
            p->color.g == COLORES[t].g &&
            p->color.b == COLORES[t].b) return t;
    }
    return 0;
}

// Inicializa la pieza con un tipo concreto sin consumir la bolsa (para intercambio)
void InitPiezaTipo(Pieza* p, int tipo){
    for (int i = 0; i < PIEZA_BLOQUES; i++) p->bloques[i] = FORMAS[tipo][i];
    p->color = COLORES[tipo];
    p->posX  = COLUMNAS / 2 - 2;
    p->posY  = 0;
}

void DibujarGuardada(){
    int tableroX = GetTableroX();
    int tableroY = GetTableroY();

    int panelAncho = 4 * PREVIEW_SIZE + PREVIEW_MARGIN * 2;
    int panelAlto  = 4 * PREVIEW_SIZE + PREVIEW_MARGIN * 2;
    int panelX     = tableroX - panelAncho - 20;

    int tipo = GetTipoGuardado();
    if (tipo == -1) return;   // nada guardado, no dibujamos piezas

    for (int i = 0; i < PIEZA_BLOQUES; i++){
        int px = panelX + PREVIEW_MARGIN + FORMAS[tipo][i].x * PREVIEW_SIZE;
        int py = tableroY + PREVIEW_MARGIN + FORMAS[tipo][i].y * PREVIEW_SIZE;
        DrawRectangle(px, py, PREVIEW_SIZE, PREVIEW_SIZE, COLORES[tipo]);
        DrawRectangleLinesEx(
            (Rectangle){(float)px, (float)py, PREVIEW_SIZE, PREVIEW_SIZE},
            1, (Color){80, 80, 80, 255});
    }
}

void MoverPieza(Pieza* p, int dx, int dy){
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
        DrawRectangleLinesEx(
            (Rectangle){(float)px, (float)py, CELDA_SIZE, CELDA_SIZE},
            1, (Color){80, 80, 80, 255});
    }
}

void DibujarSiguientes(){
    int tableroX = GetTableroX();
    int tableroY = GetTableroY();

    // Panel a la derecha del tablero
    int panelX = tableroX + COLUMNAS * CELDA_SIZE + 20;
    int cajaAncho = 4 * PREVIEW_SIZE + PREVIEW_MARGIN * 2;
    int cajaAlto  = 4 * PREVIEW_SIZE + PREVIEW_MARGIN * 2;
    int panelAlto = NUM_SIGUIENTES * (cajaAlto + PREVIEW_MARGIN) - PREVIEW_MARGIN;

    for (int n = 0; n < NUM_SIGUIENTES; n++){
        int tipo = siguientes[n];
        int offsetY = tableroY + n * (cajaAlto + PREVIEW_MARGIN);

        for (int i = 0; i < PIEZA_BLOQUES; i++){
            int px = panelX + PREVIEW_MARGIN + FORMAS[tipo][i].x * PREVIEW_SIZE;
            int py = offsetY + PREVIEW_MARGIN + FORMAS[tipo][i].y * PREVIEW_SIZE;
            DrawRectangle(px, py, PREVIEW_SIZE, PREVIEW_SIZE, COLORES[tipo]);
            DrawRectangleLinesEx(
                (Rectangle){(float)px, (float)py, PREVIEW_SIZE, PREVIEW_SIZE},
                1, (Color){80, 80, 80, 255});
        }
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
    for (int i = 0; i < PIEZA_BLOQUES; i++) p->bloques[i] = rotados[i];
}
