/*
 * MUSIC PLAYER SIMULATOR - ESTRUTURAS DE DADOS
 * Empresa: PiratariaCodificada
 * Autores: Joao Gualberto, Yasmin Pereira, Gabriela Rocca
 * 
 * Implementacao das estruturas de dados:
 * - Lista Duplamente Encadeada (Biblioteca Musical)
 * - Pilha (Historico de Reproducao) 
 * - Fila (Fila de Reproducao)
 */

#include "music_player.h"

// ===========================================
// FUNCOES DA BIBLIOTECA MUSICAL (LISTA DUPLAMENTE ENCADEADA)
// ===========================================

BibliotecaMusical* criar_biblioteca() {
    BibliotecaMusical* biblioteca = (BibliotecaMusical*)malloc(sizeof(BibliotecaMusical));
    biblioteca->primeiro = NULL;
    biblioteca->ultimo = NULL;
    biblioteca->total_musicas = 0;
    return biblioteca;
}

void adicionar_musica(BibliotecaMusical* biblioteca, char* titulo, char* artista, char* arquivo, int duracao) {    // Criar nova musica
    Musica* nova_musica = (Musica*)malloc(sizeof(Musica));
    strcpy(nova_musica->titulo, titulo);
    strcpy(nova_musica->artista, artista);
    strcpy(nova_musica->arquivo, arquivo);
    nova_musica->duracao = duracao;
    nova_musica->anterior = NULL;
    nova_musica->proximo = NULL;
    
    // Se a biblioteca esta vazia
    if (biblioteca->primeiro == NULL) {
        biblioteca->primeiro = nova_musica;
        biblioteca->ultimo = nova_musica;
    } else {
        // Adicionar no final da lista
        biblioteca->ultimo->proximo = nova_musica;
        nova_musica->anterior = biblioteca->ultimo;
        biblioteca->ultimo = nova_musica;
    }
    
    biblioteca->total_musicas++;    printf("Musica '%s' de '%s' adicionada com sucesso!\n", titulo, artista);
}

void adicionar_musica_mp3(BibliotecaMusical* biblioteca, char* arquivo_mp3) {
    // Construir caminho completo
    char caminho_completo[300];
    if (strstr(arquivo_mp3, "musicas\\") == arquivo_mp3 || strstr(arquivo_mp3, "musicas/") == arquivo_mp3) {
        // Ja tem o caminho da pasta musicas
        strcpy(caminho_completo, arquivo_mp3);
    } else if (arquivo_mp3[1] == ':' || arquivo_mp3[0] == '\\' || arquivo_mp3[0] == '/') {
        // Caminho absoluto
        strcpy(caminho_completo, arquivo_mp3);
    } else {
        // Adicionar pasta musicas
        sprintf(caminho_completo, "musicas\\%s", arquivo_mp3);
    }
    
    // Extrair o nome do arquivo para usar como titulo
    char titulo[100];
    char* nome_arquivo = strrchr(caminho_completo, '\\');
    if (nome_arquivo == NULL) {
        nome_arquivo = strrchr(caminho_completo, '/');
    }
    if (nome_arquivo == NULL) {
        nome_arquivo = caminho_completo;
    } else {
        nome_arquivo++; // Pular a barra
    }
    
    // Copiar nome sem extensao
    strcpy(titulo, nome_arquivo);
    char* ponto = strrchr(titulo, '.');
    if (ponto != NULL) {
        *ponto = '\0'; // Remover extensao
    }
    
    // Verificar se o arquivo existe
    FILE* arquivo = fopen(caminho_completo, "rb");
    if (arquivo == NULL) {        printf("Erro: Arquivo '%s' nao encontrado!\n", caminho_completo);
        printf("Verifique se o arquivo esta na pasta 'musicas\\'\n");
        return;
    }
    fclose(arquivo);
      adicionar_musica(biblioteca, titulo, "Artista Desconhecido", caminho_completo, 180); // 3 minutos padrao
}

