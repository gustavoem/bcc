#include <stdio.h>
#include <math.h>
#define MAX 800
#define MAX2 640000
#define FNMAX 200
#define cinza int
/*
int unbin(int x){
    int aux=x,casa=1,bin=0;
    while(aux>0){
        bin+=(aux%10)*casa;
        casa*=2;
        aux/=10;
    }
    return bin;
}

int bin(int x){
    int aux=x,casa=1,bin=0;
    while(aux>0){
        bin+=(aux%2)*casa;
        casa*=10;
        aux/=2;
    }
    return bin;
}*/

int LeDesenho(char nomearq[FNMAX], cinza M[MAX][MAX], int *pm, int *pn, int *pmax){
    /*nomearq[FNMAX] - guarda o nome do arquivo em formato PGM
    *pm - numero de linhas
    *pn - numero de colunas
    *pmax - valor maximo de um tom de cinza
    M[MAX][MAX] - conteudo matriz*/
    char texto[MAX];
    int cont=0,i,j;
    FILE *imagem;
    imagem=fopen(nomearq,"r");
    
    if(imagem==NULL)
        return 1;
    while(fgets(texto, MAX,imagem)!=NULL){
        if(cont==0){
            if(fscanf(imagem,"%d %d", &(*pn),&(*pm))>0){
            cont++;
            }
        }
        if(cont==1){
            if(fscanf(imagem,"%d", &*pmax)>0){
                cont++;
            }
        }
        if(cont>1){
	    for(j=0; j<*pm;j++){
            for(i=0; i<*pn;i++){
                if(i>=MAX || cont-2>=MAX)
                    return 1;
                if(!fscanf(imagem,"%d", &M[j][i])>0){
                    i--;
                }
	    }
            }
        }
    }
    if(cont<1)
	return 1;
    fclose(imagem);
    printf("Desenho lido com com m=%d e n=%d\n", *pm, *pn);
    return 0;
}

int LeTexto(char nomearq[FNMAX], char T[MAX2], int *pk){
    /*
    nomearq[FNMAX]- nome do arquivo
    T[MAX2]- vetor que recebe  o texto do arquivo
    pk- tamanho do texto lido
	*/
    FILE *texto;
    *pk=0;	
    texto=fopen(nomearq,"r");
    if(texto==NULL)
        return 1;

    while(fscanf(texto,"%c", &T[*pk])==1){
        (*pk)++;
        if(*pk>=MAX2-1)
            return 1;
    }
    (*pk)--;
    printf("Texto lido com k=%d\n",*pk);
    return 0;
}

int BeDeu(int k, int m, int n, int *pb, int *pd){
    int i;
    /*
    k- tamanho do texto que sera codificado
    m- linhas da imagem
    n- colunas da imagem
    *pb- ponteiro que recebe o valor de b
    *pd- ponteiro que recebe o valor de d
	*/
    *pb=1;
    if(k<1){
        *pb=0;
    }else if(8*k>m*n-1){
        *pd=1;
        for(i=2; i<=8; i++){
            if(i*((m*n)-1)>=8*k && (8%i==0)){                
		*pb=i;
                break;
            }
        }
        if(*pb==0)
            return 1;
    }

    for(i=1; i<=m && i<=n ; i++){
        if((m/i)*(n/i)*(*pb)>=8*k+(*pb))
            *pd=i;
    }
    if(*pd==0 || m*n<=k)
        return 1;
    printf("b e d calculados com sucesso: %d %d", *pb,*pd);
    return 0;
}

int ProximosBBits(char T[MAX2], int b, int *pik, int *pib){
    int res;
    /*
    T[MAX2]- vetor com o texto codificado
    b- valor de b
    *pik- indice do texto que a funcao trabalha
    *pib- ajuda a ignorar os bits menos significativos já codificados
    res- bits a serem codificados
    */
    res=T[*pik]/(pow(2,*pib));
    res=res%((int)pow(2,b));
    if(*pib+b>7)
        (*pik)++;
    *pib=((*pib)+b)%8;
    return res;
}

