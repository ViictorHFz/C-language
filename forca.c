#include <stdio.h>
#include <string.h>
#include "forca.h"
#include <time.h>
#include <stdlib.h>

	
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

void adicionapalavra() {

	char quer;

	printf("Você quer adicionar uma nova palavra no jogo? (S/N)\n");
	scanf(" %c", &quer);

	if(quer == 'S') {

		char novaplavra[20];
		printf("Qual a nova palavra? \n");
		scanf("%s", novaplavra);


		FILE* f;

		f = fopen("palavras.txt", "r+");

		if(f == 0) {
			printf("Desculpa, não foi possível acessar o banco de palavras secretas!\n");
		}

		//Ler a quantidade de palavras do arquivo e adiciona mais 1
		int qtd;
		fscanf(f, "%d", &qtd);
		qtd++;

		/*fseek posiciona o ponteiro
				
			fseek(aquivo, x, y)

			x = número de bytes que o ponteiro deve "andar"
			y = constante que indica de onde o ponteiro vai começar a andar

			SEEK_SET indica que ponteiro deve começar a "andar" do começo do aquivo
			SEEK END indica que deve começar do final do aquivo
		
		*/

		fseek(f, 0, SEEK_SET);
		fprintf(f, "%d", qtd);

		fseek(f, 0, SEEK_END);
		fprintf(f, "\n%s", novaplavra);

		fclose(f);
	}
}

void escolhepalavra() {
	FILE* f;

	f = fopen("palavras.txt", "r");

	if(f == 0) {
		printf("Desculpa, não foi possível acessar o banco de palavras secretas!\n");
		exit(1);
	}

	int qtddepalavras;
	fscanf(f, "%d", &qtddepalavras);

	//gera numero aleatório
	srand(time(0));
	int randomico = rand() % qtddepalavras;

	//ler do arquivo palavras.txt até chegar na linha desejada/sorteada
	for (int i = 0; i < randomico; ++i) {
		fscanf(f, "%s", palavrasecreta);
	}

	fclose(f);
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

	adicionapalavra();
}