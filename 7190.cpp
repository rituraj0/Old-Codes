#include<iostream>
#include<cstring>
#include<cstdio>
typedef long long int lg;
using namespace std;
lg gc(lg n,lg m)
    { 
        if(m<=n && n%m == 0)
	   return m;
	  if(n < m)
	   return gc(m,n);
	  else
	   return gc(m,n%m);
  }
 

int main()
{
 char s[25];
  lg lc=1,i,j,k,n,gl;
 
 scanf("%s",s);
 
 while(s[0]!='*')
 {

 i=0;
 while(s[i]=='N'&&i<strlen(s))
   i++;
  
 lc=i+1; //q ki uske inedx pa ho rha hai
 


 for(i=i+1;i<strlen(s);i++)
    if(s[i]=='Y')
    {j=i+1;    
     lc=(lc*j)/gc(lc,j);   
    }

 gl=0;
  
 for(i=0;i<strlen(s);i++)
 {  
       j=i+1;
     if(lc%j==0)
       if(s[i]=='N')
         gl=1;
    
  }//end for

 if(gl==1)
 printf("-1\n");
 else
 printf("%lld\n",lc);

 scanf("%s",s);
}

return 0;
}   
   
/*  j=i+1;
 
 while(s[j]=='N'&&j<n )
    j++;
 mila2=j;
 
 if(i<n && j<n)//man leki kow mila hi nahi
 lc=(i*j)/gc(i,j);
  */
