#include <ncurses.h>
#include <string.h>

void menu(WINDOW *win);
void salvar();
void abrir();
void novo_arquivo();
void ajuda();
int quit = 0;

int main(){ 
  char c;
	char splash[4][50]={"BEM AO VENCI!",
					"An Epic Epic of Epicness Text Editor",
					"Aperte ESC para acessar o menu",
					"Utilize o comando :h para ajuda..."
					};

	initscr();
	cbreak();
	noecho();
	
	attron(A_BOLD);
	mvprintw((LINES/2)-2, (COLS-strlen(splash[0]))/2,"%s",splash[0]);
	attroff(A_BOLD);
	attron(A_UNDERLINE);
	mvprintw((LINES/2)-1, (COLS-strlen(splash[1]))/2,"%s",splash[1]);
	attroff(A_UNDERLINE);
	mvprintw(LINES/2, (COLS-strlen(splash[2]))/2,"%s",splash[2]);
	mvprintw((LINES/2)+1, (COLS-strlen(splash[3]))/2,"%s",splash[3]);
	refresh();
	move(0,0);
	
	WINDOW *win;
	win = newwin(2, COLS, LINES-2, 0);
	
	menu(win);
	
	if(quit == 1){
		delwin(win);
		endwin();
		return 0;
	}
	
	while((c = getch())){
		if(c == 27){
			menu(win);
			if(quit == 1){
				break;
			}
		}else{
			printw("%c",c);
		}
		refresh();
	}
	
	delwin(win);
	endwin();
	return 0;
}

void menu(WINDOW *win){
	
	char option[6];
	werase(win);
	mvwaddstr(win, 0, 0, "-------------------------MODO-MENU----------------------------------------------\n");
	wrefresh(win);
	
	echo();
	
	mvwscanw(win,1,0,"%s", option);
	
	if (strcmp(option,"i")==0){
		werase(win);
	}else if (strcmp(option,":q")==0){
		quit = 1;
	}else if (strcmp(option,":w")==0){
		wprintw(win,"Função salvar ainda não implementada!");
	}else if (strcmp(option,":e")==0){
		wprintw(win,"Função abrir arquivo ainda não implementada!");
	}else if (strcmp(option,":enew")==0){
		wprintw(win,"Função novo arquivo ainda não implementada!");
	}else if (strcmp(option,":h")==0){	
		erase();
		refresh();
		printw("YOU KNOW I NEED SOMEONE...HEEEELP!!!!!\n\nHá dois modos no editor: MENU e INSERIR.\nO programa inicia no MODO MENU.\nPara inserir, tecle i e dê ENTER.\nPara ir para o menu, tecle ESC. Digite um dos comandos a seguir:\n----> :e --- abre um arquivo;\n----> :enew --- abre um novo arquivo;\n----> :w --- salva um arquivo;\n----> :q --- sair do programa;\n----> :h --- ajuda;\n");
	}else{
		wprintw(win,"Comando inválido");
	}

	mvwaddstr(win, 0, 0,"--------------------------INSERIR-----------------------------------------------\n");
	wrefresh(win);
	
	noecho();
}
