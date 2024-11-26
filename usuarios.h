#ifndef USUARIOS_H
#define USUARIOS_H

//Estrutura de AVL de usuarios
typedef struct usuarioBloco{
    char nome[50];
    int numeroUSP;
    usuarioBloco *esq;
    usuarioBloco *dir;
    int fb;

} usuarioBloco;

//Estrutura de AVL de usuarios
typedef struct usuarioArvore{
    usuarioBloco *raiz;
} usuarioArvore;

//Funcoes de usuarios
usuarioArvore *criaArvoreUsuarios();
usuarioBloco *criaBlocoUsuario(char nome[], int numeroUSP);
usuarioBloco *insereUsuario(usuarioBloco *raiz, usuarioBloco *novo);
usuarioBloco *buscaUsuario(usuarioBloco *raiz, int numeroUSP);
usuarioBloco *removeUsuario(usuarioBloco *raiz, int numeroUSP);
usuarioBloco *removeUsuarioAux(usuarioBloco *raiz, int numeroUSP);
usuarioBloco *rotacaoDireita(usuarioBloco *raiz);
usuarioBloco *rotacaoEsquerda(usuarioBloco *raiz);
usuarioBloco *rotacaoDuplaDireita(usuarioBloco *raiz);
usuarioBloco *rotacaoDuplaEsquerda(usuarioBloco *raiz);
int alturaUsuario(usuarioBloco *raiz);
int fatorBalanceamentoUsuario(usuarioBloco *raiz);
void imprimeUsuarios(usuarioBloco *raiz);
void destroiArvoreUsuarios(usuarioBloco *raiz);
void destroiArvoreUsuarios(usuarioArvore *arvore);


#endif