#include<bits/stdc++.h>
#include<ext/rope>
using namespace std;
using ll=long long;
__gnu_cxx::crope s;
ll now,t;
template<class T>inline void read(T&t_)noexcept{
    unsigned char ch=getchar();T t=0;
    while(!isdigit(ch))ch=getchar();
    while(isdigit(ch))t=t*10+ch-'0',ch=getchar();
    t_=t;[[assume(t_>=0)]];
}
template<class T,class ...Args>__always_inline void read(T&first,Args&...args)noexcept{read(first);read(args...);}
inline void insert(){
    static char buf[2ll<<20];ll n;
    read(n);
    for(char*p=buf,*e=buf+n;p!=e;p+=*p>31)
        *p=getchar();
    s.insert(now,buf,buf+n);
}
inline void del(){ll n;read(n);s.erase(now,n);}
inline void get(){
    ll n;read(n);cout<<s.substr(now,n)<<'\n';
}
inline void opt(){
    char ch=getchar(),o;
    while(ch<21)ch=getchar();o=ch;
    while(ch>32&ch<127)ch=getchar();
    switch(o){
        case 'M':read(now);break;//Move
        case 'I':insert();break;//Insert
        case 'D':del();break;//Delete
        case 'G':get();break;//Get
        case 'P':--now;break;//Prev
        case 'N':++now;break;//Next
    }
}
int main(){
    read(t);
    while(t--)
        opt();
    return 0;
}