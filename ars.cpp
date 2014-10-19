#include<iostream>
#include<cstdio>
#include<cstring>
#include<cctype>
#include<vector>
#include<cstdlib>
using namespace std;
int main()
{
long long int  test;
long long int i,sm,k,j,n1,an,l,x;
char s[999999],aa[999999];
char ch;

gets(aa);
test=atoi(aa);

while(test--)
{


 gets(aa);

 gets(s);

l=strlen(s);

  //reading firstd inteer
  n1=0;an=0;
  i=0;

 while(s[i]==32)
  i++;
 
 if( isdigit(s[i]) )
 {
   while( isdigit(s[i]) )
  {
   x=s[i]-48;
   an=10*an+x;
   i++;
  }

 }//end this if


//bhai chalo paha red hi gaya
int cn=1;

for(j=i;s[j]!='=' && j<l;)
{
 //cout<<"\nIterationn "<<cn++<<endl;
  //cout<<"an "<<an<<endl;
 
  while(s[j]==32)
  j++;

 if(s[j]=='+')
 ch=s[j];
 else if(s[j]=='-')
 ch=s[j];
 else if(s[j]=='*')
 ch=s[j];
 else if(s[j]=='/')
 ch=s[j];
 
 j++;

 //cout<<"op is "<<ch<<endl;
 
 while(s[j]==32)
  j++;


 if( isdigit(s[j]) )
 {
   n1=0;
   while( isdigit(s[j]) )
   {
    x=s[j]-48;
    n1=10*n1+x;
    j++;
   }

  }//end if
  
 //cout<<"n1 is  "<<n1<<endl;
 if(ch=='+')
 an=an+n1;
 else if(ch=='-')
 an=an-n1;
 else if(ch=='*')
 an=an*n1;
 else if(ch=='/')
 an=an/n1;
  

 //j++;
  
}//end for

printf("%lld\n",an);

 }//end while

return 0;
}
  


