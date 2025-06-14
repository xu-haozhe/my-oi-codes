#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
namespace pbds{using namespace __gnu_pbds;};
template<class K,class V,class CMP=std::less<K> >using map=pbds::tree<K,V,CMP,pbds::rb_tree_tag>;
// template<class K,class CMP=std::less<K> >using set=pbds::tree<K,pbds::null_type,CMP,pbds::rb_tree_tag>;
template<class T,class CMP=std::less<T> >using priority_queue=pbds::priority_queue<T,CMP>;
// template<class K,class V,class CMP=std::less<K> >using map=std::map<K,V,CMP>;
template<class K,class CMP=std::less<K> >using set=std::set<K,CMP>;
// template<class T,class CMP=std::less<T> >using priority_queue=std::priority_queue<T,std::vector<T>,CMP>;
template<class T>inline void read(T&t_)noexcept{
    unsigned char ch=getchar();T t=0;
    while(!isdigit(ch))ch=getchar();
    while(isdigit(ch))t=t*10+(ch&0xf),ch=getchar();
    t_=t;[[assume(t_>=0)]];
}
template<class T,class ...Args>__always_inline void read(T&first,Args&...args)noexcept{read(first);read(args...);}
using ll=long long;using ull=unsigned long long;
constexpr ll maxn=7e4,maxm=1.5e5;
struct city{
    int x,y,ans;std::vector<int>jumpers;
}citys[maxn+10];using cityid=int;
struct jumper{
    int l,r,u,d,t;
    template<class F>inline void for_each(F&&func)const noexcept;
    inline bool operator<(const jumper&j)const noexcept{return t>j.t;}
    inline jumper add_t(int dt)noexcept{return jumper{l,r,u,d,t+dt};}
}jumpers[maxm+10];using jumperid=int;
namespace segment_tree{ 
    constexpr int depn=17,k=1<<depn;
    struct cmp_helper{int x;};
    struct cmp{
        using is_transparent = void;
        inline bool operator()(int const&a,int const&b)const noexcept{return (((ll)citys[a].y)<<32|citys[a].x)<(((ll)citys[b].y)<<32|citys[b].x);}
        inline bool operator()(cmp_helper const&a,int const&b)const noexcept{return (((ll)a.x)<<32)<(((ll)citys[b].y)<<32|citys[b].x);}
        inline bool operator()(int const&a,cmp_helper const&b)const noexcept{return (((ll)citys[a].y)<<32|citys[a].x)<(((ll)b.x)<<32);}
    };
    set<int,cmp>val[k<<1];
    inline void add(cityid p)noexcept{for(int x=citys[p].x|k;x;x>>=1)val[x].insert(p);}
    inline void del(cityid p)noexcept{for(int x=citys[p].x|k;x;x>>=1)val[x].erase(p);}
    
    template<class F>inline void for_range(int l,int r,F&&func)noexcept{
        for(l--,l|=k,r|=k;l^r^1;l>>=1,r>>=1){
            if(!(l&1))func(val[l^1]);
            if(r&1)func(val[r^1]);
        }
    }
};
template<class F>inline void jumper::for_each(F&&func)const noexcept{
    using namespace segment_tree;
    for_range(l,r,[&](auto&v){
        for(decltype(val->begin())i=v.lower_bound(cmp_helper{d}),e=v.lower_bound(cmp_helper{u}),t;i!=e;t=i++,del(*t))
            func(*i,this->t);
    });
}
priority_queue<jumper>pq;
int n,m,w,h;
int main(){
    read(n,m,w,h);
    for(int i=0;i<n;i++)read(citys[i].x,citys[i].y),segment_tree::add(i);
    for(int i=0,p;i<m;i++){
        read(p,jumpers[i].t,jumpers[i].l,jumpers[i].r,jumpers[i].d,jumpers[i].u);
        jumpers[i].r++,jumpers[i].u++;
        citys[p-1].jumpers.push_back(i);
    }
    int cnt=n-1;segment_tree::del(0);
    for(auto i:citys->jumpers){
        auto&j=jumpers[i];
        pq.push(j);
    }
    while(cnt){
        auto now=pq.top();pq.pop();
        now.for_each([&](cityid p,int t){
            cnt--;
            auto&c=citys[p];
            c.ans=t;
            for(auto i:c.jumpers){
                auto&j=jumpers[i];
                pq.push(j.add_t(t));
            }
        });
    }
    for(int i=1;i<n;i++)std::cout<<(citys[i].ans)<<"\n";
    return 0;
}