#include <stdio.h>
#include <ncurses.h>
#include "lib_lista_space.h"

/*definindo os modelos de aliens*/
#define ALIEN_1_A "  A   AMA  /X\\ \0"
#define ALIEN_1_B "  A   AMA  \\X/ \0"
#define ALIEN_2_A ".v_v.}WMW{ / \\ \0"
#define ALIEN_2_B ".v_v.}WMW{ \\ / \0"
#define ALIEN_3_A " nmn dbMdb_/-\\_\0"
#define ALIEN_3_B " nmn dbMdb_\\-/_\0"
#define ALIEN_SHOT "&\0"
/*definindo o modelo para a barreira*/
#define BARRIER "AMMMAAMMMMMAMM   MM\0"
/*definindo os modelos para o jogador*/
#define PLAYER_SPACESHIP " /^\\ MMMMM\0"
#define PLAYER_SHOT "|\0"
#define EXPLOSION "\\ \' /-   -/ , \\\0"

#define TAM_X 37
#define TAM_Y 100

/* Inicia o ncurses */
void inicia_ncurses();

/* Fecha o ncurses */
void finaliza_ncurses();

/*Inicializa o jogo*/
int inicia_jogo(t_lista *tiros, t_lista *player, t_lista *barreira, t_lista *aliens);

/*Comanda as operações para impressão do jogo*/
void imprime_jogo(t_lista *l1, t_lista *l2, t_lista *l3, t_lista *l4);

/*imprime a borda do jogo*/
void imprime_borda();

/*Imprime a lista passada*/
void imprime_lista(t_lista *lista);

/*Muda estilo*/
void muda_estilo(char *estilo, char novo[]);

/*função para mover o jogador*/
void player_move(int dir);

/*função para o jogador atirar*/
void player_atira();