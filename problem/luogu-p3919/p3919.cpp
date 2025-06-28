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
    T d;uint mask;uint p[20]; 
}nodes[305];

inline T find(uint v,uint i)noexcept{
    while(nodes[v].mask^i)v=nodes[v].p[__builtin_ctz(nodes[v].mask^i)];
    return nodes[v].d;
}
inline void add(uint v1,uint v2,uint p,T d)noexcept{ 
    nodes[v2].d=d;
    for(uint i=0,k=p^nodes[v1].mask;i<20;i++)nodes[v2].p[i]=d&(1u<<i)?v1=nodes[v1].p[i]:v1;
}
inline void cp(uint v1,uint v2)noexcept{memcpy(nodes+v2,nodes+v1,sizeof(node));}

int n,m,v,opt,p,c;
int main(){
    read(n,m);
    for(int i=1,val;i<=n;i++)read(val),add(i-1,i,i,val);
    for(int i=1;i<=m;i++){
        read(v,opt,p);
        if(opt==1)read(c),add(v+n,i+n,p,c);
        else cout<<find(v+n,p)<<'\n',cp(v+n,v+i);
    }
    return 0;
}