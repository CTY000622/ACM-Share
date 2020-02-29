分析：
本题是一道状压dp的经典题目，我相信很多人都做过最短哈密顿路径，只要做过那道题，这道题就迎刃而解。
我们自然想到可以用f[i][j]表示当前已经吃过i，这次吃的是j来表示状态，注意i是用二进制表示的，每个食物都对应一个位置
因此我们就能用除去j且包含k的集合来更新这个状态。
因为题目说如果k在j前面一个吃并且满足题目的rule，就额外加值，我们可以在预处理的时候先算，我采用了map存储，当然也可用二维数组。
因为我们转移的时候一定是刚吃k然后吃j的。
本题爆int并注意只能吃m个
==========================================================
代码：
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#include<string> 
#include<set>
#include<map>
#include<queue>
using namespace std;
typedef long long ll;
typedef pair<int,int> pll;
const int N=20;
const int inf=0x3f3f3f3f;
ll f[1<<N][N];
int i;
int n,m,k;
int a[N];
int x,y;
int w;
map<pll,int> m1;
bool check(int x){
	int res=0;
	for(i=0;i<n;i++){
		if(x>>i&1)
		res++;
	}
	if(res==m)
	return  true;
	else
	return false;
}
int main(){
   	cin>>n>>m>>k;
   	int i,j;
   	for(i=0;i<n;i++){
   		cin>>a[i];
	}
	for(i=1;i<=k;i++){
		cin>>x>>y>>w;
		x--;
		y--;
		m1[pll(x,y)]=w;	
	}
	memset(f,-0x3f,sizeof f);
	f[0][0]=0;
	for(i=0;i<1<<n;i++){
		for(j=0;j<n;j++){
			if(i>>j&1){
				f[i][j]=a[j];
			 for(k=0;k<n;k++){
				if(k==j)
				continue;
				if(i>>k&1){
					if(m1[pll(k,j)]){
						f[i][j]=max(f[i][j],f[i-(1<<j)][k]+a[j]+m1[pll(k,j)]);
					}
					else
						f[i][j]=max(f[i][j],f[i-(1<<j)][k]+a[j]);
				}
			}	
			}
			
		}
	}
	ll res=0;
	for(i=0;i<1<<n;i++){
		if(check(i)){
			for(j=0;j<n;j++){
				res=max(res,f[i][j]);
			}
		}
	}
	cout<<res<<endl;
    return 0;
}
