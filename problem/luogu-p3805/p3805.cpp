#include<bits/stdc++.h>
using namespace std;
char s[2205]={1};
int p[2205],c,r,ans;
int main(){
    for(char*i=s+1;(*i=getchar())!=EOF;++i)*(++i)=1;
    for(int i=1;s[i]!=EOF;++i){
        if(i<=r)p[i]=min(p[(c<<1)-i],r-i);else p[i]=1;
        while(s[i-p[i]]==s[i+p[i]])++p[i];
        if(i+p[i]>r)c=i,r=i+p[i];
    }
    for(int i=1;s[i]!=EOF;++i)ans=max(ans,p[i]-1);
    cout<<ans;
    return 0;
}