void Codifica(cinza D[MAX][MAX], int m, int n, char T[MAX2], int k, cinza D1[MAX][MAX], int b, int d,int modo){
    int i, j, num, posT=0, posP=0,cont=0;
    /*
    D- imagem original
    m- numero de linhas de D
    n- numero de colunas de D 
    T- texto a ser codificado
    k- tamanho do texto a ser codificado
    D1- matriz com o texto codificado
    b- parametro b
    d- parametro d
    modo- verborragico, sim ou nao
    num- b bits que a funcao ProximosBBits devolve
*/
    num=0;
    for(i=0;i<m; i++){
        for(j=0;j<n;j++){
            if((i+1)%d==0 && (j+1)%d==0 && (i!=d-1 || j!=d-1)){
                cont++;
                if(cont<8*k)
                    num=ProximosBBits(T, b, &posT, &posP);
                else
                    num=0;
                D1[i][j]=((int)(D[i][j]/pow(2,b))*pow(2,b))+((D[i][j])+num)%((int)pow(2,b));
            	if(modo==1){
		    printf("\nPosicao que recebeu marca: %d %d",i,j);
		    printf("\nInteiro que codifica os b bits ocultados: %d",num);
		    printf("\nTom de cinza original: %02x", D[i][j]);
		    printf("\nTom de cinza com marca d'agua: %02x\n", D1[i][j]);		
		}
	    }
            else{
                D1[i][j]=D[i][j];
            }
        }
    }
    D1[d-1][d-1]=((int)(D[d-1][d-1]/pow(2,b))*pow(2,b))+((D[d-1][d-1])+b)%((int)pow(2,b));
    printf("\nA matriz D1 foi calculada com m=%d e n=%d\n", m,n);
    printf("O texto ocultado com sucesso tem tamanho k=%d\n", k);
}

cinza Maximo(cinza D[MAX][MAX], int m, int n){
    /*
    D- matriz
    m- numero de linhas da matriz
    n- numero de colunas da matriz
    res- valor maximo da matriz
    */
    int res=D[0][0], i,j;
    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
            if(D[i][j]>res)
                res=D[i][j];
    return res;
}

int EscreveDesenho(char nomearq[FNMAX], cinza M[MAX][MAX], int m, int n, int max){
    /*
    nomearq- nome do arquivo que recebera a matriz calculada
    m- numero de linhas da matriz
    n- numero de colunas da matriz
    max- valor maximo da matriz
    */
    int i,j;
    FILE *imagem;
    imagem=fopen(nomearq,"w");
    if(imagem==NULL){
        printf("Erro ao abrir o arquivo");
        return 1;
    }
    fprintf(imagem,"P2");
    fprintf(imagem,"\n%d %d",n,m);
    fprintf(imagem,"\n%d", max);
    fprintf(imagem,"\n");
    for(i=0;i<m;i++){
        for(j=0;j<n;j++)
            fprintf(imagem,"%d ",M[i][j]);
        fprintf(imagem,"\n");
    }
    fclose(imagem);
    return 0;
}

