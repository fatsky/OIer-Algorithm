//图的最短路径 --SPFA
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int maxn = 10005;
const int INF = 1 << 30;


//邻接表存图
struct Edge{
	int to, var, next;		//to--下一个点,next--下一条变,var--边长
}e[maxn * 2];

int num_of_edge,front[maxn];
int n,m,s,t;				//n表示顶点个数，m表示边的条数，查询从s到t的最短路 

inline void AddEdge(int from, int to, int var){
	//u, v
	num_of_edge++;
	e[num_of_edge].to = to;
	e[num_of_edge].var = var;
	e[num_of_edge].next = front[from];
	front[from] = num_of_edge;
}


//SPFA O(mn)
//原理：队列 + 松弛

void SPFA()
{
	int inq[maxn], d[maxn];
	queue<int> q;
	memset(inq, 0, sizeof(inq));
	for(int i = 1;i <= n;i++) d[i] = INF;

	d[s] = 0; inq[s] = 1; q.push(s);
	while(!q.empty())
	{
		int from = q.front();
		q.pop();
		inq[from] = 0;
		for(int i = front[from]; i >= 0;i = e[i].next)
		{
			int to = e[i].to, var = e[i].var;
			if(d[to] > d[from] + var)
			{
				//松弛
				d[to] = d[from] + var;
				if(!inq[to])
				{
					inq[to] = 1;
					q.push(to);
				}
			}
		}
	}
	printf("%d\n",d[t]);
}





int main(){
	memset(front, -1, sizeof(front));
	scanf("%d%d%d%d", &n, &m, &s, &t);
	int from, to, var;
	for(int i = 1;i <= m;i++)
	{
		scanf("%d%d%d", &from, &to, &var);
		AddEdge(from, to, var);
		//AddEdge(to, from, var);		//有向图
	}
	SPFA();
	return 0;
}