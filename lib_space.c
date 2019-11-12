#include "lib_space.h"
#include <stdio.h>
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

	/*int pos_lin, pos_col, velocidade, estado, tam_lin, tam_col;
	char estilo[MAX];*/

	/*Inserindo canhao na lista*/
	if (! insere_inicio_lista(34, 47, 1, 1, 2, 5, CANHAO_STYLE, canhao)){
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
		if (! insere_inicio_lista(pos_lin, pos_col, 1, 1, 3, 5, ALIEN_1_A, aliens))
			return 0;
		pos_col+=7;
	}
	pos_lin+=4;
	/*Segundo estilo de aliens*/
	while(pos_lin < 17){
		pos_col = 1;
		for(i = 0; i < 11; i++){
			if (! insere_inicio_lista(pos_lin, pos_col, 1, 1, 3, 5, ALIEN_2_A, aliens))
				return 0;
			pos_col+=7;
		}
		pos_lin+=4;
	}
	/*Terceiro estilo de aliens*/
	while(pos_lin < 25){
		pos_col = 1;
		for(i = 0; i < 11; i++){
			if (! insere_inicio_lista(pos_lin, pos_col, 1, 1, 3, 5, ALIEN_3_A, aliens))
				return 0;
			pos_col+=7;
		}
		pos_lin+=4;
	}
	/*Inserindo barreiras*/
	pos_col = 15;
	pos_lin = 28;
	for(i = 0; i < 4; i++){
		if (! insere_inicio_lista(pos_lin, pos_col, 1, 1, 3, 7, BARRIER, barreira))
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
		}
		incrementa_atual(lista);
	}

}

/*muda estilo*/
void muda_estilo(char *estilo, char novo[]){
	int i = 0;

	while(novo[i] != '\0' && i < MAX){
		estilo[i] = novo[i];
		i++;
	}
}

/*função para mover o canhao*/
/*Direção 1 para esquerda e 2 para direita*/
void move_elemento(t_lista *l, int direcao){
	if (lista_vazia(l))
		return;

	t_nodo *p;

	p = l->ini->prox;

	while(p != NULL){
		if (direcao == 1)
			if (p->pos_col > 1)
				p->pos_col--;
		
		if (direcao == 2)
			if ((p->pos_col + p->tam_col) < 99)
				p->pos_col++;

		p = p->prox;
	}
}
/*função para o canhao atirar*/
void canhao_atira(t_lista *tiros){

}