/*
 * Written by:
 * Guilherme Reginaldo Ruella <potentii@gmail.com>
 */
#include <stdio.h>
#include <stdlib.h>
#include "conio.c"


int TicTacToe[3][3];		   // *Matriz global que armazena os 'X' e 'O'
int placar[3] = {0,0,0};   // *Quantidade de vezes que 'X' ou 'O' venceu, ou que deu velha

// *Protótipos das funções:
void wrtMsg(char mensagem[], int context);
void limpaTela(int xIn, int yIn, int xFin, int yFin);
void mostra_jogo(void);
void inicia_jogo(void);
void desenhaBorda(int x, int y, int show);
void printWinner(int referencial, int tipo);
void whoWins(int turno);
void theGame(void);
void buildBorder(void);
void buildScoreboard(void);
void buildMenu(void);
void WASDMenu(void);


/*
 *
 *	Função main (apenas controla o fluxo inicial do programa).
 *
 */
int main(void){
	buildBorder();
	buildMenu();
}


/*
 *
 *	Função que escreve no "OUTPUT" do programa.
 *	* mensagem: A mensagem que devera ser escrita logo após de ">> OUTPUT:".
 *	* context: Indica qual contexto está ( 1:Partida | 2:Nenhum | 3:Menu principal | 4:Scoreboard ).
 *
 */
void wrtMsg(char mensagem[], int context){
	// *Apaga oque estiver escrito antes:
	gotoxy(15,24);
	clreol();
	gotoxy(80,24);
	printf("%c", 179);
	gotoxy(60,24);
    printf("%c", 179);
	gotoxy(78,24);
    printf("%c", 179);
	gotoxy(79,24);
    printf("%c", 178);

	// *Escreve a mensagem:
	gotoxy(15,24);
	printf("%s", mensagem);

	// *Verifica "context":
	switch(context){
	case 1:
		gotoxy(61,24);
    	printf("Tic Tac Toe");
		break;
	case 2:
		gotoxy(61,24);
    	printf("");
		break;
	case 3:
		gotoxy(61,24);
    	printf("Menu Principal");
		break;
	case 4:
		gotoxy(61,24);
    	printf("Scoreboard");
		break;
	}
}


/*
 *
 *	Função que limpa uma determinada area da tela.
 *	* xIn e yIn: Formam a coordenada inicial da area de limpeza.
 *	* xFin e yFin: Formam a coordenada final da area de limpeza.
 *
 */
void limpaTela(int xIn, int yIn, int xFin, int yFin){
	int i, j;

	// *Verificando se as coords são validas:
	xIn = (xIn>80) ? 80:xIn;
	xIn = (xIn<1) ? 1:xIn;
	xFin = (xFin>80) ? 80:xFin;
	xFin = (xFin<1) ? 1:xFin;

	yIn = (yIn>25) ? 25:yIn;
	yIn = (yIn<1) ? 1:yIn;
	yFin = (yFin>25) ? 25:yFin;
	yFin = (yFin<1) ? 1:yFin;

	// *Executando a limpeza:
	if(!((xFin<xIn) || (yFin<yIn))){
		for(i=yIn; i<=yFin; i++){
			for(j=xIn; j<=xFin; j++){
				gotoxy(j, i);
				printf(" ");
			}
		}
	}

	// *Depois da limpeza, volta para a posição original do cursor:
	gotoxy(xIn, yIn);
}


/*
 *
 *	Função que imprime o tabuleiro na tela.
 *
 */
