#include<bits/stdc++.h>
#include <cstdint>
#include <sys/cdefs.h>
using namespace std;
int n,m,r;
vector<int>edges[500005];
namespace lca{
    int dfn[500005],st[20][500005];
    void dfs(int u,int fa){
        static int cnt=0;
        st[0][dfn[u]=++cnt]=fa;
        for(auto i:edges[u])if(i^fa)dfs(i,u);
    }
    __always_inline uint8_t lg2(uint64_t x){return 63-__builtin_clzll(x);}
    inline int upd(int x,int y){return dfn[x]<dfn[y]?x:y;}
    inline void init(){
        dfs(r,0);
        for(int i=1,e=lg2(n);i<=e;i++)
            for(int j=0;j<=n-(1<<i)+1;j++)
                st[i][j]=upd(st[i-1][j],st[i-1][j+(1<<(i-1))]);
    }
    int lca(int x,int y){
        if(x==y)return x;
        if((x=dfn[x])>(y=dfn[y]))swap(x,y);
        int l=lg2(y-x++);
        return upd(st[l][x],st[l][y-(1<<l)+1]);
    }
};
int main(){
    cin>>n>>m>>r;
    for(int i=1,u,v;i<n;i++)cin>>u>>v,edges[u].push_back(v),edges[v].push_back(u);
    lca::init();
    for(int i=0,u,v;i<m;i++)cin>>u>>v,cout<<lca::lca(u,v)<<'\n';
    return 0;
}