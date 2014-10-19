#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
typedef long long int lg;
char  pt[5999999],tt[5999999];
lg  pi[5999999],m,n,q,k;

inline void pr()
{
 pi[1]=0;
 k=0;
 
for(q=2;q<=m;q++)
{
 
 while(k>0 && pt[k+1]!=pt[q])
 k=pi[k];

 if(pt[k+1]==pt[q])
  k=k+1;
 
 pi[q]=k;
}
}


int main()
{

lg i,q,k,p,in;

while( (scanf("%lld",&in) )!=EOF)
{
 
 scanf("%s%s",pt,tt);

/// reapribg the [attern
 m=strlen(pt);

 for(i=m;i>=0;i--)
 pt[i]=pt[i-1];

 pt[m+1]='\0';

//reapting the tt
 n=strlen(tt);

 for(i=n;i>=0;i--)
 tt[i]=tt[i-1];

 tt[n+1]='\0';

//do br abid ] yiksdhn


pr();

//above that finctiom is called

q=0;

lg cn=0;

  for(i=1;i<=n;i++)
    {
       while(q>0 && pt[q+1]!=tt[i])
        q=pi[q];
      
        if(pt[q+1]==tt[i])
          q=q+1;
      
       if(q==m)
           {cout<<i-m<<endl;
            q=pi[q];
            cn++;      
           }
   }//end for
 if(cn==0)
  cout<<endl;

}
  return 0;
}       
