#include<iostream>
#include<cstdio>
#include<cstring>
int main()
{
    
int c;
char s[210],a[202][202];
scanf("%d",&c);

int l,c;

while(c!=0)
{
  scanf("%s",s);         

l=strlen(s);
r=l/c;

int tc=0,tr=0,cn=0;

for(i=0;i<r;)
{
  for(j=0;j<c;j++)
  {a[j]=s[cn];
  cn++;
  }

  if(cn>l)
  break;



  for(j=c-1;j>=0;j--)
  { a[j]=s[cn];
    cn++;
   }

if(cn>l)
break;

}//end main for


//now prinutng

for(i=0;i<c;i++)
 for(j=0;j<r;j++)
  printf("%c",a[i][j]);
  
  printf("\n");
  
  scanf("%d",&c);
  
}//end while

return 0;
}
