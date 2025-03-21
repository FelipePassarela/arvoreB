CC = gcc
CFLAGS =  -std=c11 -Wall -Wextra -Iinclude -g
SRC_DIR = src
OBJ_DIR = build
BIN_DIR = bin

BTREE_SRC = $(wildcard $(SRC_DIR)/btree/node/*.c) $(wildcard $(SRC_DIR)/btree/*.c)
UTILS_SRC = $(wildcard $(SRC_DIR)/utils/*.c)
MAIN_SRC = $(SRC_DIR)/main.c

BTREE_OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(BTREE_SRC))
UTILS_OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(UTILS_SRC))
MAIN_OBJ = $(OBJ_DIR)/main.o

OBJ = $(BTREE_OBJ) $(UTILS_OBJ) $(MAIN_OBJ)

TARGET = $(BIN_DIR)/trab2

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@  -lm

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run: $(TARGET)
	./$(TARGET)

test: all
	@rm -rf test/output
	@mkdir test/output/	
	@for file in test/input/caso_teste_*.txt; do \
		base=$$(basename $$file .txt); \
		echo "Testando $$base..."; \
		./$(TARGET) $$file test/output/$${base}_output.txt; \
	done
	@echo "Comparando resultados..."
	@diff -r test/output/ test/output_corretos/ || (echo "Teste falhou!" && exit 1)

test_gerados: all
	@rm -rf test/output test/input_gerados test/output_gerados
	@mkdir -p test/output test/input_gerados test/output_gerados
	@echo "Gerando casos de teste..."
	@python3 scripts/generate_test_files.py
	@echo "Executando casos de teste gerados..."
	@for file in test/input_gerados/caso_teste_*.txt; do \
		base=$$(basename $$file .txt); \
		echo "Testando $$base..."; \
		./$(TARGET) $$file test/output/$${base}_output.txt; \
	done
	@echo "Comparando resultados..."
	@diff -r -q -Z test/output/ test/output_gerados/ || (echo "Teste falhou!" && exit 1)
	@echo "Testes gerados concluídos com sucesso!"

.PHONY: all clean run