#include<iostream>
#include<cstring>
#include<cstdio>
#include<cctype>
int main()
{

char s[105][15];
int test,i,ep,n;

scanf("%d",&test);
while(test--)
{

  scanf("%d",&n);
 
  ep=-1;
 
  for(i=0;i<n;i++)
  {
     scanf("%s",s[i]);
   
   if( isalpha(s[i][0]) )
     ep=i;
  }

  if(ep==-1)
  {
   for(i=0;i<n;i++)
   printf("%s ",s[i]);
   
   printf("\n");
   continue;
  }

  
   for(i=ep+1;i<n;i++)
   printf("%s ",s[i]);

   printf("%s ",s[ep]);
  
   for(i=0;i<ep;i++)
   printf("%s ",s[i]);

  printf("\n");

}

return 0;
} 

