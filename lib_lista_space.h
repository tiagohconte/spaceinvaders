  /*
  Biblioteca para a implementação do jogo Space Invaders
  Feita por Tiago Henrique Conte
  10 de novembro de 2019
*/

#include <stdlib.h>
#define MAX 27

struct t_nodo {
    int pos_lin;
    int pos_col;
    int estado;
    int tam_lin;
    int tam_col;
    char estilo[MAX];
    struct t_nodo *prox;
    struct t_nodo *prev;
};
typedef struct t_nodo t_nodo;

struct t_lista {
    t_nodo *ini;
    t_nodo *atual;
    t_nodo *fim;
    int tamanho;
};
typedef struct t_lista t_lista;

/*
  Cria uma lista vazia. Ela eh duplamente encadeada e tem sentinelas no
  inicio e no final. Tambem tem um apontador para um elemento qualquer.
*/
int inicializa_lista(t_lista *l);

/*
  Retorna 1 se a lista está vazia e zero caso contrário.
*/
int lista_vazia(t_lista *l);

/*
  Remove todos os elementos da lista e faz com que ela aponte para NULL.
*/
void destroi_lista(t_lista *l);

/*
  Retorna o tamanho da lista em *tam.
  Retorna 1 se a operação foi bem sucedida e zero caso contrário.
*/
int tamanho_lista(int *tam, t_lista *l);

/*
  Insere o elemento item no início da lista.
  Retorna 1 se a operação foi bem sucedida e zero caso contrário.
*/
int insere_inicio_lista(int pos_lin, int pos_col, int estado, int tam_lin, int tam_col, char estilo[], t_lista *l);

/*
  Insere o elemento item no final da lista.
  Retorna 1 se a operação foi bem sucedida e zero caso contrário.
*/
int insere_fim_lista(int pos_lin, int pos_col, int estado, int tam_lin, int tam_col, char estilo[], t_lista *l);

/*
  Remove o primeiro elemento da lista e retorna localização em local.
  Retorna 1 se a operação foi bem sucedida e zero caso contrário.
*/
int remove_inicio_lista(t_lista *l);

/*
  Remove o último elemento da lista e o retorna em *item.
  Retorna 1 se a operação foi bem sucedida e zero caso contrário.
*/
int remove_fim_lista(t_lista *l);

/* 
  Inicializa o ponteiro atual para o primeiro elemento da lista.
  Retorna 1 se a operação foi bem sucedida e zero caso contrário.
*/
int inicializa_atual_inicio(t_lista *l);

/* 
  Inicializa o ponteiro atual para o ultimo elemento da lista.
  Retorna 1 se a operação foi bem sucedida e zero caso contrário.
*/
int inicializa_atual_fim(t_lista *l);

/*
  Faz o ponteiro atual apontar para o próximo nodo da lista l e retorna 
  este ponteiro. Se atual estiver apontando para o último, isto é, não 
  tem próximo, retorna NULL.
*/
void incrementa_atual(t_lista *l);

/*
  Faz o ponteiro atual apontar para o nodo anterior da lista l e retorna 
  este ponteiro. Se atual estiver apontando para o primeiro, isto é, não 
  tem anterior, retorna NULL.
*/
void decrementa_atual(t_lista *l);

/*
  Retorna em *item o valor contido na chave apontada pelo ponteiro atual. 
  Se atual não for válido a função retorna zero senão retorna 1.
*/
int consulta_item_atual(int *pos_lin, int *pos_col, int *estado, int *tam_lin, int *tam_col, char estilo[], t_lista *l);

/*
  Remove o elemento apontado por atual da lista l e o retorna em *item.
  Faz o atual apontar para o sucessor do nodo removido.
  Retorna 1 se houve sucesso e zero caso contrário.
*/
int remove_item_atual(t_lista *l);
