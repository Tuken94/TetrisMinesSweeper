# TetrisMinesSweeper

> Un híbrido entre Tetris y Buscaminas.

 **Español** | [English](README.md) | [Português](README.pt.md)

![Estado](https://img.shields.io/badge/estado-WIP%20%2F%20prototipo-orange)
![Lenguaje](https://img.shields.io/badge/lenguaje-C-blue)
![Plataforma](https://img.shields.io/badge/plataforma-Windows%20%7C%20Linux-lightgrey)
![Licencia](https://img.shields.io/badge/licencia-MIT-green)

TetrisMinesSweeper es un juego de PC que fusiona dos clásicos:

- **Tetris**: las piezas de siempre caen desde arriba. Las mueves, las rotas, intentas colocarlas bien.
- **Buscaminas**: cada pieza trae ocultas una o varias minas. Al aterrizar, sus celdas pasan a formar parte del tablero como casillas de buscaminas, mostrando los números de minas adyacentes a su alrededor.

La clave del juego es que **una línea no se elimina simplemente llenándola**. Primero hay que desbloquear todas las casillas blancas de esa fila, es decir, las que no contienen mina. Explotar una mina o no gestionar bien el tablero te penaliza. La puntuación combina la velocidad y eficiencia del Tetris con la precisión del Buscaminas.

---

## Estado del proyecto

**Prototipo en desarrollo.** Lo que está implementado actualmente:

- [x] Tablero 10×20 centrado en pantalla
- [x] Las 7 piezas estándar del Tetris con sus colores
- [x] Movimiento y rotación de piezas
- [x] Estructura de celdas con campos de mina y número de adyacentes
- [x] Pantallas básicas: Logo → Título → Juego → Final

Lo que falta (work in progress):

- [ ] Colisión de piezas con el suelo y entre piezas
- [ ] Caída automática por gravedad
- [ ] Asignación de minas al generar cada pieza
- [ ] Actualización de números adyacentes al aterrizar
- [ ] Lógica de desbloqueo de casillas y eliminación de líneas
- [ ] Sistema de puntuación
- [ ] Pantalla siguiente pieza / pieza en espera
- [ ] Niveles y progresión
- [ ] Menus
- [ ] Interfaz
- [ ] ArtWork (assets)

---

## Compilación

### Requisitos

- [raylib](https://www.raylib.com/) (probado con raylib 4.x o superior)
- Compilador C compatible con C99 o superior (`gcc` en Linux, MinGW en Windows)
- [Code::Blocks](https://www.codeblocks.org/) con el compilador configurado

### Windows (Code::Blocks)

1. Clona o descarga el repositorio.
2. Abre el archivo `.cbp` con Code::Blocks.
3. Asegúrate de que la ruta a raylib está configurada correctamente en las opciones del proyecto:
   - **Build Options → Search directories**: ruta a `raylib/include`
   - **Build Options → Linker settings**: `raylib`, `opengl32`, `gdi32`, `winmm`
4. Compila y ejecuta con `F9`.

### Linux (línea de comandos)

```bash
gcc main.c escenario.c pieza.c -o tetris_mines \
    -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
./tetris_mines
```

> En algunas distribuciones puede ser necesario instalar raylib desde los repositorios o compilarla desde fuente: https://github.com/raysan5/raylib

---

## Estructura del proyecto

```
TetrisMinesSweeper/
├── main.c          # Bucle principal y gestión de pantallas
├── escenario.h     # Definición del tablero, celdas y constantes
├── escenario.c     # Inicialización y dibujado del tablero
├── pieza.h         # Definición de piezas y bloques
├── pieza.c         # Lógica de piezas: init, movimiento, rotación
└── README.md
```

---

## Constantes principales

| Constante | Valor | Descripción |
|---|---|---|
| `COLUMNAS` | 10 | Ancho del tablero en celdas |
| `FILAS` | 20 | Alto del tablero en celdas |
| `CELDA_SIZE` | 40px | Tamaño en píxeles de cada celda |
| `PIEZA_BLOQUES` | 4 | Bloques por pieza |
| `PIEZA_TIPOS` | 7 | Número de tipos de pieza (I O T S Z J L) |

---

## Licencia

Este proyecto está bajo la licencia **MIT**. Puedes usarlo, modificarlo y distribuirlo libremente siempre que mantengas el aviso de copyright original.

```
MIT License — Copyright (c) 2026 Tuken
```

---

## Créditos

- Construido con [raylib](https://www.raylib.com/) de Ramon Santamaria [@raysan5](https://x.com/raysan5?lang=es)
- Inspirado en Tetris y Minesweeper
- La idea original se inspiró en [Itch.io](https://kertisjones.itch.io/tetrisweeper) del usuario Kertis Jones [@KertisJones](https://x.com/KertisJones), quien hizo esta fusión antes que yo