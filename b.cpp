#include<iostream>
#include<cstdio>
#include<math.h>
#include<cstdlib>
using namespace std;
int main()
{
int a,b,f;
//scanf("%d/%d",&a,&b);
//printf("\n\n%d/%d",a,b);

scanf("%d",&f);

int hf=0,af=0,tf=0,tt=0,he=0;
int i,x,y,z,cn=0;

for(i=0;i<f;i++)
{
scanf("%d/%d",&a,&b);

if(a==1 && b==2)
hf++;
else if(a==1 && b==4)
af++;
else if(a==3 && b==4)
tf++;
}


x=hf;y=af;z=tf;


cn=tf;//3/4 kahatam
he=tf;

cn+=hf/2+hf%2;

he+=(hf%2)*2;


if(af>he)
cn+=(af-he)/4;

if((af-he)%4!=0)
cn++;

cn++;//for himself
printf("%d\n",cn);

return 0;
}




