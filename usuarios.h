#ifndef USUARIOS_H
#define USUARIOS_H

#include "filmes.h"

//Estrutura de AVL de usuarios
typedef struct usuarioBloco{
    char nome[50];
    int numeroUSP;
    usuarioBloco *esq;
    usuarioBloco *dir;
    posicaoLista *posicao;
    int fb;

} usuarioBloco;

//Estrutura de AVL de usuarios
typedef struct usuarioArvore{
    usuarioBloco *raiz;
} usuarioArvore;

//Funcoes de usuarios

usuarioArvore *inicializaArvoreUsuarios();
usuarioBloco *criaBlocoUsuario(char nome[], int numeroUSP);
usuarioBloco *buscaUsuario(usuarioBloco *raiz, int numeroUSP);
void imprimeUsuariosEmOrdem(usuarioBloco *raiz);
void imprimeUsuariosPreOrdem(usuarioBloco *raiz);
void imprimeUsuariosPosOrdem(usuarioBloco *raiz);

/* Ideia de algumas funcoes que faltam (talvez os tipos e nomes possam ser diferentes)

int *insereUsuario(usuarioBloco *raiz, usuarioBloco *novo);
usuarioBloco *removeUsuario(usuarioBloco *raiz, int numeroUSP);
usuarioBloco *removeUsuarioAux(usuarioBloco *raiz, int numeroUSP);
usuarioBloco *rotacaoDireita(usuarioBloco *raiz);
usuarioBloco *rotacaoEsquerda(usuarioBloco *raiz);
usuarioBloco *rotacaoDuplaDireita(usuarioBloco *raiz);
usuarioBloco *rotacaoDuplaEsquerda(usuarioBloco *raiz);
int alturaUsuario(usuarioBloco *raiz);
int fatorBalanceamentoUsuario(usuarioBloco *raiz); (talvez essa nem possar ser util)
void destroiArvoreUsuarios(usuarioBloco *raiz);
void destroiArvoreUsuarios(usuarioArvore *arvore);

*/

#endif