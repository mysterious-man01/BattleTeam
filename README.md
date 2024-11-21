# 🛡️ BattleTeam 🛡️



https://github.com/user-attachments/assets/f69fd313-76c8-49e3-8116-aed83c6f9abf



## 🎮 Descrição

**BattleTeam** é um jogo desenvolvido para a disciplina de Computabilidade e Complexidade de Algoritmos no 6º Semestre do curso de Ciência da Computação na UDF. O jogo tem como objetivo defender uma área (elemento verde) dos inimigos (elementos vermelhos), o jogador (elementos em azul) deve defender podendo se mover livremente pela tela (area de jogo).  

## 👥 Participantes

- 👩‍🏫 **Professora:** [Kadidja Valéria](https://github.com/Kadidjah)  
- 👤 [**João Pedro Coutinho**](https://github.com/mysterious-man01) | RGM: 29982588 

## 💻 Tecnologias

- **C**
- **[SDL2](https://github.com/libsdl-org/SDL) e [SDL_ttl](https://github.com/libsdl-org/SDL_ttf)** (bibliotecas multimidia necessárias para renderização)

## 📋 Instalação e Execução

### **Windows**

### 1. Download
Baixe o arquivo [BattleTeam.zip](https://github.com/mysterious-man01/BattleTeam/releases/tag/1.0) e extraia.

### 2. Execute o arquivo
Depois de extrair, entre na pasta **BattleTeam** e execute o programa **BattleTeam.exe**

### ou

### 1. Clone o repositório

clone este repositório:
 
 ```bash
  git clone https://github.com/mysterious-man01/BattleTeam
  ```

### 2. Instale as dependências

instale o compilador C/C++ MinGW-w64:

- [w64devkit](https://github.com/skeeto/w64devkit)

- [winlibs.com](https://winlibs.com)

- [MSYS2](https://www.msys2.org)

Baixe as bibliotecas [SDL](https://github.com/libsdl-org/SDL/releases) e [SDL_ttl](https://github.com/libsdl-org/SDL_ttf/releases) e extraia na raiz do projeto.

### 3. Configure o ambiente de compilação

No arquivo Makefile altere as seguintes linhas se necessário:

 ```bash
SDL_INCLUDE_DIR = ./SDL2/x86_64-w64-mingw32/include/SDL2
SDL_LIB_DIR = ./SDL2/x86_64-w64-mingw32/lib
SDL_TTF_INCLUDE_DIR = ./SDL2_ttf/x86_64-w64-mingw32/include/SDL2
SDL_TTF_LIB_DIR = ./SDL2_ttf/x86_64-w64-mingw32/lib
  ```

Crie uma pasta **build** e cole os arquivos **SDL.dll** e **SDL_ttf.dll** contidos nas pastas das bibliotecas dentro de **build**.

### 4. Compile o código fonte!

Em um terminal aberto no diretório raíz do projeto digite:

 ```bash
  make
  ```

## 🎯 Objetivo

O objetivo deste projeto é desenvolver um jogo utilizando C puro e SDL2, onde o foco está na interação entre entidades dinâmicas (aliados e inimigos), gerenciamento de estados (como seguir, atacar) O projeto visa implementar mecânicas de movimento, detecção de colisões, combate.

## 🎮 Regras (Jogabilidade)

- O objetivo do jogo é defender a área verde dos inimigos.
- Quando um inimigo é eliminado, ele reaparece em algum ponto de alguma das bordas da tela
- Quando um aliado é eliminado, ele reaparece ao redor do cursor do jogador.
- quando a área do objetivo é destruída, ela reaparece em algum ponto aleatório da área de renderização da tela do jogo.
- Os inimigos irão segir o alvo mais próximo seja ele a área verde ou os aliados.
- Os aliados irão seguir o cursor do jogador.
- Quando um inimigo se aproximar do raio de ação do aliado, o mesmo irá atacar.
- Quando um inimigo se aproximar da área verde ou de algum aliado, o mesmo atacará.
- Controles:
  - mouse: Responsável por guiar os aliados.
  - Tecla ESC: Finaliza o jogo.

## ✒️ Checklist de Desenvolvimento

### Definição do Tema

- ✅ cenário de estratégia e sobrevivência, onde o jogador lidera um grupo de aliados para proteger um objetivo principal enquanto enfrenta ondas de inimigos.

### Planejamento

- ✅ 1. Definição do Escopo do jogo.
- ✅ 2. Implementação das Estruturas de Dados das entidades do jogo.
- ✅ 3. Mecânicas de Jogo como os autômatos para os inimigos e aliados.
- ✅ 4. Controle e Física dos elementos do jogo
- ✅ 6. Renderização dos elementos do jogo como inimigos, aliados, o objetivo e o cursor.

### Desenvolvimento

- ✅ Foi utilizado o conceito de modularização onde blocos de códigos foram divididos em funções baseadas em suas respectivas funcionalidades e separadas em arquivos diferêntes para cada escopo funcional. 

### Testes

- ⌛ Foram realizados testes nos sistemas de colizão, renderização, Controles e nos autômatos dos inimigos e aliados.

## 📶 Identificação da Complexidade

O jogo apresenta uma complexidade moderada em termos de lógica e desempenho, considerando elementos como movimentação, colisões, transições de estados e interações entre entidades.