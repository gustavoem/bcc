/***************************************************************/
/**                                                           **/
/**   Gustavo Estrela de Matos                NUSP: 8536051   **/
/**   Exercício-Programa 1                                    **/
/**                                                           **/
/***************************************************************/

#include <stdio.h>  /* scanf, printf,  ... */
#include <stdlib.h> /* srand, rand,    ... */
#include <string.h> /* strlen, strcmp, ... */  
#include <math.h>
/*---------------------------------------------------------------*/
/* 
 * 0. C O N S T A N T E S 
 */

/* tamanho máximo de um tdorm */
#define MAX       128
/* tamanho máximo do nome de um arquivo lido*/
#define FNMAX     200 

#define ACORDADO  '#'
#define DORMINDO  ' '
#define TAPINHA   'T'

#define TRUE  1
#define FALSE 0

#define ENTER  '\n'
#define FIM    '\0'
#define ESPACO ' '


/*---------------------------------------------------------------*/
/*
 * 1. P R O T Ó T I P O S
 */

/* PARTE I */
void
leiaTurtledorm(int *n, int tdorm[MAX][MAX]);	

void 
mostreTurtledorm(int n, int tdorm[][MAX], char c);

void
atualizeTurtledorm(int n, int tdorm[][MAX], int lin, int col);

int 
todosDormindo(int n, int tdorm[][MAX]);

int
graveTurtledorm(int n, int tdorm[][MAX]);

/* PARTE II */

void
sorteieTurtledorm(int *n, int tdorm[][MAX]);

int
randomInteger(int low, int high);

/* PARTE III */

void
resolvaTurtledorm(int n, int tdorm[][MAX]);

/* FUNÇõES AUXILIARES */
void
achaSolucoes(int vLivres, int a[][MAX * MAX], int n, int melhorSolucao[MAX * MAX], int *tamSolucao);

int
soTemZero(int v[MAX * MAX], int n);

/*---------------------------------------------------------------*/
/* 
 *  M A I N 
 */
int
main(int argc, char *argv[])
{
	char resp;
	int tdorm[MAX][MAX], n, cond=0, lin, col, numJogadas=0;
	printf("(s)ortear ou (l)er turtledorm de arquivo:");
	scanf("%c",&resp);
	if(resp=='l')
		leiaTurtledorm(&n, tdorm);
	else
	{
		sorteieTurtledorm(&n, tdorm);
	}
	mostreTurtledorm(n, tdorm, ACORDADO);
	printf("\nDigite sua jogada no formato: linha coluna");
	printf("\nOu digite uma das opções:");
	printf("\n(d)esistir da partida");
	printf("\n(a)juda");
	printf("\n(g)ravar jogo\n");
	for(numJogadas = 0; !todosDormindo(n, tdorm) && cond == 0; numJogadas++)
	{
		if(scanf("%d %d", &lin, &col) == 0)
		{
			scanf("%c", &resp);
			if(resp == 'g')
			{
				numJogadas--;
				if(graveTurtledorm(n,tdorm) == EXIT_SUCCESS)
					printf("Jogo salvo com sucesso, entre com a próxima jogada.\n");
				else
					printf("Houve algum problema ao salvar o jogo, entre com a próxima jogada.\n");
			}			
			if(resp == 'd')
			{
				cond = 1;
				numJogadas--;
			}
			if(resp == 'a')
			{
				resolvaTurtledorm(n, tdorm);
				numJogadas--;
				printf("\nDigite sua jogada no formato: linha coluna");
				printf("\nOu digite uma das opções:");
				printf("\n(d)esistir da partida");
				printf("\n(a)juda");
				printf("\n(g)ravar jogo\n");
			}	
		}
		else
		{
			atualizeTurtledorm(n, tdorm, lin, col);
			mostreTurtledorm(n, tdorm, ACORDADO);
			printf("\nDigite sua jogada no formato: linha coluna");
			printf("\nOu digite uma das opções:");
			printf("\n(d)esistir da partida");
			printf("\n(a)juda");
			printf("\n(g)ravar jogo\n");
		}
	}
	if(todosDormindo(n, tdorm))
		printf("Você ganhou o jogo com %d jogadas feitas!\n", numJogadas);
	else
		printf("Você desistiu do jogo com %d jogadas feitas!\n", numJogadas);
	return EXIT_SUCCESS;
}

