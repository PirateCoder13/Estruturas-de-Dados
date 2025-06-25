#include "music_player.h"

// Variável global para controle de reprodução
static char arquivo_atual[200] = "";
static int tocando = 0;

void tocar_arquivo_mp3(char* arquivo) {
    if (arquivo == NULL || strlen(arquivo) == 0) {
        printf("Erro: Arquivo invalido!\n");
        return;
    }
    
    // Parar música atual se houver
    if (tocando) {
        parar_reproducao();
    }
    
    // Construir caminho completo se não começar com "musicas\"
    char caminho_completo[300];
    if (strstr(arquivo, "musicas\\") == arquivo || strstr(arquivo, "musicas/") == arquivo) {
        // Ja tem o caminho da pasta musicas
        strcpy(caminho_completo, arquivo);
    } else if (arquivo[1] == ':' || arquivo[0] == '\\' || arquivo[0] == '/') {
        // Caminho absoluto
        strcpy(caminho_completo, arquivo);
    } else {
        // Adicionar pasta musicas
        sprintf(caminho_completo, "musicas\\%s", arquivo);
    }
    
    strcpy(arquivo_atual, caminho_completo);
      // Comando MCI para abrir e tocar o arquivo
    char comando[400];
    sprintf(comando, "open \"%s\" alias musica", caminho_completo);
    
    MCIERROR erro = mciSendString(comando, NULL, 0, NULL);
    if (erro != 0) {
        char erro_msg[100];
        mciGetErrorString(erro, erro_msg, sizeof(erro_msg));
        printf("Erro ao abrir arquivo: %s\n", erro_msg);
        printf("Caminho tentado: %s\n", caminho_completo);
        return;
    }
    
    // Tocar a música
    erro = mciSendString("play musica", NULL, 0, NULL);
    if (erro != 0) {
        char erro_msg[100];
        mciGetErrorString(erro, erro_msg, sizeof(erro_msg));
        printf("Erro ao reproduzir: %s\n", erro_msg);
        mciSendString("close musica", NULL, 0, NULL);
        return;
    }    tocando = 1;
    printf("Reproduzindo arquivo: %s\n", caminho_completo);
}

void pausar_reproducao() {
    if (!tocando) {
        printf("Nenhuma musica esta tocando!\n");
        return;
    }
    
    MCIERROR erro = mciSendString("pause musica", NULL, 0, NULL);
    if (erro != 0) {
        char erro_msg[100];
        mciGetErrorString(erro, erro_msg, sizeof(erro_msg));
        printf("Erro ao pausar: %s\n", erro_msg);
        return;
    }
    
    printf("Musica pausada\n");
}

void retomar_reproducao() {
    if (!tocando) {
        printf("Nenhuma musica para retomar!\n");
        return;
    }
    
    MCIERROR erro = mciSendString("resume musica", NULL, 0, NULL);
    if (erro != 0) {
        char erro_msg[100];
        mciGetErrorString(erro, erro_msg, sizeof(erro_msg));
        printf("Erro ao retomar: %s\n", erro_msg);
        return;
    }
    
    printf("Musica retomada\n");
}

void parar_reproducao() {
    if (!tocando) {
        return;
    }
    
    mciSendString("stop musica", NULL, 0, NULL);
    mciSendString("close musica", NULL, 0, NULL);
    tocando = 0;
    arquivo_atual[0] = '\0';
    printf("Reproducao parada\n");
}

int esta_tocando() {
    if (!tocando) {
        return 0;
    }
    
    char status[50];
    MCIERROR erro = mciSendString("status musica mode", status, sizeof(status), NULL);
    if (erro != 0) {
        return 0;
    }
    
    return (strcmp(status, "playing") == 0);
}
