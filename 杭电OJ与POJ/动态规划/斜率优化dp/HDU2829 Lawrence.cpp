代码：
#include<iostream>
#include<algorithm>
#include<vector>
#include<cstdio>
#include<string>
#include<cstring>
using namespace std;
typedef long long ll;
const int N =1100;
int w[N];
int a[N];
int s[N];
int f[N][N];
int q[N];
int getup(int a,int b,int x){
	return f[b][x-1]+s[b]*s[b]-w[b]-f[a][x-1]-s[a]*s[a]+w[a];
}
int getdown(int a,int b){
	return s[b]-s[a];
}
int dp(int a,int x,int i){
	return f[a][x-1]-w[a]-s[a]*(s[i]-s[a])+w[i];
}
int main(){
	int i,m,n;
	while(cin>>n>>m){
		if(n==0&&m==0)
		break;
		memset(s,0,sizeof s);
		memset(w,0,sizeof w); 
		memset(f,0,sizeof f);
		for(i=1;i<=n;i++){
			cin>>a[i];
			s[i]=s[i-1]+a[i];
			w[i]=w[i-1]+s[i-1]*a[i];	
		}
		int j,x;
		for(i=1;i<=n;i++)
		f[i][0]=w[i];
		for(x=1;x<=m;x++){
			int hh=0;
			int tt=0;
			q[tt]=x;
			for(i=x+1;i<=n;i++){
				while(hh+1<=tt&&getup(q[hh],q[hh+1],x)<=s[i]*getdown(q[hh],q[hh+1]))
				hh++;
				f[i][x]=dp(q[hh],x,i);
				while(hh+1<=tt&&getup(q[tt-1],q[tt],x)*getdown(q[tt],i)>=getup(q[tt],i,x)*getdown(q[tt-1],q[tt]))
				tt--;
				q[++tt]=i;
			}
		}
		cout<<f[n][m]<<endl;
	}
} 
