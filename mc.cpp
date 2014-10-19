#include<iostream>
#include<cstdio>
int a[500001]={0};
int ck(int m )
{
    int p;
    int x,y,mila,i;
  p=ck(m-1);
  x=p-m;
  y=p+m;
  
  mila=0;
  for(i=0;i<m;i++)
  {if(a[i]==x)
    {mila=1;
     break;
     }
  }
  
  if(mila==0 && x>0)
  a[m]=x;
  else
  a[m]=y;
  
  return a[m];
}
  


int main()
{
    
 int m;
 
 scanf("%d",&m);
 while(m!=-1)
 {
             printf("%d\n",ck(m));
             scanf("%d",&m);
             }
             
             return 0;
             }   
