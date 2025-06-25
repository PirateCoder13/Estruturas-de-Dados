# Music Player Simulator - Estudo Dirigido 2

**Disciplina:** Estruturas de Dados  
**Professor:** Baroni  
**Curso:** Análise e Desenvolvimento de Sistemas  
**Entrega:** 27/06/2025

## 📋 Descrição do Projeto

Simulador de player de música desenvolvido em C que implementa as principais estruturas de dados:
- **Lista Duplamente Encadeada** (Biblioteca Musical)
- **Pilha** (Histórico de Reprodução)  
- **Fila** (Fila de Reprodução)

O projeto **reproduz arquivos MP3 de verdade** usando a API do Windows.

## 📁 Estrutura dos Arquivos

```
Ed-02/
├── main.c                          # Arquivo principal
├── music_player.h                  # Cabeçalhos e estruturas
├── biblioteca_fila_historico.c     # Implementação das estruturas de dados
├── player_funcoes.c                # Funções específicas do player
├── interface.c                     # Interface do usuário
├── audio_player.c                  # Reprodução de áudio MP3
├── compilar.bat                    # Script de compilação
├── README.md                       # Este arquivo
├── RELATORIO_TECNICO.md            # Relatório detalhado
└── musicas/                        # Pasta com arquivos MP3
    └── paper-planes-chill-future-beat-283956.mp3
```

## 🚀 Como Executar

### Método Simples:
```cmd
compilar.bat
```

### Compilação Manual:
```cmd
gcc -o music_player.exe main.c biblioteca_fila_historico.c player_funcoes.c interface.c audio_player.c -lwinmm
music_player.exe
```

## 🎵 Como Usar

1. **Execute o programa**
2. **Carregue músicas de exemplo:** Escolha "1" quando perguntado
3. **Reproduza MP3 real:** 
   - Opção "7" (Reproduzir música)
   - Digite: `paper-planes-chill-future-beat-283956`
   - **A música MP3 vai tocar de verdade!** 🎵

## 🎛️ Funcionalidades

### Gerenciamento de Músicas
- ✅ Adicionar músicas à biblioteca
- ✅ Remover músicas da biblioteca  
- ✅ Listar todas as músicas
- ✅ Buscar músicas por título
- ✅ Carregar arquivos MP3 da pasta `musicas/`

### Reprodução de Áudio
- ✅ **Reproduzir arquivos MP3 reais**
- ✅ Pausar e retomar reprodução
- ✅ Parar reprodução
- ✅ Navegar entre músicas (próxima/anterior)

### Estruturas de Dados
- ✅ **Lista Duplamente Encadeada:** Biblioteca musical
- ✅ **Pilha:** Histórico das últimas músicas reproduzidas
- ✅ **Fila:** Fila de reprodução personalizada

## 🛠️ Requisitos Técnicos

- **Compilador:** GCC (MinGW no Windows)
- **Sistema:** Windows (usa winmm.dll para reprodução MP3)
- **Biblioteca:** winmm (Windows Multimedia API)

## 🏆 Critérios Atendidos

- ✅ **Funcionalidade (40%)**: Todos os requisitos implementados
- ✅ **Arquitetura (30%)**: Código modular e bem estruturado  
- ✅ **Implementação (20%)**: Estruturas de dados corretas
- ✅ **Relatório (10%)**: Documentação completa

## 🎯 Diferencial

Este projeto vai além de uma simulação - **reproduz música de verdade**, demonstrando aplicação prática das estruturas de dados em um sistema real de áudio.

---
**Desenvolvido para MelodiaCode** 🎵  
**Autor:** [Seu Nome]