void mostra_jogo(void){
	int i;

	limpaTela(24, 10, 77, 14);

	// *Linhas horizontais:
	for(i=34; i<45; i++){
		gotoxy(i, 6);
		printf("%c", 196);
		gotoxy(i, 10);
		printf("%c", 196);
		gotoxy(i, 14);
		printf("%c", 196);
		gotoxy(i, 18);
		printf("%c", 196);
	}

	// *Linhas verticais:
	for(i=7; i<18; i++){
		gotoxy(33, i);
		printf("%c", 179);
		gotoxy(37, i);
		printf("%c", 179);
		gotoxy(41, i);
		printf("%c", 179);
		gotoxy(45, i);
		printf("%c", 179);
	}

	// *Complementos:
	gotoxy(33, 6);
	printf("%c", 218);
	gotoxy(37, 6);
	printf("%c", 194);
	gotoxy(41, 6);
	printf("%c", 194);
	gotoxy(45, 6);
	printf("%c", 191);

	gotoxy(33, 10);
	printf("%c", 195);
	gotoxy(37, 10);
	printf("%c", 197);
	gotoxy(41, 10);
	printf("%c", 197);
	gotoxy(45, 10);
	printf("%c", 180);

	gotoxy(33, 14);
	printf("%c", 195);
	gotoxy(37, 14);
	printf("%c", 197);
	gotoxy(41, 14);
	printf("%c", 197);
	gotoxy(45, 14);
	printf("%c", 180);

	gotoxy(33, 18);
	printf("%c", 192);
	gotoxy(37, 18);
	printf("%c", 193);
	gotoxy(41, 18);
	printf("%c", 193);
	gotoxy(45, 18);
	printf("%c", 217);

	// *Centraliza o cursor na célula do meio:
	gotoxy(39, 12);
}


/*
 *
 *	Função que prepara a matriz "TicTacToe" para um novo jogo
 *	e depois chama a função para imprimir o tabuleiro.
 *
 */
void inicia_jogo(void){
	int i, j;

	// *Zera a matriz:
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			TicTacToe[i][j] = 2;
		}
	}

	// *Monta o tabuleiro:
	mostra_jogo();

	// *Inicia o jogo:
	theGame();
}


/*
 *
 *	Função que imprime uma borda na célula selecionada.
 *	* x, y: Informam a coordenada do centro da celula.
 *	* show: Booleana que diz: ( 0:Apagar borda | 1:Desenhar borda ).
 *
 */
void desenhaBorda(int x, int y, int show){
	if(show){
		gotoxy(x-1, y+1);
		printf("%c", 192);
		gotoxy(x-1, y);
		printf("%c", 179);
		gotoxy(x-1, y-1);
		printf("%c", 218);
		gotoxy(x, y-1);
		printf("%c", 196);

		gotoxy(x+1, y-1);
		printf("%c", 191);
		gotoxy(x+1, y);
		printf("%c", 179);
		gotoxy(x+1, y+1);
		printf("%c", 217);
		gotoxy(x, y+1);
		printf("%c", 196);
	} else{
		gotoxy(x-1, y+1);
		printf(" ");
		gotoxy(x-1, y);
		printf(" ");
		gotoxy(x-1, y-1);
		printf(" ");
		gotoxy(x, y-1);
		printf(" ");

		gotoxy(x+1, y-1);
		printf(" ");
		gotoxy(x+1, y);
		printf(" ");
		gotoxy(x+1, y+1);
		printf(" ");
		gotoxy(x, y+1);
		printf(" ");
	}
	gotoxy(x, y);
	return;
}


/*
 *
 *	Função que realça onde que ocorreu a vitoria.
 *	* referencial: a posição referencial da linha, coluna ou diagonal que ocorreu a vitoria.
 *	* tipo: tipo da vitoria ( 0:Horizontal | 1:Vertical | 2:Diagonal ).
 *
 */
