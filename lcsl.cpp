#include<iostream>
#include<cstring>
char x[100],y[100],a[100],bt[100];
int c[100][100];
char b[100][100];
void print(int,int);

int main()
{
    scanf("%s",a);
    scanf("%s",bt);
    
int  m,n,i,j;

    m=strlen(a);
    n=strlen(bt);
    
    for(i=0;i<m;i++)
    x[i+1]=a[i];
    
    for(i=0;i<n;i++)
    y[i+1]=bt[i];
    
   
    
    for(i=1;i<=m;i++)
     c[i][0]=0;
     
     for(j=0;j<=n;j++)
      c[0][j]=0;
      
      for(i=1;i<=m;i++)
       for(j=1;j<=n;j++)
       {
        if(x[i]==y[j])
        {c[i][j]=c[i-1][j-1]+1;
        b[i][j]='<';
        }
        else if(c[i-1][j]>=c[i][j-1])
        {c[i][j]=c[i-1][j];
         b[i][j]='^';
         }
         else
         {c[i][j]=c[i][j-1];
         b[i][j]=' ';
         }
         
         }
         
         
    print(m,n);
    printf("\n\n");
    system("pause");
    return 0;
}


void print(int i,int j)
{
     if(i==0||j==0)
     return ;
     
       if(b[i][j]=='<')
          {
           print(i-1,j-1);
           printf("%c",x[i]);
          }
        else if(b[i][j]=='^')
         print(i-1,j);
       else
        print(i,j-1);
       
       }                         
    
