#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "lib_space.h"

int main() {
	t_lista tiros_canhao, canhao, barreiras, aliens, tiros_aliens;

    int nlin, ncol, cont_alien, vel_alien, dir_alien, cont_tiros_canhao, cont_tiros_aliens, tam_lista, aleat;
    chtype key;

	srand(time(NULL));

	inicia_ncurses();
	getmaxyx(stdscr, nlin, ncol);
    	if (nlin < TAM_LIN || ncol < TAM_COL)	/*verifica tamanho do terminal*/
    	{
    		endwin();
    		printf("O terminal deve ter tamanho mínimo de %d linhas por %d colunas\n", TAM_LIN, TAM_COL);
    		exit(0);
    	} 
	if (! inicia_jogo(&tiros_canhao, &canhao, &barreiras, &aliens, &tiros_aliens)){
		endwin();
		printf("Erro na inicialização!\n");
		exit(0);
	}
	
	dir_alien = 2;			/*Seta a direção inicial do alien*/
	vel_alien = 12;			/*Seta a velocidade inicial do alien*/
	cont_alien = 0;			/*Contador de ciclos para controlar a velocidade do alien*/
	cont_tiros_canhao = 0;	/*Contador de ciclos para controlar a velocidade dos tiros do canhao*/
	cont_tiros_aliens = 0;	/*Contador de ciclos para controlar a velocidade dos tiros do alien*/

	while (1) { 
		getmaxyx(stdscr, nlin, ncol);
    	if (nlin < TAM_LIN || ncol < TAM_COL)	/*verifica tamanho do terminal*/
    	{
    		endwin();
    		printf("O terminal deve ter tamanho mínimo de %d linhas por %d colunas\n", TAM_LIN, TAM_COL);
    		exit(0);
    	} 

    	imprime_jogo(&tiros_canhao, &canhao, &barreiras, &aliens, &tiros_aliens);

	    key = getch();

		if(key == KEY_UP || key == ' ' || key == 'w') {
			/* atira */
        	canhao_atira(&tiros_canhao, &canhao);
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
	   		finaliza_jogo(&tiros_canhao, &canhao, &barreiras, &aliens, &tiros_aliens);
	    }
	    else if (key == 'p') {
			/*pausa o jogo por 10 segundos*/
	   		sleep(10);
	    }	    

	    verifica_colisao(&tiros_canhao, &canhao, &barreiras, &aliens, &tiros_aliens);
	    if(cont_tiros_canhao == 1){
	    	move_tiros(&tiros_canhao, 3);
	    	cont_tiros_canhao = 0;
		}
		if(cont_tiros_aliens == 4){
	    	move_tiros(&tiros_aliens, 4);
	    	cont_tiros_aliens = 0;
		}

		if(cont_alien == vel_alien){
	    	move_aliens(&aliens, &dir_alien, &vel_alien);
	    	cont_alien = 0;
	    }

	    tamanho_lista(&tam_lista, &tiros_aliens);
	    if(tam_lista < 3){
	    	tamanho_lista(&tam_lista, &aliens);
	    	aleat = rand() % tam_lista;
	    	alien_atira(&tiros_aliens, &aliens, aleat);
	    }

	    cont_alien++;
	    cont_tiros_canhao++;
	    cont_tiros_aliens++;

	    usleep(36000);
    }

   finaliza_jogo(&tiros_canhao, &canhao, &barreiras, &aliens, &tiros_aliens);
}