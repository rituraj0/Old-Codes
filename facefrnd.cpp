#include<iostream>
#include<cstdio>
int fid[5999999]={0},ffid[5999999]={0},tt[599999];
int main()
{
   // printf("COOL %d  %d",fid[9],ffid[69]);
   
   int n;
   
   int j,k,c=0,x;
   
   scanf("%lld",&n);
   
for(j=0;j<n;j++)//enter the friend list
{
   scanf("%d",&tt[c]);
   fid[tt[c]]=1;
   c++;

   scanf("%d",&m);

 for(k=0;k<m;k++)
 {
  scanf("%d",&tt[c]);
   ffid[tt[c]]=1;
   c++;
 }//end inner for
}
 
  
  
                  
   
   
   
   
   
   
   
   
   
   
   
   
    system("pause");
    return 0;
}
