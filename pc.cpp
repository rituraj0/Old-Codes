#include<iostream>
#include<climits>
using namespace std;
int m[10000];
struct coin
{
  int value;
  int weight;
}s1[1000];
 

int  main()
{
  int t,w0,w1,n,temp,temp1,i,j,w;
  cin>>t;
  while(t--)
    {
      cin>>w0>>w1;
      w=w1-w0;
      cin>>n;
      temp1=INT_MAX;
      
       for(i=1;i<=n;i++)
          {
             cin>>s1[i].value>>s1[i].weight;
               if(temp1>s1[i].weight)
                 temp1=s1[i].weight;//min value note kiya
          }
      
      for(i=0;i<temp1;i++)
      m[i]=0;

      for(i=1;i<=w;i++)
        {
          temp1=INT_MAX;
             for(j=1;j<=n;j++)
              {
                 temp=0;
                   if(i-s1[j].weight>=0)
                     {
                        if(m[i-s1[j].weight]>0 || i==s1[j].weight)
                        temp=m[i-s1[j].weight]+s1[j].value;
                      }
 
                  if(temp<temp1 && temp!=0) 
                  temp1=temp;
               }
 
         if(temp1==INT_MAX)
         m[i]=0;
         else
         m[i]=temp1;
        }
 
      if(!m[w])
      cout<<"This is impossible."<<endl;
      else
      cout<<"The minimum amount of money in the piggy-bank is "<<m[w]<<"."<<endl;
    
  }
}
