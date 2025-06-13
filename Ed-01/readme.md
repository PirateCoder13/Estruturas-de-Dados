# Relatório - 1º Estudo Dirigido de Estruturas de Dados

**Universidade Tuiuti do Paraná**
Curso: Análise e Desenvolvimento de Sistemas
Disciplina: Estruturas de Dados
Professor: Baroni
Grupo: João, Yasmin, Luiz
Data de entrega: 23/04/2025

---

## Introdução

Este relatório documenta o desenvolvimento de um sistema de gerenciamento de livros para a Biblioteca Imaginária Digital (BiD), conforme especificado no 1º Estudo Dirigido de Estruturas de Dados. O projeto visa implementar um programa em Java capaz de cadastrar, buscar e remover livros, utilizando vetores como estrutura de dados principal.

---

## Estrutura de Dados Escolhida

A estrutura de dados escolhida para este projeto foi um **vetor de objetos** do tipo `Livro`. Cada objeto `Livro` armazena informações como título, autor e número de páginas. A escolha do vetor foi motivada por sua simplicidade, eficiência para conjuntos de dados de tamanho limitado e conformidade com o requisito de utilizar vetores.

---

## Funcionalidades Implementadas

O sistema implementa as seguintes funcionalidades:

*   **Inserção:** Permite adicionar novos livros ao final do vetor.
*   **Busca:** Possibilita a busca de livros por título ou autor.
*   **Remoção:** Remove um livro específico pelo título, reorganizando o vetor.
*   **Interface:** Fornece um menu textual simples para interação do usuário.

---

## Justificativa das Escolhas

As escolhas de design foram justificadas da seguinte forma:

*   **Vetor:** A escolha do vetor foi baseada em sua facilidade de implementação e adequação para o tamanho esperado do acervo de livros.
*   **Classe `Livro`:** A criação da classe `Livro` foi essencial para organizar o código e facilitar a manipulação dos dados dos livros.
*   **Busca e Remoção Lineares:** As operações de busca e remoção foram implementadas de forma linear, o que é adequado para o tamanho do acervo e simplifica a lógica do programa.

---

## Código Fonte

O código fonte do projeto está estruturado em um único arquivo `Main.java`, que contém a classe `Livro` e a classe `Main`.

### Classe `Livro`

```java
class Livro {
    String titulo;
    String autor;
    int numPaginas;

    public Livro(String titulo, String autor, int numPaginas) {
        this.titulo = titulo;
        this.autor = autor;
        this.numPaginas = numPaginas;
    }
}
```

### Classe `Main`

```java
import java.util.Scanner;

public class Main {
    static Livro[] biblioteca = new Livro[100];
    static int numLivros = 0;
    static Scanner scanner = new Scanner(System.in);

    // ... (resto do código: inserirLivro, buscarLivro, removerLivro, exibirMenu, main)

    public static void main(String[] args) {
        exibirMenu();
    }

    // ... (métodos inserirLivro, buscarLivro, removerLivro, exibirMenu)

    static void inserirLivro() {
        // ... (implementação da inserção)
    }

    static void buscarLivro() {
        // ... (implementação da busca)
    }

    static void removerLivro() {
        // ... (implementação da remoção)
    }

    static void exibirMenu() {
        // ... (implementação do menu)
    }
}
```

O código completo está disponível no arquivo `Main.java`.

---

## Divisão das Tarefas

- **João:** Responsável pela implementação da função de remoção e pela estrutura do vetor.
- **Yasmin:** Responsável pelas funções de busca e colaborou nos testes.
- **Luiz:** Responsável pela função de inserção e pela interface do menu.

---

## Conclusão

O sistema desenvolvido atende a todos os requisitos do projeto, permitindo a inserção, busca e remoção de livros de forma eficiente, utilizando vetores. O código foi organizado em um único arquivo `Main.java`, facilitando a entrega e a avaliação. O projeto demonstra a aplicação prática de vetores e programação orientada a objetos em Java.

---