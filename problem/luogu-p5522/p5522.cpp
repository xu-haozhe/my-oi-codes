#include<bits/stdc++.h>
using namespace std;
using ll=long long;
template<class T>inline void read_(T&t_)noexcept{
    unsigned char ch=getchar();T t=0;
    while(!isdigit(ch))ch=getchar();
    while(isdigit(ch))t=t*10+ch-'0',ch=getchar();
    t_=t;[[assume(t_>=0)]];
}
inline void read_(char*t_)noexcept{
    unsigned char ch=getchar();
    while(ch==' '||ch=='\n')ch=getchar();
    while(ch!=' '&&ch!='\n'&&ch!=0xff)*t_=ch,t_++,ch=getchar();
}
__always_inline void read()noexcept{}
template<class T,class ...Args>__always_inline void read(T&first,Args&...args)noexcept{read_(first);read(args...);}
constexpr int maxn=1e5+7,maxlogn=17,k=1<<maxlogn;
int n,m,q,opt,l,r,ans;
char str[32];
struct d{//节点数据
    uint32_t a,b;//a记录确定的内容，'1'=>1, '0'/'?' =>0,b记录不确定的内容，'1'/'0'=>1,'?' =>0
    friend inline d operator+(d x,d y)noexcept{return ((x.b&y.b&x.a)^(x.b&y.b&y.a))?d{UINT_MAX,UINT_MAX}:d{x.a|y.a,x.b|y.b};}
    //如果确定的内容不冲突使用or合并，否则全部置1,统计答案时通过检测a的最高位是否为1来判断是否冲突
}val[2<<maxlogn],res;
inline d getd()noexcept{
    uint32_t a=0,b=0;static char*e=str+n;
    for(char*i=str;i!=e;i++ )
        switch(a<<=1,b<<=1,*i){case '1':a|=1,b|=1;break;case '0':b|=1;}
    return d{a,b};
}

int main(){
    read(n,m,q);
    // if(q==0) return (cout<<0),0;//特判，这将跳过之后的全部代码，不加无法通过 subtask#1
    for(int i=1;i<=m;i++)read(str),val[i|k]=getd();
    for(int i=k-1;i;i--)val[i]=val[i<<1]+val[i<<1|1];
    while(q--){
        if(read(opt,l),opt){
            for(read(str),val[l|=k]=getd();l;l>>=1)val[l>>1]=val[l]+val[l^1];
        }else{
            for(res={0,0},read(r),l--,r++,l|=k,r|=k;l^r^1;l>>=1,r>>=1){
                if(!(l&1))res=res+val[l^1];
                if(r&1)res=res+val[r^1];
            }
            if(!(res.a&(1u<<31)))ans^=(1ll<<(n-__builtin_popcount(res.b)));
        }
    }
    cout<<ans;
    return 0;
}