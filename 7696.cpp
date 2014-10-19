#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
typedef long long int lg;

char r1(lg l)//return l charcter from the  string  first ie  vowel wala
{
char s[]="#aeiou";


lg k=l%5;

if(k==0)
return s[5];

return s[k];

}


char r2(lg l)//returns  l th charcter from  the string ie constant wala
{
char s[]="#bcdfghjklmnpqrstvwxyz";

lg k=l%21;

if(k==0)
 return s[21];

return s[k];

}


lg find1(char ch,lg k)//return the positon of the particular positio if the  kth occurance In firsts string
{ 
char s[]="#aeiou";
lg i;
for(i=1;i<6;i++)
    if(ch==s[i])
     return i+(k-1)*5;

}


lg find2(char ch,lg k)
{

 char s[]="#bcdfghjklmnpqrstvwxyz";
 lg i;

  for(i=1;i<=21;i++)
    if(ch==s[i])
      return i+(k-1)*21; 

}
int main()
{

char a[50005];
lg i,k,x,st,test,l;
char ch,c;


scanf("%lld",&test);
 
 while(test--)
{
 scanf("%s",a);

 l=strlen(a);

 lg ct[30]={0};
//cout<<"c   k   st   x   ch"<<endl;
 for(i=0;i<l;i++)
 {
   
  c=a[i]; 

  ct[c-97]=ct[c-97]+1;//asuming the value of  a is 97

  k=ct[c-97];  
 
  if(c=='a'||c=='e'||c=='i'||c=='o'||c=='u')
  st=1;
  else 
  st=2;

  if(st==1)
     { x=find1(c,k);
       ch=r2(x);
      }
   else if(st==2)
    { x=find2(c,k);
      ch=r1(x);
     }
   
  // cout<<c<<"   "<<k<<"   "<<st<<"   "<<x<<"   "<<ch<<endl;

  printf("%c",ch);
  }


printf("\n");

}
return 0;
} 
         
 

  

