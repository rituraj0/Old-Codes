#include<iostream>
#include<cstdio>
#include<cmath>
int main()
{

float r,u,an,rd,pi,g=9.806;

int test,i;

scanf("%d",&test);

for(i=1;i<=test;i++)
{

  scanf("%f%f",&r,&u);
  
  if( r > ((u/g)*u) )
  { printf("Scenario #%d: -1\n",i);
  continue;
  }

   rd=(asin( (g/u)*(r/u) ) )/2;
 
   pi=2*acos(0.00);

  an=(rd/pi)*(180);

  printf("Scenario #%d: %0.2f\n",i,an);
}

return 0;
}

  
 

