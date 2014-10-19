#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
 int l,c;
int tc=0,tr=0,cn=0;
int i,j,r;   

char s[210],a[202][202];
scanf("%d",&c);



while(c!=0)
{
  scanf("%s",s);         

l=strlen(s);
r=l/c;


cn=0;

for(i=0;i<r;)
{

  for(j=0;j<c;j++)
  {a[i][j]=s[cn];
  cn++;
  }

  if(cn>l-1)
  break;

 i++;

  for(j=c-1;j>=0;j--)
  { a[i][j]=s[cn];
    cn++;
   }
 i++;

 if(cn>l-1)//bharne ke bad bhdh arhe hai and a cn index batata hai
 break;

}//end main for


//now prinutng

for(i=0;i<c;i++)
 for(j=0;j<r;j++)
  printf("%c",a[j][i]);
/*
  cout<<"The  matrix is\n";
  for(i=0;i<r;i++)
  {
      for(j=0;j<c;j++)
        cout<<a[i][j]<<"  ";
    cout<<endl;
 }
  */
  printf("\n");
  
  scanf("%d",&c);
  
}//end while

return 0;
}
