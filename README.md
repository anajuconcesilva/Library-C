## 📚 Sistema de Gerenciamento de Biblioteca (Projeto Individual)

[cite_start]Este projeto foi desenvolvido como trabalho final da disciplina de **Algoritmos e Linguagem de Programação** para o curso de **Engenharia de Software** da **PUC-Campinas**

[cite_start]O objetivo deste projeto é aplicar os conceitos estudados em sala de aula — variáveis, condicionais, loops, vetores, funções e structs — no desenvolvimento de um sistema de gerenciamento de biblioteca. O projeto simula, de forma simples, mas funcional, as principais operações realizadas em uma biblioteca[cite: 12].

---

### 💻 Linguagem de Desenvolvimento

O projeto foi desenvolvido **exclusivamente em linguagem C**.

### ✨ Funcionalidades

O sistema é uma aplicação console, contendo um menu interativo que permite realizar as seguintes operações:

* **1. [cite_start]Cadastro de Livros:** Permite adicionar novos livros ao acervo (até 100 livros). [cite_start]Inclui verificação para que o Código Único (ID) não seja duplicado.
* **2. [cite_start]Consulta de Livros:** Permite listar todos os livros cadastrados ou buscar um livro específico a partir do código (ID).
* **3. [cite_start]Empréstimo de Livros:** Permite registrar o empréstimo, atualizando a quantidade disponível.
* **4. [cite_start]Devolução de Livros:** Permite registrar a devolução, atualizando a quantidade disponível e removendo a pessoa do registro de empréstimos.
* **5. [cite_start]Remoção de Livros:** Permite a exclusão de um livro cadastrado[cite: 43].
* **6. [cite_start]Encerrar o Programa:** Finaliza a execução da aplicação (`return 0` no `main`).

### ⚙️ Estrutura de Dados

Os dados da biblioteca (livros e usuários) são organizados por meio de `structs`, e as operações são implementadas por funções.

### 🚀 Como Compilar e Executar

1.  **Salve o código:** Certifique-se de que o código-fonte esteja salvo em um único arquivo com a extensão `.c` (e.g., `biblioteca.c`).
2.  **Compile:** Use um compilador C (como GCC) no terminal:
    ```bash
    gcc biblioteca.c -o biblioteca
    ```
3.  **Execute:** Rode o arquivo executável gerado:
    ```bash
    ./biblioteca
    ```
    *(Em sistemas Windows, o comando pode ser `biblioteca.exe`)*
