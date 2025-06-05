#include<bits/stdc++.h>
using namespace std;
using ll=long long;using ull=unsigned long long;
template<class T>inline void read_(T&t_)noexcept{
    unsigned char ch=getchar();T t=0;
    while(!isdigit(ch))ch=getchar();
    while(isdigit(ch))t=t*10+ch-'0',ch=getchar();
    t_=t;[[assume(t_>=0)]];
}
__always_inline void read()noexcept{}
template<class T,class ...Args>__always_inline void read(T&first,Args&...args)noexcept{read_(first);read(args...);}
constexpr int maxn=2e5,maxm=6e5,maxq=1e6;
mt19937_64 rnd(time(0));
int n,m,q,p[maxn+10];
struct u128{
    ull a,b;
    inline u128 operator*(u128 const&y)const noexcept{return {a*y.a,b*y.b};}
    inline u128 operator+(u128 const&y)const noexcept{return {a+y.a,b+y.b};}
    inline u128&operator+=(u128 const&y)noexcept{return a+=y.a,b+=y.b,*this;}
    inline u128 operator-(u128 const&y)const noexcept{return {a-y.a,b-y.b};}
    inline u128&operator-=(u128 const&y)noexcept{return a-=y.a,b-=y.b,*this;}
    inline bool operator==(u128 const&y)const noexcept{return (a==y.a)&(b==y.b);}
}hash_x,hash_p[maxn+10],hash_a[maxm+5],hashnowa,hash_b[maxm+5],hashnowb;
struct arr{int a,b,c;}arra[maxn+10],arrb[maxn+10];
inline void adda(int p,int x){hashnowa-=hash_a[x]*hash_a[x]*hash_a[x],hash_a[x]+=hash_p[p],hashnowa+=hash_a[x]*hash_a[x]*hash_a[x];}
inline void addb(int p,int x){hashnowb-=hash_b[x]*hash_b[x]*hash_b[x],hash_b[x]+=hash_p[p],hashnowb+=hash_b[x]*hash_b[x]*hash_b[x];}
inline void modifyadd(int p)noexcept{
    adda(p,arra[p].a),adda(p,arra[p].b),adda(p,arra[p].c);
    addb(p,arrb[p].a),addb(p,arrb[p].b),addb(p,arrb[p].c);
}
inline void suba(int p,int x){hashnowa-=hash_a[x]*hash_a[x]*hash_a[x],hash_a[x]-=hash_p[p],hashnowa+=hash_a[x]*hash_a[x]*hash_a[x];}
inline void subb(int p,int x){hashnowb-=hash_b[x]*hash_b[x]*hash_b[x],hash_b[x]-=hash_p[p],hashnowb+=hash_b[x]*hash_b[x]*hash_b[x];}
inline void modifydel(int p)noexcept{
    suba(p,arra[p].a),suba(p,arra[p].b),suba(p,arra[p].c);
    subb(p,arrb[p].a),subb(p,arrb[p].b),subb(p,arrb[p].c);
}
int main(){
    read(n,m,q);
    for(auto*i=arra,*e=i+n;i!=e;i++)read(i->a,i->b,i->c);
    for(auto*i=arrb,*e=i+n;i!=e;i++)read(i->a,i->b,i->c);
    hash_x.a=rnd(),hash_x.b=rnd();
    for(int i=0;i<=n;i++)hash_p[i].a=rnd(),hash_p[i].b=rnd();
    for(int l=0,r=0;r<n;r++){
        modifyadd(r);
        while(!(hashnowa==hashnowb))modifydel(l++);
        p[r]=l;
    }
    for(int l=0,r=0;q--;){
        read(l,r);
        if(p[r-1]<l)putchar('Y'),putchar('e'),putchar('s'),putchar('\n');
        else putchar('N'),putchar('o'),putchar('\n');
    }
    return 0;
}