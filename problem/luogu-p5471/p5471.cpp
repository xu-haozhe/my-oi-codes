#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
namespace pbds{using namespace __gnu_pbds;};
template<class K,class V,class CMP=std::less<K> >using map=pbds::tree<K,V,CMP,pbds::rb_tree_tag>;
template<class K,class CMP=std::less<K> >using set=pbds::tree<K,pbds::null_type,CMP,pbds::rb_tree_tag>;
template<class T,class CMP=std::less<T> >using priority_queue=pbds::priority_queue<T,CMP>;
using ll=long long;using ull=unsigned long long;
constexpr ll maxn=7e4;
class node;class jumper;
struct jumper{
    int l,r,u,d;ll t;
    template<class Fun>inline void run(Fun fun)noexcept;
    inline jumper add_t(ll dt)noexcept{return {l,r,u,d,t+dt};};
};
struct node{int id;std::vector<jumper>jmp;};
map<int,map<int,node> >mp;
template<class Fun>inline void jumper::run(Fun fun)noexcept{
    for(auto i=mp.lower_bound(l),e=mp.lower_bound(r);i!=e;i++){
        auto&m=i->second;
        for(auto j=m.lower_bound(u),e=m.upper_bound(d);j!=e;j=m.erase(j))fun(j,t);
    }
}
struct jumper_cmp{inline bool operator()(const jumper&a,const jumper&b){return a.t>b.t;}};
ll n,ans[maxn+10];
inline void sovel(){
    int num=n;
    priority_queue<jumper,jumper_cmp>updates;
    while(n){
        auto&jmp=updates.top();updates.pop();auto t=jmp.t;
        jmp.run([](auto it,ll t){

        });
    }
}
int main(){
    int arr[10];
    std::sort(arr,arr,[](int a,int b){return a>b;});
    return 0;
}