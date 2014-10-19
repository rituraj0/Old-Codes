#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
typedef long long int lg;
using namespace std;
char st[5005],sp[5005],n;//n is strlen(st)

lg dp[5005]={0};

lg df(lg i)//aisa karte hai left se right ki  taraf chalte hai
{

 if(i>n-1)
 return 0;//q ki waha hum i+1 n i+2 call kar rahe hai
 
  if(i==n-1)
  return 1;


 if(dp[i]!=0)
   return dp[i];

 lg cool=0,x=0,y=0,vl=0;
 
 
 if(i<n-1 && st[i]!='x' && st[i+1]!='x')//matlab bad me atleat do bache hai
   {
    char a[3];
    a[0]=st[i];
    a[1]=st[i+1];
    a[2]='\0';
    vl=atoi(a);
   }

 if(i==n-2 && vl>=1 && vl<=26)//jab cool hai to 1 retunrn karenge na
 return 2;

 if(i==n-2 && (st[i]=='x' || st[i+1]=='x') )
  return 1;
 

 
  x=df(i+1);//agar a ek digit hia to isko chhorkar aaage wala ko call karo

  if(vl>=1 && vl<=26)
   y=df(i+2);//dp(i+2) to apne aap hi 0 ho jaega

 dp[i]=x+y;
 
       
return dp[i];


}

lg icall()//it is invoked for  initial call  aim  05 nahi aan a dea hai not a valid character
{

 // cout<<"Intial is sp \n"<<sp<<"   "<<strlen(sp)<<endl;

  int i,cn;

 for(i=1;i<n;i++)
  if(sp[i]=='0' && sp[i-1]>'2')
   return 0;


 for(i=1;i<n;i++)
  if(sp[i]=='0')
   sp[i-1]='x';

  //cout<<"After x is sp\n"<<sp<<"  "<<strlen(sp)<<endl;
 cn=0;

 for(i=0;i<n;i++)
 {
   if(sp[i]!='0')
    {st[cn]=sp[i];
    cn++;
    }
  }

  st[cn]='\0';

 //cout<<"st[] is   \n"<<st<<"   "<<strlen(st)<<endl;

 n=strlen(st);

  return df(0);
}

  


int main()
{
 scanf("%s",sp);//sp a copy of string
  int i;
 while(sp[0]!='0')
 {
 n=strlen(sp);
  
  for(i=0;i<=n;i++)
  dp[i]=0;

 cout<<icall()<<endl;;

 scanf("%s",sp);
 }

return 0;
}


