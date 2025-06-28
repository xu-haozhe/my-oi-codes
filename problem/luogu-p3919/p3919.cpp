/*
1.09s/92.99mb https://www.luogu.com.cn/record/221715131
*/
#include<bits/stdc++.h>
using namespace std;
template<class T>inline void read(T&t_)noexcept{
    unsigned char ch=getchar_unlocked();T t=0;bool f=false;
    while(!isdigit(ch)){if(ch=='-'){f=true;}ch=getchar_unlocked();}
    while(isdigit(ch))t=t*10+(ch&0xf),ch=getchar_unlocked();
    t_=f?-t:t;
}
template<class T,class ...Args>__always_inline void read(T&first,Args&...args)noexcept{read(first);read(args...);}
int n,m,v,opt,p,c,arr[1000005],d[10000005];
uint mask[10000005],ptr[1000005][20];
inline int find(uint v,uint i)noexcept{
    while((mask[v]^i)&&(v))v=ptr[v][__builtin_ctz(mask[v]^i)];
    return v?d[v]:arr[i];
}
inline void add(uint v1,uint v2,uint p,int d)noexcept{ 
    ::d[v2]=d,mask[v2]=p;
    auto&v2p=ptr[v2];
    for(uint i=0;i<20;i++)
        if((p^mask[v1])&(1u<<i))v2p[i]=v1,v1=ptr[v1][i];
        else v2p[i]=ptr[v1][i];
}
inline void cp(uint v1,uint v2)noexcept{memcpy(ptr[v2],ptr[v1],20*sizeof(uint)),mask[v2]=mask[v1],d[v2]=d[v1];}
int main(){
    read(n,m);
    for(int i=1;i<=n;i++)read(arr[i]);
    for(int i=1;i<=m;i++){
        read(v,opt,p);
        if(opt==1)read(c),add(v,i,p,c);
        else cout<<find(v,p)<<'\n',cp(v,i);
    }
    return 0;
}