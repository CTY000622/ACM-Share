分析：
本题是一道经典的TSP问题，但是不同的是，这个题目他每个点可以走很多次，这也就意味着我们需要用最短路算法来求两点之间的最小距离。
本题数据范围很小，因此用floyd傻瓜算法是代码量最小的，floyd的本质是动态规划，过程是枚举每一个点作为中间节点
之后就用状压dp来做，我在查询资料的时候发现，因为最后要回到0点，所以很多人有不同的做法，有些人把n++，让第一位作为0点，我觉得没有必要。
这样思考容易在代码上出错，因此我提供一种比较好的状态设计，我们还是将第0位到第n-1位作为1-n这些点，然后枚举点数的时候从1枚举到n，而不是从0-n-1
但是在右移计算的时候，将点数-1运算，这样就和普通的状压一毛一样，具体可结合注释观看。
=========================================================================
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
const int N=13;
const int inf=0x3f3f3f3f;
int g[N][N];
int f[1<<N][N];
int n; 
void floyd(){
	int i,j,k;
	for(k=0;k<=n;k++){
		for(i=0;i<=n;i++){
			for(j=0;j<=n;j++){
				g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
			}
		}
	}
}
int main(){
    int i,j,k;
    while(cin>>n,n){
    for(i=0;i<=n;i++){
    	for(j=0;j<=n;j++)
    	cin>>g[i][j];
	}
	floyd();
	memset(f,0x3f,sizeof f);
	f[0][0]=0;
	for(i=0;i<1<<n;i++){
		for(j=1;j<=n;j++){//枚举1-n这些点 
			if((i>>(j-1))&1){//但是位置对应的是0-n-1，所以-1 
				if(i==(1<<(j-1)))
				f[i][j]=g[0][j];
				else{
				for(k=1;k<=n;k++){ 
					if(k==j)
					continue;
					if((i>>(k-1))&1){
						f[i][j]=min(f[i][j],f[i-(1<<(j-1))][k]+g[k][j]);
					}
				}	
				}
			}
		}
	}
	int res=0x3f3f3f3f;
	for(i=1;i<=n;i++){//这样f[(1<<n)-1][i]中存的就是从遍历完所有点的最短消费，之后回到原点 
		res=min(res,f[(1<<n)-1][i]+g[i][0]);
	}
	cout<<res<<endl;
	}
    return 0;
}
