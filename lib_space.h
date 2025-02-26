/*
  Biblioteca para a implementação do jogo Space Invaders
  Feita por Tiago Henrique Conte
  Concluído em  de novembro de 2019
*/

#include <string.h>
#include <stdio.h>
#include <ncurses.h>
#include "lib_lista_space.h"

/*definindo os modelos de aliens*/
#define ALIEN_1_A " A AMA/X\\\0"
#define ALIEN_1_B " A AMA{ }\0"
#define ALIEN_2_A ".v_v.}WMW{ / \\ \0"
#define ALIEN_2_B " v_v }WMW{'( )'\0"
#define ALIEN_3_A " nmn dbMdb_/-\\_\0"
#define ALIEN_3_B " nmn dbMdb <^> \0"
#define ALIEN_SHOT "&\0"
#define NAVE_MAE_A " /MMMMM\\ AMoMoMoMA \\/'-'\\/ "
#define NAVE_MAE_B " /MMMMM\\ AoMoMoMoA \\/'-'\\/ "
/*definindo o modelo para a barreira*/
#define BARRIER_A "A\0"
#define BARRIER_M "M\0"
/*definindo os modelos para o jogador*/
#define CANHAO_STYLE " /^\\ MMMMM\0"
#define CANHAO_SHOT "|\0"
#define EXPLOSION "\\ \' /-   -/ , \\\0"

#define TAM_LIN 37
#define TAM_COL 100

/* Inicia o ncurses */
void inicia_ncurses();

/*Inicializa o jogo*/
int inicia_jogo(t_lista *tiros_canhao, t_lista *canhao, t_lista *barreira, t_lista *aliens, t_lista *tiros_aliens, t_lista *nave_mae, int *dir, int *vel, int *cont);

/* Finaliza o jogo */
void finaliza_jogo(t_lista *tiros_canhao, t_lista *canhao, t_lista *barreira, t_lista *aliens, t_lista *tiros_aliens, t_lista *nave_mae, int pontos);

/* Destroi as listas*/
void destroi_todas_listas(t_lista *tiros_canhao, t_lista *canhao, t_lista *barreira, t_lista *aliens, t_lista *tiros_aliens, t_lista *nave_mae);

/*verifica colisão de elementos*/
int verifica_colisao(t_lista *tiros_canhao, t_lista *canhao, t_lista *barreiras, t_lista *aliens, t_lista *tiros_aliens, t_lista *nave_mae, int *pontos);

/*movimenta os tiros*/
void move_tiros(t_lista *tiros, int direcao);

/*movimenta os aliens*/
void move_aliens(t_lista *aliens, int *direcao, int *vel_alien);

/*Comanda as operações para impressão do jogo*/
void imprime_jogo(t_lista *tiros_canhao, t_lista *canhao, t_lista *barreiras, t_lista *aliens, t_lista *tiros_aliens, t_lista *nave_mae, int pontos);

/*imprime a borda do jogo*/
void imprime_borda();

/*Imprime a lista passada*/
void imprime_lista(t_lista *lista);

/*Muda estilo*/
void muda_estilo(char *estilo, char novo[]);

/*função para mover o canhao*/
/*Direção 1 para esquerda e 2 para direita*/
/*Retorna 1 se bateu*/
int move_elemento(t_lista *l, int direcao);

/*função para o canhao atirar*/
void canhao_atira(t_lista *tiros, t_lista *canhao);

/*função para o alien atirar*/
void alien_atira(t_lista *tiros, t_lista *aliens, int num_alien);

/*gera uma nave mae*/
int gera_nave_mae(t_lista *nave_mae);

/*move a nave mae*/
void move_nave_mae(t_lista *nave_mae);