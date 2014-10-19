#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
typedef long long int lg;
int match(char s[])
{
int l,m;
char p[]="FBI";

l=strlen(s);
m=strlen(p);

if(l<m)
return 3;

//cout<<"\nMatching detaila\n";
//cout<<l<<"  "<<m<<endl;
int mila=0,i,j,cn;

for(i=0;(i<l-m+1)&&(mila==0);i++)
{
 cn=0;
 for(j=0;j<m;j++)
  if(s[i+j]==p[j])
  cn++;

 if(cn==m)
 mila=2;

}
//cout<<s<<"    "<<fs<<"  "<<mila<<endl;
return mila;

}


int main()
{
//23 + 47 = machula
char  a[15];
int i,cn=0;



 for(i=1;i<=5;i++)
 {
  cin>>a; 
 if(match(a)==2)
  {printf("%d\n",i);cn++;
   }


 }

  if(cn==0)
 printf("HE GOT AWAY!\n");
return 0;
}
