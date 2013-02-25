/**
 * VENCI - https://github.com/mateuswetah/venci
 * Alunos: Eduardo Faria de Souza,
 * 		   Leonardo Vieira Pacheco,
 * 		   Mateus Machado Luna
 */

#include <ncurses.h>
#include <panel.h>
#include <string.h>

//Protótipos de função
void novo(WINDOW *edit, WINDOW *bar);
void salvar(WINDOW *edit, WINDOW *bar);
void abrir(WINDOW *edit, WINDOW *bar);
void salvar_como(WINDOW *edit, WINDOW *bar);
void ajuda(WINDOW *menu, WINDOW *bar, WINDOW *edit);
void show_menu(WINDOW *menu, WINDOW *bar, WINDOW *edit);

// Cria os painéis
PANEL *popup;
PANEL *editor;
PANEL *infobar;
PANEL *m_ajuda;

// Algumas variáveis globais
FILE *text;
char nome[30]; //Nome do arquivo, fornecido pelo usuário.
int count = 0; //Registra se é a primeira vez que um documento é aberto.
int sair = 0;

int main() {
	
	// Inicia a ncurses
	initscr();
	noecho(); //Não exibir os caractéres digitados como é feito no terminal
	cbreak(); //Permite a leitura imediata, caractére à caractére
	start_color();

	// Cria as  janelas
	WINDOW *menu;
	WINDOW *edit;
	WINDOW *bar;
	WINDOW *help;
		
	menu = newwin(14, 30, (LINES/2)-7, (COLS/2)-15); //Centralizado!
	edit = newwin(LINES-2, COLS, 0, 0);
	bar = newwin(2, COLS, LINES-2, 0);
	help = newwin(16, 30, (LINES/2)-8, (COLS/2)-15); //Maior que o menu.
		
	// Associa os painéis às suas respectivas janelas
	editor = new_panel(edit);
	infobar = new_panel(bar);
	popup = new_panel(menu);
	m_ajuda = new_panel(help);

	// Atributos de cor
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	
	wattrset(bar, COLOR_PAIR(1));
	wattrset(menu, COLOR_PAIR(1));
	wattrset(help, COLOR_PAIR(1));
	
	// Habilita teclas especiais
	keypad(stdscr, TRUE);
	keypad(menu, TRUE);

	// Refresh para plotar todas as janelas
	refresh();
	
	// Inicializa as variáveis da main e associa valores
	char ch = 27;	
	strcpy (nome, "novo_arquivo");// Colocar bordas na menu
	box(menu, 0, '\0');
	box(help, 0, '\0');	
	
	// Inicializa o menu
	mvwprintw(menu, 0, 12, "VENCI");
	mvwprintw(menu, 4, 5, "novo");
	mvwprintw(menu, 5, 5, "abrir");
	mvwprintw(menu, 6, 5, "salvar");
	mvwprintw(menu, 7, 5, "salvar como");
	mvwprintw(menu, 8, 5, "ajuda");
	mvwprintw(menu, 10, 5, "sair");
	
	wrefresh(menu);
	
	mvwprintw(help, 1, 2, "Ajuda");
	mvwprintw(help, 3, 2, "Bem vindo ao VENCI!");
	mvwprintw(help, 4, 2, "Para acessar o menu,");
	mvwprintw(help, 5, 2, "basta apertar a tecla ESC.");
	mvwprintw(help, 6, 2, "Navegue entre as opcoes");
	mvwprintw(help, 7, 2, "com as setinhas para cima");
	mvwprintw(help, 8, 2, "e para baixo. Aperte ENTER");
	mvwprintw(help, 9, 2, "quando tiver escolhido.");
	mvwprintw(help, 10, 2, "Para voltar a janela de");
	mvwprintw(help, 11, 2, "edicao, aperte ESC. Voce");
	mvwprintw(help, 12, 2, "pode navegar entre os");
	mvwprintw(help, 13, 2, "caracteres usando as setas");
	mvwprintw(help, 14, 2, "para cima, baixo e lados.");
	
	
	// Loop principal
	while (1) {
		if (ch == 27) { //ESC para exibir o menu
		
			show_menu(menu, bar, edit);
			
			if(sair == 1){
				break;
			}
			
			// Reorganização de painés, da janela e do cursor.
			hide_panel(popup);
			hide_panel(m_ajuda);
			update_panels();
			doupdate();
			
			wrefresh(edit);
			wmove(edit, 0, 0);
		}
		
		ch = getch(); //Aqui a mágica ocorre.
		
		if (ch != 27) { //Não sendo ESC, exibe o caractére e atualiza a tela
			waddch(edit, ch);
			wrefresh(edit);
		}
		
	}

	endwin();
	 
	return 0;
}

