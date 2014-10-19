#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
 
void print_solution(int n,int x[]){
    int i,j;
    char c[100][100];
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            c[i][j]='X';
        }
    }
    for(i=1;i<=n;i++)
    {
        c[i][x[i]] ='Q';
    }
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            printf("%c\t",c[i][j]);
        }
    printf("\n");
    }
}
     
int place(int x[],int n){
 
int i;
    for(i=1;i<n;i++)
    {
        if((x[i] == x[n]) || (i-x[i] == n-x[n]) || (i+x[i]==n +x[n]))
        {
            return 0;
        }
    }
    return 1;
}
 
void nqueens(int n){
    int x[100],count=0,k=1;
 
    x[k] = 0;
     
    while(k != 0)
    {
        x[k] +=1;
        while((x[k] <= n) && ( !place(x,k)))
        {
            x[k] +=1;
        }
        if(x[k] <= n)
        {
            if(k == n)
            {
                count++;
                printf("solution:%d\n",count);
                print_solution(n,x);
            }
            else
            {
                k++;
                x[k]=0;
            }
        }
        else
        {
            k--;
        }
         
    }
}
int main()
{
    int n;
    printf("enter number of queens\n");
    scanf("%d",&n);
     
    nqueens(n);
     getch();
    return 0;
}
