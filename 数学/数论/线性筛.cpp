//线性筛法
#include <cstdio>
#include <cstring>

const int MAXN = 100005;

int is_prime[MAXN];
int prime[MAXN];
int num_prime = 0;

void make_prime(int up_bound)
{
	//for(int i = 0;i < up_bound;i++) is_prime[i] = 1;
	memset(is_prime, -1, sizeof(is_prime));
	is_prime[0] = is_prime[1] = 0;
	for(int i = 2; i <= up_bound; i++)
	{
		if(is_prime[i]) prime[num_prime++] = i;
		for(int j = 0;j < num_prime && i * prime[j] <= up_bound;j++)
		{
			is_prime[i * prime[j]] = 0;
			if(i % prime[j] == 0)break;
		}
	}
	return;
}