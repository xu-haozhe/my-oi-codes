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
namespace init_graph{
    vector<uint>edges[maxn+10];
}
int main(){

    return 0;
}