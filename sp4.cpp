#include<iostream>
#include<conio.h>
int main()
{
    int n,i,j,r,c;
    
    char a[20][20],ch;
    
    scanf("%d%d",&r,&c);
    //r++;
    //c++;//shayad enter ke karan ais ho raha hai s
    
    for(i=0;i<r;i++)
     {
     for(j=0;j<c;j++)
     { scanf("%c",&a[i][j]);
     }
     scanf("%c",&ch);
     }
      
      printf("\n\n%d  %d\n",r,c);
      
      for(i=0;i<r;i++)
      for(j=0;j<c;j++)
      printf("%c",a[i][j]);
      
      scanf("%d",&n);
      return 0;
      }
