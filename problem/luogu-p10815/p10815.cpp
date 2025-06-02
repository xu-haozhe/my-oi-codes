#include<bits/stdc++.h>
using namespace std;
template<class T>inline void read_(T&t_)noexcept{
    unsigned char ch=getchar();T t=0;char f=1;
    while(!isdigit(ch))(ch=='-'?f=-1:f),ch=getchar();
    while(isdigit(ch))t=t*10+(ch&0xf),ch=getchar();
    t_=t*f;
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
int n;long long a,ans;
int main(){
    read(n);
    while(n--)read(a),ans+=a;
    if(ans>=0)write_(ans);else putchar('-'),write_(-ans);
    return 0;
}