/*---------------------------------------------------------------*/
/* 
 *  I M P L E M E N T A Ç Ã O   D A S   F U N Ç Õ E S   DA  
 *                       P A R T E   I 
 */

/*Lê de um arquivo a configuração de um turtledorm e retorna em *n a sua ordem e em tdorm a sua representação*/
void
leiaTurtledorm(int *n, int tdorm[][MAX])
{
	char nomearq[FNMAX];
	int i, j;
	FILE *turtledorm;
	/*leitura do nome do arquivo*/
	printf("Digite o nome do arquivo com o jogo salvo:");
	scanf(" ");
	fgets(nomearq, FNMAX, stdin);
	for(i = 0;i < FNMAX; i++)
	{
		if(nomearq[i]==10 || nomearq[i]==12)
		{
			nomearq[i]=0;
			break;
		}
	}
	/*leitura da matriz que representa o turtledorm e seu tamanho*/	
	turtledorm = fopen(nomearq,"r");
	if(turtledorm == NULL)
		printf("Nao foi possivel achar o arquivo com o jogo");
	fscanf(turtledorm,"%d ", &(*n));
	for(i = 0; i < *n; i++)
		for(j = 0; j < *n ; j++)	
		{
			fscanf(turtledorm, "%d ", &tdorm[i][j]);	
		}
}

/*Mostra na tela o turtledorm representado por n e por tdorm. O parâmetro c é o caracter que representará os "1" da matriz binaria tdorm*/
void
mostreTurtledorm(int n, int tdorm[][MAX], char c)
{
	int sep,i,j;
	printf("\n");
	printf("   |");
	/*grade de cima do turtledorm*/
	for(i = 1; i <= n; i++)
		printf("%3d|", i);

	for(i = 0; i < n; i++){
		printf("\n");
		/*separador horizontal do turtledorm*/
		for(sep = 0; sep <= n; sep++)
			printf("---+");
		
		printf("\n");
		/*separador vertical e conteudo do turtledorm*/
		for(j = 0; j <= n; j++){
			if(j==0)
				printf("%3d|", i + 1);
			else{
				if(tdorm[i][j-1] == 1)
					printf("%3c|", c);
				else
					printf("   |");
			}
		}
	}
	printf("\n");
}

/*Recebe em lin e col coordenadas da jogada feita e atualiza a configuração do jogo em tdorm*/
void
atualizeTurtledorm(int n, int tdorm[][MAX], int lin, int col)
{
	lin--;
	col--;
	if(lin - 1 >= 0)
		tdorm[lin - 1][col] = (tdorm[lin - 1][col] + 1) % 2;
	if(col - 1 >= 0) 
		tdorm[lin][col - 1] = (tdorm[lin][col - 1] + 1) % 2;	
	if(lin + 1 < n)
		tdorm[lin + 1][col] = (tdorm[lin + 1][col] + 1) % 2;
	if( col + 1 < n) 
		tdorm[lin][col + 1] = (tdorm[lin][col + 1] + 1) % 2;
	tdorm[lin][col] = (tdorm[lin][col] + 1) % 2;
}
/*Verifica se todos os turtles de tdorm estão dormindo, ou seja, se a matriz tdorm tem apenas zeros. Se for verdade retorn TRUE
se não retorna FALSE*/
int 
todosDormindo(int n, int tdorm[][MAX])
{
	int i,j;
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			if(tdorm[i][j] == 1)
				return FALSE;
	return TRUE;
}

