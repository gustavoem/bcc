/*EP 3 MAC 0110
GUSTAVO ESTRELA DE MATOS - NºUSP: 8536051
Como foi interpretado o bônus:
1) Letras maiúsculas:
    -O programa troca as palavras que aparecem no texto mesmo que elas estejam em maiúscula, porém, a palavra que a substituirá será estritamente igual a palavra que o usuário digitar.
    Exemplo:
    10
    A abcA afga
    1
    a
    2
    Zw
    Zw ZwbcZw ZwfgZw
2) Sequências encaixadas:
    -O programa substitui toas as ocorrencias das palavras, mesmo que ela esteja encaixada, mas a lógica seguida é que o novo texto tenha o tamanho igual ao número de vezes que a
    sequência apareceu multiplicado pela diferença entre o texto novo e o substituido, assim não há problemas de looping infinito e o programa não deixa de trocar sequências encaixadas.
    Exemplos:
    6
    banana
    3
    ana
    5
    luana
    bluanluana

    7
    bananan
    4
    anan
    2
    an
    ban   --> perceba, o texto original possui 7 caracteres, todas as sequências que apareceram foram trocadas, e o novo texto tem o tamanho  7+2*(2-4)=3. E se fizéssemos a mão, o resultado
    seria o mesmo:

    bananan
    trocando anan por an:
    b(anan)an
    b(an)an
    banan
    b(anan)
    b(an)
    ban

    */
#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

void formata(char texto[MAX], int *n){/*Essa função retira os espaços duplos e junta pontos as palavras*/
    int i, k;
    /*Dicionário de variáveis:
    texto[MAX]- vetor com o texto digitado pelo usuário
    *n- ponteiro que indica o tamanho do texto no vetor texto[MAX]*/
    for(i=0;i<=*n;i++){
        if(texto[i]==texto[i+1] && texto[i]==' '){
            for(k=0; k+i<=*n;k++){
                texto[i+k]=texto[i+k+1];
            }
            i--;
            (*n)--;
        }
    }

    for(i=0;i<=*n;i++){/*deixa os sinais de pontuação formatados de maneira correta*/
        if(texto[i]=='.' || texto[i]==',' || texto[i]==':' || texto[i]==';' || texto[i]=='!' || texto[i]=='?'){
            if(texto[i-1]==' '){/*retira espaço antes do sinal de pontuação*/
                for(k=i-1; k<=*n;k++){
                    texto[k]=texto[k+1];
                }
                i--;
                (*n)--;
            }
            if(texto[i+1]!=' '){/*adiciona espaço após sinal de pontuação*/
                for(k=*n; k>i; k--){
                    texto[k+1]=texto[k];
                }
                texto[i+1]=' ';
                (*n)++;
            }
        }
    }

    return;
}

void trocaPalavra(char texto[MAX], char novotexto[2*MAX],int indices[MAX], char nova[MAX], int tamTexto, int tamProcura, int tamTroca, int nTrocas){
    int k=(nTrocas-1), i, j, auxInd=0;

     /*Dicionário de variáveis:
    texto[MAX]- texto digitado pelo usuário com as alterações já feitas em formata()
    novotexto[2*MAX]- texto final
    indices[MAX]- indices onde foram encontradas o texto que será substituido (segundo a função pegaindices())
    nova[MAX]- texto que será colocado no lugar do texto que será substituido
    tamTexto- tamanho do vetor texto[MAX]
    tamProcura- tamanho do texto que será substituido
    tamTroca- tamanho do texto que substituirá
    nTrocas- tamanho do vetor indices[MAX]
    k- indica a quantidade de trocas, ajudando no espaçamento e determinando o final do vetor que contem os índices das palavras que serão substituidas (indices[MAX])
    i,j- contadores
    auxInd- ajuda a indicar a posição certa na qual atribuir a nova palavra
    */

    /*dá o espacamento necessario*/
        for(i=tamTexto; i>=0; i--){
            novotexto[i+((k+1)*(tamTroca-tamProcura))]=texto[i];
            if(i==(indices[k]) && k>=0){
                k--;
            }
        }

    /*trocando a palavra*/
    k=(nTrocas-1);
    for(i=0; i<=k; i++){
        for(j=0; j<=tamTroca; j++){
            novotexto[indices[i]+j+(auxInd*(tamTroca-tamProcura))]=nova[j];
        }
        auxInd++;
    }
}

