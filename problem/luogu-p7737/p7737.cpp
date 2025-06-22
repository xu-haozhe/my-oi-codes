#include<bits/stdc++.h>
using namespace std;
template<class T>inline void read(T&t_){
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
    vector<int>son[maxn+50];int num[20][maxn+50],fa[20][maxn+50],t[maxn+50],dfn[maxn+50],st[20][maxn+50],root,dep[maxn+50],siz;
    inline void dfs(int u,int fa_)noexcept{
        static int cnt=0;st[0][dfn[u]=++cnt]=fa[0][u]=fa_;
        for(auto v:son[u])dep[v]=dep[u]+1,dfs(v,u);
    }
    __always_inline uint8_t lg2(uint64_t x)noexcept{return 63-__builtin_clzll(x);}
    inline int upd(int x,int y)noexcept{return dfn[x]<dfn[y]?x:y;}
    inline void init(){
        dep[root]=1;dfs(root,0);
        for(int i=1,e=lg2(siz);i<=e;i++)
            for(int j=0;j<=siz-(1<<i)+1;j++)
                st[i][j]=upd(st[i-1][j],st[i-1][j+(1<<(i-1))]);
        for(int i=1;i<20;i++)
            for(int j=1;j<=siz;j++)fa[i][j]=fa[i-1][fa[i-1][j]],num[i][j]=num[i-1][j]+num[i-1][fa[i-1][j]];
    }
    int lca(int x,int y){
        if(x==y)return x;
        if((x=dfn[x])>(y=dfn[y]))swap(x,y);
        int l=lg2(y-x++);
        return upd(st[l][x],st[l][y-(1<<l)+1]);
    }
    __always_inline uint8_t lowbit_lg2(uint64_t x)noexcept{return __builtin_ctzll(x);}
    inline int getw(int f,int son)noexcept{
        if(lca(f,fa[0][son])^f)return 0;
        int res=0;
        for(int d=dep[son=fa[0][son]]-dep[f];d;d&=d-1)res+=num[lowbit_lg2(d)][son],son=fa[lowbit_lg2(d)][son];
        return res;
    }
};
namespace init_graph{
    vector<uint>edges[maxn+50];
    inline void input(){
        for(int i=0,u,v;i<m;i++)read(u,v),edges[u].push_back(v);
    }
    int dfn[maxn+50],low[maxn+50];auto&cnt_c=g::siz;auto&num=g::num[0];auto&c=g::t;
    void dfs_tarjan(int u)noexcept{
        static int stk[maxn+50],*top=stk,cnt_dfn;
        static bool vis[maxn+50];
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
    vector<int>edges2[maxn+50];int in[maxn+50];
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
            for(auto i:edges2[now])if(!--in[i])q.push(i),g::son[now].push_back(i);
        }
    }
    inline void solve()noexcept{input(),tarjan(),topo();}
}
namespace virtual_tree{
    vector<pair<int,uint8_t>>son[maxn+50];vector<int>redge[maxn+50];int tree[50],*e_tree;
    int s,t,a,b,c,d;
    using g::dfn,g::lca;auto&tr=g::t;
    inline void build()noexcept{
        e_tree=tree+2+k*2,read(s,t),s=tr[s],t=tr[t],tree[0]=s,tree[1]=t;
        if(k>0)read(a,b),a=tr[a],b=tr[b],tree[2]=a,tree[3]=b;
        if(k>1)read(c,d),c=tr[c],d=tr[d],tree[4]=c,tree[5]=d;
        sort(tree,e_tree,[&](int x,int y){return dfn[x]<dfn[y];});
        e_tree=unique(tree,e_tree);
        for(int *i=tree+1,*e=e_tree;i!=e;++i)*(e_tree++)=lca(*(i-1),*i);
        *(e_tree++)=g::root;
        sort(tree,e_tree,[&](int x,int y){return dfn[x]<dfn[y];});
        e_tree=unique(tree,e_tree);
        for(int *i=tree;i!=e_tree;++i)son[*i].clear(),redge[*i].clear();
        for(int *i=tree+1;i!=e_tree;++i)son[lca(*(i-1),*i)].push_back({*i,1});
        if(k>0)son[a].push_back({b,0});
        if(k>1)son[c].push_back({d,0});
        for(int*i=tree;i!=e_tree;++i)for(auto j:son[*i])redge[j.first].push_back(*i);
    }
    inline int get_ans(){
        static uint8_t vis[maxn+50];
        for(int*i=tree;i!=e_tree;++i)vis[*i]=false;
        static int stk[50],*top,now;
        for(vis[*stk=t]=2,top=stk+1;top!=stk;){
            now=*(--top);for(auto j:redge[now])if(!vis[j])vis[j]=2,*(top++)=j;
        }
        int res=0;
        for(vis[*stk=s]|=1,top=stk+1;top!=stk;){
            now=*(--top);for(auto j:son[now])if(!(vis[j.first]&1))vis[j.first]|=1,*(top++)=j.first;
        }
        for(int*i=tree;i!=e_tree;++i)if(vis[*i]==3){
            res+=g::num[0][*i];
            for(auto j:son[*i])if(vis[j.first]==3){
                if(j.second)res+=g::getw(*i,j.first);
            }
        }
        return res;
    }
}
int main(){
    read(n,m,q,k);
    init_graph::solve();
    g::init();
    while(q--){
        virtual_tree::build();
        cout<<virtual_tree::get_ans()<<'\n';
    }
    return 0;
}