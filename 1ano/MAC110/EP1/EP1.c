#include <stdio.h>
#include <stdlib.h>
/* Nome: Gustavo Estrela de Matos | Nusp: 8536051
EP1
Como o tabuleiro está organizado:

y1    |   |
   ---+---+---
y2    |   |
   ---+---+---
y3    |   |
   x1   x2  x3

   Dicionario de variaveis:
   x, y: Coordenadas da jogada feita pelo computador ou usuario
   somaTab: soma que representa a tabela no formato:

            3^0|3^1|
            ---+---+---
               |   |
            ---+---+---
               |   |3^8

    vezJog: Controla a vez de quem joga
    controle: Faz com que ocorram somente 9 rodadas no jogo
    jogada: Representa se a jogada foi "O" ou "S"
    ternario: Represantação do numero somaTab na forma de base 3. Ex: somaTab=1 -> ternario=1  |  somaTab=16 -> ternario=121
    parcial: Auxiliar para transformar somaTab em um número de base 3
    i,j: Contadores
    casa: Auxiliar para transformar somaTab em um número de base 3 | variável auxiliar para obter algum algarismo no numero ternario (no momento em que o computador joga "aleatoriamente")
    ptosRodada: Conta a quantidade de SOS formados em cada rodada
    jogPlacar: Armazena pontuação do usuario
    compPlacar: Armazena pontuação do computador
    passar: Faz que o jogo seja compassado, rodada por rodada
    permissao: Permite um looping que faz o usuario digitar coordenadas até que uma delas seja válida

*/
int main()
{
    int x,y,somaTab=0,vezJog=0,controle=0, jogada=0, ternario=0, parcial,i=0,j, casa=1,ptosRodada=0, jogPlacar=0,compPlacar=0, passar=0, permissao=0;

    printf("Bem-vindo ao jogo do SOS\nDigite 1 para comecar e digite 2 para o computador comecar\n");
    scanf("%d",&vezJog);
    while(controle<9){
        ptosRodada=0;
        printf("\nDigite algo para comecar a rodada\n");
        scanf("%d", &passar);
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\nJogador: ");   /*mostrar vez do jogador*/
        jogada=3;
        x=0;
        y=0;
        if(vezJog==1){ /*jogador escolhe a casa e a jogada*/
            permissao=0;
            while(permissao!=1){
                permissao=1;
                printf("Usuario");
                printf("\n\nDigite a coluna de sua jogada\n");
                scanf("%d",&x);
                printf("\nDigite a linha de sua jogada\n");
                scanf("%d",&y);
                printf("\nDigite 1 para S e 2 para O\n");
                scanf("%d",&jogada);
                /*verifica se a entrada do usuario é válida*/
                if(x<1 || x>3 || y<1 || y>3 || (jogada!=1 && jogada!=2)){
                    permissao=0;
                }
                else if(x==1 && y==1 && (ternario%10)!=0){
                    permissao=0;
                }
                else if(x==2 && y==1 && (ternario%100)/10!=0){
                    permissao=0;
                }
                else if(x==3 && y==1 && (ternario%1000)/100!=0){
                    permissao=0;
                }
                else if(x==1 && y==2 && (ternario%10000)/1000!=0){
                    permissao=0;
                }
                else if(x==2 && y==2 && (ternario%100000)/10000!=0){
                    permissao=0;
                }
                else if(x==3 && y==2 && (ternario%1000000)/100000!=0){
                    permissao=0;
                }
                else if(x==1 && y==3 && (ternario%10000000)/1000000!=0){
                    permissao=0;
                }
                else if(x==2 && y==3 && (ternario%100000000)/10000000!=0){
                    permissao=0;
                }
                else if(x==3 && y==3 && (ternario%1000000000)/100000000!=0){
                    permissao=0;
                }
                if(permissao==0){
                    printf("\n\nDigite as coordenadas de um numero valido!\n");
                }
            }
        }
        else{
            printf("Computador");
            /*Inteligencia do computador*/
            /*jogara S x=1 e y=1*/
            if((ternario%10000)/1000==2 && (ternario%10000000)/1000000==1 && ternario%10==0){
                    x=y=1;
                    jogada=1;
            }
            if((ternario%100)/10==2 && (ternario%1000)/100==1 && ternario%10==0){
                    x=y=1;
                    jogada=1;
            }
            if((ternario%100000)/10000==2 && (ternario%1000000000)/100000000==1 && ternario%10==0){
                    x=y=1;
                    jogada=1;
            }


            /*jogara S ou O x=2 y=1*/
            if((ternario%100000)/10000==2 && (ternario%100000000)/10000000==1 && (ternario%100)/10==0){
                x=2;y=1;
                jogada=1;
            }
            if((ternario%10)==1 && (ternario%1000)/100==1 && (ternario%100)/10==0){
                x=2;y=1;
                jogada=2;
            }


            /*jogara S x=3 y=1*/
            if((ternario%10)==1 && (ternario%100)/10==2 && (ternario%1000)/100==0){
                x=3;y=1;
                jogada=1;
            }
            if((ternario%100000)/10000==2 && (ternario%10000000)/1000000==1 && (ternario%1000)/100==0){
                x=3;y=1;
                jogada=1;
            }
            if((ternario%1000000)/100000==2 && (ternario%1000000000)/100000000==1 && (ternario%1000)/100==0){
                x=3;y=1;
                jogada=1;
            }

            /*jogara S ou O x=1 y=2*/
            if((ternario%100000)/10000==2 && (ternario%1000000)/100000==1 && (ternario%10000)/1000==0){
                x=1;y=2;
                jogada=1;
            }
            if((ternario%10)==1 && (ternario%10000000)/1000000==1 && (ternario%10000)/1000==0){
                x=1;y=2;
                jogada=2;
            }

            /*jogara O x=2 y=2*/
            if((ternario%10)==1 && (ternario%1000000000)/100000000==1 && (ternario%100000)/10000==0){
                x=2;y=2;
                jogada=2;
            }
            if((ternario%10000)/1000==1 && (ternario%1000000)/100000==1 && (ternario%100000)/10000==0){
                x=2;y=2;
                jogada=2;
            }
            if((ternario%100)/10==1 && (ternario%100000000)/10000000==1 && (ternario%100000)/10000==0){
                x=2;y=2;
                jogada=2;
            }
            if((ternario%1000)/100==1 && (ternario%10000000)/1000000==1 && (ternario%100000)/10000==0){
                x=2;y=2;
                jogada=2;
            }

            /*jogara S ou O x=3 y=2*/
            if((ternario%10000)/1000==1 && (ternario%100000)/10000==2 && (ternario%1000000)/100000==0){
                x=3;y=2;
                jogada=1;
            }
            if((ternario%1000)/100==1 && (ternario%1000000000)/100000000==1 && (ternario%1000000)/100000==0){
                x=3;y=2;
                jogada=2;
            }

            /*jogara S x=1 y=3 */
            if((ternario%1000)/100==1 && (ternario%100000)/10000==2 && (ternario%10000000)/1000000==0){
                x=1;y=3;
                jogada=1;
            }
            if((ternario%100000000)/10000000==2 && (ternario%1000000000)/100000000==1 && (ternario%10000000)/1000000==0){
                x=1;y=3;
                jogada=1;
            }
            if((ternario%10)==1 && (ternario%10000)/1000==2 && (ternario%10000000)/1000000==0){
                x=1;y=3;
                jogada=1;
            }

            /*jogara S ou O x=2 y=3*/
            if((ternario%100)/10==1 && (ternario%100000)/10000==2 && (ternario%100000000)/10000000==0){
                x=2;y=3;
                jogada=1;
            }
            if((ternario%10000000)/1000000==1 && (ternario%1000000000)/100000000==1 && (ternario%100000000)/10000000==0){
                x=2;y=3;
                jogada=2;
            }

            /*jogara S x=3 y=3*/
            if((ternario%10)==1 && (ternario%100000)/10000==2 && (ternario%1000000000)/100000000==0){
                x=3;y=3;
                jogada=1;
            }
            if((ternario%1000)/100==1 && (ternario%1000000)/100000==2 && (ternario%1000000000)/100000000==0){
                x=3;y=3;
                jogada=1;
            }
            if((ternario%10000000)/1000000==1 && (ternario%100000000)/10000000==2 && (ternario%1000000000)/100000000==0){
                x=1;y=3;
                jogada=1;
            }
            /*jogando "aleatoriamente"*/
            casa=1;
            if(x==0 && y==0 && jogada==3){
                for(i=1;i<10;i++){
                    j=i;
                    casa=1;
                    while(j>0){
                        casa=casa*10;
                        j--;
                    }
                    if((ternario%casa/(casa/10))==0){
                        if(i==1){
                            x=1;y=1;
                            jogada=1;
                        }
                        else if(i==2){
                            x=2;y=1;
                            jogada=2;
                        }
                        else if(i==3){
                            x=3;y=1;
                            jogada=1;
                        }
                        if(i==4){
                            x=1;y=2;
                            jogada=2;
                        }
                        else if(i==5){
                            x=2;y=2;
                            jogada=2;
                        }
                        else if(i==6){
                            x=3;y=2;
                            jogada=2;
                        }
                        if(i==7){
                            x=1;y=3;
                            jogada=1;
                        }
                        else if(i==8){
                            x=2;y=3;
                            jogada=2;
                        }
                        else if(i==9){
                            x=3;y=3;
                            jogada=1;
                        }
                    }
                }
            }
        }
         /*Marcando jogada e verificando se pontuou
            X1 Y1*/
            if (y==1){
                 if(x==1){
                     if (jogada==1){
                        /*jogou S*/
                        somaTab=somaTab+(jogada*1);
                        /*Verificando se ele pontuou*/
                        if((ternario%10000)/1000==2 && (ternario%10000000)/1000000==1){
                            ptosRodada++;
                        }
                        if((ternario%100)/10==2 && (ternario%1000)/100==1){
                            ptosRodada++;
                        }
                        if((ternario%100000)/10000==2 && (ternario%1000000000)/100000000==1){
                            ptosRodada++;
                        }
                     }
                     else{/*Jogou O */
                        somaTab=somaTab+(jogada*1);
                     }
                 }
                 /*X2 Y1*/
                else if(x==2){
                    if (jogada==1){/*jogou S*/
                        somaTab=somaTab+jogada*3;
                        /*Verificando se ele pontuou*/
                        if((ternario%100000)/10000==2 && (ternario%100000000)/10000000==1){
                            ptosRodada++;
                        }
                    }
                    else{/*jogou O*/
                        somaTab=somaTab+jogada*3;
                        if((ternario%10)==1 && (ternario%1000)/100==1){
                            ptosRodada++;
                        }
                    }
                }
                 /*X3 Y1*/
                else{
                    if (jogada==1){/*jogou S*/
                        somaTab=somaTab+jogada*3*3;
                        /*verificando se pontuou*/
                        if((ternario%10)==1 && (ternario%100)/10==2){
                            ptosRodada++;
                        }
                        if((ternario%100000)/10000==2 && (ternario%10000000)/1000000==1){
                            ptosRodada++;
                        }
                        if((ternario%1000000)/100000==2 && (ternario%1000000000)/100000000==1){
                            ptosRodada++;
                        }
                    }
                    else{/*jogou O*/
                        somaTab=somaTab+jogada*3*3;
                    }
                }
            }
            else if(y==2){
                /*X1 Y2*/
                if(x==1){
                    if (jogada==1){/*jogou S*/
                        somaTab=somaTab+jogada*3*3*3;
                        /*verificando se pontuou*/
                        if((ternario%100000)/10000==2 && (ternario%1000000)/100000==1){
                            ptosRodada++;
                        }
                     }
                     else{/*jogou O*/
                        somaTab=somaTab+jogada*3*3*3;
                        /*verificando se pontuou*/
                        if((ternario%10)==1 && (ternario%10000000)/1000000==1){
                            ptosRodada++;
                        }
                     }
                 }
                 /*X2 Y2*/
                 else if(x==2){
                    if (jogada==1){/*jogou S*/
                        somaTab=somaTab+jogada*3*3*3*3;
                     }
                     else{/*jogou O*/
                        somaTab=somaTab+jogada*3*3*3*3;
                        /*verificando se pontuou*/
                        if((ternario%10)==1 && (ternario%1000000000)/100000000==1){
                            ptosRodada++;
                        }
                        if((ternario%10000)/1000==1 && (ternario%1000000)/100000==1){
                            ptosRodada++;
                        }
                        if((ternario%100)/10==1 && (ternario%100000000)/10000000==1){
                            ptosRodada++;
                        }
                        if((ternario%1000)/100==1 && (ternario%10000000)/1000000==1){
                            ptosRodada++;
                        }
                     }
                 }
                 /*X3 Y2*/
                 else{
                     if (jogada==1){/*jogou S*/
                        somaTab=somaTab+jogada*3*3*3*3*3;
                        /*verifica se pontuou*/
                        if((ternario%10000)/1000==1 && (ternario%100000)/10000==2){
                            ptosRodada++;
                        }
                     }
                     else{/*jogou O*/
                        somaTab=somaTab+jogada*3*3*3*3*3;
                        /*verifica se pontou*/
                        if((ternario%1000)/100==1 && (ternario%1000000000)/100000000==1){
                            ptosRodada++;
                        }
                    }
                 }
            }
            else{
                /*X1 Y3*/
                if(x==1){
                    if (jogada==1){/*jogou S*/
                        somaTab=somaTab+jogada*3*3*3*3*3*3;
                        /*verificando se pontuou*/
                        if((ternario%1000)/100==1 && (ternario%100000)/10000==2){
                            ptosRodada++;
                        }
                        if((ternario%100000000)/10000000==2 && (ternario%1000000000)/100000000==1){
                            ptosRodada++;
                        }
                        if((ternario%10)==1 && (ternario%10000)/1000==2){
                            ptosRodada++;
                        }
                     }
                     else{/*jogou O*/
                        somaTab=somaTab+jogada*3*3*3*3*3*3;
                     }
                }
                /*X2 Y3*/
                else if(x==2){
                    if (jogada==1){/*jogou S*/
                        somaTab=somaTab+jogada*3*3*3*3*3*3*3;
                        /*verificando se pontuou*/
                        if((ternario%100)/10==1 && (ternario%100000)/10000==2){
                            ptosRodada++;
                        }
                     }
                     else{/*jogou O*/
                        somaTab=somaTab+jogada*3*3*3*3*3*3*3;
                        if((ternario%10000000)/1000000==1 && (ternario%1000000000)/100000000==1){
                            ptosRodada++;
                        }
                     }
                }
                /*X3 Y3*/
                else{
                    if (jogada==1){/*jogou S*/
                        somaTab=somaTab+jogada*3*3*3*3*3*3*3*3;
                        if((ternario%10)==1 && (ternario%100000)/10000==2){
                            ptosRodada++;
                        }
                        if((ternario%1000)/100==1 && (ternario%1000000)/100000==2){
                            ptosRodada++;
                        }
                        if((ternario%10000000)/1000000==1 && (ternario%100000000)/10000000==2){
                            ptosRodada++;
                        }
                     }
                     else{/*jogou O*/
                        somaTab=somaTab+jogada*3*3*3*3*3*3*3*3;
                     }
                }
            }
        /*Atualizando o Jogo:*/

        /*relendo a tabela depois da jogada*/
        parcial = somaTab;
        ternario=0;
        /*transformando a soma da tabela em um número ternario*/
        i=0; casa=1;
        if (parcial==1 || parcial==2){
            ternario=parcial;
        }
        else{
            while (parcial>2){
                int j=i;
                while(i>0){
                    casa=casa*10;
                    i--;
                }
                i=j;
                i++;
                ternario=ternario+(parcial%3)*casa;
                casa=1;
                parcial= parcial/3;
                if (parcial<3){
                    while(i>0){
                        casa=casa*10;
                        i--;
                    }
                ternario=ternario+(parcial*casa);
                }
            }
        }
        /*reescrevendo a Tabela...*/
        printf("\n\n\n");
        /*X1 Y1*/
        if((ternario%10)==2){
            printf(" O |");
        }
        else if((ternario%10)==1){
            printf(" S |");
        }
        else{
            printf("   |");
        }

        /*X2 Y1*/
        if((ternario%100)/10==2){
            printf(" O ");
        }
        else if((ternario%100)/10==1){
            printf(" S ");
        }
        else{
            printf("   ");
        }

        /*X3 Y1*/
        if((ternario%1000)/100==2){
            printf("| O ");
        }
        else if((ternario%1000)/100==1){
            printf("| S ");
        }
        else{
            printf("|   ");
        }

        printf("\n---+---+---\n");

        /*X1 Y2*/
        if((ternario%10000)/1000==2){
            printf(" O |");
        }
        else if((ternario%10000)/1000==1){
            printf(" S |");
        }
        else{
            printf("   |");
        }

        /*X2 Y2*/
        if((ternario%100000)/10000==2){
            printf(" O |");
        }
        else if((ternario%100000)/10000==1){
            printf(" S |");
        }
        else{
            printf("   |");
        }
        /*X3 Y2*/
        if((ternario%1000000)/100000==2){
            printf(" O ");
        }
        else if((ternario%1000000)/100000==1){
            printf(" S ");
        }
        else{
            printf("   ");
        }

        printf("\n---+---+---\n");

        /*X1 Y3*/
        if((ternario%10000000)/1000000==2){
            printf(" O |");
        }
        else if((ternario%10000000)/1000000==1){
            printf(" S |");
        }
        else{
            printf("   |");
        }

        /*X2 Y3*/
        if((ternario%100000000)/10000000==2){
            printf(" O |");
        }
        else if((ternario%100000000)/10000000==1){
            printf(" S |");
        }
        else{
            printf("   |");
        }
        /*X3 Y3*/
        if((ternario%1000000000)/100000000==2){
            printf(" O ");
        }
        else if((ternario%1000000000)/100000000==1){
            printf(" S ");
        }
        else{
            printf("   ");
        }
        /*Troca a vez do jogador se nenhum ponto for marcado; soma os pontos marcados; mostra os pontos marcados*/
        if (vezJog==1){
            if(ptosRodada!=0){
                jogPlacar+=ptosRodada;
                printf("\n\n\nO jogador marcou %d pontos nessa rodada\n", ptosRodada);
            }
            else{
                printf("\n\n\nNenhum ponto foi marcado nessa rodada\n");
                vezJog=2;
            }
        }
        else{
            if(ptosRodada!=0){
                compPlacar+=ptosRodada;
                printf("\n\n\nO computador marcou %d pontos nessa rodada\n", ptosRodada);
            }
            else{
                printf("\n\n\nNenhum ponto foi marcado nessa rodada");
                vezJog=1;
            }
        }
        /*Mostra o placar(exceto na ultima rodada)*/
        if(jogada!=9)
            printf("\nPlacar atual:\nJogador %d x %d Computador", jogPlacar, compPlacar);
        /*Controla 9 jogadas*/
        controle++;
    }
    printf("\n\nPontuacao final:\nJogador:%d    Computador:%d\n", jogPlacar, compPlacar);
    if(jogPlacar>compPlacar){
        printf("O jogador ganhou do computador!");
    }
    else if(jogPlacar<compPlacar){
        printf("O computador ganhou do jogador!");
    }else{
        printf("Houve um empate!");
    }
    return 0;
}
