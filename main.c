#include "playlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void exibir_menu() {
    printf("1. Adicionar música\n"
           "2. Remover música\n"
           "3. Próxima música\n"
           "4. Música anterior\n"
           "5. Listar músicas\n"
           "0. Sair\n"
           "Opção: ");
}

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    Playlist* playlist = criar_playlist();
    if (!playlist) return 1;
    
    int opcao, min, seg, duracao;
    char titulo[100], artista[100];
    
    adicionar_musica(playlist, "Jigsaw Falling Into Place", "RADIOHEAD", 255);
    adicionar_musica(playlist, "Invisible", "Duran Duran", 223);
    adicionar_musica(playlist, "Windowlicker", "Aphex Twin", 367);
    adicionar_musica(playlist, "Youngest Daughter", "Superheaven", 192);
    
    do {
        exibir_menu();
        scanf("%d", &opcao);
        limpar_buffer();
        
        switch (opcao) {
            case 1:
                printf("Título: ");
                scanf("%99[^\n]", titulo);
                limpar_buffer();
                
                printf("Artista: ");
                scanf("%99[^\n]", artista);
                limpar_buffer();
                
                printf("Duração (min seg): ");
                scanf("%d %d", &min, &seg);
                limpar_buffer();
                
                adicionar_musica(playlist, titulo, artista, min*60 + seg);
                break;
                
            case 2:
                printf("Título para remover: ");
                scanf("%99[^\n]", titulo);
                limpar_buffer();
                remover_musica(playlist, titulo);
                break;
                
            case 3:
                proxima_musica(playlist);
                break;
                
            case 4:
                musica_anterior(playlist);
                break;
                
            case 5:
                listar_musicas(playlist);
                break;
                
            case 0:
                printf("Encerrando...\n");
                break;
                
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
    
    liberar_playlist(playlist);
    return 0;
}