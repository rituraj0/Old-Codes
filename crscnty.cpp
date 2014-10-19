#include<iostream>
#include<cstdio>
int main()
{
	int t, alen, tlen, temp, max, i, j;
	char ar[2001][2001];//int ar[2001][2001] overflow ho rha tha yaar so char se kam
	int tom[2001];
	int agnes[2001];
	scanf("%d", &t);
	while(t--)
	{
		temp=1;
		alen=0;
		while(temp!=0)
		{
			scanf("%d", &temp);
			agnes[alen]=temp;
			alen++;
		}
		max=0;
		while(1)
		{
			scanf("%d", &temp);
			if(temp==0)
				break;
			else
			{
				tlen=1;
				tom[0]=temp;
				while(temp!=0)
				{
					scanf("%d", &temp);
					tom[tlen]=temp;
					tlen++;
				}
			//ek input  taken 
                                   //ab niche lcs lenght nikal rahe hai
				for(i=0;i<alen;i++)
					ar[i][0]='0';
				for(j=1;j<tlen;j++)
					ar[0][j]='0';
				for(i=1;i<alen;i++)
					for(j=1;j<tlen;j++)
					{
						if(ar[i-1][j]>ar[i][j-1])
							ar[i][j] = ar[i-1][j];
						else
							ar[i][j] = ar[i][j-1];
						if((tom[j-1]==agnes[i-1])&&(ar[i-1][j-1]+1>ar[i][j]))
							ar[i][j] = ar[i-1][j-1] + 1;
					}
				if(max<ar[alen-1][tlen-1])
					max = ar[alen-1][tlen-1];
			}
		}
		printf("%d\n", max-'0');
	}
	return 0;
}
