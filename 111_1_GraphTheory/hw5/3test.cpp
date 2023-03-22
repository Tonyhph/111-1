#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<LL,LL> pii;
const int N=1e5+10;
LL n,m,ans;
LL d1[N],d2[N],x[N],y[N],z[N];

LL cnt=1,head[N],to[N<<1],nxt[N<<1],len[N<<1];
void add_edge(LL x,LL y,LL z) {
    nxt[++cnt]=head[x]; to[cnt]=y; len[cnt]=z; head[x]=cnt;
}

bool vis[N]; 
priority_queue<pii> q;
void Dijkstra(LL d[],LL s) {
    while (!q.empty()) q.pop();
    memset(vis,0,sizeof(vis));
    d[s]=0; q.push(make_pair(0,s));
    while (!q.empty()) {
        pii x=q.top(); q.pop();
        if (vis[x.second]) continue;
        vis[x.second]=1;
        for (LL i=head[x.second];i;i=nxt[i]) {
            LL y=to[i];
            if (d[y]>d[x.second]+len[i]) {
                d[y]=d[x.second]+len[i];
                q.push(make_pair(-d[y],y));
            }
        }
    }
}

int num,low[N],dfn[N],bridge[N];
void tarjan(int x,int in) {
    dfn[x]=low[x]=++num;
    for (int i=head[x];i;i=nxt[i]) {
        int y=to[i];
        if (!dfn[y]) {
            tarjan(y,i);
            low[x]=min(low[x],low[y]);
            
            if (low[y]>dfn[x])
                bridge[len[i]]=bridge[len[i^1]]=1;
        } else if (i!=(in^1))
            low[x]=min(low[x],dfn[y]);
    }
}

void getbridge() {
    cnt=1; memset(head,0,sizeof(head));
    for (int i=1;i<=m;i++)
        if (d1[x[i]]+z[i]+d2[y[i]]==ans) 
            add_edge(x[i],y[i],i),add_edge(y[i],x[i],i);
    for (int i=1;i<=n;i++)
        if (!dfn[i]) tarjan(i,0);    
}

int main()
{
    cin>>n>>m;
    for (int i=1;i<=m;i++) scanf("%lld%lld%lld",&x[i],&y[i],&z[i]);
    
    memset(d1,0x3f,sizeof(d1)); memset(d2,0x3f,sizeof(d2));
    for (int i=1;i<=m;i++) add_edge(x[i],y[i],z[i]);
    Dijkstra(d1,1);

    cnt=1; memset(head,0,sizeof(head));
    for (int i=1;i<=m;i++) add_edge(y[i],x[i],z[i]);
    Dijkstra(d2,2);
   
    ans=d1[2]; getbridge();
    
    for (int i=1;i<=m;i++)
        if (ans>d1[y[i]]+d2[x[i]]+z[i]) puts("HAPPY");
        else if (bridge[i]) puts("SAD"); else puts("SOSO");
    return 0;
} 