/*Recebe a configuração de um turtledorm e sua dimensão e a salva em um arquivo*/
int
graveTurtledorm(int n, int tdorm[][MAX])
{
	int i, j;
	char nomearq[FNMAX];	
	FILE *turtledorm;
	/*leitura do nome do arquivo*/
	printf("Digite o nome do arquivo com o jogo a ser salvo:");
	scanf(" ");
	fgets(nomearq, FNMAX, stdin);
	for(i=0;i<FNMAX;i++)
		if( nomearq[i] == 10 || nomearq[i] == 12)
		{
			nomearq[i] = 0;
			break;
		}
	/*leitura da matriz que representa o turtledorm e seu tamanho*/	
	turtledorm = fopen(nomearq,"w");
	if(turtledorm == NULL)
		return EXIT_FAILURE;
	fprintf(turtledorm, "%d\n", n);
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
			fprintf(turtledorm, "%d ", tdorm[i][j]);
		fprintf(turtledorm, "\n");
	}
	fclose(turtledorm);
	return EXIT_SUCCESS;
}
/*---------------------------------------------------------------*/
/* 
 *  I M P L E M E N T A Ç Ã O   D A S   F U N Ç Õ E S   DA  
 *                       P A R T E   II 
 */
/*Recebe um valor inteiro e uma matriz, e, com o auxílio da função randomInteger, sorteia uma configuração de Turtledorm salvando-a na matriz tdorm[][MAX]*/
void
sorteieTurtledorm(int *n, int tdorm[][MAX])
{
	int semente, nTapinhas=0, i, j, linha, coluna, acordados=0;
	char dificuldade;
	printf("Digite o tamanho do turtledorm:");
	scanf("%d", n);
	/*iniciando a matriz/turtledorm*/
	for(i = 0; i < (*n); i++)
		for(j = 0; j < (*n); j++)
			tdorm[i][j] = 0;
	printf("Digite uma semente para o sorteio do turtledorm:");
	scanf("%d", &semente);	
	srand(semente);
	printf("Digite o nivel de dificulade [f/d/m]:");
	scanf(" %c", &dificuldade);
	if(dificuldade == 'f')
		nTapinhas = randomInteger((int) (*n) * (*n) * 0.05, (int) (*n) * (*n) * 0.2);
	if(dificuldade == 'm')
		nTapinhas = randomInteger((int) (*n) * (*n) * 0.25, (int) (*n) * (*n) * 0.5);
	if(dificuldade == 'd')
		nTapinhas = randomInteger((int) (*n) * (*n) * 0.55, (int) (*n)* (*n) * 0.85);
	for(i = 0; i < nTapinhas; i++)
	{
		linha = randomInteger(1, (*n));
		coluna = randomInteger(1, (*n));
		atualizeTurtledorm((*n), tdorm, linha, coluna);
	}
	for(i = 0; i < (*n); i++)
		for(j = 0; j < (*n); j++)
			if(tdorm[i][j] == 1)
				acordados++;
	printf("Numero de tapinhas sorteados: %d", nTapinhas);
	printf("\nNumero de turtles acordados: %d", acordados);
}

/*Recebe um valor mínimo e máximo, devolvendo um inteiro entre esses números.*/
int
randomInteger(int low, int high)
{
	int a;
	a = rand();
	a = a % (high - low);
	return low + a;
}

/*---------------------------------------------------------------*/
/* 
 *  I M P L E M E N T A Ç Ã O   D A S   F U N Ç Õ E S   DA  
 *                       P A R T E   III 
 */
