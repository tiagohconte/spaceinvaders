#include "lib_space.h"
#include <stdio.h>
#include <string.h>
#include <ncurses.h>
/*
	ESTADOS

	0 = MORTO
	1 = VIVO
	2 = MORRENDO

*/

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
/* Finaliza o jogo */
void finaliza_jogo(t_lista *tiros_canhao, t_lista *canhao, t_lista *barreira, t_lista *aliens, t_lista *tiros_aliens){
	/*Destruindo listas*/
	destroi_lista(tiros_canhao);
	destroi_lista(canhao);
	destroi_lista(barreira);
	destroi_lista(aliens);
	destroi_lista(tiros_aliens);

	endwin();
    exit(0);
}
int inicia_jogo(t_lista *tiros_canhao, t_lista *canhao, t_lista *barreira, t_lista *aliens, t_lista *tiros_aliens){
	/*Inicializando as listas*/
	if (! inicializa_lista(tiros_canhao))
		return 0;
	if (! inicializa_lista(canhao))
		return 0;
	if (! inicializa_lista(barreira))
		return 0;
	if (! inicializa_lista(aliens))
		return 0;
	if (! inicializa_lista(tiros_aliens))
		return 0;

	/*Inserindo canhao na lista*/
	if (! insere_fim_lista(34, 47, 1, 2, 5, CANHAO_STYLE, canhao)){
		return 0;
	}

	/*Inserindo aliens na lista*/
	int i, j;
	int pos_col, pos_lin;

	pos_lin = 5;

	/*Primeiro estilo de aliens*/
	pos_col = 2;
	for(i = 0; i < 11; i++){
		if (! insere_fim_lista(pos_lin, pos_col, 1, 3, 3, ALIEN_1_A, aliens))
			return 0;
		pos_col+=7;
	}
	pos_lin+=4;
	/*Segundo estilo de aliens*/
	for(i = 0; i < 2; i++){
		pos_col = 1;
		for(j = 0; j < 11; j++){
			if (! insere_fim_lista(pos_lin, pos_col, 1, 3, 5, ALIEN_2_A, aliens))
				return 0;
			pos_col+=7;
		}
		pos_lin+=4;
	}
	/*Terceiro estilo de aliens*/
	for(i = 0; i < 2; i++){
		pos_col = 1;
		for(j = 0; j < 11; j++){			
			if (! insere_fim_lista(pos_lin, pos_col, 1, 3, 5, ALIEN_3_A, aliens))
				return 0;
			pos_col+=7;
		}
		pos_lin+=4;
	}

	/*Inserindo barreiras*/
	/*LINHA 1 - BARREIRAS*/
	pos_col = 16;
	pos_lin = 28;
	for(i = 0; i < 4; i++){
		if (! insere_fim_lista(pos_lin, pos_col, 1, 1, 1, BARRIER_A, barreira))
			return 0;
		for(j = 0; j < 3; j++){
			pos_col++;
			if (! insere_fim_lista(pos_lin, pos_col, 1, 1, 1, BARRIER_M, barreira))
				return 0;			
		}
		pos_col++;
		if (! insere_fim_lista(pos_lin, pos_col, 1, 1, 1, BARRIER_A, barreira))
			return 0;
		pos_col+=16;
	}
	/*LINHA 2 - BARREIRAS*/
	pos_col = 15;
	pos_lin = 29;
	for(i = 0; i < 4; i++){
		if (! insere_fim_lista(pos_lin, pos_col, 1, 1, 1, BARRIER_A, barreira))
			return 0;
		for(j = 0; j < 5; j++){
			pos_col++;
			if (! insere_fim_lista(pos_lin, pos_col, 1, 1, 1, BARRIER_M, barreira))
				return 0;			
		}
		pos_col++;
		if (! insere_fim_lista(pos_lin, pos_col, 1, 1, 1, BARRIER_A, barreira))
			return 0;
		pos_col+=14;
	}
	/*LINHA 3 - BARREIRAS*/
	pos_col = 14;
	pos_lin = 30;
	for(i = 0; i < 4; i++){
		for(j = 0; j < 2; j++){
			pos_col++;
			if (! insere_fim_lista(pos_lin, pos_col, 1, 1, 1, BARRIER_M, barreira))
				return 0;			
		}
		pos_col+=3;
		for(j = 0; j < 2; j++){
			pos_col++;
			if (! insere_fim_lista(pos_lin, pos_col, 1, 1, 1, BARRIER_M, barreira))
				return 0;			
		}
		pos_col+=13;
	}

	return 1;
}
void imprime_jogo(t_lista *tiros_canhao, t_lista *canhao, t_lista *barreiras, t_lista *aliens, t_lista *tiros_aliens){
	clear();

	imprime_lista(tiros_canhao);
	imprime_lista(canhao);
	imprime_lista(barreiras);
	imprime_lista(aliens);
	imprime_lista(tiros_aliens);

	imprime_borda();

	refresh();
}
void imprime_borda(){
	int i;

	for (i = 1; i < TAM_LIN-1; i++){
		move(i, 0);
		addch('|');
		move(i, TAM_COL-1);
		addch('|');
	}
	for (i = 0; i < TAM_COL; i++){
		move(0, i);
		addch('-');
		move(TAM_LIN-1, i);
		addch('-');
	}
}

