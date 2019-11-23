/*	Implementação do jogo space invaders em C
	Apenas para fins educacionais
	Feito por Tiago Henrique Conte
	Concluído em  de novembro de 2019
*/

#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "lib_space.h"

/* Mostra mensagem de game over */
void perdeu_jogo(int pontos){
	clear();
	wattron(stdscr, COLOR_PAIR(1));
	wattron(stdscr, A_BOLD);
	move(16, 45);
	printw("GAME OVER");
	wattroff(stdscr, A_BOLD);
	move(17, 36);
	printw("space para tentar novamente");
	move(25, 45);
	printw("Pontos: %d", pontos);
	refresh();
}
/* Prepara o jogo para uma nova rodada */
void ganhou_rodada(pontos){
	clear();
	wattron(stdscr, COLOR_PAIR(1));
	wattron(stdscr, A_BOLD);
	move(16, 42);
	printw("GANHOU A RODADA");
	wattroff(stdscr, A_BOLD);
	move(17, 40);
	printw("space para continuar");
	move(25, 45);
	printw("Pontos: %d", pontos);
	refresh();	
}

int main() {
	/* Configuracoes do jogo*/
	t_lista tiros_canhao, canhao, barreiras, aliens, tiros_aliens, nave_mae;

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
	if (! inicia_jogo(&tiros_canhao, &canhao, &barreiras, &aliens, &tiros_aliens, &nave_mae, &dir_alien, &vel_alien, &cont)){
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

    	imprime_jogo(&tiros_canhao, &canhao, &barreiras, &aliens, &tiros_aliens, &nave_mae, pontos);

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
	   		finaliza_jogo(&tiros_canhao, &canhao, &barreiras, &aliens, &tiros_aliens, &nave_mae, pontos);
	    }
	    else if (key == 'p') {
			/*pausa o jogo por 10 segundos*/
	   		sleep(10);
	    }	    

	    acabou = verifica_colisao(&tiros_canhao, &canhao, &barreiras, &aliens, &tiros_aliens, &nave_mae, &pontos);
	    if(acabou == 0){
	    	/* Movimenta os tiros na tela a cada 2 ciclos */
	        if(cont % 2 == 0){
	        	move_tiros(&tiros_canhao, 3);
	        	if(!lista_vazia(&nave_mae)){
	        		move_nave_mae(&nave_mae);
	        	}
	    	}
	    	/* Movimenta os tiros de aliens e gera novos tiros a cada 4 ciclos */
	    	if(cont % 4 == 0){
	    		tamanho_lista(&tam_lista, &tiros_aliens);
	    		/* Caso haja menos de 3 tiros de aliens na tela será criado mais um vindo de um alien aleatorio */
	    		if(tam_lista < 3){
	    			tamanho_lista(&tam_lista, &aliens);
	    			aleat = rand() % tam_lista;
	    			alien_atira(&tiros_aliens, &aliens, aleat);
	    		}
	        	move_tiros(&tiros_aliens, 4);
	    	}
	    	/* Movimenta os aliens na tela a cada vel_alien ciclos */
	    	if(cont % vel_alien == 0){
	        	move_aliens(&aliens, &dir_alien, &vel_alien);
	        }

	        /* Gera e movimenta uma nave mae */
	        if(((cont+1) % 500 == 0) && lista_vazia(&nave_mae)){
				if(!gera_nave_mae(&nave_mae))
			    	return 0;
        	}

	        cont++;
	    } else {
	    	if(acabou == 1){
	    		ganhou_rodada(pontos);
	    	} else if(acabou == 2){
	    		perdeu_jogo(pontos);
	    		pontos = 0;
	    	}
	    	key = getch();
	    	while(key != 'q' && key != ' '){
	    		key = getch();
	    	}
	    	if(key == 'q'){
	    		finaliza_jogo(&tiros_canhao, &canhao, &barreiras, &aliens, &tiros_aliens, &nave_mae, pontos);
	    	} else {
	    		destroi_todas_listas(&tiros_canhao, &canhao, &barreiras, &aliens, &tiros_aliens, &nave_mae);
	    		if (! inicia_jogo(&tiros_canhao, &canhao, &barreiras, &aliens, &tiros_aliens, &nave_mae, &dir_alien, &vel_alien, &cont)){
	    			endwin();
	    			printf("Erro na inicialização!\n");
	    			exit(0);
	    		}	
	    	}
	    }

	    usleep(36000);
    }

   finaliza_jogo(&tiros_canhao, &canhao, &barreiras, &aliens, &tiros_aliens, &nave_mae, pontos);
}