void DeBeDeu(cinza D[MAX][MAX], cinza D1[MAX][MAX], int m, int n, int *pb, int *pd){
    int i;
    /*
    D- matriz original
    D1- matriz com o texto codificado
    m- numero de linhas das matrizes
    n- numero de colunas das matrizes
    *pb- valor de b descoberto
    *pd- valor de d descoberto
    */
    for(i=0;i<m && i<n;i++){
        if(D[i][i]!=D1[i][i]){
            *pd=i+1;
            break;
        }
    }
    for(i=1; i<=8; i*=2){
	/*printf("\n\n i: %d  D: %d   D1: %d",i,D[*pd-1][*pd-1]%i,D1[*pd-1][*pd-1]%i);*/
    	if((D[*pd-1][*pd-1]%(i))!=(D1[*pd-1][*pd-1]%(i))){
	    *pb=i/2;
	    break;	
	}
    }
    /*printf("\n\n D1[*pd-1][*pd-1]: %d  D[*pd-1][*pd-1] %d \n\n",bin(D1[*pd-1][*pd-1]),bin(D[*pd-1][*pd-1]));*/
    printf("\nOs parametros b e d foram descobertos: %d %d", *pb,*pd);
}
int DeCodifica(cinza D[MAX][MAX], cinza D1[MAX][MAX],int m, int n, int b, int d, char T[MAX2], int modo){
    /*
    D- matriz original
    D1- matriz com o texto codificado
    m- numero de linhas das matrizes
    n- numero de colunas das matrizes
    b- valor de b
    d- valor de d
    T- texto decodificado pela funcao
    modo- verborragico ou nao
    */
    int i,j,bit=0, pos=0,casa=1, aux=0, achafim=0,res=0, num=0;
    for(i=d-1;i<=((int)(m/d))*(d)-1;i=i+d){
    	for(j=d-1; j<=((int)(n/d))*(d)-1; j=j+d){
	    if(i!=d-1 || j!=d-1){
		/*printf("\ni:%d j:%d   dif:%d  res:%d", i,j,D1[i][j]-D[i][j],((D1[i][j]-D[i][j]+256)%((int)pow(2,b)))*casa+aux);*/
		num=((D1[i][j]-D[i][j]+256)%((int)pow(2,b)));	    	
		aux=num*casa+aux;	    	
		bit+=b;
		casa*=pow(2,b);
		if(modo==1){
		    printf("\nPosicao que recebeu marca: %d %d",i,j);
		    printf("\nInteiro que codifica os b bits ocultados: %d",num);
		    printf("\nTom de cinza original: %02x", D[i][j]);
		    printf("\nTom de cinza com marca d'agua: %02x\n", D1[i][j]);		
		}
		achafim+=aux;
	    	if(bit>7){
		    if(achafim!=0){
		    	res=pos;
		    }
		    achafim=0;
		    T[pos]=aux;
		    pos++;
	    	    bit=bit%8;
		    casa=1;
		    aux=0;	
	    	}
	    }
	}
    }
    /*printf("\n");
    for(i=0;i<pos;i++){
    	printf("%c", T[i]);
    }
    printf("\n");*/						
																																																																								
    
    printf("\nTexto decodificado com k=%d",res+1);
    return res+1;
}	

int EscreveTexto(char nomearq[FNMAX], char T[MAX2], int k){
    /*
    nomearq- nome do arquivo que recebera o texto
    T- texto que foi decodificado
    k- tamanho do texto que foi decodificado
    */
    int i;
    FILE *texto;
    texto=fopen(nomearq,"w");
    if(texto==NULL){
        printf("Erro ao abrir o arquivo");
        return 1;
    }	
    for(i=0;i<k;i++){
	fprintf(texto,"%c",T[i]);
    }
    fclose(texto);
    return 0;
}

