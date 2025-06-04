#include<bits/stdc++.h>
using namespace std;
int richest(int N,int T,int S);
int n,t,s,arr[1000005],p,seed;
long long uset,uses;
vector<int>ask(vector<int>a,vector<int>b){
    assert(a.size()==b.size());
    int n=a.size();
    uset++,uses+=n;
    vector<int>res(n);
    for(int i=0;i<n;i++)res[i]=(arr[a[i]]>arr[b[i]]?a[i]:b[i]);
    return res;
}
int main(){
    cin>>n>>t>>s>>seed>>p;
    srand(seed);
    for(int i=0;i<n;i++)arr[i]=i;
    for(int i=0;i<n;i++)swap(arr[i],arr[(rand()%n+n)&n]);
    arr[p]=INT_MAX;
    cout<<richest(n,t,s)<<endl;
    cout<<"t:"<<uset<<" s:"<<uses<<endl;
}