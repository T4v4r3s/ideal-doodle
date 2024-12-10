#include <stdlib.h>
#include <string.h>
#include <stdio.h>
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
        imprimeUsuariosEmOrdem(raiz->esq);
    }

    printf("Nome: %s\n", raiz->nome);
    printf("Numero USP: %d\n", raiz->numeroUSP);

    if (raiz->dir != NULL){
        imprimeUsuariosEmOrdem(raiz->dir);
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
        imprimeUsuariosPreOrdem(raiz->esq);
    }

    if (raiz->dir != NULL){
        imprimeUsuariosPreOrdem(raiz->dir);
    }

}

//Funcao que imprime usuarios POS ORDEM
void imprimeUsuariosPosOrdem(usuarioBloco *raiz){

    if(raiz == NULL){
        return;
    }

    if (raiz->esq != NULL){
        imprimeUsuariosPosOrdem(raiz->esq);
    }

    if (raiz->dir != NULL){
        imprimeUsuariosPosOrdem(raiz->dir);
    }

    printf("Nome: %s\n", raiz->nome);
    printf("Numero USP: %d\n", raiz->numeroUSP);

}



//Funcao de login
int buscaUspSenha(usuarioArvore *usuarios, int NUSP, char senha[]){

    usuarioBloco *procurado;

    procurado = buscaUsuario(usuarios->raiz, NUSP);

    //Caso nao ache um usuario com o nome
    if(procurado == NULL){
        printf("Usuario nao encontrado\n");
        return 0;
    }
    //Caso ache o usuario e senha valida
    if(strcmp(procurado->senha, senha) == 0){
        printf("Usuario logado com sucesso\n");
        return 1;
    }

    //Caso ache usuario mas senha errada
    printf("Senha incorreta\n");
    return 0;

}

//Funcao para obter a altura do no
int obterAltura(usuarioBloco *no) {
    if (no == NULL)
        return 0;
    return no->altura;
}

//Funcao para obter o valor máximo entre dois inteiros
int obterMaximo(int valor1, int valor2) {
    return (valor1 > valor2) ? valor1 : valor2;
}

//Funcao para criar um novo nó
usuarioBloco* criarNovoNo(char nome[], char senha[], int numeroUSP) {
    usuarioBloco* novoNo = (usuarioBloco*)malloc(sizeof(usuarioBloco));
    strcpy(novoNo->nome, nome);
    strcpy(novoNo->senha, senha);
    novoNo->numeroUSP = numeroUSP;
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    novoNo->altura = 1; //Novo no eh inicialmente adicionado na folha
    novoNo->fb = 0; //Fator de balanceamento inicial é 0
    return(novoNo);
}

//Funcao para realizar uma rotacao a direita
usuarioBloco *rotacionarDireita(usuarioBloco *noDesbalanceado) {
    usuarioBloco *novoNo = noDesbalanceado->esq;
    usuarioBloco *subArvore = novoNo->dir;

    //Realiza a rotacao
    novoNo->dir = noDesbalanceado;
    noDesbalanceado->esq = subArvore;

    //Atualiza as alturas
    noDesbalanceado->altura = obterMaximo(obterAltura(noDesbalanceado->esq), obterAltura(noDesbalanceado->dir)) + 1;
    novoNo->altura = obterMaximo(obterAltura(novoNo->esq), obterAltura(novoNo->dir)) + 1;

    //Atualiza os fatores de balanceamento
    noDesbalanceado->fb = obterAltura(noDesbalanceado->esq) - obterAltura(noDesbalanceado->esq);
    novoNo->fb = obterAltura(novoNo->esq) - obterAltura(novoNo->dir);

    //Retorna a nova raiz
    return novoNo;
}

//Funcao para realizar uma rotacao a esquerda
usuarioBloco *rotacionarEsquerda(usuarioBloco *noDesbalanceado) {
    usuarioBloco *novoNo = noDesbalanceado->dir;
    usuarioBloco *subArvore = novoNo->esq;

    //Realiza a rotacao
    novoNo->esq = noDesbalanceado;
    noDesbalanceado->dir = subArvore;

    //Atualiza as alturas
    noDesbalanceado->altura = obterMaximo(obterAltura(noDesbalanceado->esq), obterAltura(noDesbalanceado->dir)) + 1;
    novoNo->altura = obterMaximo(obterAltura(novoNo->esq), obterAltura(novoNo->dir)) + 1;

    //Atualiza os fatores de balanceamento
    noDesbalanceado->fb = obterAltura(noDesbalanceado->esq) - obterAltura(noDesbalanceado->dir);
    novoNo->fb = obterAltura(novoNo->esq) - obterAltura(novoNo->dir);

    //Retorna a nova raiz
    return novoNo;
}

//Funcao para obter o fator de balanceamento
int obterFatorBalanceamento(usuarioBloco *no) {
    if (no == NULL)
        return 0;
    return obterAltura(no->esq) - obterAltura(no->dir);
}

