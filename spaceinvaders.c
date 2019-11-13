#include <stdlib.h>
#include <unistd.h>

#include "lib_space.h"

int main() {
	t_lista tiros, canhao, barreira, aliens;

    int nlin, ncol, cont, vel_alien, move_aliens, direcao;
    chtype key;

	inicia_ncurses();
	getmaxyx(stdscr, nlin, ncol);
    	if (nlin < TAM_LIN || ncol < TAM_COL)	/*verifica tamanho do terminal*/
    	{
    		endwin();
    		printf("O terminal deve ter tamanho mínimo de %d linhas por %d colunas\n", TAM_LIN, TAM_COL);
    		exit(0);
    	} 
	if (! inicia_jogo(&tiros, &canhao, &barreira, &aliens)){
		endwin();
		printf("Erro na inicialização!\n");
		exit(0);
	}

	cont = 0;
	move_aliens = 0;
	direcao = 2;
	vel_alien = 6;

	while (1) { 
		getmaxyx(stdscr, nlin, ncol);
    	if (nlin < TAM_LIN || ncol < TAM_COL)	/*verifica tamanho do terminal*/
    	{
    		endwin();
    		printf("O terminal deve ter tamanho mínimo de %d linhas por %d colunas\n", TAM_LIN, TAM_COL);
    		exit(0);
    	} 

    	imprime_jogo(&tiros, &canhao, &barreira, &aliens);

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

	    if(cont == vel_alien){
	    	move_aliens = 1;
	    	cont = 0;
	    }

	    opera_jogo(&tiros, &canhao, &barreira, &aliens, move_aliens, &direcao);

	    move_aliens = 0;

	    cont++;

	    usleep(40000);
    }

   finaliza_ncurses();
}