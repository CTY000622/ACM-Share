分析：
状压dp主要的就是状态的设计，对于本题，我们知道只可能横放或者竖放，因此我们算出横放的个数
设f[i][j]为在第i列，i-1列放了横置j状态的值，最后答案就是最后一列的后面m，m-1状态j=0的情况，我们的列是从0开始的
======================================================
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
const int N=12;
ll f[N][1<<13];
int st[1<<13];
int main(){
    int i,j;
    int n,m;
    int k;
    while(cin>>n>>m){
	if(n==0&&m==0)
	break;
	memset(st,0,sizeof st);
	for(i=0;i<1<<n;i++){
		int cnt=0;
		for(j=0;j<n;j++){
			if(i>>j&1){
				if(cnt&1){
					st[i]=1;
					break;
				}
				else
				cnt=0;	
			}
			else
			cnt++;
		}
		if(cnt&1)
		st[i]=1;
	}
	memset(f,0,sizeof f);
	f[0][0]=1;
	for(i=1;i<=m;i++){
		for(j=0;j<1<<n;j++){
			for(k=0;k<1<<n;k++){
				if(j&k||st[j|k])
				continue;
				f[i][j]+=f[i-1][k];
			}
		}
	}
	cout<<f[m][0]<<endl;
	} 
    return 0;
}
