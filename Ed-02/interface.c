#include "music_player.h"

// Função externa para mostrar status do player
void mostrar_status_player(MusicPlayer* player);

void mostrar_menu() {
    printf("\n");
    printf("=========================================================\n");
    printf("              MUSIC PLAYER SIMULATOR                    \n");
    printf("                 PiratariaCodificada                    \n");
    printf("=========================================================\n");    
    printf("  1. Adicionar musica a biblioteca                      \n");
    printf("  2. Escanear pasta musicas/ (carregar todos)            \n");
    printf("  3. Remover musica da biblioteca                       \n");
    printf("  4. Listar todas as musicas                            \n");
    printf("  5. Buscar musica por titulo                           \n");
    printf("  6. Reproduzir musica                                  \n");
    printf("  7. Pausar/Retomar reproducao                          \n");
    printf("  8. Parar reproducao                                   \n");
    printf("  9. Proxima musica                                     \n");
    printf(" 10. Musica anterior                                    \n");
    printf(" 11. Adicionar musica a fila                            \n");
    printf(" 12. Ver fila de reproducao                             \n");
    printf(" 13. Ver historico                                      \n");
    printf(" 14. Status do player                                   \n");
    printf(" 15. Sair                                               \n");
    printf("=========================================================\n");
    printf("Escolha uma opcao: ");
}

void adicionar_musicas_exemplo(MusicPlayer* player) {
    printf("Adicionando algumas musicas de exemplo...\n");
    adicionar_musica(player->biblioteca, "Bohemian Rhapsody", "Queen", "", 355);
    adicionar_musica(player->biblioteca, "Hotel California", "Eagles", "", 391);
    adicionar_musica(player->biblioteca, "Imagine", "John Lennon", "", 183);
    adicionar_musica(player->biblioteca, "Stairway to Heaven", "Led Zeppelin", "", 482);
    adicionar_musica(player->biblioteca, "Sweet Child O Mine", "Guns N Roses", "", 356);
    
    // Adicionar arquivo MP3 real da pasta musicas (apenas o nome do arquivo)
    printf("Carregando arquivo MP3 real da pasta musicas...\n");
    adicionar_musica_mp3(player->biblioteca, "paper-planes-chill-future-beat-283956.mp3");
    
    printf("Musicas de exemplo adicionadas!\n");
}

void executar_player() {
    MusicPlayer* player = criar_player();
    int opcao;
    char titulo[100], artista[100];
    int duracao;
    Musica* musica_encontrada;
      printf("Bem-vindo ao Music Player Simulator!\n");
    printf("Desenvolvido para PiratariaCodificada\n\n");
      // Perguntar se quer carregar musicas de exemplo
    printf("Deseja carregar algumas musicas de exemplo? (1-Sim / 0-Nao): ");
    int carregar_exemplo;
    scanf("%d", &carregar_exemplo);
    if (carregar_exemplo == 1) {
        adicionar_musicas_exemplo(player);
    }
    
    do {
        mostrar_menu();
        scanf("%d", &opcao);
        
        switch (opcao) {            case 1: // Adicionar musica
                printf("\n=== ADICIONAR MUSICA ===\n");
                printf("Digite o titulo da musica: ");
                getchar(); // Limpar buffer
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = 0; // Remover \n
                
                printf("Digite o artista: ");
                fgets(artista, sizeof(artista), stdin);
                artista[strcspn(artista, "\n")] = 0; // Remover \n
                  printf("Digite a duracao em segundos: ");
                scanf("%d", &duracao);
                  adicionar_musica(player->biblioteca, titulo, artista, "", duracao);
                break;
                
            case 2: // Escanear pasta musicas
                printf("\n=== ESCANEAR PASTA MUSICAS ===\n");
                carregar_todos_mp3(player->biblioteca);
                break;
                
            case 3: // Remover musica
                printf("\n=== REMOVER MUSICA ===\n");
                printf("Digite o titulo da musica para remover: ");
                getchar(); // Limpar buffer
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = 0; // Remover \n
                  remover_musica(player->biblioteca, titulo);
                break;
                
            case 4: // Listar musicas
                listar_musicas(player->biblioteca);
                break;
                
            case 5: // Buscar musica
                printf("\n=== BUSCAR MUSICA ===\n");
                printf("Digite o titulo da musica: ");
                getchar(); // Limpar buffer
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = 0; // Remover \n
                
                musica_encontrada = buscar_musica(player->biblioteca, titulo);
                if (musica_encontrada != NULL) {
                    int min = musica_encontrada->duracao / 60;
                    int seg = musica_encontrada->duracao % 60;
                    printf("Musica encontrada:\n");
                    printf("Titulo: %s\n", musica_encontrada->titulo);
                    printf("Artista: %s\n", musica_encontrada->artista);
                    printf("Arquivo: %s\n", musica_encontrada->arquivo);
                    printf("Duracao: %d:%02d\n", min, seg);
                } else {
                    printf("Musica nao encontrada!\n");                }
                break;
                
            case 6: // Reproduzir musica
                printf("\n=== REPRODUZIR MUSICA ===\n");
                printf("Digite o titulo da musica: ");
                getchar(); // Limpar buffer
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = 0; // Remover \n
                
                musica_encontrada = buscar_musica(player->biblioteca, titulo);
                if (musica_encontrada != NULL) {
                    reproduzir_musica(player, musica_encontrada);
                } else {
                    printf("Musica nao encontrada!\n");                }
                break;
                
            case 7: // Pausar/Retomar
                pausar_player(player);
                break;
                
            case 8: // Parar
                parar_player(player);
                break;
                
            case 9: // Proxima musica
                proximo_musica(player);
                break;
                
            case 10: // Musica anterior
                anterior_musica(player);
                break;
                
            case 11: // Adicionar a fila
                printf("\n=== ADICIONAR A FILA ===\n");
                printf("Digite o titulo da musica: ");
                getchar(); // Limpar buffer
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = 0; // Remover \n
                
                musica_encontrada = buscar_musica(player->biblioteca, titulo);
                if (musica_encontrada != NULL) {
                    adicionar_fila(player->fila_reproducao, musica_encontrada);
                } else {
                    printf("Musica nao encontrada!\n");                }
                break;
                
            case 12: // Ver fila
                mostrar_fila(player->fila_reproducao);
                break;
                
            case 13: // Ver historico
                mostrar_historico(player->historico);
                break;
                
            case 14: // Status do player
                mostrar_status_player(player);
                break;
                
            case 15: // Sair
                printf("\nObrigado por usar o Music Player Simulator!\n");
                printf("Desenvolvido para PiratariaCodificada\n");
                break;
                  default:
                printf("Opcao invalida! Tente novamente.\n");
        }
        
        if (opcao != 15) {
            printf("\nPressione Enter para continuar...");
            getchar();
            if (opcao != 1 && opcao != 3 && opcao != 5 && opcao != 6 && opcao != 11) {
                getchar(); // Para opcoes que nao usaram getchar()
            }
        }
        
    } while (opcao != 15);
    
    // Liberar memória
    liberar_player(player);
}
