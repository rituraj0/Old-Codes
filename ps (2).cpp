
#include<iostream>
using namespace std;
int main()
{
    int n,i,j,spoon,c,r;
    char a[101][101];
    cin>>n;
    while(n!=0)
    {n=n-1;
   cin>>r>>c;
    spoon=0;
    
    for(i=0;i<r;i++)
     for(j=0;j<c;j++)
       cin>>a[i][j];

     for(i=0;i<r;i++)
     {
    for(j=0;j<c;j++)
      {
                         if(a[i][j]=='S' || a[i][j]=='s')
                         if(a[i][j+1]=='P' ||a[i][j+1]=='p')
                         if(a[i][j+2]=='O' ||a[i][j+2]=='o')
                         if(a[i][j+3]=='O' ||a[i][j+3]=='o' )
                         if(a[i][j+4]=='N' ||a[i][j+4]=='n')
                              spoon++;
                              
                            if(a[i][j]=='S' || a[i][j]=='s')
                            if(a[i+1][j]=='P' || a[i+1][j]=='p')
                            if(a[i+2][j]=='O' || a[i+2][j]=='o')
                            if(a[i+3][j]=='O' || a[i+3][j]=='o' )
                            if(a[i+4][j]=='N' || a[i+4][j]=='n')
                              spoon++; 

                              
                                    
                       
                  }
                  }
                  

                if(spoon)
                cout<<"There is a spoon!\n";
                else
                cout<<"There is indeed no spoon!\n";
                
                }
            
              
             return 0;
             }   

                                 
