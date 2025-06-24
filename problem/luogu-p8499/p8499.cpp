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
        tr.hash[p]*=tr.hash[p]*xor_shift(tr.hash[p]);
    }
    template<class T,class Fun>inline void vec_rm_if(vector<T>&vec,Fun&&f){vec.erase(remove_if(vec.begin(),vec.end(),f),vec.end());}
    __always_inline uint8_t lowbitlg2(uint8_t x)noexcept{return __builtin_ctz(x);}
    int dfs(int p1,int p2,int m){
        if((tree1.siz[p1]<tree2.siz[p2])|(tree1.siz[p1]-tree2.siz[p2]>m))return 0xfffff;
        if(p2==0)return tree1.siz[p1];
        vector<int>v1,v2;
        {
        set<pair<ull,int>>s;
        for(auto i:tree1.son[p1])s.insert({tree1.hash[i],i});
        for(auto i:tree2.son[p2]){
            auto it=s.lower_bound({tree2.hash[i],0});
            if((it!=s.end())&&(it->first==tree2.hash[i]))s.erase(it);
            else v2.push_back(i);
        }
        for(auto i:s)v1.push_back(i.second);
        }
        int l=v1.size(),m_=1+l-m;
        if(l==0)return 0;
        if(l>m)return 0xfffff;
        for(int i=l-v2.size();i;i--)v2.push_back(0);
        vector<int>order(l);
        for(int i=0;i<l;++i)order[i]=i;
        int res=0xfffff;
        do{
            int tot=0;
            for(int i=0;i<l;i++)if((tot+=dfs(v1[order[i]],v2[i],m_))>m)break;
            res=min(res,tot);
        }while(next_permutation(order.begin(),order.end()));
        return res;
    }
    inline void sovel(){
        hash_k=xor_shift();
        tree1.input(),tree2.input();
        dfs<tree1>(tree1.root),dfs<tree2>(tree2.root);
        if(k==0){
            if(tree1.hash[tree1.root]==tree2.hash[tree2.root])cout<<"Yes\n";else cout<<"No\n";
            return;
        }
        if(dfs(tree1.root,tree2.root,k)<=k)cout<<"Yes\n";else cout<<"No\n";
    }
};
int main(){
    read(c,t,k);
    while(t--){
        solve::sovel();
    }
    return 0;
}