代码：
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<vector> 
using namespace std;
typedef long long ll;
const ll N=5e5+10;
const ll inf=0x3f3f3f3f;
ll a[N];
ll q[N];
ll s[N];
ll f[N];
ll getup(ll j,ll i){
	return f[i]-s[i]+a[i+1]*i-(f[j]-s[j]+a[j+1]*j);
}
ll getdown(ll j,ll i){
	return a[i+1]-a[j+1];
}
ll getdp(ll j,ll i){
	return f[j]+s[i]-s[j]-a[j+1]*(i-j);
}
int main(){
	ll n;
	ll t,m;
	cin>>t;
	while(t--){
		cin>>n>>m;
		ll i;
		memset(f,0x3f,sizeof f);
		memset(s,0,sizeof s);
		f[0]=0;
		for(i=1;i<=n;i++){
			scanf("%lld",&a[i]);
			s[i]=s[i-1]+a[i];
		}
		ll tt=0;
		ll hh=0;
		q[0]=0;
		for(i=1;i<=n;i++){
			while(hh+1<=tt&&getup(q[hh],q[hh+1])<=getdown(q[hh],q[hh+1])*i)
			hh++;
			f[i]=getdp(q[hh],i);
			ll j=i-m+1;
			if(j<m)
			continue; 
			while(hh+1<=tt&&getup(q[tt-1],q[tt])*getdown(q[tt],j)>=getdown(q[tt-1],q[tt])*getup(q[tt],j))
			tt--;
			q[++tt]=j;
		}
		cout<<f[n]<<endl;
	}
}
