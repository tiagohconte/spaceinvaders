#include "lib_lista_space.h"

/* Cria uma lista vazia duplamente encadeada com sentinelas no
  inicio e no final. Tambem tem um apontador para um elemento qualquer. */
int inicializa_lista(t_lista *l){
	l->tamanho = 0;
	l->ini = (t_nodo *) malloc(sizeof(t_nodo));
	if (l->ini == NULL)
		return 0;
	l->fim = (t_nodo *) malloc(sizeof(t_nodo));
	if (l->fim == NULL)		
		return 0;

	l->ini->prox = l->fim;
	l->ini->prev = NULL;

	l->fim->prox = NULL;
	l->fim->prev = l->ini;

	l->atual = NULL;
	
	return 1;
}
/* Retorna 1 se a lista está vazia e zero caso contrário. */
int lista_vazia(t_lista *l){
	if (l->tamanho == 0)
		return 1;
	return 0;
}
/* Remove todos os elementos da lista e faz com que ela aponte para NULL. */
void destroi_lista(t_lista *l){
	if(!inicializa_atual_inicio(l))
		return;

	while (! lista_vazia(l)){
		remove_item_atual(l);
	}

	free(l->ini);
	free(l->fim);

	l->ini = NULL;
	l->fim = NULL;
	l->atual = NULL;
}
/* Retorna o tamanho da lista em *tam.
  Retorna 1 se a operação foi bem sucedida e zero caso contrário. */
int tamanho_lista(int *tam, t_lista *l){
	if (lista_vazia(l))
		return 0;

	*tam = l->tamanho;
	return 1;
}
/* Insere o elemento item no início da lista.
  Retorna 1 se a operação foi bem sucedida e zero caso contrário. */
int insere_inicio_lista(int pos_lin, int pos_col, int estado, int tam_lin, int tam_col, char *estilo, t_lista *l){
	t_nodo *new;
	int i = 0;

	new = (t_nodo *) malloc(sizeof(t_nodo));
	if (new == NULL)
		return 0;

	new->pos_lin = pos_lin;
	new->pos_col = pos_col;
	new->estado = estado;
	new->tam_lin = tam_lin;
	new->tam_col = tam_col;	
	while(estilo[i] != '\0' && i < MAX){
		new->estilo[i] = estilo[i];
		i++;
	}

	new->prev = l->ini;
	new->prox = l->ini->prox;

	new->prox->prev = new;
	new->prev->prox = new;

	l->tamanho++;

	return 1;
}
/* Insere o elemento item no final da lista.
  Retorna 1 se a operação foi bem sucedida e zero caso contrário. */
int insere_fim_lista(int pos_lin, int pos_col, int estado, int tam_lin, int tam_col, char *estilo, t_lista *l){
	t_nodo *new;
	int i = 0;

	new = (t_nodo *) malloc(sizeof(t_nodo));
	if (new == NULL)
		return 0;

	new->pos_lin = pos_lin;
	new->pos_col = pos_col;
	new->estado = estado;
	new->tam_lin = tam_lin;
	new->tam_col = tam_col;
	while(estilo[i] != '\0' && i < MAX){
		new->estilo[i] = estilo[i];
		i++;
	}

	new->prev = l->fim->prev;
	new->prox = l->fim;

	new->prox->prev = new;
	new->prev->prox = new;

	l->tamanho++;

	return 1;
}
/* Remove o primeiro elemento da lista e o retorna em *item.
  Retorna 1 se a operação foi bem sucedida e zero caso contrário. */
int remove_inicio_lista(t_lista *l){
	if (lista_vazia(l))
		return 0;

	inicializa_atual_inicio(l);

	return remove_item_atual(l);
}
/*
  Remove o último elemento da lista e o retorna em *item.
  Retorna 1 se a operação foi bem sucedida e zero caso contrário. */
int remove_fim_lista(t_lista *l){
	if (lista_vazia(l))
		return 0;

	inicializa_atual_fim(l);

	return remove_item_atual(l);
}
/* Inicializa o ponteiro atual para o primeiro elemento da lista.
  Retorna 1 se a operação foi bem sucedida e zero caso contrário. */
int inicializa_atual_inicio(t_lista *l){
	if (lista_vazia(l)){
		l->atual = NULL;
		return 0;
	}
	l->atual = l->ini->prox;
	return 1;
}
/* Inicializa o ponteiro atual para o ultimo elemento da lista.
  Retorna 1 se a operação foi bem sucedida e zero caso contrário.
*/
int inicializa_atual_fim(t_lista *l){
	if (lista_vazia(l)){
		l->atual = NULL;
		return 0;
	}
	l->atual = l->fim->prev;
	return 1;
}
/* Faz o ponteiro atual apontar para o próximo nodo da lista l e retorna 
  este ponteiro. Se atual estiver apontando para o último, isto é, não 
  tem próximo, retorna NULL.
*/
void incrementa_atual(t_lista *l){
	if (l->atual->prox != l->fim)
		l->atual = (l->atual)->prox;
	else
		l->atual = NULL;
}
/* Faz o ponteiro atual apontar para o nodo anterior da lista l e retorna 
  este ponteiro. Se atual estiver apontando para o primeiro, isto é, não 
  tem anterior, retorna NULL. */
void decrementa_atual(t_lista *l){
	if (l->atual->prev != l->ini)
		l->atual = (l->atual)->prev;
	else
		l->atual = NULL;
}
/*
  Retorna em *item o valor contido na chave apontada pelo ponteiro atual. 
  Se atual não for válido a função retorna zero senão retorna 1. */
int consulta_item_atual(int *pos_lin, int *pos_col, int *estado, int *tam_lin, int *tam_col, char *estilo, t_lista *l){
	if (l->atual == NULL || l->atual == l->ini || l->atual == l->fim)
		return 0;

	int i = 0;

	*pos_lin = l->atual->pos_lin;
	*pos_col = l->atual->pos_col;
	*estado = l->atual->estado;
	*tam_lin = l->atual->tam_lin;
	*tam_col = l->atual->tam_col;
	while(l->atual->estilo[i] != '\0' && i < MAX){
		estilo[i] = l->atual->estilo[i];
		i++;
	}

	return 1;
}
/* Remove o elemento apontado por atual da lista l e o retorna em *item.
  Faz o atual apontar para o sucessor do nodo removido.
  Retorna 1 se houve sucesso e zero caso contrário. */
int remove_item_atual(t_lista *l){
	if (lista_vazia(l))
		return 0;

	t_nodo *temp;

	temp = l->atual->prox;
	l->atual->prox->prev = l->atual->prev;
	l->atual->prev->prox = l->atual->prox;
	free(l->atual);
	l->atual = temp;
	l->tamanho--;
	return 1;
}