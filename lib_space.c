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
/* Fecha o ncurses */
void finaliza_ncurses(){
	endwin();
    exit(0);
}
int inicia_jogo(t_lista *tiros, t_lista *canhao, t_lista *barreira, t_lista *aliens){
	/*Inicializando as listas*/
	if (! inicializa_lista(tiros))
		return 0;
	if (! inicializa_lista(canhao))
		return 0;
	if (! inicializa_lista(barreira))
		return 0;
	if (! inicializa_lista(aliens))
		return 0;

	/*Inserindo canhao na lista*/
	if (! insere_inicio_lista(34, 47, 1, 2, 5, CANHAO_STYLE, canhao)){
		return 0;
	}
	/*endwin();
	inicializa_atual_inicio(canhao);
	printf("estilo: %s", canhao->atual->estilo);
	exit(0);*/

	/*Inserindo aliens na lista*/
	int i;
	int pos_col, pos_lin;
	pos_lin = 5;
	/*Primeiro estilo de aliens*/
	pos_col = 1;
	for(i = 0; i < 11; i++){
		if (! insere_inicio_lista(pos_lin, pos_col, 1, 3, 5, ALIEN_1_A, aliens))
			return 0;
		pos_col+=7;
	}
	pos_lin+=4;
	/*Segundo estilo de aliens*/
	while(pos_lin < 17){
		pos_col = 1;
		for(i = 0; i < 11; i++){
			if (! insere_inicio_lista(pos_lin, pos_col, 1, 3, 5, ALIEN_2_A, aliens))
				return 0;
			pos_col+=7;
		}
		pos_lin+=4;
	}
	/*Terceiro estilo de aliens*/
	while(pos_lin < 25){
		pos_col = 1;
		for(i = 0; i < 11; i++){
			if (! insere_inicio_lista(pos_lin, pos_col, 1, 3, 5, ALIEN_3_A, aliens))
				return 0;
			pos_col+=7;
		}
		pos_lin+=4;
	}

	/*Inserindo barreiras*/
	pos_col = 15;
	pos_lin = 28;
	for(i = 0; i < 4; i++){
		if (! insere_inicio_lista(pos_lin, pos_col, 1, 3, 7, BARRIER, barreira))
			return 0;
		pos_col+=21;
	}

	return 1;
}
void imprime_jogo(t_lista *l1, t_lista *l2, t_lista *l3, t_lista *l4){
	clear();

	imprime_lista(l1);
	imprime_lista(l2);
	imprime_lista(l3);
	imprime_lista(l4);

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
		if (estado == 1){
			for(i = 0; i < tam_lin; i++)
				for(j = 0; j < tam_col; j++){
					move((pos_lin + i), (pos_col + j));
					addch(estilo[k]);
					k++;
				}
		}
		else if (estado == 2){
			muda_estilo(estilo, EXPLOSION);
			for(i = 0; i < tam_lin; i++)
				for(j = 0; j < tam_col; j++){
					move((pos_lin + i), (pos_col + j));
					addch(estilo[k]);
					k++;
				}
			remove_item_atual(&pos_lin, &pos_col, lista);
		}
		incrementa_atual(lista);
	}

}
/*verifica colisão de elementos*/
void verifica_colisao(t_lista *tiros, t_lista *canhao, t_lista *barreira, t_lista *aliens){
	t_nodo *alien, *tiro;
	int pos_lin, pos_col;

	/*verifica colisão de aliens*/
	if(! lista_vazia(aliens)){
		inicializa_atual_inicio(aliens);
		alien = aliens->atual;
		while(aliens->atual != NULL){
			if(! lista_vazia(tiros)){
				inicializa_atual_inicio(tiros);
				tiro = tiros->atual;		
				while(tiros->atual != NULL){
					tiro = tiros->atual;
					if((tiro->pos_lin >= alien->pos_lin) && (tiro->pos_lin <= (alien->pos_lin + alien->tam_lin-1)))
						if((tiro->pos_col >= alien->pos_col) && (tiro->pos_col <= (alien->pos_col + alien->tam_col-1))){
							alien->estado = 2;
							if (! remove_item_atual(&pos_lin, &pos_col, tiros))
								return;
						}
					incrementa_atual(tiros);
					tiro = tiros->atual;
				}
			}
			incrementa_atual(aliens);
			alien = aliens->atual;
		}
	}
}
/*movimenta os tiros*/
void move_tiros(t_lista *tiros){
	int pos_lin, pos_col;

	if(! lista_vazia(tiros)){
		inicializa_atual_inicio(tiros);
		while(tiros->atual != NULL){
			if (move_elemento(tiros, 3))
				remove_item_atual(&pos_lin, &pos_col, tiros);
			incrementa_atual(tiros);
		}
	}
}
/*movimenta os aliens*/
void move_aliens(t_lista *aliens, int *direcao, int *vel_alien){
	int prox_dir, down = 4, temp;
	prox_dir = *direcao;
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


			if(move_elemento(aliens, *direcao)){
				if(*direcao == 1){
					prox_dir = 2;
				} else if (*direcao == 2){
					prox_dir = 1;
				}
			}
			incrementa_atual(aliens);
		}
		if(*direcao != prox_dir){
			move_aliens(aliens, &down, &temp);
			*direcao = prox_dir;
			*vel_alien--;
		}					
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

	if (direcao == 1){
		if (p->pos_col > 1)
			p->pos_col--;
		if (p->pos_col == 1)
			return 1;
	}
	
	if (direcao == 2){
		if ((p->pos_col + p->tam_col) < 99)
			p->pos_col++;
		if ((p->pos_col + p->tam_col) == 99)
			return 1;
	}

	if (direcao == 3){
		if (p->pos_lin > 1)
			p->pos_lin--;
		else
			if (p->estado == 1)
				return 1;
	}
	
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
	if(tiros->tamanho >= 3){
		return;
	}

	inicializa_atual_inicio(canhao);
	int pos_lin, pos_col;
	pos_lin = canhao->atual->pos_lin-1;
	pos_col = canhao->atual->pos_col+2;

	if (! insere_inicio_lista(pos_lin, pos_col, 1, 1, 1, CANHAO_SHOT, tiros))
		return;
}