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
int inicia_jogo(t_lista *tiros, t_lista *player, t_lista *barreira, t_lista *aliens){
	/*Inicializando as listas*/
	if (! inicializa_lista(tiros))
		return 0;
	if (! inicializa_lista(player))
		return 0;
	if (! inicializa_lista(barreira))
		return 0;
	if (! inicializa_lista(aliens))
		return 0;

	/*int pos_lin, pos_col, velocidade, estado, tam_lin, tam_col;
	char estilo[MAX];*/

	/*Inserindo player na lista*/
	if (! insere_inicio_lista(98, 17, 1, 1, 2, 5, PLAYER_SPACESHIP, player)){
		return 0;
	}

	/*endwin();
	inicializa_atual_inicio(player);
	printf("estilo: %s", player->atual->estilo);
	exit(0);*/

	imprime_jogo(tiros, player, barreira, aliens);

	return 1;
}
void imprime_jogo(t_lista *l1, t_lista *l2, t_lista *l3, t_lista *l4){
	clear();

	/*move(50,20);
	addch('#');*/
	imprime_lista(l1);
	/*imprime_lista(l2);
	imprime_lista(l3);
	imprime_lista(l4);*/
	imprime_borda();

	refresh();
}
void imprime_borda(){
	int i;

	clear();
	for (i = 1; i < TAM_X-1; i++){
		move(i, 0);
		addch('|');
		move(i, TAM_Y-1);
		addch('|');
	}
	for (i = 0; i < TAM_Y; i++){
		move(0, i);
		addch('-');
		move(TAM_X-1, i);
		addch('-');
	}
	refresh();
}

/*Imprime a lista*/
void imprime_lista(t_lista *lista){
	int pos_lin, pos_col, estado, tam_lin, tam_col, i, j, k;
	char estilo[MAX];

	inicializa_atual_inicio(lista);
	while(consulta_item_atual(&pos_lin, &pos_col, &estado, &tam_lin, &tam_col, estilo, lista) == 1){
		
		k = 0;
		if (estado == 1){
			for(i = pos_lin; i < (pos_lin+tam_lin); i++)
				for(j = pos_col; j < (pos_col+tam_col); j++){
					move(i, j);
					addch(estilo[k]);
					k++;
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

/*função para mover o jogador*/
void player_move(int dir){

}
/*função para o jogador atirar*/
void player_atira(t_lista *tiros){

}