/*Recebe uma configuração de Turtledorm e sua dimensão, e dá ao usuário a solução do mesmo, ou a mensagem de que a configuração não possui solução.*/
void
resolvaTurtledorm(int n, int tdorm[][MAX])
{
	/*Podemos gerar a solução para o turtledorm resolvendo o seguinte sistema linear:
	Ax=B
	No qual, A é a matriz que representa por 1 os turtles afetados pelo clique em cada turtle e 0 os turtles não afetados. Para criar essa matriz deveremos numerar os turtles de 1 a n*n. Assim, na coluna 1 da matriz A (a[i][0] | 0 <= i <= n*n) as linhas que terão 1 serão as que o turtle numero 1 afeta, que serão os turtles 2, 1 e 1+n; na coluna n*n da matriz A (a[i][n*n] | 0 <= i <= n*n) as linhas que terão 1 serão as que o ultimo turtle afeta, que serão os turtles n*n-1, n*n e n*n-n
	Ex de A (n = 3):
	1 1 0 1 0 0 0 0 0 
	1 1 1 0 1 0 0 0 0 
	0 1 1 0 0 1 0 0 0 
	1 0 0 1 1 0 1 0 0 
	0 1 0 1 1 1 0 1 0 
	0 0 1 0 1 1 0 0 1 
	0 0 0 1 0 0 1 1 0 
	0 0 0 0 1 0 1 1 1 
	0 0 0 0 0 1 0 1 1
	
	B é o vetor que representa a configuração original a turtledorm a ser gerado a solução. B[x] = tdorm[i][l] com 0 <= i,j < n e 0 <= l < n*n
	
	x é o vetor que varia de 0 até n*n-1 que representa quais os turtledorms que devem levar tapas para que todos os turtles durmam
	Acharemos x usando o método de Gauss na matriz aumentada (A|B)
	
	*/
	int i, j, x=0, pivoN, linhapivo, aux, vLivres;	
	static int a[MAX * MAX][MAX * MAX];
	int solucao[MAX * MAX];
	int matrizSolucao[MAX][MAX];
	int tamSolucao;

	/*Preenchendo A*/
	for(j = 0; j < n * n; j++)
	{	
		for(i = 0; i < n * n; i++)
		{
			if(i == j)
				a[i][j] = 1;
			else if(i == j - 1 && j % n != 0)
				a[i][j] = 1;
			else if(i == j + 1 && j % n != n - 1)
				a[i][j] = 1;
			else if(i == j - n)
				a[i][j] = 1;
			else if(i == j + n)
				a[i][j] = 1;
			else
				a[i][j] = 0;
		}
	}
	/*Criando (A|B)*/
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			a[x][n * n] = tdorm[i][j];
			x++;
		}
	}

	/*aplicando o eliminação de Gauss para solucionar o sistema*/	
	for(pivoN = 0; pivoN < n * n; pivoN++)
	{
		linhapivo = -1;/*evita passos desnecessários quando a matriz já está na forma escalonada reduzida (vide condição nos próximos laços de repetição)*/
		for(i = pivoN; i < n * n; i++)/*o pivo foi localizado*/
			if(a[i][pivoN] == 1)
			{
				linhapivo = i;
				break;
			}
		/*trocar a linha pivoN da matriz pela linha i com o pivo achado*/
		for(j = 0; j < n*n+1 && linhapivo != -1; j++)
		{
			aux = a[pivoN][j];
			a[pivoN][j] = a[linhapivo][j];
			a[linhapivo][j] = aux;
		}
		linhapivo = pivoN;
		/*transforma em zeros os elementos de coluna pivoN das outras linhas somando a linha do pivo nessas linhas*/
		for(i = 0; i < n * n && linhapivo != -1; i++)
		{
			if(a[i][pivoN] == 1 && i != linhapivo)
				for(j = 0; j < n * n + 1; j++){
					a[i][j] = (a[linhapivo][j] + a[i][j]) % 2;
					
				}
		}
	}
	/*Se não houve nenhum problema, temos agora em no vetor a[i][n*n]  0 <= i < n * n uma das soluções para o sistema solução para o sistema, que, no caso, representa quais turtles devem receber tapinhas para que todos os turtles durmam. Mas, pode ser que ao escalonar o sistema algumas linhas fiquem apenas com zeros. Nesse caso existem mais de uma solução. Também pode ocorrer de o sistema escalonado ser impossível, logo não há soluções para o turtledorm.
Chamaremos de quiet pattern cada uma das colunas com variáveis livres, e nesse vetor, consideramos que a[quietpatern][j] com j == quietpatern o valor 1, pois assim assumimos valores para a variavel livre e geramos novas soluções (explicado na função achaSolucoes).*/
	vLivres = 0;
	for(i = 0; i < n * n; i++)
		if(a[i][i] != 1)
			vLivres++;

	for(i = n * n - 1; i > (n * n - 1) - vLivres; i--)
		if(!soTemZero(a[i], n * n + 1))
		{
			printf("\nEste jogo não possui solução");
			return;
		}
	achaSolucoes(vLivres, a, n, solucao, &tamSolucao);
	aux = 0;
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++, aux++)
			matrizSolucao[i][j] = solucao[aux];
	mostreTurtledorm(n, matrizSolucao, 'T');
	printf("Numero de tapinhas necessários: %d\n", tamSolucao);
}

