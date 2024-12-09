#include<stdio.h>
#include "filmes.h"
#include "usuarios.h"

typedef struct filmeBloco{
    char nome[50];
} filmeBloco;

struct filmeLista{
    filmeBloco *filme;
    filmeLista *prox;
    filmeLista *ant;
}filmeLista;

typedef struct posicaoLista{
    filmeLista *inicio;
    filmeLista *fim;
} posicaoLista;

// Estrutura de AVL de usuarios
typedef struct usuarioBloco {
    char nome[50];
    int numeroUSP;
    char senha[50];
    int altura;
    struct usuarioBloco *esq;
    struct usuarioBloco *dir;
    struct posicaoLista *posicao;
    int fb; // Fator de balanceamento

} usuarioBloco;

// Estrutura de AVL de usuarios
typedef struct usuarioArvore {
    usuarioBloco *raiz;
} usuarioArvore;

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

// Função para calcular a interseção entre as listas de filmes
int calcular_intersecao(Pessoa* pessoa, ArvoreUsuario*) {
    int intersecao = 0;
    filmeBloco* lista1 = pessoa->filmeLista;
    filmeBloco* lista2 = usuario->filmeLista;

    while (lista1 != NULL) {
        filmeBloco* aux2 = lista2;
        while (aux2 != NULL) {
            if (lista1->filmelista == aux2->filmelista) {
                intersecao++;
                break;  // Interseção encontrada, não há necessidade de continuar a busca
            }
            aux2 = aux2->prox;
        }
        lista1 = lista1->prox;
    }
    return intersecao;
}

// Função para calcular a união entre as listas de filmes
int calcular_uniao(Pessoa* pessoa, ArvoreUsuario*) {
    int uniao = 0;
    filmeBloco* lista1 = pessoa->filmeLista;
    filmeBloco* lista2 = usuario->filmeLista;

    // Contando filmes da primeira lista
    while (lista1 != NULL) {
        uniao++;
        lista1 = lista1->prox;
    }

    // Contando filmes da segunda lista, sem contar os repetidos
    while (lista2 != NULL) {
        filmeBloco* lista1_check = pessoa->filmeLista;
        int ja_contado = 0;
        while (lista1_check != NULL) {
            if (lista2->filmelista- == lista1_check->filmelista) {
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
double similaridade_jaccard(Pessoa* pessoa, ArvoreUsuario* ) {
    int intersecao = calcular_intersecao(pessoa, usuario);
    int uniao = calcular_uniao(pessoa, usuario);

    if (uniao == 0) {
        return 0.0;  // Se não houver filmes em comum ou nenhuma união
    }

    return (double)intersecao / uniao;
}

void recomendar_colega(Pessoa* pessoa, ArvoreUsuario*ArvoreUsuarios) {
    Pessoa* melhor_colega = NULL;
    double melhor_similaridade = -1.0;  // Inicia com um valor negativo para garantir que qualquer similaridade será maior
    Pessoa* aux = ArvoreUsuario-> raiz;

    // Percorre todos os usuários para encontrar o mais similar
    while (aux != NULL) {
        if (aux != pessoa) {  // Não compara a pessoa consigo mesma
            double similaridade = similaridade_jaccard(pessoa,ArvoreUsuario);
            printf("Similaridade entre %s e %s: %.2f\n", pessoa->nome, aux->nome, similaridade);

            // Se a similaridade for maior que a melhor já encontrada, atualiza o melhor colega
            if (similaridade > melhor_similaridade) {
                melhor_similaridade = similaridade;
                melhor_colega = aux;
            }
        }
        aux = aux->dir;  // Percorrendo a árvore binária
    }

    if (melhor_colega != NULL) {
        printf("Recomenda-se que %s vá ao cinema com %s!\n", pessoa->nome, melhor_colega->nome);
    } else {
        printf("Nenhum colega foi encontrado para recomendar.\n");
    }
}

int main(){
    int numeroUSP;
    Pessoa*pessoa;

  // A primeira pergunta seria o quem e o usuario
    printf("Qual o seu número USP, por favor ?")
    scanf("%d", &numeroUSP);

     pessoa = buscaUsuario(ArvoreUsuario*, numeroUSP);
    if (pessoa == NULL) {
        printf("Usuário não encontrado!\n");
        return 1;
    }

        recomendar_colega(pessoa, &ArvoreUsuario);

    return 0;
} 