void carregar_todos_mp3(BibliotecaMusical* biblioteca) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind;
    
    printf("Escaneando pasta musicas/ em busca de arquivos MP3...\n");
    
    // Buscar todos os arquivos .mp3 na pasta musicas
    hFind = FindFirstFile("musicas\\*.mp3", &findFileData);
    
    if (hFind == INVALID_HANDLE_VALUE) {
        printf("Pasta 'musicas/' nao encontrada ou vazia.\n");
        return;
    }
    
    int contador = 0;
    do {
        printf("Encontrado: %s\n", findFileData.cFileName);
        adicionar_musica_mp3(biblioteca, findFileData.cFileName);
        contador++;
    } while (FindNextFile(hFind, &findFileData) != 0);
    
    FindClose(hFind);
    printf("Total de %d arquivo(s) MP3 carregado(s)!\n", contador);
}

void remover_musica(BibliotecaMusical* biblioteca, char* titulo) {
    Musica* atual = biblioteca->primeiro;
    
    // Buscar a musica
    while (atual != NULL) {
        if (strcmp(atual->titulo, titulo) == 0) {
            // Remover da lista
            if (atual->anterior != NULL) {
                atual->anterior->proximo = atual->proximo;
            } else {
                // E o primeiro elemento
                biblioteca->primeiro = atual->proximo;
            }
            
            if (atual->proximo != NULL) {
                atual->proximo->anterior = atual->anterior;
            } else {
                // E o ultimo elemento
                biblioteca->ultimo = atual->anterior;
            }
            
            printf("Musica '%s' removida com sucesso!\n", titulo);
            free(atual);
            biblioteca->total_musicas--;
            return;
        }
        atual = atual->proximo;
    }
    
    printf("Musica '%s' nao encontrada!\n", titulo);
}

void listar_musicas(BibliotecaMusical* biblioteca) {
    if (biblioteca->primeiro == NULL) {
        printf("Nenhuma musica na biblioteca!\n");
        return;
    }
    
    printf("\n=== BIBLIOTECA MUSICAL ===\n");
    printf("Total de musicas: %d\n\n", biblioteca->total_musicas);
    
    Musica* atual = biblioteca->primeiro;
    int contador = 1;
    
    while (atual != NULL) {
        int minutos = atual->duracao / 60;
        int segundos = atual->duracao % 60;
        printf("%d. '%s' - %s (%d:%02d)\n", 
               contador, atual->titulo, atual->artista, minutos, segundos);
        atual = atual->proximo;
        contador++;
    }
    printf("\n");
}

Musica* buscar_musica(BibliotecaMusical* biblioteca, char* titulo) {
    Musica* atual = biblioteca->primeiro;
    
    while (atual != NULL) {
        if (strcmp(atual->titulo, titulo) == 0) {
            return atual;
        }
        atual = atual->proximo;
    }
    
    return NULL; // Nao encontrou
}

// Função para busca por similaridade (busca parcial)
Musica* buscar_musica_similar(BibliotecaMusical* biblioteca, char* termo_busca) {
    Musica* atual = biblioteca->primeiro;
    Musica* melhor_match = NULL;
    
    // Converter termo de busca para minúsculo
    char termo_lower[100];
    strcpy(termo_lower, termo_busca);
    for (int i = 0; termo_lower[i]; i++) {
        if (termo_lower[i] >= 'A' && termo_lower[i] <= 'Z') {
            termo_lower[i] = termo_lower[i] + 32;
        }
    }
    
    while (atual != NULL) {
        // Converter título atual para minúsculo
        char titulo_lower[100];
        strcpy(titulo_lower, atual->titulo);
        for (int i = 0; titulo_lower[i]; i++) {
            if (titulo_lower[i] >= 'A' && titulo_lower[i] <= 'Z') {
                titulo_lower[i] = titulo_lower[i] + 32;
            }
        }
        
        // Verificar se o termo está contido no título
        if (strstr(titulo_lower, termo_lower) != NULL) {
            melhor_match = atual;
            // Se encontrou uma correspondência exata, retorna imediatamente
            if (strcmp(titulo_lower, termo_lower) == 0) {
                return atual;
            }
        }
        atual = atual->proximo;
    }
    
    return melhor_match; // Retorna a melhor correspondência ou NULL
}

void liberar_biblioteca(BibliotecaMusical* biblioteca) {
    Musica* atual = biblioteca->primeiro;
    Musica* proximo;
    
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    
    free(biblioteca);
}

// ===========================================
// FUNCOES DO HISTORICO (PILHA)
// ===========================================

