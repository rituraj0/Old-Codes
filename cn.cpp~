#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<cmath>
using namespace std;
int main()
{
 int  test,n,i;
 char s[50];
 float  x,mx,t;
 scanf("%d",&test);

 while(test--)
 {
  scanf("%d",&n);

 vector<float> tm;

  for(i=0;i<n;i++)
  { scanf("%s%f",s,&t);
   tm.push_back(t);
  }

   mx=0;
  sort( tm.begin(),tm.end() );

  for(i=0;i<n-1;i++)
  {
    x=tm[i+1]-tm[i]; 
   if(mx<x)
   mx=x;
  }

  x=tm[0]+360-tm[n-1];

   if(mx<x)
   mx=x;
 
   x=((360-mx)/360)*72*60;
   printf("%.0f\n",ceil(x));
 }

return 0;
}

  

  
   



