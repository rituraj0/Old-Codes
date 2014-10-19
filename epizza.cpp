#include<iostream>
#include<cstdio>
#include<math.h>
#include<cstdlib>
using namespace std;

int main()
{
int a,b,f;

scanf("%d",&f);

int hf=0,af=0,tf=0,tt=0,he=0;
int i,x,y,z,cn=0;

for(i=0;i<f;i++)
{
scanf("%d/%d",&a,&b);

if(a==1 && b==2)
hf++;
else if(a==1 && b==4)
af++;
else if(a==3 && b==4)
tf++;
}


x=hf;y=af;z=tf;

/*Total:= 1 + (Two div 2) + Three;
        Two:= Two mod 2;
 
        if Three < One then
                One:= One - Three
        else
                One:= 0;
 
        Total:= Total + (One div 4);
        One:= One mod 4;
 
        if Two = 1 then
        begin
                if One > 2 then
                        Total:= Total + 2
                else
                        Total:= Total + 1;
        end
        else
        begin
                if One > 0 then Total:= Total + 1
        end;
        writeln(Total);*/

tt=1+(hf/2)+tf;//1 to uslelia chahia

hf=hf%2;

if(tf<af)
 af=af-tf;
else
 af=0;

tt=tt+af/4;
af=af%4;

if(hf==1)
   {
     if(af>2)
           tt=tt+2;
      else
         tt=tt+1;
    }
 else
    {
         if(af>0)
          tt=tt+1;
    }

printf("%d\n",tt);

return 0;
}





