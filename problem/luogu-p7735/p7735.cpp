#include<bits/stdc++.h>
#if __cplusplus>=201703L
#define register
#endif
using namespace std;
#define expect(x,y) __builtin_expect(x,y)
template<class T> inline void  read(T&t)noexcept{
    register char ch=getchar();
    while(!isdigit(ch))ch=getchar();
    for(t=0;isdigit(ch);ch=getchar())t=t*10+ch-'0';
    [[assume(t>=0)]];
}
template<class T>inline void  write(T t)noexcept{
    [[assume(t>=0)]];
    static char ch[20];register char*p;
    for(*(p=ch)=t%10+'0',t/=10;t;t/=10)*(++p)=t%10+'0';
    for(;p!=(ch-1);--p)putchar(*p);
}
constexpr static int N=1e5,M=1e5;
int n,m,T,opt_id;
namespace xd_tree{
    constexpr static int logl=17,L=1<<logl;
    uint v[L<<1],va[L<<1],vb[L<<1],tag[L<<1],funl,funr,funx,funa,funb;
    inline void pd(uint p,uint ls,uint rs,uint ssiz)noexcept{
        [[assume(p<(L<<1))]][[assume(ls<(L<<1))]][[assume(rs<(L<<1))]];
        if(tag[p])tag[ls]=tag[rs]=va[ls]=va[rs]=vb[ls]=vb[rs]=tag[p],v[ls]=v[rs]=ssiz-1,tag[p]=0;
    }
    inline void pu(uint p,uint ls,uint rs)noexcept{
        [[assume(p<(L<<1))]][[assume(ls<(L<<1))]][[assume(rs<(L<<1))]];
        v[p]=v[ls]+v[rs]+(vb[ls]==va[rs]),va[p]=va[ls],vb[p]=vb[rs];
    }
    void modify_(uint p,uint l,uint r)noexcept{
        [[assume(p<(L<<1))]];
        if(funl<=l&&r<=funr)return (void)(tag[p]=va[p]=vb[p]=funx,v[p]=r-l-1);
        register uint mid=(l+r)>>1,ls=p<<1,rs=ls|1;[[assume(ls<(L<<1))]][[assume(rs<(L<<1))]];
        pd(p,ls,rs,mid-l);if(funl<mid)modify_(ls,l,mid);if(mid<funr)modify_(rs,mid,r);pu(p,ls,rs);
    }
    inline void modify(uint l,uint r,uint x)noexcept{funl=l,funr=r,funx=x,modify_(1,0,L);}
    struct query_res{
        uint a,b,x;
        constexpr inline query_res operator+(const query_res&y)const noexcept{return {a,y.b,x+y.x+((b==y.a)&(b!=0))};}
        inline query_res rev()noexcept{return {b,a,x};}
    };
    inline void query1_(uint p,uint l,uint r)noexcept{
        [[assume(p<(L<<1))]];
        if(funl<=l&&r<=funr)return (void)(funx+=v[p]+(funb==va[p]),funb=vb[p]);
        register uint mid=(l+r)>>1,ls=p<<1,rs=ls|1;[[assume(ls<(L<<1))]][[assume(rs<(L<<1))]];
        pd(p,ls,rs,mid-l);if(funl<mid)query1_(ls,l,mid);if(mid<funr)query1_(rs,mid,r);
    }
    inline void query2_(uint p,uint l,uint r)noexcept{
        [[assume(p<(L<<1))]];
        if(funl<=l&&r<=funr)return (void)(funx=v[p],funa=va[p],funb=vb[p]);
        register uint mid=(l+r)>>1,ls=p<<1,rs=ls|1;[[assume(ls<(L<<1))]][[assume(rs<(L<<1))]];
        pd(p,ls,rs,mid-l);if(funl<mid){query2_(ls,l,mid);if(mid<funr)query1_(rs,mid,r);}else if(mid<funr)query2_(rs,mid,r);
    }
    inline query_res query(uint l,uint r)noexcept{funl=l,funr=r,funa=funb=funx=0,query2_(1,0,L);return {funa,funb,funx};}
    inline void build()noexcept{
        memset(tag,0,sizeof(tag));
        for(register uint i=0;i!=L;++i)va[i|L]=vb[i|L]=i+1,v[i|L]=0;
        for(register uint i=L-1;i;--i)pu(i,i<<1,i<<1|1);
        opt_id=L+1;
    }
};
namespace tree{
    using xd_tree::modify,xd_tree::query,xd_tree::query_res;
    struct node{
        uint id,dep,siz;node*son,*fa,*top;vector<node*>sons;uint point_id;
        void dfs1()noexcept;void dfs2()noexcept;
    }nodes[N+10];
    inline void node::dfs1()noexcept{
        siz=1;
        for(auto i:sons)if(expect(i!=fa,1)){
            i->fa=this,i->dep=dep+1,i->dfs1(),siz+=i->siz;
            if((!son)||i->siz>son->siz)son=i;
        }
    }
    static uint cnt_id=1;
    inline void node::dfs2()noexcept{
        id=++cnt_id;
        if(son)son->top=top,son->dfs2();
        for(auto i:sons)if(expect((i!=fa)&(i!=son),1))i->top=i,i->dfs2();
    }
    inline void build()noexcept{
        for(int i=1;i<n;++i){
            static uint u,v;
            read(u),read(v);
            nodes[u].sons.push_back(nodes+v),nodes[v].sons.push_back(nodes+u);
        }
        nodes[1].fa=nullptr,nodes[1].dep=1,nodes[1].dfs1(),nodes[1].top=nodes+1,nodes[1].dfs2(),xd_tree::build();
    }
    inline void opt_set(uint a_,uint b_)noexcept{
        register node*a=nodes+a_,*b=nodes+b_;opt_id++;
        while(a->top!=b->top)
            if(a->top->dep<b->top->dep)modify(b->top->id,b->id+1,opt_id),b=b->top->fa;
            else modify(a->top->id,a->id+1,opt_id),a=a->top->fa;
        if(a->dep<b->dep)swap(a,b);modify(b->id,a->id+1,opt_id);
    }
    inline void opt_get(uint a_,uint b_)noexcept{
        register node*a=nodes+a_,*b=nodes+b_;uint ans=0;
        query_res resa={0,0,0},resb={0,0,0};
        while(a->top!=b->top)
            if(a->top->dep<b->top->dep)resb=query(b->top->id,b->id+1)+resb,b=b->top->fa;
            else resa=query(a->top->id,a->id+1)+resa,a=a->top->fa;
        if(a->dep<b->dep) ans=(resa.rev()+query(a->id,b->id+1)+resb).x;
        else ans=(resb.rev()+query(b->id,a->id+1)+resa).x;
        write(ans),putchar('\n');
    }
    inline void clear(){memset(nodes,0,sizeof(node)*(n+5)),opt_id=0,cnt_id=1;}
};
using tree::build,tree::opt_set,tree::opt_get,tree::clear;
int main(){
    for(auto&i:tree::nodes)i.point_id=&i-tree::nodes;
    read(T);
    while(T--){
        read(n),read(m),build();
        while(m--){
            static int opt,a,b;
            read(opt),read(a),read(b);
            if(opt==1)opt_set(a,b);else opt_get(a,b);
        }
        clear();
    }
    return 0;
}