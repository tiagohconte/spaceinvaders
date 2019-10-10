#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>

#define TAM_X 38
#define TAM_Y 100

/*definindo os modelos de aliens*/
#define ALIEN_1_A "A\nAMA\n/X\\"
#define ALIEN_1_B "A\nAMA\n\\X/"
#define ALIEN_2_A ".v_v.\n}WMW{\n/ \\"
#define ALIEN_2_B ".v_v.\n}WMW{\n\\ /"
#define ALIEN_3_A "nmn\ndbMdb\n_/-\\_"
#define ALIEN_3_B "nmn\ndbMdb\n_\\-/_\n"
#define ALIEN_EXPLOSION "\\ \' /\n-   -\n/,\\"
#define ALIEN_SHOT "&"
/*definindo o modelo para a barreira*/
#define BARRIER "AMMMA\nAMMMMMA\nMM   MM"
/*definindo os modelos para o jogador*/
#define PLAYER_SPACESHIP "/^\\\nMMMMM"
#define PLAYER_SHOT "|"

/*função para mover o jogador*/
void player_move(int dir)
{

}
/*função para o jogador atirar*/
void player_atira(void)
{

}

void main(void) {
	/*inicializações do ncurses*/  
    initscr();              /* inicia a tela */
    cbreak();               /* desabilita o buffer de entrada */
    noecho();               /* não mostra os caracteres digitados */
    nodelay(stdscr, TRUE);  /* faz com que getch não aguarde a digitação */
    keypad(stdscr, TRUE);   /* permite a leitura das setas */
    curs_set(FALSE);        /* não mostra o cursor na tela */

    int nlin, ncol;
    chtype key;

	while (1) {
		getmaxyx(stdscr, nlin, ncol);
    	if (nlin < TAM_X || ncol < TAM_Y)	/*verifica tamanho do terminal*/
    	{
    		endwin();
    		printf("O terminal deve ter tamanho mínimo de 38x100\n");
    		exit(0);
    	}

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
	   		endwin();
	    	exit(0);
	    }
    }

    endwin();
}