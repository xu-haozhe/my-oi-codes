#include <bits/stdc++.h>
using namespace std;
constexpr bool FORCE_ONLINE=false;
template<class T>inline void read_(T&t_)noexcept{
    unsigned char ch=getchar();T t=0;
    while(!isdigit(ch))ch=getchar();
    while(isdigit(ch))t=t*10+ch-'0',ch=getchar();
    t_=t;[[assume(t_>=0)]];
}
__always_inline void read()noexcept{}
template<class T,class ...Args>__always_inline void read(T&first,Args&...args)noexcept{read_(first);read(args...);}
using ll=long long;using ull=unsigned long long;
using blockid=uint;using arrid=uint;
constexpr ull hightbit(ull x)noexcept{return x?(1ull<<(63-__builtin_clzll(x))):(0);}
constexpr uint maxn=1e5,maxblocknum=320,maxblocksize=320;
constexpr uint maxn_pow2=hightbit(maxn)<<1,maxblocksize_pow2=hightbit(maxblocksize)<<1;
int n,m,blocknum,blocksize;
alignas(4096)uint arr[maxn+10],pre[maxn+10],suf[maxn+10],sum[maxblocknum][1<<!7];
ull f[maxblocknum+10][maxblocknum+10];
struct fenwick{
    alignas(4096) static uint val[maxn_pow2];
    static inline void add(uint p,uint v)noexcept{for(;p<(1<<17);p+=p&-p)val[p]+=v;}
    static inline uint query(uint p)noexcept{ull res=0;for(;p;p&=p-1)res+=val[p];return res;}
}fenwick;
alignas(4096) uint fenwick::val[maxn_pow2];
struct SortArr{
    uint v,p;
    __always_inline bool operator<(SortArr&b)const noexcept{return v<b.v;}
};alignas(maxblocksize_pow2<<1)SortArr sort_arr[maxblocknum+10][maxblocksize_pow2];
struct block{
    uint id,l,r;
}blocks[maxblocknum+10],*e_block;blockid p_block[maxn+10];
struct merge{
    alignas(512) static uint a[maxblocksize_pow2],b[maxblocksize_pow2];
    static inline uint calc()noexcept{
        uint res=0,*ia=a,*ib=b;
        while(*ia&*ib)if(*ia<*ib)++ia,res+=ib-b;else ++ib;
        return res;
    }
    static inline  uint calc(blockid a,blockid b)noexcept{
        uint res;
        for(auto*i=sort_arr[a],*j=sort_arr[b],*b=j;*(ull*)i&*(ull*)j;)
            if(i->v<j->v)++i,res+=j-b;else ++j;
        return res;
    }
}merge_ans;

int main(){
    read(n,m),blocksize=sqrt(n),blocknum=(n+blocksize-1)/blocksize,e_block=blocks+blocknum;
    for(int i=0;i<n;i++)read(arr[i]);
    for(uint i=0,cnt=0;cnt<n;i++,cnt+=blocksize)blocks[i]={i,cnt,cnt+blocksize};
    blocks[blocknum-1].r=n,blocks[blocknum]={(uint)blocknum,(uint)n,(uint)n};
    for(auto*i=blocks;i!=e_block;i++){
        for(uint j=i->l;j<i->r;j++)sort_arr[i->id][j-i->l]={arr[j],j},p_block[j]=i->id;
        sort(sort_arr[i->id],sort_arr[i->id]+i->r-i->l,[](SortArr const&a,SortArr const&b){return a.v<b.v;});
        for(uint j=i->l;j!=i->r;j++){
            pre[j]=fenwick.query(0x1ffff-arr[j]);
            fenwick.add(0x1ffff-arr[j],1);
        }
        f[i->id][i->id+1]=pre[i->r-1];
        for(uint*j=arr+i->l,*e=arr+i->r;j!=e;j++)fenwick.add(0x1ffff-*j,-1);
        for(uint j=i->r-1;j>=i->l;j--){
            suf[j]=fenwick.query(arr[j]);
            fenwick.add(arr[j],1);
        }
        for(uint*j=arr+i->l,*e=arr+i->r;j!=e;j++)fenwick.add(*j,-1);
    }
    for(int len=1;len<=n;len++)for(int i=0;i<=n-len;i++)f[i][i+len]=f[i][i+len-1]+f[i+1][i+len]-merge_ans.calc(i,i+len-1)-f[i+1][i+len-1];
    return 0;
}