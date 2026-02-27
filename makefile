# =====================================================
#               CONFIGURAÇÕES DO PROJETO
# =====================================================

TARGET = app
CC = gcc

SRC_DIR   = src
INC_DIR   = include
BUILD_DIR = build
OBJ_DIR   = $(BUILD_DIR)/obj
BIN_DIR   = $(BUILD_DIR)/bin

# =====================================================
#               GTK CONFIG
# =====================================================

GTK_CFLAGS = `pkg-config --cflags gtk+-3.0`
GTK_LIBS   = `pkg-config --libs gtk+-3.0`

# =====================================================
#               FLAGS DE COMPILAÇÃO
# =====================================================

BASE_FLAGS    = -Wall -Wextra -I$(INC_DIR)
DEBUG_FLAGS   = -g -DDEBUG
RELEASE_FLAGS = -O2

CFLAGS = $(BASE_FLAGS) $(GTK_CFLAGS)

# =====================================================
#               ARQUIVOS
# =====================================================

SRC  = $(wildcard $(SRC_DIR)/*.c)
OBJ  = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
EXEC = $(BIN_DIR)/$(TARGET)

# =====================================================
#               REGRAS PRINCIPAIS
# =====================================================

all: release

debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(EXEC)

release: CFLAGS += $(RELEASE_FLAGS)
release: $(EXEC)

# =====================================================
#               LINKAGEM FINAL
# =====================================================

$(EXEC): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJ) -o $(EXEC) $(GTK_LIBS)
	@echo "Build concluído -> $(EXEC)"

# =====================================================
#               COMPILAÇÃO DOS OBJETOS
# =====================================================

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# =====================================================
#               LIMPEZA
# =====================================================

clean:
	rm -rf $(BUILD_DIR)
	@echo "Arquivos removidos."

rebuild: clean all

# =====================================================
#               EXECUÇÃO
# =====================================================

run: all
	./$(EXEC)