#include <stdlib.h>
#include <unistd.h>

#include "lib_space.h"

int main() {
	t_lista tiros, player, barreira, aliens;

    int nlin, ncol;
    chtype key;

	inicia_ncurses();
	getmaxyx(stdscr, nlin, ncol);
    	if (nlin < TAM_X || ncol < TAM_Y)	/*verifica tamanho do terminal*/
    	{
    		endwin();
    		printf("O terminal deve ter tamanho mínimo de %d linhas por %d colunas\n", TAM_X, TAM_Y);
    		exit(0);
    	} 
	if (! inicia_jogo(&tiros, &player, &barreira, &aliens)){
		endwin();
		printf("Erro na inicialização!\n");
		exit(0);
	}

	while (1) {
		getmaxyx(stdscr, nlin, ncol);
    	if (nlin < TAM_X || ncol < TAM_Y)	/*verifica tamanho do terminal*/
    	{
    		endwin();
    		printf("O terminal deve ter tamanho mínimo de %d linhas por %d colunas\n", TAM_X, TAM_Y);
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
			/*sai do jogo*/
	   		finaliza_ncurses();
	    }

	    usleep(40000);
    }

   finaliza_ncurses();
}