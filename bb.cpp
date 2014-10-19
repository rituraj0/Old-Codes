#include<iostream>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
int a[11],mx,maxc;
int main()
{
    int k,test,i,s,j,sm;
    
    scanf("%d",&test);
    
    while(test--)
    {
      for(i=0;i<11;i++)
      scanf("%d",&a[i]);
      
      scanf("%d",&k);  
      
    
        mx=0;maxc=0;
        
     for(i=1;i<2048;i++)
     {     
     sm=0;  
     s=0;             
      for(j=0;j<11;j++)
        if((i&(1<<j))>0)
          { sm+=a[j];
           s++;
           }
           
       if(sm>mx && s==k)
       {mx=sm;
       maxc=1;
       }
       else if(sm==mx && s==k)
       maxc++;                   
                        
         }
       
        printf("%d\n",maxc);
        
        }
        return 0;
        
        }
        
   
