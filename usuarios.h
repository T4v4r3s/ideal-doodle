#ifndef USUARIOS_H
#define USUARIOS_H

#include "filmes.h"

// Estrutura de AVL de usuarios
typedef struct usuarioBloco {
    char nome[50];
    int numeroUSP;
    char senha[50];
    int altura;
    struct usuarioBloco *esq;
    struct usuarioBloco *dir;
    struct posicaoLista *posicao; // Lista de filmes
    int fb; // Fator de balanceamento

} usuarioBloco;

// Estrutura de AVL de usuarios
typedef struct usuarioArvore {
    usuarioBloco *raiz;
} usuarioArvore;

// Funções de usuarios
usuarioArvore *inicializaArvoreUsuarios();
usuarioBloco *criaBlocoUsuario(char nome[], int numeroUSP, char senha[]);
usuarioBloco *buscaUsuario(usuarioBloco *raiz, int numeroUSP);
void imprimeUsuariosEmOrdem(usuarioBloco *raiz);
void imprimeUsuariosPreOrdem(usuarioBloco *raiz);
void imprimeUsuariosPosOrdem(usuarioBloco *raiz);
int buscaUspSenha(usuarioArvore *usuarios, int NUSP, char senha[]);
int obterAltura(usuarioBloco *no);
int obterMaximo(int valor1, int valor2);
usuarioBloco* criarNovoNo(char nome[], char senha[], int numeroUSP);
usuarioBloco *rotacionarDireita(usuarioBloco *noDesbalanceado);
usuarioBloco *rotacionarEsquerda(usuarioBloco *noDesbalanceado);
int obterFatorBalanceamento(usuarioBloco *no);
usuarioBloco* inserirNo(usuarioBloco* raiz, char nome[], char senha[], int numeroUSP);
void deletaRecursivamenteTodaArvore(usuarioBloco *raiz);
int adicionarFilmeUsuario(usuarioBloco *usuario, filmeBloco *filme);
int removeUsuarioAvl(usuarioArvore *usuarios, int numeroUSP);
usuarioBloco* removeNoAvl(usuarioBloco* raiz, int numeroUSP);
usuarioBloco* minValor(usuarioBloco* usuario);

#endif // USUARIOS_H