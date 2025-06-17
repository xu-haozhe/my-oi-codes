#include<bits/stdc++.h>
using namespace std;
using ll=long long;
constexpr size_t maxn=2.5e5;
int n,m,fa[maxn+5][20],w[maxn+5][20],dfn[maxn+5],dep[maxn+5],k;
namespace input_tree{
    vector<pair<int,int> >edges[maxn+5];
    inline void dfs(int p){
        static int cnt;
        dfn[p]=++cnt;
        for(auto i:edges[p])if(i.first!=fa[p][0]){
            fa[i.first][0]=p,w[i.first][0]=i.second,dep[i.first]=dep[p]+1,dfs(i.first);
        }
    }
    inline void init(){
        for(int i=1,u,v,w;i<n;i++)cin>>u>>v>>w,edges[u].push_back({v,w}),edges[v].push_back({u,w});
        fa[1][0]=1,dep[1]=1,dfs(1);
        for(int i=0;i<19;i++)for(int j=0;j<=n;j++)fa[j][i+1]=fa[fa[j][i]][i],w[j][i+1]=min(w[j][i],w[fa[j][i]][i]);
    }
};
__always_inline unsigned char fastlog2(ll x)noexcept{return __builtin_ctzll(x);}
inline int lca(int x,int y){
    if(dep[x]<dep[y])swap(x,y);
    for(int i=dep[x]-dep[y];i;i&=i-1)x=fa[x][fastlog2(i)];
    for(int i=19;i>=0;i--)if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
    return x==y?x:fa[x][0];
}
inline int getw(int f,int son){
    int res=INT_MAX;
    for(int i=dep[son]-dep[f];i;i&=i-1)res=min(res,w[son][fastlog2(i)]),son=fa[son][fastlog2(i)];
    return res;
}
bool is[maxn+5];
int tree[maxn*2+10],*e_tree=tree;
vector<int>son[maxn+5];
inline void build_virtual_tree(){
    for(int *i=tree;i!=e_tree;i++)is[*i]=false;
    cin>>k,e_tree=tree;
    for(int i=0,h;i<k;i++)cin>>h,is[h]=true,*(e_tree++)=h;
    sort(tree,e_tree,[&](int x,int y){return dfn[x]<dfn[y];});
    for(int *i=tree+1,*e=e_tree;i!=e;++i)*(e_tree++)=lca(*(i-1),*i);
    *(e_tree++)=1;
    sort(tree,e_tree,[&](int x,int y){return dfn[x]<dfn[y];});
    e_tree=unique(tree,e_tree);
    for(int *i=tree;i!=e_tree;++i)son[*i].clear();
    for(int *i=tree+1;i!=e_tree;++i)son[lca(*(i-1),*i)].push_back(*i);
}
inline ll dfs_dp(int p){
    ll res=0;
    for(auto i:son[p])res+=(is[i]?getw(p,i):min(dfs_dp(i),(ll)getw(p,i)));
    return res;
}
int main(){
    cin>>n;
    input_tree::init();
    cin>>m;
    while(m--){
        build_virtual_tree();
        cout<<dfs_dp(1)<<'\n';
    }
    return 0;
}