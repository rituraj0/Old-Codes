#include<iostream>
#include<cstdio>
long long int sm,mx,n,a[5999999],cn,cf,mn;
int main()
{
long long int i,test;

scanf("%lld",&test);
while(test--)
{
scanf("%lld",&n);

for(i=0;i<n;i++)
scanf("%lld",&a[i]);

cf=0;
cn=1;
mx=-99999999;
mn=0;
sm=0;

for(i=0;i<n;i++)
{sm=sm+a[i];

  if(sm-mn >mx)//sm-mn sum hai ab tak ka
   {mx=sm-mn;
   cf=cn;//bhai yaha nae assign kar rahe hai
   }
  else if(sm-mn==mx)
  cf=cf+cn;

  if(sm<mn)//mn to o to 0 to i tal hai na
 { mn=sm;
  cn=1;//all we han to do is to  mai ntian ha nbede 9d yhe mivni sum mf tha
 }
  else if(sm==mn)
 cn++;

}
/*rmx = -inf;
mn = 0; mnct = 1;
 
for(i=sum=0;i<n;i++)
{
	sum += A[i];
			
	if( sum - mn > rmx) rmx = sum-mn ,  rct = mnct;
	else if( sum - mn == rmx ) rct += mnct;
 
	if( sum < mn ) mn = sum ,  mnct = 1;
	else if( sum == mn ) mnct++;
}*/




printf("%lld %lld\n",mx,cf);
}

return 0;
}

