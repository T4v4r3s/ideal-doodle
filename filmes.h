#ifndef FILMES_H
#define FILMES_H

//Estrutura de lista ordenada de filmes
typedef struct filmeBloco{
    char nome[50];
} filmeBloco;

typedef struct filmeLista{
    filmeBloco *filme;
    filmeLista *prox;
} filmeLista;

//Funcoes de filmes
filmeLista *criaListaFilmes();
filmeBloco *criaBlocoFilme(char nome[]);
filmeLista *insereFilme(filmeLista *lista, filmeBloco *novo);
filmeBloco *buscaFilme(filmeLista *lista, char nome[]);
filmeLista *removeFilme(filmeLista *lista, char nome[]);
void imprimeFilmes(filmeLista *lista);
void destroiListaFilmes(filmeLista *lista);


#endif