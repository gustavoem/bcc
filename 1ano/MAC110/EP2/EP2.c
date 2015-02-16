#include <stdio.h>
double frac(double num){
    num=num-(int)num;
    return num;
}
double modulo(double num){
    if(num<0)
        num*=-1;
    return num;
}
double sen(double num){
    int cond=1, i; double sum=0,term;
    term=num;
    for (i=3; cond!=0; i+=2){
        sum+=term;
        term=(-1)*term*(num*num)/((i)*(i-1));
        if(term<0){
            if(term*(-1)<0.00000001)
                cond=0;
        }
        else{
        if(term<0.00000001)
                cond=0;
        }
    }
    return sum;
}

int main(){
    double b, x,y;
    int i, n;
    b=0.44551529893;
    printf("Digite a quantidade n de numeros a serem gerados:");
    scanf("%d",&n);
    for(i=1;i<=n;i++){
        b=frac(7*7*7*7*(7+b)*modulo(sen(b)));
        printf("%.17lf\n",b);
    }
    return 0;
}
