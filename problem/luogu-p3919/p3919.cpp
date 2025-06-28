#include<bits/stdc++.h>
using namespace std;

template<class T>inline void read(T&t_)noexcept{
    char ch=getchar();T t=0;char f=1;
    while(!isdigit(ch))ch=getchar();
    while(isdigit(ch))t=t*10+(ch&0xf),ch=getchar();
    t_=t*f;
}
template<class T,class ...Args>__always_inline void read(T&first,Args&...args)noexcept{read(first);read(args...);}

using T=int;

struct node{
    uint mask;uint p[20]; 
}nodes[1000005];



int n,m,v,opt,p,c;
int main(){

    return 0;
}