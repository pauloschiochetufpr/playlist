#include "playlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Playlist* criar_playlist() {
    Playlist* nova = malloc(sizeof(Playlist));
    if (nova) {
        nova->atual = NULL;
        nova->tamanho = 0;
        nova->modo_repeticao = 0;
    }
    return nova;
}

void liberar_playlist(Playlist* playlist) {
    if (!playlist || playlist->tamanho == 0) {
        free(playlist);
        return;
    }
    
    Musica* atual = playlist->atual;
    Musica* inicio = atual;
    do {
        Musica* temp = atual;
        atual = atual->proxima;
        free(temp);
    } while (atual != inicio);
    
    free(playlist);
}

void adicionar_musica(Playlist* playlist, const char* titulo, const char* artista, int duracao) {
    if (!playlist) return;
    
    Musica* nova = malloc(sizeof(Musica));
    if (!nova) return;
    
    strncpy(nova->titulo, titulo, 99);
    nova->titulo[99] = '\0';
    
    strncpy(nova->artista, artista, 99);
    nova->artista[99] = '\0';
    
    nova->duracao = duracao;
    
    if (playlist->tamanho == 0) {
        nova->proxima = nova;
        playlist->atual = nova;
    } else {
        nova->proxima = playlist->atual->proxima;
        playlist->atual->proxima = nova;
    }
    
    playlist->tamanho++;
    printf("Adicionada: %s - %s\n", titulo, artista);
}

int remover_musica(Playlist* playlist, const char* titulo) {
    if (!playlist || playlist->tamanho == 0) {
        printf("Playlist vazia\n");
        return 0;
    }
    
    Musica* atual = playlist->atual;
    int encontrada = 0;
    do {
        if (strcmp(atual->proxima->titulo, titulo) == 0) {
            encontrada = 1;
            break;
        }
        atual = atual->proxima;
    } while (atual != playlist->atual);
    
    if (!encontrada) {
        printf("Música não encontrada\n");
        return 0;
    }
    
    Musica* remover = atual->proxima;
    
    if (playlist->tamanho == 1) {
        playlist->atual = NULL;
    } else {
        if (remover == playlist->atual) {
            playlist->atual = atual;
        }
        atual->proxima = remover->proxima;
    }
    
    free(remover);
    playlist->tamanho--;
    printf("Música removida\n");
    return 1;
}

void proxima_musica(Playlist* playlist) {
    if (!playlist || playlist->tamanho == 0) {
        printf("Playlist vazia\n");
        return;
    }
    
    playlist->atual = playlist->atual->proxima;
    exibir_musica_atual(playlist);
}

void musica_anterior(Playlist* playlist) {
    if (!playlist || playlist->tamanho == 0) {
        printf("Playlist vazia\n");
        return;
    }
    
    Musica* anterior = playlist->atual;
    while (anterior->proxima != playlist->atual) {
        anterior = anterior->proxima;
    }
    
    playlist->atual = anterior;
    exibir_musica_atual(playlist);
}

void alternar_modo_repeticao(Playlist* playlist) {
    if (!playlist) return;
    playlist->modo_repeticao = !playlist->modo_repeticao;
    printf("Modo repetição: %s\n", playlist->modo_repeticao ? "ON" : "OFF");
}

void listar_musicas(Playlist* playlist) {
    if (!playlist || playlist->tamanho == 0) {
        printf("Playlist vazia\n");
        return;
    }
    
    printf("\nMÚSICAS (%d)\n", playlist->tamanho);
    
    Musica* atual = playlist->atual;
    Musica* inicio = atual;
    int i = 1;
    
    do {
        int min = atual->duracao / 60;
        int seg = atual->duracao % 60;
        
        printf("%d. %s - %s (%d:%02d)", i, atual->titulo, atual->artista, min, seg);
        if (atual == playlist->atual) printf(" ◄");
        printf("\n");
        
        atual = atual->proxima;
        i++;
    } while (atual != inicio);
}

Musica* buscar_musica(Playlist* playlist, const char* titulo) {
    if (!playlist || playlist->tamanho == 0) return NULL;
    
    Musica* atual = playlist->atual;
    Musica* inicio = atual;
    
    do {
        if (strcmp(atual->titulo, titulo) == 0) {
            return atual;
        }
        atual = atual->proxima;
    } while (atual != inicio);
    
    return NULL;
}

void exibir_musica_atual(Playlist* playlist) {
    if (!playlist || playlist->tamanho == 0) {
        printf("Playlist vazia\n");
        return;
    }
    
    int min = playlist->atual->duracao / 60;
    int seg = playlist->atual->duracao % 60;
    
    printf("Tempo %s - %s (%d:%02d)\n", 
           playlist->atual->titulo, 
           playlist->atual->artista, 
           min, seg);
}
