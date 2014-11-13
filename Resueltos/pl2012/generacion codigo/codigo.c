#include <stdio.h>
int n;
int curr;
int main(){
printf("introduce numero : ");
scanf("%d",&n);
printf("%d",n);
printf(" == ");
curr = 2 ;
etiqueta_0:
{
int temp0;
temp0 = curr <= n;
if(!temp0) goto etiqueta_1;
int d;
int temp1;
temp1 = n / curr;
d = temp1 ;
int temp2;
temp2 = d * curr;
int temp3;
temp3 = temp2 == n;
if(!temp3) goto etiqueta_2;
{
printf("* ");
printf("%d",curr);
int temp4;
temp4 = n / curr;
n = temp4 ;
}
goto etiqueta_3;
etiqueta_2:
{
int temp5;
temp5 = curr + 1;
curr = temp5 ;
}
etiqueta_3:
{}
}
goto etiqueta_0;
etiqueta_1:
{}
printf("\n");

}

