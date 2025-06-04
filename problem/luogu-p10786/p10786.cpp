#include<vector>
#include<bits/stdc++.h>
std::vector<int> ask(std::vector<int> a, std::vector<int> b);

namespace sovle{
    using namespace ::std;
    int n,t,s;
    inline int subtask1(){
        static vector<int>a,b;a.clear(),b.clear();
        static int cnt[1005];bzero(cnt,sizeof(cnt));
        for(int i=0;i<n;i++)for(int j=i+1;j<n;j++)a.push_back(i),b.push_back(j);
        vector<int>c=ask(a,b);
        for(auto i:c)cnt[i]++;
        for(int i=0;i<n;i++)if(cnt[i]==n-1)return i;
        return -1;
    }
    template<class It>inline void add_to_ask_list(vector<int>&va,vector<int>&vb,int num[],It b,It e){
        int n=e-b;
        for(auto i=b;i!=e;i++){
            num[*i]=n-1;
            for(auto j=i+1;j!=e;j++){
                va.push_back(*i),vb.push_back(*j);
            }
        }
    }
    inline vector<int>query(vector<int>arr,int m){
        static int cnt[1000005],num[1000005];bzero(cnt,sizeof(cnt));bzero(num,sizeof(num));
        static vector<int>va,vb,res;va.clear(),vb.clear(),res.clear();
        int n=arr.size(),a=n/m,b=a+1,y=n%m,x=m-y;
        auto it=arr.begin();
        for(int i=0;i<x;i++)add_to_ask_list(va,vb,num,it,it+a),it+=a;
        for(int i=0;i<y;i++)add_to_ask_list(va,vb,num,it,it+b),it+=b;
        vector<int>c=ask(va,vb);
        for(auto i:c)cnt[i]++;
        for(auto i:arr)if(cnt[i]==num[i])res.push_back(i);
        return res;
    }
    inline int subtask2()noexcept{
        constexpr int l[]={500000,250000,125000,62500,20832,3472,183,1};
        static vector<int>vec;vec.clear();
        for(int i=0;i<n;i++)vec.push_back(i);
        for(auto i:l)if(vec.size()>1)vec=query(vec,i);
        return vec[0];
    }
    inline int sovle(){
        if((n==1000)&&(t==1)&&(s==499500))return subtask1();
        if((n==1000000))return subtask2();
        return -1;
    }
};
int richest(int N,int T,int S){sovle::n=N,sovle::t=T,sovle::s=S;;return sovle::sovle();};