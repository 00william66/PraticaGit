# makefile do aço - run and test com unity

# Nomes do projeto e módulo a testar
APP_NAME = app
MODULE_NAME_TEST = LinkedList

# Caminhos das pastas
SRC_FOLDER = src
TEST_FOLDER = test
BUILD_FOLDER = build
UNITY_ROOT = ../../Unity

# Comandos de Sistema
CLEANUP = rm -rf
MKDIR = mkdir -p

# Compilador e Flags
CC = gcc
CFLAGS = -std=c89
CFLAGS += -Wall -Wextra
CFLAGS += -Wpointer-arith
CFLAGS += -Wcast-align
CFLAGS += -Wwrite-strings
CFLAGS += -Wswitch-default
CFLAGS += -Wunreachable-code
CFLAGS += -Winit-self
CFLAGS += -Wmissing-field-initializers
CFLAGS += -Wno-unknown-pragmas
CFLAGS += -Wstrict-prototypes
CFLAGS += -Wundef
CFLAGS += -Wold-style-definition

# ------------------------------------------------------------------------------
# Separação de Ficheiros do Projeto
# ------------------------------------------------------------------------------

# Ficheiro main e módulos da Aplicação Principal
MAIN_SRC = $(SRC_FOLDER)/main.c
MODULES_SRC = $(SRC_FOLDER)/configData.c \
			$(SRC_FOLDER)/gen_rand.c \
			$(SRC_FOLDER)/confArrayString.c \
			$(SRC_FOLDER)/LinkedList.c

# Ficheiros necessários apenas para Unit test
TESTS_SRC = $(UNITY_ROOT)/src/unity.c \
            $(TEST_FOLDER)/test_$(MODULE_NAME_TEST).c \
            $(SRC_FOLDER)/$(MODULE_NAME_TEST).c

# Targets
APP_TARGET = $(BUILD_FOLDER)/$(APP_NAME)
TEST_TARGET = $(BUILD_FOLDER)/test_$(MODULE_NAME_TEST)

# Flags para o linker e inclusões
LDFLAGS = -lm
INC_DIRS = -I$(SRC_FOLDER) -I$(UNITY_ROOT)/src

# ------------------------------------------------------------------------------
# Regras do Makefile
# ------------------------------------------------------------------------------

.PHONY: all run test clean

# Default do 'make' é 'run'
all: run

# Criar pasta build caso não exista
$(BUILD_FOLDER):
	$(MKDIR) $(BUILD_FOLDER)

# 1. Compilação da Aplicação Principal
$(APP_TARGET): $(MAIN_SRC) $(MODULES_SRC) | $(BUILD_FOLDER)
	$(CC) $(CFLAGS) $(INC_DIRS) $(MAIN_SRC) $(MODULES_SRC) -o $@ $(LDFLAGS)

# Executar a Aplicação Principal
run: $(APP_TARGET)
	./$(APP_TARGET)

# 2. Compilação do Executável de Testes
$(TEST_TARGET): $(TESTS_SRC) | $(BUILD_FOLDER)
	$(CC) $(CFLAGS) $(INC_DIRS) $(TESTS_SRC) -o $@ $(LDFLAGS)

# Executar os Testes Unitários
test: $(TEST_TARGET)
	-./$(TEST_TARGET)

# Limpeza da pasta de build
clean:
	$(CLEANUP) $(BUILD_FOLDER)


#DESTA MANEIRA POSSO SÓ FAZER make e o codigo corre
#SE QUISER FAZER UNIT TESTING BASTA PREENCHER O MODULE_NAME 
#COM O NOME DO MODULO QUE QUERO TESTAR E FAZER make test