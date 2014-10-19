#include<iostream>
#include<cstdlib>
#include<cstring>
using namespace std;
int main()
{
 char ch='2',d='3',a[3];
 a[0]=ch;
 a[1]=d;
 //a[2]='\0';

 cout<<atoi(a)*2<<endl;

return 0;
}
