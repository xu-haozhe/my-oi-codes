#include <bits/stdc++.h>
using namespace std;
constexpr bool FORCE_ONLINE=true;
template<class T>inline void read_(T&t_)noexcept{
    unsigned char ch=getchar();T t=0;
    while(!isdigit(ch))ch=getchar();
    while(isdigit(ch))t=t*10+(ch&0xf),ch=getchar();
    t_=t;[[assume(t_>=0)]];
}
__always_inline void read()noexcept{}
template<class T,class ...Args>__always_inline void read(T&first,Args&...args)noexcept{read_(first);read(args...);}
template<class T>inline void write_(T t_)noexcept{
    [[assume(t_>=0)]];
    if(t_==0)return (void)(putchar('0'),putchar('\n'));
    static char str[100],*p;
    for((p=str+64);t_;t_/=10)*(--p)=(t_%10)|'0';
    for(;*p;++p)putchar(*p);putchar('\n');
}
using ll=long long;using ull=unsigned long long;
using blockid=uint;using arrid=uint;
constexpr ull hightbit(ull x)noexcept{return x?(1ull<<(63-__builtin_clzll(x))):(0);}
constexpr uint maxn=1e5,maxblocknum=320,maxblocksize=320;
constexpr uint maxn_pow2=hightbit(maxn)<<1,maxblocksize_pow2=hightbit(maxblocksize)<<1;
int n,m,blocknum,blocksize,l,r;
alignas(4096)uint arr[maxn+10],pre[maxn+10],suf[maxn+10],sum_[maxblocknum][1<<17],merge_ans_block[maxblocknum+10][maxblocknum+10];constexpr uint (*sum)[1<<17]=sum_;
ull f[maxblocknum+10][maxblocknum+10],ans;
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
        uint res=0,*ia=a,*ib=b,cnt;
        while(*ia&&*ib)if(*ia<*ib)++ia,res+=ib-b;else ++ib;
        for(cnt=0;*ia;++ia)++cnt;
        return res+cnt*(ib-b);
    }
    static inline  uint calc(blockid a,blockid b)noexcept{
        uint res=0,cnt=0;auto*i=sort_arr[a],*j=sort_arr[b],*s=j;
        while(*(ull*)i&&*(ull*)j)
            if(i->v<j->v)++i,res+=j-s;else ++j;
        for(cnt=0;*(ull*)i;++i)++cnt;
        return res+ cnt*(j-s);
    }
}merge_ans;alignas(512) uint merge::a[maxblocksize_pow2],merge::b[maxblocksize_pow2];
inline ull get_ans()noexcept{
    if(l+1==r)return 0;
    uint p_lblock=p_block[l],p_rblock=p_block[r];
    auto*lblock=blocks+p_lblock,*rblock=blocks+p_rblock;
    if(p_lblock==p_rblock){
        uint*p1=merge_ans.a-1,*p2=merge_ans.b-1;
        for(auto*i=sort_arr[p_lblock];*(ull*)i;++i){
            if(i->p<l)*(++p1)=i->v;
            if((i->p>=l)&(i->p<r))*(++p2)=i->v;
        }*(p1+1)=0,*(p2+1)=0;
        return pre[r-1]-(l==lblock->l?0:pre[l-1])-merge_ans.calc();
    }else{
        ull res=0;
        res+=f[p_lblock+1][p_rblock]+suf[l]+(r==rblock->l?0:pre[r-1]);
        if(p_lblock+1!=p_rblock){
            auto&lsum=sum[p_lblock],&rsum=sum[p_rblock-1];
            for(uint*i=arr+l,*e=arr+lblock->r;i!=e;++i)res+=rsum[*i]-lsum[*i];
            res+=(rsum[n]-lsum[n])*(r-rblock->l);
            for(uint*i=arr+rblock->l,*e=arr+r;i!=e;++i)res-=rsum[*i]-lsum[*i];
        }
        uint*p1=merge_ans.a-1,*p2=merge_ans.b-1;
        for(auto*i=sort_arr[p_lblock];*(ull*)i;++i)if(i->p>=l)*(++p1)=i->v;*(p1+1)=0;
        for(auto*i=sort_arr[p_rblock];*(ull*)i;++i)if(i->p<r)*(++p2)=i->v;*(p2+1)=0;
        res+=merge_ans.calc();
        return res;
    }
    return -1;
}

int main(){
    read(n,m),blocksize=sqrt(n),blocknum=(n+blocksize-1)/blocksize,e_block=blocks+blocknum;
    for(int i=0;i<n;i++)read(arr[i]);
    for(uint i=0,cnt=0;cnt<n;i++,cnt+=blocksize)blocks[i]={i,cnt,cnt+blocksize};
    blocks[blocknum-1].r=n,blocks[blocknum]={(uint)blocknum,(uint)n,(uint)n},p_block[n]=blocknum;
    for(auto*i=blocks;i!=e_block;i++){
        alignas(4096) static uint sum_[1<<17];
        for(uint j=i->l;j<i->r;j++)sum_[arr[j]]++,sort_arr[i->id][j-i->l]={arr[j],j},p_block[j]=i->id;
        for(uint j=1;j<=n;j++)sum[i->id][j]=sum[i->id][j-1]+sum_[j];
        sort(sort_arr[i->id],sort_arr[i->id]+i->r-i->l,[](SortArr const&a,SortArr const&b){return a.v<b.v;});
        for(uint j=i->l,sum=0;j!=i->r;j++){
            pre[j]=(sum+=fenwick.query(0x1ffff-arr[j]));
            fenwick.add(0x1ffff-arr[j],1);
        }
        f[i->id][i->id+1]=pre[i->r-1];
        for(uint*j=arr+i->l,*e=arr+i->r;j!=e;j++)fenwick.add(0x1ffff-*j,-1);
        for(int j=i->r-1,sum=0;j>=(int)i->l;j--){
            suf[j]=(sum+=fenwick.query(arr[j]));
            fenwick.add(arr[j],1);
        }
        for(uint*j=arr+i->l,*e=arr+i->r;j!=e;j++)fenwick.add(*j,-1);
    }
    for(int len=2;len<=blocknum;len++)for(int i=0;i<=blocknum-len;i++)
        f[i][i+len]=f[i][i+len-1]+f[i+1][i+len]+merge_ans.calc(i,i+len-1)-f[i+1][i+len-1];
    while(m--){
        if constexpr(FORCE_ONLINE){
            static int a,b;read(a,b),a^=ans,b^=ans,l=min(a,b),r=max(a,b),l--;
        }else read(l,r),l--;
        write_(ans=get_ans());
    }
    return 0;
}