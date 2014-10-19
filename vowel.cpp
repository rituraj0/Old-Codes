#include<iostream>
#include<cstdio>
int main()
{
    int v=0,i;
    char s[100005];
    scanf("%s",s);
    
    for(i=0;i<strlen(s);i++)
    {
            if(s[i]=='a'||s[i]=='e'||s[i]=='i'||s[i]=='o'||s[i]=='u'||s[i]=='A'||s[i]=='E'||s[i]=='I'||s[i]=='O'||s[i]=='U'||s[i]=='y'||s[i]=='Y')
            v++;
            }
            printf("%d",v);
           
            return 0;
            }


