#include <stdio.h>
#include <stdlib.h>
#include "filmes.h"

//Declaracao de funcoes
void exibirMenu();
//void imprimeFilmesEmOrdem(posicaoLista *p);
//void imprimeFilmesReverso(posicaoLista *p);

int main() {


    int escolha;
    int funcionando = 1;

    while (funcionando) {
        exibirMenu();
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                //criarCadastro(); Esses comentário são só para ilustrar o que deve ser feito.
                break;
            case 2:
                //listarAlunos();
                break;
            case 3:
                //buscarAluno();
                break;
            case 4:
                //listarTodosFilmes();
                break;
            case 5:
                //buscarFilme();
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
            case 0:
                printf("Encerrando o programa. Até mais!\n");
                funcionando = 0;
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
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
    printf("0) Sair\n");
    printf("==============================\n");
    printf("Escolha uma opção: ");
}
