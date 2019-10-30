#include <stdlib.h>
#include <ncurses.h>
#include "lib_space.h"

/*definindo os modelos de aliens*/
#define ALIEN_1_A "  A   AMA  /X\\ "
#define ALIEN_1_B "  A   AMA  \\X/ "
#define ALIEN_2_A ".v_v.}WMW{ / \\ "
#define ALIEN_2_B ".v_v.}WMW{ \\ / "
#define ALIEN_3_A " nmn dbMdb_/-\\_"
#define ALIEN_3_B " nmn dbMdb_\\-/_"
#define ALIEN_EXPLOSION "\\ \' /-   -/ , \\"
#define ALIEN_SHOT "&"
/*definindo o modelo para a barreira*/
#define BARRIER "AMMMA\nAMMMMMA\nMM   MM"
/*definindo os modelos para o jogador*/
#define PLAYER_SPACESHIP "/^\\\nMMMMM"
#define PLAYER_SHOT "|"

/* Inicia o ncurses */
void inicia_ncurses(){ 
    initscr();              /* inicia a tela */
    cbreak();               /* desabilita o buffer de entrada */
    noecho();               /* não mostra os caracteres digitados */
    nodelay(stdscr, TRUE);  /* faz com que getch não aguarde a digitação */
    keypad(stdscr, TRUE);   /* permite a leitura das setas */
    curs_set(FALSE);        /* não mostra o cursor na tela */

	/*inicia cores*/
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
}
/* Fecha o ncurses */
void finaliza_ncurses(){
	endwin();
    exit(0);
}
void imprime_borda(void){
	int i;

	clear();
	for (i = 1; i < TAM_X-1; i++){
		move(i, 0);
		addch('|');
		move(i, TAM_Y-1);
		addch('|');
	}
	for (i = 0; i < TAM_Y; i++){
		move(0, i);
		addch('-');
		move(TAM_X-1, i);
		addch('-');
	}
	refresh();
}
void imprime_aliens(void){
	int i, j, a, b, c;
	char v[15] = ALIEN_1_A;

	clear();
	for (i = 6; i < TAM_X-11; i+=4)
		for (j = 1; j < TAM_Y-6; j+=6){
			c = 0;
			for (a = i; a < i+3; a++)
				for (b = j; b < j+5; b++){
					move(a, b);
					addch(v[c]);
					c++;
				}
		}
	refresh();
}
/*função para mover o jogador*/
void player_move(int dir){

}
/*função para o jogador atirar*/
void player_atira(void){

}