int pegaindices(char texto[MAX], char procurado[MAX],int tamTexto,int tamProcura, int indices[MAX]){
    int i,j,k=0,a=0;
    /*Dicionário de variáveis:
    texto[MAX]- vetor com o texto digitado pelo usuário
    procurado[MAX]- texto que será trocado
    tamTexto- tamanho do texto em texto[MAX]
    tamProcura- tamanho do texto em procurado[MAX]
    indices[MAX]- vetor que guarda os indices onde serão trocadas palavras
    i,j,a- contadores e auxiliares no indice
    k- número de trocas que serão feitas no texto*/
    for(i=0; i<=tamTexto; i++){
        a=0;
        for(j=0; j<=tamProcura; j++){
            if(texto[i+j]==procurado[j] || texto[i+j]==procurado[j]-'a'+'A' || texto[i+j]==procurado[j]-'A'+'a')
                a++;
        }
        if(a==(tamProcura+1)){
            indices[k]=i;
            k++;
        }
    }
    return k;
}

int main()
{
    /*Dicionário de variáveis:
    tamTexto- tamanho do texto que será digitado pelo usuário
    tamProcura- tamanho do texto que será trocado
    tamTroca- tamanho do novo texto
    indiceTrocas- vetor com os índices de onde haverão trocas
    nTrocas- número de trocas que haverão no texto
    i,k- auxiliares de indice de vetor
    txt- auxiliar na atribuição do texto ao vetor
    txtEntrada[MAX]- vetor com a instância entrada pelo usuário
    txtSaída[MAX]- vetor com a instância devidamente modificada
    antiga[MAX]- vetor com o texto que será substituido
    nova[MAX]- vetor com o texto que substituirá as ocorrências de antiga[MAX]*/
    int tamTexto, tamProcura, tamTroca, indiceTrocas[MAX], nTrocas, i, k;
    char txt, txtEntrada[MAX], txtSaida[2*MAX], antiga[MAX], nova[MAX];

    for(k=1; ;k++){
        if(k>1) printf("\n----------------------------------------------------------------\n\n");
        printf("Instancia %d\n", k);
        /*lendo a instancia*/
        printf("Digite o numero de caracteres presentes no texto a ser digitado:\n");
        scanf("%d", &tamTexto);
        /*sai do looping se o tamanho do texto for 0*/
        if(tamTexto==0) break;
        printf("Digite a instancia %d:\n",k);
        scanf(" %c", &txt);

        /*salvando o texto digitado em um vetor*/
        for (i=0; i<tamTexto; i++){
            txtEntrada[i]=txt;
            scanf("%c", &txt);
        }

        /*tira os espaços duplos digitados e traz o texto para as virgulas*/
        formata(txtEntrada, &tamTexto);

        /*lê a palavra que sera trocada*/
        printf("Digite o numero de caracteres do texto que sera trocado:\n");
        scanf("%d",&tamProcura);
        printf("Digite o texto que deseja trocar:\n");
        scanf(" %c",&txt);
        for (i=0; i<tamProcura; i++){
            antiga[i]=txt;
            scanf("%c", &txt);
        }

        /*percorre o texto procurando pelas ocorrencias das palavras a serem trocadas*/
        nTrocas=pegaindices(txtEntrada, antiga, (tamTexto-1), (tamProcura-1), indiceTrocas);

        /*lê a nova palavra*/
        printf("Digite o numero de caracteres do novo texto:\n");
        scanf("%d",&tamTroca);
        printf("Digite o novo texto:\n");
        scanf(" %c",&txt);
        for (i=0; i<tamTroca; i++){
            nova[i]=txt;
            scanf("%c", &txt);
        }

        /*troca o texto*/
        trocaPalavra(txtEntrada, txtSaida, indiceTrocas, nova,(tamTexto-1), (tamProcura-1), (tamTroca-1), nTrocas);

        /*dá ao usuário o texto novo*/
        printf("Instancia %d modificada:\n",k);
        for (i=0; i<=tamTexto+nTrocas*(tamTroca-tamProcura)-1; i++){
            printf("%c",txtSaida[i]);
        }
    }
    printf("FIM DO PROGRAMA");
    return 0;
}
