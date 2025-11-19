#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LIVROS 100
#define MAX_EXEMPLARES 10
#define MAX_NOME 50
#define MAX_TITULO 100
#define MAX_AUTOR 100
#define MAX_CPF 12

typedef struct {
    char nome[MAX_NOME];
    char cpf[MAX_CPF];
} PESSOA;

typedef struct {
    int id;
    char titulo[MAX_TITULO];
    char autor[MAX_AUTOR];
    int ano_publicacao;
    int quantidade_disponivel;
    PESSOA pessoas_emprestimo[MAX_EXEMPLARES];
    int num_emprestimos;
} LIVRO;

typedef struct {
    LIVRO livros[MAX_LIVROS];
    int contador_livros;
} BIBLIOTECA;

void exibir_menu();
int buscar_livro_por_id(BIBLIOTECA *b, int id);
int buscar_pessoa_por_cpf(LIVRO *l, const char *cpf);
void exibir_detalhes_livro(LIVRO *l);

void cadastrar_livro(BIBLIOTECA *b);
void consultar_livros(BIBLIOTECA *b);
void emprestar_livro(BIBLIOTECA *b);
void devolver_livro(BIBLIOTECA *b);
void remover_livro(BIBLIOTECA *b);

int main() {
    BIBLIOTECA minha_biblioteca = {.contador_livros = 0};
    int opcao;

    do {
        exibir_menu();
        printf("Escolha uma opção: ");

        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n');
            opcao = -1;
        } else {
            while (getchar() != '\n');
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
            getchar();
        }

    } while (opcao != 6);

    return 0;
}

