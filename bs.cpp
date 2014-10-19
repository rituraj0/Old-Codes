#include<iostream>
#include<cstdio>
#include<cstring>
int main()
{

char s[500];
int a[500],l,i,j,temp,x;

while( scanf("%s",s)!=EOF) 
{
  if(strlen(s)==1 &&(s[0]=='0' || s[0]=='1'))
    printf("%s\n",s);
 else
 {
  l=strlen(s);
  for(j=0;j<l;j++)
  a[j+1]=s[j]-48;
 
   a[0]=0;
 
  temp=0,x=0;
 
  for(j=l;j>-1;j--)
  {
  x=a[j]*2+temp;
  a[j]=x%10;
  temp=x/10; 
  }
 
//bhai 2*n-2 hai
  if(a[l]!=0)
  a[l]=a[l]-2;
  else
  {
  a[l]=8;
  j=l-1;
  while(a[j]==0)
  {a[j]=9;
  j--;
  }
  a[j]=a[j]-1; 
  }
 

  if(a[0]==0)
  {
    for(j=1;j<l+1;j++)
    printf("%d",a[j]);
  }
  else
  {
   for(j=0;j<l+1;j++)
   printf("%d",a[j]);
   }
  printf("\n");

 }

}
}



