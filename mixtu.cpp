#include<iostream>
#include<cstdio>
int main()
{

 cin>>n;

 for(i=0;i<n;i++)
  cin>>a[i];

 int wt[n][n];

 for(i=0;i<n;i++)
 {
     for(j=0;j<n;j++)
      {
          if(i==j)
           wt[i][j]=a[i];
           else
             {wt[i][j]=
