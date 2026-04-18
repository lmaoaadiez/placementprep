#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define vll vector<ll>
#define ull unsigned long long
#define vull vector<ull>
int main(){
    int t=1;
    while(t--){
        ll n,k;
        cin>>n>>k;
        // cout<<n<<" "<<k<<endl;
        vll x(2*n);
        for(ll i=0;i<n;i++)cin>>x[i];
        for(ll i=n;i<2*n;i++)x[i]=x[i-n];
        vector<vector<ll>>table(20,vector<ll>(2*n+1,2*n));
        ll curr =0;
        ll r = 0;
        ll l =0;
        while(l<2*n){
            while(r<2*n && curr+x[r]<=k){
                curr+=x[r];
                r++;
            }
            table[0][l]=r;
            curr-=x[l];
            l++;
        }
        table[0][2*n]=2*n;
        for(ll i=1;i<20;i++){
            for(ll j=0;j<2*n;j++){
                table[i][j]=table[i-1][table[i-1][j]];
            }
        }
        ll ans =n;
        for(ll i=0;i<n;i++){
            ll start = i;
            ll temp =0;
            for(ll j=19;j>=0;j--){
                if(table[j][start]<i+n){
                    temp+=((1ll<<j));
                    start = table[j][start];
                }
            }
            temp++;
            ans=min(ans,temp);
            // cout<<temp<<endl;
        }
        cout<<ans<<endl;
        
    }
}
