#include<iostream>
#include<cstdio>
using namespace std;

int gcd(int a,int b)
{
if(b==0)
 return a;
else
 return gcd(b,a%b);
}


int main()
{

int test,a,b,c,ac,bc,cc,mv1,mv2;

scanf("%d",&test);

while(test--)
{

scanf("%d%d%d",&ac,&bc,&cc);

if(cc>ac&&cc>bc)
   {printf("-1\n");continue;}
else if(cc==0)
   {printf("0\n");continue;}
else if(cc==ac||cc==bc)
   {printf("1\n");continue;}
else if(cc%gcd(ac,bc)!=0)
   {printf("-1\n");continue;}

//pahle a ko bhar 

mv1=0;
a=0;b=0;

cout<<"Pahuch gaya hai Post  1\n";
int i=0;
while((a!=cc)&&(b!=cc)&&(i<3))
{

 printf("In outer a is %d b is %d and cc is %d\n",a,b,cc);
 if(a==0)
 {a=ac;
  mv1++;
  }

 if(b==bc)
  {b=0;
   mv1++;
  }
 
 while( (a!=0)&&(b!=bc)&&(a!=cc)&&(b!=cc)&&(i<3) )
 {  
    if(b+a>=bc)
    { b=bc;
    a=a-(bc-b);
       if(a==cc||b==cc)
        i=4;
    }
    if(b+a<bc)
    {a=0;
    b=b+a;
      if(a==cc||b==cc)
        i=4;
    }
  printf("In INNER a is %d b is %d and bc is %d\n",a,b,bc);
 }
  
  mv1++;
}
   
 cout<<"Pahuch gyaa hai post 2\n";
 
//b ko karna hai
mv2=0;
a=0;b=0;

while(a!=cc && b!=cc)
{


 if(b==0)
 {b=bc;
  mv2++;
  }
 else if(a==ac)
  {a=0;
   mv2++;
  }
 
 while(b!=0 && a!=ac)
 {
    if(b+a>=ac)
    { a=ac;
    b=b-(ac-a);
    }
    else
    {b=0;
    a=b+a;
    }
 }
  
  mv2++;
}


if(mv1>mv2)
printf("%d  \n",mv1);
else
printf("%d  \n",mv2);

}


return 0;
}


