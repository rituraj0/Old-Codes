#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
    
    int a,b,c;
    
    scanf("%d%d%d",&a,&b,&c);
    
    while(a!=0 || b!=0 || c!=0)
    {
         
          
          if(b*2==a+c)
          printf("AP %d\n",c+(b-a) );
          else if(b*b== a*c)
          printf("GP %d\n",c*(b/a));
          
          scanf("%d%d%d",&a,&b,&c);
          
          }
          
      
          return 0;
          }   
