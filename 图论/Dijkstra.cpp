#include <cstdio>
#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

const int MAXN = 100005;
const int INF = 2147483647;

struct Edge{
	int to, var, next;
}e[MAXN];

int num_of_edge, front[MAXN];
int n, m, s, t;					//n个点,m条边,查询从s到t的最短路

inline void AddEdge(int from, int to, int var){
	num_of_edge++;
	e[num_of_edge].to = to;
	e[num_of_edge].var = var;
	e[num_of_edge].next = front[from];
	front[from] = num_of_edge;
}


//Dijkstra O(m log n)
struct HeapNode{
	//小根堆，储存最小的
	int u, distance;
	bool operator < (const HeapNode& rhs) const {
		return distance > rhs.distance;
	}
};


int d[MAXN];					//目前已知最短边
priority_queue<HeapNode> q;
void Dijkstra(){
	for(int i = 1;i <= n;i++) d[i] = INF;
	d[s] = 0;					//起始点
	q.push((HeapNode){s, d[s]});//找到距离最小的

	while(!q.empty()){
		HeapNode x = q.top(); q.pop();
		int from = x.u;
		if(x.distance != d[from]) continue;
		
		for(int i = front[from]; i >= 0; i = e[i].next){
			int to = e[i].to;
			int var = e[i].var;
			if(d[from] + var < d[to]){
				d[to] = d[from] + var;
				q.push((HeapNode){to, d[to]});
			}
		}
	}
	printf("%d\n", d[t]);
}


int main(){
	memset(front, -1, sizeof(front));
	scanf("%d%d%d%d", &n, &m, &s, &t);
	int from, to, var;

	for(int i = 1; i <= m;i++){
		scanf("%d%d%d", &from, &to, &var);
		AddEdge(from, to, var);
		AddEdge(to, from, var);	//无向图
	}
	Dijkstra();
	return 0;
}