#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5e6 + 2333; // X 集合中的顶点数上限
const int MAXM = 5e6 + 2333; // 总的边数上限
const int INF = 0x3f3f3f3f;
int head[MAXN], tot;
int S, T;
int d[MAXN]; // 存储每个顶点的层次
struct Edge
{
    int to, cap, next;
} e[MAXM];

void addedge(int from, int to, int cap)
{
    e[tot].to = to;
    e[tot].cap = cap;
    e[tot].next = head[from];
    head[from] = tot++;

    e[tot].to = from;
    e[tot].cap = 0;
    e[tot].next = head[to];
    head[to] = tot++;
}
bool bfs()
{
    memset(d, -1, sizeof(d));
    queue<int> q;
    q.push(S);
    d[S] = 1;
    while (!q.empty())
    {
        int from = q.front();
        q.pop();
        for (int i = head[from]; i != -1; i = e[i].next)
        {
            int to = e[i].to;
            if (e[i].cap > 0 && d[to] == -1)
            {
                q.push(to);
                d[to] = d[from] + 1;
            }
        }
    }
    return (d[T] != -1);
}
int dfs(int from, int flow)
{
    // dfs在层次图G_L中寻找增广路径
    // flow 表示当前搜索分支的流量上限
    if (from == T)
    {
        return flow;
    }
    int res = 0;
    for (int i = head[from]; i != -1; i = e[i].next)
    {
        int to = e[i].to;
        if (e[i].cap > 0 && d[from] + 1 == d[to])
        {
            int tmp = dfs(to, min(flow, e[i].cap));
            // 递归计算顶点 to，用 cap(from, to) 来更新当前流量上限
            flow -= tmp;
            e[i].cap -= tmp;
            res += tmp;
            e[i ^ 1].cap += tmp; // 修改反向弧的容量
            if (flow == 0)
            { // 流量达到上限，不必继续搜索了
                break;
            }
        }
    }
    if (res == 0)
    {
        // 当前没有经过顶点 from 的可行流，不再搜索顶点 from
        d[from] = -1;
    }
    return res;
}
int maxflow()
{ // 函数返回值就是最大流的结果
    int res = 0;
    while (bfs())
    {
        res += dfs(S, INF); // 初始流量上限为 INF
    }
    return res;
}
int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    int m, n, k, mid1, mid2;
    cin>>n>>m>>k;
    memset(head, -1, sizeof(head));
    tot = 0;
    S = 1;
    T = n + m + 4;
    mid1 = 2;
    mid2 = 3;
    int t;
    addedge(S, mid1, n);
    addedge(S, mid2, k);
    for (int i = 1; i <= n; i++)
    {
        addedge(mid1, i + 3, 1);
        addedge(mid2, i + 3, 1);
        cin>>t;
        for (int j = 0; j < t; j++)
        {
            cin>>m;
            addedge(i + 3, n + m + 3, 1);
        }
    }
    for (int i = 1; i <= m; i++)
        addedge(n + i + 3, T, 1);
    cout<<maxflow()<<'\n';
    
    return 0;
}