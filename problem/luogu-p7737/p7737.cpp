#include<bits/stdc++.h>
using namespace std;
template<class T>inline void read(T&t){
    unsigned char ch=getchar();T t=0;
    while(!isdigit(ch))ch=getchar();
    while(isdigit(ch))t=t*10+(ch&0xf),ch=getchar();
    t_=t;[[assume(t_>=0)]];
}
template<class T,class...Args>__always_inline void read(T&first,Args&...args){read(first);read(args...);}
using ll=long long;using ull=unsigned long long;
constexpr size_t maxn=3e5;
int n,m,q,k;
namespace g{
    vector<int>son[maxn+5];int num[maxn+5],t[maxn+5],dfn[maxn+5],st[20][maxn+5],root;
    inline void dfs(int u,int fa)noexcept{static int cnt=0;st[0][dfn[u]=++cnt]=fa;for(auto v:son[u])dfs(v,u);}
    __always_inline uint8_t lg2(uint64_t x)noexcept{return 63-__builtin_clzll(x);}
    inline int upd(int x,int y)noexcept{return dfn[x]<dfn[y]?x:y;}
    inline void init(){
        dfs(root,0);
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
namespace init_graph{
    vector<uint>edges[maxn+10];
    inline void input(){
        for(int i=0,u,v;i<m;i++)read(u,v),edges[u].push_back(v);
    }
    int dfn[maxn+5],low[maxn+5];using  g::num;auto&c=g::t;
    void dfs_tarjan(int u)noexcept{
        static int cnt_dfn,stk[maxn+5],*top=stk,cnt_c;
        static bool vis[maxn+5];
        dfn[u]=low[u]=++cnt_dfn,vis[u]=true,*(++top)=u;
        for(auto v:edges[u]){
            if(!dfn[v])dfs_tarjan(v),low[u]=min(low[u],low[v]);
            else if(vis[v])low[u]=min(low[u],dfn[v]);
        }
        if(low[u]==dfn[u]){
            for(cnt_c++;u^*top;--top)c[*top]=cnt_c,vis[*top]=false;
            c[*top]=cnt_c,vis[*top]=0,--top;
        }
    }
    vector<int>edges2[maxn+5];int in[maxn+5];
    inline void tarjan()noexcept{
        for(int i=1;i<=n;++i)if(!dfn[i])dfs_tarjan(i);
        for(int i=1;i<=n;i++){
            num[c[i]]++;
            for(auto j:edges[i])if(c[i]^c[j])edges2[c[i]].push_back(c[j]),in[c[j]]++;
        }
    }
    inline void topo()noexcept{ 
        queue<int>q;
        for(int i=1;i<=n;i++)if(!in[i]){q.push(g::root=i);break;}
        while(!empty(q)){
            int now=q.front();q.pop();
            for(auto i:edges2[now])if(!--in[i])q.push(i),g::son[i].push_back(i);
        }
    }
    inline void solve()noexcept{input(),tarjan(),topo();}
}
namespace virtual_tree{
    vector<int>son[maxn+5],redge[maxn+5];int tree[20],*e_tree;
    int s,t,a,b,c,d;
    using g::dfn,g::lca;
    inline void build()noexcept{
        e_tree=tree+2+k*2,read(s,t),tree[0]=s,tree[1]=t;
        if(k>0)read(a,b),tree[2]=a,tree[3]=b;
        if(k>1)read(c,d),tree[4]=c,tree[5]=d;
        sort(tree,e_tree,[&](int x,int y){return dfn[x]<dfn[y];});
        for(int *i=tree+1,*e=e_tree;i!=e;++i)*(e_tree++)=lca(*(i-1),*i);
        sort(tree,e_tree,[&](int x,int y){return dfn[x]<dfn[y];});
        e_tree=unique(tree,e_tree);
        for(int *i=tree;i!=e_tree;++i)son[*i].clear(),redge[*i].clear();
        for(int *i=tree+1;i!=e_tree;++i)son[lca(*(i-1),*i)].push_back(*i);
        if(k>0)son[a].push_back(b);
        if(k>1)son[c].push_back(d);
        for(int*i=tree;i!=e_tree;++i)for(auto j:son[*i])redge[j].push_back(*i);
    }
    inline void get_ans(){
        uint8_t vis[maxn+5];
        for(int*i=tree;i!=e_tree;++i)vis[*i]=false;
        static int stk[50],*top,now;
        for(*stk=s,top=stk+1;top!=stk;){
            now=*(top--);for(auto j:son[now])if(!vis[j])vis[j]=2,*(++top)=j;
        }

    }
}
int main(){

    return 0;
}