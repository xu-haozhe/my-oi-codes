#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int n,m,s,t,dep[205];
ll ans;
struct edge{int t,w;union Rev{int p;vector<edge>::iterator it;}rev;};
vector<edge>edges[205];
vector<edge>::iterator it[205];
template<class T>inline void read(T&t_)noexcept{
    char ch=getchar();T t=0;char f=1;
    while(!isdigit(ch))ch=getchar();
    while(isdigit(ch))t=t*10+(ch&0xf),ch=getchar();
    t_=t*f;
}
template<class T,class ...Args>__always_inline void read(T&first,Args&...args)noexcept{read(first);read(args...);}
inline void add_edge(int u,int v,int w)noexcept{//u --w--> v
    edges[u].push_back({v,w,{(int)edges[v].size()}});
    edges[v].push_back({u,0,{(int)edges[u].size()-1}});
}


inline bool bfs()noexcept{
    bzero(dep,(n+1)*sizeof(*dep));
    queue<int>q;q.push(s),dep[s]=1,it[s]=edges[s].begin();
    while(!q.empty()){
        int u=q.front();q.pop();
        for(auto [v,w,_]:edges[u])if((w>0)&(!dep[v])){
           it[v]=edges[v].begin(),q.push(v),dep[v]=dep[u]+1;
           if(v==t)return 1;
        }
    }
    return false;
}
ll dfs(int u,ll sum)noexcept{
    if(u==t)return sum;
    int d=dep[u]+1;ll k=0,res=0;
    for(auto i=it[u];i->t&&sum;i++){
        it[u]=i;
        auto [v,w,rev]=*i;
        if((w>0)&(dep[v]==d)){
            k=dfs(v,min(sum,(ll)w));
            if(k==0)dep[v]=0;
            i->w-=k,rev.it->w+=k,res+=k,sum-=k;
        }
    }
    return res;
}

int main(){
    read(n,m,s,t);
    for(int i=1;i<=n;i++)edges[i].reserve(m+2);
    for(int i=0,u,v,w;i<m;i++)read(u,v,w),add_edge(u,v,w);
    for(int i=1;i<=n;i++){
        edges[i].push_back({0});
        for(auto &[v,w,rev]:edges[i])rev.it=edges[v].begin()+rev.p;
    }
    while(bfs()){
        ans+=dfs(s,0xffffffffffffll);
    }
    printf("%lld\n",ans);
    return 0;
}