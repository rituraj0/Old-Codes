#include<iostream>
char s[2000];
#include<cstdio>
#include<cstring>
int main()
{

 int test;

 scanf("%d",&test);
 while(test--)
 { 
   scanf("%s",s);
 int l;

  l=strlen(s);
  char d=s[l-1];

 if( (d-48)%2==0)
  printf("Mandark\n");
 else
  printf("Dexter\n");

 }


return 0;

}

 
