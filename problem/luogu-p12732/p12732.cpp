#include<bits/stdc++.h>
using namespace std;
int n,a[15],b[15],ans;
int main(){
    cin>>n;
    for(int i=0;i<n;i++)cin>>a[i];
    for(int i=0;i<n;i++)cin>>b[i];
    for(int i=1;i<n;i++){
        if((a[i-1]-b[i-1])*(a[i]-b[i])<=0)ans++;
    }
    cout<<ans;
    return 0;
}