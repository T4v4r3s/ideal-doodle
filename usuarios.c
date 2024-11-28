#include <stdlib.h>
#include "filmes.h"
#include "usuarios.h"


//Funcao que inicializa a arvore de usuarios
usuarioArvore *inicializaArvoreUsuarios(){
    
    usuarioArvore *arvore = (usuarioArvore *) malloc(sizeof(usuarioArvore));
    if(arvore == NULL){
        return NULL;
    }
    arvore->raiz = NULL;
    return arvore;

}


//Funcao que cria um bloco de usuario
usuarioBloco *criaBlocoUsuario(char nome[], int numeroUSP, char senha[]){

    usuarioBloco *novo = (usuarioBloco *) malloc(sizeof(usuarioBloco));

    if(novo == NULL){
        return NULL;
    }

    strcpy(novo->nome, nome);
    novo->numeroUSP = numeroUSP;
    strcpy(novo->senha, senha);
    novo->esq = NULL;
    novo->dir = NULL;
    novo->posicao = (posicaoLista *) malloc(sizeof(posicaoLista)); //Mudar (?)
    inicializaListaFilmes(novo->posicao);
    novo->fb = 0;

    return novo;
}

//Funcao que busca um usuario na arvore de usuarios
usuarioBloco *buscaUsuario(usuarioBloco *raiz, int numeroUSP){

    if(raiz == NULL){
        return NULL;
    }

    if(raiz->numeroUSP == numeroUSP){
        return raiz;
    }

    if(raiz->numeroUSP < numeroUSP){
        return buscaUsuario(raiz->dir, numeroUSP);
    }

    return buscaUsuario(raiz->esq, numeroUSP);

}

//Funcao que imprime os usuarios da arvore de usuarios EM ORDEM
void imprimeUsuariosEmOrdem(usuarioBloco *raiz){

    if(raiz == NULL){
        return;
    }

    if (raiz->esq != NULL){
        imprimeUsuarios(raiz->esq);
    }

    printf("Nome: %s\n", raiz->nome);
    printf("Numero USP: %d\n", raiz->numeroUSP);

    if (raiz->dir != NULL){
        imprimeUsuarios(raiz->dir);
    }

}

//Funcao que imprime os usuarios PRE ORDEM
void imprimeUsuariosPreOrdem(usuarioBloco *raiz){

    if(raiz == NULL){
        return;
    }

    printf("Nome: %s\n", raiz->nome);
    printf("Numero USP: %d\n", raiz->numeroUSP);

    if (raiz->esq != NULL){
        imprimeUsuarios(raiz->esq);
    }

    if (raiz->dir != NULL){
        imprimeUsuarios(raiz->dir);
    }

}

//Funcao que imprime usuarios POS ORDEM
void imprimeUsuariosPosOrdem(usuarioBloco *raiz){

    if(raiz == NULL){
        return;
    }

    if (raiz->esq != NULL){
        imprimeUsuarios(raiz->esq);
    }

    if (raiz->dir != NULL){
        imprimeUsuarios(raiz->dir);
    }

    printf("Nome: %s\n", raiz->nome);
    printf("Numero USP: %d\n", raiz->numeroUSP);

}

//Funcao de login
int buscaUspSenha(usuarioArvore *usuarios, int NUSP, char senha[]){

    usuarioBloco *procurado;

    procurado = buscaUsuario(&usuarios, NUSP);

    //Caso nao ache um usuario com o nome
    if(procurado == NULL){
        return 1;
    }
    //Caso ache o usuario e senha valida
    if(strcmp(procurado->senha, senha) == 0){
        return 0;
    }

    //Caso ache usuario mas senha errada
    return 1;

}