#include <ncurses.h>
void novo(WINDOW *edit, WINDOW *bar){
	
	// Limpa a tela
	werase(edit);
	wrefresh(edit);
	
}
void salvar(){}
void abrir(){}
void salvar_como(){}
void ajuda(WINDOW *menu, WINDOW *bar) {
	
	int i, j;
	
	// Limpa a tela
	werase(menu);
	wrefresh(menu);
	
	// Imprime a ajuda
	box(menu, 0, '\0');	
	for (i = 1; i < 19; i++) {
		for (j = 1; j < 29; j++) {
			mvwaddch(menu, i, j, ' ');
		}
	}	
	mvwprintw(menu, 1, 2, "Ajuda");
	mvwprintw(menu, 3, 2, "Adhoc");
	
	// Organiza a barra
	werase(bar);
	wrefresh(bar);
	mvwprintw(bar, 1, 0, "Pressione qualquer tecla para voltar ao editor.");
	
	// Exibe a ajuda
	wrefresh(bar);
	wrefresh(menu);
	
	getch();
				
	werase(bar);
	wrefresh(bar);

}

int show_menu(WINDOW *menu, WINDOW *bar, WINDOW *edit) {
	
	//Inicialização
	curs_set(0);
	
	int pos = 4;
	int ch;
	
	// Colocar bordas na menu
	box(menu, 0, '\0');
	
	// Imprime o menu
	mvwprintw(menu, 2, 12, "VENCI");
	mvwprintw(menu, 4,5,"novo");
	mvwprintw(menu, 5,5,"abrir");
	mvwprintw(menu, 6,5,"salvar");
	mvwprintw(menu, 7,5,"salvar como");
	mvwprintw(menu, 8,5,"ajuda");
	mvwprintw(menu, 9,5,"sair");
	mvwaddch(menu, pos, 3, '>');
	
	wrefresh(menu);
	
	
	// Movimentação do cursor e sair do menu
	while ((ch = getch())){
		mvwaddch(menu, pos, 3, ' ');
		if (ch == KEY_DOWN){
			if (pos >=4 && pos <=8){
				pos++;
			}else if (pos == 9){
				pos = 4;
			}
		}else if (ch == KEY_UP){
			if (pos >=5 && pos <=9){
				pos--;
			}else if (pos == 4){
				pos = 9;
			}
		}else if (ch == 10){ // ENTER para escolher opção
			break;
		}else if (ch == 27){ // ESC para sair do menu sem selecionar
			return 0;
		}
		
		mvwaddch(menu, pos, 3, '>');
		wrefresh(menu);
	}
	
	werase(bar);
	wrefresh(bar);
	
	// Executa a função de acordo com a opção escolhida
	switch(pos) {		
		case 4: novo(edit, bar);
			mvwprintw(bar, 1, 0, "Função novo não implementada");
			break;
		case 5: abrir();
			mvwprintw(bar, 1, 0, "Função abrir não implementada");
			break;	
		case 6: salvar();
			mvwprintw(bar, 1, 0, "Função salvar não implementada");
			break;	
		case 7: salvar_como();
			mvwprintw(bar, 1, 0, "Função salvar como não implementada");
			break;	
		case 8: ajuda(menu, bar);
			break;
		case 9:
			return 1;
			break;
	}
	wrefresh(bar);

	curs_set(1);
	return 0;
}

int main() {
	
	// Inicia a ncurses
	initscr();
	noecho();
	cbreak();

	// Cria as  janelas
	WINDOW *menu;
	WINDOW *edit;
	WINDOW *bar;
		
	menu = newwin(20, 30, (LINES/2)-10, (COLS/2)-15);
	edit = newwin(LINES-2, COLS, 0, 0);
	bar = newwin(2, COLS, LINES-2, 0);
	
	// Habilita teclas especiais
	keypad(stdscr, TRUE);
	keypad(menu, TRUE);

	// Refresh para plotar todas as janelas
	refresh();
	
	// Inicializa as variáveis da main
	short init = 0;
	char ch;	
	
	// Loop principal
	while (1) {
		if (ch == 27 || init == 0) { // ESC ou primeira execução do loop para exebir o menu
			if(show_menu(menu, bar, edit) == 1){
				break;
			}
		
			init = 1;
			
			werase(menu);
			wrefresh(menu);
			
			wrefresh(edit);
			wmove(edit, 0, 0);
		}
		
		ch = getch();
		
		if (ch != 27) {
			waddch(edit, ch);
			wrefresh(edit);
		}
		
	}

	endwin();
		 
	return 0;
}