void printWinner(int referencial, int tipo){
	int i;
	int sair;

	for(i=0; i<4; i++){
		sleep(600);		      // *MinGW
		//usleep(600000);		// *TDM
		// *Limpa as bordas:
		desenhaBorda(35, 8, 0);
		desenhaBorda(39, 8, 0);
		desenhaBorda(43, 8, 0);
		desenhaBorda(35, 12, 0);
		desenhaBorda(39, 12, 0);
		desenhaBorda(43, 12, 0);
		desenhaBorda(35, 16, 0);
		desenhaBorda(39, 16, 0);
		desenhaBorda(43, 16, 0);
		gotoxy(1,1);
		sleep(600);		      // *MinGW
		//usleep(600000);		// *TDM
		if(tipo==0){									// *Se for horizontal, faz as bordas nas celulas da linha referencial.
			desenhaBorda(35, referencial, 1);
			desenhaBorda(39, referencial, 1);
			desenhaBorda(43, referencial, 1);
		} else if(tipo==1){								// *Se for vertical, faz as bordas nas celulas da coluna referencial.
			desenhaBorda(referencial, 8, 1);
			desenhaBorda(referencial, 12, 1);
			desenhaBorda(referencial, 16, 1);
		} else if((tipo==2) && (referencial==35)){		// *Se for diagonal e na diagonal principal.
			desenhaBorda(35, 8, 1);
			desenhaBorda(39, 12, 1);
			desenhaBorda(43, 16, 1);
		} else if((tipo==2) && (referencial==43)){		// *Se for diagonal e na diagonal secundaria.
			desenhaBorda(43, 8, 1);
			desenhaBorda(39, 12, 1);
			desenhaBorda(35, 16, 1);
		}
	}

	// *Enquanto não apertar o ENTER ele não faz nada:
	do{
		wrtMsg("Pessione [ENTER] para voltar ao Menu.", 1);
	} while(getch() != 13);
	main();
}


/*
 *
 *	Função que faz um desvio de fluxo se alguém ganhar a rodada ou se der velha.
 *	* turno: Diz em qual turno da partida estamos.
 *
 */
void whoWins(int turno){
	int i, j;			// *Contadores, o "i" também vai servir para informar o referencial da função "printWinner()"
	int type;			// *Tipo da vitoria: ( 0:Horizontal | 1:Vertical | 2:Diagonal )
	int x = 0;			// *Contador para vitoria de 'X'
	int o = 0;			// *Contador para vitoria de 'O'
	int winner = 2;	// *winner: ( 0:Bola venceu | winner=1:Xis venceu | winner=2:Deu velha )

	// *verifica horizontalmente:
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			if(TicTacToe[i][j]==0){
				o++;
				winner = (o==3) ? 0:winner;
			}

			if(TicTacToe[i][j]==1){
				x++;
				winner = (x==3) ? 1:winner;
			}
		}
		if(winner!=2){
			type = 0;
			i = (i==0) ? 8:i;
			i = (i==1) ? 12:i;
			i = (i==2) ? 16:i;
			break;
		}
		x=0;
		o=0;
	}

	// *Se ainda estiver velha, verifique verticalmente:
	if(winner == 2){
		// *verifica verticalmente:
		for(i=0; i<3; i++){
			for(j=0; j<3; j++){
				if(TicTacToe[j][i]==0){
					o++;
					winner = (o==3) ? 0:winner;
				}

				if(TicTacToe[j][i]==1){
					x++;
					winner = (x==3) ? 1:winner;
				}
			}
			if(winner!=2){
				type = 1;
				i = (i==0) ? 35:i;
				i = (i==1) ? 39:i;
				i = (i==2) ? 43:i;
				break;
			}
			x=0;
			o=0;
		}
	}

	// *Diagonais:
	if(winner == 2){
		if((TicTacToe[0][0]==1) && (TicTacToe[1][1]==1) && (TicTacToe[2][2]==1)){			// *Se na diagonal principal 'X' ganhar
			winner = 1;		// *'X' venceu
			type = 2;		// *Tipo diagonal
			i = 35;			// *Abscissa na tela do inicio da diagonal principal
		} else if((TicTacToe[0][2]==1) && (TicTacToe[1][1]==1) && (TicTacToe[2][0]==1)){	// *Se na diagonal secundaria 'X' ganhar
			winner = 1;		// *'X' venceu
			type = 2;		// *Tipo diagonal
			i = 43;			// *Abscissa na tela do inicio da diagonal secundaria
		} else if((TicTacToe[0][0]==0) && (TicTacToe[1][1]==0) && (TicTacToe[2][2]==0)){	// *Se na diagonal principal 'O' ganhar
			winner = 0;		// *'O' venceu
			type = 2;		// *Tipo diagonal
			i = 35;			// *Abscissa na tela do inicio da diagonal principal
		} else if((TicTacToe[0][2]==0) && (TicTacToe[1][1]==0) && (TicTacToe[2][0]==0)){	// *Se na diagonal secundaria 'O' ganhar
			winner = 0;		// *'O' venceu
			type = 2;		// *Tipo diagonal
			i = 43;			// *Abscissa na tela do inicio da diagonal secundaria
		}
	}

	if((winner==2) && (turno==9)){			// *Se ninguém venceu na ultima rodada, deu velha
		wrtMsg("Deu velha, ninguem ganhou.", 1);
		placar[2]++;
		getch();
		do{
			wrtMsg("Pressione [ENTER] para voltar ao Menu.", 1);
		} while(getch() != 13);
		main();
	} else if(winner==1){					// *Se 'X' venceu
		wrtMsg("Xis venceu, parabens !!!", 1);
		placar[1]++;
		printWinner(i, type);
		getch();
	} else if(winner==0){					// *Se 'O' venceu
		wrtMsg("Bola venceu, parabens !!!", 1);
		placar[0]++;
		printWinner(i, type);
		getch();
	}
}


