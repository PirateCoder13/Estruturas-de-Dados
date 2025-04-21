package ed_estrutura_dados;

import java.util.Scanner;

/**
 * A classe `BibliotecaDigital` simula um sistema de gerenciamento de uma
 * biblioteca digital.
 * Ela permite cadastrar, buscar e remover livros, mantendo um controle sobre o
 * acervo disponível.
 */
public class BibliotecaDigital {
    /**
     * `CAPACIDADE` é uma constante que define o tamanho máximo do acervo de
     * livros que a biblioteca pode armazenar.
     * Este valor é fixo e não pode ser alterado durante a execução do programa.
     */
    private static final int CAPACIDADE = 100;
    /**
     * `acervo` é um array de objetos `Livro` que representa o conjunto de livros
     * armazenados na biblioteca.
     * Cada posição do array pode conter um objeto `Livro`, representando um livro
     * específico.
     */
    private static Livro[] acervo = new Livro[CAPACIDADE];
    /**
     * `totalLivros` é uma variável que armazena a quantidade atual de livros
     * presentes no acervo.
     * Ela é incrementada quando um novo livro é adicionado e decrementada quando
     * um livro é removido.
     */
    private static int totalLivros = 0;

    /**
     * A classe interna `Livro` representa um livro individual dentro do sistema
     * da biblioteca.
     * Cada livro é caracterizado por seu título, autor e número de páginas.
     * Esta classe é estática e interna à classe `BibliotecaDigital`.
     */
    static class Livro {
        String titulo;
        String autor;
        int paginas;

        /**
         * Construtor para a classe `Livro`.
         * Este construtor inicializa um novo objeto `Livro` com os dados
         * fornecidos.
         * 
         * @param titulo  O título do livro.
         * @param autor   O autor do livro.
         * @param paginas O número de páginas do livro.
         */
        public Livro(String titulo, String autor, int paginas) {
            this.titulo = titulo;
            this.autor = autor;
            this.paginas = paginas;
        }
    }

    /**
     * O método `main` é o ponto de entrada principal do programa.
     * Ele exibe um menu interativo para o usuário, permitindo que ele escolha
     * entre as operações disponíveis no sistema da biblioteca.
     *
     * @param args Argumentos de linha de comando (não utilizados).
     */
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int opcao;

        do {
            System.out.println("\n=== SISTEMA BIBLIOTECA DIGITAL ===");
            System.out.println("1. Cadastrar novo livro");
            System.out.println("2. Buscar livro por título");
            System.out.println("3. Buscar livros por autor");
            System.out.println("4. Remover livro");
            System.out.println("0. Sair do sistema");
            System.out.print("Opção: ");
            opcao = input.nextInt();
            input.nextLine(); // Limpar buffer
            // Estrutura de controle switch para as opções do menu.
            switch (opcao) {
                case 1 -> inserirLivro(input);
                case 2 -> buscarPorTitulo(input);
                case 3 -> buscarPorAutor(input);
                case 4 -> removerLivro(input);
                case 0 -> System.out.println("Encerrando sistema...");
                default -> System.out.println("Opção inválida!");
            }
        } while (opcao != 0);
        input.close();
    }

    /**
     * O método `inserirLivro` adiciona um novo livro ao acervo da biblioteca.
     * Ele solicita ao usuário o título, autor e número de páginas do livro.
     * A complexidade deste método é O(1), pois a inserção é feita no final do
     * array.
     *
     * @param input Scanner para leitura de dados do usuário.
     */
    private static void inserirLivro(Scanner input) {
        if (totalLivros >= CAPACIDADE) {
            System.out.println("Erro: Acervo lotado!");
            return;
        }

        System.out.print("Título do livro: ");
        String titulo = input.nextLine();
        System.out.print("Autor: ");
        String autor = input.nextLine();
        System.out.print("Número de páginas: ");
        int paginas = input.nextInt();
        input.nextLine(); // Limpar buffer

        acervo[totalLivros] = new Livro(titulo, autor, paginas);
        totalLivros++;
        System.out.println("Livro cadastrado com sucesso!");
    }

    /**
     * O método `buscarPorTitulo` realiza uma busca no acervo da biblioteca por
     * livros que contenham um determinado título.
     * A complexidade deste método é O(n), pois ele realiza uma busca linear no
     * array.
     *
     * @param input Scanner para leitura de dados do usuário.
     */

    private static void buscarPorTitulo(Scanner input) {
        System.out.print("Digite o título para busca: ");
        String busca = input.nextLine().trim().toLowerCase();
        int encontrados = 0;

        for (int i = 0; i < totalLivros; i++) {
            if (acervo[i].titulo.toLowerCase().contains(busca)) {
                exibirLivro(acervo[i]);
                encontrados++;
            }
        }
        System.out.println(encontrados + " livro(s) encontrado(s)");
    }

    /**
     * O método `buscarPorAutor` realiza uma busca no acervo da biblioteca por
     * livros que contenham um determinado autor.
     * A complexidade deste método é O(n), pois ele realiza uma busca linear no
     * array.
     *
     * @param input Scanner para leitura de dados do usuário.
     */

    private static void buscarPorAutor(Scanner input) {
        System.out.print("Digite o autor para busca: ");
        String busca = input.nextLine().trim().toLowerCase();
        int encontrados = 0;

        for (int i = 0; i < totalLivros; i++) {
            if (acervo[i].autor.toLowerCase().contains(busca)) {
                exibirLivro(acervo[i]);
                encontrados++;
            }
        }
        System.out.println(encontrados + " livro(s) encontrado(s)");
    }

    /**
     * O método `removerLivro` remove um livro específico do acervo da biblioteca
     * com base no título fornecido pelo usuário.
     * A complexidade deste método é O(n), pois ele realiza uma busca linear e
     * desloca os elementos do array.
     *
     * @param input Scanner para leitura de dados do usuário.
     */

    private static void removerLivro(Scanner input) {
        System.out.print("Digite o título exato do livro para remover: ");
        String titulo = input.nextLine();
        int posicao = -1;

        // Busca linear
        for (int i = 0; i < totalLivros; i++) {
            if (acervo[i].titulo.equalsIgnoreCase(titulo)) {
                posicao = i;
                break;
            }
        }

        if (posicao == -1) {
            System.out.println("Livro não encontrado!");
            return;
        }

        // Deslocamento de elementos
        for (int i = posicao; i < totalLivros - 1; i++) {
            acervo[i] = acervo[i + 1];
        }
        acervo[totalLivros - 1] = null;
        totalLivros--;
        System.out.println("Livro removido com sucesso!");
    }

    /**
     * O método `exibirLivro` exibe os detalhes de um livro específico,
     * incluindo seu título, autor e número de páginas.
     *
     * @param livro Objeto Livro a ser exibido.
     */

    private static void exibirLivro(Livro livro) {
        System.out.println("\nTítulo: " + livro.titulo);
        System.out.println("Autor: " + livro.autor);
        System.out.println("Páginas: " + livro.paginas);
    }
}
