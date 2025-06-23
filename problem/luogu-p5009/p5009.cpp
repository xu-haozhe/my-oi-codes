#include <cstdint>
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include<bits/stdc++.h>
using namespace std;
template<class T>inline void read(T&t_){
    unsigned char ch=getchar();T t=0;
    while(!isdigit(ch))ch=getchar();
    while(isdigit(ch))t=t*10+(ch&0xf),ch=getchar();
    t_=t;[[assume(t_>=0)]];
}
template<class T,class...Args>__always_inline void read(T&first,Args&...args){read(first);read(args...);}
using ll=long long;
/*
0
1 0
1 1 0
1 1 0 0
1 0 1 1 0
*/
int main(){
    return 0;
}