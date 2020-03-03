
#include <cstdio>

#include <iostream>

#define ll long long

#define mode 1000000007

#define maxx 1000000

ll v[1000005];

ll dp[1000005];

ll f[25];

int n;

int main()

{

	v[0]=1;

	scanf("%d",&n);

	for(int i=1;i<=maxx;i++)

	{

		v[i]=(v[i-1]<<1)%mode;

	}

	for(int i=1;i<=n;i++)

	{

		int x;

		scanf("%d",&x);

		dp[x]++;

	}

	for(int j=0;j<=20;j++)

	{

		for(int i=1;i<=maxx;i++)

		{

			if(((1<<j)&i))

			{

				dp[i^(1<<j)]+=dp[i];

			}

		}

	}

	ll ans=0;

	for(int i=0;i<=maxx;i++)

	{

		int cnt=0;

		for(int j=0;j<=20;j++)

		{

			if((1<<j)&i)

			{

				cnt++;

			}

		}

		f[cnt]+=((v[dp[i]]-1)%mode+mode)%mode;

	}

	for(int i=0;i<=20;i++)

	{

		if(i%2)

		{

			ans-=f[i];

			ans%=mode;

		}else

		{

			ans+=f[i];

			ans%=mode;

		}

	}

	printf("%I64d\n",(ans%mode+mode)%mode);

	return 0;

}
