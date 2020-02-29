分析：
典型的棋盘型状压，这类问题都是记录合法状态和枚举合法状态即可
=====================================
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
const int N=102;
int f[2][1<<10][1<<10];
int g[1025];
int cnt[1025];
vector<int> st;
int n,m;
int count(int x){
	int i;
	int res=0;
	for(i=0;i<m;i++){
		if(x>>i&1)
		res++;
	}
	return res;
}
int main(){
    int i,j;
    cin>>n>>m;
    char s;
    for(i=1;i<=n;i++){
    	for(j=0;j<m;j++){
    		cin>>s;
    		g[i]+=(s=='H')<<j;
		}
	}
	int flag=0;
	for(i=0;i<1<<m;i++){
		for(j=0;j<m;j++){
			if(i>>j&1){
				if(i>>(j+1)&1||i>>(j+2)&1){
					flag=1;	
					break;
				}
				
			}
		}
		if(!flag){
			st.push_back(i);
			cnt[i]=count(i);
		}
		flag=0;
	}
	int k,l;
	for(i=1;i<=n;i++){
		for(j=0;j<st.size();j++){
			for(k=0;k<st.size();k++){
				for(l=0;l<st.size();l++){
					int a=st[j],b=st[k],c=st[l];
					if(a&b|b&c|c&a)
					continue;
					if(g[i]&a|g[i-1]&b)
					continue;
					f[i&1][j][k]=max(f[i&1][j][k],f[i-1&1][k][l]+cnt[a]);
				}		
			}
		}
	}
	int res=0;
	for(i=0;i<st.size();i++){
		for(j=0;j<st.size();j++){
			res=max(res,f[n&1][i][j]);
		}
	}
	cout<<res<<endl;
    return 0;
}