//Funcao para inserir um novo nó na árvore AVL
usuarioBloco* inserirNo(usuarioBloco* raiz, char nome[], char senha[], int numeroUSP) {
    // 1. Realiza a insercao normal na arvore
    if (raiz == NULL){
        return(criarNovoNo(nome, senha, numeroUSP));
    }

    if (numeroUSP < raiz->numeroUSP)
        raiz->esq = inserirNo(raiz->esq, nome, senha, numeroUSP);
    else if (numeroUSP > raiz->numeroUSP)
        raiz->dir = inserirNo(raiz->dir, nome, senha, numeroUSP);
    else //Numeros USP iguais nao sao permitidos na arvore (para evitar erros (principalmente de senha))
        return raiz;

    //2. Atualiza a altura deste no pai
    raiz->altura = 1 + obterMaximo(obterAltura(raiz->esq), obterAltura(raiz->dir));

    //3. Atualiza o fator de balanceamento deste no pai
    raiz->fb = obterAltura(raiz->esq) - obterAltura(raiz->dir);

    //4. Obtem o fator de balanceamento deste no pai para verificar se este no ficou desbalanceado
    int balanceamento = raiz->fb;

    //Se este no ficou desbalanceado, entao existem 4 casos

    //Caso Esquerda Esquerda
    if (balanceamento > 1 && numeroUSP < raiz->esq->numeroUSP)
        return rotacionarDireita(raiz);

    //Caso Direita Direita
    if (balanceamento < -1 && numeroUSP > raiz->dir->numeroUSP)
        return rotacionarEsquerda(raiz);

    //Caso Esquerda Direita
    if (balanceamento > 1 && numeroUSP > raiz->esq->numeroUSP) {
        raiz->esq = rotacionarEsquerda(raiz->esq);
        return rotacionarDireita(raiz);
    }

    //Caso Direita Esquerda
    if (balanceamento < -1 && numeroUSP < raiz->dir->numeroUSP) {
        raiz->dir = rotacionarDireita(raiz->dir);
        return rotacionarEsquerda(raiz);
    }

    //Retorna o ponteiro do no (inalterado)
    return raiz;
}

void deletaRecursivamenteTodaArvore(usuarioBloco *raiz){

    if(raiz == NULL){
        return;
    }

    deletaRecursivamenteTodaArvore(raiz->esq);
    deletaRecursivamenteTodaArvore(raiz->dir);
    destroiListaFilmes(raiz->posicao);
    free(raiz);

    return;
}

int adicionarFilmeUsuario(usuarioBloco *usuario, filmeBloco *filme){

    if(insereFilmeOrdenado(usuario->posicao, filme)){
        return 1;
    }

    return 0;

}

int removeUsuarioAvl(usuarioArvore *usuarios, int numeroUSP){

    usuarioBloco *procurado = buscaUsuario(usuarios->raiz, numeroUSP);

    if(procurado == NULL){
        return 0;
    }

    usuarios->raiz = removeNoAvl(usuarios->raiz, numeroUSP);
    return 1;
}

usuarioBloco* removeNoAvl(usuarioBloco* raiz, int numeroUSP) {
    if (raiz == NULL) {
        return raiz;
    }

    if (numeroUSP < raiz->numeroUSP) {
        raiz->esq = removeNoAvl(raiz->esq, numeroUSP);
    } else if (numeroUSP > raiz->numeroUSP) {
        raiz->dir = removeNoAvl(raiz->dir, numeroUSP);
    } else {
        if ((raiz->esq == NULL) || (raiz->dir == NULL)) {
            usuarioBloco *temp = raiz->esq ? raiz->esq : raiz->dir;

            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else {
                *raiz = *temp;
            }
            free(temp);
        } else {
            usuarioBloco* temp = minValor(raiz->dir);
            raiz->numeroUSP = temp->numeroUSP;
            raiz->dir = removeNoAvl(raiz->dir, temp->numeroUSP);
        }
    }

    if (raiz == NULL) {
        return raiz;
    }

    raiz->altura = 1 + obterMaximo(obterAltura(raiz->esq), obterAltura(raiz->dir));

    int balanceamento = obterFatorBalanceamento(raiz);

    if (balanceamento > 1 && obterFatorBalanceamento(raiz->esq) >= 0) {
        return rotacionarDireita(raiz);
    }

    if (balanceamento > 1 && obterFatorBalanceamento(raiz->esq) < 0) {
        raiz->esq = rotacionarEsquerda(raiz->esq);
        return rotacionarDireita(raiz);
    }

    if (balanceamento < -1 && obterFatorBalanceamento(raiz->dir) <= 0) {
        return rotacionarEsquerda(raiz);
    }

    if (balanceamento < -1 && obterFatorBalanceamento(raiz->dir) > 0) {
        raiz->dir = rotacionarDireita(raiz->dir);
        return rotacionarEsquerda(raiz);
    }

    return raiz;
}



usuarioBloco* minValor(usuarioBloco* usuario) {
    usuarioBloco* atual = usuario;
    while (atual->esq != NULL) {
        atual = atual->esq;
    }
    return atual;
}