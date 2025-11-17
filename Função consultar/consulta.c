void consultar_livros(BIBLIOTECA *b) {
    printf("2. Consulta de Livros\n");

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
        // Listar todos os livros cadastrados
        printf("\n--- LISTA COMPLETA DE LIVROS (%d no total) ---\n", b->contador_livros);
        for (int i = 0; i < b->contador_livros; i++) {
            LIVRO *l = &b->livros[i];
            printf("ID: %d | Título: %s | Autor: %s | Disp.: %d/%d\n",
                   l->id, l->titulo, l->autor, l->quantidade_disponivel, MAX_EXEMPLARES);
        }
        printf("---------------------------------------------\n");
    } else if (sub_opcao == 2) {
        // Buscar um livro específico a partir do código (ID)
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