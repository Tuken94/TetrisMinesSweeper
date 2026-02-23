#include  "escenario.h"

const char* FONDO="Textures/Background.png";
const char* BORDE="Textures/Border.png";
const char* PATRON="Textures/Pattern02.png";

Texture2D fondo;
Texture2D borde;
Texture2D patron;

void DibujarInterface(){
    Vector2 centro = {GetScreenWidth()/2 - fondo.width/1.35, GetScreenHeight()/2 - fondo.width*1.35};
    Vector2 centro2 = {GetScreenWidth()/2, GetScreenHeight()/2};
    Vector2 cero = {0, 0};
    fondo = LoadTexture(FONDO);
    borde = LoadTexture(BORDE);
    patron = LoadTexture(PATRON);
    for (int i = 0; i < TERRENO_ALTO; i++){
        for (int j = 0; j < TERRENO_ANCHO; j++){
            int posX = j * patron.width;
            int posY = i * patron.height;
            DrawTextureEx(patron, (Vector2){ posX, posY }, 0, 1, WHITE);
            }
        }
    Rectangle region = { 50, 100, 300, 600};
    Rectangle destino = { centro.x+50*1.35, centro.y+100*1.35, region.width * 1.35, region.height * 1.35 };
    DrawTexturePro(fondo, region, destino, (Vector2){0,0}, 0.0f, WHITE);
    DrawTextureEx(borde, centro, 0, 1.35, WHITE);
}
