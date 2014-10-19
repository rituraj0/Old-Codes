#include<iostream>
#include<cstdio>
#include<cstring>
int main()
{

char  s[406];
int n,l,t,i,j;
int p[205]={0};
int c,r,tr,k;
scanf("%d",&c);
while(c!=0)
{
scanf("%s",s);

l=strlen(s);

r=l/c;

p[0]=0;
tr=1;

for(k=1;tr<r;k++)
{
p[tr]=2*k-1;
tr++;
if(tr>r-1)
break;

p[tr]=2*k;
tr++;
if(tr>r-1)
break;

}


for(i=0;i<c;i++)//number of ciloml
{
  for(j=0;j<r;j++)//number of rows
{
 printf("%c",s[p[j]] );

if(j%2==0)
p[j]--;
else
p[j]++;
}

}


scanf("%d",&c);
}

return 0;
}
