# Nome do executável final
TARGET = ./build/BattleTeam

# Diretórios
SRC_DIR = ./src
SDL_INCLUDE_DIR = ./SDL2/x86_64-w64-mingw32/include/SDL2
SDL_LIB_DIR = ./SDL2/x86_64-w64-mingw32/lib
SDL_TTF_INCLUDE_DIR = ./SDL2_ttf/x86_64-w64-mingw32/include/SDL2
SDL_TTF_LIB_DIR = ./SDL2_ttf/x86_64-w64-mingw32/lib

# Arquivo fonte
SRCS = $(SRC_DIR)/main.c

# Flags do compilador
CFLAGS = -I$(SDL_INCLUDE_DIR) -I$(SDL_TTF_INCLUDE_DIR)

# Flags do linker
LDFLAGS = -L$(SDL_LIB_DIR) -L$(SDL_TTF_LIB_DIR) -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

# Comando de compilação
$(TARGET): $(SRCS)
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS) $(LDFLAGS)

# Limpeza dos arquivos gerados
clean:
	rm -f $(TARGET)