void show_menu(WINDOW *menu, WINDOW *bar, WINDOW *edit) {
	
	//Ajusta o painel
	
	hide_panel(m_ajuda);
	show_panel(popup);
	update_panels();
	doupdate();	
	
	//Inicialização
	curs_set(0);
	
	int pos = 4;
	int ch;
	mvwaddch(menu, pos, 3, '>');
	wrefresh(menu);
	
	// Movimentação do cursor e sair do menu
	while ((ch = getch())){
		mvwaddch(menu, pos, 3, ' ');
		if (ch == KEY_DOWN){
			if (pos >=4 && pos <=8){
				pos++;
				if (pos == 9) {
					pos++;
				}		
			}else if (pos == 10){
				pos = 4;
			}
		}else if (ch == KEY_UP){
			if (pos >=5 && pos <=10){
				pos--;
				if (pos == 9) {
					pos--;
				}
			}else if (pos == 4){
				pos = 10;
			}
		}else if (ch == 10){ // ENTER para escolher opção
			break;
		}else if (ch == 27){ // ESC para sair do menu sem selecionar
			return;
		}
		
		mvwaddch(menu, pos, 3, '>');
		wrefresh(menu);
		
	}
	
	werase(bar);
	wrefresh(bar);
	
	// Executa a função de acordo com a opção escolhida
	switch(pos) {		
		case 4: novo(edit, bar);
			break;
		case 5: abrir(edit, bar);
			break;	
		case 6: salvar(edit, bar);
			break;	
		case 7: salvar_como(edit, bar);
			break;	
		case 8: ajuda(menu, bar,edit);
			break;
		case 10:
			sair = 1;
			break;
	}
	wrefresh(bar);

	curs_set(1);
		
	count++; // Já acessou o menu mais de uma vez, então já acessou o arquivo.
	
	return;
}

void novo(WINDOW *edit, WINDOW *bar){
	
	char ch;
	
	//Verifica se Deseja salvar o arquivo atual antes de criar um novo;
	if (count > 0) {  //só pergunta se o arquivo já tiver sido acessado.
	
		werase(bar);
		wrefresh(bar);
		
		wprintw(bar, "Deseja salvar e sair do arquivo aberto? (S/N)");
		
		echo(); //Volta a exibir os caractéres digitados.
		curs_set(1); //Exibe o cursor piscando.
		mvwscanw(bar, 1, 0, "%c", &ch);
		curs_set(0);
		noecho();
		
		if (ch == 'S') {
			
			salvar(edit, bar);
			
		} else if (ch == 'N') {
			
		}
		
	}
	
	werase(bar);
	strcpy (nome, "novo_arquivo");
	mvwprintw(bar, 0, 0, "Arquivo %s criado.", nome);
	
	// Limpa a tela
	werase(edit);
	wrefresh(edit);
	
}

void abrir(WINDOW *edit, WINDOW *bar) {
	
	mvwprintw(bar, 0, 0, "Entre com o nome do arquivo que vai abrir:");
	wrefresh (bar);
	
	echo();	//Volta a exibir os caractéres digitados.
	curs_set(1); //Exibe o cursor piscando.
	mvwscanw(bar, 1, 0, "%s", nome);
	curs_set(0);
	noecho();
	werase(edit);
	wrefresh(edit);
	
	char ch;
	
	if ((text = fopen(nome, "r")) == NULL) {
		werase(bar);
		mvwprintw(bar, 0, 0, "Não foi possível abrir o arquivo!\nAperte ESC para voltar ao menu.");
		wrefresh(bar);
		
	} else {
		
		wclear(bar);
		//Na InfoBar, devemos informar nome do documento aberto, última
		//modificação, número de caractéres, etc... 
		mvwprintw(bar, 0, 0, "Documento %s aberto. Pressione ESC para voltar ao Menu", nome);
		
		wmove (edit, 0, 0);
		
		while ((ch = fgetc(text)) != EOF) {
					
			wprintw(edit, "%c", ch);
			
		}
		
		fclose(text);
		
	}
	
	wrefresh (bar);
	
}

void salvar(WINDOW *edit, WINDOW *bar) {
	
	werase(bar);
	mvwprintw(bar, 0,0 , "Arquivo %s salvo!", nome);
	
	wrefresh(bar);
	
	if(strcmp(nome, "novo_arquivo") == 0) {
		salvar_como (edit,bar);
	} else {
		
		text = fopen(nome, "w");
		//Rotina para salvar na memória cada ch que ele recebe. (lista);
		fclose(text);
		
	}
	
}
	
void salvar_como(WINDOW *edit, WINDOW *bar){
	
	char n[30];
	int i = -1;
	mvwprintw(bar, 0, 0, "Entre com o nome do novo arquivo");
	wrefresh (bar);
	echo();//Volta a exibir os caractéres digitados.
	curs_set(1); //Exibe o cursor piscando.	
	
	wmove(bar, 4, 0);
	
	while((n[++i] = getch()) !=  '\n'){
		if(n[i] == 27){
			return;
		}
	}
	n[i] = '\0';
	strcpy(nome, n);
	curs_set(0);
	noecho();
	
	wclear(bar);
	salvar(edit,bar);

}

void ajuda(WINDOW *menu, WINDOW *bar, WINDOW *edit) {
	
	// Organiza a barra
	mvwprintw(bar, 1, 0, "Pressione qualquer tecla para voltar ao editor, ou ESC para voltar ao menu.");
	
	// Exibe a ajuda
	show_panel(m_ajuda);
	update_panels();
	doupdate();	
	
	//getch();
	if (getch() == 27){ // ESC para voltar ao menu sem passar pela edit
	
		werase(bar);
		wrefresh(bar);
		
		show_menu(menu, bar, edit);
	}else{			
		werase(bar);
		wrefresh(bar);
	}
	
	hide_panel(m_ajuda);
	update_panels();
	doupdate();
	
}
