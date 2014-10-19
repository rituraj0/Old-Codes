#include<iostream>
int main()
{
    int n,i,j,spoon,c,r;
    char a[101][101];
    scanf("%d",&n);
    while(n--)
    {scanf("%d%d",&r,&c);
    spoon=0;
    
    for(i=0;i<r;i++)
     for(j=0;j<c;j++)
       scanf("%c",a[i][j]);
     
     for(i=0;i<r;i++)
      for(j=0;j<c;j++)
      {
                if(a[i][j]=='S' ||a[i][j]=='s')
                  {
                    if(a[i][j+1]=='P' ||a[i][j+1]=='p')//NIche bhai
                      {
                         if(a[i][j+2]=='O' ||a[i][j+2]=='o')
                         if(a[i][j+3]=='O' || a[i][j+3]=='o' )
                         if(a[i][j+4]=='N' ||a[i][j+1]=='n')
                              spoon++;
                              
                              }
                    else if( a[i+1][j]=='P' || a[i+1][j]=='p')
                         {  if(a[i+3][j]=='O'|| a[i+2][j]=='o')
                            if(a[i+3][j]=='O' || a[i+3][j]=='o' )
                            if(a[i+4][j]=='N' ||a[i+4][j]=='n')
                              spoon++; 
                              }
                              
                                    
                  }     
                  }//chalo for 
                  
                if(spoon)
                printf("There is a spoon!\n");
                else
                printf("There is indeed no spoon!\n");
                
                }
            
            scanf("%d",&n);    
             return 0;
             }   

                                 
