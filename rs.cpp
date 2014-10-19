#include<iostream>
#include<cstdio>
int pr[9000000]={0};
int a[500001]={0};


int main()
{
    int i,x,y;
    
    for(int m=1;m<500001;m++)
    {
            
      x=a[m-1]-m;
      y=a[m-1]+m;
      
      if(x>0 && pr[x]==0)
      {a[m]=x;
      pr[a[m]]=1;
      }
      else
      { a[m]=y;
      pr[a[m]]=1;
      }  
      
      }
      
      
      scanf("%d",&i);
      while(i!=-1)
      {
                  printf("%d\n",a[i]);
                  scanf("%d",&i);
                  }
                  
                  
                  return 0;
                  }   
            
               
 
