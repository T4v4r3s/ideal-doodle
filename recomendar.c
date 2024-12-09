#include <stdio.h>
#include <string.h>
#include "filmes.h"
#include "usuarios.h"

// Estruturas de filmes e usuários
typedef struct filmeBloco {
    char nome[50];
} filmeBloco;

struct filmeLista {
    filmeBloco *filme;
    struct filmeLista *prox;
    struct filmeLista *ant;
};

typedef struct posicaoLista {
    struct filmeLista *inicio;
    struct filmeLista *fim;
} posicaoLista;

typedef struct usuarioBloco {
    char nome[50];
    int numeroUSP;
    char senha[50];
    int altura;
    struct usuarioBloco *esq;
    struct usuarioBloco *dir;
    struct posicaoLista *posicao;
    int fb;  // Fator de balanceamento
} usuarioBloco;

typedef struct usuarioArvore {
    usuarioBloco *raiz;
} usuarioArvore;

// Inicializa a árvore de usuários
void inicializaArvoreUsuarios(usuarioArvore *arvoreUsuarios) {
    arvoreUsuarios->raiz = NULL;
}

// Função que busca um usuário na árvore de usuários
usuarioBloco *buscaUsuario(usuarioBloco *raiz, int numeroUSP) {
    if (raiz == NULL) {
        return NULL;
    }

    if (raiz->numeroUSP == numeroUSP) {
        return raiz;
    }

    if (raiz->numeroUSP < numeroUSP) {
        return buscaUsuario(raiz->dir, numeroUSP);
    }

    return buscaUsuario(raiz->esq, numeroUSP);
}

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

// Função recursiva para recomendar o melhor colega
void recomendar_colega_recursiva(usuarioBloco* pessoa, usuarioArvore* arvoreUsuarios, usuarioBloco* aux, double* melhor_similaridade, usuarioBloco** melhor_colega) {
    if (aux == NULL) {
        return;  // Condição de parada
    }

    if (aux != pessoa) {
        double similaridade = similaridade_jaccard(pessoa, aux);  // Calcula a similaridade
        printf("Similaridade entre %s e %s: %.2f\n", pessoa->nome, aux->nome, similaridade);

        // Atualiza o melhor colega caso a similaridade seja maior
        if (similaridade > *melhor_similaridade) {
            *melhor_similaridade = similaridade;
            *melhor_colega = aux;
        }
    }

    // Chama recursivamente para os dois filhos
    recomendar_colega_recursiva(pessoa, arvoreUsuarios, aux->esq, melhor_similaridade, melhor_colega);
    recomendar_colega_recursiva(pessoa, arvoreUsuarios, aux->dir, melhor_similaridade, melhor_colega);
}

// Função principal para recomendar o colega mais semelhante
void Colega_Semelhante(usuarioBloco* pessoa, usuarioArvore* arvoreUsuarios) {
    usuarioBloco* melhor_colega = NULL;
    double melhor_similaridade = -1.0;  // Valor inicial

    // Chama a função recursiva para encontrar o melhor colega
    recomendar_colega_recursiva(pessoa, arvoreUsuarios, arvoreUsuarios->raiz, &melhor_similaridade, &melhor_colega);

    // Exibe o melhor colega encontrado
    if (melhor_colega != NULL) {
        printf("A pessoa com maior similaridade com %s é: %s com uma similaridade de %.2f\n", pessoa->nome, melhor_colega->nome, melhor_similaridade);
        printf("Recomenda-se que %s vá ao cinema com %s!\n", pessoa->nome, melhor_colega->nome);
    } else {
        printf("Nenhum colega foi encontrado para recomendar.\n");
    }
}

//Aproveitando já crie o código para amigo diferente

// Função recursiva para recomendar o melhor colega com o perfil mais diferente
void recomendar_colega_diferente_recursiva(usuarioBloco* pessoa, usuarioArvore* arvoreUsuarios, usuarioBloco* aux, double* menor_similaridade, usuarioBloco** pior_colega) {
    if (aux == NULL) {
        return;  // Condição de parada
    }

    if (aux != pessoa) {
        double similaridade = similaridade_jaccard(pessoa, aux);  // Calcula a similaridade
        printf("Similaridade entre %s e %s: %.2f\n", pessoa->nome, aux->nome, similaridade);

        // Atualiza o pior colega caso a similaridade seja menor
        if (similaridade < *menor_similaridade) {
            *menor_similaridade = similaridade;
            *pior_colega = aux;
        }
    }

    // Chama recursivamente para os dois filhos
    recomendar_colega_diferente_recursiva(pessoa, arvoreUsuarios, aux->esq, menor_similaridade, pior_colega);
    recomendar_colega_diferente_recursiva(pessoa, arvoreUsuarios, aux->dir, menor_similaridade, pior_colega);
}

// Função principal para recomendar o colega com o perfil mais diferente

void Colega_Diferente(usuarioBloco* pessoa, usuarioArvore* arvoreUsuarios) {
    usuarioBloco* pior_colega = NULL;
    double menor_similaridade = 1.0;  // Valor máximo possível (sem similaridade)

    // Chama a função recursiva para encontrar o pior colega
    recomendar_colega_diferente_recursiva(pessoa, arvoreUsuarios, arvoreUsuarios->raiz, &menor_similaridade, &pior_colega);

    // Exibe o pior colega encontrado
    if (pior_colega != NULL) {
        printf("A pessoa com menor similaridade com %s é: %s com uma similaridade de %.2f\n", pessoa->nome, pior_colega->nome, menor_similaridade);
        printf("Recomenda-se que %s entre em contato com %s para pedir sugestões de filmes!\n", pessoa->nome, pior_colega->nome);
    } else {
        printf("Nenhum colega foi encontrado para recomendar.\n");
    }
}


// Função principal do programa
int main() {
    int numeroUSP;
    usuarioBloco* pessoa;
    usuarioArvore arvoreUsuarios;

    // Inicializa a árvore
    inicializaArvoreUsuarios(&arvoreUsuarios);

    // Solicita o número USP do usuário
    printf("Qual o seu número USP, por favor? ");
    scanf("%d", &numeroUSP);

    // Busca o usuário na árvore de usuários
    pessoa = buscaUsuario(arvoreUsuarios.raiz, numeroUSP);
    if (pessoa == NULL) {
        printf("Usuário não encontrado!\n");
        return 1;
    }

    // Chama a função para recomendar o colega mais semelhante
    Colega_Semelhante(pessoa, &arvoreUsuarios);
    
    //Chama a função para recomendar o colega mais diferente
    Colega_Diferente(pessoa, &arvoreUsuarios);

    
    return 0;
}
