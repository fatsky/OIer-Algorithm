//并查集（带路径压缩）
const int MAXN = 10005;


int node[MAXN];			//每个节点
int rank[MAXN];			//树的高度

//初始化n个节点
void Init(int n){
	for(int i = 0;i < n;i++){
		node[i] = i;
		rank[i] = 0;
	}
}

//查找元素根节点
int find(int x){
	if(x == node[x])
		return x;
	return node[x] = find(node[x]);
}

//合并x, y所在的集合
void Unite(int x, int y){
	//查找根
	x = find(x);
	y = find(y);

	if(x == y) return ;

	//判断两树的高度，决定子树
	if(rank[x] < rank[y])
		node[x] = y;
	else {
		node[y] = x;
		if(rank[x] == rank[y]) rank[x]++;
	}
}

//判断x, y是否属于同一个集合
bool same(int x, int y){
	return find(x) == find(y);
}