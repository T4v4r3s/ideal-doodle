#ifndef FILMES_H
#define FILMES_H

//Estrutura de lista ordenada de filmes
typedef struct filmeBloco{
    char nome[50];
} filmeBloco;

typedef struct filmeLista filmeLista;

//Estrutura de lista ordenada de filmes duplamente encadeada
struct filmeLista{
    filmeBloco *filme;
    filmeLista *prox;
    filmeLista *ant;
};

typedef struct posicaoLista{
    filmeLista *inicio;
    filmeLista *fim;
} posicaoLista;

//Funcoes de filmes
void inicializaListaFilmes(posicaoLista *posicao);
filmeLista *criaListaFilmes(posicaoLista *posicao);
filmeBloco *criaBlocoFilme(char nome[]);
int insereFilmeOrdenado(posicaoLista *posicoes, filmeBloco *novo);
filmeBloco *buscaFilme(filmeLista *lista, char nome[]);
int removeFilme(filmeLista *lista, char nome[]);
void destroiListaFilmes(posicaoLista *posicoes);

#endif