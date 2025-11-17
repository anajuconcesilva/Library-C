void cadastrar_livro(BIBLIOTECA *b) {
    printf("## 1. Cadastro de Livros\n");

    if (b->contador_livros >= MAX_LIVROS) {
        printf("ERRO: A biblioteca atingiu o limite máximo de %d livros cadastrados.\n", MAX_LIVROS);
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
            // Caso seja inserido um livro com ID já existente, o programa deverá
            // exibir um aviso e retornar ao menu.
            printf("AVISO: Livro com ID %d já existe. Voltando ao menu...\n", id);
            return;
        }
    } while (id <= 0);
    novo_livro.id = id;

    // Leitura dos demais dados
    printf("Digite o Título: ");
    fgets(novo_livro.titulo, MAX_TITULO, stdin);
    novo_livro.titulo[strcspn(novo_livro.titulo, "\n")] = '\0';

    printf("Digite o Autor: ");
    fgets(novo_livro.autor, MAX_AUTOR, stdin);
    novo_livro.autor[strcspn(novo_livro.autor, "\n")] = '\0';

    printf("Digite o Ano de publicação: ");
    scanf("%d", &novo_livro.ano_publicacao);
    while (getchar() != '\n');

    // Leitura e validação da quantidade de exemplares
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

    // Adiciona o novo livro ao vetor da biblioteca e incrementa o contador
    b->livros[b->contador_livros] = novo_livro;
    b->contador_livros++;

    printf("\nSUCESSO: Livro '%s' cadastrado com sucesso! ID: %d.\n", novo_livro.titulo, novo_livro.id);
}