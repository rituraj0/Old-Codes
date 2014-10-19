#include<iostream>
#include<cstdio>
#include<cstring>
int main()
{
    int test;
    char s[25000];
    scanf("%d",&test);
    while(test--)
    {
                 gets(s);
                 l=strlen(s);
                 
                 mx=0;
                 
                 t1=0;
                 for(i=0;i<l;i++)
                 {
                   if(s[i]==' ')
                    t2=i;//mila hai space i pe temp
                    
                    d=t2-t1+1;
                    if(d>mx)
                    mx=d;
                    
                    t1=t2;
                    
                    }  
                    
                    
                               
                 
