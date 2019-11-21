#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "lib_space.h"

/* Mostra mensagem de game over */
void perdeu_jogo(){
	clear();
	wattron(stdscr, COLOR_PAIR(1));
	move(16, 45);
	addstr("GAME OVER");
	move(17, 36);
	addstr("space para tentar novamente");
	refresh();
}
/* Prepara o jogo para uma nova rodada */
void ganhou_rodada(){
	clear();
	wattron(stdscr, COLOR_PAIR(1));
	move(16, 42);
	addstr("GANHOU A RODADA");
	move(17, 40);
	addstr("space para continuar");
	refresh();	
}

int main() {
	/* Configuracoes do jogo*/
	t_lista tiros_canhao, canhao, barreiras, aliens, tiros_aliens;

    int nlin, ncol, cont, vel_alien, dir_alien, tam_lista, aleat, acabou, pontos;
    chtype key;

	srand(time(NULL));

	inicia_ncurses();
	getmaxyx(stdscr, nlin, ncol);
    	if (nlin < TAM_LIN || ncol < TAM_COL){	/*verifica tamanho do terminal*/
    		endwin();
    		printf("O terminal deve ter tamanho mínimo de %d linhas por %d colunas\n", TAM_LIN, TAM_COL);
    		exit(0);
    	} 
	if (! inicia_jogo(&tiros_canhao, &canhao, &barreiras, &aliens, &tiros_aliens, &dir_alien, &vel_alien, &cont)){
		endwin();
		printf("Erro na inicialização!\n");
		exit(0);
	}
	pontos = 0;		/* Inicializa a pontuacao em zero */

	/*Inicio do jogo*/
	while (1) { 
		getmaxyx(stdscr, nlin, ncol);
    	if (nlin < TAM_LIN || ncol < TAM_COL){	/*verifica tamanho do terminal*/
    		endwin();
    		printf("O terminal deve ter tamanho mínimo de %d linhas por %d colunas\n", TAM_LIN, TAM_COL);
    		exit(0);
    	} 

    	imprime_jogo(&tiros_canhao, &canhao, &barreiras, &aliens, &tiros_aliens, pontos);

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
	   		finaliza_jogo(&tiros_canhao, &canhao, &barreiras, &aliens, &tiros_aliens, pontos);
	    }
	    else if (key == 'p') {
			/*pausa o jogo por 10 segundos*/
	   		sleep(10);
	    }	    

	    acabou = verifica_colisao(&tiros_canhao, &canhao, &barreiras, &aliens, &tiros_aliens, &pontos);
	    if(acabou == 0){
	        if(cont % 2 == 0){
	        	move_tiros(&tiros_canhao, 3);
	    	}
	    	if(cont % 4 == 0){
	    		tamanho_lista(&tam_lista, &tiros_aliens);
	    		if(tam_lista < 3){
	    			tamanho_lista(&tam_lista, &aliens);
	    			aleat = rand() % tam_lista;
	    			alien_atira(&tiros_aliens, &aliens, aleat);
	    		}
	        	move_tiros(&tiros_aliens, 4);
	    	}

	    	if(cont % vel_alien == 0){
	        	move_aliens(&aliens, &dir_alien, &vel_alien);
	        }

	        cont++;
	    } else if(acabou == 1){
	    	ganhou_rodada();
	    	key = getch();
	    	while(key != 'q' && key != ' '){
	    		key = getch();
	    	}
	    	if(key == 'q'){
	    		finaliza_jogo(&tiros_canhao, &canhao, &barreiras, &aliens, &tiros_aliens, pontos);
	    	} else {
	    		destroi_todas_listas(&tiros_canhao, &canhao, &barreiras, &aliens, &tiros_aliens);
	    		if (! inicia_jogo(&tiros_canhao, &canhao, &barreiras, &aliens, &tiros_aliens, &dir_alien, &vel_alien, &cont)){
	    			endwin();
	    			printf("Erro na inicialização!\n");
	    			exit(0);
	    		}	
	    	}
	    } else if(acabou == 2){
	    	perdeu_jogo();
	    	key = getch();
	    	while(key != 'q' && key != ' '){
	    		key = getch();
	    	}
	    	if(key == 'q'){
	    		finaliza_jogo(&tiros_canhao, &canhao, &barreiras, &aliens, &tiros_aliens, pontos);
	    	} else {
	    		pontos = 0;
	    		destroi_todas_listas(&tiros_canhao, &canhao, &barreiras, &aliens, &tiros_aliens);
	    		if (! inicia_jogo(&tiros_canhao, &canhao, &barreiras, &aliens, &tiros_aliens, &dir_alien, &vel_alien, &cont)){
	    			endwin();
	    			printf("Erro na inicialização!\n");
	    			exit(0);
	    		}
	    	}
	    }  

	    usleep(36000);
    }

   finaliza_jogo(&tiros_canhao, &canhao, &barreiras, &aliens, &tiros_aliens, pontos);
}