/*
 *
 *	Função principal do programa, ela quem executa as operações na partida.
 *
 */
void theGame(void){
	int x = 39;		// *Abscissa X
	int y = 12;		// *Ordenada Y
	int vez = 1;	// *De quem é a vez ( 0:O | 1:X )
	char carac;		// *Caractere digitado no teclado
	int c = 1;		// *Abscissa c na matriz
	int l = 1;		// *Ordenada l na matriz
	int turns = 0;	// *Contador de turnos

	// *Construindo a borda da célula inicial:
	desenhaBorda(x, y, 1);
	while(1){
		if(vez){
			wrtMsg("Vez de 'X'", 1);
		} else{
			wrtMsg("Vez de 'O'", 1);
		}

		// *Capturando tecla digitada:
		carac = getch();

		gotoxy(x, y);

		// *Verifica se a célula selecionada não contém um valor:
		if(TicTacToe[l][c]==2){

			// *Vê se é a vez de 'X' ou de 'O':
			if(vez){
				if((carac=='x') || (carac=='X')){	// *Se 'X' for pressionado na vez dele:
					printf("X");
					TicTacToe[l][c] = 1;
					turns++;
					whoWins(turns);
					vez=0;
				}
			} else{
				if((carac=='o') || (carac=='O')){	// *Se 'O' for pressionado na vez dele:
					printf("O");
					TicTacToe[l][c] = 0;
					turns++;
					whoWins(turns);
					vez=1;
				}
			}
		}

		// *Tirando a borda da célula selecionada:
		desenhaBorda(x, y, 0);

		// *WASD:
		// *w ou W
        if(((carac=='w') || (carac=='W')) && y>8){
            y -= 4;
			l -= 1;
        }
		// *a ou A
		if(((carac=='a') || (carac=='A')) && x>35){
            x -= 4;
			c -= 1;
        }
		// *s ou S
		if(((carac=='s') || (carac=='S')) && y<16){
            y += 4;
			l += 1;
        }
        // *d ou D
		if(((carac=='d') || (carac=='D')) && x<43){
            x += 4;
			c += 1;
        }

		// *Construindo a borda da célula selecionada:
		desenhaBorda(x, y, 1);
	}
}


/*
 *
 *	Função que imprime a 'janela' em que o jogo está.
 *
 */
