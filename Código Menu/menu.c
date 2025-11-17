#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIVROS 100
#define MAX_PESSOAS_POR_LIVRO 10

//STRUCT PESSOA
typedef struct {
    char nome[50];
    char cpf[12];
} PESSOA;

// STRUCT LIVRO
typedef struct {
    int id;
    char titulo[100];
    char autor[100];
    int ano_publicacao;
    int quantidade_disponivel;
    PESSOA pessoas_emprestimo[MAX_PESSOAS_POR_LIVRO];
    int num_emprestimos;
} LIVRO;

// STRUCT BIBLIOTECA
typedef struct {
    LIVRO livros[MAX_LIVROS];
    int contador_livros;
} BIBLIOTECA;

void exibir_menu();
void cadastrar_livro(BIBLIOTECA *b); //Cadastro de livros 
void consultar_livros(BIBLIOTECA *b); //Consulta de livros 
void emprestar_livro(BIBLIOTECA *b); // Empréstimo de livros
void devolver_livro(BIBLIOTECA *b);  // Devolução de livros
void remover_livro(BIBLIOTECA *b);   // Remoção de livros

int main() {
    BIBLIOTECA minha_biblioteca = {.contador_livros = 0};

    int opcao;

    do {
        exibir_menu();
        printf("Escolha uma opção: ");
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n');
            opcao = -1;
        }

        switch (opcao) {
            case 1:
                cadastrar_livro(&minha_biblioteca);
                break;
            case 2:
                consultar_livros(&minha_biblioteca);
                break;
            case 3:
                emprestar_livro(&minha_biblioteca);
                break;
            case 4:
                devolver_livro(&minha_biblioteca);
                break;
            case 5:
                remover_livro(&minha_biblioteca);
                break;
            case 6:
                printf("\nEncerrando o programa. Obrigado!\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }
        if (opcao != 6) {
            printf("\nPressione ENTER para continuar...");
            while (getchar() != '\n');
            getchar();
        }

    } while (opcao != 6);

    return 0;
}

//MENU
void exibir_menu() {
    system("clear || cls");
    printf("==========================================\n");
    printf("  SISTEMA DE GERENCIAMENTO DE BIBLIOTECA\n");
    printf("==========================================\n");
    printf("1. Cadastro de livros\n");
    printf("2. Consulta de livros\n");
    printf("3. Empréstimo de livros\n");
    printf("4. Devolução de livros\n");
    printf("5. Remoção de livros\n");
    printf("6. Encerrar o programa\n");
    printf("------------------------------------------\n");
}
