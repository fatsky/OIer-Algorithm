#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

class Graph {
    private:
        static const int maxn = 10005;      //节点的最大个数
        static const int maxm = 200005;     //边的最大个数
        static const int inf = 2e9 + 7;
        int head[maxn];             //链式前向星存图
        int V[maxm], C[maxm], nxt[maxm];    //每条边指向的点、每条边的容量
        int depth[maxn];            //记录每个节点的深度层次，源点深度为1
        int num_edge;               //总边数

        void _Add (int u, int v, int c) {   //添加一条边
            nxt[num_edge] = head[u];
            head[u] = num_edge;
            V[num_edge] = v;
            C[num_edge] = c;
            num_edge++;
        }


        bool bfs () {       //广度优先搜索，构造分层图
            queue<int> q;
            memset (depth, 0, sizeof (depth));

            depth[s] = 1;
            q.push (s);
            while (!q.empty ()) {
                int t = q.front ();
                q.pop ();
                for (int i = head[t]; i != -1; i = nxt[i]) {
                    if (C[i] > 0 && !depth[V[i]]) {     //必须确保残量>0
                        depth[V[i]] = depth[t] + 1;
                        q.push (V[i]);
                    }
                }
            }

            if (depth[t] == 0) return false;        //没有拓展到汇点，说明不存在增广路了
            else return true;
        }

        int dfs (int u, int flow) {             //深搜更新最大流
            if (u == t)
                return flow;
            
            for (int i = head[u]; i != -1; i = nxt[i]) {
                if (depth[V[i]] > depth[u] && C[i] != 0) {      //残量不能为0
                    int di = dfs (V[i], min (flow, C[i]));
                    if (di > 0) {
                        C[i] -= di;     //正向边流量-di，反向边流量+di
                        C[i ^ 1] += di;
                        return di;
                    }
                }
            }

            return 0;
        }

    public:
        int s, t;   //源点、汇点

        void init () {
            memset (head, -1, sizeof (head));
            num_edge = 0;
        }

        void AddEdge (int from, int to, int cap) {
            _Add (from, to, cap);       //加一条正向边，一条反向边
            _Add (to, from, 0);
        }

        int Dinic () {
            int ans = 0;
            while (bfs ()) {    //只要有层次图，就更新最大流
                while (int d = dfs (s, inf)) {
                    ans += d;
                }
            }
            return ans;
        }
};


Graph g;

int main () {
    int n, m;
    g.init ();
    scanf ("%d%d%d%d", &n, &m, &g.s, &g.t);

    for (int i = 0; i < m; ++i) {
        int x, y, z;
        scanf ("%d%d%d", &x, &y, &z);
        g.AddEdge (x, y, z);
    }

    printf ("%d\n", g.Dinic ());
    return 0;
}