/*Imprime a lista*/
void imprime_lista(t_lista *lista){
	if (lista_vazia(lista))
		return;

	int pos_lin, pos_col, estado, tam_lin, tam_col, i, j, k;
	char estilo[MAX];

	inicializa_atual_inicio(lista);	
	while(consulta_item_atual(&pos_lin, &pos_col, &estado, &tam_lin, &tam_col, estilo, lista) == 1){	
		k = 0;

		if(estado == 0){
			remove_item_atual(lista);
		}
		else if (estado == 1){
			for(i = 0; i < tam_lin; i++)			
				for(j = 0; j < tam_col; j++){
					move((pos_lin + i), (pos_col + j));
					addch(estilo[k]);
					k++;
				}
			incrementa_atual(lista);
		} 
		else if (estado == 2){
			muda_estilo(estilo, EXPLOSION);
			for(i = 0; i < tam_lin; i++)
				for(j = 0; j < tam_col; j++){
					move((pos_lin + i), (pos_col + j));
					addch(estilo[k]);
					k++;
				}
			lista->atual->estado = 0;
			incrementa_atual(lista);
		}		
	}

}
/*verifica colisão de elementos*/
void verifica_colisao(t_lista *tiros_canhao, t_lista *canhao, t_lista *barreiras, t_lista *aliens, t_lista *tiros_aliens){

	t_nodo *alien, *barreira, *tiro;

	int atual_remov;		/*atual_remov indica se o nodo em atual foi removido*/

	/*verifica colisão de aliens*/
	if(! lista_vazia(aliens)){
		inicializa_atual_inicio(aliens);
		alien = aliens->atual;
		while(alien != NULL){
			/*verifica colisão de tiros_canhao em aliens*/
			if(! lista_vazia(tiros_canhao)){
				inicializa_atual_inicio(tiros_canhao);
				tiro = tiros_canhao->atual;		
				while(tiro != NULL){
					atual_remov = 0;
					if((tiro->pos_lin >= alien->pos_lin) && (tiro->pos_lin <= (alien->pos_lin + alien->tam_lin-1)))
						if((tiro->pos_col >= alien->pos_col) && (tiro->pos_col <= (alien->pos_col + alien->tam_col-1))){
							alien->estado = 2;
							if (! remove_item_atual(tiros_canhao))
								return;
							else
								atual_remov = 1;
						}
					if(!atual_remov)
						incrementa_atual(tiros_canhao);
					tiro = tiros_canhao->atual;
				}
			}
			/*verifica colisão de barreiras em aliens*/
			if(! lista_vazia(barreiras)){
				inicializa_atual_inicio(barreiras);
				barreira = barreiras->atual;		
				while(barreira != NULL){
					atual_remov = 0;
					if((barreira->pos_lin >= alien->pos_lin) && (barreira->pos_lin <= (alien->pos_lin + alien->tam_lin-1)))
						if((barreira->pos_col >= alien->pos_col) && (barreira->pos_col <= (alien->pos_col + alien->tam_col-1))){
							if (! remove_item_atual(barreiras))
								return;
							else
								atual_remov = 1;
						}
					if(!atual_remov)
						incrementa_atual(barreiras);
					barreira = barreiras->atual;
				}
			}
			incrementa_atual(aliens);
			alien = aliens->atual;
		}
	}
	
	/*verifica colisão de tiros na barreira*/
	if(! lista_vazia(barreiras)){
		inicializa_atual_inicio(barreiras);
		barreira = barreiras->atual;
		while(barreira != NULL){
			if(! lista_vazia(tiros_canhao)){
				inicializa_atual_inicio(tiros_canhao);
				tiro = tiros_canhao->atual;		
				while(tiro != NULL){
					atual_remov = 0;
					if((tiro->pos_lin >= barreira->pos_lin) && (tiro->pos_lin <= (barreira->pos_lin + barreira->tam_lin-1)))
						if((tiro->pos_col >= barreira->pos_col) && (tiro->pos_col <= (barreira->pos_col + barreira->tam_col-1))){
							barreira->estado = 2;
							if (! remove_item_atual(tiros_canhao))
								return;
							else
								atual_remov = 1;
						}
					if(!atual_remov)
						incrementa_atual(tiros_canhao);
					tiro = tiros_canhao->atual;
				}
			}
			if(! lista_vazia(tiros_aliens)){
				inicializa_atual_inicio(tiros_aliens);
				tiro = tiros_aliens->atual;		
				while(tiro != NULL){
					atual_remov = 0;
					if((tiro->pos_lin >= barreira->pos_lin) && (tiro->pos_lin <= (barreira->pos_lin + barreira->tam_lin-1)))
						if((tiro->pos_col >= barreira->pos_col) && (tiro->pos_col <= (barreira->pos_col + barreira->tam_col-1))){
							barreira->estado = 2;
							if (! remove_item_atual(tiros_aliens))
								return;
							else
								atual_remov = 1;
						}
					if(!atual_remov)
						incrementa_atual(tiros_aliens);
					tiro = tiros_aliens->atual;
				}
			}
			incrementa_atual(barreiras);
			barreira = barreiras->atual;
		}
	}

	/*verifica colisão de tiros na barreira*/
	if(! lista_vazia(canhao)){
		inicializa_atual_inicio(canhao);		
		if(! lista_vazia(tiros_aliens)){
			inicializa_atual_inicio(tiros_aliens);
			tiro = tiros_aliens->atual;		
			while(tiro != NULL){
				atual_remov = 0;
				if((tiro->pos_lin >= canhao->atual->pos_lin) && (tiro->pos_lin <= (canhao->atual->pos_lin + canhao->atual->tam_lin-1)))
					if((tiro->pos_col >= canhao->atual->pos_col) && (tiro->pos_col <= (canhao->atual->pos_col + canhao->atual->tam_col-1))){
						canhao->atual->estado = 2;
						if (! remove_item_atual(tiros_aliens))
							return;
						else
							atual_remov = 1;
					}
				if(!atual_remov)
					incrementa_atual(tiros_aliens);
				tiro = tiros_aliens->atual;
			}			
		}
	}

}
/*movimenta os tiros*/
void move_tiros(t_lista *tiros, int direcao){
	if(! lista_vazia(tiros)){
		inicializa_atual_inicio(tiros);
		while(tiros->atual != NULL){
			if (move_elemento(tiros, direcao))
				remove_item_atual(tiros);
			else
				incrementa_atual(tiros);
		}
	}
}
/*movimenta os aliens*/
void move_aliens(t_lista *aliens, int *direcao, int *vel_alien){
	int prox_dir, colisao;

	colisao = 0;
	prox_dir = *direcao;

	if(*direcao == 5){				/*Próxima direção será para esquerda*/
		prox_dir = 1;
		*direcao = 4;
	} else if(*direcao == 6){		/*Próxima direção será para direita*/
		prox_dir = 2;
		*direcao = 4;
	}	
	if(! lista_vazia(aliens)){
		inicializa_atual_inicio(aliens);
		while(aliens->atual != NULL){

			if(strcmp(aliens->atual->estilo, ALIEN_1_A) == 0)
				muda_estilo(aliens->atual->estilo, ALIEN_1_B);
			else if(strcmp(aliens->atual->estilo, ALIEN_1_B) == 0)
				muda_estilo(aliens->atual->estilo, ALIEN_1_A);

			else if(strcmp(aliens->atual->estilo, ALIEN_2_A) == 0)
				muda_estilo(aliens->atual->estilo, ALIEN_2_B);
			else if(strcmp(aliens->atual->estilo, ALIEN_2_B) == 0)
				muda_estilo(aliens->atual->estilo, ALIEN_2_A);

			else if(strcmp(aliens->atual->estilo, ALIEN_3_A) == 0)
				muda_estilo(aliens->atual->estilo, ALIEN_3_B);
			else if(strcmp(aliens->atual->estilo, ALIEN_3_B) == 0)
				muda_estilo(aliens->atual->estilo, ALIEN_3_A);
			
			if(move_elemento(aliens, *direcao) && !colisao)
				colisao = 1;

			incrementa_atual(aliens);
		}	
		if(colisao){
			if(*direcao == 1){
				prox_dir = 6;
			} else if (*direcao == 2){
				prox_dir = 5;
			}
			if(*vel_alien > 2)
				(*vel_alien)-=2;
		}

		*direcao = prox_dir;				
	}
}
/*muda estilo*/
void muda_estilo(char *estilo, char novo[]){
	int i = 0;

	while(novo[i] != '\0' && i < MAX){
		estilo[i] = novo[i];
		i++;
	}
	estilo[i] = novo[i];
}

