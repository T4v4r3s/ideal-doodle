#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filmes.h"
#include "usuarios.h"
#include "recomendar.h"

//Declaracao de funcoes
void exibirMenu();
void imprimeFilmesEmOrdem(posicaoLista *p);
void imprimeFilmesReverso(posicaoLista *p);
void imprimeListaFilmesUsuario(usuarioBloco *usuario);
void recomendar_colega_diferente_recursiva(usuarioBloco* pessoa, usuarioArvore* arvoreUsuarios, usuarioBloco* aux, double* menor_similaridade, usuarioBloco** pior_colega);
void recomendar_colega_recursiva(usuarioBloco* pessoa, usuarioArvore* arvoreUsuarios, usuarioBloco* aux, double* melhor_similaridade, usuarioBloco** melhor_colega);

int main() {

    //Declaracao de variaveis
    int escolha;
    int funcionando = 1;
    int logado = 0;
    int NUSPLogin;
    char senhaLogin[50];
    char nomeCriacao[50], senhaCriacao[50];
    int NUSPCriacao;
    int escolhaPrint;
    int NUSPBusca;
    //char nomeFilme[50];

    // Variáveis para armazenar o melhor e o pior colega
    usuarioBloco *melhor_colega = NULL;
    usuarioBloco *pior_colega = NULL;

    //Inicialização das estruturas
    usuarioArvore *usuarios = inicializaArvoreUsuarios();
    usuarioBloco *usuarioLogado;

    posicaoLista *filmesPosicao = (posicaoLista *) malloc(sizeof(posicaoLista));
    inicializaListaFilmes(filmesPosicao);
    
    while (funcionando) {

        printf("---------------------------");
        printf("    \nBem-Vindo\n\n");
        printf("   -- Escolha uma opcao --\n\n");
        printf("1 - Login\n");
        printf("2 - Cadastrar Usuario\n");
        printf("3 - SAIR!\n");
        printf("---------------------------\n");

        scanf("%d", &escolha);
        switch (escolha){
        case 1:
            //Login

            printf("Informe o numero USP\n");
            scanf("%d", &NUSPLogin);

            printf("Informe a senha: \n");
            scanf("%s", senhaLogin);

            if(buscaUspSenha(usuarios, NUSPLogin, senhaLogin)){
                logado = 1;
                usuarioLogado = buscaUsuario(usuarios->raiz, NUSPLogin);
            }
            break;
        case 2:
            //Criar usuario
            printf("Informe o nome do usuario\n");
            scanf("%s", nomeCriacao);

            printf("Informe o NUSP\n");
            scanf("%d", &NUSPCriacao);

            printf("Informe a senha\n");
            scanf("%s", senhaCriacao);

            usuarios->raiz = inserirNo(usuarios->raiz, nomeCriacao, senhaCriacao, NUSPCriacao);

            break;
        case 3:
            printf("Encerrando o programa. Até mais!\n");

            // Liberar memória
            deletaRecursivamenteTodaArvore(usuarios->raiz);
            destroiListaFilmes(filmesPosicao);

            // Encerrar o programa
            logado = 0;
            funcionando = 0;

            break;
        default:
            printf("Informe um numero valido!");
            break;
        }

        while (logado){
            exibirMenu();
            scanf("%d", &escolha);

            switch (escolha) {
                case 1:
                    //Criar usuario
                    printf("Informe o nome do usuario\n");
                    scanf("%s", nomeCriacao);

                    printf("Informe o NUSP\n");
                    scanf("%d", &NUSPCriacao);

                    printf("Informe a senha\n");
                    scanf("%s", senhaCriacao);

                    usuarios->raiz = inserirNo(usuarios->raiz, nomeCriacao, senhaCriacao, NUSPCriacao);

                    break;
                case 2:
                    //listar Alunos
                    
                    printf("Escolha a forma de impressao:\n");
                    printf("1 - Em ordem\n");
                    printf("2 - Pré ordem\n");
                    printf("3 - Pós ordem\n");
                    
                    scanf("%d", &escolhaPrint);

                    if(escolhaPrint == 1){
                        imprimeUsuariosEmOrdem(usuarios->raiz);
                    } else if(escolhaPrint == 2){
                        imprimeUsuariosPreOrdem(usuarios->raiz);
                    } else if(escolhaPrint == 3){
                        imprimeUsuariosPosOrdem(usuarios->raiz);
                    } else {
                        printf("Opcao invalida\n");
                    }
                    
                    break;
                case 3:
                    // Buscar Aluno

                    printf("Informe o numero USP do aluno que deseja buscar: ");
                    scanf("%d", &NUSPBusca);

                    usuarioBloco *buscado = buscaUsuario(usuarios->raiz, NUSPBusca);

                    if(buscado == NULL){
                        printf("Aluno nao encontrado\n");
                    } else {
                        printf("Nome: %s\n", buscado->nome);
                        printf("Numero USP: %d\n", buscado->numeroUSP);
                    }

                    break;
                case 4:
                    // Listar Filmes cadastrados

                    printf("Escolha a forma de impressao:\n");
                    printf("1 - Em ordem\n");
                    printf("2 - Reverso\n");

                    scanf("%d", &escolhaPrint);

                    if(escolhaPrint == 1){
                        imprimeFilmesEmOrdem(filmesPosicao);
                    } else if(escolhaPrint == 2){
                        imprimeFilmesReverso(filmesPosicao);
                    } else {
                        printf("Opcao invalida\n");
                    }

                    break;
                case 5:
                    // Buscar Filme cadastrado no sistema

                    if (filmesPosicao->inicio == NULL){
                        printf("Nenhum filme cadastrado\n");
                        break;
                    }

                    char nomeFilme[50];
                    printf("Informe o nome do filme que deseja buscar: ");
                    scanf("%s", nomeFilme);

                    filmeBloco *buscadoFilme = buscaFilme(filmesPosicao->inicio, nomeFilme);

                    if(buscadoFilme == NULL){
                        printf("Filme nao encontrado\n");
                    } else {
                        printf("Filme encontrado!\n");
                        printf("Nome: %s\n", buscadoFilme->nome); // Podemos só falar que foi encontrado se quisermos
                    }
                    
                    break;
                case 6:
                    // Recomendar Colega para ir ao cinema
                        double melhor_similaridade = -1.0;  // Valor inicial

                        // Chama a função recursiva para encontrar o melhor colega
                        recomendar_colega_recursiva(usuarioLogado, usuarios, usuarios->raiz, &melhor_similaridade, &melhor_colega);

                        // Exibe o melhor colega encontrado
                        if (melhor_colega != NULL) {
                            printf("A pessoa com maior similaridade com %s é: %s com uma similaridade de %.2f\n", usuarioLogado->nome, melhor_colega->nome, melhor_similaridade);
                            printf("Recomenda-se que %s vá ao cinema com %s!\n", usuarioLogado->nome, melhor_colega->nome);
                        } else {
                            printf("Nenhum colega foi encontrado para recomendar.\n");
                        }

                    break;
                case 7:
                    // Recomendar Colega com perfil diferente

                        double menor_similaridade = 1.0;  // Valor máximo possível (sem similaridade)

                        // Chama a função recursiva para encontrar o pior colega
                        recomendar_colega_diferente_recursiva(usuarioLogado, usuarios, usuarios->raiz, &menor_similaridade, &pior_colega);

                        // Exibe o pior colega encontrado
                        if (pior_colega != NULL) {
                            printf("A pessoa com menor similaridade com %s é: %s com uma similaridade de %.2f\n", usuarioLogado->nome, pior_colega->nome, menor_similaridade);
                            printf("Recomenda-se que %s entre em contato com %s para pedir sugestões de filmes!\n", usuarioLogado->nome, pior_colega->nome);
                        } else {
                            printf("Nenhum colega foi encontrado para recomendar.\n");
                        }
                    break;
                case 8:
                    //salvarDadosEmArquivo();
                    break;
                case 9:
                    //exibirDadosArvore();
                    break;
                case 10:
                    // Remover Aluno

                    printf("Informe o numero USP do aluno que deseja remover: ");
                    scanf("%d", &NUSPBusca);

                    if(removeUsuarioAvl(usuarios, NUSPBusca)){
                        printf("Usuario removido com sucesso\n");
                    } else {
                        printf("Usuario nao encontrado\n");
                    }
                    
                    break;
                case 11:
                    // Voltar ao menu

                    logado = 0;
                    break;
                case 12:
                    // Cadastrar Filme

                    printf("Informe o nome do filme que deseja cadastrar: ");
                    scanf("%s", nomeFilme);

                    filmeBloco *novoFilme = criaBlocoFilme(nomeFilme);
                    insereFilmeOrdenado(filmesPosicao, novoFilme);

                    break;
                case 13:
                    // Remover Filme

                    printf("Informe o nome do filme que deseja remover: ");
                    scanf("%s", nomeFilme);

                    removeFilme(filmesPosicao->inicio, nomeFilme);

                    break;
                case 14:

                    // Adiciona filme favorito ao usuário

                    printf("Informe o nome do filme que deseja adicionar: ");
                    scanf("%s", nomeFilme);

                    filmeBloco *filmeFavorito = buscaFilme(filmesPosicao->inicio, nomeFilme);

                    if(filmeFavorito == NULL){
                        printf("Filme nao encontrado\n");
                    } else {
                        if(adicionarFilmeUsuario(usuarioLogado, filmeFavorito)){
                            printf("Filme adicionado com sucesso\n");
                        } else {
                            printf("Erro ao adicionar filme\n");
                        }
                    }

                    break;
                case 0:
                    printf("Encerrando o programa. Até mais!\n");

                    // Liberar memória
                    deletaRecursivamenteTodaArvore(usuarios->raiz);
                    destroiListaFilmes(filmesPosicao);

                    // Encerrar o programa
                    logado = 0;
                    funcionando = 0;
                    break;
                default:
                    printf("Opção inválida! Tente novamente.\n");
                    break;
            }    
        }
        

        
    }

    
    return 0;
}