/*---------------------------------------------------------------*/
/* 
 *  I M P L E M E N T A Ç Ã O   D A S   F U N Ç Õ E S   DA  
 *                     A U X I L I A R E S 
 */


/*recebe uma matriz a[][MAX * MAX] com n * n linhas e n * n + 1 colunas ,que representa a matriz que dá solução ao turtledorm, e a partir de suas vLivres variaveis livres, dá em melhorSolucao a melhor solução e em *tamSolucao a quantidade de tapinhas para resolver o turtledorm*/
void
achaSolucoes(int vLivres, int a[][MAX * MAX], int n, int melhorSolucao[MAX * MAX], int *tamSolucao)
{
	int i, j, k, cont = 0, n1Menor=0, n1;
	int flagCol, colSomar;
	int solucao[MAX * MAX];	
	/*Seja qp1,qp2,...,qpn os vetores das colunas dos n quiet patterns da matriz a e x a ultima coluna da matriz a, as 2^n soluções possíveis serão dadas por:
	x
	x+qp1
	x+qp1+qp2
	...
	x+qp1+qp2+...+qpn
	x+qp1+qp3
	x+qp1+qp3+qp4
	.
	.
	.
	ou seja, todas as somas possíveis entre qpi e x.
	para nos orientar e somar as colunas certas sem esquecer de nenhuma usaremos a variavel colSomar, que em binario nos ajudará a saber qual colunasomar. Ex: 01010 => devo somar qp2 e qp3
	*/
	for(i = 0; i < n * n; i++)
	{	
		melhorSolucao[i] = a[i][n * n];
		if(melhorSolucao[i] == 1)
			n1Menor++;
	}
	colSomar = 1;
	/*Faremos todas as somas possíveis entre qpi e x. Note que são 2^n-1, e somando x que também é solução, temos 2^n soluções para n variaveis livres*/
	for(k = 0; k < pow(2, vLivres) - 1; k++, colSomar++)
	{
		/*Guardaremos o numero de "1"s ou tapinhas de cada solução gerada*/	
		n1 = 0;

		for(i = 0; i < n * n; i++)
			solucao[i] = 0;

		/*Percorreremos agora cada linha da matriz a, e ao mesmo tempo, cada coluna com variáveis livres, somando-as a x para determinar novas soluções.*/
		for(i = 0; i < n * n; i++)
		{
			cont = 0;/*auxiliar para determinar em qual digito de colSomar estamos olhando, e assim determinar flagCol*/
			for(j = n * n - 1; j >= n * n - vLivres; j--, cont++)
			{
				/*flagCol pode ser 1 ou 0. Se for 1, considera a coluna na soma*/
				flagCol = ((colSomar) / ((int)(pow(2,cont)))) % ((int)(pow(2,cont+1)));
				if(i == j)
					solucao[i] = ((	flagCol * (1+ a[i][n * n])) + solucao[i]) % 2;
				else
					solucao[i] = (flagCol * (a[i][j]) + solucao[i]) % 2;
			}
			solucao[i] = (solucao[i] + a[i][n * n]) % 2;
			if(solucao[i] == 1)
				n1++;
		}

		if(n1 < n1Menor)
		{
			for(i = 0; i < n * n; i++)
				melhorSolucao[i] = solucao[i];
			n1Menor = n1;		
		}

	}
	*tamSolucao = n1Menor;
}

/*Recebe um vetor de tamanho n, e verifica se so existem zeros em seu conteúdo, retornando 1 se sim e 0 se não.*/
int
soTemZero(int v[MAX * MAX], int n)
{
	int i;
	for(i = 0; i < n; i++)
		if(v[i] != 0)
			return 0;
	return 1;	
}
