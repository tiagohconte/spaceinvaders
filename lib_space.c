#include "lib_space.h"
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
	if (! insere_inicio_lista(98, 17, 1, 1, 2, 5, CANHAO_STYLE, canhao)){
		return 0;
	}
	/*endwin();
	inicializa_atual_inicio(canhao);
	printf("estilo: %s", canhao->atual->estilo);
	exit(0);*/

	/*Inserindo aliens na lista*/
	/*int i;*/
	/*Primeiro modelo de alien*/
	/*for(i = 0; i < 7; i++)*/
		if (! insere_inicio_lista(50, 17, 1, 1, 3, 5, ALIEN_1_A, aliens)){
			return 0;
		}

	imprime_jogo(tiros, canhao, barreira, aliens);

	return 1;
}
void imprime_jogo(t_lista *l1, t_lista *l2, t_lista *l3, t_lista *l4){
	clear();

	imprime_lista(l1);
	imprime_lista(l2);
	imprime_lista(l3);
	imprime_lista(l4);

	imprime_borda();

	move(10,10);
	addch('#');	

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
		/*endwin();
		printf("pos_lin: %d\n", pos_lin);
		printf("pos_col: %d\n", pos_col);
		printf("tam_lin: %d\n", tam_lin);
		printf("tam_col: %d\n", tam_col);
		printf("estado: %d\n", estado);
		exit(0);*/
		/*move(50, 17);
		addch('O');*/
		if (estado == 1){
			for(i = pos_lin; i < (pos_lin+tam_lin); i++){
				for(j = pos_col; j < (pos_col+tam_col); j++){
					move(i, j);
					addch(estilo[k]);
					k++;
				}
			}
		}
		else if (estado == 2){
			muda_estilo(estilo, EXPLOSION);
			for(i = pos_lin; i < (pos_lin+5); i++)
				for(j = pos_col; j < (pos_col+5); j++){
					move(i, j);
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
void canhao_move(int direcao){

}
/*função para o canhao atirar*/
void canhao_atira(t_lista *tiros){

}