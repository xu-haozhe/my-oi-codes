#include<bits/stdc++.h>
using namespace std;
using ll=long long;
template<class T>inline void read(T&t_)noexcept{
    char ch=getchar();T t=0;char f=1;
    while(!isdigit(ch))ch=getchar();
    while(isdigit(ch))t=t*10+(ch&0xf),ch=getchar();
    t_=t*f;
}
template<class T,class ...Args>__always_inline void read(T&first,Args&...args)noexcept{read(first);read(args...);}
int n,m,s,t,dep[205],cnt=1,h[205],now[205];ll ans;
struct edge{int v,w,nxt;}edges[10005];
inline void add_edge(int u,int v,int w)noexcept{edges[++cnt]=(edge){v,w,h[u]},h[u]=cnt;}
inline bool bfs()noexcept{ 
    bzero(dep+1,n*sizeof(*dep));
    queue<int>q;q.push(s),dep[s]=1,now[s]=h[s];
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int i=h[u];i;i=edges[i].nxt){
            int v=edges[i].v,w=edges[i].w;
            if(w&&!dep[v]){
                dep[v]=dep[u]+1,now[v]=h[v];
                q.push(v);
                if(v==t)return 1;
            }
        }
    }
    return 0;
}
ll dfs(int u,ll sum){
    if(u==t)return sum;
    ll k,res=0;
    for(auto &i=now[u];
        i&&sum;
        i=edges[i].nxt){
        // now[u]=i;
        int v=edges[i].v,w=edges[i].w;
        if(w&&(dep[v]==dep[u]+1)){
            k=dfs(v,min(sum,(ll)w));
            if(!k)dep[v]=0;
            sum-=k,res+=k,edges[i].w-=k,edges[i^1].w+=k;
        }
    }
    return res;
}
int main(){
    read(n,m,s,t);
    for(int i=0,u,v,w;i<m;i++)read(u,v,w),add_edge(u,v,w),add_edge(v,u,0);
    while(bfs())
        ans+=dfs(s,0xffffffffffff);
    printf("%lld\n",ans);
    return 0;
}