#include<bits/stdc++.h>
using namespace std;
constexpr int maxn=1e4;
int n,m,val[maxn+5],dfn[maxn+5],low[maxn+5],c[maxn+5],s[maxn+5],*top=s,cnt;
bool vis[maxn+5];
vector<int >edges[maxn+5];
int val2[maxn+5],dp[maxn+10],in[maxn+10],ans;
vector<int> edges2[maxn+5];
void tarjan(int u){
    static int cnt_dfn=0;
    low[u]=dfn[u]=++cnt_dfn,vis[u]=1,*(++top)=u;
    for(auto i:edges[u]){
        if(!dfn[i])tarjan(i),low[u]=min(low[u],low[i]);
        else if(vis[i])low[u]=min(low[u],dfn[i]);
    }
    if(dfn[u]==low[u]){        
        for(cnt++;u^*top;top--)
            c[*top]=cnt,vis[*top]=0;
        c[*top]=cnt,vis[*top]=0,top--;
    }
}
inline void tuopu(){
    queue<int>q;
    for(int i=1;i<=cnt;i++)if(in[i]==0)q.push(i),dp[i]=val2[i];
    while(!q.empty()){
        int u=q.front();q.pop();
        for(auto i:edges2[u]){
            dp[i]=max(dp[i],dp[u]+val2[i]);
            if(--in[i]==0)q.push(i);
        }
    }
    for(int i=1;i<=cnt;i++)ans=max(ans,dp[i]);
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>val[i];
    for(int i=0,u,v;i<m;i++)cin>>u>>v,edges[u].push_back(v);
    for(int i=1;i<=n;i++)if(!dfn[i])tarjan(i);
    for(int i=1;i<=n;i++){
        val2[c[i]]+=val[i];
        for(auto j:edges[i])if(c[i]^c[j])edges2[c[i]].push_back(c[j]),in[c[j]]++;
    }
    tuopu();
    cout<<ans<<'\n';
    return 0;
}