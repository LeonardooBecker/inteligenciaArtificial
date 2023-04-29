#include <stdio.h>
#include <stdlib.h>

int main()
{
    int matriz[30][30];
    int i,j;
    int n=30;
    for(i=0;i<(30/2+1);i++)
    {
        for(j=0;j<(30/2+1);j++)
        {
            matriz[i][j]=n/(abs(i-j)+1);
            matriz[i][(n-j-1)]=n/(abs(i-j)+1);
            matriz[(n-i-1)][j]=n/(abs(i-j)+1);
            matriz[(n-i-1)][(n-j-1)]=n/(abs(i-j)+1);
        }
    }
        for(i=0;i<30;i++)
    {
        for(j=0;j<30;j++)
        {
            printf("%2d ",matriz[i][j]);
        }
        printf("\n");
    }
    
}