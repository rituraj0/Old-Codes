#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
typedef long long int lg;
using namespace std;
lg a[15000],b[15000],n1,n2;
lg ca[15000],cb[15000],cn;//cn denotes the crosssings  of the numbers  obvouid it 'll same for both

lg sr(lg x)
{
  lg ub=n2-1,lb=0,m;

  while(ub >= lb)
 {
   
  m=(ub+lb)/2;

  if(b[m]>x)
   ub=m-1;
  else if(b[m]<x)
   lb=m+1;
  else
    return m;
  }

 return -1;
}


int main()
{
lg i,j,sm1,sm2,sa,sb,sm,cv,x;
   
 scanf("%lld",&n1);
  
 while(n1!=0)
 {
   

   for(i=0;i<n1;i++)
   scanf("%lld",&a[i]);

  
   for(i=0;i<12000;i++)
   {ca[i]=-1; cb[i]=-1;
   }
   
 

   scanf("%lld",&n2);
  
   for(i=0;i<n2;i++)
   scanf("%lld",&b[i]);
   
  

//niche we are searching for the  values in the 

  cn=0;
  ca[cn]=cb[cn]=0;
  cn++; 
 
for(i=0;i<n1;i++)
 {
  if(sr(a[i])!=-1)
  {x=sr(a[i]);
   ca[cn]=i;
   cb[cn]=x;
   cn++;
  }
 }//now crsosings are marked 



//chal upar cool hai


//above we are checkiing wheterhe t it is found or nor

 
 
 sa=sb=sm1=sm2=sm=0;//total sum


 for(cv=0;cv<cn;cv++)//dekh bhaoi dono ke number of crossings same hi honge
 {

  sa=ca[cv];
  sm1=0;
  for(i=sa;i<ca[cv+1];i++)//sum upto next crossings(croosing not included)
  sm1+=a[i];
 
   
  sb=cb[cv];
  sm2=0;

  for(i=sb;i<cb[cv+1];i++)
  sm2+=b[i];
 
  if(sm1>sm2)
   sm=sm+sm1;
  else
   sm=sm+sm2;

 }
  
   
  //agar ab koe bacha rah gaya ho 

  sm1=0;
 
  for(i=ca[cn-1];i<n1;i++)
  sm1+=a[i];

  sm2=0;
  for(i=cb[cn-1];i<n2;i++)
  sm2+=b[i];

 if(sm1>sm2)
   sm=sm+sm1;
  else
   sm=sm+sm2;

printf("%lld\n",sm);

 scanf("%lld",&n1);

}

return 0;

}




 
  

