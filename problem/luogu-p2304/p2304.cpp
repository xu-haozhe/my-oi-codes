#include<bits/stdc++.h>
#include<bits/extc++.h>
namespace pbds=__gnu_pbds;

template<class T,class CMP=std::less<T>>using priority_queue=pbds::priority_queue<T,CMP>;

using ll=long long;using ull=unsigned long long;

template<class T>inline void read(T&t_)noexcept{ 
    char ch=getchar();T t=0;
    while(!isdigit(ch))ch=getchar();
    while(isdigit(ch))t=t*10+(ch^'0'),ch=getchar();
    t_=t;
    [[assume(t_>=0)]];
}
template<class T>inline void read2(T&t_)noexcept{
    char ch=getchar();T t=0;bool f=false;
    while(!isdigit(ch)){if(ch=='-')f=true;ch=getchar();}
    while(isdigit(ch))t=t*10+(ch^'0'),ch=getchar();
    t_=f?-t:t;
    [[assume(t>=0)]];
}
template<class T,class...Args>__always_inline void read(T&t_,Args&...args)noexcept{read(t_),read(args...);} 

namespace graph_raw{
    struct point{ll x,y;};
    std::vector<point>points;
    ll n;
    inline void input(){
        read(n),points.reserve(n);
        for(ll i=0,x,y;i<n;i++)read2(x),read(y),points.push_back({x,y});
        std::sort(points.begin(),points.end(),[](const point&a,const point&b){return a.y<b.y;});
    }
};
namespace dp{

};
int main(){

    return 0;
}