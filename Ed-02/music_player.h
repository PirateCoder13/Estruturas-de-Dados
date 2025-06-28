/*
 * MUSIC PLAYER SIMULATOR - CABECALHOS E ESTRUTURAS
 * Empresa: PiratariaCodificada
 * Autores: Joao Gualberto, Yasmin Pereira, Gabriela Rocca
 *
 * Definicoes de estruturas de dados e prototipos de funcoes
 */

#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <mmsystem.h>
#include <time.h>
#pragma comment(lib, "winmm.lib")

// Estrutura para representar uma musica
typedef struct Musica {
    char titulo[100];
    char artista[100];
    char arquivo[200];  // Caminho do arquivo MP3
    int duracao; // duracao em segundos
    struct Musica* anterior;
    struct Musica* proximo;
} Musica;

// Estrutura para a lista duplamente encadeada (biblioteca de musicas)
typedef struct {
    Musica* primeiro;
    Musica* ultimo;
    int total_musicas;
} BibliotecaMusical;

// Estrutura para o no da pilha (historico)
typedef struct NoHistorico {
    Musica* musica;
    struct NoHistorico* proximo;
} NoHistorico;

// Estrutura para a pilha (historico de reproducao)
typedef struct {
    NoHistorico* topo;
    int tamanho;
} HistoricoReproducao;

// Estrutura para o no da fila
typedef struct NoFila {
    Musica* musica;
    struct NoFila* proximo;
} NoFila;

// Estrutura para a fila (fila de reproducao)
typedef struct {
    NoFila* frente;
    NoFila* tras;
    int tamanho;
} FilaReproducao;

// Estrutura principal do player
typedef struct {
    BibliotecaMusical* biblioteca;
    HistoricoReproducao* historico;
    FilaReproducao* fila_reproducao;
    Musica* musica_atual;
    int reproduzindo; // 0 = parado, 1 = tocando, 2 = pausado
    int shuffle_ativo; // 0 = desativado, 1 = ativado
} MusicPlayer;

// Funcoes da biblioteca musical (lista duplamente encadeada)
BibliotecaMusical* criar_biblioteca();
void adicionar_musica(BibliotecaMusical* biblioteca, char* titulo, char* artista, char* arquivo, int duracao);
void adicionar_musica_mp3(BibliotecaMusical* biblioteca, char* arquivo_mp3);
void carregar_todos_mp3(BibliotecaMusical* biblioteca);
void remover_musica(BibliotecaMusical* biblioteca, char* titulo);
void listar_musicas(BibliotecaMusical* biblioteca);
Musica* buscar_musica(BibliotecaMusical* biblioteca, char* titulo);
Musica* buscar_musica_similar(BibliotecaMusical* biblioteca, char* termo_busca);
void liberar_biblioteca(BibliotecaMusical* biblioteca);

// Funcoes do historico (pilha)
HistoricoReproducao* criar_historico();
void adicionar_ao_historico(HistoricoReproducao* historico, Musica* musica);
Musica* voltar_historico(HistoricoReproducao* historico);
void mostrar_historico(HistoricoReproducao* historico);
void liberar_historico(HistoricoReproducao* historico);

// Funcoes da fila de reproducao
FilaReproducao* criar_fila_reproducao();
void adicionar_fila(FilaReproducao* fila, Musica* musica);
Musica* proximo_da_fila(FilaReproducao* fila);
void mostrar_fila(FilaReproducao* fila);
void liberar_fila(FilaReproducao* fila);

// Funcoes do player
MusicPlayer* criar_player();
void reproduzir_musica(MusicPlayer* player, Musica* musica);
void pausar_player(MusicPlayer* player);
void parar_player(MusicPlayer* player);
void proximo_musica(MusicPlayer* player);
void anterior_musica(MusicPlayer* player);
void alternar_shuffle(MusicPlayer* player);
Musica* obter_musica_aleatoria(BibliotecaMusical* biblioteca);
void liberar_player(MusicPlayer* player);

// Funcoes de reproducao de audio
void tocar_arquivo_mp3(char* arquivo);
void pausar_reproducao();
void parar_reproducao();
void retomar_reproducao();

// Funcoes de interface
void mostrar_menu();
void executar_player();

#endif
