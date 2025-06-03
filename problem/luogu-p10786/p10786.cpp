#include<vector>
#include<bits/stdc++.h>
std::vector<int> ask(std::vector<int> a, std::vector<int> b);

namespace sovle{

    using namespace ::std;
    int n,t,s;
    inline int subtaask1()noexcept{
        static vector<int>a,b;
        static int cnt[1005];
        for(int i=0;i<n;i++)for(int j=i+1;j<n;j++)a.push_back(i),b.push_back(j);
        static vector<int>c=ask(move(a),move(b));
        for(auto i:c)cnt[i]++;
        for(auto i:cnt)if(i==n-1)return i;
        return -1;
    }
    inline int subtask2()noexcept{
        constexpr int l[]={2,2,2,2,3,5,15,139};
        static int all_[2][1000005],*e=all_[0],maxnum[1000005],cnt[1000005],*all=all_[0],*old=all_[1];
        for(int i=0;i<n;i++)*(e++)=i;
        for(auto a:l){
            auto b=a+1,y=(int)(e-all)%a,x=(int)(e-all)/a-y,*p=all;
            vector<int>va,vb;
            for(int i=0;i<x;i++,p+=a)for(int j=0;j<a;j++){
                maxnum[p[j]]=a-1;
                for(int k=j+1;k<a;k++)va.push_back(p[j]),vb.push_back(p[k]);
            }
            for(int i=0;i<y;i++,p+=b)for(int j=0;j<b;j++){
                maxnum[p[j]]=b-1;
                for(int k=j+1;k<b;k++)va.push_back(p[j]),vb.push_back(p[k]);
            }
            auto vc=ask(move(va),move(vb));
            for(int *i=all;i!=e;i++)cnt[*i]=0;
            for(auto i:vc)cnt[i]++;
            int*p=old;
            for(int*i=all;i!=e;i++)if(cnt[*i]==maxnum[*i])*(p++)=*i;
            swap(old,all),e=p;
        }
    }
    inline int sovle()noexcept{
        if((n==1000)&&(s==1)&&(t==499500))return subtaask1();
        if((n==1000000))return subtask2();
        return -1;
    }
};
inline int richest(int N,int T,int S)noexcept{sovle::n=N,sovle::t=T,sovle::s=S;;return sovle::sovle();};