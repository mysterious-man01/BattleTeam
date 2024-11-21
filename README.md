# BattleTeam 🐾 

## 🎮 Descrição

**BattleTeam** é um jogo desenvolvido para a disciplina de Computabilidade e Complexidade de Algoritmos no 6º Semestre do curso de Ciência da Computação na UDF. O jogo tem como objetivo defender uma área (elemento verde) dos inimigos (elementos vermelhos), o jogador (elementos em azul) deve defender podendo se mover livremente pela tela (area de jogo).  

## 🧑‍🤝‍🧑 Participantes

- 👩‍🏫 **Professora:** [Kadidja Valéria](https://github.com/Kadidjah)  
- 👤 [**João Pedro Coutinho**](https://github.com/mysterious-man01) | RGM: 29982588 

## 🚀 Tecnologias

- **C**
- **SDL2 e SDL_ttl** (biblioteca multimidia para renderização)

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

