# RELATÓRIO TÉCNICO - MUSIC PLAYER SIMULATOR

**Disciplina:** Estruturas de Dados  
**Professor:** Baroni  
**Projeto:** Estudo Dirigido 2  
**Empresa Simulada:** MelodiaCode  
**Data:** Junho 2025

## 1. INTRODUÇÃO

Este relatório apresenta o desenvolvimento de um simulador de player de música em linguagem C, implementando as principais estruturas de dados: lista duplamente encadeada, pilha e fila. O projeto foi desenvolvido seguindo os requisitos do Estudo Dirigido 2.

## 2. ESTRUTURAS DE DADOS IMPLEMENTADAS

### 2.1 Lista Duplamente Encadeada (Biblioteca Musical)

**Finalidade:** Armazenar a biblioteca de músicas do usuário.

**Características:**
- Cada nó contém: título, artista, duração, ponteiro para anterior e próximo
- Permite navegação bidirecional
- Inserção sempre no final da lista
- Busca sequencial por título

**Operações Implementadas:**
```c
- criar_biblioteca()      // Inicializa lista vazia
- adicionar_musica()      // Insere no final
- remover_musica()        // Remove por título
- buscar_musica()         // Busca por título
- listar_musicas()        // Exibe toda a biblioteca
```

**Complexidade das Operações:**
- Inserção: O(1) no final
- Busca: O(n) 
- Remoção: O(n)
- Listagem: O(n)

### 2.2 Pilha (Histórico de Reprodução)

**Finalidade:** Manter histórico das músicas reproduzidas recentemente.

**Características:**
- Estrutura LIFO (Last In, First Out)
- Limitada a 10 músicas para controle de memória
- Não permite músicas duplicadas consecutivas

**Operações Implementadas:**
```c
- criar_historico()           // Inicializa pilha vazia
- adicionar_ao_historico()    // Push - adiciona ao topo
- voltar_historico()          // Pop - remove do topo
- mostrar_historico()         // Exibe últimas 5 músicas
```

**Complexidade das Operações:**
- Push: O(1)
- Pop: O(1)
- Peek: O(1)

### 2.3 Fila (Fila de Reprodução)

**Finalidade:** Gerenciar ordem das próximas músicas a serem reproduzidas.

**Características:**
- Estrutura FIFO (First In, First Out)
- Ponteiros para frente e trás
- Tamanho dinâmico

**Operações Implementadas:**
```c
- criar_fila_reproducao()  // Inicializa fila vazia
- adicionar_fila()         // Enqueue - adiciona ao final
- proximo_da_fila()        // Dequeue - remove do início
- mostrar_fila()           // Exibe todas as músicas na fila
```

**Complexidade das Operações:**
- Enqueue: O(1)
- Dequeue: O(1)

## 3. ARQUITETURA DO SISTEMA

### 3.1 Modularização

O projeto foi dividido em módulos para facilitar manutenção e compreensão:

- **music_player.h**: Definições de estruturas e protótipos
- **biblioteca_fila_historico.c**: Implementação das estruturas de dados
- **player_funcoes.c**: Lógica específica do player
- **interface.c**: Interface do usuário e menu
- **main.c**: Função principal e inicialização

### 3.2 Estrutura Principal (MusicPlayer)

```c
typedef struct {
    BibliotecaMusical* biblioteca;      // Lista de todas as músicas
    HistoricoReproducao* historico;     // Pilha de músicas tocadas
    FilaReproducao* fila_reproducao;    // Fila de próximas músicas
    Musica* musica_atual;               // Música sendo reproduzida
    int reproduzindo;                   // Status: 0=parado, 1=tocando, 2=pausado
} MusicPlayer;
```

## 4. FUNCIONALIDADES IMPLEMENTADAS

### 4.1 Gerenciamento de Músicas ✅
- [x] Cadastrar músicas (título, artista, duração)
- [x] Remover músicas da biblioteca
- [x] Listar todas as músicas cadastradas
- [x] Buscar músicas por título

### 4.2 Simulação de Player ✅
- [x] "Reproduzir" uma música (simulação via console)
- [x] Pausar e retomar reprodução
- [x] Navegar entre músicas (próxima, anterior)
- [x] Status do player em tempo real

### 4.3 Histórico e Fila ✅
- [x] Histórico das últimas músicas reproduzidas (pilha)
- [x] Fila de reprodução personalizada
- [x] Navegação automática pela fila

## 5. GERENCIAMENTO DE MEMÓRIA

### 5.1 Alocação Dinâmica
Todas as estruturas utilizam `malloc()` para alocação dinâmica:
- Nós da lista duplamente encadeada
- Nós da pilha de histórico  
- Nós da fila de reprodução
- Estruturas principais (Player, Biblioteca, etc.)

### 5.2 Liberação de Memória
Implementadas funções específicas para liberar memória:
```c
- liberar_biblioteca()
- liberar_historico() 
- liberar_fila()
- liberar_player()
```

## 6. INTERFACE DO USUÁRIO

### 6.1 Menu Interativo
Interface via console com 14 opções principais:
- Gerenciamento da biblioteca
- Controles de reprodução
- Visualização de dados (histórico, fila, status)

### 6.2 Feedback Visual
- Uso de emojis para melhor experiência (quando suportado)
- Mensagens claras de confirmação
- Exibição de status detalhado

## 7. COMPILAÇÃO E EXECUÇÃO

### 7.1 Arquivos Necessários
- Versão modular: 5 arquivos (.h + 4 .c)
- Versão única: 1 arquivo (music_player_completo.c)

### 7.2 Comando de Compilação
```bash
gcc -o music_player main.c biblioteca_fila_historico.c player_funcoes.c interface.c
```

## 8. TESTES REALIZADOS

### 8.1 Testes das Estruturas
- [x] Lista: Inserção, remoção, busca, navegação
- [x] Pilha: Push, pop, controle de limite
- [x] Fila: Enqueue, dequeue, ordem FIFO

### 8.2 Testes de Integração
- [x] Fluxo completo: adicionar → reproduzir → histórico → fila
- [x] Navegação entre músicas
- [x] Controles de reprodução

## 9. PONTOS FORTES

- **Modularidade**: Código bem organizado e reutilizável
- **Simplicidade**: Implementação didática, ideal para aprendizado
- **Completude**: Atende todos os requisitos funcionais
- **Documentação**: Código comentado e documentação completa

## 10. POSSÍVEIS MELHORIAS

- Implementar modo shuffle (reprodução aleatória)
- Adicionar persistência em arquivos
- Melhorar busca (por artista, por duração)
- Implementar playlists nomeadas
- Adicionar validações de entrada mais robustas

## 11. CONCLUSÃO

O projeto Music Player Simulator foi desenvolvido com sucesso, implementando corretamente as três estruturas de dados solicitadas. O código é didático, bem comentado e atende a todos os requisitos funcionais e técnicos do Estudo Dirigido 2.

A implementação demonstra compreensão sólida dos conceitos de:
- Ponteiros e alocação dinâmica
- Estruturas de dados fundamentais
- Modularização de código
- Interface de usuário

O projeto está pronto para compilação e execução, servindo como uma excelente base para aprendizado de estruturas de dados em C.

---

**Desenvolvido por:** [Seu Nome]  
**Turma:** Análise e Desenvolvimento de Sistemas  
**Data de Entrega:** 27/06/2025
