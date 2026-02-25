#include "escenario.h"
#include <stdio.h>

/*const char* FONDO="Textures/Background.png";
const char* BORDE="Textures/Border.png";
const char* PATRON="Textures/Pattern02.png";

static Texture2D fondo;
static Texture2D borde;
static Texture2D patron;*/

static Celda tablero[FILAS][COLUMNAS];
static int tableroX = 0;
static int tableroY = 0;

/*void LoadearTexturas(){
    fondo = LoadTexture(FONDO);
    borde = LoadTexture(BORDE);
    patron = LoadTexture(PATRON);
}*/

void InitTablero(){
    tableroX = GetScreenWidth()  / 2 - (COLUMNAS * CELDA_SIZE) / 2;
    tableroY = GetScreenHeight() / 2 - (FILAS    * CELDA_SIZE) / 2;

    for (int i = 0; i < FILAS; i++){
        for (int j = 0; j < COLUMNAS; j++){
            tablero[i][j].estado           = CELDA_VACIA;
            tablero[i][j].tiene_mina       = false;
            tablero[i][j].minas_adyacentes = 0;
            tablero[i][j].color            = BLACK;
        }
    }
}

void DibujarTablero(){
    /*Vector2 centro = {GetScreenWidth()/2 - fondo.width/1.35, GetScreenHeight()/2 - fondo.width*1.35};
    Vector2 centro2 = {GetScreenWidth()/2, GetScreenHeight()/2};
    Vector2 cero = {0, 0};*/

    DrawRectangle(tableroX, tableroY, COLUMNAS * CELDA_SIZE, FILAS * CELDA_SIZE, BLACK);

    // Panel de siguientes a la derecha del tablero
    int panelX     = tableroX + COLUMNAS * CELDA_SIZE + 20;
    int panelAncho  = 4 * PREVIEW_SIZE + PREVIEW_MARGIN * 2;
    int cajaAlto    = 4 * PREVIEW_SIZE + PREVIEW_MARGIN * 2;
    int panelAlto   = NUM_SIGUIENTES * (cajaAlto + PREVIEW_MARGIN) - PREVIEW_MARGIN;
    DrawRectangle(panelX, tableroY, panelAncho, panelAlto, (Color){30, 30, 30, 255});
    DrawRectangleLinesEx(
        (Rectangle){(float)panelX, (float)tableroY, (float)panelAncho, (float)panelAlto},
        2, (Color){80, 80, 80, 255});

    // Panel de guardada a la izquierda del tablero
    int panelAncho2 = 4 * PREVIEW_SIZE + PREVIEW_MARGIN * 2;
    int panelAlto2  = 4 * PREVIEW_SIZE + PREVIEW_MARGIN * 2;
    int panelX2     = tableroX - panelAncho2 - 20;
    DrawRectangle(panelX2, tableroY, panelAncho2, panelAlto2, (Color){30, 30, 30, 255});
    DrawRectangleLinesEx(
        (Rectangle){(float)panelX2, (float)tableroY, (float)panelAncho2, (float)panelAlto2},
        2, (Color){80, 80, 80, 255});

    for (int i = 0; i < FILAS; i++){
        for (int j = 0; j < COLUMNAS; j++){
            int px = tableroX + j * CELDA_SIZE;
            int py = tableroY + i * CELDA_SIZE;

            Celda* c = &tablero[i][j];

            if (c->estado != CELDA_VACIA){
                DrawRectangle(px, py, CELDA_SIZE, CELDA_SIZE, c->color);

                if (c->estado == CELDA_NUMERO && c->minas_adyacentes > 0){
                    char buf[3];
                    snprintf(buf, sizeof(buf), "%d", c->minas_adyacentes);
                    int fs = CELDA_SIZE / 2;
                    DrawText(buf,
                             px + (CELDA_SIZE - MeasureText(buf, fs)) / 2,
                             py + (CELDA_SIZE - fs) / 2,
                             fs, WHITE);
                }
            }

            DrawRectangleLinesEx(
                (Rectangle){(float)px, (float)py, CELDA_SIZE, CELDA_SIZE},
                1, (Color){80, 80, 80, 255});
        }
    }
}

int GetTableroX(){ return tableroX; }
int GetTableroY(){ return tableroY; }

// Devuelve true si (x,y) est  dentro del tablero y la celda est  vac¡a
bool EsCeldaLibre(int x, int y){
    if (x < 0 || x >= COLUMNAS || y < 0 || y >= FILAS) return false;
    return tablero[y][x].estado == CELDA_VACIA;
}

// Marca una celda como bloqueada con el color de la pieza
void BloquearCelda(int x, int y, Color color){
    tablero[y][x].estado = CELDA_BLOQUEADA;
    tablero[y][x].color  = color;
}

/*void Unlodear(){
    UnloadTexture(fondo);
    UnloadTexture(borde);
    UnloadTexture(patron);
}*/
