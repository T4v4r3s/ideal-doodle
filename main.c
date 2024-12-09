#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filmes.h"
#include "usuarios.h"

//Declaracao de funcoes
void exibirMenu();
void imprimeFilmesEmOrdem(posicaoLista *p);
void imprimeFilmesReverso(posicaoLista *p);

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
    char nomeFilme[50];

    //Inicialização das estruturas
    usuarioArvore *usuarios = inicializaArvoreUsuarios();
    posicaoLista filmes;

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
                    // Listar Filmes

                    printf("Escolha a forma de impressao:\n");
                    printf("1 - Em ordem\n");
                    printf("2 - Reverso\n");

                    scanf("%d", &escolhaPrint);

                    if(escolhaPrint == 1){
                        imprimeFilmesEmOrdem(&filmes);
                    } else if(escolhaPrint == 2){
                        imprimeFilmesReverso(&filmes);
                    } else {
                        printf("Opcao invalida\n");
                    }

                    break;
                case 5:
                    // Buscar Filme

                    char nomeFilme[50];
                    printf("Informe o nome do filme que deseja buscar: ");
                    scanf("%s", nomeFilme);

                    filmeBloco *buscado = buscaFilme(filmes.inicio, nomeFilme);

                    if(buscado == NULL){
                        printf("Filme nao encontrado\n");
                    } else {
                        printf("Nome: %s\n", buscado->nome); // Podemos só falar que foi encontrado se quisermos
                    }
                    
                    break;
                case 6:
                    //recomendarColegaCinema();
                    break;
                case 7:
                    //recomendarColegaDiferente();
                    break;
                case 8:
                    //salvarDadosEmArquivo();
                    break;
                case 9:
                    //exibirDadosArvore();
                    break;
                case 10:
                    //removerAluno();
                    break;
                case 11:
                    //funcionalidadeExtra();
                    break;
                case 12:
                    // Cadastrar Filme

                    printf("Informe o nome do filme que deseja cadastrar: ");
                    scanf("%s", nomeFilme);

                    filmeBloco *novoFilme = criaBlocoFilme(nomeFilme);
                    insereFilmeOrdenado(&filmes, novoFilme);

                    break;
                case 13:
                    // Remover Filme

                    printf("Informe o nome do filme que deseja remover: ");
                    scanf("%s", nomeFilme);

                    removeFilme(&filmes, nomeFilme);

                    break;
                case 0:
                    printf("Encerrando o programa. Até mais!\n");

                    // Liberar memória
                    destroiListaFilmes(&filmes);
                    deletaRecursivamenteTodaArvore(usuarios->raiz);

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
    printf("11) Funcionalidade extra\n");
    printf("12) Cadastrar filme\n");
    printf("13) Remover filme\n");
    printf("0) Sair\n");
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