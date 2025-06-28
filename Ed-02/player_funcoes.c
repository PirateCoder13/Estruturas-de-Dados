/*
 * MUSIC PLAYER SIMULATOR - FUNCOES DO PLAYER
 * Empresa: PiratariaCodificada
 * Autores: Joao Gualberto, Yasmin Pereira, Gabriela Rocca
 *
 * Modulo com as funcionalidades principais do player de musica
 */

#include "music_player.h"

// ===========================================
// FUNCOES DO PLAYER PRINCIPAL
// ===========================================

MusicPlayer* criar_player() {
    MusicPlayer* player = (MusicPlayer*)malloc(sizeof(MusicPlayer));
    player->biblioteca = criar_biblioteca();
    player->historico = criar_historico();
    player->fila_reproducao = criar_fila_reproducao();
    player->musica_atual = NULL;
    player->reproduzindo = 0; // 0 = parado
    player->shuffle_ativo = 0; // shuffle desativado por padrão
    return player;
}

void reproduzir_musica(MusicPlayer* player, Musica* musica) {
    if (musica == NULL) {
        printf("Musica invalida!\n");
        return;
    }
    
    // Adicionar musica atual ao historico (se houver)
    if (player->musica_atual != NULL) {
        adicionar_ao_historico(player->historico, player->musica_atual);
    }
    
    player->musica_atual = musica;
    player->reproduzindo = 1; // tocando
    
    printf("\n>> REPRODUZINDO: '%s' - %s\n", musica->titulo, musica->artista);
    int minutos = musica->duracao / 60;
    int segundos = musica->duracao % 60;
    printf("   Duracao: %d:%02d\n", minutos, segundos);
    printf("   Arquivo: %s\n", musica->arquivo);
    
    // Reproduzir o arquivo MP3 real
    if (strlen(musica->arquivo) > 0) {
        tocar_arquivo_mp3(musica->arquivo);
    }
    
    printf("   Status: Tocando\n\n");
}

void pausar_player(MusicPlayer* player) {
    if (player->musica_atual == NULL) {
        printf("Nenhuma musica esta tocando!\n");
        return;
    }
    
    if (player->reproduzindo == 1) {
        player->reproduzindo = 2; // pausado        pausar_reproducao(); // Pausar audio real
        printf("|| Musica pausada: '%s'\n", player->musica_atual->titulo);
    } else if (player->reproduzindo == 2) {
        player->reproduzindo = 1; // retomar
        retomar_reproducao(); // Retomar audio real
        printf(">> Retomando: '%s'\n", player->musica_atual->titulo);
    } else {
        printf("Nenhuma musica esta tocando!\n");
    }
}

void parar_player(MusicPlayer* player) {
    if (player->musica_atual == NULL) {
        printf("Nenhuma musica esta tocando!\n");
        return;
    }
    
    printf("[] Parando: '%s'\n", player->musica_atual->titulo);    parar_reproducao(); // Parar audio real
    player->reproduzindo = 0; // parado
    // Nao limpar musica_atual para permitir retomar
}

void proximo_musica(MusicPlayer* player) {
    // Primeiro, verificar se ha musica na fila
    Musica* proxima = proximo_da_fila(player->fila_reproducao);
    
    if (proxima != NULL) {
        reproduzir_musica(player, proxima);
        return;
    }
    
    // Verificar se o shuffle está ativo
    if (player->shuffle_ativo) {
        Musica* musica_aleatoria = obter_musica_aleatoria(player->biblioteca);
        if (musica_aleatoria != NULL) {
            reproduzir_musica(player, musica_aleatoria);
            return;
        }
    }
    
    // Se nao ha fila e shuffle desativado, tentar proxima da biblioteca
    if (player->musica_atual != NULL && player->musica_atual->proximo != NULL) {
        reproduzir_musica(player, player->musica_atual->proximo);
    } else {
        printf("Nao ha proxima musica!\n");
    }
}

void anterior_musica(MusicPlayer* player) {
    // Tentar voltar do historico
    Musica* anterior = voltar_historico(player->historico);
    
    if (anterior != NULL) {
        // Parar reprodução atual se estiver tocando
        if (player->reproduzindo == 1) {
            parar_reproducao();
        }
        
        player->musica_atual = anterior;
        player->reproduzindo = 1;
        printf("<< Voltando para: '%s' - %s\n", anterior->titulo, anterior->artista);
        
        // Reproduzir a música do histórico
        tocar_arquivo_mp3(anterior->arquivo);
        
        int min = anterior->duracao / 60;
        int seg = anterior->duracao % 60;
        printf("   Duracao: %d:%02d\n", min, seg);
        printf("   Arquivo: %s\n", anterior->arquivo);
        printf("   Status: Tocando\n");
    } else if (player->musica_atual != NULL && player->musica_atual->anterior != NULL) {
        // Se nao ha historico, usar lista da biblioteca
        reproduzir_musica(player, player->musica_atual->anterior);
    } else {
        printf("Nao ha musica anterior!\n");
    }
}

void mostrar_status_player(MusicPlayer* player) {
    printf("\n=== STATUS DO PLAYER ===\n");
    
    if (player->musica_atual == NULL) {
        printf("Nenhuma musica selecionada\n");
        printf("Status: Parado\n");
    } else {
        printf("Musica atual: '%s' - %s\n", 
               player->musica_atual->titulo, player->musica_atual->artista);
        
        switch (player->reproduzindo) {
            case 0:
                printf("Status: Parado\n");
                break;
            case 1:
                printf("Status: Tocando\n");
                break;
            case 2:
                printf("Status: Pausado\n");
                break;
        }
    }
    
    printf("Total de musicas na biblioteca: %d\n", player->biblioteca->total_musicas);
    printf("Musicas no historico: %d\n", player->historico->tamanho);
    printf("Musicas na fila: %d\n", player->fila_reproducao->tamanho);
    printf("Modo shuffle: %s\n", player->shuffle_ativo ? "ATIVO" : "DESATIVADO");
    printf("\n");
}

// Função para alternar o modo shuffle
void alternar_shuffle(MusicPlayer* player) {
    player->shuffle_ativo = !player->shuffle_ativo;
    printf("Modo shuffle %s!\n", player->shuffle_ativo ? "ATIVADO" : "DESATIVADO");
}

// Função para obter uma música aleatória da biblioteca
Musica* obter_musica_aleatoria(BibliotecaMusical* biblioteca) {
    if (biblioteca->total_musicas == 0) {
        return NULL;
    }
    
    // Gerar número aleatório baseado no tempo atual
    srand((unsigned int)time(NULL));
    int indice_aleatorio = rand() % biblioteca->total_musicas;
    
    // Navegar até a música no índice aleatório
    Musica* atual = biblioteca->primeiro;
    for (int i = 0; i < indice_aleatorio && atual != NULL; i++) {
        atual = atual->proximo;
    }
    
    return atual;
}

void liberar_player(MusicPlayer* player) {
    liberar_biblioteca(player->biblioteca);
    liberar_historico(player->historico);
    liberar_fila(player->fila_reproducao);
    free(player);
}
