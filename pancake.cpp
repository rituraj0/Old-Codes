#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<climits>
using namespace std;

float av[100],rc,ic;//rc recipe count  ..ic intergernt count .... tp[] check for the remaining in the aaray

float rd[105][105];//recipe demanded

long  check(int k)//check for tha Kth recipe how it will return
{
 
 float x;
int i; 

long mn=LONG_MAX;
 
 for(i=0;i<ic;i++)
 {
   x=av[i]/rd[k][i];
   
  if(floor(x)<mn)
  mn=x;
 }


return mn;

}
   

int main()
{

 cin>>ic>>rc;

 while(ic!=0 || rc!=0)
 {
 int i,j;
 float x;
 
 for(i=0;i<ic;i++)
  cin>>av[i];
 
 

 for(i=0;i<rc;i++)
  for(j=0;j<ic;j++)
  { cin>>x;
    rd[i][j]=x/10.0f;
  }
   // cin>>rd[i][j];


  long  mx=-1,xt;
  int in=0;
 
    for(i=0;i<rc;i++)
     {  
      xt=check(i);
      
      if(xt>mx)
        {mx=xt;
         in=i+1;
      }
       
   }


cout<<in<<" "<<mx<<endl;
cin>>ic>>rc;
}
 return 0;
}
   

 /*
20 20 20

5 10 1

2 1 3
*/
