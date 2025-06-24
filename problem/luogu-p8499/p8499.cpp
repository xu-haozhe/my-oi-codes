#include <algorithm>
#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace std;
using ll=long long;using ull=unsigned long long;
int c,t,k;
ull xor_shift_rand_=((ull)time(0))<<48|((ull)time(0))<<32|((ull)time(0))<<16|time(0);
ull xor_shift(){return (((xor_shift_rand_^=xor_shift_rand_<<13)^=xor_shift_rand_>>17)^=xor_shift_rand_<<5);}
ull xor_shift(ull x)noexcept{return (x)^(x<<17)^(x>>13)^(x<<5);}
template<class T>inline void read(T&t_)noexcept{
    unsigned char ch=getchar_unlocked();T t=0;
    while(!isdigit(ch))ch=getchar_unlocked();
    while(isdigit(ch))t=t*10+(ch&0xf),ch=getchar_unlocked();
    t_=t;[[assume(t_>=0)]];
}
template<class T,class...Args>inline void read(T&a_,Args&...args_)noexcept{read(a_);read(args_...);}
template<class T>inline void read2(T&t_)noexcept{
    unsigned char ch=getchar_unlocked();T t=0;
    while(!isdigit(ch)){if(ch=='-'){t_=0;while(isdigit(getchar_unlocked())){};return;}
    ch=getchar_unlocked();}
    while(isdigit(ch))t=t*10+(ch&0xf),ch=getchar_unlocked();
    t_=t;[[assume(t_>=0)]];
}
constexpr int maxn=1e5;
namespace solve{
    struct tree{
        static constexpr int arrsiz=maxn+5;
        int n,root,siz[arrsiz];
        ull hash[arrsiz];
        vector<int>son[arrsiz];
        inline void input()noexcept{ 
            for(int i=1;i<=n;++i)son[i].clear();
            read(n);
            for(int i=1,f;i<=n;++i)read2(f),f?son[f].push_back(i):(void)(root=i);
        }
    }tree1,tree2;
    ull hash_k;
    template<tree&tr>void dfs(int p)noexcept{
        tr.hash[p]=hash_k;
        for(auto i:tr.son[p])dfs<tr>(i),tr.siz[p]+=tr.siz[i],tr.hash[p]+=xor_shift(tr.hash[i]);
    }
    template<class T,class Fun>inline void vec_rm_if(vector<T>&vec,Fun&&f){vec.erase(remove_if(vec.begin(),vec.end(),f),vec.end());}
    __always_inline uint8_t lowbitlg2(uint8_t x)noexcept{return __builtin_ctz(x);}
    template<class Fun>int check_each(uint8_t mask,uint8_t dep,Fun&&f){
        if(!dep)return true;
        for(uint8_t i=mask;i;i&=-i){
            if(f(lowbitlg2(i),dep-1)&&check_each(mask^(i&-i),dep-1,f));
        }
    }
    int dfs(int p1,int p2,int m){
        if((tree1.siz[p1]<tree2.siz[p2])|(tree1.siz[p1]-tree2.siz[p2]>m))return 0xfffff;
        map<ull,vector<int>::iterator>mp;
        vector<int>&v1=tree1.son[p1],&v2=tree2.son[p2];
        for(auto it=v1.begin();it!=v1.end();++it)mp.insert({tree1.hash[*it],it});
        for(auto&i:v2){
            auto it=mp.find(tree2.hash[i]);
            if(it!=mp.end())i=0,*(it->second)=0;
        }
        vec_rm_if(v1,[](int x){return !x;}),vec_rm_if(v2,[](int x){return !x;});
        if(v1.size()>k)return 0xfffff;
        
    }
    inline void sovel(){
        tree1.input(),tree2.input();
        dfs<tree1>(tree1.root),dfs<tree2>(tree2.root);
    }
};
int main(){
    read(c,t,k);
    assert(k==0);
    while(t--){

    }
    return 0;
}