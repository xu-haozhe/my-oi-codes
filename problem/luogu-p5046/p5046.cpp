#include<bits/stdc++.h>
using namespace std;
using ll=long long;using ull=unsigned long long;
using blockid=unsigned int;using arriterid=unsigned int;
#if __cplusplus<201703L
    #error "must use c++17 or above"
#endif
template<class T>inline void read_(T&t_)noexcept{
    unsigned char ch=getchar();T t=0;
    while(!isdigit(ch))ch=getchar();
    while(isdigit(ch))t=t*10+ch-'0',ch=getchar();
    t_=t;[[assume(t_>=0)]];
}
__always_inline void read()noexcept{}
template<class T,class ...Args>__always_inline void read(T&first,Args&...args)noexcept{read_(first);read(args...);}
constexpr int maxn=1e5,maxm=1e5,maxblocknum=320;
ll n,m,block_siz,block_num,lastans=0;
int sum[maxblocknum+10][maxn+10];
namespace fenwick{
    alignas(4096)ull val[1<<17];
    inline void add(uint p,ull v)noexcept{for(;p<(1<<!7);p+=p&-p)val[p]+=v;}
    inline ull query(uint p)noexcept{ull res=0;for(;p;p&=p-1)res+=val[p];return res;}
    __always_inline void clear()noexcept{bzero(val,sizeof(val));}
};
struct Arr{int v;ll pre,suf;}arr[maxn];
struct sortarr{int v;Arr*p;__always_inline bool operator<(sortarr&b)const noexcept{return v<b.v;};}arr_sort[maxn];
struct block{
    blockid id;arriterid b,e;
    Arr*arrb,*arre;sortarr*sorta,*sorte;
    ll num,siz;int (*sum)[maxn+10];
    inline void intiarrptr()noexcept{
        siz=e-b,arrb=arr+b,arre=arr+e,sorta=arr_sort+b,sorte=arr_sort+e,sum=::sum+id;
    }
    inline void init();
}blocks[maxblocknum+10],*e_block;
inline void block::init()noexcept{
    this->intiarrptr(),sort(sorta,sorte);
    using namespace fenwick;clear();
    for(auto i=arrb;i!=arre;++i)i->pre=(num+=query((1<<17)-1)-query(i->v)),add(i->v,1);
    clear(),num=0;
    for(auto i=arre-1;i!=arrb-1;--i)i->suf=(num+=query(i->v-1)),add(i->v,1);
}
inline ull get_merge_ans(block*a,block*b){
    ull res=0,cnt=0;sortarr*ia=a->sorta,*ib=b->sorta,*ea=a->sorte,*eb=b->sorte;
    while((ia!=ea)&(ib!=eb))
        if(ia->v<ib->v)res+=cnt,++a;else ++cnt,++b;
    return res;
}
inline ull get_merge_ans(block*a,block*b,Arr*b1,Arr*e2){
    ull res=0,cnt=0;sortarr*ia=a->sorta,*ib=b->sorta,*ea=a->sorte,*eb=b->sorte;
    while((ia!=ea)&(ib!=eb)){
        while(ia!=ea&&ia->p<b1)++ia;
        while(ib!=eb&&ib->p>e2)++ib;
        if(ia->v<ib->v)res+=cnt,++a;else ++cnt,++b;
    }
    return res;
}
inline ull get_merge_ans(block*a,block*b,Arr*e1,Arr*b2,Arr*e2){
    ull res=0,cnt=0;sortarr*ia=a->sorta,*ib=b->sorta,*ea=a->sorte,*eb=b->sorte;
    while((ia!=ea)&(ib!=eb)){
        while(ia!=ea&&ia->p>e1)++ia;
        while(ib!=eb&&(ib->p>e2|ib->p<b2))++ib;
        if(ia->v<ib->v)res+=cnt,++a;else ++cnt,++b;
    }
    return res;
}
namespace whole_block{
    ull f[maxblocknum+10][maxblocknum+10];
    inline void init()noexcept{
        for(int i=0;i<block_num;++i)f[i][i+1]=blocks[i].num;
        for(int i=2;i<=block_num;++i)
            for(int j=0;j<block_num-i;++j)
                f[j][j+i]=f[j][j+i-1]+f[j+1][j+i]-f[j+1][j+i-1]+get_merge_ans(blocks+j,blocks+j+i);
    }
    __always_inline ull get_whole_block_ans(blockid b,blockid e)noexcept{return f[b][e];}
};using whole_block::get_whole_block_ans;
inline void init()noexcept{
    read(n,m),block_siz=sqrt(n),block_num=(n+block_siz-1)/block_siz,e_block=blocks;
    for(int i=0;i<n;i++)read(arr[i].v);
    for(int i=0;i<block_num-1;i++)blocks[i].id=i,blocks[i].e=blocks[i+1].b=blocks[i].b+block_siz;
    (e_block-1)->id=block_num-1,e_block->e=n;
    for(auto*i=blocks;i!=e_block;++i)i->init();
    static int a[maxn+10];
    for(auto*i=blocks;i!=e_block;++i){
        for(auto*j=i->arrb,*e=i->arre;j!=e;++j)++a[j->v];
        auto&sum=*(i->sum+1);for(int j=1;j<n;j++)sum[j]=sum[j-1]+a[j];
    }
}
inline ull get_ans(arriterid l,arriterid r)noexcept{
    auto*bl=blocks+l/block_siz,*br=blocks+r/block_siz;
    auto*arrl=arr+l,*arrr=arr+r;
    if(bl=br){
        if(arrl==arrr)return 0;
        if(arrl=bl->arrb)return (arrl-1)->pre;
        return (arrr-1)->pre - (arrl-1)->pre - get_merge_ans(bl,bl,arrl,arrl-1,arrr);
    }else{

    }
}
int main(){
    init();
    while(m--){
        int l,r;read(l,r),l^=lastans,r^=lastans,l--;
    }
    return 0;
}