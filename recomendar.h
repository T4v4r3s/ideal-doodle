#ifndef RECOMENDAR_H
#define RECOMENDAR_H

#include "filmes.h"
#include "usuarios.h"

int calcular_intersecao(usuarioBloco* pessoa1, usuarioBloco* pessoa2);
int calcular_uniao(usuarioBloco* pessoa1, usuarioBloco* pessoa2);
double similaridade_jaccard(usuarioBloco* pessoa1, usuarioBloco* pessoa2);

#endif