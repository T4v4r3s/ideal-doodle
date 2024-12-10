#include <string.h>
#include "filmes.h"
#include "usuarios.h"

// Funções para calcular a interseção e união de filmes (para calcular similaridade de Jaccard)
int calcular_intersecao(usuarioBloco* pessoa1, usuarioBloco* pessoa2) {
    int intersecao = 0;
    filmeLista* lista1 = pessoa1->posicao->inicio;
    filmeLista* lista2 = pessoa2->posicao->inicio;

    while (lista1 != NULL) {
        filmeLista* aux2 = lista2;
        while (aux2 != NULL) {
            if (strcmp(lista1->filme->nome, aux2->filme->nome) == 0) {
                intersecao++;
                break;
            }
            aux2 = aux2->prox;
        }
        lista1 = lista1->prox;
    }
    return intersecao;
}

// Função para calcular a união de filmes
int calcular_uniao(usuarioBloco* pessoa1, usuarioBloco* pessoa2) {
    int uniao = 0;
    filmeLista* lista1 = pessoa1->posicao->inicio;
    filmeLista* lista2 = pessoa2->posicao->inicio;

    while (lista1 != NULL) {
        uniao++;
        lista1 = lista1->prox;
    }

    while (lista2 != NULL) {
        filmeLista* lista1_check = pessoa1->posicao->inicio;
        int ja_contado = 0;
        while (lista1_check != NULL) {
            if (strcmp(lista2->filme->nome, lista1_check->filme->nome) == 0) {
                ja_contado = 1;
                break;
            }
            lista1_check = lista1_check->prox;
        }
        if (!ja_contado) {
            uniao++;
        }
        lista2 = lista2->prox;
    }

    return uniao;
}

// Função para calcular a similaridade de Jaccard
double similaridade_jaccard(usuarioBloco* pessoa1, usuarioBloco* pessoa2) {
    int intersecao = calcular_intersecao(pessoa1, pessoa2);
    int uniao = calcular_uniao(pessoa1, pessoa2);

    if (uniao == 0) {
        return 0.0;  // Se não houver filmes em comum ou nenhuma união
    }

    return (double)intersecao / uniao;
}