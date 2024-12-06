#include "filmes.h"
#include <stdlib.h>
#include <string.h>

//Funcao que inicializa uma lista de filmes
void inicializaListaFilmes(posicaoLista *posicao){

    posicao->inicio = NULL;
    posicao->fim = NULL;

}

//Funcao que cria uma lista de filmes
filmeLista *criaListaFilmes(posicaoLista *posicao){

    filmeLista *lista = (filmeLista *) malloc(sizeof(filmeLista));
    if(lista == NULL){
        return NULL;
    }
    lista->filme = NULL;
    lista->prox = NULL;
    lista->ant = NULL;

    posicao->inicio = lista;
    posicao->fim = lista;

    return lista;

}

//Funcao que cria um bloco de filme
filmeBloco *criaBlocoFilme(char nome[]){

    filmeBloco *novo = (filmeBloco *) malloc(sizeof(filmeBloco));
    if(novo == NULL){
        return NULL;
    }
    strcpy(novo->nome, nome);

    return novo;

}

//Funcao que insere um filme na lista de filmes de forma ordenada
int insereFilmeOrdenado(posicaoLista *posicoes, filmeBloco *novo){

    filmeLista *aux = posicoes->inicio;
    filmeLista *ant = NULL;

    while(aux != NULL && strcmp(aux->filme->nome, novo->nome) < 0){
        ant = aux;
        aux = aux->prox;
    }

    filmeLista *novoBloco = (filmeLista *) malloc(sizeof(filmeLista));
    if(novoBloco == NULL){
        return 1;
    }
    novoBloco->filme = novo;

    if(ant == NULL){
        novoBloco->prox = posicoes->inicio;
        novoBloco->ant = NULL;
        posicoes->inicio->ant = novoBloco;
        posicoes->inicio = novoBloco;
    } else {
        novoBloco->prox = ant->prox;
        novoBloco->ant = ant;
        if(ant->prox == NULL){
            posicoes->fim = novoBloco;
        } else {
            ant->prox->ant = novoBloco;
        }
        ant->prox = novoBloco;
    }

    return 0;

}

//Funcao que busca um filme na lista de filmes
filmeBloco *buscaFilme(filmeLista *lista, char nome[]){

    filmeLista *aux = lista;

    while(aux != NULL && strcmp(aux->filme->nome, nome) != 0){
        aux = aux->prox;
    }

    if(aux == NULL){
        return NULL;
    }

    return aux->filme;

}

//Funcao que remove um filme da lista de filmes (podemos mudar a forma que faz para ser mais eficiente?)
int removeFilme(filmeLista *lista, char nome[]){

    filmeLista *aux = lista;
    filmeLista *ant = NULL;

    while(aux != NULL && strcmp(aux->filme->nome, nome) != 0){
        ant = aux;
        aux = aux->prox;
    }

    if(aux == NULL){
        return 0;
    }

    if(ant == NULL){
        lista = aux->prox;
    } else {
        ant->prox = aux->prox;
    }

    free(aux->filme);
    free(aux);

    return 1;

}

//Funcao que destroi a lista de filmes (recebendo as posicoes)
void destroiListaFilmes(posicaoLista *posicoes){

    filmeLista *aux = posicoes->inicio;
    filmeLista *prox = NULL;

    while(aux != NULL){
        prox = aux->prox;
        free(aux->filme);
        free(aux);
        aux = prox;
    }

    posicoes->inicio = NULL;
    posicoes->fim = NULL;

}