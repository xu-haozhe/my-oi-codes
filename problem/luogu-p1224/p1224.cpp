#include<bits/stdc++.h>
#define expect(x,y) __builtin_expect(x,y)
#define assume(x) do{if(!(x)){__builtin_unreachable();}}while(0)
#define popcountll(x) __builtin_popcountll(x)
using namespace std;
using ll=long long;using ull=unsigned long long;
int n,d,k,order[100005],p[100005];
ull x[100005][5];
inline unsigned char read1(){
    char c=getchar();
    unsigned int t=0;
    while(!isdigit(c))c=getchar();
    while(isdigit(c))t=(t<<3)+(t<<1)+c-'0',c=getchar();
    assume(k==2||k==3);
    return t%k;
}
inline unsigned char read2(){
    char c=getchar();
    while(!isdigit(c))c=getchar();
    assume(k==2||k==3);
    return (c-'0')%k;
}
inline void trans_2(ull (&a)[5],unsigned char (*read)()){
    assume(read==read1||read==read2);
    for(int i=0;i<d;i++)a[i>>6]|=((ull)read())<<(i&63);
}
inline void trans_3(ull (&a)[5],unsigned char (*read)()){
    assume(read==read1||read==read2);
    constexpr static ull b[]={0b111,0b001,0b010};
    for(int i=0;i<d;i++)a[i/21]|=b[read()]<<(i%21*3);
}
inline bool check_2_1(ull const (&a)[5],ull const (&b)[5]){return !(popcountll(a[0]&b[0])&1);}
inline bool check_2_2(ull const (&a)[5],ull const (&b)[5]){return !((popcountll(a[0]&b[0])+popcountll(a[1]&b[1]))&1);}

inline bool check_3_2(ull const (&a)[5],ull const (&b)[5]){return !( (popcountll(a[0]|b[0])+popcountll(a[1]|b[1])) %3);}
inline bool check_3_5(ull const (&a)[5],ull const (&b)[5]){return !( (popcountll(a[0]|b[0])+popcountll(a[1]|b[1])+popcountll(a[2]|b[2])+popcountll(a[3]|b[3])+popcountll(a[4]|b[4])) %3);}

inline unsigned int r(){static unsigned x=time(0);return ((x^=x<<13)^=x>>17)^=x<<5;}
int main(){
    cin>>n>>d>>k;
    assume(n>0&&n<=100000&&d>0&&d<=100);assume(k==2||k==3);

    for(int i=0;i<n;i++)order[i]=i;
    for(int i=0;i<n;i++)swap(order[r()%n],order[r()%n]);
    for(int i=0;i<n;i++)p[order[i]]=i+1;
    {
        auto*read=n<10000?read1:read2;auto*trans=k==2?trans_2:trans_3;
        for(int i=0;i<n;i++)trans(x[order[i]],read);
    }
    #define run(check) do{\
        for(int i=0;i<n;i++)for(int j=i+1;j<n;j++)\
            if(expect(check(x[i],x[j]),false))return cout<<min(p[i],p[j])<<' '<<max(p[i],p[j]),0;\
    }while(0)
    if(k==2){
        if(n<=64)run(check_2_1);
        else run(check_2_2);
    }else{
        if(n<=42)run(check_3_2);
        else run(check_3_5);
    }
    cout<<"-1 -1";
    return 0;
}