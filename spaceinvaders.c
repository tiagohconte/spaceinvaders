#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>

#define TAM_X 38
#define TAM_Y 100

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
#define PLAYER_SPACESHIP " /^\\ MM-MM"
#define PLAYER_SHOT "|"

/*Inicia a matriz nas posições adequadas*/
void inicia_matriz(char m[][TAM_Y]){
	int i, j, a;
	char c[15] = PLAYER_SPACESHIP;

	/*Gera a borda*/
	for (i = 1; i < TAM_X-1; i++){
		m[i][0] = '|';
		m[i][TAM_Y-1] = '|';
	}
	for (i = 0; i < TAM_Y; i++){
		m[0][i] = '-';
		m[TAM_X-1][i] = '-';
	}
	/*zera todos os espaços dentro da borda*/
	for (i = 1; i < TAM_X-1; i++)
		for (j = 1; j < TAM_Y-1; j++)
			m[i][j] = ' ';
	/*insere player na matriz*/
	a = 0;
	for (i = TAM_X-3; i < TAM_X-1; i++)
		for (j = (TAM_Y/2)-2; j <= (TAM_Y/2)+2; j++){
			m[i][j] = c[a];
			a++;
		}

}
/*Imprime a matriz*/
void imprime_matriz(char m[][TAM_Y]){
	int i, j;

	clear();
	for (i = 0; i < TAM_X; i++)
		for (j = 0; j < TAM_Y; j++){
			move(i,j);
			addch(m[i][j]);
		}
	refresh();
}
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
/*função para mover o jogador*/
void player_move(int dir){

}
/*função para o jogador atirar*/
void player_atira(void){

}

void main(void) {
	char m[TAM_X][TAM_Y];
	inicia_ncurses();
	inicia_matriz(m);

    int nlin, ncol;
    chtype key;

	while (1) {
		getmaxyx(stdscr, nlin, ncol);
    	if (nlin < TAM_X || ncol < TAM_Y)	/*verifica tamanho do terminal*/
    	{
    		endwin();
    		printf("O terminal deve ter tamanho mínimo de %d linhas por %d colunas\n", TAM_X, TAM_Y);
    		exit(0);
    	}

    	imprime_matriz(m);

	    key = getch();

		if(key == KEY_UP || key == ' ' || key == 'w') {
			/* atira */
        	player_atira();
	    }
		else if(key == KEY_LEFT || key == 'a') {
	   		/*move pra esquerda*/
	   		player_move(1);
	    }
		else if (key == KEY_RIGHT || key == 'd') {
	    	/*move pra direita*/
	    	player_move(2);
	    }
		else if (key == 'q') {
			/*sai do jogo*/
	   		finaliza_ncurses();
	    }

	    usleep(40000);
    }

   finaliza_ncurses();
}