#include<bits/stdc++.h>
using namespace std;
constexpr int maxn=2e4;
int n,m,low[maxn+10],dfn[maxn+10],cnt_dfn;
vector<int>edges[maxn+10];
bool iscut[maxn+10];
void dfs(int p,int fa){
    low[p]=dfn[p]=++cnt_dfn;
    for(auto i:edges[p]){
        if(!dfn[i]){
            dfs(i,p);
            low[p]=min(low[p],low[i]);
            if(low[i]>=dfn[p])iscut[p]=true;
        }else if(dfn[p]>dfn[i]&&i!=fa)low[p]=min(low[p],dfn[i]);
    }
}
void dfs(int p){
    low[p]=dfn[p]=++cnt_dfn;
    int cnt=0;
    for(auto i:edges[p]){
        if(!dfn[i]){
            cnt++;
            dfs(i,p);
            low[p]=min(low[p],low[i]);
        }else if(dfn[p]>dfn[i])low[p]=min(low[p],dfn[i]);
    }
    if(cnt>1)iscut[p]=true;
}
int main(){
    cin>>n>>m;
    for(int i=0,u,v;i<m;i++)cin>>u>>v,edges[u].push_back(v),edges[v].push_back(u);
    for(int i=1;i<=n;i++)if(!dfn[i])dfs(i);
    cout<<count_if(iscut+1,iscut+n+1,[](bool x){return x;})<<'\n';
    for(int i=1;i<=n;i++)if(iscut[i])cout<<i<<' ';
    return 0;
}