void exibirMenu() {
    printf("\n==============================\n");
    printf("   Sistema de Filmes - Menu\n");
    printf("==============================\n");
    printf("1) Criar cadastro de aluno\n");
    printf("2) Listar todos os alunos\n");
    printf("3) Buscar aluno pelo número USP\n");
    printf("4) Listar todos os filmes cadastrados\n");
    printf("5) Buscar filme no sistema\n");
    printf("6) Recomendar colega para ir ao cinema\n");
    printf("7) Recomendar colega com perfil diferente\n");
    printf("8) Salvar dados em arquivo\n");
    printf("9) Exibir dados técnicos da árvore\n");
    printf("10) Remover aluno do sistema\n");
    printf("11) Voltar ao menu\n");
    printf("12) Cadastrar filme\n");
    printf("13) Remover filme\n");
    printf("0) Finalizar programa!\n");
    printf("==============================\n");
    printf("Escolha uma opção: ");
}

void imprimeFilmesEmOrdem(posicaoLista *p){
    filmeLista *aux = p->inicio;

    while(aux != NULL){
        printf("Nome: %s\n", aux->filme->nome);
        aux = aux->prox;
    }
}

void imprimeFilmesReverso(posicaoLista *p){
    filmeLista *aux = p->fim;

    while(aux != NULL){
        printf("Nome: %s\n", aux->filme->nome);
        aux = aux->ant;
    }
}

void imprimeListaFilmesUsuario(usuarioBloco *usuario){
    filmeLista *aux = usuario->posicao->inicio;

    while(aux != NULL){
        printf("Nome: %s\n", aux->filme->nome);
        aux = aux->prox;
    }
}

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