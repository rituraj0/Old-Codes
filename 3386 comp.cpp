#include<iostream>
#include<cstdio>
int main()
{
    
    char a[4],p[4];
    int tm=0,qs,sm,i;
  
   scanf("%d",&a[0]);
   
    while(a[0]!=EOF)
    {
        tm++;  
        qs=0; 
        sm=0;         
        for(i=1;i<3;i++)
        scanf("%d",&a[i]);
        
        for(i=0;i<3;i++)
        scanf("%d",&p[i]);
        
        for(i=0;i<3;i++)
        {
            if(a[i]!=0)
            {
            qs++;
            sm+=a[i]+(p[i]-1)*60;
            }
            
            }
            
          printf("%team %d: %d, %d\n",tm,qs,sm);
           scanf("%d",&a[0]);
           
           }
           
           return 0;
           }       
                                   
        
                 
    
