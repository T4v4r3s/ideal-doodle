# Nome do executável
TARGET = programa

# Compilador
CC = gcc

# Flags do compilador
CFLAGS = -Wall -Wextra -g

# Arquivos-fonte e cabeçalhos
SRCS = main.c filmes.c usuarios.c
HEADERS = filmes.h usuarios.h

# Objetos gerados
OBJS = $(SRCS:.c=.o)

# Regra principal
all: $(TARGET)

# Regra para gerar o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Regra para compilar os objetos
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos gerados
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
