#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace std;
template<class T>inline void read(T&t_)noexcept{
    unsigned char ch=getchar_unlocked();T t=0;
    while(!isdigit(ch))ch=getchar_unlocked();
    while(isdigit(ch))t=t*10+(ch&0xf),ch=getchar_unlocked();
    t_=t;
}
template<class T,class ...Args>__always_inline void read(T&first,Args&...args)noexcept{read(first);read(args...);}

using ll=long long;
constexpr int maxn=2e5,maxm=4e5;
int n,m,fa[maxn+10],h_fa[maxn+10],treeh[maxn+10],T;
ll l[maxn+10];
struct edge{int t,l;};
vector<edge> edges[maxn+10];
struct edge_{int h,a,b;inline friend bool operator<(const edge_&a,const edge_&b){return a.h<b.h;}};
// priority_queue<edge_>q;
__gnu_pbds::priority_queue<edge_>q;
// map<pair<int,int>,ll>mp;
__gnu_pbds::tree<pair<int,int>,ll>mp;
inline int get_fa(int p,int h)noexcept{while(h_fa[p]>h)p=fa[p];return p;}
inline ll query(int p,int h)noexcept{
    return mp.upper_bound({get_fa(p,h),h})->second;
}
int main(){
    read(T);
    while(T--){
        read(n,m);
        bzero(fa,(n+5)*sizeof(int)),bzero(h_fa,(n+5)*sizeof(int)),bzero(treeh,(n+5)*sizeof(int));
        mp.clear();while(!q.empty())q.pop();
        for(int i=0;i<=n;i++)edges[i].clear();
        for(int i=0,u,v,l,a;i<m;i++)read(u,v,l,a),edges[u].push_back({v,l}),edges[v].push_back({u,l}),q.push({a,u,v});
        {
            // priority_queue<pair<ll,int>,vector<pair<ll,int> >,greater<pair<ll,int> > >q;
            __gnu_pbds::priority_queue<pair<ll,int>,greater<pair<ll,int> > >q;
            static bool vis[maxn+10];
            bzero(vis,(n+5)*sizeof(bool)),memset(l,0x3f,(n+5)*sizeof(ll));
            q.push({l[1]=0,1});
            while(!q.empty()){
                auto [d,u]=q.top();q.pop();
                if(vis[u])continue;vis[u]=true;
                for(auto [v,w]:edges[u])if(l[v]>d+w)q.push({l[v]=d+w,v});
            }
        }
        cerr<<"dijstra done\n";
        {
            for(int i=1;i<=n;i++)mp[{i,INT_MAX}]=l[i];
            while(!q.empty()){
                auto [h,a,b]=q.top();q.pop();
                a=get_fa(a,0),b=get_fa(b,0);
                if(a==b)continue;
                if(treeh[a]<treeh[b]){
                    h_fa[a]=h,fa[a]=b;
                    mp[{b,h}]=min(mp.lower_bound({a,0})->second,mp.lower_bound({b,0})->second);
                    treeh[b]=max(treeh[a]+1,treeh[b]);
                }else{
                    h_fa[b]=h,fa[b]=a;
                    mp[{a,h}]=min(mp.lower_bound({a,0})->second,mp.lower_bound({b,0})->second);
                    treeh[a]=max(treeh[a]+1,treeh[b]);
                }
            }
        }
        cerr<<"bingchaji done\n";
        {
            ll v,p,v0,p0,q,k,s,lstans=0;
            read(q,k,s);
            while(q--){
                if(k)read(v0,p0),v=(v0+lstans-1)%n+1,p=(p0+lstans)%(s+1);
                else read(v,p);
                cout<<(lstans=query(v,p))<<'\n';
            }
        }
    }
    return 0;
}