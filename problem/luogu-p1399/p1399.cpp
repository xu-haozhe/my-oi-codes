#include<bits/stdc++.h>
using namespace std;
using ll=long long;
ll n,a,b,l,cycles_len,ans1,ans2=LONG_LONG_MAX;
#define DEBUG
#ifdef DEBUG
class node;
struct edge{ll len;node*to;};
struct node:vector<edge>{ll id;node();}nodes[100005];
node::node():id(this-nodes){}
#else
struct edge{ll len;vector<edge>*to;};
typedef vector<edge> node;node nodes[100005];
#endif
struct cycle{ll a,b;node*p;}cycles[200005];
struct data2{ll len,id;inline bool operator<(const data2&y)const{return len<y.len;}};
priority_queue<data2>q1,q2;
namespace find_cycles{
    node*a[100005],**l,**r;bool vis[100005];
    bool dfs(node**p,node*fa=nullptr){
        auto now=*p;
        if(vis[now-nodes])
            return r=p,true;
        vis[now-nodes]=true;
        for(auto i:*now)if(i.to!=fa)if(*(p+1)=i.to,dfs(p+1,now))return true;
        return false;
    }
    inline void find_cycles(){
        *a=nodes+1,dfs(a);
        for(auto&i:a)if(i==*r){l=&i;break;}
        cycles_len=r-l;
        for(int i=0;i<cycles_len;++i){
            static ll len;static auto j=nodes->begin();static node*e;
            for(j=l[i]->begin(),e=l[i+1];;j++)if(j->to==e){len=j->len;l[i]->erase(j);break;}
            for(j=l[i+1]->begin(),e=l[i];assert(j!=l[i+1]->end()),true;j++)if(j->to==e){l[i+1]->erase(j);break;}
            cycles[i+1].a=cycles[i].a+len;
            cycles[i+1].b=cycles[i].b-len;
            cycles[i].p=l[i];
        }
        for(int i=0;i<cycles_len;++i){
            cycles[i+cycles_len].a=cycles[i].a+cycles[cycles_len].a;
            cycles[i+cycles_len].b=cycles[i].b+cycles[cycles_len].b;
            cycles[i+cycles_len].p=cycles[i].p;
        }
    }
};
ll dfs_len;node*dfs_p;
inline void dfs_(node*p,void*fa,ll len){
    if(len>dfs_len)dfs_len=len,dfs_p=p;
    for(auto i:*p)if(i.to!=fa)dfs_(i.to,p,len+i.len);
}
inline void dfs(node*p){dfs_len=-1,dfs_(p,nullptr,0);}

int main(){
    cin>>n;
    for(int i=0;i<n;i++)cin>>a>>b>>l,nodes[a].push_back({l,nodes+b}),nodes[b].push_back({l,nodes+a});
    find_cycles::find_cycles();
    for(int i=0;i<cycles_len;i++){
        dfs(cycles[i].p);
        cycles[i].a+=dfs_len,cycles[i].b+=dfs_len;
        cycles[i+cycles_len].a+=dfs_len,cycles[i+cycles_len].b+=dfs_len;
        dfs(dfs_p);
        ans1=max(ans1,dfs_len);
    }
    for(int i=0;i<cycles_len;i++)q1.push(data2{cycles[i].a,i}),q2.push(data2{cycles[i].b,i});
    for(int i=0;i<cycles_len;i++){
        while(q1.top().id<i)q1.pop();while(q2.top().id<i)q2.pop();
        if(q1.top().id==q2.top().id){
            auto t1=q1.top(),t2=q2.top();q1.pop(),q2.pop();
            while(q1.top().id<i)q1.pop();while(q2.top().id<i)q2.pop();
            ans2=min(ans2,max(t1.len+q2.top().len,q1.top().len+t2.len));
            q1.push(t1),q2.push(t2);
        }else ans2=min(ans2,q1.top().len+q2.top().len);
        q1.push(data2{cycles[i+cycles_len].a,i+cycles_len}),q2.push(data2{cycles[i+cycles_len].b,i+cycles_len});
    }
    cout<<fixed<<setprecision(1)<<((double)max(ans1,ans2))/2;
    return 0;
}