/*função para mover o canhao*/
/*Direção 1 para esquerda, 2 para direita, 3 para cima e 4 para baixo*/
/*Retorna 1 se bateu*/
int move_elemento(t_lista *l, int direcao){
	if (lista_vazia(l))
		return 0;

	t_nodo *p;
	p = l->atual;

	/*Move o elemento para esquerda*/
	if (direcao == 1){
		if (p->pos_col > 1)
			p->pos_col--;
		if (p->pos_col == 1)
			return 1;
	}
	/*Move o elemento para direita*/
	if (direcao == 2){
		if ((p->pos_col + p->tam_col) < 99)
			p->pos_col++;
		if ((p->pos_col + p->tam_col) == 99)
			return 1;
	}
	/*Move o elemento para cima*/
	if (direcao == 3){
		if (p->pos_lin > 1)
			p->pos_lin--;
		else
			if (p->estado == 1)
				return 1;
	}
	/*Move o elemento para baixo*/
	if (direcao == 4){
		if ((p->pos_lin + p->tam_lin) < 36)
			p->pos_lin++;
		else
			if (p->estado == 1)
				return 1;
	}

	return 0;
}
/*função para o canhao atirar*/
void canhao_atira(t_lista *tiros, t_lista *canhao){
	if (lista_vazia(canhao))
		return;

	int tam;	
	tamanho_lista(&tam, tiros);	
	if(tam >= 3){
		return;
	}

	inicializa_atual_inicio(canhao);
	int pos_lin, pos_col;
	pos_lin = canhao->atual->pos_lin-1;
	pos_col = canhao->atual->pos_col+2;

	if (! insere_fim_lista(pos_lin, pos_col, 1, 1, 1, CANHAO_SHOT, tiros))
		return;
}
/*função para o alien atirar*/
void alien_atira(t_lista *tiros, t_lista *aliens, int num_alien){
	if (lista_vazia(aliens))
		return;

	int i, pos_lin, pos_col;

	inicializa_atual_inicio(aliens);
	for(i = 0; i < num_alien; i++){
		incrementa_atual(aliens);
	}

	pos_lin = aliens->atual->pos_lin+(aliens->atual->tam_lin);
	pos_col = aliens->atual->pos_col+((aliens->atual->tam_col)/2);

	if (! insere_fim_lista(pos_lin, pos_col, 1, 1, 1, ALIEN_SHOT, tiros))
		return;
}