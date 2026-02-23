# TetrisMinesSweeper

> Um híbrido entre Tetris e Campo Minado.

[Español](README.es.md) | [English](README.md) | **Português**

![Estado](https://img.shields.io/badge/estado-WIP%20%2F%20prot%C3%B3tipo-orange)
![Linguagem](https://img.shields.io/badge/linguagem-C-blue)
![Plataforma](https://img.shields.io/badge/plataforma-Windows%20%7C%20Linux-lightgrey)
![Licença](https://img.shields.io/badge/licen%C3%A7a-MIT-green)

TetrisMinesSweeper é um jogo para PC que une dois clássicos:

- **Tetris**: as peças de sempre caem de cima. Você as move, rotaciona e tenta posicioná-las bem.
- **Campo Minado**: cada peça carrega uma ou mais minas escondidas. Ao pousar, suas células passam a fazer parte do tabuleiro como casas do Campo Minado, exibindo o número de minas adjacentes ao redor.

O ponto central do jogo é que **uma linha não é eliminada apenas por ser preenchida**. Primeiro é preciso desbloquear todas as casas brancas dessa linha — as que não contêm mina. Detonar uma mina ou não gerenciar bem o tabuleiro resulta em penalização. A pontuação combina a velocidade e eficiência do Tetris com a precisão do Campo Minado.

---

## Estado do Projeto

**Protótipo em desenvolvimento.** O que já está implementado:

- [x] Tabuleiro 10×20 centralizado na tela
- [x] As 7 peças padrão do Tetris com suas cores
- [x] Movimentação e rotação de peças
- [x] Estrutura de células com campos de mina e contagem de minas adjacentes
- [x] Telas básicas: Logo → Título → Jogo → Final

O que ainda falta (work in progress):

- [ ] Detecção de colisão com o chão e entre peças
- [ ] Queda automática por gravidade
- [ ] Atribuição de minas ao gerar cada peça
- [ ] Atualização dos números adjacentes ao pousar
- [ ] Lógica de desbloqueio de casas e eliminação de linhas
- [ ] Sistema de pontuação
- [ ] Exibição da próxima peça / peça guardada
- [ ] Níveis e progressão
- [ ] Menus
- [ ] Interface
- [ ] Arte (assets)

---

## Compilação

### Requisitos

- [raylib](https://www.raylib.com/) (testado com raylib 4.x ou superior)
- Compilador C compatível com C99 ou superior (`gcc` no Linux, MinGW no Windows)
- [Code::Blocks](https://www.codeblocks.org/) com compilador configurado

### Windows (Code::Blocks)

1. Clone ou baixe o repositório.
2. Abra o arquivo `.cbp` com o Code::Blocks.
3. Certifique-se de que o caminho do raylib está configurado corretamente nas opções do projeto:
   - **Build Options → Search directories**: caminho para `raylib/include`
   - **Build Options → Linker settings**: `raylib`, `opengl32`, `gdi32`, `winmm`
4. Compile e execute com `F9`.

### Linux (linha de comando)

```bash
gcc main.c escenario.c pieza.c -o tetris_mines \
    -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
./tetris_mines
```

> Em algumas distribuições pode ser necessário instalar o raylib pelo gerenciador de pacotes ou compilá-lo a partir do código fonte: https://github.com/raysan5/raylib

---

## Estrutura do Projeto

```
TetrisMinesSweeper/
├── main.c          # Loop principal e gerenciamento de telas
├── escenario.h     # Definição do tabuleiro, células e constantes
├── escenario.c     # Inicialização e renderização do tabuleiro
├── pieza.h         # Definição de peças e blocos
├── pieza.c         # Lógica das peças: init, movimentação, rotação
└── README.md
```

---

## Constantes Principais

| Constante | Valor | Descrição |
|---|---|---|
| `COLUMNAS` | 10 | Largura do tabuleiro em células |
| `FILAS` | 20 | Altura do tabuleiro em células |
| `CELDA_SIZE` | 40px | Tamanho em pixels de cada célula |
| `PIEZA_BLOQUES` | 4 | Blocos por peça |
| `PIEZA_TIPOS` | 7 | Número de tipos de peça (I O T S Z J L) |

---

## Licença

Este projeto está sob a licença **MIT**. Você pode usá-lo, modificá-lo e distribuí-lo livremente, desde que mantenha o aviso de copyright original.

```
MIT License — Copyright (c) 2026 Tuken
```

---

## Créditos

- Desenvolvido com [raylib](https://www.raylib.com/) por Ramon Santamaria [@raysan5](https://x.com/raysan5)
- Inspirado em Tetris e Campo Minado
- O conceito original foi inspirado pelo jogo no [Itch.io](https://kertisjones.itch.io/tetrisweeper) de Kertis Jones [@KertisJones](https://x.com/KertisJones), que fez essa fusão antes de mim