void buildBorder(void){
	int i;

	// *Horizontal:
	for(i=1; i<81; i++){
		gotoxy(i, 1);
		printf("%c", 196);
		gotoxy(i, 3);
		printf("%c", 196);
		gotoxy(i, 23);
		printf("%c", 196);
		gotoxy(i, 25);
		printf("%c", 196);
	}

	// *Vertical:
	for(i=1; i<26; i++){
		gotoxy(1, i);
		printf("%c", 179);
		gotoxy(3, i);
		printf("%c", 179);
		gotoxy(78, i);
		printf("%c", 179);
		gotoxy(80, i);
		printf("%c", 179);
	}

	// *Cantos:
	gotoxy(1, 1);
	printf("%c", 218);
	gotoxy(3, 1);
	printf("%c", 194);
	gotoxy(78, 1);
	printf("%c", 194);
	gotoxy(80, 1);
	printf("%c", 191);

	gotoxy(1, 3);
	printf("%c", 195);
	gotoxy(3, 3);
	printf("%c", 197);
	gotoxy(78, 3);
	printf("%c", 197);
	gotoxy(80, 3);
	printf("%c", 180);

	gotoxy(1, 23);
	printf("%c", 195);
	gotoxy(3, 23);
	printf("%c", 197);
	gotoxy(78, 23);
	printf("%c", 197);
	gotoxy(80, 23);
	printf("%c", 180);

	gotoxy(1, 25);
	printf("%c", 192);
	gotoxy(3, 25);
	printf("%c", 193);
	gotoxy(78, 25);
	printf("%c", 193);
	gotoxy(80, 25);
	printf("%c", 217);

	gotoxy(2, 2);
	printf("%c", 178);
	gotoxy(79, 2);
	printf("%c", 178);
	gotoxy(2, 24);
	printf("%c", 178);
	gotoxy(79, 24);
	printf("%c", 178);

	gotoxy(60,24);
    printf("%c", 179);
	gotoxy(60,23);
    printf("%c", 194);
	gotoxy(60,25);
    printf("%c", 193);

	gotoxy(30, 2);
	printf("*** Tic Tac Toe ***");
	gotoxy(4, 24);
	printf(")) OUTPUT:");
	gotoxy(1, 1);

}


/*
 *
 *	Função que imprime o Scoreboard na tela.
 *
 */
void buildScoreboard(void){
	int i;

	limpaTela(24, 10, 45, 16);

	for(i=29; i<51; i++){
		gotoxy(i, 8);
		printf("%c", 196);
		gotoxy(i, 16);
		printf("%c", 196);
	}

	for(i=9; i<16; i++){
		gotoxy(28, i);
		printf("%c", 179);
		gotoxy(51, i);
		printf("%c", 179);
	}

	gotoxy(28, 8);
	printf("%c", 218);
	gotoxy(51, 8);
	printf("%c", 191);
	gotoxy(28, 16);
	printf("%c", 192);
	gotoxy(51, 16);
	printf("%c", 217);

	gotoxy(31, 9);
	printf("*** Scoreboard ***");
	gotoxy(34, 12);
	printf("X wins  %c  %d", 26, placar[1]);
	gotoxy(34, 13);
	printf("O wins  %c  %d", 26, placar[0]);
	gotoxy(34, 14);
	printf("Velha   %c  %d", 26, placar[2]);

	fflush(stdin);
	do{
		wrtMsg("Pessione [ENTER] para voltar ao Menu.", 4);
	} while(getch() != 13);
	main();
}


/*
 *
 *	Função que imprime o menu principal na tela.
 *
 */
void buildMenu(void){
	limpaTela(27, 6, 55, 18);

	gotoxy(30, 10);
	printf("Start a New Game");
	gotoxy(30, 12);
	printf("Scoreboard");
	gotoxy(30, 14);
	printf("Quit Game");

	WASDMenu();
}


/*
 *
 *	Função que seleciona os itens do menu com a WASD.
 *
 */
void WASDMenu(void){
	int carac;
	int x = 28;
	int y = 10;

	wrtMsg("Escolha uma opcao.  [W] Cima  [S] Baixo.", 3);
	gotoxy(x, y);
	printf("%c", 26);
	gotoxy(1, 1);

	while(1){

		carac = getch();

		gotoxy(x, y);
		printf(" ", 26);
		// *WASD:
		// *w ou W
	    if(((carac==119) || (carac==87)) && y>10){
	        y -= 2;
	    }

		// *s ou S
		if(((carac==115) || (carac==83)) && y<14){
	        y += 2;
		}

		// *Enter
		if(carac==13){
			switch(y){
			case 10:
				inicia_jogo();
				break;
			case 12:
				buildScoreboard();
				break;
			case 14:
				exit(0);
				break;
			}
		}
		gotoxy(x, y);
		printf("%c", 26);
		gotoxy(1, 1);
	}
}
