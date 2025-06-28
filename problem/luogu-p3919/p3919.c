/*
932ms/93.11mb https://www.luogu.com.cn/record/221715178
使用了 https://www.luogu.com.cn/user/929850 大佬提交记录 https://www.luogu.com.cn/record/210503174 中的的io优化代码，c版本得以卡进 1s ，感谢大佬的代码
*/
#include<stdio.h>
#include <string.h>
#include<sys/mman.h>
#define uint unsigned int
static inline int r(){
    static int i,f;static char*bf,cd[65536];
    if(!bf)for(bf=(char*)mmap((void*)1,1<<30,1,1,0,0),memset(cd,-1,65536),i=47;i++^57;)
    for(f=47;f++^57;)cd[i<<8|f]=(f-48)*10+i-48;
    for(;*bf<45;bf++);
    for(i=0,bf+=f=*bf^45?0:1;~cd[*(short*)bf];bf+=2)i=i*100+cd[*(short*)bf];
    *bf>47?i=i*10+*bf++-48:0;
    return f?-i:i;
}
static inline  void pc(char c){
    static char s[1<<16],*p=s,*q=s+sizeof(s);
    ~c?p==q&&fwrite(p=s,1,q-s,stdout),*p++=c:fwrite(s,1,p-s,stdout)&&(p=s);
}
static inline void w(int i){
    static int c[11],*p=c;
    if(i<0)i=-i,pc(45);
    do{*++p=i%10;}while(i/=10);
    for(;p!=c;)pc(*p--^48);
}
int n,m,v,opt,p,c,arr[1000005],d[10000005];
uint mask[10000005],ptr[1000005][20];


static inline int find(uint v,uint i){
    while((mask[v]^i)&&(v))v=ptr[v][__builtin_ctz(mask[v]^i)];
    return v?d[v]:arr[i];
}
static inline void add(uint v1,uint v2,uint p,int d_){ 
    d[v2]=d_,mask[v2]=p;
    uint*v2p=ptr[v2];
    for(uint i=0;i<20;i++)
        if((p^mask[v1])&(1u<<i))v2p[i]=v1,v1=ptr[v1][i];
        else v2p[i]=ptr[v1][i];
}
static inline void cp(uint v1,uint v2){memcpy(ptr[v2],ptr[v1],20*sizeof(uint)),mask[v2]=mask[v1],d[v2]=d[v1];}


int main(){
    n=r(),m=r();
    for(int i=1;i<=n;i++)arr[i]=r();
    for(int i=1;i<=m;i++){
        v=r(),opt=r(),p=r();
        if(opt==1)c=r(),add(v,i,p,c);
        else w(find(v,p)),pc('\n'),cp(v,i);
    }
    return pc(-1),0;
}