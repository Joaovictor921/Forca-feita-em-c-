#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <iostream>

//Feito por João Victor Dalbem e Guilherme Duque
//Forca feito em c++



// maximo de tentativa e tamanho maximo da palavra
#define MAX_TENTATIVAS 8
#define TAMANHO_PALAVRA 100

void limpaTela() {
     //Comando para limpar a tela (Windows ou Linux/Mac)
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

	typedef struct{
		char nome[50];
		int pontos;
	}jogador;
	

void TROCA(jogador *x, jogador *y);
void classifica();


int main() {
	setlocale(LC_ALL,"Portuguese");
    //Lista de palavras possíveis
    int pontosp2p[3];
    int pessoas;
    int maiorP = 0;
	int menorP = 0;
	int mediaP = 0;
	
	

	jogador player[3],*p1,*p2,*p3,troca;
	for(int i; i <=2; i++)
		player[i].pontos = 0;
    
    
    printf("------Deseja jogar contra  quantas pessoas?------\n"); //quantidade de jogadores
    printf("-------------------Max:3-------------------------\n");
    scanf("%d", &pessoas);
    fflush(stdin);
    if(pessoas < 1 || pessoas > 3 ){
    	printf("quantidades de pessoas errada\n");
    	printf("Digite novamente\n");
    	scanf("%d", &pessoas);
    	fflush(stdin);
    	limpaTela();
	}
	
	printf("Digite o primeiro nome: ");
    fgets(player[0].nome, sizeof(player[0].nome) , stdin);
    fflush(stdin);
    
    printf("\n");
    if(pessoas >= 2){
    	printf("Digite o segundo nome: ");
    	fgets(player[1].nome, sizeof(player[1].nome), stdin);
		fflush(stdin);
	}
	printf("\n");
	if(pessoas == 3){
    	printf("Digite o terceiro nome: ");
    	fgets(player[2].nome,sizeof(player[2].nome), stdin);
    	fflush(stdin);
    
    	printf("\n");
    
    	system("pause");
	}
	
   if(pessoas == 3){
		for(int a = 0;a<3;a++){
		    const char *listaPalavras[] = {
		        "computador",
		        "programacao",
		        "linguagem",
		        "teclado",
		        "monitor",
		        "internet",
		        "jogo",
		        "variavel",
		        "ponteiro",
		        "memoria",
		        "palavra",
		        "injogavel",
		        "cs2",
		        "vitorgay",
		        "minhoca",
		        "nome",
		        "duque",
		        "bola",
		        "cubo",
		        "naruto",
		        "goku",
		    	"nariz",
		        "legal",
		        "lapis",
		        "visualg",
		        "python",
		    	"elefante",
				"girafa",
				"canguru",
				"tubarão",
				"arara",
				"leao",
				"coruja",
				"camaleao",
				"abacaxi",
				"morango",
				"laranja",
				"uva",
				"banana",
				"manga",
				"kiwi",
				"melancia",
				"brasil",
				"canada",
				"japao",
				"frança",
				"india",
				"egito",
				"italia",
				"mexico",
				"medico",
				"professor",
				"engenheiro",
				"advogado",
				"enfermeiro",
				"arquiteto",
				"jornalista",
				"cozinheiro",
				"vermelho",
				"azul",
				"amarelo",
				"verde",
				"roxo",
				"laranja",
				"preto",
				"branco"
		    };
		    
		
		    int totalPalavras = sizeof(listaPalavras) / sizeof(listaPalavras[0]);
		
		    //Inicializa o gerador de números aleatórios
		    srand(time(NULL));
		    int indice = rand() % totalPalavras;
		
		    char palavraSecreta[TAMANHO_PALAVRA];
		    strcpy(palavraSecreta, listaPalavras[indice]);
		
		    char palavraOculta[TAMANHO_PALAVRA];
		    int tamanho = strlen(palavraSecreta);
		    int tentativas = 0;
		    int letrasAcertadas = 0;
		    int letrasEncontradas[TAMANHO_PALAVRA] = {0};
		    int j = 0;
		    char chute;
		    char letra[20];
		    int pontos = 0;
		    int continuar = 0;
		    
		    
		
		    //Inicializa a palavra oculta com "_"
		    for (int i = 0; i < tamanho; i++) {
		        palavraOculta[i] = '_';
		    }
		    palavraOculta[tamanho] = '\0';
		
		    //Loop principal do jogo
		    while (tentativas < MAX_TENTATIVAS && letrasAcertadas < tamanho) {
		        limpaTela();
		        printf("=== Jogo da Forca ===\n\n");
		        printf("Palavra: ");
		        for (int i = 0; i < tamanho; i++) {
		            printf("%c ", palavraOculta[i]);
		        }
		        printf("\n\nAs letras ja colocadas são: ");
		    	for(int i = 0; i <= j - 1; i++){
		    		printf("%c ", letra[i]);
				}
		        printf("\nTentativas restantes: %d\n", MAX_TENTATIVAS - tentativas);
		        printf("Digite uma letra: ");
		        scanf(" %c", &chute);
		        chute = tolower(chute);
		        letra[j] = chute;
		        j++;
		    	for(int i = 0; i <= j - 1; i++){
				}
		        
		        int acertou = 0;
		        for (int i = 0; i < tamanho; i++) {
		            if (palavraSecreta[i] == chute && letrasEncontradas[i] == 0) {
		                palavraOculta[i] = chute;
		                letrasEncontradas[i] = 1;
		                letrasAcertadas++;
		                acertou = 1;
		            }
		        }
		        
		        if (!acertou) {
		            tentativas++;
		            player[a].pontos -= 1;
		            printf("Letra incorreta!\n");
		        } else {
		        	player[a].pontos += 3;
		            printf("Boa! Letra correta!\n");
		        }
		        
		        
		        
		        printf("Pressione Enter para continuar...");
		        getchar(); // consome o '\n' anterior
		        getchar(); // espera o Enter
			}
			pontosp2p[a] = player[a].pontos;
		        

		    printf("A palavra era: %s\n", palavraSecreta);
		    system("pause");
		    
		    
		    
		}
		printf("O jogador %s teve: %d pontos\n", player[0].nome, player[0].pontos);
		printf("O jogador %s teve: %d pontos\n", player[1].nome, player[1].pontos);
		printf("O jogador %s teve: %d pontos\n", player[2].nome, player[2].pontos);
	}
	
	if(pessoas == 2){
		for(int a = 0;a<2;a++){
		    const char *listaPalavras[] = {
		        "computador",
		        "programacao",
		        "linguagem",
		        "teclado",
		        "monitor",
		        "internet",
		        "jogo",
		        "variavel",
		        "ponteiro",
		        "memoria",
		        "palavra",
		        "injogavel",
		        "cs2",
		        "vitorgay",
		        "minhoca",
		        "nome",
		        "duque",
		        "bola",
		        "cubo",
		        "naruto",
		        "goku",
		    	"nariz",
		        "legal",
		        "lapis",
		        "visualg",
		        "python",
		    	"elefante",
				"girafa",
				"canguru",
				"tubarão",
				"arara",
				"leão",
				"coruja",
				"camaleao",
				"abacaxi",
				"morango",
				"laranja",
				"uva",
				"banana",
				"manga",
				"kiwi",
				"melancia",
				"brasil",
				"canadá",
				"japão",
				"frança",
				"india",
				"egito",
				"itália",
				"méxico",
				"médico",
				"professor",
				"engenheiro",
				"advogado",
				"enfermeiro",
				"arquiteto",
				"jornalista",
				"cozinheiro",
				"vermelho",
				"azul",
				"amarelo",
				"verde",
				"roxo",
				"laranja",
				"preto",
				"branco"
		    };
		    
		
		    int totalPalavras = sizeof(listaPalavras) / sizeof(listaPalavras[0]);
		
		    //Inicializa o gerador de números aleatórios
		    srand(time(NULL));
		    int indice = rand() % totalPalavras;
		
		    char palavraSecreta[TAMANHO_PALAVRA];
		    strcpy(palavraSecreta, listaPalavras[indice]);
		
		    char palavraOculta[TAMANHO_PALAVRA];
		    int tamanho = strlen(palavraSecreta);
		    int tentativas = 0;
		    int letrasAcertadas = 0;
		    int letrasEncontradas[TAMANHO_PALAVRA] = {0};
		    int j = 0;
		    char chute;
		    char letra[20];
		    int pontos = 2;
		    int continuar = 0;
		    int maiorP = 0;
		    int menorP = 0;
		    
		
		    //Inicializa a palavra oculta com "_"
		    for (int i = 0; i < tamanho; i++) {
		        palavraOculta[i] = '_';
		    }
		    palavraOculta[tamanho] = '\0';
		
		    //Loop principal do jogo
		    while (tentativas < MAX_TENTATIVAS && letrasAcertadas < tamanho) {
		        limpaTela();
		        printf("=== Jogo da Forca ===\n\n");
		        printf("Palavra: ");
		        for (int i = 0; i < tamanho; i++) {
		            printf("%c ", palavraOculta[i]);
		        }
		        printf("\n\nAs letras ja colocadas são: ");
		    	for(int i = 0; i <= j - 1; i++){
		    		printf("%c ", letra[i]);
				}
		        printf("\nTentativas restantes: %d\n", MAX_TENTATIVAS - tentativas);
		        printf("Digite uma letra: ");
		        scanf(" %c", &chute);
		        chute = tolower(chute);
		        letra[j] = chute;
		        j++;
		    	for(int i = 0; i <= j - 1; i++){
				}
		        
		        int acertou = 0;
		        for (int i = 0; i < tamanho; i++) {
		            if (palavraSecreta[i] == chute && letrasEncontradas[i] == 0) {
		                palavraOculta[i] = chute;
		                letrasEncontradas[i] = 1;
		                letrasAcertadas++;
		                acertou = 1;
		            }
		        }
		        
		        if (!acertou) {
		            tentativas++;
		            pontos = pontos-1;
		            printf("Letra incorreta!\n");
		        } else {
		        	pontos = pontos+3;
		            printf("Boa! Letra correta!\n");
		        }
		        
		        printf("Pressione Enter para continuar...");
		        getchar(); // consome o '\n' anterior
		        getchar(); // espera o Enter
			}
			pontosp2p[a] = pontos;
		        
		        if(pontosp2p[a] < pontosp2p[menorP]){
		        	menorP = a;
				} else if (pontosp2p[a] > pontosp2p[maiorP]){
					maiorP = a;
				}
			
			
			
		
		    if (letrasAcertadas == tamanho){
		        printf("Parabens! Voce venceu!\n");
		    }	else {
		        	printf("Voce perdeu! :( \n");
		    	}
		
		    printf("A palavra era: %s\n", palavraSecreta);
		   	system("pause");
		   
		}
		printf("O primeiro lugar é: %c %d pontos\n", pontosp2p[maiorP]);
		printf("Em segundo lugar teve: %d pontos\n",pontosp2p[menorP]);
	}
	if(pessoas == 1){
		const char *listaPalavras[] = {
		    "computador",
		    "programacao",
		    "linguagem",
		    "teclado",
		    "monitor",
		    "internet",
		    "jogo",
		    "variavel",
		    "ponteiro",
		    "memoria",
		    "palavra",
		    "injogavel",
		    "cs2",
		    "vitorgay",
		    "minhoca",
		    "nome",
		    "duque",
		    "bola",
		    "cubo",
		    "naruto",
		    "goku",
		    "nariz",
		    "legal",
		    "lapis",
		    "visualg",
		    "python",
		    "elefante",
			"girafa",
			"canguru",
			"tubarão",
			"arara",
			"leão",
			"coruja",
			"camaleao",
			"abacaxi",
			"morango",
			"laranja",
			"uva",
			"banana",
			"manga",
			"kiwi",
			"melancia",
			"brasil",
			"canadá",
			"japão",
			"frança",
			"india",
			"egito",
			"itália",
			"méxico",
			"médico",
			"professor",
			"engenheiro",
			"advogado",
			"enfermeiro",
			"arquiteto",
			"jornalista",
			"cozinheiro",
			"vermelho",
			"azul",
			"amarelo",
			"verde",
			"roxo",
			"laranja",
			"preto",
			"branco"
        };
		    
		
		    int totalPalavras = sizeof(listaPalavras) / sizeof(listaPalavras[0]);
		
		    //Inicializa o gerador de números aleatórios
		    srand(time(NULL));
		    int indice = rand() % totalPalavras;
		
		    char palavraSecreta[TAMANHO_PALAVRA];
		    strcpy(palavraSecreta, listaPalavras[indice]);
		
		    char palavraOculta[TAMANHO_PALAVRA];
		    int tamanho = strlen(palavraSecreta);
		    int tentativas = 0;
		    int letrasAcertadas = 0;
		    int letrasEncontradas[TAMANHO_PALAVRA] = {0};
		    int j = 0;
		    char chute;
		    char letra[20];
		    int pontos = 2;
		    int continuar = 0;
		    
		
		    //Inicializa a palavra oculta com "_"
		    for (int i = 0; i < tamanho; i++) {
		        palavraOculta[i] = '_';
		    }
		    palavraOculta[tamanho] = '\0';
		
		    //Loop principal do jogo
		    while (tentativas < MAX_TENTATIVAS && letrasAcertadas < tamanho) {
		        limpaTela();
		        printf("=== Jogo da Forca ===\n\n");
		        printf("Palavra: ");
		        for (int i = 0; i < tamanho; i++) {
		            printf("%c ", palavraOculta[i]);
		        }
		        printf("\n\nAs letras ja colocadas são: ");
		    	for(int i = 0; i <= j - 1; i++){
		    		printf("%c ", letra[i]);
				}
		        printf("\nTentativas restantes: %d\n", MAX_TENTATIVAS - tentativas);
		        printf("Digite uma letra: ");
		        scanf(" %c", &chute);
		        chute = tolower(chute);
		        letra[j] = chute;
		        j++;
		    	for(int i = 0; i <= j - 1; i++){
				}
		        
		        int acertou = 0;
		        for (int i = 0; i < tamanho; i++) {
		            if (palavraSecreta[i] == chute && letrasEncontradas[i] == 0) {
		                palavraOculta[i] = chute;
		                letrasEncontradas[i] = 1;
		                letrasAcertadas++;
		                acertou = 1;
		            }
		        }
		        
		        if (!acertou) {
		            tentativas++;
		            player[0].pontos -= 1;
		            printf("Letra incorreta!\n");
		        } else {
		        	player[0].pontos += 3;
		            printf("Boa! Letra correta!\n");
		        }
		        
		        printf("Pressione Enter para continuar...");
		        getchar(); // consome o '\n' anterior
		        getchar(); // espera o Enter
			}
			
			
			
		
		    if (letrasAcertadas == tamanho) {
		        printf("Parabens! %s Voce venceu!\nTeve %d pontos \n",player[0].nome,player[0].pontos);
		    }	else {
		        	printf("Voce perdeu!\n%s teve %d pontos :( \n",player[0].nome, player[0].pontos);
		    	}
		
		    printf("A palavra era: %s\n", palavraSecreta);
		    printf("deseja continuar?\n");	//caso a pessoa deja continuar
		    printf("1 - sim\n");
		    printf("2 - não\n");
		    scanf("%d", &continuar);
		    
		    
		    
		    if(continuar <1 || continuar >2){
		    	printf("Digite um número correto!\n");
		    	printf("Digite novamente\n");
		    	scanf("%d", continuar);
			}
			
		
		    if(continuar == 1 ){
		    	main(); // Chama a função inicial
		    	return 0;
			} else if( continuar == 2){
						return 0;
				}
	}
	return 0;
}	
void TROCA(jogador *x, jogador *y) {

	jogador temp;	
	temp = *x;
	*x = *y;
	*y = temp;
}


void classifica(){
	
}