void exibir_menu() {
    system("clear || cls");
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

int buscar_livro_por_id(BIBLIOTECA *b, int id) {
    for (int i = 0; i < b->contador_livros; i++) {
        if (b->livros[i].id == id) {
            return i;
        }
    }
    return -1;
}

int buscar_pessoa_por_cpf(LIVRO *l, const char *cpf) {
    for (int i = 0; i < l->num_emprestimos; i++) {
        if (strcmp(l->pessoas_emprestimo[i].cpf, cpf) == 0) {
            return i;
        }
    }
    return -1;
}

void exibir_detalhes_livro(LIVRO *l) {
    printf("\n--- DETALHES DO LIVRO (ID: %d) ---\n", l->id);
    printf("  Título: %s\n", l->titulo);
    printf("  Autor: %s\n", l->autor);
    printf("  Ano de Publicação: %d\n", l->ano_publicacao);
    printf("  Exemplares Disponíveis: %d/%d\n", l->quantidade_disponivel, MAX_EXEMPLARES);
    printf("  Empréstimos Ativos: %d\n", l->num_emprestimos);

    if (l->num_emprestimos > 0) {
        printf("  Pessoas com Empréstimo:\n");
        for (int j = 0; j < l->num_emprestimos; j++) {
            printf("    - Nome: %s (CPF: %s)\n", l->pessoas_emprestimo[j].nome, l->pessoas_emprestimo[j].cpf);
        }
    }
    printf("----------------------------------------\n");
}

void cadastrar_livro(BIBLIOTECA *b) {
    printf("## 1. Cadastro de Livros\n");

    if (b->contador_livros >= MAX_LIVROS) {
        printf("ERRO: A biblioteca atingiu o limite máximo de %d livros.\n", MAX_LIVROS);
        return;
    }

    LIVRO novo_livro;
    int id, qtd;

    do {
        printf("Digite o Código Único (ID) do livro: ");
        if (scanf("%d", &id) != 1 || id <= 0) {
            printf("ID inválido. Digite um número inteiro positivo.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (buscar_livro_por_id(b, id) != -1) {
            printf("AVISO: Livro com ID %d já existe. Voltando ao menu...\n", id);
            return;
        }
    } while (id <= 0);
    novo_livro.id = id;

    printf("Digite o Título: ");
    fgets(novo_livro.titulo, MAX_TITULO, stdin);
    novo_livro.titulo[strcspn(novo_livro.titulo, "\n")] = '\0';

    printf("Digite o Autor: ");
    fgets(novo_livro.autor, MAX_AUTOR, stdin);
    novo_livro.autor[strcspn(novo_livro.autor, "\n")] = '\0';

    printf("Digite o Ano de publicação: ");
    scanf("%d", &novo_livro.ano_publicacao);
    while (getchar() != '\n');

    do {
        printf("Digite a Quantidade de exemplares a adicionar (máx %d): ", MAX_EXEMPLARES);
        if (scanf("%d", &qtd) != 1 || qtd <= 0 || qtd > MAX_EXEMPLARES) {
            printf("Quantidade inválida. Digite um número entre 1 e %d.\n", MAX_EXEMPLARES);
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');
    } while (qtd <= 0 || qtd > MAX_EXEMPLARES);
    
    novo_livro.quantidade_disponivel = qtd;
    novo_livro.num_emprestimos = 0;

    b->livros[b->contador_livros] = novo_livro;
    b->contador_livros++;

    printf("\nSUCESSO: Livro '%s' cadastrado com sucesso! ID: %d.\n", novo_livro.titulo, novo_livro.id);
}

void consultar_livros(BIBLIOTECA *b) {
    printf("## 2. Consulta de Livros\n");

    if (b->contador_livros == 0) {
        printf("AVISO: Nenhuma livro cadastrado na biblioteca.\n");
        return;
    }

    int sub_opcao;
    printf("1. Listar todos os livros cadastrados\n");
    printf("2. Buscar um livro específico por ID\n");
    printf("Escolha a opção de consulta: ");
    if (scanf("%d", &sub_opcao) != 1) {
        while (getchar() != '\n');
        printf("Opção inválida.\n");
        return;
    }
    while (getchar() != '\n');

    if (sub_opcao == 1) {
        printf("\n--- LISTA COMPLETA DE LIVROS (%d no total) ---\n", b->contador_livros);
        for (int i = 0; i < b->contador_livros; i++) {
            LIVRO *l = &b->livros[i];
            printf("ID: %d | Título: %s | Autor: %s | Disp.: %d/%d\n",
                   l->id, l->titulo, l->autor, l->quantidade_disponivel, MAX_EXEMPLARES);
        }
        printf("---------------------------------------------\n");
    } else if (sub_opcao == 2) {
        int id_busca;
        printf("Digite o ID do livro que deseja buscar: ");
        if (scanf("%d", &id_busca) != 1) {
            while (getchar() != '\n');
            printf("ID inválido.\n");
            return;
        }
        while (getchar() != '\n');

        int idx = buscar_livro_por_id(b, id_busca);

        if (idx != -1) {
            exibir_detalhes_livro(&b->livros[idx]);
        } else {
            printf("AVISO: Livro com ID %d não encontrado.\n", id_busca);
        }
    } else {
        printf("Opção inválida.\n");
    }
}

void emprestar_livro(BIBLIOTECA *b) {
    printf("## 3. Empréstimo de Livros\n");

    int id_busca;
    printf("Digite o ID do livro a ser emprestado: ");
    if (scanf("%d", &id_busca) != 1) {
        while (getchar() != '\n');
        printf("ID inválido.\n");
        return;
    }
    while (getchar() != '\n');

    int idx_livro = buscar_livro_por_id(b, id_busca);

    if (idx_livro == -1) {
        printf("ERRO: Livro com ID %d não encontrado.\n", id_busca);
        return;
    }

    LIVRO *livro = &b->livros[idx_livro];

    if (livro->quantidade_disponivel == 0) {
        printf("AVISO: O livro '%s' não possui exemplares disponíveis para empréstimo.\n", livro->titulo);
        return;
    }

    PESSOA nova_pessoa;
    printf("Empréstimo do livro: %s\n", livro->titulo);

    printf("Digite o CPF da pessoa (11 dígitos, sem pontos/traços): ");
    fgets(nova_pessoa.cpf, MAX_CPF, stdin);
    nova_pessoa.cpf[strcspn(nova_pessoa.cpf, "\n")] = '\0';

    if (buscar_pessoa_por_cpf(livro, nova_pessoa.cpf) != -1) {
        printf("AVISO: O CPF %s já possui um exemplar de '%s' emprestado.\n", nova_pessoa.cpf, livro->titulo);
        return;
    }

    printf("Digite o Nome completo da pessoa: ");
    fgets(nova_pessoa.nome, MAX_NOME, stdin);
    nova_pessoa.nome[strcspn(nova_pessoa.nome, "\n")] = '\0';

    livro->quantidade_disponivel--;
    livro->pessoas_emprestimo[livro->num_emprestimos] = nova_pessoa;
    livro->num_emprestimos++;

    printf("\nSUCESSO: Livro '%s' emprestado para %s (CPF: %s).\n", 
           livro->titulo, nova_pessoa.nome, nova_pessoa.cpf);
    printf("Agora há %d exemplares disponíveis.\n", livro->quantidade_disponivel);
}

void devolver_livro(BIBLIOTECA *b) {
    printf("## 4. Devolução de Livros\n");

    int id_busca;
    printf("Digite o ID do livro a ser devolvido: ");
    if (scanf("%d", &id_busca) != 1) {
        while (getchar() != '\n');
        printf("ID inválido.\n");
        return;
    }
    while (getchar() != '\n');

    int idx_livro = buscar_livro_por_id(b, id_busca);

    if (idx_livro == -1) {
        printf("ERRO: Livro com ID %d não encontrado.\n", id_busca);
        return;
    }

    LIVRO *livro = &b->livros[idx_livro];

    if (livro->num_emprestimos == 0) {
        printf("AVISO: Não há empréstimos ativos para o livro '%s'.\n", livro->titulo);
        return;
    }

    char cpf_busca[MAX_CPF];
    printf("Devolução do livro: %s\n", livro->titulo);
    printf("Digite o CPF da pessoa que está devolvendo: ");
    fgets(cpf_busca, MAX_CPF, stdin);
    cpf_busca[strcspn(cpf_busca, "\n")] = '\0';

    int idx_pessoa = buscar_pessoa_por_cpf(livro, cpf_busca);

    if (idx_pessoa == -1) {
        printf("AVISO: CPF %s não encontrado como emprestador ativo do livro '%s'.\n", cpf_busca, livro->titulo);
        return;
    }

    livro->quantidade_disponivel++;

    PESSOA pessoa_removida = livro->pessoas_emprestimo[idx_pessoa];
    livro->pessoas_emprestimo[idx_pessoa] = livro->pessoas_emprestimo[livro->num_emprestimos - 1];
    livro->num_emprestimos--;

    printf("\nSUCESSO: Livro '%s' devolvido por %s (CPF: %s).\n", 
           livro->titulo, pessoa_removida.nome, pessoa_removida.cpf);
    printf("Agora há %d exemplares disponíveis.\n", livro->quantidade_disponivel);
}

void remover_livro(BIBLIOTECA *b) {
    printf("## 5. Remoção de Livros\n");

    if (b->contador_livros == 0) {
        printf("AVISO: Nenhuma livro cadastrado para remover.\n");
        return;
    }

    int id_busca;
    printf("Digite o ID do livro a ser excluído: ");
    if (scanf("%d", &id_busca) != 1) {
        while (getchar() != '\n');
        printf("ID inválido.\n");
        return;
    }
    while (getchar() != '\n');

    int idx_livro = buscar_livro_por_id(b, id_busca);

    if (idx_livro == -1) {
        printf("ERRO: Livro com ID %d não encontrado.\n", id_busca);
        return;
    }

    LIVRO *livro_remover = &b->livros[idx_livro];

    if (livro_remover->num_emprestimos > 0) {
        printf("AVISO: O livro '%s' possui %d empréstimo(s) ativo(s). Remova-o mesmo assim? (S/N): ",
               livro_remover->titulo, livro_remover->num_emprestimos);
        char conf;
        scanf(" %c", &conf);
        while (getchar() != '\n');
        if (toupper(conf) != 'S') {
            printf("Remoção cancelada.\n");
            return;
        }
    }

    char titulo_removido[MAX_TITULO];
    strcpy(titulo_removido, livro_remover->titulo);

    b->livros[idx_livro] = b->livros[b->contador_livros - 1];
    b->contador_livros--;

    printf("\nSUCESSO: Livro '%s' (ID: %d) excluído do acervo.\n", titulo_removido, id_busca);
}
