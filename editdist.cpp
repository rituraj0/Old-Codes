#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

short int inline mi(short int a,short int b,short int c)
 {
    if(a<=b && a<=c)
    return a;

    if(b<=a && b<=c)
    return b;
     
    if(c<=a && c<=b)
    return c;
}

int main()
{

int i,m,n,j,test;

for(scanf("%d",&test);test--; )
{
 char s[2005],t[2005];

 short int dp[2005][2005]={0};


  scanf("%s%s",s,t);
  m=strlen(s);
   for(i=m;i>0;i--)
     s[i]=s[i-1];
       s[m+1]='\0';
         s[0]=' ';
 
  n=strlen(t);
   for(i=n;i>0;i--)
     t[i]=t[i-1];
        t[n+1]='\0';     
          t[0]=' ';
 //mXn matrix
 
 

  for(i=0;i<=n;i++)
   dp[0][i]=i;
 
  for(i=0;i<=m;i++)
    dp[i][0]=i;

 //cout<<s<<"  "<<t<<endl;

 for(j=1;j<=n;j++)
  for(i=1;i<=m;i++)
   {
    if(s[i]==t[j])
     dp[i][j]=dp[i-1][j-1];
   else
    dp[i][j]=mi(dp[i-1][j]+1,dp[i][j-1]+1,dp[i-1][j-1]+1);
  }

 printf("%d\n",dp[m][n]);
  
}
return 0;
}








/*for(i=0;i<=m;i++)
  dp[i][0]=i;int LevenshteinDistance(char s[1..m], char t[1..n])
{
  // for all i and j, d[i,j] will hold the Levenshtein distance between
  // the first i characters of s and the first j characters of t;
  // note that d has (m+1)x(n+1) values
  declare int d[0..m, 0..n]

  clear all elements in d  // set each element to zero

  // source prefixes can be transformed into empty string by
  // dropping all characters 
  for i from 1 to m
  {
    d[i, 0] := i                    
  }

  // target prefixes can be reached from empty source prefix
  // by inserting every characters
  for j from 1 to n
  {
    d[0, j] := j                    
  }

  for j from 1 to n
  {
    for i from 1 to m
    {
      if s[i] = t[j] then  
        d[i, j] := d[i-1, j-1]       // no operation required
      else
        d[i, j] := minimum
                   (
                     d[i-1, j] + 1,  // a deletion
                     d[i, j-1] + 1,  // an insertion
                     d[i-1, j-1] + 1 // a substitution
                   )
    }
  }

  return d[m,n]
}*/
