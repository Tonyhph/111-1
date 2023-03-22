#include<bits/stdc++.h>
using namespace std;
const int INF=0x3f3f3f3f;
const int maxn=2*500+10;
struct Edge{
    int u,v,c,f;
};
struct Dinic
{
    int s,t; //源点汇点
    vector<Edge> E;
    vector<int> G[maxn];
    
    void addedge(int from,int to,int cap)
    {
        E.push_back((Edge){from,to,cap,0});
        E.push_back((Edge){to,from,0,0});
        G[from].push_back(E.size()-2);
        G[to].push_back(E.size()-1);
    }
    int dist[maxn],vis[maxn];
    queue<int> q;
    bool bfs() //在残量网络上构造分层图
    {
        memset(vis,0,sizeof(vis));
        while(!q.empty()) q.pop();
        q.push(s);
        dist[s]=0;
        vis[s]=1;
        while(!q.empty())
        {
            int now=q.front(); q.pop();
            for(int i=0;i<G[now].size();i++)
            {
                Edge& e=E[G[now][i]]; int nxt=e.v;
                if(!vis[nxt] && e.c>e.f)
                {
                    dist[nxt]=dist[now]+1;
                    q.push(nxt);
                    vis[nxt]=1;
                }
            }
        }
        return vis[t];
    }
    int dfs(int now,int flow)
    {
        if(now==t || flow==0) return flow;
        int rest=flow,k;
        for(int i=0;rest>0 && i<G[now].size();i++)
        {
            Edge &e=E[G[now][i]]; int nxt=e.v;
            if(e.c>e.f && dist[nxt]==dist[now]+1)
            {
                k=dfs(nxt,min(rest,e.c-e.f));
                if(!k) dist[nxt]=0; //剪枝，去掉增广完毕的点
                e.f+=k; E[G[now][i]^1].f-=k;
                rest-=k;
            }
        }
        return flow-rest;
    }
    int mf; //存储最大流
    int maxflow()
    {
        mf=0;
        int flow=0;
        while(bfs()) while(flow=dfs(s,INF)) mf+=flow;
        return mf;
    }
}dinic;
int n,m,k;
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    dinic.s=0, dinic.t=n+m+2;
    dinic.addedge(dinic.s,n+m+1,k);
    for(int i=1,t;i<=n;i++)
    {
        dinic.addedge(dinic.s,i,1);
        dinic.addedge(n+m+1,i,1);
        scanf("%d",&t);
        for(int j=1,k;j<=t;j++)
        {
            scanf("%d",&k);
            dinic.addedge(i,n+k,1);
        }
    }
    for(int i=1;i<=m;i++) {
        dinic.addedge(n+i,dinic.t,1);
    }
    printf("%d\n",dinic.maxflow());
}