#include<iostream>
#include<cstdio>
#include<cstdlib>
typedef long long int lg;


/*lg modulo(lg a,lg b,lg c)
{
    lg x=1,y=a; // long long is taken to avoid overflow of intermediate results
    while(b > 0){
        if(b&1){
            x=(x*y)%c;
        }
        y = (y*y)%c; // squaring the base
        b /= 2;
    }
    return x%c;
}*/




lg mul(lg a,lg b,lg c){
    lg x = 0,y=a%c;
    while(b > 0){
        if(b%2 == 1){
            x = (x+y)%c;
        }
        y = (y*2)%c;
        b /= 2;
    }
    return x%c;
}

lg mod(lg a,lg b,lg c){
    lg x=1,y=a; 
    while(b > 0){
        if(b%2 == 1){
            x=mul(x,y,c);
        }
        y = mul(y,y,c); 
        b /= 2;
    }
    return x%c;
}

bool miller(lg p,lg iteration)
 {
    if(p<2){
        return false;
    }
    if(p!=2 && p%2==0){
        return false;
    }
     lg s=p-1;
    while(s%2==0){
        s/=2;
    }
    for(lg i=0;i<iteration;i++){
        lg  a=rand()%(p-1)+1,temp=s;
        lg mo=mod(a,temp,p);
        while(temp!=p-1 && mo!=1 && mo!=p-1){
            mo=mul(mo,mo,p);
            temp *= 2;
        }
        if(mo!=p-1 && temp%2==0){
            return false;
        }
    }
    return true;
}



int main()
{
 lg n;
 int test;
 scanf("%d",&test);
   while(test--)
  {
    scanf("%lld",&n);
   if (miller(n,50))
    printf("YES\n");
   else
     printf("NO\n");
 }

 return 0;
}