HistoricoReproducao* criar_historico() {
    HistoricoReproducao* historico = (HistoricoReproducao*)malloc(sizeof(HistoricoReproducao));
    historico->topo = NULL;
    historico->tamanho = 0;
    return historico;
}

void adicionar_ao_historico(HistoricoReproducao* historico, Musica* musica) {
    // Nao adicionar musica duplicada consecutiva
    if (historico->topo != NULL && historico->topo->musica == musica) {
        return;
    }
    
    NoHistorico* novo_no = (NoHistorico*)malloc(sizeof(NoHistorico));
    novo_no->musica = musica;
    novo_no->proximo = historico->topo;
    historico->topo = novo_no;
    historico->tamanho++;
    
    // Limitar historico a 10 musicas
    if (historico->tamanho > 10) {
        NoHistorico* atual = historico->topo;
        while (atual->proximo->proximo != NULL) {
            atual = atual->proximo;
        }
        free(atual->proximo);
        atual->proximo = NULL;
        historico->tamanho--;
    }
}

Musica* voltar_historico(HistoricoReproducao* historico) {
    if (historico->topo == NULL) {
        printf("Historico vazio!\n");
        return NULL;
    }
    
    NoHistorico* removido = historico->topo;
    Musica* musica = removido->musica;
    historico->topo = historico->topo->proximo;
    free(removido);
    historico->tamanho--;
    
    return musica;
}

void mostrar_historico(HistoricoReproducao* historico) {
    if (historico->topo == NULL) {
        printf("Historico vazio!\n");
        return;
    }
    
    printf("\n=== HISTORICO DE REPRODUCAO ===\n");
    NoHistorico* atual = historico->topo;
    int contador = 1;
    
    while (atual != NULL && contador <= 5) { // Mostrar apenas as 5 ultimas
        printf("%d. '%s' - %s\n", contador, atual->musica->titulo, atual->musica->artista);
        atual = atual->proximo;
        contador++;
    }
    printf("\n");
}

void liberar_historico(HistoricoReproducao* historico) {
    NoHistorico* atual = historico->topo;
    NoHistorico* proximo;
    
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    
    free(historico);
}

// ===========================================
// FUNCOES DA FILA DE REPRODUCAO
// ===========================================

FilaReproducao* criar_fila_reproducao() {
    FilaReproducao* fila = (FilaReproducao*)malloc(sizeof(FilaReproducao));
    fila->frente = NULL;
    fila->tras = NULL;
    fila->tamanho = 0;
    return fila;
}

void adicionar_fila(FilaReproducao* fila, Musica* musica) {
    NoFila* novo_no = (NoFila*)malloc(sizeof(NoFila));
    novo_no->musica = musica;
    novo_no->proximo = NULL;
    
    if (fila->tras == NULL) {
        // Fila vazia
        fila->frente = novo_no;
        fila->tras = novo_no;
    } else {
        fila->tras->proximo = novo_no;
        fila->tras = novo_no;
    }
    
    fila->tamanho++;
    printf("'%s' adicionada a fila de reproducao!\n", musica->titulo);
}

Musica* proximo_da_fila(FilaReproducao* fila) {
    if (fila->frente == NULL) {
        return NULL;
    }
    
    NoFila* removido = fila->frente;
    Musica* musica = removido->musica;
    fila->frente = fila->frente->proximo;
    
    if (fila->frente == NULL) {
        fila->tras = NULL;
    }
    
    free(removido);
    fila->tamanho--;
    
    return musica;
}

void mostrar_fila(FilaReproducao* fila) {
    if (fila->frente == NULL) {
        printf("Fila de reprodução vazia!\n");
        return;
    }
    
    printf("\n=== FILA DE REPRODUÇÃO ===\n");
    printf("Próximas %d músicas:\n", fila->tamanho);
    
    NoFila* atual = fila->frente;
    int contador = 1;
    
    while (atual != NULL) {
        printf("%d. '%s' - %s\n", contador, atual->musica->titulo, atual->musica->artista);
        atual = atual->proximo;
        contador++;
    }
    printf("\n");
}

void liberar_fila(FilaReproducao* fila) {
    NoFila* atual = fila->frente;
    NoFila* proximo;
    
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    
    free(fila);
}
