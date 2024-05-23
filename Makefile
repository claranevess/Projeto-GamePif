# Nome do executável
EXEC = jogo

# Diretórios
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# Compilador e flags
CC = gcc
CFLAGS = -Wall -I$(INC_DIR)

# Arquivos fonte e objetos
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Regra padrão
all: $(OBJ_DIR) $(EXEC)

# Regra para criar o diretório de objetos
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Regra para criar o executável
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

# Regra para compilar os arquivos fonte
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar os arquivos compilados
clean:
	rm -rf $(OBJ_DIR) $(EXEC)

# Regra para rodar o jogo
run: all
	./$(EXEC)