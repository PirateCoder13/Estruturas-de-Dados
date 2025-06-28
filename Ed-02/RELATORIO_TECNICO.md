# RELATÓRIO TÉCNICO - SIMULADOR DE PLAYER DE MÚSICAS

**Universidade Tuiuti do Paraná**  
**Curso:** Análise e Desenvolvimento de Sistemas  
**Disciplina:** Estruturas de Dados  
**Professor:** Baroni  
**Data:** 27/06/2025  

---

## EQUIPE DE DESENVOLVIMENTO

**Empresa Fictícia:** PiratariaCodificada

| **Nome** | **Função** | **Responsabilidades** |
|----------|------------|----------------------|
| **João Gualberto** | Líder Técnico & Desenvolvedor Sênior | • Arquitetura do sistema e estruturas de dados principais<br>• Implementação da busca inteligente por similaridade<br>• Sistema de histórico com pilha e modo shuffle<br>• Finalização e integração de todos os módulos |
| **Yasmin Pereira** | Desenvolvedora | • Interface do usuário e menu interativo<br>• Sistema de fila de reprodução<br>• Validação de entrada e tratamento de erros |
| **Gabriela Rocca** | Desenvolvedora | • Gerenciamento de biblioteca musical (lista duplamente encadeada)<br>• Funcionalidades de player (reproduzir, pausar, parar)<br>• Sistema de carregamento automático de arquivos MP3 |

---

## TECNOLOGIAS UTILIZADAS

- **Linguagem:** C (Padrão C99)
- **Compilador:** MinGW GCC
- **Sistema Operacional:** Windows 10/11
- **APIs:** Windows Multimedia API (winmm.lib)

---

## ESTRUTURAS DE DADOS IMPLEMENTADAS

### 1. **Lista Duplamente Encadeada** (Biblioteca Musical)
```c
typedef struct Musica {
    char titulo[100];
    char artista[100]; 
    char arquivo[200];
    int duracao;
    struct Musica* anterior;
    struct Musica* proximo;
} Musica;
```
**Responsável:** Gabriela Rocca

### 2. **Pilha** (Histórico de Reprodução)
```c
typedef struct NoHistorico {
    Musica* musica;
    struct NoHistorico* proximo;
} NoHistorico;
```
**Responsável:** João Gualberto

### 3. **Fila** (Fila de Reprodução)
```c
typedef struct NoFila {
    Musica* musica;
    struct NoFila* proximo;
} NoFila;
```
**Responsável:** Yasmin Pereira

---

## FUNCIONALIDADES IMPLEMENTADAS

### ✅ **Requisitos Básicos Atendidos:**
1. **Gerenciamento de Músicas** - Cadastrar, remover, listar e buscar
2. **Simulação de Playlist** - Navegação entre músicas
3. **Histórico de Reprodução** - Pilha com últimas músicas tocadas
4. **Fila de Reprodução** - Sistema de fila para próximas músicas
5. **Funcionalidades de Simulação** - Reproduzir, pausar, avançar/retroceder
6. **Modo Aleatório (Shuffle)** - Sistema de reprodução aleatória

### 🌟 **Funcionalidades Extras:**
- **Busca Inteligente:** Sistema de busca por similaridade (não apenas exata)
- **Carregamento Automático:** Escaneia pasta de músicas e carrega arquivos MP3
- **Reprodução Real:** Integração com Windows API para tocar arquivos reais
- **Interface Profissional:** Menu interativo com feedback detalhado

---

## ARQUITETURA DO SISTEMA

```
music_player.h          # Estruturas e protótipos
├── main.c              # Função principal
├── interface.c         # Interface do usuário (Yasmin)
├── biblioteca_fila_historico.c  # Estruturas de dados (Gabriela + João)
├── player_funcoes.c    # Lógica do player (João + Gabriela)
└── audio_player.c      # Reprodução de áudio (Gabriela)
```

---

## DESTAQUES TÉCNICOS

### **Busca por Similaridade** (João Gualberto)
Implementação de algoritmo que permite buscar músicas digitando apenas parte do nome:
- Conversão para minúsculas (case-insensitive)
- Busca por substring usando `strstr()`
- Priorização de correspondências exatas

### **Modo Shuffle** (João Gualberto)
Sistema de reprodução aleatória com:
- Geração de números aleatórios baseada em `time()`
- Navegação inteligente na lista para o índice sorteado
- Integração com o sistema de navegação existente

### **Gerenciamento de Memória**
- Alocação dinâmica para todas as estruturas
- Funções específicas de liberação (`liberar_*`)
- Prevenção de vazamentos de memória

---

## COMPILAÇÃO E EXECUÇÃO

```bash
# Compilar o projeto
gcc -o music_player.exe main.c biblioteca_fila_historico.c player_funcoes.c interface.c audio_player.c -lwinmm

# Executar
./music_player.exe
```

---

## CONCLUSÃO

O projeto **Music Player Simulator** foi desenvolvido com sucesso, atendendo a todos os requisitos funcionais e técnicos especificados. A equipe da PiratariaCodificada demonstrou domínio completo das estruturas de dados fundamentais (listas, pilhas e filas) e implementou funcionalidades extras que elevam a qualidade do sistema.

O projeto serve como excelente demonstração prática de conceitos de estruturas de dados aplicados em um contexto real e familiar aos usuários.

---

**Projeto finalizado em:** 27 de Junho de 2025  
**Status:** ✅ Completo e Funcional
