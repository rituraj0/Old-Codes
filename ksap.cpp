#include<iostream>
#include<cstdio>
using namespace std;
int  wt[1005],p[1005],cost,maja,k;
int keep[1005][1005],v[1005][1005];

int main()
{
    int n,i,w,j,test,wm;


scanf("%d",&test);

while(test--)
{

scanf("%d%d",&n,&wm);



for(i=0;i<n;i++)
{scanf("%d",&wt[i+2]);
p[i+2]=wt[i+2];
}

for(w=0;w<=wm;w++)
{v[0][w]=0;
 v[1][w]=0;
}

for(i=2;i<=n+1;i++)
 for(w=0;w<=wm;w++)
{
keep[i][w]=0;
if(wt[i]<=w)
{ 
    if(v[i-2][w]<p[i]+v[i-2][w-wt[i]])
   { keep[i][w]=1;        
    v[i][w]=p[i]+v[i-2][w-wt[i]];
   }
  else
  v[i][w]=v[i-2][w];
}//a yaha ka hai 
else
v[i][w]=v[i-2][w];
}///end niche wal for
/*
cout<<"\nNOw pwrinting the matrix\n";

for(i=0;i<=n+1;i++)
{
  for(j=0;j<=wm;j++)
  cout<<v[i][j]<<"  ";
 cout<<endl;
}*/

cost=0;maja=0;
k=wm;

for(i=n+1;i>1;i--)
if(keep[i][k]==1)
{
//cost+=wt[i];
//keep[i][k]=0;
maja+=p[i];
k=k-wt[i];
}

printf("Hey stupid robber, you can get %d.\n",maja);

//scanf("%d%d",&wm,&n);

}//end while


return 0;
}



