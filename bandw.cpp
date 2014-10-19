#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int main()
{

char a[505],b[505];
int i,cn,l,bada;

scanf("%s%s",a,b);

while(a[0]!='*' && b[0]!='*')
{
l=strlen(a);

cn=0;
bada=0;

for(i=0;i<l;)
{

 bada=0;
 
 while(a[i]!=b[i] && i<l)
 {i++;
 bada=1;
 }

 if(bada==1)
  cn++;

  
 while(a[i]==b[i] && i<l)
 i++;

}

printf("%d\n",cn);
scanf("%s%s",a,b);
}

return 0;
}
