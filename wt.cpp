#include<iostream>
#include<cstdio>
int nm;
int f(int n,int k)
{
if(n>=0)
 {
 if(n==1)
 return 1;//if 0 and 1 is saved

 int x=f(n-1,k+1);
 return (x+k)%n;

 } 

}

int main()
{
  while(1)
{
  std::cin>>nm;//ek kam kara ke inpur lena
  
  std::cout<<f(nm,1)<<"\n";
}
return 0;
}