int main(){
    int i, m, n, max,  Matrix[MAX][MAX], codMatrix[MAX][MAX],k, b, d, modo=0,op=1;
    char nome[FNMAX], texto[MAX2], dectexto[MAX2];
    /*
    nome- nome do arquivo lido
    texto- texto lido
    dectexto- texto decodificado
    m,n- linhas, colunas da matriz
    b,d- valor dos parametros b,d
    k- qtde de letras do texto
    Matrix- matriz original
    codMatrix- matriz codificada
    modo- verborragico ou nao
    op- opcao
    */
    while(op!=0){
	printf("\n");
    	printf("Escolha uma opcao:\n");
	printf("1- Codificar um texto\n");
	printf("2- Decodificar uma imagem\n");
	printf("3- Mostra texto de um arquivo\n");
	if(modo==0)	
	printf("4- Ligar modo verborrágico\n");	
	else
	printf("4- Desligar modo verborrágico\n");
	scanf("%d", &op);
        if(op<0 || op>4)
            printf("Digite uma opcao valida\n");
	if(op==1){/*Codifica um texto*/
	    printf("_________________________________________________________");
	    printf("\nDigite o nome do arquivo que contem o desenho original\n");
	    scanf(" ");
	    
    	    fgets(nome,FNMAX,stdin);
	    for(i=0;i<FNMAX;i++){
		if(nome[i]==10 || nome[i]==12)
		    nome[i]=0;
	    }
		
	    if(LeDesenho(nome, Matrix, &m, &n, &max)==1){
		printf("Nao foi possivel ler a imagem. Tente novamente\n");
	    }
	    else
	    {
	    printf("\nDigite o nome do arquivo que contem o texto a codificar\n");
	    fgets(nome,FNMAX,stdin);
	    for(i=0;i<FNMAX;i++){
		if(nome[i]==10 || nome[i]==12)
		    nome[i]=0;
	    }
	    if(LeTexto(nome,texto,&k)==1)
		printf("Nao foi possivel ler o texto. Tente novamente\n");
	    else
	    {
	    if(BeDeu(k, m, n, &b, &d)==1)
		printf("Nao foi possivel calcular os parametros b,d. Tente novamente\n");
	    else
	    {
    	    Codifica(Matrix, m, n, texto, k, codMatrix, b, d, modo);
	    if(max<Maximo(codMatrix,m,n))
		max=Maximo(codMatrix,m,n);
	    printf("\nDigite o nome do arquivo que contera o desenho codificado\n");
	    fgets(nome,FNMAX,stdin);
	    for(i=0;i<FNMAX;i++){
		if(nome[i]==10 || nome[i]==12)
		    nome[i]=0;
	    }
	    if(EscreveDesenho(nome, codMatrix, m,n,max)==1)
	    	printf("Nao foi possivel escrever a imagem. Tente novamente\n");
	    printf("_________________________________________________________");
	    printf("\n");
	    }
	    }
	    }	
	}
	if(op==2){
	    printf("_________________________________________________________");
	    printf("\nDigite o nome do arquivo que contem o desenho original\n");
	    scanf(" ");
    	    fgets(nome,FNMAX,stdin);
	    for(i=0;i<FNMAX;i++){
		if(nome[i]==10 || nome[i]==12)
		    nome[i]=0;
	    }
	    if(LeDesenho(nome, Matrix, &m, &n, &max)==1)
		printf("Nao foi possivel ler a imagem. Tente novamente\n");
	    else
	    {
	    printf("\nDigite o nome do arquivo que contem o desenho codificado\n");
    	    fgets(nome,FNMAX,stdin);
	    for(i=0;i<FNMAX;i++){
		if(nome[i]==10 || nome[i]==12)
		    nome[i]=0;
	    }
	    if(LeDesenho(nome, codMatrix, &m, &n, &max)==1)
		printf("Nao foi possivel ler a imagem. Tente novamente\n");
	    else{
	    DeBeDeu(Matrix, codMatrix,m,n,&b,&d);
	    k=DeCodifica(Matrix, codMatrix, m, n, b, d, dectexto, modo);
	    printf("\nDigite o nome do arquivo que recebera o texto codificado\n");
    	    fgets(nome,FNMAX,stdin);
	    for(i=0;i<FNMAX;i++){
		if(nome[i]==10 || nome[i]==12)
		    nome[i]=0;
	    }
	    EscreveTexto(nome, dectexto, k);
	    printf("_________________________________________________________");
	    printf("\n");
	    }
	    }	
	}
	if(op==3){
	    printf("_________________________________________________________");
	    printf("\nDigite o nome do arquivo que contem o texto\n");
	    scanf(" ");
	    fgets(nome,FNMAX,stdin);
	    for(i=0;i<FNMAX;i++){
		if(nome[i]==10 || nome[i]==12)
		    nome[i]=0;
	    }
	    if(LeTexto(nome, texto, &k)==1)
	    	printf("Nao foi possivel ler o texto. Tente novamente\n");
	    else{
	    printf("\n");
	    for(i=0; i<k; i++){
		printf("%c",texto[i]);
	    }
	    printf("\n_________________________________________________________");
	    printf("\n");
	    }
	}
	if(op==4){	
	    modo=(modo+1)%2;	
	}
    }
    return 0;
}
