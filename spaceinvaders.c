#include <stdlib.h>
#include <unistd.h>

#include "lib_space.h"

int main() {
	t_lista tiros, canhao, barreiras, aliens;

    int nlin, ncol, cont_alien, vel_alien, dir_alien, cont_tiros;
    chtype key;

	inicia_ncurses();
	getmaxyx(stdscr, nlin, ncol);
    	if (nlin < TAM_LIN || ncol < TAM_COL)	/*verifica tamanho do terminal*/
    	{
    		endwin();
    		printf("O terminal deve ter tamanho mínimo de %d linhas por %d colunas\n", TAM_LIN, TAM_COL);
    		exit(0);
    	} 
	if (! inicia_jogo(&tiros, &canhao, &barreiras, &aliens)){
		endwin();
		printf("Erro na inicialização!\n");
		exit(0);
	}

	cont_alien = 0;
	dir_alien = 2;
	vel_alien = 8;
	cont_tiros = 0;

	while (1) { 
		getmaxyx(stdscr, nlin, ncol);
    	if (nlin < TAM_LIN || ncol < TAM_COL)	/*verifica tamanho do terminal*/
    	{
    		endwin();
    		printf("O terminal deve ter tamanho mínimo de %d linhas por %d colunas\n", TAM_LIN, TAM_COL);
    		exit(0);
    	} 

    	imprime_jogo(&tiros, &canhao, &barreiras, &aliens);

	    key = getch();

		if(key == KEY_UP || key == ' ' || key == 'w') {
			/* atira */
        	canhao_atira(&tiros, &canhao);
	    }
		else if(key == KEY_LEFT || key == 'a') {
	   		/*move pra esquerda*/
	   		inicializa_atual_inicio(&canhao);	
	   		move_elemento(&canhao, 1);
	    }
		else if (key == KEY_RIGHT || key == 'd') {
	    	/*move pra direita*/
	    	inicializa_atual_inicio(&canhao);	
	    	move_elemento(&canhao, 2);
	    }
		else if (key == 'q') {
			/*sai do jogo*/
	   		finaliza_ncurses();
	    }

	    if(cont_alien == vel_alien){
	    	move_aliens(&aliens, &dir_alien, &vel_alien);
	    	cont_alien = 0;
	    }

	    verifica_colisao(&tiros, &canhao, &barreiras, &aliens);
	    if(cont_tiros == 1){
	    	move_tiros(&tiros);
	    	cont_tiros = 0;
		}

	    cont_alien++;
	    cont_tiros++;

	    usleep(35000);
    }

   finaliza_ncurses();
}