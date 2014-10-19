#include<iostream>
#include<cstdio>

typedef long long int lg;
using namespace std;
struct node
{
lg f[7];
}a[100005];

lg n;




void sort(lg l,lg r,lg x)
{
     lg p,i,j;
     node temp;
     if(l<r)
     {
            i=l;
            j=r+1;
            
            p=a[l].f[x];//bhai yaha finishing  time pe sort kar rahe hai
            do{
                   do i++;
                   while(a[i].f[x]<p && i<r);
                   
                   do j--;
                   while(a[j].f[x]>p);
                   
                   if(i<j)
                   {temp=a[i];
                   a[i]=a[j];
                   a[j]=temp;
                   }
                   
                   }while(i<j);
                   
               temp=a[l];
               a[l]=a[j];
               a[j]=temp;
               sort(l,j-1,x);
               sort(j+1,r,x);
               }
               
               }


bool chek(lg x,lg y)
{

for(lg i=0;i<6;i++)
 if(a[x].f[i]!=a[y].f[i])
  return false;

 return true;
}


void print()
{
lg i,j;

for(i=0;i<n;i++)
printf("%lld %lld %lld %lld %lld %lld \n",a[i].f[0],a[i].f[1],a[i].f[2],a[i].f[3],a[i].f[4],a[i].f[5]);

cout<<"\nUpar sorted printed\n";
}

int main()
{

lg test,i,j,cn;

scanf("%lld",&test);

while(test--)
{

 scanf("%lld",&n);

  for(i=0;i<n;i++)
    for(j=0;j<6;j++)
      scanf("%lld",&a[i].f[j]);
  
    for(j=0;j<6;j++)
      sort(0,n-1,5-j);


cout<<"After sorting the \n";
print();
  
  
  for(i=0;i<n;)
  {
     cn=1;
   j=i;//saving a copy of current
   

   if( (i+1)<n && chek(i,i+1) )
     {
         while( (i+1)<n && chek(i,i+1)  )
          {i++;
          cn++;}
         printf("%lld %lld %lld %lld %lld %lld %lld\n",a[j].f[0],a[j].f[1],a[j].f[2],a[j].f[3],a[j].f[4],a[j].f[5],cn);

      }
   else 
    {
       printf("%lld %lld %lld %lld %lld %lld %lld\n",a[i].f[0],a[i].f[1],a[i].f[2],a[i].f[3],a[i].f[4],a[i].f[5],cn);
         i++;
    }

   }//end for
  printf("\nsecond ab suru hoga\n");

}

return 0;
}
       


  
