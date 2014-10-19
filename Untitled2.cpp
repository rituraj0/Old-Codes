#include<stdio.h>
int main(){long long int s=0,i,t;
scanf("%d",&t);
while(t--)
{scanf("%lld",&i);
if(i>0)s+=i;
}
printf("%lld\n",s);
scanf("%d",&t);return 0;} 
