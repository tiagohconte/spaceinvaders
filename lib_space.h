/* Inicia o ncurses */
void inicia_ncurses();
/* Fecha o ncurses */
void finaliza_ncurses();
/*imprime a borda do jogo*/
void imprime_borda(void);
void imprime_aliens(void);
/*função para mover o jogador*/
void player_move(int dir);
/*função para o jogador atirar*/
void player_atira(void);