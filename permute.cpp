#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char a[50],st_char;
int i,j,k,n,st,ctr,main_ctr;

int fn_print()
{
 for(i=0;i<=n-2;++i)
	{
		ctr=0;  /*counter for printing the string */
		printf("\n\n");
		printf("%c",a[0]);
		for(j=i+1;j<=n-1;j++)
			{
				printf("%c",a[j]);
				ctr++;
			}

	if(ctr!=n-1)
	while(ctr!=n-1)
		{
			st=i+1;
			for(k=1;k<=st-1;k++)
			{
				printf("%c",a[k]);
				ctr++;
			}
		}
	}
st_char=a[0];
for(i=0;i<=n-2;i++)
a[i]=a[i+1];

a[n-1]=st_char;

main_ctr++;



}

int main()
{

printf("Enter the string : ");
gets(a);

n=strlen(a);

while(main_ctr<n)
fn_print();


getch();
return 0;
}
