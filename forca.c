#include <stdio.h>
#include <string.h>
#include "forca.h"

	
//Variáveis GLOBAIS
char palavrasecreta[20]; 
char chutes[26];
int chutesdados = 0;
	

void abertura(){
    printf(" ************************************************************************   \n");
    printf(" -+                         Bem vindo ao                               +- \n\n");
    printf("      | |                       | |       |_____|                           \n");
    printf("      | | ___   __ _  ___     __| | __ _  | |__ ___  _ __ ___ __ _          \n");
    printf("  _   | |/ _ \\ / _` |/ _ \\   / _` |/ _` | |  __/ _ \\| '__/ __/ _` |      \n");
    printf(" | |__| | (_) | (_| | (_) | | (_| | (_| | | | | (_) | | | (_| (_| |         \n");
    printf("  \\____/ \\___/ \\__, |\\___/   \\__,_|\\__,_| |_|  \\___/|_|  \\___\\__,_|\n");
    printf("                __/ |                                                       \n");
    printf("               |___/                                                        \n\n");
    printf(" -+                Descobre qual a palavra secreta!                    +-   \n");
    printf(" ************************************************************************   \n");
}

void chuta() {
    char chute;
    printf("Qual letra? ");
    scanf(" %c", &chute);

    chutes[chutesdados] = chute;
    chutesdados++;
}

int jachutou(char letra) {
	int achou = 0;

	for (int j = 0; j < chutesdados; j++) {
		if(chutes[j] == letra) {
			achou = 1;
			break;
		}
	}

	return achou;
}

int acertou() {
	for (int i = 0; i < strlen(palavrasecreta); ++i) {
		
		if(!jachutou(palavrasecreta[i])) {
			return 0;
		}
	}

	return 1;
}

void desenhaforca() {

	for (int i = 0; i < strlen(palavrasecreta); i++) {

		int achou = jachutou(palavrasecreta[i]);

		if(achou){
			printf("%c ", palavrasecreta[i]);
		} else {
			printf("_ ");
		}
	}

	printf("\n");
}

void escolhepalavra() {
	sprintf(palavrasecreta, "MELANCIA");
}

int enforcou() {

	int erros = 0;

	// loop que verifica os chutes dados
	for (int i = 0; i < chutesdados; i++) {
		
		int existe = 0;

		//Verifica letra a letra da palavra secreta e ver se encontra o chute aqui
		for (int j = 0; j < strlen(palavrasecreta); j++) {

			if(chutes[i] == palavrasecreta[j]) {
				//encontramos o chute
				existe = 1;
				break;
			}
		}

		// se nao encontrou, soma um na quantidade de erros
		if(!existe) erros++;

		/*
		if(!existe) {
			erros++;
		}*/

	}

	// se tivermos mais do que 5 erros, retornamos 1
    // caso contrario, retornamos 0.
	return erros >= 5;
}

int main() {

	escolhepalavra();
	abertura();

	do {

		printf("Você já deu %d chutes\n", chutesdados);

		desenhaforca();
		chuta();

	} while(!acertou() && !enforcou());
}